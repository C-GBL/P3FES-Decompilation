// The battle code, seventh pass (slice battle7, group camera; docs/ANALYSIS/21_battle.md): the camera shot callbacks
// of the shot tables (the boss shots, the target shots). Siblings of the functions the six replay routes reach in
// 0x290000-0x2FFFFF (a first-call probe found 19 of the 371 still-recompiled functions of the band reached; the AI
// rows only run for enemies without an AI script). The bodies are p3fes_handgen's (frame, spills, $ra links, every
// register, cycle charges, check points); this file names their offsets (battle3.h b3::, battle4.h b4::, battle5.h
// b5::, battle7.h b7::) and gives each its role -- proposed names in brackets (ADR-0009), symbols in code are
// functions.json's. Still-recompiled callees are reached through their gen:: entry points.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle7.h"

namespace p3fes::recomp_gen {
void fn_sub_2880E0_002880e0(p3fes::EEContext&);
void fn_sub_2A2170_002a2170(p3fes::EEContext&);
void fn_sub_2A2290_002a2290(p3fes::EEContext&);
void fn_sub_2A3110_002a3110(p3fes::EEContext&);
void fn_sub_2A3750_002a3750(p3fes::EEContext&);
void fn_sub_2A4470_002a4470(p3fes::EEContext&);
void fn_sub_2A44B0_002a44b0(p3fes::EEContext&);
void fn_sub_2A4690_002a4690(p3fes::EEContext&);
void fn_sub_2A5F40_002a5f40(p3fes::EEContext&);
void fn_sub_2A8D20_002a8d20(p3fes::EEContext&);
void fn_sub_2AD880_002ad880(p3fes::EEContext&);
void fn_sub_2ADC30_002adc30(p3fes::EEContext&);
void fn_sub_2ADC80_002adc80(p3fes::EEContext&);
void fn_sub_2ADCD0_002adcd0(p3fes::EEContext&);
void fn_sub_2B0210_002b0210(p3fes::EEContext&);
void fn_sub_2B2060_002b2060(p3fes::EEContext&);
void fn_sub_2B21F0_002b21f0(p3fes::EEContext&);
void fn_sub_2B2800_002b2800(p3fes::EEContext&);
void fn_sub_2B2880_002b2880(p3fes::EEContext&);
void fn_sub_2B2EB0_002b2eb0(p3fes::EEContext&);
void fn_sub_2B32C0_002b32c0(p3fes::EEContext&);
void fn_sub_2B4DB0_002b4db0(p3fes::EEContext&);
void fn_sub_2B4F40_002b4f40(p3fes::EEContext&);
void fn_sub_2E4A30_002e4a30(p3fes::EEContext&);
void fn_sub_2E5040_002e5040(p3fes::EEContext&);
void fn_sub_2E6A20_002e6a20(p3fes::EEContext&);
void fn_sub_2E70B0_002e70b0(p3fes::EEContext&);
void fn_sub_2E71C0_002e71c0(p3fes::EEContext&);
void fn_sub_2E7320_002e7320(p3fes::EEContext&);
void fn_sub_2E7680_002e7680(p3fes::EEContext&);
void fn_sub_2E76A0_002e76a0(p3fes::EEContext&);
void fn_sub_2E7710_002e7710(p3fes::EEContext&);
void fn_sub_2E77C0_002e77c0(p3fes::EEContext&);
void fn_sub_2E7810_002e7810(p3fes::EEContext&);
void fn_sub_2E7880_002e7880(p3fes::EEContext&);
void fn_sub_2E87B0_002e87b0(p3fes::EEContext&);
void fn_sub_2E8C80_002e8c80(p3fes::EEContext&);
void fn_sub_2E8C90_002e8c90(p3fes::EEContext&);
void fn_sub_2E8D20_002e8d20(p3fes::EEContext&);
void fn_sub_2E8D40_002e8d40(p3fes::EEContext&);
void fn_sub_2E8D70_002e8d70(p3fes::EEContext&);
void fn_sub_2E9060_002e9060(p3fes::EEContext&);
void fn_sub_30C3A0_0030c3a0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b7;  // this slice's additions (battle7.h)

// 0x002ADC30 sub_2ADC30 -- 60 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2AD880(shot, 10.0, 2.0, 0.0, 250.0) (f12..f15).
// Arguments: a0 the camera shot.
void sub_2ADC30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x002adc30
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x41200000;
    mtc1(v0, f12);
    v0 = 0x40000000;
    mtc1(v0, f13);
    mtc1(zero, f14);
    v0 = 0x437A0000;
    mtc1(v0, f15);
    jal(ctx, 0x2ADC54u, gen::fn_sub_2AD880_002ad880);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002ADC80 sub_2ADC80 -- 64 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2AD880(shot, 15.0, 2.0, 0.25, 400.0) (f12..f15).
// Arguments: a0 the camera shot.
void sub_2ADC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x002adc80
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x41700000;
    mtc1(v0, f12);
    v0 = 0x40000000;
    mtc1(v0, f13);
    v0 = 0x3E800000;
    mtc1(v0, f14);
    v0 = 0x43C80000;
    mtc1(v0, f15);
    jal(ctx, 0x2ADCA8u, gen::fn_sub_2AD880_002ad880);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002ADCD0 sub_2ADCD0 -- 36 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2A8D20(shot, 1).
// Arguments: a0 the camera shot.
void sub_2ADCD0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002adcd0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 1;
    jal(ctx, 0x2ADCDCu, gen::fn_sub_2A8D20_002a8d20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002B2880 sub_2B2880 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Camera shot update: while the shot's action still has its one target (the shot's +256) and is active, sub_2B21F0
// (first call flagged) and the call counter +268.
// Arguments: a0 the camera shot.
void sub_2B2880(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002b2880
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a1, a0, shot::kAction);
    if (a1 != 0) {
        // 0x002b289c
        charge(ctx, 4);
        lhu(a0, a1, act::kTargetCount);
        v1 = 1;
        if (a0 == v1) {
            // 0x002b28ac
            charge(ctx, 4);
            lw(a0, s0, shot::kTarget);
            lw(v1, a1, act::kTargets);
            if (a0 == v1) {
                // 0x002b28bc
                charge(ctx, 4);
                lhu(v1, a1, act::kFlags2);
                v1 = v1 & 0x1;
                if (v1 != 0) {
                    // 0x002b28cc
                    charge(ctx, 5);
                    lhu(v1, s0, shot::kCalls);
                    lhu(v0, s0, 270);
                    at = slt(v1, v0);
                    if (at != 0) {
                        // 0x002b2904
                        charge(ctx, 1);
                        lwc1(f12, gp, -32512);  // 0x7CADF0
                    } else {
                        // 0x002b28e0
                        charge(ctx, 3);
                        lw(v0, s0, 264);
                        if (v0 == 0) {
                            // 0x002b28f8
                            charge(ctx, 1);
                            lwc1(f12, gp, kGpF03a);  // f32 0.3: sub_319090's argument in sub_288780 0x7CAD7C
                        } else {
                            // 0x002b28ec
                            charge(ctx, 3);
                            lwc1(f12, gp, -32516);  // 0x7CADEC
                        }
                        // 0x002b28fc
                        charge(ctx, 2);
                    }
                    // 0x002b2908
                    charge(ctx, 8);
                    a1 = v1;
                    a1 = sltiu(a1, 1);
                    a0 = s0;
                    jal(ctx, 0x2B2914u, gen::fn_sub_2B21F0_002b21f0);
                    lhu(v1, s0, shot::kCalls);
                    v1 = addiu(v1, 1);
                    sh(v1, s0, shot::kCalls);
                }
            }
        }
    }
    // 0x002b2928 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002B32C0 sub_2B32C0 -- 112 bytes; frame 0x60: ra sp+0x10, s0 sp+0x0 (sq)
// Camera shot: aims the camera at the shot point (+156) from the position sub_2B2EB0 computes (sub_2A2290 /
// sub_2A3110).
// Arguments: a0 the camera shot.
void sub_2B32C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002b32c0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(sp, 0x20);
    a1 = addiu(s0, 156);
    jal(ctx, 0x2B32D8u, gen::fn_sub_2A4470_002a4470);
    a0 = s0;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x2B32E8u, gen::fn_sub_2B2EB0_002b2eb0);
    a0 = s0;
    a1 = addiu(sp, 0x20);
    a2 = addiu(sp, 0x3C);
    a3 = 1;
    jal(ctx, 0x2B3300u, gen::fn_sub_2A2290_002a2290);
    v0 = 0x41200000;
    mtc1(v0, f12);
    a0 = s0;
    jal(ctx, 0x2B3314u, gen::fn_sub_2A3110_002a3110);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002E4A30 sub_2E4A30 -- 8 bytes; leaf frame (no stack)
