// Frame interpolation core (runtime/hfr/hfr_interp.h, docs/ANALYSIS/32_high_frame_rate.md): batch matching, cut
// detection, clip-space vertex blending against a hand-computed projection, the side table of the op recorder, and
// transform blending. Synthetic inputs only.
#include "gs_test_util.h"

#include "hfr_interp.h"
#include "p3fes/gs/gs_d3d11.h"
#include "p3fes/gs/gs_ops.h"

#include <array>
#include <string>

#include <cmath>
#include <numbers>

using namespace p3fes;
using namespace p3fes::gs;
using namespace p3fes::hfr;

namespace {

// A g3-like projection: camera-space point p (z forward) -> clip (x, y, w = z); screen = centre + focal * x / w in
// 12.4 window units; Z = zoff + zscale * q; STQ = (u, v, 1) * q.
struct Cam {
    double cx = 320 * 16, cy = 224 * 16, focal = 300 * 16, zoff = 100.0, zscale = 400000.0;
};

GpuVertex project(const Cam& c, double x, double y, double z, float u = 0.25f, float v = 0.75f) {
    GpuVertex g{};
    const double q = 1.0 / z;
    g.x = static_cast<s32>(std::lround(c.cx + c.focal * x * q));
    g.y = static_cast<s32>(std::lround(c.cy + c.focal * y * q));
    g.z = static_cast<float>(c.zoff + c.zscale * q);
    g.q = static_cast<float>(q);
    g.s = static_cast<float>(u * q);
    g.t = static_cast<float>(v * q);
    g.rgba = 100u | (50u << 8) | (200u << 16) | (128u << 24);
    g.f = 0;
    return g;
}

// Appends one native batch: `pts` = camera-space source points (all of them), `tris` = emitted triangles (indices).
void add_batch(OpList& l, u64 key, const Cam& c, const std::vector<std::array<double, 3>>& pts, const std::vector<u16>& tris,
               float tx, float ty, float tz, u32 colour = 100) {
    NativeBatchRec b;
    b.key = key;
    b.rows[0] = b.rows[5] = b.rows[10] = b.rows[15] = 1.0f;
    b.rows[12] = tx;
    b.rows[13] = ty;
    b.rows[14] = tz;
    b.nv = static_cast<u32>(pts.size());
    b.vfirst = static_cast<u32>(l.nat_verts.size());
    b.dfirst = static_cast<u32>(l.verts.size());
    b.dcount = static_cast<u32>(tris.size());
    b.sfirst = static_cast<u32>(l.nat_src.size());
    for (const auto& p : pts) {
        GpuVertex g = project(c, p[0], p[1], p[2]);
        g.rgba = (g.rgba & ~0xFFu) | colour;
        l.nat_verts.push_back(g);
    }
    for (u16 s : tris) {
        l.verts.push_back(l.nat_verts[b.vfirst + s]);
        l.nat_src.push_back(s);
    }
    GpuOp op;
    op.kind = GpuOpKind::Draw;
    op.first = b.dfirst;
    op.count = b.dcount;
    l.ops.push_back(op);
    l.nat_batches.push_back(b);
}

std::vector<std::array<double, 3>> quad(double ox, double oy, double oz, double s = 10) {
    return {{ox, oy, oz}, {ox + s, oy, oz}, {ox, oy + s, oz}, {ox + s, oy + s, oz + s}};
}
const std::vector<u16> kTris = {0, 1, 2, 1, 3, 2};

} // namespace

TEST_CASE("hfr: blend_vertex is perspective-correct: the clip-space midpoint of a vertex moving in depth (hand)") {
    const Cam c;
    // camera-space positions at N-1 and N
    const double a[3] = {-40, 10, 100}, b[3] = {60, -20, 400};
    const GpuVertex va = project(c, a[0], a[1], a[2]), vb = project(c, b[0], b[1], b[2]);
    GpuVertex o;
    for (float t : {0.0f, 0.25f, 0.5f, 1.0f, 1.5f}) {
        REQUIRE(blend_vertex(va, vb, t, true, o));
        // the object moved linearly in camera space -> clip coordinates lerp -> expected screen position
        const double p[3] = {a[0] + (b[0] - a[0]) * t, a[1] + (b[1] - a[1]) * t, a[2] + (b[2] - a[2]) * t};
        const GpuVertex e = project(c, p[0], p[1], p[2]);
        CHECK(std::abs(o.x - e.x) <= 2);  // 1/8 pixel (inputs rounded to 1/16)
        CHECK(std::abs(o.y - e.y) <= 2);
        CHECK(o.q == doctest::Approx(e.q).epsilon(1e-5));
        CHECK(o.z == doctest::Approx(e.z).epsilon(1e-4));
        CHECK(o.s / o.q == doctest::Approx(0.25).epsilon(1e-5));
        CHECK(o.t / o.q == doctest::Approx(0.75).epsilon(1e-5));
    }
    // a screen-space lerp would be wrong here: the depth weighting matters
    REQUIRE(blend_vertex(va, vb, 0.5f, true, o));
    CHECK(std::abs(o.x - (va.x + vb.x) / 2) > 16);
}

