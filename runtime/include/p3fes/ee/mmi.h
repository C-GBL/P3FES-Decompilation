// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/include/ps2/mmi.hpp (all lane operations, PMFHL/PMTHL,
// the parallel multiply/divide family, QFSRV, PLZCW) and recomp/codegen.cpp (LQ/SQ address masking,
// PMFHI/PMFLO/PMTHI/PMTLO), MIT; adapted for p3fes-port (p3fes::ee::mmi namespace, EEContext/u128 instead of
// Cpu/Reg128, GNU vector extensions replaced by a scalar lane-loop path plus an SSE2 <emmintrin.h> path,
// std::memcpy instead of __builtin_memcpy, PMULTH/PMADDW/PHMADH variants exposed as named functions).
//
// Every operation is `inline` on `u128` and, where the instruction touches HI/LO, on `EEContext&`. Operand
// order follows the instruction: `op(rd, rs, rt)`; unary forms are `op(rd, rt)`; shift-by-immediate forms are
// `op(rd, rt, sa)`. Lane numbering is little-endian (lane 0 is the least significant), as in ee_types.h.
//
// Two implementations of the lane-parallel operations are always compiled on x64:
//   p3fes::ee::mmi::scalar  — portable lane loops (the upstream text, bit for bit)
//   p3fes::ee::mmi::sse2    — <emmintrin.h> intrinsics where SSE2 has an exact equivalent; otherwise the scalar
//                             function is re-exported so the namespace is complete
// `P3FES_EE_MMI_USE_SSE2` (default 1) selects which one the unqualified `p3fes::ee::mmi::` names resolve to.
// tests/ee/test_mmi_paths.cpp runs every operation through both namespaces on random inputs and requires
// identical results (ADR-0010 §5: no GNU vector extensions, no musttail; intrinsics behind a portable fallback).
//
// Provenance tags: (manual) = EE Core Instruction Set Manual semantics reproduced by upstream;
// (upstream) = a choice where the manual leaves the result undefined; hardware-unverified.
#pragma once

#include "p3fes/ee/hilo.h"
#include "p3fes/ee_context.h"
#include "p3fes/ee_memory.h"

#include <bit>
#include <cstring>
#include <limits>
#include <type_traits>

#include <emmintrin.h>

#ifndef P3FES_EE_MMI_USE_SSE2
#define P3FES_EE_MMI_USE_SSE2 1
#endif

