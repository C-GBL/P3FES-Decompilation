// Texturing: formats (CT32/24/16, T8/T8H/T4 with CLUTs), CLUT loading (CSM1 layouts, CSA, CLD modes, CSM2),
// TEXA expansion, TFX functions, wrap modes, bilinear filtering, perspective-correct STQ and mipmap selection.
#include "gs_test_util.h"

#include "../../runtime/gs/gs_raster.h"

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;

namespace {

void put(Fixture& f, u32 psm, u32 bp, u32 bw, u32 x, u32 y, u32 v) { f.mem().write(psm, bp, bw, x, y, v); }

// Draw a sprite [x0, x0 + w) x [y0, y0 + h) with UV mapped 1:1 from (u0, v0) texels (FST = 1).
void tex_sprite(Fixture& f, u64 tex0, u32 x0, u32 y0, u32 w, u32 h, u32 u0 = 0, u32 v0 = 0, u32 rgba_q = 0x80808080u,
                u64 clamp = 0, u64 tex1 = 0) {
    GifBuilder g;
    g.ad({{reg::TEX0_1, tex0},
          {reg::TEX1_1, tex1},
          {reg::CLAMP_1, clamp},
          {reg::PRIM, gs_prim(6, false, true, false, false, true)},
          {reg::RGBAQ, gs_rgbaq(rgba_q & 0xFF, (rgba_q >> 8) & 0xFF, (rgba_q >> 16) & 0xFF, rgba_q >> 24)},
          {reg::UV, gs_uv(u0 * 16, v0 * 16)},
          {reg::XYZ2, gs_xyz(x0 * 16, y0 * 16, 0)},
          {reg::UV, gs_uv((u0 + w) * 16, (v0 + h) * 16)},
          {reg::XYZ2, gs_xyz((x0 + w) * 16, (y0 + h) * 16, 0)}});
    f.send(g);
}

// CSM1 8-bit position of CLUT entry i (index bits 3 and 4 swapped), 16 x 16 entries.
u32 csm1_8_x(u32 i) { return ((i & ~0x18u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1)) & 15u; }
u32 csm1_8_y(u32 i) { return ((i & ~0x18u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1)) >> 4; }

} // namespace

TEST_CASE("texture: PSMCT32 DECAL copies texels 1:1; MODULATE scales by vertex colour / 0x80 (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    for (u32 y = 0; y < 8; ++y)
        for (u32 x = 0; x < 8; ++x) put(f, 0x00, 0x2000, 1, x, y, rgba(x * 30, y * 30, 7, 0x40 + x));
    tex_sprite(f, gs_tex0(0x2000, 1, 0x00, 3, 3, true, 1), 10, 10, 8, 8);
    u32 bad = 0;
    for (u32 y = 0; y < 8; ++y)
        for (u32 x = 0; x < 8; ++x) bad += f.px(10 + x, 10 + y) != rgba(x * 30, y * 30, 7, 0x40 + x);
    CHECK(bad == 0u);
    tex_sprite(f, gs_tex0(0x2000, 1, 0x00, 3, 3, true, 0), 30, 10, 8, 8, 0, 0, 0x80404080u);
    const u32 c = f.px(30 + 7, 10 + 2); // texel (7, 2) = (210, 60, 7, 0x47)
    CHECK(R(c) == 210u);              // * 0x80 >> 7
    CHECK(G(c) == 30u);               // * 0x40 >> 7
    CHECK(B(c) == 3u);
    CHECK(A(c) == (0x47u * 0x80u >> 7));
    // TCC = 0: alpha is the vertex alpha.
    tex_sprite(f, gs_tex0(0x2000, 1, 0x00, 3, 3, false, 1), 50, 10, 8, 8, 0, 0, 0x33808080u);
    CHECK(A(f.px(51, 11)) == 0x33u);
}