// Camera shot callback: does nothing.
// Arguments: none.
void sub_2E4A30(EEContext& ctx) {
    using namespace hg;
    // 0x002e4a30
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x002E5040 sub_2E5040 -- 32 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2A5F40.
// Arguments: a0 the camera shot.
void sub_2E5040(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x002e5040
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2E5048u, gen::fn_sub_2A5F40_002a5f40);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E71C0 sub_2E71C0 -- 80 bytes; frame 0x10: ra sp+0x0
// Boss camera shot update: while the action is active and the side shot was taken (gBtl +2936), sub_2B0210.
// Arguments: a0 the camera shot.
void sub_2E71C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e71c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, shot::kAction);
    if (v1 != 0) {
        // 0x002e71d4
        charge(ctx, 4);
        lhu(v1, v1, act::kFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x002e71e4
            charge(ctx, 5);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(a1, v1, gbtl7::kCamSideShot);
            v1 = 1;
            if (a1 == v1) {
                // 0x002e71f8
                charge(ctx, 2);
                jal(ctx, 0x2E71F8u, gen::fn_sub_2B0210_002b0210);
            }
        }
    }
    // 0x002e7200 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E7320 sub_2E7320 -- 8 bytes; leaf frame (no stack)
// Camera shot callback: does nothing.
// Arguments: none.
void sub_2E7320(EEContext& ctx) {
    using namespace hg;
    // 0x002e7320
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x002E7680 sub_2E7680 -- 32 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2B2060.
// Arguments: a0 the camera shot.
void sub_2E7680(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x002e7680
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2E7688u, gen::fn_sub_2B2060_002b2060);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E76A0 sub_2E76A0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Boss camera shot start: remembers the action's first target (gBtl +2932); unless the unit is analysed (sub_30C3A0),
// sub_2B2800.
// Arguments: a0 the camera shot.
void sub_2E76A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e76a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, shot::kAction);
    if (v1 != 0) {
        // 0x002e76bc
        charge(ctx, 10);
        lw(v1, v1, act::kTargets);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(v1, v0, gbtl7::kCamLastTarget);
        lw(v0, s0, shot::kAction);
        lw(v0, v0, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2E76D4u, gen::fn_sub_30C3A0_0030c3a0);
        if (v0 == 0) {
            // 0x002e76e4
            charge(ctx, 3);
            a0 = s0;
            jal(ctx, 0x2E76E8u, gen::fn_sub_2B2800_002b2800);
        }
    }
    // 0x002e76f0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E7710 sub_2E7710 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Boss camera shot update: for an analysed unit (sub_30C3A0) the target shot sub_2E6A20 while the one target is still
