// Scans, inverse quantisation (§7.4 / ISO 11172-2 §2.4.4) with hand-computed vectors, and the IDCT against an
// independent double-precision reference (separable, std::cos) on synthetic blocks, with IEEE 1180 statistics.
#include "ipu_test_util.h"

#include <algorithm>
#include <cmath>
#include <numeric>

using namespace it;
using namespace p3fes::ipu::mpeg2;

namespace {

// The reference the IDCT is checked against: the defining sum, separable, basis from std::cos at run time.
void ref_idct(const s32 F[64], double out[64]) {
    const double pi = std::acos(-1.0);
    double c[8][8];
    for (int x = 0; x < 8; ++x)
        for (int u = 0; u < 8; ++u) c[x][u] = (u == 0 ? std::sqrt(0.125) : 0.5) * std::cos((2 * x + 1) * u * pi / 16.0);
    double rows[8][8];  // [v][x]
    for (int v = 0; v < 8; ++v)
        for (int x = 0; x < 8; ++x) {
            double s = 0;
            for (int u = 0; u < 8; ++u) s += c[x][u] * F[v * 8 + u];
            rows[v][x] = s;
        }
    for (int y = 0; y < 8; ++y)
        for (int x = 0; x < 8; ++x) {
            double s = 0;
            for (int v = 0; v < 8; ++v) s += c[y][v] * rows[v][x];
            out[y * 8 + x] = s;
        }
}

int round_sat(double s) {
    const double r = std::floor(s + 0.5);
    return r < -256 ? -256 : r > 255 ? 255 : static_cast<int>(r);
}

// IEEE Std 1180-1990 Annex A random number generator.
struct Ieee1180Rand {
    long long randx = 1;
    long next(long L, long H) {
        randx = (randx * 1103515245 + 12345) & 0xFFFFFFFFll;
        const long long i = randx & 0x7FFFFFFEll;
        const double x = static_cast<double>(i) / static_cast<double>(0x7FFFFFFF) * static_cast<double>(L + H + 1);
        return static_cast<long>(x) - L;
    }
};

QuantParams qp(bool intra, int qs, bool mpeg1 = false, unsigned dcp = 0, const u8* m = nullptr) {
    static u8 flat16[64];
    std::fill(std::begin(flat16), std::end(flat16), u8{16});
    QuantParams p;
    p.intra = intra;
    p.mpeg1 = mpeg1;
    p.dc_precision = dcp;
    p.quantiser_scale = qs;
    p.matrix = m ? m : (intra ? kDefaultIntraMatrix : flat16);
    return p;
}

} // namespace

TEST_CASE("scans: zigzag = the diagonal walk of Figure 7-2, alternate = Figure 7-3, both permutations") {
    // Diagonal walk: even diagonals run up-right (v decreasing), odd ones down-left.
    std::vector<u8> walk;
    for (int d = 0; d < 15; ++d) {
        const int lo = std::max(0, d - 7), hi = std::min(d, 7);
        if (d % 2 == 0)
            for (int v = hi; v >= lo; --v) walk.push_back(static_cast<u8>(v * 8 + (d - v)));
        else
            for (int v = lo; v <= hi; ++v) walk.push_back(static_cast<u8>(v * 8 + (d - v)));
    }
    REQUIRE(walk.size() == 64);
    for (unsigned k = 0; k < 64; ++k) CHECK(kZigzag[k] == walk[k]);
    const u8 alt_head[16] = {0, 8, 16, 24, 1, 9, 2, 10, 17, 25, 32, 40, 48, 56, 57, 49};
    for (unsigned k = 0; k < 16; ++k) CHECK(kAlternate[k] == alt_head[k]);
    std::vector<int> a(64, 0), z(64, 0);
    for (unsigned k = 0; k < 64; ++k) {
        ++a[kAlternate[k]];
        ++z[kZigzag[k]];
    }
    for (int i = 0; i < 64; ++i) {
        CHECK(a[static_cast<std::size_t>(i)] == 1);
        CHECK(z[static_cast<std::size_t>(i)] == 1);
    }
    // The default intra matrix in zigzag order — the order SETIQ consumes (the SDK's copy at ELF 0x77F340/0x77F410
    // holds these bytes, obs).
    const u8 zz_head[16] = {8, 16, 16, 19, 16, 19, 22, 22, 22, 22, 22, 22, 26, 24, 26, 27};
    for (unsigned k = 0; k < 16; ++k) CHECK(kDefaultIntraMatrix[kZigzag[k]] == zz_head[k]);
    CHECK(kDefaultIntraMatrix[kZigzag[63]] == 83);
}

