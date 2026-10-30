// VIF1: VIFcodes, UNPACK into VU1 data memory (the stock material packet of contract §6.2 and every format the
// census lists), write cycles / masks / modes, double buffering, MPG + MSCAL/MSCNT running a synthetic micro
// program whose XGKICK draws through PATH1, DIRECT into PATH2, MSKPATH3 with a stalled DMAC channel 2, the
// interrupt bit, traps, registers, VIF0, and local -> host reads.
#include "gs_test_util.h"

#include "../vu1/vu1_test_util.h"

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;
namespace vt = p3fes::vu1::test;

namespace {

struct Words {
    std::vector<u32> w;
    Words& c(u32 v) {
        w.push_back(v);
        return *this;
    }
    Words& d(std::initializer_list<u32> l) {
        w.insert(w.end(), l.begin(), l.end());
        return *this;
    }
    Words& q(const u128& x) {
        w.insert(w.end(), x.u32, x.u32 + 4);
        return *this;
    }
    Words& pad(u32 fill = 0) {
        while (w.size() % 4) w.push_back(fill);
        return *this;
    }
    std::vector<u128> qw() const {
        std::vector<u32> x = w;
        while (x.size() % 4) x.push_back(0);
        std::vector<u128> out(x.size() / 4);
        std::memcpy(out.data(), x.data(), x.size() * 4);
        return out;
    }
};

u32 unpack(u32 cmd_low5, u32 num, u32 addr, bool usn = false, bool flg = false) {
    return (static_cast<u32>(0x60u | cmd_low5) << 24) | ((num & 0xFFu) << 16) | (flg ? 0x8000u : 0u) |
           (usn ? 0x4000u : 0u) | (addr & 0x3FFu);
}
constexpr u32 STCYCL(u32 cl, u32 wl) { return 0x01000000u | (wl << 8) | cl; }
constexpr u32 OFFSET(u32 v) { return 0x02000000u | v; }
constexpr u32 BASE(u32 v) { return 0x03000000u | v; }
constexpr u32 ITOP(u32 v) { return 0x04000000u | v; }
constexpr u32 STMOD(u32 v) { return 0x05000000u | v; }
constexpr u32 MSKPATH3(bool on) { return 0x06000000u | (on ? 0x8000u : 0u); }
constexpr u32 MARK(u32 v) { return 0x07000000u | v; }
constexpr u32 MSCAL(u32 v) { return 0x14000000u | v; }
constexpr u32 MSCNT() { return 0x17000000u; }
constexpr u32 STMASK() { return 0x20000000u; }
constexpr u32 STROW() { return 0x30000000u; }
constexpr u32 STCOL() { return 0x31000000u; }
constexpr u32 MPG(u32 num, u32 addr) { return 0x4A000000u | ((num & 0xFFu) << 16) | addr; }
constexpr u32 DIRECT(u32 qwc) { return 0x50000000u | qwc; }
constexpr u32 FLUSHA() { return 0x13000000u; }

std::size_t feed(Fixture& f, const Words& w) {
    std::vector<u128> q = w.qw();
    return f.bus.dma[1]->transfer(q.data(), q.size(), 0);
}

u32 vu_word(Fixture& f, u32 qaddr, u32 lane) { return vt::data_word(f.gs->vu1().state(), qaddr, lane); }

// Program image as 32-bit words for MPG (lower word first per pair).
std::vector<u32> program(std::initializer_list<vt::Pair> pairs) {
    std::vector<u8> img = vt::image(pairs);
    std::vector<u32> w(img.size() / 4);
    std::memcpy(w.data(), img.data(), img.size());
    return w;
}

} // namespace

