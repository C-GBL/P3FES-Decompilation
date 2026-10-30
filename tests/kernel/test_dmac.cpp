// DMAC register block and transfer engine: normal and source-chain modes (refe/cnt/next/ref/end, call/ret
// with the ASR stack, TIE, TTE), a stalling data path, SPR channels 8/9, D_STAT semantics, traps
// (RUNTIME_CONTRACT §5.1, docs/ANALYSIS/10 §5 item 5, `15` §2.1).
#include "kernel_test_util.h"

#include <algorithm>
#include <limits>

using namespace kt;

namespace {

constexpr u32 kDCtrl = 0x1000E000u, kDStat = 0x1000E010u, kDPcr = 0x1000E020u;
constexpr u32 kD1 = 0x10009000u, kD2 = 0x1000A000u, kD8 = 0x1000D000u, kD9 = 0x1000D400u, kD0 = 0x10008000u;
constexpr u32 kChcr = 0x00, kMadr = 0x10, kQwc = 0x20, kTadr = 0x30, kSadr = 0x80;
constexpr u32 kDEnableW = 0x1000F590u, kDEnableR = 0x1000F520u;

struct Sink final : DmaChannelHandler {
    std::vector<u64> lo, hi, tags;
    std::vector<std::size_t> offered;
    std::size_t per_call = std::numeric_limits<std::size_t>::max();
    std::size_t transfer(u128* d, std::size_t qwc, u64 tag) override {
        offered.push_back(qwc);
        const std::size_t n = std::min(qwc, per_call);
        for (std::size_t i = 0; i < n; ++i) {
            lo.push_back(d[i].u64[0]);
            hi.push_back(d[i].u64[1]);
            tags.push_back(tag);
        }
        return n;
    }
};

constexpr u64 dmatag(u32 id, u32 qwc, u32 addr = 0, bool irq = false) {
    return u64{qwc} | (u64{id} << 28) | (u64{irq ? 1u : 0u} << 31) | (u64{addr} << 32);
}
enum : u32 { kRefe = 0, kCnt = 1, kNext = 2, kRef = 3, kRefs = 4, kCall = 5, kRet = 6, kEnd = 7 };

void qw(Rig& r, u32 va, u64 lo, u64 hi = 0) {
    r.mem.write<u64>(va, lo);
    r.mem.write<u64>(va + 8, hi);
}
u32 reg(Rig& r, u32 base, u32 off) { return r.bus().read32(base + off); }
void setreg(Rig& r, u32 base, u32 off, u32 v) { r.bus().write32(base + off, v); }

} // namespace

TEST_CASE("DMAC normal mode: data to the handler, STR until the completion event, D_STAT CIS, DMAE hold") {
    Rig r;
    Sink s;
    r.bus().set_dma_handler(2, &s);
    for (u32 i = 0; i < 13; ++i) qw(r, 0x00965770u + 16 * i, 0x100 + i, 0x200 + i);
    setreg(r, kD2, kMadr, 0x00965770u);
    setreg(r, kD2, kQwc, 13);
    setreg(r, kD2, kChcr, 0x101u);  // STR, DIR from memory, normal (sceDmaSendN, B-48)
    CHECK(s.lo.empty());            // D_CTRL.DMAE is clear: held
    CHECK((reg(r, kD2, kChcr) & 0x100u) != 0);
    r.bus().write32(kDCtrl, 1u);  // sceDmaReset's D_CTRL |= 1
    REQUIRE(s.lo.size() == 13);
    CHECK(s.offered == std::vector<std::size_t>{13});
    for (u32 i = 0; i < 13; ++i) {
        CHECK(s.lo[i] == 0x100 + i);
        CHECK(s.hi[i] == 0x200 + i);
        CHECK(s.tags[i] == 0);
    }
    CHECK(reg(r, kD2, kQwc) == 0);
    CHECK(reg(r, kD2, kMadr) == 0x00965770u + 13 * 16);
    // Completion after dma_base_cycles (64) + 13 * 2.
    work(r.ctx, 64 + 26 - 1);
    CHECK((reg(r, kD2, kChcr) & 0x100u) != 0);
    CHECK((r.bus().read32(kDStat) & 4u) == 0);
    work(r.ctx, 1);
    CHECK((reg(r, kD2, kChcr) & 0x100u) == 0);
    CHECK((r.bus().read32(kDStat) & 4u) != 0);
    // D_STAT: CIS write-1-to-clear, CIM toggles on a 1.
    r.bus().write32(kDStat, 0x00040004u);
    CHECK(r.bus().read32(kDStat) == 0x00040000u);
    r.bus().write32(kDStat, 0x00060000u);
    CHECK(r.bus().read32(kDStat) == 0x00020000u);
    r.bus().write32(kDPcr, 0x100u);  // Q-04: stored
    CHECK(r.bus().read32(kDPcr) == 0x100u);
    CHECK(r.k->unhandled_accesses() == 0);
}