TEST_CASE("quantiser_scale: linear 2 x code, Table 7-6 non-linear, MPEG-1 = code (in MPEG-2 units 2 x code)") {
    CHECK(quantiser_scale(5, false, false) == 10);
    CHECK(quantiser_scale(5, true, false) == 5);
    CHECK(quantiser_scale(9, true, false) == 10);
    CHECK(quantiser_scale(17, true, false) == 28);
    CHECK(quantiser_scale(31, true, false) == 112);
    CHECK(quantiser_scale(5, true, true) == 10);  // MPEG-1 has no q_scale_type
    CHECK(quantiser_scale(31, false, false) == 62);
}

TEST_CASE("inverse quantisation, MPEG-2: intra DC multiplier, AC formula with truncation, mismatch control") {
    s32 qf[64] = {}, f[64] = {};
    // intra DC = 130: x8 / x4 / x2 / x1 for intra_dc_precision 0..3; sum even -> F[7][7] = +1
    qf[0] = 130;
    for (unsigned dcp = 0; dcp < 4; ++dcp) {
        inverse_quantize(qf, qp(true, 2, false, dcp), f);
        CHECK(f[0] == (130 * 8) >> dcp);
        CHECK(f[63] == 1);
    }
    qf[0] = 131;  // precision 3: 131 is odd -> no toggle
    inverse_quantize(qf, qp(true, 2, false, 3), f);
    CHECK(f[0] == 131);
    CHECK(f[63] == 0);
    // intra AC: (2 QF W qs) / 32, scan position 1 = raster 1, W = 16; qs 8: (2*3*16*8)/32 = 24
    qf[0] = 128;
    qf[1] = 3;
    inverse_quantize(qf, qp(true, 8), f);
    CHECK(f[1] == 24);
    qf[1] = -3;
    inverse_quantize(qf, qp(true, 8), f);
    CHECK(f[1] == -24);
    // truncation toward zero: scan 5 = raster 2, W = 19, qs 2: 76/32 = 2.375 -> +2 / -2
    std::fill(std::begin(qf), std::end(qf), 0);
    qf[0] = 128;
    qf[5] = 1;
    inverse_quantize(qf, qp(true, 2), f);
    CHECK(kZigzag[5] == 2);
    CHECK(f[2] == 2);
    qf[5] = -1;
    inverse_quantize(qf, qp(true, 2), f);
    CHECK(f[2] == -2);
    // non-intra: ((2 QF + sign) W qs) / 32, W = 16: QF 1, qs 16 -> 24; QF -1 -> -24; QF 2, qs 2 -> 5; QF 1, W 20 -> 3
    std::fill(std::begin(qf), std::end(qf), 0);
    qf[0] = 1;
    inverse_quantize(qf, qp(false, 16), f);
    CHECK(f[0] == 24);
    qf[0] = -1;
    inverse_quantize(qf, qp(false, 16), f);
    CHECK(f[0] == -24);
    qf[0] = 2;
    inverse_quantize(qf, qp(false, 2), f);
    CHECK(f[0] == 5);  // sum 5 odd: F[7][7] stays 0
    CHECK(f[63] == 0);
    u8 m20[64];
    std::fill(std::begin(m20), std::end(m20), u8{20});
    qf[0] = 1;
    inverse_quantize(qf, qp(false, 2, false, 0, m20), f);
    CHECK(f[0] == 3);  // 120/32 = 3.75 -> 3
    qf[0] = -1;
    inverse_quantize(qf, qp(false, 2, false, 0, m20), f);
    CHECK(f[0] == -3);
    // mismatch control: F[0][0] = 3 and F[7][7] = 3 -> sum 6 even, F[7][7] odd -> 2; a single 3 (odd sum) stays
    std::fill(std::begin(qf), std::end(qf), 0);
    qf[63] = 1;
    inverse_quantize(qf, qp(false, 2), f);
    CHECK(f[63] == 3);
    qf[0] = 1;
    inverse_quantize(qf, qp(false, 2), f);
    CHECK(f[0] == 3);
    CHECK(f[63] == 2);
    // saturation to [-2048, 2047] before the sum
    u8 m255[64];
    std::fill(std::begin(m255), std::end(m255), u8{255});
    std::fill(std::begin(qf), std::end(qf), 0);
    qf[1] = 2047;
    qf[2] = -2048;
    inverse_quantize(qf, qp(false, 112, false, 0, m255), f);
    CHECK(f[kZigzag[1]] == 2047);
    CHECK(f[kZigzag[2]] == -2048);
    CHECK(f[63] == 0);  // sum 2047 - 2048 = -1 is odd: F[7][7] untouched
}

