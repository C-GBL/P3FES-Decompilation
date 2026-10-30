// HwBus range map / dispatch / unhandled log, the virtual time base, INTC registers and timers T0-T2.
// These run on the host fiber without a guest thread: check points then only advance the time base.
#include "kernel_test_util.h"

using namespace kt;

namespace {
constexpr u32 kIntcStat = 0x1000F000u, kIntcMask = 0x1000F010u;
constexpr u32 kT0Count = 0x10000000u, kT0Mode = 0x10000010u, kT0Comp = 0x10000020u;
constexpr u32 kT1Count = 0x10000800u, kT1Mode = 0x10000810u, kT1Comp = 0x10000820u;
constexpr u32 kT2Count = 0x10001000u, kT2Mode = 0x10001010u, kT2Comp = 0x10001020u;
// Cycle of VBLANK_START k: ceil(k * 4,920,115.2) (24600576/5 cycles per field).
constexpr u64 vblank_cycle(u64 k) { return (k * 24600576ull + 4) / 5; }
constexpr u64 hlines(u64 c) { return c * 1125ull / 21086208ull; }
} // namespace

TEST_CASE("HwBus: map refuses misaligned, out-of-window and overlapping ranges") {
    Rig r;
    RecDevice a, b;
    CHECK(r.k->try_map(0x10003000u, 0x10003100u, &a));
    CHECK_FALSE(r.k->try_map(0x100030F0u, 0x10003200u, &b));  // overlaps a's last slot
    CHECK_FALSE(r.k->try_map(0x10003104u, 0x10003200u, &b));  // misaligned begin
    CHECK_FALSE(r.k->try_map(0x10003100u, 0x10003108u, &b));  // misaligned end
    CHECK_FALSE(r.k->try_map(0x1000E000u, 0x1000E010u, &b));  // the kernel's DMAC block
    CHECK_FALSE(r.k->try_map(0x1000F000u, 0x1000F010u, &b));  // INTC
    CHECK_FALSE(r.k->try_map(0x0FFFFFF0u, 0x10000010u, &b));  // straddles the window start
    CHECK_FALSE(r.k->try_map(0x13000000u, 0x13000010u, &b));  // not a register window
    CHECK_FALSE(r.k->try_map(0x12001000u, 0x12001010u, &b));  // the rig's GS CSR
    CHECK(r.k->try_map(0x10003100u, 0x10003200u, &b));         // adjacent is fine
    CHECK(r.k->try_map(0x12000000u, 0x12000100u, &b));         // GS window
    // A refused map changed nothing: 0x10003100 goes to b, 0x100030F0 still to a.
    r.bus().write32(0x100030F0u, 1);
    r.bus().write32(0x10003100u, 2);
    REQUIRE(a.log.size() == 1);
    REQUIRE(b.log.size() == 1);
    CHECK(a.log[0].pa == 0x100030F0u);
    CHECK(b.log[0].pa == 0x10003100u);
}

TEST_CASE("HwBus: width-exact dispatch, no splitting or merging") {
    Rig r;
    RecDevice d;
    REQUIRE(r.k->try_map(0x10005000u, 0x10006000u, &d));
    d.answer = 0x1122334455667788ull;
    r.bus().write8(0x10005001u, 0xAB);
    r.bus().write16(0x10005002u, 0xBEEF);
    r.bus().write32(0x10005010u, 0xDEADBEEFu);
    r.bus().write64(0x10005020u, 0x0102030405060708ull);
    u128 q{};
    q.u64[0] = 0xAAAAull;
    q.u64[1] = 0xBBBBull;
    r.bus().write128(0x10005030u, q);
    CHECK(r.bus().read8(0x10005001u) == 0x88);
    CHECK(r.bus().read16(0x10005002u) == 0x7788);
    CHECK(r.bus().read32(0x10005010u) == 0x55667788u);
    CHECK(r.bus().read64(0x10005020u) == 0x1122334455667788ull);
    CHECK(r.bus().read128(0x10005030u).lo() == 0x1122334455667788ull);
    const u32 widths[] = {8, 16, 32, 64, 128, 8, 16, 32, 64, 128};
    REQUIRE(d.log.size() == 10);
    for (std::size_t i = 0; i < 10; ++i) {
        CHECK(d.log[i].width == widths[i]);
        CHECK(d.log[i].write == (i < 5));
    }
    CHECK(d.log[0].value == 0xAB);
    CHECK(d.log[3].value == 0x0102030405060708ull);
    CHECK(d.log[4].value == 0xAAAAull);
    CHECK(r.k->unhandled_accesses() == 0);
}