TEST_CASE("DMAC source chain: cnt, next, ref, call/call/ret/ret (ASR stack), end; refe; ret on an empty stack") {
    Rig r;
    Sink s;
    r.bus().set_dma_handler(1, &s);
    r.bus().write32(kDCtrl, 1u);
    // T0 cnt(1) A | T1 next(1) -> 0x100100, B | T2 @100100 ref(2) -> 0x180000 C0 C1 | T3 call(1) -> 0x100200, D
    // T4 @100200 call(0) -> 0x100300 | T5 @100300 ret(1) E -> pops 0x100210 | T6 @100210 ret(0) -> pops 0x100130
    // T7 @100130 end(1) F
    qw(r, 0x100000u, dmatag(kCnt, 1), 0xAA00);
    qw(r, 0x100010u, 0xA);
    qw(r, 0x100020u, dmatag(kNext, 1, 0x100100u));
    qw(r, 0x100030u, 0xB);
    qw(r, 0x100100u, dmatag(kRef, 2, 0x180000u));
    qw(r, 0x180000u, 0xC0);
    qw(r, 0x180010u, 0xC1);
    qw(r, 0x100110u, dmatag(kCall, 1, 0x100200u));
    qw(r, 0x100120u, 0xD);
    qw(r, 0x100200u, dmatag(kCall, 0, 0x100300u));
    qw(r, 0x100300u, dmatag(kRet, 1));
    qw(r, 0x100310u, 0xE);
    qw(r, 0x100210u, dmatag(kRet, 0));
    qw(r, 0x100130u, dmatag(kEnd, 1));
    qw(r, 0x100140u, 0xF);
    setreg(r, kD1, kTadr, 0x100000u);
    setreg(r, kD1, kQwc, 0);
    setreg(r, kD1, kChcr, 0x105u);  // sceDmaSend: STR, chain, DIR
    CHECK(s.lo == std::vector<u64>{0xA, 0xB, 0xC0, 0xC1, 0xD, 0xE, 0xF});
    CHECK(s.tags.front() == dmatag(kCnt, 1));
    CHECK(s.tags[2] == dmatag(kRef, 2, 0x180000u));
    CHECK(s.tags.back() == dmatag(kEnd, 1));
    CHECK(((reg(r, kD1, kChcr) >> 4) & 3u) == 0);  // ASP back to 0
    CHECK((reg(r, kD1, kChcr) >> 16) == (static_cast<u32>(dmatag(kEnd, 1)) >> 16));  // TAG field = last tag
    CHECK(reg(r, kD1, kTadr) == 0x100150u);
    work(r.ctx, 64 + 7 * 2);
    CHECK((reg(r, kD1, kChcr) & 0x100u) == 0);
    CHECK((r.bus().read32(kDStat) & 2u) != 0);

    // refe ends after its data; a ret with an empty ASR stack ends too (VU1 microprogram `ret` packets).
    s = Sink{};
    qw(r, 0x100400u, dmatag(kRefe, 1, 0x180020u));
    qw(r, 0x180020u, 0x6);
    qw(r, 0x100410u, dmatag(kCnt, 1));  // must not be read
    setreg(r, kD1, kTadr, 0x100400u);
    setreg(r, kD1, kChcr, 0x105u);
    CHECK(s.lo == std::vector<u64>{0x6});
    work(r.ctx, 1000);
    s = Sink{};
    qw(r, 0x100500u, dmatag(kRet, 2));
    qw(r, 0x100510u, 0x71);
    qw(r, 0x100520u, 0x72);
    setreg(r, kD1, kTadr, 0x100500u);
    setreg(r, kD1, kChcr, 0x105u);
    CHECK(s.lo == std::vector<u64>{0x71, 0x72});
    work(r.ctx, 1000);
    CHECK((reg(r, kD1, kChcr) & 0x100u) == 0);
}

