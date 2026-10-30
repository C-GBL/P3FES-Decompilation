// Slice libc: the C maths library (fdlibm-style __ieee754_* / __kernel_* functions and their <math.h> wrappers).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions and the C standard only
// (ADR-0010: no GPL or newlib source was opened). Pair tests: tests/game/test_libc.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libc.h"

namespace p3fes::recomp_gen {
void fn___ieee754_acos_00528ae0(p3fes::EEContext&);
void fn___ieee754_acosf_0052abd8(p3fes::EEContext&);
void fn___ieee754_asinf_0052afe8(p3fes::EEContext&);
void fn___ieee754_log10_00529578(p3fes::EEContext&);
void fn___ieee754_log_005290a0(p3fes::EEContext&);
void fn___ieee754_powf_0052b800(p3fes::EEContext&);
void fn___ieee754_rem_pio2f_0052c000(p3fes::EEContext&);
void fn___ieee754_sqrt_0052a8c8(p3fes::EEContext&);
void fn___ieee754_sqrtf_0052c398(p3fes::EEContext&);
void fn___kernel_cos_0052c478(p3fes::EEContext&);
void fn___kernel_cosf_0052d2d8(p3fes::EEContext&);
void fn___kernel_rem_pio2_0052c6d0(p3fes::EEContext&);
void fn___kernel_rem_pio2f_0052d428(p3fes::EEContext&);
void fn___kernel_sin_0052d108(p3fes::EEContext&);
void fn___kernel_sinf_0052dc48(p3fes::EEContext&);
void fn___kernel_tanf_0052dd40(p3fes::EEContext&);
void fn_acos_0052e9a0(p3fes::EEContext&);
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_asinf_0052ea00(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
void fn_atanf_0052e408(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_fabsf_0052e788(p3fes::EEContext&);
void fn_floor_0052e148(p3fes::EEContext&);
void fn_floorf_0052e7a0(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_log10_0052e9b8(p3fes::EEContext&);
void fn_logf_0052ea30(p3fes::EEContext&);
void fn_powf_0052ea48(p3fes::EEContext&);
void fn_scalbn_005237b0(p3fes::EEContext&);
void fn_scalbnf_005239a8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sqrtf_0052ea60(p3fes::EEContext&);
void fn_tanf_0052e930(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace libc;  // the named offsets of p3fes/game/libc.h
namespace gen = ::p3fes::recomp_gen;

// 0x00528AE0 __ieee754_acos -- 1468 bytes; frame 0x40: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// __ieee754_acos(x $a0) -> $v0: acos(x) in double precision on the soft-float helpers (dpadd / dpsub / dpmul / dpdiv,
// __ieee754_sqrt): |x| = 1 gives 0 or pi, |x| > 1 gives NaN ((x-x)/(x-x)), |x| < 0.5 uses pi/2 - (x + x*r(x^2)) with a
// rational approximation r, the outer ranges the half-angle form 2*asin(sqrt((1-|x|)/2)) with the split-sqrt
// correction.
void __ieee754_acos(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00528ae0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t7 = 0x7FFF0000;
    sd(s1, sp, 0x8);
    t7 = t7 | 0xFFFF;
    t4 = dsra32(a0, 0);
    sd(s0, sp, 0x0);
    t6 = 0x3FEF0000;
    sd(s2, sp, 0x10);
    t5 = t4 & t7;
    sd(s3, sp, 0x18);
    t6 = t6 | 0xFFFF;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x30);
    t6 = slt(t6, t5);
    s1 = a0;
    if (t6 == 0) {
        // 0x00528ba0
        charge(ctx, 5);
        t7 = 0x3FDF0000;
        t7 = t7 | 0xFFFF;
        t7 = slt(t7, t5);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x3C600000;
        if (cc) {
            // 0x00528d38
            charge(ctx, 2);
            s2 = 1023;
            if (i64(t4) >= 0) {
                // 0x00528ed4
                charge(ctx, 114);
                a1 = a0;
                s2 = dsll32(s2, 20);
                a0 = s2;
                jal(ctx, 0x528EDCu, gen::fn_dpsub_005311c8);
                a1 = 511;
                a0 = v0;
                a1 = dsll32(a1, 21);
                jal(ctx, 0x528EECu, gen::fn_dpmul_00531230);
                s3 = v0;
                a0 = v0;
                jal(ctx, 0x528EF8u, gen::fn___ieee754_sqrt_0052a8c8);
                t7 = si(-1);
                s4 = v0;
                t7 = dsll32(t7, 0);
                s1 = v0 & t7;
                a0 = s1;
                a1 = s1;
                jal(ctx, 0x528F14u, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528F20u, gen::fn_dpsub_005311c8);
                s0 = v0;
                a0 = s4;
                a1 = s1;
                jal(ctx, 0x528F30u, gen::fn_dpadd_00531170);
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x528F3Cu, gen::fn_dpdiv_00531480);
                t7 = 0x7C0000;
                s0 = v0;
                ld(a1, t7, -2944);  // 0x7BF480
                a0 = s3;
                jal(ctx, 0x528F50u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528F60u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2936);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528F6Cu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528F7Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2928);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528F88u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528F98u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2920);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528FA4u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528FB4u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2912);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528FC0u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528FD0u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2904);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528FDCu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                s5 = v0;
                ld(a1, t7, -2896);  // 0x7BF4B0
                a0 = s3;
                jal(ctx, 0x528FF0u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x529000u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2888);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x52900Cu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x52901Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2880);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x529028u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x529038u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2872);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x529044u, gen::fn_dpmul_00531230);
                a0 = v0;
                a1 = s2;
                jal(ctx, 0x529050u, gen::fn_dpadd_00531170);
                a0 = s5;
                a1 = v0;
                jal(ctx, 0x52905Cu, gen::fn_dpdiv_00531480);
                a0 = v0;
                a1 = s4;
                jal(ctx, 0x529068u, gen::fn_dpmul_00531230);
                a0 = v0;
                a1 = s0;
                jal(ctx, 0x529074u, gen::fn_dpadd_00531170);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x529080u, gen::fn_dpadd_00531170);
                a0 = v0;
                a1 = v0;
                jal(ctx, 0x52908Cu, gen::fn_dpadd_00531170);
                ld(s0, sp, 0x0);
                backedge(ctx);
            } else {
                // 0x00528d40
                charge(ctx, 101);
                s0 = 1023;
                s0 = dsll32(s0, 20);
                a1 = s0;
                jal(ctx, 0x528D48u, gen::fn_dpadd_00531170);
                a1 = 511;
                a0 = v0;
                a1 = dsll32(a1, 21);
                jal(ctx, 0x528D58u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                s3 = v0;
                ld(a1, t7, -2944);  // 0x7BF480
                a0 = v0;
                jal(ctx, 0x528D6Cu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528D7Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2936);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528D88u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528D98u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2928);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528DA4u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528DB4u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2920);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528DC0u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528DD0u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2912);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528DDCu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528DECu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2904);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528DF8u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                s5 = v0;
                ld(a1, t7, -2896);  // 0x7BF4B0
                a0 = s3;
                jal(ctx, 0x528E0Cu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528E1Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2888);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528E28u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528E38u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2880);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528E44u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528E54u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2872);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528E60u, gen::fn_dpmul_00531230);
                a1 = s0;
                a0 = v0;
                jal(ctx, 0x528E6Cu, gen::fn_dpadd_00531170);
                s2 = v0;
                a0 = s3;
                jal(ctx, 0x528E78u, gen::fn___ieee754_sqrt_0052a8c8);
                s4 = v0;
                a0 = s5;
                a1 = s2;
                jal(ctx, 0x528E88u, gen::fn_dpdiv_00531480);
                a0 = v0;
                a1 = s4;
                jal(ctx, 0x528E94u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528EA4u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2864);
                call(ctx, gen::fn_dpsub_005311c8);
                a0 = s4;
                a1 = v0;
                jal(ctx, 0x528EB0u, gen::fn_dpadd_00531170);
                a0 = v0;
                a1 = v0;
                jal(ctx, 0x528EBCu, gen::fn_dpadd_00531170);
                t7 = 0x7C0000;
                a1 = v0;
                ld(a0, t7, -2960);  // 0x7BF470
                backedge(ctx);
            L_00528d28:
                charge(ctx, 4);
                jal(ctx, 0x528D28u, gen::fn_dpsub_005311c8);
                ld(s0, sp, 0x0);
                backedge(ctx);
            }
        } else {
            // 0x00528bb4
            charge(ctx, 3);
            t7 = slt(t7, t5);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0x7C0000;
            if (cc) {
                // 0x00528bc8
                charge(ctx, 88);
                a1 = a0;
                jal(ctx, 0x528BC8u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                s3 = v0;
                ld(a1, t7, -2944);  // 0x7BF480
                a0 = v0;
                jal(ctx, 0x528BDCu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528BECu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2936);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528BF8u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528C08u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2928);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528C14u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528C24u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2920);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528C30u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528C40u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2912);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528C4Cu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528C5Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2904);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528C68u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                s5 = v0;
                ld(a1, t7, -2896);  // 0x7BF4B0
                a0 = s3;
                jal(ctx, 0x528C7Cu, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528C8Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2888);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528C98u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528CA8u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2880);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528CB4u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a0 = v0;
                link(ctx, 0x528CC4u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -2872);
                call(ctx, gen::fn_dpadd_00531170);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x528CD0u, gen::fn_dpmul_00531230);
                a1 = 1023;
                a0 = v0;
                a1 = dsll32(a1, 20);
                jal(ctx, 0x528CE0u, gen::fn_dpadd_00531170);
                a0 = s5;
                a1 = v0;
                jal(ctx, 0x528CECu, gen::fn_dpdiv_00531480);
                a0 = s1;
                a1 = v0;
                jal(ctx, 0x528CF8u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                a1 = v0;
                link(ctx, 0x528D08u);  // $ra first: the delay slot below depends on it
                ld(a0, t7, -2864);
                call(ctx, gen::fn_dpsub_005311c8);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x528D14u, gen::fn_dpsub_005311c8);
                t7 = 0x7C0000;
                a1 = v0;
                ld(a0, t7, -2952);  // 0x7BF478
                goto L_00528d28;
            }
            // 0x00528bc0
            charge(ctx, 2);
            ld(v0, t7, -2952);
            backedge(ctx);
        L_00528b50:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    } else {
        // 0x00528b24
        charge(ctx, 7);
        t7 = lui(0xC010);
        t6 = dsll32(a0, 0);
        t7 = addu(t5, t7);
        t6 = dsra32(t6, 0);
        t7 = t7 | t6;
        if (t7 == 0) {
            // 0x00528b40
            charge(ctx, 2);
            v0 = 0;
            if (i64(t4) <= 0) {
                // 0x00528b48
                charge(ctx, 2);
                t7 = 0x7C0000;
                ld(v0, t7, -2960);  // 0x7BF470
            }
            goto L_00528b50;
        }
        // 0x00528b74
        charge(ctx, 11);
        a1 = a0;
        jal(ctx, 0x528B74u, gen::fn_dpsub_005311c8);
        s0 = v0;
        a0 = s1;
        a1 = s1;
        jal(ctx, 0x528B84u, gen::fn_dpsub_005311c8);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x528B90u, gen::fn_dpdiv_00531480);
        ld(s0, sp, 0x0);
        backedge(ctx);
    }
    // 0x00528b54 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x005290A0 __ieee754_log -- 1240 bytes; frame 0x50: s2 sp+0x10, s5 sp+0x28, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s6 sp+0x30, s7 sp+0x38, ra sp+0x40