// the remembered one; else sub_2B2880.
// Arguments: a0 the camera shot.
void sub_2E7710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e7710
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, shot::kAction);
    if (a0 != 0) {
        // 0x002e772c
        charge(ctx, 4);
        lhu(v1, a0, act::kFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x002e773c
            charge(ctx, 6);
            lw(v0, a0, act::kUnit);
            lw(a0, v0, unit::kDat);
            jal(ctx, 0x2E7744u, gen::fn_sub_30C3A0_0030c3a0);
            if (v0 == 0) {
                // 0x002e7794
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x2E7798u, gen::fn_sub_2B2880_002b2880);
            } else {
                // 0x002e7754
                charge(ctx, 5);
                lw(a1, s0, shot::kAction);
                lhu(a0, a1, act::kTargetCount);
                v1 = 1;
                if (a0 == v1) {
                    // 0x002e7768
                    charge(ctx, 5);
                    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(a0, v1, gbtl7::kCamLastTarget);
                    lw(v1, a1, act::kTargets);
                    if (a0 == v1) {
                        // 0x002e777c
                        charge(ctx, 6);
                        a0 = s0;
                        lwc1(f12, gp, -32672);  // 0x7CAD50
                        jal(ctx, 0x2E7784u, gen::fn_sub_2E6A20_002e6a20);
                    }
                }
            }
        }
    }
    // 0x002e77a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E77C0 sub_2E77C0 -- 76 bytes; frame 0x10: ra sp+0x0
