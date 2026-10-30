// VIF1: VIFcode processing for DMAC channel 1 and the VIF1 FIFO, VU1 micro-program upload and start, unpacking
// into VU1 data memory, and DIRECT/DIRECTHL into GIF PATH2 (contract H-10..H-14, V-01..V-06; docs/ANALYSIS/10
// §2.11, §3.1, 14 §3, §6.2).
//
// Synchronous model (ADR-0013 §3): MSCAL/MSCALF/MSCNT run the VU1 interpreter to its E pair inside the call, its
// XGKICKs go to PATH1 in order; FLUSHE/FLUSH have nothing to wait for (the VU never runs concurrently and PATH1
// packets are complete or queued in the GIF), FLUSHA waits for the end of the PATH3 transfer (Gif::path3_pending:
// GIF mid-packet, stalled PATH3 data, or DMAC channel 2 still running). The VIF
// stalls (consumes fewer quadwords than offered) only when the GIF refuses PATH2 data, after a VIFcode with the
// interrupt bit, or on FBRST STP/FBK; words of a partially consumed quadword are kept internally, so the DMAC
// owner simply re-offers the unconsumed quadwords.
#pragma once

#include "p3fes/gs/gif.h"
#include "p3fes/gs/gs_pipe.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/vu1/vu1_interp.h"

#include <functional>
#include <span>
#include <vector>

namespace p3fes::gs {

enum class VifTrapKind : u8 {
    InvalidCode,     // VIFcode with an undefined CMD field (ER1)
    InvalidUnpack,   // UNPACK with vl = 3 and vn != 3 (no such format)
    VuTrap,          // the VU1 interpreter trapped (see `vu`)
    VuStepLimit,     // the VU1 program did not reach E within the step budget
    Vif0Used,        // VIF0 FIFO or DMA channel 0 data: the game never uses VIF0 (docs/ANALYSIS/10 §4)
};

struct VifTrap {
    VifTrapKind kind = VifTrapKind::InvalidCode;
    u32 code = 0;      // the VIFcode (or 0)
    vu1::Trap vu{};    // VuTrap only
};

const char* to_string(VifTrapKind k) noexcept;

// Data words of an UNPACK (VIFcode + CYCLE).
u32 unpack_data_words(u32 code, u32 cycle);
// Play-mode hook in front of every MSCAL/MSCALF/MSCNT (the native renderer, runtime/native, docs/ANALYSIS/31 §3.3).
// Whoever executes the VU1 run consults it first, with the run's inputs after the VIF's own register update
// (TOP/ITOP/DBF/TOPS: VIF state is exactly as on the exact path); `run` returns true when it handled the run itself
// (the VU1 then does not run). Today that is Vif1::run_vu on the EE fiber; with a VU1 worker stage it moves there
// with the run. `after_exact` follows every run the hook declined (diagnostics). Never installed in headless runs or
// the gates; nullptr (the default) = the exact path only.
struct VuRunInfo {
    u32 op = 0;            // 0x14 MSCAL, 0x15 MSCALF, 0x17 MSCNT
    u32 imm = 0;           // MSCAL/MSCALF entry (pairs)
    u32 top = 0, itop = 0; // as XTOP/XITOP return them
    bool gif_busy = false; // a PATH1 packet kicked now would queue behind PATH2/PATH3
};
class IVuRunHook {
public:
    virtual ~IVuRunHook() = default;
    virtual bool run(const VuRunInfo& r, vu1::VU1Interpreter& vu) = 0;
    virtual void after_exact(const VuRunInfo&, vu1::VU1Interpreter&) {}
};

struct VifStats {
    u64 codes[128] = {};     // per CMD (bits 24-30)
    u64 unpack_qwords = 0;   // qwords written to VU1 data memory
    u64 mpg_pairs = 0;
    u64 direct_qwords = 0;
    u64 vu_runs = 0;
    u64 vu_pairs = 0;
    u64 gif_stalls = 0;
    u64 interrupts = 0;
    u64 traps = 0;
};

class Vif1 {
public:
    Vif1(Gif& gif, GsCore& core, vu1::VU1Interpreter& vu) : gif_(gif), core_(core), vu_(vu) {}