TEST_CASE("DMAC: refs behaves as ref (stall control is trapped at start); D_SQWC/D_RBSR/D_RBOR/D_STADR are storage") {
    Rig r;
    Sink s;
    r.bus().set_dma_handler(1, &s);
    r.bus().write32(kDCtrl, 1u);
    qw(r, 0x100000u, dmatag(kRefs, 1, 0x180000u));
    qw(r, 0x180000u, 0x99);
    qw(r, 0x100010u, dmatag(kEnd, 0));
    setreg(r, kD1, kTadr, 0x100000u);
    setreg(r, kD1, kChcr, 0x105u);
    CHECK(s.lo == std::vector<u64>{0x99});
    CHECK(reg(r, kD1, kTadr) == 0x100020u);
    for (u32 a : {0x1000E030u, 0x1000E040u, 0x1000E050u, 0x1000E060u}) {
        r.bus().write32(a, a ^ 0x5A5Au);
        CHECK(r.bus().read32(a) == (a ^ 0x5A5Au));
    }
    setreg(r, kD1, 0x40, 0x1234u);  // ASR0 / ASR1 readable
    setreg(r, kD1, 0x50, 0x5678u);
    CHECK(reg(r, kD1, 0x40) == 0x1234u);
    CHECK(reg(r, kD1, 0x50) == 0x5678u);
    CHECK(r.k->unhandled_accesses() == 0);
}

TEST_CASE("DMAC chain: TIE + tag IRQ ends the transfer; TTE delivers the tag qword with its DMAtag half zeroed") {
    Rig r;
    Sink s;
    r.bus().set_dma_handler(1, &s);
    r.bus().write32(kDCtrl, 1u);
    qw(r, 0x100000u, dmatag(kCnt, 1, 0, true), 0x0123456789ABCDEFull);  // IRQ bit; upper half = VIF codes
    qw(r, 0x100010u, 0x11);
    qw(r, 0x100020u, dmatag(kEnd, 1));
    qw(r, 0x100030u, 0x22);
    setreg(r, kD1, kTadr, 0x100000u);
    setreg(r, kD1, kChcr, 0x185u);  // TIE: the IRQ tag ends the chain
    CHECK(s.lo == std::vector<u64>{0x11});
    work(r.ctx, 1000);
    // TTE (0x145, RW image upload): tag qword first.
    s = Sink{};
    setreg(r, kD1, kTadr, 0x100000u);
    setreg(r, kD1, kChcr, 0x145u);
    REQUIRE(s.lo.size() == 4);
    CHECK(s.lo[0] == 0);
    CHECK(s.hi[0] == 0x0123456789ABCDEFull);
    CHECK(s.lo[1] == 0x11);
    CHECK(s.lo[2] == 0);
    CHECK(s.lo[3] == 0x22);
    CHECK(s.tags[0] == dmatag(kCnt, 1, 0, true));
}

