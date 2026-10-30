// rt adapter MMI / FPU / VU0 plumbing (runtime/rt/rt_mmi.cpp, rt_fpu.cpp, rt_vu0.cpp). The lane,
// float and vector rules are tested in tests/ee/; these cases check operand order, whole-quadword
// writes, the second HI/LO pipe and the GPR <-> coprocessor moves through the rt entry points.
#include "fake_hooks.h"

#include "p3fes_recomp_rt.h"

#include <bit>

using namespace p3fes;
using rt_test::HooksScope;
using rt_test::TestHooks;

namespace {
u128 q(u32 w0, u32 w1, u32 w2, u32 w3) {
    u128 r;
    r.u32[0] = w0; r.u32[1] = w1; r.u32[2] = w2; r.u32[3] = w3;
    return r;
}
bool eq(const u128& a, const u128& b) { return a.u64[0] == b.u64[0] && a.u64[1] == b.u64[1]; }
constexpr u32 f(float x) { return std::bit_cast<u32>(x); }
} // namespace

TEST_CASE("rt mmi: lane ops write the whole quadword in (rd, rs, rt) order") {
    EEContext c;
    c.gpr[4] = q(1, 2, 3, 0xFFFFFFFFu);
    c.gpr[5] = q(10, 20, 30, 1);
    rt::paddw(c, 2, 4, 5);
    CHECK(eq(c.gpr[2], q(11, 22, 33, 0)));
    rt::psubw(c, 2, 5, 4);
    CHECK(eq(c.gpr[2], q(9, 18, 27, 2)));
    rt::pcpyld(c, 3, 4, 5);  // {rs.lo, rt.lo}: high doubleword = rs.lo
    CHECK(c.gpr[3].u64[0] == c.gpr[5].u64[0]);
    CHECK(c.gpr[3].u64[1] == c.gpr[4].u64[0]);
    rt::pcpyud(c, 3, 4, 5);  // {rt.hi, rs.hi}
    CHECK(c.gpr[3].u64[0] == c.gpr[4].u64[1]);
    CHECK(c.gpr[3].u64[1] == c.gpr[5].u64[1]);
    rt::pextlw(c, 3, 4, 5);
    CHECK(eq(c.gpr[3], q(10, 1, 20, 2)));
    rt::pextuw(c, 3, 4, 5);
    CHECK(eq(c.gpr[3], q(30, 3, 1, 0xFFFFFFFFu)));
    rt::ppacw(c, 3, 4, 5);
    CHECK(eq(c.gpr[3], q(10, 30, 1, 3)));
    rt::pand(c, 3, 4, 5);
    rt::por(c, 3, 4, 5);
    rt::pxor(c, 3, 4, 4);
    CHECK(eq(c.gpr[3], q(0, 0, 0, 0)));
    rt::pnor(c, 3, 0, 0);
    CHECK(eq(c.gpr[3], q(0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu)));
    c.gpr[6] = q(0x00030001u, 0x00070005u, 0, 0);
    rt::pcpyh(c, 3, 6);
    CHECK(eq(c.gpr[3], q(0x00010001u, 0x00010001u, 0, 0)));
    rt::pexew(c, 3, 4);
    CHECK(eq(c.gpr[3], q(3, 2, 1, 0xFFFFFFFFu)));
    rt::prot3w(c, 3, 4);
    CHECK(eq(c.gpr[3], q(2, 3, 1, 0xFFFFFFFFu)));
    c.gpr[7] = q(0x80008000u, 0x00010001u, 0, 0);
    rt::psrah(c, 3, 7, 15);
    CHECK(eq(c.gpr[3], q(0xFFFFFFFFu, 0, 0, 0)));
    rt::psrlh(c, 3, 7, 15);
    CHECK(eq(c.gpr[3], q(0x00010001u, 0, 0, 0)));
    rt::psllh(c, 3, 7, 1);
    CHECK(eq(c.gpr[3], q(0, 0x00020002u, 0, 0)));
    rt::psraw(c, 3, 7, 31);
    CHECK(eq(c.gpr[3], q(0xFFFFFFFFu, 0, 0, 0)));
    // The remaining lane ops of the census reach their mmi:: counterparts.
    rt::paddh(c, 3, 4, 5); rt::paddub(c, 3, 4, 5); rt::padduw(c, 3, 4, 5); rt::pcgth(c, 3, 4, 5);
    rt::pextlb(c, 3, 4, 5); rt::pextlh(c, 3, 4, 5); rt::pextub(c, 3, 4, 5); rt::pmaxh(c, 3, 4, 5);
    rt::pminh(c, 3, 4, 5); rt::ppacb(c, 3, 4, 5); rt::ppach(c, 3, 4, 5); rt::psubb(c, 3, 4, 5);
    rt::padduw(c, 3, 4, 5);
    CHECK(eq(c.gpr[3], q(11, 22, 33, 0xFFFFFFFFu)));  // unsigned saturation in lane 3
}