namespace p3fes::ee::mmi {

// ---------------------------------------------------------------------------------------------------------
// Shared helpers
// ---------------------------------------------------------------------------------------------------------
namespace detail {

template <typename T>
inline T sat_add(T a, T b) noexcept {
    using W = std::conditional_t<std::is_signed_v<T>, s64, u64>;
    const W r = static_cast<W>(a) + static_cast<W>(b);
    if (r > static_cast<W>(std::numeric_limits<T>::max())) return std::numeric_limits<T>::max();
    if constexpr (std::is_signed_v<T>) {
        if (r < static_cast<W>(std::numeric_limits<T>::min())) return std::numeric_limits<T>::min();
    }
    return static_cast<T>(r);
}

template <typename T>
inline T sat_sub(T a, T b) noexcept {
    if constexpr (std::is_signed_v<T>) {
        const s64 r = static_cast<s64>(a) - static_cast<s64>(b);
        if (r > std::numeric_limits<T>::max()) return std::numeric_limits<T>::max();
        if (r < std::numeric_limits<T>::min()) return std::numeric_limits<T>::min();
        return static_cast<T>(r);
    } else {
        return a > b ? static_cast<T>(a - b) : T{0};
    }
}

inline s32 sat32(s64 v) noexcept {
    return v > INT32_MAX ? INT32_MAX : v < INT32_MIN ? INT32_MIN : static_cast<s32>(v);
}

inline s16 sat16(s32 v) noexcept {
    return v > INT16_MAX ? INT16_MAX : v < INT16_MIN ? INT16_MIN : static_cast<s16>(v);
}

// Number of leading bits equal to the sign bit, minus one (PLZCW). (manual)
inline u32 leading_sign_bits(u32 x) noexcept {
    return static_cast<u32>(std::countl_zero(static_cast<s32>(x) < 0 ? ~x : x)) - 1u;
}

} // namespace detail

// ---------------------------------------------------------------------------------------------------------
// Scalar path: portable lane loops.
// ---------------------------------------------------------------------------------------------------------
namespace scalar {

#define P3FES_MMI_LANES(name, field, count, expr)                                   \
    inline void name(u128& d, const u128& s, const u128& t) noexcept {              \
        u128 r;                                                                     \
        for (int i = 0; i < (count); ++i) r.field[i] = (expr);                      \
        d = r;                                                                      \
    }

// Parallel add/subtract, wrapping. (manual)
P3FES_MMI_LANES(paddw, u32, 4, s.u32[i] + t.u32[i])
P3FES_MMI_LANES(psubw, u32, 4, s.u32[i] - t.u32[i])
P3FES_MMI_LANES(paddh, u16, 8, static_cast<u16>(s.u16[i] + t.u16[i]))
P3FES_MMI_LANES(psubh, u16, 8, static_cast<u16>(s.u16[i] - t.u16[i]))
P3FES_MMI_LANES(paddb, u8, 16, static_cast<u8>(s.u8[i] + t.u8[i]))
P3FES_MMI_LANES(psubb, u8, 16, static_cast<u8>(s.u8[i] - t.u8[i]))
// Parallel add/subtract, signed saturation. (manual)
P3FES_MMI_LANES(paddsw, s32, 4, detail::sat_add(s.s32[i], t.s32[i]))
P3FES_MMI_LANES(psubsw, s32, 4, detail::sat_sub(s.s32[i], t.s32[i]))
P3FES_MMI_LANES(paddsh, s16, 8, detail::sat_add(s.s16[i], t.s16[i]))
P3FES_MMI_LANES(psubsh, s16, 8, detail::sat_sub(s.s16[i], t.s16[i]))
P3FES_MMI_LANES(paddsb, s8, 16, detail::sat_add(s.s8[i], t.s8[i]))
P3FES_MMI_LANES(psubsb, s8, 16, detail::sat_sub(s.s8[i], t.s8[i]))
// Parallel add/subtract, unsigned saturation. (manual)
P3FES_MMI_LANES(padduw, u32, 4, detail::sat_add(s.u32[i], t.u32[i]))
P3FES_MMI_LANES(psubuw, u32, 4, detail::sat_sub(s.u32[i], t.u32[i]))
P3FES_MMI_LANES(padduh, u16, 8, detail::sat_add(s.u16[i], t.u16[i]))
P3FES_MMI_LANES(psubuh, u16, 8, detail::sat_sub(s.u16[i], t.u16[i]))
P3FES_MMI_LANES(paddub, u8, 16, detail::sat_add(s.u8[i], t.u8[i]))
P3FES_MMI_LANES(psubub, u8, 16, detail::sat_sub(s.u8[i], t.u8[i]))
// Parallel compare: all-ones on true. (manual)
P3FES_MMI_LANES(pcgtw, u32, 4, s.s32[i] > t.s32[i] ? 0xFFFFFFFFu : 0u)
P3FES_MMI_LANES(pcgth, u16, 8, static_cast<u16>(s.s16[i] > t.s16[i] ? 0xFFFFu : 0u))
P3FES_MMI_LANES(pcgtb, u8, 16, static_cast<u8>(s.s8[i] > t.s8[i] ? 0xFFu : 0u))
P3FES_MMI_LANES(pceqw, u32, 4, s.u32[i] == t.u32[i] ? 0xFFFFFFFFu : 0u)
P3FES_MMI_LANES(pceqh, u16, 8, static_cast<u16>(s.u16[i] == t.u16[i] ? 0xFFFFu : 0u))
P3FES_MMI_LANES(pceqb, u8, 16, static_cast<u8>(s.u8[i] == t.u8[i] ? 0xFFu : 0u))
// Parallel signed min/max. (manual)
P3FES_MMI_LANES(pmaxw, s32, 4, s.s32[i] > t.s32[i] ? s.s32[i] : t.s32[i])
P3FES_MMI_LANES(pminw, s32, 4, s.s32[i] < t.s32[i] ? s.s32[i] : t.s32[i])
P3FES_MMI_LANES(pmaxh, s16, 8, s.s16[i] > t.s16[i] ? s.s16[i] : t.s16[i])
P3FES_MMI_LANES(pminh, s16, 8, s.s16[i] < t.s16[i] ? s.s16[i] : t.s16[i])
// PADSBH: lower four halfwords subtract, upper four add. (manual)
P3FES_MMI_LANES(padsbh, u16, 8, static_cast<u16>(i < 4 ? s.u16[i] - t.u16[i] : s.u16[i] + t.u16[i]))
// Logical. (manual)
P3FES_MMI_LANES(pand, u64, 2, s.u64[i] & t.u64[i])
P3FES_MMI_LANES(por, u64, 2, s.u64[i] | t.u64[i])
P3FES_MMI_LANES(pxor, u64, 2, s.u64[i] ^ t.u64[i])
P3FES_MMI_LANES(pnor, u64, 2, ~(s.u64[i] | t.u64[i]))
// Extend (interleave) lower / upper halves: rd = {rs.lane1, rt.lane1, rs.lane0, rt.lane0 ...}. (manual)
P3FES_MMI_LANES(pextlw, u32, 4, (i & 1) ? s.u32[i >> 1] : t.u32[i >> 1])
P3FES_MMI_LANES(pextuw, u32, 4, (i & 1) ? s.u32[2 + (i >> 1)] : t.u32[2 + (i >> 1)])
P3FES_MMI_LANES(pextlh, u16, 8, (i & 1) ? s.u16[i >> 1] : t.u16[i >> 1])
P3FES_MMI_LANES(pextuh, u16, 8, (i & 1) ? s.u16[4 + (i >> 1)] : t.u16[4 + (i >> 1)])
P3FES_MMI_LANES(pextlb, u8, 16, (i & 1) ? s.u8[i >> 1] : t.u8[i >> 1])
P3FES_MMI_LANES(pextub, u8, 16, (i & 1) ? s.u8[8 + (i >> 1)] : t.u8[8 + (i >> 1)])
// Pack: keep the low half of every lane, rt in the low 64 bits, rs in the high 64 bits. (manual)
P3FES_MMI_LANES(ppacw, u32, 4, i < 2 ? t.u32[i * 2] : s.u32[(i - 2) * 2])
P3FES_MMI_LANES(ppach, u16, 8, i < 4 ? t.u16[i * 2] : s.u16[(i - 4) * 2])
P3FES_MMI_LANES(ppacb, u8, 16, i < 8 ? t.u8[i * 2] : s.u8[(i - 8) * 2])
// Interleave halfwords: PINTH = {rs.h7, rt.h3, rs.h6, rt.h2, ..., rs.h4, rt.h0}; PINTEH = even halfwords. (manual)
P3FES_MMI_LANES(pinth, u16, 8, (i & 1) ? s.u16[4 + (i >> 1)] : t.u16[i >> 1])
P3FES_MMI_LANES(pinteh, u16, 8, (i & 1) ? s.u16[i & ~1] : t.u16[i & ~1])
// Copy doublewords: PCPYLD = {rs.lo, rt.lo}; PCPYUD = {rt.hi, rs.hi}. (manual)
P3FES_MMI_LANES(pcpyld, u64, 2, i ? s.u64[0] : t.u64[0])
P3FES_MMI_LANES(pcpyud, u64, 2, i ? t.u64[1] : s.u64[1])

#undef P3FES_MMI_LANES

#define P3FES_MMI_UNARY(name, field, count, expr)                                   \
    inline void name(u128& d, const u128& t) noexcept {                             \
        u128 r;                                                                     \
        for (int i = 0; i < (count); ++i) r.field[i] = (expr);                      \
        d = r;                                                                      \
    }

// Absolute value with saturation of the most negative lane. (manual)
P3FES_MMI_UNARY(pabsw, s32, 4, t.s32[i] == INT32_MIN ? INT32_MAX : (t.s32[i] < 0 ? -t.s32[i] : t.s32[i]))
P3FES_MMI_UNARY(pabsh, s16, 8, static_cast<s16>(t.s16[i] == INT16_MIN ? INT16_MAX : (t.s16[i] < 0 ? -t.s16[i] : t.s16[i])))
// Permutations. (manual)
P3FES_MMI_UNARY(pcpyh, u16, 8, t.u16[i & 4])
P3FES_MMI_UNARY(pexch, u16, 8, t.u16[(i & 4) | (i & 1 ? (i & 2 ? 3 : 2) : (i & 2 ? 1 : 0))])
P3FES_MMI_UNARY(pexcw, u32, 4, t.u32[i == 1 ? 2 : i == 2 ? 1 : i])
P3FES_MMI_UNARY(pexeh, u16, 8, t.u16[(i & 4) | ((i & 3) == 0 ? 2 : (i & 3) == 2 ? 0 : (i & 3))])
P3FES_MMI_UNARY(pexew, u32, 4, t.u32[i == 0 ? 2 : i == 2 ? 0 : i])
P3FES_MMI_UNARY(prevh, u16, 8, t.u16[(i & 4) | (3 - (i & 3))])
P3FES_MMI_UNARY(prot3w, u32, 4, t.u32[i == 0 ? 1 : i == 1 ? 2 : i == 2 ? 0 : 3])
// 5:5:5:1 <-> 8:8:8:8 colour conversions. (manual)
P3FES_MMI_UNARY(pext5, u32, 4, ((t.u32[i] & 0x1Fu) << 3) | (((t.u32[i] >> 5) & 0x1Fu) << 11) |
                                   (((t.u32[i] >> 10) & 0x1Fu) << 19) | (((t.u32[i] >> 15) & 1u) << 31))
P3FES_MMI_UNARY(ppac5, u32, 4, ((t.u32[i] >> 3) & 0x1Fu) | (((t.u32[i] >> 11) & 0x1Fu) << 5) |
                                   (((t.u32[i] >> 19) & 0x1Fu) << 10) | (((t.u32[i] >> 31) & 1u) << 15))

#undef P3FES_MMI_UNARY

// Shifts by immediate; halfword shifts use sa[3:0], word shifts sa[4:0]. (manual)
inline void psllh(u128& d, const u128& t, u32 sa) noexcept { u128 r; for (int i = 0; i < 8; ++i) r.u16[i] = static_cast<u16>(t.u16[i] << (sa & 15u)); d = r; }
inline void psrlh(u128& d, const u128& t, u32 sa) noexcept { u128 r; for (int i = 0; i < 8; ++i) r.u16[i] = static_cast<u16>(t.u16[i] >> (sa & 15u)); d = r; }
inline void psrah(u128& d, const u128& t, u32 sa) noexcept { u128 r; for (int i = 0; i < 8; ++i) r.s16[i] = static_cast<s16>(t.s16[i] >> (sa & 15u)); d = r; }
inline void psllw(u128& d, const u128& t, u32 sa) noexcept { u128 r; for (int i = 0; i < 4; ++i) r.u32[i] = t.u32[i] << (sa & 31u); d = r; }
inline void psrlw(u128& d, const u128& t, u32 sa) noexcept { u128 r; for (int i = 0; i < 4; ++i) r.u32[i] = t.u32[i] >> (sa & 31u); d = r; }
inline void psraw(u128& d, const u128& t, u32 sa) noexcept { u128 r; for (int i = 0; i < 4; ++i) r.s32[i] = t.s32[i] >> (sa & 31u); d = r; }

// Variable word shifts: lanes 0 and 2 of rt shifted by rs lanes 0 and 2, each result sign-extended to 64 bits. (manual)
inline void psllvw(u128& d, const u128& s, const u128& t) noexcept {
    const s64 a = static_cast<s32>(t.u32[0] << (s.u32[0] & 31u));
    const s64 b = static_cast<s32>(t.u32[2] << (s.u32[2] & 31u));
    d.s64[0] = a;
    d.s64[1] = b;
}
inline void psrlvw(u128& d, const u128& s, const u128& t) noexcept {
    const s64 a = static_cast<s32>(t.u32[0] >> (s.u32[0] & 31u));
    const s64 b = static_cast<s32>(t.u32[2] >> (s.u32[2] & 31u));
    d.s64[0] = a;
    d.s64[1] = b;
}
inline void psravw(u128& d, const u128& s, const u128& t) noexcept {
    const s64 a = t.s32[0] >> (s.u32[0] & 31u);
    const s64 b = t.s32[2] >> (s.u32[2] & 31u);
    d.s64[0] = a;
    d.s64[1] = b;
}

// PLZCW rd, rs: leading sign bits of the two low words; rd[127:64] is left unchanged. (manual for the count;
// upstream for leaving the upper half, which the manual marks undefined)
inline void plzcw(u128& d, const u128& s) noexcept {
    const u32 a = detail::leading_sign_bits(s.u32[0]);
    const u32 b = detail::leading_sign_bits(s.u32[1]);
    d.u32[0] = a;
    d.u32[1] = b;
}

// QFSRV rd, rs, rt: rd = {rs:rt} >> (sa_bytes * 8), i.e. bytes sa_bytes .. sa_bytes+15 of the 32-byte
// concatenation with rt in the low half. `sa_bytes` is 0..15 (ee::sa_bytes(ctx)). (manual)
inline void qfsrv(u128& d, const u128& s, const u128& t, u32 sa_bytes) noexcept {
    u8 bytes[32];
    std::memcpy(bytes, &t, 16);
    std::memcpy(bytes + 16, &s, 16);
    u128 r;
    std::memcpy(&r, bytes + (sa_bytes & 15u), 16);
    d = r;
}

} // namespace scalar

// ---------------------------------------------------------------------------------------------------------
// SSE2 path. Operations without an exact SSE2 equivalent re-export the scalar function.
// ---------------------------------------------------------------------------------------------------------
namespace sse2 {

namespace simd {
inline __m128i ld(const u128& r) noexcept { return _mm_load_si128(reinterpret_cast<const __m128i*>(&r)); }
inline void st(u128& d, __m128i v) noexcept { _mm_store_si128(reinterpret_cast<__m128i*>(&d), v); }
inline __m128i count(u32 sa) noexcept { return _mm_cvtsi32_si128(static_cast<int>(sa)); }
inline __m128i ones() noexcept { return _mm_set1_epi32(-1); }
// Signed 32-bit compare-greater-than for unsigned operands: flip the sign bits first.
inline __m128i cmpgt_epu32(__m128i a, __m128i b) noexcept {
    const __m128i bias = _mm_set1_epi32(static_cast<int>(0x80000000u));
    return _mm_cmpgt_epi32(_mm_xor_si128(a, bias), _mm_xor_si128(b, bias));
}
inline __m128i blend(__m128i mask, __m128i on_true, __m128i on_false) noexcept {
    return _mm_or_si128(_mm_and_si128(mask, on_true), _mm_andnot_si128(mask, on_false));
}
// Low 64 bits: halfwords 0,2,4,6 of x (PPACH building block).
inline __m128i even_halfwords_low(__m128i x) noexcept {
    x = _mm_shufflelo_epi16(x, _MM_SHUFFLE(3, 1, 2, 0));
    x = _mm_shufflehi_epi16(x, _MM_SHUFFLE(3, 1, 2, 0));
    return _mm_shuffle_epi32(x, _MM_SHUFFLE(3, 1, 2, 0));
}
} // namespace simd

#define P3FES_MMI_SSE2_BIN(name, intrinsic)                                                                   \
    inline void name(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, intrinsic(simd::ld(s), simd::ld(t))); }

P3FES_MMI_SSE2_BIN(paddw, _mm_add_epi32)
P3FES_MMI_SSE2_BIN(psubw, _mm_sub_epi32)
P3FES_MMI_SSE2_BIN(paddh, _mm_add_epi16)
P3FES_MMI_SSE2_BIN(psubh, _mm_sub_epi16)
P3FES_MMI_SSE2_BIN(paddb, _mm_add_epi8)
P3FES_MMI_SSE2_BIN(psubb, _mm_sub_epi8)
P3FES_MMI_SSE2_BIN(paddsh, _mm_adds_epi16)
P3FES_MMI_SSE2_BIN(psubsh, _mm_subs_epi16)
P3FES_MMI_SSE2_BIN(paddsb, _mm_adds_epi8)
P3FES_MMI_SSE2_BIN(psubsb, _mm_subs_epi8)
P3FES_MMI_SSE2_BIN(padduh, _mm_adds_epu16)
P3FES_MMI_SSE2_BIN(psubuh, _mm_subs_epu16)
P3FES_MMI_SSE2_BIN(paddub, _mm_adds_epu8)
P3FES_MMI_SSE2_BIN(psubub, _mm_subs_epu8)
P3FES_MMI_SSE2_BIN(pcgtw, _mm_cmpgt_epi32)
P3FES_MMI_SSE2_BIN(pcgth, _mm_cmpgt_epi16)
P3FES_MMI_SSE2_BIN(pcgtb, _mm_cmpgt_epi8)
P3FES_MMI_SSE2_BIN(pceqw, _mm_cmpeq_epi32)
P3FES_MMI_SSE2_BIN(pceqh, _mm_cmpeq_epi16)
P3FES_MMI_SSE2_BIN(pceqb, _mm_cmpeq_epi8)
P3FES_MMI_SSE2_BIN(pmaxh, _mm_max_epi16)
P3FES_MMI_SSE2_BIN(pminh, _mm_min_epi16)
P3FES_MMI_SSE2_BIN(pand, _mm_and_si128)
P3FES_MMI_SSE2_BIN(por, _mm_or_si128)
P3FES_MMI_SSE2_BIN(pxor, _mm_xor_si128)

#undef P3FES_MMI_SSE2_BIN

inline void pnor(u128& d, const u128& s, const u128& t) noexcept {
    simd::st(d, _mm_xor_si128(_mm_or_si128(simd::ld(s), simd::ld(t)), simd::ones()));
}

// Signed 32-bit saturating add/sub: overflow when the operands agree in sign (add) or differ (sub) and the
// result's sign differs from rs; the saturated value is INT32_MAX for positive rs, INT32_MIN for negative.
inline void paddsw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    const __m128i sum = _mm_add_epi32(a, b);
    const __m128i ovf = _mm_srai_epi32(_mm_and_si128(_mm_xor_si128(a, sum), _mm_xor_si128(b, sum)), 31);
    const __m128i sat = _mm_xor_si128(_mm_srai_epi32(a, 31), _mm_set1_epi32(INT32_MAX));
    simd::st(d, simd::blend(ovf, sat, sum));
}
inline void psubsw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    const __m128i diff = _mm_sub_epi32(a, b);
    const __m128i ovf = _mm_srai_epi32(_mm_and_si128(_mm_xor_si128(a, b), _mm_xor_si128(a, diff)), 31);
    const __m128i sat = _mm_xor_si128(_mm_srai_epi32(a, 31), _mm_set1_epi32(INT32_MAX));
    simd::st(d, simd::blend(ovf, sat, diff));
}
// Unsigned 32-bit saturating add/sub.
inline void padduw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    const __m128i sum = _mm_add_epi32(a, b);
    simd::st(d, _mm_or_si128(sum, simd::cmpgt_epu32(a, sum)));
}
inline void psubuw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    simd::st(d, _mm_and_si128(_mm_sub_epi32(a, b), simd::cmpgt_epu32(a, b)));
}
inline void pmaxw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    simd::st(d, simd::blend(_mm_cmpgt_epi32(a, b), a, b));
}
inline void pminw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    simd::st(d, simd::blend(_mm_cmpgt_epi32(b, a), a, b));
}
inline void padsbh(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i a = simd::ld(s), b = simd::ld(t);
    // low 64 bits: lanes 0..3 of (a - b); high 64 bits: lanes 4..7 of (a + b)
    simd::st(d, _mm_unpacklo_epi64(_mm_sub_epi16(a, b), _mm_srli_si128(_mm_add_epi16(a, b), 8)));
}
inline void pextlw(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpacklo_epi32(simd::ld(t), simd::ld(s))); }
inline void pextuw(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpackhi_epi32(simd::ld(t), simd::ld(s))); }
inline void pextlh(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpacklo_epi16(simd::ld(t), simd::ld(s))); }
inline void pextuh(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpackhi_epi16(simd::ld(t), simd::ld(s))); }
inline void pextlb(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpacklo_epi8(simd::ld(t), simd::ld(s))); }
inline void pextub(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpackhi_epi8(simd::ld(t), simd::ld(s))); }
inline void ppacw(u128& d, const u128& s, const u128& t) noexcept {
    const __m128 a = _mm_castsi128_ps(simd::ld(t)), b = _mm_castsi128_ps(simd::ld(s));
    simd::st(d, _mm_castps_si128(_mm_shuffle_ps(a, b, _MM_SHUFFLE(2, 0, 2, 0))));
}
inline void ppach(u128& d, const u128& s, const u128& t) noexcept {
    simd::st(d, _mm_unpacklo_epi64(simd::even_halfwords_low(simd::ld(t)), simd::even_halfwords_low(simd::ld(s))));
}
inline void ppacb(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i low = _mm_set1_epi16(0x00FF);
    simd::st(d, _mm_packus_epi16(_mm_and_si128(simd::ld(t), low), _mm_and_si128(simd::ld(s), low)));
}
inline void pinth(u128& d, const u128& s, const u128& t) noexcept {
    simd::st(d, _mm_unpacklo_epi16(simd::ld(t), _mm_srli_si128(simd::ld(s), 8)));
}
inline void pinteh(u128& d, const u128& s, const u128& t) noexcept {
    const __m128i low = _mm_set1_epi32(0x0000FFFF);
    simd::st(d, _mm_or_si128(_mm_and_si128(simd::ld(t), low), _mm_slli_epi32(_mm_and_si128(simd::ld(s), low), 16)));
}
inline void pcpyld(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpacklo_epi64(simd::ld(t), simd::ld(s))); }
inline void pcpyud(u128& d, const u128& s, const u128& t) noexcept { simd::st(d, _mm_unpackhi_epi64(simd::ld(s), simd::ld(t))); }