TEST_CASE("HwBus: unhandled accesses are counted and logged with pa, width, value and pc") {
    Rig r;
    r.ctx.pc = 0x00123450u;
    r.bus().write32(0x10007770u, 0x55u);
    CHECK(r.bus().read64(0x12000040u) == 0);
    r.ctx.pc = 0x00123460u;
    CHECK(r.bus().read32(0x10000040u) == 0);  // inside the timer device, not a register
    r.bus().write32(0x1000E070u, 7);          // inside the DMAC block, not a register
    CHECK(r.k->unhandled_accesses() == 4);
    const auto log = r.k->unhandled_log();
    REQUIRE(log.size() == 4);
    CHECK(log[0].pa == 0x10007770u);
    CHECK(log[0].width == 32);
    CHECK(log[0].write);
    CHECK(log[0].value == 0x55u);
    CHECK(log[0].pc == 0x00123450u);
    CHECK(log[1].pa == 0x12000040u);
    CHECK(log[1].width == 64);
    CHECK_FALSE(log[1].write);
    CHECK(log[2].pa == 0x10000040u);
    CHECK(log[2].pc == 0x00123460u);
    CHECK(log[3].pa == 0x1000E070u);
    // The ring keeps the newest 256 entries.
    for (int i = 0; i < 300; ++i) r.bus().write32(0x10007000u, static_cast<u32>(i));
    CHECK(r.k->unhandled_accesses() == 304);
    const auto log2 = r.k->unhandled_log();
    REQUIRE(log2.size() == 256);
    CHECK(log2.back().value == 299);
    CHECK(log2.front().value == 299 - 255);
}

TEST_CASE("time base: H-lines, fields and VBLANKs from cycles with exact rationals") {
    static_assert(hlines(18743) == 0 && hlines(18744) == 1);
    static_assert(vblank_cycle(1) == 4920116 && vblank_cycle(20) == 98402304 && vblank_cycle(5) == 24600576);
    Rig r;
    EEContext& c = r.ctx;
    CHECK(r.k->time().hlines == 0);
    CHECK(*r.k->next_deadline() == 0);  // a fresh kernel takes the slow path once
    work(c, 0);
    CHECK(*r.k->next_deadline() == vblank_cycle(1));
    c.cycles = 18743;
    CHECK(r.k->time().hlines == 0);
    c.cycles = 18744;
    CHECK(r.k->time().hlines == 1);
    c.cycles = vblank_cycle(1) - 1;
    r.hooks().check_events(c);
    CHECK(r.k->time().vblanks == 0);
    CHECK(r.k->time().field == 0);
    CHECK((r.k->intc_stat() & 4u) == 0);
    c.cycles = vblank_cycle(1);
    r.hooks().check_events(c);
    CHECK(r.k->time().vblanks == 1);
    CHECK(r.k->time().field == 1);
    CHECK((r.k->intc_stat() & 4u) != 0);  // VBLANK_START sets bit 2 with no handler and the mask clear (VSync polls it)
    CHECK(r.k->time().hlines == 262);     // 262.5 lines per field
    // VBLANK_END 22 H-lines later sets bit 3.
    CHECK((r.k->intc_stat() & 8u) == 0);
    work(c, 22 * 18744);
    CHECK((r.k->intc_stat() & 8u) != 0);
    // 20 fields: field toggles at each VBLANK_START.
    c.cycles = vblank_cycle(20);
    r.hooks().check_events(c);
    CHECK(r.k->time().vblanks == 20);
    CHECK(r.k->time().field == 0);
    CHECK(r.k->time().hlines == 5250);  // 20 * 262.5
    // 1001 s of virtual time = exactly 60000 fields (59.94 Hz).
    c.cycles = 294'912'000ull * 1001ull;
    r.hooks().check_events(c);
    CHECK(r.k->time().vblanks == 60000);
    CHECK(r.k->time().hlines == 15'750'000ull);  // 60000 * 262.5
}

