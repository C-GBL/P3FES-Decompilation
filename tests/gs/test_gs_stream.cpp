// GS command-stream recording (runtime/include/p3fes/gs/gs_stream.h) and the draw observer hooks of GsCore: a
// recorded sequence of A+D, PACKED, IMAGE, HWREG, CLUT, local-copy and local->host calls replays into a fresh core
// to the same memory and state; an observer never changes what the core computes; with software rasterisation
// off the observer still sees every primitive and local memory receives no pixels. (model)
#include "gs_test_util.h"

#include "p3fes/gs/gs_stream.h"

#include <cstdio>
#include <cstring>
#include <filesystem>

using namespace p3fes;
using namespace p3fes::gs;

namespace {

u128 q4(u32 a, u32 b, u32 c, u32 d) {
    u128 q{};
    q.u32[0] = a;
    q.u32[1] = b;
    q.u32[2] = c;
    q.u32[3] = d;
    return q;
}

u64 xyz(u32 x16, u32 y16, u32 z) { return static_cast<u64>(x16) | (static_cast<u64>(y16) << 16) | (static_cast<u64>(z) << 32); }

// A small scene in the game's shape: CT32 frame, Z16S, an uploaded T8 texture with a CT32 CLUT, bilinear STQ
// triangles with blending, a flat sprite, a PACKED strip, a local copy and a readback.
void scene(GsCore& c) {
    c.write_reg(reg::FRAME_1, (10ull << 16));                                   // FBP 0, FBW 10, CT32
    c.write_reg(reg::ZBUF_1, 280ull | (0xAull << 24));                          // ZBP 280, Z16S
    c.write_reg(reg::XYOFFSET_1, 0);
    c.write_reg(reg::SCISSOR_1, 639ull << 16 | (447ull << 48));
    c.write_reg(reg::TEST_1, 0x5140Bull);                                       // ATE GEQUAL 0x40 FB_ONLY, Z GEQUAL
    c.write_reg(reg::ALPHA_1, 0x44);
    c.write_reg(reg::COLCLAMP, 1);
    c.write_reg(reg::PRMODECONT, 1);
    // Upload a 16x16 T8 texture at TBP 11200 and a 16x16 CT32 CLUT at CBP 11264 (HWREG for part of it).
    c.write_reg(reg::BITBLTBUF, (11200ull << 32) | (2ull << 48) | (0x13ull << 56));
    c.write_reg(reg::TRXPOS, 0);
    c.write_reg(reg::TRXREG, 16ull | (16ull << 32));
    c.write_reg(reg::TRXDIR, 0);
    std::vector<u128> img(16);
    for (u32 i = 0; i < 16; ++i) img[i] = q4(i * 0x04030201u, i * 0x01010101u + 7, 0x80706050u ^ i, 0x0F0E0D0Cu + i);
    c.write_image(img);
    c.write_reg(reg::BITBLTBUF, (11264ull << 32) | (1ull << 48) | (0x00ull << 56));
    c.write_reg(reg::TRXREG, 16ull | (16ull << 32));
    c.write_reg(reg::TRXDIR, 0);
    for (u32 i = 0; i < 128; ++i) c.write_hwreg((static_cast<u64>(0x80000000u | (i * 0x020406u)) << 32) | (0x40000000u | (i * 0x0A0B0Cu)));
    c.write_reg(reg::TEXCLUT, 1);
    c.write_reg(reg::TEX0_1, 11200ull | (2ull << 14) | (0x13ull << 20) | (4ull << 26) | (4ull << 30) | (1ull << 34) |
                                 (11264ull << 37) | (1ull << 61));
    c.write_reg(reg::TEX1_1, (1ull << 5) | (1ull << 6));
    c.write_reg(reg::CLAMP_1, 0);
    // Gouraud, textured (STQ), blended triangle fan.
    c.write_reg(reg::PRIM, 5 | 8 | 16 | 64);
    const float st[4][2] = {{0.1f, 0.1f}, {0.9f, 0.2f}, {0.8f, 0.9f}, {0.2f, 0.7f}};
    const u32 pos[4][2] = {{40, 30}, {300, 50}, {280, 400}, {60, 380}};
    for (int i = 0; i < 4; ++i) {
        u32 s, t;
        std::memcpy(&s, &st[i][0], 4);
        std::memcpy(&t, &st[i][1], 4);
        c.write_reg(reg::ST, s | (static_cast<u64>(t) << 32));
        c.write_reg(reg::RGBAQ, (0x80u + i * 10) | ((0x60u + i * 20) << 8) | ((0x40u + i * 30) << 16) | (0x70ull << 24) |
                                    (static_cast<u64>(0x3F800000u) << 32));
        c.write_reg(reg::XYZ2, xyz(pos[i][0] * 16 + 3, pos[i][1] * 16 + 9, 1000 + i * 500));
    }
    // PACKED tri strip with a GIF tag in between (Q reset).
    c.on_gif_tag();
    c.write_packed(0x0, q4(4 | 8, 0, 0, 0));
    for (int i = 0; i < 5; ++i) {
        c.write_packed(0x1, q4(0x20u + i * 40, 0xF0u - i * 30, 0x10u * i, 0x80));
        c.write_packed(0x5, q4((200 + i * 60) * 16, (100 + (i & 1) * 150) * 16, 3000 + i * 100, 0));
    }
    // Flat sprite with alpha test failing for part of it.
    c.write_reg(reg::PRIM, 6);
    c.write_reg(reg::RGBAQ, 0x30405060ull);
    c.write_reg(reg::XYZ2, xyz(500 * 16, 10 * 16, 9000));
    c.write_reg(reg::XYZ2, xyz(620 * 16, 200 * 16, 9000));
    // Local copy and a readback.
    c.write_reg(reg::BITBLTBUF, 0ull | (10ull << 16) | (5000ull << 32) | (2ull << 48));
    c.write_reg(reg::TRXPOS, 0);
    c.write_reg(reg::TRXREG, 64ull | (32ull << 32));
    c.write_reg(reg::TRXDIR, 2);
    c.write_reg(reg::BITBLTBUF, 0ull | (10ull << 16));
    c.write_reg(reg::TRXPOS, 32ull | (40ull << 16));
    c.write_reg(reg::TRXREG, 8ull | (2ull << 32));
    c.write_reg(reg::TRXDIR, 1);
    std::vector<u128> out(4);
    c.read_image(out);
}

struct CountingObserver final : IGsDrawObserver {
    u64 draws = 0, clut = 0, pixels = 0, copies = 0, reads = 0, xfer = 0;
    void on_draw(const GsRegs&, const GsVertex*, u32, u64 px, u64) override {
        ++draws;
        pixels += px;
    }
    void on_clut_load(u64, u64) override { ++clut; }
    void on_transfer_span(u32, u32, u32, u32, u32, u32 n) override { xfer += n; }
    void on_local_copy(u64, u64, u64) override { ++copies; }
    void on_local_read(u64, u64, u64) override { ++reads; }
};

} // namespace