// __ieee754_log(x $a0) -> $v0: natural logarithm in double precision (soft-float): x < 0 -> NaN, x == 0 -> -huge/0,
// Inf/NaN -> x + x; x = 2^k * (1 + f) with f reduced around sqrt(2), log(1+f) = f - s*(f - R(s^2)) with s = f / (2 +
// f), plus k*ln2 split into high and low parts.
void __ieee754_log(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005290a0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t7 = 0xF0000;
    sd(s2, sp, 0x10);
    t7 = t7 | 0xFFFF;
    sd(s5, sp, 0x28);
    t6 = dsll32(a0, 0);
    s2 = dsra32(a0, 0);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    v0 = a0;
    sd(s3, sp, 0x18);
    t6 = dsra32(t6, 0);
    sd(s4, sp, 0x20);
    t7 = slt(t7, s2);
    sd(s6, sp, 0x30);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x40);
    s5 = 0;
    if (t7 == 0) {
        // 0x005290ec
        charge(ctx, 6);
        t7 = 0x7FFF0000;
        t7 = t7 | 0xFFFF;
        t7 = s2 & t7;
        t7 = t7 | t6;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (cc) {
            // 0x00529134
            charge(ctx, 2);
            if (i64(s2) >= 0) {
                a1 = 1077;
                // 0x00529158
                charge(ctx, 4);
                s5 = si(-54);
                a1 = dsll32(a1, 20);
                jal(ctx, 0x52915Cu, gen::fn_dpmul_00531230);
                s2 = dsra32(v0, 0);
                goto L_00529168;
            }
            // 0x0052913c
            charge(ctx, 7);
            a1 = a0;
            jal(ctx, 0x52913Cu, gen::fn_dpsub_005311c8);
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x529148u, gen::fn_dpdiv_00531480);
            ld(s0, sp, 0x0);
            backedge(ctx);
        } else {
            // 0x00529104
            charge(ctx, 1);
            ld(v0, t7, -2768);
        L_00529108:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
        // 0x0052910c (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(s7, sp, 0x38);
        ld(ra, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_00529168:
    charge(ctx, 5);
    t7 = 0x7FEF0000;
    t7 = t7 | 0xFFFF;
    t7 = slt(t7, s2);
    a0 = v0;
    if (t7 != 0) {
        // 0x0052917c
        charge(ctx, 1);
        a1 = v0;
        goto L_00529180;
    }
    // 0x00529190
    charge(ctx, 31);
    s0 = 0xF0000;
    t4 = sra(s2, 20);
    s0 = s0 | 0xFFFF;
    t6 = 0x90000;
    s2 = s2 & s0;
    t6 = t6 | 0x5F64;
    t6 = addu(s2, t6);
    t5 = 0x100000;
    s3 = t6 & t5;
    t7 = 0x3FF00000;
    t7 = s3 ^ t7;
    t6 = dsll32(v0, 0);
    t7 = s2 | t7;
    t4 = addu(s5, t4);
    t7 = dsll32(t7, 0);
    t6 = dsrl32(t6, 0);
    t7 = dsrl32(t7, 0);
    s5 = addiu(t4, -1023);
    t7 = dsll32(t7, 0);
    t5 = sra(s3, 20);
    v0 = t6 | t7;
    a1 = 1023;
    s5 = addu(s5, t5);
    a0 = v0;
    a1 = dsll32(a1, 20);
    jal(ctx, 0x5291F0u, gen::fn_dpsub_005311c8);
    t7 = addiu(s2, 2);
    t7 = t7 & s0;
    t7 = slti(t7, 3);
    s4 = v0;
    if (t7 == 0) {
        // 0x00529314
        charge(ctx, 75);
        a1 = 1;
        a0 = v0;
        a1 = dsll32(a1, 30);
        jal(ctx, 0x52931Cu, gen::fn_dpadd_00531170);
        a1 = v0;
        a0 = s4;
        jal(ctx, 0x529328u, gen::fn_dpdiv_00531480);
        s7 = v0;
        a0 = s5;
        jal(ctx, 0x529334u, gen::fn_litodp_00531720);
        a0 = s7;
        a1 = s7;
        s6 = v0;
        jal(ctx, 0x529344u, gen::fn_dpmul_00531230);
        t7 = lui(0xFFF9);
        s1 = v0;
        t7 = t7 | 0xEB86;
        a0 = v0;
        s3 = addu(s2, t7);
        a1 = v0;
        jal(ctx, 0x529360u, gen::fn_dpmul_00531230);
        t6 = 0x60000;
        t7 = 0x7C0000;
        t6 = t6 | 0xB851;
        ld(a1, t7, -2736);  // 0x7BF550
        t6 = subu(t6, s2);
        s0 = v0;
        s3 = s3 | t6;
        a0 = v0;
        jal(ctx, 0x529384u, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x529394u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -2728);
        call(ctx, gen::fn_dpadd_00531170);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x5293A0u, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x5293B0u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -2720);
        call(ctx, gen::fn_dpadd_00531170);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x5293BCu, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        s2 = v0;
        ld(a1, t7, -2712);  // 0x7BF568
        a0 = s0;
        jal(ctx, 0x5293D0u, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x5293E0u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -2704);
        call(ctx, gen::fn_dpadd_00531170);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x5293ECu, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x5293FCu);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -2696);
        call(ctx, gen::fn_dpadd_00531170);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x529408u, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x529418u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -2688);
        call(ctx, gen::fn_dpadd_00531170);
        a1 = v0;
        a0 = s1;
        jal(ctx, 0x529424u, gen::fn_dpmul_00531230);
        a1 = s2;
        a0 = v0;
        jal(ctx, 0x529430u, gen::fn_dpadd_00531170);
        s2 = v0;
        if (i64(s3) > 0) {
            // 0x00529440
            charge(ctx, 9);
            a1 = 511;
            a0 = s4;
            a1 = dsll32(a1, 21);
            jal(ctx, 0x529448u, gen::fn_dpmul_00531230);
            a0 = v0;
            a1 = s4;
            jal(ctx, 0x529454u, gen::fn_dpmul_00531230);
            s3 = v0;
            if (s5 == 0) {
                // 0x00529464
                charge(ctx, 10);
                a1 = s2;
                a0 = v0;
                jal(ctx, 0x529468u, gen::fn_dpadd_00531170);
                a0 = s7;
                a1 = v0;
                jal(ctx, 0x529474u, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x529480u, gen::fn_dpsub_005311c8);
                a1 = v0;
                goto L_0052948c;
            }
            // 0x00529494
            charge(ctx, 21);
            t7 = 0x7C0000;
            a0 = s6;
            link(ctx, 0x52949Cu);  // $ra first: the delay slot below depends on it
            ld(a1, t7, -2760);
            call(ctx, gen::fn_dpmul_00531230);
            a0 = s3;
            a1 = s2;
            s1 = v0;
            jal(ctx, 0x5294ACu, gen::fn_dpadd_00531170);
            a1 = v0;
            a0 = s7;
            jal(ctx, 0x5294B8u, gen::fn_dpmul_00531230);
            t7 = 0x7C0000;
            s0 = v0;
            ld(a1, t7, -2752);  // 0x7BF540
            a0 = s6;
            jal(ctx, 0x5294CCu, gen::fn_dpmul_00531230);
            a1 = v0;
            a0 = s0;
            jal(ctx, 0x5294D8u, gen::fn_dpadd_00531170);
            a1 = v0;
            a0 = s3;
            goto L_005294e8;
        }
        // 0x00529508
        charge(ctx, 2);
        t7 = 0x7C0000;
        if (s5 != 0) {
            // 0x00529530
            charge(ctx, 18);
            a0 = s6;
            link(ctx, 0x529534u);  // $ra first: the delay slot below depends on it
            ld(a1, t7, -2760);
            call(ctx, gen::fn_dpmul_00531230);
            a0 = s4;
            a1 = s2;
            s1 = v0;
            jal(ctx, 0x529544u, gen::fn_dpsub_005311c8);
            a1 = v0;
            a0 = s7;
            jal(ctx, 0x529550u, gen::fn_dpmul_00531230);
            t7 = 0x7C0000;
            s0 = v0;
            ld(a1, t7, -2752);  // 0x7BF540
            a0 = s6;
            jal(ctx, 0x529564u, gen::fn_dpmul_00531230);
            a1 = v0;
            a0 = s0;
            backedge(ctx);
        L_005294e8:
            charge(ctx, 8);
            jal(ctx, 0x5294E8u, gen::fn_dpsub_005311c8);
            a0 = v0;
            a1 = s4;
            jal(ctx, 0x5294F4u, gen::fn_dpsub_005311c8);
            a1 = v0;
            a0 = s1;
            backedge(ctx);
        } else {
            // 0x00529510
            charge(ctx, 8);
            a1 = v0;
            a0 = s4;
            jal(ctx, 0x529514u, gen::fn_dpsub_005311c8);
            a1 = v0;
            a0 = s7;
            jal(ctx, 0x529520u, gen::fn_dpmul_00531230);
            a1 = v0;
            backedge(ctx);
        L_0052948c:
            charge(ctx, 2);
            a0 = s4;
            backedge(ctx);
        }
    L_005292b0:
        charge(ctx, 4);
        jal(ctx, 0x5292B0u, gen::fn_dpsub_005311c8);
        ld(s0, sp, 0x0);
        backedge(ctx);
    } else {
        // 0x0052920c
        charge(ctx, 6);
        s0 = 0;
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x529214u, gen::fn_dpcmp_005316d0);
        a0 = s4;
        if (v0 != 0) {
            // 0x00529268
            charge(ctx, 16);
            a1 = s4;
            jal(ctx, 0x529268u, gen::fn_dpmul_00531230);
            t7 = 0x7C0000;
            s0 = v0;
            ld(a1, t7, -2744);  // 0x7BF548
            a0 = s4;
            jal(ctx, 0x52927Cu, gen::fn_dpmul_00531230);
            a0 = 511;
            a1 = v0;
            a0 = dsll32(a0, 21);
            jal(ctx, 0x52928Cu, gen::fn_dpsub_005311c8);
            a1 = v0;
            a0 = s0;
            jal(ctx, 0x529298u, gen::fn_dpmul_00531230);
            s2 = v0;
            if (s5 != 0) {
                // 0x005292c0
                charge(ctx, 21);
                a0 = s5;
                jal(ctx, 0x5292C0u, gen::fn_litodp_00531720);
                t7 = 0x7C0000;
                s6 = v0;
                ld(a1, t7, -2760);  // 0x7BF538
                a0 = v0;
                jal(ctx, 0x5292D4u, gen::fn_dpmul_00531230);
                t7 = 0x7C0000;
                s0 = v0;
                ld(a1, t7, -2752);  // 0x7BF540
                a0 = s6;
                jal(ctx, 0x5292E8u, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s2;
                jal(ctx, 0x5292F4u, gen::fn_dpsub_005311c8);
                a0 = v0;
                a1 = s4;
                jal(ctx, 0x529300u, gen::fn_dpsub_005311c8);
                a1 = v0;
                a0 = s0;
                backedge(ctx);
            } else {
                // 0x005292a8
                charge(ctx, 2);
                a0 = s4;
                a1 = v0;
            }
            goto L_005292b0;
        }
        // 0x00529224
        charge(ctx, 2);
        v0 = s0;
        if (s5 == 0) {
            backedge(ctx);
            goto L_00529108;
        }
        // 0x0052922c
        charge(ctx, 15);
        a0 = s5;
        jal(ctx, 0x52922Cu, gen::fn_litodp_00531720);
        t7 = 0x7C0000;
        s6 = v0;
        ld(a1, t7, -2760);  // 0x7BF538
        a0 = v0;
        jal(ctx, 0x529240u, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        s0 = v0;
        ld(a1, t7, -2752);  // 0x7BF540
        a0 = s6;
        jal(ctx, 0x529254u, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s0;
        backedge(ctx);
    L_00529180:
        charge(ctx, 4);
        jal(ctx, 0x529180u, gen::fn_dpadd_00531170);
        ld(s0, sp, 0x0);
        backedge(ctx);
    }
    // 0x0052910c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00529578 __ieee754_log10 -- 372 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// __ieee754_log10(x $a0) -> $v0: log10(x) = k*log10(2) + log10(e) * __ieee754_log(the mantissa rescaled to [1,2) or
// [0.5,1)), with the special cases of log (negative: NaN, zero: -huge).
void __ieee754_log10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00529578
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t7 = 0xF0000;
    sd(s0, sp, 0x0);
    t7 = t7 | 0xFFFF;
    sd(s1, sp, 0x8);
    t6 = dsll32(a0, 0);
    sd(s2, sp, 0x10);
    s0 = dsra32(a0, 0);
    sd(ra, sp, 0x18);
    t6 = dsra32(t6, 0);
    s2 = a0;
    t7 = slt(t7, s0);
    s1 = 0;
    if (t7 == 0) {
        // 0x005295b0
        charge(ctx, 6);
        t7 = 0x7FFF0000;
        t7 = t7 | 0xFFFF;
        t7 = s0 & t7;
        t7 = t7 | t6;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (cc) {
            // 0x005295e4
            charge(ctx, 2);
            if (i64(s0) >= 0) {
                a1 = 1077;
                // 0x00529608
                charge(ctx, 5);
                s1 = si(-54);
                a1 = dsll32(a1, 20);
                jal(ctx, 0x52960Cu, gen::fn_dpmul_00531230);
                s2 = v0;
                s0 = dsra32(v0, 0);
                goto L_0052961c;
            }
            // 0x005295ec
            charge(ctx, 7);
            a1 = a0;
            jal(ctx, 0x5295ECu, gen::fn_dpsub_005311c8);
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x5295F8u, gen::fn_dpdiv_00531480);
            ld(s0, sp, 0x0);
            backedge(ctx);
        } else {
            // 0x005295c8
            charge(ctx, 2);
            ld(v0, t7, -2640);
            ld(s0, sp, 0x0);
        }
        // 0x005295d0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0052961c:
    charge(ctx, 5);
    t7 = 0x7FEF0000;
    t7 = t7 | 0xFFFF;
    t7 = slt(t7, s0);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = sra(s0, 20);
    if (cc) {
        // 0x00529648
        charge(ctx, 41);
        t6 = 0xF0000;
        t7 = addu(s1, t7);
        t6 = t6 | 0xFFFF;
        s1 = addiu(t7, -1023);
        t6 = s0 & t6;
        a0 = srl(s1, 31);
        t7 = 1023;
        t7 = subu(t7, a0);
        t7 = sll(t7, 20);
        a0 = addu(s1, a0);
        s0 = t6 | t7;
        jal(ctx, 0x529670u, gen::fn_litodp_00531720);
        t6 = dsll32(s0, 0);
        t7 = 0x7C0000;
        t5 = dsll32(s2, 0);
        ld(a1, t7, -2632);  // 0x7BF5B8
        t6 = dsrl32(t6, 0);
        t5 = dsrl32(t5, 0);
        t6 = dsll32(t6, 0);
        s1 = v0;
        s2 = t5 | t6;
        a0 = v0;
        jal(ctx, 0x52969Cu, gen::fn_dpmul_00531230);
        s0 = v0;
        a0 = s2;
        jal(ctx, 0x5296A8u, gen::fn___ieee754_log_005290a0);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x5296B8u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, -2624);
        call(ctx, gen::fn_dpmul_00531230);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x5296C4u, gen::fn_dpadd_00531170);
        t7 = 0x7C0000;
        s0 = v0;
        ld(a1, t7, -2616);  // 0x7BF5C8
        a0 = s1;
        jal(ctx, 0x5296D8u, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s0;
        backedge(ctx);
    } else {
        // 0x00529630
        charge(ctx, 2);
        a0 = s2;
        a1 = s2;
    }
    // 0x00529638
    charge(ctx, 4);
    jal(ctx, 0x529638u, gen::fn_dpadd_00531170);
    ld(s0, sp, 0x0);
    backedge(ctx);
    // 0x005295d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0052A8C8 __ieee754_sqrt -- 784 bytes; frame 0x40: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, ra sp+0x30
// __ieee754_sqrt(x $a0) -> $v0: square root in double precision, computed entirely on the soft-float helpers (dpmul /
// dpadd / dpsub / dpdiv / dpcmp); sqrt(-x) gives a NaN, +-0 returns x.
void __ieee754_sqrt(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052a8c8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t5 = 0x7FF00000;
    sd(s0, sp, 0x0);
    t4 = dsra32(a0, 0);
    sd(s1, sp, 0x8);
    t3 = dsll32(a0, 0);
    sd(s2, sp, 0x10);
    s0 = lui(0x8000);
    sd(s3, sp, 0x18);
    s1 = a0;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    t7 = t4 & t5;
    sd(ra, sp, 0x30);
    t3 = dsra32(t3, 0);
    if (t7 == t5) {
        // 0x0052a908
        charge(ctx, 5);
        a1 = a0;
        jal(ctx, 0x52A908u, gen::fn_dpmul_00531230);
        a0 = v0;
        a1 = s1;
        jal(ctx, 0x52A914u, gen::fn_dpadd_00531170);
        goto L_0052a91c;
    }
    // 0x0052a940
    charge(ctx, 2);
    s2 = sra(t4, 20);
    if (i64(t4) <= 0) {
        // 0x0052a948
        charge(ctx, 6);
        t7 = 0x7FFF0000;
        t7 = t7 | 0xFFFF;
        t7 = t4 & t7;
        t7 = t7 | t3;
        v0 = a0;
        if (t7 == 0) {
            backedge(ctx);
        L_0052a91c:
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        } else {
            // 0x0052a960
            charge(ctx, 2);
            if (i64(t4) >= 0) {
                goto L_0052a994;
            }
            // 0x0052a968
            charge(ctx, 11);
            a1 = a0;
            jal(ctx, 0x52A968u, gen::fn_dpsub_005311c8);
            s0 = v0;
            a0 = s1;
            a1 = s1;
            jal(ctx, 0x52A978u, gen::fn_dpsub_005311c8);
            a1 = v0;
            a0 = s0;
            jal(ctx, 0x52A984u, gen::fn_dpdiv_00531480);
            ld(s0, sp, 0x0);
            backedge(ctx);
        }
        // 0x0052a920 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_0052a994:
    charge(ctx, 2);
    t7 = 0xF0000;
    if (s2 == 0) {
        // 0x0052a99c
        charge(ctx, 2);
        t7 = 0x100000;
        if (t4 == 0) {
            // 0x0052a9a4
            charge(ctx, 2);
            t5 = t3;
            t6 = s2;
            for (;;) {
                // 0x0052a9ac
                charge(ctx, 7);
                t7 = srl(t5, 11);
                t6 = addiu(t6, -21);
                t4 = t4 | t7;
                t5 = sll(t5, 21);
                if (t4 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052a9c8
            charge(ctx, 3);
            s2 = t6;
            t3 = t5;
            t7 = 0x100000;
        }
        // 0x0052a9d4
        charge(ctx, 3);
        t7 = t4 & t7;
        t2 = 0;
        if (t7 == 0) {
            // 0x0052a9e0
            charge(ctx, 2);
            t6 = t4;
            t5 = 0x100000;
            for (;;) {
                // 0x0052a9e8
                charge(ctx, 7);
                t6 = sll(t6, 1);
                t7 = t6 & t5;
                t2 = addiu(t2, 1);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052aa04
            charge(ctx, 1);
            t4 = t6;
        }
        // 0x0052aa08
        charge(ctx, 7);
        t7 = subu(0, t2);
        t6 = subu(s2, t2);
        t7 = srlv(t3, t7);
        s2 = addiu(t6, 1);
        t4 = t4 | t7;
        t3 = sllv(t3, t2);
        t7 = 0xF0000;
    }
    // 0x0052aa24
    charge(ctx, 7);
    s2 = addiu(s2, -1023);
    t7 = t7 | 0xFFFF;
    t6 = 0x100000;
    t7 = t4 & t7;
    t5 = s2 & 0x1;
    t4 = t7 | t6;
    if (t5 != 0) {
        // 0x0052aa40
        charge(ctx, 5);
        t7 = t3 & s0;
        t7 = srl(t7, 31);
        t3 = sll(t3, 1);
        t7 = addu(t4, t7);
        t4 = addu(t4, t7);
    }
    // 0x0052aa54
    charge(ctx, 11);
    t7 = t3 & s0;
    s2 = sra(s2, 1);
    t7 = srl(t7, 31);
    t5 = sll(t3, 1);
    t7 = addu(t4, t7);
    a1 = 0;
    t6 = addu(t4, t7);
    a2 = 0;
    s3 = 0;
    s1 = 0;
    t2 = 0x200000;
    for (;;) {
        // 0x0052aa80
        charge(ctx, 4);
        t4 = addu(a2, t2);
        t7 = slt(t6, t4);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = t5 & s0;
        if (!cc) {
            // 0x0052aa90
            charge(ctx, 3);
            t6 = subu(t6, t4);
            a2 = addu(t4, t2);
            s1 = addu(s1, t2);
        }
        // 0x0052aa9c
        charge(ctx, 6);
        t2 = srl(t2, 1);
        t7 = srl(t7, 31);
        t5 = sll(t5, 1);
        t7 = addu(t6, t7);
        t6 = addu(t6, t7);
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0052aab4
    charge(ctx, 1);
    t2 = lui(0x8000);
    for (;;) {
    L_0052aab8:
        charge(ctx, 6);
        t3 = addu(a1, t2);
        t4 = a2;
        t1 = sltu(t5, t3);
        t7 = slt(a2, t6);
        t0 = t3 & s0;
        if (t7 == 0) {
            // 0x0052aad0
            charge(ctx, 2);
            t7 = t5 & s0;
            if (a2 != t6) {
            L_0052ab08:
                charge(ctx, 1);
                t2 = srl(t2, 1);
            } else {
                // 0x0052aad8
                charge(ctx, 2);
                if (t1 == 0) {
                    goto L_0052aae0;
                }
                t2 = srl(t2, 1);
            }
            goto L_0052ab0c;
        }
    L_0052aae0:
        charge(ctx, 3);
        a1 = addu(t3, t2);
        a3 = a1 & s0;
        if (t0 == s0) {
            // 0x0052aaec
            charge(ctx, 2);
            t7 = addiu(a2, 1);
            if (a3 == 0) a2 = t7;
        }
        // 0x0052aaf4
        charge(ctx, 5);
        t6 = subu(t6, t4);
        t5 = subu(t5, t3);
        s3 = addu(s3, t2);
        t6 = subu(t6, t1);
        t7 = t5 & s0;
        goto L_0052ab08;
    }
L_0052ab20_33:
    charge(ctx, 3);
    t7 = t6 | t5;
    s4 = 1023;
    if (t7 != 0) {
        // 0x0052ab2c
        charge(ctx, 6);
        s4 = dsll32(s4, 20);
        a0 = s4;
        a1 = s4;
        jal(ctx, 0x52AB34u, gen::fn_dpcmp_005316d0);
        t6 = sra(s1, 1);
        if (i64(v0) <= 0) {
            // 0x0052ab44
            charge(ctx, 3);
            t7 = si(-1);
            a0 = s4;
            if (s3 != t7) {
                // 0x0052aba8
                charge(ctx, 4);
                a1 = s4;
                jal(ctx, 0x52ABA8u, gen::fn_dpcmp_005316d0);
                t7 = s3 & 0x1;
                if (i64(v0) >= 0) {
                    // 0x0052abd0
                    charge(ctx, 2);
                    s3 = addu(s3, t7);
                    backedge(ctx);
                } else {
                    // 0x0052abb8
                    charge(ctx, 6);
                    t7 = si(-2);
                    t6 = addiu(s1, 1);
                    t7 = s3 ^ t7;
                    if (t7 == 0) s1 = t6;
                    s3 = addiu(s3, 2);
                    backedge(ctx);
                }
            } else {
                // 0x0052ab50
                charge(ctx, 2);
                s3 = 0;
                s1 = addiu(s1, 1);
            }
            goto L_0052ab58;
        }
        goto L_0052ab5c;
    }
L_0052ab58:
    charge(ctx, 1);
    t6 = sra(s1, 1);
L_0052ab5c:
    charge(ctx, 19);
    t7 = 0x3FE00000;
    t4 = addu(t6, t7);
    t3 = srl(s3, 1);
    t5 = s1 & 0x1;
    t7 = t3 | s0;
    t6 = sll(s2, 20);
    if (t5 != 0) t3 = t7;
    t6 = addu(t4, t6);
    s5 = dsll32(s5, 0);
    t6 = dsll32(t6, 0);
    s5 = dsrl32(s5, 0);
    t7 = si(-1);
    t5 = dsll32(t3, 0);
    s5 = s5 | t6;
    t7 = dsll32(t7, 0);
    s5 = s5 & t7;
    t5 = dsrl32(t5, 0);
    v0 = s5 | t5;
    backedge(ctx);
    goto L_0052a91c;
L_0052ab0c:
    charge(ctx, 5);
    t7 = srl(t7, 31);
    t5 = sll(t5, 1);
    t7 = addu(t6, t7);
    t6 = addu(t6, t7);
    if (t2 == 0) {
        goto L_0052ab20_33;
    }
    backedge(ctx);
    goto L_0052aab8;
}

// 0x0052ABD8 __ieee754_acosf -- 1040 bytes; frame 0x20: ra sp+0x0, f22 sp+0x10, f21 sp+0xC, f20 sp+0x8
// __ieee754_acosf(x $f12) -> $f0: acosf on the EE FPU (singles; the R5900 has no IEEE infinities / NaNs / denormals:
// out-of-range input gives the (x-x)/(x-x) result the FPU produces); the acos scheme of the double version with
// single-precision coefficients and __ieee754_sqrtf.
void __ieee754_acosf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052abd8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    mfc1(t5, f12);
    t7 = 0x7FFF0000;
    sd(ra, sp, 0x0);
    t7 = t7 | 0xFFFF;
    swc1(f22, sp, 0x10);
    swc1(f21, sp, 0xC);
    t4 = 0x3F800000;
    swc1(f20, sp, 0x8);
    t6 = t5 & t7;
    t7 = slt(t4, t6);
    if (t6 == t4) {
        // 0x0052ac08
        charge(ctx, 2);
        mtc1(zero, f0);
        if (i64(t5) <= 0) {
            // 0x0052ac10
            charge(ctx, 3);
            t7 = 0x7C0000;
            t7 = addiu(t7, -1568);  // &0x7BF9E0
            lwc1(f0, t7, 0);  // 0x7BF9E0
        }
        goto L_0052ac1c;
    }
    // 0x0052ac34
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (t7 == 0) {
        // 0x0052ac54
        charge(ctx, 5);
        t7 = 0x3EFF0000;
        t7 = t7 | 0xFFFF;
        t7 = slt(t7, t6);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (cc) {
            // 0x0052ad88
            charge(ctx, 2);
            t7 = 0x7C0000;
            if (i64(t5) >= 0) {
                // 0x0052aeb0
                charge(ctx, 78);
                t7 = addiu(t7, -1524);
                lwc1(f20, t7, 0);
                t7 = 0x7C0000;
                sub_s(f1, f20, f12);
                t7 = addiu(t7, -1512);  // &0x7BFA18
                lwc1(f0, t7, 0);  // 0x7BFA18
                mul_s(f21, f1, f0);
                mov_s(f12, f21);
                jal(ctx, 0x52AECCu, gen::fn___ieee754_sqrtf_0052c398);
                mov_s(f12, f0);
                t7 = 0x7C0000;
                mfc1(t6, f0);
                t7 = addiu(t7, -1560);  // &0x7BF9E8
                lwc1(f0, t7, 0);  // 0x7BF9E8
                t7 = si(-4096);
                mul_s(f0, f21, f0);
                t5 = t6 & t7;
                t7 = 0x7C0000;
                t7 = addiu(t7, -1556);  // &0x7BF9EC
                lwc1(f1, t7, 0);  // 0x7BF9EC
                t7 = 0x7C0000;
                mul_s(f1, f21, f1);
                t7 = addiu(t7, -1552);  // &0x7BF9F0
                lwc1(f2, t7, 0);  // 0x7BF9F0
                add_s(f0, f0, f2);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1548);  // &0x7BF9F4
                mtc1(t5, f2);
                mul_s(f0, f21, f0);
                add_s(f3, f12, f2);
                mul_s(f4, f2, f2);
                lwc1(f2, t7, 0);  // 0x7BF9F4
                sub_s(f4, f21, f4);
                add_s(f1, f1, f2);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1544);  // &0x7BF9F8
                div_s(f4, f4, f3);
                lwc1(f2, t7, 0);  // 0x7BF9F8
                mul_s(f1, f21, f1);
                add_s(f0, f0, f2);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1540);  // &0x7BF9FC
                lwc1(f2, t7, 0);  // 0x7BF9FC
                mul_s(f0, f21, f0);
                add_s(f1, f1, f2);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1536);  // &0x7BFA00
                lwc1(f2, t7, 0);  // 0x7BFA00
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                add_s(f0, f0, f2);
                t7 = addiu(t7, -1532);  // &0x7BFA04
                lwc1(f3, t7, 0);  // 0x7BFA04
                add_s(f1, f1, f3);
                t7 = 0x7C0000;
                mul_s(f0, f21, f0);
                t7 = addiu(t7, -1528);  // &0x7BFA08
                lwc1(f2, t7, 0);  // 0x7BFA08
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                add_s(f0, f0, f2);
                t7 = addiu(t7, -1520);  // &0x7BFA10
                add_s(f22, f1, f20);
                mul_s(f0, f21, f0);
                lwc1(f1, t7, 0);  // 0x7BFA10
                add_s(f0, f0, f1);
                mul_s(f20, f21, f0);
                div_s(f0, f20, f22);
                mul_s(f1, f0, f12);
                add_s(f0, f1, f4);
                mtc1(t5, f1);
                add_s(f0, f1, f0);
                add_s(f0, f0, f0);
                backedge(ctx);
            } else {
                // 0x0052ad90
                charge(ctx, 72);
                t7 = addiu(t7, -1524);
                lwc1(f4, t7, 0);
                t7 = 0x7C0000;
                add_s(f2, f12, f4);
                t7 = addiu(t7, -1512);  // &0x7BFA18
                lwc1(f1, t7, 0);  // 0x7BFA18
                t7 = 0x7C0000;
                mul_s(f21, f2, f1);
                t7 = addiu(t7, -1560);  // &0x7BF9E8
                lwc1(f0, t7, 0);  // 0x7BF9E8
                t7 = 0x7C0000;
                mul_s(f0, f21, f0);
                t7 = addiu(t7, -1556);  // &0x7BF9EC
                mov_s(f12, f21);
                lwc1(f1, t7, 0);  // 0x7BF9EC
                t7 = 0x7C0000;
                mul_s(f1, f21, f1);
                t7 = addiu(t7, -1552);  // &0x7BF9F0
                lwc1(f2, t7, 0);  // 0x7BF9F0
                t7 = 0x7C0000;
                add_s(f0, f0, f2);
                t7 = addiu(t7, -1548);  // &0x7BF9F4
                lwc1(f3, t7, 0);  // 0x7BF9F4
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1544);  // &0x7BF9F8
                mul_s(f0, f21, f0);
                lwc1(f2, t7, 0);  // 0x7BF9F8
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1540);  // &0x7BF9FC
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BF9FC
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1536);  // &0x7BFA00
                mul_s(f0, f21, f0);
                lwc1(f2, t7, 0);  // 0x7BFA00
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1532);  // &0x7BFA04
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BFA04
                add_s(f1, f1, f3);
                t7 = 0x7C0000;
                mul_s(f0, f21, f0);
                t7 = addiu(t7, -1528);  // &0x7BFA08
                lwc1(f2, t7, 0);  // 0x7BFA08
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                add_s(f0, f0, f2);
                t7 = addiu(t7, -1520);  // &0x7BFA10
                add_s(f22, f1, f4);
                mul_s(f0, f21, f0);
                lwc1(f1, t7, 0);  // 0x7BFA10
                add_s(f0, f0, f1);
                mul_s(f20, f21, f0);
                jal(ctx, 0x52AE70u, gen::fn___ieee754_sqrtf_0052c398);
                mov_s(f12, f0);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1516);  // &0x7BFA14
                lwc1(f1, t7, 0);  // 0x7BFA14
                div_s(f0, f20, f22);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1568);  // &0x7BF9E0
                mul_s(f2, f0, f12);
                sub_s(f0, f2, f1);
                add_s(f0, f12, f0);
                add_s(f0, f0, f0);
                backedge(ctx);
            L_0052ad7c:
                charge(ctx, 3);
                lwc1(f1, t7, 0);
                sub_s(f0, f1, f0);
                backedge(ctx);
            }
        } else {
            // 0x0052ac68
            charge(ctx, 6);
            t7 = addiu(t7, -1564);
            lwc1(f0, t7, 0);
            t7 = 0x23000000;
            t7 = slt(t7, t6);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 0x7C0000;
            if (!cc) {
                // 0x0052ac80
                charge(ctx, 63);
                mul_s(f21, f12, f12);
                t7 = addiu(t7, -1560);
                lwc1(f0, t7, 0);
                t7 = 0x7C0000;
                mul_s(f0, f21, f0);
                t7 = addiu(t7, -1556);  // &0x7BF9EC
                lwc1(f1, t7, 0);  // 0x7BF9EC
                t7 = 0x7C0000;
                mul_s(f1, f21, f1);
                t7 = addiu(t7, -1552);  // &0x7BF9F0
                lwc1(f2, t7, 0);  // 0x7BF9F0
                t7 = 0x7C0000;
                add_s(f0, f0, f2);
                t7 = addiu(t7, -1548);  // &0x7BF9F4
                lwc1(f3, t7, 0);  // 0x7BF9F4
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1544);  // &0x7BF9F8
                mul_s(f0, f21, f0);
                lwc1(f2, t7, 0);  // 0x7BF9F8
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1540);  // &0x7BF9FC
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BF9FC
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1536);  // &0x7BFA00
                mul_s(f0, f21, f0);
                lwc1(f2, t7, 0);  // 0x7BFA00
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1532);  // &0x7BFA04
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BFA04
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1528);  // &0x7BFA08
                mul_s(f0, f21, f0);
                lwc1(f2, t7, 0);  // 0x7BFA08
                mul_s(f1, f21, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1524);  // &0x7BFA0C
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BFA0C
                add_s(f22, f1, f3);
                t7 = 0x7C0000;
                mul_s(f0, f21, f0);
                t7 = addiu(t7, -1520);  // &0x7BFA10
                lwc1(f1, t7, 0);  // 0x7BFA10
                add_s(f0, f0, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1516);  // &0x7BFA14
                mul_s(f20, f21, f0);
                div_s(f0, f20, f22);
                mul_s(f1, f12, f0);
                lwc1(f0, t7, 0);  // 0x7BFA14
                sub_s(f0, f0, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1564);  // &0x7BF9E4
                sub_s(f0, f12, f0);
                goto L_0052ad7c;
            }
            backedge(ctx);
        }
    L_0052ac1c:
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        lwc1(f22, sp, 0x10);
    } else {
        // 0x0052ac3c
        charge(ctx, 6);
        sub_s(f0, f12, f12);
        div_s(f0, f0, f0);
        lwc1(f22, sp, 0x10);
        backedge(ctx);
    }
    // 0x0052ac24 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lwc1(f21, sp, 0xC);
    lwc1(f20, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x0052AFE8 __ieee754_asinf -- 920 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, ra sp+0x10, f22 sp+0x20, f21 sp+0x1C, f20 sp+0x18
// __ieee754_asinf(x $f12) -> $f0: asinf on the EE FPU: tiny |x| returns x, |x| < 0.5 uses x + x*r(x^2), the rest pi/2
// - 2*asin-of-the-half-angle with __ieee754_sqrtf, fabsf for |x|.
void __ieee754_asinf(EEContext& ctx) {
    using namespace hg;
    Gpr t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052afe8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t7 = 0x7FFF0000;
    sd(s1, sp, 0x8);
    t7 = t7 | 0xFFFF;
    sd(s0, sp, 0x0);
    t6 = 0x3F800000;
    mfc1(s1, f12);
    sd(ra, sp, 0x10);
    swc1(f22, sp, 0x20);
    s0 = s1 & t7;
    swc1(f21, sp, 0x1C);
    swc1(f20, sp, 0x18);
    t7 = slt(t6, s0);
    if (s0 == t6) {
        // 0x0052b020
        charge(ctx, 8);
        t7 = 0x7C0000;
        t7 = addiu(t7, -1444);  // &0x7BFA5C
        lwc1(f0, t7, 0);  // 0x7BFA5C
        t7 = 0x7C0000;
        mula_s(f12, f0);
        t7 = addiu(t7, -1440);  // &0x7BFA60
        lwc1(f1, t7, 0);  // 0x7BFA60
        madd_s(f4, f12, f1);
        goto L_0052b040;
    }
    // 0x0052b064
    charge(ctx, 2);
    cc = t7 == 0;  // the condition, before the delay slot changes it
    t7 = 0x3EFF0000;
    if (cc) {
        // 0x0052b084
        charge(ctx, 4);
        t7 = t7 | 0xFFFF;
        t7 = slt(t7, s0);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x31FF0000;
        if (!cc) {
            // 0x0052b094
            charge(ctx, 4);
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0x7C0000;
            if (cc) {
                // 0x0052b298
                charge(ctx, 58);
                mul_s(f20, f12, f12);
                t7 = addiu(t7, -1428);
                lwc1(f0, t7, 0);
                t7 = 0x7C0000;
                mul_s(f0, f20, f0);
                t7 = addiu(t7, -1424);  // &0x7BFA70
                lwc1(f1, t7, 0);  // 0x7BFA70
                t7 = 0x7C0000;
                mul_s(f1, f20, f1);
                t7 = addiu(t7, -1420);  // &0x7BFA74
                lwc1(f2, t7, 0);  // 0x7BFA74
                t7 = 0x7C0000;
                add_s(f0, f0, f2);
                t7 = addiu(t7, -1416);  // &0x7BFA78
                lwc1(f3, t7, 0);  // 0x7BFA78
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1412);  // &0x7BFA7C
                mul_s(f0, f20, f0);
                lwc1(f2, t7, 0);  // 0x7BFA7C
                mul_s(f1, f20, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1408);  // &0x7BFA80
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BFA80
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1404);  // &0x7BFA84
                mul_s(f0, f20, f0);
                lwc1(f2, t7, 0);  // 0x7BFA84
                mul_s(f1, f20, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1400);  // &0x7BFA88
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BFA88
                t7 = 0x7C0000;
                add_s(f1, f1, f3);
                t7 = addiu(t7, -1396);  // &0x7BFA8C
                mul_s(f0, f20, f0);
                lwc1(f2, t7, 0);  // 0x7BFA8C
                mul_s(f1, f20, f1);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1432);  // &0x7BFA68
                add_s(f0, f0, f2);
                lwc1(f3, t7, 0);  // 0x7BFA68
                add_s(f22, f1, f3);
                t7 = 0x7C0000;
                mul_s(f0, f20, f0);
                t7 = addiu(t7, -1392);  // &0x7BFA90
                lwc1(f1, t7, 0);  // 0x7BFA90
                add_s(f0, f0, f1);
                mul_s(f21, f20, f0);
                div_s(f21, f21, f22);
                mul_s(f0, f12, f21);
                add_s(f4, f12, f0);
                backedge(ctx);
            } else {
                // 0x0052b0a4
                charge(ctx, 10);
                t7 = 0x7C0000;
                t7 = addiu(t7, -1436);  // &0x7BFA64
                lwc1(f0, t7, 0);  // 0x7BFA64
                t7 = 0x7C0000;
                add_s(f0, f12, f0);
                t7 = addiu(t7, -1432);  // &0x7BFA68
                lwc1(f1, t7, 0);  // 0x7BFA68
                c_lt_s(f1, f0);
                mov_s(f4, f12);
                if (!cond(ctx)) {
                    goto L_0052b0cc;
                }
                backedge(ctx);
            }
            goto L_0052b040;
        }
    L_0052b0cc:
        charge(ctx, 66);
        jal(ctx, 0x52B0CCu, gen::fn_fabsf_0052e788);
        t7 = 0x7C0000;
        t7 = addiu(t7, -1432);  // &0x7BFA68
        lwc1(f4, t7, 0);  // 0x7BFA68
        t7 = 0x7C0000;
        sub_s(f0, f4, f0);
        t7 = addiu(t7, -1388);  // &0x7BFA94
        lwc1(f1, t7, 0);  // 0x7BFA94
        mul_s(f20, f0, f1);
        t7 = 0x7C0000;
        t7 = addiu(t7, -1428);  // &0x7BFA6C
        lwc1(f0, t7, 0);  // 0x7BFA6C
        mov_s(f12, f20);
        t7 = 0x7C0000;
        mul_s(f0, f20, f0);
        t7 = addiu(t7, -1424);  // &0x7BFA70
        lwc1(f1, t7, 0);  // 0x7BFA70
        t7 = 0x7C0000;
        mul_s(f1, f20, f1);
        t7 = addiu(t7, -1420);  // &0x7BFA74
        lwc1(f2, t7, 0);  // 0x7BFA74
        t7 = 0x7C0000;
        add_s(f0, f0, f2);
        t7 = addiu(t7, -1416);  // &0x7BFA78
        lwc1(f3, t7, 0);  // 0x7BFA78
        t7 = 0x7C0000;
        add_s(f1, f1, f3);
        t7 = addiu(t7, -1412);  // &0x7BFA7C
        mul_s(f0, f20, f0);
        lwc1(f2, t7, 0);  // 0x7BFA7C
        mul_s(f1, f20, f1);
        t7 = 0x7C0000;
        t7 = addiu(t7, -1408);  // &0x7BFA80
        add_s(f0, f0, f2);
        lwc1(f3, t7, 0);  // 0x7BFA80
        t7 = 0x7C0000;
        add_s(f1, f1, f3);
        t7 = addiu(t7, -1404);  // &0x7BFA84
        mul_s(f0, f20, f0);
        lwc1(f2, t7, 0);  // 0x7BFA84
        mul_s(f1, f20, f1);
        t7 = 0x7C0000;
        t7 = addiu(t7, -1400);  // &0x7BFA88
        add_s(f0, f0, f2);
        lwc1(f3, t7, 0);  // 0x7BFA88
        add_s(f1, f1, f3);
        t7 = 0x7C0000;
        mul_s(f0, f20, f0);
        t7 = addiu(t7, -1396);  // &0x7BFA8C
        lwc1(f2, t7, 0);  // 0x7BFA8C
        mul_s(f1, f20, f1);
        t7 = 0x7C0000;
        add_s(f0, f0, f2);
        t7 = addiu(t7, -1392);  // &0x7BFA90
        add_s(f22, f1, f4);
        mul_s(f0, f20, f0);
        lwc1(f1, t7, 0);  // 0x7BFA90
        add_s(f0, f0, f1);
        mul_s(f21, f20, f0);
        jal(ctx, 0x52B1B8u, gen::fn___ieee754_sqrtf_0052c398);
        t7 = 0x3F790000;
        t7 = t7 | 0x9999;
        t7 = slt(t7, s0);
        mfc1(t5, f0);
        if (t7 == 0) {
            // 0x0052b220
            charge(ctx, 30);
            t7 = si(-4096);
            mtc1(t5, f2);
            t6 = t5 & t7;
            div_s(f4, f21, f22);
            mtc1(t6, f0);
            t7 = 0x7C0000;
            mtc1(t6, f6);
            t7 = addiu(t7, -1384);  // &0x7BFA98
            mul_s(f1, f0, f0);
            add_s(f3, f2, f0);
            lwc1(f5, t7, 0);  // 0x7BFA98
            sub_s(f1, f20, f1);
            t7 = 0x7C0000;
            add_s(f0, f6, f6);
            t7 = addiu(t7, -1440);  // &0x7BFA60
            add_s(f2, f2, f2);
            div_s(f1, f1, f3);
            sub_s(f22, f5, f0);
            mul_s(f2, f2, f4);
            lwc1(f0, t7, 0);  // 0x7BFA60
            add_s(f1, f1, f1);
            sub_s(f0, f0, f1);
            sub_s(f21, f2, f0);
            sub_s(f1, f21, f22);
            sub_s(f20, f5, f1);
            backedge(ctx);
        } else {
            // 0x0052b1d4
            charge(ctx, 15);
            div_s(f21, f21, f22);
            t7 = 0x7C0000;
            mtc1(t5, f1);
            t7 = addiu(t7, -1440);  // &0x7BFA60
            mul_s(f0, f0, f21);
            add_s(f0, f1, f0);
            add_s(f0, f0, f0);
            lwc1(f1, t7, 0);  // 0x7BFA60
            t7 = 0x7C0000;
            sub_s(f0, f0, f1);
            t7 = addiu(t7, -1444);  // &0x7BFA5C
            lwc1(f2, t7, 0);  // 0x7BFA5C
            sub_s(f20, f2, f0);
        }
        // 0x0052b210
        charge(ctx, 2);
        mov_s(f4, f20);
        if (i64(s1) > 0) {
            backedge(ctx);
        } else {
            // 0x0052b218
            charge(ctx, 2);
            neg_s(f4, f20);
            backedge(ctx);
        }
    L_0052b040:
        charge(ctx, 1);
        mov_s(f0, f4);
    } else {
        // 0x0052b06c
        charge(ctx, 6);
        sub_s(f0, f12, f12);
        div_s(f4, f0, f0);
        mov_s(f0, f4);
        backedge(ctx);
    }
    // 0x0052b044 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    lwc1(f22, sp, 0x20);
    lwc1(f21, sp, 0x1C);
    lwc1(f20, sp, 0x18);
    sp = addiu(sp, 0x30);
}

