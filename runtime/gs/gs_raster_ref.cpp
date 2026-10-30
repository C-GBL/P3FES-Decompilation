// Reference software rasteriser: the pre-optimisation pixel pipeline (gs_raster.cpp as of commit 2b33c18, kept
// verbatim apart from `clamp_like_stl`) behind `detail::ref::rasterize` / `detail::ref::sample`. It is the oracle of the fast paths in
// gs_raster.cpp: tests/gs/test_gs_fast.cpp draws random primitives through both and requires identical local
// memory. The fast rasteriser also falls back to `ref::sample` for texture states it does not specialise
// (mipmapping, MMAG != MMIN with LCM 0). Not used by the game otherwise; every documented approximation of
// runtime/gs/README.md "Exact vs approximate" is defined by this file.
#include "gs_raster.h"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace p3fes::gs::detail::ref {


constexpr s32 sign_extend(u32 v, unsigned nbits) noexcept {
    const u32 m = 1u << (nbits - 1u);
    return static_cast<s32>((v ^ m) - m);
}

constexpr bool is16(u32 psm) noexcept { return psm == 0x02 || psm == 0x0A || psm == 0x32 || psm == 0x3A; }
constexpr bool is24(u32 psm) noexcept { return psm == 0x01 || psm == 0x31; }

inline s32 clamp255(s32 v) noexcept { return v < 0 ? 0 : (v > 255 ? 255 : v); }

// floor(n / d) for d > 0.
inline s64 floor_div(s64 n, s64 d) noexcept {
    s64 q = n / d;
    if ((n % d) != 0 && n < 0) --q;
    return q;
}

