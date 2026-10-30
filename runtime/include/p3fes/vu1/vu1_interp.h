// VU1 micro-program interpreter (Phase 3, docs/ANALYSIS/09_vu1_micro_census.md §4).
//
// Executes exactly the instruction set of the 114 programs the game uploads (43 upper + 45 lower mnemonics, I and E
// flags) and traps, without executing any part of the pair, on every other encoding: undefined words, defined ops
// no program uses (SQRT, R ops, status-flag ops, JALR, most EFU ops, ABS ...) and the M/D/T flags. The semantics
// are ported from ps2-web-recomp @ c0f476e (`runtime/src/vu_micro.cpp` `run()`/`upper()`/`lower()`, the
// `vuops::FlagPipe` and Q timing model of `runtime/include/ps2/vu_ops.hpp`); the float datapath is
// `p3fes/ee/fpu.h` (the same bit-level model upstream's exact path uses). See README.md for the model and its limits.
//
// Execution model (upstream): one pair per step. The upper op reads registers before the lower op runs and commits
// after it, so the upper result wins when both write the same vf. Branches have one delay slot; every PC is masked
// with 0x3FFF. The pair carrying E executes, then exactly one more pair, then the unit stops and TPC holds the
// address of the following pair: MSCNT resumes there (09 §2.4: "the pair after the E pair").
#pragma once

#include "p3fes/ee_types.h"
#include "p3fes/vu1/vu1_decode.h"

#include <array>
#include <memory>
#include <span>
#include <string_view>

namespace p3fes {
class StateIo;  // p3fes/state_io.h (machine states)
}

