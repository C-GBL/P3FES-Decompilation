// Software rasteriser for the GS (correctness first; runtime/gs/README.md lists what is exact and what is
// approximate). Pixel pipeline order and every register field are the GS User's Manual's: scissor -> (texture,
// TFX) -> fog -> alpha test -> destination alpha test -> depth test -> alpha blend -> dither -> colour clamp ->
// FBA -> FBMSK write, Z write. The texture-function, fog and blend arithmetic was cross-checked against
// ps2-web-recomp @ c0f476e runtime/src/gs/raster.cpp (MIT); coverage, interpolation, mipmapping, CLUT and dither
// handling are our own.
//
// This is the fast implementation. Its *semantics* are gs_raster_ref.cpp (the same pipeline written one generic
// operation per pixel, kept verbatim as the oracle): every value here is computed from the same integer and
// floating-point expressions, only with the per-primitive constant parts hoisted out of the pixel loop:
//   * the texel fetch is a template per PSM (and per filter) over level 0 with the wrap mode, the buffer base and
//     the swizzle table resolved once, and the CLUT indirection folded into a 256-entry palette ("TexCtx");
//     texture states the templates do not cover (MXL > 0, or MMAG != MMIN with LCM 0 where the LOD sign decides
//     the filter per pixel) go through `ref::sample`; the pixel loop itself is instantiated per sampler (the
//     census's T8/T4/CT32 formats inline it, the rest call through a pointer) so that nothing in the loop is an
//     opaque call;
//   * the per-pixel LOD (`log2(1/|Q|)`) is skipped when TEX1.MXL = 0 and the magnification and minification filters
//     agree, because then the LOD selects nothing (level 0 either way, same filter), and decided once per primitive
//     when LCM = 1;
//   * frame and Z accesses are inline page/table lookups for the primitive's two buffers ("Plane"), with the
//     24-bit / T8H / T4HL / T4HH merges as read/write masks;
//   * a triangle walks the exact pixel span of every row (the three edge functions are linear in x, so the
//     half-plane tests become one division per edge per row) and steps the edge functions and the floor-divided
//     attribute planes incrementally (quotient + remainder carry, exact), instead of three products and up to seven
//     64-bit divisions per pixel; sprites step U the same way;
//   * `std::floor` is replaced by a truncating conversion and one compare (`floor_exact`, `floor_to_s32`,
//     `floor_to_u64_positive`) where the result feeds an integer conversion.
// tests/gs/test_gs_fast.cpp draws random primitives through both implementations and requires identical memory.
#include "gs_raster.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cmath>
#include <cstring>

#if defined(_MSC_VER)
#define P3FES_FORCEINLINE __forceinline
#else
#define P3FES_FORCEINLINE inline __attribute__((always_inline))
#endif

