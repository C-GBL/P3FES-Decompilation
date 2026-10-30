// Rasteriser: coverage (sprite / triangle top-left rule, XYOFFSET, scissor), kick rules, shading, and the
// per-pixel pipeline (alpha blend with every ALPHA_1 value of the game's census, alpha test, destination alpha
// test, Z16S depth test, FBMSK, dithering, colour clamp, PABE, FBA, fog).
#include "gs_test_util.h"

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;

TEST_CASE("sprite: covers [x0, x1) x [y0, y1) on pixel sample points (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    f.sprite(10, 20, 30, 25, 200, 0, 0, 0x80);
    CHECK(R(f.px(10, 20)) == 200u);
    CHECK(R(f.px(29, 24)) == 200u);
    CHECK(R(f.px(30, 24)) == 0u);
    CHECK(R(f.px(29, 25)) == 0u);
    CHECK(R(f.px(9, 20)) == 0u);
    CHECK(R(f.px(10, 19)) == 0u);
    CHECK(f.core().stats().pixels_written == 20u * 5u);
    CHECK(A(f.px(10, 20)) == 0x80u);
}

TEST_CASE("sprite: fractional 12.4 coordinates follow the top-left rule; vertex order does not matter (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::PRIM, gs_prim(6)},
          {reg::RGBAQ, gs_rgbaq(9, 9, 9, 0x80)},
          {reg::XYZ2, gs_xyz(20 * 16 + 8, 7 * 16 + 1, 0)}, // (20.5, 7.0625): kicked first, as the right/bottom
          {reg::XYZ2, gs_xyz(10 * 16 + 8, 3 * 16, 0)}});   // (10.5, 3.0)
    f.send(g);
    CHECK(R(f.px(10, 3)) == 0u);
    CHECK(R(f.px(11, 3)) == 9u);
    CHECK(R(f.px(20, 3)) == 9u);
    CHECK(R(f.px(21, 3)) == 0u);
    CHECK(R(f.px(11, 7)) == 9u);  // 7.0 < 7.0625: row 7 is inside
    CHECK(R(f.px(11, 8)) == 0u);
    CHECK(R(f.px(11, 2)) == 0u);
}

TEST_CASE("XYOFFSET and SCISSOR: window coordinates and inclusive scissor bounds (game: docs/ANALYSIS/10 §2.8)") {
    Fixture f;
    f.env();
    GifBuilder g;
    // The game's offset: OFX = (2048-320)*16, OFY = (2048-224)*16; vertex (1728+5, 1824+6) is pixel (5, 6).
    g.ad({{reg::XYOFFSET_1, gs_xyoffset((2048 - 320) * 16, (2048 - 224) * 16)},
          {reg::SCISSOR_1, gs_scissor(6, 8, 7, 9)},
          {reg::PRIM, gs_prim(6)},
          {reg::RGBAQ, gs_rgbaq(50, 60, 70, 0x80)},
          {reg::XYZ2, gs_xyz((1728 + 5) * 16, (1824 + 6) * 16, 0)},
          {reg::XYZ2, gs_xyz((1728 + 15) * 16, (1824 + 16) * 16, 0)}});
    f.send(g);
    u32 drawn = 0;
    for (u32 y = 0; y < 20; ++y)
        for (u32 x = 0; x < 20; ++x) drawn += R(f.px(x, y)) == 50u;
    CHECK(drawn == 9u);
    CHECK(R(f.px(6, 7)) == 50u);
    CHECK(R(f.px(8, 9)) == 50u);
    CHECK(R(f.px(9, 9)) == 0u);
    CHECK(R(f.px(5, 7)) == 0u);
}

