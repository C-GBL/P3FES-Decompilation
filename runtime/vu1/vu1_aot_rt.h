// Inline helpers for the generated VU1 programs (vu1_aot.h; output of p3fes_vu1_aotgen). Private to p3fes_vu1.
//
// Round 3 (docs/ANALYSIS/24_vu1_acceleration.md §8): the generated block functions keep the vf registers and ACC in
// SSE registers (`V`, one 128-bit value per VU register) and the vi registers in integer locals for the whole block,
// written back at every exit. Float arithmetic is host SSE arithmetic run under round-toward-zero with
// flush-to-zero and denormals-are-zero (CsrScope, set for the duration of a compiled run). Under that mode a host
// MULPS/ADDPS gives exactly fp::mul / fp::add (p3fes/ee/fpu.h) except when an operand has the exponent-255 binade
// (Inf/NaN to the host) or the result overflows: both show as a result lane of magnitude >= 0x7F7FFFFF, and only those
// ops are redone lane by lane with fp:: itself (the "slow path", out of line). Proof sketch per op:
//   * mul: the host rounds the exact product toward zero = fp::mul's truncation of the 48-bit product; a product below
//     2^-126 becomes a denormal or zero and FTZ makes it the signed zero fp::mul packs; DAZ turns zero/denormal
//     operands into the signed zero fp::mul returns.
//   * add: fp::add aligns the smaller operand with one guard bit and drops the bits below it, then truncates the exact
//     sum. The compiled code reproduces the alignment exactly in floats: for an exponent difference >= 2 the smaller
//     operand s is replaced by (s + C) - C with C = copysign(2^(E_big - 1), s) (round toward zero truncates s to a
//     multiple of ulp(big) / 2 and both steps are exact), then the host adds with round toward zero. Exact
//     cancellation is +0 under round toward zero, as fp::add returns.
//   * ITOF / FTOI / MAX / MINI / ABS / CLIP are exact by construction (scaling by powers of two, truncating
//     conversion with the saturation fixed up, integer keys).
// tests/vu1/test_vu1_aot.cpp compares every kernel with fp:: on biased random lanes (all exponents, alignments,
// cancellation, zero / denormal / exponent-255 operands, overflow).
//
// MXCSR is switched back to the host default around every call that leaves the compiled code's float model: XGKICK
// (the GS runs inside it), RSQRT (two double roundings) and ERCPR (a host float division). fp::div and fp::from_fixed
// do not depend on the rounding mode (a quotient of two 24-bit significands is never within 2^-48 of a 24-bit boundary
// unless it is one; a power-of-two scaling is exact).
#pragma once

#include "p3fes/vu1/vu1_aot.h"
#include "vu1_semantics.h"

#include <array>
#include <bit>
#include <cstring>

#include <emmintrin.h>
#include <smmintrin.h>

#if defined(_MSC_VER) && !defined(__clang__)
#define P3FES_VU1_INLINE __forceinline
#define P3FES_VU1_NOINLINE __declspec(noinline)
// Block functions: no /GS cookie (no arrays indexed by data).
#define P3FES_VU1_BLOCK static __declspec(safebuffers)
#define P3FES_VU1_UNLIKELY(x) (x)
#else
#define P3FES_VU1_INLINE inline __attribute__((always_inline))
#define P3FES_VU1_NOINLINE __attribute__((noinline))
#define P3FES_VU1_BLOCK static
#define P3FES_VU1_UNLIKELY(x) __builtin_expect(!!(x), 0)
#endif

