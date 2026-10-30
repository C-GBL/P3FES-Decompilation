#include "host_watch.h"

#include <windows.h>

#include <cstdio>
#include <cstring>

#include "guest_symbols.h"
#include "host_backtrace.h"

namespace p3fes::app {

namespace {

struct Watch {
    bool armed = false;
    std::uint8_t* ram = nullptr;
    std::uint32_t va = 0, len = 0;
    std::uintptr_t page_lo = 0, page_hi = 0;  // protected host pages [lo, hi)
    unsigned max_hits = 0, hits = 0;
    const GuestSymbols* syms = nullptr;
    const std::uint64_t* cycles = nullptr;
    std::function<void(const std::string&)> log;
    void* veh = nullptr;
    // pending single step
    bool stepping = false;
    bool report = false;
    std::uintptr_t fault = 0;
    std::uint8_t before[16] = {};
    std::string where;
};
Watch g;

bool protect(DWORD prot) {
    DWORD old = 0;
    return VirtualProtect(reinterpret_cast<void*>(g.page_lo), g.page_hi - g.page_lo, prot, &old) != FALSE;
}

std::string hex16(const std::uint8_t* p) {
    char b[48];
    for (int i = 0; i < 16; ++i) std::snprintf(b + 2 * i, 3, "%02x", p[i]);
    return b;
}

LONG CALLBACK on_exception(EXCEPTION_POINTERS* ep) {
    EXCEPTION_RECORD* er = ep->ExceptionRecord;
    if (er->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && g.armed && !g.stepping && er->NumberParameters >= 2 &&
        er->ExceptionInformation[0] == 1) {
        const std::uintptr_t a = er->ExceptionInformation[1];
        if (a < g.page_lo || a >= g.page_hi) return EXCEPTION_CONTINUE_SEARCH;
        const std::uintptr_t lo = reinterpret_cast<std::uintptr_t>(g.ram) + g.va;
        g.report = a + 16 > lo && a < lo + g.len && g.hits < g.max_hits;
        g.fault = a & ~std::uintptr_t{15};
        if (g.report) {
            std::memcpy(g.before, reinterpret_cast<const void*>(g.fault), 16);
            g.where.clear();
            for (const GuestFrame& f : guest_backtrace_from_context(ep->ContextRecord, 4))
                g.where += (g.where.empty() ? "" : " <- ") + g.syms->describe(f.va);
        }
        protect(PAGE_READWRITE);
        g.stepping = true;
        ep->ContextRecord->EFlags |= 0x100;  // trap flag: re-protect after this one instruction
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    if (er->ExceptionCode == EXCEPTION_SINGLE_STEP && g.stepping) {
        g.stepping = false;
        if (g.report) {
            ++g.hits;
            char line[640];
            std::snprintf(line, sizeof line, "[watch] [%12llu] write @0x%08X: %s -> %s  in %s",
                          static_cast<unsigned long long>(g.cycles ? *g.cycles : 0),
                          static_cast<unsigned>(g.fault - reinterpret_cast<std::uintptr_t>(g.ram)), hex16(g.before).c_str(),
                          hex16(reinterpret_cast<const std::uint8_t*>(g.fault)).c_str(),
                          g.where.empty() ? "(host code: no recompiled frame)" : g.where.c_str());
            g.log(line);
        }
        if (g.hits < g.max_hits) protect(PAGE_READONLY);
        else g.armed = false;  // enough: leave the pages writable
        ep->ContextRecord->EFlags &= ~0x100u;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

} // namespace

bool arm_write_watch(std::uint8_t* ram, std::uint32_t va, std::uint32_t len, unsigned max_hits, const GuestSymbols& syms,
                     const std::uint64_t* cycles, std::function<void(const std::string&)> log) {
    if (g.armed || !ram || !len) return false;
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    const std::uintptr_t page = si.dwPageSize;
    const std::uintptr_t lo = reinterpret_cast<std::uintptr_t>(ram) + va;
    g.ram = ram;
    g.va = va;
    g.len = len;
    g.page_lo = lo & ~(page - 1);
    g.page_hi = (lo + len + page - 1) & ~(page - 1);
    g.max_hits = max_hits ? max_hits : 1;
    g.hits = 0;
    g.syms = &syms;
    g.cycles = cycles;
    g.log = std::move(log);
    if (!g.veh) g.veh = AddVectoredExceptionHandler(1, on_exception);
    if (!g.veh || !protect(PAGE_READONLY)) return false;
    g.armed = true;
    return true;
}

void disarm_write_watch() {
    if (g.armed) protect(PAGE_READWRITE);
    g.armed = false;
    if (g.veh) RemoveVectoredExceptionHandler(g.veh);
    g.veh = nullptr;
}

} // namespace p3fes::app