inline float u2f(u32 v) noexcept {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

u32 expand16(u32 c, const TexState& t) noexcept {
    const u32 r = (c & 0x1Fu) << 3, g = ((c >> 5) & 0x1Fu) << 3, b = ((c >> 10) & 0x1Fu) << 3;
    u32 a;
    if (c & 0x8000u) a = t.ta1;
    else a = (t.aem && (c & 0x7FFFu) == 0) ? 0u : t.ta0;
    return r | (g << 8) | (b << 16) | (a << 24);
}

u32 clut_entry(const std::array<u16, 512>& clut, const TexState& t, u32 index, bool eight) noexcept {
    if (t.cpsm == 0x0u || t.cpsm == 0x1u) {
        const u32 slot = eight ? (index & 255u) : (((t.csa & 15u) * 16u + index) & 255u);
        return static_cast<u32>(clut[slot]) | (static_cast<u32>(clut[slot + 256u]) << 16);
    }
    const u32 slot = eight ? (index & 255u) : ((t.csa * 16u + index) & 511u);
    return expand16(clut[slot], t);
}

// std::clamp spelled out as the MSVC STL evaluates it for scalars in Release (upper bound wins), so that inverted
// REGION_CLAMP bounds (MINU > MAXU; undefined for std::clamp, an abort in _ITERATOR_DEBUG_LEVEL 2 builds) give the
// same value in every build. The only edit to the pre-optimisation code.
inline s32 clamp_like_stl(s32 v, s32 lo, s32 hi) noexcept { return hi < v ? hi : (v < lo ? lo : v); }

s32 wrap_coord(s32 v, u32 size, u32 mode, u32 lo, u32 hi) noexcept {
    switch (mode) {
    case 0: return v & static_cast<s32>(size - 1u);
    case 1: return clamp_like_stl(v, 0, static_cast<s32>(size) - 1);
    case 2: return clamp_like_stl(v, static_cast<s32>(lo), static_cast<s32>(hi));
    default: return static_cast<s32>((static_cast<u32>(v) & lo) | hi);
    }
}

u32 fetch(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, u32 level, s32 x, s32 y) noexcept {
    const TexLevel& L = t.level[level];
    const u32 w = 1u << L.tw, h = 1u << L.th;
    x = wrap_coord(x, w, t.wms, t.minu >> level, t.maxu >> level);
    y = wrap_coord(y, h, t.wmt, t.minv >> level, t.maxv >> level);
    const u32 raw = mem.read(t.psm, L.tbp, L.tbw, static_cast<u32>(x), static_cast<u32>(y));
    switch (t.psm) {
    case 0x00: case 0x30: return raw;
    case 0x01: case 0x31: return (raw & 0xFFFFFFu) | (((t.aem && (raw & 0xFFFFFFu) == 0) ? 0u : t.ta0) << 24);
    case 0x02: case 0x0A: case 0x32: case 0x3A: return expand16(raw, t);
    case 0x13: case 0x1B: return clut_entry(clut, t, raw, true);
    case 0x14: case 0x24: case 0x2C: return clut_entry(clut, t, raw, false);
    default: return raw;
    }
}

u32 bilinear(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, u32 level, s32 u16ths,
             s32 v16ths) noexcept {
    const s32 uu = u16ths - 8, vv = v16ths - 8; // texel centres sit at +0.5
    const s32 x0 = uu >> 4, y0 = vv >> 4;
    const u32 fx = static_cast<u32>(uu & 15), fy = static_cast<u32>(vv & 15);
    const u32 c00 = fetch(mem, clut, t, level, x0, y0), c10 = fetch(mem, clut, t, level, x0 + 1, y0);
    const u32 c01 = fetch(mem, clut, t, level, x0, y0 + 1), c11 = fetch(mem, clut, t, level, x0 + 1, y0 + 1);
    const u32 w00 = (16u - fx) * (16u - fy), w10 = fx * (16u - fy), w01 = (16u - fx) * fy, w11 = fx * fy;
    u32 out = 0;
    for (u32 sh = 0; sh < 32; sh += 8) {
        const u32 v = (((c00 >> sh) & 0xFFu) * w00 + ((c10 >> sh) & 0xFFu) * w10 + ((c01 >> sh) & 0xFFu) * w01 +
                       ((c11 >> sh) & 0xFFu) * w11) >> 8;
        out |= (v & 0xFFu) << sh;
    }
    return out;
}

u32 sample_level(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, s32 u16ths, s32 v16ths,
                 bool linear, u32 level) noexcept {
    const s32 u = u16ths >> level, v = v16ths >> level;
    return linear ? bilinear(mem, clut, t, level, u, v) : fetch(mem, clut, t, level, u >> 4, v >> 4);
}

u32 lerp_rgba(u32 a, u32 b, u32 w256) noexcept {
    u32 out = 0;
    for (u32 sh = 0; sh < 32; sh += 8) {
        const u32 x = (a >> sh) & 0xFFu, y = (b >> sh) & 0xFFu;
        out |= (((x * (256u - w256) + y * w256) >> 8) & 0xFFu) << sh;
    }
    return out;
}

// Texture lookup with LOD selection (TEX1: LCM, MXL, MMAG, MMIN, L, K).
u32 sample(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, s32 u16ths, s32 v16ths,
           float q) noexcept {
    double lod;
    if (t.lcm) {
        lod = t.k16 / 16.0;
    } else {
        const double aq = std::fabs(static_cast<double>(q));
        lod = (aq > 0.0 ? std::log2(1.0 / aq) : 0.0) * static_cast<double>(1u << t.l) + t.k16 / 16.0;
    }
    if (lod <= 0.0) return sample_level(mem, clut, t, u16ths, v16ths, t.mmag_linear, 0);
    const u32 mxl = std::min<u32>(t.mxl, 6u);
    switch (t.mmin) {
    case 1: return sample_level(mem, clut, t, u16ths, v16ths, true, 0);
    case 2:
    case 4: {
        const u32 level = std::min<u32>(static_cast<u32>(std::floor(lod + 0.5)), mxl);
        return sample_level(mem, clut, t, u16ths, v16ths, t.mmin == 4, level);
    }
    case 3:
    case 5: {
        const u32 lo = std::min<u32>(static_cast<u32>(std::floor(lod)), mxl);
        const u32 hi = std::min<u32>(lo + 1u, mxl);
        const u32 w = static_cast<u32>((lod - std::floor(lod)) * 256.0);
        const bool lin = t.mmin == 5;
        const u32 a = sample_level(mem, clut, t, u16ths, v16ths, lin, lo);
        if (hi == lo) return a;
        return lerp_rgba(a, sample_level(mem, clut, t, u16ths, v16ths, lin, hi), std::min<u32>(w, 256u));
    }
    default: return sample_level(mem, clut, t, u16ths, v16ths, false, 0);
    }
}

u32 zmax_of(u32 zpsm) noexcept {
    switch (zpsm) {
    case 0x31: return 0xFFFFFFu;
    case 0x32: case 0x3A: return 0xFFFFu;
    default: return 0xFFFFFFFFu;
    }
}

// Interpolated per-pixel inputs.
struct PixelIn {
    s32 r = 0, g = 0, b = 0, a = 0;
    u64 z = 0; // before clamping to the Z format
    s32 f = 255;
    float s = 0, t = 0, q = 1;
    s32 u = 0, v = 0; // 1/16 texel (FST)
};

class Raster {
public:
    Raster(GsMemory& mem, const std::array<u16, 512>& clut, const DrawState& ds, GsCoreStats& stats)
        : mem_(mem), clut_(clut), ds_(ds), stats_(stats), zmax_(zmax_of(ds.zpsm)) {}

    void pixel(s32 x, s32 y, const PixelIn& in);

    void sprite(const GsVertex& v0, const GsVertex& v1);
    void triangle(const GsVertex& v0, const GsVertex& v1, const GsVertex& v2);
    void line(const GsVertex& v0, const GsVertex& v1);
    void point(const GsVertex& v0);

private:
    s32 wx(const GsVertex& v) const noexcept { return static_cast<s32>(v.x) - ds_.ofx; }
    s32 wy(const GsVertex& v) const noexcept { return static_cast<s32>(v.y) - ds_.ofy; }
    bool clip_box(s32& x0, s32& y0, s32& x1, s32& y1) const noexcept {
        x0 = std::max(x0, std::max(ds_.scax0, 0));
        y0 = std::max(y0, std::max(ds_.scay0, 0));
        x1 = std::min(x1, std::min(ds_.scax1, 2047));
        y1 = std::min(y1, std::min(ds_.scay1, 2047));
        return x0 <= x1 && y0 <= y1;
    }
    u32 read_frame(s32 x, s32 y) const noexcept;

    GsMemory& mem_;
    const std::array<u16, 512>& clut_;
    const DrawState& ds_;
    GsCoreStats& stats_;
    u32 zmax_;
};

u32 Raster::read_frame(s32 x, s32 y) const noexcept {
    const u32 raw = mem_.read(ds_.fpsm, ds_.fbp, ds_.fbw, static_cast<u32>(x), static_cast<u32>(y));
    if (is16(ds_.fpsm)) {
        return ((raw & 0x1Fu) << 3) | (((raw >> 5) & 0x1Fu) << 11) | (((raw >> 10) & 0x1Fu) << 19) |
               ((raw & 0x8000u) ? 0x80000000u : 0u);
    }
    if (is24(ds_.fpsm)) return (raw & 0xFFFFFFu) | 0x80000000u; // no stored alpha: Ad reads as 0x80 (inferred)
    return raw;
}

void Raster::pixel(s32 x, s32 y, const PixelIn& in) {
    if (x < ds_.scax0 || x > ds_.scax1 || y < ds_.scay0 || y > ds_.scay1) return;
    if (ds_.scanmsk == 2 && (y & 1) == 0) return;
    if (ds_.scanmsk == 3 && (y & 1) == 1) return;

    s32 r = in.r, g = in.g, b = in.b, a = in.a;
    if (ds_.tme) {
        s32 u, v;
        float q = 1.0f;
        if (ds_.fst) {
            u = in.u;
            v = in.v;
        } else {
            q = in.q;
            const float qq = q != 0.0f ? q : 1.0e-30f;
            const TexLevel& L0 = ds_.tex.level[0];
            u = static_cast<s32>(std::floor(static_cast<double>(in.s / qq) * static_cast<double>(1u << L0.tw) * 16.0));
            v = static_cast<s32>(std::floor(static_cast<double>(in.t / qq) * static_cast<double>(1u << L0.th) * 16.0));
        }
        const u32 tc = sample(mem_, clut_, ds_.tex, u, v, q);
        const s32 tr = static_cast<s32>(tc & 0xFFu), tg = static_cast<s32>((tc >> 8) & 0xFFu);
        const s32 tb = static_cast<s32>((tc >> 16) & 0xFFu), ta = static_cast<s32>(tc >> 24);
        switch (ds_.tex.tfx) {
        case 0: // MODULATE
            r = clamp255((tr * r) >> 7);
            g = clamp255((tg * g) >> 7);
            b = clamp255((tb * b) >> 7);
            a = ds_.tex.tcc ? clamp255((ta * a) >> 7) : a;
            break;
        case 1: // DECAL
            r = tr;
            g = tg;
            b = tb;
            a = ds_.tex.tcc ? ta : a;
            break;
        case 2: // HIGHLIGHT
            r = clamp255(((tr * r) >> 7) + a);
            g = clamp255(((tg * g) >> 7) + a);
            b = clamp255(((tb * b) >> 7) + a);
            a = ds_.tex.tcc ? clamp255(ta + a) : a;
            break;
        default: // HIGHLIGHT2
            r = clamp255(((tr * r) >> 7) + a);
            g = clamp255(((tg * g) >> 7) + a);
            b = clamp255(((tb * b) >> 7) + a);
            a = ds_.tex.tcc ? ta : a;
            break;
        }
    }
    if (ds_.fge) {
        const s32 f = in.f;
        const s32 fr = static_cast<s32>(ds_.fogcol & 0xFFu), fg = static_cast<s32>((ds_.fogcol >> 8) & 0xFFu);
        const s32 fb = static_cast<s32>((ds_.fogcol >> 16) & 0xFFu);
        r = (f * r + (255 - f) * fr) >> 8;
        g = (f * g + (255 - f) * fg) >> 8;
        b = (f * b + (255 - f) * fb) >> 8;
    }

    bool write_fb = true, write_z = !ds_.zmsk, write_alpha = true;
    if (ds_.ate) {
        const u32 av = static_cast<u32>(a);
        bool pass;
        switch (ds_.atst) {
        case 0: pass = false; break;
        case 1: pass = true; break;
        case 2: pass = av < ds_.aref; break;
        case 3: pass = av <= ds_.aref; break;
        case 4: pass = av == ds_.aref; break;
        case 5: pass = av >= ds_.aref; break;
        case 6: pass = av > ds_.aref; break;
        default: pass = av != ds_.aref; break;
        }
        if (!pass) {
            switch (ds_.afail) {
            case 0: return;                                    // KEEP
            case 1: write_z = false; break;                    // FB_ONLY
            case 2: write_fb = false; break;                   // ZB_ONLY
            default: write_z = false; write_alpha = false; break; // RGB_ONLY
            }
        }
    }

    u32 dst = 0;
    bool have_dst = false;
    if (ds_.date) {
        dst = read_frame(x, y);
        have_dst = true;
        if (((dst >> 31) & 1u) != static_cast<u32>(ds_.datm)) return;
    }

    const u32 z = static_cast<u32>(std::min<u64>(in.z, zmax_));
    if (ds_.ztst != 1) {
        const u32 old = mem_.read(ds_.zpsm, ds_.zbp, ds_.fbw, static_cast<u32>(x), static_cast<u32>(y)) & zmax_;
        bool pass;
        switch (ds_.ztst) {
        case 0: pass = false; break;
        case 1: pass = true; break;
        case 2: pass = z >= old; break;
        default: pass = z > old; break;
        }
        if (!pass) return;
    }

    ++stats_.pixels_written;
    if (write_fb) {
        s32 out[3] = {r, g, b};
        if (ds_.abe && (!ds_.pabe || (a & 0x80))) {
            if (!have_dst) dst = read_frame(x, y);
            const s32 cs[3] = {r, g, b};
            const s32 cd[3] = {static_cast<s32>(dst & 0xFFu), static_cast<s32>((dst >> 8) & 0xFFu),
                               static_cast<s32>((dst >> 16) & 0xFFu)};
            const s32 ad = static_cast<s32>(dst >> 24);
            const s32 cc = ds_.c == 0 ? a : (ds_.c == 1 ? ad : static_cast<s32>(ds_.fix));
            for (int i = 0; i < 3; ++i) {
                const s32 va = ds_.a == 0 ? cs[i] : (ds_.a == 1 ? cd[i] : 0);
                const s32 vb = ds_.b == 0 ? cs[i] : (ds_.b == 1 ? cd[i] : 0);
                const s32 vd = ds_.d == 0 ? cs[i] : (ds_.d == 1 ? cd[i] : 0);
                out[i] = (((va - vb) * cc) >> 7) + vd;
            }
        }
        const bool fb16 = is16(ds_.fpsm);
        if (ds_.dthe && fb16) {
            const s32 dm = ds_.dimx[y & 3][x & 3];
            for (s32& c : out) c += dm;
        }
        for (s32& c : out) c = ds_.colclamp ? clamp255(c) : (c & 0xFF);
        u32 alpha = static_cast<u32>(a) & 0xFFu;
        if (ds_.fba) alpha |= 0x80u;
        const u32 xu = static_cast<u32>(x), yu = static_cast<u32>(y);
        if (fb16) {
            u32 value = (static_cast<u32>(out[0]) >> 3) | ((static_cast<u32>(out[1]) >> 3) << 5) |
                        ((static_cast<u32>(out[2]) >> 3) << 10) | ((alpha >> 7) << 15);
            const u32 m = ds_.fbmsk;
            u32 m16 = ((m >> 3) & 0x1Fu) | (((m >> 11) & 0x1Fu) << 5) | (((m >> 19) & 0x1Fu) << 10) | (((m >> 31) & 1u) << 15);
            if (!write_alpha) m16 |= 0x8000u;
            if (m16) value = (value & ~m16) | (mem_.read(ds_.fpsm, ds_.fbp, ds_.fbw, xu, yu) & m16);
            mem_.write(ds_.fpsm, ds_.fbp, ds_.fbw, xu, yu, value);
        } else {
            u32 value = static_cast<u32>(out[0]) | (static_cast<u32>(out[1]) << 8) | (static_cast<u32>(out[2]) << 16) |
                        (alpha << 24);
            u32 m = ds_.fbmsk;
            if (!write_alpha || is24(ds_.fpsm)) m |= 0xFF000000u;
            if (m) value = (value & ~m) | (mem_.read(ds_.fpsm, ds_.fbp, ds_.fbw, xu, yu) & m);
            mem_.write(ds_.fpsm, ds_.fbp, ds_.fbw, xu, yu, value);
        }
    }
    if (write_z) mem_.write(ds_.zpsm, ds_.zbp, ds_.fbw, static_cast<u32>(x), static_cast<u32>(y), z);
}

void Raster::sprite(const GsVertex& v0, const GsVertex& v1) {
    s32 x0 = wx(v0), x1 = wx(v1), y0 = wy(v0), y1 = wy(v1);
    s32 u0 = static_cast<s32>(v0.u), u1 = static_cast<s32>(v1.u), vv0 = static_cast<s32>(v0.v), vv1 = static_cast<s32>(v1.v);
    float s0 = u2f(v0.s), s1 = u2f(v1.s), t0 = u2f(v0.t), t1 = u2f(v1.t), q0 = u2f(v0.q), q1 = u2f(v1.q);
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(u0, u1);
        std::swap(s0, s1);
    }
    if (y0 > y1) {
        std::swap(y0, y1);
        std::swap(vv0, vv1);
        std::swap(t0, t1);
    }
    // Top-left rule on pixel sample points (px * 16): px in [ceil(x0/16), ceil(x1/16)).
    s32 px0 = static_cast<s32>(floor_div(x0 + 15, 16)), px1 = static_cast<s32>(floor_div(x1 + 15, 16)) - 1;
    s32 py0 = static_cast<s32>(floor_div(y0 + 15, 16)), py1 = static_cast<s32>(floor_div(y1 + 15, 16)) - 1;
    if (!clip_box(px0, py0, px1, py1)) return;
    PixelIn in;
    in.r = v1.r;
    in.g = v1.g;
    in.b = v1.b;
    in.a = v1.a;
    in.z = v1.z;
    in.f = v1.f;
    const s64 dx = x1 - x0, dy = y1 - y0;
    for (s32 py = py0; py <= py1; ++py) {
        const s64 oy = static_cast<s64>(py) * 16 - y0;
        in.v = dy ? vv0 + static_cast<s32>(floor_div(oy * (vv1 - vv0), dy)) : vv0;
        in.t = dy ? t0 + (t1 - t0) * static_cast<float>(static_cast<double>(oy) / static_cast<double>(dy)) : t0;
        for (s32 px = px0; px <= px1; ++px) {
            const s64 ox = static_cast<s64>(px) * 16 - x0;
            in.u = dx ? u0 + static_cast<s32>(floor_div(ox * (u1 - u0), dx)) : u0;
            in.s = dx ? s0 + (s1 - s0) * static_cast<float>(static_cast<double>(ox) / static_cast<double>(dx)) : s0;
            in.q = dx ? q0 + (q1 - q0) * static_cast<float>(static_cast<double>(ox) / static_cast<double>(dx)) : q1;
            pixel(px, py, in);
        }
    }
}