TEST_CASE("UNPACK: the stock material packet lands at 0x3FC..0x3FF (game: contract §6.2 V-01/V-02, 14 §3)") {
    Fixture f;
    Words w;
    // 0x6C0103FC01000404 = STCYCL(4,4) + UNPACK V4-32 x1 -> 0x3FC; 0x6C0303FD01000404 = STCYCL + UNPACK x3 -> 0x3FD.
    w.c(0x01000404).c(0x6C0103FC).d({0x3F800000, 0x3F000000, 0x3E800000, 0x3F800000});
    w.c(0x01000404).c(0x6C0303FD);
    for (u32 i = 0; i < 12; ++i) w.c(0x1000 + i);
    CHECK(w.w.size() == 20u);
    CHECK(feed(f, w) == 5u);
    CHECK(vu_word(f, 0x3FC, 0) == 0x3F800000u);
    CHECK(vu_word(f, 0x3FC, 1) == 0x3F000000u);
    CHECK(vu_word(f, 0x3FC, 3) == 0x3F800000u);
    for (u32 i = 0; i < 12; ++i) CHECK(vu_word(f, 0x3FD + i / 4, i % 4) == 0x1000 + i);
    CHECK(f.gs->vif1().stats().unpack_qwords == 4u);
    CHECK(f.bus.read32(0x10003C40) == 0x0404u); // CYCLE
}

TEST_CASE("UNPACK: every format, sign/zero extension, V4-5 (hand: EE User's Manual; upstream behaviour for indeterminate lanes)") {
    Fixture f;
    Words w;
    w.c(STCYCL(4, 4));
    w.c(unpack(0x0, 1, 0x00)).c(0xAABBCCDD);                                 // S-32
    w.c(unpack(0x1, 2, 0x01)).c(0x7FFFFFFE);                                 // S-16 x2 signed: -2, 0x7FFF
    w.c(unpack(0x1, 1, 0x03, true)).c(0x0000FFFE);                           // S-16 unsigned
    w.c(unpack(0x2, 4, 0x04)).c(0x7F0180FFu);                                // S-8 x4: -1, -128, 1, 127
    w.c(unpack(0x4, 1, 0x08)).d({1, 2});                                     // V2-32 -> (x, y, x, y)
    w.c(unpack(0x5, 1, 0x09)).c(0x8000FFFFu);                                // V2-16: -1, -32768
    w.c(unpack(0x6, 1, 0x0A, true)).c(0x0000F00Fu);                          // V2-8 unsigned: 15, 240
    w.c(unpack(0x8, 1, 0x0B)).d({3, 4, 5});                                  // V3-32 -> (x, y, z, 0)
    w.c(unpack(0x9, 1, 0x0C)).d({0x00020001, 0x00000003});                   // V3-16
    w.c(unpack(0xA, 1, 0x0D)).c(0x00FF0201u);                                // V3-8: 1, 2, -1
    w.c(unpack(0xC, 1, 0x0E)).d({6, 7, 8, 9});                               // V4-32
    w.c(unpack(0xD, 1, 0x0F)).d({0x0002FFFF, 0x80000003});                   // V4-16
    w.c(unpack(0xE, 1, 0x10, true)).c(0x04030201u);                          // V4-8 unsigned
    w.c(unpack(0xF, 1, 0x11)).c(0x8000u | (31u << 10) | (1u << 5) | 2u);     // V4-5
    feed(f, w);
    const auto lanes = [&](u32 a) {
        return std::array<u32, 4>{vu_word(f, a, 0), vu_word(f, a, 1), vu_word(f, a, 2), vu_word(f, a, 3)};
    };
    CHECK(lanes(0x00) == std::array<u32, 4>{0xAABBCCDD, 0xAABBCCDD, 0xAABBCCDD, 0xAABBCCDD});
    CHECK(lanes(0x01) == std::array<u32, 4>{0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE});
    CHECK(vu_word(f, 0x02, 0) == 0x7FFFu);
    CHECK(vu_word(f, 0x03, 2) == 0xFFFEu);
    CHECK(vu_word(f, 0x04, 0) == 0xFFFFFFFFu);
    CHECK(vu_word(f, 0x05, 0) == 0xFFFFFF80u);
    CHECK(vu_word(f, 0x06, 0) == 1u);
    CHECK(vu_word(f, 0x07, 0) == 127u);
    CHECK(lanes(0x08) == std::array<u32, 4>{1, 2, 1, 2});
    CHECK(lanes(0x09) == std::array<u32, 4>{0xFFFFFFFF, 0xFFFF8000, 0xFFFFFFFF, 0xFFFF8000});
    CHECK(lanes(0x0A) == std::array<u32, 4>{15, 240, 15, 240});
    CHECK(lanes(0x0B) == std::array<u32, 4>{3, 4, 5, 0});
    CHECK(lanes(0x0C) == std::array<u32, 4>{1, 2, 3, 0});
    CHECK(lanes(0x0D) == std::array<u32, 4>{1, 2, 0xFFFFFFFF, 0});
    CHECK(lanes(0x0E) == std::array<u32, 4>{6, 7, 8, 9});
    CHECK(lanes(0x0F) == std::array<u32, 4>{0xFFFFFFFF, 2, 3, 0xFFFF8000});
    CHECK(lanes(0x10) == std::array<u32, 4>{1, 2, 3, 4});
    CHECK(lanes(0x11) == std::array<u32, 4>{16, 8, 248, 128});
}