TEST_CASE("DMAC: a stalling data path is resumed at later check points; STR clears only after all data") {
    Rig r;
    Sink s;
    s.per_call = 3;
    r.bus().set_dma_handler(2, &s);
    r.bus().write32(kDCtrl, 1u);
    for (u32 i = 0; i < 10; ++i) qw(r, 0x100000u + 16 * i, i);
    setreg(r, kD2, kMadr, 0x100000u);
    setreg(r, kD2, kQwc, 10);
    setreg(r, kD2, kChcr, 0x101u);
    CHECK(s.lo.size() == 3);
    CHECK(reg(r, kD2, kQwc) == 7);
    CHECK(reg(r, kD2, kMadr) == 0x100030u);
    work(r.ctx, 1);  // before the retry quantum (64 cycles): nothing
    CHECK(s.lo.size() == 3);
    for (int i = 0; i < 3; ++i) work(r.ctx, 64);
    CHECK(s.lo.size() == 10);
    CHECK(s.offered == std::vector<std::size_t>{10, 7, 4, 1});
    CHECK((reg(r, kD2, kChcr) & 0x100u) != 0);
    work(r.ctx, 64 + 20);
    CHECK((reg(r, kD2, kChcr) & 0x100u) == 0);
    for (u32 i = 0; i < 10; ++i) CHECK(s.lo[i] == i);
    // A chain stalled in the middle of a block resumes with the same tag.
    s = Sink{};
    s.per_call = 1;
    qw(r, 0x100200u, dmatag(kCnt, 2));
    qw(r, 0x100210u, 0x51);
    qw(r, 0x100220u, 0x52);
    qw(r, 0x100230u, dmatag(kEnd, 0));
    setreg(r, kD2, kTadr, 0x100200u);
    setreg(r, kD2, kChcr, 0x104u | 0x100u);
    CHECK(s.lo.size() == 1);
    work(r.ctx, 64);
    CHECK(s.lo == std::vector<u64>{0x51, 0x52});
    CHECK(s.tags == std::vector<u64>{dmatag(kCnt, 2), dmatag(kCnt, 2)});
    work(r.ctx, 1000);
    CHECK((reg(r, kD2, kChcr) & 0x100u) == 0);
}