void Raster::triangle(const GsVertex& a0, const GsVertex& a1, const GsVertex& a2) {
    const GsVertex* v[3] = {&a0, &a1, &a2};
    const GsVertex& last = a2; // flat shading uses the kicking vertex
    s64 X[3], Y[3];
    for (int i = 0; i < 3; ++i) {
        X[i] = wx(*v[i]);
        Y[i] = wy(*v[i]);
    }
    s64 area = (X[1] - X[0]) * (Y[2] - Y[0]) - (X[2] - X[0]) * (Y[1] - Y[0]);
    if (area == 0) return;
    if (area < 0) {
        std::swap(v[1], v[2]);
        std::swap(X[1], X[2]);
        std::swap(Y[1], Y[2]);
        area = -area;
    }
    const auto top_left = [](s64 ax, s64 ay, s64 bx, s64 by) { return (by - ay) < 0 || ((by - ay) == 0 && (bx - ax) > 0); };
    const bool tl0 = top_left(X[1], Y[1], X[2], Y[2]); // edge opposite v0
    const bool tl1 = top_left(X[2], Y[2], X[0], Y[0]);
    const bool tl2 = top_left(X[0], Y[0], X[1], Y[1]);
    s32 px0 = static_cast<s32>(floor_div(std::min({X[0], X[1], X[2]}) + 15, 16));
    s32 px1 = static_cast<s32>(floor_div(std::max({X[0], X[1], X[2]}), 16));
    s32 py0 = static_cast<s32>(floor_div(std::min({Y[0], Y[1], Y[2]}) + 15, 16));
    s32 py1 = static_cast<s32>(floor_div(std::max({Y[0], Y[1], Y[2]}), 16));
    if (!clip_box(px0, py0, px1, py1)) return;

    // Attribute deltas relative to v0: attr = a0 + (w1 * (a1 - a0) + w2 * (a2 - a0)) / area, so equal vertex values
    // interpolate exactly.
    const GsVertex& b0 = *v[0];
    const GsVertex& b1 = *v[1];
    const GsVertex& b2 = *v[2];
    const s64 dr1 = b1.r - b0.r, dr2 = b2.r - b0.r, dg1 = b1.g - b0.g, dg2 = b2.g - b0.g;
    const s64 db1 = b1.b - b0.b, db2 = b2.b - b0.b, da1 = b1.a - b0.a, da2 = b2.a - b0.a;
    const s64 df1 = b1.f - b0.f, df2 = b2.f - b0.f;
    const s64 du1 = static_cast<s64>(b1.u) - b0.u, du2 = static_cast<s64>(b2.u) - b0.u;
    const s64 dv1 = static_cast<s64>(b1.v) - b0.v, dv2 = static_cast<s64>(b2.v) - b0.v;
    const double dz1 = static_cast<double>(b1.z) - b0.z, dz2 = static_cast<double>(b2.z) - b0.z;
    const float s0 = u2f(b0.s), t0 = u2f(b0.t), q0 = u2f(b0.q);
    const float ds1 = u2f(b1.s) - s0, ds2 = u2f(b2.s) - s0, dt1 = u2f(b1.t) - t0, dt2 = u2f(b2.t) - t0;
    const float dq1 = u2f(b1.q) - q0, dq2 = u2f(b2.q) - q0;
    const double inv_area = 1.0 / static_cast<double>(area);

    PixelIn in;
    if (!ds_.iip) {
        in.r = last.r;
        in.g = last.g;
        in.b = last.b;
        in.a = last.a;
    }
    for (s32 py = py0; py <= py1; ++py) {
        const s64 sy = static_cast<s64>(py) * 16;
        for (s32 px = px0; px <= px1; ++px) {
            const s64 sx = static_cast<s64>(px) * 16;
            const s64 w0 = (X[2] - X[1]) * (sy - Y[1]) - (Y[2] - Y[1]) * (sx - X[1]);
            const s64 w1 = (X[0] - X[2]) * (sy - Y[2]) - (Y[0] - Y[2]) * (sx - X[2]);
            const s64 w2 = (X[1] - X[0]) * (sy - Y[0]) - (Y[1] - Y[0]) * (sx - X[0]);
            if (w0 < 0 || (w0 == 0 && !tl0)) continue;
            if (w1 < 0 || (w1 == 0 && !tl1)) continue;
            if (w2 < 0 || (w2 == 0 && !tl2)) continue;
            if (ds_.iip) {
                in.r = b0.r + static_cast<s32>(floor_div(w1 * dr1 + w2 * dr2, area));
                in.g = b0.g + static_cast<s32>(floor_div(w1 * dg1 + w2 * dg2, area));
                in.b = b0.b + static_cast<s32>(floor_div(w1 * db1 + w2 * db2, area));
                in.a = b0.a + static_cast<s32>(floor_div(w1 * da1 + w2 * da2, area));
            }
            in.f = b0.f + static_cast<s32>(floor_div(w1 * df1 + w2 * df2, area));
            const double zz = static_cast<double>(b0.z) + (static_cast<double>(w1) * dz1 + static_cast<double>(w2) * dz2) * inv_area;
            in.z = zz <= 0.0 ? 0u : static_cast<u64>(std::floor(zz));
            if (ds_.tme) {
                if (ds_.fst) {
                    in.u = static_cast<s32>(b0.u) + static_cast<s32>(floor_div(w1 * du1 + w2 * du2, area));
                    in.v = static_cast<s32>(b0.v) + static_cast<s32>(floor_div(w1 * dv1 + w2 * dv2, area));
                } else {
                    const float l1 = static_cast<float>(static_cast<double>(w1) * inv_area);
                    const float l2 = static_cast<float>(static_cast<double>(w2) * inv_area);
                    in.s = s0 + ds1 * l1 + ds2 * l2;
                    in.t = t0 + dt1 * l1 + dt2 * l2;
                    in.q = q0 + dq1 * l1 + dq2 * l2;
                }
            }
            pixel(px, py, in);
        }
    }
}

