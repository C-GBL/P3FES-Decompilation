// The battle code, seventh pass (slice battle7, group ai; docs/ANALYSIS/21_battle.md): the battle AI rows: the
// conditions of the table 0x6971B0 and the target selectors of 0x6975E0 (btlAICommand.c's tables, the rows the
// comm_ai handlers call through jalr), their predicates and helpers, the weighted command decode for units without a
// script, the AI script packets. Siblings of the functions the six replay routes reach in 0x290000-0x2FFFFF (a
// first-call probe found 19 of the 371 still-recompiled functions of the band reached; the AI rows only run for
// enemies without an AI script). The bodies are p3fes_handgen's (frame, spills, $ra links, every register, cycle
// charges, check points); this file names their offsets (battle3.h b3::, battle4.h b4::, battle5.h b5::, battle7.h
// b7::) and gives each its role -- proposed names in brackets (ADR-0009), symbols in code are functions.json's.
// Still-recompiled callees are reached through their gen:: entry points.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle7.h"

namespace p3fes::recomp_gen {
void fn_btlGetMeanLevel_002d4cf0(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datCalcDamage_00303130(p3fes::EEContext&);
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetLevel_002ffcc0(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);
void fn_datCalcGetSkillList_00308bb0(p3fes::EEContext&);
void fn_datCalcGetSkillSlotCount_00308ba0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_scrFindPrcdIdxByName_0035c090(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrGetUserData_0035f160(p3fes::EEContext&);
void fn_sub_17B260_0017b260(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_288F80_00288f80(p3fes::EEContext&);
void fn_sub_289030_00289030(p3fes::EEContext&);
void fn_sub_29A1D0_0029a1d0(p3fes::EEContext&);
void fn_sub_2BFF60_002bff60(p3fes::EEContext&);
void fn_sub_2C0880_002c0880(p3fes::EEContext&);
void fn_sub_2C08B0_002c08b0(p3fes::EEContext&);
void fn_sub_2C08C0_002c08c0(p3fes::EEContext&);
void fn_sub_2C0970_002c0970(p3fes::EEContext&);
void fn_sub_2C0A50_002c0a50(p3fes::EEContext&);
void fn_sub_2C1080_002c1080(p3fes::EEContext&);
void fn_sub_2C1360_002c1360(p3fes::EEContext&);
void fn_sub_2C1440_002c1440(p3fes::EEContext&);
void fn_sub_2C1490_002c1490(p3fes::EEContext&);
void fn_sub_2C14F0_002c14f0(p3fes::EEContext&);
void fn_sub_2C1550_002c1550(p3fes::EEContext&);
void fn_sub_2C15E0_002c15e0(p3fes::EEContext&);
void fn_sub_2C1740_002c1740(p3fes::EEContext&);
void fn_sub_2C1850_002c1850(p3fes::EEContext&);
void fn_sub_2C1960_002c1960(p3fes::EEContext&);
void fn_sub_2C1A30_002c1a30(p3fes::EEContext&);
void fn_sub_2C1B10_002c1b10(p3fes::EEContext&);
void fn_sub_2C1BF0_002c1bf0(p3fes::EEContext&);
void fn_sub_2C1D80_002c1d80(p3fes::EEContext&);
void fn_sub_2C1E50_002c1e50(p3fes::EEContext&);
void fn_sub_2C1E90_002c1e90(p3fes::EEContext&);
void fn_sub_2C1F10_002c1f10(p3fes::EEContext&);
void fn_sub_2C1FC0_002c1fc0(p3fes::EEContext&);
void fn_sub_2C2010_002c2010(p3fes::EEContext&);
void fn_sub_2C2070_002c2070(p3fes::EEContext&);
void fn_sub_2C20C0_002c20c0(p3fes::EEContext&);
void fn_sub_2C2120_002c2120(p3fes::EEContext&);
void fn_sub_2C2170_002c2170(p3fes::EEContext&);
void fn_sub_2C21D0_002c21d0(p3fes::EEContext&);
void fn_sub_2C2220_002c2220(p3fes::EEContext&);
void fn_sub_2C2270_002c2270(p3fes::EEContext&);
void fn_sub_2C2310_002c2310(p3fes::EEContext&);
void fn_sub_2C2360_002c2360(p3fes::EEContext&);
void fn_sub_2C23C0_002c23c0(p3fes::EEContext&);
void fn_sub_2C2420_002c2420(p3fes::EEContext&);
void fn_sub_2C2470_002c2470(p3fes::EEContext&);
void fn_sub_2C24F0_002c24f0(p3fes::EEContext&);
void fn_sub_2C2510_002c2510(p3fes::EEContext&);
void fn_sub_2C25D0_002c25d0(p3fes::EEContext&);
void fn_sub_2C25E0_002c25e0(p3fes::EEContext&);
void fn_sub_2C2630_002c2630(p3fes::EEContext&);
void fn_sub_2C2690_002c2690(p3fes::EEContext&);
void fn_sub_2C26E0_002c26e0(p3fes::EEContext&);
void fn_sub_2C2740_002c2740(p3fes::EEContext&);
void fn_sub_2C2790_002c2790(p3fes::EEContext&);
void fn_sub_2C27F0_002c27f0(p3fes::EEContext&);
void fn_sub_2C2840_002c2840(p3fes::EEContext&);
void fn_sub_2C28A0_002c28a0(p3fes::EEContext&);
void fn_sub_2C28C0_002c28c0(p3fes::EEContext&);
void fn_sub_2C29E0_002c29e0(p3fes::EEContext&);
void fn_sub_2C2C40_002c2c40(p3fes::EEContext&);
void fn_sub_2C2CA0_002c2ca0(p3fes::EEContext&);
void fn_sub_2C3150_002c3150(p3fes::EEContext&);
void fn_sub_2C31B0_002c31b0(p3fes::EEContext&);
void fn_sub_2C3210_002c3210(p3fes::EEContext&);
void fn_sub_2C3270_002c3270(p3fes::EEContext&);
void fn_sub_2C32C0_002c32c0(p3fes::EEContext&);
void fn_sub_2C32E0_002c32e0(p3fes::EEContext&);
void fn_sub_2C3430_002c3430(p3fes::EEContext&);
void fn_sub_2C3770_002c3770(p3fes::EEContext&);
void fn_sub_2C3BE0_002c3be0(p3fes::EEContext&);
void fn_sub_2C3CE0_002c3ce0(p3fes::EEContext&);
void fn_sub_2C3E10_002c3e10(p3fes::EEContext&);
void fn_sub_2C3E20_002c3e20(p3fes::EEContext&);
void fn_sub_2C3E60_002c3e60(p3fes::EEContext&);
void fn_sub_2C3EA0_002c3ea0(p3fes::EEContext&);
void fn_sub_2C3EE0_002c3ee0(p3fes::EEContext&);
void fn_sub_2C3F00_002c3f00(p3fes::EEContext&);
void fn_sub_2C4000_002c4000(p3fes::EEContext&);
void fn_sub_2C4040_002c4040(p3fes::EEContext&);
void fn_sub_2C4080_002c4080(p3fes::EEContext&);
void fn_sub_2C40C0_002c40c0(p3fes::EEContext&);
void fn_sub_2C4100_002c4100(p3fes::EEContext&);
void fn_sub_2C4140_002c4140(p3fes::EEContext&);
void fn_sub_2C4180_002c4180(p3fes::EEContext&);
void fn_sub_2C41C0_002c41c0(p3fes::EEContext&);
void fn_sub_2C4200_002c4200(p3fes::EEContext&);
void fn_sub_2C42C0_002c42c0(p3fes::EEContext&);
void fn_sub_2C43A0_002c43a0(p3fes::EEContext&);
void fn_sub_2C43E0_002c43e0(p3fes::EEContext&);
void fn_sub_2C4420_002c4420(p3fes::EEContext&);
void fn_sub_2C4460_002c4460(p3fes::EEContext&);
void fn_sub_2C44A0_002c44a0(p3fes::EEContext&);
void fn_sub_2C44E0_002c44e0(p3fes::EEContext&);
void fn_sub_2C4520_002c4520(p3fes::EEContext&);
void fn_sub_2C4560_002c4560(p3fes::EEContext&);
void fn_sub_2C45A0_002c45a0(p3fes::EEContext&);
void fn_sub_2C45E0_002c45e0(p3fes::EEContext&);
void fn_sub_2C4620_002c4620(p3fes::EEContext&);
void fn_sub_2C4660_002c4660(p3fes::EEContext&);
void fn_sub_2C46A0_002c46a0(p3fes::EEContext&);
void fn_sub_2C46E0_002c46e0(p3fes::EEContext&);
void fn_sub_2C4720_002c4720(p3fes::EEContext&);
void fn_sub_2C4760_002c4760(p3fes::EEContext&);
void fn_sub_2C4820_002c4820(p3fes::EEContext&);
void fn_sub_2C4860_002c4860(p3fes::EEContext&);
void fn_sub_2C4A90_002c4a90(p3fes::EEContext&);
void fn_sub_2C65D0_002c65d0(p3fes::EEContext&);
void fn_sub_2C6A00_002c6a00(p3fes::EEContext&);
void fn_sub_2C6F50_002c6f50(p3fes::EEContext&);
void fn_sub_2C74E0_002c74e0(p3fes::EEContext&);
void fn_sub_2D08E0_002d08e0(p3fes::EEContext&);
void fn_sub_2D1660_002d1660(p3fes::EEContext&);
void fn_sub_2D1C20_002d1c20(p3fes::EEContext&);
void fn_sub_2D1D00_002d1d00(p3fes::EEContext&);
void fn_sub_301870_00301870(p3fes::EEContext&);
void fn_sub_301CA0_00301ca0(p3fes::EEContext&);
void fn_sub_308860_00308860(p3fes::EEContext&);
void fn_sub_30BC20_0030bc20(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b7;  // this slice's additions (battle7.h)

// 0x002C08B0 sub_2C08B0 -- 16 bytes; leaf frame (no stack)
// [btlAIRecCopyUid] Copies the chosen candidate's uid (u64 +48) of one AI target record into another.
// Arguments: a0 the destination record (btlAction + 136), a1 the source record.
void sub_2C08B0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002c08b0
    enter(ctx, 4);  // entry check point + this block's cycles
    ld(v1, a1, airec::kUid);
    sd(v1, a0, airec::kUid);
}

// 0x002C08C0 sub_2C08C0 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIRecFindAction] The live combatant (active, placed, not dead -- or without a DatUnit) whose uid equals the AI
// record's chosen uid (+48), walking gBtl's action list; 0 when none.
// Arguments: a0 an AI target record.
void sub_2C08C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c08c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c0944
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c08e4
        charge(ctx, 4);
        lhu(v1, s0, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c08f4
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                goto L_002c0940;
            }
            // 0x002c0900
            charge(ctx, 4);
            lw(v0, s0, act::kUnit);
            lw(a0, v0, unit::kDat);
            if (a0 != 0) {
                // 0x002c0910
                charge(ctx, 5);
                a1 = 0;
                jal(ctx, 0x2C0914u, gen::fn_datCalcIsDead_0030b5a0);
                if (v0 != 0) {
                    goto L_002c0940;
                }
                goto L_002c0924;
            }
        L_002c0924:
            charge(ctx, 4);
            ld(v1, s0, act::kUid);
            ld(v0, s1, airec::kUid);
            if (v1 != v0) {
                goto L_002c0940;
            }
            goto L_002c0934_6;
        }
    L_002c0940:
        charge(ctx, 1);
        lw(s0, s0, act::kNext);
    }
    // 0x002c094c
    charge(ctx, 1);
    v0 = 0;
    // 0x002c0950 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_002c0934_6:
    charge(ctx, 3);
    v0 = s0;
    // 0x002c0950 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C0A50 sub_2C0A50 -- 104 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Points the AI target record of the action of uid a1's unit at the action of uid a1: finds the unit (sub_289030),
// its action (sub_29A1D0) and copies the action's uid into the record +184 of the first action.
// Arguments: a0 (unused by the body beyond the call), a1 u16 a unit uid.
void sub_2C0A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c0a50
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x2C0A64u, gen::fn_sub_29A1D0_0029a1d0);
    s0 = v0;
    a0 = s1 & 0xFFFF;
    jal(ctx, 0x2C0A74u, gen::fn_sub_289030_00289030);
    a0 = v0;
    if (a0 != 0) {
        // 0x002c0a88
        charge(ctx, 4);
        jal(ctx, 0x2C0A88u, gen::fn_sub_29A1D0_0029a1d0);
        if (v0 != 0) {
            // 0x002c0a98
            charge(ctx, 2);
            ld(v1, v0, 0);
            sd(v1, s0, 184);
        }
    }
    // 0x002c0aa0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C1360 sub_2C1360 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPredHpAbove] AI predicate: the action's unit has at least a1 percent of its max HP (max HP * a1 <= 100 * HP)
// -- the predicate of ENHP_O.
// Arguments: a0 a btlAction, a1 a percentage.
void sub_2C1360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1360
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    lhu(s1, a0, dat::kHp);
    jal(ctx, 0x2C1380u, gen::fn_datCalcGetMaxHp_002ffdf0);
    a0 = v0 & 0xFFFF;
    v0 = sll(s1, 2);
    v1 = addu(v0, s1);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 2);
    mult(v0, a0, s0);
    v0 = sltu(v1, v0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C1440 sub_2C1440 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRHP] AI condition 3 FRHP: whether any living combatant of the acting unit's side satisfies: its HP is
