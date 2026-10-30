// Phase 5 support: what hand-decompiled code needs from the guest machine (game/README.md).
//
// A replaced function keeps the recompiled program's contract: it is entered through its generated
// signature `void fn_<name>_<addr>(EEContext&)` with the arguments in $a0..$a3 (and on the guest
// stack), returns through $v0/$v1, preserves the callee-saved registers, reads and writes guest RAM
// through EEContext::memory, and -- until Phase 6 moves timing to the wall clock -- charges the same
// virtual cycles on the same path and reaches rt::check_events at the same places (function entry and
// loop back-edges) as the recompiled body did (ADR-0013). tests/game/ checks all of that against the
// recompiled body kept under the __recomp symbol.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"
#include "p3fes_recomp_rt.h"

#include <cstdint>

namespace p3fes::game::guest {

// --- arguments and results (EE ABI: $a0..$a3, $v0; 32-bit values sign-extended to 64) ------------
inline u32 arg32(const EEContext& ctx, unsigned i) noexcept { return ee::core::gpr32(ctx, GPR_A0 + i); }
inline s32 args32(const EEContext& ctx, unsigned i) noexcept { return static_cast<s32>(arg32(ctx, i)); }
inline void ret32(EEContext& ctx, u32 v) noexcept { ee::core::set_gpr64(ctx, GPR_V0, ee::core::sext32(v)); }
inline void rets32(EEContext& ctx, s32 v) noexcept { ret32(ctx, static_cast<u32>(v)); }

// --- guest memory ---------------------------------------------------------------------------------
// Typed accesses through EEMemory (main RAM, scratchpad, BIOS window; an unmapped address reads zero
// and counts, as for every other guest access). Hardware windows are never touched from game code.
template <typename T> T load(const EEContext& ctx, u32 va) noexcept { return ctx.memory->read<T>(va); }
template <typename T> void store(EEContext& ctx, u32 va, const T& v) noexcept { ctx.memory->write<T>(va, v); }

// Host pointer into main RAM or the scratchpad for a naturally aligned `len`-byte item (len a power of
// two <= 16; nullptr otherwise): for walking byte strings and tables in place. Main RAM is one flat
// 32 MiB buffer, so a run that starts inside it can be read up to its end.
inline const u8* ptr(const EEContext& ctx, u32 va, u32 len = 1) noexcept { return ctx.memory->fast_ptr(va, len); }
inline u8* mutable_ptr(EEContext& ctx, u32 va, u32 len = 1) noexcept { return ctx.memory->fast_ptr(va, len); }
inline const char* cstr(const EEContext& ctx, u32 va) noexcept { return reinterpret_cast<const char*>(ptr(ctx, va)); }

// --- calling a function that is still recompiled ----------------------------------------------------
// Arguments go to $a0..$a3 (32-bit values sign-extended, as `move`/`addiu` would leave them), the callee
// runs through its generated entry point, the result is $v0. The callee charges its own cycles and
// reaches its own check points, so the caller's model only covers the caller's blocks. A recompiled
// callee preserves the callee-saved registers and restores $ra itself; nothing is saved here.
using Fn = void (*)(EEContext&);
inline u64 call(EEContext& ctx, Fn fn, u32 a0, u32 a1 = 0, u32 a2 = 0, u32 a3 = 0) {
    ee::core::set_gpr64(ctx, GPR_A0, ee::core::sext32(a0));
    ee::core::set_gpr64(ctx, GPR_A1, ee::core::sext32(a1));
    ee::core::set_gpr64(ctx, GPR_A2, ee::core::sext32(a2));
    ee::core::set_gpr64(ctx, GPR_A3, ee::core::sext32(a3));
    fn(ctx);
    return ee::core::gpr64(ctx, GPR_V0);
}

// --- a frame on the guest stack ----------------------------------------------------------------------
// A hand-written function whose original kept buffers on its stack frame and handed them to callees
// (strcpy into a local, then strcmp against it) keeps those buffers on the GUEST stack: the recompiled
// callees read and write guest RAM, and the bytes land where the recompiled body put them, so a run
// stays byte-identical even in the stack. Construction lowers $sp by `size` (as `addiu sp, sp, -size`
// did, 32-bit result sign-extended), destruction restores it (as the epilogue's `addiu sp, sp, size`),
// `at(off)` is the guest address of frame byte `off`. Register spill slots are not written: the hand
// version keeps its values in host variables (the one legitimate difference, masked by the dead-stack
// rule of tracediff and tests/game/).
class StackFrame {
public:
    StackFrame(EEContext& ctx, u32 size) noexcept
        : ctx_(ctx), base_(ee::core::gpr32(ctx, GPR_SP) - size), size_(size) {
        ee::core::set_gpr64(ctx_, GPR_SP, ee::core::sext32(base_));
    }
    ~StackFrame() { ee::core::set_gpr64(ctx_, GPR_SP, ee::core::sext32(base_ + size_)); }
    StackFrame(const StackFrame&) = delete;
    StackFrame& operator=(const StackFrame&) = delete;

    u32 base() const noexcept { return base_; }
    u32 at(u32 off) const noexcept { return base_ + off; }

private:
    EEContext& ctx_;
    u32 base_;
    u32 size_;
};

// --- virtual time (ADR-0013) ----------------------------------------------------------------------
// The recompiled body did `rt::check_events(ctx)` first and then `ctx.cycles += N` per basic block.
// A hand-written function mirrors that with `enter` once, `charge` per block it executes, and
// `backedge` where the recompiled loop had its back-edge check. The counts come from the generated
// function (recomp/generated/..., `ctx.cycles += N` lines) and are verified by tests/game/.
// `enter` and `backedge` are not noexcept: a check point can raise a fatal event (a test hook's stop, a cycle budget),
// which must unwind through whichever hand-written bodies are on the stack.
inline void enter(EEContext& ctx, u64 first_block_cycles) {
    rt::check_events(ctx);
    ctx.cycles += first_block_cycles;
}
inline void charge(EEContext& ctx, u64 cycles) noexcept { ctx.cycles += cycles; }
inline void backedge(EEContext& ctx) { rt::check_events(ctx); }

}  // namespace p3fes::game::guest
