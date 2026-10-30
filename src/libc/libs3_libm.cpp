// Slice libs3: the double-precision power and argument reduction of the maths library (__ieee754_pow,
// __ieee754_rem_pio2).
// Started from p3fes_handgen's faithful bodies (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"): every body
// keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check points
// (game/include/p3fes/game/hg_cpu.h); the names, structure, comments and typed views are this slice's.
// Names are symbols/functions.json's (ADR-0009); roles are read from the instructions, the pseudocode reference and
// the public C standard / MPEG standards only (ADR-0010: no newlib, GPL or CRI source was opened).
// Pair tests: tests/game/test_libs3.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs3.h"

namespace p3fes::recomp_gen {
void fn___ieee754_pow_005296f0(p3fes::EEContext&);
void fn___ieee754_rem_pio2_0052a3f0(p3fes::EEContext&);
void fn___ieee754_sqrt_0052a8c8(p3fes::EEContext&);
void fn___kernel_rem_pio2_0052c6d0(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpdiv_00531480(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptoli_005317d0(p3fes::EEContext&);
void fn_fabs_0052e118(p3fes::EEContext&);
void fn_litodp_00531720(p3fes::EEContext&);
void fn_scalbn_005237b0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x005296F0 __ieee754_pow -- 3328 bytes; frame 0x80: s2 sp+0x40, s0 sp+0x30, s4 sp+0x50, s6 sp+0x60, s1 sp+0x38, s5 sp+0x58, s7 sp+0x68, s3 sp+0x48, fp sp+0x70, ra sp+0x78
// fdlibm-style __ieee754_pow(x, y) in soft-float doubles: the special cases (y = 0, NaN, |x| = 1, Inf, x < 0 with
// integer / odd-integer y, |y| huge giving overflow / underflow), y = 1 / 2 / 0.5 / -1 shortcuts (__ieee754_sqrt for
// 0.5), then log2(x) to extra precision (the 3/2 split, tables 0x7BF6D8..), times y split in two, and 2^(y log2 x) by
// the polynomial and scalbn. The result comes back in $v0.
void __ieee754_pow(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x005296f0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    t7 = 0x7FFF0000;
    sd(s2, sp, 0x40);
    t7 = t7 | 0xFFFF;
    sd(s0, sp, 0x30);
    t3 = dsll32(a1, 0);
    sd(s4, sp, 0x50);
    s2 = dsra32(a1, 0);
    sd(s6, sp, 0x60);
    t3 = dsra32(t3, 0);
    sd(s1, sp, 0x38);
    s0 = s2 & t7;
    sd(s5, sp, 0x58);
    s4 = dsra32(a0, 0);
    sd(s7, sp, 0x68);
    s6 = dsll32(a0, 0);
    v0 = 1023;
    sd(s3, sp, 0x48);
    sd(fp, sp, 0x70);
    s7 = a1;
    sd(ra, sp, 0x78);
    s1 = a0;
    s6 = dsra32(s6, 0);
    s5 = s4 & t7;
    t6 = s0 | t3;
    v0 = dsll32(v0, 20);
    if (t6 != 0) {
        // 0x0052975c
        charge(ctx, 4);
        t6 = 0x7FF00000;
        t7 = slt(t6, s5);
        if (t7 != 0) {
            a0 = s1;
        } else {
            // 0x0052976c
            charge(ctx, 2);
            t7 = slt(t6, s0);
            if (s5 == t6) {
                // 0x00529774
                charge(ctx, 2);
                a0 = s1;
                if (s6 != 0) {
                    goto L_00529798;
                }
                // 0x0052977c
                charge(ctx, 1);
                t7 = slt(t6, s0);
                goto L_00529780;
            }
        L_00529780:
            charge(ctx, 2);
            a0 = s1;
            if (t7 != 0) {
                goto L_00529798;
            }
            // 0x00529788
            charge(ctx, 2);
            if (s0 == t6) {
                // 0x00529790
                charge(ctx, 2);
                if (t3 == 0) {
                    goto L_005297d0;
                }
                goto L_00529798;
            }
        L_005297d0:
            charge(ctx, 2);
            sw(zero, sp, 0x1C);
            if (i64(s4) < 0) {
                // 0x005297d8
                charge(ctx, 5);
                t7 = 0x433F0000;
                t7 = t7 | 0xFFFF;
                t7 = slt(t7, s0);
                t4 = 2;
                if (t7 != 0) {
                    // 0x005297ec
                    charge(ctx, 1);
                    sw(t4, sp, 0x1C);
                    goto L_005297f0;
                }
                // 0x0052a378
                charge(ctx, 5);
                t7 = 0x3FEF0000;
                t7 = t7 | 0xFFFF;
                t7 = slt(t7, s0);
                cc = t7 == 0;  // the condition, before the delay slot changes it
                t7 = sra(s0, 20);
                if (cc) {
                    backedge(ctx);
                    goto L_005297f0;
                }
                // 0x0052a38c
                charge(ctx, 4);
                t7 = addiu(t7, -1023);
                t6 = slti(t7, 21);
                sw(t7, sp, 0x18);
                if (t6 == 0) {
                    // 0x0052a39c
                    charge(ctx, 7);
                    lw(t5, sp, 0x18);
                    t7 = 52;
                    t7 = subu(t7, t5);
                    s3 = srlv(t3, t7);
                    t7 = sllv(s3, t7);
                    t6 = s3 & 0x1;
                    if (t7 == t3) {
                        // 0x0052a3b8
                        charge(ctx, 1);
                        t7 = 2;
                        goto L_0052a3bc;
                    }
                    backedge(ctx);
                    goto L_005297f0;
                }
                // 0x0052a3c8
                charge(ctx, 2);
                lw(t6, sp, 0x18);
                if (t3 == 0) {
                    // 0x0052a3d0
                    charge(ctx, 6);
                    t7 = 20;
                    t7 = subu(t7, t6);
                    s3 = srav(s0, t7);
                    t7 = sllv(s3, t7);
                    t6 = s3 & 0x1;
                    if (t7 != s0) {
                        backedge(ctx);
                    } else {
                        // 0x0052a3e8
                        charge(ctx, 2);
                        t7 = 2;
                        backedge(ctx);
                    L_0052a3bc:
                        charge(ctx, 3);
                        t7 = subu(t7, t6);
                        sw(t7, sp, 0x1C);
                        backedge(ctx);
                    }
                    goto L_005297f0;
                }
                backedge(ctx);
            L_005298f8:
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x5298F8u, gen::fn_fabs_0052e118);
                fp = v0;
                if (s6 == 0) {
                    // 0x00529908
                    charge(ctx, 3);
                    t7 = 0x7FF00000;
                    if (s5 != t7) {
                        // 0x00529914
                        charge(ctx, 2);
                        t7 = 0x3FF00000;
                        if (s5 == 0) {
                            goto L_00529924;
                        }
                        // 0x0052991c
                        charge(ctx, 2);
                        if (s5 == t7) {
                            goto L_00529924;
                        }
                        s4 = srl(s4, 31);
                        goto L_005299a4;
                    }
                L_00529924:
                    charge(ctx, 2);
                    s1 = fp;
                    if (i64(s2) < 0) {
                        // 0x0052992c
                        charge(ctx, 5);
                        a0 = 1023;
                        a1 = fp;
                        a0 = dsll32(a0, 20);
                        jal(ctx, 0x529934u, gen::fn_dpdiv_00531480);
                        s1 = v0;
                    }
                    // 0x00529940
                    charge(ctx, 2);
                    v0 = s1;
                    if (i64(s4) >= 0) {
                        backedge(ctx);
                    } else {
                        // 0x00529948
                        charge(ctx, 6);
                        t7 = lui(0xC010);
                        lw(t3, sp, 0x1C);
                        t7 = addu(s5, t7);
                        t7 = t7 | t3;
                        lw(t4, sp, 0x1C);
                        if (t7 == 0) {
                            // 0x00529960
                            charge(ctx, 8);
                            a0 = s1;
                            a1 = s1;
                            jal(ctx, 0x529964u, gen::fn_dpsub_005311c8);
                            a0 = v0;
                            a1 = v0;
                            jal(ctx, 0x529970u, gen::fn_dpdiv_00531480);
                            s1 = v0;
                            backedge(ctx);
                            goto L_0052988c;
                        }
                        // 0x00529980
                        charge(ctx, 3);
                        t7 = 1;
                        if (t4 != t7) {
                            v0 = s1;
                            backedge(ctx);
                        } else {
                            // 0x0052998c
                            charge(ctx, 5);
                            a1 = s1;
                            a0 = 0;
                            jal(ctx, 0x529990u, gen::fn_dpsub_005311c8);
                            s1 = v0;
                            backedge(ctx);
                        L_0052988c:
                            charge(ctx, 2);
                            v0 = s1;
                            backedge(ctx);
                        }
                    }
                    goto L_005297a0;
                }
                // 0x005299a0
                charge(ctx, 1);
                s4 = srl(s4, 31);
            L_005299a4:
                charge(ctx, 5);
                lw(t5, sp, 0x1C);
                t7 = addiu(s4, -1);
                t7 = t7 | t5;
                sw(s4, sp, 0x24);
                if (t7 != 0) {
                    // 0x005299d0
                    charge(ctx, 4);
                    t7 = 0x41E00000;
                    t7 = slt(t7, s0);
                    cc = t7 == 0;  // the condition, before the delay slot changes it
                    t7 = 0x43F00000;
                    if (!cc) {
                        // 0x005299e0
                        charge(ctx, 3);
                        t7 = slt(t7, s0);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = 0x3FEF0000;
                        if (!cc) {
                            // 0x005299ec
                            charge(ctx, 4);
                            t7 = t7 | 0xFFFF;
                            t7 = slt(t7, s5);
                            if (t7 == 0) {
                                goto L_00529a10;
                            }
                            // 0x005299fc
                            charge(ctx, 2);
                            if (i64(s2) > 0) {
                                // 0x00529a04
                                charge(ctx, 1);
                                t7 = 0x7C0000;
                                goto L_00529a08;
                            }
                            v0 = 0;
                            backedge(ctx);
                            goto L_005297a0;
                        }
                        // 0x00529a20
                        charge(ctx, 4);
                        t7 = t7 | 0xFFFE;
                        t7 = slt(t7, s5);
                        cc = t7 == 0;  // the condition, before the delay slot changes it
                        t7 = 0x3FF00000;
                        if (cc) {
                            backedge(ctx);
                        L_00529a10:
                            charge(ctx, 2);
                            t7 = 0x7C0000;
                            if (i64(s2) < 0) {
                                backedge(ctx);
                            L_00529a08:
                                charge(ctx, 2);
                                ld(v0, t7, -2344);
                                backedge(ctx);
                            } else {
                                // 0x00529a18
                                charge(ctx, 2);
                                v0 = 0;
                                backedge(ctx);
                            }
                            goto L_005297a0;
                        }
                        // 0x00529a30
                        charge(ctx, 3);
                        t7 = slt(t7, s5);
                        a1 = 1023;
                        if (t7 != 0) {
                            // 0x00529a3c
                            charge(ctx, 2);
                            t7 = 0x7C0000;
                            if (i64(s2) <= 0) {
                                backedge(ctx);
                            L_00529844:
                                charge(ctx, 2);
                                v0 = 0;
                                backedge(ctx);
                            } else {
                                // 0x00529a44
                                charge(ctx, 2);
                                ld(v0, t7, -2344);
                                backedge(ctx);
                            }
                            goto L_005297a0;
                        }
                        // 0x00529a50
                        charge(ctx, 56);
                        a0 = s1;
                        a1 = dsll32(a1, 20);
                        jal(ctx, 0x529A54u, gen::fn_dpsub_005311c8);
                        s5 = v0;
                        a0 = v0;
                        a1 = v0;
                        jal(ctx, 0x529A64u, gen::fn_dpmul_00531230);
                        a1 = 1021;
                        s0 = v0;
                        a0 = s5;
                        a1 = dsll32(a1, 20);
                        jal(ctx, 0x529A78u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        a1 = v0;
                        link(ctx, 0x529A88u);  // $ra first: the delay slot below depends on it
                        ld(a0, t7, -2336);
                        call(ctx, gen::fn_dpsub_005311c8);
                        a1 = v0;
                        a0 = s5;
                        jal(ctx, 0x529A94u, gen::fn_dpmul_00531230);
                        a0 = 511;
                        a1 = v0;
                        a0 = dsll32(a0, 21);
                        jal(ctx, 0x529AA4u, gen::fn_dpsub_005311c8);
                        a0 = s0;
                        a1 = v0;
                        jal(ctx, 0x529AB0u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        s2 = v0;
                        ld(a1, t7, -2328);  // 0x7BF6E8
                        a0 = s5;
                        jal(ctx, 0x529AC4u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        sd(v0, sp, 0x8);
                        ld(a1, t7, -2320);  // 0x7BF6F0
                        a0 = s5;
                        jal(ctx, 0x529AD8u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        s0 = v0;
                        ld(a1, t7, -2312);  // 0x7BF6F8
                        a0 = s2;
                        jal(ctx, 0x529AECu, gen::fn_dpmul_00531230);
                        a1 = v0;
                        a0 = s0;
                        jal(ctx, 0x529AF8u, gen::fn_dpsub_005311c8);
                        ld(a0, sp, 0x8);
                        a1 = v0;
                        link(ctx, 0x529B08u);  // $ra first: the delay slot below depends on it
                        sd(v0, sp, 0x10);
                        call(ctx, gen::fn_dpadd_00531170);
                        t7 = si(-1);
                        ld(a1, sp, 0x8);
                        t7 = dsll32(t7, 0);
                        s3 = v0 & t7;
                        a0 = s3;
                        jal(ctx, 0x529B20u, gen::fn_dpsub_005311c8);
                        ld(a0, sp, 0x10);
                        a1 = v0;
                        goto L_00529b30;
                    }
                    // 0x00529f5c
                    charge(ctx, 5);
                    s0 = 0xF0000;
                    s0 = s0 | 0xFFFF;
                    t7 = slt(s0, s5);
                    sw(zero, sp, 0x20);
                    if (t7 == 0) {
                        // 0x00529f70
                        charge(ctx, 8);
                        t6 = si(-53);
                        a1 = 269;
                        sw(t6, sp, 0x20);
                        a0 = fp;
                        a1 = dsll32(a1, 22);
                        jal(ctx, 0x529F80u, gen::fn_dpmul_00531230);
                        fp = v0;
                        s5 = dsra32(v0, 0);
                    }
                    // 0x00529f90
                    charge(ctx, 13);
                    lw(t3, sp, 0x20);
                    t7 = sra(s5, 20);
                    t6 = 0x30000;
                    sw(zero, sp, 0x18);
                    t5 = addu(t3, t7);
                    s3 = s5 & s0;
                    t4 = addiu(t5, -1023);
                    t6 = t6 | 0x988E;
                    t7 = 0x3FF00000;
                    sw(t4, sp, 0x20);
                    t6 = slt(t6, s3);
                    s5 = s3 | t7;
                    if (t6 != 0) {
                        // 0x00529fc4
                        charge(ctx, 6);
                        t7 = 0xB0000;
                        t6 = 1;
                        t7 = t7 | 0xB679;
                        t7 = slt(t7, s3);
                        sw(t6, sp, 0x18);
                        if (t7 != 0) {
                            // 0x00529fdc
                            charge(ctx, 5);
                            t5 = addiu(t5, -1022);
                            sw(zero, sp, 0x18);
                            t7 = lui(0xFFF0);
                            sw(t5, sp, 0x20);
                            s5 = addu(s5, t7);
                        }
                    }
                    // 0x00529ff0
                    charge(ctx, 226);
                    lw(t7, sp, 0x18);
                    t6 = dsll32(s5, 0);
                    t5 = dsll32(fp, 0);
                    t6 = dsrl32(t6, 0);
                    s3 = sll(t7, 3);
                    t6 = dsll32(t6, 0);
                    t7 = 0x7C0000;
                    t5 = dsrl32(t5, 0);
                    t7 = addiu(t7, -2608);  // &0x7BF5D0
                    fp = t5 | t6;
                    t7 = addu(s3, t7);
                    a0 = fp;
                    ld(s0, t7, 0);
                    s4 = si(-1);
                    s4 = dsll32(s4, 0);
                    s6 = 2049;
                    a1 = s0;
                    s6 = dsll32(s6, 19);
                    jal(ctx, 0x52A034u, gen::fn_dpsub_005311c8);
                    sd(v0, sp, 0x8);
                    a0 = fp;
                    a1 = s0;
                    jal(ctx, 0x52A044u, gen::fn_dpadd_00531170);
                    a0 = 1023;
                    a1 = v0;
                    a0 = dsll32(a0, 20);
                    jal(ctx, 0x52A054u, gen::fn_dpdiv_00531480);
                    ld(a0, sp, 0x8);
                    a1 = v0;
                    link(ctx, 0x52A064u);  // $ra first: the delay slot below depends on it
                    sd(v0, sp, 0x10);
                    call(ctx, gen::fn_dpmul_00531230);
                    lw(t3, sp, 0x18);
                    t7 = sra(s5, 1);
                    t6 = 0x20000000;
                    sd(v0, sp, 0x0);
                    t5 = sll(t3, 18);
                    t7 = t7 | t6;
                    t7 = addu(t7, t5);
                    t6 = 0x80000;
                    t7 = addu(t7, t6);
                    s2 = v0 & s4;
                    t7 = dsll32(t7, 0);
                    a1 = s0;
                    sd(t7, sp, 0x28);
                    link(ctx, 0x52A0A0u);  // $ra first: the delay slot below depends on it
                    ld(a0, sp, 0x28);
                    call(ctx, gen::fn_dpsub_005311c8);
                    a0 = fp;
                    a1 = v0;
                    jal(ctx, 0x52A0ACu, gen::fn_dpsub_005311c8);
                    ld(a1, sp, 0x28);
                    s1 = v0;
                    a0 = s2;
                    jal(ctx, 0x52A0BCu, gen::fn_dpmul_00531230);
                    ld(a0, sp, 0x8);
                    a1 = v0;
                    jal(ctx, 0x52A0C8u, gen::fn_dpsub_005311c8);
                    s0 = v0;
                    a0 = s2;
                    a1 = s1;
                    jal(ctx, 0x52A0D8u, gen::fn_dpmul_00531230);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A0E4u, gen::fn_dpsub_005311c8);
                    ld(a0, sp, 0x10);
                    a1 = v0;
                    jal(ctx, 0x52A0F0u, gen::fn_dpmul_00531230);
                    ld(a0, sp, 0x0);
                    s5 = v0;
                    a1 = a0;
                    jal(ctx, 0x52A100u, gen::fn_dpmul_00531230);
                    s0 = v0;
                    a0 = v0;
                    a1 = v0;
                    jal(ctx, 0x52A110u, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    s1 = v0;
                    ld(a1, t7, -2304);  // 0x7BF700
                    a0 = s0;
                    jal(ctx, 0x52A124u, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A134u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -2296);
                    call(ctx, gen::fn_dpadd_00531170);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A140u, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A150u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -2288);
                    call(ctx, gen::fn_dpadd_00531170);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A15Cu, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A16Cu);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -2280);
                    call(ctx, gen::fn_dpadd_00531170);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A178u, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A188u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -2272);
                    call(ctx, gen::fn_dpadd_00531170);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A194u, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A1A4u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -2264);
                    call(ctx, gen::fn_dpadd_00531170);
                    a0 = s1;
                    a1 = v0;
                    jal(ctx, 0x52A1B0u, gen::fn_dpmul_00531230);
                    ld(a1, sp, 0x0);
                    fp = v0;
                    a0 = s2;
                    jal(ctx, 0x52A1C0u, gen::fn_dpadd_00531170);
                    a0 = s5;
                    a1 = v0;
                    jal(ctx, 0x52A1CCu, gen::fn_dpmul_00531230);
                    a0 = fp;
                    a1 = v0;
                    jal(ctx, 0x52A1D8u, gen::fn_dpadd_00531170);
                    fp = v0;
                    a0 = s2;
                    a1 = s2;
                    jal(ctx, 0x52A1E8u, gen::fn_dpmul_00531230);
                    s0 = v0;
                    a1 = s6;
                    a0 = v0;
                    jal(ctx, 0x52A1F8u, gen::fn_dpadd_00531170);
                    a1 = fp;
                    a0 = v0;
                    jal(ctx, 0x52A204u, gen::fn_dpadd_00531170);
                    t7 = v0 & s4;
                    a1 = s6;
                    sd(t7, sp, 0x28);
                    link(ctx, 0x52A218u);  // $ra first: the delay slot below depends on it
                    ld(a0, sp, 0x28);
                    call(ctx, gen::fn_dpsub_005311c8);
                    a1 = s0;
                    a0 = v0;
                    jal(ctx, 0x52A224u, gen::fn_dpsub_005311c8);
                    a0 = fp;
                    a1 = v0;
                    jal(ctx, 0x52A230u, gen::fn_dpsub_005311c8);
                    ld(a1, sp, 0x28);
                    s1 = v0;
                    a0 = s2;
                    jal(ctx, 0x52A240u, gen::fn_dpmul_00531230);
                    ld(a1, sp, 0x28);
                    a0 = s5;
                    link(ctx, 0x52A250u);  // $ra first: the delay slot below depends on it
                    sd(v0, sp, 0x8);
                    call(ctx, gen::fn_dpmul_00531230);
                    ld(a1, sp, 0x0);
                    s0 = v0;
                    a0 = s1;
                    jal(ctx, 0x52A260u, gen::fn_dpmul_00531230);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A26Cu, gen::fn_dpadd_00531170);
                    ld(a0, sp, 0x8);
                    a1 = v0;
                    link(ctx, 0x52A27Cu);  // $ra first: the delay slot below depends on it
                    sd(v0, sp, 0x10);
                    call(ctx, gen::fn_dpadd_00531170);
                    s6 = v0 & s4;
                    ld(a1, sp, 0x8);
                    a0 = s6;
                    jal(ctx, 0x52A28Cu, gen::fn_dpsub_005311c8);
                    ld(a0, sp, 0x10);
                    a1 = v0;
                    jal(ctx, 0x52A298u, gen::fn_dpsub_005311c8);
                    t7 = 0x7C0000;
                    fp = v0;
                    ld(a1, t7, -2256);  // 0x7BF730
                    a0 = s6;
                    jal(ctx, 0x52A2ACu, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    s2 = v0;
                    ld(a1, t7, -2248);  // 0x7BF738
                    a0 = s6;
                    jal(ctx, 0x52A2C0u, gen::fn_dpmul_00531230);
                    t7 = 0x7C0000;
                    s0 = v0;
                    ld(a1, t7, -2240);  // 0x7BF740
                    a0 = fp;
                    jal(ctx, 0x52A2D4u, gen::fn_dpmul_00531230);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A2E0u, gen::fn_dpadd_00531170);
                    t7 = 0x7C0000;
                    a0 = v0;
                    t7 = addiu(t7, -2576);  // &0x7BF5F0
                    t7 = addu(s3, t7);
                    link(ctx, 0x52A2F8u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, 0);
                    call(ctx, gen::fn_dpadd_00531170);
                    lw(a0, sp, 0x20);
                    s1 = v0;
                    jal(ctx, 0x52A304u, gen::fn_litodp_00531720);
                    s5 = v0;
                    a0 = s2;
                    a1 = s1;
                    jal(ctx, 0x52A314u, gen::fn_dpadd_00531170);
                    t7 = 0x7C0000;
                    a0 = v0;
                    t7 = addiu(t7, -2592);  // &0x7BF5E0
                    s3 = addu(s3, t7);
                    ld(s0, s3, 0);
                    a1 = s0;
                    jal(ctx, 0x52A330u, gen::fn_dpadd_00531170);
                    a0 = v0;
                    a1 = s5;
                    jal(ctx, 0x52A33Cu, gen::fn_dpadd_00531170);
                    s3 = v0 & s4;
                    a1 = s5;
                    a0 = s3;
                    jal(ctx, 0x52A34Cu, gen::fn_dpsub_005311c8);
                    a0 = v0;
                    a1 = s0;
                    jal(ctx, 0x52A358u, gen::fn_dpsub_005311c8);
                    a0 = v0;
                    a1 = s2;
                    jal(ctx, 0x52A364u, gen::fn_dpsub_005311c8);
                    a1 = v0;
                    a0 = s1;
                    backedge(ctx);
                L_00529b30:
                    charge(ctx, 12);
                    jal(ctx, 0x529B30u, gen::fn_dpsub_005311c8);
                    lw(t4, sp, 0x24);
                    s2 = v0;
                    lw(t5, sp, 0x1C);
                    t7 = addiu(t4, -1);
                    t6 = addiu(t5, -1);
                    t7 = t7 | t6;
                    t6 = 1023;
                    t6 = dsll32(t6, 20);
                    sd(t6, sp, 0x0);
                    if (t7 == 0) {
                        // 0x00529b60
                        charge(ctx, 3);
                        t7 = si(-1025);
                        t7 = dsll32(t7, 20);
                        sd(t7, sp, 0x0);
                    }
                    // 0x00529b6c
                    charge(ctx, 32);
                    t7 = si(-1);
                    a0 = s7;
                    t7 = dsll32(t7, 0);
                    s1 = s7 & t7;
                    a1 = s1;
                    jal(ctx, 0x529B7Cu, gen::fn_dpsub_005311c8);
                    a1 = s3;
                    a0 = v0;
                    jal(ctx, 0x529B88u, gen::fn_dpmul_00531230);
                    s0 = v0;
                    a0 = s7;
                    a1 = s2;
                    jal(ctx, 0x529B98u, gen::fn_dpmul_00531230);
                    a1 = v0;
                    a0 = s0;
                    jal(ctx, 0x529BA4u, gen::fn_dpadd_00531170);
                    a0 = s1;
                    a1 = s3;
                    fp = v0;
                    jal(ctx, 0x529BB4u, gen::fn_dpmul_00531230);
                    s6 = v0;
                    a0 = fp;
                    a1 = v0;
                    jal(ctx, 0x529BC4u, gen::fn_dpadd_00531170);
                    t7 = 0x408F0000;
                    s3 = dsra32(v0, 0);
                    t7 = t7 | 0xFFFF;
                    t5 = dsll32(v0, 0);
                    s1 = v0;
                    t7 = slt(t7, s3);
                    t5 = dsra32(t5, 0);
                    if (t7 != 0) {
                        // 0x00529bec
                        charge(ctx, 5);
                        t7 = lui(0xBF70);
                        t7 = addu(s3, t7);
                        t7 = t7 | t5;
                        cc = t7 != 0;  // the condition, before the delay slot changes it
                        t7 = 0x7C0000;
                        if (!cc) {
                            // 0x00529c00
                            charge(ctx, 13);
                            t7 = 0x7C0000;
                            a0 = fp;
                            link(ctx, 0x529C08u);  // $ra first: the delay slot below depends on it
                            ld(a1, t7, -2224);
                            call(ctx, gen::fn_dpadd_00531170);
                            s0 = v0;
                            a0 = s1;
                            a1 = s6;
                            jal(ctx, 0x529C18u, gen::fn_dpsub_005311c8);
                            a0 = v0;
                            a1 = s0;
                            jal(ctx, 0x529C24u, gen::fn_dpcmp_005316d0);
                            t3 = 0x7FFF0000;
                            if (i64(v0) >= 0) {
                                goto L_00529c58;
                            }
                            // 0x00529c34
                            charge(ctx, 1);
                            t7 = 0x7C0000;
                            goto L_00529c38;
                        }
                    L_00529c38:
                        charge(ctx, 2);
                        ld(a0, sp, 0x0);
                        ld(s0, t7, -2232);
                        goto L_00529c40;
                    }
                    // 0x00529ef8
                    charge(ctx, 8);
                    t7 = 0x7FFF0000;
                    t6 = 0x40900000;
                    t7 = t7 | 0xFFFF;
                    t6 = t6 | 0xCBFF;
                    t7 = s3 & t7;
                    t6 = slt(t6, t7);
                    t7 = 0x3F6F0000;
                    if (t6 == 0) {
                        backedge(ctx);
                        // 0x00529c54
                        charge(ctx, 1);
                        t3 = 0x7FFF0000;
                    L_00529c58:
                        charge(ctx, 7);
                        sw(zero, sp, 0x20);
                        t3 = t3 | 0xFFFF;
                        t7 = 0x3FE00000;
                        t5 = s3 & t3;
                        t7 = slt(t7, t5);
                        t6 = sra(t5, 20);
                        if (t7 != 0) {
                            // 0x00529c74
                            charge(ctx, 32);
                            t4 = 0x100000;
                            t7 = addiu(t6, -1022);
                            t7 = srav(t4, t7);
                            t6 = 0xF0000;
                            t7 = addu(s3, t7);
                            t6 = t6 | 0xFFFF;
                            sw(t7, sp, 0x20);
                            a0 = s6;
                            t7 = t7 & t3;
                            lw(t3, sp, 0x20);
                            t7 = sra(t7, 20);
                            t7 = addiu(t7, -1023);
                            t5 = t3 & t6;
                            sw(t7, sp, 0x18);
                            t5 = t5 | t4;
                            t6 = srav(t6, t7);
                            lw(t4, sp, 0x18);
                            t7 = 20;
                            t6 = nor(0, t6);
                            t7 = subu(t7, t4);
                            t6 = t3 & t6;
                            t5 = srav(t5, t7);
                            t4 = slti(s3, 0);
                            t7 = subu(0, t5);
                            t6 = dsll32(t6, 0);
                            t6 = dsrl32(t6, 0);
                            if (t4 != 0) t5 = t7;
                            s5 = dsll32(t6, 0);
                            sw(t5, sp, 0x20);
                            a1 = s5;
                            jal(ctx, 0x529CE8u, gen::fn_dpsub_005311c8);
                            s6 = v0;
                        }
                        // 0x00529cf4
                        charge(ctx, 117);
                        a0 = fp;
                        a1 = s6;
                        jal(ctx, 0x529CF8u, gen::fn_dpadd_00531170);
                        t7 = si(-1);
                        a1 = 0x3FE60000;
                        t7 = dsll32(t7, 0);
                        a1 = a1 | 0x2E43;
                        s5 = v0 & t7;
                        a1 = dsll32(a1, 0);
                        a0 = s5;
                        jal(ctx, 0x529D18u, gen::fn_dpmul_00531230);
                        sd(v0, sp, 0x8);
                        a0 = s5;
                        a1 = s6;
                        jal(ctx, 0x529D28u, gen::fn_dpsub_005311c8);
                        a1 = v0;
                        a0 = fp;
                        jal(ctx, 0x529D34u, gen::fn_dpsub_005311c8);
                        t7 = 0x7C0000;
                        a0 = v0;
                        link(ctx, 0x529D44u);  // $ra first: the delay slot below depends on it
                        ld(a1, t7, -2208);
                        call(ctx, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        s0 = v0;
                        ld(a1, t7, -2200);  // 0x7BF768
                        a0 = s5;
                        jal(ctx, 0x529D58u, gen::fn_dpmul_00531230);
                        a0 = s0;
                        a1 = v0;
                        jal(ctx, 0x529D64u, gen::fn_dpadd_00531170);
                        ld(a0, sp, 0x8);
                        a1 = v0;
                        link(ctx, 0x529D74u);  // $ra first: the delay slot below depends on it
                        sd(v0, sp, 0x10);
                        call(ctx, gen::fn_dpadd_00531170);
                        ld(a1, sp, 0x8);
                        s1 = v0;
                        a0 = v0;
                        jal(ctx, 0x529D84u, gen::fn_dpsub_005311c8);
                        ld(a0, sp, 0x10);
                        a1 = v0;
                        jal(ctx, 0x529D90u, gen::fn_dpsub_005311c8);
                        s2 = v0;
                        a0 = s1;
                        a1 = s1;
                        jal(ctx, 0x529DA0u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        s5 = v0;
                        ld(a1, t7, -2192);  // 0x7BF770
                        a0 = v0;
                        jal(ctx, 0x529DB4u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        a0 = v0;
                        link(ctx, 0x529DC4u);  // $ra first: the delay slot below depends on it
                        ld(a1, t7, -2184);
                        call(ctx, gen::fn_dpadd_00531170);
                        a1 = v0;
                        a0 = s5;
                        jal(ctx, 0x529DD0u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        a0 = v0;
                        link(ctx, 0x529DE0u);  // $ra first: the delay slot below depends on it
                        ld(a1, t7, -2176);
                        call(ctx, gen::fn_dpadd_00531170);
                        a1 = v0;
                        a0 = s5;
                        jal(ctx, 0x529DECu, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        a0 = v0;
                        link(ctx, 0x529DFCu);  // $ra first: the delay slot below depends on it
                        ld(a1, t7, -2168);
                        call(ctx, gen::fn_dpadd_00531170);
                        a1 = v0;
                        a0 = s5;
                        jal(ctx, 0x529E08u, gen::fn_dpmul_00531230);
                        t7 = 0x7C0000;
                        a0 = v0;
                        link(ctx, 0x529E18u);  // $ra first: the delay slot below depends on it
                        ld(a1, t7, -2160);
                        call(ctx, gen::fn_dpadd_00531170);
                        a1 = v0;
                        a0 = s5;
                        jal(ctx, 0x529E24u, gen::fn_dpmul_00531230);
                        a1 = v0;
                        a0 = s1;
                        jal(ctx, 0x529E30u, gen::fn_dpsub_005311c8);
                        s3 = v0;
                        a0 = s1;
                        a1 = v0;
                        jal(ctx, 0x529E40u, gen::fn_dpmul_00531230);
                        a1 = 1;
                        s0 = v0;
                        a0 = s3;
                        a1 = dsll32(a1, 30);
                        jal(ctx, 0x529E54u, gen::fn_dpsub_005311c8);
                        a0 = s0;
                        a1 = v0;
                        jal(ctx, 0x529E60u, gen::fn_dpdiv_00531480);
                        s0 = v0;
                        a0 = s1;
                        a1 = s2;
                        jal(ctx, 0x529E70u, gen::fn_dpmul_00531230);
                        a1 = v0;
                        a0 = s2;
                        jal(ctx, 0x529E7Cu, gen::fn_dpadd_00531170);
                        a1 = v0;
                        a0 = s0;
                        jal(ctx, 0x529E88u, gen::fn_dpsub_005311c8);
                        a0 = v0;
                        a1 = s1;
                        jal(ctx, 0x529E94u, gen::fn_dpsub_005311c8);
                        a0 = 1023;
                        a1 = v0;
                        a0 = dsll32(a0, 20);
                        jal(ctx, 0x529EA4u, gen::fn_dpsub_005311c8);
                        lw(t5, sp, 0x20);
                        s3 = dsra32(v0, 0);
                        t6 = sll(t5, 20);
                        s3 = addu(s3, t6);
                        t7 = sra(s3, 20);
                        t6 = dsll32(s3, 0);
                        if (i64(t7) > 0) {
                            // 0x00529ee0
                            charge(ctx, 6);
                            t7 = dsll32(v0, 0);
                            t6 = dsrl32(t6, 0);
                            t7 = dsrl32(t7, 0);
                            t6 = dsll32(t6, 0);
                            s1 = t7 | t6;
                            backedge(ctx);
                        } else {
                            // 0x00529ec8
                            charge(ctx, 4);
                            lw(a1, sp, 0x20);
                            a0 = v0;
                            jal(ctx, 0x529ECCu, gen::fn_scalbn_005237b0);
                            s1 = v0;
                        }
                        // 0x00529ed8
                        charge(ctx, 2);
                        ld(a0, sp, 0x0);
                        backedge(ctx);
                    L_005298a0:
                        charge(ctx, 1);
                        a1 = s1;
                    } else {
                        // 0x00529f18
                        charge(ctx, 5);
                        t7 = t7 | 0x3400;
                        t7 = addu(s3, t7);
                        t7 = t7 | t5;
                        cc = t7 != 0;  // the condition, before the delay slot changes it
                        t7 = 0x7C0000;
                        if (!cc) {
                            // 0x00529f2c
                            charge(ctx, 8);
                            a0 = v0;
                            a1 = s6;
                            jal(ctx, 0x529F30u, gen::fn_dpsub_005311c8);
                            a1 = v0;
                            a0 = fp;
                            jal(ctx, 0x529F3Cu, gen::fn_dpcmp_005316d0);
                            t3 = 0x7FFF0000;
                            if (i64(v0) > 0) {
                                backedge(ctx);
                                goto L_00529c58;
                            }
                            // 0x00529f4c
                            charge(ctx, 1);
                            t7 = 0x7C0000;
                            goto L_00529f50;
                        }
                    L_00529f50:
                        charge(ctx, 3);
                        ld(a0, sp, 0x0);
                        ld(s0, t7, -2216);
                        backedge(ctx);
                    L_00529c40:
                        charge(ctx, 5);
                        a1 = s0;
                        jal(ctx, 0x529C40u, gen::fn_dpmul_00531230);
                        a0 = v0;
                        a1 = s0;
                        backedge(ctx);
                    }
                    // 0x005298a4
                    charge(ctx, 4);
                    jal(ctx, 0x5298A4u, gen::fn_dpmul_00531230);
                    ld(s0, sp, 0x30);
                    backedge(ctx);
                } else {
                    // 0x005299b8
                    charge(ctx, 6);
                    a0 = s1;
                    a1 = s1;
                    jal(ctx, 0x5299BCu, gen::fn_dpsub_005311c8);
                    a0 = v0;
                    a1 = v0;
                    backedge(ctx);
                L_0052987c:
                    charge(ctx, 4);
                    jal(ctx, 0x52987Cu, gen::fn_dpdiv_00531480);
                    ld(s0, sp, 0x30);
                    backedge(ctx);
                }
                // 0x005297a4 (the shared epilogue, written out on this path)
                charge(ctx, 11);
                ld(s1, sp, 0x38);
                ld(s2, sp, 0x40);
                ld(s3, sp, 0x48);
                ld(s4, sp, 0x50);
                ld(s5, sp, 0x58);
                ld(s6, sp, 0x60);
                ld(s7, sp, 0x68);
                ld(fp, sp, 0x70);
                ld(ra, sp, 0x78);
                sp = addiu(sp, 0x80);
                return;
            }
        L_005297f0:
            charge(ctx, 2);
            t7 = 0x7FF00000;
            if (t3 != 0) {
                goto L_005298f8;
            }
            // 0x005297f8
            charge(ctx, 2);
            cc = s0 != t7;  // the condition, before the delay slot changes it
            t7 = 0x3FF00000;
            if (cc) {
                // 0x00529860
                charge(ctx, 2);
                cc = s0 != t7;  // the condition, before the delay slot changes it
                t7 = 0x40000000;
                if (!cc) {
                    // 0x00529868
                    charge(ctx, 2);
                    if (i64(s2) >= 0) {
                        v0 = s1;
                        backedge(ctx);
                        goto L_005297a0;
                    }
                    // 0x00529870
                    charge(ctx, 3);
                    a0 = 1023;
                    a1 = s1;
                    a0 = dsll32(a0, 20);
                    goto L_0052987c;
                }
                // 0x00529894
                charge(ctx, 2);
                cc = s2 != t7;  // the condition, before the delay slot changes it
                t7 = 0x3FE00000;
                if (!cc) {
                    // 0x0052989c
                    charge(ctx, 1);
                    a0 = s1;
                    goto L_005298a0;
                }
                // 0x005298b4
                charge(ctx, 2);
                if (s2 != t7) {
                    goto L_005298f8;
                }
                // 0x005298bc
                charge(ctx, 2);
                a0 = s1;
                if (i64(s4) < 0) {
                    goto L_005298f8;
                }
                // 0x005298c4
                charge(ctx, 12);
                ld(s0, sp, 0x30);
                ld(s1, sp, 0x38);
                ld(s2, sp, 0x40);
                ld(s3, sp, 0x48);
                ld(s4, sp, 0x50);
                ld(s5, sp, 0x58);
                ld(s6, sp, 0x60);
                ld(s7, sp, 0x68);
                ld(fp, sp, 0x70);
                ld(ra, sp, 0x78);
                sp = addiu(sp, 0x80);
                gen::fn___ieee754_sqrt_0052a8c8(ctx);  // tail call
                return;
            }
            // 0x00529800
            charge(ctx, 5);
            t7 = lui(0xC010);
            t7 = addu(s5, t7);
            t7 = t7 | s6;
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0x3FEF0000;
            if (!cc) {
                // 0x00529814
                charge(ctx, 2);
                a0 = s7;
                a1 = s7;
                goto L_0052981c;
            }
            // 0x0052982c
            charge(ctx, 4);
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s5);
            if (t7 != 0) {
                // 0x0052983c
                charge(ctx, 2);
                v0 = s7;
                if (i64(s2) < 0) {
                    goto L_00529844;
                }
                backedge(ctx);
                goto L_005297a0;
            }
            // 0x0052984c
            charge(ctx, 2);
            if (i64(s2) >= 0) {
                v0 = 0;
                backedge(ctx);
                goto L_005297a0;
            }
            // 0x00529854
            charge(ctx, 3);
            a1 = s7;
            a0 = 0;
            backedge(ctx);
        L_0052981c:
            charge(ctx, 4);
            jal(ctx, 0x52981Cu, gen::fn_dpsub_005311c8);
            ld(s0, sp, 0x30);
            backedge(ctx);
            // 0x005297a4 (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(s1, sp, 0x38);
            ld(s2, sp, 0x40);
            ld(s3, sp, 0x48);
            ld(s4, sp, 0x50);
            ld(s5, sp, 0x58);
            ld(s6, sp, 0x60);
            ld(s7, sp, 0x68);
            ld(fp, sp, 0x70);
            ld(ra, sp, 0x78);
            sp = addiu(sp, 0x80);
            return;
        }
    L_00529798:
        charge(ctx, 2);
        a1 = s7;
        jal(ctx, 0x529798u, gen::fn_dpadd_00531170);
    }
L_005297a0:
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x005297a4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(s6, sp, 0x60);
    ld(s7, sp, 0x68);
    ld(fp, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

// 0x0052A3F0 __ieee754_rem_pio2 -- 1240 bytes; frame 0x80: s4 sp+0x50, s0 sp+0x30, s2 sp+0x40, s1 sp+0x38, s3 sp+0x48, s5 sp+0x58, s6 sp+0x60, s7 sp+0x68, fp sp+0x70, ra sp+0x78
// fdlibm-style __ieee754_rem_pio2(x, y): reduces x by multiples of pi/2 -- |x| <= pi/4 returns n = 0 (y[0] = x); up to
// 3pi/4 one subtraction of the two-part pi/2; up to 2^20 * pi/2 the medium case with n = round(x * 2/pi) and the
// three-part pi/2 with the cancellation check; beyond, __kernel_rem_pio2 on the 24-bit pieces of x; Inf / NaN give x -
// x. x is the 64-bit soft-float argument in $a0; stores the reduced value as y[0] + y[1] (two doubles at $a1) and
// returns n.
void __ieee754_rem_pio2(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052a3f0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    t7 = 0x7FFF0000;
    sd(s4, sp, 0x50);
    t7 = t7 | 0xFFFF;
    sd(s0, sp, 0x30);
    t6 = 0x3FE90000;
    sd(s2, sp, 0x40);
    s4 = dsra32(a0, 0);
    s0 = s4 & t7;
    sd(s1, sp, 0x38);
    t6 = t6 | 0x21FB;
    sd(s3, sp, 0x48);
    sd(s5, sp, 0x58);
    sd(s6, sp, 0x60);
    t6 = slt(t6, s0);
    sd(s7, sp, 0x68);
    sd(fp, sp, 0x70);
    sd(ra, sp, 0x78);
    s2 = a1;
    if (t6 != 0) {
        // 0x0052a480
        charge(ctx, 5);
        t7 = 0x40020000;
        t7 = t7 | 0xD97B;
        t7 = slt(t7, s0);
        cc = t7 != 0;  // the condition, before the delay slot changes it
        t7 = 0x41390000;
        if (cc) {
            // 0x0052a590
            charge(ctx, 4);
            t7 = t7 | 0x21FB;
            t7 = slt(t7, s0);
            cc = t7 != 0;  // the condition, before the delay slot changes it
            t7 = 0x7FEF0000;
            if (!cc) {
                // 0x0052a5a0
                charge(ctx, 32);
                jal(ctx, 0x52A5A0u, gen::fn_fabs_0052e118);
                t7 = 0x7C0000;
                s3 = v0;
                ld(a1, t7, -1648);  // 0x7BF990
                a0 = v0;
                jal(ctx, 0x52A5B4u, gen::fn_dpmul_00531230);
                a1 = 511;
                a0 = v0;
                a1 = dsll32(a1, 21);
                jal(ctx, 0x52A5C4u, gen::fn_dpadd_00531170);
                a0 = v0;
                jal(ctx, 0x52A5CCu, gen::fn_dptoli_005317d0);
                s6 = v0;
                a0 = v0;
                jal(ctx, 0x52A5D8u, gen::fn_litodp_00531720);
                t7 = 0x7C0000;
                s7 = v0;
                ld(a1, t7, -1680);  // 0x7BF970
                a0 = v0;
                jal(ctx, 0x52A5ECu, gen::fn_dpmul_00531230);
                a1 = v0;
                a0 = s3;
                jal(ctx, 0x52A5F8u, gen::fn_dpsub_005311c8);
                t7 = 0x7C0000;
                s5 = v0;
                ld(a1, t7, -1672);  // 0x7BF978
                a0 = s7;
                jal(ctx, 0x52A60Cu, gen::fn_dpmul_00531230);
                t7 = slti(s6, 32);
                s1 = v0;
                if (t7 != 0) {
                    // 0x0052a620
                    charge(ctx, 7);
                    t6 = 0x7C0000;
                    t7 = sll(s6, 2);
                    t6 = addiu(t6, -1888);  // &0x7BF8A0
                    t7 = addu(t7, t6);
                    lw(t5, t7, -4);
                    a0 = s5;
                    if (s0 == t5) {
                        goto L_0052a63c;
                    }
                L_0052a754:
                    charge(ctx, 3);
                    a1 = s1;
                    jal(ctx, 0x52A754u, gen::fn_dpsub_005311c8);
                    sd(v0, s2, 0);
                    goto L_0052a760;
                }
            L_0052a63c:
                charge(ctx, 10);
                a0 = s5;
                a1 = s1;
                jal(ctx, 0x52A640u, gen::fn_dpsub_005311c8);
                fp = sra(s0, 20);
                t7 = dsrl32(v0, 20);
                t7 = t7 & 0x7FF;
                s0 = subu(fp, t7);
                t6 = slti(s0, 17);
                sd(v0, s2, 0);
                if (t6 == 0) {
                    // 0x0052a664
                    charge(ctx, 35);
                    t7 = 0x7C0000;
                    a0 = s7;
                    ld(a1, t7, -1664);  // 0x7BF980
                    s3 = s5;
                    jal(ctx, 0x52A670u, gen::fn_dpmul_00531230);
                    s1 = v0;
                    a0 = s5;
                    a1 = v0;
                    jal(ctx, 0x52A680u, gen::fn_dpsub_005311c8);
                    t7 = 0x7C0000;
                    sd(v0, sp, 0x20);
                    ld(a1, t7, -1656);  // 0x7BF988
                    s5 = v0;
                    a0 = s7;
                    jal(ctx, 0x52A698u, gen::fn_dpmul_00531230);
                    s0 = v0;
                    a0 = s3;
                    a1 = s5;
                    jal(ctx, 0x52A6A8u, gen::fn_dpsub_005311c8);
                    a1 = s1;
                    a0 = v0;
                    jal(ctx, 0x52A6B4u, gen::fn_dpsub_005311c8);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x52A6C0u, gen::fn_dpsub_005311c8);
                    s1 = v0;
                    a0 = s5;
                    a1 = v0;
                    jal(ctx, 0x52A6D0u, gen::fn_dpsub_005311c8);
                    t7 = dsrl32(v0, 20);
                    t7 = t7 & 0x7FF;
                    s0 = subu(fp, t7);
                    t6 = slti(s0, 50);
                    sd(v0, s2, 0);
                    if (t6 == 0) {
                        // 0x0052a6f0
                        charge(ctx, 25);
                        t7 = 0x7C0000;
                        a0 = s7;
                        link(ctx, 0x52A6F8u);  // $ra first: the delay slot below depends on it
                        ld(a1, t7, -1640);
                        call(ctx, gen::fn_dpmul_00531230);
                        s1 = v0;
                        a0 = s5;
                        a1 = v0;
                        jal(ctx, 0x52A708u, gen::fn_dpsub_005311c8);
                        t7 = 0x7C0000;
                        s5 = v0;
                        ld(a1, t7, -1632);  // 0x7BF9A0
                        a0 = s7;
                        jal(ctx, 0x52A71Cu, gen::fn_dpmul_00531230);
                        ld(a0, sp, 0x20);
                        s0 = v0;
                        a1 = s5;
                        jal(ctx, 0x52A72Cu, gen::fn_dpsub_005311c8);
                        a1 = s1;
                        a0 = v0;
                        jal(ctx, 0x52A738u, gen::fn_dpsub_005311c8);
                        a1 = v0;
                        a0 = s0;
                        jal(ctx, 0x52A744u, gen::fn_dpsub_005311c8);
                        s1 = v0;
                        a0 = s5;
                        goto L_0052a754;
                    }
                }
            L_0052a760:
                charge(ctx, 10);
                ld(s3, s2, 0);
                a0 = s5;
                a1 = s3;
                jal(ctx, 0x52A768u, gen::fn_dpsub_005311c8);
                a1 = s1;
                a0 = v0;
                jal(ctx, 0x52A774u, gen::fn_dpsub_005311c8);
                sd(v0, s2, 8);
                s1 = v0;
                if (i64(s4) >= 0) {
                    goto L_0052a7b8;
                }
                // 0x0052a788
                charge(ctx, 7);
                s0 = 0;
                a1 = s3;
                a0 = s0;
                jal(ctx, 0x52A790u, gen::fn_dpsub_005311c8);
                sd(v0, s2, 0);
                a0 = s0;
                a1 = s1;
                goto L_0052a7a4;
            }
            // 0x0052a7c0
            charge(ctx, 4);
            t7 = t7 | 0xFFFF;
            t7 = slt(t7, s0);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = sra(s0, 20);
            if (cc) {
                // 0x0052a7e8
                charge(ctx, 11);
                t6 = dsll32(a0, 0);
                s5 = addiu(t7, -1046);
                t6 = dsra32(t6, 0);
                t7 = sll(s5, 20);
                t6 = dsll32(t6, 0);
                t7 = subu(s0, t7);
                t6 = dsrl32(t6, 0);
                t7 = dsll32(t7, 0);
                s3 = sp;
                s1 = t6 | t7;
                s0 = 1;
                for (;;) {
                    // 0x0052a814
                    charge(ctx, 16);
                    a0 = s1;
                    s0 = addiu(s0, -1);
                    jal(ctx, 0x52A818u, gen::fn_dptoli_005317d0);
                    a0 = v0;
                    jal(ctx, 0x52A820u, gen::fn_litodp_00531720);
                    sd(v0, s3, 0);
                    a0 = s1;
                    a1 = v0;
                    jal(ctx, 0x52A830u, gen::fn_dpsub_005311c8);
                    s3 = addiu(s3, 8);
                    a1 = 1047;
                    a0 = v0;
                    a1 = dsll32(a1, 20);
                    jal(ctx, 0x52A844u, gen::fn_dpmul_00531230);
                    s1 = v0;
                    if (i64(s0) < 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0052a854
                charge(ctx, 4);
                sd(v0, sp, 0x10);
                s1 = 3;
                s3 = 0;
                s0 = addiu(sp, 0x10);
                for (;;) {
                    // 0x0052a864
                    charge(ctx, 6);
                    ld(a0, s0, 0);
                    a1 = s3;
                    s0 = addiu(s0, -8);
                    jal(ctx, 0x52A86Cu, gen::fn_dpcmp_005316d0);
                    t1 = 0x7C0000;
                    if (v0 != 0) {
                        break;
                    }
                    // 0x0052a8c0
                    charge(ctx, 2);
                    s1 = addiu(s1, -1);
                    backedge(ctx);
                }
                // 0x0052a87c
                charge(ctx, 9);
                a2 = s5;
                a3 = s1;
                t1 = addiu(t1, -2152);
                a0 = sp;
                a1 = s2;
                t0 = 2;
                jal(ctx, 0x52A890u, gen::fn___kernel_rem_pio2_0052c6d0);
                s6 = v0;
                if (i64(s4) >= 0) {
                    backedge(ctx);
                L_0052a7b8:
                    charge(ctx, 2);
                    a0 = s6;
                    backedge(ctx);
                } else {
                    // 0x0052a8a0
                    charge(ctx, 7);
                    ld(a1, s2, 0);
                    a0 = s3;
                    jal(ctx, 0x52A8A4u, gen::fn_dpsub_005311c8);
                    ld(a1, s2, 8);
                    a0 = s3;
                    sd(v0, s2, 0);
                    backedge(ctx);
                L_0052a7a4:
                    charge(ctx, 5);
                    jal(ctx, 0x52A7A4u, gen::fn_dpsub_005311c8);
                    sd(v0, s2, 8);
                    a0 = subu(0, s6);
                    backedge(ctx);
                }
            } else {
                // 0x0052a7d0
                charge(ctx, 6);
                a1 = a0;
                jal(ctx, 0x52A7D0u, gen::fn_dpsub_005311c8);
                sd(v0, s2, 0);
                a0 = 0;
                sd(v0, s2, 8);
                backedge(ctx);
            }
        } else {
            // 0x0052a494
            charge(ctx, 2);
            t7 = 0x7C0000;
            if (i64(s4) <= 0) {
                // 0x0052a514
                charge(ctx, 6);
                link(ctx, 0x52A514u);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -1680);
                call(ctx, gen::fn_dpadd_00531170);
                t7 = 0x3FF90000;
                t7 = t7 | 0x21FB;
                s1 = v0;
                if (s0 == t7) {
                    // 0x0052a568
                    charge(ctx, 9);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A570u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -1664);
                    call(ctx, gen::fn_dpadd_00531170);
                    t7 = 0x7C0000;
                    s1 = v0;
                    ld(s0, t7, -1656);  // 0x7BF988
                    a0 = v0;
                    backedge(ctx);
                } else {
                    // 0x0052a52c
                    charge(ctx, 3);
                    t7 = 0x7C0000;
                    a0 = v0;
                    ld(s0, t7, -1672);  // 0x7BF978
                }
                // 0x0052a538
                charge(ctx, 12);
                a1 = s0;
                jal(ctx, 0x52A538u, gen::fn_dpadd_00531170);
                sd(v0, s2, 0);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x52A548u, gen::fn_dpsub_005311c8);
                a0 = v0;
                a1 = s0;
                jal(ctx, 0x52A554u, gen::fn_dpadd_00531170);
                sd(v0, s2, 8);
                a0 = si(-1);
                backedge(ctx);
            } else {
                // 0x0052a49c
                charge(ctx, 6);
                link(ctx, 0x52A49Cu);  // $ra first: the delay slot below depends on it
                ld(a1, t7, -1680);
                call(ctx, gen::fn_dpsub_005311c8);
                t7 = 0x3FF90000;
                t7 = t7 | 0x21FB;
                s1 = v0;
                if (s0 == t7) {
                    // 0x0052a4f0
                    charge(ctx, 9);
                    t7 = 0x7C0000;
                    a0 = v0;
                    link(ctx, 0x52A4F8u);  // $ra first: the delay slot below depends on it
                    ld(a1, t7, -1664);
                    call(ctx, gen::fn_dpsub_005311c8);
                    t7 = 0x7C0000;
                    s1 = v0;
                    ld(s0, t7, -1656);  // 0x7BF988
                    a0 = v0;
                    backedge(ctx);
                } else {
                    // 0x0052a4b4
                    charge(ctx, 3);
                    t7 = 0x7C0000;
                    a0 = v0;
                    ld(s0, t7, -1672);  // 0x7BF978
                }
                // 0x0052a4c0
                charge(ctx, 12);
                a1 = s0;
                jal(ctx, 0x52A4C0u, gen::fn_dpsub_005311c8);
                sd(v0, s2, 0);
                a1 = v0;
                a0 = s1;
                jal(ctx, 0x52A4D0u, gen::fn_dpsub_005311c8);
                a0 = v0;
                a1 = s0;
                jal(ctx, 0x52A4DCu, gen::fn_dpsub_005311c8);
                sd(v0, s2, 8);
                a0 = 1;
                backedge(ctx);
            }
        }
    } else {
        // 0x0052a440
        charge(ctx, 3);
        sd(a0, s2, 0);
        sd(zero, a1, 8);
        a0 = 0;
    }
    // 0x0052a44c (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(s0, sp, 0x30);
    v0 = a0;
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(s6, sp, 0x60);
    ld(s7, sp, 0x68);
    ld(fp, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

}  // namespace p3fes::game
