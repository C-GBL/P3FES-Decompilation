// ADR-0013 hot-path cost probe (built with -DP3FES_RT_PERF=ON): times the recompiled game memset
// (0x521408) over 1 MiB of guest RAM. p3fes_rt_perf links the subset emitted with cycle accounting
// and check points (the defaults), p3fes_rt_perf_off the same function emitted with --no-cycles
// --no-check-events. The hooks' check_events is the "one compare when nothing is due" the ADR
// expects of the kernel HLE (a deadline far away), so the difference between the two binaries is
// the cost of the emitted statements plus that call.
//
//   p3fes_rt_perf[_off] [runs=5] [reps=20]
#include "p3fes/ee_memory.h"
#include "p3fes/hle/hw_bus.h"
#include "p3fes/rt/rt_adapter.h"
#include "p3fes/rt_hooks.h"
#include "p3fes_recomp_rt.h"

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace p3fes;

namespace {

class PerfHooks final : public RtHooks {
public:
    u64 deadline = ~0ull;
    u64 due = 0;
    void syscall(EEContext&, u32 pc) override { die("syscall", pc); }
    void check_events(EEContext& ctx) override {
        if (ctx.cycles >= deadline) ++due;  // never true here: the cost of a check with nothing due
    }
    hle::HwBus& bus() override { die("bus", 0); }
    void trap(EEContext&, u32 pc, u32, u32) override { die("trap", pc); }
    [[noreturn]] void fatal(EEContext&, u32 pc, const char* what) override {
        std::fprintf(stderr, "fatal at 0x%08x: %s\n", pc, what);
        std::exit(2);
    }

private:
    [[noreturn]] static void die(const char* what, u32 pc) {
        std::fprintf(stderr, "unexpected %s at 0x%08x\n", what, pc);
        std::exit(2);
    }
};

} // namespace

int main(int argc, char** argv) {
    const int runs = argc > 1 ? std::atoi(argv[1]) : 5;
    const int reps = argc > 2 ? std::atoi(argv[2]) : 20;
    constexpr u32 kDst = 0x00200000u, kSize = 1u << 20, kMemset = 0x521408u;

    EEMemory mem;
    EEContext ctx;
    ctx.memory = &mem;
    PerfHooks hooks;
    set_hooks(&hooks);
    rt::bind_context(&ctx);
    const rt::Fn memset_fn = rt::lookup_func(kMemset);

    std::vector<double> ms_per_call;
    u64 cycles_per_call = 0;
    for (int r = 0; r < runs; ++r) {
        const u64 c0 = ctx.cycles;
        const auto t0 = std::chrono::steady_clock::now();
        for (int i = 0; i < reps; ++i) {
            ctx.gpr[GPR_A0].u64[0] = kDst;
            ctx.gpr[GPR_A1].u64[0] = static_cast<u64>(0x5A + i);
            ctx.gpr[GPR_A2].u64[0] = kSize;
            memset_fn(ctx);
        }
        const auto t1 = std::chrono::steady_clock::now();
        cycles_per_call = (ctx.cycles - c0) / static_cast<u64>(reps);
        ms_per_call.push_back(std::chrono::duration<double, std::milli>(t1 - t0).count() / reps);
    }
    // The last value written must fill the whole range.
    const u8 last = static_cast<u8>(0x5A + reps - 1);
    for (u32 i = 0; i < kSize; ++i) {
        if (mem.main_ram()[kDst + i] != last) {
            std::fprintf(stderr, "memset result wrong at +0x%x\n", i);
            return 1;
        }
    }
    std::vector<double> sorted = ms_per_call;
    std::sort(sorted.begin(), sorted.end());
    std::printf("variant: %s\nmemset(1 MiB) x %d per run, %d runs; ms per call:", P3FES_RT_PERF_VARIANT, reps, runs);
    for (double v : ms_per_call) std::printf(" %.3f", v);
    std::printf("\nmedian %.3f ms, min %.3f ms, ctx.cycles per call %llu\n", sorted[sorted.size() / 2], sorted.front(),
                static_cast<unsigned long long>(cycles_per_call));
    set_hooks(nullptr);
    return 0;
}