// at most param percent of its max HP (100 * HP <= max HP * param) -- btlAIAnyUnit (sub_2C1080) with the status mask
// 0x80000, filters 0 and the predicate sub_2C12F0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C1440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1440
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 4848);  // &sub_2C12F0
    jal(ctx, 0x2C146Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1490 sub_2C1490 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENHP] AI condition 4 ENHP: whether any living combatant of the other side satisfies: its HP is at most
// param percent of its max HP (100 * HP <= max HP * param) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
// filters 0 and the predicate sub_2C12F0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C1490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1490
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c14b4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c14a8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c14b8
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 4848);  // &sub_2C12F0
    jal(ctx, 0x2C14D8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C14F0 sub_2C14F0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENHP_O] AI condition 5 ENHP_O: whether any living combatant of the other side satisfies: its HP is at
// least param percent of its max HP (max HP * param <= 100 * HP) -- btlAIAnyUnit (sub_2C1080) with the status mask
// 0x80000, filters 0 and the predicate sub_2C1360.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C14F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c14f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c1514
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c1508
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c1518
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 4960);  // &sub_2C1360
    jal(ctx, 0x2C1538u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1550 sub_2C1550 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAICond_MYLV_O] AI condition 6 MYLV_O: the acting unit's level (datCalcGetLevel) is at least the parameter.
// Arguments: a0 the acting btlAction, a1 the level.
void sub_2C1550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1550
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C1568u, gen::fn_datCalcGetLevel_002ffcc0);
    v0 = v0 & 0xFF;
    v0 = sltu(v0, s0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C15E0 sub_2C15E0 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAICond_ENLV_O] AI condition 8 ENLV_O: the mean level of the other side's living units (btlGetMeanLevel, status
// mask 0x80000) is at least the parameter.
// Arguments: a0 the acting btlAction, a1 the level.
void sub_2C15E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c15e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c160c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c1600
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c1610
    charge(ctx, 15);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a0 = v0 & 0xFFFF;
    a1 = 0x80000;
    jal(ctx, 0x2C1624u, gen::fn_btlGetMeanLevel_002d4cf0);
    v0 = v0 & 0xFFFF;
    v0 = sltu(v0, s0);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C1740 sub_2C1740 -- 112 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRBAD] AI condition 12 FRBAD: whether a combatant of the acting unit's side has the bad status param --
// sub_2C1080 with the predicate sub_2C1710 and the status mask 0x80000 (living units only), or 0 when the param
// itself asks for the dead status 0x80000.
// Arguments: a0 the acting btlAction, a1 the bad status; returns 1 / 0.
void sub_2C1740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1740
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    v0 = a1 & a3;
    if (v0 == 0) {
        // 0x002c178c
        charge(ctx, 5);
        t0 = 0;
        t1 = 0x2C0000;
        t1 = addiu(t1, 5904);  // &sub_2C1710
        jal(ctx, 0x2C1798u, gen::fn_sub_2C1080_002c1080);
    } else {
        // 0x002c176c
        charge(ctx, 8);
        a3 = 0;
        t0 = 0;
        t1 = 0x2C0000;
        t1 = addiu(t1, 5904);  // &sub_2C1710
        jal(ctx, 0x2C177Cu, gen::fn_sub_2C1080_002c1080);
    }
    // 0x002c17a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1850 sub_2C1850 -- 264 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_ENBAD_ALL] AI condition 14 ENBAD_ALL: every living combatant of the other side has the bad status param
// (the walk stops at the first one without it; true when it reaches the end).
// Arguments: a0 the acting btlAction, a1 the bad status mask.
void sub_2C1850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1850
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c1888
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c187c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c188c
    charge(ctx, 8);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    s1 = v0 & 0xFFFF;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s2, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c1918
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c18ac
        charge(ctx, 4);
        lhu(v1, s2, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c18bc
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c18c8
                charge(ctx, 7);
                lw(s0, s2, act::kUnit);
                lbu(v1, s0, unit::kSide);
                v0 = 1;
                v0 = sllv(v0, v1);
                v0 = s1 & v0;
                if (v0 != 0) {
                    // 0x002c18e4
                    charge(ctx, 6);
                    lw(a0, s0, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x2C18ECu, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x002c18fc
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = s3;
                        jal(ctx, 0x2C1904u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            break;
                        }
                    }
                }
            }
        }
        charge(ctx, 1);
        lw(s2, s2, act::kNext);
    }
    // 0x002c1920
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x002c1934
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c1928
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c1938 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C1960 sub_2C1960 -- 204 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_FRID] AI condition 15 FRID: an ally (same side, not the acting action, not dead) has the unit id param.
// Arguments: a0 the acting btlAction, a1 a unit id.
void sub_2C1960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1960
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c1a00
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c1990
        charge(ctx, 2);
        if (s3 != s1) {
            // 0x002c1998
            charge(ctx, 4);
            lhu(v1, s1, act::kFlags2);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x002c19a8
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 != 0) {
                    // 0x002c19b4
                    charge(ctx, 6);
                    lw(s0, s1, act::kUnit);
                    lw(v0, s3, act::kUnit);
                    lbu(v1, v0, unit::kSide);
                    lbu(v0, s0, unit::kSide);
                    if (v1 == v0) {
                        // 0x002c19cc
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = 0x80000;
                        jal(ctx, 0x2C19D4u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002c19e4
                            charge(ctx, 3);
                            lhu(v0, s0, unit::kId);
                            if (v0 == s2) {
                                goto L_002c19f0_7;
                            }
                        }
                    }
                }
            }
        }
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002c1a08
    charge(ctx, 1);
    v0 = 0;
    // 0x002c1a0c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_002c19f0_7:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c1a0c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C1A30 sub_2C1A30 -- 220 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_ENID] AI condition 16 ENID: a living unit of the other side has the unit id param.
// Arguments: a0 the acting btlAction, a1 a unit id.
void sub_2C1A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1a30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c1a68
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c1a5c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c1a6c
    charge(ctx, 5);
    s0 = v0 & 0xFFFF;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c1ae0
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c1a80
        charge(ctx, 4);
        lhu(v1, s1, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c1a90
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c1a9c
                charge(ctx, 4);
                lw(s3, s1, act::kUnit);
                lbu(v0, s3, unit::kSide);
                if (v0 == s0) {
                    // 0x002c1aac
                    charge(ctx, 6);
                    lw(a0, s3, unit::kDat);
                    a1 = 0x80000;
                    jal(ctx, 0x2C1AB4u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        // 0x002c1ac4
                        charge(ctx, 3);
                        lhu(v0, s3, unit::kId);
                        if (v0 == s2) {
                            goto L_002c1ad0_9;
                        }
                    }
                }
            }
        }
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002c1ae8
    charge(ctx, 1);
    v0 = 0;
    // 0x002c1aec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_002c1ad0_9:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c1aec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C1B10 sub_2C1B10 -- 216 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_FRHOJO] AI condition 17 FRHOJO: a living ally (not the acting action) has the support effect param
// (sub_301CA0).
// Arguments: a0 the acting btlAction, a1 the support effect.
void sub_2C1B10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1b10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c1bbc
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c1b40
        charge(ctx, 2);
        if (s3 != s1) {
            // 0x002c1b48
            charge(ctx, 4);
            lhu(v1, s1, act::kFlags2);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x002c1b58
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 != 0) {
                    // 0x002c1b64
                    charge(ctx, 6);
                    lw(s0, s1, act::kUnit);
                    lw(v0, s3, act::kUnit);
                    lbu(v1, v0, unit::kSide);
                    lbu(v0, s0, unit::kSide);
                    if (v1 == v0) {
                        // 0x002c1b7c
                        charge(ctx, 6);
                        lw(a0, s0, unit::kDat);
                        a1 = 0x80000;
                        jal(ctx, 0x2C1B84u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002c1b94
                            charge(ctx, 6);
                            lw(a0, s0, unit::kDat);
                            a1 = s2;
                            jal(ctx, 0x2C1B9Cu, gen::fn_sub_301CA0_00301ca0);
                            if (v0 != 0) {
                                goto L_002c1bac_7;
                            }
                        }
                    }
                }
            }
        }
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002c1bc4
    charge(ctx, 1);
    v0 = 0;
    // 0x002c1bc8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_002c1bac_7:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c1bc8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C1BF0 sub_2C1BF0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_ENHOJO] AI condition 18 ENHOJO: a living unit of the other side has the support effect param
