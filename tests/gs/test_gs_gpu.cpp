// The GPU back end's front half (GsOpRecorder / OpList, pure C++) and, when this machine has a suitable D3D11
// device, the executor against the software rasteriser (docs/ANALYSIS/25_d3d11_gs_backend.md). The device part is
// skipped (not failed) without a hardware adapter with ROVs and doubles, so the suite runs anywhere. (model)
#include "gs_test_util.h"

#include "p3fes/gs/gs_d3d11.h"
#include "p3fes/gs/gs_ops.h"
#include "p3fes/gs/gs_stream.h"

#include <cstring>
#include <memory>

using namespace p3fes;
using namespace p3fes::gs;

namespace {

u64 xyz(u32 x16, u32 y16, u32 z) { return static_cast<u64>(x16) | (static_cast<u64>(y16) << 16) | (static_cast<u64>(z) << 32); }

// A small game-shaped scene: CT32 frame, Z16S, an uploaded T8 texture + CT32 CLUT, a bilinear STQ Gouraud fan with
// blending and alpha test, a flat sprite, a 16-bit upload.
void scene(GsCore& c) {
    c.write_reg(reg::FRAME_1, 10ull << 16);
    c.write_reg(reg::ZBUF_1, 280ull | (0xAull << 24));
    c.write_reg(reg::SCISSOR_1, 639ull << 16 | (447ull << 48));
    c.write_reg(reg::TEST_1, 0x5140Bull);
    c.write_reg(reg::ALPHA_1, 0x44);
    c.write_reg(reg::COLCLAMP, 1);
    c.write_reg(reg::BITBLTBUF, (11200ull << 32) | (2ull << 48) | (0x13ull << 56));
    c.write_reg(reg::TRXPOS, 0);
    c.write_reg(reg::TRXREG, 16ull | (16ull << 32));
    c.write_reg(reg::TRXDIR, 0);
    std::vector<u128> img(16);
    for (u32 i = 0; i < 16; ++i)
        for (u32 k = 0; k < 4; ++k) img[i].u32[k] = (i * 0x01020304u) ^ (k * 0x11223344u) ^ 0x5A5A5A5Au;
    c.write_image(img);
    c.write_reg(reg::BITBLTBUF, (11264ull << 32) | (1ull << 48));
    c.write_reg(reg::TRXREG, 16ull | (16ull << 32));
    c.write_reg(reg::TRXDIR, 0);
    std::vector<u128> pal(64);
    for (u32 i = 0; i < 64; ++i)
        for (u32 k = 0; k < 4; ++k) pal[i].u32[k] = 0x40000000u + ((i * 4 + k) * 0x00030507u);
    c.write_image(pal);
    c.write_reg(reg::BITBLTBUF, (12000ull << 32) | (1ull << 48) | (0x02ull << 56));  // a CT16 upload
    c.write_reg(reg::TRXREG, 8ull | (2ull << 32));
    c.write_reg(reg::TRXDIR, 0);
    std::vector<u128> s16(2);
    s16[0].u64[0] = 0x123456789ABCDEF0ull;
    s16[1].u64[1] = 0x0FEDCBA987654321ull;
    c.write_image(s16);
    c.write_reg(reg::TEXCLUT, 1);
    c.write_reg(reg::TEX0_1, 11200ull | (2ull << 14) | (0x13ull << 20) | (4ull << 26) | (4ull << 30) | (1ull << 34) | (11264ull << 37) |
                                 (1ull << 61));
    c.write_reg(reg::TEX1_1, (1ull << 5) | (1ull << 6));
    c.write_reg(reg::PRIM, 5 | 8 | 16 | 64);
    const float st[4][2] = {{0.05f, 0.1f}, {0.95f, 0.2f}, {0.8f, 0.9f}, {0.2f, 0.75f}};
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
    c.write_reg(reg::PRIM, 6);
    c.write_reg(reg::RGBAQ, 0x30405060ull);
    c.write_reg(reg::XYZ2, xyz(500 * 16, 10 * 16, 9000));
    c.write_reg(reg::XYZ2, xyz(620 * 16, 200 * 16, 9000));
}

} // namespace

