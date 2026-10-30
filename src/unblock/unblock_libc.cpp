// Phase 5 slice unblock, part libc (game/include/p3fes/game/unblock.h):
// the C runtime callees -- isinf / isnan / strncmp, libm cos / sin / fabs, libgcc __fixunssfdi / fptodp, the double
// compare helper.
// These functions were kept recompiled only because other slices' pair tests stood them in with recorders; slice
// unblock rewrote those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Started from p3fes_handgen's
// bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h): every path
// keeps the original's statements, cycle charges and check points in order; the role comments name what each does.
// Pair tests: tests/game/test_unblock.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/unblock.h"

namespace p3fes::recomp_gen {
void fn___fixunssfdi_0052eda0(p3fes::EEContext&);
void fn___floatdidf_0052eac8(p3fes::EEContext&);
void fn___ieee754_rem_pio2_0052a3f0(p3fes::EEContext&);
void fn___kernel_cos_0052c478(p3fes::EEContext&);
void fn___kernel_sin_0052d108(p3fes::EEContext&);
void fn___make_dp_00531870(p3fes::EEContext&);
void fn___unpack_f_00530d18(p3fes::EEContext&);
void fn_cos_0052e038(p3fes::EEContext&);
void fn_dpadd_00531170(p3fes::EEContext&);
void fn_dpcmp_005316d0(p3fes::EEContext&);
void fn_dpmul_00531230(p3fes::EEContext&);
void fn_dpsub_005311c8(p3fes::EEContext&);
void fn_dptoul_005318f8(p3fes::EEContext&);
void fn_fabs_0052e118(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_isinf_00523730(p3fes::EEContext&);
void fn_isnan_00523778(p3fes::EEContext&);
void fn_sin_0052e328(p3fes::EEContext&);
void fn_strncmp_00524670(p3fes::EEContext&);
void fn_sub_45EC00_0045ec00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0045EC00 sub_45EC00 -- 32 bytes; frame 0x10: ra sp+0x0
// [libgcc] [proposed: dpLess] A double compare: dpcmp($a0, $a1) < 0.
void sub_45EC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0045ec00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x45EC08u, gen::fn_dpcmp_005316d0);
    ld(ra, sp, 0x0);
    v0 = slt(v0, 0);
    sp = addiu(sp, 0x10);
}

// 0x00523730 isinf -- 72 bytes; leaf frame (no stack)
// [newlib] isinf(double) on the two words of $a0.
void isinf(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00523730
    enter(ctx, 18);  // entry check point + this block's cycles
    t6 = dsll32(a0, 0);
    t5 = 0x7FFF0000;
    t6 = dsra32(t6, 0);
    t5 = t5 | 0xFFFF;
    t4 = subu(0, t6);
    t7 = dsra32(a0, 0);
    t6 = t6 | t4;
    t7 = t7 & t5;
    t6 = srl(t6, 31);
    t5 = 0x7FF00000;
    t7 = t7 | t6;
    v0 = 1;
    t7 = subu(t5, t7);
    t6 = subu(0, t7);
    t7 = t7 | t6;
    t7 = srl(t7, 31);
    v0 = subu(v0, t7);
}

// 0x00523778 isnan -- 56 bytes; leaf frame (no stack)
// [newlib] isnan(double).
void isnan(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x00523778
    enter(ctx, 14);  // entry check point + this block's cycles
    t7 = dsll32(a0, 0);
    t6 = 0x7FFF0000;
    t7 = dsra32(t7, 0);
    t6 = t6 | 0xFFFF;
    t5 = subu(0, t7);
    v0 = dsra32(a0, 0);
    t7 = t7 | t5;
    v0 = v0 & t6;
    t7 = srl(t7, 31);
    t6 = 0x7FF00000;
    v0 = v0 | t7;
    v0 = subu(t6, v0);
    v0 = srl(v0, 31);
}

