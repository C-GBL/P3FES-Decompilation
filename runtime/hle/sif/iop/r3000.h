// R3000 (MIPS I) interpreter for the IOP modules the IOP HLE runs in place (ADR-0014 "B-lite":
// SDRDRV, SKSOUND, SKHSYNTH, SKSESQ, MODSESQ, MODHSYN -- 80,592 bytes of plain MIPS I text, no FPU,
// no COP2, no COP0 instruction in their .text; docs/ANALYSIS/19 §2.1). Integer set only: SPECIAL
// shifts/ALU/jumps/HI-LO/mult/div, REGIMM, J/JAL, branches, immediates, LB/LH/LW/LBU/LHU/SB/SH/SW
// and the LWL/LWR/SWL/SWR merges; branch delay slots through a pc/npc pair; load delay slots are not
// modelled (compiler-scheduled code never reads the loaded register in the slot; the six modules'
// listings were checked for that with ps2dev objdump).
//
// Host calls: the IRX loader rewrites an import stub's first word into opcode 0x3F (unused in MIPS I)
// with a 26-bit host-call id; executing it invokes the registered std::function with the CPU, which
// reads a0..a3 (+ stack words) and writes v0/v1, then execution continues at ra -- a HLE'd library
// function costs one interpreted instruction. A host call may `request_stop()` (thread switch) so the
// kernel regains control right after it. Running stops at a `return sentinel` (pc == kExitSentinel,
// what a thread's entry function returns to), on a trap (reserved word, hardware access, misaligned
// access) or when the step budget is spent.
//
// Provenance: dispatch shape and the LWL/LWR/SWL/SWR shift formulas follow the MIT reference
// ps2-web-recomp `runtime/src/iop/cpu.cpp` @ c0f476e (Copyright (c) 2026 Samir Nuri); written against
// IopRam with our own stop/trap/host-call model. THIRD_PARTY_NOTICES.md "ps2-web-recomp (IOP R3000)".
#pragma once

#include <cstddef>
#include <functional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "iop_core.h"

namespace p3fes::hle::sif::iop {

inline constexpr u32 kHleOpcode = 0x3Fu;                 // major opcode of a host-call word
inline constexpr u32 kHleIdMask = 0x03FFFFFFu;
inline constexpr u32 kExitSentinel = 0xBFC00000u;        // the IOP reset vector: never module code
inline constexpr u32 kHwBase = 0x1F800000u;              // IOP hardware registers (no module touches them)

struct R3000State {
    u32 r[32]{};
    u32 hi = 0, lo = 0;
    u32 pc = 0, npc = 4;
};

class R3000 {
public:
    using HostCall = std::function<void(R3000&)>;
    enum class Stop { Budget, Sentinel, HostStop, Trap };
    struct Result {
        Stop stop = Stop::Budget;
        u32 pc = 0;        // address of the stopping instruction (Trap) / the sentinel
        u32 word = 0;      // the offending word (Trap)
        std::string what;  // trap description
    };

    explicit R3000(detail::IopRam& ram);

    R3000State& state() { return s_; }
    const R3000State& state() const { return s_; }
    detail::IopRam& ram() { return ram_; }

    // Registers a host call; returns its id (the loader writes it into the stub).
    u32 register_host_call(std::string name, HostCall fn);
    std::string_view host_call_name(u32 id) const;
    u32 host_call_count() const { return static_cast<u32>(calls_.size()); }

    // Runs at most `budget` instructions.
    Result run(u64 budget);
    void request_stop() { stop_requested_ = true; }
    u64 instructions() const { return instructions_; }   // retired since construction
    u64 host_calls_made() const { return host_calls_made_; }

    // ---- memory (addresses masked to the 2 MiB window; out-of-window accesses trap inside run) --------
    u8 read8(u32 a) const;
    u16 read16(u32 a) const;
    u32 read32(u32 a) const;
    void write8(u32 a, u8 v);
    void write16(u32 a, u16 v);
    void write32(u32 a, u32 v);
    std::string c_string(u32 a, std::size_t max = 256) const;
    // Call-argument i of the current host call (a0..a3, then the caller's stack from sp + 16).
    u32 arg(unsigned i) const;
    void set_result(u32 v0) { s_.r[2] = v0; }
    void set_result64(u32 v0, u32 v1) { s_.r[2] = v0; s_.r[3] = v1; }
    void state(StateIo& io);  // machine state (iop_state.cpp); the host-call table is wiring

private:
    detail::IopRam& ram_;
    u8* mem_;  // 2 MiB
    R3000State s_{};
    std::vector<std::pair<std::string, HostCall>> calls_;
    bool stop_requested_ = false;
    u64 instructions_ = 0;
    u64 host_calls_made_ = 0;
    bool trapped_ = false;
    Result trap_{};
    void trap(u32 pc, u32 word, std::string what);
    bool check_addr(u32 a, u32 size, u32 pc, u32 word);
};

}  // namespace p3fes::hle::sif::iop
