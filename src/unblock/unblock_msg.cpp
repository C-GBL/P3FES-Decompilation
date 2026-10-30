// Phase 5 slice unblock, part msg (game/include/p3fes/game/unblock.h):
// the message-window helpers -- msgWin of the current window (state, show / hide), the facility window's busy
// test, fclBankManager.c's bank list and queries, the coloured string draw of frFontEx.c.
// These functions were kept recompiled only because other slices' pair tests stood them in with recorders; slice
// unblock rewrote those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Started from p3fes_handgen's
// bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h): every path
// keeps the original's statements, cycle charges and check points in order; the role comments name what each does.
// Pair tests: tests/game/test_unblock.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/unblock.h"

namespace p3fes::recomp_gen {
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontGetStyleSize_003b35c0(p3fes::EEContext&);
void fn_frFontLineFadeStep_003b0ec0(p3fes::EEContext&);
void fn_itfMesMngClearStateFlags_003a3e90(p3fes::EEContext&);
void fn_itfMesMngGetState_003a3da0(p3fes::EEContext&);
void fn_itfMesMngSetBusy_003a25f0(p3fes::EEContext&);
void fn_itfMesMngSetStateFlags_003a3e10(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_3B0030_003b0030(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7C90_003c7c90(p3fes::EEContext&);
void fn_sub_3C7D50_003c7d50(p3fes::EEContext&);
void fn_sub_3C83B0_003c83b0(p3fes::EEContext&);
void fn_sub_3CF120_003cf120(p3fes::EEContext&);
void fn_sub_3CF3A0_003cf3a0(p3fes::EEContext&);
void fn_sub_3CF440_003cf440(p3fes::EEContext&);
void fn_sub_3CF5D0_003cf5d0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x003B32D0 sub_3B32D0 -- 740 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [frFontEx.c] [proposed: frFontDrawStringColored] Draws a message string: the glyph list of ($t1 text, $t0 style, $a3
// size) built by frFontBuildGlyphList (with the palette word $a7 in 0x7CE638 during the build), its width when the
// alignment flags ask, the line drawn at ($a0, $a1) with colour $a2 by frFontDraw, then the fade step and release.
void sub_3B32D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003b32d0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    mov_s(f20, f12);
    s5 = a2;
    s6 = t0;
    s2 = t2;
    s0 = 0;
    v1 = dsll32(a3, 24);
    v1 = dsra32(v1, 24);
    v0 = 10;
    if (v1 == v0) {
        // 0x003b3328
        charge(ctx, 4);
        a3 = 5;
        v0 = s5 & 0xFF;
        if (i64(v0) < 0) {
            // 0x003b334c
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x003b3338
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x003b3368
        charge(ctx, 7);
        lwc1(f0, gp, -32604);  // 0x7CAD94
        mul_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = si(-256);
        v0 = s5 & v0;
        s5 = v0 | v1;
    }
    // 0x003b3384
    charge(ctx, 27);
    lh(v0, gp, -22512);  // 0x7CD500
    v0 = v0 | 0x1;
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-3);
    v0 = v1 & v0;
    sh(v0, gp, -22512);  // 0x7CD500
    sw(t3, gp, -18104);  // 0x7CE638
    a0 = t1;
    a1 = s6;
    a2 = a3;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x3B33B8u, gen::fn_frFontBuildGlyphList_003b0970);
    s1 = v0;
    sw(zero, gp, -18104);  // 0x7CE638
    lh(v1, gp, -22512);  // 0x7CD500
    v0 = si(-2);
    v0 = v1 & v0;
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 | 0x2;
    sh(v0, gp, -22512);  // 0x7CD500
    v0 = s2 & 0xB;
    if (v0 != 0) {
        // 0x003b33f0
        charge(ctx, 4);
        s0 = 0;
        lw(a0, s1, 28);
        for (;;) {
            // 0x003b3414
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b3400
            charge(ctx, 5);
            lw(v0, a0, 12);
            v1 = addu(s0, v0);
            lb(v0, s1, 3);
            s0 = addu(v1, v0);
            lw(a0, a0, 40);
        }
    }
    // 0x003b341c
    charge(ctx, 3);
    v0 = s2 & 0x8;
    if (v0 == 0) {
        // 0x003b3438
        charge(ctx, 3);
        v0 = s2 & 0x2;
        if (v0 != 0) {
            // 0x003b3444
            charge(ctx, 1);
            s4 = subu(s4, s0);
        }
    } else {
        // 0x003b3428
        charge(ctx, 4);
        v0 = sra(s0, 1);
        s4 = subu(s4, v0);
    }
    // 0x003b3448
    charge(ctx, 3);
    v0 = s2 & 0x4;
    if (v0 == 0) {
        // 0x003b346c
        charge(ctx, 3);
        v0 = s2 & 0x10;
        if (v0 != 0) {
            // 0x003b3478
            charge(ctx, 16);
            a0 = s6;
            jal(ctx, 0x3B347Cu, gen::fn_frFontGetStyleSize_003b35c0);
            mtc1(v0, f0);
            cvt_s_w(f3, f0);
            lwc1(f2, gp, -32628);  // 0x7CAD7C
            mtc1(s3, f0);
            cvt_s_w(f1, f0);
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f0, f2, f3);
            cvt_w_s(f0, f0);
            mfc1(s3, f0);
        }
    } else {
        // 0x003b3454
        charge(ctx, 6);
        a0 = s6;
        jal(ctx, 0x3B3458u, gen::fn_frFontGetStyleSize_003b35c0);
        s3 = subu(s3, v0);
    }
    // 0x003b34b8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x003b34c0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10032);  // "frFont.c"
        a1 = 2188;
        jal(ctx, 0x3B34CCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b34d4
    charge(ctx, 6);
    v0 = sll(s4, 4);
    sw(v0, s1, 4);
    v0 = sll(s3, 3);
    sw(v0, s1, 8);
    if (s1 == 0) {
        // 0x003b34ec
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10376);  // "frFontEx.c"
        a1 = 19;
        jal(ctx, 0x3B34F8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003b3500
    charge(ctx, 4);
    swc1(f20, s1, 20);
    v1 = s1;
    for (;;) {
        // 0x003b353c
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b3510
        charge(ctx, 3);
        lw(v0, v1, 28);
        for (;;) {
            // 0x003b3524
            charge(ctx, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003b351c
            charge(ctx, 2);
            sw(s5, v0, 16);
            lw(v0, v0, 40);
        }
        // 0x003b3538
        charge(ctx, 1);
        lw(v1, v1, 36);
    }
    // 0x003b3544
    charge(ctx, 12);
    a0 = s1;
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x3B3550u, gen::fn_frFontDraw_003b1360);
    a0 = s1;
    jal(ctx, 0x3B355Cu, gen::fn_frFontLineFadeStep_003b0ec0);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    if (v0 == 0) {
        // 0x003b3574
        charge(ctx, 3);
        a0 = s1;
        jal(ctx, 0x3B3578u, gen::fn_sub_3B0030_003b0030);
    }
    // 0x003b3580 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s0;
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003C7850 sub_3C7850 -- 120 bytes; frame 0x10: ra sp+0x0
// [msgWin] [proposed: msgWinGetState] The current message window's state byte (+4), or 0 when there is none, its handle is
// negative, or it is closing (+5) in state 2.
void sub_3C7850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7850
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3C7858u, gen::fn_sub_3C7D50_003c7d50);
    if (v0 != 0) {
        // 0x003c7874
        charge(ctx, 3);
        lw(v1, v0, 0);
        if (i64(v1) >= 0) {
            // 0x003c788c
            charge(ctx, 3);
            lb(v1, v0, 5);
            if (v1 != 0) {
                // 0x003c7898
                charge(ctx, 4);
                lb(a0, v0, 4);
                v1 = 2;
                if (a0 != v1) {
                    goto L_003c78b4;
                }
                // 0x003c78a8
                charge(ctx, 3);
                v0 = 0;
                // 0x003c78b8 (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(ra, sp, 0x0);
                sp = addiu(sp, 0x10);
                return;
            }
        L_003c78b4:
            charge(ctx, 1);
            lb(v0, v0, 4);
        } else {
            // 0x003c7880
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003c7868
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c78b8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003C7C90 sub_3C7C90 -- 180 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [msgWin] [proposed: msgWinSetVisible] Shows ($a0 != 0: state flags 0x800000 / 0x100000 cleared, +5 = 0, busy, state 1)
// or hides (flags set, +5 = 1) the current message window.
void sub_3C7C90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c7c90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3C7CA4u, gen::fn_sub_3C7D50_003c7d50);
    s0 = v0;
    if (s0 != 0) {
        // 0x003c7cb8
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x003c7d04
            charge(ctx, 10);
            lw(a0, s0, 0);
            a1 = 0x800000;
            jal(ctx, 0x3C7D0Cu, gen::fn_itfMesMngSetStateFlags_003a3e10);
            lw(a0, s0, 0);
            a1 = 0x100000;
            jal(ctx, 0x3C7D1Cu, gen::fn_itfMesMngSetStateFlags_003a3e10);
            v1 = 1;
            sb(v1, s0, 5);
        } else {
            // 0x003c7cc0
            charge(ctx, 17);
            lw(a0, s0, 0);
            a1 = 0x800000;
            jal(ctx, 0x3C7CC8u, gen::fn_itfMesMngClearStateFlags_003a3e90);
            lw(a0, s0, 0);
            a1 = 0x100000;
            jal(ctx, 0x3C7CD8u, gen::fn_itfMesMngClearStateFlags_003a3e90);
            sb(zero, s0, 5);
            lw(a0, s0, 0);
            a1 = 1;
            jal(ctx, 0x3C7CECu, gen::fn_itfMesMngSetBusy_003a25f0);
            v1 = 1;
            sb(v1, s0, 4);
        }
    }
    // 0x003c7d2c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003C83B0 sub_3C83B0 -- 72 bytes; frame 0x10: ra sp+0x0
// [msgWin] Is the facility message window busy: its manager state has bits 0x3300.
void sub_3C83B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c83b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    v0 = addiu(v0, -16752);  // &0x95BE90
    if (v0 != 0) {
        // 0x003c83d4
        charge(ctx, 5);
        lw(a0, v0, 0);
        jal(ctx, 0x3C83D8u, gen::fn_itfMesMngGetState_003a3da0);
        v0 = v0 & 0x3300;
        v0 = sltu(0, v0);
    } else {
        // 0x003c83c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003c83e8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003CF120 sub_3CF120 -- 56 bytes; frame 0x10: ra sp+0x0
// [fclBankManager.c] Creates the bank list object (nmListObjCreate(64)) into 0x7CE680 and returns its payload (+36).
void sub_3CF120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf120
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 64;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3CF138u, gen::fn_sub_3C44D0_003c44d0);
    sw(v0, gp, -18032);  // 0x7CE680
    lw(v0, v0, 36);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003CF3A0 sub_3CF3A0 -- 148 bytes; leaf frame (no stack)
// [fclBankManager.c] The data of the first of the three bank entries that is used (bit 0) and loaded (bit 3) with bit 8
// equal to $a0, or 0.
void sub_3CF3A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x003cf3a0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, -18032);  // 0x7CE680
    lw(v0, v0, 36);
    a2 = addiu(v0, 4);
    a1 = 0;
    for (;;) {
        // 0x003cf41c
        charge(ctx, 3);
        v0 = slti(a1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf3b8
        charge(ctx, 4);
        lh(v1, a2, 0);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x003cf3c8
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                goto L_003cf414;
            }
            // 0x003cf3d4
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x003cf3dc
                charge(ctx, 3);
                v0 = v1 & 0x100;
                if (v0 == 0) {
                    goto L_003cf3f4;
                }
                goto L_003cf3e8_5;
            }
        L_003cf3f4:
            charge(ctx, 2);
            if (a0 != 0) {
                goto L_003cf414;
            }
            // 0x003cf3fc
            charge(ctx, 3);
            v0 = v1 & 0x100;
            if (v0 != 0) {
                goto L_003cf414;
            }
            goto L_003cf408_8;
        }
    L_003cf414:
        charge(ctx, 2);
        a2 = addiu(a2, 20);
        a1 = addiu(a1, 1);
    }
    // 0x003cf428
    charge(ctx, 1);
    v0 = 0;
    // 0x003cf42c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003cf3e8_5:
    charge(ctx, 3);
    lw(v0, a2, 4);
    // 0x003cf42c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003cf408_8:
    charge(ctx, 3);
    lw(v0, a2, 4);
    // 0x003cf42c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003CF440 sub_3CF440 -- 216 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBankManager.c] [proposed: fclBankManagerReleaseAll] Marks every used bank for release (0x400 when loaded or