TEST_CASE("skyInitialClear: the 1024x1024 sprite clears all 4 MiB (game: docs/ANALYSIS/10 §2.1)") {
    Fixture f;
    std::memset(f.mem().data(), 0x5A, kVramBytes);
    GifBuilder g;
    g.tag(1, true, 0, 12, 0xEEEEEEEEEEEEull);
    g.raw(0, reg::ALPHA_1);
    g.raw(0x100000, reg::FRAME_1);
    g.raw(0x03FF000003FF0000ull, reg::SCISSOR_1);
    g.raw(1, reg::PRMODECONT);
    g.raw(0x30000, reg::TEST_1);
    g.raw(0, reg::XYOFFSET_1);
    g.raw(0x10A000100ull, reg::ZBUF_1);
    g.raw(6, reg::PRIM);
    g.raw(0, reg::RGBAQ);
    g.raw(0, reg::XYZ2);
    g.raw(0x3FFFFFFF, reg::XYZ2);
    g.raw(0, reg::NOP);
    CHECK(f.send(g) == 13u);
    u32 nonzero = 0;
    for (u32 i = 0; i < kVramBytes; ++i) nonzero += f.mem().data()[i] != 0;
    CHECK(nonzero == 0u);
    CHECK(f.core().stats().pixels_written == 1024u * 1024u);
}

TEST_CASE("triangles: two triangles sharing an edge cover a square exactly once (hand: top-left rule)") {
    Fixture f;
    f.env();
    // Additive blend 0x48 with As = 0x80: Cd + Cs. A pixel drawn twice would read 20, a gap 0.
    GifBuilder g;
    g.ad({{reg::ALPHA_1, gs_alpha(0, 2, 0, 1)},
          {reg::PRIM, gs_prim(3, false, false, false, true)},
          {reg::RGBAQ, gs_rgbaq(10, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::XYZ2, gs_xyz(16 * 16, 0, 0)},
          {reg::XYZ2, gs_xyz(16 * 16, 16 * 16, 0)},
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::XYZ2, gs_xyz(16 * 16, 16 * 16, 0)},
          {reg::XYZ2, gs_xyz(0, 16 * 16, 0)}});
    f.send(g);
    u32 once = 0, twice = 0, never = 0;
    for (u32 y = 0; y < 16; ++y)
        for (u32 x = 0; x < 16; ++x) {
            const u32 r = R(f.px(x, y));
            once += r == 10;
            twice += r == 20;
            never += r == 0;
        }
    CHECK(once == 256u);
    CHECK(twice == 0u);
    CHECK(never == 0u);
    CHECK(R(f.px(16, 5)) == 0u);
    CHECK(R(f.px(5, 16)) == 0u);
}

TEST_CASE("kick rules: strip, fan, line strip, PRIM write resets the queue (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::PRIM, gs_prim(4)},
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::XYZ2, gs_xyz(160, 0, 0)},
          {reg::XYZ2, gs_xyz(0, 160, 0)},
          {reg::XYZ2, gs_xyz(160, 160, 0)},
          {reg::XYZ2, gs_xyz(0, 320, 0)}});
    f.send(g);
    CHECK(f.core().stats().primitives == 3u);
    GifBuilder h;
    h.ad({{reg::PRIM, gs_prim(5)},
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::XYZ2, gs_xyz(160, 0, 0)},
          {reg::XYZ2, gs_xyz(160, 160, 0)},
          {reg::XYZ2, gs_xyz(0, 160, 0)},
          {reg::PRIM, gs_prim(2)}, // resets the queue: the pending fan state is dropped
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::XYZ2, gs_xyz(320, 0, 0)},
          {reg::XYZ2, gs_xyz(320, 320, 0)}});
    f.send(h);
    CHECK(f.core().stats().primitives == 3u + 2u + 2u);
    GifBuilder p;
    p.ad({{reg::PRIM, 7}, {reg::XYZ2, gs_xyz(0, 0, 0)}});
    f.send(p);
    CHECK(f.core().stats().prohibited_prims == 1u);
}