// (sub_301CA0).
// Arguments: a0 the acting btlAction, a1 the support effect.
void sub_2C1BF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1bf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c1c28
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c1c1c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c1c2c
    charge(ctx, 5);
    s0 = v0 & 0xFFFF;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c1cac
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c1c40
        charge(ctx, 4);
        lhu(v1, s1, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c1c50
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c1c5c
                charge(ctx, 4);
                lw(s3, s1, act::kUnit);
                lbu(v0, s3, unit::kSide);
                if (v0 == s0) {
                    // 0x002c1c6c
                    charge(ctx, 6);
                    lw(a0, s3, unit::kDat);
                    a1 = 0x80000;
                    jal(ctx, 0x2C1C74u, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 == 0) {
                        // 0x002c1c84
                        charge(ctx, 6);
                        lw(a0, s3, unit::kDat);
                        a1 = s2;
                        jal(ctx, 0x2C1C8Cu, gen::fn_sub_301CA0_00301ca0);
                        if (v0 != 0) {
                            goto L_002c1c9c_9;
                        }
                    }
                }
            }
        }
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002c1cb4
    charge(ctx, 1);
    v0 = 0;
    // 0x002c1cb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_002c1c9c_9:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c1cb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002C1D80 sub_2C1D80 -- 12 bytes; leaf frame (no stack)
// [btlAICond_SUMMON] AI condition 20 SUMMON: always false (returns 0).
// Arguments: a0 the acting btlAction.
void sub_2C1D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x002c1d80
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x002C1E50 sub_2C1E50 -- 60 bytes; frame 0x10: ra sp+0x0
// [btlAICond_MYKYUSYU] AI predicate (condition 23 MYKYUSYU): the action's unit drains the element a1 (affinity bit
// 0x4000000).
// Arguments: a0 a btlAction, a1 an element.
void sub_2C1E50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1e50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    a1 = dsll32(a1, 16);
    a1 = dsra32(a1, 16);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C1E68u, gen::fn_datCalcGetAffinity_00306e80);
    v1 = 0x4000000;
    v0 = v0 & v1;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1E90 sub_2C1E90 -- 60 bytes; frame 0x10: ra sp+0x0
// [btlAICond_MYMUKOU] AI predicate (condition 24 MYMUKOU): the action's unit nullifies the element a1 (affinity bit
// 0x1000000).
// Arguments: a0 a btlAction, a1 an element.
void sub_2C1E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1e90
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    a1 = dsll32(a1, 16);
    a1 = dsra32(a1, 16);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C1EA8u, gen::fn_datCalcGetAffinity_00306e80);
    v1 = 0x1000000;
    v0 = v0 & v1;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1F10 sub_2C1F10 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRHANSYA] AI condition 26 FRHANSYA: whether any living combatant of the acting unit's side satisfies: it
// repels the element param (affinity bit 0x2000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
// filters 0 and the predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C1F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1f10
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C1F3Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C1FC0 sub_2C1FC0 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRKYUSYU] AI condition 28 FRKYUSYU: whether any living combatant of the acting unit's side satisfies: it
// drains the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
// filters 0 and the predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C1FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c1fc0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C1FECu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2010 sub_2C2010 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENKYUSYU] AI condition 29 ENKYUSYU: whether any living combatant of the other side satisfies: it drains
// the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
// the predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2010
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2034
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2028
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2038
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C2058u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2070 sub_2C2070 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRMUKOU] AI condition 30 FRMUKOU: whether any living combatant of the acting unit's side satisfies: it
// nullifies the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
// filters 0 and the predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2070
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C209Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C20C0 sub_2C20C0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENMUKOU] AI condition 31 ENMUKOU: whether any living combatant of the other side satisfies: it nullifies
// the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
// the predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C20C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c20c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c20e4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c20d8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c20e8
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C2108u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2120 sub_2C2120 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRWEAK] AI condition 32 FRWEAK: whether any living combatant of the acting unit's side satisfies: it is
// weak to the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
// filters 0 and the predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2120
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C214Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2170 sub_2C2170 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENWEAK] AI condition 33 ENWEAK: whether any living combatant of the other side satisfies: it is weak to
// the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
// the predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2170
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2194
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2188
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2198
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C21B8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C21D0 sub_2C21D0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAICond_MYUSEATTR] AI predicate (condition 34 MYUSEATTR): the element of the action's last skill (+126,
// datCalcGetSkillElement) is a1.
// Arguments: a0 a btlAction, a1 an element.
void sub_2C21D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c21d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = a0;
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    lhu(a1, v1, act4::kLastCmdId);
    jal(ctx, 0x2C21F0u, gen::fn_datCalcGetSkillElement_003082f0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    v0 = v0 ^ s0;
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C2220 sub_2C2220 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRUSEATTR] AI condition 35 FRUSEATTR: whether any living combatant of the acting unit's side satisfies:
// the element of its last skill (+126) is param -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0
// and the predicate sub_2C21D0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2220
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 8656);  // &sub_2C21D0
    jal(ctx, 0x2C224Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2270 sub_2C2270 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENUSEATTR] AI condition 36 ENUSEATTR: whether any living combatant of the other side satisfies: the
// element of its last skill (+126) is param -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0 and
// the predicate sub_2C21D0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2270
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2294
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2288
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2298
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 8656);  // &sub_2C21D0
    jal(ctx, 0x2C22B8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2310 sub_2C2310 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRUSESKIL] AI condition 38 FRUSESKIL: whether any living combatant of the acting unit's side satisfies:
// its last command was an attack / skill (+124 kind 1 / 2) with the id param -- btlAIAnyUnit (sub_2C1080) with the
// status mask 0x80000, filters 0 and the predicate sub_2C22D0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2310
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 8912);  // &sub_2C22D0
    jal(ctx, 0x2C233Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2360 sub_2C2360 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENUSESKIL] AI condition 39 ENUSESKIL: whether any living combatant of the other side satisfies: its last
// command was an attack / skill (+124 kind 1 / 2) with the id param -- btlAIAnyUnit (sub_2C1080) with the status mask
// 0x80000, filters 0 and the predicate sub_2C22D0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2360
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2384
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2378
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2388
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 8912);  // &sub_2C22D0
    jal(ctx, 0x2C23A8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C23C0 sub_2C23C0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_MYGROUP] AI predicate (condition 40 MYGROUP): the action's last skill (+126) targets a group or all
// (sub_2BFF60 returns 1 or 2).
// Arguments: a0 a btlAction.
void sub_2C23C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c23c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;
    lhu(a2, a0, act4::kLastCmdId);
    a3 = 0;
    jal(ctx, 0x2C23D4u, gen::fn_sub_2BFF60_002bff60);
    v1 = v0 & 0xFFFF;
    v0 = 2;
    if (v1 != v0) {
        // 0x002c23ec
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x002c23f8
            charge(ctx, 2);
            // 0x002c240c
            charge(ctx, 1);
            v0 = 0;
            // 0x002c2410 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
    }
    charge(ctx, 3);
    v0 = 1;
    // 0x002c2410 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2420 sub_2C2420 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRGROUP] AI condition 41 FRGROUP: whether any living combatant of the acting unit's side satisfies: its
// last skill targets a group (sub_2BFF60 kind 1 or 2) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000,
// filters 0 and the predicate sub_2C23C0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2420
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 9152);  // &sub_2C23C0
    jal(ctx, 0x2C244Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2470 sub_2C2470 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENGROUP] AI condition 42 ENGROUP: whether any living combatant of the other side satisfies: its last
// skill targets a group (sub_2BFF60 kind 1 or 2) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters 0
// and the predicate sub_2C23C0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2470
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2494
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2488
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2498
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 9152);  // &sub_2C23C0
    jal(ctx, 0x2C24B8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C24F0 sub_2C24F0 -- 20 bytes; leaf frame (no stack)
// [btlAICond_TURN_O] AI condition 44 TURN_O: the acting unit has taken at least param turns (+32).
// Arguments: a0 the acting btlAction, a1 the turn count.
void sub_2C24F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002c24f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, act::kTurnsTaken);
    v0 = sltu(v0, a1);
    v0 = v0 ^ 0x1;
}

// 0x002C2510 sub_2C2510 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_MYHREC] AI condition 45 MYHREC: the acting unit knows a usable recovery skill: any skill of its list
// (below 0x1D0) for which sub_308860 holds.
// Arguments: a0 the acting btlAction.
void sub_2C2510(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2510
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, act::kUnit);
    lw(a0, s1, unit::kDat);
    jal(ctx, 0x2C252Cu, gen::fn_datCalcGetSkillSlotCount_00308ba0);
    s0 = v0 & 0xFFFF;
    lw(a0, s1, unit::kDat);
    jal(ctx, 0x2C253Cu, gen::fn_datCalcGetSkillList_00308bb0);
    s1 = v0;
    s2 = 0;
    s0 = s0 & 0xFFFF;
    for (;;) {
        // 0x002c25a0
        charge(ctx, 4);
        v0 = s2 & 0xFFFF;
        v0 = slt(v0, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c2558
        charge(ctx, 6);
        v0 = s2 & 0xFFFF;
        v0 = sll(v0, 1);
        v0 = addu(s1, v0);
        lhu(a0, v0, 0);
        if (a0 != 0) {
            // 0x002c2570
            charge(ctx, 3);
            at = slti(a0, 464);
            if (at != 0) {
                // 0x002c257c
                charge(ctx, 4);
                jal(ctx, 0x2C257Cu, gen::fn_sub_308860_00308860);
                if (v0 != 0) {
                    goto L_002c258c_4;
                }
            }
        }
        charge(ctx, 2);
        v0 = addiu(s2, 1);
        s2 = v0 & 0xFFFF;
    }
    // 0x002c25b0
    charge(ctx, 1);
    v0 = 0;
    // 0x002c25b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_002c258c_4:
    charge(ctx, 3);
    v0 = 1;
    // 0x002c25b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002C25D0 sub_2C25D0 -- 16 bytes; leaf frame (no stack)
// [btlAICond_MORE] AI condition 46 MORE: the action has a "one more" this turn (+40 nonzero).
// Arguments: a0 the acting btlAction.
void sub_2C25D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002c25d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lbu(v0, a0, act::kOneMore);
    v0 = slt(0, v0);
}

// 0x002C25E0 sub_2C25E0 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRHANSYA_ST] AI condition 47 FRHANSYA_ST: whether any living, standing (not down) combatant of the
// acting unit's side satisfies: it repels the element param (affinity bit 0x2000000) -- btlAIAnyUnit (sub_2C1080)
// with the status mask 0x180000, filters 0 and the predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C25E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c25e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C260Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2630 sub_2C2630 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENHANSYA_ST] AI condition 48 ENHANSYA_ST: whether any living, standing (not down) combatant of the other
// side satisfies: it repels the element param (affinity bit 0x2000000) -- btlAIAnyUnit (sub_2C1080) with the status
// mask 0x180000, filters 0 and the predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2630
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2654
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2648
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2658
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C2678u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2690 sub_2C2690 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRKYUSYU_ST] AI condition 49 FRKYUSYU_ST: whether any living, standing (not down) combatant of the
// acting unit's side satisfies: it drains the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080)
// with the status mask 0x180000, filters 0 and the predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2690
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C26BCu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C26E0 sub_2C26E0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENKYUSYU_ST] AI condition 50 ENKYUSYU_ST: whether any living, standing (not down) combatant of the other
// side satisfies: it drains the element param (affinity bit 0x4000000) -- btlAIAnyUnit (sub_2C1080) with the status
// mask 0x180000, filters 0 and the predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C26E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c26e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2704
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c26f8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2708
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C2728u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2740 sub_2C2740 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRMUKOU_ST] AI condition 51 FRMUKOU_ST: whether any living, standing (not down) combatant of the acting
// unit's side satisfies: it nullifies the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with
// the status mask 0x180000, filters 0 and the predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2740
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C276Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2790 sub_2C2790 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENMUKOU_ST] AI condition 52 ENMUKOU_ST: whether any living, standing (not down) combatant of the other
// side satisfies: it nullifies the element param (affinity bit 0x1000000) -- btlAIAnyUnit (sub_2C1080) with the
// status mask 0x180000, filters 0 and the predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2790
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c27b4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c27a8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c27b8
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C27D8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C27F0 sub_2C27F0 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlAICond_FRWEAK_ST] AI condition 53 FRWEAK_ST: whether any living, standing (not down) combatant of the acting
// unit's side satisfies: it is weak to the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with
// the status mask 0x180000, filters 0 and the predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C27F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c27f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C281Cu, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2840 sub_2C2840 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENWEAK_ST] AI condition 54 ENWEAK_ST: whether any living, standing (not down) combatant of the other
// side satisfies: it is weak to the element param (affinity bit 0x8000000) -- btlAIAnyUnit (sub_2C1080) with the
// status mask 0x180000, filters 0 and the predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2840
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2864
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2858
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2868
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C2888u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C28A0 sub_2C28A0 -- 24 bytes; leaf frame (no stack)
// [btlAICond_MYID] AI predicate (condition 55 MYID): the action's unit id is a1.
// Arguments: a0 a btlAction, a1 a unit id.
void sub_2C28A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x002c28a0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, act::kUnit);
    lhu(v0, v0, unit::kId);
    v0 = v0 ^ a1;
    v0 = sltiu(v0, 1);
}

