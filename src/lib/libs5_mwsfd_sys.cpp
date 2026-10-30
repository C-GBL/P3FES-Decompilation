// Phase 5 slice libs5: CRI Sofdec MWSFD, part 2: the player's lower layer -- the loop-play list (LSC) bridges, the
// SJ ring set, the SVM server hooks, the error reporter, the per-frame server and the playback state machine
// (0x584000-0x5863D8).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs5.h. Names are
// symbols/functions.json's (ADR-0009); roles are read from the instructions and the binary's own strings
// (no CRI material was opened). Pair tests: tests/game/test_libs5.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs5.h"

namespace p3fes::recomp_gen {
void fn_WTLS_get_table_1_005851b0(p3fes::EEContext&);
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn_atan2l_11_00585468(p3fes::EEContext&);
void fn_cosl_11_00585480(p3fes::EEContext&);
void fn_log10l_11_00585628(p3fes::EEContext&);
void fn_r_lock_def_free_3_00585c70(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_3_00585c90(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_4_005863f8(p3fes::EEContext&);
void fn_sub_541008_00541008(p3fes::EEContext&);
void fn_sub_55D790_0055d790(p3fes::EEContext&);
void fn_sub_55D7C0_0055d7c0(p3fes::EEContext&);
void fn_sub_55DA48_0055da48(p3fes::EEContext&);
void fn_sub_564DD0_00564dd0(p3fes::EEContext&);
void fn_sub_564FE8_00564fe8(p3fes::EEContext&);
void fn_sub_5651B0_005651b0(p3fes::EEContext&);
void fn_sub_565550_00565550(p3fes::EEContext&);
void fn_sub_5655E8_005655e8(p3fes::EEContext&);
void fn_sub_565690_00565690(p3fes::EEContext&);
void fn_sub_57C730_0057c730(p3fes::EEContext&);
void fn_sub_57FC60_0057fc60(p3fes::EEContext&);
void fn_sub_580130_00580130(p3fes::EEContext&);
void fn_sub_580750_00580750(p3fes::EEContext&);
void fn_sub_580958_00580958(p3fes::EEContext&);
void fn_sub_581108_00581108(p3fes::EEContext&);
void fn_sub_581120_00581120(p3fes::EEContext&);
void fn_sub_581148_00581148(p3fes::EEContext&);
void fn_sub_5847A8_005847a8(p3fes::EEContext&);
void fn_sub_5847D0_005847d0(p3fes::EEContext&);
void fn_sub_584B18_00584b18(p3fes::EEContext&);
void fn_sub_584C38_00584c38(p3fes::EEContext&);
void fn_sub_584C80_00584c80(p3fes::EEContext&);
void fn_sub_584CD8_00584cd8(p3fes::EEContext&);
void fn_sub_584D30_00584d30(p3fes::EEContext&);
void fn_sub_584E08_00584e08(p3fes::EEContext&);
void fn_sub_585050_00585050(p3fes::EEContext&);
void fn_sub_585100_00585100(p3fes::EEContext&);
void fn_sub_5851D0_005851d0(p3fes::EEContext&);
void fn_sub_585210_00585210(p3fes::EEContext&);
void fn_sub_5852F8_005852f8(p3fes::EEContext&);
void fn_sub_585360_00585360(p3fes::EEContext&);
void fn_sub_5853B8_005853b8(p3fes::EEContext&);
void fn_sub_585410_00585410(p3fes::EEContext&);
void fn_sub_585578_00585578(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_585698_00585698(p3fes::EEContext&);
void fn_sub_585738_00585738(p3fes::EEContext&);
void fn_sub_5857B8_005857b8(p3fes::EEContext&);
void fn_sub_585960_00585960(p3fes::EEContext&);
void fn_sub_585A20_00585a20(p3fes::EEContext&);
void fn_sub_585AC8_00585ac8(p3fes::EEContext&);
void fn_sub_585B40_00585b40(p3fes::EEContext&);
void fn_sub_585BA8_00585ba8(p3fes::EEContext&);
void fn_sub_585BC0_00585bc0(p3fes::EEContext&);
void fn_sub_585C08_00585c08(p3fes::EEContext&);
void fn_sub_585C50_00585c50(p3fes::EEContext&);
void fn_sub_585DA8_00585da8(p3fes::EEContext&);
void fn_sub_585DD8_00585dd8(p3fes::EEContext&);
void fn_sub_585E40_00585e40(p3fes::EEContext&);
void fn_sub_585E70_00585e70(p3fes::EEContext&);
void fn_sub_585F38_00585f38(p3fes::EEContext&);
void fn_sub_5860E8_005860e8(p3fes::EEContext&);
void fn_sub_586130_00586130(p3fes::EEContext&);
void fn_sub_586140_00586140(p3fes::EEContext&);
void fn_sub_5861B8_005861b8(p3fes::EEContext&);
void fn_sub_586200_00586200(p3fes::EEContext&);
void fn_sub_586248_00586248(p3fes::EEContext&);
void fn_sub_5862F0_005862f0(p3fes::EEContext&);
void fn_sub_586530_00586530(p3fes::EEContext&);
void fn_sub_5865A8_005865a8(p3fes::EEContext&);
void fn_sub_586610_00586610(p3fes::EEContext&);
void fn_sub_589F70_00589f70(p3fes::EEContext&);
void fn_sub_58C228_0058c228(p3fes::EEContext&);
void fn_sub_595BA0_00595ba0(p3fes::EEContext&);
void fn_sub_595BC0_00595bc0(p3fes::EEContext&);
void fn_sub_595BE8_00595be8(p3fes::EEContext&);
void fn_sub_595C60_00595c60(p3fes::EEContext&);
void fn_sub_597968_00597968(p3fes::EEContext&);
void fn_sub_5990C0_005990c0(p3fes::EEContext&);
void fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs5;

// 0x005847A8 sub_5847A8 -- 36 bytes; frame 0x10: ra sp+0x0
// [mwPlyIsLscEnd] MWSFD: true when the loop-play list (sub_55D790) reports status 3.
void sub_5847A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005847a8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5847B0u, gen::fn_sub_55D790_0055d790);
    v0 = v0 ^ 0x3;
    ld(ra, sp, 0x0);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x005847D0 sub_5847D0 -- 44 bytes; frame 0x10: ra sp+0x0
// [mwPlySetLscReadSize] MWSFD: forwards a read size to the player's loop-play list (+72, sub_55DA48) when it has one.
void sub_5847D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005847d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 72);
    a0 = v0;
    if (v0 == 0) {
        // 0x005847f0
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005847e4
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55DA48_0055da48(ctx);  // tail call
}

// 0x00584C80 sub_584C80 -- 88 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSlaveStart] MWSFD: starts the audio slave (+640) through the slave interface (*0x7B4538, method +20) with its
// handle (+20) and SJ (+12), when it is active.
void sub_584C80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584c80
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x584C8Cu, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584ca0
        charge(ctx, 5);
        jal(ctx, 0x584CA0u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a1, s0, slave::kSj);
        lw(a0, s0, slave::kHandle);
        if (v0 != 0) {
            // 0x00584cb4
            charge(ctx, 3);
            lw(v0, v0, 20);
            if (v0 != 0) {
                // 0x00584cc0
                charge(ctx, 2);
                jalr(ctx, 0x584CC0u, v0.u());
                goto L_00584cc8;
            }
            ld(s0, sp, 0x0);
            // 0x00584ccc (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_00584cc8:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00584ccc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00584CD8 sub_584CD8 -- 84 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSlaveStop] MWSFD: stops the audio slave (interface method +24 on its handle) when it is active.
void sub_584CD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584cd8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x584CE4u, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584cf8
        charge(ctx, 4);
        jal(ctx, 0x584CF8u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a0, s0, slave::kHandle);
        if (v0 != 0) {
            // 0x00584d08
            charge(ctx, 3);
            lw(v0, v0, 24);
            if (v0 != 0) {
                // 0x00584d14
                charge(ctx, 2);
                jalr(ctx, 0x584D14u, v0.u());
                goto L_00584d1c;
            }
            ld(s0, sp, 0x0);
            // 0x00584d20 (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_00584d1c:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00584d20 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00584E08 sub_584E08 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdSlavePause] MWSFD: pauses / resumes the audio slave (interface method +36: handle, flag) when it is active.
void sub_584E08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584e08
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x584E1Cu, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584e30
        charge(ctx, 4);
        jal(ctx, 0x584E30u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a0, s0, slave::kHandle);
        if (v0 != 0) {
            // 0x00584e40
            charge(ctx, 3);
            lw(v0, v0, 36);
            if (v0 != 0) {
                // 0x00584e4c
                charge(ctx, 2);
                a1 = s1;
                jalr(ctx, 0x584E4Cu, v0.u());
                goto L_00584e54;
            }
            ld(s0, sp, 0x0);
            // 0x00584e58 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
    L_00584e54:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00584e58 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00585050 sub_585050 -- 176 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [mwsfdSlaveReset] MWSFD: resets the player's audio slave: stops it, resets its SJ (method +20) and re-registers the
// SJ as SFD stream 192 + its index (sub_58C228).
void sub_585050(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585050
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 640);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    link(ctx, 0x58506Cu);  // $ra first: the delay slot below depends on it
    lw(s3, a0, 60);
    call(ctx, gen::fn_WTLS_get_table_1_005851b0);
    a0 = s0;
    lw(s2, s0, 20);
    lw(s1, s0, 12);
    link(ctx, 0x585080u);  // $ra first: the delay slot below depends on it
    lw(s0, s0, 16);
    call(ctx, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x005850e8
        charge(ctx, 6);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x00585094
    charge(ctx, 2);
    if (s2 == 0) {
        lw(v1, s1, 0);
    } else {
        // 0x0058509c
        charge(ctx, 3);
        a0 = s2;
        jal(ctx, 0x58509Cu, gen::fn_sub_584CD8_00584cd8);
        lw(v1, s1, 0);
    }
    // 0x005850a8
    charge(ctx, 15);
    lw(v0, v1, 20);
    a0 = s1;
    jalr(ctx, 0x5850ACu, v0.u());
    a0 = s3;
    a1 = addiu(s0, 192);
    ld(s0, sp, 0x0);
    a2 = s1;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    a3 = 0;
    ld(s3, sp, 0x18);
    t0 = 0;
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_58C228_0058c228(ctx);  // tail call
}

// 0x00585100 sub_585100 -- 160 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// [mwsfdSlaveDestroy] MWSFD: destroys an audio slave: releases the SVM lock 6 (log10l_11), stops it, clears its used
// word, frees its handle (sub_584C38), destroys its SJ (method +12), clears the handle, then sub_584B18.
void sub_585100(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585100
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s1 = a0;
    jal(ctx, 0x585114u, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
        // 0x0058518c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00585128
    charge(ctx, 5);
    jal(ctx, 0x585128u, gen::fn_WTLS_get_table_1_005851b0);
    lw(s0, s1, slave::kHandle);
    lw(s2, s1, slave::kSj);
    if (s0 == 0) {
        // 0x00585188
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x0058518c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058513c
    charge(ctx, 18);
    jal(ctx, 0x58513Cu, gen::fn_log10l_11_00585628);
    a0 = s0;
    jal(ctx, 0x585144u, gen::fn_sub_584CD8_00584cd8);
    sw(zero, s1, slave::kUsed);
    a0 = s0;
    jal(ctx, 0x585150u, gen::fn_sub_584C38_00584c38);
    lw(v1, s2, 0);
    lw(v0, v1, 12);
    a0 = s2;
    jalr(ctx, 0x585160u, v0.u());
    sw(zero, s1, slave::kHandle);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_584B18_00584b18(ctx);  // tail call
}

// 0x005851B0 WTLS_get_table_1 -- 12 bytes; leaf frame (no stack)
// [mwsfdGetSlaveIf] MWSFD: the audio slave interface 0x7B4538 (FLIRT misname).
void WTLS_get_table_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x005851b0
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 17720);  // 0x7B4538
}

// 0x005851D0 sub_5851D0 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSlaveIsActive] MWSFD: true when the slave interface is set, the slave record is in use (+0 = 1) and has a
// handle (+20).
void sub_5851D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005851d0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5851DCu, gen::fn_WTLS_get_table_1_005851b0);
    a0 = 1;
    if (v0 != 0) {
        // 0x005851ec
        charge(ctx, 3);
        lw(v1, s0, slave::kUsed);
        v0 = 0;
        if (v1 == a0) {
            // 0x005851f8
            charge(ctx, 2);
            lw(v0, s0, slave::kHandle);
            v0 = sltu(0, v0);
        }
    }
    // 0x00585200 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00585210 sub_585210 -- 60 bytes; frame 0x10: ra sp+0x0
// [mwsfdInitSvm] MWSFD: SVM init (sub_565550) and the four server ids 0x9A6EC0..0x9A6ECC cleared; $v0 keeps 0x9A0000.
void sub_585210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585210
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585218u, gen::fn_sub_565550_00565550);
    ld(ra, sp, 0x0);
    v0 = 0x9A0000;
    v1 = 0x9A0000;
    a0 = 0x9A0000;
    a1 = 0x9A0000;
    sw(zero, v0, 28352);  // 0x9A6EC0
    sw(zero, v1, 28356);  // 0x9A6EC4
    sw(zero, a0, 28360);  // 0x9A6EC8
    sw(zero, a1, 28364);  // 0x9A6ECC
    sp = addiu(sp, 0x10);
}

// 0x005852F8 sub_5852F8 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSetSvmCb2] MWSFD: registers SVM server class 2 (sub_564FE8) and keeps the id at 0x9A6EC4.
void sub_5852F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005852f8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    v1 = a2;
    a2 = v0;
    sd(s0, sp, 0x0);
    s0 = a0;
    a1 = s0;
    t0 = a3;
    a0 = 2;
    sd(ra, sp, 0x8);
    a3 = v1;
    jal(ctx, 0x585320u, gen::fn_sub_564FE8_00564fe8);
    v0 = 0x9A0000;
    ld(ra, sp, 0x8);
    sw(s0, v0, 28356);  // 0x9A6EC4
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00585360 sub_585360 -- 56 bytes; frame 0x10: ra sp+0x0
// [mwsfdSetSvmCb6] MWSFD: registers SVM server class 6 (sub_564DD0); id at 0x9A6EC8.
void sub_585360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585360
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a0;
    sp = addiu(sp, -0x10);
    a3 = a2;
    a0 = 6;
    a1 = v0;
    sd(ra, sp, 0x0);
    a2 = v1;
    jal(ctx, 0x58537Cu, gen::fn_sub_564DD0_00564dd0);
    v1 = 0x9A0000;
    ld(ra, sp, 0x0);
    sw(v0, v1, 28360);  // 0x9A6EC8
    sp = addiu(sp, 0x10);
}

// 0x005853B8 sub_5853B8 -- 56 bytes; frame 0x10: ra sp+0x0
// [mwsfdSetSvmCb5] MWSFD: registers SVM server class 5 (sub_564DD0); id at 0x9A6ECC.
void sub_5853B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005853b8
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a0;
    sp = addiu(sp, -0x10);
    a3 = a2;
    a0 = 5;
    a1 = v0;
    sd(ra, sp, 0x0);
    a2 = v1;
    jal(ctx, 0x5853D4u, gen::fn_sub_564DD0_00564dd0);
    v1 = 0x9A0000;
    ld(ra, sp, 0x0);
    sw(v0, v1, 28364);  // 0x9A6ECC
    sp = addiu(sp, 0x10);
}