TEST_CASE("UNPACK: skipping (CL > WL) and filling (WL > CL) write cycles (hand: EE User's Manual; upstream fill = row)") {
    Fixture f;
    Words w;
    w.c(STROW()).d({0xA0, 0xA1, 0xA2, 0xA3});
    w.c(STCYCL(2, 1)).c(unpack(0xC, 3, 0x40)).d({1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3});
    w.c(STCYCL(1, 2)).c(unpack(0xC, 4, 0x60)).d({4, 4, 4, 4, 5, 5, 5, 5});
    feed(f, w);
    CHECK(vu_word(f, 0x40, 0) == 1u);
    CHECK(vu_word(f, 0x41, 0) == 0u);
    CHECK(vu_word(f, 0x42, 0) == 2u);
    CHECK(vu_word(f, 0x44, 0) == 3u);
    CHECK(vu_word(f, 0x60, 0) == 4u);
    CHECK(vu_word(f, 0x61, 1) == 0xA1u);
    CHECK(vu_word(f, 0x62, 0) == 5u);
    CHECK(vu_word(f, 0x63, 3) == 0xA3u);
}

TEST_CASE("UNPACK: STMASK data/row/column/protect and STMOD offset/difference (hand: EE User's Manual)") {
    Fixture f;
    vt::set_qword(f.gs->vu1().state(), 0x80, 0, 0, 0, 0xDEAD);
    Words w;
    w.c(STCYCL(4, 4));
    w.c(STROW()).d({10, 20, 30, 40});
    w.c(STCOL()).d({100, 200, 300, 400});
    w.c(STMASK()).c(0x00u | (1u << 2) | (2u << 4) | (3u << 6)); // row 0: x data, y row, z col[0], w protect
    w.c(unpack(0x1C, 1, 0x80)).d({7, 8, 9, 11});                 // V4-32 with the mask bit (cmd 0x7C)
    feed(f, w);
    CHECK(vu_word(f, 0x80, 0) == 7u);
    CHECK(vu_word(f, 0x80, 1) == 20u);
    CHECK(vu_word(f, 0x80, 2) == 100u);
    CHECK(vu_word(f, 0x80, 3) == 0xDEADu);
    Words m;
    m.c(STMOD(1)).c(unpack(0xC, 1, 0x81)).d({1, 1, 1, 1});       // offset: + row
    m.c(STMOD(2)).c(unpack(0xC, 2, 0x82)).d({1, 2, 3, 4, 1, 2, 3, 4}); // difference: row accumulates
    m.c(STMOD(0));
    feed(f, m);
    CHECK(vu_word(f, 0x81, 0) == 11u);
    CHECK(vu_word(f, 0x82, 3) == 44u);
    CHECK(vu_word(f, 0x83, 3) == 48u);
    CHECK(f.bus.read32(0x10003D00) == 12u); // R0 after two difference additions: 10 + 1 + 1
    CHECK(f.bus.read32(0x10003D40) == 100u); // C0
    CHECK(f.bus.read32(0x10003C70) == 0xE4u); // MASK
}

