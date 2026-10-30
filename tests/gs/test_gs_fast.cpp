// The fast rasteriser (runtime/gs/gs_raster.cpp) against the reference one (gs_raster_ref.cpp): random draw
// states and primitives, both drawn into local memories with identical contents, must leave identical memories.
// This is the proof of the per-primitive specialisations (texel templates, palette, inline frame/Z addressing,
// span walking, incremental floor divisions, floor_exact, the skipped LOD); every documented approximation is
// defined by the reference.
#include "gs_test_util.h"

#include "../../runtime/gs/gs_raster.h"

#include <cstdlib>
#include <cstring>
#include <string>

using namespace p3fes;
using namespace p3fes::gs;

namespace {

struct Rng {
    u64 s;
    explicit Rng(u64 seed) : s(seed * 0x9E3779B97F4A7C15ull + 1) {}
    u64 next() noexcept {
        s ^= s << 13;
        s ^= s >> 7;
        s ^= s << 17;
        return s;
    }
    u32 below(u32 n) noexcept { return static_cast<u32>(next() % n); }
    bool chance(u32 percent) noexcept { return below(100) < percent; }
    u32 pick(std::initializer_list<u32> l) noexcept { return *(l.begin() + below(static_cast<u32>(l.size()))); }
    float uniform(float lo, float hi) noexcept {
        return lo + (hi - lo) * static_cast<float>(next() >> 40) / static_cast<float>(1u << 24);
    }
};

constexpr u32 kAllPsm[13] = {0x00, 0x01, 0x02, 0x0A, 0x13, 0x14, 0x1B, 0x24, 0x2C, 0x30, 0x31, 0x32, 0x3A};
constexpr u32 kFramePsm[11] = {0x00, 0x01, 0x02, 0x0A, 0x30, 0x31, 0x32, 0x3A, 0x1B, 0x24, 0x2C};

u32 f2u(float f) noexcept {
    u32 u;
    std::memcpy(&u, &f, 4);
    return u;
}

// A random draw environment. `game` biases it to the title screen's census (CT32 frame, Z16S, indexed textures
// with a CT32 CLUT, STQ, bilinear or nearest with MMAG == MMIN, MXL 0, blend a0 b1 c0 d1, Z GEQUAL).
GsRegs random_regs(Rng& rng, bool game) {
    GsRegs r{};
    const u32 ctxt = game ? 0 : rng.below(2);
    GsContextRegs& c = r.ctx[ctxt];
    const bool iip = game ? true : rng.chance(50);
    const bool tme = game ? true : rng.chance(70);
    const bool fge = game ? false : rng.chance(20);
    const bool abe = game ? true : rng.chance(60);
    const bool fst = game ? rng.chance(15) : rng.chance(50);
    const u32 type = game ? 5 : rng.below(7);
    r.prim = type | (iip ? 8u : 0u) | (tme ? 16u : 0u) | (fge ? 32u : 0u) | (abe ? 64u : 0u) | (fst ? 256u : 0u) |
             (static_cast<u64>(ctxt) << 9);
    r.prmodecont = 1;

    const u32 fpsm = game ? 0x00 : kFramePsm[rng.below(11)];
    const u32 fbw = game ? 10 : 1 + rng.below(4);
    const u32 fbmsk = rng.chance(game ? 5 : 30) ? static_cast<u32>(rng.next()) : 0u;
    c.frame = gs_frame(rng.below(300), fbw, fpsm, fbmsk);
    const u32 zpsm_nibble = game ? 0xA : rng.pick({0x0, 0x1, 0x2, 0xA});
    c.zbuf = gs_zbuf(300 + rng.below(100), zpsm_nibble, rng.chance(game ? 10 : 40));
    c.xyoffset = rng.chance(50) ? gs_xyoffset(rng.below(64 * 16), rng.below(64 * 16)) : 0;
    const u32 sx0 = rng.chance(70) ? 0 : rng.below(40), sy0 = rng.chance(70) ? 0 : rng.below(40);
    c.scissor = gs_scissor(sx0, sx0 + 20 + rng.below(game ? 620 : 200), sy0, sy0 + 20 + rng.below(game ? 430 : 200));

    const bool ate = game ? rng.chance(60) : rng.chance(50);
    const u32 atst = game ? rng.pick({5, 6}) : rng.below(8);
    const u32 ztst = game ? rng.pick({1, 2}) : rng.below(4);
    c.test = gs_test(ate, atst, rng.below(256), rng.below(4), !game && rng.chance(20), rng.chance(50),
                     game ? true : rng.chance(90), ztst);
    c.alpha = game ? gs_alpha(0, 1, 0, 1, rng.below(256))
                   : gs_alpha(rng.below(3), rng.below(3), rng.below(3), rng.below(3), rng.below(256));
    c.fba = rng.chance(game ? 0 : 20);
    r.pabe = rng.chance(game ? 0 : 20);
    r.colclamp = rng.chance(game ? 100 : 80);
    r.dthe = rng.chance(game ? 0 : 50);
    r.dimx = rng.next();
    r.scanmsk = rng.chance(game ? 0 : 15) ? rng.below(4) : 0;
    r.fogcol = rng.next() & 0xFFFFFFu;
    r.texa = (rng.next() & 0xFFull) | (rng.chance(50) ? 0x8000ull : 0ull) | ((rng.next() & 0xFFull) << 32);

    // Texture.
    const u32 tpsm = game ? rng.pick({0x13, 0x14, 0x00}) : (rng.chance(5) ? 0x05 /* undefined */ : kAllPsm[rng.below(13)]);
    const u32 tw = rng.chance(10) ? rng.below(11) : 1 + rng.below(8), th = rng.chance(10) ? rng.below(11) : 1 + rng.below(8);
    const u32 cpsm = game ? 0x0 : rng.pick({0x0, 0x2, 0xA});
    const u32 tfx = game ? rng.pick({0, 1}) : rng.below(4);
    c.tex0 = gs_tex0(rng.below(0x4000), 1 + rng.below(8), tpsm, tw, th, rng.chance(60), tfx, rng.below(0x4000), cpsm,
                     rng.below(2), rng.below(32), 0);
    const bool lcm = game ? false : rng.chance(30);
    const u32 mxl = game ? 0 : (rng.chance(75) ? 0 : rng.below(7));
    const bool mmag = rng.chance(50);
    const u32 mmin = game ? (mmag ? rng.pick({1, 4, 5}) : rng.pick({0, 2, 3, 6, 7})) : rng.below(8);
    const u32 l = rng.below(4);
    const u32 k = rng.below(4096);
    c.tex1 = (lcm ? 1u : 0u) | (mxl << 2) | (mmag ? 32u : 0u) | (mmin << 6) | (rng.chance(30) ? 512u : 0u) | (l << 19) |
             (static_cast<u64>(k) << 32);
    c.miptbp1 = rng.next() & 0x0FFFFFFFFFFFFFFFull;
    c.miptbp2 = rng.next() & 0x0FFFFFFFFFFFFFFFull;
    const u32 wms = rng.below(4), wmt = rng.below(4);
    const u32 minu = rng.below(1024), maxu = rng.below(1024), minv = rng.below(1024), maxv = rng.below(1024);
    c.clamp = wms | (wmt << 2) | (minu << 4) | (static_cast<u64>(maxu) << 14) | (static_cast<u64>(minv) << 24) |
              (static_cast<u64>(maxv) << 34);
    return r;
}

GsVertex random_vertex(Rng& rng, u32 span16, bool game) {
    GsVertex v;
    v.x = rng.below(span16);
    v.y = rng.below(span16);
    v.z = game ? rng.below(0x20000) : (rng.chance(50) ? static_cast<u32>(rng.next()) : rng.below(70000));
    v.r = static_cast<u8>(rng.below(256));
    v.g = static_cast<u8>(rng.below(256));
    v.b = static_cast<u8>(rng.below(256));
    v.a = static_cast<u8>(rng.below(256));
    float q = rng.uniform(0.2f, 4.0f);
    if (!game && rng.chance(5)) q = 0.0f;
    if (!game && rng.chance(5)) q = -q;
    if (!game && rng.chance(3)) q = 1.0e-30f;
    v.q = f2u(q);
    v.s = f2u(rng.uniform(-1.5f, 1.5f) * q);
    v.t = f2u(rng.uniform(-1.5f, 1.5f) * q);
    v.u = rng.below(0x4000);
    v.v = rng.below(0x4000);
    v.f = static_cast<u8>(rng.below(256));
    return v;
}

struct Pair {
    GsMemory fast, ref;
    std::array<u16, 512> clut{};
    GsCoreStats sf{}, sr{};