TEST_CASE("gs ops: the recorder sees every primitive, transfer word and CLUT load; lists append with rebased indices (model)") {
    GsCore c;
    GsOpRecorder rec(c, false);
    c.set_software_raster(false);
    c.set_draw_observer(&rec);
    scene(c);
    OpList l;
    rec.take(l);
    CHECK(rec.stats().prims == 3);  // 2 fan triangles + 1 sprite
    CHECK(rec.stats().clut_loads == 1);
    // The CLUT's source was uploaded and never drawn: resolved on the CPU into one version, no GPU load; the list
    // ends by handing that version to the GPU CLUT buffer.
    CHECK(rec.stats().clut_versions == 1);
    CHECK(rec.stats().clut_gpu_loads == 0);
    CHECK(l.clut_tab.size() == 512);
    CHECK(l.ops.back().kind == GpuOpKind::ClutResolve);
    CHECK(rec.stats().scatter_words == 64 + 16);  // T8 16x16 = 64 words, CT16 16 px (neighbours in different words)
    CHECK(rec.stats().page_words == 256);         // the CT32 CLUT upload goes up as a page record
    CHECK(rec.stats().pages == 1);
    CHECK(l.verts.size() == 3 * 2 + 6);
    CHECK(l.prims.size() == 2 + 2);
    // The scattered values are the core's CPU memory (the transfers' result).
    for (std::size_t i = 0; i < l.words.size(); i += 3) {
        const u32 w = l.words[i], m = l.words[i + 1], v = l.words[i + 2];
        CHECK((v & m) == (c.mem().read_u32(w * 4) & m));
    }
    OpList a = l;
    a.append(l);
    CHECK(a.ops.size() == 2 * l.ops.size());
    CHECK(a.verts.size() == 2 * l.verts.size());
    const GpuOp& d0 = l.ops.back();
    const GpuOp& d1 = a.ops.back();
    CHECK(d1.kind == d0.kind);
    if (d0.kind == GpuOpKind::Draw) {
        CHECK(d1.first == d0.first + l.verts.size());
        CHECK(d1.prim_base == d0.prim_base + l.prims.size());
        CHECK(a.cbs[d1.cb].prim_base == d1.prim_base);
    }
}

TEST_CASE("gs d3d11: the executor reproduces the software rasteriser byte for byte in exact mode (model, needs a GPU)") {
    using Microsoft::WRL::ComPtr;
    ComPtr<ID3D11Device> dev;
    ComPtr<ID3D11DeviceContext> ctx;
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 2, D3D11_SDK_VERSION, &dev, nullptr, &ctx))) {
        MESSAGE("no hardware D3D11 device: skipped");
        return;
    }
    const GsD3D11Caps caps = query_caps(dev.Get());
    if (!caps.rov || !caps.doubles || !caps.ext_doubles) {
        MESSAGE("device without ROVs/doubles (" << caps.summary() << "): skipped");
        return;
    }
    GsD3D11Executor gpu;
    std::string err;
    REQUIRE_MESSAGE(gpu.init(dev.Get(), ctx.Get(), true, true, err), err);

    GsCore sw;
    scene(sw);
    GsCore fe;
    GsOpRecorder rec(fe, false);
    fe.set_software_raster(false);
    fe.set_draw_observer(&rec);
    scene(fe);
    OpList l;
    rec.take(l);
    std::vector<u8> zeros(kVramBytes, 0), out;
    // Twice through the upload ring's slots: every execution must give the same memory.
    for (int run = 0; run < 4; ++run) {
        gpu.reset(zeros.data(), std::array<u16, 512>{});
        gpu.execute(l);
        gpu.readback_vram(out);
        u64 diff = 0;
        for (u32 i = 0; i < kVramBytes; ++i) diff += out[i] != sw.mem().data()[i];
        CHECK_MESSAGE(diff == 0, "run " << run << ": " << diff << " bytes differ");
    }
    // The GPU CRTC pass equals gs::compose.
    DisplayRegs d;
    d.pmode = 0x8067;
    d.smode2 = 1;
    d.dispfb[0] = 10ull << 9;
    d.dispfb[1] = (10ull << 9) | (1ull << 43);
    d.display[0] = 0x001BF9FF0183227Cull;
    d.display[1] = 0x001BE9FF0183227Cull;
    Frame g;
    REQUIRE(gpu.compose_readback(d, g));
    const Frame c = compose(sw.mem(), d);
    REQUIRE(g.width == c.width);
    REQUIRE(g.height == c.height);
    u64 px = 0;
    for (std::size_t i = 0; i < g.rgba.size(); ++i) px += (g.rgba[i] & 0xFFFFFFu) != (c.rgba[i] & 0xFFFFFFu);
    CHECK(px == 0);
}

