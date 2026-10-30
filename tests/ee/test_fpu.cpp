// EE COP1 vectors (runtime/include/p3fes/ee/fpu.h). The EE FPU is single precision, round-toward-zero only,
// flushes denormals and has no NaN/Inf: overflow clamps to +/-0x7FFFFFFF.
// Provenance:
//   (hand: EE Core User's Manual semantics)   - the manual defines the result (flush, clamp, RZ, saturation)
//   (upstream behaviour, hardware-unverified) - detail the manual does not pin down; we match ps2-web-recomp @ c0f476e
//   (PCSX2 2.8.2 observed: <id>)             - settled by tests/ee/vectors/pcsx2_vectors.json (tools/ours/eevec)
#include "ee_test_util.h"

#include "p3fes/ee/fpu.h"

using namespace p3fes;
using namespace p3fes::ee;
using namespace p3fes::ee_test;

namespace {

constexpr u32 kOne = f2u(1.0f), kTwo = f2u(2.0f), kThree = f2u(3.0f), kFour = f2u(4.0f), kHalf = f2u(0.5f);
constexpr u32 kFltMax = 0x7F7FFFFFu; // IEEE FLT_MAX; the EE's own maximum is 0x7FFFFFFF
constexpr u32 kEEMax = 0x7FFFFFFFu;
constexpr u32 kNegZero = 0x80000000u;
constexpr u32 kDenormal = 0x00000001u;
constexpr u32 kNegDenormal = 0x80000001u;

} // namespace

TEST_CASE("flush: denormals become signed zero, normals pass") {
    // (hand: manual)
    CHECK(fpu::flush(kDenormal) == 0u);
    CHECK(fpu::flush(kNegDenormal) == kNegZero);
    CHECK(fpu::flush(0x007FFFFFu) == 0u);
    CHECK(fpu::flush(0x00800000u) == 0x00800000u); // smallest normal is kept
    CHECK(fpu::flush(kOne) == kOne);
}

TEST_CASE("add.s / sub.s: exact cases, signed zero, flush, round-toward-zero") {
    // (hand: manual)
    CHECK(fpu::add(kOne, kOne) == kTwo);
    CHECK(fpu::add(f2u(1.5f), f2u(2.25f)) == f2u(3.75f));
    CHECK(fpu::add(kOne, kOne ^ fpu::kSign) == 0u);          // x + (-x) = +0
    CHECK(fpu::sub(kThree, kTwo) == kOne);
    CHECK(fpu::sub(kTwo, kThree) == (kOne | fpu::kSign));
    CHECK(fpu::add(kNegZero, kNegZero) == kNegZero);          // (-0) + (-0) = -0
    CHECK(fpu::add(0u, kNegZero) == 0u);                      // (+0) + (-0) = +0
    CHECK(fpu::add(kOne, kDenormal) == kOne);                 // denormal operand is zero
    CHECK(fpu::add(kDenormal, kNegDenormal) == 0u);
    CHECK(fpu::add(0u, kTwo) == kTwo);
    CHECK(fpu::add(kTwo, 0u) == kTwo);
    // (hand: manual) overflow clamps to the EE maximum, not Inf.
    CHECK(fpu::add(kFltMax, kFltMax) == kEEMax);
    CHECK(fpu::add(kFltMax | fpu::kSign, kFltMax | fpu::kSign) == (kEEMax | fpu::kSign));
    // (hand: manual) round toward zero: 1 + 1.5 ulp truncates to 1 + 1 ulp (round-to-nearest would give +2 ulp).
    CHECK(fpu::add(kOne, 0x34400000u) == 0x3F800001u);
    // (hand: manual) 1 + 2^-24 is below half an ulp and truncates away entirely.
    CHECK(fpu::add(kOne, 0x33800000u) == kOne);
    // (upstream behaviour, deliberate disagreement; PCSX2 2.8.2 recompiler observed: fpu_2128, fpu_2129, fpu_2174)
    // operands more than 25 binades apart contribute nothing, so 1 - 2^-26 stays 1.0 and 2^31 + -1.0 stays 2^31. PCSX2's
    // EE recompiler -- the state oracle of ADR-0012, which every capture runs -- computes exactly this; its interpreter
    // and both engines' VU path are exact round-toward-zero (0x3F7FFFFF, 0x4EFFFFFF; vu0_2839). Lead decision 2026-10-19
    // on the same basis as integration decision 1 for DIV.S; hardware truth unknown.
    CHECK(fpu::add(kOne, 0x32800000u) == kOne);
    CHECK(fpu::sub(kOne, 0x32800000u) == kOne);
    CHECK(fpu::add(0x4F000000u, kOne | fpu::kSign) == 0x4F000000u);
}

