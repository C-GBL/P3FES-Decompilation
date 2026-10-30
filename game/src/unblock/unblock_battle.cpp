// Phase 5 slice unblock, part battle (game/include/p3fes/game/unblock.h):
// battle-side callees -- a Shuffle Time pose jump, the item-stock background close, the encounter fade, the
// effect rng, the event camera block, two g_data helpers, the NPC reset of the field battle set-up.
// These functions were kept recompiled only because other slices' pair tests stood them in with recorders; slice
// unblock rewrote those checks as guest-memory checks (docs/INTEGRATION_LOG.md, "unblock"). Started from p3fes_handgen's
// bodies (register for register, block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h): every path
// keeps the original's statements, cycle charges and check points in order; the role comments name what each does.
// Pair tests: tests/game/test_unblock.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/unblock.h"

namespace p3fes::recomp_gen {
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_sub_16D2F0_0016d2f0(p3fes::EEContext&);
void fn_sub_16DBC0_0016dbc0(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_173280_00173280(p3fes::EEContext&);
void fn_sub_173330_00173330(p3fes::EEContext&);
void fn_sub_174960_00174960(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_250CF0_00250cf0(p3fes::EEContext&);
void fn_sub_25F570_0025f570(p3fes::EEContext&);
void fn_sub_2FF260_002ff260(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_3580B0_003580b0(p3fes::EEContext&);
void fn_sub_37CF50_0037cf50(p3fes::EEContext&);
void fn_sub_434F70_00434f70(p3fes::EEContext&);
void fn_sub_455CF0_00455cf0(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0016D2F0 sub_16D2F0 -- 616 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [g_data.c] [proposed: datGetLevelProgress] The experience bar of a party member: its experience (the protagonist's
// 0x836268, else the persona's through datPersonaGetByPcId / sub_173330) against the level table 0x5DC050 (99 entries):
// the level reached and the fraction to the next one.
void sub_16D2F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016d2f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = dsll32(s1, 16);
    s0 = dsra32(s0, 16);
    v0 = 1;
    if (s0 != v0) {
        // 0x0016d32c
        charge(ctx, 6);
        a0 = s1 & 0xFFFF;
        jal(ctx, 0x16D330u, gen::fn_datPersonaGetByPcId_00174800);
        s2 = v0;
        if (s2 == 0) {
            // 0x0016d344
            charge(ctx, 5);
            a0 = 0x5E0000;
            a0 = addiu(a0, 12440);  // "g_data.c"
            a1 = 622;
            jal(ctx, 0x16D350u, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x0016d358
        charge(ctx, 3);
        a0 = s2;
        jal(ctx, 0x16D35Cu, gen::fn_sub_173330_00173330);
    } else {
        // 0x0016d31c
        charge(ctx, 4);
        v0 = 0x830000;
        lw(v0, v0, 25192);  // 0x836268
    }
    // 0x0016d364
    charge(ctx, 6);
    a1 = 0;
    a2 = 0;
    a0 = 0x5E0000;
    a0 = addiu(a0, -16304);  // &0x5DC050
    for (;;) {
        // 0x0016d3b4
        charge(ctx, 4);
        v1 = a2 & 0xFF;
        v1 = slti(v1, 99);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016d37c
        charge(ctx, 7);
        v1 = a2 & 0xFF;
        v1 = sll(v1, 2);
        v1 = addu(a0, v1);
        lw(v1, v1, 0);
        at = slt(v0, v1);
        if (at != 0) {
            goto L_0016d398_7;
        }
        // 0x0016d3a4
        charge(ctx, 4);
        v1 = addiu(a1, 1);
        a1 = v1 & 0xFF;
        v1 = addiu(a2, 1);
        a2 = v1 & 0xFF;
    }
    // 0x0016d3c4
    charge(ctx, 1);
    v0 = 99;
L_0016d3c8:
    charge(ctx, 4);
    v1 = v0 & 0xFF;
    v0 = 99;
    if (v1 != v0) {
        // 0x0016d3e4
        charge(ctx, 3);
        v0 = 1;
        if (s0 != v0) {
            // 0x0016d400
            charge(ctx, 6);
            a0 = s1 & 0xFFFF;
            jal(ctx, 0x16D404u, gen::fn_datPersonaGetByPcId_00174800);
            s2 = v0;
            if (s2 == 0) {
                // 0x0016d418
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 622;
                jal(ctx, 0x16D424u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0016d42c
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x16D430u, gen::fn_sub_173330_00173330);
        } else {
            // 0x0016d3f0
            charge(ctx, 4);
            v0 = 0x830000;
            lw(v0, v0, 25192);  // 0x836268
        }
        // 0x0016d438
        charge(ctx, 6);
        a1 = 0;
        a2 = 0;
        a0 = 0x5E0000;
        a0 = addiu(a0, -16304);  // &0x5DC050
        for (;;) {
            // 0x0016d488
            charge(ctx, 4);
            v1 = a2 & 0xFF;
            v1 = slti(v1, 99);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016d450
            charge(ctx, 7);
            v1 = a2 & 0xFF;
            v1 = sll(v1, 2);
            v1 = addu(a0, v1);
            lw(v1, v1, 0);
            at = slt(v0, v1);
            if (at != 0) {
                goto L_0016d46c_20;
            }
            // 0x0016d478
            charge(ctx, 4);
            v1 = addiu(a1, 1);
            a1 = v1 & 0xFF;
            v1 = addiu(a2, 1);
            a2 = v1 & 0xFF;
        }
        // 0x0016d498
        charge(ctx, 1);
        v0 = 99;
    L_0016d49c:
        charge(ctx, 5);
        v0 = v0 & 0xFF;
        v0 = addiu(v0, 1);
        s2 = v0 & 0xFF;
        if (i64(s2) > 0) {
            // 0x0016d4b0
            charge(ctx, 3);
            at = slti(s2, 100);
            if (at == 0) {
                goto L_0016d4bc;
            }
            goto L_0016d4d0;
        }
    L_0016d4bc:
        charge(ctx, 5);
        a0 = 0x5E0000;
        a0 = addiu(a0, 12440);  // "g_data.c"
        a1 = 876;
        jal(ctx, 0x16D4C8u, gen::fn_sub_19D3F0_0019d3f0);
    L_0016d4d0:
        charge(ctx, 8);
        v1 = sll(s2, 2);
        v0 = 0x5E0000;
        v0 = addiu(v0, -16308);  // &0x5DC04C
        v0 = addu(v0, v1);
        lw(s2, v0, 0);
        v0 = 1;
        if (s0 != v0) {
            // 0x0016d500
            charge(ctx, 6);
            a0 = s1 & 0xFFFF;
            jal(ctx, 0x16D504u, gen::fn_datPersonaGetByPcId_00174800);
            s0 = v0;
            if (s0 == 0) {
                // 0x0016d518
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, 12440);  // "g_data.c"
                a1 = 622;
                jal(ctx, 0x16D524u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0016d52c
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x16D530u, gen::fn_sub_173330_00173330);
        } else {
            // 0x0016d4f0
            charge(ctx, 4);
            v0 = 0x830000;
            lw(v0, v0, 25192);  // 0x836268
        }
        // 0x0016d538
        charge(ctx, 1);
        v0 = subu(s2, v0);
    } else {
        // 0x0016d3d8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0016d53c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_0016d398_7:
    charge(ctx, 3);
    v0 = a1 & 0xFF;
    goto L_0016d3c8;
L_0016d46c_20:
    charge(ctx, 3);
    v0 = a1 & 0xFF;
    goto L_0016d49c;
}

// 0x0016DBC0 sub_16DBC0 -- 276 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [g_data.c] Finds the highest-ranked persona of the protagonist's arcana (sub_16DF30): over the 12 stock slots, the
// persona whose arcana (sub_173280 of its id) matches with the largest +4 byte; stores its id at *$a1. Returns 1 / 0.
void sub_16DBC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016dbc0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    s3 = 0;
    s2 = 0;
    s1 = si(-1);
    jal(ctx, 0x16DBF4u, gen::fn_sub_16DF30_0016df30);
    s6 = dsll32(v0, 24);
    s6 = dsra32(s6, 24);
    s0 = 0;
    for (;;) {
        // 0x0016dc7c
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slti(v0, 12);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016dc10
        charge(ctx, 7);
        s5 = dsll32(s0, 16);
        s5 = dsra32(s5, 16);
        a0 = s5;
        jal(ctx, 0x16DC1Cu, gen::fn_sub_174960_00174960);
        if (v0 != 0) {
            // 0x0016dc2c
            charge(ctx, 10);
            a0 = s5;
            jal(ctx, 0x16DC30u, gen::fn_sub_174A90_00174a90);
            s5 = v0;
            lhu(a0, v0, 2);
            jal(ctx, 0x16DC40u, gen::fn_sub_173280_00173280);
            v0 = v0 & 0xFF;
            if (v0 == s6) {
                // 0x0016dc54
                charge(ctx, 5);
                lbu(v1, s5, 4);
                v0 = s2 & 0xFF;
                at = slt(v0, v1);
                if (at != 0) {
                    // 0x0016dc68
                    charge(ctx, 3);
                    s3 = 1;
                    lhu(s1, s5, 2);
                    s2 = v1;
                }
            }
        }
        // 0x0016dc74
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x0016dc8c
    charge(ctx, 3);
    v0 = 1;
    if (s3 != v0) {
        // 0x0016dca4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0016dc98
        charge(ctx, 3);
        sw(s1, s4, 0);
    }
    // 0x0016dca8 (the shared epilogue, written out on this path)
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

// 0x00250CF0 sub_250CF0 -- 372 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [gc_pose.c] [proposed: gcPoseStartJump] Starts a ballistic move of a pose (mode 2, sub-state 3 required): the target
// position $a1 (+52..+60), heights $f12 / $f13 (+64 / +68), the duration $a2 frames in 16.16 (+48); the vertical speed and
// gravity (+72 / +76) from h1 - h0 over the duration; the position rotated through sub_4BDDE0.
void sub_250CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00250cf0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    mov_s(f21, f12);
    mov_s(f20, f13);
    s2 = a2;
    lw(v1, a0, 12);
    v0 = 2;
    if (v1 != v0) {
        // 0x00250d38
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1373;
        jal(ctx, 0x250D44u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250d4c
    charge(ctx, 4);
    lw(v1, s4, 36);
    v0 = 3;
    if (v1 != v0) {
        // 0x00250d5c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5728);  // "gc_pose.c"
        a1 = 1374;
        jal(ctx, 0x250D68u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00250d70
    charge(ctx, 61);
    s1 = addiu(s4, 40);
    s0 = addiu(s1, 12);
    v0 = 1;
    sw(v0, s4, 40);
    lwc1(f2, s3, 0);
    lwc1(f1, s3, 4);
    lwc1(f0, s3, 8);
    swc1(f2, s4, 52);
    swc1(f1, s4, 56);
    swc1(f0, s4, 60);
    swc1(f21, s4, 64);
    swc1(f20, s4, 68);
    lwc1(f1, s4, 64);
    lwc1(f0, gp, -32264);  // 0x7CAEE8
    div_s(f1, f1, f0);
    v0 = 0x43B40000;
    mtc1(v0, f0);
    mul_s(f12, f0, f1);
    a0 = addiu(s4, 20);
    a1 = s3;
    a2 = 0;
    jal(ctx, 0x250DC8u, gen::fn_sub_4BDDE0_004bdde0);
    a0 = sll(s2, 16);
    mtc1(a0, f0);
    cvt_s_w(f1, f0);
    v1 = 0x49F00000;
    mtc1(v1, f0);
    div_s(f2, f1, f0);
    lwc1(f1, s0, 16);
    lwc1(f0, s0, 12);
    sub_s(f1, f1, f0);
    v1 = 0x40000000;
    mtc1(v1, f0);
    mul_s(f1, f0, f1);
    mul_s(f0, f2, f2);
    div_s(f1, f1, f0);
    neg_s(f0, f1);
    swc1(f0, s0, 24);
    mul_s(f0, f1, f2);
    swc1(f0, s0, 20);
    sw(zero, s4, 16);
    sw(a0, s1, 8);
    lw(v1, s1, 4);
    v1 = v1 | 0x1;
    sw(v1, s1, 4);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0025F570 sub_25F570 -- 84 bytes; frame 0x10: ra sp+0x0
// [br_item.c] Closes the stock-over background: +12 = 0, +4 = 1, flag 2 (closing). K_Assert when it does not exist.
void sub_25F570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0025f570
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, -18816);  // 0x7CE370
    if (v1 == 0) {
        // 0x0025f584
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -5128);  // "br_item.c"
        a1 = 117;
        jal(ctx, 0x25F590u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0025f598 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lw(a0, gp, -18816);  // 0x7CE370
    sw(zero, a0, 12);
    v1 = 1;
    sw(v1, a0, 4);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FF260 sub_2FF260 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [battle] [proposed: btlEncountFadeStart] Starts the "battle_encount_fade" task (priority 7359, sub_2FED10, work
// 0x7CE508: kind 2, the fade id $a0 at +6) unless one already exists.
void sub_2FF260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ff260
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x6A0000;
    a0 = addiu(a0, -21968);  // "battle_encount_fade"
    jal(ctx, 0x2FF278u, gen::fn_kwlnTaskGetTaskByName_00195340);
    if (v0 == 0) {
        // 0x002ff288
        charge(ctx, 13);
        v0 = 2;
        sb(v0, gp, -18408);  // 0x7CE508
        sh(s0, gp, -18402);  // 0x7CE50E
        a0 = 0;
        a1 = 0x6A0000;
        a1 = addiu(a1, -21968);  // "battle_encount_fade"
        a2 = 7359;
        a3 = 0x300000;
        a3 = addiu(a3, -4848);  // &sub_2FED10
        t0 = 0;
        t1 = addiu(gp, -18408);  // &0x7CE508
        jal(ctx, 0x2FF2B4u, gen::fn_kwlnTaskCreate_00194b20);
    }
    // 0x002ff2bc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003580B0 sub_3580B0 -- 52 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [effect] The effect random number: sub_357FD0() modulo $a1.
void sub_3580B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003580b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3580C0u, gen::fn_sub_357FD0_00357fd0);
    divu(v0, s0);
    mfhi(v0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0037CF50 sub_37CF50 -- 132 bytes; leaf frame (no stack)
// [event] Sets the event camera block: 38 doublewords from $a0 into 0x958700, the eye $a1 into 0x9585B8 and the target $a2
// into 0x9585A8 (three floats each); 0x7CE5FC cleared.
void sub_37CF50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x0037cf50
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(zero, gp, -18164);  // 0x7CE5FC
    t1 = 0x960000;
    t1 = addiu(t1, -30976);  // &0x958700
    t0 = 38;
    for (;;) {
        // 0x0037cf60
        charge(ctx, 9);
        lw(a3, a0, 0);
        lw(v1, a0, 4);
        a0 = addiu(a0, 8);
        t0 = addiu(t0, -1);
        sw(a3, t1, 0);
        sw(v1, t1, 4);
        t1 = addiu(t1, 8);
        if (i64(t0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0037cf84
    charge(ctx, 20);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    v1 = 0x960000;
    swc1(f2, v1, -31304);  // 0x9585B8
    v1 = 0x960000;
    swc1(f1, v1, -31300);  // 0x9585BC
    v1 = 0x960000;
    swc1(f0, v1, -31296);  // 0x9585C0
    lwc1(f2, a2, 0);
    lwc1(f1, a2, 4);
    lwc1(f0, a2, 8);
    v1 = 0x960000;
    swc1(f2, v1, -31320);  // 0x9585A8
    v1 = 0x960000;
    swc1(f1, v1, -31316);  // 0x9585AC
    v1 = 0x960000;
    swc1(f0, v1, -31312);  // 0x9585B0
}

// 0x00434F70 sub_434F70 -- 228 bytes; frame 0x10: ra sp+0x0
// [Y_Npc] [proposed: Y_Npc_ResetGlobals] Resets the NPC globals at a battle's set-up (called once by sub_1D8CB0): eight
// bytes cleared (gp-17972, -17968, -17964, -17960, gp-17928..-17926, gp-17920), the halfword gp-17916 = -1, the byte
// gp-20960 = 1, eight words 16 bytes apart at 0x86BE00 cleared, the 256-byte table 0x95C110 cleared unless flag 5140 is
// set; then sub_455CF0.
void sub_434F70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00434f70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    sb(zero, gp, -17972);  // 0x7CE6BC
    sb(zero, gp, -17968);  // 0x7CE6C0
    a0 = 0;
    v1 = addiu(gp, -17928);  // &0x7CE6E8
    for (;;) {
        // 0x00434f9c
        charge(ctx, 4);
        v0 = slti(a0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00434f90
        charge(ctx, 3);
        v0 = addu(v1, a0);
        sb(zero, v0, 0);
        a0 = addiu(a0, 1);
    }
    // 0x00434fac
    charge(ctx, 5);
    a0 = 5140;
    jal(ctx, 0x434FB0u, gen::fn_datGetFlag_0016f190);
    if (v0 == 0) {
        // 0x00434fc0
        charge(ctx, 5);
        a0 = 0;
        v1 = 0x960000;
        v1 = addiu(v1, -16112);  // &0x95C110
        for (;;) {
            // 0x00434fe0
            charge(ctx, 4);
            v0 = slti(a0, 256);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00434fd4
            charge(ctx, 3);
            v0 = addu(v1, a0);
            sb(zero, v0, 0);
            a0 = addiu(a0, 1);
        }
    }
    // 0x00434ff0
    charge(ctx, 12);
    v0 = si(-1);
    sh(v0, gp, -17916);  // 0x7CE6F4
    sb(zero, gp, -17920);  // 0x7CE6F0
    sb(zero, gp, -17964);  // 0x7CE6C4
    sb(zero, gp, -17960);  // 0x7CE6C8
    v0 = 1;
    sb(v0, gp, -20960);  // 0x7CDB10
    a0 = 0;
    v1 = 0x870000;
    v1 = addiu(v1, -16896);  // &0x86BE00
    for (;;) {
        // 0x00435030
        charge(ctx, 3);
        v0 = slti(a0, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00435020
        charge(ctx, 4);
        v0 = sll(a0, 4);
        v0 = addu(v1, v0);
        sw(zero, v0, 0);
        a0 = addiu(a0, 1);
    }
    // 0x0043503c
    charge(ctx, 6);
    jal(ctx, 0x43503Cu, gen::fn_sub_455CF0_00455cf0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
