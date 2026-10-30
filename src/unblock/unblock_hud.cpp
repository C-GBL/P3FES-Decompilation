// Phase 5 slice unblock, part hud (game/include/p3fes/game/unblock.h):
// the 2D layer of 0x100000-0x116000 -- the cursor task, the h_fade.c colour fades, the debug text screen, the AFS /
// movie / cut-in / animation-stream tasks, the sound request, the sprite handles (sprCreateHandle and its release).
// These functions were kept recompiled only because other slices' pair tests stood them in with recorders; slice
// unblock rewrote those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Started from p3fes_handgen's
// bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h): every path
// keeps the original's statements, cycle charges and check points in order; the role comments name what each does.
// Pair tests: tests/game/test_unblock.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/unblock.h"

namespace p3fes::recomp_gen {
void fn_H_Cursor_CreateTask_001005b0(p3fes::EEContext&);
void fn_H_Sndcom_PlayVoice_0010db60(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcmp_00524128(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_103C30_00103c30(p3fes::EEContext&);
void fn_sub_103CB0_00103cb0(p3fes::EEContext&);
void fn_sub_104D10_00104d10(p3fes::EEContext&);
void fn_sub_1071B0_001071b0(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_1086D0_001086d0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10A770_0010a770(p3fes::EEContext&);
void fn_sub_10BC20_0010bc20(p3fes::EEContext&);
void fn_sub_10BDA0_0010bda0(p3fes::EEContext&);
void fn_sub_110F80_00110f80(p3fes::EEContext&);
void fn_sub_1114B0_001114b0(p3fes::EEContext&);
void fn_sub_111500_00111500(p3fes::EEContext&);
void fn_sub_111530_00111530(p3fes::EEContext&);
void fn_sub_111580_00111580(p3fes::EEContext&);
void fn_sub_111CA0_00111ca0(p3fes::EEContext&);
void fn_sub_111F00_00111f00(p3fes::EEContext&);
void fn_sub_111F10_00111f10(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115DE0_00115de0(p3fes::EEContext&);
void fn_vsprintf_005288c8(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001005B0 H_Cursor_CreateTask -- 352 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Cursor] Makes the cursor draw task: a 336-byte work block from the RW calloc slot (0x960184), then
// kwlnTaskCreate(parent $a0, "H CURSOR Draw", priority 6335, H_Cursor_UpdateDrawTask / H_Cursor_DestroyDrawTask, work).
// On success the work gets the scale $f12 (+300), the position $a1 (+276, two floats), the rectangle $a2[0..3] (+284) and
// the colour bytes of $a3 repeated in the four corner colours (+304..+319); +320 = 1 (shown). Returns the task, or 0 when
// the allocation or the task creation fails.
void H_Cursor_CreateTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001005b0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    mov_s(f20, f12);
    sd(a1, sp, 0x40);
    sw(a3, sp, 0x4C);
    lwc1(f3, a2, 0);
    lwc1(f2, a2, 4);
    lwc1(f1, a2, 8);
    lwc1(f0, a2, 12);
    swc1(f3, sp, 0x50);
    swc1(f2, sp, 0x54);
    swc1(f1, sp, 0x58);
    swc1(f0, sp, 0x5C);
    a0 = 1;
    a1 = 336;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x100608u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00100628
        charge(ctx, 13);
        a0 = s1;
        a1 = 0x5D0000;
        a1 = addiu(a1, -9344);  // "H CURSOR Draw"
        a2 = 6335;
        a3 = 0x100000;
        a3 = addiu(a3, 560);  // &H_Cursor_UpdateDrawTask
        t0 = 0x100000;
        t0 = addiu(t0, 1408);  // &H_Cursor_DestroyDrawTask
        t1 = s0;
        jal(ctx, 0x10064Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00100668
            charge(ctx, 35);
            swc1(f20, s0, 300);
            lwc1(f1, sp, 0x40);
            lwc1(f0, sp, 0x44);
            swc1(f1, s0, 276);
            swc1(f0, s0, 280);
            lwc1(f3, sp, 0x50);
            lwc1(f2, sp, 0x54);
            lwc1(f1, sp, 0x58);
            lwc1(f0, sp, 0x5C);
            swc1(f3, s0, 284);
            swc1(f2, s0, 288);
            swc1(f1, s0, 292);
            swc1(f0, s0, 296);
            lbu(a2, sp, 0x4C);
            lbu(a1, sp, 0x4D);
            lbu(a0, sp, 0x4E);
            lbu(v1, sp, 0x4F);
            sb(a2, s0, 304);
            sb(a1, s0, 305);
            sb(a0, s0, 306);
            sb(v1, s0, 307);
            sb(a2, s0, 308);
            sb(a1, s0, 309);
            sb(a0, s0, 310);
            sb(v1, s0, 311);
            sb(a2, s0, 312);
            sb(a1, s0, 313);
            sb(a0, s0, 314);
            sb(v1, s0, 315);
            sb(a2, s0, 316);
            sb(a1, s0, 317);
            sb(a0, s0, 318);
            sb(v1, s0, 319);
            v1 = 1;
            sw(v1, s0, 320);
        } else {
            // 0x0010065c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0010061c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001006f4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00103C30 sub_103C30 -- 128 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [h_fade.c] [proposed: fadeRequestBlack] Requests a colour fade on the fade record 0x7CDE90 when option flag 387 (fades
// enabled) is set: kind 2, colour ($a0 -> +24, $a2 -> +16, $a3 -> +12, $a1 -> +4), the counters +8 / +20 cleared.
// Returns datGetFlag(387).
void sub_103C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00103c30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    a0 = 387;
    jal(ctx, 0x103C5Cu, gen::fn_datGetFlag_0016f190);
    v1 = 1;
    if (v0 == v1) {
        // 0x00103c70
        charge(ctx, 8);
        sh(s3, gp, -20040);  // 0x7CDEA8
        sh(zero, gp, -20044);  // 0x7CDEA4
        sh(s1, gp, -20048);  // 0x7CDEA0
        sh(s0, gp, -20052);  // 0x7CDE9C
        sh(s2, gp, -20060);  // 0x7CDE94
        v1 = 2;
        sh(v1, gp, -20064);  // 0x7CDE90
        sh(zero, gp, -20056);  // 0x7CDE98
    }
    // 0x00103c90 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00103CB0 sub_103CB0 -- 56 bytes; leaf frame (no stack)
// [h_fade.c] [proposed: fadeReset] Clears the fade record 0x7CDE90 (kind 1 = none, colour and counters 0) and the two
// fade words 0x7E09DE / 0x7E09E0.
void sub_103CB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, gp{ctx, 28};
    // 0x00103cb0
    enter(ctx, 14);  // entry check point + this block's cycles
    sh(zero, gp, -20040);  // 0x7CDEA8
    sh(zero, gp, -20044);  // 0x7CDEA4
    sh(zero, gp, -20048);  // 0x7CDEA0
    sh(zero, gp, -20052);  // 0x7CDE9C
    sh(zero, gp, -20060);  // 0x7CDE94
    v1 = 1;
    sh(v1, gp, -20064);  // 0x7CDE90
    sh(zero, gp, -20056);  // 0x7CDE98
    v1 = 0x7E0000;
    sh(zero, v1, 2526);  // 0x7E09DE
    v1 = 0x7E0000;
    sh(zero, v1, 2528);  // 0x7E09E0
}

// 0x00104D10 sub_104D10 -- 416 bytes; frame 0x1B0: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [debug] [proposed: dbgPrintAt] The debug text screen: vsprintf(buf, fmt, ...) into a 256-byte stack buffer, then the
// characters go into the 53 x 40 character grid 0x7E1E30 at column (int)x, row (int)y of the packed position $a0 (two
// floats); '\n' returns to the start column one row down; the copy stops at the NUL, at 256 characters, or at the grid's
// edge (x >= 53.0 or y >= 40.0 as floats, or the running column / row). The printf("ERROR \n") branch for row 39 past
// column 52 cannot be reached: the column has been checked against 53 just before.
void sub_104D10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x00104d10
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x160);
    sw(a1, sp, 0x170);
    sd(a2, sp, 0x180);
    sd(a3, sp, 0x188);
    sd(t0, sp, 0x190);
    sd(t1, sp, 0x198);
    sd(t2, sp, 0x1A0);
    sd(t3, sp, 0x1A8);
    lwc1(f20, sp, 0x164);
    v1 = 2;
    v0 = slti(v1, 8);
    if (v0 != 0) {
        // 0x00104d6c
        charge(ctx, 3);
        v0 = 8;
        v0 = subu(v0, v1);
        v1 = sll(v0, 3);
    } else {
        // 0x00104d60
        charge(ctx, 3);
        v1 = 0;
    }
    // 0x00104d78
    charge(ctx, 15);
    v0 = addiu(sp, 0x1B0);
    a2 = subu(v0, v1);
    a0 = addiu(sp, 0x60);
    lw(a1, sp, 0x170);
    jal(ctx, 0x104D88u, gen::fn_vsprintf_005288c8);
    lwc1(f0, sp, 0x160);
    cvt_w_s(f0, f0);
    mfc1(s2, f0);
    cvt_w_s(f0, f20);
    mfc1(s1, f0);
    s3 = 0;
    s0 = s2;
    for (;;) {
        // 0x00104e80
        charge(ctx, 3);
        v1 = slti(s3, 256);
        if (v1 != 0) {
            backedge(ctx);
            // 0x00104db4
            charge(ctx, 7);
            lwc1(f1, sp, 0x160);
            v1 = 0x42540000;
            mtc1(v1, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x00104dd0
                charge(ctx, 6);
                v1 = 0x42200000;
                mtc1(v1, f0);
                c_lt_s(f20, f0);
                if (cond(ctx)) {
                    // 0x00104de8
                    charge(ctx, 3);
                    at = slti(s2, 53);
                    if (at != 0) {
                        // 0x00104df4
                        charge(ctx, 3);
                        at = slti(s1, 40);
                        if (at != 0) {
                            // 0x00104e00
                            charge(ctx, 5);
                            v1 = addu(s3, sp);
                            v1 = addiu(v1, 96);
                            lb(a1, v1, 0);
                            if (a1 != 0) {
                                // 0x00104e14
                                charge(ctx, 3);
                                v1 = 10;
                                if (a1 != v1) {
                                    // 0x00104e30
                                    charge(ctx, 3);
                                    v1 = 39;
                                    if (s1 == v1) {
                                        // 0x00104e3c
                                        charge(ctx, 3);
                                        v1 = slti(s2, 53);
                                        if (v1 != 0) {
                                            goto L_00104e5c;
                                        }
                                        // 0x00104e48
                                        charge(ctx, 5);
                                        a0 = addiu(gp, -31336);  // "ERROR \n"
                                        jal(ctx, 0x104E4Cu, gen::fn_printf_005225a8);
                                        goto L_00104e78;
                                    }
                                L_00104e5c:
                                    charge(ctx, 7);
                                    v1 = 53;
                                    mult(a0, s1, v1);
                                    v1 = 0x7E0000;
                                    v1 = addiu(v1, 7728);  // &0x7E1E30
                                    v1 = addu(v1, a0);
                                    v1 = addu(s2, v1);
                                    sb(a1, v1, 0);
                                L_00104e78:
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 1);
                                } else {
                                    // 0x00104e20
                                    charge(ctx, 4);
                                    s2 = s0;
                                    s1 = addiu(s1, 1);
                                }
                                // 0x00104e7c
                                charge(ctx, 1);
                                s3 = addiu(s3, 1);
                                continue;
                            }
                        }
                    }
                }
            }
        }
        break;
    }
    // 0x00104e8c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1B0);
}

// 0x001071B0 sub_1071B0 -- 64 bytes; frame 0x10: ra sp+0x0
// [h_fade.c] Ends the fade task: if a fade is running (0x7CDED4), clears the flag and destroys its kwln task (0x7CDED8)
// with its hierarchy.
void sub_1071B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001071b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, -19996);  // 0x7CDED4
    if (v1 != 0) {
        // 0x001071c4
        charge(ctx, 4);
        sw(zero, gp, -19996);  // 0x7CDED4
        lw(a0, gp, -19992);  // 0x7CDED8
        if (a0 != 0) {
            // 0x001071d4
            charge(ctx, 3);
            jal(ctx, 0x1071D4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
            sw(zero, gp, -19992);  // 0x7CDED8
        }
    }
    // 0x001071e0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00108570 sub_108570 -- 68 bytes; leaf frame (no stack)
// [h_fade.c] [proposed: fadeStartOut] Starts a fade-out when none runs: duration 15 (0x7CDF00), running flag 0x7CDED4 = 1,
// phase 0x7CDEFC = 0, the three colour bytes and the speed word 0x7CDF08 cleared. Returns 1, or 0 when a fade already runs.
void sub_108570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, gp{ctx, 28};
    // 0x00108570
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19996);  // 0x7CDED4
    if (v0 != 0) {
        // 0x001085a8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0010857c
        charge(ctx, 11);
        v0 = 15;
        sh(v0, gp, -19952);  // 0x7CDF00
        v0 = 1;
        sw(v0, gp, -19996);  // 0x7CDED4
        sh(zero, gp, -19956);  // 0x7CDEFC
        sb(zero, gp, -19960);  // 0x7CDEF8
        sb(zero, gp, -19964);  // 0x7CDEF4
        sb(zero, gp, -19968);  // 0x7CDEF0
        sh(zero, gp, -19944);  // 0x7CDF08
    }
    // 0x001085ac (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001085C0 sub_1085C0 -- 172 bytes; frame 0x10: ra sp+0x0
// [h_fade.c] [proposed: fadeStartIn] Turns a finished fade-out (running, phase 3) into a fade-in: duration 15, phase 4;
// at time slot 8 with flag 5138 set the flag is cleared and the fade becomes a slow one (40 / 40, speed 7). Returns 1, or 0
// when no fade-out has finished.
void sub_1085C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001085c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -19996);  // 0x7CDED4
    if (v0 != 0) {
        // 0x001085d4
        charge(ctx, 4);
        lh(v1, gp, -19956);  // 0x7CDEFC
        v0 = 3;
        if (v1 != v0) {
            goto L_00108658;
        }
        // 0x001085e4
        charge(ctx, 12);
        v0 = 15;
        sh(v0, gp, -19952);  // 0x7CDF00
        v0 = 1;
        sw(v0, gp, -19996);  // 0x7CDED4
        v0 = 4;
        sh(v0, gp, -19956);  // 0x7CDEFC
        jal(ctx, 0x1085FCu, gen::fn_datGetTime_0016ef30);
        v1 = v0 & 0xFF;
        v0 = 8;
        if (v1 == v0) {
            // 0x00108614
            charge(ctx, 5);
            a0 = 5138;
            jal(ctx, 0x108618u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00108628
                charge(ctx, 9);
                a0 = 5138;
                a1 = 0;
                jal(ctx, 0x108630u, gen::fn_datSetFlag_0016f1f0);
                v0 = 40;
                sh(v0, gp, -19952);  // 0x7CDF00
                sh(v0, gp, -19948);  // 0x7CDF04
                v0 = 7;
                sh(v0, gp, -19944);  // 0x7CDF08
            }
        }
        // 0x0010864c
        charge(ctx, 3);
        v0 = 1;
        // 0x0010865c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_00108658:
    charge(ctx, 1);
    v0 = 0;
    // 0x0010865c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00108670 sub_108670 -- 12 bytes; leaf frame (no stack)
// [h_fade.c] Sets the fade speed word 0x7CDF08.
void sub_108670(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28};
    // 0x00108670
    enter(ctx, 3);  // entry check point + this block's cycles
    sh(a0, gp, -19944);  // 0x7CDF08
}