TEST_CASE("double buffering: BASE/OFFSET/ITOP, TOP/ITOP/DBF/TOPS at MSCAL, UNPACK FLG uses TOPS (hand: EE User's Manual)") {
    Fixture f;
    const std::vector<u32> prog = program({{vt::UNOP | vt::E_BIT, vt::LNOP}, {vt::UNOP, vt::LNOP}});
    Words w;
    w.c(0).c(MPG(2, 0)).d({prog[0], prog[1], prog[2], prog[3]});
    w.c(BASE(0x100)).c(OFFSET(0x80)).c(ITOP(0x37));
    feed(f, w);
    Vif1& v = f.gs->vif1();
    CHECK(v.tops() == 0x100u);
    CHECK_FALSE(v.dbf());
    feed(f, Words{}.c(MSCAL(0)));
    CHECK(v.top() == 0x100u);
    CHECK(v.itop() == 0x37u);
    CHECK(v.dbf());
    CHECK(v.tops() == 0x180u);
    CHECK(f.gs->vu1().state().top == 0x100u);
    CHECK((f.bus.read32(0x10003C00) & (1u << 7)) != 0); // STAT.DBF
    feed(f, Words{}.c(unpack(0xC, 1, 0x5, false, true)).d({1, 2, 3, 4}));
    CHECK(vu_word(f, 0x185, 0) == 1u);
    feed(f, Words{}.c(MSCAL(0)));
    CHECK(v.top() == 0x180u);
    CHECK(v.tops() == 0x100u);
    CHECK_FALSE(v.dbf());
    CHECK(v.stats().vu_runs == 2u);
}

TEST_CASE("MPG + MSCAL: a synthetic micro program XGKICKs a GIF packet through PATH1 and draws (hand: VU/GS manuals)") {
    Fixture f;
    f.env();
    // xtop vi1 ; xgkick vi1 (with E) ; nop
    const std::vector<u32> prog = program({{vt::UNOP, vt::l_xtop(1)},
                                           {vt::UNOP | vt::E_BIT, vt::l_xgkick(1)},
                                           {vt::UNOP, vt::LNOP}});
    GifBuilder pkt;
    pkt.ad({{reg::PRIM, gs_prim(6)},
            {reg::RGBAQ, gs_rgbaq(1, 2, 3, 0x80)},
            {reg::XYZ2, gs_xyz(4 * 16, 4 * 16, 0)},
            {reg::XYZ2, gs_xyz(8 * 16, 8 * 16, 0)}});
    Words w;
    w.c(STCYCL(4, 4)).c(BASE(0x20)).c(OFFSET(0x100));
    w.c(MPG(3, 0)).d({prog[0], prog[1], prog[2], prog[3], prog[4], prog[5]});
    w.c(unpack(0xC, static_cast<u32>(pkt.qwords().size()), 0, false, true));
    for (const u128& q : pkt.qwords()) w.q(q);
    w.c(MSCAL(0));
    feed(f, w);
    CHECK(f.gs->vif1().stats().mpg_pairs == 3u);
    CHECK(f.gs->vif1().stats().vu_runs == 1u);
    CHECK(f.gs->vu1().stats().kicks == 1u);
    CHECK(f.gs->gif().stats().qwords[1] == 5u);
    CHECK(f.px(5, 5) == rgba(1, 2, 3, 0x80));
    CHECK(f.px(8, 8) == 0u);
    CHECK(f.gs->vif1().stats().traps == 0u);
}