inline void pabsw(u128& d, const u128& t) noexcept {
    const __m128i x = simd::ld(t);
    const __m128i sign = _mm_srai_epi32(x, 31);
    const __m128i abs = _mm_sub_epi32(_mm_xor_si128(x, sign), sign);
    const __m128i is_min = _mm_cmpeq_epi32(x, _mm_set1_epi32(INT32_MIN));
    simd::st(d, simd::blend(is_min, _mm_set1_epi32(INT32_MAX), abs));
}
inline void pabsh(u128& d, const u128& t) noexcept {
    const __m128i x = simd::ld(t);
    simd::st(d, _mm_max_epi16(x, _mm_subs_epi16(_mm_setzero_si128(), x)));
}
inline void pcpyh(u128& d, const u128& t) noexcept {
    simd::st(d, _mm_shufflehi_epi16(_mm_shufflelo_epi16(simd::ld(t), 0), 0));
}
inline void pexch(u128& d, const u128& t) noexcept {
    simd::st(d, _mm_shufflehi_epi16(_mm_shufflelo_epi16(simd::ld(t), _MM_SHUFFLE(3, 1, 2, 0)), _MM_SHUFFLE(3, 1, 2, 0)));
}
inline void pexeh(u128& d, const u128& t) noexcept {
    simd::st(d, _mm_shufflehi_epi16(_mm_shufflelo_epi16(simd::ld(t), _MM_SHUFFLE(3, 0, 1, 2)), _MM_SHUFFLE(3, 0, 1, 2)));
}
inline void prevh(u128& d, const u128& t) noexcept {
    simd::st(d, _mm_shufflehi_epi16(_mm_shufflelo_epi16(simd::ld(t), _MM_SHUFFLE(0, 1, 2, 3)), _MM_SHUFFLE(0, 1, 2, 3)));
}
inline void pexcw(u128& d, const u128& t) noexcept { simd::st(d, _mm_shuffle_epi32(simd::ld(t), _MM_SHUFFLE(3, 1, 2, 0))); }
inline void pexew(u128& d, const u128& t) noexcept { simd::st(d, _mm_shuffle_epi32(simd::ld(t), _MM_SHUFFLE(3, 0, 1, 2))); }
inline void prot3w(u128& d, const u128& t) noexcept { simd::st(d, _mm_shuffle_epi32(simd::ld(t), _MM_SHUFFLE(3, 0, 2, 1))); }