// 0x002C28C0 sub_2C28C0 -- 284 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_FRALLHP] AI condition 56 FRALLHP: the living units of the acting unit's side have, summed, at most param
// percent of their summed max HP (sum max HP * param >= 100 * sum HP).
// Arguments: a0 the acting btlAction, a1 a percentage.
void sub_2C28C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c28c0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v1, v0, unit::kSide);
    v0 = 1;
    v0 = sllv(v0, v1);
    s2 = v0 & 0xFFFF;
    s4 = 0;
    s3 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s5, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c298c
        charge(ctx, 2);
        if (s5 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c2910
        charge(ctx, 4);
        lhu(v1, s5, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c2920
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c292c
                charge(ctx, 7);
                lw(s1, s5, act::kUnit);
                lbu(v1, s1, unit::kSide);
                v0 = 1;
                v0 = sllv(v0, v1);
                v0 = s2 & v0;
                if (v0 != 0) {
                    // 0x002c2948
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x2C2950u, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x002c2960
                        charge(ctx, 10);
                        lw(a0, s1, unit::kDat);
                        jal(ctx, 0x2C2964u, gen::fn_datCalcGetHp_002ffd70);
                        v0 = v0 & 0xFFFF;
                        s4 = addu(s4, v0);
                        lw(a0, s1, unit::kDat);
                        jal(ctx, 0x2C2978u, gen::fn_datCalcGetMaxHp_002ffdf0);
                        v0 = v0 & 0xFFFF;
                        s3 = addu(s3, v0);
                    }
                }
            }
        }
        // 0x002c2988
        charge(ctx, 1);
        lw(s5, s5, act::kNext);
    }
    // 0x002c2994
    charge(ctx, 18);
    v0 = sll(s4, 2);
    v1 = addu(v0, s4);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 2);
    mult(v0, s3, s0);
    v0 = sltu(v0, v1);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002C29E0 sub_2C29E0 -- 312 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAICond_ENALLHP] AI condition 57 ENALLHP: as FRALLHP over the other side.
// Arguments: a0 the acting btlAction, a1 a percentage.
void sub_2C29E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c29e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2a20
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2a14
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2a24
    charge(ctx, 10);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    s2 = v0 & 0xFFFF;
    s4 = 0;
    s3 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s5, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c2ac8
        charge(ctx, 2);
        if (s5 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c2a4c
        charge(ctx, 4);
        lhu(v1, s5, act::kFlags2);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x002c2a5c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002c2a68
                charge(ctx, 7);
                lw(s1, s5, act::kUnit);
                lbu(v1, s1, unit::kSide);
                v0 = 1;
                v0 = sllv(v0, v1);
                v0 = s2 & v0;
                if (v0 != 0) {
                    // 0x002c2a84
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x2C2A8Cu, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x002c2a9c
                        charge(ctx, 10);
                        lw(a0, s1, unit::kDat);
                        jal(ctx, 0x2C2AA0u, gen::fn_datCalcGetHp_002ffd70);
                        v0 = v0 & 0xFFFF;
                        s4 = addu(s4, v0);
                        lw(a0, s1, unit::kDat);
                        jal(ctx, 0x2C2AB4u, gen::fn_datCalcGetMaxHp_002ffdf0);
                        v0 = v0 & 0xFFFF;
                        s3 = addu(s3, v0);
                    }
                }
            }
        }
        // 0x002c2ac4
        charge(ctx, 1);
        lw(s5, s5, act::kNext);
    }
    // 0x002c2ad0
    charge(ctx, 18);
    v0 = sll(s4, 2);
    v1 = addu(v0, s4);
    v0 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 2);
    mult(v0, s3, s0);
    v0 = sltu(v0, v1);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002C2C40 sub_2C2C40 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENWEAK_ST_PAI] AI condition 60 ENWEAK_ST_PAI: whether any living, standing (not down) combatant of the
// other side satisfies: it is weak to the element param (affinity bit 0x8000000) (not shielded against the element;
// an enemy whose affinities the party has not analysed is skipped) -- btlAIAnyUnit (sub_2C1080) with the status mask
// 0x180000, filters 6 and the predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2C40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2c40
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2c64
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2c58
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2c68
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 6;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C2C88u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C2CA0 sub_2C2CA0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENWEAK_DW_PAI] AI condition 61 ENWEAK_DW_PAI: whether any living combatant of the other side satisfies:
// it is weak to the element param (affinity bit 0x8000000) (downed units only; not shielded against the element; an
// enemy whose affinities the party has not analysed is skipped) -- btlAIAnyUnit (sub_2C1080) with the status mask
// 0x80000, filters 7 and the predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C2CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c2ca0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c2cc4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c2cb8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c2cc8
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 7;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C2CE8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3150 sub_2C3150 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENNOMAL] AI condition 64 ENNOMAL: whether any living combatant of the other side satisfies: the element
// param may be used on it, the shields counted (sub_2C2ED0) (not shielded against the element; an enemy whose
// affinities are not analysed counts as a match) -- btlAIAnyUnit (sub_2C1080) with the status mask 0x80000, filters
// 10 and the predicate sub_2C30F0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C3150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3150
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c3174
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c3168
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c3178
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 10;
    t1 = 0x2C0000;
    t1 = addiu(t1, 12528);  // &sub_2C30F0
    jal(ctx, 0x2C3198u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C31B0 sub_2C31B0 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENNOMAL_ST] AI condition 65 ENNOMAL_ST: whether any living, standing (not down) combatant of the other
// side satisfies: the element param may be used on it, the shields counted (sub_2C2ED0) (not shielded against the
// element; an enemy whose affinities are not analysed counts as a match) -- btlAIAnyUnit (sub_2C1080) with the status
// mask 0x180000, filters 10 and the predicate sub_2C30F0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C31B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c31b0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c31d4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c31c8
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c31d8
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x180000;
    t0 = 10;
    t1 = 0x2C0000;
    t1 = addiu(t1, 12528);  // &sub_2C30F0
    jal(ctx, 0x2C31F8u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3210 sub_2C3210 -- 96 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ENNOMAL_DW] AI condition 66 ENNOMAL_DW: whether any living combatant of the other side satisfies: the
// element param may be used on it, the shields counted (sub_2C2ED0) (downed units only; not shielded against the
// element; an enemy whose affinities are not analysed counts as a match) -- btlAIAnyUnit (sub_2C1080) with the status
// mask 0x80000, filters 11 and the predicate sub_2C30F0.
// Arguments: a0 the acting btlAction, a1 the condition parameter; returns 1 / 0.
void sub_2C3210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3210
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 != 0) {
        // 0x002c3234
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c3228
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002c3238
    charge(ctx, 14);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    v0 = sllv(v0, v1);
    a2 = v0 & 0xFFFF;
    a3 = 0x80000;
    t0 = 11;
    t1 = 0x2C0000;
    t1 = addiu(t1, 12528);  // &sub_2C30F0
    jal(ctx, 0x2C3258u, gen::fn_sub_2C1080_002c1080);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3270 sub_2C3270 -- 72 bytes; frame 0x10: ra sp+0x0
// [btlAICond_ANALYZE] AI condition 67 ANALYZE: the acting unit is an enemy whose affinities the party has analysed
// (sub_17B260 on its id).
// Arguments: a0 the acting btlAction.
void sub_2C3270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3270
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, act::kUnit);
    lbu(v1, a0, unit::kSide);
    v0 = 1;
    if (v1 == v0) {
        // 0x002c3298
        charge(ctx, 4);
        lhu(a0, a0, unit::kId);
        jal(ctx, 0x2C329Cu, gen::fn_sub_17B260_0017b260);
        v0 = sltu(0, v0);
    } else {
        // 0x002c328c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002c32a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C32C0 sub_2C32C0 -- 32 bytes; leaf frame (no stack)
// [btlAICond_DOWN] AI condition 68 DOWN: the acting unit's DatUnit flag 0x10 is clear.
// Arguments: a0 the acting btlAction.
void sub_2C32C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002c32c0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, a0, act::kUnit);
    lw(v0, v0, unit::kDat);
    lhu(v0, v0, dat::kFlags);
    v0 = v0 & 0x10;
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
}

// 0x002C32E0 sub_2C32E0 -- 32 bytes; leaf frame (no stack)
// [btlAICond_SLIP] AI condition 69 SLIP: the acting unit's DatUnit flag 0x20 is clear.
// Arguments: a0 the acting btlAction.
void sub_2C32E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002c32e0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, a0, act::kUnit);
    lw(v0, v0, unit::kDat);
    lhu(v0, v0, dat::kFlags);
    v0 = v0 & 0x20;
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
}

