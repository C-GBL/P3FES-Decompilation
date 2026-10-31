// Ported from snuri00/ps2-web-recomp @ c0f476e, runtime/include/ps2/fpu.hpp (bit-level add/sub/mul/div/sqrt/
// rsqrt/min/max/key/to_fixed/from_fixed), runtime/include/ps2/generated.hpp (fpu_compare, fpu_div, fpu_rsqrt),
// runtime/src/cop.cpp (cfc1/ctc1) and recomp/codegen.cpp (per-instruction emit rules: abs/neg/mov, the ACC
// forms, compares, mfc1/mtc1), MIT; adapted for p3fes-port (p3fes::ee::fpu namespace, EEContext with u32
// bit-pattern FPR/ACC storage, per-instruction wrappers).
//
// EE COP1 is single precision only, round-toward-zero only, has no denormals (inputs are flushed to signed
// zero) and no NaN/Inf (results that overflow clamp to +/-0x7FFFFFFF, the EE's largest magnitude). Upstream
// models the datapath directly on the 32-bit patterns; this port keeps every expression as written.
//
// Verified against PCSX2 2.8.2 with compiled test vectors (tools/ours/eevec, tests/ee/vectors/pcsx2_vectors.json,
// docs/PCSX2.md "EE semantics vectors"); where PCSX2's EE interpreter and recompiler disagree the interpreter is
// the reference. Rules changed by that pass (each with the vector id that drove it):
//  * Flags: x/0 raises D (bit 16) + SD (bit 5); 0/0, sqrt of a negative and rsqrt of a negative raise I (bit 17)
//    + SI (bit 6); rsqrt with ft = 0 raises D + SD (fpu_2216, fpu_2219, fpu_2259, fpu_2280). Bits are OR-ed in,
//    nothing is cleared (the interpreter's behaviour; the recompiler clears I/D on every DIV/SQRT/RSQRT).
//    The binary never executes CFC1 (docs/ANALYSIS/08), so only the C bit (23) is observable.
// Rules kept as documented disagreements with PCSX2 (see docs/PCSX2.md for the classes):
//  * add/sub keep upstream's 25-binade alignment, which is the EE recompiler's ADD.S/SUB.S (fpu_2129: 1 - 2^-26 =
//    1.0; fpu_2174: 2^31 + -1.0 = 2^31); the interpreter and both engines' VU path are exact round-toward-zero
//    (0x3F7FFFFF / 0x4EFFFFFF, vu0_2839). Lead decision (ADR-0012: the recompiler is the state oracle); hardware unknown.
//  * The EE's exponent-255 binade and the +/-0x7FFFFFFF overflow / divide-by-zero value (manual: Fmax). PCSX2
//    computes on host IEEE floats: exponent-255 operands are Inf/NaN to it and every such result is clamped to
//    +/-0x7F7FFFFF ("ee-range" vectors).
//  * div/sqrt/rsqrt computed in IEEE double then narrowed; DIV.S and SQRT.S round to nearest (`div_nearest`,
//    `sqrt_nearest`: the recompiler's values; the interpreter truncates both: fpu_2213, fpu_2271). SQRT.S followed
//    the interpreter until 2026-10-31, which broke the field pad heading on a centred stick (sqrt_nearest). VU0
//    VDIV / VSQRT and the unused RSQRT.S keep truncation.
//  * max/min flush both operands and return the first on ties; both PCSX2 engines order -0 below +0 without
//    flushing (fpu_2530). The binary never uses MAX.S/MIN.S.
//  * cfc1 of FCR0 returns 0x2E30 (recompiler; interpreter 0x2E00). FCR31 is held unmasked from reset value 0, as
//    the interpreter does; the recompiler fixes bits 24 and 0 (0x01000001) and masks CTC1 to 0x0083C078.
#pragma once

#include "p3fes/ee_context.h"

#include <bit>
#include <cmath>