// 0x00524670 strncmp -- 440 bytes; leaf frame (no stack)
// [newlib] strncmp: word-at-a-time compare for aligned strings, then bytes.
void strncmp(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00524670
    enter(ctx, 2);  // entry check point + this block's cycles
    v1 = a0 | a1;
    if (a2 == 0) {
        // 0x00524678 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = 0;
        return;
    }
    // 0x00524680
    charge(ctx, 3);
    v0 = v1 & 0x7;
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = a2;
    if (!cc) {
        // 0x0052468c
        charge(ctx, 11);
        v0 = v1 & 0xF;
        a3 = sltiu(a2, 16);
        t1 = 0x1010000;
        t1 = t1 | 0x101;  // &0x1010101
        t1 = dsll(t1, 16);
        t1 = t1 | 0x101;
        t1 = dsll(t1, 16);
        t1 = t1 | 0x101;
        v0 = v0 | a3;
        a3 = a0;
        if (v0 != 0) {
            // 0x00524758
            charge(ctx, 3);
            v0 = sltiu(a2, 8);
            t0 = a1;
            if (v0 != 0) {
            L_005247d0:
                charge(ctx, 1);
                a0 = a3;
            L_005247d4:
                charge(ctx, 2);
                a1 = t0;
                v0 = a2;
                goto L_005247dc;
            }
            // 0x00524764
            charge(ctx, 4);
            ld(v1, a0, 0);
            ld(v0, a1, 0);
            cc = v1 != v0;  // the condition, before the delay slot changes it
            v0 = a2;
            if (cc) {
                goto L_005247dc;
            }
            // 0x00524774
            charge(ctx, 7);
            a2 = addiu(a2, -8);
            t2 = lui(0x8080);
            t2 = t2 | 0x8080;
            t2 = dsll(t2, 16);
            t2 = t2 | 0x8080;
            t2 = dsll(t2, 16);
            t2 = t2 | 0x8080;
            for (;;) {
                // 0x00524790
                charge(ctx, 2);
                if (a2 == 0) {
                    backedge(ctx);
                    // 0x00524678 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    v0 = 0;
                    return;
                }
                // 0x00524798
                charge(ctx, 7);
                ld(v0, a3, 0);
                v1 = nor(0, v0);
                v0 = v0 - t1;
                v0 = v0 & v1;
                v0 = v0 & t2;
                a3 = addiu(a3, 8);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x00524678 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    v0 = 0;
                    return;
                }
                // 0x005247b4
                charge(ctx, 3);
                v0 = sltiu(a2, 8);
                t0 = addiu(t0, 8);
                if (v0 != 0) {
                    break;
                }
                // 0x005247c0
                charge(ctx, 4);
                ld(v1, a3, 0);
                ld(v0, t0, 0);
                if (v1 != v0) {
                    break;
                }
                a2 = addiu(a2, -8);
                backedge(ctx);
            }
            goto L_005247d0;
        }
        // 0x005246b8
        charge(ctx, 16);
        lq(v1, a0, 0);
        pcpyld(t2, t1, t1);
        lq(v0, a1, 0);
        t0 = lui(0x8080);
        t0 = t0 | 0x8080;
        t0 = dsll(t0, 16);
        t0 = t0 | 0x8080;
        t0 = dsll(t0, 16);
        t0 = t0 | 0x8080;
        psubw(v1, v1, v0);
        pcpyld(t1, t0, t0);
        pcpyud(v0, v1, a0);
        t0 = a1;
        v1 = v0 | v1;
        v0 = a2;
        if (v1 != 0) {
            goto L_005247dc;
        }
        // 0x005246f8
        charge(ctx, 1);
        a2 = addiu(a2, -16);
        for (;;) {
            // 0x005246fc
            charge(ctx, 2);
            if (a2 == 0) {
                backedge(ctx);
                // 0x00524678 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                v0 = 0;
                return;
            }
            // 0x00524704
            charge(ctx, 9);
            lq(v0, a3, 0);
            pnor(v1, zero, v0);
            psubb(v0, v0, t2);
            pand(v0, v0, v1);
            pand(v1, v0, t1);
            pcpyud(v0, v1, a0);
            v0 = v0 | v1;
            a3 = addiu(a3, 16);
            if (v0 != 0) {
                backedge(ctx);
                // 0x00524678 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                v0 = 0;
                return;
            }
            // 0x00524728
            charge(ctx, 4);
            v0 = sltiu(a2, 16);
            lq(v1, a3, 0);
            t0 = addiu(t0, 16);
            if (v0 != 0) {
                goto L_005247d0;
            }
            // 0x00524738
            charge(ctx, 6);
            lq(v0, t0, 0);
            psubw(v1, v1, v0);
            pcpyud(v0, v1, a0);
            v0 = v0 | v1;
            if (v0 != 0) {
                break;
            }
            a2 = addiu(a2, -16);
            backedge(ctx);
        }
        // 0x00524750
        charge(ctx, 2);
        a0 = a3;
        goto L_005247d4;
    }
