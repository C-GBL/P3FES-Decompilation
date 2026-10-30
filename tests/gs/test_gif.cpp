// GIF: tag decoding, PACKED / REGLIST / IMAGE data, A+D, PRE, and the PATH1/2/3 arbitration model; GIF registers.
#include "gs_test_util.h"

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;

TEST_CASE("giftag: decode of the game's tags (game: docs/ANALYSIS/10 §2.1, 14 §3; hand: GS User's Manual)") {
    // skyInitialClear: NLOOP 1, EOP, PACKED, NREG 12, REGS all A+D.
    const GifTag a = GifTag::decode(make_giftag(1, true, 0, 12, 0xEEEEEEEEEEEEull));
    CHECK(a.nloop == 1);
    CHECK(a.eop);
    CHECK(a.flg == 0);
    CHECK(a.nreg == 12);
    CHECK(a.reg(11) == 0xE);
    CHECK(a.data_qwords() == 12);
    // _rwSkySetRenderState's literal 0x1000000000008001: NLOOP 1, EOP, NREG 1, PACKED.
    const GifTag b = GifTag::decode(make_qword(0x1000000000008001ull, 0xE));
    CHECK(b.nloop == 1);
    CHECK(b.eop);
    CHECK(b.nreg == 1);
    CHECK(b.flg == 0);
    // Texture upload IMAGE tag 0x0800000000000000 | nloop.
    const GifTag c = GifTag::decode(make_qword(0x0800000000000000ull | 300u, 0));
    CHECK(c.flg == 2);
    CHECK(c.nloop == 300);
    CHECK(c.data_qwords() == 300);
    // NREG 0 means 16; PRE/PRIM fields; REGLIST data size rounds up.
    const GifTag d = GifTag::decode(make_giftag(3, false, 1, 0, 0, true, 0x15));
    CHECK(d.nreg == 16);
    CHECK(d.pre);
    CHECK(d.prim == 0x15);
    CHECK(d.data_qwords() == 24);
    CHECK(GifTag::decode(make_giftag(3, false, 1, 3, 0)).data_qwords() == 5);
}

TEST_CASE("PACKED: register formats (hand: GS User's Manual)") {
    Fixture f;
    GifBuilder g;
    // ST then RGBAQ: RGBAQ takes the Q that ST left in the internal register; UV, FOG, TEX0, CLAMP; XYZF2 with ADC.
    g.tag(1, true, 0, 8, 0x0A98F312ull);
    // descriptor order (low nibble first): 2 ST, 1 RGBAQ, 3 UV, F NOP, 8 CLAMP_1, 9 CLAMP_2, A FOG, 0 PRIM
    g.raw(0x400000003F800000ull /* S=1.0, T=2.0 */, 0x40400000ull /* Q=3.0 */);
    g.raw(0x0000002200000011ull, 0x0000004400000033ull); // R=0x11 G=0x22 B=0x33 A=0x44
    g.raw(0x0000123400002345ull, 0);                     // U=0x2345 V=0x1234 (14 bits)
    g.raw(0xFFFFFFFFFFFFFFFFull, 0xFFFFFFFFFFFFFFFFull); // NOP
    g.raw(0x123456789ull, 0);
    g.raw(0x987654321ull, 0);
    g.raw(0, 0x00000AB000000000ull);                     // FOG F = 0xAB at bits 100..107
    g.raw(0x6, 0);                                       // PRIM sprite
    f.send(g);
    const GsRegs& r = f.core().regs();
    CHECK(r.st == 0x400000003F800000ull);
    CHECK(r.rgbaq == ((0x40400000ull << 32) | 0x44332211ull));
    CHECK(r.uv == ((0x1234ull << 16) | 0x2345ull));
    CHECK(r.ctx[0].clamp == 0x123456789ull);
    CHECK(r.ctx[1].clamp == 0x987654321ull);
    CHECK(r.fog == (0xABull << 56));
    CHECK(r.prim == 6);
    // A new tag resets the internal Q to 1.0: a PACKED RGBAQ right after it carries Q = 1.0.
    GifBuilder h;
    h.tag(1, true, 0, 1, 0x1);
    h.raw(0, 0);
    f.send(h);
    CHECK((r.rgbaq >> 32) == 0x3F800000ull);
}