TEST_CASE("texture: HIGHLIGHT / HIGHLIGHT2 (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    put(f, 0x00, 0x2000, 1, 0, 0, rgba(100, 200, 10, 0x30));
    tex_sprite(f, gs_tex0(0x2000, 1, 0x00, 0, 0, true, 2), 0, 0, 1, 1, 0, 0, 0x20808080u);
    CHECK(f.px(0, 0) == rgba(132, 232, 42, 0x50)); // C = Ct*Cf>>7 + Af (Af = 0x20); A = At + Af
    tex_sprite(f, gs_tex0(0x2000, 1, 0x00, 0, 0, true, 3), 1, 0, 1, 1, 0, 0, 0x20808080u);
    CHECK(f.px(1, 0) == rgba(132, 232, 42, 0x30)); // A = At
}

TEST_CASE("texture: PSMCT24 / PSMCT16 alpha expansion through TEXA (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::TEXA, 0x11u | (static_cast<u64>(0x99) << 32) | 0x8000u}}); // TA0 0x11, TA1 0x99, AEM
    f.send(g);
    put(f, 0x01, 0x2000, 1, 0, 0, 0x102030);
    put(f, 0x01, 0x2000, 1, 1, 0, 0x000000);
    tex_sprite(f, gs_tex0(0x2000, 1, 0x01, 1, 0, true, 1), 0, 0, 2, 1);
    CHECK(f.px(0, 0) == (0x102030u | (0x11u << 24)));
    CHECK(f.px(1, 0) == 0u); // AEM: black -> alpha 0
    // PSMCT16: RGB5 << 3; A bit -> TA1, otherwise TA0 (AEM: 0 when RGB = 0 and A = 0).
    put(f, 0x02, 0x2100, 1, 0, 0, 0x8000u | (31u << 10) | (16u << 5) | 1u);
    put(f, 0x02, 0x2100, 1, 1, 0, (2u << 5));
    put(f, 0x02, 0x2100, 1, 2, 0, 0u);
    tex_sprite(f, gs_tex0(0x2100, 1, 0x02, 2, 0, true, 1), 0, 2, 3, 1);
    CHECK(f.px(0, 2) == rgba(8, 128, 248, 0x99));
    CHECK(f.px(1, 2) == rgba(0, 16, 0, 0x11));
    CHECK(f.px(2, 2) == 0u);
}

TEST_CASE("CLUT: PSMT8 with a 256-entry CT32 CLUT in CSM1 layout (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    // CLUT at block 0x3000 (BW 1): entry i at the CSM1 position; entries are distinct colours.
    for (u32 i = 0; i < 256; ++i) put(f, 0x00, 0x3000, 1, csm1_8_x(i), csm1_8_y(i), rgba(i, 255 - i, i ^ 0x5A, 0x80));
    // 16x2 PSMT8 texture holding indices 0..31 (entries 8..15 and 16..23 are the ones CSM1 swaps).
    for (u32 i = 0; i < 32; ++i) put(f, 0x13, 0x2000, 2, i & 15u, i >> 4, i);
    tex_sprite(f, gs_tex0(0x2000, 2, 0x13, 4, 1, true, 1, 0x3000, 0x0, 0, 0, 1), 0, 0, 16, 2);
    u32 bad = 0;
    for (u32 i = 0; i < 32; ++i) bad += f.px(i & 15u, i >> 4) != rgba(i, 255 - i, i ^ 0x5A, 0x80);
    CHECK(bad == 0u);
    CHECK(f.core().stats().clut_loads == 1u);
    // The CLUT entries really are swapped in memory: entry 8 lives at (0, 1), entry 16 at (8, 0).
    CHECK(csm1_8_x(8) == 0u);
    CHECK(csm1_8_y(8) == 1u);
    CHECK(csm1_8_x(16) == 8u);
    CHECK(csm1_8_y(16) == 0u);
}