TEST_CASE("MSCNT resumes after the E pair; a VU trap is reported as a VIF trap (hand: VU manual)") {
    Fixture f;
    std::vector<VifTrap> traps;
    f.gs->set_trap_handler([&](const VifTrap& t) { traps.push_back(t); });
    const std::vector<u32> prog = program({{vt::UNOP | vt::E_BIT, vt::l_iaddiu(2, 0, 5)},
                                           {vt::UNOP, vt::LNOP},
                                           {vt::UNOP | vt::E_BIT, vt::l_iaddiu(3, 0, 7)},
                                           {vt::UNOP, vt::LNOP},
                                           {vt::UNOP, vt::l_sqrt(1, vt::bx)}, // SQRT: defined, used by no program
                                           {vt::UNOP, vt::LNOP}});
    Words w;
    w.c(0).c(MPG(6, 0)); // MPG data starts on a 64-bit boundary: the code goes in an odd word
    for (u32 x : prog) w.c(x);
    w.c(MSCAL(0));
    feed(f, w);
    CHECK(f.gs->vu1().state().vi[2] == 5u);
    CHECK(f.gs->vu1().state().vi[3] == 0u);
    feed(f, Words{}.c(MSCNT()));
    CHECK(f.gs->vu1().state().vi[3] == 7u);
    CHECK(traps.empty());
    feed(f, Words{}.c(MSCAL(4)));
    REQUIRE(traps.size() == 1u);
    CHECK(traps[0].kind == VifTrapKind::VuTrap);
    CHECK(traps[0].vu.kind == vu1::TrapKind::UncensusedLower);
    CHECK(traps[0].code == MSCAL(4));
}

TEST_CASE("DIRECT: GIF data at the next qword boundary into PATH2; split across transfers (game: 14 §3 upload layout)") {
    Fixture f;
    f.env();
    GifBuilder pkt;
    pkt.ad({{reg::PRIM, gs_prim(6)},
            {reg::RGBAQ, gs_rgbaq(9, 8, 7, 0x80)},
            {reg::XYZ2, gs_xyz(0, 0, 0)},
            {reg::XYZ2, gs_xyz(2 * 16, 2 * 16, 0)}});
    // DIRECT in word 1: words 2 and 3 are padding the VIF skips.
    Words w;
    w.c(0).c(DIRECT(static_cast<u32>(pkt.qwords().size()))).c(0xFFFFFFFF).c(0xFFFFFFFF);
    for (const u128& q : pkt.qwords()) w.q(q);
    CHECK(feed(f, w) == 1u + pkt.qwords().size());
    CHECK(f.px(1, 1) == rgba(9, 8, 7, 0x80));
    CHECK(f.gs->vif1().stats().direct_qwords == pkt.qwords().size());
    // RW's texture-upload shape: a TTE tag qword (DMAtag half zeroed, NOP + DIRECT in the upper half), then the
    // data in a separate REF transfer.
    GifBuilder pkt2;
    pkt2.ad({{reg::PRIM, gs_prim(6)},
             {reg::RGBAQ, gs_rgbaq(4, 5, 6, 0x80)},
             {reg::XYZ2, gs_xyz(4 * 16, 0, 0)},
             {reg::XYZ2, gs_xyz(6 * 16, 2 * 16, 0)}});
    Words tag;
    tag.c(0).c(0).c(0).c(DIRECT(static_cast<u32>(pkt2.qwords().size())));
    CHECK(feed(f, tag) == 1u);
    CHECK((f.bus.read32(0x10003C00) & 3u) != 0u); // VPS: waiting for data
    std::vector<u128> data = pkt2.qwords();
    CHECK(f.bus.dma[1]->transfer(data.data(), 2, 0) == 2u);
    CHECK(f.bus.dma[1]->transfer(data.data() + 2, data.size() - 2, 0) == data.size() - 2);
    CHECK(f.px(5, 1) == rgba(4, 5, 6, 0x80));
    CHECK((f.bus.read32(0x10003C00) & 0x1F000003u) == 0u); // idle as sceGsSyncPath polls it
    // An UNPACK whose data is split across two transfers.
    Words a;
    a.c(STCYCL(4, 4)).c(unpack(0xC, 2, 0x200)).d({1, 2});
    CHECK(feed(f, a) == 1u);
    Words b;
    b.d({3, 4, 5, 6, 7, 8});
    feed(f, b);
    CHECK(vu_word(f, 0x200, 2) == 3u);
    CHECK(vu_word(f, 0x201, 3) == 8u);
}