// 0x0052B800 __ieee754_powf -- 2044 bytes; frame 0x40: s1 sp+0x8, f21 sp+0x34, f20 sp+0x30, s2 sp+0x10, s0 sp+0x0, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// __ieee754_powf(x $f12, y $f13) -> $f0: powf on the EE FPU: the special cases (y == 0 -> 1, y == +-1, +-2, 0.5, x ==
// 0 / 1, negative x with an integral / odd y), then log2(|x|) in extra precision (high / low split singles), times y,
// and 2^(y*log2 x) through a polynomial and scalbnf; overflow / underflow give the huge / tiny products.
void __ieee754_powf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052b800
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t6 = 0x7FFF0000;
    sd(s1, sp, 0x8);
    t5 = 0x7C0000;
    swc1(f21, sp, 0x34);
    t6 = t6 | 0xFFFF;
    swc1(f20, sp, 0x30);
    t7 = 0x7F0000;
    sd(s2, sp, 0x10);
    mov_s(f21, f13);
    sd(s0, sp, 0x0);
    mov_s(f20, f12);
    sd(s3, sp, 0x18);
    t5 = addiu(t5, -1096);  // &0x7BFBB8
    sd(s4, sp, 0x20);
    t7 = t7 | 0xFFFF;  // &0x7FFFFF
    sd(ra, sp, 0x28);
    mfc1(s1, f13);
    mfc1(s2, f12);
    s0 = s1 & t6;
    lwc1(f0, t5, 0);  // 0x7BFBB8
    t7 = slt(t7, s0);
    s3 = s2 & t6;
    if (t7 != 0) {
        // 0x0052b860
        charge(ctx, 2);
        s4 = 0;
        if (i64(s2) < 0) {
            // 0x0052b868
            charge(ctx, 5);
            t7 = 0x4B7F0000;
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 0x3F7F0000;
            if (!cc) {
                // 0x0052b87c
                charge(ctx, 1);
                s4 = 2;
                goto L_0052b880;
            }
            // 0x0052bfc4
            charge(ctx, 4);
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 150;
            if (cc) {
                backedge(ctx);
                goto L_0052b880;
            }
            // 0x0052bfd4
            charge(ctx, 6);
            t6 = sra(s0, 23);
            t7 = subu(t7, t6);
            t4 = srav(s0, t7);
            t7 = sllv(t4, t7);
            cc = t7 != s0;  // the condition, before the delay slot changes it
            t7 = 0x3F800000;
            if (!cc) {
                // 0x0052bfec
                charge(ctx, 4);
                t6 = t4 & 0x1;
                t7 = 2;
                s4 = subu(t7, t6);
                backedge(ctx);
                goto L_0052b880;
            }
            backedge(ctx);
            goto L_0052b884;
        }
    L_0052b880:
        charge(ctx, 1);
        t7 = 0x3F800000;
    L_0052b884:
        charge(ctx, 2);
        if (s0 == t7) {
            // 0x0052b88c
            charge(ctx, 2);
            mov_s(f0, f20);
            if (i64(s1) < 0) {
                // 0x0052b894
                charge(ctx, 6);
                t6 = 0x7C0000;
                t6 = addiu(t6, -1096);  // &0x7BFBB8
                lwc1(f0, t6, 0);  // 0x7BFBB8
                div_s(f0, f0, f20);
            }
            goto L_0052b8ac;
        }
        t7 = 0x40000000;
        // 0x0052b8d4
        charge(ctx, 2);
        cc = s1 != t7;  // the condition, before the delay slot changes it
        t7 = 0x3F000000;
        if (!cc) {
            // 0x0052b8dc
            charge(ctx, 2);
            mul_s(f0, f20, f20);
            backedge(ctx);
            goto L_0052b8ac;
        }
        // 0x0052b8e4
        charge(ctx, 2);
        if (s1 == t7) {
            // 0x0052b8ec
            charge(ctx, 2);
            mov_s(f12, f20);
            if (i64(s2) < 0) {
                goto L_0052b91c;
            }
            // 0x0052b8f4
            charge(ctx, 10);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(ra, sp, 0x28);
            lwc1(f21, sp, 0x34);
            lwc1(f20, sp, 0x30);
            sp = addiu(sp, 0x40);
            gen::fn___ieee754_sqrtf_0052c398(ctx);  // tail call
            return;
        }
    L_0052b91c:
        charge(ctx, 7);
        mov_s(f12, f20);
        jal(ctx, 0x52B91Cu, gen::fn_fabsf_0052e788);
        t6 = 0x7F0000;
        t6 = t6 | 0xFFFF;  // &0x7FFFFF
        t7 = slt(t6, s3);
        mov_s(f12, f0);
        if (t7 != 0) {
            // 0x0052b938
            charge(ctx, 3);
            t5 = 0x3F800000;
            t0 = srl(s2, 31);
            if (s3 == t5) {
                goto L_0052b944;
            }
            // 0x0052b9a8
            charge(ctx, 4);
            t7 = addiu(t0, -1);
            t7 = t7 | s4;
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0x4D000000;
            if (cc) {
                // 0x0052b9d0
                charge(ctx, 3);
                t7 = slt(t7, s0);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = 0x3F7F0000;
                if (cc) {
                    // 0x0052bd78
                    charge(ctx, 9);
                    t4 = s3 & t6;
                    t7 = 0x1C0000;
                    t6 = sra(s3, 23);
                    t7 = t7 | 0xC471;  // &0x1CC471
                    s3 = t4 | t5;
                    t7 = slt(t7, t4);
                    a0 = addiu(t6, -127);
                    t2 = 0;
                    if (t7 != 0) {
                        // 0x0052bd9c
                        charge(ctx, 5);
                        t7 = 0x5D0000;
                        t7 = t7 | 0xB3D6;  // "ommu/card/i_s_card0d.tmx"
                        t7 = slt(t7, t4);
                        t2 = 1;
                        if (t7 != 0) {
                            // 0x0052bdb0
                            charge(ctx, 4);
                            t7 = lui(0xFF80);
                            a0 = addiu(t6, -126);
                            s3 = addu(s3, t7);
                            t2 = 0;
                        }
                    }
                    // 0x0052bdc0
                    charge(ctx, 129);
                    t7 = 0x7C0000;
                    mtc1(s3, f12);
                    t4 = sll(t2, 2);
                    t7 = addiu(t7, -1232);  // &0x7BFB30
                    t7 = addu(t4, t7);
                    t6 = sra(s3, 1);
                    lwc1(f1, t7, 0);
                    t5 = sll(t2, 21);
                    t7 = 0x20000000;
                    add_s(f2, f12, f1);
                    t6 = t6 | t7;
                    sub_s(f11, f12, f1);
                    t7 = 0x7C0000;
                    t6 = addu(t6, t5);
                    t7 = addiu(t7, -1096);  // &0x7BFBB8
                    t5 = si(-4096);
                    lwc1(f0, t7, 0);  // 0x7BFBB8
                    div_s(f10, f0, f2);
                    t7 = 0x40000;
                    t3 = addu(t6, t7);
                    t7 = 0x7C0000;
                    mtc1(t3, f3);
                    t7 = addiu(t7, -1216);  // &0x7BFB40
                    t6 = 0x7C0000;
                    t7 = addu(t4, t7);
                    t6 = addiu(t6, -1068);  // &0x7BFBD4
                    lwc1(f8, t7, 0);
                    lwc1(f4, t6, 0);  // 0x7BFBD4
                    t7 = 0x7C0000;
                    mtc1(t3, f0);
                    t7 = addiu(t7, -1224);  // &0x7BFB38
                    mul_s(f20, f11, f10);
                    t6 = 0x7C0000;
                    sub_s(f1, f0, f1);
                    t4 = addu(t4, t7);
                    t6 = addiu(t6, -1064);  // &0x7BFBD8
                    lwc1(f7, t4, 0);
                    mfc1(t7, f20);
                    mtc1(a0, f0);
                    sub_s(f12, f12, f1);
                    cvt_s_w(f0, f0);
                    mul_s(f9, f20, f20);
                    mfc1(t2, f0);
                    mul_s(f6, f9, f9);
                    lwc1(f0, t6, 0);  // 0x7BFBD8
                    t6 = t7 & t5;
                    mul_s(f0, f9, f0);
                    mtc1(t6, f1);
                    t7 = 0x7C0000;
                    t7 = addiu(t7, -1060);  // &0x7BFBDC
                    mul_s(f2, f1, f3);
                    add_s(f5, f1, f20);
                    suba_s(f11, f2);
                    lwc1(f1, t7, 0);  // 0x7BFBDC
                    add_s(f0, f0, f1);
                    t7 = 0x7C0000;
                    t7 = addiu(t7, -1056);  // &0x7BFBE0
                    mtc1(t6, f1);
                    mul_s(f0, f9, f0);
                    msub_s(f3, f1, f12);
                    lwc1(f1, t7, 0);  // 0x7BFBE0
                    mul_s(f3, f10, f3);
                    add_s(f0, f0, f1);
                    t7 = 0x7C0000;
                    t7 = addiu(t7, -1052);  // &0x7BFBE4
                    mul_s(f0, f9, f0);
                    lwc1(f1, t7, 0);  // 0x7BFBE4
                    t7 = 0x7C0000;
                    add_s(f0, f0, f1);
                    t7 = addiu(t7, -1048);  // &0x7BFBE8
                    mul_s(f0, f9, f0);
                    lwc1(f1, t7, 0);  // 0x7BFBE8
                    t7 = 0x7C0000;
                    add_s(f0, f0, f1);
                    t7 = addiu(t7, -1044);  // &0x7BFBEC
                    mul_s(f0, f9, f0);
                    lwc1(f1, t7, 0);  // 0x7BFBEC
                    add_s(f0, f0, f1);
                    mtc1(t6, f1);
                    mula_s(f6, f0);
                    mul_s(f9, f1, f1);
                    madd_s(f1, f3, f5);
                    add_s(f0, f9, f4);
                    add_s(f0, f0, f1);
                    mfc1(t7, f0);
                    t3 = t7 & t5;
                    mtc1(t3, f2);
                    sub_s(f4, f2, f4);
                    mula_s(f3, f2);
                    mtc1(t6, f3);
                    sub_s(f4, f4, f9);
                    t6 = 0x7C0000;
                    mul_s(f11, f3, f2);
                    t6 = addiu(t6, -1040);  // &0x7BFBF0
                    sub_s(f12, f1, f4);
                    madd_s(f10, f12, f20);
                    add_s(f4, f11, f10);
                    mfc1(t7, f4);
                    t1 = t7 & t5;
                    mtc1(t1, f0);
                    t7 = 0x7C0000;
                    mtc1(t1, f1);
                    t7 = addiu(t7, -1032);  // "N8v?"
                    sub_s(f3, f0, f11);
                    lwc1(f0, t6, 0);  // 0x7BFBF0
                    sub_s(f3, f10, f3);
                    t6 = 0x7C0000;
                    mula_s(f1, f0);
                    t6 = addiu(t6, -1036);  // &0x7BFBF4
                    lwc1(f2, t6, 0);  // 0x7BFBF4
                    mul_s(f2, f1, f2);
                    lwc1(f1, t7, 0);  // 0x7BFBF8
                    madd_s(f1, f3, f1);
                    add_s(f1, f1, f8);
                    mtc1(t2, f3);
                    add_s(f0, f2, f1);
                    add_s(f0, f0, f7);
                    add_s(f3, f0, f3);
                    mfc1(t7, f3);
                    t3 = t7 & t5;
                    mtc1(t2, f3);
                    mtc1(t3, f4);
                    sub_s(f0, f4, f3);
                    sub_s(f0, f0, f7);
                    sub_s(f0, f0, f2);
                    sub_s(f1, f1, f0);
                    backedge(ctx);
                L_0052babc:
                    charge(ctx, 7);
                    t5 = 0x7C0000;
                    t7 = addiu(t0, -1);
                    t5 = addiu(t5, -1096);  // &0x7BFBB8
                    t6 = addiu(s4, -1);
                    t7 = t7 | t6;
                    lwc1(f20, t5, 0);  // 0x7BFBB8
                    if (t7 == 0) {
                        // 0x0052bad8
                        charge(ctx, 3);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -1028);  // &0x7BFBFC
                        lwc1(f20, t6, 0);  // 0x7BFBFC
                    }
                    // 0x0052bae4
                    charge(ctx, 17);
                    mfc1(t4, f21);
                    t7 = si(-4096);
                    mtc1(t3, f3);
                    t5 = 0x7FFF0000;
                    t6 = t4 & t7;
                    t5 = t5 | 0xFFFF;
                    mtc1(t6, f2);
                    sub_s(f0, f21, f2);
                    mul_s(f2, f2, f3);
                    mula_s(f0, f3);
                    madd_s(f3, f21, f1);
                    mfc1(t1, f2);
                    add_s(f12, f3, f2);
                    mfc1(t3, f12);
                    mfc1(t6, f12);
                    t5 = t3 & t5;
                    if (i64(t3) > 0) {
                        // 0x0052bb28
                        charge(ctx, 4);
                        t4 = 0x43010000;
                        t7 = slt(t4, t5);
                        if (t7 != 0) {
                            t5 = 0x7C0000;
                        } else {
                            // 0x0052bb38
                            charge(ctx, 2);
                            t7 = 0x3F000000;
                            if (t5 != t4) {
                                goto L_0052bb78;
                            }
                            // 0x0052bb40
                            charge(ctx, 8);
                            t7 = 0x7C0000;
                            sub_s(f1, f12, f2);
                            t7 = addiu(t7, -1020);  // &0x7BFC04
                            lwc1(f0, t7, 0);  // 0x7BFC04
                            add_s(f0, f3, f0);
                            c_lt_s(f1, f0);
                            t7 = 0x3F000000;
                            if (!cond(ctx)) {
                                goto L_0052bb78;
                            }
                            // 0x0052bb60
                            charge(ctx, 1);
                            t5 = 0x7C0000;
                            goto L_0052bb64;
                        }
                    L_0052bb64:
                        charge(ctx, 1);
                        t5 = addiu(t5, -1024);
                        goto L_0052bb68;
                    }
                    // 0x0052bd30
                    charge(ctx, 4);
                    t4 = 0x42FC0000;
                    t7 = slt(t4, t5);
                    if (t7 != 0) {
                        // 0x0052bd40
                        charge(ctx, 4);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -1016);  // &0x7BFC08
                        lwc1(f1, t6, 0);  // 0x7BFC08
                        backedge(ctx);
                        goto L_0052bb6c;
                    }
                    // 0x0052bd50
                    charge(ctx, 2);
                    t7 = 0x3F000000;
                    if (t5 != t4) {
                        backedge(ctx);
                    L_0052bb78:
                        charge(ctx, 1);
                        t4 = sra(t5, 23);
                    L_0052bb7c:
                        charge(ctx, 3);
                        t7 = slt(t7, t5);
                        a0 = 0;
                        if (t7 != 0) {
                            // 0x0052bb88
                            charge(ctx, 26);
                            t5 = 0x800000;
                            mtc1(t1, f0);
                            t7 = addiu(t4, -126);
                            t6 = 0x7F0000;
                            t7 = srav(t5, t7);
                            t6 = t6 | 0xFFFF;  // &0x7FFFFF
                            a0 = addu(t3, t7);
                            t7 = srl(a0, 23);
                            t4 = a0 & t6;
                            t7 = t7 & 0xFF;
                            t4 = t4 | t5;
                            t2 = addiu(t7, -127);
                            t5 = 23;
                            t6 = srav(t6, t2);
                            t5 = subu(t5, t2);
                            t6 = nor(0, t6);
                            t3 = slti(t3, 0);
                            t2 = a0 & t6;
                            mtc1(t2, f1);
                            a0 = srav(t4, t5);
                            t7 = subu(0, a0);
                            sub_s(f0, f0, f1);
                            if (t3 != 0) a0 = t7;
                            mfc1(t1, f0);
                            add_s(f0, f3, f0);
                            mfc1(t6, f0);
                        }
                        // 0x0052bbf0
                        charge(ctx, 75);
                        t7 = si(-4096);
                        mtc1(t1, f0);
                        t2 = t6 & t7;
                        t5 = sll(a0, 23);
                        mtc1(t2, f4);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -1012);  // &0x7BFC0C
                        t7 = 0x7C0000;
                        sub_s(f2, f4, f0);
                        t7 = addiu(t7, -1008);  // &0x7BFC10
                        lwc1(f0, t6, 0);  // 0x7BFC0C
                        sub_s(f2, f3, f2);
                        mul_s(f11, f4, f0);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -1004);  // &0x7BFC14
                        lwc1(f1, t6, 0);  // 0x7BFC14
                        lwc1(f0, t7, 0);  // 0x7BFC10
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -1000);  // &0x7BFC18
                        mula_s(f2, f0);
                        t7 = 0x7C0000;
                        madd_s(f10, f4, f1);
                        t7 = addiu(t7, -1096);  // &0x7BFBB8
                        add_s(f12, f11, f10);
                        mul_s(f0, f12, f12);
                        sub_s(f2, f12, f11);
                        mfc1(t2, f0);
                        sub_s(f3, f10, f2);
                        lwc1(f0, t6, 0);  // 0x7BFC18
                        mtc1(t2, f1);
                        t6 = 0x7C0000;
                        mul_s(f0, f1, f0);
                        t6 = addiu(t6, -996);  // &0x7BFC1C
                        mul_s(f2, f12, f3);
                        lwc1(f1, t6, 0);  // 0x7BFC1C
                        add_s(f2, f3, f2);
                        add_s(f0, f0, f1);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -992);  // &0x7BFC20
                        mtc1(t2, f1);
                        mul_s(f0, f1, f0);
                        lwc1(f1, t6, 0);  // 0x7BFC20
                        add_s(f0, f0, f1);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -988);  // &0x7BFC24
                        mtc1(t2, f1);
                        mul_s(f0, f1, f0);
                        lwc1(f1, t6, 0);  // 0x7BFC24
                        add_s(f0, f0, f1);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -984);  // &0x7BFC28
                        mtc1(t2, f1);
                        mul_s(f0, f1, f0);
                        lwc1(f1, t6, 0);  // 0x7BFC28
                        add_s(f0, f0, f1);
                        t6 = 0x7C0000;
                        t6 = addiu(t6, -980);  // &0x7BFC2C
                        mtc1(t2, f1);
                        mul_s(f0, f1, f0);
                        sub_s(f0, f12, f0);
                        lwc1(f1, t6, 0);  // 0x7BFC2C
                        sub_s(f1, f0, f1);
                        mul_s(f0, f12, f0);
                        div_s(f0, f0, f1);
                        sub_s(f1, f0, f2);
                        sub_s(f1, f1, f12);
                        lwc1(f0, t7, 0);  // 0x7BFBB8
                        sub_s(f12, f0, f1);
                        mfc1(t7, f12);
                        t4 = addu(t7, t5);
                        t6 = sra(t4, 23);
                        if (i64(t6) > 0) {
                            mtc1(t4, f12);
                        } else {
                            // 0x0052bd1c
                            charge(ctx, 3);
                            jal(ctx, 0x52BD1Cu, gen::fn_scalbnf_005239a8);
                            mov_s(f12, f0);
                        }
                        // 0x0052bd28
                        charge(ctx, 2);
                        mul_s(f0, f20, f12);
                        backedge(ctx);
                    } else {
                        // 0x0052bd58
                        charge(ctx, 4);
                        sub_s(f0, f12, f2);
                        c_le_s(f3, f0);
                        t4 = sra(t5, 23);
                        if (!cond(ctx)) {
                            backedge(ctx);
                            goto L_0052bb7c;
                        }
                        // 0x0052bd68
                        charge(ctx, 3);
                        t5 = 0x7C0000;
                        t5 = addiu(t5, -1016);  // &0x7BFC08
                        backedge(ctx);
                    L_0052bb68:
                        charge(ctx, 1);
                        lwc1(f1, t5, 0);
                    L_0052bb6c:
                        charge(ctx, 3);
                        mul_s(f0, f20, f1);
                        mul_s(f0, f0, f1);
                        backedge(ctx);
                    }
                } else {
                    // 0x0052b9dc
                    charge(ctx, 4);
                    t7 = t7 | 0xFFF7;
                    t7 = slt(t7, s3);
                    if (t7 != 0) {
                        t7 = 0x3F800000;
                        // 0x0052ba04
                        charge(ctx, 4);
                        t7 = t7 | 0x7;
                        t7 = slt(t7, s3);
                        t5 = 0x7C0000;
                        if (t7 == 0) {
                            // 0x0052ba28
                            charge(ctx, 37);
                            t6 = 0x7C0000;
                            t5 = addiu(t5, -1096);
                            t6 = addiu(t6, -1092);  // &0x7BFBBC
                            lwc1(f0, t5, 0);
                            t7 = 0x7C0000;
                            lwc1(f3, t6, 0);  // 0x7BFBBC
                            t7 = addiu(t7, -1088);  // &0x7BFBC0
                            sub_s(f20, f20, f0);
                            t5 = 0x7C0000;
                            t6 = 0x7C0000;
                            t5 = addiu(t5, -1084);  // &0x7BFBC4
                            t6 = addiu(t6, -1080);  // &0x7BFBC8
                            lwc1(f2, t5, 0);  // 0x7BFBC4
                            lwc1(f1, t6, 0);  // 0x7BFBC8
                            mul_s(f3, f20, f3);
                            t5 = 0x7C0000;
                            lwc1(f0, t7, 0);  // 0x7BFBC0
                            t5 = addiu(t5, -1072);  // &0x7BFBD0
                            mul_s(f4, f20, f20);
                            t7 = 0x7C0000;
                            mula_s(f20, f0);
                            sub_s(f1, f1, f3);
                            t7 = addiu(t7, -1076);  // &0x7BFBCC
                            lwc1(f0, t7, 0);  // 0x7BFBCC
                            mul_s(f11, f20, f2);
                            t7 = si(-4096);
                            mul_s(f1, f20, f1);
                            sub_s(f0, f0, f1);
                            mul_s(f3, f4, f0);
                            lwc1(f1, t5, 0);  // 0x7BFBD0
                            msub_s(f10, f3, f1);
                            add_s(f0, f11, f10);
                            mfc1(t6, f0);
                            t3 = t6 & t7;
                            mtc1(t3, f1);
                            sub_s(f0, f1, f11);
                            sub_s(f1, f10, f0);
                            goto L_0052babc;
                        }
                        // 0x0052ba14
                        charge(ctx, 2);
                        t7 = 0x7C0000;
                        if (i64(s1) <= 0) {
                            backedge(ctx);
                        L_0052b9f4:
                            charge(ctx, 2);
                            mtc1(zero, f0);
                            backedge(ctx);
                        } else {
                            // 0x0052ba1c
                            charge(ctx, 2);
                            lwc1(f0, t7, -1100);
                            backedge(ctx);
                        }
                    } else {
                        // 0x0052b9ec
                        charge(ctx, 2);
                        t7 = 0x7C0000;
                        if (i64(s1) >= 0) {
                            goto L_0052b9f4;
                        }
                        // 0x0052b9fc
                        charge(ctx, 2);
                        lwc1(f0, t7, -1100);
                        backedge(ctx);
                    }
                }
                goto L_0052b8ac;
            }
            // 0x0052b9b8
            charge(ctx, 6);
            sub_s(f0, f20, f20);
            div_s(f0, f0, f0);
            ld(s0, sp, 0x0);
            backedge(ctx);
            // 0x0052b8b0 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(s4, sp, 0x20);
            ld(ra, sp, 0x28);
            lwc1(f21, sp, 0x34);
            lwc1(f20, sp, 0x30);
            sp = addiu(sp, 0x40);
            return;
        }
    L_0052b944:
        charge(ctx, 2);
        t7 = 0x7C0000;
        if (i64(s1) < 0) {
            // 0x0052b94c
            charge(ctx, 5);
            t7 = addiu(t7, -1096);
            lwc1(f0, t7, 0);
            div_s(f12, f0, f12);
        }
        // 0x0052b960
        charge(ctx, 2);
        mov_s(f0, f12);
        if (i64(s2) >= 0) {
            backedge(ctx);
        } else {
            // 0x0052b968
            charge(ctx, 5);
            t7 = lui(0xC080);
            t7 = addu(s3, t7);
            t7 = t7 | s4;
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 1;
            if (!cc) {
                // 0x0052b97c
                charge(ctx, 4);
                sub_s(f0, f12, f12);
                div_s(f12, f0, f0);
                goto L_0052b98c;
            }
            // 0x0052b994
            charge(ctx, 2);
            if (s4 == t7) {
                neg_s(f12, f12);
                backedge(ctx);
            L_0052b98c:
                charge(ctx, 2);
                mov_s(f0, f12);
                backedge(ctx);
            } else {
                // 0x0052b99c
                charge(ctx, 2);
                mov_s(f0, f12);
                backedge(ctx);
            }
        }
        goto L_0052b8ac;
    }
