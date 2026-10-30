#include "host_profile.h"

#include <windows.h>
// dbghelp.h needs windows.h first.
#include <dbghelp.h>

#include <algorithm>
#include <atomic>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

namespace p3fes::app {

namespace {

// Frames kept per sample: the sampled RIP and up to kDepth - 1 callers, unwound while the thread is suspended
// (RtlVirtualUnwind over the x64 unwind tables; a function without unwind data is a leaf: its return address is at
// [RSP]). 0 ends a short stack.
constexpr unsigned kDepth = 8;

struct Profiler {
    HANDLE target = nullptr;
    std::thread sampler;
    std::atomic<bool> stop{false};
    std::vector<std::uint64_t> samples;  // kDepth per sample; preallocated; written only by the sampler thread
    std::size_t count = 0;
    unsigned interval_us = 1000;
    unsigned top = 40;
    std::uint64_t suspend_failures = 0, context_failures = 0;
};

Profiler* g_prof = nullptr;

// Unwinds the suspended thread's stack from `ctx` into out[0..kDepth). Reads only the thread's own stack and the
// image's unwind tables; nothing is allocated (the target may hold the heap lock).
void unwind(CONTEXT ctx, std::uint64_t* out) {
    for (unsigned i = 0; i < kDepth; ++i) out[i] = 0;
    for (unsigned i = 0; i < kDepth; ++i) {
        if (!ctx.Rip) break;
        out[i] = ctx.Rip;
        if (i + 1 == kDepth) break;
        DWORD64 image = 0;
        PRUNTIME_FUNCTION fn = RtlLookupFunctionEntry(ctx.Rip, &image, nullptr);
        if (!fn) {  // leaf: return address at [RSP]
            if (!ctx.Rsp || (ctx.Rsp & 7)) break;
            ctx.Rip = *reinterpret_cast<const DWORD64*>(ctx.Rsp);
            ctx.Rsp += 8;
            continue;
        }
        void* handler_data = nullptr;
        DWORD64 frame = 0;
        RtlVirtualUnwind(UNW_FLAG_NHANDLER, image, ctx.Rip, fn, &ctx, &handler_data, &frame, nullptr);
    }
}

void sampler_main(Profiler* p) {
    // A waitable timer gives a finer period than Sleep(1) on most hosts; fall back to Sleep otherwise.
    HANDLE timer = CreateWaitableTimerW(nullptr, FALSE, nullptr);
    LARGE_INTEGER due;
    due.QuadPart = -static_cast<LONGLONG>(p->interval_us) * 10;  // relative, 100 ns units
    const LONG period_ms = static_cast<LONG>(std::max(1u, p->interval_us / 1000u));
    if (timer) SetWaitableTimer(timer, &due, period_ms, nullptr, nullptr, FALSE);
    CONTEXT ctx;
    while (!p->stop.load(std::memory_order_relaxed)) {
        if (timer) WaitForSingleObject(timer, period_ms + 1);
        else Sleep(period_ms);
        if ((p->count + 1) * kDepth > p->samples.size()) continue;  // buffer full: keep running, drop samples
        if (SuspendThread(p->target) == static_cast<DWORD>(-1)) {
            ++p->suspend_failures;
            continue;
        }
        std::memset(&ctx, 0, sizeof ctx);
        ctx.ContextFlags = CONTEXT_CONTROL | CONTEXT_INTEGER;
        const BOOL ok = GetThreadContext(p->target, &ctx);
        if (ok) unwind(ctx, &p->samples[p->count * kDepth]);
        ResumeThread(p->target);
        if (!ok) {
            ++p->context_failures;
            continue;
        }
        ++p->count;
    }
    if (timer) CloseHandle(timer);
}

std::string describe(std::uint64_t a, bool& resolved) {
    HMODULE mod = nullptr;
    char path[MAX_PATH] = "?";
    if (GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           reinterpret_cast<LPCSTR>(a), &mod) &&
        mod)
        GetModuleFileNameA(mod, path, MAX_PATH);
    const char* base = std::strrchr(path, '\\');
    base = base ? base + 1 : path;
    alignas(SYMBOL_INFO) char buf[sizeof(SYMBOL_INFO) + 512];
    auto* si = reinterpret_cast<SYMBOL_INFO*>(buf);
    std::memset(buf, 0, sizeof buf);
    si->SizeOfStruct = sizeof(SYMBOL_INFO);
    si->MaxNameLen = 511;
    DWORD64 disp = 0;
    if (SymFromAddr(GetCurrentProcess(), a, &disp, si)) {
        resolved = true;
        return std::string(base) + "!" + si->Name;
    }
    resolved = false;
    char b[64];
    std::snprintf(b, sizeof b, "+0x%llX", static_cast<unsigned long long>(a - reinterpret_cast<std::uint64_t>(mod)));
    return std::string(base) + b;
}

} // namespace