inline void psllh(u128& d, const u128& t, u32 sa) noexcept { simd::st(d, _mm_sll_epi16(simd::ld(t), simd::count(sa & 15u))); }
inline void psrlh(u128& d, const u128& t, u32 sa) noexcept { simd::st(d, _mm_srl_epi16(simd::ld(t), simd::count(sa & 15u))); }
inline void psrah(u128& d, const u128& t, u32 sa) noexcept { simd::st(d, _mm_sra_epi16(simd::ld(t), simd::count(sa & 15u))); }
inline void psllw(u128& d, const u128& t, u32 sa) noexcept { simd::st(d, _mm_sll_epi32(simd::ld(t), simd::count(sa & 31u))); }
inline void psrlw(u128& d, const u128& t, u32 sa) noexcept { simd::st(d, _mm_srl_epi32(simd::ld(t), simd::count(sa & 31u))); }
inline void psraw(u128& d, const u128& t, u32 sa) noexcept { simd::st(d, _mm_sra_epi32(simd::ld(t), simd::count(sa & 31u))); }

// No exact SSE2 equivalent (bit-field repack, 2-lane sign-extending shifts, bit scans, byte funnel shift).
using scalar::pext5;
using scalar::plzcw;
using scalar::ppac5;
using scalar::psllvw;
using scalar::psravw;
using scalar::psrlvw;
using scalar::qfsrv;

} // namespace sse2