L_0052b8ac:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0052b8b0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    lwc1(f21, sp, 0x34);
    lwc1(f20, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0052C000 __ieee754_rem_pio2f -- 920 bytes; frame 0x30: s2 sp+0x20, s0 sp+0x10, s1 sp+0x18, ra sp+0x28
// __ieee754_rem_pio2f(x $f12, y $a0) -> $v0: argument reduction for the single trig functions: n = round(x / (pi/2))
// and y[0] + y[1] = x - n*pi/2 (two floats at $a0) in Cody-Waite steps with pi/2 split into 3 parts (more steps when
// cancellation is detected), huge |x| through __kernel_rem_pio2f on the 8-bit pieces of x; returns n (low bits =
// quadrant).
void __ieee754_rem_pio2f(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052c000
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t6 = 0x7FFF0000;
    sd(s2, sp, 0x20);
    t6 = t6 | 0xFFFF;
    sd(s0, sp, 0x10);
    t7 = 0x3F490000;
    mfc1(s2, f12);
    t7 = t7 | 0xFD8;
    sd(s1, sp, 0x18);
    s0 = s2 & t6;
    sd(ra, sp, 0x28);
    t7 = slt(t7, s0);
    s1 = a0;
    if (t7 == 0) {
        // 0x0052c038
        charge(ctx, 3);
        swc1(f12, s1, 0);
        v0 = 0;
        sw(zero, a0, 4);
        goto L_0052c044;
    }
    // 0x0052c05c
    charge(ctx, 5);
    t7 = 0x40160000;
    t7 = t7 | 0xCBE3;
    t7 = slt(t7, s0);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = 0x43490000;
    if (!cc) {
        // 0x0052c070
        charge(ctx, 2);
        t6 = 0x3FC90000;
        if (i64(s2) <= 0) {
            // 0x0052c0ec
            charge(ctx, 9);
            t5 = 0x7C0000;
            t5 = addiu(t5, -16);  // &0x7BFFF0
            t7 = si(-16);
            lwc1(f0, t5, 0);  // 0x7BFFF0
            t7 = s0 & t7;
            t6 = t6 | 0xFD0;
            add_s(f1, f12, f0);
            mfc1(t5, f1);
            if (t7 == t6) {
                // 0x0052c138
                charge(ctx, 9);
                t7 = 0x7C0000;
                t6 = 0x7C0000;
                t7 = addiu(t7, -4);  // &0x7BFFFC
                t6 = addiu(t6, -8);  // &0x7BFFF8
                lwc1(f0, t7, 0);  // 0x7BFFFC
                lwc1(f2, t6, 0);  // 0x7BFFF8
                add_s(f1, f1, f0);
                mfc1(t5, f1);
                backedge(ctx);
            } else {
                // 0x0052c110
                charge(ctx, 3);
                t6 = 0x7C0000;
                t6 = addiu(t6, -12);  // &0x7BFFF4
                lwc1(f2, t6, 0);  // 0x7BFFF4
            }
            // 0x0052c11c
            charge(ctx, 7);
            add_s(f1, f1, f2);
            v0 = si(-1);
            mtc1(t5, f3);
            sub_s(f0, f3, f1);
            swc1(f1, s1, 0);
            add_s(f0, f0, f2);
            backedge(ctx);
        } else {
            // 0x0052c078
            charge(ctx, 9);
            t5 = 0x7C0000;
            t5 = addiu(t5, -16);  // &0x7BFFF0
            t7 = si(-16);
            lwc1(f0, t5, 0);  // 0x7BFFF0
            t7 = s0 & t7;
            t6 = t6 | 0xFD0;
            sub_s(f1, f12, f0);
            mfc1(t5, f1);
            if (t7 == t6) {
                // 0x0052c0c8
                charge(ctx, 9);
                t7 = 0x7C0000;
                t6 = 0x7C0000;
                t7 = addiu(t7, -4);  // &0x7BFFFC
                t6 = addiu(t6, -8);  // &0x7BFFF8
                lwc1(f0, t7, 0);  // 0x7BFFFC
                lwc1(f2, t6, 0);  // 0x7BFFF8
                sub_s(f1, f1, f0);
                mfc1(t5, f1);
                backedge(ctx);
            } else {
                // 0x0052c09c
                charge(ctx, 3);
                t6 = 0x7C0000;
                t6 = addiu(t6, -12);  // &0x7BFFF4
                lwc1(f2, t6, 0);  // 0x7BFFF4
            }
            // 0x0052c0a8
            charge(ctx, 6);
            sub_s(f1, f1, f2);
            v0 = 1;
            mtc1(t5, f3);
            sub_s(f0, f3, f1);
            swc1(f1, s1, 0);
            sub_s(f0, f0, f2);
        }
        goto L_0052c0c0;
    }
    // 0x0052c160
    charge(ctx, 4);
    t7 = t7 | 0xF80;
    t7 = slt(t7, s0);
    t6 = 0x7C0000;
    if (t7 == 0) {
        // 0x0052c170
        charge(ctx, 26);
        jal(ctx, 0x52C170u, gen::fn_fabsf_0052e788);
        mov_s(f4, f0);
        t5 = 0x7C0000;
        t5 = addiu(t5, 0);  // &0x7C0000
        t6 = 0x7C0000;
        t6 = addiu(t6, 4);  // &0x7C0004
        lwc1(f1, t6, 0);  // 0x7C0004
        lwc1(f0, t5, 0);  // 0x7C0000
        t6 = 0x7C0000;
        mul_s(f0, f4, f0);
        t5 = 0x7C0000;
        t5 = addiu(t5, -16);  // &0x7BFFF0
        t6 = addiu(t6, -12);  // &0x7BFFF4
        add_s(f0, f0, f1);
        cvt_w_s(f1, f0);
        mfc1(v0, f1);
        lwc1(f0, t5, 0);  // 0x7BFFF0
        mtc1(v0, f6);
        t7 = slti(v0, 32);
        lwc1(f1, t6, 0);  // 0x7BFFF4
        cvt_s_w(f6, f6);
        mul_s(f0, f6, f0);
        mul_s(f3, f6, f1);
        sub_s(f5, f4, f0);
        if (t7 == 0) {
            // 0x0052c228
            charge(ctx, 1);
            sub_s(f0, f5, f3);
        L_0052c22c:
            charge(ctx, 8);
            t5 = sra(s0, 23);
            mfc1(t7, f0);
            t7 = srl(t7, 23);
            t7 = t7 & 0xFF;
            t6 = subu(t5, t7);
            t6 = slti(t6, 9);
            swc1(f0, s1, 0);
            if (t6 != 0) {
                backedge(ctx);
            } else {
                // 0x0052c24c
                charge(ctx, 21);
                t7 = 0x7C0000;
                mov_s(f4, f5);
                t7 = addiu(t7, -4);  // &0x7BFFFC
                t6 = 0x7C0000;
                lwc1(f0, t7, 0);  // 0x7BFFFC
                t6 = addiu(t6, -8);  // &0x7BFFF8
                lwc1(f1, t6, 0);  // 0x7BFFF8
                mul_s(f3, f6, f0);
                mul_s(f1, f6, f1);
                sub_s(f5, f5, f3);
                sub_s(f0, f4, f5);
                sub_s(f0, f0, f3);
                sub_s(f3, f1, f0);
                sub_s(f2, f5, f3);
                mfc1(t7, f2);
                t7 = srl(t7, 23);
                t7 = t7 & 0xFF;
                t6 = subu(t5, t7);
                t6 = slti(t6, 26);
                swc1(f2, s1, 0);
                if (t6 != 0) {
                    backedge(ctx);
                } else {
                    // 0x0052c2a0
                    charge(ctx, 16);
                    t7 = 0x7C0000;
                    mov_s(f4, f5);
                    t7 = addiu(t7, 8);  // &0x7C0008
                    t5 = 0x7C0000;
                    lwc1(f0, t7, 0);  // 0x7C0008
                    t5 = addiu(t5, 12);  // &0x7C000C
                    lwc1(f2, t5, 0);  // 0x7C000C
                    mul_s(f3, f6, f0);
                    mul_s(f2, f6, f2);
                    sub_s(f5, f5, f3);
                    sub_s(f0, f4, f5);
                    sub_s(f0, f0, f3);
                    sub_s(f3, f2, f0);
                    sub_s(f1, f5, f3);
                    swc1(f1, s1, 0);
                    backedge(ctx);
                }
            }
        } else {
            // 0x0052c1d8
            charge(ctx, 9);
            t7 = 0x7C0000;
            t5 = sll(v0, 2);
            t7 = addiu(t7, -184);  // &0x7BFF48
            t6 = si(-256);
            t5 = addu(t5, t7);
            t6 = s0 & t6;
            lw(t7, t5, -4);
            sub_s(f0, f5, f3);
            if (t6 == t7) {
                goto L_0052c22c;
            }
            // 0x0052c1fc
            charge(ctx, 1);
            swc1(f0, s1, 0);
        }
        // 0x0052c200
        charge(ctx, 5);
        lwc1(f1, s1, 0);
        sub_s(f0, f5, f1);
        sub_s(f0, f0, f3);
        swc1(f0, s1, 4);
        if (i64(s2) < 0) {
            // 0x0052c214
            charge(ctx, 2);
            neg_s(f1, f1);
            v0 = subu(0, v0);
            goto L_0052c21c;
        }
        backedge(ctx);
        goto L_0052c044;
    }
    // 0x0052c2e0
    charge(ctx, 8);
    t7 = sra(s0, 23);
    t6 = addiu(t6, 16);
    a2 = addiu(t7, -134);
    lwc1(f2, t6, 0);
    t7 = sll(a2, 23);
    t4 = sp;
    t5 = subu(s0, t7);
    t6 = 1;
    for (;;) {
        // 0x0052c300
        charge(ctx, 13);
        mtc1(t5, f0);
        t6 = addiu(t6, -1);
        mtc1(t5, f3);
        cvt_w_s(f1, f0);
        mfc1(t7, f1);
        mtc1(t7, f0);
        cvt_s_w(f0, f0);
        sub_s(f1, f3, f0);
        swc1(f0, t4, 0);
        t4 = addiu(t4, 4);
        mul_s(f1, f1, f2);
        mfc1(t5, f1);
        if (i64(t6) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0052c334
    charge(ctx, 6);
    mtc1(zero, f1);
    a3 = 3;
    mtc1(t5, f0);
    c_eq_s(f0, f1);
    sw(t5, sp, 0x8);
    if (cond(ctx)) {
        // 0x0052c34c
        charge(ctx, 1);
        t7 = addiu(sp, 0x8);
        for (;;) {
            // 0x0052c350
            charge(ctx, 5);
            t7 = addiu(t7, -4);
            lwc1(f0, t7, 0);
            c_eq_s(f0, f1);
            a3 = addiu(a3, -1);
            if (!cond(ctx)) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0052c364
    charge(ctx, 8);
    t1 = 0x7C0000;
    a0 = sp;
    t1 = addiu(t1, -976);  // &0x7BFC30
    a1 = s1;
    t0 = 2;
    jal(ctx, 0x52C374u, gen::fn___kernel_rem_pio2f_0052d428);
    ld(s0, sp, 0x10);
    if (i64(s2) >= 0) {
        backedge(ctx);
    } else {
        // 0x0052c384
        charge(ctx, 5);
        lwc1(f1, s1, 0);
        v0 = subu(0, v0);
        lwc1(f0, s1, 4);
        neg_s(f1, f1);
        backedge(ctx);
    L_0052c21c:
        charge(ctx, 3);
        neg_s(f0, f0);
        swc1(f1, s1, 0);
        backedge(ctx);
    L_0052c0c0:
        charge(ctx, 2);
        swc1(f0, s1, 4);
        backedge(ctx);
    L_0052c044:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0052c048 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0052C398 __ieee754_sqrtf -- 220 bytes; leaf frame (no stack)
// __ieee754_sqrtf(x $f12) -> $f0: sqrt.s on the EE FPU (the hardware square root, which takes |x| on the R5900).
void __ieee754_sqrtf(EEContext& ctx) {
    using namespace hg;
    Gpr t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0052c398
    enter(ctx, 9);  // entry check point + this block's cycles
    t7 = 0x7FFF0000;
    mfc1(t6, f12);
    t7 = t7 | 0xFFFF;
    t4 = 0x7F0000;
    t7 = t6 & t7;
    t4 = t4 | 0xFFFF;  // &0x7FFFFF
    t7 = sltu(t4, t7);
    mfc1(t5, f12);
    if (t7 != 0) {
        // 0x0052c3bc
        charge(ctx, 2);
        if (i64(t6) >= 0) {
            t1 = sra(t6, 23);
            // 0x0052c3e0
            charge(ctx, 11);
            t1 = addiu(t1, -127);
            t7 = t6 & t4;
            t5 = t1 & 0x1;
            t6 = 0x800000;
            t1 = sra(t1, 1);
            t6 = t7 | t6;
            t3 = 0;
            t6 = sllv(t6, t5);
            t2 = 0;
            t6 = sll(t6, 1);
            t4 = 0x1000000;
            for (;;) {
                // 0x0052c40c
                charge(ctx, 4);
                t5 = addu(t3, t4);
                t7 = slt(t6, t5);
                if (t7 != 0) {
                    t4 = srl(t4, 1);
                } else {
                    // 0x0052c41c
                    charge(ctx, 4);
                    t6 = subu(t6, t5);
                    t3 = addu(t5, t4);
                    t2 = addu(t2, t4);
                    t4 = srl(t4, 1);
                }
                // 0x0052c42c
                charge(ctx, 2);
                t6 = sll(t6, 1);
                if (t4 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052c434
            charge(ctx, 2);
            t7 = sra(t2, 1);
            if (t6 != 0) {
                // 0x0052c43c
                charge(ctx, 6);
                t7 = 0x7C0000;
                t7 = addiu(t7, 32);  // &0x7C0020
                lwc1(f0, t7, 0);  // 0x7C0020
                c_le_s(f0, f0);
                if (!cond(ctx)) {
                    t7 = sra(t2, 1);
                } else {
                    // 0x0052c454
                    charge(ctx, 3);
                    t7 = t2 & 0x1;
                    t2 = addu(t2, t7);
                    t7 = sra(t2, 1);
                }
            }
            // 0x0052c460
            charge(ctx, 5);
            t6 = 0x3F000000;
            t6 = addu(t7, t6);
            t5 = sll(t1, 23);
            t5 = addu(t6, t5);
            backedge(ctx);
        } else {
            // 0x0052c3c4
            charge(ctx, 5);
            sub_s(f0, f12, f12);
            div_s(f0, f0, f0);
            mfc1(t5, f0);
        }
    }
    // 0x0052c3d8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    mtc1(t5, f0);
}

// 0x0052C478 __kernel_cos -- 600 bytes; frame 0x40: s1 sp+0x8, s3 sp+0x18, s6 sp+0x30, s0 sp+0x0, s2 sp+0x10, s4 sp+0x20, s5 sp+0x28, ra sp+0x38
// __kernel_cos(x $a0, y $a1) -> $v0: cos(x + y) for |x| <= pi/4 in double precision (soft-float): 1 - x^2/2 +
// x^4*C(x^2) with the tail correction for y; tiny x returns 1 (dptoli(x) == 0 test).
void __kernel_cos(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052c478
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t7 = 0x7FFF0000;
    sd(s1, sp, 0x8);
    t7 = t7 | 0xFFFF;
    sd(s3, sp, 0x18);
    t6 = 0x3E3F0000;
    sd(s6, sp, 0x30);
    s1 = dsra32(a0, 0);
    s1 = s1 & t7;
    sd(s0, sp, 0x0);
    t6 = t6 | 0xFFFF;
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    s3 = a0;
    sd(s5, sp, 0x28);
    sd(ra, sp, 0x38);
    t6 = slt(t6, s1);
    s6 = a1;
    if (t6 == 0) {
        // 0x0052c4c4
        charge(ctx, 5);
        jal(ctx, 0x52C4C4u, gen::fn_dptoli_005317d0);
        t7 = 1023;
        t7 = dsll32(t7, 20);
        if (v0 != 0) {
            goto L_0052c4d8;
        }
        // 0x0052c5f8 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(s0, sp, 0x0);
        v0 = t7;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0052c4d8:
    charge(ctx, 48);
    a0 = s3;
    a1 = s3;
    jal(ctx, 0x52C4DCu, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    s0 = v0;
    ld(a1, t7, 96);  // 0x7C0060
    a0 = v0;
    jal(ctx, 0x52C4F0u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52C500u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 104);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s0;
    jal(ctx, 0x52C50Cu, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52C51Cu);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 112);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s0;
    jal(ctx, 0x52C528u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52C538u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 120);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s0;
    jal(ctx, 0x52C544u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52C554u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 128);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s0;
    jal(ctx, 0x52C560u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52C570u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 136);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s0;
    jal(ctx, 0x52C57Cu, gen::fn_dpmul_00531230);
    t7 = 0x3FD30000;
    t7 = t7 | 0x3332;
    t7 = slt(t7, s1);
    s4 = v0;
    if (t7 != 0) {
        // 0x0052c624
        charge(ctx, 5);
        s2 = 8169;
        t7 = 0x3FE90000;
        t7 = slt(t7, s1);
        s2 = dsll32(s2, 17);
        if (t7 == 0) {
            // 0x0052c638
            charge(ctx, 9);
            t7 = lui(0xFFE0);
            s5 = dsll32(s5, 0);
            t7 = addu(s1, t7);
            s5 = dsrl32(s5, 0);
            t7 = dsll32(t7, 0);
            t6 = si(-1);
            s5 = s5 | t7;
            t6 = dsll32(t6, 0);
            s2 = s5 & t6;
        }
        // 0x0052c65c
        charge(ctx, 29);
        a1 = 511;
        a0 = s0;
        a1 = dsll32(a1, 21);
        jal(ctx, 0x52C664u, gen::fn_dpmul_00531230);
        a1 = s2;
        a0 = v0;
        jal(ctx, 0x52C670u, gen::fn_dpsub_005311c8);
        a0 = 1023;
        a1 = s2;
        s1 = v0;
        a0 = dsll32(a0, 20);
        jal(ctx, 0x52C684u, gen::fn_dpsub_005311c8);
        a0 = s0;
        s2 = v0;
        a1 = s4;
        jal(ctx, 0x52C694u, gen::fn_dpmul_00531230);
        s0 = v0;
        a0 = s3;
        a1 = s6;
        jal(ctx, 0x52C6A4u, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x52C6B0u, gen::fn_dpsub_005311c8);
        a1 = v0;
        a0 = s1;
        jal(ctx, 0x52C6BCu, gen::fn_dpsub_005311c8);
        a1 = v0;
        a0 = s2;
        backedge(ctx);
    } else {
        // 0x0052c598
        charge(ctx, 21);
        a1 = 511;
        a0 = s0;
        a1 = dsll32(a1, 21);
        jal(ctx, 0x52C5A0u, gen::fn_dpmul_00531230);
        a0 = s0;
        s1 = v0;
        a1 = s4;
        jal(ctx, 0x52C5B0u, gen::fn_dpmul_00531230);
        s0 = v0;
        a0 = s3;
        a1 = s6;
        jal(ctx, 0x52C5C0u, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x52C5CCu, gen::fn_dpsub_005311c8);
        a1 = v0;
        a0 = s1;
        jal(ctx, 0x52C5D8u, gen::fn_dpsub_005311c8);
        a0 = 1023;
        a1 = v0;
        a0 = dsll32(a0, 20);
    }
    // 0x0052c5ec
    charge(ctx, 3);
    jal(ctx, 0x52C5ECu, gen::fn_dpsub_005311c8);
    t7 = v0;
    // 0x0052c5f8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s0, sp, 0x0);
    v0 = t7;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0052C6D0 __kernel_rem_pio2 -- 2616 bytes; frame 0x2C0: s0 sp+0x270, s1 sp+0x278, s2 sp+0x280, s3 sp+0x288, s4 sp+0x290, s5 sp+0x298, s6 sp+0x2A0, s7 sp+0x2A8, fp sp+0x2B0, ra sp+0x2B8
// __kernel_rem_pio2(x $a0, y $a1, e0 $a2, nx $a3, prec $t0, ipio2 $t1) -> $v0: the large-argument reduction x mod pi/2
// for huge doubles: x given as nx 24-bit pieces with exponent e0, the integer table of 2/pi digits (ipio2), products
// accumulated in doubles (litodp / dpmul / dpadd / dptoli / floor / scalbn), recomputed with more terms while
// precision is lost; writes the reduced value as 1-3 doubles at y and returns n mod 8.
void __kernel_rem_pio2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052c6d0
    enter(ctx, 29);  // entry check point + this block's cycles
    t5 = 24;
    t4 = addiu(a2, -3);
    div(t4, t5);
    sp = addiu(sp, -0x2C0);
    t7 = 0x7C0000;
    sd(s0, sp, 0x270);
    sd(s1, sp, 0x278);
    t7 = addiu(t7, 144);  // &0x7C0090
    sd(s2, sp, 0x280);
    t6 = sll(t0, 2);
    sd(s3, sp, 0x288);
    t6 = addu(t6, t7);
    sd(s4, sp, 0x290);
    a3 = addiu(a3, -1);
    sd(s5, sp, 0x298);
    sd(s6, sp, 0x2A0);
    sd(s7, sp, 0x2A8);
    sd(fp, sp, 0x2B0);
    sd(ra, sp, 0x2B8);
    sw(t0, sp, 0x238);
    lw(t6, t6, 0);
    sw(a3, sp, 0x240);
    sw(t6, sp, 0x248);
    t3 = addu(a3, t6);
    sw(a0, sp, 0x230);
    sw(a1, sp, 0x234);
    sw(t1, sp, 0x23C);
    if (t5 == 0) {
        brk(ctx, 0x52C740u, 0x7u);
    }
    // 0x0052c744
    charge(ctx, 10);
    mflo(t4);
    t7 = slti(t4, 0);
    if (t7 != 0) t4 = 0;
    mult(t5, t4, t5);
    sw(t4, sp, 0x244);
    t6 = subu(t4, a3);
    a2 = subu(a2, t5);
    a2 = addiu(a2, -24);
    sw(a2, sp, 0x250);
    if (i64(t3) >= 0) {
        // 0x0052c76c
        charge(ctx, 5);
        t7 = sll(t6, 2);
        s3 = t6;
        s2 = addiu(t3, 1);
        s0 = addu(t7, t1);
        s1 = addiu(sp, 0x50);
        for (;;) {
            // 0x0052c780
            charge(ctx, 2);
            v0 = 0;
            if (i64(s3) >= 0) {
                // 0x0052c788
                charge(ctx, 2);
                link(ctx, 0x52C788u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 0);
                call(ctx, gen::fn_litodp_00531720);
            }
            // 0x0052c790
            charge(ctx, 6);
            sd(v0, s1, 0);
            s2 = addiu(s2, -1);
            s0 = addiu(s0, 4);
            s3 = addiu(s3, 1);
            s1 = addiu(s1, 8);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0052c7a8
    charge(ctx, 5);
    lw(t5, sp, 0x248);
    s4 = 0;
    t5 = slti(t5, 0);
    sw(t5, sp, 0x258);
    if (t5 == 0) {
        // 0x0052c7bc
        charge(ctx, 6);
        lw(t6, sp, 0x240);
        s6 = addiu(sp, 0x190);
        t3 = slti(t6, 0);
        t7 = sll(t6, 3);
        sw(t3, sp, 0x260);
        s5 = addu(t7, sp);
        for (;;) {
            // 0x0052c7d4
            charge(ctx, 3);
            lw(t4, sp, 0x260);
            s2 = 0;
            if (t4 == 0) {
                // 0x0052c7e0
                charge(ctx, 5);
                lw(t5, sp, 0x240);
                s3 = s2;
                lw(s0, sp, 0x230);
                s1 = addiu(s5, 80);
                s2 = addiu(t5, 1);
                for (;;) {
                    // 0x0052c7f4
                    charge(ctx, 11);
                    ld(a0, s0, 0);
                    s2 = addiu(s2, -1);
                    ld(a1, s1, 0);
                    s0 = addiu(s0, 8);
                    jal(ctx, 0x52C800u, gen::fn_dpmul_00531230);
                    s1 = addiu(s1, -8);
                    a0 = s3;
                    a1 = v0;
                    jal(ctx, 0x52C810u, gen::fn_dpadd_00531170);
                    s3 = v0;
                    if (s2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0052c820
                charge(ctx, 1);
                s2 = v0;
            }
            // 0x0052c824
            charge(ctx, 7);
            sd(s2, s6, 0);
            s4 = addiu(s4, 1);
            lw(t6, sp, 0x248);
            s5 = addiu(s5, 8);
            t7 = slt(t6, s4);
            s6 = addiu(s6, 8);
            if (t7 != 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0052c840
    charge(ctx, 1);
    lw(s6, sp, 0x248);
    for (;;) {
        // 0x0052c844
        charge(ctx, 4);
        t7 = sll(s6, 3);
        a0 = addu(t7, sp);
        ld(s3, a0, 400);
        if (i64(s6) > 0) {
            // 0x0052c854
            charge(ctx, 3);
            s4 = s6;
            s1 = addiu(a0, 392);
            s2 = sp;
            for (;;) {
                // 0x0052c860
                charge(ctx, 27);
                a1 = 999;
                a0 = s3;
                a1 = dsll32(a1, 20);
                s4 = addiu(s4, -1);
                jal(ctx, 0x52C86Cu, gen::fn_dpmul_00531230);
                a0 = v0;
                jal(ctx, 0x52C874u, gen::fn_dptoli_005317d0);
                a0 = v0;
                jal(ctx, 0x52C87Cu, gen::fn_litodp_00531720);
                a1 = 1047;
                s0 = v0;
                a0 = v0;
                a1 = dsll32(a1, 20);
                jal(ctx, 0x52C890u, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x52C89Cu, gen::fn_dpsub_005311c8);
                a0 = v0;
                jal(ctx, 0x52C8A4u, gen::fn_dptoli_005317d0);
                ld(a0, s1, 0);
                a1 = s0;
                sw(v0, s2, 0);
                s1 = addiu(s1, -8);
                jal(ctx, 0x52C8B8u, gen::fn_dpadd_00531170);
                s2 = addiu(s2, 4);
                s3 = v0;
                if (i64(s4) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052c8cc
        charge(ctx, 29);
        lw(a1, sp, 0x250);
        a0 = s3;
        jal(ctx, 0x52C8D0u, gen::fn_scalbn_005237b0);
        a1 = 255;
        s3 = v0;
        a1 = dsll32(a1, 22);
        a0 = v0;
        jal(ctx, 0x52C8E4u, gen::fn_dpmul_00531230);
        a0 = v0;
        jal(ctx, 0x52C8ECu, gen::fn_floor_0052e148);
        a1 = 513;
        a0 = v0;
        a1 = dsll32(a1, 21);
        jal(ctx, 0x52C8FCu, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s3;
        jal(ctx, 0x52C908u, gen::fn_dpsub_005311c8);
        s3 = v0;
        a0 = v0;
        jal(ctx, 0x52C914u, gen::fn_dptoli_005317d0);
        sw(v0, sp, 0x24C);
        link(ctx, 0x52C920u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x24C);
        call(ctx, gen::fn_litodp_00531720);
        a0 = s3;
        a1 = v0;
        jal(ctx, 0x52C92Cu, gen::fn_dpsub_005311c8);
        lw(t7, sp, 0x250);
        s3 = v0;
        if (i64(t7) <= 0) {
            // 0x0052d0c4
            charge(ctx, 3);
            lw(t4, sp, 0x250);
            t5 = 2;
            if (t4 != 0) {
                // 0x0052d0e4
                charge(ctx, 9);
                a0 = 511;
                sw(t5, sp, 0x254);
                a1 = v0;
                a0 = dsll32(a0, 21);
                jal(ctx, 0x52D0F0u, gen::fn_dpcmp_005316d0);
                lw(t6, sp, 0x254);
                v0 = slt(0, v0);
                if (v0 != 0) t6 = 0;
                backedge(ctx);
            } else {
                // 0x0052d0d0
                charge(ctx, 5);
                t7 = sll(s6, 2);
                t7 = addu(t7, sp);
                lw(t6, t7, -4);
                t6 = sra(t6, 23);
                backedge(ctx);
            }
        } else {
            // 0x0052c940
            charge(ctx, 16);
            t4 = sll(s6, 2);
            lw(t3, sp, 0x250);
            t4 = addu(t4, sp);
            t7 = 24;
            lw(t6, t4, -4);
            t7 = subu(t7, t3);
            t5 = 23;
            s4 = srav(t6, t7);
            t5 = subu(t5, t3);
            lw(t3, sp, 0x24C);
            t7 = sllv(s4, t7);
            t6 = subu(t6, t7);
            t3 = addu(t3, s4);
            sw(t6, t4, -4);
            sw(t3, sp, 0x24C);
            t6 = srav(t6, t5);
        }
        // 0x0052c980
        charge(ctx, 4);
        sw(t6, sp, 0x254);
        lw(t7, sp, 0x254);
        lw(t3, sp, 0x24C);
        if (i64(t7) > 0) {
            // 0x0052c990
            charge(ctx, 4);
            s0 = 0;
            t3 = addiu(t3, 1);
            sw(t3, sp, 0x24C);
            if (i64(s6) > 0) {
                // 0x0052c9a0
                charge(ctx, 5);
                t3 = 0xFF0000;
                t2 = 0x1000000;
                t3 = t3 | 0xFFFF;  // &0xFFFFFF
                t5 = sp;
                t4 = s6;
                for (;;) {
                    // 0x0052c9b4
                    charge(ctx, 3);
                    lw(t6, t5, 0);
                    t7 = subu(t3, t6);
                    if (s0 == 0) {
                        // 0x0052c9c0
                        charge(ctx, 2);
                        t7 = subu(t2, t6);
                        if (t6 != 0) {
                            // 0x0052c9c8
                            charge(ctx, 1);
                            s0 = 1;
                            goto L_0052c9cc;
                        }
                        goto L_0052c9d0;
                    }
                L_0052c9cc:
                    charge(ctx, 1);
                    sw(t7, t5, 0);
                L_0052c9d0:
                    charge(ctx, 3);
                    t4 = addiu(t4, -1);
                    t5 = addiu(t5, 4);
                    if (t4 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052c9dc
            charge(ctx, 3);
            lw(t4, sp, 0x250);
            t7 = 1;
            if (i64(t4) > 0) {
                // 0x0052c9e8
                charge(ctx, 2);
                cc = t4 == t7;  // the condition, before the delay slot changes it
                t7 = 2;
                if (cc) {
                    // 0x0052d0b8
                    charge(ctx, 3);
                    t5 = sll(s6, 2);
                    t6 = 0x7F0000;
                    backedge(ctx);
                L_0052d0a0:
                    charge(ctx, 6);
                    t5 = addu(t5, sp);
                    t6 = t6 | 0xFFFF;
                    lw(t7, t5, -4);
                    t7 = t7 & t6;
                    sw(t7, t5, -4);
                    backedge(ctx);
                } else {
                    // 0x0052c9f0
                    charge(ctx, 2);
                    t5 = sll(s6, 2);
                    if (t4 == t7) {
                        // 0x0052d09c
                        charge(ctx, 1);
                        t6 = 0x3F0000;
                        goto L_0052d0a0;
                    }
                }
            }
            // 0x0052c9f8
            charge(ctx, 4);
            lw(t5, sp, 0x254);
            t7 = 2;
            a0 = s3;
            if (t5 == t7) {
                // 0x0052ca08
                charge(ctx, 7);
                s1 = 1023;
                a1 = s3;
                s1 = dsll32(s1, 20);
                a0 = s1;
                jal(ctx, 0x52CA14u, gen::fn_dpsub_005311c8);
                s3 = v0;
                if (s0 != 0) {
                    // 0x0052ca24
                    charge(ctx, 7);
                    lw(a1, sp, 0x250);
                    a0 = s1;
                    jal(ctx, 0x52CA28u, gen::fn_scalbn_005237b0);
                    a0 = s3;
                    a1 = v0;
                    jal(ctx, 0x52CA34u, gen::fn_dpsub_005311c8);
                    s3 = v0;
                }
                goto L_0052ca40;
            }
            goto L_0052ca44;
        }
    L_0052ca40:
        charge(ctx, 1);
        a0 = s3;
    L_0052ca44:
        charge(ctx, 4);
        a1 = 0;
        jal(ctx, 0x52CA44u, gen::fn_dpcmp_005316d0);
        a0 = s3;
        if (v0 == 0) {
            // 0x0052ca54
            charge(ctx, 5);
            lw(t3, sp, 0x248);
            s4 = addiu(s6, -1);
            t7 = slt(s4, t3);
            t6 = 0;
            if (t7 == 0) {
                // 0x0052ca68
                charge(ctx, 3);
                t7 = sll(s4, 2);
                t4 = t6;
                t5 = addu(t7, sp);
                for (;;) {
                    // 0x0052ca74
                    charge(ctx, 7);
                    lw(t7, t5, 0);
                    s4 = addiu(s4, -1);
                    t6 = slt(s4, t3);
                    t4 = t4 | t7;
                    t5 = addiu(t5, -4);
                    if (t6 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0052ca90
                charge(ctx, 2);
                sw(t3, sp, 0x248);
                t6 = t4;
            }
            // 0x0052ca98
            charge(ctx, 2);
            a0 = s3;
            if (t6 == 0) {
                // 0x0052caa0
                charge(ctx, 7);
                lw(t4, sp, 0x248);
                t7 = addiu(t4, -1);
                t7 = sll(t7, 2);
                t7 = addu(t7, sp);
                lw(t6, t7, 0);
                s0 = 1;
                if (t6 == 0) {
                    // 0x0052cabc
                    charge(ctx, 3);
                    t7 = sll(t4, 2);
                    t7 = addu(t7, sp);
                    t6 = addiu(t7, -4);
                    for (;;) {
                        // 0x0052cac8
                        charge(ctx, 7);
                        t6 = addiu(t6, -4);
                        lw(t7, t6, 0);
                        s0 = addiu(s0, 1);
                        if (t7 != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0052cae4
                charge(ctx, 5);
                s0 = addu(s6, s0);
                s4 = addiu(s6, 1);
                t7 = slt(s0, s4);
                sw(s0, sp, 0x25C);
                if (t7 == 0) {
                    // 0x0052caf8
                    charge(ctx, 19);
                    lw(t5, sp, 0x240);
                    t6 = sll(s4, 3);
                    lw(t3, sp, 0x244);
                    t7 = sll(t5, 3);
                    t7 = addu(t6, t7);
                    t5 = addu(t3, s4);
                    lw(t3, sp, 0x240);
                    t7 = addu(t7, sp);
                    t6 = addu(t6, sp);
                    s7 = addiu(t7, 80);
                    s6 = addiu(t6, 400);
                    t4 = addu(t3, s4);
                    lw(t6, sp, 0x23C);
                    t7 = slti(t3, 0);
                    t5 = sll(t5, 2);
                    sw(t7, sp, 0x260);
                    t4 = sll(t4, 3);
                    s5 = addu(t5, t6);
                    fp = addu(t4, sp);
                    for (;;) {
                        // 0x0052cb44
                        charge(ctx, 7);
                        lw(a0, s5, 0);
                        s2 = 0;
                        jal(ctx, 0x52CB48u, gen::fn_litodp_00531720);
                        sd(v0, s7, 0);
                        lw(t3, sp, 0x260);
                        if (t3 != 0) {
                            sd(s2, s6, 0);
                        } else {
                            // 0x0052cb60
                            charge(ctx, 5);
                            lw(t4, sp, 0x240);
                            s3 = s2;
                            lw(s0, sp, 0x230);
                            s1 = addiu(fp, 0x50);
                            s2 = addiu(t4, 1);
                            for (;;) {
                                // 0x0052cb74
                                charge(ctx, 11);
                                ld(a0, s0, 0);
                                s2 = addiu(s2, -1);
                                ld(a1, s1, 0);
                                s0 = addiu(s0, 8);
                                jal(ctx, 0x52CB80u, gen::fn_dpmul_00531230);
                                s1 = addiu(s1, -8);
                                a0 = s3;
                                a1 = v0;
                                jal(ctx, 0x52CB90u, gen::fn_dpadd_00531170);
                                s3 = v0;
                                if (s2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x0052cba0
                            charge(ctx, 2);
                            s2 = v0;
                            sd(s2, s6, 0);
                        }
                        // 0x0052cba8
                        charge(ctx, 8);
                        s4 = addiu(s4, 1);
                        lw(t5, sp, 0x25C);
                        s7 = addiu(s7, 8);
                        s5 = addiu(s5, 4);
                        s6 = addiu(s6, 8);
                        t7 = slt(t5, s4);
                        fp = addiu(fp, 0x8);
                        if (t7 != 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0052cbc8
                charge(ctx, 2);
                lw(s6, sp, 0x25C);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x0052cbd0
    charge(ctx, 4);
    a1 = 0;
    jal(ctx, 0x52CBD0u, gen::fn_dpcmp_005316d0);
    lw(t4, sp, 0x250);
    if (v0 != 0) {
        // 0x0052cfe8
        charge(ctx, 11);
        a0 = s3;
        s0 = 1047;
        a1 = subu(0, t4);
        s0 = dsll32(s0, 20);
        jal(ctx, 0x52CFF4u, gen::fn_scalbn_005237b0);
        s3 = v0;
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x52D004u, gen::fn_dpcmp_005316d0);
        if (i64(v0) > 0) {
            s0 = sll(s6, 2);
            // 0x0052d090
            charge(ctx, 3);
            a0 = s3;
            s0 = addu(s0, sp);
            backedge(ctx);
        } else {
            // 0x0052d014
            charge(ctx, 27);
            lw(t5, sp, 0x250);
            a1 = 999;
            a1 = dsll32(a1, 20);
            a0 = s3;
            t5 = addiu(t5, 24);
            s1 = sll(s6, 2);
            sw(t5, sp, 0x250);
            s1 = addu(s1, sp);
            s6 = addiu(s6, 1);
            jal(ctx, 0x52D034u, gen::fn_dpmul_00531230);
            a0 = v0;
            jal(ctx, 0x52D03Cu, gen::fn_dptoli_005317d0);
            a0 = v0;
            jal(ctx, 0x52D044u, gen::fn_litodp_00531720);
            a1 = s0;
            s2 = v0;
            a0 = v0;
            s0 = sll(s6, 2);
            jal(ctx, 0x52D058u, gen::fn_dpmul_00531230);
            s0 = addu(s0, sp);
            a1 = v0;
            a0 = s3;
            jal(ctx, 0x52D068u, gen::fn_dpsub_005311c8);
            a0 = v0;
            jal(ctx, 0x52D070u, gen::fn_dptoli_005317d0);
            sw(v0, s1, 0);
            a0 = s2;
        }
        // 0x0052d080
        charge(ctx, 4);
        jal(ctx, 0x52D080u, gen::fn_dptoli_005317d0);
        sw(v0, s0, 0);
        backedge(ctx);
    L_0052cc24:
        charge(ctx, 1);
        lw(a1, sp, 0x250);
    } else {
        // 0x0052cbe0
        charge(ctx, 9);
        lw(t6, sp, 0x250);
        s6 = addiu(s6, -1);
        t7 = sll(s6, 2);
        t6 = addiu(t6, -24);
        t7 = addu(t7, sp);
        sw(t6, sp, 0x250);
        lw(t6, t7, 0);
        if (t6 == 0) {
            // 0x0052cc04
            charge(ctx, 1);
            t6 = t7;
            for (;;) {
                // 0x0052cc08
                charge(ctx, 7);
                lw(t3, sp, 0x250);
                t6 = addiu(t6, -4);
                lw(t7, t6, 0);
                s6 = addiu(s6, -1);
                t3 = addiu(t3, -24);
                sw(t3, sp, 0x250);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            goto L_0052cc24;
        }
        lw(a1, sp, 0x250);
    }
    // 0x0052cc28
    charge(ctx, 6);
    a0 = 1023;
    a0 = dsll32(a0, 20);
    s4 = s6;
    jal(ctx, 0x52CC30u, gen::fn_scalbn_005237b0);
    s2 = v0;
    if (i64(s6) >= 0) {
        // 0x0052cc40
        charge(ctx, 5);
        t7 = sll(s6, 3);
        t6 = sll(s6, 2);
        t7 = addu(t7, sp);
        s1 = addu(t6, sp);
        s0 = addiu(t7, 400);
        for (;;) {
            // 0x0052cc54
            charge(ctx, 15);
            lw(a0, s1, 0);
            s4 = addiu(s4, -1);
            jal(ctx, 0x52CC58u, gen::fn_litodp_00531720);
            s1 = addiu(s1, -4);
            a0 = s2;
            a1 = v0;
            jal(ctx, 0x52CC68u, gen::fn_dpmul_00531230);
            sd(v0, s0, 0);
            a1 = 999;
            a0 = s2;
            a1 = dsll32(a1, 20);
            jal(ctx, 0x52CC7Cu, gen::fn_dpmul_00531230);
            s0 = addiu(s0, -8);
            s2 = v0;
            if (i64(s4) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0052cc90
        charge(ctx, 2);
        s4 = s6;
        if (i64(s6) >= 0) {
            // 0x0052cc98
            charge(ctx, 2);
            t7 = sll(s6, 3);
            fp = addu(t7, sp);
            for (;;) {
                // 0x0052cca0
                charge(ctx, 4);
                lw(t6, sp, 0x258);
                s2 = 0;
                s0 = 0;
                if (t6 != 0) {
                    // 0x0052cfe0
                    charge(ctx, 2);
                    s5 = subu(s6, s4);
                    backedge(ctx);
                } else {
                    // 0x0052ccb0
                    charge(ctx, 3);
                    s5 = subu(s6, s4);
                    s7 = s5;
                    if (i64(s5) >= 0) {
                        // 0x0052ccbc
                        charge(ctx, 4);
                        t7 = 0x7C0000;
                        s3 = addiu(fp, 0x190);
                        s1 = addiu(t7, 160);  // &0x7C00A0
                        ld(a0, s1, 0);  // 0x7C00A0
                        for (;;) {
                            // 0x0052cccc
                            charge(ctx, 13);
                            s0 = addiu(s0, 1);
                            ld(a1, s3, 0);
                            s1 = addiu(s1, 8);
                            jal(ctx, 0x52CCD4u, gen::fn_dpmul_00531230);
                            s3 = addiu(s3, 8);
                            a0 = s2;
                            a1 = v0;
                            jal(ctx, 0x52CCE4u, gen::fn_dpadd_00531170);
                            lw(t3, sp, 0x248);
                            s2 = v0;
                            t7 = slt(t3, s0);
                            t6 = slt(s7, s0);
                            if (t7 == 0) {
                                // 0x0052cd00
                                charge(ctx, 2);
                                if (t6 == 0) {
                                    ld(a0, s1, 0);
                                    backedge(ctx);
                                    continue;
                                }
                            }
                            break;
                        }
                    }
                }
                // 0x0052cd08
                charge(ctx, 6);
                t7 = sll(s5, 3);
                fp = addiu(fp, -0x8);
                t7 = addu(t7, sp);
                s4 = addiu(s4, -1);
                sd(s2, t7, 240);
                if (i64(s4) < 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0052cd20
    charge(ctx, 4);
    lw(t4, sp, 0x238);
    t7 = slti(t4, 3);
    lw(t5, sp, 0x238);
    if (t7 != 0) {
        // 0x0052cd30
        charge(ctx, 2);
        if (i64(t4) > 0) {
            s2 = 0;
            // 0x0052cdcc
            charge(ctx, 2);
            s4 = s6;
            if (i64(s6) >= 0) {
                // 0x0052cdd4
                charge(ctx, 3);
                t7 = sll(s6, 3);
                t7 = addu(t7, sp);
                s0 = addiu(t7, 240);
                for (;;) {
                    // 0x0052cde0
                    charge(ctx, 7);
                    ld(a1, s0, 0);
                    a0 = s2;
                    s4 = addiu(s4, -1);
                    jal(ctx, 0x52CDE8u, gen::fn_dpadd_00531170);
                    s0 = addiu(s0, -8);
                    s2 = v0;
                    if (i64(s4) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052cdfc
            charge(ctx, 3);
            lw(t3, sp, 0x254);
            v0 = s2;
            if (t3 != 0) {
                // 0x0052ce08
                charge(ctx, 3);
                a1 = s2;
                a0 = 0;
                jal(ctx, 0x52CE0Cu, gen::fn_dpsub_005311c8);
            }
            // 0x0052ce14
            charge(ctx, 7);
            ld(a0, sp, 0xF0);
            a1 = s2;
            lw(t4, sp, 0x234);
            link(ctx, 0x52CE20u);  // $ra first: the delay slot below depends on it
            sd(v0, t4, 0);
            call(ctx, gen::fn_dpsub_005311c8);
            s2 = v0;
            if (i64(s6) > 0) {
                // 0x0052ce30
                charge(ctx, 3);
                s3 = v0;
                s0 = s6;
                s2 = addiu(sp, 0xF8);
                for (;;) {
                    // 0x0052ce3c
                    charge(ctx, 7);
                    ld(a1, s2, 0);
                    a0 = s3;
                    s0 = addiu(s0, -1);
                    jal(ctx, 0x52CE44u, gen::fn_dpadd_00531170);
                    s2 = addiu(s2, 8);
                    s3 = v0;
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0052ce58
                charge(ctx, 1);
                s2 = v0;
            }
            // 0x0052ce5c
            charge(ctx, 3);
            lw(t5, sp, 0x254);
            v0 = s2;
            if (t5 != 0) {
                // 0x0052ce68
                charge(ctx, 3);
                a1 = s2;
                a0 = 0;
                jal(ctx, 0x52CE6Cu, gen::fn_dpsub_005311c8);
            }
            // 0x0052ce74
            charge(ctx, 3);
            lw(t6, sp, 0x234);
            sd(v0, t6, 8);
            backedge(ctx);
        } else {
            // 0x0052cd38
            charge(ctx, 2);
            s4 = s6;
            if (t4 == 0) {
                // 0x0052cd78
                charge(ctx, 2);
                s2 = 0;
                if (i64(s6) >= 0) {
                    // 0x0052cd80
                    charge(ctx, 3);
                    t7 = sll(s6, 3);
                    t7 = addu(t7, sp);
                    s0 = addiu(t7, 240);
                    for (;;) {
                        // 0x0052cd8c
                        charge(ctx, 7);
                        ld(a1, s0, 0);
                        a0 = s2;
                        s4 = addiu(s4, -1);
                        jal(ctx, 0x52CD94u, gen::fn_dpadd_00531170);
                        s0 = addiu(s0, -8);
                        s2 = v0;
                        if (i64(s4) < 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0052cda8
                charge(ctx, 3);
                lw(t6, sp, 0x254);
                v0 = s2;
                if (t6 != 0) {
                    // 0x0052cdb4
                    charge(ctx, 3);
                    a1 = s2;
                    a0 = 0;
                    jal(ctx, 0x52CDB8u, gen::fn_dpsub_005311c8);
                }
                // 0x0052cdc0
                charge(ctx, 3);
                lw(t7, sp, 0x234);
                sd(v0, t7, 0);
                backedge(ctx);
            }
        }
        goto L_0052cd40;
    }
    // 0x0052ce80
    charge(ctx, 3);
    t7 = 3;
    cc = t5 != t7;  // the condition, before the delay slot changes it
    lw(t7, sp, 0x24C);
    if (cc) {
        backedge(ctx);
    } else {
        // 0x0052ce8c
        charge(ctx, 2);
        s4 = s6;
        if (i64(s6) > 0) {
            // 0x0052ce94
            charge(ctx, 2);
            t7 = sll(s6, 3);
            s3 = addu(t7, sp);
            for (;;) {
                // 0x0052ce9c
                charge(ctx, 17);
                ld(s0, s3, 232);
                s4 = addiu(s4, -1);
                ld(s1, s3, 240);
                a0 = s0;
                a1 = s1;
                jal(ctx, 0x52CEACu, gen::fn_dpadd_00531170);
                s2 = v0;
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x52CEBCu, gen::fn_dpsub_005311c8);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x52CEC8u, gen::fn_dpadd_00531170);
                sd(v0, s3, 240);
                sd(s2, s3, 232);
                s3 = addiu(s3, -8);
                if (i64(s4) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052cee0
        charge(ctx, 3);
        t7 = slti(s6, 2);
        s4 = s6;
        if (t7 == 0) {
            // 0x0052ceec
            charge(ctx, 2);
            t7 = sll(s6, 3);
            s3 = addu(t7, sp);
            for (;;) {
                // 0x0052cef4
                charge(ctx, 18);
                ld(s0, s3, 232);
                s4 = addiu(s4, -1);
                ld(s1, s3, 240);
                a0 = s0;
                a1 = s1;
                jal(ctx, 0x52CF04u, gen::fn_dpadd_00531170);
                s2 = v0;
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x52CF14u, gen::fn_dpsub_005311c8);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x52CF20u, gen::fn_dpadd_00531170);
                sd(v0, s3, 240);
                t7 = slti(s4, 2);
                sd(s2, s3, 232);
                s3 = addiu(s3, -8);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052cf3c
        charge(ctx, 4);
        s4 = s6;
        t7 = slti(s6, 2);
        s2 = 0;
        if (t7 == 0) {
            // 0x0052cf4c
            charge(ctx, 3);
            t7 = sll(s6, 3);
            t7 = addu(t7, sp);
            s0 = addiu(t7, 240);
            for (;;) {
                // 0x0052cf58
                charge(ctx, 8);
                ld(a1, s0, 0);
                a0 = s2;
                s4 = addiu(s4, -1);
                jal(ctx, 0x52CF60u, gen::fn_dpadd_00531170);
                s0 = addiu(s0, -8);
                t7 = slti(s4, 2);
                s2 = v0;
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052cf78
        charge(ctx, 3);
        lw(t7, sp, 0x254);
        if (t7 != 0) {
            ld(a1, sp, 0xF0);
            // 0x0052cfa0
            charge(ctx, 16);
            s0 = 0;
            a0 = s0;
            jal(ctx, 0x52CFA4u, gen::fn_dpsub_005311c8);
            ld(a1, sp, 0xF8);
            a0 = s0;
            lw(t4, sp, 0x234);
            link(ctx, 0x52CFB8u);  // $ra first: the delay slot below depends on it
            sd(v0, t4, 0);
            call(ctx, gen::fn_dpsub_005311c8);
            lw(t5, sp, 0x234);
            a0 = s0;
            a1 = s2;
            link(ctx, 0x52CFCCu);  // $ra first: the delay slot below depends on it
            sd(v0, t5, 8);
            call(ctx, gen::fn_dpsub_005311c8);
            lw(t6, sp, 0x234);
            sd(v0, t6, 16);
            backedge(ctx);
        } else {
            // 0x0052cf84
            charge(ctx, 7);
            ld(t7, sp, 0xF0);
            ld(t6, sp, 0xF8);
            lw(t3, sp, 0x234);
            sd(s2, t3, 16);
            sd(t7, t3, 0);
            sd(t6, t3, 8);
            backedge(ctx);
        }
    L_0052cd40:
        charge(ctx, 1);
        lw(t7, sp, 0x24C);
    }
    // 0x0052cd44 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(s0, sp, 0x270);
    ld(s1, sp, 0x278);
    v0 = t7 & 0x7;
    ld(s2, sp, 0x280);
    ld(s3, sp, 0x288);
    ld(s4, sp, 0x290);
    ld(s5, sp, 0x298);
    ld(s6, sp, 0x2A0);
    ld(s7, sp, 0x2A8);
    ld(fp, sp, 0x2B0);
    ld(ra, sp, 0x2B8);
    sp = addiu(sp, 0x2C0);
}

// 0x0052D108 __kernel_sin -- 464 bytes; frame 0x40: s0 sp+0x0, s2 sp+0x10, s5 sp+0x28, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, ra sp+0x30
// __kernel_sin(x $a0, y $a1, iy $a2) -> $v0: sin(x + y) for |x| <= pi/4 in double precision: x + x^3*S(x^2), with the
// y correction when iy != 0; tiny x returns x.
void __kernel_sin(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052d108
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t7 = 0x7FFF0000;
    sd(s0, sp, 0x0);
    t7 = t7 | 0xFFFF;
    sd(s2, sp, 0x10);
    t6 = dsra32(a0, 0);
    sd(s5, sp, 0x28);
    t5 = 0x3E3F0000;
    t6 = t6 & t7;
    sd(s1, sp, 0x8);
    t5 = t5 | 0xFFFF;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    s2 = a0;
    sd(ra, sp, 0x30);
    t5 = slt(t5, t6);
    s5 = a1;
    s0 = a2;
    if (t5 == 0) {
        // 0x0052d154
        charge(ctx, 4);
        jal(ctx, 0x52D154u, gen::fn_dptoli_005317d0);
        t7 = s2;
        if (v0 != 0) {
            goto L_0052d164;
        }
        // 0x0052d238 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s0, sp, 0x0);
        v0 = t7;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_0052d164:
    charge(ctx, 39);
    a0 = s2;
    a1 = s2;
    jal(ctx, 0x52D168u, gen::fn_dpmul_00531230);
    s1 = v0;
    a0 = v0;
    a1 = s2;
    jal(ctx, 0x52D178u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = s1;
    ld(a1, t7, 312);  // 0x7C0138
    s4 = v0;
    jal(ctx, 0x52D18Cu, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52D19Cu);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 320);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s1;
    jal(ctx, 0x52D1A8u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52D1B8u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 328);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s1;
    jal(ctx, 0x52D1C4u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52D1D4u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 336);
    call(ctx, gen::fn_dpadd_00531170);
    a1 = v0;
    a0 = s1;
    jal(ctx, 0x52D1E0u, gen::fn_dpmul_00531230);
    t7 = 0x7C0000;
    a0 = v0;
    link(ctx, 0x52D1F0u);  // $ra first: the delay slot below depends on it
    ld(a1, t7, 344);
    call(ctx, gen::fn_dpadd_00531170);
    s3 = v0;
    if (s0 != 0) {
        // 0x0052d260
        charge(ctx, 30);
        a1 = 511;
        a0 = s5;
        a1 = dsll32(a1, 21);
        jal(ctx, 0x52D268u, gen::fn_dpmul_00531230);
        s0 = v0;
        a0 = s4;
        a1 = s3;
        jal(ctx, 0x52D278u, gen::fn_dpmul_00531230);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x52D284u, gen::fn_dpsub_005311c8);
        a1 = v0;
        a0 = s1;
        jal(ctx, 0x52D290u, gen::fn_dpmul_00531230);
        a0 = v0;
        a1 = s5;
        jal(ctx, 0x52D29Cu, gen::fn_dpsub_005311c8);
        t7 = 0x7C0000;
        s0 = v0;
        ld(a1, t7, 352);  // 0x7C0160
        a0 = s4;
        jal(ctx, 0x52D2B0u, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s0;
        jal(ctx, 0x52D2BCu, gen::fn_dpsub_005311c8);
        a1 = v0;
        a0 = s2;
        jal(ctx, 0x52D2C8u, gen::fn_dpsub_005311c8);
        t7 = v0;
        backedge(ctx);
    } else {
        // 0x0052d200
        charge(ctx, 14);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x52D204u, gen::fn_dpmul_00531230);
        t7 = 0x7C0000;
        a0 = v0;
        link(ctx, 0x52D214u);  // $ra first: the delay slot below depends on it
        ld(a1, t7, 352);
        call(ctx, gen::fn_dpadd_00531170);
        a0 = s4;
        a1 = v0;
        jal(ctx, 0x52D220u, gen::fn_dpmul_00531230);
        a1 = v0;
        a0 = s2;
        jal(ctx, 0x52D22Cu, gen::fn_dpadd_00531170);
        t7 = v0;
    }
    // 0x0052d238 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    v0 = t7;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0052D2D8 __kernel_cosf -- 332 bytes; leaf frame (no stack)
// __kernel_cosf(x $f12, y $f13) -> $f0: cos(x + y) for |x| <= pi/4 on the EE FPU (polynomial in x^2 with the 0.3 /
// 0.78125 split for 1 - x^2/2 accuracy; tiny x -> 1).
void __kernel_cosf(EEContext& ctx) {
    using namespace hg;
    Gpr t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0052d2d8
    enter(ctx, 10);  // entry check point + this block's cycles
    cvt_w_s(f0, f12);
    t7 = 0x7FFF0000;
    mfc1(t5, f12);
    t7 = t7 | 0xFFFF;
    t6 = 0x31FF0000;
    t6 = t6 | 0xFFFF;
    t5 = t5 & t7;
    t6 = slt(t6, t5);
    mfc1(t4, f0);
    if (t6 == 0) {
        // 0x0052d300
        charge(ctx, 4);
        t6 = 0x7C0000;
        t6 = addiu(t6, 388);  // &0x7C0184
        lwc1(f0, t6, 0);  // 0x7C0184
        if (t4 != 0) {
            goto L_0052d310;
        }
        // 0x0052d41c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0052d310:
    charge(ctx, 34);
    mul_s(f2, f12, f12);
    t6 = 0x7C0000;
    t6 = addiu(t6, 392);  // &0x7C0188
    t7 = 0x3E990000;
    lwc1(f0, t6, 0);  // 0x7C0188
    t7 = t7 | 0x9999;
    t7 = slt(t7, t5);
    mul_s(f0, f2, f0);
    t6 = 0x7C0000;
    t6 = addiu(t6, 396);  // &0x7C018C
    lwc1(f1, t6, 0);  // 0x7C018C
    add_s(f0, f0, f1);
    t6 = 0x7C0000;
    t6 = addiu(t6, 400);  // &0x7C0190
    mul_s(f0, f2, f0);
    lwc1(f1, t6, 0);  // 0x7C0190
    t6 = 0x7C0000;
    add_s(f0, f0, f1);
    t6 = addiu(t6, 404);  // &0x7C0194
    mul_s(f0, f2, f0);
    lwc1(f1, t6, 0);  // 0x7C0194
    t6 = 0x7C0000;
    add_s(f0, f0, f1);
    t6 = addiu(t6, 408);  // &0x7C0198
    mul_s(f0, f2, f0);
    lwc1(f1, t6, 0);  // 0x7C0198
    t6 = 0x7C0000;
    add_s(f0, f0, f1);
    t6 = addiu(t6, 412);  // &0x7C019C
    mul_s(f0, f2, f0);
    lwc1(f1, t6, 0);  // 0x7C019C
    add_s(f0, f0, f1);
    mul_s(f0, f2, f0);
    if (t7 == 0) {
        // 0x0052d398
        charge(ctx, 12);
        t7 = 0x7C0000;
        mula_s(f2, f0);
        t7 = addiu(t7, 416);  // &0x7C01A0
        msub_s(f1, f12, f13);
        lwc1(f0, t7, 0);  // 0x7C01A0
        t6 = 0x7C0000;
        t6 = addiu(t6, 388);  // &0x7C0184
        mul_s(f0, f2, f0);
        sub_s(f0, f0, f1);
        lwc1(f2, t6, 0);  // 0x7C0184
        sub_s(f0, f2, f0);
        return;
    }
    // 0x0052d3c8
    charge(ctx, 4);
    t7 = 0x3F480000;
    t7 = slt(t7, t5);
    t6 = 0x3E900000;
    if (t7 == 0) {
        // 0x0052d3d8
        charge(ctx, 2);
        t7 = lui(0xFF00);
        t6 = addu(t5, t7);
    }
    // 0x0052d3e0
    charge(ctx, 15);
    t7 = 0x7C0000;
    mula_s(f2, f0);
    t7 = addiu(t7, 416);  // &0x7C01A0
    mtc1(t6, f1);
    lwc1(f0, t7, 0);  // 0x7C01A0
    mtc1(t6, f3);
    mul_s(f0, f2, f0);
    t7 = 0x7C0000;
    t7 = addiu(t7, 388);  // &0x7C0184
    sub_s(f0, f0, f1);
    msub_s(f2, f12, f13);
    lwc1(f1, t7, 0);  // 0x7C0184
    sub_s(f0, f0, f2);
    sub_s(f1, f1, f3);
    sub_s(f0, f1, f0);
    // 0x0052d41c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0052D428 __kernel_rem_pio2f -- 2080 bytes; frame 0x1B0: s5 sp+0x178, s1 sp+0x158, s3 sp+0x168, s6 sp+0x180, s0 sp+0x150, s2 sp+0x160, s4 sp+0x170, s7 sp+0x188, fp sp+0x190, ra sp+0x198, f20 sp+0x1A0
// __kernel_rem_pio2f(x $a0, y $a1, e0 $a2, nx $a3, prec $t0, ipio2 $t1) -> $v0: the large-argument pi/2 reduction of
// __kernel_rem_pio2 in singles (8-bit pieces, scalbnf / floorf), the reduced value as floats at y, n mod 8 returned.
void __kernel_rem_pio2f(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0052d428
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    t7 = addiu(a2, -3);
    t5 = addiu(a2, 4);
    sd(s5, sp, 0x178);
    t6 = slti(t7, 0);
    sd(s1, sp, 0x158);
    if (t6 != 0) t7 = t5;
    sd(s3, sp, 0x168);
    s5 = sra(t7, 3);
    sd(s6, sp, 0x180);
    t7 = 0x7C0000;
    sd(s0, sp, 0x150);
    t5 = slti(s5, 0);
    sd(s2, sp, 0x160);
    t7 = addiu(t7, 424);  // &0x7C01A8
    sd(s4, sp, 0x170);
    sd(s7, sp, 0x188);
    t6 = sll(t0, 2);
    sd(fp, sp, 0x190);
    t6 = addu(t6, t7);
    sd(ra, sp, 0x198);
    if (t5 != 0) s5 = 0;
    swc1(f20, sp, 0x1A0);
    t7 = sll(s5, 3);
    s1 = addiu(a3, -1);
    sw(t0, sp, 0x144);
    lw(s0, t6, 0);
    a2 = subu(a2, t7);
    sw(a1, sp, 0x140);
    s6 = a0;
    sw(t1, sp, 0x148);
    s3 = addiu(a2, -8);
    t5 = addu(s1, s0);
    t6 = subu(s5, s1);
    if (i64(t5) >= 0) {
        // 0x0052d4b4
        charge(ctx, 5);
        t7 = sll(t6, 2);
        t4 = t6;
        t5 = addiu(t5, 1);
        t7 = addu(t7, t1);
        t6 = addiu(sp, 0x50);
        for (;;) {
            // 0x0052d4c8
            charge(ctx, 2);
            mtc1(zero, f0);
            if (i64(t4) >= 0) {
                // 0x0052d4d0
                charge(ctx, 2);
                lwc1(f0, t7, 0);
                cvt_s_w(f0, f0);
            }
            // 0x0052d4d8
            charge(ctx, 6);
            swc1(f0, t6, 0);
            t5 = addiu(t5, -1);
            t7 = addiu(t7, 4);
            t4 = addiu(t4, 1);
            t6 = addiu(t6, 4);
            if (t5 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0052d4f0
    charge(ctx, 4);
    t6 = slti(s0, 0);
    t1 = 0;
    sw(t6, sp, 0x14C);
    if (t6 == 0) {
        // 0x0052d500
        charge(ctx, 4);
        t7 = sll(s1, 2);
        a3 = slti(s1, 0);
        t4 = addu(t7, sp);
        t3 = addiu(sp, 0xF0);
        for (;;) {
            // 0x0052d510
            charge(ctx, 2);
            mtc1(zero, f2);
            if (a3 == 0) {
                // 0x0052d518
                charge(ctx, 3);
                t6 = addiu(t4, 80);
                t7 = s6;
                t5 = addiu(s1, 1);
                for (;;) {
                    // 0x0052d524
                    charge(ctx, 8);
                    lwc1(f0, t7, 0);
                    t5 = addiu(t5, -1);
                    lwc1(f1, t6, 0);
                    t7 = addiu(t7, 4);
                    mul_s(f0, f0, f1);
                    t6 = addiu(t6, -4);
                    add_s(f2, f2, f0);
                    if (t5 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052d544
            charge(ctx, 6);
            swc1(f2, t3, 0);
            t1 = addiu(t1, 1);
            t4 = addiu(t4, 4);
            t7 = slt(s0, t1);
            t3 = addiu(t3, 4);
            if (t7 != 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0052d55c
    charge(ctx, 1);
    s2 = s0;
    for (;;) {
        // 0x0052d560
        charge(ctx, 4);
        s4 = sll(s2, 2);
        t7 = addu(s4, sp);
        lwc1(f20, t7, 240);
        if (i64(s2) > 0) {
            // 0x0052d570
            charge(ctx, 9);
            t6 = 0x7C0000;
            t4 = s2;
            t6 = addiu(t6, 500);  // &0x7C01F4
            t5 = sp;
            lwc1(f4, t6, 0);  // 0x7C01F4
            t6 = addiu(t7, 236);
            t7 = 0x7C0000;
            t7 = addiu(t7, 504);  // &0x7C01F8
            lwc1(f3, t7, 0);  // 0x7C01F8
            for (;;) {
                // 0x0052d594
                charge(ctx, 16);
                mul_s(f0, f20, f4);
                t4 = addiu(t4, -1);
                lwc1(f1, t6, 0);
                t6 = addiu(t6, -4);
                cvt_w_s(f2, f0);
                mfc1(t7, f2);
                mtc1(t7, f2);
                cvt_s_w(f2, f2);
                mul_s(f0, f2, f3);
                sub_s(f0, f20, f0);
                cvt_w_s(f5, f0);
                add_s(f20, f1, f2);
                mfc1(t7, f5);
                sw(t7, t5, 0);
                t5 = addiu(t5, 4);
                if (i64(t4) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052d5d4
        charge(ctx, 21);
        mov_s(f12, f20);
        a0 = s3;
        fp = 0;
        jal(ctx, 0x52D5DCu, gen::fn_scalbnf_005239a8);
        t6 = 0x7C0000;
        mov_s(f20, f0);
        t6 = addiu(t6, 508);  // &0x7C01FC
        lwc1(f12, t6, 0);  // 0x7C01FC
        mul_s(f12, f0, f12);
        jal(ctx, 0x52D5F4u, gen::fn_floorf_0052e7a0);
        t7 = 0x7C0000;
        t7 = addiu(t7, 512);  // &0x7C0200
        lwc1(f1, t7, 0);  // 0x7C0200
        mul_s(f0, f0, f1);
        sub_s(f20, f20, f0);
        cvt_w_s(f0, f20);
        mfc1(s7, f0);
        mtc1(s7, f0);
        cvt_s_w(f0, f0);
        sub_s(f20, f20, f0);
        if (i64(s3) <= 0) {
            // 0x0052dc14
            charge(ctx, 2);
            t6 = 0x7C0000;
            if (s3 != 0) {
                // 0x0052dc2c
                charge(ctx, 5);
                t6 = addiu(t6, 516);
                lwc1(f0, t6, 0);
                c_le_s(f0, f20);
                if (cond(ctx)) {
                    fp = 0x2;
                    backedge(ctx);
                } else {
                    // 0x0052dc40
                    charge(ctx, 2);
                    backedge(ctx);
                }
            } else {
                // 0x0052dc1c
                charge(ctx, 4);
                t7 = addu(s4, sp);
                lw(t6, t7, -4);
                fp = sra(t6, 8);
                backedge(ctx);
            }
        } else {
            // 0x0052d628
            charge(ctx, 12);
            t4 = addu(s4, sp);
            t7 = 8;
            lw(t5, t4, -4);
            t7 = subu(t7, s3);
            t6 = 7;
            t1 = srav(t5, t7);
            t6 = subu(t6, s3);
            t7 = sllv(t1, t7);
            s7 = addu(s7, t1);
            t5 = subu(t5, t7);
            sw(t5, t4, -4);
            fp = srav(t5, t6);
        }
        // 0x0052d658
        charge(ctx, 2);
        if (i64(fp) <= 0) {
            mtc1(zero, f0);
        } else {
            // 0x0052d660
            charge(ctx, 3);
            s7 = addiu(s7, 1);
            t3 = 0;
            if (i64(s2) > 0) {
                // 0x0052d66c
                charge(ctx, 4);
                t1 = 256;
                t2 = 255;
                t5 = sp;
                t4 = s2;
                for (;;) {
                    // 0x0052d67c
                    charge(ctx, 3);
                    lw(t6, t5, 0);
                    t7 = subu(t2, t6);
                    if (t3 == 0) {
                        // 0x0052d688
                        charge(ctx, 2);
                        t7 = subu(t1, t6);
                        if (t6 != 0) {
                            // 0x0052d690
                            charge(ctx, 1);
                            t3 = 1;
                            goto L_0052d694;
                        }
                        goto L_0052d698;
                    }
                L_0052d694:
                    charge(ctx, 1);
                    sw(t7, t5, 0);
                L_0052d698:
                    charge(ctx, 3);
                    t4 = addiu(t4, -1);
                    t5 = addiu(t5, 4);
                    if (t4 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052d6a4
            charge(ctx, 2);
            t7 = 1;
            if (i64(s3) > 0) {
                // 0x0052d6ac
                charge(ctx, 2);
                if (s3 == t7) {
                    t6 = addu(s4, sp);
                    // 0x0052dc08
                    charge(ctx, 3);
                    lw(t7, t6, -4);
                    t7 = t7 & 0x7F;
                    backedge(ctx);
                L_0052dc00:
                    charge(ctx, 2);
                    sw(t7, t6, -4);
                    backedge(ctx);
                } else {
                    // 0x0052d6b4
                    charge(ctx, 3);
                    t7 = 2;
                    if (s3 == t7) {
                        t6 = addu(s4, sp);
                        // 0x0052dbf8
                        charge(ctx, 2);
                        lw(t7, t6, -4);
                        t7 = t7 & 0x3F;
                        goto L_0052dc00;
                    }
                }
            }
            // 0x0052d6c0
            charge(ctx, 3);
            t7 = 2;
            mtc1(zero, f0);
            if (fp == t7) {
                // 0x0052d6cc
                charge(ctx, 5);
                t7 = 0x7C0000;
                t7 = addiu(t7, 520);  // &0x7C0208
                lwc1(f12, t7, 0);  // 0x7C0208
                sub_s(f20, f12, f20);
                if (t3 != 0) {
                    // 0x0052d6e0
                    charge(ctx, 4);
                    a0 = s3;
                    jal(ctx, 0x52D6E0u, gen::fn_scalbnf_005239a8);
                    sub_s(f20, f20, f0);
                    mtc1(zero, f0);
                }
            }
        }
        // 0x0052d6f0
        charge(ctx, 3);
        c_eq_s(f20, f0);
        t1 = addiu(s2, -1);
        if (!cond(ctx)) {
            goto L_0052db68;
        }
        // 0x0052d6fc
        charge(ctx, 3);
        t7 = slt(t1, s0);
        t6 = 0;
        if (t7 == 0) {
            // 0x0052d708
            charge(ctx, 3);
            t7 = sll(t1, 2);
            t5 = t6;
            t4 = addu(t7, sp);
            for (;;) {
                // 0x0052d714
                charge(ctx, 7);
                lw(t7, t4, 0);
                t1 = addiu(t1, -1);
                t6 = slt(t1, s0);
                t5 = t5 | t7;
                t4 = addiu(t4, -4);
                if (t6 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052d730
            charge(ctx, 1);
            t6 = t5;
        }
        // 0x0052d734
        charge(ctx, 2);
        mtc1(zero, f0);
        if (t6 != 0) {
            break;
        }
        // 0x0052d73c
        charge(ctx, 6);
        t7 = addiu(s0, -1);
        t7 = sll(t7, 2);
        t7 = addu(t7, sp);
        lw(t6, t7, 0);
        t4 = 1;
        if (t6 == 0) {
            // 0x0052d754
            charge(ctx, 3);
            t7 = sll(s0, 2);
            t7 = addu(t7, sp);
            t6 = addiu(t7, -4);
            for (;;) {
                // 0x0052d760
                charge(ctx, 7);
                t6 = addiu(t6, -4);
                lw(t7, t6, 0);
                t4 = addiu(t4, 1);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052d77c
        charge(ctx, 5);
        a2 = addu(s2, t4);
        t1 = addiu(s2, 1);
        t7 = slt(a2, t1);
        s2 = a2;
        if (t7 != 0) {
            backedge(ctx);
        } else {
            // 0x0052d790
            charge(ctx, 15);
            t6 = sll(t1, 2);
            t7 = sll(s1, 2);
            t7 = addu(t6, t7);
            t5 = addu(s5, t1);
            t7 = addu(t7, sp);
            t4 = addu(s1, t1);
            t0 = addiu(t7, 80);
            t5 = sll(t5, 2);
            lw(t7, sp, 0x148);
            t4 = sll(t4, 2);
            t6 = addu(t6, sp);
            t4 = addu(t4, sp);
            t6 = addiu(t6, 240);
            t5 = addu(t5, t7);
            a3 = slti(s1, 0);
            for (;;) {
                // 0x0052d7cc
                charge(ctx, 5);
                lwc1(f0, t5, 0);
                mtc1(zero, f2);
                cvt_s_w(f0, f0);
                swc1(f0, t0, 0);
                if (a3 == 0) {
                    // 0x0052d7e0
                    charge(ctx, 3);
                    t3 = addiu(t4, 80);
                    t7 = s6;
                    t2 = addiu(s1, 1);
                    for (;;) {
                        // 0x0052d7ec
                        charge(ctx, 8);
                        lwc1(f0, t7, 0);
                        t2 = addiu(t2, -1);
                        lwc1(f1, t3, 0);
                        t7 = addiu(t7, 4);
                        mul_s(f0, f0, f1);
                        t3 = addiu(t3, -4);
                        add_s(f2, f2, f0);
                        if (t2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x0052d80c
                charge(ctx, 8);
                swc1(f2, t6, 0);
                t1 = addiu(t1, 1);
                t0 = addiu(t0, 4);
                t5 = addiu(t5, 4);
                t6 = addiu(t6, 4);
                t7 = slt(a2, t1);
                t4 = addiu(t4, 4);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0052d82c
            charge(ctx, 2);
            s2 = a2;
            backedge(ctx);
        }
    }
    // 0x0052d834
    charge(ctx, 3);
    c_eq_s(f20, f0);
    mov_s(f12, f20);
    if (!cond(ctx)) {
    L_0052db6c:
        charge(ctx, 8);
        a0 = subu(0, s3);
        jal(ctx, 0x52DB6Cu, gen::fn_scalbnf_005239a8);
        t6 = 0x7C0000;
        t6 = addiu(t6, 504);  // &0x7C01F8
        lwc1(f1, t6, 0);  // 0x7C01F8
        c_le_s(f1, f0);
        mov_s(f20, f0);
        if (!cond(ctx)) {
            // 0x0052dbe4
            charge(ctx, 5);
            cvt_w_s(f0, f0);
            t7 = addu(s4, sp);
            mfc1(t6, f0);
            sw(t6, t7, 0);
            backedge(ctx);
        } else {
            // 0x0052db8c
            charge(ctx, 22);
            t7 = 0x7C0000;
            t5 = addu(s4, sp);
            t7 = addiu(t7, 500);  // &0x7C01F4
            s2 = addiu(s2, 1);
            lwc1(f0, t7, 0);  // 0x7C01F4
            t6 = sll(s2, 2);
            t6 = addu(t6, sp);
            s3 = addiu(s3, 8);
            mul_s(f0, f20, f0);
            cvt_w_s(f2, f0);
            mfc1(t7, f2);
            mtc1(t7, f2);
            cvt_s_w(f2, f2);
            mul_s(f0, f2, f1);
            sub_s(f0, f20, f0);
            cvt_w_s(f1, f0);
            cvt_w_s(f0, f2);
            mfc1(t7, f1);
            sw(t7, t5, 0);
            mfc1(t7, f0);
            sw(t7, t6, 0);
            backedge(ctx);
        }
    } else {
        // 0x0052d840
        charge(ctx, 6);
        s2 = addiu(s2, -1);
        t7 = sll(s2, 2);
        t7 = addu(t7, sp);
        lw(t6, t7, 0);
        s3 = addiu(s3, -8);
        if (t6 == 0) {
            // 0x0052d858
            charge(ctx, 1);
            t6 = t7;
            for (;;) {
                // 0x0052d85c
                charge(ctx, 7);
                t6 = addiu(t6, -4);
                s2 = addiu(s2, -1);
                lw(t7, t6, 0);
                s3 = addiu(s3, -8);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0052d878
    charge(ctx, 8);
    t6 = 0x7C0000;
    a0 = s3;
    t6 = addiu(t6, 520);  // &0x7C0208
    link(ctx, 0x52D884u);  // $ra first: the delay slot below depends on it
    lwc1(f12, t6, 0);
    call(ctx, gen::fn_scalbnf_005239a8);
    mov_s(f2, f0);
    t1 = s2;
    if (i64(s2) >= 0) {
        // 0x0052d898
        charge(ctx, 5);
        t6 = 0x7C0000;
        t7 = sll(s2, 2);
        t6 = addiu(t6, 500);  // &0x7C01F4
        t7 = addu(t7, sp);
        lwc1(f1, t6, 0);  // 0x7C01F4
        for (;;) {
            // 0x0052d8ac
            charge(ctx, 8);
            lwc1(f0, t7, 0);
            t1 = addiu(t1, -1);
            cvt_s_w(f0, f0);
            mul_s(f0, f2, f0);
            mul_s(f2, f2, f1);
            swc1(f0, t7, 240);
            t7 = addiu(t7, -4);
            if (i64(t1) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0052d8cc
        charge(ctx, 2);
        t1 = s2;
        if (i64(s2) >= 0) {
            // 0x0052d8d4
            charge(ctx, 4);
            t6 = sll(s2, 2);
            t7 = 0x7C0000;
            a2 = addiu(t7, 440);  // &0x7C01B8
            t6 = addu(t6, sp);
            for (;;) {
                // 0x0052d8e4
                charge(ctx, 4);
                mtc1(zero, f2);
                lw(t7, sp, 0x14C);
                t4 = 0;
                if (t7 != 0) {
                    // 0x0052db60
                    charge(ctx, 2);
                    t0 = subu(s2, t1);
                    backedge(ctx);
                } else {
                    // 0x0052d8f4
                    charge(ctx, 3);
                    t0 = subu(s2, t1);
                    a3 = t0;
                    if (i64(t0) >= 0) {
                        // 0x0052d900
                        charge(ctx, 3);
                        t3 = addiu(t6, 240);
                        t5 = a2;
                        lwc1(f0, t5, 0);
                        for (;;) {
                            // 0x0052d90c
                            charge(ctx, 9);
                            t4 = addiu(t4, 1);
                            lwc1(f1, t3, 0);
                            t2 = slt(a3, t4);
                            t5 = addiu(t5, 4);
                            t7 = slt(s0, t4);
                            mul_s(f0, f0, f1);
                            t3 = addiu(t3, 4);
                            add_s(f2, f2, f0);
                            if (t7 == 0) {
                                // 0x0052d930
                                charge(ctx, 2);
                                if (t2 == 0) {
                                    lwc1(f0, t5, 0);
                                    backedge(ctx);
                                    continue;
                                }
                            }
                            break;
                        }
                    }
                }
                // 0x0052d938
                charge(ctx, 6);
                t7 = sll(t0, 2);
                t6 = addiu(t6, -4);
                t7 = addu(t7, sp);
                t1 = addiu(t1, -1);
                swc1(f2, t7, 160);
                if (i64(t1) < 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0052d950
    charge(ctx, 4);
    lw(t6, sp, 0x144);
    t7 = slti(t6, 3);
    if (t7 != 0) {
        // 0x0052d960
        charge(ctx, 2);
        if (i64(t6) > 0) {
            mtc1(zero, f2);
            // 0x0052d9e8
            charge(ctx, 2);
            t1 = s2;
            if (i64(s2) >= 0) {
                // 0x0052d9f0
                charge(ctx, 3);
                t7 = sll(s2, 2);
                t7 = addu(t7, sp);
                t7 = addiu(t7, 160);
                for (;;) {
                    // 0x0052d9fc
                    charge(ctx, 5);
                    lwc1(f0, t7, 0);
                    t1 = addiu(t1, -1);
                    add_s(f2, f2, f0);
                    t7 = addiu(t7, -4);
                    if (i64(t1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052da10
            charge(ctx, 2);
            mov_s(f0, f2);
            if (fp != 0) {
                // 0x0052da18
                charge(ctx, 1);
                neg_s(f0, f2);
            }
            // 0x0052da1c
            charge(ctx, 5);
            lw(t6, sp, 0x140);
            swc1(f0, t6, 0);
            lwc1(f0, sp, 0xA0);
            sub_s(f2, f0, f2);
            if (i64(s2) > 0) {
                // 0x0052da30
                charge(ctx, 2);
                t6 = s2;
                t5 = addiu(sp, 0xA4);
                for (;;) {
                    // 0x0052da38
                    charge(ctx, 5);
                    lwc1(f0, t5, 0);
                    t6 = addiu(t6, -1);
                    add_s(f2, f2, f0);
                    t5 = addiu(t5, 4);
                    if (t6 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052da4c
            charge(ctx, 2);
            mov_s(f0, f2);
            if (fp != 0) {
                // 0x0052da54
                charge(ctx, 1);
                neg_s(f0, f2);
            }
            // 0x0052da58
            charge(ctx, 1);
            lw(t7, sp, 0x140);
            goto L_0052da5c;
        }
        // 0x0052d968
        charge(ctx, 2);
        if (t6 == 0) {
            mtc1(zero, f2);
            // 0x0052d9a8
            charge(ctx, 2);
            t1 = s2;
            if (i64(s2) >= 0) {
                // 0x0052d9b0
                charge(ctx, 3);
                t7 = sll(s2, 2);
                t7 = addu(t7, sp);
                t7 = addiu(t7, 160);
                for (;;) {
                    // 0x0052d9bc
                    charge(ctx, 5);
                    lwc1(f0, t7, 0);
                    t1 = addiu(t1, -1);
                    add_s(f2, f2, f0);
                    t7 = addiu(t7, -4);
                    if (i64(t1) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0052d9d0
            charge(ctx, 2);
            mov_s(f0, f2);
            if (fp != 0) {
                // 0x0052d9d8
                charge(ctx, 1);
                neg_s(f0, f2);
            }
            // 0x0052d9dc
            charge(ctx, 3);
            lw(t7, sp, 0x140);
            swc1(f0, t7, 0);
            backedge(ctx);
        }
        goto L_0052d970;
    }
    t7 = 3;
    // 0x0052da64
    charge(ctx, 2);
    v0 = s7 & 0x7;
    if (t6 != t7) {
        backedge(ctx);
    } else {
        // 0x0052da6c
        charge(ctx, 2);
        t1 = s2;
        if (i64(s2) > 0) {
            // 0x0052da74
            charge(ctx, 2);
            t7 = sll(s2, 2);
            t7 = addu(t7, sp);
            for (;;) {
                // 0x0052da7c
                charge(ctx, 10);
                lwc1(f0, t7, 156);
                t1 = addiu(t1, -1);
                lwc1(f1, t7, 160);
                add_s(f2, f0, f1);
                sub_s(f0, f0, f2);
                swc1(f2, t7, 156);
                add_s(f1, f1, f0);
                swc1(f1, t7, 160);
                t7 = addiu(t7, -4);
                if (i64(t1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052daa4
        charge(ctx, 3);
        t7 = slti(s2, 2);
        t1 = s2;
        if (t7 == 0) {
            // 0x0052dab0
            charge(ctx, 2);
            t7 = sll(s2, 2);
            t4 = addu(t7, sp);
            for (;;) {
                // 0x0052dab8
                charge(ctx, 11);
                lwc1(f1, t4, 156);
                t1 = addiu(t1, -1);
                lwc1(f0, t4, 160);
                t7 = slti(t1, 2);
                add_s(f2, f1, f0);
                sub_s(f1, f1, f2);
                swc1(f2, t4, 156);
                add_s(f0, f0, f1);
                swc1(f0, t4, 160);
                t4 = addiu(t4, -4);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052dae4
        charge(ctx, 4);
        mtc1(zero, f2);
        t7 = slti(s2, 2);
        t1 = s2;
        if (t7 == 0) {
            // 0x0052daf4
            charge(ctx, 3);
            t7 = sll(s2, 2);
            t7 = addu(t7, sp);
            t4 = addiu(t7, 160);
            for (;;) {
                // 0x0052db00
                charge(ctx, 6);
                lwc1(f0, t4, 0);
                t1 = addiu(t1, -1);
                t7 = slti(t1, 2);
                add_s(f2, f2, f0);
                t4 = addiu(t4, -4);
                if (t7 != 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0052db18
        charge(ctx, 2);
        lwc1(f1, sp, 0xA0);
        if (fp != 0) {
            // 0x0052db3c
            charge(ctx, 8);
            lwc1(f0, sp, 0xA4);
            neg_s(f2, f2);
            lw(t7, sp, 0x140);
            neg_s(f1, f1);
            neg_s(f0, f0);
            swc1(f2, t7, 8);
            swc1(f1, t7, 0);
            backedge(ctx);
        L_0052da5c:
            charge(ctx, 2);
            swc1(f0, t7, 4);
            backedge(ctx);
        } else {
            // 0x0052db20
            charge(ctx, 7);
            lw(t6, sp, 0x140);
            swc1(f2, t6, 8);
            lwc1(f0, sp, 0xA0);
            swc1(f0, t6, 0);
            lwc1(f1, sp, 0xA4);
            swc1(f1, t6, 4);
            backedge(ctx);
        }
    L_0052d970:
        charge(ctx, 1);
        v0 = s7 & 0x7;
    }
    // 0x0052d974 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(s0, sp, 0x150);
    ld(s1, sp, 0x158);
    ld(s2, sp, 0x160);
    ld(s3, sp, 0x168);
    ld(s4, sp, 0x170);
    ld(s5, sp, 0x178);
    ld(s6, sp, 0x180);
    ld(s7, sp, 0x188);
    ld(fp, sp, 0x190);
    ld(ra, sp, 0x198);
    lwc1(f20, sp, 0x1A0);
    sp = addiu(sp, 0x1B0);
    return;
L_0052db68:
    charge(ctx, 1);
    mov_s(f12, f20);
    goto L_0052db6c;
}

// 0x0052DC48 __kernel_sinf -- 244 bytes; leaf frame (no stack)
// __kernel_sinf(x $f12, y $f13, iy $a0) -> $f0: sin(x + y) for |x| <= pi/4 on the EE FPU (x + x^3*S(x^2), the y
// correction when iy != 0; tiny x -> x).
void __kernel_sinf(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0052dc48
    enter(ctx, 11);  // entry check point + this block's cycles
    cvt_w_s(f0, f12);
    t5 = 0x7FFF0000;
    mfc1(t7, f12);
    t5 = t5 | 0xFFFF;
    t6 = 0x31FF0000;
    t6 = t6 | 0xFFFF;
    t7 = t7 & t5;
    mfc1(t4, f0);
    t6 = slt(t6, t7);
    mov_s(f0, f12);
    if (t6 == 0) {
        // 0x0052dc74
        charge(ctx, 2);
        if (t4 != 0) {
            goto L_0052dc7c;
        }
        // 0x0052dd34 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0052dc7c:
    charge(ctx, 26);
    mul_s(f2, f12, f12);
    t7 = 0x7C0000;
    t7 = addiu(t7, 556);  // &0x7C022C
    lwc1(f0, t7, 0);  // 0x7C022C
    t7 = 0x7C0000;
    mul_s(f0, f2, f0);
    t7 = addiu(t7, 560);  // &0x7C0230
    mul_s(f3, f2, f12);
    lwc1(f1, t7, 0);  // 0x7C0230
    add_s(f0, f0, f1);
    t7 = 0x7C0000;
    t7 = addiu(t7, 564);  // &0x7C0234
    mul_s(f0, f2, f0);
    lwc1(f1, t7, 0);  // 0x7C0234
    t7 = 0x7C0000;
    add_s(f0, f0, f1);
    t7 = addiu(t7, 568);  // &0x7C0238
    mul_s(f0, f2, f0);
    lwc1(f1, t7, 0);  // 0x7C0238
    t7 = 0x7C0000;
    add_s(f0, f0, f1);
    t7 = addiu(t7, 572);  // &0x7C023C
    mul_s(f0, f2, f0);
    lwc1(f1, t7, 0);  // 0x7C023C
    add_s(f0, f0, f1);
    if (a0 == 0) {
        // 0x0052dce4
        charge(ctx, 8);
        mul_s(f0, f2, f0);
        t7 = 0x7C0000;
        t7 = addiu(t7, 576);  // &0x7C0240
        lwc1(f1, t7, 0);  // 0x7C0240
        add_s(f0, f0, f1);
        mul_s(f0, f3, f0);
        add_s(f0, f12, f0);
        return;
    }
    // 0x0052dd04
    charge(ctx, 12);
    t7 = 0x7C0000;
    t7 = addiu(t7, 580);  // &0x7C0244
    lwc1(f1, t7, 0);  // 0x7C0244
    mula_s(f13, f1);
    t7 = 0x7C0000;
    msub_s(f0, f3, f0);
    t7 = addiu(t7, 576);  // &0x7C0240
    lwc1(f1, t7, 0);  // 0x7C0240
    mul_s(f0, f2, f0);
    suba_s(f0, f13);
    msub_s(f0, f3, f1);
    sub_s(f0, f12, f0);
    // 0x0052dd34 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0052DD40 __kernel_tanf -- 760 bytes; frame 0x10: ra sp+0x0
// __kernel_tanf(x $f12, y $f13, k $a0) -> $f0: tan(x + y) (k = 1) or -1/tan(x + y) (k = -1) for |x| <= pi/4 on the EE
// FPU: |x| >= 0.6744 folds to pi/4 - x, then an odd polynomial, the -1/t case through a split division.
void __kernel_tanf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f13{ctx, 13};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052dd40
    enter(ctx, 11);  // entry check point + this block's cycles
    t6 = 0x7FFF0000;
    mfc1(t3, f12);
    sp = addiu(sp, -0x10);
    t6 = t6 | 0xFFFF;
    sd(ra, sp, 0x0);
    t7 = 0x317F0000;
    t5 = t3 & t6;
    t7 = t7 | 0xFFFF;
    t7 = slt(t7, t5);
    mov_s(f5, f12);
    if (t7 != 0) {
        // 0x0052dde8
        charge(ctx, 1);
        t7 = 0x3F2C0000;
    L_0052ddec:
        charge(ctx, 4);
        t7 = t7 | 0xA13F;
        t7 = slt(t7, t5);
        if (t7 == 0) {
            mul_s(f0, f5, f5);
        } else {
            // 0x0052ddfc
            charge(ctx, 2);
            t6 = 0x7C0000;
            if (i64(t3) < 0) {
                // 0x0052de04
                charge(ctx, 2);
                neg_s(f5, f5);
                neg_s(f13, f13);
            }
            // 0x0052de0c
            charge(ctx, 10);
            t7 = 0x7C0000;
            t6 = addiu(t6, 660);
            t7 = addiu(t7, 664);  // &0x7C0298
            lwc1(f0, t6, 0);
            lwc1(f1, t7, 0);  // 0x7C0298
            sub_s(f0, f0, f5);
            sub_s(f1, f1, f13);
            add_s(f5, f0, f1);
            mtc1(zero, f13);
            mul_s(f0, f5, f5);
        }
        // 0x0052de34
        charge(ctx, 83);
        t7 = 0x3F2C0000;
        t7 = t7 | 0xA13F;
        t7 = slt(t7, t5);
        t5 = 0x7C0000;
        mfc1(t4, f0);
        t5 = addiu(t5, 668);  // &0x7C029C
        mtc1(t4, f1);
        mul_s(f0, f0, f0);
        mul_s(f4, f1, f5);
        mfc1(t6, f0);
        lwc1(f0, t5, 0);  // 0x7C029C
        mtc1(t6, f1);
        t5 = 0x7C0000;
        mtc1(t6, f2);
        mul_s(f0, f1, f0);
        t5 = addiu(t5, 672);  // &0x7C02A0
        lwc1(f1, t5, 0);  // 0x7C02A0
        mul_s(f1, f2, f1);
        t5 = 0x7C0000;
        t5 = addiu(t5, 676);  // &0x7C02A4
        lwc1(f2, t5, 0);  // 0x7C02A4
        t5 = 0x7C0000;
        add_s(f0, f0, f2);
        t5 = addiu(t5, 680);  // &0x7C02A8
        lwc1(f3, t5, 0);  // 0x7C02A8
        add_s(f1, f1, f3);
        t5 = 0x7C0000;
        mtc1(t6, f2);
        t5 = addiu(t5, 684);  // &0x7C02AC
        mul_s(f0, f2, f0);
        mul_s(f1, f2, f1);
        lwc1(f2, t5, 0);  // 0x7C02AC
        t5 = 0x7C0000;
        add_s(f0, f0, f2);
        t5 = addiu(t5, 688);  // &0x7C02B0
        lwc1(f3, t5, 0);  // 0x7C02B0
        add_s(f1, f1, f3);
        t5 = 0x7C0000;
        mtc1(t6, f2);
        t5 = addiu(t5, 692);  // &0x7C02B4
        mul_s(f0, f2, f0);
        mul_s(f1, f2, f1);
        lwc1(f2, t5, 0);  // 0x7C02B4
        t5 = 0x7C0000;
        add_s(f0, f0, f2);
        t5 = addiu(t5, 696);  // &0x7C02B8
        lwc1(f3, t5, 0);  // 0x7C02B8
        add_s(f1, f1, f3);
        t5 = 0x7C0000;
        mtc1(t6, f2);
        t5 = addiu(t5, 700);  // &0x7C02BC
        mul_s(f0, f2, f0);
        mul_s(f1, f2, f1);
        lwc1(f2, t5, 0);  // 0x7C02BC
        t5 = 0x7C0000;
        add_s(f0, f0, f2);
        t5 = addiu(t5, 704);  // &0x7C02C0
        lwc1(f3, t5, 0);  // 0x7C02C0
        add_s(f1, f1, f3);
        t5 = 0x7C0000;
        mtc1(t6, f2);
        t5 = addiu(t5, 708);  // &0x7C02C4
        mul_s(f0, f2, f0);
        t6 = 0x7C0000;
        mul_s(f1, f2, f1);
        t6 = addiu(t6, 712);  // &0x7C02C8
        lwc1(f3, t6, 0);  // 0x7C02C8
        lwc1(f2, t5, 0);  // 0x7C02C4
        adda_s(f1, f3);
        add_s(f0, f0, f2);
        mtc1(t4, f1);
        t4 = 0x7C0000;
        madd_s(f0, f1, f0);
        t4 = addiu(t4, 716);  // &0x7C02CC
        mul_s(f0, f4, f0);
        add_s(f0, f0, f13);
        mul_s(f0, f1, f0);
        lwc1(f1, t4, 0);  // 0x7C02CC
        adda_s(f13, f0);
        madd_s(f3, f4, f1);
        add_s(f0, f5, f3);
        mfc1(t6, f0);
        if (t7 == 0) {
            // 0x0052dfd0
            charge(ctx, 3);
            t7 = 1;
            t4 = 0x7C0000;
            if (a0 == t7) {
                backedge(ctx);
            } else {
                // 0x0052dfdc
                charge(ctx, 23);
                t5 = si(-4096);
                t4 = addiu(t4, 656);
                lwc1(f2, t4, 0);
                div_s(f2, f2, f0);
                t4 = t6 & t5;
                mtc1(t4, f1);
                t4 = 0x7C0000;
                t4 = addiu(t4, 652);  // &0x7C028C
                sub_s(f0, f1, f5);
                mfc1(t7, f2);
                t6 = t7 & t5;
                sub_s(f12, f3, f0);
                mtc1(t6, f0);
                mul_s(f3, f0, f1);
                lwc1(f0, t4, 0);  // 0x7C028C
                adda_s(f3, f0);
                mtc1(t6, f0);
                madd_s(f1, f0, f12);
                mul_s(f2, f2, f1);
                add_s(f0, f0, f2);
                backedge(ctx);
            }
        } else {
            // 0x0052df80
            charge(ctx, 20);
            mtc1(a0, f12);
            t6 = sra(t3, 30);
            mov_s(f1, f0);
            t6 = t6 & 0x2;
            cvt_s_w(f12, f12);
            t7 = 1;
            t7 = subu(t7, t6);
            mtc1(t7, f2);
            mul_s(f0, f0, f0);
            add_s(f1, f1, f12);
            cvt_s_w(f2, f2);
            div_s(f0, f0, f1);
            sub_s(f0, f0, f3);
            sub_s(f0, f5, f0);
            add_s(f0, f0, f0);
            sub_s(f0, f12, f0);
            mul_s(f0, f2, f0);
            backedge(ctx);
        }
    L_0052ddb0:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x0052dd6c
        charge(ctx, 4);
        cvt_w_s(f0, f12);
        mfc1(t7, f0);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x3F2C0000;
        if (cc) {
            goto L_0052ddec;
        }
        // 0x0052dd7c
        charge(ctx, 4);
        t7 = addiu(a0, 1);
        t7 = t5 | t7;
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 1;
        if (!cc) {
            // 0x0052dd8c
            charge(ctx, 9);
            jal(ctx, 0x52DD8Cu, gen::fn_fabsf_0052e788);
            t4 = 0x7C0000;
            t4 = addiu(t4, 652);  // &0x7C028C
            lwc1(f1, t4, 0);  // 0x7C028C
            div_s(f0, f1, f0);
            goto L_0052ddb0;
        }
        // 0x0052ddbc
        charge(ctx, 2);
        t5 = 0x7C0000;
        if (a0 == t7) {
            // 0x0052dde0
            charge(ctx, 2);
            mov_s(f0, f12);
            backedge(ctx);
            goto L_0052ddb0;
        }
        // 0x0052ddc4
        charge(ctx, 7);
        t5 = addiu(t5, 656);
        lwc1(f0, t5, 0);
        div_s(f0, f0, f12);
        ld(ra, sp, 0x0);
        backedge(ctx);
    }
    // 0x0052ddb4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0052E148 floor -- 476 bytes; frame 0x30: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// floor(x $a0) -> $v0: the largest integral double <= x, by clearing the fraction bits below the binary point in the
// high or low word (the exponent decides which); a non-integral negative value first adds one unit at the binary
// point. The fdlibm-style 'huge + x > 0' inexact test runs on dpadd / dpcmp. NaN / Inf / already integral x return x.
void floor(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052e148
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a0;
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    s1 = dsra32(a0, 0);
    sd(s2, sp, 0x10);
    t6 = sra(s1, 20);
    sd(s3, sp, 0x18);
    t6 = t6 & 0x7FF;
    sd(s4, sp, 0x20);
    s2 = dsll32(a0, 0);
    sd(ra, sp, 0x28);
    s0 = addiu(t6, -1023);
    t7 = slti(s0, 20);
    s2 = dsra32(s2, 0);
    if (t7 != 0) {
        // 0x0052e188
        charge(ctx, 2);
        t6 = 0xF0000;
        if (i64(s0) < 0) {
            // 0x0052e190
            charge(ctx, 8);
            t7 = 0x7C0000;
            link(ctx, 0x52E194u);  // $ra first: the delay slot below depends on it
            ld(a1, t7, 728);
            call(ctx, gen::fn_dpadd_00531170);
            a1 = v0;
            a0 = 0;
            jal(ctx, 0x52E1A0u, gen::fn_dpcmp_005316d0);
            t7 = dsll32(s1, 0);
            if (i64(v0) < 0) {
                // 0x0052e1b0
                charge(ctx, 2);
                t7 = 0x7FFF0000;
                if (i64(s1) >= 0) {
                    // 0x0052e1b8
                    charge(ctx, 2);
                    s2 = 0;
                    s1 = 0;
                    goto L_0052e1c0;
                }
                // 0x0052e210
                charge(ctx, 5);
                t7 = t7 | 0xFFFF;
                t7 = s1 & t7;
                t7 = t7 | s2;
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = dsll32(s1, 0);
                if (!cc) {
                    // 0x0052e224
                    charge(ctx, 3);
                    s1 = lui(0xBFF0);
                    s2 = 0;
                    backedge(ctx);
                    goto L_0052e1c0;
                }
                backedge(ctx);
            }
            goto L_0052e1c4;
        }
        // 0x0052e230
        charge(ctx, 6);
        t6 = t6 | 0xFFFF;
        s4 = srav(t6, s0);
        t7 = s1 & s4;
        t7 = t7 | s2;
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 0x7C0000;
        if (!cc) {
            // 0x0052e248
            charge(ctx, 7);
            link(ctx, 0x52E248u);  // $ra first: the delay slot below depends on it
            ld(a1, t7, 728);
            call(ctx, gen::fn_dpadd_00531170);
            a1 = v0;
            a0 = 0;
            jal(ctx, 0x52E254u, gen::fn_dpcmp_005316d0);
            t7 = dsll32(s1, 0);
            if (i64(v0) < 0) {
                // 0x0052e264
                charge(ctx, 2);
                t7 = nor(0, s4);
                if (i64(s1) < 0) {
                    // 0x0052e26c
                    charge(ctx, 4);
                    t7 = 0x100000;
                    t7 = srav(t7, s0);
                    s1 = addu(s1, t7);
                    t7 = nor(0, s4);
                }
                // 0x0052e27c
                charge(ctx, 3);
                s2 = 0;
                s1 = s1 & t7;
                backedge(ctx);
                goto L_0052e1c0;
            }
            backedge(ctx);
            goto L_0052e1c4;
        }
        backedge(ctx);
        goto L_0052e1f0;
    }
    // 0x0052e288
    charge(ctx, 3);
    t7 = slti(s0, 52);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = addiu(t6, -1043);
    if (cc) {
        // 0x0052e2b0
        charge(ctx, 5);
        t6 = si(-1);
        s4 = srlv(t6, t7);
        t5 = s2 & s4;
        t7 = 0x7C0000;
        if (t5 == 0) {
            backedge(ctx);
        } else {
            // 0x0052e2c4
            charge(ctx, 7);
            link(ctx, 0x52E2C4u);  // $ra first: the delay slot below depends on it
            ld(a1, t7, 728);
            call(ctx, gen::fn_dpadd_00531170);
            a1 = v0;
            a0 = 0;
            jal(ctx, 0x52E2D0u, gen::fn_dpcmp_005316d0);
            t7 = dsll32(s1, 0);
            if (i64(v0) >= 0) {
                backedge(ctx);
            } else {
                // 0x0052e2e0
                charge(ctx, 2);
                t7 = nor(0, s4);
                if (i64(s1) < 0) {
                    // 0x0052e2e8
                    charge(ctx, 3);
                    t7 = 20;
                    cc = s0 != t7;  // the condition, before the delay slot changes it
                    t7 = 52;
                    if (cc) {
                        // 0x0052e304
                        charge(ctx, 8);
                        t6 = 1;
                        t7 = subu(t7, s0);
                        t6 = sllv(t6, t7);
                        t6 = addu(s2, t6);
                        t7 = sltu(t6, s2);
                        s1 = addu(s1, t7);
                        s2 = t6;
                        backedge(ctx);
                    } else {
                        // 0x0052e2f4
                        charge(ctx, 1);
                        s1 = addiu(s1, 1);
                    }
                    // 0x0052e2f8
                    charge(ctx, 1);
                    t7 = nor(0, s4);
                }
                // 0x0052e2fc
                charge(ctx, 2);
                s2 = s2 & t7;
                backedge(ctx);
            L_0052e1c0:
                charge(ctx, 1);
                t7 = dsll32(s1, 0);
            }
        L_0052e1c4:
            charge(ctx, 11);
            s3 = dsll32(s3, 0);
            t7 = dsrl32(t7, 0);
            s3 = dsrl32(s3, 0);
            t7 = dsll32(t7, 0);
            t6 = dsll32(s2, 0);
            s3 = s3 | t7;
            t6 = dsrl32(t6, 0);
            t7 = si(-1);
            t7 = dsll32(t7, 0);
            s3 = s3 & t7;
            v0 = s3 | t6;
        }
    L_0052e1f0:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        // 0x0052e294
        charge(ctx, 3);
        t7 = 1024;
        if (s0 != t7) {
            ld(s0, sp, 0x0);
            backedge(ctx);
        } else {
            // 0x0052e2a0
            charge(ctx, 4);
            a1 = a0;
            jal(ctx, 0x52E2A0u, gen::fn_dpadd_00531170);
            ld(s0, sp, 0x0);
            backedge(ctx);
        }
    }
    // 0x0052e1f4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0052E408 atanf -- 720 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// atanf(x $f12) -> $f0: arctangent on the EE FPU: |x| reduced to [0, 7/16), [7/16, 11/16) (atan 0.5), [11/16, 19/16)
// (atan 1), [19/16, 39/16) (atan 1.5) or beyond (atan inf = pi/2, -1/x) with the high / low atan tables at 0x7C02E0 /
// 0x7C02F0, then an odd polynomial in the reduced argument; the sign of x restored; |x| >= 2^26 returns +-pi/2, tiny x
// returns x.
void atanf(EEContext& ctx) {
    using namespace hg;
    Gpr t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052e408
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    t6 = 0x7FFF0000;
    sd(s0, sp, 0x0);
    t6 = t6 | 0xFFFF;
    mfc1(s1, f12);
    t7 = 0x507F0000;
    t7 = t7 | 0xFFFF;
    sd(ra, sp, 0x10);
    s0 = s1 & t6;
    t7 = slt(t7, s0);
    mov_s(f6, f12);
    if (t7 == 0) {
        // 0x0052e470
        charge(ctx, 5);
        t7 = 0x3EDF0000;
        t7 = t7 | 0xFFFF;
        t7 = slt(t7, s0);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x30FF0000;
        if (cc) {
            // 0x0052e5f8
            charge(ctx, 7);
            jal(ctx, 0x52E5F8u, gen::fn_fabsf_0052e788);
            t7 = 0x3F970000;
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            mov_s(f6, f0);
            if (t7 == 0) {
                // 0x0052e614
                charge(ctx, 5);
                t7 = 0x3F2F0000;
                t7 = t7 | 0xFFFF;
                t7 = slt(t7, s0);
                cc = t7 != 0;  // the condition, before the delay slot changes it
                t7 = 0x7C0000;
                if (cc) {
                    // 0x0052e664
                    charge(ctx, 6);
                    t6 = 1;
                    t7 = addiu(t7, 832);
                    lwc1(f0, t7, 0);
                    add_s(f1, f6, f0);
                    sub_s(f0, f6, f0);
                    backedge(ctx);
                } else {
                    // 0x0052e628
                    charge(ctx, 10);
                    t7 = 0x7C0000;
                    add_s(f0, f0, f0);
                    t7 = addiu(t7, 836);  // &0x7C0344
                    t6 = 0;
                    lwc1(f1, t7, 0);  // 0x7C0344
                    t7 = 0x7C0000;
                    add_s(f1, f6, f1);
                    t7 = addiu(t7, 832);  // &0x7C0340
                    lwc1(f2, t7, 0);  // 0x7C0340
                    sub_s(f0, f0, f2);
                }
                goto L_0052e650;
            }
            // 0x0052e67c
            charge(ctx, 5);
            t7 = 0x401B0000;
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0x7C0000;
            if (cc) {
                // 0x0052e6bc
                charge(ctx, 7);
                t7 = addiu(t7, 844);
                lwc1(f0, t7, 0);
                div_s(f6, f0, f6);
                t6 = 3;
                backedge(ctx);
            L_0052e4c0:
                charge(ctx, 1);
                mul_s(f5, f6, f6);
            } else {
                // 0x0052e690
                charge(ctx, 11);
                t7 = 0x7C0000;
                t6 = 2;
                t7 = addiu(t7, 840);  // &0x7C0348
                lwc1(f0, t7, 0);  // 0x7C0348
                t7 = 0x7C0000;
                mul_s(f1, f6, f0);
                t7 = addiu(t7, 832);  // &0x7C0340
                lwc1(f2, t7, 0);  // 0x7C0340
                sub_s(f0, f6, f0);
                add_s(f1, f1, f2);
                backedge(ctx);
            L_0052e650:
                charge(ctx, 5);
                div_s(f6, f0, f1);
                mul_s(f5, f6, f6);
                backedge(ctx);
            }
            // 0x0052e4c4
            charge(ctx, 55);
            t7 = 0x7C0000;
            t7 = addiu(t7, 848);  // &0x7C0350
            lwc1(f0, t7, 0);  // 0x7C0350
            mul_s(f4, f5, f5);
            t7 = 0x7C0000;
            t7 = addiu(t7, 852);  // &0x7C0354
            lwc1(f1, t7, 0);  // 0x7C0354
            mul_s(f0, f4, f0);
            t7 = 0x7C0000;
            t7 = addiu(t7, 856);  // &0x7C0358
            mul_s(f1, f4, f1);
            lwc1(f2, t7, 0);  // 0x7C0358
            t7 = 0x7C0000;
            add_s(f0, f0, f2);
            t7 = addiu(t7, 860);  // &0x7C035C
            lwc1(f3, t7, 0);  // 0x7C035C
            mul_s(f0, f4, f0);
            t7 = 0x7C0000;
            t7 = addiu(t7, 864);  // &0x7C0360
            add_s(f1, f1, f3);
            lwc1(f2, t7, 0);  // 0x7C0360
            t7 = 0x7C0000;
            add_s(f0, f0, f2);
            t7 = addiu(t7, 868);  // &0x7C0364
            mul_s(f1, f4, f1);
            lwc1(f3, t7, 0);  // 0x7C0364
            mul_s(f0, f4, f0);
            t7 = 0x7C0000;
            t7 = addiu(t7, 872);  // &0x7C0368
            add_s(f1, f1, f3);
            lwc1(f2, t7, 0);  // 0x7C0368
            t7 = 0x7C0000;
            add_s(f0, f0, f2);
            t7 = addiu(t7, 876);  // &0x7C036C
            mul_s(f1, f4, f1);
            lwc1(f3, t7, 0);  // 0x7C036C
            mul_s(f0, f4, f0);
            t7 = 0x7C0000;
            t7 = addiu(t7, 880);  // &0x7C0370
            add_s(f1, f1, f3);
            lwc1(f2, t7, 0);  // 0x7C0370
            t7 = 0x7C0000;
            add_s(f0, f0, f2);
            t7 = addiu(t7, 884);  // &0x7C0374
            mul_s(f1, f4, f1);
            lwc1(f3, t7, 0);  // 0x7C0374
            mul_s(f0, f4, f0);
            t7 = 0x7C0000;
            t7 = addiu(t7, 888);  // &0x7C0378
            add_s(f1, f1, f3);
            lwc1(f2, t7, 0);  // 0x7C0378
            add_s(f0, f0, f2);
            mul_s(f4, f4, f1);
            mul_s(f0, f5, f0);
            if (i64(t6) >= 0) {
                // 0x0052e5b0
                charge(ctx, 15);
                add_s(f0, f0, f4);
                t7 = 0x7C0000;
                t6 = sll(t6, 2);
                t7 = addiu(t7, 752);  // &0x7C02F0
                t7 = addu(t6, t7);
                lwc1(f2, t7, 0);
                mul_s(f0, f6, f0);
                t7 = 0x7C0000;
                t7 = addiu(t7, 736);  // &0x7C02E0
                t6 = addu(t6, t7);
                sub_s(f0, f0, f2);
                lwc1(f1, t6, 0);
                sub_s(f0, f0, f6);
                sub_s(f0, f1, f0);
                if (i64(s1) < 0) {
                    // 0x0052e5ec
                    charge(ctx, 1);
                    neg_s(f0, f0);
                }
                // 0x0052e5f0
                charge(ctx, 2);
                mov_s(f4, f0);
                backedge(ctx);
            } else {
                // 0x0052e5a0
                charge(ctx, 4);
                add_s(f0, f0, f4);
                mul_s(f0, f6, f0);
                sub_s(f4, f6, f0);
                backedge(ctx);
            }
        } else {
            // 0x0052e484
            charge(ctx, 4);
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            t6 = si(-1);
            if (t7 != 0) {
                goto L_0052e4c0;
            }
            // 0x0052e494
            charge(ctx, 10);
            t7 = 0x7C0000;
            t7 = addiu(t7, 828);  // &0x7C033C
            lwc1(f0, t7, 0);  // 0x7C033C
            t7 = 0x7C0000;
            add_s(f0, f12, f0);
            t7 = addiu(t7, 832);  // &0x7C0340
            lwc1(f1, t7, 0);  // 0x7C0340
            c_lt_s(f1, f0);
            mov_s(f4, f12);
            if (!cond(ctx)) {
                // 0x0052e4bc
                charge(ctx, 1);
                t6 = si(-1);
                goto L_0052e4c0;
            }
            backedge(ctx);
        }
    } else {
        // 0x0052e43c
        charge(ctx, 4);
        t7 = 0x7C0000;
        t7 = addiu(t7, 820);  // &0x7C0334
        lwc1(f4, t7, 0);  // 0x7C0334
        if (i64(s1) <= 0) {
            // 0x0052e44c
            charge(ctx, 3);
            t7 = 0x7C0000;
            t7 = addiu(t7, 824);  // &0x7C0338
            lwc1(f4, t7, 0);  // 0x7C0338
        }
    }
    // 0x0052e458 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    mov_s(f0, f4);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0052E6D8 cosf -- 176 bytes; frame 0x20: ra sp+0x10
// cosf(x $f12) -> $f0: |x| <= pi/4 -> __kernel_cosf(x, 0); otherwise __ieee754_rem_pio2f into y[2] on the stack and
// the quadrant n & 3 picks cos, -sin, -cos or sin of the reduced value (__kernel_cosf / __kernel_sinf).
void cosf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052e6d8
    enter(ctx, 11);  // entry check point + this block's cycles
    t5 = 0x7FFF0000;
    mfc1(t7, f12);
    sp = addiu(sp, -0x20);
    t5 = t5 | 0xFFFF;
    sd(ra, sp, 0x10);
    t6 = 0x3F490000;
    t7 = t7 & t5;
    t6 = t6 | 0xFD8;  // 0x3F490FD8: the bits of pi/4 (|x| compared as an integer)
    t6 = slt(t6, t7);
    mtc1(zero, f13);
    if (t6 != 0) {
        // 0x0052e704: |x| > pi/4: reduce into y[2] on the stack, n & 3 picks the quadrant
        charge(ctx, 6);
        a0 = sp;
        jal(ctx, 0x52E704u, gen::fn___ieee754_rem_pio2f_0052c000);
        v0 = v0 & 0x3;
        t7 = 1;
        cc = v0 == t7;  // the condition, before the delay slot changes it
        t7 = slti(v0, 2);
        if (!cc) {
            // 0x0052e71c
            charge(ctx, 2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 2;
            if (!cc) {
                // 0x0052e724
                charge(ctx, 2);
                lwc1(f12, sp, 0x0);
                if (v0 != 0) {
                    goto L_0052e72c;
                }
                // 0x0052e744: n == 0: cos(y)
                charge(ctx, 1);
                lwc1(f13, sp, 0x4);
                goto L_0052e748;
            }
            // 0x0052e758: n == 2: -cos(y); n == 3 below: sin(y)
            charge(ctx, 2);
            lwc1(f12, sp, 0x0);
            if (v0 != t7) {
                backedge(ctx);
            L_0052e72c:
                charge(ctx, 3);
                a0 = 1;
                link(ctx, 0x52E730u);  // $ra first: the delay slot below depends on it
                lwc1(f13, sp, 0x4);
                call(ctx, gen::fn___kernel_sinf_0052dc48);
            } else {
                // 0x0052e760: n == 2: -__kernel_cosf
                charge(ctx, 4);
                link(ctx, 0x52E760u);  // $ra first: the delay slot below depends on it
                lwc1(f13, sp, 0x4);
                call(ctx, gen::fn___kernel_cosf_0052d2d8);
                neg_s(f0, f0);
                backedge(ctx);
            }
            goto L_0052e738;
        }
        // 0x0052e770: n == 1: -sin(y)
        charge(ctx, 6);
        lwc1(f12, sp, 0x0);
        a0 = 1;
        link(ctx, 0x52E778u);  // $ra first: the delay slot below depends on it
        lwc1(f13, sp, 0x4);
        call(ctx, gen::fn___kernel_sinf_0052dc48);
        neg_s(f0, f0);
        backedge(ctx);
    L_0052e738:
        charge(ctx, 1);
        ld(ra, sp, 0x10);
        // 0x0052e73c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x20);
        return;
    }
L_0052e748:
    charge(ctx, 4);
    jal(ctx, 0x52E748u, gen::fn___kernel_cosf_0052d2d8);
    ld(ra, sp, 0x10);
    backedge(ctx);
    // 0x0052e73c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x0052E788 fabsf -- 24 bytes; leaf frame (no stack)
// fabsf(x $f12) -> $f0: |x| (abs.s).
void fabsf(EEContext& ctx) {
    using namespace hg;
    Gpr t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x0052e788
    enter(ctx, 6);  // entry check point + this block's cycles
    mfc1(t6, f12);
    t7 = 0x7FFF0000;
    t7 = t7 | 0xFFFF;
    t6 = t6 & t7;
    mtc1(t6, f0);
}

// 0x0052E7A0 floorf -- 212 bytes; leaf frame (no stack)
// floorf(x $f12) -> $f0: the largest integral float <= x by masking fraction bits of the bit pattern (|x| < 1: 0 or
// -1; integral, NaN-like or huge x returned unchanged; negative non-integral values add one unit of the kept part
// first). Integer arithmetic on the bits: the EE has no inexact flag to raise.
void floorf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0052e7a0
    enter(ctx, 10);  // entry check point + this block's cycles
    mfc1(t7, f12);
    t6 = 0x7FFF0000;
    t6 = t6 | 0xFFFF;
    t3 = t7 & t6;
    t4 = t7;
    t7 = srl(t3, 23);
    t5 = addiu(t7, -127);
    t6 = slti(t5, 23);
    mov_s(f0, f12);
    if (t6 == 0) {
        // 0x0052e800 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0052e7c8
    charge(ctx, 2);
    t7 = 0x7F0000;
    if (i64(t5) < 0) {
        // 0x0052e7d0
        charge(ctx, 8);
        t7 = 0x7C0000;
        mtc1(zero, f1);
        t7 = addiu(t7, 900);  // &0x7C0384
        lwc1(f0, t7, 0);  // 0x7C0384
        add_s(f0, f12, f0);
        c_lt_s(f1, f0);
        mtc1(t4, f0);
        if (!cond(ctx)) {
            // 0x0052e800 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        // 0x0052e7f0
        charge(ctx, 2);
        t7 = 0x7F0000;
        if (i64(t4) >= 0) {
            // 0x0052e7f8
            charge(ctx, 1);
            t4 = 0;
            goto L_0052e7fc;
        }
        // 0x0052e808
        charge(ctx, 4);
        t7 = t7 | 0xFFFF;
        t7 = sltu(t7, t3);
        if (t7 != 0) {
            t4 = lui(0xBF80);
            backedge(ctx);
            goto L_0052e7fc;
        }
        // 0x0052e818
        charge(ctx, 2);
        mtc1(t4, f0);
        return;
    }
    // 0x0052e820
    charge(ctx, 5);
    t7 = t7 | 0xFFFF;
    t3 = srav(t7, t5);
    t6 = t4 & t3;
    mov_s(f0, f12);
    if (t6 == 0) {
        backedge(ctx);
    } else {
        // 0x0052e834
        charge(ctx, 8);
        t7 = 0x7C0000;
        mtc1(zero, f1);
        t7 = addiu(t7, 900);  // &0x7C0384
        lwc1(f0, t7, 0);  // 0x7C0384
        add_s(f0, f12, f0);
        c_lt_s(f1, f0);
        mtc1(t4, f0);
        if (!cond(ctx)) {
            backedge(ctx);
        } else {
            // 0x0052e854
            charge(ctx, 2);
            t7 = nor(0, t3);
            if (i64(t4) < 0) {
                // 0x0052e85c
                charge(ctx, 4);
                t7 = 0x800000;
                t7 = srav(t7, t5);
                t4 = addu(t4, t7);
                t7 = nor(0, t3);
            }
            // 0x0052e86c
            charge(ctx, 2);
            t4 = t4 & t7;
            backedge(ctx);
        L_0052e7fc:
            charge(ctx, 1);
            mtc1(t4, f0);
        }
    }
    // 0x0052e800 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0052E878 sinf -- 184 bytes; frame 0x20: ra sp+0x10
// sinf(x $f12) -> $f0: |x| <= pi/4 -> __kernel_sinf(x, 0, 0); otherwise __ieee754_rem_pio2f and the quadrant selects
// sin, cos, -sin or -cos of the reduced value.
void sinf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052e878
    enter(ctx, 11);  // entry check point + this block's cycles
    t5 = 0x7FFF0000;
    mfc1(t7, f12);
    sp = addiu(sp, -0x20);
    t5 = t5 | 0xFFFF;
    t6 = 0x3F490000;
    sd(ra, sp, 0x10);
    t6 = t6 | 0xFD8;  // 0x3F490FD8: the bits of pi/4 (|x| compared as an integer)
    t7 = t7 & t5;
    t6 = slt(t6, t7);
    mtc1(zero, f13);
    if (t6 == 0) {
        // 0x0052e8a4: |x| <= pi/4: __kernel_sinf(x, 0, iy = 0)
        charge(ctx, 1);
        a0 = 0;
        goto L_0052e8a8;
    }
    // 0x0052e8bc: |x| > pi/4: reduce into y[2], n & 3 picks the quadrant
    charge(ctx, 6);
    a0 = sp;
    jal(ctx, 0x52E8BCu, gen::fn___ieee754_rem_pio2f_0052c000);
    v0 = v0 & 0x3;
    t7 = 1;
    cc = v0 == t7;  // the condition, before the delay slot changes it
    t7 = slti(v0, 2);
    if (cc) {
        // 0x0052e91c: n == 1: cos(y)
        charge(ctx, 5);
        lwc1(f12, sp, 0x0);
        link(ctx, 0x52E920u);  // $ra first: the delay slot below depends on it
        lwc1(f13, sp, 0x4);
        call(ctx, gen::fn___kernel_cosf_0052d2d8);
        ld(ra, sp, 0x10);
        backedge(ctx);
    } else {
        // 0x0052e8d4
        charge(ctx, 2);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 2;
        if (cc) {
            // 0x0052e900: n == 3: -cos(y), n == 2: -sin(y)
            charge(ctx, 2);
            lwc1(f12, sp, 0x0);
            if (v0 != t7) {
                backedge(ctx);
            L_0052e8e4:
                charge(ctx, 4);
                link(ctx, 0x52E8E4u);  // $ra first: the delay slot below depends on it
                lwc1(f13, sp, 0x4);
                call(ctx, gen::fn___kernel_cosf_0052d2d8);
                neg_s(f0, f0);
                backedge(ctx);
            } else {
                // 0x0052e908: n == 2: -__kernel_sinf(y, iy = 1)
                charge(ctx, 5);
                a0 = 1;
                link(ctx, 0x52E90Cu);  // $ra first: the delay slot below depends on it
                lwc1(f13, sp, 0x4);
                call(ctx, gen::fn___kernel_sinf_0052dc48);
                neg_s(f0, f0);
                backedge(ctx);
            }
        } else {
            // 0x0052e8dc: n == 0: sin(y) (iy = 1)
            charge(ctx, 2);
            lwc1(f12, sp, 0x0);
            if (v0 != 0) {
                goto L_0052e8e4;
            }
            // 0x0052e8f4
            charge(ctx, 3);
            a0 = 1;
            lwc1(f13, sp, 0x4);
            backedge(ctx);
        L_0052e8a8:
            charge(ctx, 2);
            jal(ctx, 0x52E8A8u, gen::fn___kernel_sinf_0052dc48);
        }
        // 0x0052e8b0
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    }
    // 0x0052e8b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x0052E930 tanf -- 108 bytes; frame 0x20: ra sp+0x10
// tanf(x $f12) -> $f0: __kernel_tanf(x, 0, 1) for |x| <= pi/4, else after __ieee754_rem_pio2f with k = 1 - 2*(n & 1)
// (tan or -1/tan of the reduced value).
void tanf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x0052e930
    enter(ctx, 11);  // entry check point + this block's cycles
    t5 = 0x7FFF0000;
    mfc1(t7, f12);
    sp = addiu(sp, -0x20);
    t5 = t5 | 0xFFFF;
    t6 = 0x3F490000;
    sd(ra, sp, 0x10);
    t6 = t6 | 0xFDA;  // 0x3F490FDA: the bits of pi/4 rounded up
    t7 = t7 & t5;
    t6 = slt(t6, t7);
    if (t6 != 0) {
        // 0x0052e978: |x| > pi/4: reduce; k = 1 - 2 * (n & 1)
        charge(ctx, 9);
        a0 = sp;
        jal(ctx, 0x52E978u, gen::fn___ieee754_rem_pio2f_0052c000);
        v0 = v0 & 0x1;
        lwc1(f12, sp, 0x0);
        v0 = sll(v0, 1);
        lwc1(f13, sp, 0x4);
        a0 = 1;
        a0 = subu(a0, v0);
        backedge(ctx);
    } else {
        // 0x0052e95c: |x| <= pi/4: tan(x + 0), k = 1
        charge(ctx, 2);
        mtc1(zero, f13);
        a0 = 1;
    }
    // 0x0052e964: __kernel_tanf(y0, y1, k)
    charge(ctx, 5);
    jal(ctx, 0x52E964u, gen::fn___kernel_tanf_0052dd40);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0052E9A0 acos -- 20 bytes; frame 0x10: ra sp+0x0
// acos(x $a0) -> $v0: the <math.h> wrapper: a tail call of __ieee754_acos (no errno handling in this build).
void acos(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052e9a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_acos_00528ae0(ctx);  // tail call
}

// 0x0052E9B8 log10 -- 20 bytes; frame 0x10: ra sp+0x0
// log10(x $a0) -> $v0: the <math.h> wrapper: tail call of __ieee754_log10.
void log10(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052e9b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_log10_00529578(ctx);  // tail call
}

// 0x0052E9E8 acosf -- 20 bytes; frame 0x10: ra sp+0x0
// acosf(x $f12) -> $f0: the <math.h> wrapper: tail call of __ieee754_acosf.
void acosf(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052e9e8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_acosf_0052abd8(ctx);  // tail call
}

// 0x0052EA00 asinf -- 20 bytes; frame 0x10: ra sp+0x0
// asinf(x $f12) -> $f0: the <math.h> wrapper: tail call of __ieee754_asinf.
void asinf(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052ea00
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_asinf_0052afe8(ctx);  // tail call
}

// 0x0052EA18 atan2f -- 476 bytes, 2 chunks; frame 0x10: ra sp+0x0
// atan2f(y $f12, x $f13) -> $f0: the angle of (x, y) in [-pi, pi] on the EE FPU. x == 1.0 -> atanf(y); y == 0 gives
// +-0 or +-pi by the quadrant (signs of y and x: m = sign(y) | 2*sign(x)); x == 0 gives +-pi/2; a large exponent
// difference gives +-pi/2 or (x < 0) +-pi / 0; else atanf(|y/x|) adjusted by the quadrant (pi - z, z - pi). Its body
// is the second chunk 0x52B380-0x52B548 (0x52EA18 is the entry stub); the +-pi/2 constants go through the VU0 I
// register (ctc2 / vaddi).
void atan2f(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052ea18
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0052b380
    charge(ctx, 12);
    mov_s(f0, f12);
    sp = addiu(sp, -0x10);
    t6 = 0x7FFF0000;
    mfc1(t4, f13);
    mfc1(t3, f12);
    t6 = t6 | 0xFFFF;
    sd(s0, sp, 0x0);
    t1 = t4 & t6;
    sd(ra, sp, 0x8);
    t7 = 0x3F800000;
    t2 = t3 & t6;
    if (t4 == t7) {
        // 0x0052b3b0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_atanf_0052e408(ctx);  // tail call
        return;
    }
    // 0x0052b3c0
    charge(ctx, 8);
    t7 = sra(t4, 30);
    t6 = 0x7F0000;
    t7 = t7 & 0x2;
    t5 = srl(t3, 31);
    t6 = t6 | 0xFFFF;  // &0x7FFFFF
    t6 = slt(t6, t2);
    s0 = t5 | t7;
    if (t6 == 0) {
        // 0x0052b3e0
        charge(ctx, 4);
        t6 = 0x40490000;
        t7 = 2;
        t6 = t6 | 0xFDA;
        if (s0 == t7) {
            goto L_0052b40c;
        }
        // 0x0052b3f0
        charge(ctx, 3);
        t7 = slti(s0, 3);
        if (t7 != 0) {
            // 0x0052b3fc
            charge(ctx, 2);
            t7 = 0x7F0000;
            if (i64(s0) < 0) {
                goto L_0052b424;
            }
            // 0x0052b404
            charge(ctx, 1);
            goto L_0052b408;
        }
        t6 = lui(0xC049);
        // 0x0052b534
        charge(ctx, 3);
        t7 = 3;
        t6 = t6 | 0xFDA;
        if (s0 == t7) {
            backedge(ctx);
            goto L_0052b40c;
        }
        // 0x0052b540
        charge(ctx, 2);
        t7 = 0x7F0000;
        backedge(ctx);
        goto L_0052b424;
    }
    // 0x0052b420
    charge(ctx, 1);
    t7 = 0x7F0000;
L_0052b424:
    charge(ctx, 4);
    t7 = t7 | 0xFFFF;
    t7 = slt(t7, t1);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = 0x7C0000;
    if (cc) {
        // 0x0052b46c
        charge(ctx, 7);
        t6 = subu(t2, t1);
        t7 = addiu(t7, -1352);
        t6 = sra(t6, 23);
        lwc1(f1, t7, 0);
        t7 = slti(t6, 61);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 1;
        if (!cc) {
            // 0x0052b488
            charge(ctx, 2);
            t7 = slti(t6, -60);
            if (i64(t4) < 0) {
                // 0x0052b490
                charge(ctx, 2);
                mtc1(zero, f1);
                if (t7 == 0) {
                    goto L_0052b498;
                }
                goto L_0052b4b8;
            }
        L_0052b498:
            charge(ctx, 8);
            div_s(f12, f0, f13);
            jal(ctx, 0x52B4A4u, gen::fn_fabsf_0052e788);
            mov_s(f12, f0);
            jal(ctx, 0x52B4ACu, gen::fn_atanf_0052e408);
            mov_s(f1, f0);
        L_0052b4b8:
            charge(ctx, 1);
            t7 = 1;
        }
        // 0x0052b4bc
        charge(ctx, 2);
        cc = s0 == t7;  // the condition, before the delay slot changes it
        t7 = slti(s0, 2);
        if (cc) {
            // 0x0052b524
            charge(ctx, 4);
            mfc1(t6, f1);
            t7 = lui(0x8000);
            t6 = t6 ^ t7;
            backedge(ctx);
        } else {
            // 0x0052b4c4
            charge(ctx, 2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 2;
            if (cc) {
                // 0x0052b4f8
                charge(ctx, 2);
                cc = s0 != t7;  // the condition, before the delay slot changes it
                t7 = 0x7C0000;
                if (cc) {
                    backedge(ctx);
                L_0052b4d8:
                    charge(ctx, 8);
                    t7 = addiu(t7, -1348);
                    lwc1(f0, t7, 0);
                    sub_s(f0, f1, f0);
                    t7 = 0x7C0000;
                    t7 = addiu(t7, -1344);  // &0x7BFAC0
                    lwc1(f1, t7, 0);  // 0x7BFAC0
                    sub_s(f0, f0, f1);
                    backedge(ctx);
                L_0052b408:
                    charge(ctx, 1);
                    mfc1(t6, f0);
                } else {
                    // 0x0052b500
                    charge(ctx, 9);
                    t7 = addiu(t7, -1348);
                    lwc1(f0, t7, 0);
                    sub_s(f0, f1, f0);
                    t7 = 0x7C0000;
                    t7 = addiu(t7, -1344);  // &0x7BFAC0
                    lwc1(f1, t7, 0);  // 0x7BFAC0
                    sub_s(f1, f1, f0);
                    mfc1(t6, f1);
                    backedge(ctx);
                }
            } else {
                // 0x0052b4cc
                charge(ctx, 2);
                mfc1(t6, f1);
                if (s0 != 0) {
                    // 0x0052b4d4
                    charge(ctx, 1);
                    t7 = 0x7C0000;
                    goto L_0052b4d8;
                }
                backedge(ctx);
            }
        }
    L_0052b40c:
        charge(ctx, 1);
        mtc1(t6, f0);
    } else {
        // 0x0052b434
        charge(ctx, 6);
        t7 = lui(0xBFC9);
        t7 = t7 | 0xFDA;
        ctc2(t7, 22, false);  // ctc2
        vnop(ctx);
        t7 = 0x3FC90000;
        if (i64(t3) >= 0) {
            // 0x0052b44c
            charge(ctx, 3);
            t7 = t7 | 0xFDA;
            ctc2(t7, 22, false);  // ctc2
            vnop(ctx);
        }
        // 0x0052b458
        charge(ctx, 5);
        vwaitq(ctx);
        cfc2(t6, 22, false);  // cfc2
        vnop(ctx);
        mtc1(t6, f0);
        backedge(ctx);
    }
    // 0x0052b410 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0052EA30 logf -- 716 bytes, 2 chunks; frame 0x10: ra sp+0x0
// logf(x $f12) -> $f0: natural logarithm on the EE FPU: x <= 0 handled first (zero -> the -huge constant at 0x7BFAF4,
// negative -> (x-x)/0 as the FPU computes it), x = 2^k * (1 + f) with f around sqrt(2)/2..sqrt(2), log(1+f) by the s =
// f/(2+f) polynomial (the R5900 multiply-accumulate mula / madd / msub), plus k*ln2 in two parts. Its body is the
// second chunk 0x52B548-0x52B800.
void logf(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f12{ctx, 12};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052ea30
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0052b548
    charge(ctx, 9);
    mfc1(t5, f12);
    t7 = 0x7FFF0000;
    t7 = t7 | 0xFFFF;
    t2 = 0x7F0000;
    t2 = t2 | 0xFFFF;  // &0x7FFFFF
    t7 = t5 & t7;
    t7 = slt(t2, t7);
    cc = t7 != 0;  // the condition, before the delay slot changes it
    t7 = 0x7C0000;
    if (!cc) {
        // 0x0052b56c
        charge(ctx, 2);
        lwc1(f0, t7, -1292);
        return;
    }
    // 0x0052b574
    charge(ctx, 2);
    t6 = 0x4A0000;
    if (i64(t5) < 0) {
        // 0x0052b57c
        charge(ctx, 5);
        sub_s(f1, f12, f12);
        mtc1(zero, f0);
        div_s(f0, f1, f0);
        // 0x0052b590 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x0052b598
    charge(ctx, 21);
    t3 = t5 & t2;
    t4 = sra(t5, 23);
    t6 = t6 | 0xFB20;
    t6 = addu(t3, t6);
    t5 = 0x800000;
    t1 = t6 & t5;
    t7 = 0x3F800000;
    t7 = t1 ^ t7;
    t6 = addiu(t3, 15);
    t5 = t3 | t7;
    t6 = t6 & t2;
    t7 = 0x7C0000;
    mtc1(t5, f1);
    t7 = addiu(t7, -1288);  // &0x7BFAF8
    t4 = addiu(t4, -127);
    lwc1(f0, t7, 0);  // 0x7BFAF8
    t6 = slti(t6, 16);
    sub_s(f12, f1, f0);
    t7 = sra(t1, 23);
    t4 = addu(t4, t7);
    if (t6 != 0) {
        // 0x0052b5ec
        charge(ctx, 4);
        mtc1(zero, f0);
        c_eq_s(f12, f0);
        t5 = 0x7C0000;
        if (cond(ctx)) {
            // 0x0052b5fc
            charge(ctx, 2);
            t5 = 0x7C0000;
            if (t4 == 0) {
                backedge(ctx);
                // 0x0052b590 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
            // 0x0052b604
            charge(ctx, 10);
            mtc1(t4, f6);
            t5 = addiu(t5, -1284);
            t7 = 0x7C0000;
            cvt_s_w(f6, f6);
            t7 = addiu(t7, -1280);  // &0x7BFB00
            lwc1(f0, t5, 0);
            lwc1(f1, t7, 0);  // 0x7BFB00
            mula_s(f6, f0);
            madd_s(f0, f6, f1);
            return;
        }
        // 0x0052b62c
        charge(ctx, 10);
        mul_s(f2, f12, f12);
        t5 = addiu(t5, -1276);
        t7 = 0x7C0000;
        lwc1(f1, t5, 0);
        t7 = addiu(t7, -1272);  // &0x7BFB08
        lwc1(f0, t7, 0);  // 0x7BFB08
        mul_s(f1, f12, f1);
        sub_s(f0, f0, f1);
        mul_s(f2, f2, f0);
        if (t4 == 0) {
            // 0x0052b654
            charge(ctx, 2);
            sub_s(f0, f12, f2);
            return;
        }
        // 0x0052b65c
        charge(ctx, 11);
        mtc1(t4, f6);
        t5 = 0x7C0000;
        t5 = addiu(t5, -1280);  // &0x7BFB00
        t7 = 0x7C0000;
        cvt_s_w(f6, f6);
        t7 = addiu(t7, -1284);  // &0x7BFAFC
        lwc1(f0, t5, 0);  // 0x7BFB00
        lwc1(f1, t7, 0);  // 0x7BFAFC
        mul_s(f0, f6, f0);
        mul_s(f1, f6, f1);
        sub_s(f0, f2, f0);
        // 0x0052b688 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        sub_s(f0, f0, f12);
        sub_s(f0, f1, f0);
        return;
    }
    // 0x0052b694
    charge(ctx, 52);
    t5 = 0x7C0000;
    mtc1(t4, f6);
    t5 = addiu(t5, -1268);  // &0x7BFB0C
    t6 = lui(0xFFCF);
    lwc1(f0, t5, 0);  // 0x7BFB0C
    t7 = 0x350000;
    t6 = t6 | 0x5C30;
    cvt_s_w(f6, f6);
    add_s(f0, f12, f0);
    t7 = t7 | 0xC288;  // &0x35C288
    t7 = subu(t7, t3);
    t1 = addu(t3, t6);
    t1 = t1 | t7;
    t5 = 0x7C0000;
    t7 = 0x7C0000;
    t5 = addiu(t5, -1260);  // &0x7BFB14
    div_s(f7, f12, f0);
    t7 = addiu(t7, -1264);  // &0x7BFB10
    lwc1(f1, t5, 0);  // 0x7BFB14
    t5 = 0x7C0000;
    t5 = addiu(t5, -1252);  // &0x7BFB1C
    lwc1(f3, t5, 0);  // 0x7BFB1C
    t5 = 0x7C0000;
    mul_s(f5, f7, f7);
    t5 = addiu(t5, -1244);  // &0x7BFB24
    lwc1(f0, t7, 0);  // 0x7BFB10
    t7 = 0x7C0000;
    mul_s(f4, f5, f5);
    t7 = addiu(t7, -1256);  // &0x7BFB18
    lwc1(f2, t7, 0);  // 0x7BFB18
    t7 = 0x7C0000;
    mul_s(f0, f4, f0);
    t7 = addiu(t7, -1248);  // &0x7BFB20
    mul_s(f1, f4, f1);
    add_s(f0, f0, f2);
    add_s(f1, f1, f3);
    mul_s(f0, f4, f0);
    lwc1(f2, t7, 0);  // 0x7BFB20
    mul_s(f1, f4, f1);
    t7 = 0x7C0000;
    lwc1(f3, t5, 0);  // 0x7BFB24
    add_s(f0, f0, f2);
    t7 = addiu(t7, -1240);  // &0x7BFB28
    add_s(f1, f1, f3);
    mul_s(f0, f4, f0);
    lwc1(f2, t7, 0);  // 0x7BFB28
    mula_s(f4, f1);
    add_s(f0, f0, f2);
    madd_s(f2, f5, f0);
    if (i64(t1) <= 0) {
        // 0x0052b7c0
        charge(ctx, 2);
        sub_s(f0, f12, f2);
        if (t4 == 0) {
            // 0x0052b7c8
            charge(ctx, 2);
            mul_s(f0, f7, f0);
            backedge(ctx);
            // 0x0052b788 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            sub_s(f0, f12, f0);
            return;
        }
        // 0x0052b7d0
        charge(ctx, 12);
        t5 = 0x7C0000;
        t5 = addiu(t5, -1280);  // &0x7BFB00
        t7 = 0x7C0000;
        lwc1(f1, t5, 0);  // 0x7BFB00
        t7 = addiu(t7, -1284);  // &0x7BFAFC
        mula_s(f7, f0);
        msub_s(f0, f6, f1);
        lwc1(f2, t7, 0);  // 0x7BFAFC
        mul_s(f2, f6, f2);
        sub_s(f0, f0, f12);
        sub_s(f0, f2, f0);
        return;
    }
    // 0x0052b764
    charge(ctx, 6);
    t5 = 0x7C0000;
    t5 = addiu(t5, -1272);  // &0x7BFB08
    lwc1(f0, t5, 0);  // 0x7BFB08
    mul_s(f0, f12, f0);
    mul_s(f3, f0, f12);
    if (t4 == 0) {
        // 0x0052b77c
        charge(ctx, 3);
        add_s(f0, f3, f2);
        mul_s(f0, f7, f0);
        sub_s(f0, f3, f0);
        // 0x0052b788 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sub_s(f0, f12, f0);
        return;
    }
    // 0x0052b790
    charge(ctx, 12);
    add_s(f2, f3, f2);
    t5 = 0x7C0000;
    t5 = addiu(t5, -1280);  // &0x7BFB00
    t7 = 0x7C0000;
    lwc1(f0, t5, 0);  // 0x7BFB00
    t7 = addiu(t7, -1284);  // &0x7BFAFC
    lwc1(f1, t7, 0);  // 0x7BFAFC
    mula_s(f7, f2);
    madd_s(f0, f6, f0);
    mul_s(f1, f6, f1);
    sub_s(f0, f3, f0);
    backedge(ctx);
    // 0x0052b688 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sub_s(f0, f0, f12);
    sub_s(f0, f1, f0);
}

// 0x0052EA48 powf -- 20 bytes; frame 0x10: ra sp+0x0
// powf(x $f12, y $f13) -> $f0: the <math.h> wrapper: tail call of __ieee754_powf.
void powf(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052ea48
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_powf_0052b800(ctx);  // tail call
}

// 0x0052EA60 sqrtf -- 20 bytes; frame 0x10: ra sp+0x0
// sqrtf(x $f12) -> $f0: the <math.h> wrapper: tail call of __ieee754_sqrtf.
void sqrtf(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0052ea60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn___ieee754_sqrtf_0052c398(ctx);  // tail call
}

}  // namespace p3fes::game