TEST_CASE("MSKPATH3 through the VIF1 FIFO stalls DMAC channel 2 until PATH2 clears it (game: 10 §3.1 queue type 0x21)") {
    Fixture f;
    f.env();
    int ready = 0;
    f.gs->set_path3_ready_callback([&] { ++ready; });
    u128 code{};
    code.u32[0] = MSKPATH3(true);
    f.bus.write128(0x10005000, code);
    CHECK((f.bus.read32(0x10003020) & 2u) != 0); // GIF_STAT.M3P
    GifBuilder p3;
    p3.ad({{reg::PRIM, gs_prim(6)},
           {reg::RGBAQ, gs_rgbaq(0x11, 0, 0, 0x80)},
           {reg::XYZ2, gs_xyz(0, 0, 0)},
           {reg::XYZ2, gs_xyz(16, 16, 0)}});
    std::vector<u128> d2 = p3.qwords();
    CHECK(f.bus.dma[2]->transfer(d2.data(), d2.size(), 0) == 0u);
    CHECK((f.bus.read32(0x10003020) & 0x40u) != 0); // P3Q
    // VIF1 chain: an IMAGE upload through DIRECT, then MSKPATH3 off.
    std::vector<u32> pixels(16, 0x12345678u);
    GifBuilder up;
    up.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0x2000, 1, 0)}, {reg::TRXPOS, 0}, {reg::TRXREG, gs_trxreg(4, 4)}, {reg::TRXDIR, 0}});
    up.image(pixels.data(), pixels.size() * 4);
    Words w;
    w.c(0).c(0).c(0).c(DIRECT(static_cast<u32>(up.qwords().size())));
    for (const u128& q : up.qwords()) w.q(q);
    w.c(MSKPATH3(false));
    feed(f, w);
    CHECK(ready == 1);
    CHECK(f.mem().read(0, 0x2000, 1, 3, 3) == 0x12345678u);
    CHECK(f.bus.dma[2]->transfer(d2.data(), d2.size(), 0) == d2.size());
    CHECK(R(f.px(0, 0)) == 0x11u);
}

TEST_CASE("interrupt bit: stall after the VIFcode, INTC VIF1, FBRST.STC resumes (hand: EE User's Manual)") {
    Fixture f;
    Words w;
    w.c(0x80000000u).c(STCYCL(1, 1)).c(MARK(0x1234)).c(0);
    CHECK(feed(f, w) == 1u); // the qword is taken; its last three words wait in the VIF
    CHECK(f.bus.count_intc(5) == 1u);
    const u32 stat = f.bus.read32(0x10003C00);
    CHECK((stat & (1u << 10)) != 0); // VIS
    CHECK((stat & (1u << 11)) != 0); // INT
    CHECK(f.bus.read32(0x10003C40) == 0u);
    std::vector<u128> more = Words{}.c(STCYCL(2, 2)).qw();
    CHECK(f.bus.dma[1]->transfer(more.data(), more.size(), 0) == 0u);
    f.bus.write32(0x10003C10, 8); // FBRST.STC
    CHECK(f.bus.read32(0x10003C40) == 0x0101u);
    CHECK(f.bus.read32(0x10003C30) == 0x1234u);
    CHECK((f.bus.read32(0x10003C00) & (1u << 6)) != 0); // STAT.MRK
    f.bus.write32(0x10003C30, 0x55); // an EE write to MARK clears STAT.MRK
    CHECK((f.bus.read32(0x10003C00) & (1u << 6)) == 0);
    CHECK(f.bus.dma[1]->transfer(more.data(), more.size(), 0) == 1u);
    CHECK(f.bus.read32(0x10003C40) == 0x0202u);
    // ERR.MII masks the interrupt bit.
    f.bus.write32(0x10003C20, 1);
    CHECK(feed(f, Words{}.c(0x80000000u).c(0).c(0).c(0)) == 1u);
    CHECK(f.bus.count_intc(5) == 1u);
}