    // Stream input (DMA channel 1 data or VIF1 FIFO qwords). Returns the quadwords consumed.
    std::size_t transfer(std::span<const u128> q);
    // 128-bit store to the VIF1 FIFO (0x10005000). Processed at once; kept in the backlog while stalled.
    void fifo_write(const u128& q);
    // Local -> host image data (BUSDIR = 1): reads of the FIFO / channel 1 with DIR = 0.
    u128 fifo_read();
    // Process backlog words (after a stall clears). Called by the GIF before PATH3 yields to a waiting PATH2.
    void resume();

    bool stalled() const noexcept { return stall_flags_ != 0 || gif_wait_; }

    u32 read_reg(u32 off) const;
    void write_reg(u32 off, u32 v);

    void set_bus(hle::HwBus* bus) noexcept { bus_ = bus; }
    void set_busdir_source(const u64* busdir) noexcept { busdir_ = busdir; }
    void set_trap_handler(std::function<void(const VifTrap&)> h) { trap_ = std::move(h); }
    void set_vu_step_limit(u64 n) noexcept { vu_step_limit_ = n; }
    // Threaded pipeline (gs_pipeline.h): UNPACK / MPG / VU1 runs become commands; nullptr = synchronous (default).
    void set_pipe(GsPipe* p) noexcept { pipe_ = p; }
    GsPipe* pipe() const noexcept { return pipe_; }
    // Pipeline workers: VU1 pairs of a run executed off the EE thread, and the traps they hit (reported on the EE
    // thread at the next sync point).
    void add_vu_pairs(u64 n) noexcept { stats_.vu_pairs += n; }
    void report_trap(const VifTrap& t) { report(t); }
    void set_run_hook(IVuRunHook* h) noexcept { run_hook_ = h; }
    u64 hooked_runs() const noexcept { return hooked_runs_; }
    IVuRunHook* run_hook() const noexcept { return run_hook_; }
    void note_hooked_run() noexcept {  // pipeline: the VU1 stage's hook handled a run
        ++hooked_runs_;
    }

    const VifStats& stats() const noexcept { return stats_; }

    // Register state (tests).
    void state(StateIo& io);  // machine state (gs_state.cpp)

    u32 tops() const noexcept { return tops_; }
    u32 top() const noexcept { return top_; }
    u32 itop() const noexcept { return itop_; }
    bool dbf() const noexcept { return dbf_; }

private:
    enum class State : u8 { Idle, Skip, Imm, Mpg, Unpack, Direct };

    std::size_t run_words(const u32* w, std::size_t n, bool aligned_source);
    void begin_code(u32 code);
    void finish_code();
    void exec_unpack() { exec_unpack(buf_.data(), buf_.size()); }
    void exec_unpack(const u32* words, std::size_t n);
    void run_vu(u32 op, u32 imm);
    void report(const VifTrap& t);
    void reset_state();

    Gif& gif_;
    GsCore& core_;
    vu1::VU1Interpreter& vu_;
    hle::HwBus* bus_ = nullptr;
    const u64* busdir_ = nullptr;
    std::function<void(const VifTrap&)> trap_;
    GsPipe* pipe_ = nullptr;
    u64 vu_step_limit_ = vu1::VU1Interpreter::kDefaultStepLimit;
    IVuRunHook* run_hook_ = nullptr;
    u64 hooked_runs_ = 0;

    // Registers (EE User's Manual VIF chapter).
    u32 err_ = 0, mark_ = 0, cycle_ = 0, mode_ = 0, num_ = 0, mask_ = 0, code_ = 0;
    u32 itops_ = 0, base_ = 0, ofst_ = 0, tops_ = 0, itop_ = 0, top_ = 0;
    u32 row_[4] = {}, col_[4] = {};
    bool dbf_ = false, mrk_ = false;
    u32 stall_flags_ = 0; // STAT bits VSS(8) VFS(9) VIS(10) INT(11) ER0(12) ER1(13)
    bool gif_wait_ = false;