    void seed(Rng& rng) {
        u8* a = fast.data();
        for (u32 i = 0; i < kVramBytes; i += 8) {
            const u64 w = rng.next();
            std::memcpy(a + i, &w, 8);
        }
        std::memcpy(ref.data(), fast.data(), kVramBytes);
        for (u16& h : clut) h = static_cast<u16>(rng.next());
    }
    // First differing byte, or -1.
    long long diff() const {
        if (std::memcmp(fast.data(), ref.data(), kVramBytes) == 0) return -1;
        for (u32 i = 0; i < kVramBytes; ++i)
            if (fast.data()[i] != ref.data()[i]) return i;
        return -2;
    }
};

// P3FES_GS_FAST_ITERATIONS=<n> multiplies the iteration counts (stress runs; the default keeps the suite fast).
u32 scaled(u32 iterations) {
    const char* e = std::getenv("P3FES_GS_FAST_ITERATIONS");
    const long m = e ? std::strtol(e, nullptr, 10) : 1;
    return m > 1 ? iterations * static_cast<u32>(m) : iterations;
}

void run(Pair& p, u64 seed, u32 iterations, bool game, u32 span_px) {
    iterations = scaled(iterations);
    Rng rng(seed);
    p.seed(rng);
    u64 drawn = 0;
    for (u32 it = 0; it < iterations; ++it) {
        const GsRegs regs = random_regs(rng, game);
        const detail::DrawState ds = detail::decode_draw_state(regs);
        GsVertex v[3];
        for (GsVertex& x : v) x = random_vertex(rng, span_px * 16, game);
        if (rng.chance(10)) v[1].y = v[0].y; // horizontal edges exercise the top-left rule
        if (rng.chance(10)) v[2].x = v[0].x;
        if (!game && rng.chance(5)) v[1] = v[0]; // degenerate
        const u32 count = ds.prim == 0 ? 1 : (ds.prim == 1 || ds.prim == 2 || ds.prim == 6 ? 2 : 3);
        detail::rasterize(p.fast, p.clut, ds, v, count, p.sf);
        detail::ref::rasterize(p.ref, p.clut, ds, v, count, p.sr);
        drawn += p.sf.pixels_written;
        const long long d = p.diff();
        INFO("seed " << seed << " iteration " << it << " prim " << ds.prim << " fpsm " << ds.fpsm << " zpsm " << ds.zpsm
                     << " tme " << ds.tme << " tpsm " << ds.tex.psm << " fst " << ds.fst << " tw/th " << ds.tex.level[0].tw
                     << "/" << ds.tex.level[0].th << " tbp " << ds.tex.level[0].tbp << " tbw " << ds.tex.level[0].tbw
                     << " wms/wmt " << ds.tex.wms << "/" << ds.tex.wmt << " min/max " << ds.tex.minu << " " << ds.tex.maxu
                     << " " << ds.tex.minv << " " << ds.tex.maxv << " lcm " << ds.tex.lcm << " mxl " << ds.tex.mxl
                     << " mmag " << ds.tex.mmag_linear << " mmin " << ds.tex.mmin << " k16 " << ds.tex.k16
                     << " cpsm " << ds.tex.cpsm << " csa " << ds.tex.csa << " v0 " << v[0].x << "," << v[0].y << " v1 "
                     << v[1].x << "," << v[1].y << " q " << v[0].q << " " << v[1].q << " s " << v[0].s << " " << v[1].s
                     << " first difference at byte " << d);
        REQUIRE(d == -1);
        REQUIRE(p.sf.pixels_written == p.sr.pixels_written);
        // Keep the memories moving so later primitives read what earlier ones wrote.
        if (it % 64 == 63) p.seed(rng);
    }
    CHECK(p.sf.pixels_written > 0);
    (void)drawn;
}

} // namespace

TEST_CASE("fast rasteriser == reference rasteriser: random states and primitives, identical local memory (model)") {
    auto p = std::make_unique<Pair>();
    SUBCASE("every PSM, filter, wrap, test and blend combination") { run(*p, 1, 1200, false, 96); }
    SUBCASE("the title screen's census: indexed textures, STQ, bilinear/nearest, blended trifans") { run(*p, 2, 400, true, 200); }
    SUBCASE("second seed") { run(*p, 3, 600, false, 64); }
}
