// Fixed-address host memory for machine-state save/restore (runtime/STATE.md).
//
// A saved machine state includes the host stacks of the suspended guest threads (each guest thread runs on a
// fiber whose frames are the recompiled call chain), and those frames hold host pointers: the EEContext, the
// kernel object, guest RAM. A state can only be resumed in a fresh process if those objects sit at the same
// addresses there, so the host reserves two regions at fixed virtual addresses before it builds the runtime:
//   * the arena: a bump allocator for the objects the frames point into (EEMemory's RAM / scratchpad / BIOS
//     buffers, the EEContext, the kernel's KernelHooks); the host allocates them in the same order in every
//     process, so they land at the same addresses;
//   * the fiber region: kFiberSlots fixed stack slots for the guest-thread fibers (kernel scheduler).
// Nothing is ever freed back to the arena (process lifetime). Without `enable()` (tests, tools) alloc()
// returns nullptr and callers use the normal heap; a state cannot be saved then.
#pragma once

#include <cstddef>
#include <cstdint>

namespace p3fes::pinned {

inline constexpr std::uintptr_t kArenaBase = 0x00005E0000000000ull;
inline constexpr std::size_t kArenaBytes = 256ull << 20;  // reserved; committed as allocated
inline constexpr std::uintptr_t kFiberBase = 0x00005E1000000000ull;
inline constexpr std::size_t kFiberSlots = 128;
inline constexpr std::size_t kFiberGuardBytes = 64ull << 10;    // reserved, never committed (overflow faults)
inline constexpr std::size_t kFiberStackBytes = 1ull << 20;     // committed per slot on first use
inline constexpr std::size_t kFiberSlotStride = kFiberGuardBytes + kFiberStackBytes;

// Reserves both regions (idempotent). false: an address is taken (logged once); alloc() then returns nullptr.
bool enable();
bool enabled();

// Bump allocation from the arena (committed, zero-filled). nullptr when not enabled or exhausted.
void* alloc(std::size_t bytes, std::size_t align = 64);
// Bytes handed out so far (the state header records it: equal order of allocation in both processes).
std::size_t arena_used();
bool owns(const void* p);

// Fiber stack slot i: [lo, hi) committed (hi 16-byte aligned); nullptr when not enabled or i out of range.
// Commits the slot on first use.
void* fiber_slot_lo(std::size_t i);
void* fiber_slot_hi(std::size_t i);

} // namespace p3fes::pinned