    // Command in progress.
    State state_ = State::Idle;
    u32 cmd_ = 0;           // CMD field of the VIFcode in progress
    u32 skip_ = 0;          // alignment words to skip before the data (DIRECT: qword, MPG: 64-bit)
    u32 need_ = 0;          // data words still expected (Imm/Mpg/Unpack) or qwords (Direct)
    std::vector<u32> buf_;  // collected data words
    u32 direct_part_[4] = {};
    u32 direct_part_n_ = 0;
    u64 word_pos_ = 0;      // words consumed since reset (alignment)

    std::vector<u32> backlog_;
    const u32* mpg_src_ = nullptr;  // first payload word of the MPG being received (p3fes/prof.h attribution)
    VifStats stats_{};
};

// VIF1 registers device (physical 0x10003C00-0x10003D80).
class Vif1RegsDevice final : public hle::HwDevice {
public:
    static constexpr u32 kBase = 0x10003C00u;
    static constexpr u32 kEnd = 0x10003D80u;
    explicit Vif1RegsDevice(Vif1& vif) : vif_(vif) {}
    u32 read32(u32 pa) override { return vif_.read_reg(pa - kBase); }
    void write32(u32 pa, u32 v) override { vif_.write_reg(pa - kBase, v); }
    u64 read64(u32 pa) override { return read32(pa); }
    void write64(u32 pa, u64 v) override { write32(pa, static_cast<u32>(v)); }

private:
    Vif1& vif_;
};

// VIF1 FIFO (physical 0x10005000-0x10005010), 128-bit.
class Vif1FifoDevice final : public hle::HwDevice {
public:
    static constexpr u32 kBase = 0x10005000u;
    static constexpr u32 kEnd = 0x10005010u;
    explicit Vif1FifoDevice(Vif1& vif) : vif_(vif) {}
    void write128(u32, const u128& v) override { vif_.fifo_write(v); }
    u128 read128(u32) override { return vif_.fifo_read(); }
    u64 read64(u32) override { return vif_.fifo_read().u64[0]; }

private:
    Vif1& vif_;
};

// DMAC channel 1 data path. With BUSDIR = 1 (local -> host, D1_CHCR.DIR = 0) the transfer fills `data` from the GS.
class Vif1DmaHandler final : public hle::DmaChannelHandler {
public:
    Vif1DmaHandler(Vif1& vif, const u64* busdir) : vif_(vif), busdir_(busdir) {}
    std::size_t transfer(u128* data, std::size_t qwc, u64 tag) override;

private:
    Vif1& vif_;
    const u64* busdir_;
};

// VIF0: registers accepted (the game resets it and ORs VIF0_ERR, B-42/B-55), data traps.
class Vif0StubDevice final : public hle::HwDevice {
public:
    static constexpr u32 kBase = 0x10003800u;
    static constexpr u32 kEnd = 0x10003980u;
    static constexpr u32 kFifoBase = 0x10004000u;
    static constexpr u32 kFifoEnd = 0x10004010u;
    explicit Vif0StubDevice(std::function<void(const VifTrap&)>* trap) : trap_(trap) {}
    u32 read32(u32 pa) override;
    void write32(u32 pa, u32 v) override;
    u64 read64(u32 pa) override { return read32(pa); }
    void write64(u32 pa, u64 v) override { write32(pa, static_cast<u32>(v)); }
    void write128(u32 pa, const u128& v) override;
    u64 data_traps() const noexcept { return data_traps_; }
    void state(StateIo& io);  // machine state (gs_state.cpp)

private:
    std::function<void(const VifTrap&)>* trap_;
    u32 err_ = 0, mark_ = 0;
    u64 data_traps_ = 0;
};

class Vif0DmaTrap final : public hle::DmaChannelHandler {
public:
    explicit Vif0DmaTrap(Vif0StubDevice& dev) : dev_(dev) {}
    std::size_t transfer(u128* data, std::size_t qwc, u64 tag) override;

private:
    Vif0StubDevice& dev_;
};

} // namespace p3fes::gs