bool start_profiler(const ProfileOptions& opt) {
    if (g_prof) return false;
    auto* p = new Profiler;
    if (!DuplicateHandle(GetCurrentProcess(), GetCurrentThread(), GetCurrentProcess(), &p->target, 0, FALSE,
                         DUPLICATE_SAME_ACCESS)) {
        delete p;
        return false;
    }
    p->interval_us = std::max(100u, opt.interval_us);
    p->top = opt.top;
    p->samples.resize(opt.max_samples * kDepth);
    g_prof = p;
    p->sampler = std::thread(sampler_main, p);
    return true;
}

std::size_t stop_profiler(const std::string& report_path) {
    Profiler* p = g_prof;
    if (!p) return 0;
    p->stop.store(true);
    p->sampler.join();
    g_prof = nullptr;
    const std::size_t n = p->count;

    SymSetOptions(SYMOPT_UNDNAME | SYMOPT_DEFERRED_LOADS | SYMOPT_FAIL_CRITICAL_ERRORS);
    SymInitialize(GetCurrentProcess(), nullptr, TRUE);  // harmless if already initialised
    // Per address first (cheap), then per symbol.
    std::unordered_map<std::uint64_t, std::uint64_t> by_addr;
    by_addr.reserve(n / 4 + 16);
    for (std::size_t i = 0; i < n; ++i) ++by_addr[p->samples[i * kDepth]];
    std::unordered_map<std::string, std::uint64_t> by_sym;
    std::uint64_t unresolved = 0;
    for (const auto& [a, c] : by_addr) {
        bool ok = false;
        by_sym[describe(a, ok)] += c;
        if (!ok) unresolved += c;
    }
    // Symbols of every unwound frame (cached per address), for the inclusive table and the callers of the hottest.
    std::unordered_map<std::uint64_t, std::string> names;
    auto name_of = [&names](std::uint64_t a) -> const std::string& {
        auto it = names.find(a);
        if (it != names.end()) return it->second;
        bool ok = false;
        return names.emplace(a, describe(a, ok)).first->second;
    };
    std::unordered_map<std::string, std::uint64_t> incl;                                  // samples with it on the stack
    std::unordered_map<std::string, std::unordered_map<std::string, std::uint64_t>> callers;  // self symbol -> caller -> n
    for (std::size_t i = 0; i < n; ++i) {
        const std::uint64_t* f = &p->samples[i * kDepth];
        std::vector<const std::string*> seen;
        for (unsigned d = 0; d < kDepth && f[d]; ++d) {
            const std::string& nm = name_of(d == 0 ? f[d] : f[d] - 1);  // a return address belongs to the call before it
            if (std::find(seen.begin(), seen.end(), &nm) == seen.end()) {
                seen.push_back(&nm);
                ++incl[nm];
            }
        }
        if (f[1]) ++callers[name_of(f[0])][name_of(f[1] - 1)];
    }
    std::vector<std::pair<std::string, std::uint64_t>> rows(by_sym.begin(), by_sym.end());
    std::sort(rows.begin(), rows.end(), [](const auto& x, const auto& y) { return x.second > y.second; });

    std::printf("p3fes: profile: %zu samples at %u us (%.1f s sampled), %zu distinct addresses, %llu unresolved samples, "
                "suspend failures %llu, context failures %llu\n",
                n, p->interval_us, n * (p->interval_us / 1e6), by_addr.size(), static_cast<unsigned long long>(unresolved),
                static_cast<unsigned long long>(p->suspend_failures), static_cast<unsigned long long>(p->context_failures));
    const unsigned top = std::min<unsigned>(p->top, static_cast<unsigned>(rows.size()));
    std::uint64_t shown = 0;
    for (unsigned i = 0; i < top; ++i) {
        shown += rows[i].second;
        std::printf("p3fes:   %6.2f%%  %8llu  %s\n", n ? 100.0 * rows[i].second / n : 0.0,
                    static_cast<unsigned long long>(rows[i].second), rows[i].first.c_str());
    }
    if (rows.size() > top)
        std::printf("p3fes:   %6.2f%%  %8llu  (%zu more)\n", n ? 100.0 * (n - shown) / n : 0.0,
                    static_cast<unsigned long long>(n - shown), rows.size() - top);
    if (!report_path.empty()) {
        if (std::FILE* f = std::fopen(report_path.c_str(), "w")) {
            std::fprintf(f, "# p3fes --profile: %zu samples at %u us; percent samples symbol\n", n, p->interval_us);
            for (const auto& [s, c] : rows)
                std::fprintf(f, "%7.3f %10llu %s\n", n ? 100.0 * c / n : 0.0, static_cast<unsigned long long>(c), s.c_str());
            // Inclusive: samples with the function anywhere in the first frames (a subsystem's whole cost).
            std::vector<std::pair<std::string, std::uint64_t>> inc(incl.begin(), incl.end());
            std::sort(inc.begin(), inc.end(), [](const auto& x, const auto& y) { return x.second > y.second; });
            std::fprintf(f, "\n# inclusive (on the stack within %u frames): percent samples symbol\n", kDepth);
            for (std::size_t k = 0; k < inc.size() && k < 200; ++k)
                std::fprintf(f, "%7.3f %10llu %s\n", n ? 100.0 * inc[k].second / n : 0.0,
                             static_cast<unsigned long long>(inc[k].second), inc[k].first.c_str());
            // Callers of the hottest functions (self time).
            std::fprintf(f, "\n# callers of the top functions: symbol, then percent of its samples per caller\n");
            for (std::size_t k = 0; k < rows.size() && k < 30; ++k) {
                std::fprintf(f, "%s\n", rows[k].first.c_str());
                auto it = callers.find(rows[k].first);
                if (it == callers.end()) continue;
                std::vector<std::pair<std::string, std::uint64_t>> cs(it->second.begin(), it->second.end());
                std::sort(cs.begin(), cs.end(), [](const auto& x, const auto& y) { return x.second > y.second; });
                for (std::size_t j = 0; j < cs.size() && j < 5; ++j)
                    std::fprintf(f, "    %6.2f%%  %s\n", 100.0 * cs[j].second / rows[k].second, cs[j].first.c_str());
            }
            // The samples with their two callers (function <- caller <- caller's caller), as track B's version had.
            std::unordered_map<std::string, std::uint64_t> chains;
            for (std::size_t i = 0; i < n; ++i) {
                const std::uint64_t* fr = &p->samples[i * kDepth];
                chains[name_of(fr[0]) + "  <-  " + (fr[1] ? name_of(fr[1] - 1) : std::string("?")) + "  <-  " +
                       (fr[1] && fr[2] ? name_of(fr[2] - 1) : std::string("?"))] += 1;
            }
            std::vector<std::pair<std::string, std::uint64_t>> crow(chains.begin(), chains.end());
            std::sort(crow.begin(), crow.end(), [](const auto& x, const auto& y) { return x.second > y.second; });
            std::fprintf(f, "\n# with callers\n");
            for (std::size_t i = 0; i < crow.size() && i < 400; ++i)
                std::fprintf(f, "%7.3f %10llu %s\n", n ? 100.0 * crow[i].second / n : 0.0,
                             static_cast<unsigned long long>(crow[i].second), crow[i].first.c_str());
            std::fclose(f);
            std::printf("p3fes: profile written to %s\n", report_path.c_str());
        } else {
            std::fprintf(stderr, "p3fes: cannot write %s\n", report_path.c_str());
        }
    }
    CloseHandle(p->target);
    delete p;
    return n;
}

} // namespace p3fes::app