// 0x002C3BE0 sub_2C3BE0 -- 244 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAITarget_HPMIN] AI target selector 1 HPMIN: an all-target skill takes the whole candidate list; otherwise the
// candidate with the lowest HP (DatUnit +8).
// Arguments: a0 the acting btlAction; returns 1.
void sub_2C3BE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3be0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = addiu(s0, 136);
    lhu(a2, a0, act::kCmdSkill);
    a3 = 0;
    jal(ctx, 0x2C3BFCu, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
        // 0x002c3c5c
        charge(ctx, 7);
        a3 = 0;
        v0 = 0xFFF0000;
        a1 = v0 | 0xFFFF;
        a2 = 0;
        lhu(a0, s0, act::kTargetRecCount);
        for (;;) {
            // 0x002c3ca8
            charge(ctx, 3);
            v0 = sltu(a2, a0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c3c78
            charge(ctx, 9);
            v0 = sll(a2, 2);
            v0 = addu(s0, v0);
            lw(v1, v0, 136);
            lw(v0, v1, 48);
            lw(v0, v0, 2604);
            lhu(v0, v0, 8);
            at = sltu(v0, a1);
            if (at != 0) {
                // 0x002c3c9c
                charge(ctx, 2);
                a3 = v1;
                a1 = v0;
            }
            // 0x002c3ca4
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x002c3cb4
        charge(ctx, 3);
        sw(a3, s0, act::kTargets);
        v0 = 1;
        sh(v0, s0, act::kTargetCount);
    } else {
        // 0x002c3c10
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c3c38
            charge(ctx, 5);
            lhu(v1, s0, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c3c1c
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s0, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c3c4c
        charge(ctx, 4);
        sh(v1, s0, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c3cc0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C3CE0 sub_2C3CE0 -- 300 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAITarget_LVMIN] AI target selector 2 LVMIN: an all-target skill takes the whole list; otherwise the candidate
// with the lowest level (datCalcGetLevel).
// Arguments: a0 the acting btlAction; returns 1.
void sub_2C3CE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3ce0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    a1 = addiu(s4, 136);
    lhu(a2, a0, act::kCmdSkill);
    a3 = 0;
    jal(ctx, 0x2C3D0Cu, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
        // 0x002c3d6c
        charge(ctx, 6);
        s2 = 0;
        v0 = 0xFFFF;
        s0 = v0 & 0xFFFF;
        s1 = 0;
        for (;;) {
            // 0x002c3dc8
            charge(ctx, 5);
            v1 = s1 & 0xFFFF;
            lhu(v0, s4, act::kTargetRecCount);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c3d84
            charge(ctx, 13);
            v0 = s1 & 0xFFFF;
            v0 = sll(v0, 2);
            v0 = addu(s4, v0);
            lw(s3, v0, 136);
            lw(v0, s3, 48);
            lw(a0, v0, 2604);
            jal(ctx, 0x2C3D9Cu, gen::fn_datCalcGetLevel_002ffcc0);
            v1 = v0 & 0xFF;
            v0 = s0 & 0xFFFF;
            at = slt(v1, v0);
            if (at != 0) {
                // 0x002c3db8
                charge(ctx, 2);
                s2 = s3;
                s0 = v1;
            }
            // 0x002c3dc0
            charge(ctx, 2);
            v0 = addiu(s1, 1);
            s1 = v0 & 0xFFFF;
        }
        // 0x002c3ddc
        charge(ctx, 3);
        sw(s2, s4, act::kTargets);
        v0 = 1;
        sh(v0, s4, act::kTargetCount);
    } else {
        // 0x002c3d20
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c3d48
            charge(ctx, 5);
            lhu(v1, s4, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c3d2c
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s4, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c3d5c
        charge(ctx, 4);
        sh(v1, s4, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c3de8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002C3E10 sub_2C3E10 -- 12 bytes; leaf frame (no stack)
// [btlAITarget_MPMAX] AI target selector 3 MPMAX: never selects (returns 0: the caller falls back to row 0).
// Arguments: a0 the acting btlAction.
void sub_2C3E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x002c3e10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x002C3E20 sub_2C3E20 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_BAD] AI target selector 4 BAD: from the candidates of the action's skill, the units -- those for which
// it holds: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row 0,
// sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
// sub_2C1710.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C3E20(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3e20
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 5904);  // &sub_2C1710
    jal(ctx, 0x2C3E3Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3E60 sub_2C3E60 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTBAD] AI target selector 5 NOTBAD: from the candidates of the action's skill, the units -- those for
// which it does NOT hold: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row
// 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate
// sub_2C1710.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C3E60(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3e60
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 5904);  // &sub_2C1710
    jal(ctx, 0x2C3E7Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3EA0 sub_2C3EA0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_ID] AI target selector 6 ID: from the candidates of the action's skill, the units -- those for which
// it holds: its unit id is param; one at random, the default selector (row 0, sub_2C3770) when none --
// btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate sub_2C28A0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C3EA0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3ea0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 10400);  // &sub_2C28A0
    jal(ctx, 0x2C3EBCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C3EE0 sub_2C3EE0 -- 20 bytes; leaf frame (no stack)
// [btlAITarget_MINE] AI target selector 7 MINE: the acting action targets itself (one target).
// Arguments: a0 the acting btlAction; returns 1.
void sub_2C3EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x002c3ee0
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(a0, a0, act::kTargets);
    v0 = 1;
    sh(v0, a0, act::kTargetCount);
}

// 0x002C3F00 sub_2C3F00 -- 256 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAITarget_MYAI] AI target selector 8 MYAI: a random living ally other than the acting action (itself when it has
// none).
// Arguments: a0 the acting btlAction; returns 1.
void sub_2C3F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c3f00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    // collect the living allies (not the action itself) into the stack list
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x002c3f9c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c3f2c
        charge(ctx, 2);
        if (s2 != s1) {
            // 0x002c3f34
            charge(ctx, 4);
            lhu(v1, s1, act::kFlags2);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x002c3f44
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 != 0) {
                    // 0x002c3f50
                    charge(ctx, 6);
                    lw(a0, s1, act::kUnit);
                    lw(v0, s2, act::kUnit);
                    lbu(v1, v0, unit::kSide);
                    lbu(v0, a0, unit::kSide);
                    if (v1 == v0) {
                        // 0x002c3f68
                        charge(ctx, 6);
                        lw(a0, a0, unit::kDat);
                        a1 = 0x80000;
                        jal(ctx, 0x2C3F70u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002c3f80
                            charge(ctx, 6);
                            v0 = s0 & 0xFFFF;
                            v0 = sll(v0, 2);
                            v0 = addu(v0, sp);
                            sw(s1, v0, 64);
                            v0 = addiu(s0, 1);
                            s0 = v0 & 0xFFFF;
                        }
                    }
                }
            }
        }
        // 0x002c3f98
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002c3fa4
    charge(ctx, 3);
    a0 = s0 & 0xFFFF;
    if (a0 != 0) {
        // 0x002c3fc4
        charge(ctx, 8);
        // one at random, else the action itself
        jal(ctx, 0x2C3FC4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        lw(v0, v0, 64);
        sw(v0, s2, act::kTargets);
        v0 = 1;
        sh(v0, s2, act::kTargetCount);
    } else {
        // 0x002c3fb0
        charge(ctx, 5);
        sw(s2, s2, act::kTargets);
        v0 = 1;
        sh(v0, s2, act::kTargetCount);
    }
    // 0x002c3fe4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002C4000 sub_2C4000 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_HANSYA] AI target selector 9 HANSYA: from the candidates of the action's skill, the units -- those for
// which it holds: it repels the element param (affinity bit 0x2000000); one at random, the default selector (row 0,
// sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
// sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4000(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4000
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C401Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4040 sub_2C4040 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_KYUSYU] AI target selector 10 KYUSYU: from the candidates of the action's skill, the units -- those
// for which it holds: it drains the element param (affinity bit 0x4000000); one at random, the default selector (row
// 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
// sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4040(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4040
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C405Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4080 sub_2C4080 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_MUKOU] AI target selector 11 MUKOU: from the candidates of the action's skill, the units -- those for
// which it holds: it nullifies the element param (affinity bit 0x1000000); one at random, the default selector (row
// 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
// sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4080(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4080
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C409Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C40C0 sub_2C40C0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_WEAK] AI target selector 12 WEAK: from the candidates of the action's skill, the units -- those for
// which it holds: it is weak to the element param (affinity bit 0x8000000); one at random, the default selector (row
// 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
// sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C40C0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c40c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C40DCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4100 sub_2C4100 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTHANSYA] AI target selector 13 NOTHANSYA: from the candidates of the action's skill, the units --
// those for which it does NOT hold: it repels the element param (affinity bit 0x2000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value
// 1, predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4100(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4100
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C411Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4140 sub_2C4140 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTKYUSYU] AI target selector 14 NOTKYUSYU: from the candidates of the action's skill, the units --
// those for which it does NOT hold: it drains the element param (affinity bit 0x4000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value
// 1, predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4140(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4140
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C415Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4180 sub_2C4180 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTMUKOU] AI target selector 15 NOTMUKOU: from the candidates of the action's skill, the units --
// those for which it does NOT hold: it nullifies the element param (affinity bit 0x1000000); one at random, the
// default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0,
// compare value 1, predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4180(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4180
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C419Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C41C0 sub_2C41C0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTWEAK] AI target selector 16 NOTWEAK: from the candidates of the action's skill, the units -- those
// for which it does NOT hold: it is weak to the element param (affinity bit 0x8000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value
// 1, predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C41C0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c41c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C41DCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4200 sub_2C4200 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAITarget_AI_REV] AI target selector 17 AI_REV: the candidate list of the reversed target side (sub_2BFF60 with
// 1); a group skill takes it whole, else one at random (datCalcRand).
// Arguments: a0 the acting btlAction; returns 1.
void sub_2C4200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4200
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = addiu(s0, 136);
    lhu(a2, a0, act::kCmdSkill);
    a3 = 1;
    jal(ctx, 0x2C421Cu, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
        // 0x002c427c
        charge(ctx, 10);
        lhu(a0, s0, act::kTargetRecCount);
        jal(ctx, 0x2C4280u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
        v0 = v0 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, s0);
        lw(v0, v0, 136);
        sw(v0, s0, act::kTargets);
        v0 = 1;
        sh(v0, s0, act::kTargetCount);
    } else {
        // 0x002c4230
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c4258
            charge(ctx, 5);
            lhu(v1, s0, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c423c
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s0, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c426c
        charge(ctx, 4);
        sh(v1, s0, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c42a4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C42C0 sub_2C42C0 -- 224 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAITarget_APPOINT] AI target selector 18 APPOINT: a group skill takes the whole list; else the candidate the
// record already points at (sub_2C0970 / sub_2C0880), or the default selector (sub_2C3770).
// Arguments: a0 the acting btlAction, a1 the parameter.
void sub_2C42C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c42c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    a1 = addiu(s0, 136);
    lhu(a2, a0, act::kCmdSkill);
    a3 = 0;
    jal(ctx, 0x2C42E4u, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
        // 0x002c4344
        charge(ctx, 5);
        a0 = addiu(s0, 136);
        jal(ctx, 0x2C4348u, gen::fn_sub_2C0970_002c0970);
        if (v0 != 0) {
            // 0x002c4370
            charge(ctx, 6);
            a0 = addiu(s0, 136);
            jal(ctx, 0x2C4374u, gen::fn_sub_2C0880_002c0880);
            sw(v0, s0, act::kTargets);
            v0 = 1;
            sh(v0, s0, act::kTargetCount);
        } else {
            // 0x002c4358
            charge(ctx, 6);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x2C4360u, gen::fn_sub_2C3770_002c3770);
        }
    } else {
        // 0x002c42f8
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c4320
            charge(ctx, 5);
            lhu(v1, s0, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c4304
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s0, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c4334
        charge(ctx, 4);
        sh(v1, s0, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c4388 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002C43A0 sub_2C43A0 -- 56 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_DOWN] AI target selector 19 DOWN: from the candidates of the action's skill, the units -- those for
// which it holds: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row 0,
// sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate
// sub_2C1710.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C43A0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c43a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0x100000;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 5904);  // &sub_2C1710
    jal(ctx, 0x2C43C0u, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C43E0 sub_2C43E0 -- 56 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_STAND] AI target selector 20 STAND: from the candidates of the action's skill, the units -- those for
// which it does NOT hold: it has the bad status param (datCalcChkBadStatus); one at random, the default selector (row
// 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate
// sub_2C1710.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C43E0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c43e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0x100000;
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 5904);  // &sub_2C1710
    jal(ctx, 0x2C4400u, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4420 sub_2C4420 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_HANSYA_ST] AI target selector 21 HANSYA_ST: from the candidates of the action's skill, the standing
// (status 0x100000 excluded) units -- those for which it holds: it repels the element param (affinity bit 0x2000000);
// one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask
// 0x100000, flags 0, compare value 0, predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4420(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4420
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C443Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4460 sub_2C4460 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_KYUSYU_ST] AI target selector 22 KYUSYU_ST: from the candidates of the action's skill, the standing
// (status 0x100000 excluded) units -- those for which it holds: it drains the element param (affinity bit 0x4000000);
// one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask
// 0x100000, flags 0, compare value 0, predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4460(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4460
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C447Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C44A0 sub_2C44A0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_MUKOU_ST] AI target selector 23 MUKOU_ST: from the candidates of the action's skill, the standing
// (status 0x100000 excluded) units -- those for which it holds: it nullifies the element param (affinity bit
// 0x1000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with
// status mask 0x100000, flags 0, compare value 0, predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C44A0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c44a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C44BCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C44E0 sub_2C44E0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_WEAK_ST] AI target selector 24 WEAK_ST: from the candidates of the action's skill, the standing
// (status 0x100000 excluded) units -- those for which it holds: it is weak to the element param (affinity bit
// 0x8000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with
// status mask 0x100000, flags 0, compare value 0, predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C44E0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c44e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C44FCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4520 sub_2C4520 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTHANSYA_ST] AI target selector 25 NOTHANSYA_ST: from the candidates of the action's skill, the
// standing (status 0x100000 excluded) units -- those for which it does NOT hold: it repels the element param
// (affinity bit 0x2000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget
// (sub_2C3430) with status mask 0x100000, flags 0, compare value 1, predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4520(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4520
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C453Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4560 sub_2C4560 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTKYUSYU_ST] AI target selector 26 NOTKYUSYU_ST: from the candidates of the action's skill, the
// standing (status 0x100000 excluded) units -- those for which it does NOT hold: it drains the element param
// (affinity bit 0x4000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget
// (sub_2C3430) with status mask 0x100000, flags 0, compare value 1, predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4560(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4560
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C457Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C45A0 sub_2C45A0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTMUKOU_ST] AI target selector 27 NOTMUKOU_ST: from the candidates of the action's skill, the
// standing (status 0x100000 excluded) units -- those for which it does NOT hold: it nullifies the element param
// (affinity bit 0x1000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget
// (sub_2C3430) with status mask 0x100000, flags 0, compare value 1, predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C45A0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c45a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C45BCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C45E0 sub_2C45E0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTWEAK_ST] AI target selector 28 NOTWEAK_ST: from the candidates of the action's skill, the standing
// (status 0x100000 excluded) units -- those for which it does NOT hold: it is weak to the element param (affinity bit
// 0x8000000); one at random, the default selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with
// status mask 0x100000, flags 0, compare value 1, predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C45E0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c45e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0x100000;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C45FCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4620 sub_2C4620 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_HANSYA_DW] AI target selector 29 HANSYA_DW: from the candidates of the action's skill, the downed
// units -- those for which it holds: it repels the element param (affinity bit 0x2000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
// 0, predicate sub_2C1E10.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4620(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4620
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 1;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7696);  // &sub_2C1E10
    jal(ctx, 0x2C463Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4660 sub_2C4660 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_KYUSYU_DW] AI target selector 30 KYUSYU_DW: from the candidates of the action's skill, the downed
