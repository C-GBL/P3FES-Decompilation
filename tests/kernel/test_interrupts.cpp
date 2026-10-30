// INTC/DMAC handler chains: docs/ANALYSIS/15 §2 and §8 H-01..H-04, H-06, H-07 (and H-03's cause-2 cadence).
#include "kernel_test_util.h"

#include <string>

using namespace kt;

namespace {

std::vector<std::string> g_log;
u32 g_seen_gp = 0, g_seen_sp = 0, g_seen_a1 = 0, g_seen_a2 = 0;
int g_ids[8] = {};

constexpr u32 kGate = 0x00300000u, kRw = 0x00300100u, kCb = 0x00300200u;
constexpr u32 kH1 = 0x00301000u, kH2 = 0x00301100u, kH3 = 0x00301200u, kH4 = 0x00301300u;
constexpr u32 kIntcStat = 0x1000F000u, kDStat = 0x1000E010u;
constexpr u32 kFlagVa = 0x00220000u, kCsrVa = 0x00220010u;

void ei(EEContext& c) { c.cop0[12] |= 1u << 16; }
void ret(EEContext& c, s64 v) { set_reg(c, GPR_V0, v); }

RunResult run_main(Rig& r, GuestFn f) {
    const RunResult res = r.k->run(f);
    CHECK_MESSAGE(r.fatals.empty(), (r.fatals.empty() ? std::string() : r.fatals.front()));
    return res;
}

void until_vblanks(EEContext& c, u64 n) {
    while (g_rig->k->time().vblanks < n) work(c, 50'000);
}

} // namespace

TEST_CASE("H-03: cause-2 chain [gate, RW, cb] from next = 0, 0, -1; gate's -1 on even fields stops RW and cb") {
    g_log.clear();
    g_seen_gp = g_seen_sp = 0;
    register_fn(kGate, [](EEContext& c) {
        // kwlnVsyncFieldGate 0x19D320: ld GS_CSR; FIELD (bit 13) == 0 -> -1, else 0; `sync; ei`
        const u64 csr = g_rig->bus().read64(0x12001000u);
        g_log.push_back((csr >> 13) & 1 ? "G1" : "G0");
        g_seen_gp = c.gpr[GPR_GP].u32[0];
        g_seen_sp = c.gpr[GPR_SP].u32[0];
        ei(c);
        ret(c, ((csr >> 13) & 1) ? 0 : -1);
    });
    register_fn(kRw, [](EEContext& c) { g_log.push_back("R"); ret(c, 0); });
    register_fn(kCb, [](EEContext& c) { g_log.push_back("C"); ret(c, 0); });
    Rig r;
    const RunResult res = run_main(r, [](EEContext& c) {
        set_reg(c, GPR_GP, 0x7D2CF0);
        set_reg(c, GPR_S0, 0x1234);
        g_ids[0] = static_cast<int>(sys(c, kAddIntcHandler, 2, kRw, 0, 0));    // _rwDMAHook, next 0
        g_ids[1] = static_cast<int>(sys(c, kAddIntcHandler, 2, kGate, 0, 0));  // kwlnInstallVsyncFieldGate, next 0
        g_ids[2] = static_cast<int>(sys(c, kAddIntcHandler, 2, kCb, -1, 0));   // sceGsSyncVCallback, next -1
        CHECK(sys(c, kEnableIntc, 2) == 1);
        ei(c);
        until_vblanks(c, 20);
        CHECK(c.gpr[GPR_S0].u64[0] == 0x1234u);  // interrupted context restored after every chain
        CHECK(c.gpr[GPR_GP].u32[0] == 0x7D2CF0u);
    });
    CHECK(res.status == RunStatus::MainExited);
    CHECK(g_ids[0] == 1);
    CHECK(g_ids[1] == 2);
    CHECK(g_ids[2] == 3);
    int gates = 0, rws = 0, cbs = 0;
    for (const auto& s : g_log) {
        gates += s[0] == 'G';
        rws += s == "R";
        cbs += s == "C";
    }
    CHECK(gates == 20);
    CHECK(rws == 10);  // 10 flips over 20 fields (30 / 60 Hz)
    CHECK(cbs == 10);
    REQUIRE(g_log.size() == 40);
    // Field 1 first (FIELD toggles at VBLANK_START from 0): [G1 R C] [G0] [G1 R C] [G0] ...
    for (std::size_t i = 0; i < g_log.size();) {
        CHECK(g_log[i] == "G1");
        CHECK(g_log[i + 1] == "R");
        CHECK(g_log[i + 2] == "C");
        CHECK(g_log[i + 3] == "G0");
        i += 4;
    }
    CHECK(g_seen_gp == 0x7D2CF0u);  // registrant's $gp
    CHECK(g_seen_sp == 0x81FC0u);   // trampoline stack
}

TEST_CASE("H-01/H-02: insert positions, shared id pool, invalid arguments, stop on a negative return") {
    g_log.clear();
    register_fn(kH1, [](EEContext& c) { g_log.push_back("1"); ret(c, 5); });
    register_fn(kH2, [](EEContext& c) { g_log.push_back("2"); ret(c, 0); });
    register_fn(kH3, [](EEContext& c) {
        g_log.push_back("3");
        g_seen_a1 = c.gpr[GPR_A1].u32[0];
        g_seen_a2 = c.gpr[GPR_A0].u32[0];
        ret(c, 0);
    });
    register_fn(kH4, [](EEContext& c) { g_log.push_back("4"); ret(c, -2); });
    Rig r;
    run_main(r, [](EEContext& c) {
        ei(c);
        const s64 h1 = sys(c, kAddIntcHandler, 5, kH1, 0, 0);
        const s64 d1 = sys(c, kAddDmacHandler, 1, kH2, 0, 0);  // DMAC shares the pool
        const s64 h2 = sys(c, kAddIntcHandler, 5, kH2, 0, 0);
        const s64 h3 = sys(c, kAddIntcHandler, 5, kH3, -1, 0x77);
        const s64 h4 = sys(c, kAddIntcHandler, 5, kH4, h1, 0);  // immediately before h1
        CHECK(h1 == 1);
        CHECK(d1 == 2);
        CHECK(h2 == 3);
        CHECK(h3 == 4);
        CHECK(h4 == 5);
        CHECK(g_rig->k->handler_count(false, 5) == 4);
        CHECK(g_rig->k->handler_count(true, 1) == 1);
        // Invalid arguments.
        CHECK(sys(c, kAddIntcHandler, 15, kH1, 0, 0) == -1);
        CHECK(sys(c, kAddIntcHandler, 1, kH1, 0, 0) == -1);  // SBUS is the kernel's
        CHECK(sys(c, kAddIntcHandler, -1, kH1, 0, 0) == -1);
        CHECK(sys(c, kAddIntcHandler, 5, kH1, 129, 0) == -1);
        CHECK(sys(c, kAddIntcHandler, 5, kH1, 100, 0) == -1);  // id not in use
        CHECK(sys(c, kAddIntcHandler, 5, kH1, -2, 0) == -1);
        CHECK(sys(c, kAddDmacHandler, 16, kH1, 0, 0) == -1);
        CHECK(sys(c, kRemoveIntcHandler, 5, 0) == -1);
        CHECK(sys(c, kRemoveIntcHandler, 5, 129) == -1);
        // Order is [h2, h4, h1, h3]; h4 returns -2 -> h1 and h3 do not run.
        CHECK(sys(c, kEnableIntc, 5) == 1);
        g_rig->bus().raise_intc(5);
        work(c, 1);
        CHECK(g_log == std::vector<std::string>{"2", "4"});
        // Disable h4's node (mode 1): skipped; h1 returns 5 (>= 0 continues), h3 gets (cause, arg, EPC).
        g_log.clear();
        CHECK(sys(c, 0x5D, 5, h4) == 0);  // DisableIntcHandler
        g_rig->bus().raise_intc(5);
        work(c, 1);
        CHECK(g_log == std::vector<std::string>{"2", "1", "3"});
        CHECK(g_seen_a1 == 0x77u);
        CHECK(g_seen_a2 == 5u);
        // Remove frees the id to the FIFO tail: new ids continue at 6 before 2 is reused.
        CHECK(sys(c, kRemoveDmacHandler, 1, d1) == 0);
        CHECK(sys(c, kAddIntcHandler, 6, kH1, 0, 0) == 6);
        CHECK(g_rig->k->handler_count(true, 1) == 0);
        // Exhaust the pool: 128 ids in total.
        int n = 0;
        while (sys(c, kAddIntcHandler, 7, kH1, -1, 0) > 0) ++n;
        CHECK(n == 128 - 6 + 1);  // 6 in use before the loop minus the removed one
    });
}

TEST_CASE("H-04: one cause per delivery, highest first, ack before dispatch, no nesting, DMAC before INTC") {
    g_log.clear();
    register_fn(kH1, [](EEContext& c) {
        const u32 cause = c.gpr[GPR_A0].u32[0];
        const u32 stat = g_rig->bus().read32(kIntcStat);
        g_log.push_back("i" + std::to_string(cause) + ((stat >> cause) & 1 ? "!" : ""));
        if (cause == 9) {
            g_rig->bus().raise_intc(10);  // raised inside a handler: must wait for the chain to end
            work(c, 1000);                // check points inside a handler do not deliver
            g_log.push_back("i9-end");
        }
        ret(c, 0);
    });
    register_fn(kH2, [](EEContext& c) {
        const u32 ch = c.gpr[GPR_A0].u32[0];
        const u32 ds = g_rig->bus().read32(kDStat);
        g_log.push_back("d" + std::to_string(ch) + ((ds >> ch) & 1 ? "!" : ""));
        ret(c, 0);
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        for (int cause : {3, 5, 9, 10}) {
            sys(c, kAddIntcHandler, cause, kH1, 0, 0);
            sys(c, kEnableIntc, cause);
        }
        sys(c, kAddDmacHandler, 2, kH2, 0, 0);
        CHECK(sys(c, kEnableDmac, 2) == 1);
        // Pending while EIE is clear (the main thread starts with EIE clear, crt0 executes `ei`): nothing runs.
        g_rig->bus().raise_intc(3);
        g_rig->bus().raise_intc(5);
        g_rig->bus().raise_intc(9);
        g_rig->bus().dma_complete(2);
        work(c, 10);
        CHECK(g_log.empty());
        ei(c);
        // Delivery after EI waits for the masked-interrupt poll (KernelOptions::masked_poll_cycles = 64):
        // the adapter need not call check_events after EI.
        work(c, 10);
        CHECK(g_log.empty());
        work(c, 64);
    });
    std::string joined;
    for (const auto& e : g_log) joined += e + " ";
    const std::vector<std::string> expect{"d2", "i9", "i9-end", "i10", "i5", "i3"};
    CHECK_MESSAGE(g_log == expect, joined);
}

TEST_CASE("H-06: SetVSyncFlag is serviced at the next VBLANK_START before the cause-2 handlers, once") {
    g_log.clear();
    register_fn(kH1, [](EEContext& c) {
        g_log.push_back("h flag=" + std::to_string(g_rig->r32(kFlagVa)) + " csr=" + std::to_string(g_rig->r32(kCsrVa)));
        ret(c, -1);  // a negative return does not undo the flag service
    });
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kAddIntcHandler, 2, kH1, 0, 0);
        sys(c, kEnableIntc, 2);
        ei(c);
        g_rig->w32(kFlagVa, 0);
        g_rig->w32(kCsrVa, 0xFFFFFFFFu);
        sys(c, kSetVSyncFlag, kFlagVa, kCsrVa);
        until_vblanks(c, 1);
        CHECK(g_rig->r32(kFlagVa) == 1);
        CHECK(g_rig->r32(kCsrVa) == (1u << 13));  // GS_CSR at the vblank (FIELD = 1), stored as u64
        CHECK(g_rig->r32(kCsrVa + 4) == 0);
        g_rig->w32(kFlagVa, 0);
        until_vblanks(c, 2);
        CHECK(g_rig->r32(kFlagVa) == 0);  // one-shot
    });
    REQUIRE(g_log.size() == 2);
    CHECK(g_log[0] == "h flag=1 csr=8192");
    CHECK(g_log[1] == "h flag=0 csr=8192");
}

