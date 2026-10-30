// p3fes_gsreplay: replay a recorded GS command stream (p3fes --gs-record, runtime/include/p3fes/gs/gs_stream.h)
// through the software GS (the oracle) and through the D3D11 GS back end (p3fes/gs/gs_d3d11.h, the same executor the
// windowed host uses), then compare the two local memories and the CRTC pictures
// (docs/ANALYSIS/25_d3d11_gs_backend.md §6-7).
//
//   p3fes_gsreplay STREAM|--synthetic [--out DIR] [--warp] [--no-rov] [--exact] [--repeat N] [--tolerance N]
//
// The front end is a GsCore with software rasterisation off and a GsOpRecorder (gs_ops.h) -- the op list the EE
// fiber hands to the render thread. Each repeat resets GPU memory and executes the list again; the tool warns when
// two executions differ (the repeatability check for buffer reuse). A diagnostic tool: never used by gates.
#include "../gs_raster.h"
#include "p3fes/gs/gs_d3d11.h"
#include "p3fes/gs/gs_ops.h"
#include "p3fes/gs/gs_output.h"
#include "p3fes/gs/gs_stream.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <d3d11.h>
#include <wrl/client.h>
#undef DrawState  // winuser.h macro; gs::detail::DrawState is meant

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using Microsoft::WRL::ComPtr;
using namespace p3fes;
using namespace p3fes::gs;

namespace {

double now_s() { return std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count(); }

// The software oracle's per-frame-buffer pixel counts (which buffers the comparison decodes) and raster time.
struct OracleObserver final : IGsDrawObserver {
    std::map<std::tuple<u32, u32, u32>, u64> fb_pixels;  // (FBP blocks, FBW, PSM) -> pixels written
    std::map<std::tuple<u32, u32, u32>, u64> z_pixels;   // (ZBP blocks, FBW, ZPSM)
    u64 ns = 0, prims = 0;
    void on_draw(const GsRegs& r, const GsVertex*, u32, u64 pixels, u64 t) override {
        const detail::DrawState ds = detail::decode_draw_state(r);
        fb_pixels[{ds.fbp, ds.fbw, ds.fpsm}] += pixels;
        if (!ds.zmsk) z_pixels[{ds.zbp, ds.fbw, ds.zpsm}] += pixels;
        ns += t;
        ++prims;
    }
};

Frame decode(const GsMemory& m, u32 psm, u32 bp, u32 bw, u32 w, u32 h) {
    Frame f;
    f.width = w;
    f.height = h;
    f.rgba.resize(static_cast<std::size_t>(w) * h);
    for (u32 y = 0; y < h; ++y)
        for (u32 x = 0; x < w; ++x) {
            u32 v = m.read(psm, bp, bw, x, y);
            if (psm_bits(psm) == 16)
                v = ((v & 0x1Fu) << 3) | (((v >> 5) & 0x1Fu) << 11) | (((v >> 10) & 0x1Fu) << 19) | ((v & 0x8000u) ? 0x80000000u : 0u);
            f.rgba[static_cast<std::size_t>(y) * w + x] = v;
        }
    return f;
}

void print_diff(const char* what, const FrameDiff& d) {
    std::printf("  %-34s pixels %llu, differing (any RGB > tol) %llu (%.4f%%), max |d| %u, mean |d| %.4f, PSNR %.2f dB\n", what,
                static_cast<unsigned long long>(d.pixels), static_cast<unsigned long long>(d.pixels_over),
                d.pixels ? 100.0 * static_cast<double>(d.pixels_over) / static_cast<double>(d.pixels) : 0.0, d.max_abs, d.mean_abs,
                d.psnr_db);
}

int usage() {
    std::fprintf(stderr, "usage: p3fes_gsreplay STREAM|--synthetic [--out DIR] [--warp] [--no-rov] [--exact] [--repeat N] [--tolerance N] [--gpu-profile]\n");
    return 2;
}

bool synthetic_stream(const std::filesystem::path& out, std::string& err) {
    // One large Gouraud triangle with varying alpha, blended, and a flat sprite, recorded in-process: a quick check
    // of the attribute paths without a game recording.
    GsCore c;
    GsStreamRecorder r;
    r.begin(c, 0, 0);
    c.write_reg(reg::FRAME_1, 10ull << 16);
    c.write_reg(reg::ZBUF_1, 280ull | (0xAull << 24));
    c.write_reg(reg::SCISSOR_1, 639ull << 16 | (447ull << 48));
    c.write_reg(reg::TEST_1, 0x30000);
    c.write_reg(reg::ALPHA_1, 0x44);
    c.write_reg(reg::COLCLAMP, 1);
    c.write_reg(reg::PRIM, 3 | 8 | 64);
    const u32 px[3][2] = {{0, 0}, {640, 0}, {0, 448}};
    for (int i = 0; i < 3; ++i) {
        c.write_reg(reg::RGBAQ, (10u + i * 100) | ((200u - i * 90) << 8) | ((30u + i * 50) << 16) | (static_cast<u64>(0x20 + i * 0x30) << 24));
        c.write_reg(reg::XYZ2, (px[i][0] * 16) | ((px[i][1] * 16) << 16) | (static_cast<u64>(1000 + i * 20000) << 32));
    }
    c.write_reg(reg::PRIM, 6);
    c.write_reg(reg::RGBAQ, 0x80405060ull);
    c.write_reg(reg::XYZ2, (400u * 16) | ((300u * 16) << 16));
    c.write_reg(reg::XYZ2, (600u * 16 + 7) | ((440u * 16 + 3) << 16));
    DisplayRegs d;
    d.pmode = 0x8067;  // the game's two-circuit flicker filter
    d.smode2 = 1;
    d.dispfb[0] = 10ull << 9;
    d.dispfb[1] = (10ull << 9) | (1ull << 43);
    d.display[0] = 0x001BF9FF0183227Cull;
    d.display[1] = 0x001BE9FF0183227Cull;
    r.end(c, d, 1, 1);
    return r.write(out, err);
}

} // namespace