namespace p3fes::ee::fpu {

inline constexpr u32 kSign = 0x80000000u;
inline constexpr u32 kAbs = 0x7FFFFFFFu;
inline constexpr u32 kOne = 0x3F800000u;
inline constexpr u32 kMax = 0x7FFFFFFFu; // largest EE magnitude; +/-kMax is the overflow clamp

// FCR31 layout (EE Core User's Manual): bit 23 = C (condition), 17..14 = I D O U cause/flag bits,
// 6..3 = SI SD SO SU sticky bits.
inline constexpr u32 kFcr31Condition = 1u << 23;
inline constexpr u32 kFcr31DivideByZero = (1u << 16) | (1u << 5); // D + SD: x/0, rsqrt with ft = 0 (PCSX2 2.8.2 observed: fpu_2216)
inline constexpr u32 kFcr31Invalid = (1u << 17) | (1u << 6);      // I + SI: 0/0, sqrt/rsqrt of a negative (fpu_2219, fpu_2259)
inline constexpr u32 kFcr0Value = 0x2E30u;         // CFC1 $0 (implementation/revision), PCSX2 recompiler value

// ---------------------------------------------------------------------------------------------------------
// Bit-level core on u32 patterns.
// ---------------------------------------------------------------------------------------------------------
inline u32 exponent(u32 x) noexcept { return (x >> 23) & 0xFFu; }
// Denormals flush to a zero of the same sign. (manual)
inline u32 flush(u32 x) noexcept { return exponent(x) ? x : (x & kSign); }
inline u32 mantissa(u32 x) noexcept { return (x & 0x7FFFFFu) | 0x800000u; }

// Assemble a result: exponent overflow clamps to +/-kMax, underflow to signed zero. (manual: no Inf/NaN,
// overflow saturates, underflow flushes)
inline u32 pack(u32 sign, int e, u32 m) noexcept {
    if (e > 255) return sign | kAbs;
    if (e <= 0) return sign;
    return sign | (static_cast<u32>(e) << 23) | (m & 0x7FFFFFu);
}

// Upstream's addition: operands aligned with one extra bit, the shifted-out bits of the smaller operand dropped, and
// nothing contributed beyond 25 binades. This is NOT exact round-toward-zero (1.0 - 2^-26 gives 1.0, 2^31 + -1.0 gives
// 2^31) but it is what PCSX2's EE recompiler computes for ADD.S/SUB.S (fpu_2129, fpu_2174), and ADR-0012 makes that
// recompiler the state oracle: every capture the port is compared against runs it. PCSX2's interpreter and its VU
// path are exact RZ (vu0_2839, vu0_2873); those vectors are recorded as agree-rec / disagree:add-alignment. Hardware
// truth is unknown. (lead decision 2026-10-19, same basis as integration decision 1 for DIV.S)
inline u32 add(u32 a, u32 b) noexcept {
    a = flush(a);
    b = flush(b);
    u32 aa = a & kAbs, ba = b & kAbs;
    if (!ba) return aa ? a : (a & b); // x + 0 = x; (+/-0) + (+/-0) keeps the sign only when both agree
    if (!aa) return b;
    if (ba > aa) {
        const u32 ta = a; a = b; b = ta;
        const u32 tm = aa; aa = ba; ba = tm;
    }
    int e = static_cast<int>(aa >> 23);
    const int diff = e - static_cast<int>(ba >> 23);
    u32 ma = mantissa(aa) << 1;
    const u32 mb = diff > 25 ? 0u : (mantissa(ba) << 1) >> diff;
    if ((a ^ b) & kSign) {
        ma -= mb;
        if (!ma) return 0;
        const int shift = std::countl_zero(ma) - 7;
        ma <<= shift;
        e -= shift;
    } else {
        ma += mb;
        if (ma & 0x2000000u) {
            ma >>= 1;
            ++e;
        }
    }
    return pack(a & kSign, e, ma >> 1);
}

inline u32 sub(u32 a, u32 b) noexcept { return add(a, b ^ kSign); }

inline u32 mul(u32 a, u32 b) noexcept {
    const u32 sign = (a ^ b) & kSign;
    const int ea = static_cast<int>(exponent(a)), eb = static_cast<int>(exponent(b));
    if (!ea || !eb) return sign; // a denormal/zero operand yields signed zero
    u64 m = static_cast<u64>(mantissa(a)) * mantissa(b);
    int e = ea + eb - 127;
    if (m >> 47) {
        m >>= 24;
        ++e;
    } else {
        m >>= 23;
    }
    return pack(sign, e, static_cast<u32>(m));
}

// Exact widening of an EE single to a double (denormals read as zero).
inline double to_double(u32 x) noexcept {
    if (!exponent(x)) return (x & kSign) ? -0.0 : 0.0;
    const u64 bits = (static_cast<u64>(x & kSign) << 32) |
                     (static_cast<u64>(exponent(x) + 1023u - 127u) << 52) |
                     (static_cast<u64>(x & 0x7FFFFFu) << 29);
    return std::bit_cast<double>(bits);
}

// Truncating narrowing back to an EE single (round toward zero, clamp, flush).
inline u32 from_double(double d) noexcept {
    const u64 bits = std::bit_cast<u64>(d);
    const u32 sign = static_cast<u32>(bits >> 32) & kSign;
    const int e = static_cast<int>((bits >> 52) & 0x7FFu);
    if (!e) return sign;
    return pack(sign, e - 1023 + 127, static_cast<u32>(bits >> 29));
}

// Round-to-nearest-even narrowing (clamp, flush), for DIV.S only (div_nearest below). A double quotient of two
// 24-bit significands rounded once more to 24 bits is correctly rounded (53 >= 2 * 24 + 2).
inline u32 from_double_nearest(double d) noexcept {
    const u64 bits = std::bit_cast<u64>(d);
    const u32 sign = static_cast<u32>(bits >> 32) & kSign;
    const int e = static_cast<int>((bits >> 52) & 0x7FFu);
    if (!e) return sign;
    u64 m = (bits & 0xFFFFFFFFFFFFFull) | (1ull << 52);  // 53-bit significand
    const u64 rest = m & ((1ull << 29) - 1u);
    m >>= 29;                                             // 24 bits
    if (rest > (1ull << 28) || (rest == (1ull << 28) && (m & 1u))) ++m;
    int ee = e - 1023 + 127;
    if (m >> 24) {
        m >>= 1;
        ++ee;
    }
    return pack(sign, ee, static_cast<u32>(m));
}

struct Result {
    u32 value;
    bool invalid;      // the operation raised the divide-by-zero OR the invalid condition (either flag)
    bool zero_divide;  // D: x / 0, rsqrt with ft = 0 (any fs)   (PCSX2 2.8.2 observed: fpu_2216, fpu_2280, fpu_2289)
    bool invalid_op;   // I: 0 / 0, sqrt / rsqrt of a negative    (fpu_2219, fpu_2259, fpu_2283)
};
inline constexpr Result ok(u32 v) noexcept { return {v, false, false, false}; }
inline constexpr Result raise_d(u32 v) noexcept { return {v, true, true, false}; }
inline constexpr Result raise_i(u32 v) noexcept { return {v, true, false, true}; }

// x / 0 = +/-kMax with D; 0 / 0 = +/-kMax with I; 0 / y = signed zero. (manual; flags: PCSX2 2.8.2 observed)
inline Result div(u32 a, u32 b) noexcept {
    a = flush(a);
    b = flush(b);
    const u32 sign = (a ^ b) & kSign;
    if (!(b & kAbs)) return (a & kAbs) ? raise_d(sign | kAbs) : raise_i(sign | kAbs);
    if (!(a & kAbs)) return ok(sign);
    return ok(from_double(to_double(a) / to_double(b)));
}

// DIV.S of the EE FPU: as `div`, but the quotient rounds to nearest. Chosen to agree with the PCSX2 oracle, whose
// FPU division rounds to nearest while every other FPU operation chops (PCSX2 2.8.2 "Division Rounding Mode"
// default): its first_flip state holds 1.0 / 20.0 = 0x3D4CCCCD (div.s @0x1D4470 in sub_1D4460, stored at
// 0x872258), where truncation gives 0x3D4CCCCC (docs/INTEGRATION_LOG.md). Hardware-unverified. VU0 VDIV and
// VU1 DIV keep `div` (truncating).
inline Result div_nearest(u32 a, u32 b) noexcept {
    a = flush(a);
    b = flush(b);
    const u32 sign = (a ^ b) & kSign;
    if (!(b & kAbs)) return (a & kAbs) ? raise_d(sign | kAbs) : raise_i(sign | kAbs);
    if (!(a & kAbs)) return ok(sign);
    return ok(from_double_nearest(to_double(a) / to_double(b)));
}

// sqrt(|a|), truncated; the sign of a negative operand is dropped (manual; PCSX2 2.8.2 observed: fpu_2259 sqrt(-4) = 2
// with I). VU0 VSQRT uses this (with sqrt_flags); the FPU's SQRT.S rounds to nearest (sqrt_nearest below).
inline u32 sqrt(u32 a) noexcept {
    a = flush(a) & kAbs;
    if (!a) return 0;
    return from_double(std::sqrt(to_double(a)));
}
// SQRT.S of the EE FPU: as `sqrt`, but rounded to nearest, like DIV.S (div_nearest). PCSX2's EE recompiler -- the state
// oracle (ADR-0012), whose DIV.S rounding div_nearest already follows -- rounds SQRT.S to nearest too (eevec class
// `int-sqrt-truncates`, docs/PCSX2.md: sqrt(10) = 0x404A62C2; its interpreter truncates to ...C1). Truncating SQRT.S
// while DIV.S rounds broke the game's own unit-vector code: the field pad heading sub_1B02C0 normalises the stick
// (0, 127) to z = 0x3F7FFFFF, then divides it by sqrt(z * z) = sqrt(0x3F7FFFFE): truncated 0x3F7FFFFE gives the
// quotient 0x3F800001, acosf of a value above 1 returns its 0/0 clamp and the hero turns away and stops (a centred x
// byte 0x80 with 64 of the 256 y bytes, the keyboard's S among them). Rounded, sqrt gives 0x3F7FFFFF and the quotient
// is 1.0. A double square root of a single rounded once more to 24 bits is correctly rounded (53 >= 2 * 24 + 2).
inline u32 sqrt_nearest(u32 a) noexcept {
    a = flush(a) & kAbs;
    if (!a) return 0;
    return from_double_nearest(std::sqrt(to_double(a)));
}
// `sqrt` / `sqrt_nearest` with the I flag for a negative operand.
inline Result sqrt_flags(u32 a, bool nearest = false) noexcept {
    const u32 r = nearest ? sqrt_nearest(a) : sqrt(a);
    const u32 f = flush(a);   // a negative denormal is -0 after the flush: no I (PCSX2 2.8.2 interpreter: fpu_2273)
    return ((f & kSign) && (f & kAbs)) ? raise_i(r) : ok(r);
}

// a / sqrt(|b|). b = 0 gives +/-kMax (sign of a) with D, also for a = 0 (manual: RSQRT has no 0/0 case; PCSX2 2.8.2
// interpreter: fpu_2289); b < 0 uses |b| and raises I; a = 0 gives signed zero. (fpu_2280, fpu_2283, vu0_3279)
inline Result rsqrt(u32 a, u32 b) noexcept {
    a = flush(a);
    b = flush(b);
    const bool negative = (b & kSign) != 0;
    b &= kAbs;
    if (!b) return raise_d((a & kSign) | kAbs);
    if (!(a & kAbs)) return negative ? raise_i(a & kSign) : ok(a & kSign);
    const u32 r = from_double(to_double(a) / std::sqrt(to_double(b)));
    return negative ? raise_i(r) : ok(r);
}

// Order-preserving integer key: flushes denormals, so -0 and +0 compare equal. (manual: C.cond flushes)
inline s32 key(u32 x) noexcept {
    x = flush(x);
    const s32 magnitude = static_cast<s32>(x & kAbs);
    return (x & kSign) ? -magnitude : magnitude;
}

// MAX.S / MIN.S return the first operand's pattern on ties. (manual; tie choice: upstream)
inline u32 max(u32 a, u32 b) noexcept { return key(a) >= key(b) ? a : b; }
inline u32 min(u32 a, u32 b) noexcept { return key(a) <= key(b) ? a : b; }

// Float -> fixed point with `fraction` fractional bits, truncating; saturates at the 32-bit bounds. CVT.W.S is
// fraction 0 (the VU's FTOI4/12/15 reuse this). (manual: EE saturates instead of returning the IEEE 0x80000000)
inline u32 to_fixed(u32 x, int fraction) noexcept {
    const int e = static_cast<int>(exponent(x)) + fraction;
    if (e <= 126 || !exponent(x)) return 0;
    const bool negative = (x & kSign) != 0;
    if (e >= 158) return negative ? 0x80000000u : 0x7FFFFFFFu;
    const int shift = e - 150;
    const u32 m = mantissa(x);
    const u32 v = shift >= 0 ? m << shift : m >> -shift;
    return negative ? 0u - v : v;
}

// Fixed point -> float, truncating. CVT.S.W is fraction 0. (manual)
inline u32 from_fixed(s32 v, int fraction) noexcept {
    return from_double(static_cast<double>(v) / static_cast<double>(1u << fraction));
}

inline u32 cvt_w_s(u32 x) noexcept { return to_fixed(x, 0); }
inline u32 cvt_s_w(u32 v) noexcept { return from_fixed(static_cast<s32>(v), 0); }

// ---------------------------------------------------------------------------------------------------------
// Register access. EEContext stores FPRs and ACC as raw u32 bit patterns, so no host floating-point
// operation ever touches a register; `bits`/`from_bits` exist for callers that hold host floats.
// ---------------------------------------------------------------------------------------------------------
inline u32 bits(f32 f) noexcept { return std::bit_cast<u32>(f); }
inline f32 from_bits(u32 v) noexcept { return std::bit_cast<f32>(v); }

inline u32 fpr(const EEContext& c, u32 i) noexcept { return c.fpr[i]; }
inline void set_fpr(EEContext& c, u32 i, u32 v) noexcept { c.fpr[i] = v; }
inline u32 acc(const EEContext& c) noexcept { return c.acc; }
inline void set_acc(EEContext& c, u32 v) noexcept { c.acc = v; }

// ---------------------------------------------------------------------------------------------------------
// Instruction forms. Register numbers are the fd/fs/ft fields of the instruction word.
// ---------------------------------------------------------------------------------------------------------
inline void add_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, add(fpr(c, fs), fpr(c, ft))); }
inline void sub_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, sub(fpr(c, fs), fpr(c, ft))); }
inline void mul_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, mul(fpr(c, fs), fpr(c, ft))); }
// Flag bits are OR-ed into FCR31; nothing is cleared (PCSX2 2.8.2 interpreter observed: fpu_2781 keeps preset I/D).
inline void raise(EEContext& c, const Result& r) noexcept {
    if (r.zero_divide) c.fcr31 |= kFcr31DivideByZero;
    if (r.invalid_op) c.fcr31 |= kFcr31Invalid;
}
inline void div_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept {
    const Result r = div_nearest(fpr(c, fs), fpr(c, ft));
    set_fpr(c, fd, r.value);
    raise(c, r);
}
// SQRT.S fd, ft (the source is the ft field; manual encoding), rounded to nearest (sqrt_nearest).
inline void sqrt_s(EEContext& c, u32 fd, u32 ft) noexcept {
    const Result r = sqrt_flags(fpr(c, ft), true);
    set_fpr(c, fd, r.value);
    raise(c, r);
}
// RSQRT.S fd, fs, ft = fs / sqrt(ft). Unused by the binary (docs/ANALYSIS/08).
inline void rsqrt_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept {
    const Result r = rsqrt(fpr(c, fs), fpr(c, ft));
    set_fpr(c, fd, r.value);
    raise(c, r);
}
// ABS/NEG/MOV operate on the pattern without flushing. (manual)
inline void abs_s(EEContext& c, u32 fd, u32 fs) noexcept { set_fpr(c, fd, fpr(c, fs) & kAbs); }
inline void neg_s(EEContext& c, u32 fd, u32 fs) noexcept { set_fpr(c, fd, fpr(c, fs) ^ kSign); }
inline void mov_s(EEContext& c, u32 fd, u32 fs) noexcept { set_fpr(c, fd, fpr(c, fs)); }