TEST_CASE("traps: undefined VIFcode (ER1), VIF0 data; VIF0 registers accept the game's resets (game: 10 §2.2, §2.14)") {
    Fixture f;
    std::vector<VifTrap> traps;
    f.gs->set_trap_handler([&](const VifTrap& t) { traps.push_back(t); });
    feed(f, Words{}.c(0x08000000u).c(0).c(0).c(0));
    REQUIRE(traps.size() == 1u);
    CHECK(traps[0].kind == VifTrapKind::InvalidCode);
    CHECK((f.bus.read32(0x10003C00) & (1u << 13)) != 0);
    f.bus.write32(0x10003C10, 8);
    CHECK((f.bus.read32(0x10003C00) & (1u << 13)) == 0);
    // VIF0: FBRST/ERR accepted (VIF1_ERR = VIF0_ERR | 2 reads it back), data traps.
    f.bus.write32(0x10003810, 1);
    f.bus.write32(0x10003820, f.bus.read32(0x10003820) | 2);
    CHECK(f.bus.read32(0x10003820) == 2u);
    CHECK(f.bus.read32(0x10003800) == 0u);
    f.bus.write128(0x10004000, u128{});
    std::vector<u128> d(2);
    CHECK(f.bus.dma[0]->transfer(d.data(), d.size(), 0) == 2u);
    REQUIRE(traps.size() == 3u);
    CHECK(traps[1].kind == VifTrapKind::Vif0Used);
    // VIF1 FBRST.RST resets the VIF registers.
    feed(f, Words{}.c(STCYCL(3, 3)));
    f.bus.write32(0x10003C10, 1);
    CHECK(f.bus.read32(0x10003C40) == 0u);
}

TEST_CASE("FLUSHA waits for the end of the PATH3 transfer: DMAC channel 2 still running, or PATH3 data stalled (hand: EE "
          "User's Manual VIFcode FLUSHA; the title-screen ordering bug)") {
    Fixture f;
    bool dma2_running = true;
    f.gs->gif().set_path3_dma_busy([&] { return dma2_running; });
    // Channel 2 is mid-transfer (STR set) but the GIF is between PATH3 packets: FLUSHA must still wait, so the
    // DIRECT draw that follows cannot overtake the texture upload the channel is carrying.
    CHECK(feed(f, Words{}.c(FLUSHA()).c(STCYCL(2, 2))) == 1u);
    CHECK(f.bus.read32(0x10003C40) == 0u);               // STCYCL not executed
    CHECK((f.bus.read32(0x10003C00) & (1u << 3)) != 0);  // VGW
    CHECK(f.gs->vif1().stalled());
    f.gs->vif1().resume();                               // nothing changed: still waiting
    CHECK(f.bus.read32(0x10003C40) == 0u);
    dma2_running = false;                                // the DMAC completed the channel (STR cleared)
    f.gs->vif1().resume();
    CHECK(f.bus.read32(0x10003C40) == 0x0202u);          // FLUSHA passed, STCYCL executed
    CHECK(!f.gs->vif1().stalled());

    // PATH3 data stalled in the GIF counts as a pending transfer too: masked by MSKPATH3, the channel-2 data is
    // refused and stays queued; after MSKPATH3 off the DMAC re-offers it later (here: the test), and a FLUSHA
    // issued in between waits for that re-offer. (A FLUSHA *while* PATH3 is masked by the same VIF would wait
    // forever on hardware as well; games unmask first.)
    GifBuilder p3;
    p3.tag(1, true, 0, 1, 0xE);
    p3.raw(5, reg::TEXA);
    feed(f, Words{}.c(0x06008000u));  // MSKPATH3 on
    CHECK(f.gs->gif().path3(p3.qwords()) == 0u);
    CHECK(!f.gs->gif().path3_pending());  // masked: a FLUSHA now must not wait (it could never finish)
    feed(f, Words{}.c(0x06000000u));  // MSKPATH3 off -> path3-ready fires; the data is still with the DMAC
    CHECK(f.gs->gif().path3_pending());   // unmasked and stalled: pending until the DMAC re-offers it
    CHECK(feed(f, Words{}.c(FLUSHA()).c(STCYCL(3, 3))) == 1u);
    CHECK(f.bus.read32(0x10003C40) == 0x0202u);          // waits for the stalled PATH3 data
    CHECK(f.gs->gif().path3(p3.qwords()) == p3.qwords().size());  // the DMAC's re-offer
    CHECK(!f.gs->gif().path3_pending());
    f.gs->vif1().resume();
    CHECK(f.bus.read32(0x10003C40) == 0x0303u);
}