TEST_CASE("H-07: Enable/Disable Intc/Dmac return whether the mask bit changed; i forms share the slot") {
    Rig r;
    run_main(r, [](EEContext& c) {
        CHECK(sys(c, kEnableIntc, 9) == 1);
        CHECK(sys(c, kEnableIntc, 9) == 0);
        CHECK(sys(c, -0x1A, 11) == 1);  // iEnableIntc
        CHECK(g_rig->k->intc_mask() == ((1u << 9) | (1u << 11)));
        CHECK(sys(c, kDisableIntc, 9) == 1);
        CHECK(sys(c, kDisableIntc, 9) == 0);
        CHECK(sys(c, -0x1B, 11) == 1);
        CHECK(g_rig->k->intc_mask() == 0);
        CHECK(sys(c, kEnableDmac, 5) == 1);
        CHECK(sys(c, kEnableDmac, 5) == 0);
        CHECK((g_rig->k->d_stat() >> 16) == (1u << 5));
        CHECK(sys(c, -0x1D, 5) == 1);  // iDisableDmac
        CHECK(sys(c, kDisableDmac, 5) == 0);
        CHECK(g_rig->k->d_stat() == 0);
        CHECK(sys(c, kEnableIntc, 15) == -1);
    });
}

TEST_CASE("DMAC chain: completion sets D_STAT, the handler gets the channel, the bit is acked before dispatch") {
    g_log.clear();
    register_fn(kH1, [](EEContext& c) {
        const u32 ch = c.gpr[GPR_A0].u32[0];
        g_log.push_back("a" + std::to_string(ch) + ((g_rig->bus().read32(kDStat) >> ch) & 1 ? "!" : ""));
        ret(c, -1);
    });
    register_fn(kH2, [](EEContext& c) { g_log.push_back("b"); ret(c, 0); });
    Rig r;
    run_main(r, [](EEContext& c) {
        ei(c);
        sys(c, kAddDmacHandler, 1, kH2, 0, 0);
        sys(c, kAddDmacHandler, 1, kH1, 0, 0);  // head: [a, b]; a returns -1
        // CIS set while CIM is clear: no interrupt, the bit stays readable.
        g_rig->bus().dma_complete(1);
        work(c, 1);
        CHECK(g_log.empty());
        CHECK((g_rig->bus().read32(kDStat) & 2u) != 0);
        g_rig->bus().write32(kDStat, 2u);  // W1C
        CHECK((g_rig->bus().read32(kDStat) & 2u) == 0);
        sys(c, kEnableDmac, 1);
        g_rig->bus().dma_complete(1);
        work(c, 1);
        CHECK((g_rig->bus().read32(kDStat) & 2u) == 0);  // acked by the dispatcher
    });
    CHECK(g_log == std::vector<std::string>{"a1"});
}

TEST_CASE("an enabled cause with an empty list is fatal (the kernel prints and KExits)") {
    Rig r;
    const RunResult res = r.k->run([](EEContext& c) {
        ei(c);
        sys(c, kEnableIntc, 4);
        g_rig->bus().raise_intc(4);
        work(c, 1);
        CHECK(false);  // not reached
    });
    CHECK(res.status == RunStatus::Fatal);
    REQUIRE(r.fatals.size() == 1);
    CHECK(r.fatals[0].find("# INTC(4) Handler does not exist.") != std::string::npos);
    // Sticky: a later run reports the same fatal without running anything.
    CHECK(r.k->run_until(nullptr).status == RunStatus::Fatal);
}
