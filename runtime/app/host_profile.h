// In-process sampling profiler for the host (`p3fes --profile FILE [--profile-us N]`), diagnostics only.
//
// A sampler thread suspends the thread that runs the guest every N microseconds (default 1000), reads its RIP
// (GetThreadContext), unwinds up to 7 callers from the x64 unwind tables, resumes it and stores the addresses in a
// preallocated buffer -- nothing is allocated or symbolised while the target is suspended (it may hold the heap
// lock). At stop, the unique addresses are resolved with DbgHelp (the build needs a PDB: configure with `/Zi` +
// `/DEBUG`, see BUILDING.md "Profiling"; a relink with `/DEBUG` alone gives public symbols, enough for functions
// with external linkage) and the report lists the top functions by sample count (self), with module+offset for
// unresolved ones; the file adds an inclusive table (on the stack within 8 frames) and the callers of the 30
// hottest functions. Recompiled
// guest functions appear under their generated names (`fn_<name>_<addr8>`), the adapter under `p3fes::rt::`,
// the GS under `p3fes::gs::`, so one list covers guest code, adapter and device models alike.
//
// The profiled thread must call start_profiler() itself (it duplicates the current thread's handle); stop
// from the same thread. Fibers: the guest fibers run on the same OS thread, so they are covered.
#pragma once

#include <cstdint>
#include <string>

namespace p3fes::app {

struct ProfileOptions {
    unsigned interval_us = 1000;      // sampling period
    std::size_t max_samples = 1u << 20; // 1 M samples x 8 frames (64 MiB) = 17 min at 1 ms (the timer often gives ~15 ms)
    unsigned top = 40;                // functions listed on the console
};

bool start_profiler(const ProfileOptions& opt);
// Joins the sampler, resolves symbols, prints the top-N table to stdout and the full table to `report_path`
// (empty = console only). Returns the number of samples taken.
std::size_t stop_profiler(const std::string& report_path);

} // namespace p3fes::app
