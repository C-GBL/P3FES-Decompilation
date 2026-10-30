// The boundary between the rt adapter (implements `p3fes::rt`, recomp/include/p3fes_recomp_rt.h)
// and the kernel/timing HLE (ADR-0013). The adapter owns register semantics and guest RAM
// access; everything that is "the system" -- syscalls, interrupt delivery, hardware registers,
// traps -- goes through one `RtHooks` instance installed with `set_hooks()`.
//
// Single-threaded contract (ADR-0013 §1): every call happens on the host thread that runs guest
// code, from the fiber of the current guest thread. `syscall` and `check_events` may switch
// fibers and return later on the same fiber with `ctx` updated; the adapter must re-read `ctx`
// after them and never cache guest state across them.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes {

namespace hle { class HwBus; }

class RtHooks {
public:
    virtual ~RtHooks() = default;

    // `syscall` instruction at `pc`; the number is in $v1 (negative = the i* / interrupt-context
    // form, ADR-0013 §4 / docs/ANALYSIS/15 §7). Returns with $v0 set (and $v1 for the few that
    // return two values) after any thread switch has completed.
    virtual void syscall(EEContext& ctx, u32 pc) = 0;

    // Check point (ADR-0013 §2): called by generated code at every function entry and loop
    // back-edge, and by the adapter after every hardware-register access. The implementation
    // compares `ctx.cycles` against the next event deadline and, when due, advances the time
    // base, raises/delivers interrupts (handler chains run as nested calls on the current
    // fiber, docs/ANALYSIS/15 §2.3) and may preempt (switch fibers). Must be cheap when nothing
    // is due: one compare.
    virtual void check_events(EEContext& ctx) = 0;

    // Optional: the address of the "next event deadline" that check_events compares ctx.cycles with.
    // When provided, the adapter's inline check point (recomp/include/p3fes_recomp_rt_inline.h) does
    // that compare itself and calls check_events only when ctx.cycles >= *deadline_ptr(); the
    // implementation must keep the value current (lower it to force a check). nullptr (default):
    // every check point calls check_events.
    virtual const u64* deadline_ptr() const { return nullptr; }

    // Hardware-register windows (EEMemory::is_hw after ADR-0013: 0x10000000-0x1000FFFF and
    // 0x12000000-0x12001FFF, physical). The adapter calls these for any access that resolves
    // there instead of touching RAM.
    virtual hle::HwBus& bus() = 0;

    // Fatal and non-fatal guest events the adapter cannot decide alone. `trap` may return
    // (debugger-style resume at pc + 4 for `break`); the others never return.
    virtual void trap(EEContext& ctx, u32 pc, u32 kind, u32 code) = 0;
    [[noreturn]] virtual void fatal(EEContext& ctx, u32 pc, const char* what) = 0;

    // CTC2 to a COP2 control register whose effect is on the VU1 side: vi28 FBRST (bit 9 RS1 resets VU1,
    // bit 8 FB1 force-breaks it; B-42/B-43). The adapter keeps no state for it (CFC2 of vi28/vi29 reads 0:
    // VU1 never runs concurrently, so VPU_STAT's busy bits are clear); the device owner decides. Default:
    // ignored.
    virtual void vu_control_write(EEContext& ctx, u32 reg, u32 value) {
        (void)ctx;
        (void)reg;
        (void)value;
    }
};

// Installed once by the runtime before the first recompiled function runs; never changed while
// guest code is on any fiber's stack.
void set_hooks(RtHooks* hooks);
RtHooks& hooks();

} // namespace p3fes
