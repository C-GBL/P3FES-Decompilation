// Layer 6's inventory report (`--kernel-census FILE`; docs/MODERNIZE_PLAN.md "Layer 6 status"): the kernel's
// KernelCensus (p3fes/hle/kernel.h) of one run written as text -- the scheduler's work, every syscall with its callers,
// the interrupt chains and handlers, the DMAC channels, timers, semaphores and every hardware register the guest
// touched, with the guest functions behind each count. Diagnostics only: the census never changes what the guest sees.
#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

#include "guest_symbols.h"
#include "p3fes/hle/kernel.h"

namespace p3fes::app {

struct KernelCensusContext {
    std::string route;   // free text (the census file's name by default)
    std::string native;  // the --native set
    std::uint64_t cycles = 0, flips = 0;
};

void write_kernel_census(std::FILE* f, const hle::KernelCensus& c, const GuestSymbols& syms, const KernelCensusContext& x);

}  // namespace p3fes::app