TEST_CASE("CLUT: PSMT4 with CSA, 32- and 16-bit CLUTs; PSMT8H index in the top byte (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    // 4-bit texture 4x1 = indices 0, 1, 2, 15.
    put(f, 0x14, 0x2000, 2, 0, 0, 0);
    put(f, 0x14, 0x2000, 2, 1, 0, 1);
    put(f, 0x14, 0x2000, 2, 2, 0, 2);
    put(f, 0x14, 0x2000, 2, 3, 0, 15);
    // A 16-entry CT32 CLUT (8 x 2 layout) at 0x3000, loaded at CSA 3.
    for (u32 i = 0; i < 16; ++i) put(f, 0x00, 0x3000, 1, i & 7u, i >> 3, rgba(10 * i, 0, 0, 0x80));
    tex_sprite(f, gs_tex0(0x2000, 2, 0x14, 2, 0, true, 1, 0x3000, 0x0, 0, 3, 1), 0, 0, 4, 1);
    CHECK(f.px(0, 0) == rgba(0, 0, 0, 0x80));
    CHECK(f.px(1, 0) == rgba(10, 0, 0, 0x80));
    CHECK(f.px(3, 0) == rgba(150, 0, 0, 0x80));
    CHECK(f.core().clut()[3 * 16 + 1] == 10u);         // low halves at CSA*16 + i
    CHECK(f.core().clut()[3 * 16 + 1 + 256] == 0x8000u); // high halves at +256
    // A 16-bit CLUT at CSA 20 (16-bit CLUTs use all 32 CSA values).
    GifBuilder g;
    g.ad({{reg::TEXA, 0x80u | (static_cast<u64>(0x80) << 32)}});
    f.send(g);
    for (u32 i = 0; i < 16; ++i) put(f, 0x02, 0x3100, 1, i & 7u, i >> 3, 0x8000u | i);
    tex_sprite(f, gs_tex0(0x2000, 2, 0x14, 2, 0, true, 1, 0x3100, 0x2, 0, 20, 1), 0, 1, 4, 1);
    CHECK(f.px(1, 1) == rgba(8, 0, 0, 0x80));
    CHECK(f.px(3, 1) == rgba(120, 0, 0, 0x80));
    CHECK(f.core().clut()[20 * 16 + 15] == (0x8000u | 15u));
    // PSMT8H: the index is the top byte of a 32-bit word (shares the frame's words, docs/ANALYSIS/14 §5).
    for (u32 i = 0; i < 256; ++i) put(f, 0x00, 0x3200, 1, csm1_8_x(i), csm1_8_y(i), rgba(0, i, 0, 0x80));
    put(f, 0x00, 0x2400, 1, 0, 0, 0x7700FFFFu);
    tex_sprite(f, gs_tex0(0x2400, 1, 0x1B, 0, 0, true, 1, 0x3200, 0x0, 0, 0, 1), 0, 2, 1, 1);
    CHECK(f.px(0, 2) == rgba(0, 0x77, 0, 0x80));
}

TEST_CASE("CLUT: CLD load control (0 keep, 1 load, 2/3 load and set CBP0/1, 4/5 load when CBP differs) (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    put(f, 0x14, 0x2000, 2, 0, 0, 0);
    const auto entry0 = [&](u32 cbp, u32 cld) {
        tex_sprite(f, gs_tex0(0x2000, 2, 0x14, 0, 0, true, 1, cbp, 0x0, 0, 0, cld), 0, 0, 1, 1);
        return R(f.px(0, 0));
    };
    put(f, 0x00, 0x3000, 1, 0, 0, rgba(11, 0, 0, 0x80));
    put(f, 0x00, 0x3100, 1, 0, 0, rgba(22, 0, 0, 0x80));
    CHECK(entry0(0x3000, 1) == 11u);
    put(f, 0x00, 0x3000, 1, 0, 0, rgba(12, 0, 0, 0x80));
    CHECK(entry0(0x3000, 0) == 11u); // CLD 0: the cache keeps the old entry
    CHECK(entry0(0x3000, 2) == 12u); // load, CBP0 = 0x3000
    put(f, 0x00, 0x3000, 1, 0, 0, rgba(13, 0, 0, 0x80));
    CHECK(entry0(0x3000, 4) == 12u); // CBP == CBP0: no load
    CHECK(entry0(0x3100, 4) == 22u); // differs: load, CBP0 = 0x3100
    CHECK(entry0(0x3000, 3) == 13u); // load, CBP1 = 0x3000
    CHECK(entry0(0x3100, 5) == 22u); // differs from CBP1: load
    CHECK(entry0(0x3100, 5) == 22u); // same: no load
    CHECK(f.core().stats().clut_loads == 5u);
    // TEX2 rewrites only PSM and the CLUT fields of TEX0 and triggers the same load logic.
    GifBuilder g;
    g.ad({{reg::TEX2_1, gs_tex0(0, 0, 0x14, 0, 0, false, 0, 0x3000, 0x0, 0, 0, 1)}});
    f.send(g);
    CHECK(bits(f.core().regs().ctx[0].tex0, 0, 14) == 0x2000u);
    CHECK(bits(f.core().regs().ctx[0].tex0, 37, 14) == 0x3000u);
    CHECK(f.core().stats().clut_loads == 6u);
}

