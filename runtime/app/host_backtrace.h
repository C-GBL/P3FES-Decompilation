// Host-stack view of the recompiled guest call chain, for diagnostics only.
//
// Recompiled functions are host functions named `p3fes::recomp_gen::fn_<name>_<addr8>` (recomp/README.md
// "Names"), and guest calls are host calls, so the host stack of the current fiber *is* the guest call
// chain. Resolving return addresses with DbgHelp (needs the PDB; Debug and RelWithDebInfo builds have one)
// gives the exact guest functions active at a fatal or a traced access, which the generated code does not
// otherwise record (it maintains no guest pc, runtime/rt/README.md "No pc for memory faults").
#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace p3fes::app {

struct GuestFrame {
    std::uint32_t va = 0;  // start (or mid-body entry) of the recompiled function
    std::string host_name; // the generated function's name
};

// Innermost first; at most `max_frames` recompiled frames (host frames in between are skipped).
std::vector<GuestFrame> guest_backtrace(unsigned max_frames);
// The same from a captured Win32 CONTEXT (an exception's, host_watch.cpp), walked with StackWalk64.
std::vector<GuestFrame> guest_backtrace_from_context(const void* win32_context, unsigned max_frames);

} // namespace p3fes::app