// loading; 0x800 unless flag 5145) and removes every node of the bank list.
void sub_3CF440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf440
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -18032);  // 0x7CE680
    lw(v1, v1, 36);
    s0 = addiu(v1, 4);
    s1 = 0;
    for (;;) {
        // 0x003cf4c4
        charge(ctx, 3);
        v1 = slti(s1, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf468
        charge(ctx, 4);
        lh(a0, s0, 0);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            // 0x003cf478
            charge(ctx, 3);
            v0 = a0 & 0x8;
            if (v0 == 0) {
                // 0x003cf484
                charge(ctx, 3);
                v0 = a0 & 0x2;
                if (v0 != 0) {
                    goto L_003cf490;
                }
                goto L_003cf49c;
            }
        L_003cf490:
            charge(ctx, 3);
            lh(v0, s0, 0);
            v0 = v0 | 0x400;
            sh(v0, s0, 0);
        L_003cf49c:
            charge(ctx, 5);
            a0 = 5145;
            jal(ctx, 0x3CF4A0u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x003cf4b0
                charge(ctx, 3);
                lh(v1, s0, 0);
                v1 = v1 | 0x800;
                sh(v1, s0, 0);
            }
        }
        // 0x003cf4bc
        charge(ctx, 2);
        s0 = addiu(s0, 20);
        s1 = addiu(s1, 1);
    }
    // 0x003cf4d0
    charge(ctx, 4);
    lw(v1, gp, -18032);  // 0x7CE680
    lw(a2, v1, 4);
    for (;;) {
        // 0x003cf4f8
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf4e0
        charge(ctx, 6);
        lw(s0, a2, 16);
        lw(a0, gp, -18032);  // 0x7CE680
        a1 = addiu(a0, 4);
        jal(ctx, 0x3CF4ECu, gen::fn_sub_3C49E0_003c49e0);
        a2 = s0;
    }
    // 0x003cf500
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CF5D0 sub_3CF5D0 -- 88 bytes; leaf frame (no stack)
// [fclBankManager.c] Marks every used bank that has not loaded yet with 0x800.
void sub_3CF5D0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x003cf5d0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -18032);  // 0x7CE680
    lw(v1, v1, 36);
    a1 = addiu(v1, 4);
    a2 = 0;
    for (;;) {
        // 0x003cf614
        charge(ctx, 3);
        v1 = slti(a2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf5e8
        charge(ctx, 4);
        lh(a0, a1, 0);
        v1 = a0 & 0x1;
        if (v1 != 0) {
            // 0x003cf5f8
            charge(ctx, 3);
            v1 = a0 & 0x8;
            if (v1 == 0) {
                // 0x003cf604
                charge(ctx, 2);
                v1 = a0 | 0x800;
                sh(v1, a1, 0);
            }
        }
        // 0x003cf60c
        charge(ctx, 2);
        a1 = addiu(a1, 20);
        a2 = addiu(a2, 1);
    }
    // 0x003cf620
    charge(ctx, 2);
}

}  // namespace p3fes::game