namespace p3fes::vu1 {

struct VU1Profile; // vu1_profile.h
class AotIndex;    // vu1_aot.h

// Receiver of PATH1 GIF packets. `kick` is called synchronously while the XGKICK pair executes with the complete
// packet: the GIF tags and their data from the kicked qword up to and including the last data qword of the first
// tag with EOP set, copied out of VU1 data memory (addresses wrap at 1024 qwords; at most 1024 qwords per kick). The
// span is valid only during the call. A synchronous copy is safe for the game's programs because they alternate two
// output buffers (09 §2.3). Kicks that hit the 1024-qword bound before an EOP tag are delivered truncated and counted
// in VU1Stats::kicks_without_eop.
class IGifSink {
public:
    virtual ~IGifSink() = default;
    virtual void kick(std::span<const u128> qwords) = 0;
};

// 16 KiB micro memory. Writes go through `write`, which bumps `generation()` when a byte changes (re-uploading the
// resident code leaves it alone): decode and Q-timing caches key on it, so code can never change behind the
// interpreter's back.
class MicroMemory {
public:
    std::span<const u8, kMicroBytes> bytes() const noexcept { return std::span<const u8, kMicroBytes>(bytes_); }
    u32 lower_word(u32 byte_pc) const noexcept; // bytes 0..3 of the pair at byte_pc & 0x3FF8
    u32 upper_word(u32 byte_pc) const noexcept; // bytes 4..7
    // Copy `src` to byte_offset (wrapping at 16 KiB, like VIF MPG), invalidating cached decodes.
    void write(u32 byte_offset, std::span<const u8> src) noexcept;
    void clear() noexcept;
    u64 generation() const noexcept { return generation_; }

private:
    alignas(16) std::array<u8, kMicroBytes> bytes_{};
    u64 generation_ = 1;
};

// Port of upstream vuops::FlagPipe: timestamped MAC/status/clip history (a reader at time t sees the newest MAC
// value written at or before t - 4 and the newest clip value written at or before t - 3) and the pending Q result.
// Reset at the start of every run; `t` counts pairs from 16.
struct FlagPipe {
    u32 t = 16;
    std::array<u32, 8> mac_ts{}, mac_v{}, status_v{}, clip_ts{}, clip_v{};
    u32 mh = 0, ch = 0;
    u32 q_value = 0; // result of the last DIV/RSQRT, not yet visible in VU1State::q
    u32 q_ready = 0; // value of t from which a time-synchronised read sees q_value
    bool q_pending = false;
};

struct VU1State {
    // Registers as raw bit patterns. vf00 is (0, 0, 0, 1.0) and vi00 is 0 after every pair.
    u32 vf[32][4] = {{0u, 0u, 0u, 0x3F800000u}};
    u16 vi[16] = {};
    u32 acc[4] = {};
    u32 q = 0, p = 0, i = 0, r = 0;
    u32 mac = 0;    // MAC flags of the newest flag-setting upper op: Z bits 3..0, S 7..4, O 15..12 (x = high bit)
    u32 status = 0; // Z S U O I D (bits 0..5) + sticky ZS SS US OS (6..9); kept, no census op reads it
    u32 clip = 0;   // 24-bit clip history, newest CLIP judgement in bits 5..0
    u32 top = 0, itop = 0; // VIF1 TOP / ITOP as XTOP / XITOP return them (set_tops)
    u32 pc = 0;   // byte address of the next pair
    u32 npc = 8;  // byte address of the pair after it (a taken branch rewrites it: the delay slot)
    u32 tpc = 0;  // MSCNT resume address, written when a run ends
    bool running = false;
    bool ending = false; // the E pair has executed: stop after the current (delay) pair
    // Upstream BranchView: conditional branches read the vi values from before the previous pair's lower op, unless
    // that op was a flag read (FCAND, FMAND ...), BAL/JALR, or absent (LOI). PCSX2's "branch VI delay".
    u16 vi_before[16] = {};
    bool vi_delay_live = false;
    FlagPipe pipe{};
    MicroMemory micro{};
    alignas(16) u8 data[kDataBytes] = {}; // persists across MSCAL/MSCNT (09 §2.5)
};

enum class TrapKind : u8 {
    None,
    UndefinedUpper,  // no upper instruction has this encoding
    UndefinedLower,  // no lower instruction has this encoding
    UncensusedUpper, // defined, but used by none of the 114 programs: not implemented (fail closed)
    UncensusedLower,
    DebugFlag,       // M, D or T flag set (never set in the 114 programs)
};

struct Trap {
    TrapKind kind = TrapKind::None;
    u32 pc = 0; // byte address of the pair, which did not execute
    u32 lo = 0;
    u32 hi = 0;
    std::string_view upper{}; // decoded mnemonics, "UNKNOWN" for undefined halves
    std::string_view lower{};
};

std::string_view to_string(TrapKind kind) noexcept;

enum class RunStatus : u8 {
    Running,   // step(): the pair executed and the unit is still running
    Ended,     // the pair after the E pair executed; TPC is set
    StepLimit, // run(): the step budget ran out; still running, run() continues
    Trapped,   // see trap()
    Idle,      // nothing to execute
};

struct RunResult {
    RunStatus status = RunStatus::Idle;
    u64 steps = 0; // pairs executed by this call
};

struct VU1Stats {
    u64 pairs = 0;             // pairs executed since construction / reset_stats()
    u64 kicks = 0;
    u64 kick_qwords = 0;
    u64 kicks_without_eop = 0; // truncated at 1024 qwords
};

// Which engine executes MSCAL/MSCNT (docs/ANALYSIS/24_vu1_acceleration.md). Interp is the default and the oracle.
// Aot runs the ahead-of-time compiled program when the resident micro memory is one (vu1_aot.h) and the interpreter
// otherwise or after a bail-out. Diff runs the interpreter and the Aot path from the same state on every run,
// compares registers, flags, pipes, data memory, kicked packets, status and step counts, keeps the interpreter's
// outcome and counts mismatches (VU1AotStats; the first ones are described on stderr).
enum class VU1Mode : u8 { Interp, Aot, Diff };

struct VU1AotStats {
    u64 compiled_runs = 0;  // runs that entered compiled code
    u64 bails = 0;          // of those, handed to the interpreter before E
    u64 compiled_pairs = 0; // pairs executed by compiled code
    u64 interp_runs = 0;    // Aot/Diff runs with no usable compiled program resident
    u64 diff_runs = 0;
    u64 diff_mismatches = 0;
    // Census of the interpreted runs: the first 8 bytes of micro memory of up to 8 distinct images and their run
    // counts (a full-AOT build should leave this empty; docs/ANALYSIS/24 §8).
    struct InterpImage {
        u64 head = 0;
        u64 runs = 0;
    };
    InterpImage interp_images[8]{};
};

// Holds ~70 KiB (state + caches): allocate on the heap.
class VU1Interpreter {
public:
    static constexpr u64 kDefaultStepLimit = 1'000'000; // upstream's runaway guard