TEST_CASE("inverse quantisation, MPEG-1: DC x 8, oddification, no mismatch control; alternate scan placement") {
    s32 qf[64] = {}, f[64] = {};
    qf[0] = 130;
    inverse_quantize(qf, qp(true, quantiser_scale(4, false, true), true, 3), f);
    CHECK(f[0] == 1040);  // MPEG-1 DC multiplier is 8 whatever IDP says
    CHECK(f[63] == 0);    // no mismatch control
    qf[1] = 1;            // intra AC: (2 * 1 * 4 * 16) / 16 = 8 -> even -> 7
    inverse_quantize(qf, qp(true, quantiser_scale(4, false, true), true), f);
    CHECK(f[1] == 7);
    qf[1] = -1;
    inverse_quantize(qf, qp(true, quantiser_scale(4, false, true), true), f);
    CHECK(f[1] == -7);
    std::fill(std::begin(qf), std::end(qf), 0);
    qf[0] = 1;  // non-intra: ((2 + 1) * 8 * 16) / 16 = 24 -> 23
    inverse_quantize(qf, qp(false, quantiser_scale(8, false, true), true), f);
    CHECK(f[0] == 23);
    qf[0] = 3;  // (7 * 8 * 16) / 16 = 56 -> 55
    inverse_quantize(qf, qp(false, quantiser_scale(8, false, true), true), f);
    CHECK(f[0] == 55);
    // alternate scan: scan position 1 lands on raster 8 (v = 1, u = 0)
    std::fill(std::begin(qf), std::end(qf), 0);
    qf[0] = 128;
    qf[1] = 3;
    QuantParams p = qp(true, 8);
    p.alternate_scan = true;
    inverse_quantize(qf, p, f);
    CHECK(f[1] == 0);
    CHECK(f[8] == (2 * 3 * kDefaultIntraMatrix[8] * 8) / 32);
}

TEST_CASE("IDCT: DC-only blocks are exact (round half up), saturation, single coefficients vs the reference") {
    s32 F[64] = {};
    s16 out[64];
    const std::pair<int, int> dc[] = {{1040, 130}, {1044, 131}, {-4, 0}, {-12, -1}, {2047, 255}, {-2048, -256}, {4, 1}};
    for (const auto& [in, expect] : dc) {
        F[0] = in;
        idct(F, out);
        for (int p = 0; p < 64; ++p) CHECK(out[p] == expect);
    }
    // one AC coefficient at a time, magnitudes 101 and -333 (no exact .5 ties: the only rational basis values are
    // +-1/8, for u, v in {0, 4}): equal to the rounded reference everywhere
    for (int c = 1; c < 64; ++c)
        for (int mag : {101, -333}) {
            std::fill(std::begin(F), std::end(F), 0);
            F[c] = mag;
            idct(F, out);
            double ref[64];
            ref_idct(F, ref);
            for (int p = 0; p < 64; ++p) {
                INFO("coef " << c << " pixel " << p << " ref " << ref[p]);
                CHECK(out[p] == round_sat(ref[p]));
            }
        }
    // u, v in {0, 4}: the basis is exactly +-1/8, so F[0][4] = 4 gives exact +-0.5 ties, rounded half up: 1 / 0
    std::fill(std::begin(F), std::end(F), 0);
    F[4] = 4;
    idct(F, out);
    for (int y = 0; y < 8; ++y) {
        CHECK(out[y * 8 + 0] == 1);  // cos(4 pi/16) > 0 at x = 0: +0.5 -> 1
        CHECK(out[y * 8 + 1] == 0);  // x = 1: cos(12 pi/16) < 0: -0.5 -> 0
    }
    // F[0][1] = 100: f(0, y) = 100 C(0) C(1) / 4 cos(pi/16) = 17.678 * 0.98079 = 17.338 -> 17 (hand value)
    std::fill(std::begin(F), std::end(F), 0);
    F[1] = 100;
    idct(F, out);
    CHECK(out[0] == 17);
    CHECK(out[7] == -17);
}