void Raster::line(const GsVertex& v0, const GsVertex& v1) {
    // Approximation: DDA over the major axis from v0 to v1, the end pixel excluded (no AA1, no diamond rule).
    const s64 x0 = wx(v0), y0 = wy(v0), x1 = wx(v1), y1 = wy(v1);
    const s64 adx = x1 > x0 ? x1 - x0 : x0 - x1, ady = y1 > y0 ? y1 - y0 : y0 - y1;
    const s64 steps = (std::max(adx, ady) + 15) / 16;
    if (steps == 0) return;
    PixelIn in;
    for (s64 i = 0; i < steps; ++i) {
        const s64 sx = x0 + (x1 - x0) * i / steps, sy = y0 + (y1 - y0) * i / steps;
        const s32 px = static_cast<s32>(floor_div(sx + 8, 16)), py = static_cast<s32>(floor_div(sy + 8, 16));
        if (ds_.iip) {
            in.r = static_cast<s32>(v0.r + (static_cast<s64>(v1.r) - v0.r) * i / steps);
            in.g = static_cast<s32>(v0.g + (static_cast<s64>(v1.g) - v0.g) * i / steps);
            in.b = static_cast<s32>(v0.b + (static_cast<s64>(v1.b) - v0.b) * i / steps);
            in.a = static_cast<s32>(v0.a + (static_cast<s64>(v1.a) - v0.a) * i / steps);
        } else {
            in.r = v1.r;
            in.g = v1.g;
            in.b = v1.b;
            in.a = v1.a;
        }
        in.z = static_cast<u64>(static_cast<double>(v0.z) + (static_cast<double>(v1.z) - v0.z) * static_cast<double>(i) / static_cast<double>(steps));
        in.f = static_cast<s32>(v0.f + (static_cast<s64>(v1.f) - v0.f) * i / steps);
        in.u = static_cast<s32>(v0.u + (static_cast<s64>(v1.u) - v0.u) * i / steps);
        in.v = static_cast<s32>(v0.v + (static_cast<s64>(v1.v) - v0.v) * i / steps);
        const float t = static_cast<float>(static_cast<double>(i) / static_cast<double>(steps));
        in.s = u2f(v0.s) + (u2f(v1.s) - u2f(v0.s)) * t;
        in.t = u2f(v0.t) + (u2f(v1.t) - u2f(v0.t)) * t;
        in.q = u2f(v0.q) + (u2f(v1.q) - u2f(v0.q)) * t;
        if (px >= 0 && py >= 0 && px < 2048 && py < 2048) pixel(px, py, in);
    }
}