TEST_CASE("shading: Gouraud interpolation and flat shading from the last vertex (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::PRIM, gs_prim(3, true)},
          {reg::RGBAQ, gs_rgbaq(0, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(0, 0, 0)},
          {reg::RGBAQ, gs_rgbaq(160, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(16 * 16, 0, 0)},
          {reg::RGBAQ, gs_rgbaq(0, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(0, 16 * 16, 0)}});
    f.send(g);
    // R = 160 * x / 16 along the top edge's direction: pixel (5, 2) -> 50.
    CHECK(R(f.px(5, 2)) == 50u);
    CHECK(R(f.px(0, 0)) == 0u);
    CHECK(R(f.px(10, 1)) == 100u);
    GifBuilder h;
    h.ad({{reg::PRIM, gs_prim(3, false)},
          {reg::RGBAQ, gs_rgbaq(1, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(32 * 16, 0, 0)},
          {reg::RGBAQ, gs_rgbaq(2, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(48 * 16, 0, 0)},
          {reg::RGBAQ, gs_rgbaq(3, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(32 * 16, 16 * 16, 0)}});
    f.send(h);
    CHECK(R(f.px(33, 1)) == 3u);
    CHECK(R(f.px(40, 2)) == 3u);
}

namespace {
// Destination (20, 40, 60, Ad 0x80), source (200, 100, 50, As 0x40), FIX 0x60.
u32 blend_case(u64 alpha, bool colclamp = true) {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::COLCLAMP, colclamp ? 1u : 0u}, {reg::ALPHA_1, alpha}});
    f.send(g);
    f.sprite(0, 0, 4, 4, 20, 40, 60, 0x80);
    f.sprite(0, 0, 4, 4, 200, 100, 50, 0x40, true);
    return f.px(1, 1);
}
} // namespace

TEST_CASE("alpha blend: every ALPHA_1 equation of the game's census (game: docs/ANALYSIS/14 §4; hand: GS User's Manual)") {
    // ((A - B) * C >> 7) + D per channel, then clamp (COLCLAMP = 1); the written alpha is As.
    u32 c = blend_case(0x44);                         // (Cs - Cd) * As + Cd
    CHECK(R(c) == 110u); CHECK(G(c) == 70u); CHECK(B(c) == 55u); CHECK(A(c) == 0x40u);
    c = blend_case(0x48);                             // Cs * As + Cd
    CHECK(R(c) == 120u); CHECK(G(c) == 90u); CHECK(B(c) == 85u);
    c = blend_case(0x42);                             // (0 - Cs) * As + Cd
    CHECK(R(c) == 0u); CHECK(G(c) == 0u); CHECK(B(c) == 35u);
    c = blend_case(gs_alpha(2, 2, 2, 1, 0x60));       // 0x6A: Cd only
    CHECK(R(c) == 20u); CHECK(G(c) == 40u); CHECK(B(c) == 60u);
    c = blend_case(0x58);                             // Cs * Ad + Cd, Ad = 0x80
    CHECK(R(c) == 220u); CHECK(G(c) == 140u); CHECK(B(c) == 110u);
    c = blend_case(0x54);                             // (Cs - Cd) * Ad + Cd = Cs
    CHECK(R(c) == 200u); CHECK(G(c) == 100u); CHECK(B(c) == 50u);
    c = blend_case(gs_alpha(0, 1, 2, 1, 0x60));       // 0x64: (Cs - Cd) * FIX + Cd
    CHECK(R(c) == 155u); CHECK(G(c) == 85u); CHECK(B(c) == 52u); // -960 >> 7 = -8 (arithmetic shift)
    c = blend_case(0x06);                             // (0 - Cd) * As + Cs
    CHECK(R(c) == 190u); CHECK(G(c) == 80u); CHECK(B(c) == 20u);
    c = blend_case(0x24);                             // 0x2024 as RpSkyRenderStateSet passes it: (Cs - Cd) * FIX(0) + Cs
    CHECK(R(c) == 200u); CHECK(G(c) == 100u); CHECK(B(c) == 50u);
}

TEST_CASE("alpha blend: COLCLAMP off wraps, PABE skips blending for As < 0x80, FBA sets the alpha MSB (hand: GS User's Manual)") {
    {
        Fixture f;
        f.env();
        GifBuilder g;
        g.ad({{reg::COLCLAMP, 0}, {reg::ALPHA_1, 0x48}});
        f.send(g);
        f.sprite(0, 0, 2, 2, 100, 0, 0, 0x80);
        f.sprite(0, 0, 2, 2, 200, 0, 0, 0x80, true);
        CHECK(R(f.px(0, 0)) == (300u & 0xFFu));
    }
    {
        Fixture f;
        f.env();
        GifBuilder g;
        g.ad({{reg::PABE, 1}, {reg::ALPHA_1, 0x44}});
        f.send(g);
        f.sprite(0, 0, 2, 2, 20, 20, 20, 0x80);
        f.sprite(0, 0, 2, 2, 200, 200, 200, 0x40, true); // As MSB clear: written unblended
        CHECK(R(f.px(0, 0)) == 200u);
        f.sprite(2, 0, 4, 2, 20, 20, 20, 0x80);
        f.sprite(2, 0, 4, 2, 200, 200, 200, 0x80, true); // MSB set: (200-20)*0x80>>7 + 20 = 200
        CHECK(R(f.px(2, 0)) == 200u);
        f.sprite(4, 0, 6, 2, 20, 20, 20, 0x80);
        f.sprite(4, 0, 6, 2, 200, 200, 200, 0xC0, true); // (180 * 192 >> 7) + 20 = 290 -> 255
        CHECK(R(f.px(4, 0)) == 255u);
    }
    {
        Fixture f;
        f.env();
        GifBuilder g;
        g.ad({{reg::FBA_1, 1}});
        f.send(g);
        f.sprite(0, 0, 2, 2, 1, 2, 3, 0x10);
        CHECK(A(f.px(0, 0)) == 0x90u);
    }
}

TEST_CASE("alpha test: the eight ATST functions and the four AFAIL modes (hand: GS User's Manual; game: 14 §4 TEST_1 map)") {
    struct Row {
        u32 atst;
        bool lt, eq, gt; // pass for As = AREF-1, AREF, AREF+1
    };
    const Row rows[] = {{0, false, false, false}, {1, true, true, true},  {2, true, false, false},
                        {3, true, true, false},   {4, false, true, false}, {5, false, true, true},
                        {6, false, false, true},  {7, true, false, true}};
    for (const Row& row : rows) {
        CAPTURE(row.atst);
        Fixture f;
        f.env();
        GifBuilder g;
        g.ad({{reg::TEST_1, gs_test(true, row.atst, 0x40, 0, false, false, true, 1)}});
        f.send(g);
        f.sprite(0, 0, 1, 1, 10, 0, 0, 0x3F);
        f.sprite(1, 0, 2, 1, 10, 0, 0, 0x40);
        f.sprite(2, 0, 3, 1, 10, 0, 0, 0x41);
        CHECK((R(f.px(0, 0)) == 10u) == row.lt);
        CHECK((R(f.px(1, 0)) == 10u) == row.eq);
        CHECK((R(f.px(2, 0)) == 10u) == row.gt);
    }
    // AFAIL with a failing test (NEVER), Z buffer written when allowed (ZMSK = 0).
    const auto afail = [](u32 mode, u32& color, u32& z) {
        Fixture f;
        f.env();
        f.sprite(0, 0, 1, 1, 1, 2, 3, 0x55);
        GifBuilder g;
        g.ad({{reg::ZBUF_1, gs_zbuf(280, 0xA, false)}, {reg::TEST_1, gs_test(true, 0, 0, mode, false, false, true, 1)}});
        f.send(g);
        f.sprite(0, 0, 1, 1, 100, 110, 120, 0x22, false, 0x1234);
        color = f.px(0, 0);
        z = f.mem().read(0x3A, 280 * 32, 10, 0, 0);
    };
    u32 c, z;
    afail(0, c, z); // KEEP
    CHECK(c == rgba(1, 2, 3, 0x55));
    CHECK(z == 0u);
    afail(1, c, z); // FB_ONLY
    CHECK(c == rgba(100, 110, 120, 0x22));
    CHECK(z == 0u);
    afail(2, c, z); // ZB_ONLY
    CHECK(c == rgba(1, 2, 3, 0x55));
    CHECK(z == 0x1234u);
    afail(3, c, z); // RGB_ONLY: colour without alpha, no Z
    CHECK(c == rgba(100, 110, 120, 0x55));
    CHECK(z == 0u);
    // The game's gs_set_up value TEST_1 = 0x5140B: ATE, GEQUAL 0x40, FB_ONLY, Z GEQUAL (10 §2.11).
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::TEST_1, 0x5140B}});
    f.send(g);
    f.sprite(0, 0, 1, 1, 7, 0, 0, 0x3F); // fails, FB_ONLY: colour written
    CHECK(R(f.px(0, 0)) == 7u);
}