TEST_CASE("rt mmi: QFSRV with SA from MTSAB, PHMADH/PMFHL and the second pipe") {
    EEContext c;
    c.gpr[4] = q(0x03020100u, 0x07060504u, 0x0B0A0908u, 0x0F0E0D0Cu);
    c.gpr[5] = q(0x13121110u, 0x17161514u, 0x1B1A1918u, 0x1F1E1D1Cu);
    c.gpr[6].u64[0] = 0;
    rt::mtsab(c, 6, 4);  // shift 4 bytes
    rt::mfsa(c, 2);
    CHECK(c.gpr[2].u64[0] == 32u);  // SA in bits (hilo.h)
    rt::qfsrv(c, 3, 4, 5);  // ({rs, rt} >> 32): rt.w1..w3, rs.w0
    CHECK(eq(c.gpr[3], q(0x17161514u, 0x1B1A1918u, 0x1F1E1D1Cu, 0x03020100u)));
    rt::mtsah(c, 6, 1);
    rt::mfsa(c, 2);
    CHECK(c.gpr[2].u64[0] == 16u);
    c.gpr[7].u64[0] = 24u;
    rt::mtsa(c, 7);
    rt::mfsa(c, 2);
    CHECK(c.gpr[2].u64[0] == 24u);

    // PHMADH with rd = 0 still writes HI/LO.
    c.gpr[8] = q(0x00020001u, 0, 0, 0);  // halfwords 1, 2
    c.gpr[9] = q(0x00040003u, 0, 0, 0);  // halfwords 3, 4
    rt::phmadh(c, 0, 8, 9);
    CHECK(c.lo.u32[0] == 1u * 3u + 2u * 4u);
    rt::phmadh(c, 3, 8, 9);
    CHECK(c.gpr[3].u32[0] == 11u);
    rt::pmfhl(c, 2, 0);  // .lw: {HI.w2, LO.w2, HI.w0, LO.w0}
    CHECK(c.gpr[2].u32[0] == 11u);

    // Pipe 1.
    c.gpr[10].u64[0] = 6u;
    c.gpr[11].u64[0] = 7u;
    rt::mult1(c, 12, 10, 11);
    CHECK(c.gpr[12].u64[0] == 42u);
    CHECK(c.lo.u64[1] == 42u);
    rt::maddu1(c, 12, 10, 11);
    CHECK(c.gpr[12].u64[0] == 84u);
    rt::multu1(c, 12, 10, 11);
    CHECK(c.gpr[12].u64[0] == 42u);
    rt::div1(c, 11, 10);
    rt::mflo1(c, 2);
    rt::mfhi1(c, 3);
    CHECK(c.gpr[2].u64[0] == 1u);
    CHECK(c.gpr[3].u64[0] == 1u);
    rt::mthi1(c, 10);
    rt::mtlo1(c, 11);
    CHECK(c.hi.u64[1] == 6u);
    CHECK(c.lo.u64[1] == 7u);
    // MADD/MADDU (pipe 0) accumulate and write rd <- LO.
    rt::mtlo(c, 0);
    rt::mthi(c, 0);
    rt::madd(c, 2, 10, 11);
    rt::maddu(c, 2, 10, 11);
    CHECK(c.gpr[2].u64[0] == 84u);
}

