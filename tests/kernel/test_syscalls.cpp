// Syscall surface: SetSyscall recording and the cause-12 trap (H-18/H-20), the libkernel installers'
// Copy / GetEntryAddress / FindAddress (K-11, B-06/B-11), never-installed and group-C traps (H-19), the
// GS/OSD/machine values (H-21..H-25), install_syscall for the SIF module, RtHooks trap/fatal, snapshots.
#include "kernel_test_util.h"

#include <cstdio>
#include <string>

using namespace kt;

namespace {

constexpr u32 kKCopy = 0x0050CC20u, kKFindAddress = 0x0050D4C0u;
constexpr u32 kPayloadSrc = 0x0077F568u;  // the ELF VA of kpayload_tlb (synthetic bytes here)
constexpr u32 kT3Mode = 0x10001810u, kT3Comp = 0x10001820u, kIntcMask = 0x1000F010u;

u32 g_sp_in_handler = 0;

// Synthetic stand-ins for the recompiled libkernel handlers (same semantics as the ELF's words:
// 0x50CC20 copies a2/4 words a1 -> a0 and returns 0; 0x50D4C0 returns the first word address in [a0, a1)
// holding a2, else 0).
void register_kernel_handlers() {
    register_fn(kKCopy, [](EEContext& c) {
        g_sp_in_handler = c.gpr[GPR_SP].u32[0];
        u32 dst = c.gpr[GPR_A0].u32[0], src = c.gpr[GPR_A1].u32[0];
        for (u32 n = c.gpr[GPR_A2].u32[0] >> 2; n; --n, dst += 4, src += 4) g_rig->w32(dst, g_rig->r32(src));
        set_reg(c, GPR_V0, 0);
    });
    register_fn(kKFindAddress, [](EEContext& c) {
        u32 p = c.gpr[GPR_A0].u32[0];
        const u32 end = c.gpr[GPR_A1].u32[0], want = c.gpr[GPR_A2].u32[0];
        for (; p < end; p += 4)
            if (g_rig->r32(p) == want) break;
        set_reg(c, GPR_V0, p < end ? static_cast<s32>(p) : 0);
    });
}

RunResult run_main(Rig& r, GuestFn f) {
    const RunResult res = r.k->run(f);
    CHECK_MESSAGE(r.fatals.empty(), (r.fatals.empty() ? std::string() : r.fatals.front()));
    return res;
}

// Run `f` expecting a fatal whose text contains `needle`.
void expect_fatal(GuestFn f, const char* needle, KernelOptions o = {}) {
    Rig r(std::move(o));
    const RunResult res = r.k->run(f);
    CHECK(res.status == RunStatus::Fatal);
    REQUIRE(r.fatals.size() == 1);
    CHECK_MESSAGE(r.fatals[0].find(needle) != std::string::npos, r.fatals[0]);
}

} // namespace

TEST_CASE("B-11 shape: SetSyscall(0x5A kCopy), (0x5B payload), Copy into kseg0, GetEntryAddress from the payload table") {
    register_kernel_handlers();
    Rig r;
    run_main(r, [](EEContext& c) {
        Rig& g = *g_rig;
        // A synthetic 816-byte payload whose lookup table sits at +0x300 like kpayload_tlb (ELF 0x77F868).
        const u32 table[12] = {0x55, 0x80075038u, 0x56, 0x800750C8u, 0x57, 0x80075108u,
                               0x58, 0x80075158u, 0x59, 0x800751A8u, 0x03, 0x80075330u};
        for (u32 i = 0; i < 816; i += 4) g.w32(kPayloadSrc + i, 0xC0DE0000u + i);
        for (u32 i = 0; i < 12; ++i) g.w32(kPayloadSrc + 0x300 + 4 * i, table[i]);
        set_reg(c, GPR_SP, 0x01FFFD60);
        set_reg(c, GPR_RA, 0x0050CCA8);
        sys(c, kSetSyscall, 0x5A, kKCopy);
        sys(c, kSetSyscall, 0x5B, 0x80075000);
        sys(c, kSetSyscall, 0x54, 0x0050D180);  // _kExitTLBHandler: recorded, never executed
        CHECK(g.k->syscall_installed(0x5A));
        CHECK(g.k->syscall_address(0x5B) == 0x80075000u);
        CHECK(sys(c, 0x5A, 0x80075000, kPayloadSrc, 816) == 0);  // Copy
        CHECK(g_sp_in_handler == 0x80019440u);                    // run on the kernel stack
        CHECK(c.gpr[GPR_SP].u32[0] == 0x01FFFD60u);               // caller's $sp / $ra restored
        CHECK(c.gpr[GPR_RA].u32[0] == 0x0050CCA8u);
        CHECK(g.mem.read<u32>(0x00075000u) == 0xC0DE0000u);       // kseg0 0x80075000 = physical 0x75000
        CHECK(g.mem.read<u32>(0x0007532Cu) == 0x80075330u);
        for (u32 n = 0x55; n <= 0x59; ++n) {
            const s64 a = sys(c, 0x5B, n);
            CHECK(a == static_cast<s32>(table[2 * (n - 0x55) + 1]));  // sign-extended kseg0 address
            sys(c, kSetSyscall, n, a);
        }
        CHECK(sys(c, 0x5B, 3) == static_cast<s32>(0x80075330u));  // dword_77F8E0 = GetEntryAddress(3)
        CHECK(sys(c, 0x5B, 0x99) == 0);
        CHECK(g.k->syscall_address(0x57) == 0x80075108u);
    });
}