TEST_CASE("hfr: blend_vertex refuses non-positive q and keeps frame N's vertex") {
    const Cam c;
    GpuVertex va = project(c, 0, 0, 100), vb = project(c, 5, 5, 120), o;
    va.q = 0.0f;
    CHECK_FALSE(blend_vertex(va, vb, 0.5f, true, o));
    CHECK(o.x == vb.x);
    va.q = -1.0f;
    CHECK_FALSE(blend_vertex(va, vb, 0.5f, true, o));
    va = project(c, 0, 0, 100);
    CHECK_FALSE(blend_vertex(va, vb, -100.0f, true, o));  // extrapolated through the camera: w <= 0
}

TEST_CASE("hfr: matching by key, blending matched batches, holding new ones; colours lerp") {
    const Cam c;
    OpList p, n;
    add_batch(p, 0x11, c, quad(0, 0, 200), kTris, 0, 0, 200, 0);
    add_batch(p, 0x22, c, quad(-50, 0, 300), kTris, -50, 0, 300);
    add_batch(n, 0x22, c, quad(-40, 0, 300), kTris, -40, 0, 300);  // order changed
    add_batch(n, 0x11, c, quad(4, 2, 210), kTris, 4, 2, 210, 200);
    add_batch(n, 0x33, c, quad(30, 30, 250), kTris, 30, 30, 250);  // appeared
    const auto pv = batch_views(p), nv = batch_views(n);
    InterpParams prm;
    const FrameMatch m = match_frames(pv, nv, prm, &p, &n);
    REQUIRE(m.prev_of.size() == 3);
    CHECK(m.prev_of[0] == 1);
    CHECK(m.prev_of[1] == 0);
    CHECK(m.prev_of[2] == -1);
    CHECK(m.st.matched == 2);
    CHECK(m.st.unmatched == 1);
    CHECK(m.st.vanished == 0);
    CHECK_FALSE(m.st.cut);
    std::vector<GpuVertex> v = n.verts;
    const BlendStats bs = blend_vertices(p, n, m, 0.5f, prm, v);
    CHECK(bs.batches == 2);
    CHECK(bs.refused == 0);
    // batch 1 of N (key 0x11), emitted vertex 0 = source 0: midpoint of (0,0,200) and (4,2,210)
    const GpuVertex e = project(c, 2, 1, 205);
    const GpuVertex& got = v[n.nat_batches[1].dfirst];
    CHECK(std::abs(got.x - e.x) <= 2);
    CHECK(std::abs(got.y - e.y) <= 2);
    CHECK((got.rgba & 0xFFu) == 100u);  // red 0 -> 200
    // the new batch is untouched
    for (u32 i = 0; i < n.nat_batches[2].dcount; ++i) CHECK(v[n.nat_batches[2].dfirst + i].x == n.verts[n.nat_batches[2].dfirst + i].x);
    // alpha 1 reproduces frame N, alpha 0 frame N-1's positions
    std::vector<GpuVertex> v1 = n.verts, v0 = n.verts;
    blend_vertices(p, n, m, 1.0f, prm, v1);
    blend_vertices(p, n, m, 0.0f, prm, v0);
    for (std::size_t i = 0; i < v1.size(); ++i) {
        CHECK(std::abs(v1[i].x - n.verts[i].x) <= 1);
        CHECK(std::abs(v1[i].y - n.verts[i].y) <= 1);
    }
    const NativeBatchRec& b0 = n.nat_batches[1];
    const NativeBatchRec& a0 = p.nat_batches[0];
    for (u32 e2 = 0; e2 < b0.dcount; ++e2) {
        const GpuVertex& want = p.nat_verts[a0.vfirst + n.nat_src[b0.sfirst + e2]];
        CHECK(std::abs(v0[b0.dfirst + e2].x - want.x) <= 1);
    }
}

