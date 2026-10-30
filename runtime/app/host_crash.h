// Last-chance report for a host crash (an exception nothing handled: access violation, stack overflow, ...).
//
// Installed by main.cpp. Prints to stderr: the exception code and address (module + RVA, symbol when a PDB is
// present), the faulting address for access violations, the host stack (StackWalk64 from the exception context),
// the recompiled guest frames on it (host_backtrace.h) and one line of guest state from the callback, then flushes
// stdout/stderr and lets the process end with the same exception code. Diagnostics only: the guest never sees it.
// Uses SetUnhandledExceptionFilter, so first-chance users (host_watch.cpp's vectored guard-page handler) are not
// affected.
#pragma once

#include <string>

namespace p3fes::app {

using CrashContextFn = std::string (*)(void* user);

void install_crash_reporter();
// Optional one-line description of the guest state at the crash (e.g. vblank, cycles, thread); nullptr clears.
void set_crash_context(CrashContextFn fn, void* user);

} // namespace p3fes::app