TEST_CASE("mul.s: exact products, signed zero, flush, clamp, truncation") {
    // (hand: manual)
    CHECK(fpu::mul(kTwo, kThree) == f2u(6.0f));
    CHECK(fpu::mul(f2u(1.5f), f2u(1.5f)) == f2u(2.25f));
    CHECK(fpu::mul(kTwo, kThree | fpu::kSign) == (f2u(6.0f) | fpu::kSign));
    CHECK(fpu::mul(kTwo | fpu::kSign, 0u) == kNegZero);       // -x * 0 = -0
    CHECK(fpu::mul(kDenormal, kTwo) == 0u);                   // denormal operand yields zero
    CHECK(fpu::mul(kFltMax, kTwo) == kEEMax);                 // overflow clamp
    CHECK(fpu::mul(kFltMax | fpu::kSign, kTwo) == (kEEMax | fpu::kSign));
    CHECK(fpu::mul(0x0D800000u, 0x0D800000u) == 0u);          // 2^-100 * 2^-100 underflows to +0
    CHECK(fpu::mul(0x0D800000u | fpu::kSign, 0x0D800000u) == kNegZero);
    // (hand: manual) RZ: (1 + 2^-23)^2 = 1 + 2^-22 + 2^-46 truncates to 0x3F800002.
    CHECK(fpu::mul(0x3F800001u, 0x3F800001u) == 0x3F800002u);
}

TEST_CASE("div.s: quotient, divide-by-zero clamp with flag, zero dividend, truncation") {
    // (hand: manual)
    CHECK(fpu::div(kOne, kTwo).value == kHalf);
    CHECK_FALSE(fpu::div(kOne, kTwo).invalid);
    CHECK(fpu::div(f2u(6.0f), kThree).value == kTwo);
    // (hand: manual) x / 0 = +/-max with the divide-by-zero condition.
    CHECK(fpu::div(kOne, 0u).value == kEEMax);
    CHECK(fpu::div(kOne, 0u).invalid);
    CHECK(fpu::div(kOne | fpu::kSign, 0u).value == (kEEMax | fpu::kSign));
    CHECK(fpu::div(kOne, kNegZero).value == (kEEMax | fpu::kSign));
    CHECK(fpu::div(kOne, kDenormal).invalid);                 // denormal divisor is zero
    // (hand: manual) 0 / y = signed zero.
    CHECK(fpu::div(0u, f2u(5.0f)).value == 0u);
    CHECK(fpu::div(0u, f2u(-5.0f)).value == kNegZero);
    // (PCSX2 2.8.2 observed: fpu_2219) 0 / 0 = +max with the invalid (I) condition, x / 0 with divide-by-zero (D).
    CHECK(fpu::div(0u, 0u).value == kEEMax);
    CHECK(fpu::div(0u, 0u).invalid);
    CHECK(fpu::div(0u, 0u).invalid_op);
    CHECK_FALSE(fpu::div(0u, 0u).zero_divide);
    CHECK(fpu::div(kOne, 0u).zero_divide);
    CHECK_FALSE(fpu::div(kOne, 0u).invalid_op);
    // (hand: manual) RZ: 1/3 truncates to 0x3EAAAAAA (round-to-nearest would give 0x3EAAAAAB).
    CHECK(fpu::div(kOne, kThree).value == 0x3EAAAAAAu);
}

