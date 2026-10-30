// rt adapter: the RtHooks installation point (set_hooks / hooks, runtime/include/p3fes/rt_hooks.h),
// the aborting default hooks, and the rt:: entry points that only forward to the hooks: syscall,
// check_events, trap and the four stops (lookup_miss, bad_entry, unreachable, missing_function).
#include "rt_internal.h"

#include "p3fes/rt/rt_adapter.h"

#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace p3fes {

static_assert(static_cast<u32>(rt::Trap::Break) == rt::kTrapBreak && static_cast<u32>(rt::Trap::Unsupported) == rt::kTrapUnsupported,
              "rt_adapter.h trap kinds must equal p3fes::rt::Trap");

namespace {

// abort() without the Debug CRT's modal "abort() has been called" dialog, which would block an
// unattended run (tests, headless snapshot runs); a debugger still stops on the abort.
[[noreturn]] void abort_quietly() {
#if defined(_WIN32)
    _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif
    std::abort();
}

[[noreturn]] void no_hooks(const char* what) {
    std::fprintf(stderr,
                 "p3fes rt: %s reached but no RtHooks is installed; call p3fes::set_hooks() before running "
                 "recompiled code (runtime/include/p3fes/rt_hooks.h)\n",
                 what);
    std::fflush(stderr);
    abort_quietly();
}

// Installed while no runtime hooks are: every entry aborts naming itself.
class DefaultHooks final : public RtHooks {
public:
    void syscall(EEContext&, u32) override { no_hooks("RtHooks::syscall"); }
    void check_events(EEContext&) override { no_hooks("RtHooks::check_events"); }
    hle::HwBus& bus() override { no_hooks("RtHooks::bus (hardware-register access)"); }
    void trap(EEContext&, u32, u32, u32) override { no_hooks("RtHooks::trap"); }
    [[noreturn]] void fatal(EEContext&, u32 pc, const char* what) override {
        std::fprintf(stderr, "p3fes rt: fatal at pc 0x%08x: %s\n", pc, what);
        no_hooks("RtHooks::fatal");
    }
};

DefaultHooks g_default_hooks;
EEContext g_placeholder_ctx;   // reported when no context is bound
EEContext* g_bound_ctx = nullptr;

} // namespace

namespace rt::detail {

RtHooks* g_hooks = &g_default_hooks;

// The inline check point (p3fes_recomp_rt_inline.h) compares ctx.cycles with *g_deadline. Hooks
// without a deadline pointer get the zero: every check point then takes the slow path.
const u64 g_zero_deadline = 0;
const u64* g_deadline = &g_zero_deadline;

void check_events_slow(EEContext& ctx) { g_hooks->check_events(ctx); }

EEContext& report_context() noexcept { return g_bound_ctx ? *g_bound_ctx : g_placeholder_ctx; }

void fatalf(EEContext& ctx, u32 pc, const char* fmt, ...) {
    // Single-threaded (ADR-0013 §1) and never re-entered: fatal does not return.
    static char message[512];
    std::va_list ap;
    va_start(ap, fmt);
    std::vsnprintf(message, sizeof message, fmt, ap);
    va_end(ap);
    hk().fatal(ctx, pc, message);
}

} // namespace rt::detail

void set_hooks(RtHooks* h) {
    rt::detail::g_hooks = h ? h : &g_default_hooks;
    const u64* d = rt::detail::g_hooks->deadline_ptr();
    rt::detail::g_deadline = d ? d : &rt::detail::g_zero_deadline;
}
RtHooks& hooks() { return *rt::detail::g_hooks; }

namespace rt {

void bind_context(EEContext* ctx) noexcept { g_bound_ctx = ctx; }
EEContext* bound_context() noexcept { return g_bound_ctx; }

void syscall(EEContext& ctx, std::uint32_t pc) { detail::hk().syscall(ctx, pc); }

// check_events itself is inline (p3fes_recomp_rt_inline.h); its slow half is detail::check_events_slow above.

void trap(EEContext& ctx, std::uint32_t pc, Trap kind, std::uint32_t code) {
    detail::hk().trap(ctx, pc, static_cast<u32>(kind), code);
}

void lookup_miss(std::uint32_t va) {
    detail::fatalf(detail::report_context(), va,
                   "lookup_miss: no recompiled function starts or enters at 0x%08x (indirect jalr/jr target "
                   "outside symbols/functions.json)",
                   va);
}

void bad_entry(std::uint32_t fn_start, std::uint32_t entry_pc) {
    detail::fatalf(detail::report_context(), entry_pc,
                   "bad_entry: 0x%08x is not an entry point of the function at 0x%08x", entry_pc, fn_start);
}

void unreachable(std::uint32_t pc) {
    detail::fatalf(detail::report_context(), pc,
                   "unreachable: execution reached 0x%08x (IDA data word, chunk end into no function, or a "
                   "label without an instruction)",
                   pc);
}

void missing_function(std::uint32_t va) {
    detail::fatalf(detail::report_context(), va,
                   "missing_function: the function at 0x%08x was not emitted in this build (subset --only/--band)",
                   va);
}

} // namespace rt

} // namespace p3fes