TEST_CASE("PACKED: XYZF2/XYZ2 kick unless ADC, XYZF3/XYZ3 never kick (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::PRIM, gs_prim(6)}, {reg::RGBAQ, gs_rgbaq(255, 0, 0, 0x80)}});
    // XYZ2 packed: X bits 0-15, Y 32-47, Z 64-95, ADC bit 111. A vertex added with ADC = 1 completes the sprite's
    // queue without drawing it; the next two vertices draw [4,8) x [4,8).
    g.tag(4, true, 0, 1, 0x5);
    g.raw(0, 0);
    g.raw((0x40ull << 32) | 0x40ull, 1ull << 47);
    g.raw((0x40ull << 32) | 0x40ull, 0);
    g.raw((0x80ull << 32) | 0x80ull, 0);
    f.send(g);
    CHECK(f.core().stats().primitives == 1);
    CHECK(R(f.px(5, 5)) == 255u);
    CHECK(R(f.px(1, 1)) == 0u);
    // XYZF2 packed: Z = bits 68..91, F = bits 100..107.
    GifBuilder h;
    h.ad({{reg::PRIM, gs_prim(6)}});
    h.tag(2, true, 0, 1, 0x4);
    h.raw(0, (static_cast<u64>(0xAB) << 36) | (0x123456ull << 4));
    h.raw((0x20ull << 32) | 0x20, (static_cast<u64>(0xAB) << 36) | (0x123456ull << 4));
    f.send(h);
    CHECK(f.core().stats().primitives == 2);
    CHECK(R(f.px(1, 1)) == 255u);
    // XYZF3 / XYZ3 descriptors (0xC / 0xD): no kick even with a full queue.
    GifBuilder k;
    k.ad({{reg::PRIM, gs_prim(6)}, {reg::RGBAQ, gs_rgbaq(0, 255, 0, 0x80)}});
    k.tag(2, true, 0, 1, 0xD);
    k.raw((0x100ull << 32) | 0x100, 0);
    k.raw((0x120ull << 32) | 0x120, 0);
    f.send(k);
    CHECK(f.core().stats().primitives == 2);
    CHECK(G(f.px(16, 16)) == 0u);
}

TEST_CASE("REGLIST: two registers per qword, odd tail discarded; PRE ignored outside PACKED (hand: GS User's Manual)") {
    // NLOOP 3, NREG 3 {RGBAQ, ST, UV}: 9 values in 5 qwords; the 10th half is padding.
    Fixture e;
    GifBuilder h;
    h.tag(3, true, 1, 3, 0x321, true, 0x3);
    h.raw(0x11, 0x22);  // RGBAQ, ST
    h.raw(0x33, 0x44);  // UV, RGBAQ
    h.raw(0x55, 0x66);  // ST, UV
    h.raw(0x77, 0x88);  // RGBAQ, ST
    h.raw(0x99, 0xAA);  // UV, (padding half: must be discarded)
    e.send(h);
    const GsRegs& r = e.core().regs();
    CHECK(r.rgbaq == 0x77);
    CHECK(r.st == 0x88);
    CHECK(r.uv == 0x99);
    CHECK(r.prim == 0); // PRE is not applied for REGLIST
    CHECK(e.gs->gif().stats().qwords[3] == 6);
    // PRE with PACKED writes PRIM from the tag.
    GifBuilder p;
    p.tag(0, true, 0, 1, 0xF, true, 0x1E);
    e.send(p);
    CHECK(r.prim == 0x1E);
}

TEST_CASE("A+D and NOP; NLOOP 0 tags; register 0x7F ignored (game: docs/ANALYSIS/10 §2.11)") {
    Fixture f;
    GifBuilder g;
    g.tag(0, false, 0, 1, 0xE); // NLOOP 0 without EOP: the packet continues with the next tag
    g.ad({{reg::TEXA, 0x80ull << 32}, {reg::ALPHA_1, 0x44}, {reg::TEST_1, 0x5140B}, {reg::NOP, 0x1234}});
    f.send(g);
    const GsRegs& r = f.core().regs();
    CHECK(r.texa == (0x80ull << 32));
    CHECK(r.ctx[0].alpha == 0x44);
    CHECK(r.ctx[0].test == 0x5140B);
    CHECK(f.core().stats().unknown_reg_writes == 0);
    CHECK(f.gs->gif().active_path() == 0);
}

