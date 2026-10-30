// rt adapter hook forwarding (runtime/rt/rt_hooks.cpp): set_hooks/hooks, syscall, check_events,
// trap, and the four stops reaching RtHooks::fatal with the pc and a message naming the address.
#include "fake_hooks.h"

#include "p3fes_recomp_rt.h"

#include <string>

using namespace p3fes;
using rt_test::FatalEvent;
using rt_test::HooksScope;
using rt_test::TestHooks;

// An unexpected fatal escaping a test case is reported with its message.
REGISTER_EXCEPTION_TRANSLATOR(const p3fes::rt_test::FatalEvent& e) {
    return doctest::String(("RtHooks::fatal: " + e.what).c_str());
}

TEST_CASE("rt hooks: set_hooks installs, set_hooks(nullptr) restores the aborting default") {
    RtHooks& def = hooks();
    TestHooks t;
    set_hooks(&t);
    CHECK(&hooks() == &t);
    set_hooks(nullptr);
    CHECK(&hooks() == &def);
    CHECK(&hooks() != &t);
}

TEST_CASE("rt hooks: syscall, check_events and trap reach the installed hooks") {
    TestHooks t;
    HooksScope scope(&t);
    EEContext ctx;
    ctx.gpr[GPR_V1].u64[0] = 0x3Cu;  // SetupThread
    rt::syscall(ctx, 0x1001C8u);
    CHECK(t.syscalls == 1);
    CHECK(t.syscall_pc == 0x1001C8u);
    CHECK(t.syscall_v1 == 0x3Cu);
    CHECK(ctx.gpr[GPR_V0].u64[0] == 0x600DF00Du);  // the hook's write is visible
    ctx.cycles = 1234;
    rt::check_events(ctx);
    rt::check_events(ctx);
    CHECK(t.checks == 2);
    CHECK(t.checks_at_cycles == 1234u);
    rt::trap(ctx, 0x4f0000u, rt::Trap::Break, 0x7u);
    CHECK(t.traps == 1);
    CHECK(t.trap_pc == 0x4f0000u);
    CHECK(t.trap_kind == rt::kTrapBreak);
    CHECK(t.trap_code == 0x7u);
    rt::trap(ctx, 0x4f0004u, rt::Trap::Unsupported, 0xDEADBEEFu);  // trap may return
    CHECK(t.traps == 2);
    CHECK(t.trap_kind == rt::kTrapUnsupported);
    CHECK(t.trap_code == 0xDEADBEEFu);
}

namespace {
// Hooks that publish a deadline (RtHooks::deadline_ptr): the inline check point in
// p3fes_recomp_rt_inline.h must skip the call while ctx.cycles < deadline and make it otherwise.
class DeadlineHooks final : public RtHooks {
public:
    rt_test::RecordingBus bus_;
    u64 deadline = 100;
    int checks = 0;
    void syscall(EEContext&, u32) override {}
    void check_events(EEContext&) override { ++checks; }
    const u64* deadline_ptr() const override { return &deadline; }
    hle::HwBus& bus() override { return bus_; }
    void trap(EEContext&, u32, u32, u32) override {}
    [[noreturn]] void fatal(EEContext& ctx, u32 pc, const char* what) override { throw FatalEvent{pc, what, &ctx}; }
};
} // namespace

TEST_CASE("rt hooks: the inline check point compares ctx.cycles with RtHooks::deadline_ptr() before calling") {
    DeadlineHooks d;
    HooksScope scope(&d);
    EEContext ctx;
    ctx.cycles = 50;
    rt::check_events(ctx);
    CHECK(d.checks == 0);  // below the deadline: no call
    ctx.cycles = 100;
    rt::check_events(ctx);
    CHECK(d.checks == 1);  // at the deadline: called
    d.deadline = 200;      // the hooks moved their deadline: the inline compare sees it (no re-install)
    ctx.cycles = 150;
    rt::check_events(ctx);
    CHECK(d.checks == 1);
    ctx.cycles = 250;
    rt::check_events(ctx);
    CHECK(d.checks == 2);
    d.deadline = 0;        // force_check(): the next check point calls whatever the cycle count
    ctx.cycles = 0;
    rt::check_events(ctx);
    CHECK(d.checks == 3);

    // Hooks without a deadline pointer (TestHooks) are called at every check point.
    TestHooks t;
    set_hooks(&t);
    ctx.cycles = 0;
    rt::check_events(ctx);
    rt::check_events(ctx);
    CHECK(t.checks == 2);
}

namespace {
// Calls a [[noreturn]] stop through a volatile pointer (so "returned" stays reachable code for the
// compiler) and returns the FatalEvent it raised.
template <class... A>
FatalEvent expect_fatal(void (*fn)(A...), A... args) {
    void (*volatile call)(A...) = fn;
    try {
        call(args...);
    } catch (const FatalEvent& e) {
        return e;
    }
    FAIL("the stop returned");
    return {};
}
} // namespace

TEST_CASE("rt hooks: the stops call RtHooks::fatal with the pc, the bound context and a message") {
    TestHooks t;
    HooksScope scope(&t);
    EEContext ctx;
    rt::bind_context(&ctx);
    CHECK(rt::bound_context() == &ctx);
    FatalEvent e = expect_fatal<std::uint32_t>(&rt::lookup_miss, 0x00ABCDEFu);
    CHECK(e.pc == 0x00ABCDEFu);
    CHECK(e.ctx == &ctx);
    CHECK(e.what.find("lookup_miss") != std::string::npos);
    CHECK(e.what.find("0x00abcdef") != std::string::npos);
    e = expect_fatal<std::uint32_t, std::uint32_t>(&rt::bad_entry, 0x526238u, 0x526240u);
    CHECK(e.pc == 0x526240u);
    CHECK(e.what.find("0x00526240 is not an entry point of the function at 0x00526238") != std::string::npos);
    e = expect_fatal<std::uint32_t>(&rt::unreachable, 0x193a00u);
    CHECK(e.pc == 0x193a00u);
    CHECK(e.what.find("unreachable: execution reached 0x00193a00") != std::string::npos);
    e = expect_fatal<std::uint32_t>(&rt::missing_function, 0x524388u);
    CHECK(e.pc == 0x524388u);
    CHECK(e.what.find("missing_function: the function at 0x00524388") != std::string::npos);
    // Unbound: a placeholder context, never the caller's.
    rt::bind_context(nullptr);
    e = expect_fatal<std::uint32_t>(&rt::unreachable, 0x10u);
    CHECK(e.ctx != nullptr);
    CHECK(e.ctx != &ctx);
}

TEST_CASE("rt hooks: CTC2 to vi28 (FBRST) reaches RtHooks::vu_control_write; other control registers do not") {
    TestHooks t;
    HooksScope scope(&t);
    EEContext ctx;
    ctx.gpr[4].u64[0] = 0x202u;  // RS1 | RS0 (B-42/B-43 `FBRST |= 0x200`, `|= 2`)
    rt::ctc2(ctx, 4, 28, false);
    rt::ctc2(ctx, 4, 21, false);  // I register: adapter state only
    REQUIRE(t.vu_control.size() == 1);
    CHECK(t.vu_control[0].first == 28u);
    CHECK(t.vu_control[0].second == 0x202u);
    rt::cfc2(ctx, 5, 29, false);  // VPU_STAT reads 0: VU1 never runs concurrently (bit 8 clear)
    CHECK(ctx.gpr[5].u64[0] == 0u);
}