// 0x001086A0 sub_1086A0 -- 40 bytes; leaf frame (no stack)
// [h_fade.c] Sets the fade duration 0x7CDF00 and clamps the frame counter 0x7CDF04 to it.
void sub_1086A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x001086a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sh(a0, gp, -19952);  // 0x7CDF00
    lh(a1, gp, -19948);  // 0x7CDF04
    v1 = dsll32(a0, 16);
    v1 = dsra32(v1, 16);
    at = slt(v1, a1);
    if (at != 0) {
        // 0x001086bc
        charge(ctx, 1);
        sh(a0, gp, -19948);  // 0x7CDF04
    }
    // 0x001086c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001086D0 sub_1086D0 -- 52 bytes; leaf frame (no stack)
// [h_fade.c] Is a fade-out finished: running (0x7CDED4) and phase 3.
void sub_1086D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28};
    // 0x001086d0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19996);  // 0x7CDED4
    if (v0 != 0) {
        // 0x001086dc
        charge(ctx, 4);
        lh(v1, gp, -19956);  // 0x7CDEFC
        v0 = 3;
        if (v1 != v0) {
            goto L_001086f8;
        }
        // 0x001086ec
        charge(ctx, 3);
        v0 = 1;
        // 0x001086fc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_001086f8:
    charge(ctx, 1);
    v0 = 0;
    // 0x001086fc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00108710 sub_108710 -- 44 bytes; leaf frame (no stack)
// [h_fade.c] Is the screen free: no fade running, or the fade-out finished (phase 3).
void sub_108710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x00108710
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -19996);  // 0x7CDED4
    if (v0 == 0) {
        // 0x00108730
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x0010871c
        charge(ctx, 5);
        lh(v0, gp, -19956);  // 0x7CDEFC
        v0 = v0 ^ 0x3;
        v0 = sltiu(v0, 1);
    }
    // 0x00108734 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0010A4E0 sub_10A4E0 -- 32 bytes; frame 0x10: ra sp+0x0