TEST_CASE("paths: MSKPATH3 stalls PATH3 at a packet boundary and resumes when cleared (game: docs/ANALYSIS/10 §3.1 type 0x21)") {
    Fixture f;
    int ready = 0;
    f.gs->set_path3_ready_callback([&] { ++ready; });
    Gif& gif = f.gs->gif();
    GifBuilder g;
    g.ad({{reg::TEXA, 1}});
    g.ad({{reg::TEXA, 2}});
    // Mask while idle: nothing is consumed, GIF_STAT shows M3P and P3Q.
    gif.set_m3p(true);
    CHECK(gif.path3(g.qwords()) == 0);
    CHECK((gif.stat() & 0x2u) != 0);
    CHECK((gif.stat() & 0x40u) != 0);
    CHECK(f.core().regs().texa == 0);
    gif.set_m3p(false);
    CHECK(ready == 1);
    CHECK(gif.path3(g.qwords()) == g.qwords().size());
    CHECK(f.core().regs().texa == 2);
    CHECK((gif.stat() & 0x40u) == 0);
    // Mask raised while PATH3 is inside a packet: the packet finishes, the next one waits.
    GifBuilder h;
    h.tag(2, true, 0, 1, 0xE);
    h.raw(3, reg::TEXA);
    const std::size_t first = gif.path3(std::span<const u128>(h.qwords().data(), 2)); // tag + 1 of 2 data qwords
    CHECK(first == 2);
    CHECK(gif.active_path() == 3);
    gif.set_m3p(true);
    GifBuilder rest;
    rest.raw(4, reg::TEXA);
    rest.ad({{reg::TEXA, 5}});
    CHECK(gif.path3(rest.qwords()) == 1); // the open packet's last qword only
    CHECK(f.core().regs().texa == 4);
    CHECK(gif.active_path() == 0);
}

TEST_CASE("paths: PATH2 stalls while PATH3 owns the GIF; PATH1 is queued behind an open PATH2 packet (model)") {
    Fixture f;
    Gif& gif = f.gs->gif();
    // PATH3 opens a packet (tag + 1 of 2 A+D qwords).
    GifBuilder p3;
    p3.tag(2, true, 0, 1, 0xE);
    p3.raw(0x10, reg::TEXA);
    p3.raw(0x11, reg::TEXA);
    CHECK(gif.path3(std::span<const u128>(p3.qwords().data(), 2)) == 2);
    CHECK(((gif.stat() >> 10) & 3u) == 3u); // APATH = PATH3
    GifBuilder p2;
    p2.ad({{reg::TEXA, 0x20}});
    CHECK(gif.path2(p2.qwords()) == 0);
    CHECK(gif.path2_waiting());
    CHECK((gif.stat() & 0x80u) != 0); // P2Q
    CHECK(gif.path3(std::span<const u128>(p3.qwords().data() + 2, 1)) == 1);
    CHECK(f.core().regs().texa == 0x11);
    CHECK(gif.path2(p2.qwords()) == p2.qwords().size());
    CHECK(f.core().regs().texa == 0x20);
    // PATH2 opens an IMAGE packet split over two DIRECT commands; a PATH1 kick in between is deferred.
    GifBuilder up;
    up.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0x100, 1, 0)}, {reg::TRXPOS, 0}, {reg::TRXREG, gs_trxreg(4, 2)}, {reg::TRXDIR, 0}});
    CHECK(gif.path2(up.qwords()) == up.qwords().size());
    GifBuilder img;
    img.tag(2, true, 2, 0, 0);
    img.raw(0x0000000200000001ull, 0x0000000400000003ull);
    img.raw(0x0000000600000005ull, 0x0000000800000007ull);
    CHECK(gif.path2(std::span<const u128>(img.qwords().data(), 2)) == 2);
    CHECK(gif.active_path() == 2);
    GifBuilder p1;
    p1.ad({{reg::TEXA, 0x30}});
    gif.path1(p1.qwords());
    CHECK(f.core().regs().texa == 0x20); // not yet
    CHECK((gif.stat() & 0x100u) != 0);   // P1Q
    CHECK(gif.path2(std::span<const u128>(img.qwords().data() + 2, 1)) == 1);
    CHECK(f.core().regs().texa == 0x30); // ran at the packet boundary
    CHECK(f.mem().read(0, 0x100, 1, 3, 1) == 8u);
    CHECK(gif.stats().path1_queued == 1);
    CHECK(gif.idle());
}

