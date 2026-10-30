// Ahead-of-time compiled VU1 microprograms (docs/ANALYSIS/24_vu1_acceleration.md).
//
// The 114 microprograms are static data in the ELF (14 §1), every branch stays inside its program (09 §0) and the
// instruction set is closed (43 upper / 45 lower), so `p3fes_vu1_aotgen` translates each program into one C++
// function ahead of time, the way `p3fes_recomp` does for the EE: straight-line code per pair with every field
// decoded at generation time, branches as gotos, `JR` through a switch over the program's labels. The compiled code
// executes the interpreter's pair semantics exactly (vu1_semantics.h is shared; the Q-read classification and the
// DIV/RSQRT latency of every pc are precomputed with the interpreter's own analysis, vu1_qtiming.h) on the same
// `VU1State`, so it can hand the run to the interpreter at any pair boundary ("bail out") and the interpreter
// finishes it: branch in a delay slot, an encoding outside the census (the interpreter then traps), a `JR` to a pc
// that is not a label, the step limit, a non-canonical vf00/vi00 at entry.
//
// A compiled program runs only when micro memory holds its image from address 0 and nothing outside the image can
// change a precomputed Q decision: the pairs outside the program that the analysis read must be what the generator
// assumed, and no branch outside the program may target a pc whose predecessors the analysis enumerated. Both are
// checked once per micro-memory generation (`AotIndex::resident`).
//
// The interpreter stays the default and the oracle: `VU1Interpreter::set_mode(Mode::Aot)` turns this path on,
// `Mode::Diff` runs both on every MSCAL/MSCNT and compares the complete outcome.
#pragma once

#include "p3fes/ee_types.h"
#include "p3fes/vu1/vu1_interp.h"

#include <cstddef>
#include <vector>

namespace p3fes::vu1 {

// What a compiled program calls back into (XGKICK goes through the interpreter's sink and statistics).
class AotHost {
public:
    virtual void xgkick(u32 qword_addr) = 0;

protected:
    ~AotHost() = default;
};

// Result of a compiled run. `ended`: the pair after E executed and the unit stopped (TPC set). Otherwise the code
// bailed out: the state is at a pair boundary with `running` set, and the interpreter continues from it.
struct AotResult {
    bool ended = false;
    u64 steps = 0;
};

using AotFn = AotResult (*)(VU1State& s, AotHost& host, u32 start_pc, u64 step_limit);

struct AotOutsideRead {
    u16 pair; // pair index outside [0, pairs)
    u32 lo, hi; // the words the generator assumed there
};

// A Q-reading pc: its compiled classification (detail::QRead: 0 Dynamic, 1 New, 2 Old) and the pairs whose jump-list
// predecessors the classification enumerated (qnodes[first .. first + count)).
struct AotQReader {
    u16 pair;
    u8 kind;
    u32 first, count;
};

struct AotProgram {
    const char* name;        // "vu1_prog_064_g3_skin" (census name)
    u32 code_va;             // VA of the first MPG code in the ELF
    const u8* image;         // the program as uploaded at micro address 0
    u32 pairs;
    AotFn fn;
    const AotOutsideRead* outside; // footprint of the precomputed Q analysis outside the image
    u32 outside_count;
    const u64* expanded;     // 2048-bit set: pairs whose jump-list predecessors the Q analysis enumerated
    const AotQReader* qreaders;
    u32 qreader_count;
    const u16* qnodes;
};

// The compiled programs need SSE4.1 (blends, PEXTRD; vu1_aot_rt.h), and AVX2 with OS YMM support when built with
// P3FES_VU1_AOT_ARCH=AVX2 (the default). Checked once (CPUID); without it every
// run takes the interpreter.
bool aot_cpu_ok() noexcept;
// FMAC ops the compiled code redid with fp:: lane by lane (an exponent-255 operand or an overflow; vu1_aot_rt.h),
// counted over the process (all engines).
namespace detail {
extern u64 g_aot_slow_ops;
extern bool g_aot_slow_trace; // P3FES_VU1_SLOW_SITES=1: also count the slow ops per (program, pc)
extern u32 g_aot_cur_va;      // code VA of the compiled program running (set by its driver)
void aot_note_slow(u32 code_va, u32 pc) noexcept;
}
inline u64 aot_slow_ops() noexcept { return detail::g_aot_slow_ops; }
struct AotSlowSite {
    u32 code_va, pc;
    u64 count;
};
// The most frequent slow-path sites (empty unless P3FES_VU1_SLOW_SITES=1), most frequent first.
std::vector<AotSlowSite> aot_slow_sites(std::size_t max);

// The generated table (vu1_aot_programs.cpp when built with P3FES_VU1_AOT=ON; empty otherwise).
std::size_t aot_program_count() noexcept;
const AotProgram* aot_programs() noexcept;

// Re-runs the interpreter's Q-read classification on the real micro memory for every compiled reader whose
// enumerated pairs include one of `targets` (2048-bit set) and says whether all of them keep their compiled kind.
using AotQVerifier = bool (*)(void* ctx, const AotProgram& p, const u64* targets);

// Resident-program lookup over the compiled table, cached per micro generation. When code outside the image
// branches into pairs the precomputed Q analysis enumerated, the affected classifications are recomputed by
// `verify`; the verdict is cached by the content of micro memory outside the image.
class AotIndex {
public:
    // The compiled program that may run on this micro memory, or nullptr.
    const AotProgram* resident(const MicroMemory& micro, AotQVerifier verify = nullptr, void* ctx = nullptr);
    u64 checks() const noexcept { return checks_; }
    u64 rejected_footprint() const noexcept { return rejected_; }
    u64 verified() const noexcept { return verified_; }   // Q re-classifications run (cache misses)
    u64 verify_hits() const noexcept { return verify_hits_; }

private:
    struct Verdict {
        const AotProgram* program;
        u64 hash;
        std::vector<u8> outside;
        bool ok;
    };
    u64 generation_ = 0;
    const AotProgram* cached_ = nullptr;
    u64 checks_ = 0, rejected_ = 0, verified_ = 0, verify_hits_ = 0;
    std::vector<Verdict> verdicts_;
};

} // namespace p3fes::vu1