TEST_CASE("B-06 shape: SetSyscall mirrors the kernel table at 0x80015500 so kFindAddress finds slot 0x83") {
    register_kernel_handlers();
    Rig r;
    run_main(r, [](EEContext& c) {
        sys(c, kSetSyscall, 0x83, kKFindAddress);
        sys(c, kSetSyscall, 0x5A, 0x0050D488);
        CHECK(g_rig->mem.read<u32>(0x0001570Cu) == kKFindAddress);  // 0x80015500 + 4 * 0x83
        const s64 a = sys(c, 0x83, 0x80000000, 0x80080000, kKFindAddress);
        CHECK(a == static_cast<s32>(0x8001570Cu));
        CHECK(a - 524 == static_cast<s32>(0x80015500u));  // dword_77FBB8 = match - 524 = the table base
        CHECK(sys(c, 0x83, 0x80000000, 0x80080000, 0x0050D488) - 360 == static_cast<s32>(0x80015500u));
        CHECK(sys(c, 0x83, 0x80000000, 0x80080000, 0x12345678) == 0);
    });
}

TEST_CASE("H-18/H-20: SetSyscall(0x12C) and negative n are recorded; T3 reads 0 at boot; cause 12 traps") {
    Rig r;
    run_main(r, [](EEContext& c) {
        CHECK(g_rig->bus().read32(kT3Mode) == 0);  // CMPE clear: InitAlarm installs its patch (`15` §5)
        set_reg(c, GPR_V0, 0x5555);
        sys(c, kSetSyscall, 0x12C, 0x80076488);  // InitAlarm table entry
        CHECK(c.gpr[GPR_V0].u64[0] == 0x5555u);   // no return value
        sys(c, kSetSyscall, 0xFC, 0x80076440);
        sys(c, kSetSyscall, 0x08, 0x800766C0);
        sys(c, kSetSyscall, static_cast<s32>(0xFFFFC402u), 0x80074123);  // libkernel's negative index
        CHECK(g_rig->k->cause12_dispatcher() == 0x80076488u);
        CHECK(g_rig->mem.read<u32>(0x000159B0u) == 0x80076488u);  // kintc_cause_dispatch_tbl[12]
        CHECK(g_rig->mem.read<u32>(0x00006508u) == 0x80074123u);  // 0x80015500 - 0xEFF8
        CHECK(g_rig->k->syscall_installed(0xFC));
        CHECK(sys(c, kAddIntcHandler, 12, 0x00500000, 0, 0) > 0);  // a list entry alone is harmless
    });
    expect_fatal([](EEContext& c) {
        sys(c, kSetSyscall, 0x12C, 0x80076488);
        sys(c, kEnableIntc, 12);
    }, "H-18/H-20");
    expect_fatal([](EEContext&) { g_rig->bus().write32(kIntcMask, 1u << 12); }, "cause 12 (TIM3) enabled");
    expect_fatal([](EEContext& c) {
        g_rig->bus().write32(kT3Comp, 1);
        g_rig->bus().write32(kT3Mode, 0x183u);  // H-BLANK, CUE, CMPE: the stock kernel alarm setting
        for (;;) work(c, 10'000);
    }, "cause 12 (TIM3) became pending");
    expect_fatal([](EEContext& c) {
        sys(c, kSetSyscall, 0xFC, 0x80076440);
        sys(c, 0xFC, 100, 0x00500000, 0);
    }, "never executed");
    expect_fatal([](EEContext& c) {
        sys(c, kSetSyscall, 0x55, 0x80075038);
        sys(c, -0x55, 0);
    }, "never executed");
}

TEST_CASE("H-19: never-installed slots, group C, stock alarms, SIF slots and out-of-range numbers trap by name") {
    expect_fatal([](EEContext& c) { sys(c, 0x5A, 0, 0, 0); }, "Copy): slot never installed");
    expect_fatal([](EEContext& c) { sys(c, 0x83, 0, 0, 0); }, "FindAddress): slot never installed");
    expect_fatal([](EEContext& c) { sys(c, 0x81); }, "0x81 (undefined): slot never installed");
    expect_fatal([](EEContext& c) { sys(c, 0x01); }, "ResetEE): group C");
    expect_fatal([](EEContext& c) { sys(c, 0x50, 0); }, "CreateEventFlag): group C");
    expect_fatal([](EEContext& c) { sys(c, 0x3B, 2); }, "RFU059");
    expect_fatal([](EEContext& c) { sys(c, 0x49, 0); }, "iDeleteSema): group C");
    expect_fatal([](EEContext& c) { sys(c, 0x18, 1, 0, 0); }, "stock kernel alarms");
    expect_fatal([](EEContext& c) { sys(c, 0x77, 0, 0); }, "SIF module has not installed");
    expect_fatal([](EEContext& c) { sys(c, 0x100); }, "out of range");
    expect_fatal([](EEContext& c) { sys(c, 0x6D, 0); }, "SetCPUTimer");
    expect_fatal([](EEContext& c) {
        sys(c, kSetSyscall, 0x20, 0x00500000);  // overriding a stock service
        sys(c, kCreateThread, kParamVa);
    }, "stock handler was replaced");
    expect_fatal([](EEContext& c) { sys(c, -0x32); }, "no interrupt form");
    expect_fatal([](EEContext&) { g_rig->bus().write32(0x10000010u, 0x84u); }, "GATE is not modelled");
}

TEST_CASE("install_syscall: the SIF module's slots, both signs, precedence over the stock table") {
    Rig r;
    CHECK(r.k->install_syscall(0x77, [](EEContext& c, int n) -> u64 { return static_cast<u64>(n) * 2 + c.gpr[GPR_A0].u64[0]; }));
    CHECK_FALSE(r.k->install_syscall(-0x77, [](EEContext&, int) -> u64 { return 0; }));  // same slot, taken
    CHECK(r.k->install_syscall(0x7C, [](EEContext&, int) -> u64 { return 0x42; }));       // Deci2Call
    CHECK_FALSE(r.k->install_syscall(0x100, [](EEContext&, int) -> u64 { return 0; }));
    run_main(r, [](EEContext& c) {
        CHECK(sys(c, 0x77, 5) == 0x77 * 2 + 5);
        CHECK(sys(c, -0x77, 1) == -0x77 * 2 + 1);
        CHECK(sys(c, 0x7C) == 0x42);
    });
}

TEST_CASE("H-21..H-25 and group B: IMR cache, OSD word round trip, GS DX/DY offsets, machine values, FlushCache") {
    Rig r;
    run_main(r, [](EEContext& c) {
        Rig& g = *g_rig;
        CHECK(sys(c, 0x71, 0xFF00) == 0xFF00);  // GsPutIMR (sceGsResetGraph, B-47)
        REQUIRE(g.gs.imr_writes.size() == 1);
        CHECK(g.gs.imr_writes[0] == 0xFF00u);    // reached 0x12001010 through the bus
        g.gs.imr = 0x1234;                       // the register changes behind the kernel's back
        CHECK(sys(c, 0x70) == 0xFF00);           // GsGetIMR: the cached copy (H-21)
        CHECK(sys(c, -0x70) == 0xFF00);
        CHECK(g.k->gs_imr() == 0xFF00u);
        // SetOsdConfigParam / GetOsdConfigParam: verbatim 32-bit word (PatchIsNeeded's bits 13-15, H-22).
        g.w32(kScratchVa, 0xDEADE000u);
        sys(c, 0x4A, kScratchVa);
        g.w32(kScratchVa + 4, 0);
        sys(c, 0x4B, kScratchVa + 4);
        CHECK(g.r32(kScratchVa + 4) == 0xDEADE000u);
        // _GetGsDxDyOffset: early model -> all four zero (H-23, Q-03 default).
        for (u32 i = 0; i < 4; ++i) g.w32(kScratchVa + 0x10 + 4 * i, 0xFFFFFFFFu);
        sys(c, 0x80, 2, kScratchVa + 0x10, kScratchVa + 0x14, kScratchVa + 0x18, kScratchVa + 0x1C);
        for (u32 i = 0; i < 4; ++i) CHECK(g.r32(kScratchVa + 0x10 + 4 * i) == 0);
        // MachineType / PSMode / GetMemorySize (H-24).
        CHECK(sys(c, 0x7E) == 0);
        sys(c, 0x7D);
        CHECK(sys(c, 0x7E) == 0x8000);
        CHECK(sys(c, 0x7F) == 0x02000000);
        // FlushCache (any mode) is a no-op that leaves $v0 alone (H-25).
        set_reg(c, GPR_V0, 0x77);
        sys(c, 0x64, 0);
        sys(c, 0x64, 2);
        sys(c, -0x68, 1);
        CHECK(c.gpr[GPR_V0].u64[0] == 0x77u);
        // SetGsCrt(1, 2, 0) recorded (K-02); mode 0/1 resolve to NTSC.
        sys(c, 0x02, 1, 2, 0);
        CHECK(g.k->gs_crt().set);
        CHECK(g.k->gs_crt().interlace == 1);
        CHECK(g.k->gs_crt().mode == 2);
        sys(c, 0x02, 0, 1, 1);
        CHECK(g.k->gs_crt().mode == 2);
        CHECK(g.k->gs_crt().ffmd == 1);
        // Group B stubs.
        CHECK(sys(c, 0x7C) == 0);  // Deci2Call without a SIF override
        CHECK(sys(c, 0x63, 12) == static_cast<s32>(c.cop0[12]));
        CHECK(sys(c, 0x66, 0) == 0);
        CHECK(sys(c, 0x61) == 0);
        CHECK(sys(c, 0x6B) == 0);
        CHECK(sys(c, 0x4C) == 0);
        // _print logs the format string.
        const char* msg = "jpx235\n";
        for (u32 i = 0; msg[i]; ++i) g.mem.write<u8>(kScratchVa + 0x40 + i, static_cast<u8>(msg[i]));
        g.mem.write<u8>(kScratchVa + 0x47, 0);
        sys(c, 0x75, kScratchVa + 0x40);
    });
    REQUIRE_FALSE(r.logs.empty());
    CHECK(r.logs.back() == "_print: jpx235\n");
}

TEST_CASE("RtHooks: break and undecodable words are fatal with pc / $v1 / thread; fatal() reports the text") {
    expect_fatal([](EEContext& c) { g_rig->hooks().trap(c, 0x00242000u, 0, 7); }, "break 0x00007 at 0x00242000");
    expect_fatal([](EEContext& c) { g_rig->hooks().trap(c, 0x00100010u, 1, 0xFFFFFFFFu); }, "undecodable");
    expect_fatal([](EEContext& c) {
        set_reg(c, GPR_V1, 0x3C);
        g_rig->hooks().fatal(c, 0x00123456u, "lookup miss");
    }, "lookup miss (pc 0x00123456, $v1 0x0000003C, thread 1)");
    expect_fatal([](EEContext& c) {
        // A handler VA with no recompiled function behind it (test table miss -> fatal()).
        sys(c, kAddIntcHandler, 9, 0x00ABCDE0, 0, 0);
        sys(c, kEnableIntc, 9);
        c.cop0[12] |= 1u << 16;
        g_rig->bus().raise_intc(9);
        work(c, 1);
    }, "no function registered");
}

TEST_CASE("snapshot_eemem writes the 32 MiB physical RAM image") {
    Rig r;
    r.w32(0x00100000u, 0x0C064E60u);
    r.w32(0x01FFFFFCu, 0xA5A5A5A5u);
    char path[512];
    std::snprintf(path, sizeof path, "%s", "p3fes_kernel_test_snapshot.bin");
    REQUIRE(r.k->snapshot_eemem(path));
    std::FILE* f = std::fopen(path, "rb");
    REQUIRE(f);
    std::fseek(f, 0, SEEK_END);
    CHECK(std::ftell(f) == 32L * 1024 * 1024);
    u32 w = 0;
    std::fseek(f, 0x100000, SEEK_SET);
    CHECK(std::fread(&w, 4, 1, f) == 1);
    CHECK(w == 0x0C064E60u);
    std::fseek(f, 0x1FFFFFC, SEEK_SET);
    CHECK(std::fread(&w, 4, 1, f) == 1);
    CHECK(w == 0xA5A5A5A5u);
    std::fclose(f);
    std::remove(path);
}