TEST_CASE("INTC: STAT is write-1-to-clear, MASK toggles on a written 1") {
    Rig r;
    work(r.ctx, vblank_cycle(1) + 22 * 18744);  // bits 2 and 3 pending
    CHECK(r.bus().read32(kIntcStat) == 0xCu);
    r.bus().write32(kIntcStat, 0x4u);
    CHECK(r.bus().read32(kIntcStat) == 0x8u);
    r.bus().write32(kIntcStat, 0x0u);
    CHECK(r.bus().read32(kIntcStat) == 0x8u);
    r.bus().write32(kIntcMask, 0x204u);  // 2 and 9 on
    CHECK(r.bus().read32(kIntcMask) == 0x204u);
    r.bus().write32(kIntcMask, 0x004u);  // 2 off again
    CHECK(r.bus().read32(kIntcMask) == 0x200u);
    r.bus().write32(kIntcMask, 0x0u);
    CHECK(r.bus().read32(kIntcMask) == 0x200u);
}

TEST_CASE("timers: T0 counts H-blanks from cycles (MODE 0x83, B-59)") {
    Rig r;
    EEContext& c = r.ctx;
    c.cycles = 1'000'000;
    r.bus().write32(kT0Count, 0);
    r.bus().write32(kT0Mode, 0x83u);  // CLKS 3 H-BLANK, CUE
    const u64 c0 = c.cycles;
    for (u64 n : {0ull, 18'743ull, 100'000ull, 9'840'230ull, 1'234'567'890ull}) {
        c.cycles = c0 + n;
        const u32 expect = static_cast<u32>((hlines(c0 + n) - hlines(c0)) & 0xFFFFu);
        CHECK(r.bus().read32(kT0Count) == expect);
    }
    // CPU-load style difference over one 525-line frame (two fields).
    c.cycles = c0;
    r.bus().write32(kT0Count, 0);
    c.cycles = c0 + 2 * 4'920'115ull;
    CHECK(r.bus().read32(kT0Count) == static_cast<u32>(hlines(c0 + 2 * 4'920'115ull) - hlines(c0)));
    CHECK(r.bus().read32(kT0Count) >= 524);
    // CUE cleared: the count freezes.
    const u32 frozen = r.bus().read32(kT0Count);
    r.bus().write32(kT0Mode, 0x03u);
    c.cycles += 10'000'000;
    CHECK(r.bus().read32(kT0Count) == frozen);
    CHECK(r.k->unhandled_accesses() == 0);
}

TEST_CASE("timers: T0 BUSCLK/16 overflow raises cause 9 and OVFF is write-1-to-clear (B-18)") {
    Rig r;
    EEContext& c = r.ctx;
    r.bus().write32(kT0Count, 0);
    r.bus().write32(kT0Comp, 0);
    r.bus().write32(kT0Mode, 0x281u);  // CLKS 1 (32 EE cycles/tick), CUE, OVFE
    // The overflow is an exact event deadline: 0x10000 ticks * 32 cycles.
    CHECK(*r.k->next_deadline() == 0);
    work(c, 0);
    CHECK(*r.k->next_deadline() == 0x10000ull * 32);
    work(c, 0x10000ull * 32 - 1);
    CHECK((r.k->intc_stat() & (1u << 9)) == 0);
    CHECK((r.bus().read32(kT0Mode) & 0x800u) == 0);
    CHECK(r.bus().read32(kT0Count) == 0xFFFFu);
    work(c, 1);
    CHECK((r.k->intc_stat() & (1u << 9)) != 0);
    CHECK((r.bus().read32(kT0Mode) & 0x800u) != 0);
    CHECK(r.bus().read32(kT0Count) == 0);
    // EQUF also set at count 0 == COMP 0; clear both flags.
    r.bus().write32(kIntcStat, 1u << 9);
    r.bus().write32(kT0Mode, 0xC00u | 0x281u);
    CHECK((r.bus().read32(kT0Mode) & 0xC00u) == 0);
    // Next overflow raises again; without OVFE it would not.
    work(c, 0x10000ull * 32);
    CHECK((r.k->intc_stat() & (1u << 9)) != 0);
    r.bus().write32(kIntcStat, 1u << 9);
    r.bus().write32(kT0Mode, 0xC00u | 0x81u);  // OVFE off
    work(c, 0x10000ull * 32);
    CHECK((r.k->intc_stat() & (1u << 9)) == 0);
    CHECK((r.bus().read32(kT0Mode) & 0x800u) != 0);  // the flag still sets
}

TEST_CASE("timers: T2 compare (CLKS 2, CMPE) raises cause 11; T1 ZRET restarts at 0") {
    Rig r;
    EEContext& c = r.ctx;
    r.bus().write32(kT2Count, 0);
    r.bus().write32(kT2Comp, 100);
    r.bus().write32(kT2Mode, 0x182u);  // BUSCLK/256 (512 cycles/tick), CUE, CMPE
    work(c, 100 * 512 - 1);
    CHECK((r.k->intc_stat() & (1u << 11)) == 0);
    work(c, 1);
    CHECK((r.k->intc_stat() & (1u << 11)) != 0);
    CHECK((r.bus().read32(kT2Mode) & 0x400u) != 0);
    CHECK(r.bus().read32(kT2Count) == 100);  // no ZRET: keeps counting
    // Flag already set: the next match does not raise again until it is cleared (edge on EQUF, inf).
    r.bus().write32(kIntcStat, 1u << 11);
    work(c, 0x10000ull * 512);
    CHECK((r.k->intc_stat() & (1u << 11)) == 0);
    // T1: BUSCLK (2 cycles/tick), ZRET, CUE, CMPE, COMP 10.
    r.bus().write32(kT1Count, 0);
    r.bus().write32(kT1Comp, 10);
    r.bus().write32(kT1Mode, 0x1C0u);
    work(c, 2 * 25);
    CHECK(r.bus().read32(kT1Count) == 5);  // 0..9, 0..9, 0..4
    CHECK((r.k->intc_stat() & (1u << 10)) != 0);
    CHECK((r.bus().read32(kT1Mode) & 0x800u) == 0);  // never overflows
}

// Kernel::add_device_service / request_stop / set_vu_control_handler (integration hooks, docs/INTEGRATION_LOG.md).
TEST_CASE("device services: run at their deadline, after VBLANK_START and after installed syscalls; idle advances to them") {
    Rig r;
    std::vector<u64> calls;  // cycles at each call
    u64 want = 50'000;
    r.k->add_device_service([&] {
        calls.push_back(r.k->time().cycles);
        const u64 d = want;
        want = ~0ull;  // one timed wake-up only
        return d;
    });
    r.k->install_syscall(0x76, [](EEContext&, int) -> u64 { return 7; });
    r.k->start([](EEContext& c) {
        work(c, 10);                         // first slow check: services run once (deadline 50,000)
        while (c.cycles < 60'000) work(c, 1'000);
        CHECK(sys(c, 0x76) == 7);            // installed syscall: services run again
        while (g_rig->k->time().vblanks < 1) work(c, 100'000);
    });
    const RunResult res = r.k->run_until(nullptr);
    CHECK(res.status == RunStatus::MainExited);
    REQUIRE(calls.size() >= 4);
    CHECK(calls[1] >= 50'000);
    CHECK(calls[1] < 51'000);                // at the first check point past the deadline
    CHECK(calls[2] >= 60'000);               // after the installed syscall
    CHECK(calls.back() >= 4'920'115);        // after VBLANK_START 1
}

TEST_CASE("request_stop: taken before the point's interrupt delivery when requested from a service; resumable") {
    Rig r;
    int handler_runs = 0;
    static int* g_runs = nullptr;
    g_runs = &handler_runs;
    register_fn(0x00402000u, [](EEContext& c) {
        ++*g_runs;
        set_reg(c, GPR_V0, 0);
    });
    r.k->add_device_service([&] {
        if (r.k->time().vblanks == 1 && handler_runs == 0) r.k->request_stop();
        return ~0ull;
    });
    r.k->start([](EEContext& c) {
        sys(c, kAddIntcHandler, 2, 0x00402000u, 0, 0);
        sys(c, kEnableIntc, 2);
        c.cop0[12] |= 1u << 16;
        while (g_rig->k->time().vblanks < 2) work(c, 100'000);
    });
    RunResult res = r.k->run_until(nullptr);
    CHECK(res.status == RunStatus::Stopped);
    CHECK(r.k->time().vblanks == 1);
    CHECK(handler_runs == 0);  // VBLANK_START 1 processed, its handler not yet delivered
    res = r.k->run_until(nullptr);
    CHECK(res.status == RunStatus::MainExited);
    CHECK(handler_runs == 2);
}

TEST_CASE("RtHooks::vu_control_write reaches the VU control handler (CTC2 vi28 FBRST)") {
    Rig r;
    std::vector<std::pair<u32, u32>> seen;
    r.k->set_vu_control_handler([&](u32 reg, u32 v) { seen.emplace_back(reg, v); });
    r.hooks().vu_control_write(r.ctx, 28, 0x202u);
    REQUIRE(seen.size() == 1);
    CHECK(seen[0].first == 28u);
    CHECK(seen[0].second == 0x202u);
}