// units -- those for which it holds: it drains the element param (affinity bit 0x4000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
// 0, predicate sub_2C1E50.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4660(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4660
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 1;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7760);  // &sub_2C1E50
    jal(ctx, 0x2C467Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C46A0 sub_2C46A0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_MUKOU_DW] AI target selector 31 MUKOU_DW: from the candidates of the action's skill, the downed units
// -- those for which it holds: it nullifies the element param (affinity bit 0x1000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
// 0, predicate sub_2C1E90.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C46A0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c46a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 1;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7824);  // &sub_2C1E90
    jal(ctx, 0x2C46BCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C46E0 sub_2C46E0 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_WEAK_DW] AI target selector 32 WEAK_DW: from the candidates of the action's skill, the downed units --
// those for which it holds: it is weak to the element param (affinity bit 0x8000000); one at random, the default
// selector (row 0, sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 1, compare value
// 0, predicate sub_2C1ED0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C46E0(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c46e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 1;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 7888);  // &sub_2C1ED0
    jal(ctx, 0x2C46FCu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4720 sub_2C4720 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTID] AI target selector 33 NOTID: from the candidates of the action's skill, the units -- those for
// which it does NOT hold: its unit id is param; one at random, the default selector (row 0, sub_2C3770) when none --
// btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate sub_2C28A0.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4720(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4720
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 10400);  // &sub_2C28A0
    jal(ctx, 0x2C473Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4760 sub_2C4760 -- 184 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAITarget_RND] AI target selector 34 RND: a group skill takes the whole candidate list; else one candidate at
// random.
// Arguments: a0 the acting btlAction; returns 1.
void sub_2C4760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4760
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = addiu(s0, 136);
    lhu(a2, a0, act::kCmdSkill);
    a3 = 0;
    jal(ctx, 0x2C477Cu, gen::fn_sub_2BFF60_002bff60);
    v0 = v0 & 0xFFFF;
    if (v0 == 0) {
        // 0x002c47dc
        charge(ctx, 10);
        lhu(a0, s0, act::kTargetRecCount);
        jal(ctx, 0x2C47E0u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
        v0 = v0 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, s0);
        lw(v0, v0, 136);
        sw(v0, s0, act::kTargets);
        v0 = 1;
        sh(v0, s0, act::kTargetCount);
    } else {
        // 0x002c4790
        charge(ctx, 3);
        a0 = 0;
        for (;;) {
            // 0x002c47b8
            charge(ctx, 5);
            lhu(v1, s0, act::kTargetRecCount);
            v0 = a0 & 0xFFFF;
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c479c
            charge(ctx, 7);
            v0 = a0 & 0xFFFF;
            v0 = sll(v0, 2);
            v1 = addu(s0, v0);
            lw(v0, v1, 136);
            sw(v0, v1, 56);
            v0 = addiu(a0, 1);
            a0 = v0 & 0xFFFF;
        }
        // 0x002c47cc
        charge(ctx, 4);
        sh(v1, s0, act::kTargetCount);
        v0 = 1;
    }
    // 0x002c4804 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002C4820 sub_2C4820 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_HOJO] AI target selector 35 HOJO: from the candidates of the action's skill, the units -- those for
// which it holds: it has a support effect (sub_301CA0); one at random, the default selector (row 0, sub_2C3770) when
// none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 0, predicate sub_2C3400.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4820(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4820
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0x2C0000;
    t1 = addiu(t1, 13312);  // &sub_2C3400
    jal(ctx, 0x2C483Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4860 sub_2C4860 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlAITarget_NOTHOJO] AI target selector 36 NOTHOJO: from the candidates of the action's skill, the units -- those