TEST_CASE("IDCT vs the double-precision reference on IEEE 1180 random blocks (statistics)") {
    // IEEE 1180: random spatial blocks in [-L, H] -> forward DCT (double) -> round, clamp [-2048, 2047] -> IDCT.
    // Our IDCT and the reference are both double-precision evaluations of the defining sum, so they may differ only
    // where the reference lands within 1e-9 of a .5 tie; everywhere else they must agree exactly.
    const double pi = std::acos(-1.0);
    const struct { long L, H; int sign; } cfg[] = {{256, 255, 1}, {5, 5, 1}, {300, 300, 1}, {256, 255, -1}, {5, 5, -1},
                                                   {300, 300, -1}};
    const int kBlocks = 1000;
    double cs[8][8];  // cs[x][u] = cos((2x+1) u pi / 16)
    for (int x = 0; x < 8; ++x)
        for (int u = 0; u < 8; ++u) cs[x][u] = std::cos((2 * x + 1) * u * pi / 16);
    long long mismatches = 0, ties = 0, peak = 0;
    double sq = 0, mean = 0;
    for (const auto& c : cfg) {
        Ieee1180Rand rnd;
        for (int b = 0; b < kBlocks; ++b) {
            double blk[64];
            for (int i = 0; i < 64; ++i) blk[i] = static_cast<double>(rnd.next(c.L, c.H) * c.sign);
            s32 F[64];
            for (int v = 0; v < 8; ++v)
                for (int u = 0; u < 8; ++u) {
                    double s = 0;
                    for (int y = 0; y < 8; ++y)
                        for (int x = 0; x < 8; ++x)
                            s += blk[y * 8 + x] * cs[x][u] * cs[y][v];
                    s *= (u ? 0.5 : std::sqrt(0.125)) * (v ? 0.5 : std::sqrt(0.125));
                    const double r = std::floor(s + 0.5);
                    F[v * 8 + u] = static_cast<s32>(std::clamp(r, -2048.0, 2047.0));
                }
            s16 out[64];
            idct(F, out);
            double ref[64];
            ref_idct(F, ref);
            for (int p = 0; p < 64; ++p) {
                const int r = round_sat(ref[p]);
                const int e = out[p] - r;
                const double frac = ref[p] - std::floor(ref[p]);
                if (e != 0) {
                    if (std::fabs(frac - 0.5) < 1e-9) ++ties;
                    else ++mismatches;
                }
                peak = std::max<long long>(peak, std::abs(e));
                sq += static_cast<double>(e) * e;
                mean += e;
            }
        }
    }
    const double n = static_cast<double>(sizeof cfg / sizeof cfg[0]) * kBlocks * 64;
    MESSAGE("IDCT vs reference over " << n << " samples: peak " << peak << ", mse " << sq / n << ", mean " << mean / n
                                      << ", tie-only differences " << ties);
    CHECK(mismatches == 0);
    CHECK(peak <= 1);
    CHECK(sq / n <= 0.02);               // IEEE 1180 overall MSE limit
    CHECK(std::fabs(mean / n) <= 0.0015); // overall mean error limit
}

TEST_CASE("macroblock assembly: frame vs field DCT luma placement, chroma after luma") {
    s16 blocks[6][64];
    for (int b = 0; b < 6; ++b)
        for (int i = 0; i < 64; ++i) blocks[b][i] = static_cast<s16>(b * 100 + i);
    s16 out[384];
    assemble_raw16(blocks, false, out);
    CHECK(out[0] == 0);              // block 0 (0,0)
    CHECK(out[8] == 100);            // block 1 (0,0)
    CHECK(out[16 * 8] == 200);       // block 2 starts at line 8
    CHECK(out[16 * 8 + 8] == 300);   // block 3
    CHECK(out[16 * 7 + 7] == 63);    // block 0 (7,7)
    CHECK(out[256] == 400);          // Cb
    CHECK(out[320 + 63] == 563);     // Cr last
    assemble_raw16(blocks, true, out);
    CHECK(out[16 * 0] == 0);         // line 0 = block 0 row 0
    CHECK(out[16 * 1] == 200);       // line 1 = block 2 row 0
    CHECK(out[16 * 2] == 8);         // line 2 = block 0 row 1
    CHECK(out[16 * 3 + 8] == 308);   // line 3 right = block 3 row 1
    CHECK(out[16 * 15 + 15] == 363); // line 15 right = block 3 row 7
}