namespace p3fes::gs::detail {

namespace {

constexpr s32 sign_extend(u32 v, unsigned nbits) noexcept {
    const u32 m = 1u << (nbits - 1u);
    return static_cast<s32>((v ^ m) - m);
}

constexpr bool is16(u32 psm) noexcept { return psm == 0x02 || psm == 0x0A || psm == 0x32 || psm == 0x3A; }
constexpr bool is24(u32 psm) noexcept { return psm == 0x01 || psm == 0x31; }

inline s32 clamp255(s32 v) noexcept { return v < 0 ? 0 : (v > 255 ? 255 : v); }

// floor(n / d) for d > 0.
P3FES_FORCEINLINE s64 floor_div(s64 n, s64 d) noexcept {
    s64 q = n / d;
    if ((n % d) != 0 && n < 0) --q;
    return q;
}

P3FES_FORCEINLINE float u2f(u32 v) noexcept {
    float f;
    std::memcpy(&f, &v, 4);
    return f;
}

// std::floor without the CRT call. For |v| < 2^52 the truncating conversion to s64 is exact and the floor is one
// compare away; every other double (|v| >= 2^52, infinities, NaN) is its own floor. Only the sign of a zero can
// differ from std::floor (-0.0 -> +0.0), which no integer conversion of the result sees.
P3FES_FORCEINLINE double floor_exact(double v) noexcept {
    if (std::fabs(v) < 4503599627370496.0) {
        const double t = static_cast<double>(static_cast<s64>(v));
        return t > v ? t - 1.0 : t;
    }
    return v;
}

// floor(N / d) for an N that advances by a constant step: the quotient advances by floor(step / d) plus a carry
// from the remainder. Exact for every step as long as the start is exact (d > 0).
struct IncDiv {
    s64 d = 1, dq = 0, dr = 0; // step = dq * d + dr, 0 <= dr < d
    s64 q = 0, r = 0;          // N = q * d + r, 0 <= r < d
    P3FES_FORCEINLINE void set_step(s64 step, s64 den) noexcept {
        d = den;
        dq = floor_div(step, den);
        dr = step - dq * den;
    }
    P3FES_FORCEINLINE void start(s64 n) noexcept {
        q = floor_div(n, d);
        r = n - q * d;
    }
    P3FES_FORCEINLINE void next() noexcept {
        r += dr;
        const s64 carry = r >= d ? 1 : 0; // r < 2d: at most one subtraction
        r -= d & (0 - carry);
        q += dq + carry;
    }
};

P3FES_FORCEINLINE u32 expand16(u32 c, u32 ta0, u32 ta1, bool aem) noexcept {
    const u32 r = (c & 0x1Fu) << 3, g = ((c >> 5) & 0x1Fu) << 3, b = ((c >> 10) & 0x1Fu) << 3;
    u32 a;
    if (c & 0x8000u) a = ta1;
    else a = (aem && (c & 0x7FFFu) == 0) ? 0u : ta0;
    return r | (g << 8) | (b << 16) | (a << 24);
}

u32 clut_entry(const std::array<u16, 512>& clut, const TexState& t, u32 index, bool eight) noexcept {
    if (t.cpsm == 0x0u || t.cpsm == 0x1u) {
        const u32 slot = eight ? (index & 255u) : (((t.csa & 15u) * 16u + index) & 255u);
        return static_cast<u32>(clut[slot]) | (static_cast<u32>(clut[slot + 256u]) << 16);
    }
    const u32 slot = eight ? (index & 255u) : ((t.csa * 16u + index) & 511u);
    return expand16(clut[slot], t.ta0, t.ta1, t.aem);
}

// ---- Texture sampling, level 0, one template instance per PSM and filter ------------------------------------

// CLAMP wrap mode of one axis, resolved to one branchless form: a clamp to [lo, hi] followed by an AND/OR. CLAMP
// and REGION_CLAMP clamp (the mask is the identity); REPEAT and REGION_REPEAT AND/OR (the clamp is the identity).
struct Wrap {
    s32 lo = INT32_MIN, hi = INT32_MAX;
    u32 and_mask = 0xFFFFFFFFu, or_mask = 0;
};

Wrap make_wrap(u32 mode, u32 size_log2, u32 lo, u32 hi) noexcept {
    Wrap w;
    switch (mode) {
    case 0: w.and_mask = (1u << size_log2) - 1u; break;
    case 1:
        w.lo = 0;
        w.hi = static_cast<s32>(1u << size_log2) - 1;
        break;
    case 2:
        w.lo = static_cast<s32>(lo);
        w.hi = static_cast<s32>(hi);
        break;
    default:
        w.and_mask = lo;
        w.or_mask = hi;
        break;
    }
    return w;
}

P3FES_FORCEINLINE s32 wrap(s32 v, const Wrap& w) noexcept {
    // std::clamp as the MSVC STL evaluates it (upper bound tested first), which also fixes what inverted
    // REGION_CLAMP bounds (MINU > MAXU, undefined for std::clamp) give: the reference goes through std::clamp.
    const s32 c = w.hi < v ? w.hi : (v < w.lo ? w.lo : v);
    return static_cast<s32>((static_cast<u32>(c) & w.and_mask) | w.or_mask);
}


// Texel coordinates in 1/16 units -> integer texel with the GS's floor; `static_cast<s32>(std::floor(x))` of the
// reference. |x| < 2^31 (every real case): the 32-bit truncating conversion is exact and the floor is one compare
// away; otherwise the conversion of floor_exact(x), which is what the reference's cast sees.
P3FES_FORCEINLINE s32 floor_to_s32(double x) noexcept {
    if (std::fabs(x) < 2147483648.0) {
        const s32 t = static_cast<s32>(x);
        return static_cast<double>(t) > x ? t - 1 : t;
    }
    return static_cast<s32>(floor_exact(x));
}

// `static_cast<u64>(std::floor(x))` for x > 0: truncation is the floor; below 2^63 the signed conversion is the
// cheaper instruction and gives the same value.
P3FES_FORCEINLINE u64 floor_to_u64_positive(double x) noexcept {
    if (x < 9223372036854775808.0) return static_cast<u64>(static_cast<s64>(x));
    return static_cast<u64>(floor_exact(x));
}

struct TexCtx {
    const GsMemory* mem = nullptr;
    const std::array<u16, 512>* clut = nullptr;
    const TexState* ts = nullptr;
    u32 (*sample)(const TexCtx&, s32 u16ths, s32 v16ths, float q) = nullptr;
    const u8* vram = nullptr;
    u32 base = 0;         // level-0 TBP in bytes
    u32 bw = 0;           // pages per buffer row (TBW, halved for 8/4-bit formats)
    const u16* tbl = nullptr; // in-page swizzle table of the PSM, row-major
    Wrap wu, wv;
    u32 ta0 = 0, ta1 = 0;
    bool aem = false;
    u32 static_psm = 0xFFFFFFFFu; // PSM of the bound sample_fast<>, or ~0 when `sample` is the reference
    bool linear = false;
    double scale_u = 1.0, scale_v = 1.0; // 2^TW, 2^TH
    u32 pal[256] = {};    // CLUT entries expanded to 0xAABBGGRR (indexed formats)
};

// One texel at already wrapped coordinates (0..2047).
template <u32 PSM>
P3FES_FORCEINLINE u32 texel_at(const TexCtx& t, u32 ux, u32 uy) noexcept {
    if constexpr (PSM == 0x13) {
        const u32 page = (uy >> 6) * t.bw + (ux >> 7);
        const u32 addr = (t.base + page * kPageBytes + t.tbl[(uy & 63u) * 128u + (ux & 127u)]) & kVramMask;
        return t.pal[t.vram[addr]];
    } else if constexpr (PSM == 0x14) {
        const u32 page = (uy >> 7) * t.bw + (ux >> 7);
        const u32 n = ((t.base + page * kPageBytes) * 2u + t.tbl[(uy & 127u) * 128u + (ux & 127u)]) & (kVramBytes * 2u - 1u);
        return t.pal[(t.vram[n >> 1] >> ((n & 1u) * 4u)) & 0xFu];
    } else if constexpr (is16(PSM)) {
        const u32 page = (uy >> 6) * t.bw + (ux >> 6);
        const u32 addr = (t.base + page * kPageBytes + t.tbl[(uy & 63u) * 64u + (ux & 63u)]) & kVramMask;
        u16 h;
        std::memcpy(&h, t.vram + addr, 2);
        return expand16(h, t.ta0, t.ta1, t.aem);
    } else {
        const u32 page = (uy >> 5) * t.bw + (ux >> 6);
        const u32 addr = (t.base + page * kPageBytes + t.tbl[(uy & 31u) * 64u + (ux & 63u)]) & kVramMask;
        const u32 raw = t.mem->read_u32(addr);
        if constexpr (PSM == 0x01 || PSM == 0x31) {
            const u32 c = raw & 0xFFFFFFu;
            return c | (((t.aem && c == 0) ? 0u : t.ta0) << 24);
        } else if constexpr (PSM == 0x1B) {
            return t.pal[raw >> 24];
        } else if constexpr (PSM == 0x24) {
            return t.pal[(raw >> 24) & 0xFu];
        } else if constexpr (PSM == 0x2C) {
            return t.pal[raw >> 28];
        } else {
            return raw;
        }
    }
}

template <u32 PSM, bool LINEAR>
P3FES_FORCEINLINE u32 sample_static(const TexCtx& t, s32 u16ths, s32 v16ths) noexcept {
    if constexpr (!LINEAR) {
        const u32 ux = static_cast<u32>(wrap(u16ths >> 4, t.wu)) & 2047u;
        const u32 uy = static_cast<u32>(wrap(v16ths >> 4, t.wv)) & 2047u;
        return texel_at<PSM>(t, ux, uy);
    } else {
        const s32 uu = u16ths - 8, vv = v16ths - 8; // texel centres sit at +0.5
        const s32 x0 = uu >> 4, y0 = vv >> 4;
        const u32 fx = static_cast<u32>(uu & 15), fy = static_cast<u32>(vv & 15);
        const u32 ux0 = static_cast<u32>(wrap(x0, t.wu)) & 2047u, ux1 = static_cast<u32>(wrap(x0 + 1, t.wu)) & 2047u;
        const u32 uy0 = static_cast<u32>(wrap(y0, t.wv)) & 2047u, uy1 = static_cast<u32>(wrap(y0 + 1, t.wv)) & 2047u;
        const u32 c00 = texel_at<PSM>(t, ux0, uy0), c10 = texel_at<PSM>(t, ux1, uy0);
        const u32 c01 = texel_at<PSM>(t, ux0, uy1), c11 = texel_at<PSM>(t, ux1, uy1);
        const u32 w00 = (16u - fx) * (16u - fy), w10 = fx * (16u - fy), w01 = (16u - fx) * fy, w11 = fx * fy;
        // Two channels per multiply: a channel sum is at most 255 * 256 < 2^16, so the pairs never carry.
        constexpr u32 M = 0x00FF00FFu;
        const u32 even = (((c00 & M) * w00 + (c10 & M) * w10 + (c01 & M) * w01 + (c11 & M) * w11) >> 8) & M;
        const u32 odd = ((((c00 >> 8) & M) * w00 + ((c10 >> 8) & M) * w10 + ((c01 >> 8) & M) * w01 +
                          ((c11 >> 8) & M) * w11) >> 8) & M;
        return even | (odd << 8);
    }
}

template <u32 PSM, bool LINEAR>
u32 sample_fast(const TexCtx& t, s32 u16ths, s32 v16ths, float) noexcept {
    return sample_static<PSM, LINEAR>(t, u16ths, v16ths);
}

u32 sample_reference(const TexCtx& t, s32 u16ths, s32 v16ths, float q) noexcept {
    return ref::sample(*t.mem, *t.clut, *t.ts, u16ths, v16ths, q);
}

template <u32 PSM>
void bind_sampler(TexCtx& t, bool linear) noexcept {
    t.sample = linear ? &sample_fast<PSM, true> : &sample_fast<PSM, false>;
    t.static_psm = PSM;
    t.linear = linear;
}

void init_tex(TexCtx& t, const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& ts) noexcept {
    t.mem = &mem;
    t.clut = &clut;
    t.ts = &ts;
    t.vram = mem.data();
    const TexLevel& L = ts.level[0];
    t.scale_u = static_cast<double>(1u << L.tw);
    t.scale_v = static_cast<double>(1u << L.th);
    t.sample = &sample_reference;

    // Which filter level 0 gets, if the LOD cannot change it (ref::sample with MXL = 0: every MMIN path ends at
    // level 0, linear for MMIN 1/4/5, nearest otherwise; LOD <= 0 selects MMAG).
    if (ts.mxl != 0 || !psm_valid(ts.psm)) return;
    const bool min_linear = ts.mmin == 1 || ts.mmin == 4 || ts.mmin == 5;
    bool linear;
    if (ts.mmag_linear == min_linear) linear = min_linear;
    else if (ts.lcm) linear = (ts.k16 / 16.0 <= 0.0) ? ts.mmag_linear : min_linear;
    else return;

    t.ta0 = ts.ta0;
    t.ta1 = ts.ta1;
    t.aem = ts.aem;
    t.wu = make_wrap(ts.wms, L.tw, ts.minu, ts.maxu);
    t.wv = make_wrap(ts.wmt, L.th, ts.minv, ts.maxv);
    t.base = L.tbp * kBlockBytes;
    t.bw = L.tbw;
    const SwizzleTables& T = swizzle_tables();
    switch (ts.psm) {
    case 0x13: case 0x1B:
        for (u32 i = 0; i < 256; ++i) t.pal[i] = clut_entry(clut, ts, i, true);
        break;
    case 0x14: case 0x24: case 0x2C:
        for (u32 i = 0; i < 16; ++i) t.pal[i] = clut_entry(clut, ts, i, false);
        break;
    default: break;
    }
    switch (ts.psm) {
    case 0x00: t.tbl = &T.ct32[0][0]; bind_sampler<0x00>(t, linear); break;
    case 0x01: t.tbl = &T.ct32[0][0]; bind_sampler<0x01>(t, linear); break;
    case 0x1B: t.tbl = &T.ct32[0][0]; bind_sampler<0x1B>(t, linear); break;
    case 0x24: t.tbl = &T.ct32[0][0]; bind_sampler<0x24>(t, linear); break;
    case 0x2C: t.tbl = &T.ct32[0][0]; bind_sampler<0x2C>(t, linear); break;
    case 0x30: t.tbl = &T.z32[0][0]; bind_sampler<0x30>(t, linear); break;
    case 0x31: t.tbl = &T.z32[0][0]; bind_sampler<0x31>(t, linear); break;
    case 0x02: t.tbl = &T.ct16[0][0]; bind_sampler<0x02>(t, linear); break;
    case 0x0A: t.tbl = &T.ct16s[0][0]; bind_sampler<0x0A>(t, linear); break;
    case 0x32: t.tbl = &T.z16[0][0]; bind_sampler<0x32>(t, linear); break;
    case 0x3A: t.tbl = &T.z16s[0][0]; bind_sampler<0x3A>(t, linear); break;
    case 0x13: t.tbl = &T.t8[0][0]; t.bw = L.tbw >> 1; bind_sampler<0x13>(t, linear); break;
    case 0x14: t.tbl = &T.t4[0][0]; t.bw = L.tbw >> 1; bind_sampler<0x14>(t, linear); break;
    default: break;
    }
}

// The sampler a pixel loop is instantiated with: no texture, a static PSM/filter (inlined), or whatever TexCtx
// bound (an indirect call: the other formats, and the reference for mipmapped / LOD-dependent states).
struct NoSampler {
    static constexpr bool kTme = false;
    P3FES_FORCEINLINE u32 operator()(const TexCtx&, s32, s32, float) const noexcept { return 0; }
};
template <u32 PSM, bool LINEAR>
struct StaticSampler {
    static constexpr bool kTme = true;
    P3FES_FORCEINLINE u32 operator()(const TexCtx& t, s32 u, s32 v, float) const noexcept {
        return sample_static<PSM, LINEAR>(t, u, v);
    }
};
struct DynSampler {
    static constexpr bool kTme = true;
    P3FES_FORCEINLINE u32 operator()(const TexCtx& t, s32 u, s32 v, float q) const noexcept { return t.sample(t, u, v, q); }
};

// ---- Frame / Z buffer of the primitive: inline GsMemory::read / write for its PSM ---------------------------

struct Plane {
    u32 psm = 0, bp = 0, bw = 0;
    u32 base = 0;             // bp * 256
    const u16* tbl = nullptr; // in-page table (32-bit or 16-bit geometry)
    u32 kind = 2;             // 0 = 32-bit word formats, 1 = 16-bit formats, 2 = generic (T8/T4/undefined PSM)
    u32 rd_shift = 0, rd_mask = 0xFFFFFFFFu, wr_shift = 0, wr_keep = 0;