TEST_CASE("hfr: a vertex only in frame N-1's culled triangles still blends (all source vertices are kept)") {
    const Cam c;
    OpList p, n;
    add_batch(p, 7, c, quad(0, 0, 200), {0, 1, 2}, 0, 0, 200);   // vertex 3 drawn in no triangle at N-1
    add_batch(n, 7, c, quad(2, 0, 200), {1, 3, 2}, 2, 0, 200);
    const auto pv = batch_views(p), nv = batch_views(n);
    const FrameMatch m = match_frames(pv, nv, InterpParams{}, &p, &n);
    std::vector<GpuVertex> v = n.verts;
    blend_vertices(p, n, m, 0.5f, InterpParams{}, v);
    const GpuVertex e = project(c, 11, 10, 210);  // source 3 at the midpoint (x 10 -> 12)
    CHECK(std::abs(v[1].x - e.x) <= 2);
}

TEST_CASE("hfr: instances of one key are matched by the nearest origin; a far one is not the same object") {
    const Cam c;
    OpList p, n;
    add_batch(p, 5, c, quad(-100, 0, 300), kTris, -100, 0, 300);
    add_batch(p, 5, c, quad(100, 0, 300), kTris, 100, 0, 300);
    add_batch(n, 5, c, quad(102, 0, 300), kTris, 102, 0, 300);   // the right one, listed first now
    add_batch(n, 5, c, quad(-98, 0, 300), kTris, -98, 0, 300);
    add_batch(n, 5, c, quad(0, 900, 300), kTris, 0, 900, 300);   // a third, far from both
    const auto pv = batch_views(p), nv = batch_views(n);
    const FrameMatch m = match_frames(pv, nv, InterpParams{}, &p, &n);
    CHECK(m.prev_of[0] == 1);
    CHECK(m.prev_of[1] == 0);
    CHECK(m.prev_of[2] == -1);
}

TEST_CASE("hfr: a camera cut (everything jumps) disables blending for the frame; one teleporting object is held") {
    const Cam c;
    OpList p, n;
    for (int i = 0; i < 4; ++i) add_batch(p, 100 + i, c, quad(i * 30.0, 0, 200), kTris, i * 30.0f, 0, 200);
    for (int i = 0; i < 4; ++i) add_batch(n, 100 + i, c, quad(i * 30.0 + 600, 400, 900), kTris, i * 30.0f + 600, 400, 900);
    auto pv = batch_views(p), nv = batch_views(n);
    FrameMatch m = match_frames(pv, nv, InterpParams{}, &p, &n);
    CHECK(m.st.cut);
    for (int j : m.prev_of) CHECK(j == -1);

    OpList n2;
    for (int i = 0; i < 4; ++i) add_batch(n2, 100 + i, c, quad(i * 30.0 + 1, 0, 200), kTris, i * 30.0f + 1, 0, 200);
    n2.nat_batches[3].rows[12] = 5000;  // its origin jumped
    nv = batch_views(n2);
    m = match_frames(pv, nv, InterpParams{}, &p, &n2);
    CHECK_FALSE(m.st.cut);
    CHECK(m.st.held == 1);
    CHECK(m.prev_of[3] == -1);
    CHECK(m.prev_of[0] == 0);

    // a frame without native batches has nothing to blend
    OpList empty;
    const auto ev = batch_views(empty);
    CHECK(match_frames(pv, ev, InterpParams{}).st.cut);
}

TEST_CASE("hfr: flat batches give each blended triangle its third vertex's colour") {
    const Cam c;
    OpList p, n;
    add_batch(p, 9, c, quad(0, 0, 200), kTris, 0, 0, 200, 10);
    add_batch(n, 9, c, quad(1, 0, 200), kTris, 1, 0, 200, 30);
    n.nat_verts[n.nat_batches[0].vfirst + 2].rgba = 0x800000FAu;  // red 250 on the kicking vertex of both triangles
    p.nat_verts[p.nat_batches[0].vfirst + 2].rgba = 0x800000FAu;
    n.nat_batches[0].flat = 1;
    const auto pv = batch_views(p), nv = batch_views(n);
    const FrameMatch m = match_frames(pv, nv, InterpParams{}, &p, &n);
    std::vector<GpuVertex> v = n.verts;
    blend_vertices(p, n, m, 0.5f, InterpParams{}, v);
    for (int i = 0; i < 6; ++i) CHECK((v[i].rgba & 0xFFu) == 0xFAu);
}