void Raster::point(const GsVertex& v0) {
    const s32 px = static_cast<s32>(floor_div(wx(v0) + 15, 16)), py = static_cast<s32>(floor_div(wy(v0) + 15, 16));
    if (px < 0 || py < 0 || px > 2047 || py > 2047) return;
    PixelIn in;
    in.r = v0.r;
    in.g = v0.g;
    in.b = v0.b;
    in.a = v0.a;
    in.z = v0.z;
    in.f = v0.f;
    in.u = static_cast<s32>(v0.u);
    in.v = static_cast<s32>(v0.v);
    in.s = u2f(v0.s);
    in.t = u2f(v0.t);
    in.q = u2f(v0.q);
    pixel(px, py, in);
}

void rasterize(GsMemory& mem, const std::array<u16, 512>& clut, const DrawState& ds, const GsVertex* v, u32 count,
               GsCoreStats& stats) {
    Raster r(mem, clut, ds, stats);
    switch (ds.prim) {
    case 0: r.point(v[0]); break;
    case 1:
    case 2:
        if (count >= 2) r.line(v[0], v[1]);
        break;
    case 3:
    case 4:
    case 5:
        if (count >= 3) r.triangle(v[0], v[1], v[2]);
        break;
    case 6:
        if (count >= 2) r.sprite(v[0], v[1]);
        break;
    default: break;
    }
}

} // namespace p3fes::gs::detail::ref