#if P3FES_EE_MMI_USE_SSE2
using namespace sse2;
#else
using namespace scalar;
#endif

// ---------------------------------------------------------------------------------------------------------
// Operations on HI/LO (both pipes). These are not lane-parallel on the host and have a single implementation.
// ---------------------------------------------------------------------------------------------------------

// PMULTW rd, rs, rt: lanes 0 and 2 multiplied as signed 32x32; rd gets the sign-extended 64-bit products,
// pipe 0 / pipe 1 get the split HI/LO words. (manual)
inline void pmultw(EEContext& c, u128& d, const u128& s, const u128& t) noexcept {
    u128 r;
    for (int i = 0; i < 2; ++i) {
        const s64 p = static_cast<s64>(s.s32[i * 2]) * t.s32[i * 2];
        r.s64[i] = p;
        set_hilo(c, i, static_cast<u64>(p));
    }
    d = r;
}

// PMULTUW: unsigned variant. (manual)
inline void pmultuw(EEContext& c, u128& d, const u128& s, const u128& t) noexcept {
    u128 r;
    for (int i = 0; i < 2; ++i) {
        const u64 p = static_cast<u64>(s.u32[i * 2]) * t.u32[i * 2];
        r.u64[i] = p;
        set_hilo(c, i, p);
    }
    d = r;
}

