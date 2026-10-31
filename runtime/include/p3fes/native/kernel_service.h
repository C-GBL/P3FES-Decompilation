// Modernize pass, layer 6: kernel and timing (docs/MODERNIZE_PLAN.md §3 and "Layer 6 status", ADR-0017).
//
// The seam between the game's own kernel calls and the host kernel. Every kernel call of the game goes through one of
// its libkernel stubs (`li $v1, N; syscall`: the 159 thin wrappers of docs/ANALYSIS/02 and the few inline sites, all
// hand-written in game/ and reaching the runtime through the game library's hg::syscall). With `--native kernel` the
// host installs a KernelService (runtime/native/kernel/native_kernel.h) in `g_service`, and hg::syscall hands the
// call to it instead of executing the instruction: the host kernel serves it as a direct call (hle::Kernel::direct_call)
// with the same result at the same virtual time (with `--native-kernel-timing host`, the (b) set, the threads' contexts
// also live only on the host). With `g_service == nullptr` (the default) every stub executes its faithful `syscall`.
// The game library depends on headers only, so this is an interface plus an inline pointer.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/ee_types.h"

namespace p3fes::native::kernel {

class KernelService {
public:
    virtual ~KernelService() = default;
    // One kernel call from a libkernel stub: $v1 holds the call number as the stub set it (ps2sdk numbering, negative
    // for an i* form), the arguments are in $a0.. as for the instruction, `pc` is the stub's syscall address. The
    // result is in $v0 on return; a blocking or switching call may run other guest threads first, as the instruction
    // does. Called on the EE fiber.
    virtual void call(EEContext& ctx, u32 pc) = 0;
};

// Installed by the host (GameHost) while `--native kernel` is on; nullptr = the faithful path.
inline KernelService* g_service = nullptr;
inline KernelService* service() noexcept { return g_service; }

}  // namespace p3fes::native::kernel