// Boss camera shot start for an enemy action: sub_2E70B0.
// Arguments: a0 the camera shot.
void sub_2E77C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e77c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, shot::kAction);
    if (a1 != 0) {
        // 0x002e77d4
        charge(ctx, 4);
        lhu(v1, a1, act::kFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x002e77e4
            charge(ctx, 4);
            lw(v1, a1, act::kUnit);
            lbu(v1, v1, unit::kSide);
            if (v1 != 0) {
                // 0x002e77f4
                charge(ctx, 2);
                jal(ctx, 0x2E77F4u, gen::fn_sub_2E70B0_002e70b0);
            }
        }
    }
    // 0x002e77fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E7810 sub_2E7810 -- 112 bytes; frame 0x10: ra sp+0x0
// Boss camera shot update for an enemy action: sub_2B0210 once the side shot was taken (gBtl +2936).
// Arguments: a0 the camera shot.
void sub_2E7810(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e7810
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, shot::kAction);
    if (a2 != 0) {
        // 0x002e7824
        charge(ctx, 4);
        lhu(v1, a2, act::kFlags2);
        a1 = v1 & 0x1;
        if (a1 != 0) {
            // 0x002e7834
            charge(ctx, 4);
            lw(v1, a2, act::kUnit);
            lbu(v1, v1, unit::kSide);
            if (v1 != 0) {
                // 0x002e7844
                charge(ctx, 2);
                if (a2 != 0) {
                    // 0x002e784c
                    charge(ctx, 2);
                    if (a1 != 0) {
                        // 0x002e7854
                        charge(ctx, 5);
                        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                        lhu(a1, v1, gbtl7::kCamSideShot);
                        v1 = 1;
                        if (a1 == v1) {
                            // 0x002e7868
                            charge(ctx, 2);
                            jal(ctx, 0x2E7868u, gen::fn_sub_2B0210_002b0210);
                        }
                    }
                }
            }
        }
    }
    // 0x002e7870 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E7880 sub_2E7880 -- 8 bytes; leaf frame (no stack)
// Camera shot callback: does nothing.
// Arguments: none.
void sub_2E7880(EEContext& ctx) {
    using namespace hg;
    // 0x002e7880
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x002E87B0 sub_2E87B0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Camera shot update: plays the shot's motion (+292) on its unit (+288, sub_2880E0) once sub_2A3750 says so.
// Arguments: a0 the camera shot.
void sub_2E87B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e87b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a1, a0, shot::kMotionUnit);
    if (a1 != 0) {
        // 0x002e87cc
        charge(ctx, 3);
        lw(v1, s0, shot::kAction);
        if (v1 != 0) {
            // 0x002e87d8
            charge(ctx, 4);
            lhu(v1, v1, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002e87e8
                charge(ctx, 4);
                jal(ctx, 0x2E87E8u, gen::fn_sub_2A3750_002a3750);
                if (v0 != 0) {
                    // 0x002e87f8
                    charge(ctx, 4);
                    lw(a0, s0, shot::kMotionUnit);
                    lhu(a1, s0, shot::kMotion);
                    jal(ctx, 0x2E8800u, gen::fn_sub_2880E0_002880e0);
                }
            }
        }
    }
    // 0x002e8808 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E8C80 sub_2E8C80 -- 8 bytes; leaf frame (no stack)