L_005247dc:
    charge(ctx, 2);
    a2 = addiu(a2, -1);
    if (v0 == 0) {
        // 0x00524818 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        lbu(v0, a1, 0);
        lbu(v1, a0, 0);
        v0 = subu(v1, v0);
        return;
    }
    // 0x005247e4
    charge(ctx, 2);
    lb(v1, a0, 0);
    for (;;) {
        // 0x0052480c
        charge(ctx, 3);
        lb(v0, a1, 0);
        lbu(a3, a0, 0);
        if (v1 != v0) {
            break;
        }
        backedge(ctx);
        // 0x005247f0
        charge(ctx, 2);
        if (a2 == 0) {
            backedge(ctx);
            // 0x00524678 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x005247f8
        charge(ctx, 2);
        a0 = addiu(a0, 1);
        if (a3 == 0) {
            backedge(ctx);
            // 0x00524678 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            v0 = 0;
            return;
        }
        // 0x00524800
        charge(ctx, 3);
        a1 = addiu(a1, 1);
        lb(v1, a0, 0);
        a2 = addiu(a2, -1);
    }
    // 0x00524818 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lbu(v0, a1, 0);
    lbu(v1, a0, 0);
    v0 = subu(v1, v0);
}

// 0x0052E038 cos -- 224 bytes; frame 0x20: ra sp+0x10
// [newlib libm] cos(double): __kernel_cos / __kernel_sin after __ieee754_rem_pio2.
void cos(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052e038
    enter(ctx, 11);  // entry check point + this block's cycles
    t7 = 0x7FFF0000;
    sp = addiu(sp, -0x20);
    t7 = t7 | 0xFFFF;
    sd(ra, sp, 0x10);
    t5 = dsra32(a0, 0);
    t6 = 0x3FE90000;
    t5 = t5 & t7;
    t6 = t6 | 0x21FB;
    t6 = slt(t6, t5);
    a1 = a0;
    if (t6 == 0) {
        // 0x0052e064
        charge(ctx, 1);
        a1 = 0;
        goto L_0052e068;
    }
    // 0x0052e07c
    charge(ctx, 5);
    t7 = 0x7FEF0000;
    t7 = t7 | 0xFFFF;
    t7 = slt(t7, t5);
    if (t7 == 0) {
        // 0x0052e090
        charge(ctx, 6);
        a1 = sp;
        jal(ctx, 0x52E090u, gen::fn___ieee754_rem_pio2_0052a3f0);
        v0 = v0 & 0x3;
        t7 = 1;
        cc = v0 == t7;  // the condition, before the delay slot changes it
        t7 = slti(v0, 2);
        if (cc) {
            // 0x0052e100
            charge(ctx, 6);
            ld(a0, sp, 0x0);
            a2 = 1;
            link(ctx, 0x52E108u);  // $ra first: the delay slot below depends on it
            ld(a1, sp, 0x8);
            call(ctx, gen::fn___kernel_sin_0052d108);
            a1 = v0;
            backedge(ctx);
        L_0052e0ec:
            charge(ctx, 1);
            a0 = 0;
            goto L_0052e0f0;
        }
        // 0x0052e0a8
        charge(ctx, 2);
        cc = t7 == 0;  // the condition, before the delay slot changes it
        t7 = 2;
        if (cc) {
            // 0x0052e0d8
            charge(ctx, 2);
            ld(a0, sp, 0x0);
            if (v0 == t7) {
                // 0x0052e0e0
                charge(ctx, 3);
                link(ctx, 0x52E0E0u);  // $ra first: the delay slot below depends on it
                ld(a1, sp, 0x8);
                call(ctx, gen::fn___kernel_cos_0052c478);
                a1 = v0;
                goto L_0052e0ec;
            }
            backedge(ctx);
        L_0052e0b8:
            charge(ctx, 5);
            a2 = 1;
            link(ctx, 0x52E0BCu);  // $ra first: the delay slot below depends on it
            ld(a1, sp, 0x8);
            call(ctx, gen::fn___kernel_sin_0052d108);
            ld(ra, sp, 0x10);
            backedge(ctx);
        } else {
            // 0x0052e0b0
            charge(ctx, 2);
            ld(a0, sp, 0x0);
            if (v0 != 0) {
                goto L_0052e0b8;
            }
            // 0x0052e0cc
            charge(ctx, 2);
            ld(a1, sp, 0x8);
            backedge(ctx);
        L_0052e068:
            charge(ctx, 3);
            jal(ctx, 0x52E068u, gen::fn___kernel_cos_0052c478);
            ld(ra, sp, 0x10);
        }
        // 0x0052e074 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x20);
        return;
    }
L_0052e0f0:
    charge(ctx, 4);
    jal(ctx, 0x52E0F0u, gen::fn_dpsub_005311c8);
    ld(ra, sp, 0x10);
    backedge(ctx);
    // 0x0052e074 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x0052E118 fabs -- 44 bytes; leaf frame (no stack)
// [newlib libm] fabs(double): the sign bit cleared.
void fabs(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15};
    // 0x0052e118
    enter(ctx, 11);  // entry check point + this block's cycles
    t7 = 0x7FFF0000;
    t6 = dsra32(a0, 0);
    t7 = t7 | 0xFFFF;
    t5 = dsll32(a0, 0);
    t6 = t6 & t7;
    t5 = dsrl32(t5, 0);
    t6 = dsll32(t6, 0);
    t6 = dsrl32(t6, 0);
    t6 = dsll32(t6, 0);
    v0 = t5 | t6;
}