TEST_CASE("PATH3 unmask window: one GS packet (through EOP) goes through, the rest waits for the DMAC retry (hand: RW "
          "texture sync packet; the title-screen texture overwrite)") {
    Fixture f;
    // Two EOP packets as RenderWare's channel-2 chain carries them: texture (setup + IMAGE), then the next one.
    GifBuilder two;
    two.tag(1, true, 0, 1, 0xE);
    two.raw(5, reg::TEXA);
    two.tag(1, true, 0, 1, 0xE);
    two.raw(7, reg::TEXA);
    const std::size_t n = two.qwords().size();  // 4 qwords
    f.gs->gif().begin_path3_window();
    CHECK(f.gs->gif().path3(two.qwords()) == n / 2);  // the first packet only
    CHECK(f.gs->core().regs().texa == 5u);
    CHECK((f.gs->gif().stat() & (1u << 6)) != 0);  // P3Q: data waiting
    CHECK(f.gs->gif().path3_pending());
    f.gs->gif().end_path3_window();
    CHECK(f.gs->gif().path3(std::span<const u128>(two.qwords().data() + n / 2, n / 2)) == n / 2);  // the retry
    CHECK(f.gs->core().regs().texa == 7u);
    CHECK(f.gs->gif().stats().path3_window_stops == 1u);
    // Without a window every packet goes through at once.
    CHECK(f.gs->gif().path3(two.qwords()) == n);
}

TEST_CASE("FLUSHA waits while PATH3 owns the GIF; FLUSHE/FLUSH do not (model)") {
    Fixture f;
    GifBuilder p3;
    p3.tag(1, true, 0, 1, 0xE);
    p3.raw(5, reg::TEXA);
    f.gs->gif().path3(std::span<const u128>(p3.qwords().data(), 1));
    CHECK(feed(f, Words{}.c(0x10000000u).c(0x11000000u).c(FLUSHA()).c(STCYCL(2, 2))) == 1u);
    CHECK(f.bus.read32(0x10003C40) == 0u); // STCYCL waits behind FLUSHA
    CHECK((f.bus.read32(0x10003C00) & (1u << 3)) != 0); // VGW
    f.gs->gif().path3(std::span<const u128>(p3.qwords().data() + 1, 1));
    f.gs->vif1().resume();
    CHECK(f.bus.read32(0x10003C40) == 0x0202u);
}

TEST_CASE("local -> host: BUSDIR = 1 turns VIF1 FIFO reads and channel 1 into GS image reads (game: 14 §4 sceGsExecStoreImage)") {
    Fixture f;
    for (u32 i = 0; i < 8; ++i) f.mem().write(0x00, 0x2000, 1, i, 0, 0xA0000000u + i);
    GifBuilder g;
    g.ad({{reg::BITBLTBUF, gs_bitbltbuf(0x2000, 1, 0x00, 0, 0, 0)}, {reg::TRXPOS, 0}, {reg::TRXREG, gs_trxreg(8, 1)}, {reg::TRXDIR, 1}});
    f.send(g);
    f.bus.write64(0x12001040, 1);
    const u128 q0 = f.bus.read128(0x10005000);
    CHECK(q0.u32[0] == 0xA0000000u);
    CHECK(q0.u32[3] == 0xA0000003u);
    std::vector<u128> out(1);
    CHECK(f.bus.dma[1]->transfer(out.data(), 1, 0) == 1u);
    CHECK(out[0].u32[0] == 0xA0000004u);
    CHECK(out[0].u32[3] == 0xA0000007u);
    CHECK((f.bus.read32(0x10003C00) & (1u << 23)) != 0); // FDR
    CHECK_FALSE(f.core().local_to_host_active());
}