// 0x00585410 sub_585410 -- 68 bytes, 2 chunks; frame 0x10: ra sp+0x0
// [mwsfdSetSprHooks] MWSFD: installs the scratchpad swap hooks: SVM's (sub_565690(atan2l_11, 0)) and the record
// 0x99A0C8 = {cosl_11, 0}; returns 0x99A0C8.
void sub_585410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585410
    enter(ctx, 12);  // entry check point + this block's cycles
    a0 = 0x580000;
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 21608);  // &atan2l_11
    jal(ctx, 0x585420u, gen::fn_sub_565690_00565690);
    ld(ra, sp, 0x0);
    a0 = 0x580000;
    a0 = addiu(a0, 21632);  // &cosl_11
    a1 = 0;
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x005656a8
    charge(ctx, 5);
    v0 = 0x9A0000;
    v0 = addiu(v0, -24376);  // &0x99A0C8
    sw(a1, v0, 4);  // 0x99A0CC
    sw(a0, v0, 0);  // 0x99A0C8
}

// 0x00585468 atan2l_11 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdSprInHook] MWSFD: the scratchpad swap-in hook (thunk to sub_581108; FLIRT misname).
void atan2l_11(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585468
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_581108_00581108(ctx);  // tail call
}

// 0x00585480 cosl_11 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdSprOutHook] MWSFD: the scratchpad swap-out hook (thunk to sub_581120; FLIRT misname).
void cosl_11(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585480
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_581120_00581120(ctx);  // tail call
}