namespace p3fes::vu1::aot {

using namespace ::p3fes::vu1::sem;

using V = __m128i;

// ---- MXCSR ---------------------------------------------------------------------------------------------------------
// Round toward zero (RC = 11), FTZ, DAZ, every exception masked.
inline constexpr unsigned kCsrVu = 0x7FC0u | 0x8000u;
struct CsrScope {
    unsigned saved;
    CsrScope() noexcept : saved(_mm_getcsr()) { _mm_setcsr(kCsrVu); }
    ~CsrScope() { _mm_setcsr(saved); }
    CsrScope(const CsrScope&) = delete;
    CsrScope& operator=(const CsrScope&) = delete;
};
// The host's mode for the duration of a call out of the compiled float model.
struct CsrHost {
    unsigned vu;
    explicit CsrHost(unsigned host) noexcept : vu(_mm_getcsr()) { _mm_setcsr(host); }
    ~CsrHost() { _mm_setcsr(vu); }
    CsrHost(const CsrHost&) = delete;
    CsrHost& operator=(const CsrHost&) = delete;
};

// ---- register file -------------------------------------------------------------------------------------------------
P3FES_VU1_INLINE V ld(const u32 (&r)[4]) noexcept { return _mm_loadu_si128(reinterpret_cast<const __m128i*>(r)); }
P3FES_VU1_INLINE void st(u32 (&r)[4], V v) noexcept { _mm_storeu_si128(reinterpret_cast<__m128i*>(r), v); }
P3FES_VU1_INLINE V ldq(const u8* q) noexcept { return _mm_loadu_si128(reinterpret_cast<const __m128i*>(q)); }
P3FES_VU1_INLINE V vf0() noexcept { return _mm_setr_epi32(0, 0, 0, static_cast<int>(fp::kOne)); }

// dest field (x = bit 3) -> movemask lane bits (x = bit 0) and blend immediates
constexpr int lane_bits(u32 d) noexcept {
    return static_cast<int>(((d >> 3) & 1u) | (((d >> 2) & 1u) << 1) | (((d >> 1) & 1u) << 2) | ((d & 1u) << 3));
}
constexpr int blend_imm(u32 d) noexcept {
    return ((d & 8u) ? 0x03 : 0) | ((d & 4u) ? 0x0C : 0) | ((d & 2u) ? 0x30 : 0) | ((d & 1u) ? 0xC0 : 0);
}
// the dest lanes of `nw`, the other lanes of `old`
template <u32 D>
P3FES_VU1_INLINE V blend(V old, V nw) noexcept {
    if constexpr (D == 15u) return nw;
    else if constexpr (D == 0u) return old;
    else return _mm_blend_epi16(old, nw, blend_imm(D));
}
template <u32 D>
P3FES_VU1_INLINE V dmask() noexcept { // all ones in the dest lanes
    return _mm_setr_epi32((D & 8u) ? -1 : 0, (D & 4u) ? -1 : 0, (D & 2u) ? -1 : 0, (D & 1u) ? -1 : 0);
}
template <int L>
P3FES_VU1_INLINE u32 lane(V v) noexcept {
    if constexpr (L == 0) return static_cast<u32>(_mm_cvtsi128_si32(v));
    else return static_cast<u32>(_mm_extract_epi32(v, L));
}
template <int L>
P3FES_VU1_INLINE V bc(V v) noexcept { return _mm_shuffle_epi32(v, L * 0x55); }
P3FES_VU1_INLINE V splat(u32 x) noexcept { return _mm_set1_epi32(static_cast<int>(x)); }

// data memory (1024 qwords, wrapping)
P3FES_VU1_INLINE u8* qw(VU1State& s, u32 index) noexcept { return s.data + (index & (kDataQwords - 1u)) * 16u; }
template <u32 D>
P3FES_VU1_INLINE V lq(V old, const u8* q) noexcept { return blend<D>(old, ldq(q)); }
template <u32 D>
P3FES_VU1_INLINE void sq(u8* q, V v) noexcept {
    if constexpr (D == 15u) _mm_storeu_si128(reinterpret_cast<__m128i*>(q), v);
    else _mm_storeu_si128(reinterpret_cast<__m128i*>(q), blend<D>(ldq(q), v));
}
// ILW: the low 16 bits of the first dest lane
template <u32 D>
P3FES_VU1_INLINE u32 ilw(const u8* q) noexcept {
    constexpr int i = (D & 8u) ? 0 : (D & 4u) ? 1 : (D & 2u) ? 2 : 3;
    u16 v;
    std::memcpy(&v, q + i * 4, 2);
    return v;
}
// ISW: the vi value zero-extended into every dest lane
template <u32 D>
P3FES_VU1_INLINE void isw(u8* q, u32 v) noexcept {
    if constexpr ((D & 8u) != 0) std::memcpy(q, &v, 4);
    if constexpr ((D & 4u) != 0) std::memcpy(q + 4, &v, 4);
    if constexpr ((D & 2u) != 0) std::memcpy(q + 8, &v, 4);
    if constexpr ((D & 1u) != 0) std::memcpy(q + 12, &v, 4);
}
P3FES_VU1_INLINE V mr32(V v) noexcept { return _mm_shuffle_epi32(v, _MM_SHUFFLE(0, 3, 2, 1)); }

// ---- float kernels (CsrScope active) ---------------------------------------------------------------------------------
P3FES_VU1_INLINE __m128 F(V v) noexcept { return _mm_castsi128_ps(v); }
P3FES_VU1_INLINE V I(__m128 f) noexcept { return _mm_castps_si128(f); }
P3FES_VU1_INLINE V kAbsV() noexcept { return _mm_set1_epi32(0x7FFFFFFF); }
P3FES_VU1_INLINE V kSignV() noexcept { return _mm_set1_epi32(static_cast<int>(0x80000000u)); }
P3FES_VU1_INLINE V kExpV() noexcept { return _mm_set1_epi32(0x7F800000); }

// Lanes (movemask bits) whose magnitude is >= 0x7F7FFFFF: Inf/NaN (an exponent-255 operand reached the host) or a
// round-toward-zero overflow (or exactly FLT_MAX): the only lanes where the host result may differ from fp::.
P3FES_VU1_INLINE int big_lanes(V r) noexcept {
    return _mm_movemask_ps(F(_mm_cmpgt_epi32(_mm_and_si128(r, kAbsV()), _mm_set1_epi32(0x7F7FFFFE))));
}
P3FES_VU1_INLINE int big_lanes2(V p, V r) noexcept {
    const V m = _mm_max_epi32(_mm_and_si128(p, kAbsV()), _mm_and_si128(r, kAbsV()));
    return _mm_movemask_ps(F(_mm_cmpgt_epi32(m, _mm_set1_epi32(0x7F7FFFFE))));
}

P3FES_VU1_INLINE V mul_rz(V a, V b) noexcept { return I(_mm_mul_ps(F(a), F(b))); }
// fp::add on four lanes (see the header comment): the smaller operand aligned like fp::add, then a host add.
P3FES_VU1_INLINE V add_rz(V a, V b) noexcept {
    const V abs = kAbsV(), ex = kExpV();
    const V swap = _mm_cmpgt_epi32(_mm_and_si128(b, abs), _mm_and_si128(a, abs));
    const __m128 sw = F(swap);
    const __m128 big = _mm_blendv_ps(F(a), F(b), sw), small = _mm_blendv_ps(F(b), F(a), sw);
    const V eb = _mm_and_si128(I(big), ex);
    const V diff = _mm_sub_epi32(eb, _mm_and_si128(I(small), ex));
    const V need = _mm_cmpgt_epi32(diff, _mm_set1_epi32(1 << 23)); // exponent difference >= 2
    const __m128 c = F(_mm_or_si128(_mm_sub_epi32(eb, _mm_set1_epi32(1 << 23)), _mm_and_si128(I(small), kSignV())));
    const __m128 cut = _mm_sub_ps(_mm_add_ps(small, c), c);
    return I(_mm_add_ps(big, _mm_blendv_ps(small, cut, F(need))));
}

// Slow path: the lanes `bad` (movemask bits, dest lanes whose host result may differ) redone with fp::; the other
// lanes keep the host result `r`, which is exact (lanes are independent). A redone lane that overflowed (magnitude
// 0x7FFFFFFF; only fp:: produces such lanes) sets the sticky OS bit (0x200) of the status register passed as `status`
// (`o` in the kernels) at once; the fold at a block exit keeps bits 4..11.
struct Lanes {
    alignas(16) u32 v[4];
};
P3FES_VU1_INLINE Lanes lanes_of(V x) noexcept {
    Lanes l;
    _mm_store_si128(reinterpret_cast<__m128i*>(l.v), x);
    return l;
}
enum class SlowOp : int { Mul, Add, Madd, Msub };
P3FES_VU1_NOINLINE inline V slow_fix(SlowOp op, const V& acc, const V& a, const V& b, const V& r, int bad, u32& status,
                                     u32 pc) noexcept {
    ++detail::g_aot_slow_ops;
    if (detail::g_aot_slow_trace) detail::aot_note_slow(detail::g_aot_cur_va, pc);
    V res = r;
    if (op != SlowOp::Add) {
        // The common case on the routes: an exponent-255 lane (unused bone-matrix rows) times a zero weight. fp::mul
        // gives the signed zero for any zero / denormal operand; with that product the host add is exact again, so
        // only lanes still out of range go lane by lane through fp::.
        const V zop = _mm_or_si128(_mm_cmpeq_epi32(_mm_and_si128(a, kExpV()), _mm_setzero_si128()),
                                   _mm_cmpeq_epi32(_mm_and_si128(b, kExpV()), _mm_setzero_si128()));
        if (_mm_movemask_ps(F(zop)) & bad) {
            const V p = I(_mm_blendv_ps(F(mul_rz(a, b)), F(_mm_and_si128(_mm_xor_si128(a, b), kSignV())), F(zop)));
            const V r2 = op == SlowOp::Mul ? p : add_rz(acc, op == SlowOp::Madd ? p : _mm_xor_si128(p, kSignV()));
            const int still = (op == SlowOp::Mul ? big_lanes(p) : big_lanes2(p, r2)) & bad;
            const int fixed = bad & ~still;
            const V fm = _mm_setr_epi32((fixed & 1) ? -1 : 0, (fixed & 2) ? -1 : 0, (fixed & 4) ? -1 : 0, (fixed & 8) ? -1 : 0);
            res = I(_mm_blendv_ps(F(res), F(r2), F(fm)));
            bad = still;
            if (!bad) return res;
        }
    }
    const Lanes c = lanes_of(acc), x = lanes_of(a), y = lanes_of(b);
    Lanes out = lanes_of(res);
    for (int i = 0; i < 4; ++i) {
        if (!((bad >> i) & 1)) continue;
        u32 v = 0;
        switch (op) {
        case SlowOp::Mul: v = fp::mul(x.v[i], y.v[i]); break;
        case SlowOp::Add: v = fp::add(x.v[i], y.v[i]); break;
        case SlowOp::Madd: v = fp::add(c.v[i], fp::mul(x.v[i], y.v[i])); break;
        case SlowOp::Msub: v = fp::sub(c.v[i], fp::mul(x.v[i], y.v[i])); break;
        }
        if ((v & 0x7FFFFFFFu) == 0x7FFFFFFFu) status |= 0x200u; // OS: sticky overflow
        out.v[i] = v;
    }
    return _mm_load_si128(reinterpret_cast<const __m128i*>(out.v));
}

template <u32 D>
P3FES_VU1_INLINE V vmul(V a, V b, u32& o, u32 pc) noexcept {
    const V r = mul_rz(a, b);
    const int bad = big_lanes(r) & lane_bits(D);
    if (P3FES_VU1_UNLIKELY(bad != 0)) return slow_fix(SlowOp::Mul, r, a, b, r, bad, o, pc);
    return r;
}
template <u32 D>
P3FES_VU1_INLINE V vadd(V a, V b, u32& o, u32 pc) noexcept {
    const V r = add_rz(a, b);
    const int bad = big_lanes(r) & lane_bits(D);
    if (P3FES_VU1_UNLIKELY(bad != 0)) return slow_fix(SlowOp::Add, r, a, b, r, bad, o, pc);
    return r;
}
template <u32 D>
P3FES_VU1_INLINE V vsub(V a, V b, u32& o, u32 pc) noexcept { return vadd<D>(a, _mm_xor_si128(b, kSignV()), o, pc); }
template <u32 D>
P3FES_VU1_INLINE V vmadd(V acc, V a, V b, u32& o, u32 pc) noexcept {
    const V p = mul_rz(a, b);
    const V r = add_rz(acc, p);
    const int bad = big_lanes2(p, r) & lane_bits(D);
    if (P3FES_VU1_UNLIKELY(bad != 0)) return slow_fix(SlowOp::Madd, acc, a, b, r, bad, o, pc);
    return r;
}
template <u32 D>
P3FES_VU1_INLINE V vmsub(V acc, V a, V b, u32& o, u32 pc) noexcept {
    const V p = mul_rz(a, b);
    const V r = add_rz(acc, _mm_xor_si128(p, kSignV()));
    const int bad = big_lanes2(p, r) & lane_bits(D);
    if (P3FES_VU1_UNLIKELY(bad != 0)) return slow_fix(SlowOp::Msub, acc, a, b, r, bad, o, pc);
    return r;
}// fp::mul(x, 1.0) = fp::sub(x, +0) = flush(x): denormals to signed zero, every other pattern unchanged
P3FES_VU1_INLINE V vflush(V x) noexcept {
    return _mm_and_si128(x, _mm_or_si128(_mm_cmpgt_epi32(_mm_and_si128(x, kExpV()), _mm_setzero_si128()), kSignV()));
}
// fp::add(x, +0): flush(x), and +0 when that is a zero
P3FES_VU1_INLINE V vaddz(V x) noexcept { return _mm_and_si128(x, _mm_cmpgt_epi32(_mm_and_si128(x, kExpV()), _mm_setzero_si128())); }
// OPMULA / OPMSUB operands: fs.yzx and ft.zxy (dest xyz)
P3FES_VU1_INLINE V yzx(V v) noexcept { return _mm_shuffle_epi32(v, _MM_SHUFFLE(3, 0, 2, 1)); }
P3FES_VU1_INLINE V zxy(V v) noexcept { return _mm_shuffle_epi32(v, _MM_SHUFFLE(3, 1, 0, 2)); }

// fp::key per lane: denormals flushed, sign-magnitude to two's complement
P3FES_VU1_INLINE V keys(V x) noexcept {
    const V nz = _mm_cmpgt_epi32(_mm_and_si128(x, kExpV()), _mm_setzero_si128());
    const V mag = _mm_and_si128(_mm_and_si128(x, kAbsV()), nz);
    const V s = _mm_srai_epi32(x, 31);
    return _mm_sub_epi32(_mm_xor_si128(mag, s), s);
}
// fp::max / fp::min (the first operand on ties)
P3FES_VU1_INLINE V vmax(V a, V b) noexcept { return I(_mm_blendv_ps(F(a), F(b), F(_mm_cmpgt_epi32(keys(b), keys(a))))); }
P3FES_VU1_INLINE V vmin(V a, V b) noexcept { return I(_mm_blendv_ps(F(a), F(b), F(_mm_cmpgt_epi32(keys(a), keys(b))))); }
// fp::to_fixed(x, frac): x * 2^frac is exact, CVTTPS truncates; the 0x80000000 of an out-of-range lane becomes
// 0x7FFFFFFF for a positive (sign bit clear) operand, as fp::to_fixed saturates.
template <int Frac>
P3FES_VU1_INLINE V vftoi(V x) noexcept {
    __m128 f = F(x);
    if constexpr (Frac != 0) f = _mm_mul_ps(f, _mm_set1_ps(static_cast<float>(1u << Frac)));
    const V r = _mm_cvttps_epi32(f);
    const V fix = _mm_and_si128(_mm_cmpeq_epi32(r, kSignV()), _mm_cmpgt_epi32(x, _mm_set1_epi32(-1)));
    return _mm_add_epi32(r, fix);
}
// fp::from_fixed(v, frac): CVTDQ2PS rounds toward zero under CsrScope, the scaling is exact
template <int Frac>
P3FES_VU1_INLINE V vitof(V x) noexcept {
    __m128 f = _mm_cvtepi32_ps(x);
    if constexpr (Frac != 0) f = _mm_mul_ps(f, _mm_set1_ps(1.0f / static_cast<float>(1u << Frac)));
    return I(f);
}
// CLIP: sem::clip_value on x, y, z against |w|
P3FES_VU1_INLINE u32 vclip(u32 history, V s, u32 w) noexcept {
    static constexpr u8 kSpread[8] = {0x00, 0x01, 0x04, 0x05, 0x10, 0x11, 0x14, 0x15};
    const V k = keys(s);
    const V lim = _mm_shuffle_epi32(keys(_mm_and_si128(splat(w), kAbsV())), 0);
    const int gt = _mm_movemask_ps(F(_mm_cmpgt_epi32(k, lim))) & 7;
    const int lt = _mm_movemask_ps(F(_mm_cmpgt_epi32(_mm_sub_epi32(_mm_setzero_si128(), lim), k))) & 7;
    return ((history << 6) | kSpread[gt] | (static_cast<u32>(kSpread[lt]) << 1)) & 0xFFFFFFu;
}

// ---- flags ---------------------------------------------------------------------------------------------------------
// MAC flags of the dest lanes (sem::mac_flags): Z = exponent field 0, S = sign, O = magnitude 0x7FFFFFFF; lane i maps
// to bit 3 - i (x is bit 3).
P3FES_VU1_INLINE u32 mac_of(V x, u32 dest) noexcept {
    static constexpr u8 kRev[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    const V z = _mm_cmpeq_epi32(_mm_and_si128(x, kExpV()), _mm_setzero_si128());
    const V o = _mm_cmpeq_epi32(_mm_and_si128(x, kAbsV()), kAbsV());
    const u32 zm = kRev[_mm_movemask_ps(F(z))];
    const u32 sm = kRev[_mm_movemask_ps(F(x))];
    const u32 om = kRev[_mm_movemask_ps(F(o))];
    return (zm | (sm << 4) | (om << 12)) & (dest | (dest << 4) | (dest << 12));
}
// Low status bits (Z S U O present) of a MAC value, as sem::set_flags derives them.
P3FES_VU1_INLINE u32 status_low(u32 mac) noexcept {
    return ((mac & 0x000Fu) ? 1u : 0u) | ((mac & 0x00F0u) ? 2u : 0u) | ((mac & 0x0F00u) ? 4u : 0u) | ((mac & 0xF000u) ? 8u : 0u);
}
// The status register's sticky bits ZS (0x40) and SS (0x80) only ever get set (no census op clears them: FSSET is not
// used) and every flag write with a zero or negative dest lane sets them, so after the first few runs of a session
// both stay set. A compiled run starts only then (otherwise the interpreter takes the run), so the compiled code never
// accumulates them; OS (0x200) is set by the slow path, the only place an overflow lane can appear.
P3FES_VU1_INLINE bool sticky_zs_set(const VU1State& s) noexcept { return (s.status & 0xC0u) == 0xC0u; }
P3FES_VU1_INLINE void mac_ring(VU1State& s, u32 t, u32 mac) noexcept {
    const u32 i = s.pipe.mh++ & 7u;
    s.pipe.mac_ts[i] = t;
    s.pipe.mac_v[i] = mac;
}
P3FES_VU1_INLINE u32 mac_read(const FlagPipe& p, u32 t) noexcept {
    for (u32 k = 1; k <= 8; ++k) {
        const u32 i = (p.mh - k) & 7u;
        if (p.mac_ts[i] + 4u <= t) return p.mac_v[i];
    }
    return p.mac_v[(p.mh - 8u) & 7u];
}
P3FES_VU1_INLINE u32 clip_read(const FlagPipe& p, u32 t) noexcept {
    for (u32 k = 1; k <= 8; ++k) {
        const u32 i = (p.ch - k) & 7u;
        if (p.clip_ts[i] + 3u <= t) return p.clip_v[i];
    }
    return p.clip_v[(p.ch - 8u) & 7u];
}
P3FES_VU1_INLINE void clip_write(FlagPipe& p, u32 clip, u32 at) noexcept {
    const u32 i = p.ch++ & 7u;
    p.clip_ts[i] = at;
    p.clip_v[i] = clip;
}

// ---- lower ops with state -----------------------------------------------------------------------------------------
P3FES_VU1_INLINE void flush_q(VU1State& s) noexcept {
    if (!s.pipe.q_pending) return;
    s.q = s.pipe.q_value;
    s.pipe.q_pending = false;
}
P3FES_VU1_NOINLINE inline fp::Result div_slow(u32 a, u32 b) noexcept { return fp::div(a, b); }
// fp::div: from_double(a / b in double, rounded to nearest) is the quotient truncated to 24 bits, because a quotient
// of two 24-bit significands is never within 2^-47 (relative) of a 24-bit boundary unless it is one, so the double
// rounding cannot cross it. DIVSS under CsrScope truncates the exact quotient: the same value for operands with
// exponent 1..254 whose quotient neither overflows (a result lane >= 0x7F7FFFFF) nor needs fp::'s zero / exponent-255
// rules; FTZ gives fp::'s signed zero on underflow. Everything else takes fp::div.
P3FES_VU1_INLINE void div_q(VU1State& s, u32 t, u32 a, u32 b, u32 delay) noexcept {
    flush_q(s);
    const u32 ea = (a >> 23) & 0xFFu, eb = (b >> 23) & 0xFFu;
    u32 v = 0;
    bool fast = ea - 1u < 254u && eb - 1u < 254u;
    if (fast) {
        v = static_cast<u32>(_mm_cvtsi128_si32(I(_mm_div_ss(F(splat(a)), F(splat(b))))));
        fast = (v & 0x7FFFFFFFu) < 0x7F7FFFFFu;
    }
    if (fast) {
        s.status &= ~0x30u;
    } else {
        const fp::Result res = div_slow(a, b);
        s.status = (s.status & ~0x30u) | (res.invalid ? 0x20u : 0u);
        v = res.value;
    }
    s.pipe.q_value = v;
    s.pipe.q_ready = t + delay;
    s.pipe.q_pending = true;
}
P3FES_VU1_NOINLINE inline void rsqrt_q(VU1State& s, unsigned host_csr, u32 t, u32 a, u32 b, u32 delay) noexcept {
    const CsrHost h(host_csr);
    flush_q(s);
    const fp::Result res = fp::rsqrt(a, b);
    s.status = (s.status & ~0x30u) | (res.invalid ? 0x20u : 0u);
    s.pipe.q_value = res.value;
    s.pipe.q_ready = t + delay;
    s.pipe.q_pending = true;
}
P3FES_VU1_NOINLINE inline void ercpr(VU1State& s, unsigned host_csr, u32 x) noexcept {
    const CsrHost h(host_csr);
    const float v = u2f(x);
    s.p = f2u(v != 0.0f ? 1.0f / v : 3.4e38f);
}
P3FES_VU1_NOINLINE inline void xgkick(AotHost& host, unsigned host_csr, u32 addr) {
    const CsrHost h(host_csr);
    host.xgkick(addr);
}

// State hand-over when the compiled code stops at a pair boundary: what the interpreter's step() would have left
// (pc/npc, the pair counter, the branch-VI snapshot: `pw` is the vi register the previous pair's lower op wrote
// (0 = none), `pv` its value before that op, `pl` whether the snapshot is live). With no pair executed the state is
// still the one start() left. The caller has written the cached registers back.
P3FES_VU1_NOINLINE inline AotResult bail(VU1State& s, u32 pc, u32 npc, u32 t, u32 pw, u32 pv, bool pl, bool ending,
                                         u64 steps) noexcept {
    if (!steps) return AotResult{false, 0};
    s.pc = pc & kMicroMask;
    s.npc = npc & kMicroMask;
    s.pipe.t = t;
    std::memcpy(s.vi_before, s.vi, sizeof s.vi);
    if (pw) s.vi_before[pw] = static_cast<u16>(pv);
    s.vi_delay_live = pl;
    s.ending = ending;
    s.running = true;
    return AotResult{false, steps};
}
// The pair after E executed: exactly the interpreter's end of run (snapshot arguments as for bail()).
P3FES_VU1_NOINLINE inline AotResult finish(VU1State& s, u32 pc, u32 npc, u32 t, u32 pw, u32 pv, bool pl, u64 steps) noexcept {
    s.pipe.t = t;
    std::memcpy(s.vi_before, s.vi, sizeof s.vi);
    if (pw) s.vi_before[pw] = static_cast<u16>(pv);
    s.vi_delay_live = pl;
    flush_q(s);
    s.pc = pc & kMicroMask;
    s.npc = npc & kMicroMask;
    s.tpc = s.pc;
    s.running = false;
    s.ending = false;
    return AotResult{true, steps};
}

// Per-run context of a compiled program: the locals a block hands to the next one, and the result on exit.
struct Ctx {
    u32 t = 0, pw = 0, pv = 0;
    bool pl = false;
    u64 steps = 0, limit = 0;
    unsigned host_csr = 0;
    AotResult res{};
};
inline constexpr u32 kExit = 0xFFFFu; // block return: run over, result in Ctx::res

P3FES_VU1_INLINE bool canonical_zero_regs(const VU1State& s) noexcept {
    return s.vf[0][0] == 0u && s.vf[0][1] == 0u && s.vf[0][2] == 0u && s.vf[0][3] == fp::kOne && s.vi[0] == 0u;
}

} // namespace p3fes::vu1::aot
