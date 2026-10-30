// Synthetic self-test scene (see gs_selftest.h). Register values of the setup part are the ones topic 10 reads from
// SkyStart (B-41, B-49..B-51); the drawn content is invented.
#include "p3fes/gs/gs_selftest.h"

#include "p3fes/gs/gif_builder.h"

#include <array>

namespace p3fes::gs {

namespace {
constexpr u32 kOfx = 2048u - 320u, kOfy = 2048u - 224u; // XYOFFSET of mode 82 (B-50), pixels
constexpr u32 X(u32 px) { return (kOfx + px) * 16u; }
constexpr u32 Y(u32 py) { return (kOfy + py) * 16u; }
} // namespace

std::size_t run_selftest_scene(GsSystem& gs) {
    GsPrivRegs& p = gs.priv();
    const u32 b = GsPrivRegs::kBase;
    // sceGsResetGraph + sceGsPutDispEnv + the flicker-free interlace patch (10 §2.5, §2.7, §2.10).
    p.write64(b + priv::CSR, 0x200);
    p.write64(b + priv::PMODE, 0x8067);
    p.write64(b + priv::SMODE2, 0x1);
    p.write64(b + priv::DISPFB2, gs_dispfb(0, 10, 0, 0, 1));
    p.write64(b + priv::DISPLAY2, 0x001BE9FF0183227Cull);
    p.write64(b + priv::BGCOLOR, 0);
    p.write64(b + priv::DISPFB1, gs_dispfb(0, 10, 0));
    p.write64(b + priv::DISPLAY1, 0x001BF9FF0183227Cull);

    GifBuilder g;
    // skyInitialClear (B-41): clears all of local memory.
    g.tag(1, true, 0, 12, 0xEEEEEEEEEEEEull);
    for (const auto& [r, v] : std::initializer_list<std::pair<u8, u64>>{
             {reg::ALPHA_1, 0},
             {reg::FRAME_1, 0x100000},
             {reg::SCISSOR_1, 0x03FF000003FF0000ull},
             {reg::PRMODECONT, 1},
             {reg::TEST_1, 0x30000},
             {reg::XYOFFSET_1, 0},
             {reg::ZBUF_1, 0x10A000100ull},
             {reg::PRIM, 6},
             {reg::RGBAQ, 0},
             {reg::XYZ2, 0},
             {reg::XYZ2, 0x3FFFFFFF}}) {
        g.raw(v, r);
    }
    g.raw(0, reg::NOP); // 12th register of the tag (the real packet has 13 qwords)
    // Draw environment draw1 (B-50) drawing into the displayed buffer FBP 0.
    g.ad({{reg::FRAME_1, gs_frame(0, 10, 0)},
          {reg::ZBUF_1, gs_zbuf(280, 0xA, false)},
          {reg::XYOFFSET_1, gs_xyoffset(kOfx * 16u, kOfy * 16u)},
          {reg::SCISSOR_1, gs_scissor(0, 639, 0, 447)},
          {reg::PRMODECONT, 1},
          {reg::COLCLAMP, 1},
          {reg::DTHE, 0},
          {reg::TEST_1, gs_test(false, 0, 0, 0, false, false, true, 1)}});
    // Background and a blue panel.
    g.ad({{reg::PRIM, gs_prim(6)},
          {reg::RGBAQ, gs_rgbaq(0, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(X(0), Y(0), 0)},
          {reg::XYZ2, gs_xyz(X(640), Y(448), 0)},
          {reg::RGBAQ, gs_rgbaq(0x10, 0x88, 0xE8, 0x80)},
          {reg::XYZ2, gs_xyz(X(48), Y(48), 0)},
          {reg::XYZ2, gs_xyz(X(592), Y(400), 0)}});
    // Gouraud triangle.
    g.ad({{reg::PRIM, gs_prim(3, true)},
          {reg::RGBAQ, gs_rgbaq(255, 0, 0, 0x80)},
          {reg::XYZ2, gs_xyz(X(80), Y(360), 0)},
          {reg::RGBAQ, gs_rgbaq(0, 255, 0, 0x80)},
          {reg::XYZ2, gs_xyz(X(200), Y(120), 0)},
          {reg::RGBAQ, gs_rgbaq(0, 0, 255, 0x80)},
          {reg::XYZ2, gs_xyz(X(320), Y(360), 0)}});
    // A 16x16 PSMT8 texture with a 256-entry CT32 CLUT (CSM1), uploaded at blocks 0x2BE0 / 0x2C00.
    std::array<u8, 256> tex8{};
    for (u32 y = 0; y < 16; ++y)
        for (u32 x = 0; x < 16; ++x) tex8[y * 16 + x] = static_cast<u8>(((x / 4) + (y / 4)) & 1 ? 1 : 2);
    std::array<u32, 256> clut{};
    clut[1] = rgba(250, 250, 250, 0x80);
    clut[2] = rgba(240, 120, 20, 0x80);
    // CSM1 stores entry i at the position with index bits 3 and 4 swapped.
    std::array<u32, 256> clut_mem{};
    for (u32 i = 0; i < 256; ++i) clut_mem[(i & ~0x18u) | ((i & 0x08u) << 1) | ((i & 0x10u) >> 1)] = clut[i];
    g.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0x2BE0, 2, 0x13)},
          {reg::TRXPOS, gs_trxpos(0, 0, 0, 0)},
          {reg::TRXREG, gs_trxreg(16, 16)},
          {reg::TRXDIR, 0}});
    g.image(tex8.data(), tex8.size());
    g.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0x2C00, 1, 0x00)},
          {reg::TRXPOS, gs_trxpos(0, 0, 0, 0)},
          {reg::TRXREG, gs_trxreg(16, 16)},
          {reg::TRXDIR, 0}});
    g.image(clut_mem.data(), sizeof(clut_mem));
    g.ad({{reg::TEXFLUSH, 0},
          {reg::TEX0_1, gs_tex0(0x2BE0, 2, 0x13, 4, 4, true, 1, 0x2C00, 0, 0, 0, 1)},
          {reg::TEX1_1, 0},
          {reg::CLAMP_1, 0},
          {reg::PRIM, gs_prim(6, false, true, false, false, true)},
          {reg::RGBAQ, gs_rgbaq(0x80, 0x80, 0x80, 0x80)},
          {reg::UV, gs_uv(0, 0)},
          {reg::XYZ2, gs_xyz(X(360), Y(120), 0)},
          {reg::UV, gs_uv(16 * 16, 16 * 16)},
          {reg::XYZ2, gs_xyz(X(552), Y(312), 0)}});
    // An 8x8 PSMT4 texture whose 16-entry CT32 CLUT is loaded into cache slots 16..31 (CSA 1), tiled 4x by REPEAT.
    std::array<u8, 32> tex4{};
    for (u32 i = 0; i < 64; ++i) {
        const u32 x = i % 8, y = i / 8;
        const u8 v = static_cast<u8>((x == y || x + y == 7) ? 1 : 0);
        tex4[i / 2] = static_cast<u8>(tex4[i / 2] | (v << ((i & 1) * 4)));
    }
    std::array<u32, 16> clut4{};
    clut4[0] = rgba(20, 20, 60, 0x80);
    clut4[1] = rgba(255, 230, 40, 0x80);
    g.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0x2C40, 2, 0x14)},
          {reg::TRXPOS, gs_trxpos(0, 0, 0, 0)},
          {reg::TRXREG, gs_trxreg(8, 8)},
          {reg::TRXDIR, 0}});
    g.image(tex4.data(), tex4.size());
    g.ad({{reg::BITBLTBUF, gs_bitbltbuf(0, 0, 0, 0x2C80, 1, 0x00)},
          {reg::TRXPOS, gs_trxpos(0, 0, 0, 0)},
          {reg::TRXREG, gs_trxreg(8, 2)},
          {reg::TRXDIR, 0}});
    g.image(clut4.data(), sizeof(clut4));
    g.ad({{reg::TEX0_1, gs_tex0(0x2C40, 2, 0x14, 3, 3, false, 1, 0x2C80, 0, 0, 1, 1)},
          {reg::PRIM, gs_prim(6, false, true, false, false, true)},
          {reg::UV, gs_uv(0, 0)},
          {reg::XYZ2, gs_xyz(X(80), Y(380), 0)},
          {reg::UV, gs_uv(32 * 16, 4 * 16)},
          {reg::XYZ2, gs_xyz(X(336), Y(392), 0)}});
    // Alpha-blended overlay, ALPHA_1 = 0x44 (Cs - Cd) * As + Cd with As = 0x40.
    g.ad({{reg::ALPHA_1, gs_alpha(0, 1, 0, 1)},
          {reg::PRIM, gs_prim(6, false, false, false, true)},
          {reg::RGBAQ, gs_rgbaq(255, 255, 255, 0x40)},
          {reg::XYZ2, gs_xyz(X(260), Y(200), 0)},
          {reg::XYZ2, gs_xyz(X(420), Y(280), 0)}});
    return gs.gif().path3(g.qwords());
}

} // namespace p3fes::gs