    void init(u32 psm_, u32 bp_, u32 bw_) noexcept {
        psm = psm_;
        bp = bp_;
        bw = bw_;
        base = bp_ * kBlockBytes;
        const SwizzleTables& T = swizzle_tables();
        switch (psm) {
        case 0x00: kind = 0; tbl = &T.ct32[0][0]; break;
        case 0x30: kind = 0; tbl = &T.z32[0][0]; break;
        case 0x01: kind = 0; tbl = &T.ct32[0][0]; rd_mask = 0xFFFFFFu; wr_keep = 0xFF000000u; break;
        case 0x31: kind = 0; tbl = &T.z32[0][0]; rd_mask = 0xFFFFFFu; wr_keep = 0xFF000000u; break;
        case 0x1B: kind = 0; tbl = &T.ct32[0][0]; rd_shift = 24; rd_mask = 0xFFu; wr_shift = 24; wr_keep = 0x00FFFFFFu; break;
        case 0x24: kind = 0; tbl = &T.ct32[0][0]; rd_shift = 24; rd_mask = 0xFu; wr_shift = 24; wr_keep = 0xF0FFFFFFu; break;
        case 0x2C: kind = 0; tbl = &T.ct32[0][0]; rd_shift = 28; rd_mask = 0xFu; wr_shift = 28; wr_keep = 0x0FFFFFFFu; break;
        case 0x02: kind = 1; tbl = &T.ct16[0][0]; break;
        case 0x0A: kind = 1; tbl = &T.ct16s[0][0]; break;
        case 0x32: kind = 1; tbl = &T.z16[0][0]; break;
        case 0x3A: kind = 1; tbl = &T.z16s[0][0]; break;
        default: kind = 2; break;
        }
    }
    P3FES_FORCEINLINE u32 addr32(u32 x, u32 y) const noexcept {
        x &= 2047u;
        y &= 2047u;
        return (base + ((y >> 5) * bw + (x >> 6)) * kPageBytes + tbl[(y & 31u) * 64u + (x & 63u)]) & kVramMask;
    }
    P3FES_FORCEINLINE u32 addr16(u32 x, u32 y) const noexcept {
        x &= 2047u;
        y &= 2047u;
        return (base + ((y >> 6) * bw + (x >> 6)) * kPageBytes + tbl[(y & 63u) * 64u + (x & 63u)]) & kVramMask;
    }
    // Raw pixel value, as GsMemory::read gives it. kGeneric: the plane may be of kind 2.
    template <bool kGeneric>
    P3FES_FORCEINLINE u32 read(const GsMemory& m, u32 x, u32 y) const noexcept {
        if constexpr (kGeneric) {
            if (kind == 2) return m.read(psm, bp, bw, x, y);
        }
        if (kind == 0) return (m.read_u32(addr32(x, y)) >> rd_shift) & rd_mask;
        u16 h;
        std::memcpy(&h, m.data() + addr16(x, y), 2);
        return h;
    }
    // As GsMemory::write.
    template <bool kGeneric>
    P3FES_FORCEINLINE void write(GsMemory& m, u32 x, u32 y, u32 value) const noexcept {
        if constexpr (kGeneric) {
            if (kind == 2) {
                m.write(psm, bp, bw, x, y, value);
                return;
            }
        }
        if (kind == 0) {
            const u32 a = addr32(x, y);
            if (wr_keep) m.write_u32(a, (m.read_u32(a) & wr_keep) | ((value << wr_shift) & ~wr_keep));
            else m.write_u32(a, value);
        } else {
            const u16 h = static_cast<u16>(value);
            std::memcpy(m.data() + addr16(x, y), &h, 2);
        }
    }
};

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

// The pixels of a row that satisfy one edge: w(k) = c + k * s >= thr with k = px - px0 (thr 0 for a top-left
// edge, else 1), intersected into [ka, kb].
P3FES_FORCEINLINE void span_limit(s64 c, s64 s, bool top_left, s64& ka, s64& kb) noexcept {
    const s64 thr = top_left ? 0 : 1;
    if (s == 0) {
        if (c < thr) kb = -1;
    } else if (s > 0) {
        ka = std::max(ka, -floor_div(c - thr, s)); // ceil((thr - c) / s)
    } else {
        kb = std::min(kb, floor_div(c - thr, -s));
    }
}

// The per-primitive state and the pixel loops. `Smp` is the sampler (see above); `kGeneric` keeps the generic
// GsMemory paths for frame/Z formats the planes do not address inline.
class Raster {
public:
    Raster(GsMemory& mem, const std::array<u16, 512>& clut, const DrawState& ds, GsCoreStats& stats)
        : mem_(mem), ds_(ds), stats_(stats), zmax_(zmax_of(ds.zpsm)) {
        fb_.init(ds.fpsm, ds.fbp, ds.fbw);
        zb_.init(ds.zpsm, ds.zbp, ds.fbw);
        fb16_ = is16(ds.fpsm);
        fb24_ = is24(ds.fpsm);
        blend_std_ = ds.a == 0 && ds.b == 1 && ds.c == 0 && ds.d == 1;
        if (ds.tme) init_tex(tex_, mem, clut, ds.tex);
    }
    ~Raster() { stats_.pixels_written += pixels_; }