TEST_CASE("destination alpha test: DATE/DATM on the frame's alpha MSB (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    f.sprite(0, 0, 1, 1, 0, 0, 0, 0x80); // MSB 1
    f.sprite(1, 0, 2, 1, 0, 0, 0, 0x7F); // MSB 0
    GifBuilder g;
    g.ad({{reg::TEST_1, gs_test(false, 0, 0, 0, true, false, true, 1)}});
    f.send(g);
    f.sprite(0, 0, 2, 1, 50, 0, 0, 0x80);
    CHECK(R(f.px(0, 0)) == 0u);  // DATM 0: only alpha-MSB-0 pixels pass
    CHECK(R(f.px(1, 0)) == 50u);
    GifBuilder h;
    h.ad({{reg::TEST_1, gs_test(false, 0, 0, 0, true, true, true, 1)}});
    f.send(h);
    f.sprite(0, 0, 1, 1, 60, 0, 0, 0x80);
    CHECK(R(f.px(0, 0)) == 60u);
}

TEST_CASE("depth: PSMZ16S at ZBP 280 with GEQUAL/GREATER, ZMSK, and 16-bit clamping (game: docs/ANALYSIS/10 §2.8; hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::ZBUF_1, gs_zbuf(280, 0xA, false)}, {reg::TEST_1, gs_test(false, 0, 0, 0, false, false, true, 2)}});
    f.send(g);
    const auto zat = [&](u32 x, u32 y) { return f.mem().read(0x3A, 280 * 32, 10, x, y); };
    f.sprite(0, 0, 4, 4, 10, 0, 0, 0x80, false, 1000);
    CHECK(zat(1, 1) == 1000u);
    f.sprite(0, 0, 4, 4, 20, 0, 0, 0x80, false, 999); // fails GEQUAL
    CHECK(R(f.px(1, 1)) == 10u);
    f.sprite(0, 0, 4, 4, 30, 0, 0, 0x80, false, 1000); // equal passes GEQUAL
    CHECK(R(f.px(1, 1)) == 30u);
    GifBuilder h;
    h.ad({{reg::TEST_1, gs_test(false, 0, 0, 0, false, false, true, 3)}});
    f.send(h);
    f.sprite(0, 0, 4, 4, 40, 0, 0, 0x80, false, 1000); // equal fails GREATER
    CHECK(R(f.px(1, 1)) == 30u);
    f.sprite(0, 0, 4, 4, 50, 0, 0, 0x80, false, 0x12345); // > 0xFFFF: clamped to 0xFFFF (model)
    CHECK(R(f.px(1, 1)) == 50u);
    CHECK(zat(1, 1) == 0xFFFFu);
    GifBuilder k;
    k.ad({{reg::ZBUF_1, gs_zbuf(280, 0xA, true)}, {reg::TEST_1, gs_test(false, 0, 0, 0, false, false, true, 1)}});
    f.send(k);
    f.sprite(0, 0, 4, 4, 60, 0, 0, 0x80, false, 5);
    CHECK(R(f.px(1, 1)) == 60u);
    CHECK(zat(1, 1) == 0xFFFFu); // ZMSK: not written
    // The Z buffer does not overlap the frame buffers: frame page 0 untouched by Z writes at page 280.
    CHECK(f.mem().read(0x00, 140 * 32, 10, 1, 1) == 0u);
}