namespace {

// After scene(): a sprite drawn over the CLUT's 16x16 CT32 block (FBP 352 = block 11264), then the same TEX0 with
// CLD 1 again: the CLUT buffer is reloaded from rendered pixels (on the GPU path: from GPU memory only).
void clut_from_draw(GsCore& c) {
    c.write_reg(reg::FRAME_1, 352ull | (1ull << 16));
    c.write_reg(reg::SCISSOR_1, 63ull << 16 | (63ull << 48));
    c.write_reg(reg::TEST_1, 0x30000ull);  // ZTE, ZTST ALWAYS, no alpha test
    c.write_reg(reg::PRIM, 6);
    c.write_reg(reg::RGBAQ, 0x7F31A2C4ull);
    c.write_reg(reg::XYZ2, xyz(0, 0, 100));
    c.write_reg(reg::XYZ2, xyz(16 * 16, 16 * 16, 100));
    c.write_reg(reg::TEX0_1, 11200ull | (2ull << 14) | (0x13ull << 20) | (4ull << 26) | (4ull << 30) | (1ull << 34) | (11264ull << 37) |
                                 (1ull << 61));
}

// A local -> local copy (TRXDIR 2) of the drawn 16x16 block to block 12800: its source holds draw output, so the CPU
// copy of a GPU front end copies stale (uploaded) pixels and only the GPU's copy is right.
void copy_drawn(GsCore& c) {
    c.write_reg(reg::BITBLTBUF, 11264ull | (1ull << 16) | (12800ull << 32) | (1ull << 48));
    c.write_reg(reg::TRXPOS, 0);
    c.write_reg(reg::TRXREG, 16ull | (16ull << 32));
    c.write_reg(reg::TRXDIR, 2);
}

// A line (no GPU path draws points/lines) and a sprite.
void line_scene(GsCore& c) {
    c.write_reg(reg::FRAME_1, 10ull << 16);
    c.write_reg(reg::ZBUF_1, 280ull | (0xAull << 24) | (1ull << 32));
    c.write_reg(reg::SCISSOR_1, 639ull << 16 | (447ull << 48));
    c.write_reg(reg::TEST_1, 0x30000ull);
    c.write_reg(reg::PRIM, 1 | 8);  // line, Gouraud
    c.write_reg(reg::RGBAQ, 0x80102030ull);
    c.write_reg(reg::XYZ2, xyz(10 * 16, 20 * 16, 0));
    c.write_reg(reg::RGBAQ, 0x80F0E0D0ull);
    c.write_reg(reg::XYZ2, xyz(200 * 16 + 5, 90 * 16 + 11, 0));
    c.write_reg(reg::PRIM, 6);
    c.write_reg(reg::RGBAQ, 0x30405060ull);
    c.write_reg(reg::XYZ2, xyz(100 * 16, 100 * 16, 0));
    c.write_reg(reg::XYZ2, xyz(140 * 16, 130 * 16, 0));
}

} // namespace

TEST_CASE("gs ops: the sync hook fires at local reads and unsupported primitives; a hand-back makes the core draw (model)") {
    GsCore sw;
    line_scene(sw);
    GsCore fe;
    GsOpRecorder rec(fe, false);
    fe.set_software_raster(false);
    fe.set_draw_observer(&rec);
    int unsupported = 0, reads = 0;
    rec.sync_hook = [&](GpuSyncReason why) {
        if (why == GpuSyncReason::LocalRead) {
            ++reads;
            return;
        }
        ++unsupported;
        OpList l;
        rec.take(l);  // allowed inside the hook
        fe.set_draw_observer(nullptr);
        fe.set_software_raster(true);  // the core draws this primitive and every later one
    };
    line_scene(fe);
    CHECK(unsupported == 1);
    CHECK(rec.stats().unsupported == 1);
    CHECK(rec.stats().prims == 1);  // the line; the sprite after the hand-back went to the core, not the recorder
    CHECK(std::memcmp(fe.mem().data(), sw.mem().data(), kVramBytes) == 0);
    u64 drawn = 0;
    for (u32 i = 0; i < kVramBytes; ++i) drawn += sw.mem().data()[i] != 0;
    CHECK(drawn > 0);
    // A local -> host transfer start reaches the hook before GsCore serves it from CPU memory.
    GsCore rd;
    GsOpRecorder rr(rd, false);
    rd.set_software_raster(false);
    rd.set_draw_observer(&rr);
    rr.sync_hook = [&](GpuSyncReason why) { reads += why == GpuSyncReason::LocalRead ? 1 : 0; };
    rd.write_reg(reg::BITBLTBUF, 10ull << 16);
    rd.write_reg(reg::TRXREG, 8ull | (8ull << 32));
    rd.write_reg(reg::TRXDIR, 1);
    CHECK(reads == 1);
    CHECK(rr.stats().local_reads == 1);
}