int main(int argc, char** argv) {
    std::setvbuf(stdout, nullptr, _IONBF, 0);
    if (argc < 2) return usage();
    std::filesystem::path stream_path = argv[1], out_dir;
    bool warp = false, rov = true, exact = false, debug = false, gpu_profile = false;
    int repeat = 5;
    u32 tol = 0;
    for (int i = 2; i < argc; ++i) {
        const std::string a = argv[i];
        if (a == "--out" && i + 1 < argc) out_dir = argv[++i];
        else if (a == "--warp") warp = true;
        else if (a == "--no-rov") rov = false;
        else if (a == "--exact") exact = true;
        else if (a == "--gpu-debug") debug = true;
        else if (a == "--gpu-profile") gpu_profile = true;
        else if (a == "--repeat" && i + 1 < argc) repeat = std::max(1, std::atoi(argv[++i]));
        else if (a == "--tolerance" && i + 1 < argc) tol = static_cast<u32>(std::atoi(argv[++i]));
        else return usage();
    }
    GsStream s;
    std::string err;
    if (stream_path == "--synthetic") {
        const auto tmp = std::filesystem::temp_directory_path() / "p3fes_gsreplay_synthetic.p3gs";
        if (!synthetic_stream(tmp, err)) {
            std::fprintf(stderr, "gsreplay: %s\n", err.c_str());
            return 1;
        }
        stream_path = tmp;
    }
    if (!read_stream(stream_path, s, err)) {
        std::fprintf(stderr, "gsreplay: %s\n", err.c_str());
        return 1;
    }
    std::printf("gsreplay: %s: vblank %llu..%llu, flip %llu..%llu, %zu event bytes\n", stream_path.string().c_str(),
                static_cast<unsigned long long>(s.start_vblank), static_cast<unsigned long long>(s.end_vblank),
                static_cast<unsigned long long>(s.start_flip), static_cast<unsigned long long>(s.end_flip), s.events.size());

    // 1. Software oracle (and the recording's own check).
    GsCore sw;
    OracleObserver oracle;
    sw.set_draw_observer(&oracle);
    const double t_sw0 = now_s();
    const ReplayCheck chk = replay_software(s, sw, err);
    const double t_sw = now_s() - t_sw0;
    std::printf("software: %zu events, %llu primitives, %llu pixels written, raster %.2f ms of %.2f ms replay; recording check: %s "
                "(VRAM bytes differing from the recorded end %llu, state %s)\n",
                chk.events, static_cast<unsigned long long>(oracle.prims), static_cast<unsigned long long>(sw.stats().pixels_written),
                static_cast<double>(oracle.ns) * 1e-6, t_sw * 1e3, chk.ok() ? "OK" : "MISMATCH",
                static_cast<unsigned long long>(chk.vram_bytes_differing), chk.state_equal ? "equal" : "differs");
    if (!err.empty()) std::fprintf(stderr, "gsreplay: %s\n", err.c_str());

    // 2. D3D11.
    ComPtr<ID3D11Device> dev;
    ComPtr<ID3D11DeviceContext> ctx;
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
    if (FAILED(D3D11CreateDevice(nullptr, warp ? D3D_DRIVER_TYPE_WARP : D3D_DRIVER_TYPE_HARDWARE, nullptr, debug ? D3D11_CREATE_DEVICE_DEBUG : 0, levels, 2, D3D11_SDK_VERSION,
                                 &dev, nullptr, &ctx))) {
        std::fprintf(stderr, "gsreplay: D3D11CreateDevice failed\n");
        return 1;
    }
    GsD3D11Executor gpu;
    if (!gpu.init(dev.Get(), ctx.Get(), rov, exact, err)) {
        std::fprintf(stderr, "gsreplay: D3D11: %s (%s)\n", err.c_str(), gpu.caps().summary().c_str());
        return 1;
    }
    std::printf("d3d11: %s%s; pixel shader %s %s %s\n", gpu.caps().summary().c_str(), warp ? " (WARP)" : "", gpu.ps_target(),
                gpu.rov() ? "ROV (one draw per state run)" : "plain UAV (draws split where primitives overlap)",
                exact ? "exact attributes" : "interpolated attributes");
    // Front end: the GS register/queue model without rasterisation, recording the op list. First the core alone (no
    // observer) as the baseline the recorder adds to.
    double core_ms = 1e30;
    for (int it = 0; it < repeat; ++it) {
        GsCore fe;
        load_stream_start(s, fe);
        fe.set_software_raster(false);
        const double t0 = now_s();
        replay_events(s, fe, err);
        core_ms = std::min(core_ms, (now_s() - t0) * 1e3);
    }
    OpList ops;
    GpuRecorderStats rs;
    double fe_ms = 1e30;
    for (int it = 0; it < repeat; ++it) {
        GsCore fe;
        GsOpRecorder r(fe, !gpu.rov(), exact);
        // Steady state, as the host records with recycled lists: the previous run's storage, cleared.
        OpList storage = std::move(ops);
        storage.clear();
        std::swap(r.list(), storage);
        load_stream_start(s, fe);
        fe.set_software_raster(false);
        fe.set_draw_observer(&r);
        const double t0 = now_s();
        replay_events(s, fe, err);
        r.take(ops);
        fe_ms = std::min(fe_ms, (now_s() - t0) * 1e3);
        rs = r.stats();
    }
    std::printf("front end: %llu primitives (%llu triangles, %llu sprites, %llu unsupported point/line) -> %zu ops: %llu draws "
                "(%llu state breaks, %llu overlap breaks), %llu merged, %llu CLUT loads (%llu CPU-resolved into %zu versions, %llu GPU loads), %llu scatters / %llu words, %llu pages / %llu words, %llu local copies, %llu "
                "local reads; %zu vertices, %.2f ms (best of %d)\n",
                static_cast<unsigned long long>(rs.prims), static_cast<unsigned long long>(rs.tris), static_cast<unsigned long long>(rs.sprites),
                static_cast<unsigned long long>(rs.unsupported), ops.ops.size(), static_cast<unsigned long long>(rs.draws),
                static_cast<unsigned long long>(rs.state_breaks), static_cast<unsigned long long>(rs.overlap_breaks),
                static_cast<unsigned long long>(rs.merged_draws), static_cast<unsigned long long>(rs.clut_loads),
                static_cast<unsigned long long>(rs.clut_versions), ops.clut_tab.size() / 512,
                static_cast<unsigned long long>(rs.clut_gpu_loads), static_cast<unsigned long long>(rs.scatters),
                static_cast<unsigned long long>(rs.scatter_words), static_cast<unsigned long long>(rs.pages),
                static_cast<unsigned long long>(rs.page_words), static_cast<unsigned long long>(rs.local_copies),
                static_cast<unsigned long long>(rs.local_reads), ops.verts.size(), fe_ms, repeat);
    double gpu_ms = 1e30, submit_ms = 1e30, issue_ms = 1e30;
    std::vector<u8> gpu_mem, first_mem;
    for (int it = 0; it < repeat; ++it) {
        gpu.reset(s.start_vram.data(), s.start_state.clut);
        const double t0 = now_s();
        const double g = gpu.execute_timed(ops, &issue_ms);
        submit_ms = std::min(submit_ms, (now_s() - t0) * 1e3);
        gpu_ms = std::min(gpu_ms, g);
        if (it == 0) gpu.readback_vram(first_mem);
    }
    gpu.readback_vram(gpu_mem);
    if (debug) std::printf("gpu-debug: %llu debug-layer errors/warnings\n", static_cast<unsigned long long>(drain_debug_messages(dev.Get(), "gsreplay:")));
    if (gpu_mem != first_mem) {
        u64 n = 0;
        for (u32 i = 0; i < kVramBytes; ++i) n += gpu_mem[i] != first_mem[i];
        std::printf("WARNING: GPU runs are not repeatable: %llu VRAM bytes differ between run 1 and run %d\n",
                    static_cast<unsigned long long>(n), repeat);
    } else if (repeat > 1) {
        std::printf("repeatability: %d executions of the op list gave identical GPU memory\n", repeat);
    }
    std::printf("timing: software rasterisation %.2f ms | D3D11: front end %.2f ms (core alone %.2f, recorder %.2f), GPU %.3f ms, "
                "issue (CPU, execute) %.3f ms, submit+wait %.2f ms (best of %d)\n",
                static_cast<double>(oracle.ns) * 1e-6, fe_ms, core_ms, fe_ms - core_ms, gpu_ms, issue_ms, submit_ms, repeat);

    if (gpu_profile) {
        // GPU time per op kind (timestamps after every op), best total of `repeat` runs.
        GpuOpProfile best;
        best.total_ms = 1e30;
        for (int it = 0; it < repeat; ++it) {
            gpu.reset(s.start_vram.data(), s.start_state.clut);
            GpuOpProfile p;
            if (gpu.execute_profiled(ops, p) && p.total_ms < best.total_ms) best = p;
        }
        static const char* kKind[kGpuOpKinds] = {"draw", "scatter", "pages", "clut", "copy", "clut-resolve"};
        std::printf("gpu profile: total %.3f ms, upload %.3f ms", best.total_ms, best.upload_ms);
        for (unsigned k = 0; k < kGpuOpKinds; ++k)
            if (best.count[k])
                std::printf(", %s %llu ops in %llu calls %.3f ms (%.1f us/call)", kKind[k], static_cast<unsigned long long>(best.count[k]),
                            static_cast<unsigned long long>(best.calls[k]), best.ms[k], 1000.0 * best.ms[k] / static_cast<double>(best.calls[k]));
        std::printf("\n");
        gpu.reset(s.start_vram.data(), s.start_state.clut);
        gpu.execute(ops);
        gpu.readback_vram(gpu_mem);
    }

    // 3. Compare.
    GsMemory gm;
    std::memcpy(gm.data(), gpu_mem.data(), kVramBytes);
    u64 bytes_diff = 0;
    for (u32 i = 0; i < kVramBytes; ++i) bytes_diff += gm.data()[i] != sw.mem().data()[i];
    std::printf("compare: VRAM bytes differing %llu of %u (%.4f%%)\n", static_cast<unsigned long long>(bytes_diff), kVramBytes,
                100.0 * static_cast<double>(bytes_diff) / kVramBytes);
    for (const auto& [key, px] : oracle.fb_pixels) {
        const auto [fbp, fbw, psm] = key;
        if (px == 0 || fbw == 0) continue;
        const bool screen = fbp == 0 || fbp == 140 * 32;
        const u32 w = std::min<u32>(fbw * 64u, 1024u), h = screen ? 448u : std::min<u32>(512u, w);
        const Frame a = decode(sw.mem(), psm, fbp, fbw, w, h), b = decode(gm, psm, fbp, fbw, w, h);
        Frame d;
        const FrameDiff fd = diff_frames(a, b, tol, &d);
        u64 adiff = 0;
        u32 amax = 0;
        for (std::size_t i = 0; i < a.rgba.size(); ++i) {
            const int x = static_cast<int>(a.rgba[i] >> 24), y = static_cast<int>(b.rgba[i] >> 24);
            if (x != y) {
                ++adiff;
                amax = std::max<u32>(amax, static_cast<u32>(std::abs(x - y)));
            }
        }
        char what[96];
        std::snprintf(what, sizeof what, "frame FBP %u FBW %u %s %ux%u", fbp / 32u, fbw, psm_name(psm), w, h);
        print_diff(what, fd);
        std::printf("  %-34s alpha differing %llu (max |d| %u); oracle wrote %llu pixels here\n", "", static_cast<unsigned long long>(adiff), amax,
                    static_cast<unsigned long long>(px));
        if (!out_dir.empty()) {
            std::filesystem::create_directories(out_dir);
            const std::string base = "fb" + std::to_string(fbp / 32u) + "_";
            write_png((out_dir / (base + "software.png")).string(), a);
            write_png((out_dir / (base + "d3d11.png")).string(), b);
            write_png((out_dir / (base + "diff.png")).string(), d);
        }
    }
    for (const auto& [key, px] : oracle.z_pixels) {
        const auto [zbp, fbw, zpsm] = key;
        if (px == 0 || fbw == 0) continue;
        const u32 w = std::min<u32>(fbw * 64u, 1024u), h = 448;
        u64 differ = 0, total = 0;
        u32 maxd = 0;
        for (u32 y = 0; y < h; ++y)
            for (u32 x = 0; x < w; ++x) {
                const u32 a = sw.mem().read(zpsm, zbp, fbw, x, y), b = gm.read(zpsm, zbp, fbw, x, y);
                ++total;
                if (a != b) {
                    ++differ;
                    maxd = std::max<u32>(maxd, a > b ? a - b : b - a);
                }
            }
        std::printf("  Z ZBP %u %s %ux%u: values differing %llu of %llu (%.4f%%), max |d| %u\n", zbp / 32u, psm_name(zpsm), w, h,
                    static_cast<unsigned long long>(differ), static_cast<unsigned long long>(total),
                    100.0 * static_cast<double>(differ) / static_cast<double>(total), maxd);
    }
    const Frame ca = compose(sw.mem(), s.disp), cb = compose(gm, s.disp);
    if (!ca.empty() && ca.width == cb.width && ca.height == cb.height) {
        Frame d;
        print_diff("CRTC composed output", diff_frames(ca, cb, tol, &d));
        if (!out_dir.empty()) {
            write_png((out_dir / "crtc_software.png").string(), ca);
            write_png((out_dir / "crtc_d3d11.png").string(), cb);
            write_png((out_dir / "crtc_diff.png").string(), d);
        }
        // The GPU CRTC pass against the CPU one over the same (GPU) memory: must be identical.
        Frame g;
        if (gpu.compose_readback(s.disp, g) && g.width == cb.width && g.height == cb.height) {
            u64 n = 0;
            for (std::size_t i = 0; i < g.rgba.size(); ++i) n += (g.rgba[i] & 0xFFFFFFu) != (cb.rgba[i] & 0xFFFFFFu);
            std::printf("  GPU CRTC pass vs gs::compose on the same memory: %llu of %zu pixels differ\n", static_cast<unsigned long long>(n),
                        g.rgba.size());
        } else {
            std::printf("  GPU CRTC pass: no picture (%ux%u)\n", g.width, g.height);
        }
    }
    return 0;
}