TEST_CASE("div.s rounds to nearest (div_nearest; VU0/VU1 division keeps truncation)") {
    // (PCSX2 oracle, hardware-unverified) first_flip: sub_1D4460's div.s @0x1D4470 stores 1.0 / 20.0 = 0x3D4CCCCD at
    // 0x872258 (truncation gives 0x3D4CCCCC); docs/INTEGRATION_LOG.md.
    CHECK(fpu::div_nearest(kOne, f2u(20.0f)).value == 0x3D4CCCCDu);
    CHECK(fpu::div(kOne, f2u(20.0f)).value == 0x3D4CCCCCu);
    // (hand: IEEE round-to-nearest-even) 1/3 rounds up, 2/3 rounds up, exact quotients unchanged.
    CHECK(fpu::div_nearest(kOne, kThree).value == 0x3EAAAAABu);
    CHECK(fpu::div_nearest(kTwo, kThree).value == 0x3F2AAAABu);
    CHECK(fpu::div_nearest(f2u(6.0f), kThree).value == kTwo);
    CHECK(fpu::div_nearest(f2u(-2.0f), f2u(1.5f)).value == 0xBFAAAAABu);
    // Same special cases as div: x / 0 clamps with the flag, 0 / y is signed zero, EE overflow clamps.
    CHECK(fpu::div_nearest(kOne, 0u).value == kEEMax);
    CHECK(fpu::div_nearest(kOne, 0u).invalid);
    CHECK(fpu::div_nearest(0u, f2u(-5.0f)).value == kNegZero);
    CHECK(fpu::div_nearest(0x7F7FFFFFu, 0x00800000u).value == kEEMax);  // 2^128 / 2^-126: exponent overflow
    // Rounding that carries into the exponent: (2 - 2^-23) / (1 - 2^-24)... quotient just below 2 rounds to 2.0.
    CHECK(fpu::div_nearest(0x3FFFFFFFu, 0x3F7FFFFFu).value == 0x40000000u);
    EEContext c;
    fpu::set_fpr(c, 1, kOne);
    fpu::set_fpr(c, 2, kThree);
    fpu::div_s(c, 3, 1, 2);
    CHECK(fpu::fpr(c, 3) == 0x3EAAAAABu);  // the instruction form uses div_nearest
}

TEST_CASE("sqrt.s / rsqrt.s") {
    // (hand: manual)
    CHECK(fpu::sqrt(kFour) == kTwo);
    CHECK(fpu::sqrt(0u) == 0u);
    CHECK(fpu::sqrt(kNegZero) == 0u);
    CHECK(fpu::sqrt(kDenormal) == 0u);
    CHECK(fpu::sqrt(kTwo) == 0x3FB504F3u); // sqrt(2) truncated
    // (PCSX2 2.8.2 observed: fpu_2259) sqrt of a negative returns sqrt(|x|) and raises I (sqrt_flags).
    CHECK(fpu::sqrt(kFour | fpu::kSign) == kTwo);
    CHECK(fpu::sqrt_flags(kFour | fpu::kSign).invalid_op);
    CHECK_FALSE(fpu::sqrt_flags(kFour).invalid);
    CHECK_FALSE(fpu::sqrt_flags(kNegZero).invalid);
    // (hand: manual) rsqrt = fs / sqrt(ft); ft = 0 clamps with the flag; fs = 0 gives signed zero.
    CHECK(fpu::rsqrt(kOne, kFour).value == kHalf);
    CHECK_FALSE(fpu::rsqrt(kOne, kFour).invalid);
    CHECK(fpu::rsqrt(kOne, 0u).value == kEEMax);
    CHECK(fpu::rsqrt(kOne, 0u).invalid);
    CHECK(fpu::rsqrt(kOne | fpu::kSign, 0u).value == (kEEMax | fpu::kSign));
    CHECK(fpu::rsqrt(0u, kFour).value == 0u);
    CHECK(fpu::rsqrt(kNegZero, kFour).value == kNegZero);
    // (PCSX2 2.8.2 observed: fpu_2283) negative ft uses |ft| and raises I; ft = 0 raises D.
    CHECK(fpu::rsqrt(kOne, kFour | fpu::kSign).value == kHalf);
    CHECK(fpu::rsqrt(kOne, kFour | fpu::kSign).invalid_op);
    CHECK(fpu::rsqrt(kOne, 0u).zero_divide);
}