namespace detail {
inline void pmaddw_impl(EEContext& c, u128& d, const u128& s, const u128& t, bool subtract) noexcept {
    u128 r;
    for (int i = 0; i < 2; ++i) {
        const s64 p = static_cast<s64>(s.s32[i * 2]) * t.s32[i * 2];
        const u64 acc = hilo(c, i) + static_cast<u64>(subtract ? -p : p);
        r.u64[i] = acc;
        set_hilo(c, i, acc);
    }
    d = r;
}
} // namespace detail

// PMADDW / PMSUBW: {HI,LO} of each pipe +/- the signed product; rd gets the 64-bit sums. (manual)
inline void pmaddw(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::pmaddw_impl(c, d, s, t, false); }
inline void pmsubw(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::pmaddw_impl(c, d, s, t, true); }

// PMADDUW: unsigned accumulate. (manual)
inline void pmadduw(EEContext& c, u128& d, const u128& s, const u128& t) noexcept {
    u128 r;
    for (int i = 0; i < 2; ++i) {
        const u64 acc = hilo(c, i) + static_cast<u64>(s.u32[i * 2]) * t.u32[i * 2];
        r.u64[i] = acc;
        set_hilo(c, i, acc);
    }
    d = r;
}

// PDIVW / PDIVUW: lanes 0 and 2 divided into pipes 0 and 1 with the DIV/DIVU rules of hilo.h. (manual;
// divide by zero: upstream, hardware-unverified)
inline void pdivw(EEContext& c, const u128& s, const u128& t) noexcept {
    for (int i = 0; i < 2; ++i) ee::div(c, i, s.u32[i * 2], t.u32[i * 2]);
}
inline void pdivuw(EEContext& c, const u128& s, const u128& t) noexcept {
    for (int i = 0; i < 2; ++i) ee::divu(c, i, s.u32[i * 2], t.u32[i * 2]);
}