TEST_CASE("CLUT: CSM2 reads a linear 16-bit CLUT at TEXCLUT (COU, COV, CBW) (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::TEXCLUT, 2u | (1u << 6) | (5u << 12)}, {reg::TEXA, static_cast<u64>(0x80) << 32}}); // CBW 2, COU 1 (x 16), COV 5
    f.send(g);
    for (u32 i = 0; i < 16; ++i) put(f, 0x02, 0x3000, 2, 16 + i, 5, 0x8000u | (i << 5));
    put(f, 0x14, 0x2000, 2, 0, 0, 9);
    tex_sprite(f, gs_tex0(0x2000, 2, 0x14, 0, 0, true, 1, 0x3000, 0x2, 1, 0, 1), 0, 0, 1, 1);
    CHECK(f.px(0, 0) == rgba(0, 9 * 8, 0, 0x80));
}

TEST_CASE("wrap modes: REPEAT, CLAMP, REGION_CLAMP, REGION_REPEAT (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    for (u32 x = 0; x < 8; ++x) put(f, 0x00, 0x2000, 1, x, 0, rgba(x, 0, 0, 0x80));
    const u64 tex0 = gs_tex0(0x2000, 1, 0x00, 3, 0, true, 1);
    tex_sprite(f, tex0, 0, 0, 20, 1, 0, 0, 0x80808080u, 0); // REPEAT: texel x & 7
    CHECK(R(f.px(10, 0)) == 2u);
    CHECK(R(f.px(19, 0)) == 3u);
    tex_sprite(f, tex0, 0, 1, 20, 1, 0, 0, 0x80808080u, 1u | (1u << 2)); // CLAMP
    CHECK(R(f.px(10, 1)) == 7u);
    const u64 region_clamp = 2u | (2u << 2) | (2ull << 4) | (5ull << 14);
    tex_sprite(f, tex0, 0, 2, 8, 1, 0, 0, 0x80808080u, region_clamp);
    CHECK(R(f.px(0, 2)) == 2u);
    CHECK(R(f.px(7, 2)) == 5u);
    const u64 region_repeat = 3u | (3u << 2) | (1ull << 4) | (4ull << 14); // u = (u & 1) | 4
    tex_sprite(f, tex0, 0, 3, 8, 1, 0, 0, 0x80808080u, region_repeat);
    CHECK(R(f.px(0, 3)) == 4u);
    CHECK(R(f.px(3, 3)) == 5u);
}

TEST_CASE("filtering: bilinear weights in 1/16 texel steps with texel centres at +0.5 (hand: GS User's Manual)") {
    Fixture f;
    put(f, 0x00, 0x2000, 1, 0, 0, rgba(0, 0, 0, 0));
    put(f, 0x00, 0x2000, 1, 1, 0, rgba(255, 255, 255, 255));
    detail::TexState t{};
    t.psm = 0x00;
    t.level[0] = {0x2000, 1, 1, 0};
    t.wms = t.wmt = 1; // clamp
    CHECK(R(detail::sample_texture(f.mem(), f.core().clut(), t, 16, 8, true, 0)) == 127u); // halfway: 8/16
    CHECK(R(detail::sample_texture(f.mem(), f.core().clut(), t, 8, 8, true, 0)) == 0u);    // texel 0 centre
    CHECK(R(detail::sample_texture(f.mem(), f.core().clut(), t, 24, 8, true, 0)) == 255u); // texel 1 centre
    CHECK(R(detail::sample_texture(f.mem(), f.core().clut(), t, 12, 8, true, 0)) == 63u);   // 4/16
    CHECK(R(detail::sample_texture(f.mem(), f.core().clut(), t, 16, 8, false, 0)) == 255u); // nearest: texel 1
    // Through a sprite: TEX1.MMAG = 1 and an LOD of 0 select bilinear.
    f.env();
    tex_sprite(f, gs_tex0(0x2000, 1, 0x00, 1, 0, true, 1), 0, 0, 2, 1, 0, 0, 0x80808080u, 1u | (1u << 2), 1u << 5);
    CHECK(R(f.px(0, 0)) == 0u);   // u = 0 -> clamp(-0.5) blends texel 0 with itself
    CHECK(R(f.px(1, 0)) == 127u); // u = 1.0 -> halfway between the two centres
}