// ACC forms. MADD/MSUB read ACC and write fd; the *A forms write ACC. (manual)
inline void adda_s(EEContext& c, u32 fs, u32 ft) noexcept { set_acc(c, add(fpr(c, fs), fpr(c, ft))); }
inline void suba_s(EEContext& c, u32 fs, u32 ft) noexcept { set_acc(c, sub(fpr(c, fs), fpr(c, ft))); }
inline void mula_s(EEContext& c, u32 fs, u32 ft) noexcept { set_acc(c, mul(fpr(c, fs), fpr(c, ft))); }
inline void madd_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, add(acc(c), mul(fpr(c, fs), fpr(c, ft)))); }
inline void msub_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, sub(acc(c), mul(fpr(c, fs), fpr(c, ft)))); }
inline void madda_s(EEContext& c, u32 fs, u32 ft) noexcept { set_acc(c, add(acc(c), mul(fpr(c, fs), fpr(c, ft)))); }
inline void msuba_s(EEContext& c, u32 fs, u32 ft) noexcept { set_acc(c, sub(acc(c), mul(fpr(c, fs), fpr(c, ft)))); }

inline void cvt_w_s(EEContext& c, u32 fd, u32 fs) noexcept { set_fpr(c, fd, cvt_w_s(fpr(c, fs))); }
inline void cvt_s_w(EEContext& c, u32 fd, u32 fs) noexcept { set_fpr(c, fd, cvt_s_w(fpr(c, fs))); }
inline void max_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, max(fpr(c, fs), fpr(c, ft))); }
inline void min_s(EEContext& c, u32 fd, u32 fs, u32 ft) noexcept { set_fpr(c, fd, min(fpr(c, fs), fpr(c, ft))); }