// 0x00585578 sub_585578 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdTestAndSet] MWSFD: thunk to SVM's test-and-set (sub_5655E8).
void sub_585578(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585578
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5655E8_005655e8(ctx);  // tail call
}

// 0x00585628 log10l_11 -- 24 bytes; frame 0x10: ra sp+0x0
// [mwsfdUnlockSvm6] MWSFD: releases SVM lock 6 (sub_5651B0(6); FLIRT misname).
void log10l_11(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585628
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 6;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5651B0_005651b0(ctx);  // tail call
}

// 0x00585698 sub_585698 -- 156 bytes; frame 0x10: ra sp+0x0
// [mwsfdWaitSvrHndl] MWSFD: waits while the player's 'in server' word (+96) is set: up to 10 rounds of mark busy, the
// ADX server step, unmark.
void sub_585698(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00585698
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    lw(v1, a0, 96);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x005856b8
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005856b0
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    // 0x005856c0
    charge(ctx, 10);
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x18);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = 0;
    sd(s2, sp, 0x10);
    s2 = 1;
    v0 = slti(s1, 10);
    for (;;) {
        // 0x005856e8
        charge(ctx, 2);
        s1 = addiu(s1, 1);
        if (v0 != 0) {
            // 0x005856f0
            charge(ctx, 11);
            a1 = 1;
            a0 = s0;
            jal(ctx, 0x5856F4u, gen::fn_sub_5861B8_005861b8);
            jal(ctx, 0x5856FCu, gen::fn_sub_541008_00541008);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x585708u, gen::fn_sub_5861B8_005861b8);
            lw(v0, s0, ply::kInSvr);
            cc = v0 == s2;  // the condition, before the delay slot changes it
            v0 = slti(s1, 10);
            if (cc) {
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x0058571c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00585738 sub_585738 -- 128 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// [mwlSfdExecDecSvrPrep] MWSFD: the preparing step (status 1): a pending file start (+428) is retried through
// MWSTM_ReqStart; links the streams (mwPlyStartXX); when SFD reports 4 or 6 the player becomes 2 (playing). Returns 2
// or 4.
void sub_585738(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585738
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(s1, s0, ply::kStartPend);
    lw(s2, s0, ply::kSfd);
    if (s1 == v0) {
        // 0x00585760
        charge(ctx, 4);
        jal(ctx, 0x585760u, gen::fn_sub_585960_00585960);
        if (v0 == s1) {
            sw(zero, s0, ply::kStartPend);
        }
    }
    // 0x00585770
    charge(ctx, 8);
    a0 = s0;
    jal(ctx, 0x585770u, gen::fn_sub_5857B8_005857b8);
    a0 = s2;
    jal(ctx, 0x585778u, gen::fn_sub_5990C0_005990c0);
    v1 = v0;
    v0 = 4;
    a0 = 6;
    if (v1 != v0) {
        // 0x00585790
        charge(ctx, 2);
        if (v1 == a0) {
            goto L_00585798;
        }
        ld(s0, sp, 0x0);
        // 0x005857a4 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00585798:
    charge(ctx, 3);
    v0 = 2;
    sw(v0, s0, ply::kStat);
    ld(s0, sp, 0x0);
    // 0x005857a4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005857B8 sub_5857B8 -- 424 bytes; frame 0x10: ra sp+0x0
// [mwPlyStartXX] MWSFD: links the streams once SFD is ready (status 3): starts SFD, applies the pause byte, links
// (sub_589F70, 'mwPlyStartXX: can't link stream') and resumes the audio slave -- with a slave only when it is ready
// too.
void sub_5857B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005857b8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 1;
    sd(ra, sp, 0x0);
    lw(v1, a0, 640);
    ld(ra, sp, 0x0);
    if (v1 != v0) {
        // 0x005857d8
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        // 0x005858d8
        charge(ctx, 9);
        sp = addiu(sp, -0x10);
        sd(s0, sp, 0x0);
        s0 = a0;
        sd(ra, sp, 0x8);
        link(ctx, 0x5858E8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 60);
        call(ctx, gen::fn_sub_5990C0_005990c0);
        v1 = 3;
        a0 = s0;
        if (v0 == v1) {
            // 0x005858fc
            charge(ctx, 6);
            jal(ctx, 0x5858FCu, gen::fn_sub_580130_00580130);
            lb(v1, s0, 114);
            a0 = s0;
            a1 = 0;
            if (v1 == 0) {
                // 0x00585914
                charge(ctx, 2);
                jal(ctx, 0x585914u, gen::fn_sub_580750_00580750);
            }
            // 0x0058591c
            charge(ctx, 4);
            lb(v1, s0, 112);
            v0 = 1;
            if (v1 != v0) {
                ld(s0, sp, 0x0);
                // 0x00585954 (the shared epilogue, written out on this path)
                charge(ctx, 3);
                ld(ra, sp, 0x8);
                sp = addiu(sp, 0x10);
                return;
            }
            // 0x0058592c
            charge(ctx, 5);
            link(ctx, 0x58592Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 60);
            call(ctx, gen::fn_sub_589F70_00589f70);
            a0 = 0x7D0000;
            a0 = addiu(a0, -25488);  // "E99072103 mwPlyStartXX: can't link stream"
            if (v0 == 0) {
                goto L_00585950;
            }
            // 0x00585940
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            gen::fn_sub_585590_00585590(ctx);  // tail call
            return;
        }
    L_00585950:
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x00585954 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005857d0
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
    // 0x005857e0
    charge(ctx, 16);
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = addiu(s1, 640);
    sd(ra, sp, 0x18);
    link(ctx, 0x5857FCu);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 60);
    call(ctx, gen::fn_sub_5990C0_005990c0);
    a0 = s2;
    s0 = v0;
    jal(ctx, 0x585808u, gen::fn_sub_584D30_00584d30);
    v1 = v0;
    v0 = 3;
    if (s0 != v0) {
        ld(s0, sp, 0x0);
        // 0x005858c0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00585820
    charge(ctx, 3);
    v0 = 2;
    if (v1 != v0) {
        // 0x0058582c
        charge(ctx, 7);
        lw(a0, s2, 12);
        lw(v1, a0, 0);
        lw(v0, v1, 36);
        a1 = 1;
        jalr(ctx, 0x585838u, v0.u());
        ld(s0, sp, 0x0);
        if (v0 == 0) {
            goto L_00585848;
        }
        // 0x005858c0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_00585848:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x585848u, gen::fn_sub_580130_00580130);
    lb(v1, s1, 114);
    if (v1 != 0) {
        lb(v1, s1, 112);
    } else {
        // 0x0058585c
        charge(ctx, 4);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x585860u, gen::fn_sub_580750_00580750);
        lb(v1, s1, 112);
    }
    // 0x0058586c
    charge(ctx, 3);
    v0 = 1;
    if (v1 != v0) {
        lb(v0, s1, 114);
    } else {
        // 0x00585878
        charge(ctx, 4);
        link(ctx, 0x585878u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 60);
        call(ctx, gen::fn_sub_589F70_00589f70);
        if (v0 == 0) {
            lb(v0, s1, 114);
        } else {
            // 0x00585888
            charge(ctx, 4);
            a0 = 0x7D0000;
            a0 = addiu(a0, -25488);  // "E99072103 mwPlyStartXX: can't link stream"
            jal(ctx, 0x58588Cu, gen::fn_sub_585590_00585590);
            lb(v0, s1, 114);
        }
    }
    // 0x00585898
    charge(ctx, 2);
    ld(s0, sp, 0x0);
    if (v0 != 0) {
        // 0x005858c0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005858a0
    charge(ctx, 7);
    a0 = s2;
    ld(s2, sp, 0x10);
    a1 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_584E08_00584e08(ctx);  // tail call
}

// 0x00585960 sub_585960 -- 188 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [MWSTM_ReqStart] MWSFD: starts the ADXT file input unless it is already playing: the input SJ's reset method, the
// file request (sub_586530), the start (sub_5865A8); -1 with status 4 and 'MWSTM_ReqStart: can't start' on failure,
// else the header probe (sub_57C730) and 1.
void sub_585960(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585960
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    link(ctx, 0x585970u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, ply::kAdxt);
    call(ctx, gen::fn_sub_586610_00586610);
    v1 = 2;
    if (v0 != v1) {
        lw(a0, s0, ply::kInputSj);
        // 0x00585990
        charge(ctx, 2);
        if (a0 == 0) {
            lw(a1, s0, ply::kFname);
        } else {
            // 0x00585998
            charge(ctx, 5);
            lw(v1, a0, 0);
            lw(v0, v1, 20);
            jalr(ctx, 0x5859A0u, v0.u());
            lw(a1, s0, ply::kFname);
        }
        // 0x005859ac
        charge(ctx, 10);
        lw(a0, s0, ply::kAdxt);
        lw(a2, s0, ply::kFileArg0);
        lw(a3, s0, ply::kFileArg1);
        link(ctx, 0x5859B8u);  // $ra first: the delay slot below depends on it
        lw(t0, s0, ply::kFileArg2);
        call(ctx, gen::fn_sub_586530_00586530);
        link(ctx, 0x5859C0u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, ply::kAdxt);
        call(ctx, gen::fn_sub_5865A8_005865a8);
        v1 = si(-1);
        a0 = s0;
        if (v0 != v1) {
            // 0x00585a00
            charge(ctx, 3);
            jal(ctx, 0x585A00u, gen::fn_sub_57C730_0057c730);
            v0 = 1;
        } else {
            // 0x005859d4
            charge(ctx, 11);
            v0 = 4;
            a0 = si(-102);
            link(ctx, 0x5859DCu);  // $ra first: the delay slot below depends on it
            sw(v0, s0, ply::kStat);
            call(ctx, gen::fn_sub_57FC60_0057fc60);
            a0 = 0x7D0000;
            lw(a1, s0, ply::kFname);
            a0 = addiu(a0, -25440);  // "E211141 MWSTM_ReqStart: can't start '%s'"
            jal(ctx, 0x5859ECu, gen::fn_sub_585590_00585590);
            sw(zero, s0, ply::kStartPend);
            v0 = si(-1);
        }
    } else {
        // 0x00585984
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x00585a0c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00585A20 sub_585A20 -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwlSfdExecDecSvrPlaying] MWSFD: the playing step (status 2): a requested termination (+113) ends SFD's input once
// the loop list is idle ('mwlSfdExecDecSvrPlaying: can't term'); without loop play, end of file ends the input; SFD
// status 6 makes the player 3 (play end).
void sub_585A20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585a20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    lb(v0, s0, ply::kTermReq);
    lw(s1, s0, ply::kSfd);
    if (v0 == v1) {
        // 0x00585a44
        charge(ctx, 4);
        link(ctx, 0x585A44u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, ply::kLsc);
        call(ctx, gen::fn_sub_55D7C0_0055d7c0);
        if (v0 == 0) {
            // 0x00585a54
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x585A54u, gen::fn_sub_597968_00597968);
            if (v0 == 0) {
                sb(zero, s0, ply::kTermReq);
            } else {
                // 0x00585a64
                charge(ctx, 4);
                a0 = 0x7D0000;
                a0 = addiu(a0, -25392);  // "E99072102 mwlSfdExecDecSvrPlaying: can't term"
                jal(ctx, 0x585A68u, gen::fn_sub_585590_00585590);
                sb(zero, s0, ply::kTermReq);
            }
            goto L_00585a74;
        }
        lhu(v0, s0, ply::kLinkFlg);
        goto L_00585a78;
    }
L_00585a74:
    charge(ctx, 1);
    lhu(v0, s0, ply::kLinkFlg);
L_00585a78:
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x00585a80
        charge(ctx, 4);
        link(ctx, 0x585A80u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, ply::kLsc);
        call(ctx, gen::fn_sub_55D7C0_0055d7c0);
        if (v0 == 0) {
            // 0x00585a90
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x585A90u, gen::fn_sub_580958_00580958);
        }
    }
    // 0x00585a98
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x585A98u, gen::fn_sub_5990C0_005990c0);
    v1 = 6;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00585aac
        charge(ctx, 3);
        v0 = 3;
        sw(v0, s0, ply::kStat);
        ld(s0, sp, 0x0);
    }
    // 0x00585ab8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00585AC8 sub_585AC8 -- 116 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyExecSvrHndlStep] MWSFD: one player's server step: the status's step (1 preparing, 2 playing; jump table
// 0x7C9D00), the error check, the empty hook. Returns 0.
void sub_585AC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00585ac8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v1, s0, ply::kStat);
    v0 = sltiu(v1, 5);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = sll(v1, 2);
    if (!cc) {
        // 0x00585ae8
        charge(ctx, 5);
        v1 = 0x7D0000;
        v1 = addu(v1, v0);
        lw(v1, v1, -25344);
        switch (v1.u()) {
        case 0x585B00u:  // table[1]
            // 0x00585b00
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x585B00u, gen::fn_sub_585738_00585738);
            break;
        case 0x585B10u:  // table[2]
            // 0x00585b10
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x585B10u, gen::fn_sub_585A20_00585a20);
            break;
        case 0x585B18u:  // table[0, 3, 4]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00585b18
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x585B18u, gen::fn_sub_585B40_00585b40);
    a0 = s0;
    jal(ctx, 0x585B20u, gen::fn_sub_581148_00581148);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00585B40 sub_585B40 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwPlyCheckInputError] MWSFD: status 4 (error) when the ADXT input reports an error or the loop-play list ended.