// 0x0052E328 sin -- 224 bytes; frame 0x20: ra sp+0x10
// [newlib libm] sin(double).
void sin(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0052e328
    enter(ctx, 11);  // entry check point + this block's cycles
    t7 = 0x7FFF0000;
    sp = addiu(sp, -0x20);
    t7 = t7 | 0xFFFF;
    sd(ra, sp, 0x10);
    t5 = dsra32(a0, 0);
    t6 = 0x3FE90000;
    t5 = t5 & t7;
    t6 = t6 | 0x21FB;
    t6 = slt(t6, t5);
    a1 = a0;
    if (t6 == 0) {
        // 0x0052e354
        charge(ctx, 2);
        a1 = 0;
        a2 = 0;
        goto L_0052e35c;
    }
    // 0x0052e370
    charge(ctx, 5);
    t7 = 0x7FEF0000;
    t7 = t7 | 0xFFFF;
    t7 = slt(t7, t5);
    if (t7 == 0) {
        // 0x0052e384
        charge(ctx, 6);
        a1 = sp;
        jal(ctx, 0x52E384u, gen::fn___ieee754_rem_pio2_0052a3f0);
        v0 = v0 & 0x3;
        t7 = 1;
        cc = v0 == t7;  // the condition, before the delay slot changes it
        t7 = slti(v0, 2);
        if (cc) {
            // 0x0052e3f4
            charge(ctx, 5);
            ld(a0, sp, 0x0);
            link(ctx, 0x52E3F8u);  // $ra first: the delay slot below depends on it
            ld(a1, sp, 0x8);
            call(ctx, gen::fn___kernel_cos_0052c478);
            ld(ra, sp, 0x10);
            backedge(ctx);
        } else {
            // 0x0052e39c
            charge(ctx, 2);
            cc = t7 == 0;  // the condition, before the delay slot changes it
            t7 = 2;
            if (cc) {
                // 0x0052e3d8
                charge(ctx, 2);
                ld(a0, sp, 0x0);
                if (v0 != t7) {
                    backedge(ctx);
                L_0052e3ac:
                    charge(ctx, 3);
                    link(ctx, 0x52E3ACu);  // $ra first: the delay slot below depends on it
                    ld(a1, sp, 0x8);
                    call(ctx, gen::fn___kernel_cos_0052c478);
                    a1 = v0;
                } else {
                    // 0x0052e3e0
                    charge(ctx, 5);
                    a2 = 1;
                    link(ctx, 0x52E3E4u);  // $ra first: the delay slot below depends on it
                    ld(a1, sp, 0x8);
                    call(ctx, gen::fn___kernel_sin_0052d108);
                    a1 = v0;
                    backedge(ctx);
                }
                // 0x0052e3b8
                charge(ctx, 1);
                a0 = 0;
                goto L_0052e3bc;
            }
            // 0x0052e3a4
            charge(ctx, 2);
            ld(a0, sp, 0x0);
            if (v0 != 0) {
                goto L_0052e3ac;
            }
            // 0x0052e3cc
            charge(ctx, 3);
            a2 = 1;
            ld(a1, sp, 0x8);
            backedge(ctx);
        L_0052e35c:
            charge(ctx, 3);
            jal(ctx, 0x52E35Cu, gen::fn___kernel_sin_0052d108);
            ld(ra, sp, 0x10);
        }
        // 0x0052e368 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x20);
        return;
    }
L_0052e3bc:
    charge(ctx, 4);
    jal(ctx, 0x52E3BCu, gen::fn_dpsub_005311c8);
    ld(ra, sp, 0x10);
    backedge(ctx);
    // 0x0052e368 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x0052EDA0 __fixunssfdi -- 272 bytes; frame 0x20: s2 sp+0x10, ra sp+0x18, s0 sp+0x0, s1 sp+0x8
// [libgcc] __fixunssfdi: float to u64 through the soft-float doubles.
void __fixunssfdi(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0052eda0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    link(ctx, 0x52EDB0u);  // $ra first: the delay slot below depends on it
    sd(s1, sp, 0x8);
    call(ctx, gen::fn_fptodp_00530da0);
    s2 = v0;
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x52EDC0u, gen::fn_dpcmp_005316d0);
    a1 = 991;
    a0 = s2;
    a1 = dsll32(a1, 20);
    t7 = 0;
    if (i64(v0) >= 0) {
        // 0x0052eddc
        charge(ctx, 12);
        jal(ctx, 0x52EDDCu, gen::fn_dpmul_00531230);
        a0 = v0;
        jal(ctx, 0x52EDE4u, gen::fn_dptoul_005318f8);
        s1 = dsll32(v0, 0);
        s1 = dsrl32(s1, 0);
        s1 = dsll32(s1, 0);
        t7 = dsrl(s1, 1);
        t6 = s1 & 0x1;
        t6 = t6 | t7;
        a0 = s1;
        if (i64(s1) < 0) {
            // 0x0052ee94
            charge(ctx, 7);
            a0 = t6;
            jal(ctx, 0x52EE94u, gen::fn___floatdidf_0052eac8);
            a0 = v0;
            a1 = v0;
            jal(ctx, 0x52EEA0u, gen::fn_dpadd_00531170);
            a0 = s2;
            backedge(ctx);
        } else {
            // 0x0052ee0c
            charge(ctx, 3);
            jal(ctx, 0x52EE0Cu, gen::fn___floatdidf_0052eac8);
            a0 = s2;
        }
        // 0x0052ee18
        charge(ctx, 10);
        a1 = v0;
        jal(ctx, 0x52EE18u, gen::fn_dpsub_005311c8);
        s0 = 0;
        s2 = v0;
        a0 = v0;
        a1 = s0;
        jal(ctx, 0x52EE2Cu, gen::fn_dpcmp_005316d0);
        a1 = s2;
        a0 = s0;
        if (i64(v0) >= 0) {
            // 0x0052ee7c
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x52EE7Cu, gen::fn_dptoul_005318f8);
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            s1 = s1 + v0;
            backedge(ctx);
        } else {
            // 0x0052ee40
            charge(ctx, 7);
            jal(ctx, 0x52EE40u, gen::fn_dpsub_005311c8);
            a0 = v0;
            jal(ctx, 0x52EE48u, gen::fn_dptoul_005318f8);
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            s1 = s1 - v0;
        }
        // 0x0052ee5c
        charge(ctx, 1);
        t7 = s1;
    }
    // 0x0052ee60 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    v0 = t7;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00530DA0 fptodp -- 60 bytes; frame 0x30: ra sp+0x20
// [libgcc] fptodp: float to soft-float double (__unpack_f, __make_dp).
void fptodp(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00530da0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    a0 = addiu(sp, 0x10);
    swc1(f12, sp, 0x10);
    a1 = sp;
    jal(ctx, 0x530DB0u, gen::fn___unpack_f_00530d18);
    lwu(a3, sp, 0xC);
    lw(a0, sp, 0x0);
    lw(a1, sp, 0x4);
    a3 = dsll(a3, 30);
    link(ctx, 0x530DC8u);  // $ra first: the delay slot below depends on it
    lw(a2, sp, 0x8);
    call(ctx, gen::fn___make_dp_00531870);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
