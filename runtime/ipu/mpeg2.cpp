// MPEG-1/MPEG-2 reconstruction pieces of the IPU (scans, inverse quantisation, IDCT, macroblock assembly) and its
// colour-space conversion / packing back end. Written for p3fes-port from ISO/IEC 13818-2 §6.3.11, §7.3-7.5,
// Annex A and ISO/IEC 11172-2 §2.4.4; the CSC coefficients and the alpha-threshold rule were cross-checked against
// snuri00/ps2-web-recomp @ c0f476e runtime/src/ipu/ipu.cpp `convert` (MIT) — no upstream text copied (see
// runtime/include/p3fes/ipu/THIRD_PARTY.md). Hardware-unverified conventions are listed in runtime/ipu/README.md.
#include "p3fes/ipu/mpeg2.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>

// The IDCT must not be contracted into FMAs (results must not depend on the compiler or the target ISA).
#if defined(__clang__)
#pragma clang fp contract(off)
#elif defined(_MSC_VER)
#pragma fp_contract(off)
#endif

namespace p3fes::ipu::mpeg2 {

namespace {

// Figure 7-2 / Figure 7-3 of ISO/IEC 13818-2 as printed: the scan position at each raster position [v][u].
constexpr u8 kZigzagFigure[64] = {
    0,  1,  5,  6,  14, 15, 27, 28,
    2,  4,  7,  13, 16, 26, 29, 42,
    3,  8,  12, 17, 25, 30, 41, 43,
    9,  11, 18, 24, 31, 40, 44, 53,
    10, 19, 23, 32, 39, 45, 52, 54,
    20, 22, 33, 38, 46, 51, 55, 60,
    21, 34, 37, 47, 50, 56, 59, 61,
    35, 36, 48, 49, 57, 58, 62, 63,
};
constexpr u8 kAlternateFigure[64] = {
    0,  4,  6,  20, 22, 36, 38, 52,
    1,  5,  7,  21, 23, 37, 39, 53,
    2,  8,  19, 24, 34, 40, 50, 54,
    3,  9,  18, 25, 35, 41, 51, 55,
    10, 17, 26, 30, 42, 46, 56, 60,
    11, 16, 27, 31, 43, 47, 57, 61,
    12, 15, 28, 32, 44, 48, 58, 62,
    13, 14, 29, 33, 45, 49, 59, 63,
};

constexpr std::array<u8, 64> invert(const u8 (&figure)[64]) {
    std::array<u8, 64> scan{};
    for (unsigned r = 0; r < 64; ++r) scan[figure[r]] = static_cast<u8>(r);
    return scan;
}
constexpr std::array<u8, 64> kZigzagArr = invert(kZigzagFigure);
constexpr std::array<u8, 64> kAlternateArr = invert(kAlternateFigure);

// cos(k pi / 16), k = 0..8, correctly rounded decimal literals (the double nearest to each value).
constexpr double kCos16[9] = {
    1.0,
    0.98078528040323044912618223613424,
    0.92387953251128675612818318939679,
    0.83146961230254523707878837761791,
    0.70710678118654752440084436210485,
    0.55557023301960222474283081394853,
    0.38268343236508977172845998403040,
    0.19509032201612826784828486847702,
    0.0,
};
constexpr double kHalfInvSqrt2 = 0.35355339059327376220042218105242;  // C(0) / 2 = 1 / (2 sqrt 2)

// cos(m pi / 16) for any m >= 0 from the first-quadrant table.
constexpr double cos16(unsigned m) {
    m &= 31u;
    if (m <= 8) return kCos16[m];
    if (m <= 16) return -kCos16[16 - m];
    if (m <= 24) return -kCos16[m - 16];
    return kCos16[32 - m];
}

struct IdctBasis {
    double k[64][64];  // [coefficient v*8+u][pixel y*8+x]
    IdctBasis() {
        double c[8][8];  // c[x][u] = C(u)/2 cos((2x+1) u pi/16)
        for (unsigned x = 0; x < 8; ++x)
            for (unsigned u = 0; u < 8; ++u) c[x][u] = u == 0 ? kHalfInvSqrt2 : 0.5 * cos16((2 * x + 1) * u);
        for (unsigned v = 0; v < 8; ++v)
            for (unsigned u = 0; u < 8; ++u)
                for (unsigned y = 0; y < 8; ++y)
                    for (unsigned x = 0; x < 8; ++x) k[v * 8 + u][y * 8 + x] = c[y][v] * c[x][u];
        // The four basis functions with u, v in {0, 4} are exactly +-1/8 (C(0)/2 = 0.5 cos(pi/4) = 1/(2 sqrt 2));
        // pin them so DC-only and these blocks are exact rational sums (deterministic .5 ties, round half up).
        for (unsigned v = 0; v < 8; v += 4)
            for (unsigned u = 0; u < 8; u += 4)
                for (unsigned p = 0; p < 64; ++p) k[v * 8 + u][p] = k[v * 8 + u][p] < 0 ? -0.125 : 0.125;
    }
};

const IdctBasis& basis() {
    static const IdctBasis b;
    return b;
}

inline int clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

} // namespace

const u8 kZigzag[64] = {
#define P3FES_E(i) kZigzagArr[i]
    P3FES_E(0),  P3FES_E(1),  P3FES_E(2),  P3FES_E(3),  P3FES_E(4),  P3FES_E(5),  P3FES_E(6),  P3FES_E(7),
    P3FES_E(8),  P3FES_E(9),  P3FES_E(10), P3FES_E(11), P3FES_E(12), P3FES_E(13), P3FES_E(14), P3FES_E(15),
    P3FES_E(16), P3FES_E(17), P3FES_E(18), P3FES_E(19), P3FES_E(20), P3FES_E(21), P3FES_E(22), P3FES_E(23),
    P3FES_E(24), P3FES_E(25), P3FES_E(26), P3FES_E(27), P3FES_E(28), P3FES_E(29), P3FES_E(30), P3FES_E(31),
    P3FES_E(32), P3FES_E(33), P3FES_E(34), P3FES_E(35), P3FES_E(36), P3FES_E(37), P3FES_E(38), P3FES_E(39),
    P3FES_E(40), P3FES_E(41), P3FES_E(42), P3FES_E(43), P3FES_E(44), P3FES_E(45), P3FES_E(46), P3FES_E(47),
    P3FES_E(48), P3FES_E(49), P3FES_E(50), P3FES_E(51), P3FES_E(52), P3FES_E(53), P3FES_E(54), P3FES_E(55),
    P3FES_E(56), P3FES_E(57), P3FES_E(58), P3FES_E(59), P3FES_E(60), P3FES_E(61), P3FES_E(62), P3FES_E(63),
#undef P3FES_E
};
const u8 kAlternate[64] = {
#define P3FES_E(i) kAlternateArr[i]
    P3FES_E(0),  P3FES_E(1),  P3FES_E(2),  P3FES_E(3),  P3FES_E(4),  P3FES_E(5),  P3FES_E(6),  P3FES_E(7),
    P3FES_E(8),  P3FES_E(9),  P3FES_E(10), P3FES_E(11), P3FES_E(12), P3FES_E(13), P3FES_E(14), P3FES_E(15),
    P3FES_E(16), P3FES_E(17), P3FES_E(18), P3FES_E(19), P3FES_E(20), P3FES_E(21), P3FES_E(22), P3FES_E(23),
    P3FES_E(24), P3FES_E(25), P3FES_E(26), P3FES_E(27), P3FES_E(28), P3FES_E(29), P3FES_E(30), P3FES_E(31),
    P3FES_E(32), P3FES_E(33), P3FES_E(34), P3FES_E(35), P3FES_E(36), P3FES_E(37), P3FES_E(38), P3FES_E(39),
    P3FES_E(40), P3FES_E(41), P3FES_E(42), P3FES_E(43), P3FES_E(44), P3FES_E(45), P3FES_E(46), P3FES_E(47),
    P3FES_E(48), P3FES_E(49), P3FES_E(50), P3FES_E(51), P3FES_E(52), P3FES_E(53), P3FES_E(54), P3FES_E(55),
    P3FES_E(56), P3FES_E(57), P3FES_E(58), P3FES_E(59), P3FES_E(60), P3FES_E(61), P3FES_E(62), P3FES_E(63),
#undef P3FES_E
};

// §6.3.11 default intra_quantiser_matrix, raster order.
const u8 kDefaultIntraMatrix[64] = {
    8,  16, 19, 22, 26, 27, 29, 34,
    16, 16, 22, 24, 27, 29, 34, 37,
    19, 22, 26, 27, 29, 34, 34, 38,
    22, 22, 26, 27, 29, 34, 37, 40,
    22, 26, 27, 29, 32, 35, 40, 48,
    26, 27, 29, 32, 35, 40, 48, 58,
    26, 27, 29, 34, 38, 46, 56, 69,
    27, 29, 35, 38, 46, 56, 69, 83,
};

// Table 7-6 (q_scale_type = 1).
const u8 kNonLinearScale[32] = {0,  1,  2,  3,  4,  5,  6,  7,  8,  10, 12, 14, 16, 18, 20, 22,
                                24, 28, 32, 36, 40, 44, 48, 52, 56, 64, 72, 80, 88, 96, 104, 112};

int quantiser_scale(unsigned code, bool q_scale_type, bool mpeg1) {
    code &= 31u;
    if (mpeg1 || !q_scale_type) return static_cast<int>(code) * 2;
    return kNonLinearScale[code];
}

void inverse_quantize(const s32 qf[64], const QuantParams& p, s32 out[64]) {
    const u8* scan = p.alternate_scan ? kAlternate : kZigzag;
    std::fill(out, out + 64, 0);
    s32 sum = 0;
    for (unsigned k = 0; k < 64; ++k) {
        const s32 v = qf[k];
        const unsigned r = scan[k];
        s32 x;
        if (p.intra && k == 0) {
            x = v * (p.mpeg1 ? 8 : (8 >> (p.dc_precision & 3u)));
        } else {
            if (v == 0) continue;
            const s32 sign = v > 0 ? 1 : -1;
            const s32 w = p.matrix[r];
            // C++ integer division truncates toward zero, as the standard's "/" does.
            x = p.intra ? (2 * v * w * p.quantiser_scale) / 32 : ((2 * v + sign) * w * p.quantiser_scale) / 32;
            if (p.mpeg1 && x != 0 && (x & 1) == 0) x -= sign;  // ISO 11172-2 oddification (before saturation)
        }
        x = clamp(x, -2048, 2047);
        out[r] = x;
        sum += x;
    }
    // §7.4.4 mismatch control (MPEG-2 only): an even sum toggles the LSB of F[7][7].
    if (!p.mpeg1 && (sum & 1) == 0) out[63] += (out[63] & 1) ? -1 : 1;
}

void idct(const s32 in[64], s16 out[64]) {
    const IdctBasis& b = basis();
    double acc[64] = {};
    for (unsigned c = 0; c < 64; ++c) {
        if (in[c] == 0) continue;
        const double f = static_cast<double>(in[c]);
        const double* k = b.k[c];
        for (unsigned p = 0; p < 64; ++p) acc[p] += f * k[p];
    }
    for (unsigned p = 0; p < 64; ++p) {
        const double s = std::floor(acc[p] + 0.5);
        const int v = s < -256.0 ? -256 : s > 255.0 ? 255 : static_cast<int>(s);
        out[p] = static_cast<s16>(v);
    }
}

void assemble_raw16(const s16 blocks[6][64], bool field_dct, s16 out[384]) {
    for (unsigned i = 0; i < 8; ++i) {
        const unsigned top = field_dct ? 2 * i : i;
        const unsigned bottom = field_dct ? 2 * i + 1 : i + 8;
        std::memcpy(out + top * 16, blocks[0] + i * 8, 16);
        std::memcpy(out + top * 16 + 8, blocks[1] + i * 8, 16);
        std::memcpy(out + bottom * 16, blocks[2] + i * 8, 16);
        std::memcpy(out + bottom * 16 + 8, blocks[3] + i * 8, 16);
    }
    std::memcpy(out + 256, blocks[4], 128);
    std::memcpy(out + 320, blocks[5], 128);
}

void ycbcr_to_rgb(int y, int cb, int cr, int& r, int& g, int& b) {
    const int lum = 149 * std::max(0, y - 16);
    const int u = cb - 128, v = cr - 128;
    // >> on negative values is arithmetic (C++20).
    r = clamp((lum + 204 * v + 64) >> 7, 0, 255);
    g = clamp((lum - 50 * u - 104 * v + 64) >> 7, 0, 255);
    b = clamp((lum + 258 * u + 64) >> 7, 0, 255);
}

u8 threshold_alpha(int r, int g, int b, unsigned th0, unsigned th1) {
    const int t0 = static_cast<int>(th0), t1 = static_cast<int>(th1);
    if (r < t0 && g < t0 && b < t0) return 0x00;
    if (r < t1 && g < t1 && b < t1) return 0x40;
    return 0x80;
}

const s8 kDither[4][4] = {
    {-4, 2, -3, 3},
    {0, -2, 1, -1},
    {-3, 3, -4, 2},
    {1, -1, 0, -2},
};

namespace {
inline int to5(int c, bool dither, unsigned x, unsigned y) {
    if (dither) c = clamp(c + kDither[y & 3u][x & 3u], 0, 255);
    return c >> 3;
}
} // namespace

u16 rgb16_of(int r, int g, int b, u8 a, bool dither, unsigned x, unsigned y) {
    return static_cast<u16>(to5(r, dither, x, y) | (to5(g, dither, x, y) << 5) | (to5(b, dither, x, y) << 10) |
                            ((a & 0x80u) ? 0x8000u : 0u));
}

void csc(const u8 raw8[384], const CscParams& p, u8* out) {
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) {
            const unsigned c = (y >> 1) * 8 + (x >> 1);
            int r = 0, g = 0, b = 0;
            ycbcr_to_rgb(raw8[y * 16 + x], raw8[256 + c], raw8[320 + c], r, g, b);
            const u8 a = threshold_alpha(r, g, b, p.th0, p.th1);
            const unsigned i = y * 16 + x;
            if (p.rgb16) {
                const u16 v = rgb16_of(r, g, b, a, p.dither, x, y);
                out[2 * i] = static_cast<u8>(v);
                out[2 * i + 1] = static_cast<u8>(v >> 8);
            } else {
                out[4 * i] = static_cast<u8>(r);
                out[4 * i + 1] = static_cast<u8>(g);
                out[4 * i + 2] = static_cast<u8>(b);
                out[4 * i + 3] = a;
            }
        }
}