void sub_585B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00585b40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, ply::kAdxt);
    a0 = v0;
    if (v0 != 0) {
        // 0x00585b5c
        charge(ctx, 4);
        jal(ctx, 0x585B5Cu, gen::fn_r_lock_def_get_free_item_4_005863f8);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 4;
        if (!cc) {
            // 0x00585b6c
            charge(ctx, 1);
            sw(v0, s0, ply::kStat);
        }
    }
    // 0x00585b70
    charge(ctx, 3);
    lw(a0, s0, ply::kLsc);
    if (a0 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00585b7c
        charge(ctx, 5);
        jal(ctx, 0x585B7Cu, gen::fn_sub_5847A8_005847a8);
        v1 = 1;
        if (v0 != v1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00585b90
            charge(ctx, 3);
            v0 = 4;
            sw(v0, s0, ply::kStat);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00585b9c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00585BA8 sub_585BA8 -- 20 bytes; frame 0x10: ra sp+0x0
// [mwsfdVsyncThunk] MWSFD: thunk to the vsync handler wrapper (r_lock_def_free_3).
void sub_585BA8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585ba8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_r_lock_def_free_3_00585c70(ctx);  // tail call
}

// 0x00585BC0 sub_585BC0 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdExecSvrMode1] MWSFD: runs the decode server when the server mode (work +16) is 1; else 0.
void sub_585BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585bc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x585BCCu, gen::fn_sub_585C50_00585c50);
    v1 = 1;
    a0 = s0;
    a1 = 0;
    if (v0 == v1) {
        // 0x00585be4
        charge(ctx, 3);
        jal(ctx, 0x585BE4u, gen::fn_sub_585E70_00585e70);
        a1 = v0;
    }
    // 0x00585bf0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = a1;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00585C08 sub_585C08 -- 68 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdExecSvrMode0] MWSFD: runs the decode server when the server mode is not 1.