TEST_CASE("c.eq/c.lt/c.le/c.f: ordering through the flushed sign-magnitude key") {
    EEContext c;
    fpu::set_fpr(c, 1, kOne);
    fpu::set_fpr(c, 2, kTwo);
    fpu::set_fpr(c, 3, kOne | fpu::kSign);
    fpu::set_fpr(c, 4, kNegZero);
    fpu::set_fpr(c, 5, 0u);
    fpu::set_fpr(c, 6, kDenormal);
    fpu::set_fpr(c, 7, kTwo | fpu::kSign);
    // (hand: manual)
    fpu::c_lt_s(c, 1, 2); CHECK(fpu::bc1t(c));                // 1 < 2
    fpu::c_lt_s(c, 2, 2); CHECK(fpu::bc1f(c));                // equal operands are not less
    fpu::c_le_s(c, 2, 2); CHECK(fpu::bc1t(c));
    fpu::c_eq_s(c, 2, 2); CHECK(fpu::bc1t(c));
    fpu::c_eq_s(c, 1, 2); CHECK(fpu::bc1f(c));
    fpu::c_lt_s(c, 3, 5); CHECK(fpu::bc1t(c));                // -1 < +0
    fpu::c_lt_s(c, 7, 3); CHECK(fpu::bc1t(c));                // -2 < -1
    fpu::c_lt_s(c, 3, 7); CHECK(fpu::bc1f(c));
    fpu::c_eq_s(c, 4, 5); CHECK(fpu::bc1t(c));                // -0 == +0
    fpu::c_le_s(c, 5, 4); CHECK(fpu::bc1t(c));
    fpu::c_eq_s(c, 6, 5); CHECK(fpu::bc1t(c));                // denormal flushes to zero before comparing
    fpu::c_f_s(c); CHECK(fpu::bc1f(c));                       // C.F always clears
    // the condition bit is bit 23 and nothing else moves
    fpu::c_lt_s(c, 1, 2);
    CHECK(c.fcr31 == fpu::kFcr31Condition);
    fpu::c_f_s(c);
    CHECK(c.fcr31 == 0u);
}

TEST_CASE("max.s / min.s") {
    // (hand: manual)
    CHECK(fpu::max(kOne, kTwo) == kTwo);
    CHECK(fpu::min(kOne, kTwo) == kOne);
    CHECK(fpu::max(kOne | fpu::kSign, kTwo | fpu::kSign) == (kOne | fpu::kSign));
    CHECK(fpu::min(kOne | fpu::kSign, kTwo | fpu::kSign) == (kTwo | fpu::kSign));
    // (upstream behaviour, hardware-unverified) ties return the first operand's pattern.
    CHECK(fpu::max(kNegZero, 0u) == kNegZero);
    CHECK(fpu::min(0u, kNegZero) == 0u);
    EEContext c;
    fpu::set_fpr(c, 1, kOne);
    fpu::set_fpr(c, 2, kTwo);
    fpu::max_s(c, 3, 1, 2);
    fpu::min_s(c, 4, 1, 2);
    CHECK(fpu::fpr(c, 3) == kTwo);
    CHECK(fpu::fpr(c, 4) == kOne);
}

TEST_CASE("cvt.w.s: truncation and saturation at +/-2^31") {
    // (hand: manual)
    CHECK(fpu::cvt_w_s(f2u(2.5f)) == 2u);
    CHECK(fpu::cvt_w_s(f2u(-2.5f)) == static_cast<u32>(-2));
    CHECK(fpu::cvt_w_s(f2u(0.999f)) == 0u);
    CHECK(fpu::cvt_w_s(f2u(-0.999f)) == 0u);
    CHECK(fpu::cvt_w_s(0u) == 0u);
    CHECK(fpu::cvt_w_s(kDenormal) == 0u);
    CHECK(fpu::cvt_w_s(0x4E800000u) == 0x40000000u);           // 2^30
    CHECK(fpu::cvt_w_s(0x4EFFFFFFu) == 0x7FFFFF80u);           // largest float below 2^31
    CHECK(fpu::cvt_w_s(0x4F000000u) == 0x7FFFFFFFu);           // 2^31 saturates
    CHECK(fpu::cvt_w_s(0x501502F9u) == 0x7FFFFFFFu);           // 1e10 saturates
    CHECK(fpu::cvt_w_s(kEEMax) == 0x7FFFFFFFu);                // the EE maximum saturates
    CHECK(fpu::cvt_w_s(0xCF000000u) == 0x80000000u);           // -2^31 is exactly representable
    CHECK(fpu::cvt_w_s(0xCF000001u) == 0x80000000u);           // below -2^31 saturates
    CHECK(fpu::cvt_w_s(0xD01502F9u) == 0x80000000u);           // -1e10 saturates
    CHECK(fpu::cvt_w_s(kEEMax | fpu::kSign) == 0x80000000u);
    EEContext c;
    fpu::set_fpr(c, 1, f2u(-7.75f));
    fpu::cvt_w_s(c, 2, 1);
    CHECK(fpu::fpr(c, 2) == static_cast<u32>(-7));
}