// Compares set/clear FCR31.C; the EE has only C.F, C.EQ, C.LT, C.LE (no unordered forms). (manual)
inline void set_condition(EEContext& c, bool condition) noexcept {
    c.fcr31 = condition ? (c.fcr31 | kFcr31Condition) : (c.fcr31 & ~kFcr31Condition);
}
inline void c_f_s(EEContext& c) noexcept { set_condition(c, false); }
inline void c_eq_s(EEContext& c, u32 fs, u32 ft) noexcept { set_condition(c, key(fpr(c, fs)) == key(fpr(c, ft))); }
inline void c_lt_s(EEContext& c, u32 fs, u32 ft) noexcept { set_condition(c, key(fpr(c, fs)) < key(fpr(c, ft))); }
inline void c_le_s(EEContext& c, u32 fs, u32 ft) noexcept { set_condition(c, key(fpr(c, fs)) <= key(fpr(c, ft))); }

// BC1T/BC1TL branch when this is true, BC1F/BC1FL when false. (manual)
inline bool condition(const EEContext& c) noexcept { return (c.fcr31 & kFcr31Condition) != 0; }
inline bool bc1t(const EEContext& c) noexcept { return condition(c); }
inline bool bc1f(const EEContext& c) noexcept { return !condition(c); }

// MFC1 rt, fs: the 32-bit pattern sign-extended into the 64-bit GPR. MTC1 rt, fs: the low word of rt. (manual)
inline u64 mfc1(const EEContext& c, u32 fs) noexcept { return static_cast<u64>(static_cast<s64>(static_cast<s32>(fpr(c, fs)))); }
inline void mtc1(EEContext& c, u32 fs, u32 rt_low) noexcept { set_fpr(c, fs, rt_low); }

// CFC1/CTC1: only FCR0 (read-only) and FCR31 exist. (manual; FCR0 value and the unmasked FCR31 write: upstream)
inline u32 cfc1(const EEContext& c, u32 reg) noexcept {
    if (reg == 0) return kFcr0Value;
    if (reg == 31) return c.fcr31;
    return 0;
}
inline void ctc1(EEContext& c, u32 reg, u32 value) noexcept {
    if (reg == 31) c.fcr31 = value;
}

} // namespace p3fes::ee::fpu