// for which it does NOT hold: it has a support effect (sub_301CA0); one at random, the default selector (row 0,
// sub_2C3770) when none -- btlAIPickTarget (sub_2C3430) with status mask 0x0, flags 0, compare value 1, predicate
// sub_2C3400.
// Arguments: a0 the acting btlAction, a1 the selector parameter; returns 1 when a target was set.
void sub_2C4860(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c4860
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = 0x2C0000;
    t1 = addiu(t1, 13312);  // &sub_2C3400
    jal(ctx, 0x2C487Cu, gen::fn_sub_2C3430_002c3430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002C4A90 sub_2C4A90 -- 492 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickHealItemNear] AI healing pick over an item list: the item (its skill through sub_30BC20, below 0x1D0, of
// the target kind a4 by SkillRecord +8) whose heal (datCalcDamage) brings the target's HP nearest its max -- an
// overshoot is preferred to a shortfall only when nothing lands below; then sub_301870 on both DatUnits.
// Arguments: a0 the user's btlAction, a1 the target's btlAction, a2 u16[] item ids, a3 their count, t0 the target
// kind; returns the item id or -1.
void sub_2C4A90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x002c4a90
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s5 = a1;
    fp = a2;
    s7 = a3;
    s0 = t0;
    lw(v0, a1, act::kUnit);
    lw(a0, v0, unit::kDat);
    // the target's HP now; the best item so far (-1) and its distance (0xFFFFFF)
    jal(ctx, 0x2C4AD8u, gen::fn_datCalcGetHp_002ffd70);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xA0);
    s2 = si(-1);
    v0 = 0xFF0000;
    s3 = v0 | 0xFFFF;  // &0xFFFFFF
    s1 = 0;
    s6 = s0 & 0xFFFF;
    s7 = s7 & 0xFFFF;
    // each item of the list
    for (;;) {
        // 0x002c4c14
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slt(v0, s7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002c4b08
        charge(ctx, 9);
        v0 = s1 & 0xFFFF;
        v0 = sll(v0, 1);
        s0 = addu(fp, v0);
        lhu(a0, s0, 0);
        // the item's skill (0: no skill)
        jal(ctx, 0x2C4B18u, gen::fn_sub_30BC20_0030bc20);
        a0 = v0 & 0xFFFF;
        if (a0 != 0) {
            // 0x002c4b2c
            charge(ctx, 3);
            at = slti(a0, 464);
            if (at != 0) {
                // 0x002c4b38
                charge(ctx, 10);
                v0 = sll(a0, 2);
                v0 = addu(v0, a0);
                v0 = sll(v0, 1);
                v0 = addu(v0, a0);
                v1 = sll(v0, 2);
                lw(v0, gp, kGpSkillTbl);  // gBtlSkillTbl
                v0 = addu(v0, v1);
                // the skill's target kind (SkillRecord +8, 44-byte rows of gBtlSkillTbl): kind 0 keeps
                // target kind 1, kind 1 keeps target kind 0
                lbu(a1, v0, 8);
                if (s6 == 0) {
                    // 0x002c4b60
                    charge(ctx, 4);
                    v1 = a1 & 0xFF;
                    v0 = 1;
                    if (v1 != v0) {
                        goto L_002c4c0c;
                    }
                }
                charge(ctx, 3);
                v0 = 1;
                if (s6 == v0) {
                    // 0x002c4b7c
                    charge(ctx, 3);
                    v0 = a1 & 0xFF;
                    if (v0 != 0) {
                        goto L_002c4c0c;
                    }
                }
                charge(ctx, 15);
                lw(v1, s4, act::kUnit);
                lw(v0, s5, act::kUnit);
                lw(a1, v1, unit::kDat);
                lw(a2, v0, unit::kDat);
                a3 = 1;
                t0 = a3;
                t1 = a3;
                t2 = a3;
                t3 = a3;
                // HP after the heal = HP + datCalcDamage(skill, user, target, 1, 1, 1, 1, 1)
                jal(ctx, 0x2C4BACu, gen::fn_datCalcDamage_00303130);
                lq(v1, sp, 0xA0);
                v0 = addu(v1, v0);
                // a result above 0 replaces a best above 0 when smaller; at or below 0 it replaces a best
                // above 0, or one further below
                if (i64(v0) > 0) {
                    // 0x002c4bc4
                    charge(ctx, 2);
                    if (!(i64(s3) <= 0)) {
                        // 0x002c4bcc
                        charge(ctx, 3);
                        at = slt(v0, s3);
                        if (at != 0) {
                            // 0x002c4bd8
                            charge(ctx, 4);
                            lhu(s2, s0, 0);
                            s3 = v0;
                        }
                        goto L_002c4c0c;
                    }
                }
                charge(ctx, 2);
                if (i64(v0) <= 0) {
                    // 0x002c4bf0
                    charge(ctx, 2);
                    if (i64(s3) <= 0) {
                        // 0x002c4bf8
                        charge(ctx, 3);
                        at = slt(s3, v0);
                        if (at == 0) {
                            goto L_002c4c0c;
                        }
                    }
                    charge(ctx, 2);
                    lhu(s2, s0, 0);
                    s3 = v0;
                }
            }
        }
    L_002c4c0c:
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x002c4c24
    charge(ctx, 22);
    lw(v0, s4, act::kUnit);
    lw(a0, v0, unit::kDat);
    // release both units' damage work (sub_301870)
    jal(ctx, 0x2C4C2Cu, gen::fn_sub_301870_00301870);
    lw(v0, s5, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2C4C3Cu, gen::fn_sub_301870_00301870);
    v0 = s2;
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x002C65D0 sub_2C65D0 -- 1060 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIPickWeightedTarget] AI target weighting: one target -> it; else each candidate is scored by its missing HP
// percent plus a bonus per ailment (64 / 32 / 2: +20, 16 / 4: +30, 8: +50), the list is bubble-sorted by score
// (descending) and one is drawn with the weights of the table 0x696FB0 (datCalcRand over their sum).
// Arguments: a0 the acting btlAction; returns the chosen btlAction or 0.
void sub_2C65D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x002c65d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    // one candidate: it is the target
    lhu(v1, a0, act::kTargetRecCount);
    v0 = 1;
    if (v1 != v0) {
        // 0x002c6610
        charge(ctx, 4);
        s4 = 0;
        s5 = 0;
        // score each candidate: the weight sum, then 100 - HP percent
        for (;;) {
            // 0x002c68d8
            charge(ctx, 4);
            lhu(v0, s0, act::kTargetRecCount);
            v0 = sltu(s5, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c6620
            charge(ctx, 24);
            v1 = sll(s5, 2);
            v0 = 0x690000;
            v0 = addiu(v0, 28592);  // &0x696FB0
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            s4 = addu(s4, v0);
            v0 = addu(s0, v1);
            lw(s3, v0, act::kTargetRec);
            v0 = sll(s5, 1);
            v0 = addu(v0, sp);
            s2 = addiu(v0, 112);
            sh(zero, s2, 0);
            lw(v0, s3, act::kUnit);
            lw(a0, v0, unit::kDat);
            jal(ctx, 0x2C6658u, gen::fn_datCalcGetMaxHp_002ffdf0);
            s1 = v0 & 0xFFFF;
            lw(v0, s3, act::kUnit);
            lw(a0, v0, unit::kDat);
            jal(ctx, 0x2C666Cu, gen::fn_datCalcGetHp_002ffd70);
            v0 = v0 & 0xFFFF;
            if (i64(v0) < 0) {
                // 0x002c6694
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x002c6680
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x002c66b0
            charge(ctx, 2);
            if (i64(s1) < 0) {
                // 0x002c66cc
                charge(ctx, 7);
                v1 = srl(s1, 1);
                v0 = s1 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x002c66b8
                charge(ctx, 5);
                mtc1(s1, f0);
                cvt_s_w(f0, f0);
            }
            // 0x002c66e8
            charge(ctx, 24);
            div_s(f2, f1, f0);
            v0 = 0x42C80000;
            mtc1(v0, f1);
            mtc1(zero, f0);
            adda_s(f0, f1);
            msub_s(f0, f1, f2);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            lh(v0, s2, 0);
            v0 = addu(v0, v1);
            sh(v0, s2, 0);
            lw(v0, s3, act::kUnit);
            lw(a0, v0, unit::kDat);
            // plus the ailment bonus
            jal(ctx, 0x2C6734u, gen::fn_datCalcGetBadStatusNoDown_00300530);
            v1 = 64;
            if (v0 == v1) {
                // 0x002c68a4
                charge(ctx, 12);
                lh(v0, s2, 0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41A00000;
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(v0, f0);
                sh(v0, s2, 0);
            } else {
                // 0x002c6748
                charge(ctx, 3);
                v1 = 32;
                if (v0 == v1) {
                    // 0x002c686c
                    charge(ctx, 14);
                    lh(v0, s2, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41A00000;
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    sh(v0, s2, 0);
                } else {
                    // 0x002c6754
                    charge(ctx, 3);
                    v1 = 16;
                    if (v0 == v1) {
                        // 0x002c6834
                        charge(ctx, 14);
                        lh(v0, s2, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x41F00000;
                        mtc1(v0, f0);
                        add_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        sh(v0, s2, 0);
                    } else {
                        // 0x002c6760
                        charge(ctx, 3);
                        v1 = 8;
                        if (v0 == v1) {
                            // 0x002c67fc
                            charge(ctx, 14);
                            lh(v0, s2, 0);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x42480000;
                            mtc1(v0, f0);
                            add_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(v0, f0);
                            sh(v0, s2, 0);
                        } else {
                            // 0x002c676c
                            charge(ctx, 3);
                            v1 = 4;
                            if (v0 == v1) {
                                // 0x002c67c4
                                charge(ctx, 14);
                                lh(v0, s2, 0);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                v0 = 0x41F00000;
                                mtc1(v0, f0);
                                add_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(v0, f0);
                                sh(v0, s2, 0);
                            } else {
                                // 0x002c6778
                                charge(ctx, 3);
                                v1 = 2;
                                if (v0 == v1) {
                                    // 0x002c678c
                                    charge(ctx, 14);
                                    lh(v0, s2, 0);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    v0 = 0x41A00000;
                                    mtc1(v0, f0);
                                    add_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(v0, f0);
                                    sh(v0, s2, 0);
                                } else {
                                    // 0x002c6784
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
            // 0x002c68d4
            charge(ctx, 1);
            s5 = addiu(s5, 1);
        }
        // 0x002c68e8
        charge(ctx, 1);
        // bubble-sort the candidates (+136) and their scores by score, highest first
        v1 = 1;
        for (;;) {
            // 0x002c68ec
            charge(ctx, 4);
            a0 = 0;
            t2 = 0;
            for (;;) {
                // 0x002c6948
                charge(ctx, 5);
                lhu(v0, s0, act::kTargetRecCount);
                v0 = addiu(v0, -1);
                v0 = sltu(t2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002c68fc
                charge(ctx, 9);
                v0 = sll(t2, 1);
                v0 = addu(v0, sp);
                t1 = addiu(v0, 112);
                t0 = addiu(t1, 2);
                lh(a3, t1, 2);
                lh(a2, t1, 0);
                at = slt(a2, a3);
                if (at != 0) {
                    // 0x002c6920
                    charge(ctx, 9);
                    v0 = sll(t2, 2);
                    a1 = addu(s0, v0);
                    lw(a0, a1, act::kTargetRec);
                    lw(v0, a1, act::kTargetRec + 4);
                    sw(v0, a1, act::kTargetRec);
                    sw(a0, a1, act::kTargetRec + 4);
                    sh(a3, t1, 0);
                    sh(a2, t0, 0);
                    a0 = v1;
                }
                // 0x002c6944
                charge(ctx, 1);
                t2 = addiu(t2, 1);
            }
            // 0x002c695c
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x002c6964
        charge(ctx, 10);
        s1 = 0;
        a0 = s4;
        // draw by the weights of the table 0x696FB0 (one per rank)
        jal(ctx, 0x2C696Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
        a3 = 0;
        lhu(a2, s0, act::kTargetRecCount);
        a0 = 0x690000;
        a0 = addiu(a0, 28592);  // &0x696FB0
        for (;;) {
            // 0x002c69bc
            charge(ctx, 3);
            v1 = sltu(a3, a2);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002c698c
            charge(ctx, 7);
            a1 = sll(a3, 2);
            v1 = addu(a0, a1);
            lw(v1, v1, 0);
            s1 = addu(s1, v1);
            at = sltu(v0, s1);
            if (at != 0) {
                goto L_002c69a8_33;
            }
            // 0x002c69b8
            charge(ctx, 1);
            a3 = addiu(a3, 1);
        }
        // 0x002c69c8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002c6604
        charge(ctx, 3);
        lw(v0, s0, act::kTargetRec);
    }
    // 0x002c69cc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
    return;
L_002c69a8_33:
    charge(ctx, 4);
    v0 = addu(a1, s0);
    lw(v0, v0, act::kTargetRec);
    // 0x002c69cc (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x002C74E0 sub_2C74E0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// AI script command (COMM): stores the script's first parameter in the action +220 and sets the command 0x8002 (kind
// 7) through sub_2C6A00; returns 1.
// Arguments: none (the script's user data is the btlAction).
void sub_2C74E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002c74e0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2C74ECu, gen::fn_scrGetUserData_0035f160);
    s0 = v0;
    a0 = 0;
    jal(ctx, 0x2C74FCu, gen::fn_scrGetIntPara_0035ed20);
    sh(v0, s0, 220);
    a0 = s0;
    a1 = addiu(s0, 56);
    a2 = 0x8002;
    jal(ctx, 0x2C7514u, gen::fn_sub_2C6A00_002c6a00);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D08E0 sub_2D08E0 -- 132 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// AI script command (COMM): sets the action's unit argument (sub_288F80 with parameter 0) and the command of
// parameter 1 through sub_2C6A00; returns 1.
// Arguments: none (the script's user data is the btlAction).
void sub_2D08E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d08e0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2D08F4u, gen::fn_scrGetUserData_0035f160);
    s2 = v0;
    a0 = 0;
    jal(ctx, 0x2D0904u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x2D0914u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    lw(a0, s2, 48);
    a1 = s1;
    jal(ctx, 0x2D0928u, gen::fn_sub_288F80_00288f80);
    a2 = s0 & 0xFFFF;
    a0 = s2;
    a1 = addiu(s2, 56);
    jal(ctx, 0x2D093Cu, gen::fn_sub_2C6A00_002c6a00);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002D1660 sub_2D1660 -- 848 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIDecodeCommand] AI command decode for a non-scripted unit: clears the command record, picks a row by the query
// word a2 (0x200 / 64 / 32 / 16: fixed rows at 0x7CC958..; 8: the support table 0x6977D0 by a row the hero /
// sub_697294 picks; 1: the table 0x697730 by the HP / ailment conditions of rows 0x6973CC / 0x69721C) and draws one
// of its five weighted entries; then sets the command (sub_2C6A00) and calls the entry's target selector of 0x6975E0
// (row 0 when it finds nothing).
// Arguments: a0 the btlAction, a1 its command record (+56), a2 the query word.
void sub_2D1660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1660
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s3 = a2;
    // clear the command record
    sh(zero, a1, 50);
    sh(zero, a1, 54);
    sh(zero, a1, 56);
    sh(zero, a1, 52);
    a0 = addiu(s1, 62);
    a1 = 0;
    a2 = 6;
    jal(ctx, 0x2D16A4u, gen::fn_memset_00521408);
    a2 = 0;
    s0 = 0;
    // the query kind: the low 20 bits of the word
    v1 = dsll32(s3, 12);
    v1 = dsrl32(v1, 12);
    v0 = 512;
    if (v1 == v0) {
        // 0x002d184c
        charge(ctx, 1);
        s0 = addiu(gp, -25480);  // &0x7CC968
    } else {
        // 0x002d16c8
        charge(ctx, 3);
        v0 = 64;
        if (v1 == v0) {
            // 0x002d1840
            charge(ctx, 3);
            s0 = addiu(gp, -25488);  // &0x7CC960
        } else {
            // 0x002d16d4
            charge(ctx, 3);
            v0 = 32;
            if (v1 == v0) {
                // 0x002d1834
                charge(ctx, 3);
                s0 = addiu(gp, -25496);  // &0x7CC958
            } else {
                // 0x002d16e0
                charge(ctx, 3);
                v0 = 16;
                if (v1 == v0) {
                    // 0x002d1828
                    charge(ctx, 3);
                    s0 = addiu(gp, -25504);  // &0x7CC950
                } else {
                    // 0x002d16ec
                    charge(ctx, 3);
                    // kind 8: the support rows 0x6977D0, row 0 for the hero or when the row-0 condition of
                    // 0x697294 fails, else row 1
                    v0 = 8;
                    if (v1 == v0) {
                        // 0x002d17cc
                        charge(ctx, 4);
                        lw(v1, s2, act::kUnit);
                        lbu(v0, v1, unit::kSide);
                        if (v0 == 0) {
                            // 0x002d17dc
                            charge(ctx, 4);
                            lhu(v1, v1, unit::kId);
                            // kind 1: the rows 0x697730 by two conditions (0x6973CC, 0x69721C negated): row 0..3
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x002d17ec
                                charge(ctx, 3);
                                s4 = v0 & 0xFFFF;
                                goto L_002d1818;
                            }
                        }
                        charge(ctx, 8);
                        a0 = s2;
                        a1 = 0;
                        v0 = 0x690000;
                        lw(v0, v0, 29332);  // 0x697294
                        jalr(ctx, 0x2D1808u, v0.u());
                        v0 = v0 ^ 0x1;
                        s4 = sltu(0, v0);
                    L_002d1818:
                        charge(ctx, 4);
                        a2 = 0x690000;
                        a2 = addiu(a2, 30672);  // &0x6977D0
                    } else {
                        // 0x002d16f8
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x002d170c
                            charge(ctx, 18);
                            a0 = s2;
                            a1 = 0;
                            v0 = 0x690000;
                            lw(v0, v0, 29644);  // 0x6973CC
                            jalr(ctx, 0x2D171Cu, v0.u());
                            s3 = v0;
                            a0 = s2;
                            a1 = 1;
                            v0 = 0x690000;
                            lw(v0, v0, 29212);  // 0x69721C
                            jalr(ctx, 0x2D1738u, v0.u());
                            v0 = sltu(0, v0);
                            v1 = v0 ^ 0x1;
                            v0 = 1;
                            if (s3 == v0) {
                                // 0x002d1754
                                charge(ctx, 2);
                                if (v1 == v0) {
                                    // 0x002d175c
                                    charge(ctx, 3);
                                    s4 = 0;
                                    goto L_002d17bc;
                                }
                            }
                            charge(ctx, 3);
                            v0 = 1;
                            if (s3 == v0) {
                                // 0x002d1774
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x002d177c
                                    charge(ctx, 3);
                                    s4 = v0 & 0xFFFF;
                                    goto L_002d17bc;
                                }
                            }
                            charge(ctx, 2);
                            if (s3 == 0) {
                                // 0x002d1790
                                charge(ctx, 3);
                                v0 = 1;
                                if (v1 == v0) {
                                    // 0x002d179c
                                    charge(ctx, 3);
                                    s4 = 2;
                                    goto L_002d17bc;
                                }
                            }
                            charge(ctx, 2);
                            if (s3 == 0) {
                                // 0x002d17b0
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x002d17b8
                                    charge(ctx, 1);
                                    s4 = 3;
                                }
                            }
                        L_002d17bc:
                            charge(ctx, 4);
                            a2 = 0x690000;
                            a2 = addiu(a2, 30512);  // &0x697730
                        } else {
                            // 0x002d1704
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x002d1850
    charge(ctx, 2);
    // a table row: five entries of 8 bytes {u8 weight, ...}; draw one by weight
    if (a2 != 0) {
        // 0x002d1858
        charge(ctx, 9);
        a0 = 0;
        a1 = 0;
        v1 = s4 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        s3 = addu(a2, v0);
        for (;;) {
            // 0x002d189c
            charge(ctx, 4);
            v0 = a1 & 0xFFFF;
            v0 = slti(v0, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d187c
            charge(ctx, 8);
            v0 = a1 & 0xFFFF;
            v0 = sll(v0, 3);
            v0 = addu(s3, v0);
            lbu(v0, v0, 0);
            v0 = addu(a0, v0);
            a0 = v0 & 0xFFFF;
            v0 = addiu(a1, 1);
            a1 = v0 & 0xFFFF;
        }
        // 0x002d18ac
        charge(ctx, 9);
        s0 = 0;
        a0 = a0 & 0xFFFF;
        jal(ctx, 0x2D18B4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
        a1 = v0 & 0xFFFF;
        a3 = 0;
        a2 = 0;
        for (;;) {
            // 0x002d1910
            charge(ctx, 4);
            v0 = a2 & 0xFFFF;
            v0 = slti(v0, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002d18d0
            charge(ctx, 9);
            v0 = a2 & 0xFFFF;
            v0 = sll(v0, 3);
            a0 = addu(s3, v0);
            lbu(v1, a0, 0);
            v0 = addu(a3, v1);
            a3 = v0 & 0xFFFF;
            at = slt(a3, a1);
            if (at == 0) {
                // 0x002d18f4
                charge(ctx, 2);
                if (!(i64(v1) <= 0)) {
                    goto L_002d18fc_36;
                }
            }
            charge(ctx, 2);
            v0 = addiu(a2, 1);
            a2 = v0 & 0xFFFF;
        }
    }
L_002d1920:
    charge(ctx, 21);
    a0 = s2;
    a1 = s1;
    // the entry: set its command (+2) and call its target selector (+4: kind << 24 | param)
    lhu(a2, s0, 2);
    jal(ctx, 0x2D192Cu, gen::fn_sub_2C6A00_002c6a00);
    lw(v1, s0, 4);
    a1 = dsll32(v1, 8);
    a1 = dsrl32(a1, 8);
    a0 = s2;
    v0 = lui(0xFF00);
    v0 = v1 & v0;
    v0 = srl(v0, 24);
    v1 = sll(v0, 3);
    v0 = 0x690000;
    v0 = addiu(v0, 30176);  // &0x6975E0 the target selector table
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x2D1964u, v0.u());
    if (v0 == 0) {
        // 0x002d1974
        charge(ctx, 6);
        a0 = s2;
        a1 = 0;
        v0 = 0x690000;
        lw(v0, v0, 30176);  // 0x6975E0
        jalr(ctx, 0x2D1984u, v0.u());
    }
    // 0x002d198c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002d18fc_36:
    charge(ctx, 3);
    s0 = a0;
    goto L_002d1920;
}

// 0x002D1C20 sub_2D1C20 -- 216 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlAIScriptPktUpdate] AI script packet update: the first call starts the AI script (sub_2C6F50) for the action and
// marks it running (+104); later calls return 1 once the script task has ended (kwlnTaskExists) and clear the
// record's script state.
// Arguments: a0 the packet data {action, procedure, started, script}.
void sub_2D1C20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1c20
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 8);
    if (v0 == 0) {
        // 0x002d1c3c
        charge(ctx, 12);
        lw(a0, s0, 0);
        a1 = addiu(a0, 56);
        lw(a2, s0, 12);
        lw(a3, s0, 4);
        jal(ctx, 0x2D1C4Cu, gen::fn_sub_2C6F50_002c6f50);
        v1 = 1;
        lw(v0, s0, 0);
        sb(v1, v0, 104);
        sw(v1, s0, 8);
        goto L_002d1ce0;
    }
    // 0x002d1c6c
    charge(ctx, 5);
    lw(v0, s0, 0);
    s0 = addiu(v0, 56);
    lbu(v0, v0, 104);
    if (v0 != 0) {
        // 0x002d1c8c
        charge(ctx, 3);
        lw(a0, s0, 76);
        if (a0 != 0) {
            // 0x002d1ca4
            charge(ctx, 4);
            jal(ctx, 0x2D1CA4u, gen::fn_kwlnTaskExists_00195460);
            if (v0 != 0) {
                // 0x002d1cc8
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x002d1cb4
                charge(ctx, 5);
                sb(zero, s0, 48);
                sw(zero, s0, 76);
                v0 = 1;
            }
        } else {
            // 0x002d1c98
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x002d1c80
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002d1ccc
    charge(ctx, 2);
    if (v0 == 0) {
    L_002d1ce0:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002d1cd4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002d1ce4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D1D00 sub_2D1D00 -- 216 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAIScriptPktCreate] Creates an AI script packet (kind 3328, 16 data bytes, update sub_2D1C20): the action, the
// script by kind (1: *0x7CE4CC, 2: *0x7CE4D0) and its procedure named a2 (scrFindPrcdIdxByName).
// Arguments: a0 the btlAction, a1 the script kind (1 / 2), a2 the procedure name.
void sub_2D1D00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1d00
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a0 = 3328;
    a1 = 16;
    jal(ctx, 0x2D1D30u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    s1 = v0;
    lbu(v1, v0, pkt::kFlags);
    v1 = v1 & 0xEE;
    sb(v1, v0, pkt::kFlags);
    v1 = 0x2D0000;
    v1 = addiu(v1, 7200);  // &sub_2D1C20
    sw(v1, v0, pkt::kUpdate);
    lw(s0, v0, pkt::kData);
    v1 = s3 & 0xFFFF;
    v0 = 2;
    if (v1 == v0) {
        // 0x002d1d8c
        charge(ctx, 2);
        lw(v0, gp, kGpBossScript);  // the boss AI script 0x7CE4D0
        sw(v0, s0, 12);
    } else {
        // 0x002d1d68
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x002d1d7c
            charge(ctx, 4);
            lw(v0, gp, kGpPartyAiScript);  // the party AI script 0x7CE4CC
            sw(v0, s0, 12);
        } else {
            // 0x002d1d74
            charge(ctx, 2);
        }
    }
    // 0x002d1d94
    charge(ctx, 17);
    sw(s4, s0, 0);
    lw(a0, s0, 12);
    a1 = s2;
    jal(ctx, 0x2D1DA0u, gen::fn_scrFindPrcdIdxByName_0035c090);
    sw(v0, s0, 4);
    sw(zero, s0, 8);
    v0 = s1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game