TEST_CASE("cvt.s.w: exact for small values, truncates large magnitudes") {
    // (hand: manual)
    CHECK(fpu::cvt_s_w(1u) == kOne);
    CHECK(fpu::cvt_s_w(static_cast<u32>(-1)) == (kOne | fpu::kSign));
    CHECK(fpu::cvt_s_w(0u) == 0u);
    CHECK(fpu::cvt_s_w(0x80000000u) == 0xCF000000u);           // INT32_MIN = -2^31 exactly
    CHECK(fpu::cvt_s_w(0x7FFFFFFFu) == 0x4EFFFFFFu);           // 2^31-1 truncates down (RN would give 0x4F000000)
    CHECK(fpu::cvt_s_w(0x01000001u) == 0x4B800000u);           // 2^24+1 truncates to 2^24
    EEContext c;
    fpu::set_fpr(c, 1, 16u);
    fpu::cvt_s_w(c, 2, 1);
    CHECK(fpu::fpr(c, 2) == f2u(16.0f));
}

TEST_CASE("ACC forms: adda/suba/mula write ACC, madd/msub read it, madda/msuba accumulate") {
    EEContext c;
    fpu::set_fpr(c, 1, kOne);
    fpu::set_fpr(c, 2, kTwo);
    // (hand: manual)
    fpu::adda_s(c, 1, 2);                       // ACC = 3
    CHECK(fpu::acc(c) == kThree);
    fpu::madd_s(c, 3, 2, 2);                    // f3 = ACC + 2*2 = 7
    CHECK(fpu::fpr(c, 3) == f2u(7.0f));
    CHECK(fpu::acc(c) == kThree);               // MADD leaves ACC alone
    fpu::msub_s(c, 4, 2, 2);                    // f4 = ACC - 4 = -1
    CHECK(fpu::fpr(c, 4) == (kOne | fpu::kSign));
    fpu::madda_s(c, 2, 2);                      // ACC = 3 + 4 = 7
    CHECK(fpu::acc(c) == f2u(7.0f));
    fpu::msuba_s(c, 2, 2);                      // ACC = 7 - 4 = 3
    CHECK(fpu::acc(c) == kThree);
    fpu::mula_s(c, 2, 2);                       // ACC = 4
    CHECK(fpu::acc(c) == kFour);
    fpu::suba_s(c, 1, 2);                       // ACC = 1 - 2 = -1
    CHECK(fpu::acc(c) == (kOne | fpu::kSign));
    // (hand: manual) the product is rounded (truncated) before the accumulate: ACC = 1, fs*ft = (1+2^-23)^2.
    fpu::set_acc(c, kOne);
    fpu::set_fpr(c, 5, 0x3F800001u);
    fpu::madd_s(c, 6, 5, 5);
    CHECK(fpu::fpr(c, 6) == 0x40000001u);       // 1 + (1 + 2^-22) = 2 + 2^-22 -> truncated to 2 + 2^-22 (0x40000001)
}

TEST_CASE("add_s/sub_s/mul_s/div_s/sqrt_s/rsqrt_s register forms and the divide flags") {
    EEContext c;
    fpu::set_fpr(c, 1, kOne);
    fpu::set_fpr(c, 2, kTwo);
    fpu::set_fpr(c, 3, kFour);
    fpu::set_fpr(c, 4, 0u);
    // (hand: manual)
    fpu::add_s(c, 10, 1, 2); CHECK(fpu::fpr(c, 10) == kThree);
    fpu::sub_s(c, 10, 1, 2); CHECK(fpu::fpr(c, 10) == (kOne | fpu::kSign));
    fpu::mul_s(c, 10, 2, 3); CHECK(fpu::fpr(c, 10) == f2u(8.0f));
    fpu::div_s(c, 10, 1, 3); CHECK(fpu::fpr(c, 10) == f2u(0.25f));
    CHECK(c.fcr31 == 0u);
    fpu::sqrt_s(c, 10, 3);   CHECK(fpu::fpr(c, 10) == kTwo);       // SQRT.S fd, ft
    fpu::rsqrt_s(c, 10, 1, 3); CHECK(fpu::fpr(c, 10) == kHalf);    // 1 / sqrt(4)
    CHECK(c.fcr31 == 0u);
    // (PCSX2 2.8.2 observed: fpu_2216, fpu_2280) x/0 and rsqrt with ft = 0 set D (bit 16) + SD (bit 5).
    fpu::div_s(c, 10, 1, 4);
    CHECK(fpu::fpr(c, 10) == kEEMax);
    CHECK(c.fcr31 == fpu::kFcr31DivideByZero);
    c.fcr31 = 0;
    fpu::rsqrt_s(c, 10, 2, 4);
    CHECK(fpu::fpr(c, 10) == kEEMax);
    CHECK(c.fcr31 == fpu::kFcr31DivideByZero);
    // (PCSX2 2.8.2 observed: fpu_2219, fpu_2259, fpu_2283) 0/0, sqrt(-x) and rsqrt(x, -y) set I (bit 17) + SI (bit 6).
    c.fcr31 = 0;
    fpu::div_s(c, 10, 4, 4);
    CHECK(c.fcr31 == fpu::kFcr31Invalid);
    fpu::set_fpr(c, 5, kFour | fpu::kSign);
    c.fcr31 = 0;
    fpu::sqrt_s(c, 10, 5);
    CHECK(fpu::fpr(c, 10) == kTwo);
    CHECK(c.fcr31 == fpu::kFcr31Invalid);
    c.fcr31 = 0;
    fpu::rsqrt_s(c, 10, 1, 5);
    CHECK(fpu::fpr(c, 10) == kHalf);
    CHECK(c.fcr31 == fpu::kFcr31Invalid);
    // (PCSX2 2.8.2 observed: fpu_2781) bits are only ever set: the condition bit and preset flags survive.
    c.fcr31 = fpu::kFcr31Condition | fpu::kFcr31Invalid;
    fpu::div_s(c, 10, 1, 4);
    CHECK(c.fcr31 == (fpu::kFcr31Condition | fpu::kFcr31Invalid | fpu::kFcr31DivideByZero));
    CHECK(fpu::bc1t(c));
}