// [sound] [proposed: sndPlaySe] The sound-effect request: a tail call of H_Sndcom_PlayVoice with the caller's arguments.
void sub_10A4E0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0010a4e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x10A4E8u, gen::fn_H_Sndcom_PlayVoice_0010db60);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0010A770 sub_10A770 -- 240 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [h_afs.c] [proposed: afsCreateSetTask] Makes the "H_AfsSetProc" task (priority 6335, sub_10A5A0 / sub_10A6D0) with a
// 36-byte work: the file index $a1 (+4), the destination $a3 (+8), $t0 (+12), $t1 (+16), the volume $a2 (+28).
void sub_10A770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010a770
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s6 = t1;
    a0 = 1;
    a1 = 36;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x10A7C0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0010a7e0
        charge(ctx, 13);
        a0 = s5;
        a1 = 0x5D0000;
        a1 = addiu(a1, 18216);  // "H_AfsSetProc"
        a2 = 6335;
        a3 = 0x110000;
        a3 = addiu(a3, -23136);  // &sub_10A5A0
        t0 = 0x110000;
        t0 = addiu(t0, -22832);  // &sub_10A6D0
        t1 = s0;
        jal(ctx, 0x10A804u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0010a820
            charge(ctx, 5);
            sw(s2, s0, 8);
            sw(s1, s0, 12);
            sw(s6, s0, 16);
            sw(s4, s0, 4);
            sw(s3, s0, 28);
        } else {
            // 0x0010a814
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0010a7d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0010a834 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0010BC20 sub_10BC20 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [h_sfd.c] [proposed: sfdCreatePlayTask] Makes the "H_SfdPlay" movie task (priority 7383, sub_10A860 / sub_10BB00) with a
// 544-byte work: the movie number $a1 (+490), +500 = 1.
void sub_10BC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010bc20
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 544;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x10BC50u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0010bc70
        charge(ctx, 13);
        a0 = s2;
        a1 = 0x5D0000;
        a1 = addiu(a1, 21144);  // "H_SfdPlay"
        a2 = 7383;
        a3 = 0x110000;
        a3 = addiu(a3, -22432);  // &sub_10A860
        t0 = 0x110000;
        t0 = addiu(t0, -17664);  // &sub_10BB00
        t1 = s0;
        jal(ctx, 0x10BC94u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0010bcb0
            charge(ctx, 3);
            v1 = 1;
            sw(v1, s0, 500);
            sh(s1, s0, 490);
        } else {
            // 0x0010bca4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0010bc64
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0010bcbc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0010BDA0 sub_10BDA0 -- 180 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [h_sfd.c] Makes the "H_SfdPlay" movie task for movie 7 (+490), +500 / +508 cleared, and keeps the task in 0x7CDF14.
void sub_10BDA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0010bda0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 544;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x10BDC8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0010bde8
        charge(ctx, 13);
        a0 = s1;
        a1 = 0x5D0000;
        a1 = addiu(a1, 21144);  // "H_SfdPlay"
        a2 = 7383;
        a3 = 0x110000;
        a3 = addiu(a3, -22432);  // &sub_10A860
        t0 = 0x110000;
        t0 = addiu(t0, -17664);  // &sub_10BB00
        t1 = s0;
        jal(ctx, 0x10BE0Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0010be28
            charge(ctx, 5);
            v1 = 7;
            sh(v1, s0, 490);
            sw(zero, s0, 500);
            sw(zero, s0, 508);
            sw(v0, gp, -19932);  // 0x7CDF14
        } else {
            // 0x0010be1c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0010bddc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0010be3c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00110F80 sub_110F80 -- 456 bytes; frame 0x150: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [h_cutin.c] [proposed: cutinCreatePlayer] Makes the "H_CutInPlayer" task (auto priority 4207, sub_1107D0 / sub_110E70)
// with a 788-byte work: the four halfwords of $a1 (+168..+174) name the cut-in "c%02d_%d%x%02d.cpk"; the path
// "cutin/shape/<name>" goes to +252 and "cutin/shape/" to +508; printf "*** REQ CUTIN %s"; an unknown shape falls back to
// c01_1100.cpk ("No hit cutin data").
void sub_110F80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00110f80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    sd(a1, sp, 0x48);
    a0 = 1;
    a1 = 788;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x110FB0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00110fd0
        charge(ctx, 14);
        a0 = s1;
        a1 = 4207;
        a2 = 0x5D0000;
        a2 = addiu(a2, 27240);  // "H_CutInPlayer"
        a3 = 0x110000;
        a3 = addiu(a3, 2000);  // &sub_1107D0
        t0 = 0x110000;
        t0 = addiu(t0, 3696);  // &sub_110E70
        t1 = s0;
        jal(ctx, 0x110FF4u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        if (s1 != 0) {
            // 0x00111014
            charge(ctx, 31);
            lh(a0, sp, 0x48);
            lh(v1, sp, 0x4A);
            lh(v0, sp, 0x4C);
            lh(t1, sp, 0x4E);
            sh(a0, s0, 168);
            sh(v1, s0, 170);
            sh(v0, s0, 172);
            sh(t1, s0, 174);
            lh(a2, s0, 168);
            lh(a3, s0, 170);
            lh(t0, s0, 172);
            a0 = addiu(sp, 0x50);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27264);  // "c%02d_%d%x%02d.cpk"
            jal(ctx, 0x11104Cu, gen::fn_sprintf_00523ac8);
            a0 = 0x5D0000;
            a0 = addiu(a0, 27296);  // "*** REQ CUTIN %s\n"
            a1 = addiu(sp, 0x50);
            jal(ctx, 0x111060u, gen::fn_printf_005225a8);
            a0 = addiu(s0, 508);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27320);  // "cutin/shape/"
            jal(ctx, 0x111074u, gen::fn_strcpy_00524270);
            v0 = 1;
            sw(v0, s0, 784);
            s2 = 0;
            for (;;) {
                // 0x001110f8
                charge(ctx, 3);
                v0 = slti(s2, 10000);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00111090
                charge(ctx, 8);
                v1 = sll(s2, 2);
                v0 = 0x5D0000;
                v0 = addiu(v0, 26336);  // &0x5D66E0
                v0 = addu(v0, v1);
                lw(a1, v0, 0);
                lb(v0, a1, 0);
                if (v0 == 0) {
                    break;
                }
                // 0x001110b0
                charge(ctx, 5);
                a0 = addiu(sp, 0x50);
                jal(ctx, 0x1110B4u, gen::fn_strcmp_00524128);
                if (v0 == 0) {
                    goto L_001110c4_7;
                }
                // 0x001110f4
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00111104
            charge(ctx, 10);
            a0 = 0x5D0000;
            a0 = addiu(a0, 27376);  // "No hit cutin data\n"
            jal(ctx, 0x11110Cu, gen::fn_printf_005225a8);
            a0 = addiu(s0, 252);
            a1 = 0x5D0000;
            a1 = addiu(a1, 27408);  // "cutin/shape/c01_1100.cpk"
            jal(ctx, 0x111120u, gen::fn_sprintf_00523ac8);
            v0 = s1;
        } else {
            // 0x00111008
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00110fc4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011112c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
    return;
L_001110c4_7:
    charge(ctx, 12);
    lh(a2, s0, 168);
    lh(a3, s0, 170);
    lh(t0, s0, 172);
    lh(t1, s0, 174);
    a0 = addiu(s0, 252);
    a1 = 0x5D0000;
    a1 = addiu(a1, 27344);  // "cutin/shape/c%02d_%d%x%02d.cpk"
    jal(ctx, 0x1110E0u, gen::fn_sprintf_00523ac8);
    v0 = s1;
    // 0x0011112c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x001114B0 sub_1114B0 -- 80 bytes; frame 0x10: ra sp+0x0
// [h_cutin.c] Has the cut-in's file arrived (work state 5): prints "*** CUTIN READ END %s" with the path. Returns 1 / 0.
void sub_1114B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001114b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, 60);
    lw(v1, a1, 0);
    v0 = 5;
    if (v1 != v0) {
        // 0x001114ec
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001114cc
        charge(ctx, 8);
        a0 = 0x5D0000;
        a0 = addiu(a0, 27488);  // "*** CUTIN READ END %s\n"
        a1 = addiu(a1, 252);
        jal(ctx, 0x1114D8u, gen::fn_printf_005225a8);
        v0 = 1;
    }
    // 0x001114f0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00111500 sub_111500 -- 24 bytes; leaf frame (no stack)
// [h_cutin.c] Starts the cut-in: work +192 = 1, +188 = 0. Returns 1.
void sub_111500(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00111500
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    v0 = 1;
    sw(v0, v1, 192);
    sw(zero, v1, 188);
}

// 0x00111530 sub_111530 -- 52 bytes; leaf frame (no stack)
// [h_cutin.c] Moves a loaded cut-in (state 5) to state 6 (playing). Returns 1, or 0 in any other state.
void sub_111530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00111530
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    lw(v1, a0, 0);
    v0 = 5;
    if (v1 != v0) {
        // 0x00111558
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00111544
        charge(ctx, 5);
        v0 = 6;
        sw(v0, a0, 0);
        v0 = 1;
    }
    // 0x0011155c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00111580 sub_111580 -- 40 bytes; frame 0x10
// [h_cutin.c] Stores the 64-bit value $a1 in the cut-in work (+764).
void sub_111580(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00111580
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(a1, sp, 0x8);
    lw(v1, a0, 60);
    lwc1(f1, sp, 0x8);
    lwc1(f0, sp, 0xC);
    swc1(f1, v1, 764);
    swc1(f0, v1, 768);
    sp = addiu(sp, 0x10);
}

// 0x00111CA0 sub_111CA0 -- 16 bytes; leaf frame (no stack)
// [h_maestro.c] Sets work +292.
void sub_111CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00111ca0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 292);
}

// 0x00111F00 sub_111F00 -- 16 bytes; leaf frame (no stack)
// [h_maestro.c] Sets work +280.
void sub_111F00(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00111f00
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 280);
}