TEST_CASE("gs d3d11: the offscreen renderer (no window) syncs GS memory and the CLUT byte-identical to software (model, needs a GPU)") {
    {
        using Microsoft::WRL::ComPtr;
        ComPtr<ID3D11Device> dev;
        ComPtr<ID3D11DeviceContext> ctx;
        const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
        if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 2, D3D11_SDK_VERSION, &dev, nullptr, &ctx))) {
            MESSAGE("no hardware D3D11 device: skipped");
            return;
        }
        const GsD3D11Caps caps = query_caps(dev.Get());
        if (!caps.rov || !caps.doubles || !caps.ext_doubles) {
            MESSAGE("device without ROVs/doubles (" << caps.summary() << "): skipped");
            return;
        }
    }
    GsD3D11Renderer r;
    GsD3D11Renderer::Options o;
    o.exact = true;
    o.vsync = false;
    o.sync_timeout_s = 120.0;
    o.max_queued = 1;  // the second list is appended when the thread has not picked up the first yet
    std::string why;
    REQUIRE_MESSAGE(r.start(nullptr, o, why), why);
    CHECK(r.offscreen());

    GsCore sw;
    scene(sw);
    clut_from_draw(sw);
    copy_drawn(sw);
    GsCore fe;
    GsOpRecorder rec(fe, false);
    fe.set_software_raster(false);
    fe.set_draw_observer(&rec);
    scene(fe);
    OpList a;
    rec.take(a);
    clut_from_draw(fe);
    copy_drawn(fe);
    OpList b;
    rec.take(b);
    CHECK(rec.stats().local_copies == 1);
    // The second load reads a block the sprite drew: the GPU loads it from GPU memory.
    CHECK(rec.stats().clut_versions == 1);
    CHECK(rec.stats().clut_gpu_loads == 1);
    // The front end's CLUT came from its CPU memory, which holds no rendered pixels: it differs from software's.
    CHECK(fe.clut() != sw.clut());
    r.submit(std::move(a), DisplayRegs{});
    r.submit(std::move(b), DisplayRegs{});
    r.submit(OpList{}, DisplayRegs{});
    std::vector<u8> vram;
    std::array<u16, 512> clut{};
    REQUIRE(r.sync_vram(vram, &clut));
    REQUIRE(vram.size() == kVramBytes);
    u64 diff = 0;
    for (u32 i = 0; i < kVramBytes; ++i) diff += vram[i] != sw.mem().data()[i];
    CHECK_MESSAGE(diff == 0, diff << " bytes differ");
    CHECK(clut == sw.clut());
    const auto st = r.stats();
    CHECK(st.submitted == 3);
    CHECK(st.presented == 0);
    CHECK(st.skipped_presents == 0);
    r.stop();
    CHECK(!r.running());
}

TEST_CASE("gs d3d11: stop() joins a render thread that is slow to finish; the renderer can then be destroyed (model, needs a GPU)") {
    {
        using Microsoft::WRL::ComPtr;
        ComPtr<ID3D11Device> dev;
        ComPtr<ID3D11DeviceContext> ctx;
        const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
        if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 2, D3D11_SDK_VERSION, &dev, nullptr, &ctx))) {
            MESSAGE("no hardware D3D11 device: skipped");
            return;
        }
        if (!query_caps(dev.Get()).rov) {
            MESSAGE("device without ROVs: skipped");
            return;
        }
    }
    // The render thread uses the renderer object until it exits; before 2026-10-25 stop() detached it after 3 s and
    // the owner then destroyed the object under it (a use-after-free on a loaded machine).
    auto r = std::make_unique<GsD3D11Renderer>();
    GsD3D11Renderer::Options o;
    o.vsync = false;
    o.sync_timeout_s = 120.0;
    o.test_stop_delay_ms = 3500;  // longer than stop()'s first wait
    std::string why;
    REQUIRE_MESSAGE(r->start(nullptr, o, why), why);
    GsCore fe;
    GsOpRecorder rec(fe, false, false);
    fe.set_software_raster(false);
    fe.set_draw_observer(&rec);
    scene(fe);
    OpList l;
    rec.take(l);
    r->submit(std::move(l), DisplayRegs{});
    r->stop();
    CHECK(!r->running());
    r.reset();  // nothing may touch the object after this
}