    bool generic_planes() const noexcept { return fb_.kind == 2 || zb_.kind == 2; }
    const TexCtx& tex() const noexcept { return tex_; }

    // kClipped: the caller already restricted (x, y) to the scissor box and tested SCANMSK for the row.
    template <class Smp, bool kGeneric, bool kClipped>
    P3FES_FORCEINLINE void pixel(const Smp& smp, s32 x, s32 y, const PixelIn& in) noexcept;
    // SCANMSK for a row: true when its pixels are drawn.
    bool row_visible(s32 y) const noexcept {
        if (ds_.scanmsk == 2 && (y & 1) == 0) return false;
        if (ds_.scanmsk == 3 && (y & 1) == 1) return false;
        return true;
    }

    template <class Smp, bool kGeneric>
    void sprite(const Smp& smp, const GsVertex& v0, const GsVertex& v1);
    template <class Smp, bool kGeneric>
    void triangle(const Smp& smp, const GsVertex& v0, const GsVertex& v1, const GsVertex& v2);
    template <class Smp, bool kGeneric>
    void line(const Smp& smp, const GsVertex& v0, const GsVertex& v1);
    template <class Smp, bool kGeneric>
    void point(const Smp& smp, const GsVertex& v0);

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
    template <bool kGeneric>
    P3FES_FORCEINLINE u32 read_frame(u32 x, u32 y) const noexcept {
        const u32 raw = fb_.read<kGeneric>(mem_, x, y);
        if (fb16_) {
            return ((raw & 0x1Fu) << 3) | (((raw >> 5) & 0x1Fu) << 11) | (((raw >> 10) & 0x1Fu) << 19) |
                   ((raw & 0x8000u) ? 0x80000000u : 0u);
        }
        if (fb24_) return (raw & 0xFFFFFFu) | 0x80000000u; // no stored alpha: Ad reads as 0x80 (inferred)
        return raw;
    }

