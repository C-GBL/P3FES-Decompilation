// CRTC composition (PMODE / SMODE2 / DISPFB / DISPLAY / BGCOLOR), the game's flicker-free two-circuit setup, PNG
// output, frame comparison helpers, and the host self-test scene.
#include "gs_test_util.h"

#include "p3fes/gs/gs_selftest.h"

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::gs::test;

namespace {

DisplayRegs display_640x448(u64 pmode, u64 smode2 = 1) {
    DisplayRegs d;
    d.pmode = pmode;
    d.smode2 = smode2;
    d.dispfb[0] = gs_dispfb(0, 10, 0);
    d.display[0] = 0x001BF9FF0183227Cull; // DX 636 DY 50 MAGH 3 DW 2559 DH 447 (10 §2.7)
    d.dispfb[1] = gs_dispfb(0, 10, 0);
    d.display[1] = 0x001BF9FF0183227Cull;
    return d;
}

void fill_rows(GsMemory& m, u32 fbp_blocks) {
    for (u32 y = 0; y < 448; ++y)
        for (u32 x = 0; x < 640; ++x) m.write(0x00, fbp_blocks, 10, x, y, rgba(y & 0xFFu, x & 0xFFu, 0x40, 0x80));
}

// Minimal PNG reader for the writer's own output (stored deflate blocks only).
bool read_stored_png(const std::vector<u8>& png, u32& w, u32& h, std::vector<u8>& rgb) {
    const u8 sig[8] = {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
    if (png.size() < 8 || std::memcmp(png.data(), sig, 8) != 0) return false;
    std::size_t p = 8;
    std::vector<u8> z;
    const auto be32 = [&](std::size_t at) {
        return (static_cast<u32>(png[at]) << 24) | (static_cast<u32>(png[at + 1]) << 16) | (static_cast<u32>(png[at + 2]) << 8) | png[at + 3];
    };
    while (p + 8 <= png.size()) {
        const u32 len = be32(p);
        const std::string type(reinterpret_cast<const char*>(png.data() + p + 4), 4);
        const u8* data = png.data() + p + 8;
        if (type == "IHDR") {
            w = be32(p + 8);
            h = be32(p + 12);
            if (data[8] != 8 || data[9] != 2) return false;
        } else if (type == "IDAT") {
            z.insert(z.end(), data, data + len);
        }
        p += 12u + len;
    }
    std::size_t q = 2; // zlib header
    std::vector<u8> raw;
    for (;;) {
        const bool last = (z[q] & 1u) != 0;
        if ((z[q] >> 1) != 0) return false; // only stored blocks
        const u32 n = z[q + 1] | (static_cast<u32>(z[q + 2]) << 8);
        raw.insert(raw.end(), z.begin() + static_cast<std::ptrdiff_t>(q + 5), z.begin() + static_cast<std::ptrdiff_t>(q + 5 + n));
        q += 5u + n;
        if (last) break;
    }
    rgb.clear();
    for (u32 y = 0; y < h; ++y) {
        const u8* row = raw.data() + static_cast<std::size_t>(y) * (1u + w * 3u);
        if (row[0] != 0) return false;
        rgb.insert(rgb.end(), row + 1, row + 1 + w * 3u);
    }
    return true;
}

} // namespace

TEST_CASE("compose: one read circuit, DBX/DBY offsets, 640x448 from DISPLAY (hand: GS User's Manual; game: 10 §2.7)") {
    GsMemory m;
    for (u32 y = 0; y < 460; ++y)
        for (u32 x = 0; x < 650; ++x) m.write(0x00, 2 * 32, 11, x, y, rgba(x & 0xFFu, y & 0xFFu, 3, 0x80));
    DisplayRegs d;
    d.pmode = 0x1u | (1u << 5) | (0xFFu << 8); // EN1, MMOD, ALP 0xFF
    d.smode2 = 1;
    d.dispfb[0] = gs_dispfb(2, 11, 0, 3, 5);
    d.display[0] = 0x001BF9FF0183227Cull;
    ComposeInfo info;
    const Frame f = compose(m, d, &info);
    REQUIRE(f.width == 640u);
    REQUIRE(f.height == 448u);
    CHECK(info.circuit_enabled[0]);
    CHECK_FALSE(info.circuit_enabled[1]);
    CHECK(f.at(0, 0) == rgba(3, 5, 3, 0xFF));
    CHECK(f.at(639, 447) == rgba((639 + 3) & 0xFFu, (447 + 5) & 0xFFu, 3, 0xFF));
    CHECK(compose(m, DisplayRegs{}).empty());
}

TEST_CASE("compose: RenderWare's flicker-free interlace = circuit 1 over circuit 2 one line down, ALP 0x80 (game: 10 §2.10, B-51)") {
    GsMemory m;
    fill_rows(m, 0);
    DisplayRegs d = display_640x448(0x8067);
    d.dispfb[1] = gs_dispfb(0, 10, 0, 0, 1);
    d.display[1] = 0x001BE9FF0183227Cull; // DH 446
    const Frame f = compose(m, d);
    REQUIRE(f.height == 448u);
    for (u32 y : {0u, 1u, 100u, 255u, 446u}) {
        const u32 c1 = y & 0xFFu, c2 = (y + 1) & 0xFFu;
        CHECK(R(f.at(7, y)) == (c1 * 128u + c2 * 127u + 127u) / 255u);
        CHECK(G(f.at(7, y)) == (7u * 128u + 7u * 127u + 127u) / 255u);
    }
    // Last line: circuit 2 ends one line earlier, so circuit 1 blends with BGCOLOR (0).
    CHECK(R(f.at(7, 447)) == ((447u & 0xFFu) * 128u + 127u) / 255u);
}

TEST_CASE("compose: MMOD 0 uses circuit 1's pixel alpha, SLBG blends with BGCOLOR, PSMCT16 display (hand: GS User's Manual)") {
    GsMemory m;
    for (u32 y = 0; y < 448; ++y)
        for (u32 x = 0; x < 640; ++x) {
            m.write(0x00, 0, 10, x, y, rgba(200, 0, 0, 0x40));
            m.write(0x00, 140 * 32, 10, x, y, rgba(0, 100, 0, 0x80));
        }
    DisplayRegs d = display_640x448(0x3u);           // EN1 + EN2, MMOD 0, SLBG 0
    d.dispfb[1] = gs_dispfb(140, 10, 0);
    Frame f = compose(m, d);
    CHECK(R(f.at(5, 5)) == (200u * 0x40u + 127u) / 255u);
    CHECK(G(f.at(5, 5)) == (100u * (255u - 0x40u) + 127u) / 255u);
    d.pmode = 0x3u | (1u << 7);                      // SLBG: BGCOLOR under circuit 1
    d.bgcolor = 0x0000FFu;
    f = compose(m, d);
    CHECK(R(f.at(5, 5)) == (200u * 0x40u + 255u * (255u - 0x40u) + 127u) / 255u);
    CHECK(G(f.at(5, 5)) == 0u);
    // A 16-bit display buffer expands RGB5 << 3.
    GsMemory n;
    n.write(0x02, 0, 10, 0, 0, (31u << 10) | (16u << 5) | 1u);
    DisplayRegs e = display_640x448(0x1u | (1u << 5) | (0xFFu << 8));
    e.dispfb[0] = gs_dispfb(0, 10, 0x02);
    f = compose(n, e);
    CHECK(f.at(0, 0) == rgba(8, 128, 248, 0xFF));
}

TEST_CASE("compose: interlaced FRAME mode reads each buffer line for two woven lines; circuits at different DX (model)") {
    GsMemory m;
    fill_rows(m, 0);
    DisplayRegs d = display_640x448(0x1u | (1u << 5) | (0xFFu << 8), 0x3);
    Frame f = compose(m, d);
    CHECK(R(f.at(0, 10)) == 5u);
    CHECK(R(f.at(0, 11)) == 5u);
    CHECK(R(f.at(0, 12)) == 6u);
    // Circuit 2 placed 8 pixels to the right (DX + 32 VCK at MAGH 3): the composed frame is the union.
    DisplayRegs u = display_640x448(0x3u | (1u << 5) | (0xFFu << 8));
    u.display[1] = gs_display(636 + 32, 50, 3, 0, 2559, 447);
    ComposeInfo info;
    f = compose(m, u, &info);
    CHECK(f.width == 648u);
    CHECK(info.circuit_x[1] == 8);
}

TEST_CASE("PNG: the stored-deflate writer round-trips pixels; hash, resample and diff helpers (model)") {
    Frame fr;
    fr.width = 300;
    fr.height = 230; // > 65535 bytes of scanlines: several stored blocks
    fr.rgba.resize(static_cast<std::size_t>(fr.width) * fr.height);
    for (u32 i = 0; i < fr.rgba.size(); ++i) fr.rgba[i] = rgba(i & 0xFFu, (i >> 8) & 0xFFu, (i * 7) & 0xFFu);
    const std::vector<u8> png = encode_png(fr);
    u32 w = 0, h = 0;
    std::vector<u8> rgb;
    REQUIRE(read_stored_png(png, w, h, rgb));
    CHECK(w == 300u);
    CHECK(h == 230u);
    u32 bad = 0;
    for (u32 i = 0; i < fr.rgba.size(); ++i)
        bad += rgb[i * 3] != R(fr.rgba[i]) || rgb[i * 3 + 1] != G(fr.rgba[i]) || rgb[i * 3 + 2] != B(fr.rgba[i]);
    CHECK(bad == 0u);
    Frame g = fr;
    g.rgba[5] ^= 0x10u;
    CHECK(frame_hash(fr) != frame_hash(g));
    const FrameDiff d = diff_frames(fr, g, 8);
    CHECK(d.max_abs == 16u);
    CHECK(d.pixels_over == 1u);
    CHECK(diff_frames(fr, fr, 0).psnr_db == 999.0);
    const Frame r = resample_bilinear(fr, 640, 480);
    CHECK(r.width == 640u);
    CHECK(r.height == 480u);
}

TEST_CASE("self-test scene: deterministic composed output through PATH3 (model)") {
    GsSystem a, b;
    CHECK(run_selftest_scene(a) == run_selftest_scene(b));
    const Frame fa = a.compose_output(), fb = b.compose_output();
    REQUIRE(fa.width == 640u);
    REQUIRE(fa.height == 448u);
    CHECK(frame_hash(fa) == frame_hash(fb));
    CHECK(a.core().stats().primitives == 7u);
    CHECK(a.core().stats().invalid_psm == 0u);
    CHECK(a.core().stats().unknown_reg_writes == 0u);
    CHECK(a.flip_count() == 1u);
}
