// Host-side surface of the rt adapter (runtime/rt/, library p3fes_rt) that is not part of the
// generated-code API in recomp/include/p3fes_recomp_rt.h.
//
// The adapter implements every p3fes::rt declaration over the semantics headers
// runtime/include/p3fes/ee/*.h and EEMemory, and routes everything that is "the system" through
// the RtHooks instance installed with p3fes::set_hooks() (runtime/include/p3fes/rt_hooks.h).
// Before the first recompiled function runs, the runtime must
//   1. point EEContext::memory at the guest's EEMemory,
//   2. install its RtHooks (set_hooks; until then every hook aborts with a message), and
//   3. bind its single EEContext (ADR-0013 §1) with bind_context(), so that the stops which carry
//      no context (lookup_miss, bad_entry, unreachable, missing_function) report the live CPU
//      state to RtHooks::fatal instead of a zeroed placeholder.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::rt {

void bind_context(EEContext* ctx) noexcept;
EEContext* bound_context() noexcept;

// Reference mode (runtime/STATE.md): every Phase 5 replacement (game/replaced.txt) runs as its recompiled
// original (the fn_*__recomp body the emitter keeps) instead of the hand-written one, so the executable behaves
// like the zero-replacement build. Defined by the generated dispatch.cpp (the program's executable only); the
// generated call sites and dispatch rows read the flags through the fn_*__sel selectors. Takes effect at the next
// call: frames already running keep the body they entered.
void set_reference_mode(bool on);
bool reference_mode();
std::size_t replaced_count();

// The `kind` argument the adapter passes to RtHooks::trap: the value of p3fes::rt::Trap.
inline constexpr u32 kTrapBreak = 0;        // `break` (code = the 20-bit code field)
inline constexpr u32 kTrapUnsupported = 1;  // undecodable word emitted under --keep-going (code = the word)

} // namespace p3fes::rt