// 0x00111F10 sub_111F10 -- 16 bytes; leaf frame (no stack)
// [h_maestro.c] Sets work +284.
void sub_111F10(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00111f10
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 284);
}

// 0x001158B0 sprCreateHandle -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [sprite] sprCreateHandle(parent, file, sprite): a 52-byte handle from the RW calloc slot (0x960184, hint 0x40000), its
// three colour bytes +48..+50 set to 0xFF, the sprite file (+8) and sprite index (+12); linked after `parent` when one is
// given, else at the tail of the global handle list 0x7CDF3C (+0 next, +4 prev). Returns the handle.
void sprCreateHandle(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001158b0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 1;
    a1 = 52;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, ub::kRwSlotCalloc);  // 0x960184: RwCalloc
    jalr(ctx, 0x1158E4u, v0.u());
    v1 = 255;
    sb(v1, v0, ub::spr::kRgb + 0);
    sb(v1, v0, ub::spr::kRgb + 1);
    sb(v1, v0, ub::spr::kRgb + 2);
    sw(s1, v0, ub::spr::kFile);
    sw(s0, v0, ub::spr::kSprite);
    if (s2 != 0) {
        // 0x00115950
        charge(ctx, 2);
        sw(v0, s2, ub::spr::kNext);
        sw(s2, v0, ub::spr::kPrev);
    } else {
        // 0x0011590c
        charge(ctx, 3);
        lw(a0, gp, ub::spr::kGpHandleList);  // 0x7CDF3C
        if (a0 != 0) {
            for (;;) {
                // 0x00115928
                charge(ctx, 3);
                lw(v1, a0, ub::spr::kNext);
                if (v1 == 0) {
                    break;
                }
                // 0x00115944
                charge(ctx, 3);
                a0 = v1;
                backedge(ctx);
            }
            // 0x00115934
            charge(ctx, 4);
            sw(v0, a0, ub::spr::kNext);
            sw(a0, v0, ub::spr::kPrev);
        } else {
            // 0x00115918
            charge(ctx, 4);
            sw(v0, gp, ub::spr::kGpHandleList);  // 0x7CDF3C
            sw(zero, v0, ub::spr::kPrev);
        }
    }
    // 0x00115958 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00115980 sub_115980 -- 104 bytes; frame 0x10: ra sp+0x0