TEST_CASE("DMAC: clearing STR stops the channel without completion") {
    Rig r;
    Sink s;
    s.per_call = 0;  // never consumes
    r.bus().set_dma_handler(1, &s);
    r.bus().write32(kDCtrl, 1u);
    setreg(r, kD1, kMadr, 0x100000u);
    setreg(r, kD1, kQwc, 4);
    setreg(r, kD1, kChcr, 0x101u);
    work(r.ctx, 200);
    CHECK((reg(r, kD1, kChcr) & 0x100u) != 0);
    setreg(r, kD1, kChcr, 0x001u);
    work(r.ctx, 10'000);
    CHECK((r.bus().read32(kDStat) & 2u) == 0);
    CHECK(reg(r, kD1, kQwc) == 4);
    const std::size_t calls = s.offered.size();
    work(r.ctx, 10'000);
    CHECK(s.offered.size() == calls);  // no more retries
}

TEST_CASE("DMAC SPR channels: toSPR / fromSPR normal, MADR bit 31 = scratchpad, fromSPR destination chain") {
    Rig r;
    r.bus().write32(kDCtrl, 1u);
    u8* spr = r.mem.scratchpad();
    // ch9 toSPR: RAM 0x100000 x4 -> SPR 0x3FE0 (wraps at 16 KiB).
    for (u32 i = 0; i < 4; ++i) qw(r, 0x100000u + 16 * i, 0x900 + i, 0x990 + i);
    setreg(r, kD9, kMadr, 0x100000u);
    setreg(r, kD9, kQwc, 4);
    setreg(r, kD9, kSadr, 0x3FE0u);
    setreg(r, kD9, kChcr, 0x100u);
    auto spr64 = [&](u32 off) {
        u64 v = 0;
        std::memcpy(&v, spr + off, 8);
        return v;
    };
    CHECK(spr64(0x3FE0) == 0x900);
    CHECK(spr64(0x3FF0) == 0x901);
    CHECK(spr64(0x0000) == 0x902);
    CHECK(spr64(0x0018) == 0x993);
    CHECK(reg(r, kD9, kSadr) == 0x0020u);
    // ch8 fromSPR (RW _rwDMAForceBufferSwap flush): SPR 0x0000 x3 -> RAM 0x200000.
    setreg(r, kD8, kMadr, 0x200000u);
    setreg(r, kD8, kQwc, 3);
    setreg(r, kD8, kSadr, 0x3FF0u);
    r.bus().write32(kDStat, 0x100u);
    setreg(r, kD8, kChcr, 0x100u);
    CHECK(r.mem.read<u64>(0x200000u) == 0x901);
    CHECK(r.mem.read<u64>(0x200010u) == 0x902);
    CHECK(r.mem.read<u64>(0x200028u) == 0x993);
    work(r.ctx, 64 + 6);
    CHECK((reg(r, kD8, kChcr) & 0x100u) == 0);  // RW spins on this STR (B-65)
    CHECK((r.bus().read32(kDStat) & 0x100u) != 0);
    // GIF from scratchpad (MADR bit 31, libdma convention at 0x4F9850).
    Sink s;
    r.bus().set_dma_handler(2, &s);
    setreg(r, kD2, kMadr, 0x80000000u | 0x3FF0u);
    setreg(r, kD2, kQwc, 2);
    setreg(r, kD2, kChcr, 0x101u);
    CHECK(s.lo == std::vector<u64>{0x901, 0x902});
    CHECK(s.offered == std::vector<std::size_t>{1, 1});  // split at the end of the scratchpad
    // fromSPR destination chain: cnt(2) -> 0x210000, end(1) -> 0x211000.
    qw(r, 0x70000100u, dmatag(kCnt, 2, 0x210000u));
    qw(r, 0x70000110u, 0xD1);
    qw(r, 0x70000120u, 0xD2);
    qw(r, 0x70000130u, dmatag(kEnd, 1, 0x211000u));
    qw(r, 0x70000140u, 0xD3);
    setreg(r, kD8, kSadr, 0x100u);
    setreg(r, kD8, kQwc, 0);
    setreg(r, kD8, kChcr, 0x104u);
    CHECK(r.mem.read<u64>(0x210000u) == 0xD1);
    CHECK(r.mem.read<u64>(0x210010u) == 0xD2);
    CHECK(r.mem.read<u64>(0x211000u) == 0xD3);
    CHECK(reg(r, kD8, kSadr) == 0x150u);
    // D_ENABLEW.CPND holds every start until released; D_ENABLER reads it back.
    work(r.ctx, 1000);  // let ch9's first transfer complete
    CHECK((reg(r, kD9, kChcr) & 0x100u) == 0);
    r.bus().write32(kDEnableW, 0x10000u);
    CHECK(r.bus().read32(kDEnableR) == 0x10000u);
    setreg(r, kD9, kMadr, 0x100000u);
    setreg(r, kD9, kQwc, 1);
    setreg(r, kD9, kSadr, 0x1000u);
    setreg(r, kD9, kChcr, 0x100u);
    CHECK(spr64(0x1000) == 0);
    r.bus().write32(kDEnableW, 0x1201u);
    CHECK(spr64(0x1000) == 0x900);
}

TEST_CASE("DMAC traps: no data path, interleave mode, MFIFO/stall control") {
    for (int which = 0; which < 3; ++which) {
        Rig r;
        static int s_which;
        s_which = which;
        const RunResult res = r.k->run([](EEContext&) {
            Rig& g = *g_rig;
            if (s_which == 2) g.bus().write32(kDCtrl, 1u | (2u << 2));  // MFD = VIF1
            else g.bus().write32(kDCtrl, 1u);
            if (s_which == 0) {
                setreg(g, kD0, kChcr, 0x101u);  // VIF0: nobody installed a data path
            } else {
                setreg(g, kD8, kQwc, 1);
                setreg(g, kD8, kChcr, 0x108u);  // interleave
            }
            CHECK(false);
        });
        CHECK(res.status == RunStatus::Fatal);
        REQUIRE(r.fatals.size() == 1);
        const char* expect[] = {"no data path installed", "interleave mode", "MFIFO/stall control"};
        CHECK_MESSAGE(r.fatals[0].find(expect[which]) != std::string::npos, r.fatals[0]);
    }
}

TEST_CASE("DMAC completion -> D_STAT -> DMAC handler chain called with the channel (RW _rwDMAHandler shape)") {
    static std::vector<std::pair<u32, u64>> s_calls;
    s_calls.clear();
    register_fn(0x00302000u, [](EEContext& c) {
        s_calls.emplace_back(c.gpr[GPR_A0].u32[0], c.cycles);
        set_reg(c, GPR_V0, 0);
    });
    static Sink s_sink;
    s_sink = Sink{};
    Rig r;
    r.bus().set_dma_handler(1, &s_sink);
    r.k->run([](EEContext& c) {
        c.cop0[12] |= 1u << 16;
        sys(c, kAddDmacHandler, 1, 0x00302000u, 0, 0);
        sys(c, kEnableDmac, 1);
        Rig& g = *g_rig;
        g.bus().write32(kDCtrl, 1u);
        setreg(g, kD1, kMadr, 0x100000u);
        setreg(g, kD1, kQwc, 8);
        const u64 t0 = c.cycles;
        setreg(g, kD1, kChcr, 0x101u);
        while (s_calls.empty()) work(c, 4);
        CHECK(s_calls[0].first == 1u);
        CHECK(s_calls[0].second >= t0 + 64 + 16);
        CHECK((reg(g, kD1, kChcr) & 0x100u) == 0);
    });
    CHECK(r.fatals.empty());
    CHECK(s_calls.size() == 1);
}

// The re-arm window (runtime/ipu/README.md open question 4; `_slice0 0x4FC3A8` → `_decMB0` →
// `receiveDataFromIPU 0x4FE988`): the game polls D3_QWC == 0 and re-arms the channel at once, while the
// kernel's completion event for the finished transfer is still `64 + 2·qwc` cycles away. The STR write must
// complete the old transfer (CIS, handler chain at the next check point) and start the new one.
TEST_CASE("DMAC re-arm window: STR written after the data phase, before the completion event, starts the next transfer") {
    Rig r;
    Sink s;
    r.bus().set_dma_handler(3, &s);  // any normal-mode channel; ch3 is the one the game re-arms this way
    constexpr u32 kD3 = 0x1000B000u;
    r.bus().write32(kDCtrl, 1u);
    for (u32 i = 0; i < 6; ++i) qw(r, 0x100000u + 16 * i, 0xA0 + i);
    for (u32 i = 0; i < 3; ++i) qw(r, 0x100100u + 16 * i, 0xB0 + i);
    // Transfer A: 6 qwords; its data phase ends inside the CHCR write.
    setreg(r, kD3, kMadr, 0x100000u);
    setreg(r, kD3, kQwc, 6);
    setreg(r, kD3, kChcr, 0x100u);  // STR, to memory (fromIPU)
    REQUIRE(s.lo.size() == 6);
    CHECK(reg(r, kD3, kQwc) == 0);                // what the game polls
    CHECK((reg(r, kD3, kChcr) & 0x100u) != 0);    // completion pending: 64 + 12 cycles away
    CHECK((r.bus().read32(kDStat) & 8u) == 0);
    work(r.ctx, 20);                               // well inside the window
    CHECK((reg(r, kD3, kChcr) & 0x100u) != 0);
    // Transfer B re-armed inside the window.
    setreg(r, kD3, kMadr, 0x100100u);
    setreg(r, kD3, kQwc, 3);
    setreg(r, kD3, kChcr, 0x100u);
    REQUIRE(s.lo.size() == 9);  // B's data went out: it was not swallowed as a write to a running channel
    CHECK(s.lo == std::vector<u64>{0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xB0, 0xB1, 0xB2});
    CHECK(s.offered == std::vector<std::size_t>{6, 3});
    CHECK((r.bus().read32(kDStat) & 8u) != 0);    // A completed at the write
    CHECK((reg(r, kD3, kChcr) & 0x100u) != 0);    // B running / pending its own completion
    CHECK(reg(r, kD3, kQwc) == 0);
    CHECK(reg(r, kD3, kMadr) == 0x100130u);
    r.bus().write32(kDStat, 8u);                   // ack A
    work(r.ctx, 64 + 6 - 1);
    CHECK((reg(r, kD3, kChcr) & 0x100u) != 0);
    CHECK((r.bus().read32(kDStat) & 8u) == 0);
    work(r.ctx, 1);                                // B's event: 64 + 3·2 after its data
    CHECK((reg(r, kD3, kChcr) & 0x100u) == 0);
    CHECK((r.bus().read32(kDStat) & 8u) != 0);
    // A CHCR write without STR inside the window completes the pending transfer instead of cancelling it.
    r.bus().write32(kDStat, 8u);
    setreg(r, kD3, kMadr, 0x100000u);
    setreg(r, kD3, kQwc, 1);
    setreg(r, kD3, kChcr, 0x100u);
    work(r.ctx, 10);
    setreg(r, kD3, kChcr, 0x000u);
    CHECK((r.bus().read32(kDStat) & 8u) != 0);
    CHECK((reg(r, kD3, kChcr) & 0x100u) == 0);
    work(r.ctx, 10'000);
    CHECK(s.lo.size() == 10);
    CHECK(r.k->unhandled_accesses() == 0);
}

TEST_CASE("DMAC re-arm window: both completions reach the DMAC handler chain, in order") {
    static std::vector<std::pair<u32, u64>> s_calls;
    static std::vector<std::size_t> s_seen;  // sink qwords already delivered at each handler call
    s_calls.clear();
    s_seen.clear();
    static Sink s_sink;
    s_sink = Sink{};
    register_fn(0x00302100u, [](EEContext& c) {
        s_calls.emplace_back(c.gpr[GPR_A0].u32[0], c.cycles);
        s_seen.push_back(s_sink.lo.size());
        set_reg(c, GPR_V0, 0);
    });
    Rig r;
    r.bus().set_dma_handler(3, &s_sink);
    r.k->run([](EEContext& c) {
        c.cop0[12] |= 1u << 16;
        sys(c, kAddDmacHandler, 3, 0x00302100u, 0, 0);
        sys(c, kEnableDmac, 3);
        Rig& g = *g_rig;
        constexpr u32 kD3 = 0x1000B000u;
        g.bus().write32(kDCtrl, 1u);
        setreg(g, kD3, kMadr, 0x100000u);
        setreg(g, kD3, kQwc, 48);  // BDEC's 48 qwords (receiveDataFromIPU)
        setreg(g, kD3, kChcr, 0x100u);
        work(c, 8);
        CHECK(s_calls.empty());             // A's event is 64 + 96 cycles away
        CHECK(reg(g, kD3, kQwc) == 0);
        const u64 t_b = c.cycles;
        setreg(g, kD3, kMadr, 0x101000u);    // re-arm for the next macroblock
        setreg(g, kD3, kQwc, 48);
        setreg(g, kD3, kChcr, 0x100u);
        work(c, 1);                          // next check point: A's completion is delivered
        CHECK(s_calls.size() == 1);
        if (s_calls.size() != 1) return;     // (no REQUIRE on a guest fiber: the exception cannot unwind it)
        CHECK(s_calls[0].first == 3u);
        CHECK(s_calls[0].second < t_b + 64 + 96);
        while (s_calls.size() < 2) work(c, 4);
        CHECK(s_calls[1].first == 3u);
        CHECK(s_calls[1].second >= t_b + 64 + 96);
        CHECK((reg(g, kD3, kChcr) & 0x100u) == 0);
    });
    CHECK(r.fatals.empty());
    CHECK(s_calls.size() == 2);
    CHECK(s_sink.lo.size() == 96);
    CHECK(s_seen == std::vector<std::size_t>{96, 96});  // B's data was out before A's handler ran (sync engine)
}