void sub_585C08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585c08
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x585C14u, gen::fn_sub_585C50_00585c50);
    v1 = 1;
    a0 = s0;
    a1 = 0;
    if (v0 != v1) {
        // 0x00585c2c
        charge(ctx, 3);
        jal(ctx, 0x585C2Cu, gen::fn_sub_585E70_00585e70);
        a1 = v0;
    }
    // 0x00585c38 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    v0 = a1;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00585C50 sub_585C50 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdGetSvrMode] MWSFD: the server mode (work +16).
void sub_585C50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585c50
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585C58u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, v0, 16);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00585C70 r_lock_def_free_3 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdVsyncHandler] MWSFD: the vsync handler wrapper: runs sub_585C90, returns 0 (FLIRT misname).
void r_lock_def_free_3(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585c70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585C78u, gen::fn_r_lock_def_get_free_item_3_00585c90);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00585C90 r_lock_def_get_free_item_3 -- 164 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// [mwsfdVsync] MWSFD: the vsync work: counts 0x7B4540 / 0x7B4544; when MWSFD is initialised, takes the vsync lock
// (work +92), runs SFD's vsync (sub_595BA0) and frees the lock (FLIRT misname).
void r_lock_def_get_free_item_3(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585c90
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0x7B0000;
    sd(s1, sp, 0x8);
    a2 = 0x7B0000;
    sd(s2, sp, 0x10);
    a1 = addiu(a1, 17728);  // &0x7B4540
    sd(s0, sp, 0x0);
    a2 = addiu(a2, 17732);  // &0x7B4544
    sd(ra, sp, 0x18);
    a0 = 0x7B0000;
    s2 = addiu(a0, 12108);  // &0x7B2F4C
    a0 = 1;
    lw(v1, a1, 0);  // 0x7B4540
    lw(v0, a2, 0);  // 0x7B4544
    lw(s1, s2, 0);  // 0x7B2F4C
    v1 = addiu(v1, 1);
    v0 = addiu(v0, 1);
    sw(v1, a1, 0);  // 0x7B4540
    sw(v0, a2, 0);  // 0x7B4544
    if (s1 != a0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00585ce4
        charge(ctx, 8);
        jal(ctx, 0x585CE4u, gen::fn___gthread_get_ee_key_use_0057f740);
        s0 = addiu(v0, 92);
        a0 = s0;
        jal(ctx, 0x585CF0u, gen::fn_sub_585578_00585578);
        v1 = v0;
        if (v1 != s1) {
            ld(s0, sp, 0x0);
        } else {
            // 0x00585d04
            charge(ctx, 3);
            lw(v0, s2, 0);
            if (v0 != v1) {
                sw(zero, s0, 0);
            } else {
                // 0x00585d10
                charge(ctx, 3);
                jal(ctx, 0x585D10u, gen::fn_sub_595BA0_00595ba0);
                sw(zero, s0, 0);
            }
            // 0x00585d1c
            charge(ctx, 1);
            ld(s0, sp, 0x0);
        }
    }
    // 0x00585d20 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00585DA8 sub_585DA8 -- 48 bytes; frame 0x10: ra sp+0x0
// [mwsfdCallPreHook] MWSFD: the decode server's pre hook (work +64 with +68).
void sub_585DA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585da8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585DB0u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v1, v0, 64);
    lw(a0, v0, 68);
    if (v1 != 0) {
        // 0x00585dc4
        charge(ctx, 2);
        jalr(ctx, 0x585DC4u, v1.u());
    }
    // 0x00585dcc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00585DD8 sub_585DD8 -- 48 bytes; frame 0x10: ra sp+0x0