    GsMemory& mem_;
    const DrawState& ds_;
    GsCoreStats& stats_;
    u32 zmax_;
    u64 pixels_ = 0;
    Plane fb_, zb_;
    bool fb16_ = false, fb24_ = false, blend_std_ = false;
    TexCtx tex_;
};

template <class Smp, bool kGeneric, bool kClipped>
P3FES_FORCEINLINE void Raster::pixel(const Smp& smp, s32 x, s32 y, const PixelIn& in) noexcept {
    if constexpr (!kClipped) {
        if (x < ds_.scax0 || x > ds_.scax1 || y < ds_.scay0 || y > ds_.scay1) return;
        if (!row_visible(y)) return;
    }

    // The depth test first: the reference runs it after texture, fog and the alpha test, but none of those has a
    // side effect or feeds it, and a rejected pixel writes nothing either way, so the sample is never observable.
    const u32 xu = static_cast<u32>(x), yu = static_cast<u32>(y);
    const u32 z = static_cast<u32>(std::min<u64>(in.z, zmax_));
    if (ds_.ztst != 1) {
        const u32 old = zb_.read<kGeneric>(mem_, xu, yu) & zmax_;
        bool pass;
        switch (ds_.ztst) {
        case 0: pass = false; break;
        case 1: pass = true; break;
        case 2: pass = z >= old; break;
        default: pass = z > old; break;
        }
        if (!pass) return;
    }

    s32 r = in.r, g = in.g, b = in.b, a = in.a;
    if constexpr (Smp::kTme) {
        s32 u, v;
        float q = 1.0f;
        if (ds_.fst) {
            u = in.u;
            v = in.v;
        } else {
            q = in.q;
            const float qq = q != 0.0f ? q : 1.0e-30f;
            u = floor_to_s32(static_cast<double>(in.s / qq) * tex_.scale_u * 16.0);
            v = floor_to_s32(static_cast<double>(in.t / qq) * tex_.scale_v * 16.0);
        }
        const u32 tc = smp(tex_, u, v, q);
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
        dst = read_frame<kGeneric>(xu, yu);
        have_dst = true;
        if (((dst >> 31) & 1u) != static_cast<u32>(ds_.datm)) return;
    }

    ++pixels_;
    if (write_fb) {
        s32 out[3] = {r, g, b};
        if (ds_.abe && (!ds_.pabe || (a & 0x80))) {
            if (!have_dst) dst = read_frame<kGeneric>(xu, yu);
            const s32 cd[3] = {static_cast<s32>(dst & 0xFFu), static_cast<s32>((dst >> 8) & 0xFFu),
                               static_cast<s32>((dst >> 16) & 0xFFu)};
            if (blend_std_) {
                // A = Cs, B = Cd, C = As, D = Cd: (Cs - Cd) * As >> 7 + Cd, the census's dominant equation.
                out[0] = (((r - cd[0]) * a) >> 7) + cd[0];
                out[1] = (((g - cd[1]) * a) >> 7) + cd[1];
                out[2] = (((b - cd[2]) * a) >> 7) + cd[2];
            } else {
                const s32 cs[3] = {r, g, b};
                const s32 ad = static_cast<s32>(dst >> 24);
                const s32 cc = ds_.c == 0 ? a : (ds_.c == 1 ? ad : static_cast<s32>(ds_.fix));
                for (int i = 0; i < 3; ++i) {
                    const s32 va = ds_.a == 0 ? cs[i] : (ds_.a == 1 ? cd[i] : 0);
                    const s32 vb = ds_.b == 0 ? cs[i] : (ds_.b == 1 ? cd[i] : 0);
                    const s32 vd = ds_.d == 0 ? cs[i] : (ds_.d == 1 ? cd[i] : 0);
                    out[i] = (((va - vb) * cc) >> 7) + vd;
                }
            }
        }
        if (ds_.dthe && fb16_) {
            const s32 dm = ds_.dimx[y & 3][x & 3];
            for (s32& c : out) c += dm;
        }
        for (s32& c : out) c = ds_.colclamp ? clamp255(c) : (c & 0xFF);
        u32 alpha = static_cast<u32>(a) & 0xFFu;
        if (ds_.fba) alpha |= 0x80u;
        if (fb16_) {
            u32 value = (static_cast<u32>(out[0]) >> 3) | ((static_cast<u32>(out[1]) >> 3) << 5) |
                        ((static_cast<u32>(out[2]) >> 3) << 10) | ((alpha >> 7) << 15);
            const u32 m = ds_.fbmsk;
            u32 m16 = ((m >> 3) & 0x1Fu) | (((m >> 11) & 0x1Fu) << 5) | (((m >> 19) & 0x1Fu) << 10) | (((m >> 31) & 1u) << 15);
            if (!write_alpha) m16 |= 0x8000u;
            if (m16) value = (value & ~m16) | (fb_.read<kGeneric>(mem_, xu, yu) & m16);
            fb_.write<kGeneric>(mem_, xu, yu, value);
        } else {
            u32 value = static_cast<u32>(out[0]) | (static_cast<u32>(out[1]) << 8) | (static_cast<u32>(out[2]) << 16) |
                        (alpha << 24);
            u32 m = ds_.fbmsk;
            if (!write_alpha || fb24_) m |= 0xFF000000u;
            if (m) value = (value & ~m) | (fb_.read<kGeneric>(mem_, xu, yu) & m);
            fb_.write<kGeneric>(mem_, xu, yu, value);
        }
    }
    if (write_z) zb_.write<kGeneric>(mem_, xu, yu, z);
}

template <class Smp, bool kGeneric>
void Raster::sprite(const Smp& smp, const GsVertex& v0, const GsVertex& v1) {
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
    // U along a row: u0 + floor(ox * (u1 - u0) / dx) with ox advancing by 16 per pixel.
    IncDiv iu;
    if (dx) iu.set_step(16 * static_cast<s64>(u1 - u0), dx);
    for (s32 py = py0; py <= py1; ++py) {
        if (!row_visible(py)) continue;
        const s64 oy = static_cast<s64>(py) * 16 - y0;
        in.v = dy ? vv0 + static_cast<s32>(floor_div(oy * (vv1 - vv0), dy)) : vv0;
        in.t = dy ? t0 + (t1 - t0) * static_cast<float>(static_cast<double>(oy) / static_cast<double>(dy)) : t0;
        if (dx) iu.start((static_cast<s64>(px0) * 16 - x0) * (u1 - u0));
        for (s32 px = px0; px <= px1; ++px) {
            if constexpr (Smp::kTme) {
                const s64 ox = static_cast<s64>(px) * 16 - x0;
                in.u = dx ? u0 + static_cast<s32>(iu.q) : u0;
                in.s = dx ? s0 + (s1 - s0) * static_cast<float>(static_cast<double>(ox) / static_cast<double>(dx)) : s0;
                in.q = dx ? q0 + (q1 - q0) * static_cast<float>(static_cast<double>(ox) / static_cast<double>(dx)) : q1;
            }
            pixel<Smp, kGeneric, true>(smp, px, py, in);
            if (dx) iu.next();
        }
    }
}

template <class Smp, bool kGeneric>
void Raster::triangle(const Smp& smp, const GsVertex& a0, const GsVertex& a1, const GsVertex& a2) {
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

    // Edge functions w_i(sx, sy) are linear in sx: one pixel to the right adds e_ix.
    const s64 e0x = -16 * (Y[2] - Y[1]), e1x = -16 * (Y[0] - Y[2]), e2x = -16 * (Y[1] - Y[0]);
    // Gouraud with three equal vertex colours interpolates to v0's colour exactly (floor(0 / area) = 0): no stepping.
    const bool uniform_rgba = (dr1 | dr2 | dg1 | dg2 | db1 | db2 | da1 | da2) == 0;
    const bool iip = ds_.iip && !uniform_rgba, fge = ds_.fge;
    const bool tex_uv = Smp::kTme && ds_.fst, tex_stq = Smp::kTme && !ds_.fst;
    IncDiv ir, ig, ib, ia, ifog, iu, iv;
    if (iip) {
        ir.set_step(e1x * dr1 + e2x * dr2, area);
        ig.set_step(e1x * dg1 + e2x * dg2, area);
        ib.set_step(e1x * db1 + e2x * db2, area);
        ia.set_step(e1x * da1 + e2x * da2, area);
    }
    if (fge) ifog.set_step(e1x * df1 + e2x * df2, area);
    if (tex_uv) {
        iu.set_step(e1x * du1 + e2x * du2, area);
        iv.set_step(e1x * dv1 + e2x * dv2, area);
    }

    PixelIn in;
    if (!ds_.iip) {
        in.r = last.r;
        in.g = last.g;
        in.b = last.b;
        in.a = last.a;
    } else if (uniform_rgba) {
        in.r = b0.r;
        in.g = b0.g;
        in.b = b0.b;
        in.a = b0.a;
    }
    const s64 sx0 = static_cast<s64>(px0) * 16;
    for (s32 py = py0; py <= py1; ++py) {
        if (!row_visible(py)) continue;
        const s64 sy = static_cast<s64>(py) * 16;
        s64 w0 = (X[2] - X[1]) * (sy - Y[1]) - (Y[2] - Y[1]) * (sx0 - X[1]);
        s64 w1 = (X[0] - X[2]) * (sy - Y[2]) - (Y[0] - Y[2]) * (sx0 - X[2]);
        s64 w2 = (X[1] - X[0]) * (sy - Y[0]) - (Y[1] - Y[0]) * (sx0 - X[0]);
        s64 ka = 0, kb = static_cast<s64>(px1) - px0;
        span_limit(w0, e0x, tl0, ka, kb);
        span_limit(w1, e1x, tl1, ka, kb);
        span_limit(w2, e2x, tl2, ka, kb);
        if (ka > kb) continue;
        w0 += ka * e0x;
        w1 += ka * e1x;
        w2 += ka * e2x;
        if (iip) {
            ir.start(w1 * dr1 + w2 * dr2);
            ig.start(w1 * dg1 + w2 * dg2);
            ib.start(w1 * db1 + w2 * db2);
            ia.start(w1 * da1 + w2 * da2);
        }
        if (fge) ifog.start(w1 * df1 + w2 * df2);
        if (tex_uv) {
            iu.start(w1 * du1 + w2 * du2);
            iv.start(w1 * dv1 + w2 * dv2);
        }
        for (s64 k = ka; k <= kb; ++k) {
            assert(w0 >= (tl0 ? 0 : 1) && w1 >= (tl1 ? 0 : 1) && w2 >= (tl2 ? 0 : 1));
            const s32 px = px0 + static_cast<s32>(k);
            if (iip) {
                in.r = b0.r + static_cast<s32>(ir.q);
                in.g = b0.g + static_cast<s32>(ig.q);
                in.b = b0.b + static_cast<s32>(ib.q);
                in.a = b0.a + static_cast<s32>(ia.q);
            }
            if (fge) in.f = b0.f + static_cast<s32>(ifog.q);
            const double zz = static_cast<double>(b0.z) + (static_cast<double>(w1) * dz1 + static_cast<double>(w2) * dz2) * inv_area;
            in.z = zz <= 0.0 ? 0u : floor_to_u64_positive(zz);
            if (tex_uv) {
                in.u = static_cast<s32>(b0.u) + static_cast<s32>(iu.q);
                in.v = static_cast<s32>(b0.v) + static_cast<s32>(iv.q);
            } else if (tex_stq) {
                const float l1 = static_cast<float>(static_cast<double>(w1) * inv_area);
                const float l2 = static_cast<float>(static_cast<double>(w2) * inv_area);
                in.s = s0 + ds1 * l1 + ds2 * l2;
                in.t = t0 + dt1 * l1 + dt2 * l2;
                in.q = q0 + dq1 * l1 + dq2 * l2;
            }
            pixel<Smp, kGeneric, true>(smp, px, py, in);
            w0 += e0x;
            w1 += e1x;
            w2 += e2x;
            if (iip) {
                ir.next();
                ig.next();
                ib.next();
                ia.next();
            }
            if (fge) ifog.next();
            if (tex_uv) {
                iu.next();
                iv.next();
            }
        }
    }
}

template <class Smp, bool kGeneric>
void Raster::line(const Smp& smp, const GsVertex& v0, const GsVertex& v1) {
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
        if (px >= 0 && py >= 0 && px < 2048 && py < 2048) pixel<Smp, kGeneric, false>(smp, px, py, in);
    }
}

template <class Smp, bool kGeneric>
void Raster::point(const Smp& smp, const GsVertex& v0) {
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
    pixel<Smp, kGeneric, false>(smp, px, py, in);
}

// One primitive with the sampler and plane class decided.
template <class Smp, bool kGeneric>
void draw(Raster& r, const Smp& smp, const DrawState& ds, const GsVertex* v, u32 count) {
    switch (ds.prim) {
    case 0: r.point<Smp, kGeneric>(smp, v[0]); break;
    case 1:
    case 2:
        if (count >= 2) r.line<Smp, kGeneric>(smp, v[0], v[1]);
        break;
    case 3:
    case 4:
    case 5:
        if (count >= 3) r.triangle<Smp, kGeneric>(smp, v[0], v[1], v[2]);
        break;
    case 6:
        if (count >= 2) r.sprite<Smp, kGeneric>(smp, v[0], v[1]);
        break;
    default: break;
    }
}

// Triangles and sprites of the census's texture formats get the sampler inlined (6 instances); everything else
// goes through the TexCtx function pointer.
template <u32 PSM>
bool draw_static(Raster& r, const DrawState& ds, const GsVertex* v, u32 count) {
    if (r.tex().static_psm != PSM || (ds.prim != 6 && (ds.prim < 3 || ds.prim > 5))) return false;
    if (r.tex().linear) draw<StaticSampler<PSM, true>, false>(r, StaticSampler<PSM, true>{}, ds, v, count);
    else draw<StaticSampler<PSM, false>, false>(r, StaticSampler<PSM, false>{}, ds, v, count);
    return true;
}

void fill_levels(TexState& t, u64 tex0, u64 tex1, u64 mip1, u64 mip2) {
    const u32 tw = std::min<u32>(bits(tex0, 26, 4), 10u), th = std::min<u32>(bits(tex0, 30, 4), 10u);
    t.level[0] = {bits(tex0, 0, 14), bits(tex0, 14, 6), tw, th};
    const bool mtba = ((tex1 >> 9) & 1u) != 0;
    for (u32 n = 1; n < 7; ++n) {
        TexLevel& L = t.level[n];
        L.tw = tw > n ? tw - n : 0;
        L.th = th > n ? th - n : 0;
        if (n <= 3) {
            const u64 m = mip1 >> ((n - 1) * 20);
            L.tbp = bits(m, 0, 14);
            L.tbw = bits(m, 14, 6);
        } else {
            const u64 m = mip2 >> ((n - 4) * 20);
            L.tbp = bits(m, 0, 14);
            L.tbw = bits(m, 14, 6);
        }
        if (mtba && n <= 3) {
            // Inferred automatic layout: each level follows the previous one, half its buffer width.
            const TexLevel& P = t.level[n - 1];
            const u32 bytes = static_cast<u32>(((1ull << P.tw) * (1ull << P.th) * psm_bits(t.psm)) / 8u);
            L.tbp = (P.tbp + std::max<u32>(bytes / kBlockBytes, 1u)) & 0x3FFFu;
            L.tbw = std::max<u32>(P.tbw / 2u, 1u);
        }
    }
}


} // namespace