TEST_CASE("hfr: OpList::append rebases the side table; clear empties it") {
    const Cam c;
    OpList a, b;
    add_batch(a, 1, c, quad(0, 0, 100), kTris, 0, 0, 100);
    add_batch(b, 2, c, quad(5, 0, 100), kTris, 5, 0, 100);
    const OpList b0 = b;
    a.append(b);
    REQUIRE(a.nat_batches.size() == 2);
    const NativeBatchRec& r = a.nat_batches[1];
    CHECK(r.key == 2);
    CHECK(r.vfirst == 4);
    CHECK(r.dfirst == 6);
    CHECK(r.sfirst == 6);
    CHECK(a.verts[r.dfirst].x == b0.verts[0].x);
    CHECK(a.nat_verts[r.vfirst + 3].x == b0.nat_verts[3].x);
    a.clear();
    CHECK(a.nat_batches.empty());
    CHECK(a.nat_verts.empty());
    CHECK(a.nat_src.empty());
}

TEST_CASE("hfr: the recorder's side table records only when switched on") {
    GsCore core;
    GsOpRecorder rec(core, false);
    const Cam c;
    GpuVertex all[4];
    for (int i = 0; i < 4; ++i) all[i] = project(c, i, 0, 100);
    const u16 src[3] = {0, 3, 2};
    NativeBatchTag tag;
    tag.key = 0xABCDEF;
    tag.rows[12] = 7.0f;
    tag.prog = 2;
    for (u16 s : src) rec.list().verts.push_back(all[s]);
    rec.note_native_batch(tag, all, 4, src, 3, false);
    CHECK(rec.list().nat_batches.empty());
    rec.set_native_side_table(true);
    rec.note_native_batch(tag, all, 4, src, 3, true);
    REQUIRE(rec.list().nat_batches.size() == 1);
    const NativeBatchRec& b = rec.list().nat_batches[0];
    CHECK(b.key == 0xABCDEF);
    CHECK(b.rows[12] == 7.0f);
    CHECK(b.prog == 2);
    CHECK(b.flat == 1);
    CHECK(b.nv == 4);
    CHECK(b.dfirst == 0);
    CHECK(b.dcount == 3);
    CHECK(rec.list().nat_src[1] == 3);
    CHECK(rec.list().nat_verts.size() == 4);
    OpList out;
    rec.take(out);
    CHECK(out.nat_batches.size() == 1);
    CHECK(rec.list().nat_batches.empty());
}