// [mwsfdCallMidHook] MWSFD: the decode server's mid hook (work +72 with +76).
void sub_585DD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585dd8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585DE0u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v1, v0, 72);
    lw(a0, v0, 76);
    if (v1 != 0) {
        // 0x00585df4
        charge(ctx, 2);
        jalr(ctx, 0x585DF4u, v1.u());
    }
    // 0x00585dfc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00585E40 sub_585E40 -- 48 bytes; frame 0x10: ra sp+0x0
// [mwsfdCallPostHook] MWSFD: the decode server's post hook (work +80 with +84).
void sub_585E40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585e40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585E48u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v1, v0, 80);
    lw(a0, v0, 84);
    if (v1 != 0) {
        // 0x00585e5c
        charge(ctx, 2);
        jalr(ctx, 0x585E5Cu, v1.u());
    }
    // 0x00585e64 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00585E70 sub_585E70 -- 196 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// [mwPlyExecSvr] MWSFD: the decode server: under the lock (work +88) runs the pre hook, every player's server (8 x
// 684 from 0x7B2FBC), frees the lock, runs SFD's server (sub_595BE8) and the mid hook; when SFD is idle and no player
// is in a server call, the post hook. Returns SFD's busy flag.
void sub_585E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00585e70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x7B0000;
    sd(s1, sp, 0x8);
    v1 = 1;
    lw(s1, v0, 12108);  // 0x7B2F4C
    v0 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    if (s1 == v1) {
        // 0x00585e94
        charge(ctx, 7);
        jal(ctx, 0x585E94u, gen::fn___gthread_get_ee_key_use_0057f740);
        s0 = v0;
        a0 = addiu(s0, 88);
        jal(ctx, 0x585EA0u, gen::fn_sub_585578_00585578);
        cc = v0 != s1;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00585eb0
            charge(ctx, 4);
            s0 = addiu(s0, 108);
            jal(ctx, 0x585EB0u, gen::fn_sub_585DA8_00585da8);
            s1 = 7;
            for (;;) {
                // 0x00585ec0
                charge(ctx, 2);
                if (s0 == 0) {
                    s1 = addiu(s1, -1);
                } else {
                    // 0x00585ec8
                    charge(ctx, 3);
                    a0 = s0;
                    jal(ctx, 0x585EC8u, gen::fn_sub_585F38_00585f38);
                    s1 = addiu(s1, -1);
                }
                // 0x00585ed4
                charge(ctx, 2);
                s0 = addiu(s0, 684);
                if (i64(s1) < 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00585edc
            charge(ctx, 10);
            a0 = 0;
            s0 = 1;
            jal(ctx, 0x585EE0u, gen::fn_sub_5860E8_005860e8);
            jal(ctx, 0x585EE8u, gen::fn_sub_595BE8_00595be8);
            v0 = v0 ^ s0;
            s1 = sltu(0, v0);
            jal(ctx, 0x585EF4u, gen::fn_sub_585DD8_00585dd8);
            v0 = s1;
            if (s1 != s0) {
                // 0x00585f04
                charge(ctx, 4);
                jal(ctx, 0x585F04u, gen::fn_sub_586200_00586200);
                cc = v0 == s0;  // the condition, before the delay slot changes it
                v0 = s1;
                if (!cc) {
                    // 0x00585f14
                    charge(ctx, 3);
                    jal(ctx, 0x585F14u, gen::fn_sub_585E40_00585e40);
                    v0 = s1;
                }
            }
        }
    }
    // 0x00585f20 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00585F38 sub_585F38 -- 372 bytes; frame 0x10: ra sp+0x0
// [mwPlyExecSvrHndl] MWSFD: one player's server call: 'NULL handle' for 0; skipped for a free player, a re-entered
// one (+96) or while another server call runs (work +36); marks +96, remembers the player (0x7B4548), runs SFD's
// per-handle server (sub_595C60) with +100 marked, the status step when the status is set (+104), then SFD's post
// step (sub_595BC0).
void sub_585F38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585f38
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00585f50
    charge(ctx, 10);
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(a1, v0, 12108);  // 0x7B2F4C
    v0 = 0;
    v1 = 1;
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    s1 = a0;
    sd(ra, sp, 0x10);
    if (a1 != v1) {
        // 0x00585fd8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00585f78
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x00585f80
        charge(ctx, 3);
        a0 = 0x7D0000;
        a0 = addiu(a0, -25320);  // "E1071901 mwPlyExecSvrHndl: NULL handle."
        jal(ctx, 0x585F84u, gen::fn_sub_585590_00585590);
        goto L_00585f8c;
    }
    // 0x00585f98
    charge(ctx, 3);
    lw(s0, s1, 0);
    v0 = 0;
    if (s0 != a1) {
        // 0x00585fd8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00585fa4
    charge(ctx, 4);
    jal(ctx, 0x585FA4u, gen::fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138);
    if (v0 == s0) {
        v0 = 0;
        // 0x00585fd8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00585fb4
    charge(ctx, 4);
    jal(ctx, 0x585FB4u, gen::fn_sub_586200_00586200);
    a0 = s1;
    if (v0 == s0) {
        backedge(ctx);
    L_00585f8c:
        charge(ctx, 2);
        v0 = 0;
        // 0x00585fd8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x00585fc4
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x00585ff0
    charge(ctx, 14);
    sp = addiu(sp, -0x20);
    a1 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    link(ctx, 0x58600Cu);  // $ra first: the delay slot below depends on it
    lw(s2, s0, 60);
    call(ctx, gen::fn_sub_586130_00586130);
    lw(s1, s0, 0);
    v0 = 1;
    a1 = 1;
    a0 = s0;
    if (s1 == v0) {
        // 0x00586038
        charge(ctx, 11);
        v0 = 0x7B0000;
        link(ctx, 0x58603Cu);  // $ra first: the delay slot below depends on it
        sw(s0, v0, 17736);
        call(ctx, gen::fn_sub_586140_00586140);
        a0 = s2;
        jal(ctx, 0x586044u, gen::fn_sub_595C60_00595c60);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x586050u, gen::fn_sub_586140_00586140);
        lw(v0, s0, 4);
        a0 = s0;
        if (v0 != 0) {
            // 0x00586070
            charge(ctx, 3);
            link(ctx, 0x586070u);  // $ra first: the delay slot below depends on it
            sw(s1, s0, 104);
            call(ctx, gen::fn_sub_585AC8_00585ac8);
            a0 = s0;
        } else {
            // 0x00586064
            charge(ctx, 2);
            sw(zero, s0, 104);
        }
        // 0x0058607c
        charge(ctx, 6);
        a1 = 0;
        jal(ctx, 0x58607Cu, gen::fn_sub_586130_00586130);
        a0 = s2;
        jal(ctx, 0x586084u, gen::fn_sub_595BC0_00595bc0);
        v0 = v0 ^ 0x1;
        v0 = sltu(0, v0);
    } else {
        // 0x00586028
        charge(ctx, 4);
        a1 = 0;
        jal(ctx, 0x586028u, gen::fn_sub_586130_00586130);
        v0 = 0;
    }
    // 0x00586094 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x005860E8 sub_5860E8 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdSetSvrLock] MWSFD: sets the decode-server lock word (work +88).
void sub_5860E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005860e8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5860F4u, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, 88);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00586130 sub_586130 -- 8 bytes; leaf frame (no stack)
// [mwPlySetInSvr] MWSFD: sets the player's 'in server' word (+96).
void sub_586130(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00586130
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, ply::kInSvr);
}

// 0x00586138 tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc -- 8 bytes; leaf frame (no stack)
// [mwPlyGetInSvr] MWSFD: the player's 'in server' word (+96) (FLIRT misname).
void tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00586138
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, ply::kInSvr);
}