// [sprite] [proposed: sprDestroyHandle] Unlinks a handle from its list (the head 0x7CDF3C when it has no previous one) and
// frees it through the RW free slot 0x96017C.
void sub_115980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00115980
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, ub::spr::kPrev);
    if (v1 != 0) {
        // 0x001159b0
        charge(ctx, 5);
        lw(v0, a0, ub::spr::kNext);
        sw(v0, v1, ub::spr::kNext);
        lw(v0, a0, ub::spr::kNext);
        if (v0 != 0) {
            // 0x001159c4
            charge(ctx, 1);
            sw(v1, v0, ub::spr::kPrev);
        }
    } else {
        // 0x00115994
        charge(ctx, 4);
        lw(v0, a0, ub::spr::kNext);
        sw(v0, gp, ub::spr::kGpHandleList);  // 0x7CDF3C
        if (v0 != 0) {
            // 0x001159a4
            charge(ctx, 3);
            sw(zero, v0, ub::spr::kPrev);
        }
    }
    // 0x001159c8
    charge(ctx, 8);
    v0 = 0x960000;
    lw(v0, v0, ub::kRwSlotFree);  // 0x96017C: RwFree
    jalr(ctx, 0x1159D0u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00115DE0 sub_115DE0 -- 280 bytes; frame 0x80: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [sprite] [proposed: sprDrawSpriteScaled] Draws one sprite at once: a handle of ($a1 file, $a2 sprite), position $f12 /
// $f13 (+16 / +20), depth $f14 (+44), the colour byte $t0 (+24), the three colour bytes $t1..$t3 (+48..+50), the scale
// $a3 in both +40 and +42; drawn by sub_1127D0(handle, 1), then unlinked and freed (the RW free slot).
void sub_115DE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00115de0
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    mov_s(f22, f12);
    mov_s(f21, f13);
    s3 = a3;
    s2 = t0;
    s1 = t1;
    s0 = t2;
    s5 = t3;
    mov_s(f20, f14);
    a0 = 0;
    jal(ctx, 0x115E30u, gen::fn_sprCreateHandle_001158b0);
    s4 = v0;
    swc1(f20, v0, ub::spr::kDepth);
    swc1(f22, v0, ub::spr::kX);
    swc1(f21, v0, ub::spr::kY);
    sb(s2, v0, ub::spr::kColour);
    sb(s1, v0, ub::spr::kRgb + 0);
    sb(s0, v0, ub::spr::kRgb + 1);
    sb(s5, v0, ub::spr::kRgb + 2);
    sh(s3, v0, ub::spr::kScaleX);
    sh(s3, v0, ub::spr::kScaleY);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x115E68u, gen::fn_sub_1127D0_001127d0);
    lw(v1, s4, ub::spr::kPrev);
    if (v1 != 0) {
        // 0x00115e98
        charge(ctx, 5);
        lw(v0, s4, ub::spr::kNext);
        sw(v0, v1, ub::spr::kNext);
        lw(v0, s4, ub::spr::kNext);
        if (v0 != 0) {
            // 0x00115eac
            charge(ctx, 1);
            sw(v1, v0, ub::spr::kPrev);
        }
    } else {
        // 0x00115e7c
        charge(ctx, 4);
        lw(v0, s4, ub::spr::kNext);
        sw(v0, gp, ub::spr::kGpHandleList);  // 0x7CDF3C
        if (v0 != 0) {
            // 0x00115e8c
            charge(ctx, 3);
            sw(zero, v0, ub::spr::kPrev);
        }
    }
    // 0x00115eb0
    charge(ctx, 18);
    a0 = s4;
    v0 = 0x960000;
    lw(v0, v0, ub::kRwSlotFree);  // 0x96017C: RwFree
    jalr(ctx, 0x115EBCu, v0.u());
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

}  // namespace p3fes::game