TEST_CASE("rt fpu: operations go through fpu.h on bit patterns; GPR moves sign-extend") {
    EEContext c;
    c.gpr[4].u64[0] = f(1.5f);
    c.gpr[5].u64[0] = f(-2.0f);
    rt::mtc1(c, 4, 1);
    rt::mtc1(c, 5, 2);
    rt::add_s(c, 3, 1, 2);
    CHECK(c.fpr[3] == f(-0.5f));
    rt::mfc1(c, 6, 3);
    CHECK(c.gpr[6].u64[0] == 0xFFFFFFFFBF000000ull);  // pattern sign-extended
    rt::sub_s(c, 3, 1, 2);
    CHECK(c.fpr[3] == f(3.5f));
    rt::mul_s(c, 3, 1, 2);
    CHECK(c.fpr[3] == f(-3.0f));
    rt::div_s(c, 3, 2, 1);
    CHECK(c.fpr[3] == 0xBFAAAAABu);  // -1.333.. rounded to nearest (DIV.S only: fpu.h div_nearest, PCSX2 oracle)
    c.fpr[0] = 0;
    rt::div_s(c, 3, 1, 0);           // x / 0: +max with D + SD (fpu.h, PCSX2 2.8.2 observed: fpu_2216)
    CHECK(c.fpr[3] == 0x7FFFFFFFu);
    CHECK((c.fcr31 & 0x30060u) == 0x10020u);
    rt::abs_s(c, 3, 2);
    CHECK(c.fpr[3] == f(2.0f));
    rt::neg_s(c, 3, 1);
    CHECK(c.fpr[3] == f(-1.5f));
    rt::mov_s(c, 3, 1);
    CHECK(c.fpr[3] == f(1.5f));
    c.fpr[7] = f(16.0f);
    rt::sqrt_s(c, 3, 7);  // (fd, ft)
    CHECK(c.fpr[3] == f(4.0f));
    rt::cvt_w_s(c, 3, 2);
    CHECK(c.fpr[3] == 0xFFFFFFFEu);
    rt::cvt_s_w(c, 8, 3);
    CHECK(c.fpr[8] == f(-2.0f));
    rt::c_lt_s(c, 2, 1);
    CHECK(rt::cop1_cond(c));
    rt::c_le_s(c, 1, 2);
    CHECK_FALSE(rt::cop1_cond(c));
    rt::c_eq_s(c, 1, 1);
    CHECK(rt::cop1_cond(c));
    // ACC forms.
    rt::mula_s(c, 1, 1);        // ACC = 2.25
    rt::madda_s(c, 1, 1);       // ACC = 4.5
    rt::madd_s(c, 3, 1, 1);     // 4.5 + 2.25
    CHECK(c.fpr[3] == f(6.75f));
    rt::msub_s(c, 3, 1, 1);     // 4.5 - 2.25
    CHECK(c.fpr[3] == f(2.25f));
    rt::msuba_s(c, 1, 1);       // ACC = 2.25
    rt::adda_s(c, 1, 2);        // ACC = -0.5
    CHECK(c.acc == f(-0.5f));
    rt::suba_s(c, 1, 2);        // ACC = 3.5
    CHECK(c.acc == f(3.5f));
    c.gpr[9].u64[0] = 0x00800000u;  // FCR31.C
    rt::ctc1(c, 9, 31);
    CHECK(rt::cop1_cond(c));
}

