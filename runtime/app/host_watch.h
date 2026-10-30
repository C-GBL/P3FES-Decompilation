// Write watchpoints on guest RAM for divergence triage (`p3fes --watch-write VA[+LEN] N`), diagnostics only.
//
// The guest RAM is one host allocation (EEMemory::main_ram); a watch makes the host page(s) backing [va, va+len)
// read-only, catches the access violation in a vectored exception handler, lets the faulting instruction run
// with the page writable under the trap flag, re-protects it on the single-step exception and reports the
// bytes before/after with the guest call chain (host_backtrace.h; the writer may be a recompiled store or a
// device model's memcpy). Nothing on the guest path changes and nothing is read from the wall clock; with no
// watch armed there is no cost. Single-threaded like everything else (ADR-0013 §1).
#pragma once

#include <cstdint>
#include <functional>
#include <string>

namespace p3fes::app {

class GuestSymbols;

// Arms one watch over guest physical [va, va + len) of the RAM at `ram`. `log` receives one line per write
// (at most `max_hits`); `cycles` (optional) is read for the line's time stamp. Returns false if a watch is
// already armed or the protection cannot be set.
bool arm_write_watch(std::uint8_t* ram, std::uint32_t va, std::uint32_t len, unsigned max_hits, const GuestSymbols& syms,
                     const std::uint64_t* cycles, std::function<void(const std::string&)> log);
void disarm_write_watch();

} // namespace p3fes::app