DrawState decode_draw_state(const GsRegs& r) {
    DrawState ds;
    ds.prim = static_cast<u32>(r.prim) & 7u;
    const u64 attr = (r.prmodecont & 1u) ? r.prim : r.prmode;
    ds.iip = (attr >> 3) & 1u;
    ds.tme = (attr >> 4) & 1u;
    ds.fge = (attr >> 5) & 1u;
    ds.abe = (attr >> 6) & 1u;
    ds.aa1 = (attr >> 7) & 1u;
    ds.fst = (attr >> 8) & 1u;
    ds.ctxt = static_cast<u32>((attr >> 9) & 1u);
    const GsContextRegs& c = r.ctx[ds.ctxt];

    ds.fbp = bits(c.frame, 0, 9) * kBlocksPerPage;
    ds.fbw = bits(c.frame, 16, 6);
    ds.fpsm = bits(c.frame, 24, 6);
    ds.fbmsk = bits(c.frame, 32, 32);
    ds.zbp = bits(c.zbuf, 0, 9) * kBlocksPerPage;
    ds.zpsm = 0x30u | bits(c.zbuf, 24, 4);
    ds.zmsk = ((c.zbuf >> 32) & 1u) != 0;

    ds.ate = (c.test & 1u) != 0;
    ds.atst = bits(c.test, 1, 3);
    ds.aref = bits(c.test, 4, 8);
    ds.afail = bits(c.test, 12, 2);
    ds.date = ((c.test >> 14) & 1u) != 0;
    ds.datm = ((c.test >> 15) & 1u) != 0;
    ds.zte = ((c.test >> 16) & 1u) != 0;
    ds.ztst = ds.zte ? bits(c.test, 17, 2) : 1u; // ZTE = 0 (documented as prohibited): no depth test, i.e. ALWAYS

    ds.a = bits(c.alpha, 0, 2);
    ds.b = bits(c.alpha, 2, 2);
    ds.c = bits(c.alpha, 4, 2);
    ds.d = bits(c.alpha, 6, 2);
    ds.fix = bits(c.alpha, 32, 8);
    ds.pabe = (r.pabe & 1u) != 0;
    ds.fba = (c.fba & 1u) != 0;
    ds.colclamp = (r.colclamp & 1u) != 0;
    ds.dthe = (r.dthe & 1u) != 0;
    for (u32 i = 0; i < 16; ++i) ds.dimx[i / 4][i % 4] = sign_extend(bits(r.dimx, i * 4, 3), 3);

    ds.scax0 = static_cast<s32>(bits(c.scissor, 0, 11));
    ds.scax1 = static_cast<s32>(bits(c.scissor, 16, 11));
    ds.scay0 = static_cast<s32>(bits(c.scissor, 32, 11));
    ds.scay1 = static_cast<s32>(bits(c.scissor, 48, 11));
    ds.ofx = static_cast<s32>(bits(c.xyoffset, 0, 16));
    ds.ofy = static_cast<s32>(bits(c.xyoffset, 32, 16));
    ds.scanmsk = static_cast<u32>(r.scanmsk & 3u);

    TexState& t = ds.tex;
    t.psm = bits(c.tex0, 20, 6);
    t.tcc = ((c.tex0 >> 34) & 1u) != 0;
    t.tfx = bits(c.tex0, 35, 2);
    t.cpsm = bits(c.tex0, 51, 4);
    t.csa = bits(c.tex0, 56, 5);
    t.lcm = (c.tex1 & 1u) != 0;
    t.mxl = bits(c.tex1, 2, 3);
    t.mmag_linear = ((c.tex1 >> 5) & 1u) != 0;
    t.mmin = bits(c.tex1, 6, 3);
    t.l = bits(c.tex1, 19, 2);
    t.k16 = sign_extend(bits(c.tex1, 32, 12), 12);
    fill_levels(t, c.tex0, c.tex1, c.miptbp1, c.miptbp2);
    t.wms = bits(c.clamp, 0, 2);
    t.wmt = bits(c.clamp, 2, 2);
    t.minu = bits(c.clamp, 4, 10);
    t.maxu = bits(c.clamp, 14, 10);
    t.minv = bits(c.clamp, 24, 10);
    t.maxv = bits(c.clamp, 34, 10);
    t.ta0 = bits(r.texa, 0, 8);
    t.aem = ((r.texa >> 15) & 1u) != 0;
    t.ta1 = bits(r.texa, 32, 8);
    ds.fogcol = static_cast<u32>(r.fogcol & 0xFFFFFFu);
    return ds;
}


void rasterize(GsMemory& mem, const std::array<u16, 512>& clut, const DrawState& ds, const GsVertex* v, u32 count,
               GsCoreStats& stats) {
    if (!psm_valid(ds.fpsm) || (ds.tme && !psm_valid(ds.tex.psm))) ++stats.invalid_psm;
    Raster r(mem, clut, ds, stats);
    if (r.generic_planes()) {
        if (ds.tme) draw<DynSampler, true>(r, DynSampler{}, ds, v, count);
        else draw<NoSampler, true>(r, NoSampler{}, ds, v, count);
        return;
    }
    if (!ds.tme) {
        draw<NoSampler, false>(r, NoSampler{}, ds, v, count);
        return;
    }
    if (draw_static<0x13>(r, ds, v, count) || draw_static<0x14>(r, ds, v, count) || draw_static<0x00>(r, ds, v, count)) return;
    draw<DynSampler, false>(r, DynSampler{}, ds, v, count);
}

u32 sample_texture(const GsMemory& mem, const std::array<u16, 512>& clut, const TexState& t, s32 u16ths, s32 v16ths,
                   bool linear, u32 level) {
    return ref::sample_level(mem, clut, t, u16ths, v16ths, linear, level);
}

} // namespace p3fes::gs::detail