// 0x00586140 sub_586140 -- 8 bytes; leaf frame (no stack)
// [mwPlySetInSfdSvr] MWSFD: sets the player's 'in SFD server' word (+100).
void sub_586140(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00586140
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(a1, a0, ply::kInSfdSvr);
}

// 0x005861B8 sub_5861B8 -- 60 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [mwsfdSetSvrBusy] MWSFD: sets the server-busy word: the player's +92 (when given) and work +36.
void sub_5861B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005861b8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5861CCu, gen::fn___gthread_get_ee_key_use_0057f740);
    if (s0 != 0) {
        sw(s1, s0, 92);
    }
    // 0x005861dc
    charge(ctx, 6);
    sw(s1, v0, 36);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00586200 sub_586200 -- 32 bytes; frame 0x10: ra sp+0x0
// [mwsfdGetSvrBusy] MWSFD: the server-busy word (work +36).
void sub_586200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586200
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x586208u, gen::fn___gthread_get_ee_key_use_0057f740);
    lw(v0, v0, 36);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00586248 sub_586248 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [mwsfdWaitSvr] MWSFD: waits for the decode server: scratchpad in, mark busy, release SVM lock 6, unmark, scratchpad
// out, then wait out the player's server call.
void sub_586248(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586248
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x586254u, gen::fn_sub_581108_00581108);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x586260u, gen::fn_sub_5861B8_005861b8);
    jal(ctx, 0x586268u, gen::fn_log10l_11_00585628);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x586274u, gen::fn_sub_5861B8_005861b8);
    jal(ctx, 0x58627Cu, gen::fn_sub_581120_00581120);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_585698_00585698(ctx);  // tail call
}

// 0x005862F0 sub_5862F0 -- 8 bytes; leaf frame (no stack)
// [mwsfdInitHook] MWSFD: an init hook that returns 0.
void sub_5862F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005862f0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

}  // namespace p3fes::game