TEST_CASE("STQ: perspective-correct coordinates, S/Q and T/Q scaled by 2^TW / 2^TH (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    for (u32 x = 0; x < 16; ++x) put(f, 0x00, 0x2000, 1, x, 0, rgba(x * 16, 0, 0, 0x80));
    // Triangle with Q = 2 and S = 2 * s: s/q identical to a Q = 1 mapping, sample at s = x / 16 along the top edge.
    const auto st = [](float s, float t) {
        u32 a, b;
        std::memcpy(&a, &s, 4);
        std::memcpy(&b, &t, 4);
        return static_cast<u64>(a) | (static_cast<u64>(b) << 32);
    };
    GifBuilder g;
    g.ad({{reg::TEX0_1, gs_tex0(0x2000, 1, 0x00, 4, 0, true, 1)},
          {reg::TEX1_1, 0},
          {reg::CLAMP_1, 1u | (1u << 2)},
          {reg::PRIM, gs_prim(3, false, true, false, false, false)},
          {reg::ST, st(0.0f, 0.0f)},
          {reg::RGBAQ, gs_rgbaq(0x80, 0x80, 0x80, 0x80, 0x40000000u)},
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::ST, st(2.0f, 0.0f)},
          {reg::XYZ2, gs_xyz(16 * 16, 0, 0)},
          {reg::ST, st(0.0f, 0.0f)},
          {reg::XYZ2, gs_xyz(0, 16 * 16, 0)}});
    f.send(g);
    CHECK(R(f.px(5, 0)) == 5u * 16u);
    CHECK(R(f.px(9, 0)) == 9u * 16u);
}

TEST_CASE("mipmapping: LCM/K select the level, MIPTBP1 gives its base (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    for (u32 y = 0; y < 8; ++y)
        for (u32 x = 0; x < 8; ++x) put(f, 0x00, 0x2000, 1, x, y, rgba(10, 0, 0, 0x80));
    for (u32 y = 0; y < 4; ++y)
        for (u32 x = 0; x < 4; ++x) put(f, 0x00, 0x2100, 1, x, y, rgba(20, 0, 0, 0x80));
    GifBuilder g;
    g.ad({{reg::MIPTBP1_1, 0x2100u | (1u << 14)}});
    f.send(g);
    const u64 tex0 = gs_tex0(0x2000, 1, 0x00, 3, 3, true, 1);
    // LCM = 1, K = +1.0 (16 in 1/16 units), MXL = 1, MMIN = 2 (NEAREST_MIPMAP_NEAREST): level 1.
    const u64 tex1 = 1u | (1u << 2) | (2u << 6) | (static_cast<u64>(16) << 32);
    tex_sprite(f, tex0, 0, 0, 4, 4, 0, 0, 0x80808080u, 0, tex1);
    CHECK(R(f.px(1, 1)) == 20u);
    // K = -1.0 -> magnification at level 0.
    const u64 tex1_mag = 1u | (1u << 2) | (2u << 6) | (static_cast<u64>(0xFF0) << 32);
    tex_sprite(f, tex0, 8, 0, 4, 4, 0, 0, 0x80808080u, 0, tex1_mag);
    CHECK(R(f.px(9, 1)) == 10u);
    // MXL = 0 caps the level at 0.
    const u64 tex1_cap = 1u | (0u << 2) | (2u << 6) | (static_cast<u64>(16) << 32);
    tex_sprite(f, tex0, 16, 0, 4, 4, 0, 0, 0x80808080u, 0, tex1_cap);
    CHECK(R(f.px(17, 1)) == 10u);
}