TEST_CASE("abs.s / neg.s / mov.s operate on the bit pattern without flushing") {
    EEContext c;
    fpu::set_fpr(c, 1, kOne | fpu::kSign);
    fpu::set_fpr(c, 2, kNegZero);
    fpu::set_fpr(c, 3, 0u);
    fpu::set_fpr(c, 4, kNegDenormal);
    // (hand: manual)
    fpu::abs_s(c, 10, 1); CHECK(fpu::fpr(c, 10) == kOne);
    fpu::abs_s(c, 10, 2); CHECK(fpu::fpr(c, 10) == 0u);
    fpu::neg_s(c, 10, 3); CHECK(fpu::fpr(c, 10) == kNegZero);
    fpu::neg_s(c, 10, 1); CHECK(fpu::fpr(c, 10) == kOne);
    fpu::mov_s(c, 10, 4); CHECK(fpu::fpr(c, 10) == kNegDenormal); // MOV copies the pattern, denormal included
    fpu::abs_s(c, 10, 4); CHECK(fpu::fpr(c, 10) == kDenormal);    // ABS only clears the sign
}

TEST_CASE("mfc1 / mtc1 / cfc1 / ctc1") {
    EEContext c;
    // (hand: manual) MTC1 stores the low word; MFC1 sign-extends it into the 64-bit GPR.
    fpu::mtc1(c, 5, 0x80000000u);
    CHECK(fpu::fpr(c, 5) == 0x80000000u);
    CHECK(fpu::mfc1(c, 5) == 0xFFFFFFFF80000000ull);
    fpu::mtc1(c, 5, 0x7FFFFFFFu);
    CHECK(fpu::mfc1(c, 5) == 0x000000007FFFFFFFull);
    fpu::mtc1(c, 5, kDenormal);
    CHECK(fpu::fpr(c, 5) == kDenormal);                 // not flushed on transfer
    // (upstream behaviour, hardware-unverified) FCR0 reads 0x2E30; other numbers read 0.
    CHECK(fpu::cfc1(c, 0) == fpu::kFcr0Value);
    CHECK(fpu::cfc1(c, 5) == 0u);
    // (hand: manual) CTC1 $31 then CFC1 $31 round-trips; the C bit drives BC1T/BC1F.
    fpu::ctc1(c, 31, fpu::kFcr31Condition | 0x1u);
    CHECK(fpu::cfc1(c, 31) == (fpu::kFcr31Condition | 0x1u));
    CHECK(fpu::bc1t(c));
    CHECK_FALSE(fpu::bc1f(c));
    fpu::ctc1(c, 31, 0u);
    CHECK(fpu::bc1f(c));
    fpu::ctc1(c, 0, 0xFFFFFFFFu);                        // FCR0 is read-only
    CHECK(fpu::cfc1(c, 0) == fpu::kFcr0Value);
}