TEST_CASE("paths: PATH3 yields to a waiting PATH2 at a packet boundary (model)") {
    Fixture f;
    Gif& gif = f.gs->gif();
    GifBuilder p3;
    p3.tag(1, true, 0, 1, 0xE);
    p3.raw(1, reg::TEXA);
    p3.ad({{reg::TEXA, 2}});
    CHECK(gif.path3(std::span<const u128>(p3.qwords().data(), 1)) == 1); // tag only: PATH3 owns the GIF
    GifBuilder p2;
    p2.ad({{reg::TEXA, 9}});
    CHECK(gif.path2(p2.qwords()) == 0);
    // PATH3 finishes its packet, then stops before its next packet because PATH2 is waiting.
    CHECK(gif.path3(std::span<const u128>(p3.qwords().data() + 1, 3)) == 1);
    CHECK(gif.stats().path3_yields == 1);
    CHECK(gif.path2(p2.qwords()) == p2.qwords().size());
    CHECK(gif.path3(std::span<const u128>(p3.qwords().data() + 2, 2)) == 2);
    CHECK(f.core().regs().texa == 2);
}

TEST_CASE("GIF registers: CTRL reset, MODE M3R, STAT DIR from BUSDIR, TAG0 (hand: EE User's Manual GIF chapter)") {
    Fixture f;
    FakeBus& bus = f.bus;
    bus.write32(0x10003010, 1); // GIF_MODE.M3R
    CHECK((bus.read32(0x10003020) & 1u) != 0);
    GifBuilder g;
    g.ad({{reg::TEXA, 7}});
    CHECK(f.gs->gif().path3(g.qwords()) == 0);
    bus.write32(0x10003010, 0);
    CHECK(f.gs->gif().path3(g.qwords()) == g.qwords().size());
    CHECK(bus.read32(0x10003040) == static_cast<u32>(g.qwords()[0].u64[0]));
    bus.write64(0x12001040, 1); // BUSDIR
    CHECK((bus.read32(0x10003020) & (1u << 12)) != 0);
    bus.write64(0x12001040, 0);
    // An open packet is dropped by GIF_CTRL.RST.
    GifBuilder h;
    h.tag(2, true, 0, 1, 0xE);
    f.gs->gif().path3(h.qwords());
    CHECK(f.gs->gif().active_path() == 3);
    bus.write32(0x10003000, 1);
    CHECK(f.gs->gif().active_path() == 0);
    CHECK(bus.read32(0x10003020) == 0u); // the idle state sceGsSyncPath polls for (& 0xC00)
}

TEST_CASE("GsCore reg observer: state registers via A+D and PACKED, never per-vertex registers (diagnostics hook)") {
    Fixture f;
    std::vector<std::pair<u32, u64>> seen;
    f.core().set_reg_observer([&](u32 r, u64 v) { seen.emplace_back(r, v); });
    GifBuilder b;
    b.ad({{reg::PRIM, 6}, {reg::RGBAQ, 0x80808080u}, {reg::XYZ2, 0}, {reg::TEX0_1, 0x1234}, {reg::FOG, 0},
          {reg::XYZ3, 0}, {reg::ALPHA_1, 0x44}, {reg::TRXDIR, 0}});
    CHECK(f.send(b) == b.qwords().size());
    REQUIRE(seen.size() == 4);  // PRIM, TEX0_1, ALPHA_1, TRXDIR; RGBAQ/XYZ2/FOG/XYZ3 are not reported
    CHECK(seen[0] == std::pair<u32, u64>{reg::PRIM, 6});
    CHECK(seen[1] == std::pair<u32, u64>{reg::TEX0_1, 0x1234});
    CHECK(seen[2] == std::pair<u32, u64>{reg::ALPHA_1, 0x44});
    CHECK(seen[3].first == reg::TRXDIR);
    f.core().set_reg_observer(nullptr);
    CHECK(f.send(b) == b.qwords().size());
    CHECK(seen.size() == 4);
}