// Camera shot callback: does nothing.
// Arguments: none.
void sub_2E8C80(EEContext& ctx) {
    using namespace hg;
    // 0x002e8c80
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x002E8C90 sub_2E8C90 -- 144 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss camera shot: the camera's point from the boss AI row (gBtl +2840 +892 / +904, sub_2A4690), handed to
// sub_2A2170 (gBtl +32) and sub_2A44B0 (the shot point).
// Arguments: a0 the camera shot.
void sub_2E8C90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x002e8c90
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl4::kBossAiRows);
    s0 = addiu(v0, 892);
    a0 = addiu(sp, 0x3C);
    a1 = s0;
    a2 = addiu(s0, 12);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8CC4u, gen::fn_sub_2A4690_002a4690);
    a1 = addiu(sp, 0x30);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, sp, 0x30);
    swc1(f1, sp, 0x34);
    swc1(f0, sp, 0x38);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, 32);
    jal(ctx, 0x2E8CF0u, gen::fn_sub_2A2170_002a2170);
    a0 = addiu(s1, 156);
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x2E8D00u, gen::fn_sub_2A44B0_002a44b0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002E8D20 sub_2E8D20 -- 32 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2B4F40.
// Arguments: a0 the camera shot.
void sub_2E8D20(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x002e8d20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2E8D28u, gen::fn_sub_2B4F40_002b4f40);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E8D40 sub_2E8D40 -- 36 bytes; frame 0x10: ra sp+0x0
// Camera shot callback: sub_2B4DB0.
// Arguments: a0 the camera shot.
void sub_2E8D40(EEContext& ctx) {
    using namespace hg;
    Gpr gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e8d40
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lwc1(f12, gp, -32504);  // 0x7CADF8
    jal(ctx, 0x2E8D4Cu, gen::fn_sub_2B4DB0_002b4db0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E8D70 sub_2E8D70 -- 168 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss camera shot: from the shot point (+156) to the boss AI row's point (+868 / +880), sub_2A2290 / sub_2A3110.
// Arguments: a0 the camera shot.
void sub_2E8D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x002e8d70
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = addiu(sp, 0x30);
    a1 = addiu(s1, 156);
    jal(ctx, 0x2E8D8Cu, gen::fn_sub_2A4470_002a4470);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl4::kBossAiRows);
    s0 = addiu(v0, 868);
    a0 = addiu(sp, 0x58);
    a1 = s0;
    a2 = addiu(s0, 12);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8DB4u, gen::fn_sub_2A4690_002a4690);
    a2 = addiu(sp, 0x4C);
    lwc1(f2, s0, 0);
    lwc1(f1, s0, 4);
    lwc1(f0, s0, 8);
    swc1(f2, sp, 0x4C);
    swc1(f1, sp, 0x50);
    swc1(f0, sp, 0x54);
    a0 = s1;
    a1 = addiu(sp, 0x30);
    a3 = 1;
    jal(ctx, 0x2E8DE4u, gen::fn_sub_2A2290_002a2290);
    v0 = 0x3F400000;
    mtc1(v0, f12);
    a0 = s1;
    jal(ctx, 0x2E8DF8u, gen::fn_sub_2A3110_002a3110);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002E9060 sub_2E9060 -- 260 bytes; frame 0x60: ra sp+0x10, f20 sp+0x0
// Boss camera shot: the fixed position / target pair 0x699244 / 0x69925C (sub_2A4690 rows), sub_2A2290 / sub_2A3110
// on the battle camera.
// Arguments: none.
void sub_2E9060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002e9060
    enter(ctx, 65);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    swc1(f20, sp, 0x0);
    a0 = addiu(sp, 0x2C);
    a1 = 0x6A0000;
    a1 = addiu(a1, -28092);  // &0x699244
    a2 = 0x6A0000;
    a2 = addiu(a2, -28080);  // &0x699250
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E9088u, gen::fn_sub_2A4690_002a4690);
    v0 = 0x6A0000;
    lwc1(f2, v0, -28092);  // 0x699244
    v0 = 0x6A0000;
    lwc1(f1, v0, -28088);  // 0x699248
    v0 = 0x6A0000;
    lwc1(f0, v0, -28084);  // 0x69924C
    swc1(f2, sp, 0x20);
    swc1(f1, sp, 0x24);
    swc1(f0, sp, 0x28);
    a0 = addiu(sp, 0x48);
    a1 = 0x6A0000;
    a1 = addiu(a1, -28068);  // &0x69925C
    a2 = 0x6A0000;
    a2 = addiu(a2, -28056);  // &0x699268
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E90D0u, gen::fn_sub_2A4690_002a4690);
    a2 = addiu(sp, 0x3C);
    v0 = 0x6A0000;
    lwc1(f2, v0, -28068);  // 0x69925C
    v0 = 0x6A0000;
    lwc1(f1, v0, -28064);  // 0x699260
    v0 = 0x6A0000;
    lwc1(f0, v0, -28060);  // 0x699264
    swc1(f2, sp, 0x3C);
    swc1(f1, sp, 0x40);
    swc1(f0, sp, 0x44);
    v0 = 0x6A0000;
    lh(v0, v0, -28096);  // 0x699240
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41F00000;
    mtc1(v0, f0);
    div_s(f20, f1, f0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, 32);
    a1 = addiu(sp, 0x20);
    a3 = 1;
    jal(ctx, 0x2E9134u, gen::fn_sub_2A2290_002a2290);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, 32);
    mov_s(f12, f20);
    jal(ctx, 0x2E9148u, gen::fn_sub_2A3110_002a3110);
    ld(ra, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game