TEST_CASE("gs stream: a recorded scene replays to the same memory and state (model)") {
    GsCore live;
    // Some prior state the recording must capture: a partly drawn frame and registers.
    live.write_reg(reg::FRAME_1, (10ull << 16));
    live.write_reg(reg::SCISSOR_1, 639ull << 16 | (447ull << 48));
    live.write_reg(reg::TEST_1, 0x30000);
    live.write_reg(reg::PRIM, 6);
    live.write_reg(reg::RGBAQ, 0x80112233ull);
    live.write_reg(reg::XYZ2, xyz(0, 0, 0));
    live.write_reg(reg::XYZ2, xyz(640 * 16, 448 * 16, 0));
    live.write_reg(reg::PRIM, 3);  // a pending vertex in the queue at the start
    live.write_reg(reg::XYZ2, xyz(10 * 16, 10 * 16, 0));

    GsStreamRecorder rec;
    rec.begin(live, 100, 7);
    scene(live);
    DisplayRegs disp;
    disp.pmode = 0x8067;
    rec.end(live, disp, 102, 8);
    CHECK(rec.finished());
    CHECK(rec.event_bytes() > 1000);

    const auto path = std::filesystem::temp_directory_path() / "p3fes_test_gs_stream.p3gs";
    std::string err;
    REQUIRE(rec.write(path, err));
    GsStream s;
    REQUIRE(read_stream(path, s, err));
    std::filesystem::remove(path);
    CHECK(s.start_vblank == 100);
    CHECK(s.end_flip == 8);
    CHECK(s.disp.pmode == 0x8067);

    GsCore replay;
    const ReplayCheck c = replay_software(s, replay, err);
    CHECK(err.empty());
    CHECK(c.events > 150);
    CHECK(c.vram_bytes_differing == 0);
    CHECK(c.state_equal);
    CHECK(std::memcmp(replay.mem().data(), live.mem().data(), kVramBytes) == 0);
}

TEST_CASE("gs draw observer: same memory with and without it; software raster off draws nothing (model)") {
    GsCore a, b, off;
    CountingObserver ob, ob_off;
    b.set_draw_observer(&ob);
    off.set_draw_observer(&ob_off);
    off.set_software_raster(false);
    scene(a);
    scene(b);
    scene(off);
    CHECK(std::memcmp(a.mem().data(), b.mem().data(), kVramBytes) == 0);
    CHECK(ob.draws == a.stats().primitives);
    CHECK(ob.draws == 6);  // 2 fan triangles, 3 strip triangles, 1 sprite
    CHECK(ob.pixels == a.stats().pixels_written);
    CHECK(ob.clut == 1);
    CHECK(ob.copies == 1);
    CHECK(ob.reads == 1);
    CHECK(ob.xfer == 16 * 16 * 2);
    // Without rasterisation the observer sees the same primitives; transfers and the CLUT still happen.
    CHECK(ob_off.draws == ob.draws);
    CHECK(ob_off.pixels == 0);
    CHECK(off.stats().pixels_written == 0);
    CHECK(off.clut() == a.clut());
    // The frame buffer area of the triangles stays empty without rasterisation.
    CHECK(off.mem().read(0x00, 0, 10, 100, 100) == 0);
    CHECK(a.mem().read(0x00, 0, 10, 100, 100) != 0);
}