TEST_CASE("FBMSK: masked bits keep the frame's value (hand: GS User's Manual)") {
    Fixture f;
    f.env(0x00, 0xFF00FF00u);
    f.sprite(0, 0, 1, 1, 0x11, 0x22, 0x33, 0x44);
    CHECK(f.px(0, 0) == 0x00330011u);
    Fixture h;
    h.env(0x02, 0x00F800F8u); // 16-bit frame: R and B fields masked
    h.sprite(0, 0, 1, 1, 0xFF, 0xFF, 0xFF, 0x80);
    CHECK(h.mem().read(0x02, 0, 10, 0, 0) == ((1u << 15) | (0x1Fu << 5)));
}

TEST_CASE("dithering: DIMX on a 16-bit frame, none on 32-bit (game: DIMX 0x6071243571603524, 14 §4; hand: GS User's Manual)") {
    // The game's standard matrix decodes (3-bit signed, row-major) to
    // [-4 2 -3 3; 0 -2 1 -1; -3 3 -4 2; 1 -1 0 -2]. R = 103: stored R5 = (103 + d) >> 3.
    const s32 m[4][4] = {{-4, 2, -3, 3}, {0, -2, 1, -1}, {-3, 3, -4, 2}, {1, -1, 0, -2}};
    Fixture f;
    f.env(0x02);
    GifBuilder g;
    g.ad({{reg::DIMX, 0x6071243571603524ull}, {reg::DTHE, 1}});
    f.send(g);
    f.sprite(0, 0, 4, 4, 103, 0, 0, 0x80);
    u32 bad = 0;
    for (u32 y = 0; y < 4; ++y)
        for (u32 x = 0; x < 4; ++x)
            bad += (f.mem().read(0x02, 0, 10, x, y) & 0x1Fu) != static_cast<u32>((103 + m[y][x]) >> 3);
    CHECK(bad == 0u);
    CHECK((f.mem().read(0x02, 0, 10, 1, 0) & 0x1Fu) == 13u);
    CHECK((f.mem().read(0x02, 0, 10, 0, 0) & 0x1Fu) == 12u);
    // DTHE = 0: plain truncation.
    GifBuilder h;
    h.ad({{reg::DTHE, 0}});
    f.send(h);
    f.sprite(0, 0, 4, 4, 103, 0, 0, 0x80);
    CHECK((f.mem().read(0x02, 0, 10, 1, 0) & 0x1Fu) == 12u);
    // 32-bit frame with DTHE = 1: unchanged.
    Fixture k;
    k.env();
    GifBuilder q;
    q.ad({{reg::DIMX, 0x6071243571603524ull}, {reg::DTHE, 1}});
    k.send(q);
    k.sprite(0, 0, 4, 4, 103, 0, 0, 0x80);
    CHECK(R(k.px(1, 0)) == 103u);
}

TEST_CASE("fog: C = (F * C + (255 - F) * FOGCOL) >> 8 (hand: GS User's Manual)") {
    Fixture f;
    f.env();
    GifBuilder g;
    g.ad({{reg::FOGCOL, 0x0000FF},
          {reg::PRIM, gs_prim(6, false, false, true)},
          {reg::RGBAQ, gs_rgbaq(200, 100, 0, 0x80)},
          {reg::XYZF2, gs_xyz(0, 0, 0) | (255ull << 56)},
          {reg::XYZF2, gs_xyz(32, 32, 0) | (255ull << 56)},
          {reg::XYZF2, gs_xyz(32, 0, 0) | (0ull << 56)},
          {reg::XYZF2, gs_xyz(64, 32, 0) | (0ull << 56)}});
    f.send(g);
    CHECK(R(f.px(0, 0)) == 199u); // (255 * 200) >> 8
    CHECK(G(f.px(0, 0)) == 99u);
    CHECK(R(f.px(2, 0)) == 254u); // all fog colour: (255 * 255) >> 8
    CHECK(G(f.px(2, 0)) == 0u);
}