TEST_CASE("hfr: transform blending keeps lengths (slerp), lerps stretch and translation; turn angle (hand)") {
    const float k = 2.0f;
    // a: scale 2, no rotation; b: scale 2, 90 degrees about z; row-major rows = basis vectors
    const float a[16] = {k, 0, 0, 0, 0, k, 0, 0, 0, 0, k, 0, 10, 20, 30, 1};
    const float b[16] = {0, k, 0, 0, -k, 0, 0, 0, 0, 0, k, 0, 30, 40, 50, 1};
    CHECK(turn_angle(a, b) == doctest::Approx(std::numbers::pi / 2).epsilon(1e-4));
    float o[16];
    blend_affine(a, b, 0.5f, o);
    const float c45 = k * std::cos(std::numbers::pi_v<float> / 4);
    CHECK(std::fabs(o[0]) == doctest::Approx(c45).epsilon(1e-4));
    CHECK(std::fabs(o[1]) == doctest::Approx(c45).epsilon(1e-4));
    CHECK(std::sqrt(o[0] * o[0] + o[1] * o[1] + o[2] * o[2]) == doctest::Approx(k).epsilon(1e-4));  // no shrink
    CHECK(o[10] == doctest::Approx(k));
    CHECK(o[12] == doctest::Approx(20.0f));
    CHECK(o[13] == doctest::Approx(30.0f));
    CHECK(o[14] == doctest::Approx(40.0f));
    CHECK(o[15] == doctest::Approx(1.0f));
    // the ends reproduce the inputs
    blend_affine(a, b, 1.0f, o);
    for (int i = 0; i < 16; ++i) CHECK(o[i] == doctest::Approx(b[i]).epsilon(1e-4));
    blend_affine(a, b, 0.0f, o);
    for (int i = 0; i < 16; ++i) CHECK(o[i] == doctest::Approx(a[i]).epsilon(1e-4));
    // a matrix with a reflection keeps it (det < 0) and still decomposes
    const float m[16] = {-1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
    float r[9], s[9];
    REQUIRE(polar3(m, r, s));
    CHECK(s[0] == doctest::Approx(-1.0f));
    CHECK(r[0] == doctest::Approx(1.0f));
    // singular -> element-wise lerp
    const float z[16] = {};
    blend_affine(z, b, 0.5f, o);
    CHECK(o[12] == doctest::Approx(15.0f));
}

TEST_CASE("hfr: quantised alpha puts in-between pictures at 1/k steps and shows the exact frame every k-th tick") {
    CHECK(quantise_alpha(0.25, 2) == doctest::Approx(0.5));
    CHECK(quantise_alpha(0.75, 2) == doctest::Approx(1.0));
    CHECK(quantise_alpha(0.5, 2) == doctest::Approx(0.5));
    CHECK(quantise_alpha(0.125, 4) == doctest::Approx(0.25));
    CHECK(quantise_alpha(0.875, 4) == doctest::Approx(1.0));
    CHECK(quantise_alpha(0.0, 2) == doctest::Approx(0.0));
    CHECK(quantise_alpha(0.3, 0) == doctest::Approx(0.3));
}

TEST_CASE("hfr: executor memory banks save, copy and swap GS memory and the CLUT; a list run on a swapped-in bank leaves the real memory alone (needs a GPU)") {
    using Microsoft::WRL::ComPtr;
    ComPtr<ID3D11Device> dev;
    ComPtr<ID3D11DeviceContext> ctx;
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0};
    if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, levels, 2, D3D11_SDK_VERSION, &dev, nullptr, &ctx))) {
        MESSAGE("no hardware D3D11 device: skipped");
        return;
    }
    GsD3D11Executor ex;
    std::string err;
    if (!ex.init(dev.Get(), ctx.Get(), true, false, err)) {
        MESSAGE("executor unavailable (" << err << "): skipped");
        return;
    }
    std::vector<u8> a(kVramBytes), b(kVramBytes), out;
    for (std::size_t i = 0; i < kVramBytes; ++i) {
        a[i] = static_cast<u8>(i * 7 + 1);
        b[i] = static_cast<u8>(i * 13 + 5);
    }
    std::array<u16, 512> ca{}, cb{}, cout{};
    for (int i = 0; i < 512; ++i) {
        ca[i] = static_cast<u16>(i * 3);
        cb[i] = static_cast<u16>(0xFFFF - i);
    }
    REQUIRE(ex.create_banks(2));
    CHECK(ex.banks() == 2);
    ex.reset(a.data(), ca);
    ex.save_bank(0);
    ex.reset(b.data(), cb);
    ex.swap_bank(0);  // active = A, bank 0 = B
    ex.readback_vram(out);
    CHECK(out == a);
    REQUIRE(ex.readback_clut(cout));
    CHECK(cout == ca);
    ex.swap_bank(0);  // back: active = B
    ex.readback_vram(out);
    CHECK(out == b);
    REQUIRE(ex.readback_clut(cout));
    CHECK(cout == cb);
    ex.copy_bank(1, 0);  // bank 1 = B (bank 0 holds B since the swap back)
    ex.save_bank(0);
    // A list executed on a swapped-in bank: a transfer scatter over the first words.
    ex.reset(a.data(), ca);
    ex.save_bank(1);  // bank 1 = A
    ex.reset(b.data(), cb);
    ex.swap_bank(1);  // active = A
    OpList l;
    GpuOp op;
    op.kind = GpuOpKind::Scatter;
    op.first = 0;
    op.count = 4;
    l.ops.push_back(op);
    for (u32 w = 0; w < 4; ++w) {
        l.words.push_back(w);
        l.words.push_back(0xFFFFFFFFu);
        l.words.push_back(0xA5A5A5A5u);
    }
    ex.execute(l);
    ex.readback_vram(out);
    std::size_t changed = 0;
    for (std::size_t i = 0; i < kVramBytes; ++i) changed += out[i] != a[i] ? 1u : 0u;
    CHECK(changed > 0);
    CHECK(changed <= 16);
    ex.swap_bank(1);  // the real memory (B) back, untouched
    ex.readback_vram(out);
    CHECK(out == b);
}