// PDIVBW rs, rt: each word of rs divided by rt.h0 (sign-extended); LO.w[i] = quotient, HI.w[i] = remainder
// as a sign-extended halfword. (manual; divide by zero and INT32_MIN / -1: upstream, hardware-unverified)
inline void pdivbw(EEContext& c, const u128& s, const u128& t) noexcept {
    const s32 m = t.s16[0];
    for (int i = 0; i < 4; ++i) {
        const s32 n = s.s32[i];
        if (m == 0) {
            c.lo.s32[i] = n < 0 ? 1 : -1;
            c.hi.s32[i] = n;
        } else if (n == INT32_MIN && m == -1) {
            c.lo.s32[i] = INT32_MIN;
            c.hi.s32[i] = 0;
        } else {
            c.lo.s32[i] = n / m;
            c.hi.s32[i] = static_cast<s16>(n % m);
        }
    }
}

namespace detail {
// Mode 0 = PMULTH, 1 = PMADDH, 2 = PMSUBH. Products p[k] = rs.h[k] * rt.h[k] land in
// LO = {p5, p4, p1, p0}, HI = {p7, p6, p3, p2}; rd = {HI.w2, LO.w2, HI.w0, LO.w0}. (manual)
inline void pmulth_impl(EEContext& c, u128& d, const u128& s, const u128& t, int mode) noexcept {
    s32 p[8];
    for (int i = 0; i < 8; ++i) p[i] = static_cast<s32>(s.s16[i]) * t.s16[i];
    constexpr int kLo[4] = {0, 1, 4, 5}, kHi[4] = {2, 3, 6, 7};
    for (int k = 0; k < 4; ++k) {
        if (mode == 0) {
            c.lo.s32[k] = p[kLo[k]];
            c.hi.s32[k] = p[kHi[k]];
        } else if (mode == 1) {
            c.lo.s32[k] = static_cast<s32>(static_cast<u32>(c.lo.s32[k]) + static_cast<u32>(p[kLo[k]]));
            c.hi.s32[k] = static_cast<s32>(static_cast<u32>(c.hi.s32[k]) + static_cast<u32>(p[kHi[k]]));
        } else {
            c.lo.s32[k] = static_cast<s32>(static_cast<u32>(c.lo.s32[k]) - static_cast<u32>(p[kLo[k]]));
            c.hi.s32[k] = static_cast<s32>(static_cast<u32>(c.hi.s32[k]) - static_cast<u32>(p[kHi[k]]));
        }
    }
    u128 r;
    r.u32[0] = c.lo.u32[0];
    r.u32[1] = c.hi.u32[0];
    r.u32[2] = c.lo.u32[2];
    r.u32[3] = c.hi.u32[2];
    d = r;
}

// PHMADH (subtract = false) / PHMSBH (subtract = true): rs.h[2k+1]*rt.h[2k+1] +/- rs.h[2k]*rt.h[2k] into
// LO.w0, HI.w0, LO.w2, HI.w2; the odd words of HI/LO are undefined on hardware and left unchanged. (manual;
// untouched odd words: upstream)
inline void phmadh_impl(EEContext& c, u128& d, const u128& s, const u128& t, bool subtract) noexcept {
    s32 p[8];
    for (int i = 0; i < 8; ++i) p[i] = static_cast<s32>(s.s16[i]) * t.s16[i];
    const auto pair = [&](int k) noexcept {
        return subtract ? static_cast<s32>(static_cast<u32>(p[k + 1]) - static_cast<u32>(p[k]))
                        : static_cast<s32>(static_cast<u32>(p[k + 1]) + static_cast<u32>(p[k]));
    };
    c.lo.s32[0] = pair(0);
    c.hi.s32[0] = pair(2);
    c.lo.s32[2] = pair(4);
    c.hi.s32[2] = pair(6);
    u128 r;
    r.u32[0] = c.lo.u32[0];
    r.u32[1] = c.hi.u32[0];
    r.u32[2] = c.lo.u32[2];
    r.u32[3] = c.hi.u32[2];
    d = r;
}
} // namespace detail

inline void pmulth(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::pmulth_impl(c, d, s, t, 0); }
inline void pmaddh(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::pmulth_impl(c, d, s, t, 1); }
inline void pmsubh(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::pmulth_impl(c, d, s, t, 2); }
inline void phmadh(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::phmadh_impl(c, d, s, t, false); }
inline void phmsbh(EEContext& c, u128& d, const u128& s, const u128& t) noexcept { detail::phmadh_impl(c, d, s, t, true); }

// PMFHL.fmt: the `fmt` field of the instruction word (bits 10:6). (manual)
enum class PmfhlFormat : u32 { LW = 0, UW = 1, SLW = 2, LH = 3, SH = 4 };