void pack(const u8 rgb32[1024], bool rgb16, bool dither, const u16 vqclut[16], u8* out) {
    if (!rgb16) std::memset(out, 0, kIndx4Bytes);
    for (unsigned y = 0; y < 16; ++y)
        for (unsigned x = 0; x < 16; ++x) {
            const unsigned i = y * 16 + x;
            const int r = rgb32[4 * i], g = rgb32[4 * i + 1], b = rgb32[4 * i + 2];
            const u8 a = rgb32[4 * i + 3];
            if (rgb16) {
                const u16 v = rgb16_of(r, g, b, a, dither, x, y);
                out[2 * i] = static_cast<u8>(v);
                out[2 * i + 1] = static_cast<u8>(v >> 8);
                continue;
            }
            const int r5 = to5(r, dither, x, y), g5 = to5(g, dither, x, y), b5 = to5(b, dither, x, y);
            unsigned best = 0;
            int best_d = 1 << 30;
            for (unsigned e = 0; e < 16; ++e) {
                const int er = vqclut[e] & 31, eg = (vqclut[e] >> 5) & 31, eb = (vqclut[e] >> 10) & 31;
                const int d = (r5 - er) * (r5 - er) + (g5 - eg) * (g5 - eg) + (b5 - eb) * (b5 - eb);
                if (d < best_d) {
                    best_d = d;
                    best = e;
                }
            }
            out[i >> 1] = static_cast<u8>(out[i >> 1] | (best << ((i & 1u) * 4u)));
        }
}

} // namespace p3fes::ipu::mpeg2