    explicit VU1Interpreter(IGifSink* sink = nullptr);
    ~VU1Interpreter();
    VU1Interpreter(const VU1Interpreter&) = delete;
    VU1Interpreter& operator=(const VU1Interpreter&) = delete;

    VU1State& state() noexcept { return s_; }
    const VU1State& state() const noexcept { return s_; }
    void set_sink(IGifSink* sink) noexcept { sink_ = sink; }

    // Power-on registers and flags (upstream `reset`): micro and data memory are kept, TOP/ITOP cleared.
    void reset() noexcept;
    void load_micro(u32 byte_offset, std::span<const u8> bytes) noexcept;
    void set_tops(u32 top, u32 itop) noexcept {
        s_.top = top;
        s_.itop = itop;
    }

    // VIF1 entry points. `imm` is the VIFcode immediate: the pair index, i.e. byte address / 8.
    RunResult mscal(u32 imm, u64 step_limit = kDefaultStepLimit);
    // Same as MSCAL: the synchronous model has no in-flight GIF transfer or VU1 run to wait for.
    RunResult mscalf(u32 imm, u64 step_limit = kDefaultStepLimit) { return mscal(imm, step_limit); }
    RunResult mscnt(u64 step_limit = kDefaultStepLimit); // resume at TPC

    // Fine-grained control: start a run at byte_pc (resets the flag/Q pipe like upstream's run entry), then step.
    void start(u32 byte_pc) noexcept;
    RunResult step();
    RunResult run(u64 step_limit = kDefaultStepLimit);

    const Trap& trap() const noexcept { return trap_; }
    const VU1Stats& stats() const noexcept { return stats_; }
    void reset_stats() noexcept { stats_ = {}; }
    void set_mode(VU1Mode mode);
    VU1Mode mode() const noexcept { return mode_; }
    const VU1AotStats& aot_stats() const noexcept { return aot_stats_; }
    // Opt-in workload accounting (vu1_profile.h); nullptr = off. Not owned.
    void set_profile(VU1Profile* profile) noexcept { profile_ = profile; }
    // Machine state (p3fes/state_io.h): registers, flag pipeline, micro and data memory, counters. The decode
    // caches and the AOT residency index are rebuilt from micro memory after a load; the mode is the host's.
    void state(StateIo& io);
    VU1Profile* profile() const noexcept { return profile_; }

private:
    struct Caches;

    const DecodedPair& fetch(u32 byte_pc);
    void sync_caches();
    void read_q(u32 pc, const DecodedPair& d);
    u32 q_delay_of(u32 pc, u32 latency);
    bool lower(const DecodedPair& d, u32 pc, u32& target);
    void xgkick(u32 qword_addr);
    void flush_q() noexcept;
    RunResult profiled_run(u32 byte_pc, u64 step_limit);
    RunResult exec_run(u32 byte_pc, u64 step_limit);
    RunResult aot_run(u32 byte_pc, u64 step_limit);
    RunResult diff_run(u32 byte_pc, u64 step_limit);
    struct Host;
    struct DiffScratch;
    static bool verify_q(void* ctx, const struct AotProgram& p, const u64* targets);

    VU1State s_{};
    IGifSink* sink_ = nullptr;
    Trap trap_{};
    VU1Stats stats_{};
    std::unique_ptr<Caches> caches_;
    VU1Profile* profile_ = nullptr;
    u64 c_kick_ns_ = 0;
    VU1Mode mode_ = VU1Mode::Interp;
    VU1AotStats aot_stats_{};
    std::unique_ptr<AotIndex> aot_index_;
    std::unique_ptr<DiffScratch> diff_;
};

} // namespace p3fes::vu1