// PMFHL rd: move HI/LO into rd in the selected arrangement.
//   LW : rd = {HI.w2, LO.w2, HI.w0, LO.w0}
//   UW : rd = {HI.w3, LO.w3, HI.w1, LO.w1}
//   SLW: rd.d[i] = sext(sat32({HI.w[2i] : LO.w[2i]}))
//   LH : rd = {HI.h6, HI.h4, LO.h6, LO.h4, HI.h2, HI.h0, LO.h2, LO.h0}
//   SH : rd = {sat16(HI.w3), sat16(HI.w2), sat16(LO.w3), sat16(LO.w2), sat16(HI.w1), sat16(HI.w0), sat16(LO.w1), sat16(LO.w0)}
// Formats 5..31 are reserved; upstream treats them as SH (the `default:` arm). (manual; reserved: upstream)
inline void pmfhl(const EEContext& c, u128& d, u32 fmt) noexcept {
    u128 r = d;
    const u128& lo = c.lo;
    const u128& hi = c.hi;
    switch (fmt) {
    case 0:
        r.u32[0] = lo.u32[0]; r.u32[1] = hi.u32[0]; r.u32[2] = lo.u32[2]; r.u32[3] = hi.u32[2];
        break;
    case 1:
        r.u32[0] = lo.u32[1]; r.u32[1] = hi.u32[1]; r.u32[2] = lo.u32[3]; r.u32[3] = hi.u32[3];
        break;
    case 2:
        for (int i = 0; i < 2; ++i)
            r.s64[i] = detail::sat32(static_cast<s64>((static_cast<u64>(hi.u32[i * 2]) << 32) | lo.u32[i * 2]));
        break;
    case 3:
        r.u16[0] = lo.u16[0]; r.u16[1] = lo.u16[2]; r.u16[2] = hi.u16[0]; r.u16[3] = hi.u16[2];
        r.u16[4] = lo.u16[4]; r.u16[5] = lo.u16[6]; r.u16[6] = hi.u16[4]; r.u16[7] = hi.u16[6];
        break;
    default:
        r.s16[0] = detail::sat16(lo.s32[0]); r.s16[1] = detail::sat16(lo.s32[1]);
        r.s16[2] = detail::sat16(hi.s32[0]); r.s16[3] = detail::sat16(hi.s32[1]);
        r.s16[4] = detail::sat16(lo.s32[2]); r.s16[5] = detail::sat16(lo.s32[3]);
        r.s16[6] = detail::sat16(hi.s32[2]); r.s16[7] = detail::sat16(hi.s32[3]);
        break;
    }
    d = r;
}
inline void pmfhl(const EEContext& c, u128& d, PmfhlFormat fmt) noexcept { pmfhl(c, d, static_cast<u32>(fmt)); }
inline void pmfhl_lw(const EEContext& c, u128& d) noexcept { pmfhl(c, d, PmfhlFormat::LW); }
inline void pmfhl_uw(const EEContext& c, u128& d) noexcept { pmfhl(c, d, PmfhlFormat::UW); }
inline void pmfhl_slw(const EEContext& c, u128& d) noexcept { pmfhl(c, d, PmfhlFormat::SLW); }
inline void pmfhl_lh(const EEContext& c, u128& d) noexcept { pmfhl(c, d, PmfhlFormat::LH); }
inline void pmfhl_sh(const EEContext& c, u128& d) noexcept { pmfhl(c, d, PmfhlFormat::SH); }

// PMTHL.LW rs: LO.w0 = rs.w0, HI.w0 = rs.w1, LO.w2 = rs.w2, HI.w2 = rs.w3; the other words are unchanged.
// LW is the only format the instruction has. (manual)
inline void pmthl(EEContext& c, const u128& s) noexcept {
    c.lo.u32[0] = s.u32[0];
    c.hi.u32[0] = s.u32[1];
    c.lo.u32[2] = s.u32[2];
    c.hi.u32[2] = s.u32[3];
}

// Whole-register moves between HI/LO and a GPR. (manual)
inline void pmfhi(const EEContext& c, u128& d) noexcept { d = c.hi; }
inline void pmflo(const EEContext& c, u128& d) noexcept { d = c.lo; }
inline void pmthi(EEContext& c, const u128& s) noexcept { c.hi = s; }
inline void pmtlo(EEContext& c, const u128& s) noexcept { c.lo = s; }

// QFSRV with the context's SA register (see hilo.h for the bit/byte convention). The using-declaration keeps
// the four-operand form visible next to this overload (a name declared directly in `mmi` would otherwise hide
// the ones reached through the using-directive above).
using scalar::qfsrv;
inline void qfsrv(const EEContext& c, u128& d, const u128& s, const u128& t) noexcept {
    qfsrv(d, s, t, sa_bytes(c));
}

// ---------------------------------------------------------------------------------------------------------
// LQ / SQ: quadword load/store. The EE ignores the low four address bits (the access is always to the
// containing 16-byte-aligned quadword; no address error is raised). (manual; upstream emits `& ~15u`)
// ---------------------------------------------------------------------------------------------------------
inline constexpr u32 kQuadwordMask = ~15u;

inline u128 lq(const EEMemory& mem, u32 vaddr) noexcept { return mem.read<u128>(vaddr & kQuadwordMask); }
inline void sq(EEMemory& mem, u32 vaddr, const u128& rt) noexcept { mem.write<u128>(vaddr & kQuadwordMask, rt); }

} // namespace p3fes::ee::mmi