TEST_CASE("rt vu0: transfers, dest masks, broadcast/Q/I forms and the Q pipe") {
    EEContext c;
    c.gpr[4] = q(f(1.0f), f(2.0f), f(3.0f), f(4.0f));
    rt::qmtc2(c, 4, 1, false);
    rt::qmtc2(c, 4, 0, true);  // vf00 is read-only
    CHECK(c.vu0.vf[0][3] == f(1.0f));
    CHECK(c.vu0.vf[0][0] == 0u);
    rt::qmfc2(c, 5, 1, false);
    CHECK(eq(c.gpr[5], c.gpr[4]));
    rt::vadd(c, 0x8u /* x */, 2, 1, 1);
    CHECK(c.vu0.vf[2][0] == f(2.0f));
    CHECK(c.vu0.vf[2][1] == 0u);  // masked lanes untouched
    rt::vmul_bc(c, 0xFu, 2, 1, 1, 3);  // * vf1.w
    CHECK(c.vu0.vf[2][2] == f(12.0f));
    rt::vsub(c, 0xFu, 3, 2, 1);
    CHECK(c.vu0.vf[3][0] == f(3.0f));
    rt::vsub_bc(c, 0xFu, 3, 2, 1, 0);
    rt::vadd_bc(c, 0xFu, 3, 1, 1, 0);
    CHECK(c.vu0.vf[3][3] == f(5.0f));
    rt::vmax(c, 0xFu, 3, 1, 2);
    rt::vmini(c, 0xFu, 3, 1, 2);
    CHECK(c.vu0.vf[3][0] == f(1.0f));
    rt::vmove(c, 0xFu, 6, 1);
    rt::vabs(c, 0xFu, 7, 6);
    CHECK(c.vu0.vf[7][1] == f(2.0f));
    // ACC forms.
    rt::vmula(c, 0xFu, 1, 1);          // ACC = (1,4,9,16)
    rt::vmadda(c, 0xFu, 1, 1);         // ACC = (2,8,18,32)
    rt::vmadd(c, 0xFu, 8, 1, 1);       // ACC + vf1*vf1
    CHECK(c.vu0.vf[8][1] == f(12.0f));
    rt::vmsub(c, 0xFu, 8, 1, 1);
    CHECK(c.vu0.vf[8][1] == f(4.0f));
    rt::vmula_bc(c, 0xFu, 1, 1, 0);
    rt::vmadda_bc(c, 0xFu, 1, 1, 0);
    rt::vmsuba(c, 0xFu, 1, 1);
    rt::vmsuba_bc(c, 0xFu, 1, 1, 0);
    rt::vadda(c, 0xFu, 1, 1);
    rt::vadda_bc(c, 0xFu, 1, 1, 1);    // ACC = vf1 + vf1.y
    CHECK(c.vu0.acc[0] == f(3.0f));
    rt::vmadd_bc(c, 0xFu, 9, 1, 1, 0);  // ACC + vf1 * vf1.x
    CHECK(c.vu0.vf[9][0] == f(4.0f));
    rt::vmsub_bc(c, 0xFu, 9, 1, 1, 0);
    CHECK(c.vu0.vf[9][0] == f(2.0f));
    // Outer product: ACC.xyz = fs.yzx * ft.zxy, then fd = ACC - fs.zxy*ft.yzx.
    rt::vopmula(c, 0xEu, 1, 2);
    rt::vopmsub(c, 0xEu, 10, 2, 1);
    // Q pipe and I register.
    c.vu0.vf[11][0] = f(16.0f);
    rt::vsqrt(c, 11, 0);
    rt::vwaitq(c);
    rt::cfc2(c, 2, 22, false);
    CHECK(c.gpr[2].u64[0] == f(4.0f));
    rt::vmulq(c, 0xFu, 12, 1);
    CHECK(c.vu0.vf[12][3] == f(16.0f));
    rt::vrsqrt(c, 1, 0, 11, 0);  // 1 / sqrt(16)
    CHECK(c.vu0.q == f(0.25f));
    c.gpr[3].u64[0] = f(-0.5f);
    rt::ctc2(c, 3, 21, false);   // I
    rt::cfc2(c, 4, 21, false);
    CHECK(c.gpr[4].u64[0] == 0xFFFFFFFFBF000000ull);  // CFC2 sign-extends
    rt::vaddi(c, 0xFu, 13, 1);
    CHECK(c.vu0.vf[13][0] == f(0.5f));
    rt::vmuli(c, 0xFu, 13, 1);
    CHECK(c.vu0.vf[13][1] == f(-1.0f));
    // Fixed point.
    c.vu0.vf[14][0] = f(-7.9f);
    rt::vftoi0(c, 0x8u, 15, 14);
    CHECK(c.vu0.vf[15][0] == 0xFFFFFFF9u);
    rt::vitof0(c, 0x8u, 16, 15);
    CHECK(c.vu0.vf[16][0] == f(-7.0f));
    const VU0State before = c.vu0;
    rt::vnop(c);
    CHECK(c.vu0.q == before.q);
}
