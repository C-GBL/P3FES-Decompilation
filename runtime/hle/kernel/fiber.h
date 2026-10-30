// The kernel's own fibers (replacing Win32 fibers, 2026-10-21): a stack-switching primitive whose saved
// context is plain data, so a machine state can carry each guest thread's host stack and resume it in a fresh
// process (runtime/STATE.md). Stacks come from the fixed slots of p3fes/pinned.h when the host enabled them
// (the stack addresses, and therefore every frame pointer and address of a local on them, are equal in every
// process), else from VirtualAlloc (tests).
//
// p3fes_fiber_switch (fiber_switch_x64.asm) saves the Win64 callee-saved state of the running code on its own
// stack -- rbx rbp rdi rsi r12-r15, xmm6-xmm15, MXCSR and the x87 control word (what FIBER_FLAG_FLOAT_SWITCH
// kept) -- stores rsp and the TEB stack bounds (StackBase, StackLimit, DeallocationStack) into `save`, loads
// `load`'s and returns into the code that switched away from `load` (or into p3fes_fiber_start for a new fiber).
#pragma once

#include <cstddef>
#include <cstdint>

namespace p3fes::hle::kc {

struct FiberCtx {
    void* rsp = nullptr;
    void* stack_base = nullptr;   // TEB StackBase (high end)
    void* stack_limit = nullptr;  // TEB StackLimit (low end of the committed stack)
    void* dealloc = nullptr;      // TEB DeallocationStack
};

using FiberEntry = void (*)(void* arg);

struct Fiber {
    FiberCtx ctx{};
    std::uint8_t* lo = nullptr;  // stack [lo, hi)
    std::uint8_t* hi = nullptr;
    int slot = -1;               // pinned slot index; -1 = VirtualAlloc'd
    void* alloc_base = nullptr;  // VirtualAlloc base (slot == -1)
};

// Prepares `f`'s stack so that the first switch to it calls entry(arg) (which must never return).
void fiber_prepare(Fiber& f, FiberEntry entry, void* arg);

} // namespace p3fes::hle::kc

extern "C" void p3fes_fiber_switch(p3fes::hle::kc::FiberCtx* save, const p3fes::hle::kc::FiberCtx* load);
extern "C" void p3fes_fiber_start();
