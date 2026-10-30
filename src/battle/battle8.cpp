// The battle code, eighth pass (slice battle8; docs/ANALYSIS/21_battle.md): the boss fights' camera shots, battle-start
// placements, opening shots, boss talks and event packets (battle8.h lists the groups). The bodies are p3fes_handgen's
// (frame, spills, $ra links, every register, cycle charges, check points); this file names their offsets (b3::, b4::,
// b5::, b7::, bcore:: and battle8.h's b8::) and gives each its role. Still-recompiled callees are reached through their
// gen:: entry points.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle8.h"

namespace p3fes::recomp_gen {
void fn_btlCountActiveUnits_002d4e10(p3fes::EEContext&);
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_btlUnitCreate_002875a0(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datCalcClearBadStatus_00300560(p3fes::EEContext&);
void fn_datCalcGetHeldWeaponType_00308c60(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datCalcSetBadStatus_003004f0(p3fes::EEContext&);
void fn_datCalcSetHp_002ffd90(p3fes::EEContext&);
void fn_datUnitEcAddEnemy_002ff540(p3fes::EEContext&);
void fn_sub_1FDD40_001fdd40(p3fes::EEContext&);
void fn_sub_1FF3D0_001ff3d0(p3fes::EEContext&);
void fn_sub_1FF3F0_001ff3f0(p3fes::EEContext&);
void fn_sub_1FF410_001ff410(p3fes::EEContext&);
void fn_sub_27E390_0027e390(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_27F410_0027f410(p3fes::EEContext&);
void fn_sub_27F650_0027f650(p3fes::EEContext&);
void fn_sub_27F680_0027f680(p3fes::EEContext&);
void fn_sub_27F710_0027f710(p3fes::EEContext&);
void fn_sub_27F730_0027f730(p3fes::EEContext&);
void fn_sub_27FCF0_0027fcf0(p3fes::EEContext&);
void fn_sub_27FE90_0027fe90(p3fes::EEContext&);
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);
void fn_sub_280050_00280050(p3fes::EEContext&);
void fn_sub_280130_00280130(p3fes::EEContext&);
void fn_sub_280870_00280870(p3fes::EEContext&);
void fn_sub_2822B0_002822b0(p3fes::EEContext&);
void fn_sub_282C30_00282c30(p3fes::EEContext&);
void fn_sub_2831C0_002831c0(p3fes::EEContext&);
void fn_sub_2838D0_002838d0(p3fes::EEContext&);
void fn_sub_283C50_00283c50(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_2843E0_002843e0(p3fes::EEContext&);
void fn_sub_284C90_00284c90(p3fes::EEContext&);
void fn_sub_285690_00285690(p3fes::EEContext&);
void fn_sub_285D30_00285d30(p3fes::EEContext&);
void fn_sub_285E50_00285e50(p3fes::EEContext&);
void fn_sub_285F20_00285f20(p3fes::EEContext&);
void fn_sub_287510_00287510(p3fes::EEContext&);
void fn_sub_2878D0_002878d0(p3fes::EEContext&);
void fn_sub_2880E0_002880e0(p3fes::EEContext&);
void fn_sub_2889C0_002889c0(p3fes::EEContext&);
void fn_sub_288F80_00288f80(p3fes::EEContext&);
void fn_sub_289650_00289650(p3fes::EEContext&);
void fn_sub_289F40_00289f40(p3fes::EEContext&);
void fn_sub_29A1D0_0029a1d0(p3fes::EEContext&);
void fn_sub_29A2C0_0029a2c0(p3fes::EEContext&);
void fn_sub_29A320_0029a320(p3fes::EEContext&);
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);
void fn_sub_29EA60_0029ea60(p3fes::EEContext&);
void fn_sub_29EC00_0029ec00(p3fes::EEContext&);
void fn_sub_29EC50_0029ec50(p3fes::EEContext&);
void fn_sub_29EC80_0029ec80(p3fes::EEContext&);
void fn_sub_29F4B0_0029f4b0(p3fes::EEContext&);
void fn_sub_29FA50_0029fa50(p3fes::EEContext&);
void fn_sub_2A0050_002a0050(p3fes::EEContext&);
void fn_sub_2A1080_002a1080(p3fes::EEContext&);
void fn_sub_2A1280_002a1280(p3fes::EEContext&);
void fn_sub_2A16C0_002a16c0(p3fes::EEContext&);
void fn_sub_2A1B00_002a1b00(p3fes::EEContext&);
void fn_sub_2A1DB0_002a1db0(p3fes::EEContext&);
void fn_sub_2A2170_002a2170(p3fes::EEContext&);
void fn_sub_2A2290_002a2290(p3fes::EEContext&);
void fn_sub_2A3110_002a3110(p3fes::EEContext&);
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);
void fn_sub_2A3D70_002a3d70(p3fes::EEContext&);
void fn_sub_2A3E80_002a3e80(p3fes::EEContext&);
void fn_sub_2A4470_002a4470(p3fes::EEContext&);
void fn_sub_2A4690_002a4690(p3fes::EEContext&);
void fn_sub_2A54F0_002a54f0(p3fes::EEContext&);
void fn_sub_2A7830_002a7830(p3fes::EEContext&);
void fn_sub_2AC540_002ac540(p3fes::EEContext&);
void fn_sub_2B0280_002b0280(p3fes::EEContext&);
void fn_sub_2B1E00_002b1e00(p3fes::EEContext&);
void fn_sub_2B6070_002b6070(p3fes::EEContext&);
void fn_sub_2B6460_002b6460(p3fes::EEContext&);
void fn_sub_2B6BF0_002b6bf0(p3fes::EEContext&);
void fn_sub_2B6CD0_002b6cd0(p3fes::EEContext&);
void fn_sub_2B71E0_002b71e0(p3fes::EEContext&);
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);
void fn_sub_2B9030_002b9030(p3fes::EEContext&);
void fn_sub_2B90D0_002b90d0(p3fes::EEContext&);
void fn_sub_2BAC00_002bac00(p3fes::EEContext&);
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);
void fn_sub_2BB2F0_002bb2f0(p3fes::EEContext&);
void fn_sub_2BB6F0_002bb6f0(p3fes::EEContext&);
void fn_sub_2BC950_002bc950(p3fes::EEContext&);
void fn_sub_2BD480_002bd480(p3fes::EEContext&);
void fn_sub_2BD590_002bd590(p3fes::EEContext&);
void fn_sub_2BD850_002bd850(p3fes::EEContext&);
void fn_sub_2BDBD0_002bdbd0(p3fes::EEContext&);
void fn_sub_2C09F0_002c09f0(p3fes::EEContext&);
void fn_sub_2C3770_002c3770(p3fes::EEContext&);
void fn_sub_2D1DE0_002d1de0(p3fes::EEContext&);
void fn_sub_2D1F30_002d1f30(p3fes::EEContext&);
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_2D2280_002d2280(p3fes::EEContext&);
void fn_sub_2D3E00_002d3e00(p3fes::EEContext&);
void fn_sub_2D3FE0_002d3fe0(p3fes::EEContext&);
void fn_sub_2D5BF0_002d5bf0(p3fes::EEContext&);
void fn_sub_2D6290_002d6290(p3fes::EEContext&);
void fn_sub_2D6620_002d6620(p3fes::EEContext&);
void fn_sub_2D7890_002d7890(p3fes::EEContext&);
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);
void fn_sub_2D8090_002d8090(p3fes::EEContext&);
void fn_sub_2DB800_002db800(p3fes::EEContext&);
void fn_sub_2DB890_002db890(p3fes::EEContext&);
void fn_sub_2DD100_002dd100(p3fes::EEContext&);
void fn_sub_2DD4A0_002dd4a0(p3fes::EEContext&);
void fn_sub_2DD5E0_002dd5e0(p3fes::EEContext&);
void fn_sub_2DD690_002dd690(p3fes::EEContext&);
void fn_sub_2DD760_002dd760(p3fes::EEContext&);
void fn_sub_2DD830_002dd830(p3fes::EEContext&);
void fn_sub_2E2CB0_002e2cb0(p3fes::EEContext&);
void fn_sub_2E4220_002e4220(p3fes::EEContext&);
void fn_sub_2E4240_002e4240(p3fes::EEContext&);
void fn_sub_2E4A40_002e4a40(p3fes::EEContext&);
void fn_sub_2E4F50_002e4f50(p3fes::EEContext&);
void fn_sub_2E5060_002e5060(p3fes::EEContext&);
void fn_sub_2E58A0_002e58a0(p3fes::EEContext&);
void fn_sub_2E6130_002e6130(p3fes::EEContext&);
void fn_sub_2E6A20_002e6a20(p3fes::EEContext&);
void fn_sub_2E7210_002e7210(p3fes::EEContext&);
void fn_sub_2E7330_002e7330(p3fes::EEContext&);
void fn_sub_2E7890_002e7890(p3fes::EEContext&);
void fn_sub_2E7DB0_002e7db0(p3fes::EEContext&);
void fn_sub_2E82B0_002e82b0(p3fes::EEContext&);
void fn_sub_2E8820_002e8820(p3fes::EEContext&);
void fn_sub_2E8A40_002e8a40(p3fes::EEContext&);
void fn_sub_2E8E20_002e8e20(p3fes::EEContext&);
void fn_sub_2E8F40_002e8f40(p3fes::EEContext&);
void fn_sub_2E9170_002e9170(p3fes::EEContext&);
void fn_sub_2E92C0_002e92c0(p3fes::EEContext&);
void fn_sub_2E9450_002e9450(p3fes::EEContext&);
void fn_sub_2E95F0_002e95f0(p3fes::EEContext&);
void fn_sub_2E9950_002e9950(p3fes::EEContext&);
void fn_sub_2E9AC0_002e9ac0(p3fes::EEContext&);
void fn_sub_2E9C20_002e9c20(p3fes::EEContext&);
void fn_sub_2E9F10_002e9f10(p3fes::EEContext&);
void fn_sub_2EA060_002ea060(p3fes::EEContext&);
void fn_sub_2EA210_002ea210(p3fes::EEContext&);
void fn_sub_2EA400_002ea400(p3fes::EEContext&);
void fn_sub_2EA590_002ea590(p3fes::EEContext&);
void fn_sub_2EA780_002ea780(p3fes::EEContext&);
void fn_sub_2EA860_002ea860(p3fes::EEContext&);
void fn_sub_2EAB70_002eab70(p3fes::EEContext&);
void fn_sub_2EABB0_002eabb0(p3fes::EEContext&);
void fn_sub_2EABF0_002eabf0(p3fes::EEContext&);
void fn_sub_2EB250_002eb250(p3fes::EEContext&);
void fn_sub_2EB2C0_002eb2c0(p3fes::EEContext&);
void fn_sub_2EB9E0_002eb9e0(p3fes::EEContext&);
void fn_sub_2EBA50_002eba50(p3fes::EEContext&);
void fn_sub_2EBEC0_002ebec0(p3fes::EEContext&);
void fn_sub_2EC000_002ec000(p3fes::EEContext&);
void fn_sub_2EC2C0_002ec2c0(p3fes::EEContext&);
void fn_sub_2EC5C0_002ec5c0(p3fes::EEContext&);
void fn_sub_2EC790_002ec790(p3fes::EEContext&);
void fn_sub_2EC990_002ec990(p3fes::EEContext&);
void fn_sub_2ECB30_002ecb30(p3fes::EEContext&);
void fn_sub_2ECBE0_002ecbe0(p3fes::EEContext&);
void fn_sub_2ECC20_002ecc20(p3fes::EEContext&);
void fn_sub_2ECC60_002ecc60(p3fes::EEContext&);
void fn_sub_2ECF80_002ecf80(p3fes::EEContext&);
void fn_sub_2ED360_002ed360(p3fes::EEContext&);
void fn_sub_2EE640_002ee640(p3fes::EEContext&);
void fn_sub_2EEA10_002eea10(p3fes::EEContext&);
void fn_sub_2EEB70_002eeb70(p3fes::EEContext&);
void fn_sub_2EEC60_002eec60(p3fes::EEContext&);
void fn_sub_2EF000_002ef000(p3fes::EEContext&);
void fn_sub_2EF250_002ef250(p3fes::EEContext&);
void fn_sub_2EF360_002ef360(p3fes::EEContext&);
void fn_sub_2EF5A0_002ef5a0(p3fes::EEContext&);
void fn_sub_2EF670_002ef670(p3fes::EEContext&);
void fn_sub_2EF7E0_002ef7e0(p3fes::EEContext&);
void fn_sub_2EFC90_002efc90(p3fes::EEContext&);
void fn_sub_2EFCD0_002efcd0(p3fes::EEContext&);
void fn_sub_2EFD20_002efd20(p3fes::EEContext&);
void fn_sub_2EFDB0_002efdb0(p3fes::EEContext&);
void fn_sub_2EFE50_002efe50(p3fes::EEContext&);
void fn_sub_2F6330_002f6330(p3fes::EEContext&);
void fn_sub_2F6510_002f6510(p3fes::EEContext&);
void fn_sub_2F87E0_002f87e0(p3fes::EEContext&);
void fn_sub_2F8810_002f8810(p3fes::EEContext&);
void fn_sub_2F88C0_002f88c0(p3fes::EEContext&);
void fn_sub_2F8A40_002f8a40(p3fes::EEContext&);
void fn_sub_2FDBB0_002fdbb0(p3fes::EEContext&);
void fn_sub_2FDDB0_002fddb0(p3fes::EEContext&);
void fn_sub_2FDFA0_002fdfa0(p3fes::EEContext&);
void fn_sub_308930_00308930(p3fes::EEContext&);
void fn_sub_308A50_00308a50(p3fes::EEContext&);
void fn_sub_3093A0_003093a0(p3fes::EEContext&);
void fn_sub_30C3A0_0030c3a0(p3fes::EEContext&);
void fn_sub_318540_00318540(p3fes::EEContext&);
void fn_sub_318D10_00318d10(p3fes::EEContext&);
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);
void fn_sub_351BB0_00351bb0(p3fes::EEContext&);
void fn_sub_352C50_00352c50(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_395170_00395170(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
void fn_sub_4BE310_004be310(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6B20_004c6b20(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);
void fn_tanf_0052e930(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b7;  // battle7.h's additions (the camera shot)
using namespace b8;  // this slice's additions (battle8.h)

// 0x002E4A40 sub_2E4A40 -- 1296 bytes; frame 0xD0: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Boss target shot (sub_2E82B0's kind): aims the battle camera at the shot action's unit. A cut is allowed unless
// the camera is in state 28 / 29 (a party actor) or 18 / 31 (an enemy actor). In camera state 9 with the same action
// (gBtl +2940 = the action's serial) it only re-arms the cut (sub_2A3E80); otherwise it records the serial, and for
// encounter 436 lets sub_2F6330 take the shot. A party actor is framed from its look point at 1.25 x the eye height
// (sub_280870 / sub_280130); an enemy from in front at 5.5 x its height / tan (sub_27FFB0, sub_4C69F0, tanf). A far
// move (sub_2D1F30 above the $gp constant) cuts (sub_2B6070 for a party actor sub_30C3A0 accepts, else sub_2B6460, then
// gBtl +2944 = 1); a near one moves (sub_2A2290 / sub_2A3110, heights at least 25).
// Arguments: a0 the camera shot (shot::).
void sub_2E4A40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20};
    // 0x002e4a40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    lw(a0, a0, shot::kAction);
    if (a0 != 0) {
        // 0x002e4a74
        charge(ctx, 4);
        lw(v1, a0, act::kUnit);
        lbu(v1, v1, unit::kSide);
        if (v1 != 0) {
            // 0x002e4ab8
            charge(ctx, 5);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(a1, v1, gbtl::kCameraState);
            v1 = 31;
            if (a1 != v1) {
                // 0x002e4acc
                charge(ctx, 3);
                v1 = 18;
                if (a1 == v1) {
                    goto L_002e4ae0;
                }
                // 0x002e4ad8
                charge(ctx, 2);
            L_002e4aec:
                charge(ctx, 1);
                s0 = 1;
                goto L_002e4af0;
            }
        L_002e4ae0:
            charge(ctx, 3);
            s0 = 0;
        } else {
            // 0x002e4a84
            charge(ctx, 5);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(a1, v1, gbtl::kCameraState);
            v1 = 29;
            if (a1 != v1) {
                // 0x002e4a98
                charge(ctx, 3);
                v1 = 28;
                if (a1 == v1) {
                    goto L_002e4aac;
                }
                // 0x002e4aa4
                charge(ctx, 2);
                goto L_002e4aec;
            }
        L_002e4aac:
            charge(ctx, 3);
            s0 = 0;
        }
    } else {
        // 0x002e4a68
        charge(ctx, 3);
        s0 = 1;
    }
L_002e4af0:
    charge(ctx, 9);
    lw(s1, a0, act::kUnit);
    lwc1(f1, s1, unit::kRadius);
    lwc1(f0, s1, unit::kScale);
    mul_s(f20, f1, f0);
    lw(a2, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(a1, a2, gbtl::kCameraState);
    v1 = 9;
    if (a1 != v1) {
        // 0x002e4b14
        charge(ctx, 2);
        goto L_002e4b58;
    }
    // 0x002e4b1c
    charge(ctx, 4);
    lw(a1, a2, 2940);
    lw(v1, a0, 8);
    if (a1 != v1) {
    L_002e4b58:
        charge(ctx, 11);
        lw(v0, a0, 8);
        sw(v0, a2, 2940);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v0, gbtl8::kShotCut);
        a0 = addiu(sp, 0x50);
        a1 = addiu(s2, shot::kPoint);
        jal(ctx, 0x2E4B70u, gen::fn_sub_2A4470_002a4470);
        lbu(v0, s1, unit::kSide);
        if (v0 == 0) {
            // 0x002e4b84
            charge(ctx, 113);
            a0 = 2;
            a1 = 1;
            a2 = addiu(sp, 0xC0);
            a3 = 0;
            t0 = 0;
            t1 = a1;
            jal(ctx, 0x2E4B9Cu, gen::fn_sub_280870_00280870);
            a0 = s1;
            a1 = addiu(sp, 0xB0);
            jal(ctx, 0x2E4BACu, gen::fn_sub_27FFB0_0027ffb0);
            mtc1(zero, f2);
            sw(zero, sp, 0xB4);
            sw(zero, sp, 0xC4);
            lwc1(f1, sp, 0xB0);
            lwc1(f0, sp, 0xC0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x90);
            sub_s(f0, f2, f2);
            swc1(f0, sp, 0x94);
            lwc1(f1, sp, 0xB8);
            lwc1(f0, sp, 0xC8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x98);
            a0 = addiu(sp, 0x90);
            a1 = a0;
            jal(ctx, 0x2E4BF0u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f1, gp, -32672);  // 0x7CAD50
            mul_s(f1, f1, f0);
            lwc1(f0, sp, 0x90);
            mul_s(f3, f0, f1);
            lwc1(f0, sp, 0x94);
            mul_s(f2, f0, f1);
            lwc1(f0, sp, 0x98);
            mul_s(f1, f0, f1);
            lwc1(f0, sp, 0xC0);
            add_s(f0, f0, f3);
            swc1(f0, sp, 0xC0);
            lwc1(f0, sp, 0xC4);
            add_s(f0, f0, f2);
            swc1(f0, sp, 0xC4);
            lwc1(f0, sp, 0xC8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC8);
            lwc1(f0, sp, 0xB0);
            swc1(f0, sp, 0xA0);
            lwc1(f1, s1, unit4::kHeight);
            lwc1(f0, s1, unit::kScale);
            mul_s(f3, f1, f0);
            lwc1(f2, gp, -32668);  // 0x7CAD54
            lwc1(f1, sp, 0xA4);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f2, f3);
            swc1(f0, sp, 0xA4);
            lwc1(f0, sp, 0xB8);
            swc1(f0, sp, 0xA8);
            a0 = addiu(sp, 0x78);
            a1 = addiu(sp, 0xA0);
            a2 = addiu(sp, 0xC0);
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E4C88u, gen::fn_sub_2A4690_002a4690);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            lwc1(f0, s2, 184);
            mul_s(f12, f1, f0);
            jal(ctx, 0x2E4CA0u, gen::fn_tanf_0052e930);
            v0 = 0x40B00000;
            mtc1(v0, f1);
            mul_s(f1, f1, f20);
            div_s(f20, f1, f0);
            lwc1(f1, sp, 0xA0);
            lwc1(f0, sp, 0xC0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x90);
            lwc1(f1, sp, 0xA4);
            lwc1(f0, sp, 0xC4);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x94);
            lwc1(f1, sp, 0xA8);
            lwc1(f0, sp, 0xC8);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x98);
            a0 = addiu(sp, 0x90);
            a1 = a0;
            jal(ctx, 0x2E4CF4u, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f1, sp, 0x90);
            lwc1(f0, sp, 0xA0);
            mtc1(zero, f2);
            adda_s(f2, f0);
            madd_s(f0, f1, f20);
            swc1(f0, sp, 0x6C);
            lwc1(f1, sp, 0x94);
            lwc1(f0, sp, 0xA4);
            adda_s(f2, f0);
            madd_s(f0, f1, f20);
            swc1(f0, sp, 0x70);
            lwc1(f1, sp, 0x98);
            lwc1(f0, sp, 0xA8);
            adda_s(f2, f0);
            madd_s(f0, f1, f20);
            swc1(f0, sp, 0x74);
            goto L_002e4e00;
        }
        // 0x002e4d48
        charge(ctx, 6);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kSetupEnemies);
        lhu(v1, v0, kGenusEncounter);
        v0 = 436;
        if (v1 == v0) {
            // 0x002e4d60
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x2E4D64u, gen::fn_sub_2F6330_002f6330);
            if (v0 == 0) {
                goto L_002e4d74;
            }
            // 0x002e4f30 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xD0);
            return;
        }
    L_002e4d74:
        charge(ctx, 27);
        a0 = 2;
        a1 = 1;
        a2 = addiu(sp, 0xB0);
        a3 = addiu(sp, 0xCC);
        t0 = 0;
        t1 = a1;
        jal(ctx, 0x2E4D8Cu, gen::fn_sub_280870_00280870);
        a0 = s1;
        a1 = addiu(sp, 0xC0);
        jal(ctx, 0x2E4D9Cu, gen::fn_sub_280130_00280130);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        swc1(f0, sp, 0x74);
        lwc1(f1, sp, 0xCC);
        v0 = 0x3FA00000;
        mtc1(v0, f0);
        mul_s(f1, f0, f1);
        lwc1(f0, sp, 0x70);
        c_lt_s(f0, f1);
        if (cond(ctx)) {
            // 0x002e4de0
            charge(ctx, 1);
            swc1(f1, sp, 0x70);
        }
        // 0x002e4de4
        charge(ctx, 7);
        a0 = addiu(sp, 0x78);
        a1 = addiu(sp, 0x6C);
        a2 = addiu(sp, 0xC0);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E4DF8u, gen::fn_sub_2A4690_002a4690);
    L_002e4e00:
        charge(ctx, 8);
        a0 = addiu(sp, 0x5C);
        a1 = addiu(sp, 0x78);
        jal(ctx, 0x2E4E08u, gen::fn_sub_2D1F30_002d1f30);
        lwc1(f1, gp, -32664);  // 0x7CAD58
        c_le_s(f0, f1);
        if (!cond(ctx)) {
            // 0x002e4e20
            charge(ctx, 3);
            v1 = 1;
            if (s0 != v1) {
                goto L_002e4eac;
            }
            // 0x002e4e2c
            charge(ctx, 3);
            lbu(v0, s1, unit::kSide);
            if (v0 == v1) {
                // 0x002e4e38
                charge(ctx, 5);
                lw(a0, s1, unit::kDat);
                jal(ctx, 0x2E4E3Cu, gen::fn_sub_30C3A0_0030c3a0);
                if (v0 == 0) {
                    goto L_002e4e70;
                }
                // 0x002e4e4c
                charge(ctx, 9);
                v0 = 0x40100000;
                mtc1(v0, f12);
                v0 = 0x40000000;
                mtc1(v0, f13);
                a0 = s2;
                jal(ctx, 0x2E4E60u, gen::fn_sub_2B6070_002b6070);
                goto L_002e4e7c;
            }
        L_002e4e70:
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x2E4E74u, gen::fn_sub_2B6460_002b6460);
        L_002e4e7c:
            charge(ctx, 12);
            mtc1(zero, f12);
            lw(a0, s2, shot::kAction);
            a1 = 0;
            a2 = 0;
            a3 = 8;
            jal(ctx, 0x2E4E90u, gen::fn_sub_2A3E80_002a3e80);
            a0 = 1;
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(a0, v1, gbtl8::kShotCut);
            // 0x002e4f30 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            lwc1(f20, sp, 0x0);
            sp = addiu(sp, 0xD0);
            return;
        }
    L_002e4eac:
        charge(ctx, 7);
        lwc1(f1, sp, 0x54);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x002e4ec8
            charge(ctx, 1);
            swc1(f0, sp, 0x54);
        }
        // 0x002e4ecc
        charge(ctx, 7);
        lwc1(f1, sp, 0x70);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x002e4ee8
            charge(ctx, 1);
            swc1(f0, sp, 0x70);
        }
        // 0x002e4eec
        charge(ctx, 8);
        a0 = s2;
        a1 = addiu(sp, 0x50);
        a2 = addiu(sp, 0x6C);
        a3 = 1;
        jal(ctx, 0x2E4EFCu, gen::fn_sub_2A2290_002a2290);
        if (s0 == 0) {
            // 0x002e4f1c
            charge(ctx, 2);
            v0 = 0x3FA00000;
            mtc1(v0, f12);
        } else {
            // 0x002e4f0c
            charge(ctx, 4);
            v0 = 0x40200000;
            mtc1(v0, f12);
        }
        // 0x002e4f24
        charge(ctx, 3);
        a0 = s2;
        jal(ctx, 0x2E4F28u, gen::fn_sub_2A3110_002a3110);
    } else {
        // 0x002e4b2c
        charge(ctx, 3);
        lw(v1, a2, 2944);
        if (v1 != 0) {
            // 0x002e4b38
            charge(ctx, 6);
            mtc1(zero, f12);
            a1 = 0;
            a2 = 0;
            a3 = 8;
            jal(ctx, 0x2E4B48u, gen::fn_sub_2A3E80_002a3e80);
        }
        // 0x002e4b50
        charge(ctx, 2);
    }
    // 0x002e4f30 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x002E4F50 sub_2E4F50 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shot update: sub_2A54F0(shot, cut allowed, 10, 10), the cut allowed as in sub_2E4A40 or when sub_308A50 accepts
// the action's +114 word.
// Arguments: a0 the camera shot.
void sub_2E4F50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e4f50
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, shot::kAction);
    if (a0 != 0) {
        // 0x002e4f7c
        charge(ctx, 4);
        lw(v0, a0, act::kUnit);
        lbu(v0, v0, unit::kSide);
        if (v0 != 0) {
            // 0x002e4fc0
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v1, v0, gbtl::kCameraState);
            v0 = 31;
            if (v1 != v0) {
                // 0x002e4fd4
                charge(ctx, 3);
                v0 = 18;
                if (v1 == v0) {
                    goto L_002e4fe8;
                }
                // 0x002e4fe0
                charge(ctx, 2);
            L_002e4ff4:
                charge(ctx, 1);
                s1 = 1;
                goto L_002e4ff8;
            }
        L_002e4fe8:
            charge(ctx, 3);
            s1 = 0;
        } else {
            // 0x002e4f8c
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v1, v0, gbtl::kCameraState);
            v0 = 29;
            if (v1 != v0) {
                // 0x002e4fa0
                charge(ctx, 3);
                v0 = 28;
                if (v1 == v0) {
                    goto L_002e4fb4;
                }
                // 0x002e4fac
                charge(ctx, 2);
                goto L_002e4ff4;
            }
        L_002e4fb4:
            charge(ctx, 3);
            s1 = 0;
        }
    } else {
        // 0x002e4f70
        charge(ctx, 3);
        s1 = 1;
    }
L_002e4ff8:
    charge(ctx, 5);
    lhu(a0, a0, 114);
    jal(ctx, 0x2E4FFCu, gen::fn_sub_308A50_00308a50);
    if (v0 != 0) {
        // 0x002e500c
        charge(ctx, 1);
        s1 = 1;
    }
    // 0x002e5010
    charge(ctx, 12);
    a0 = s0;
    a1 = s1;
    a2 = 10;
    a3 = a2;
    jal(ctx, 0x2E5020u, gen::fn_sub_2A54F0_002a54f0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E5060 sub_2E5060 -- 2104 bytes; frame 0x160: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Attacker shot: for encounter 436 sub_2F6510 may take it. Frames the attacker (sub_27FFB0); a party attacker
// sub_30C3A0 accepts (and not ids 272 / 267 in sub_282C30 state 4) at a quarter of its height, with random angles
// (datCalcRand, sub_357FD0), the target side's mask (btlTargetGetSideMask) and the rotations of sub_4BE1E0 /
// sub_4BE310 / sub_4C31B0 / sub_4C6C60; moves or cuts the camera as sub_2E4A40 does.
// Arguments: a0 the camera shot.
void sub_2E5060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x002e5060
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(v1, v0, kGenusEncounter);
    v0 = 436;
    if (v1 == v0) {
        // 0x002e509c
        charge(ctx, 4);
        jal(ctx, 0x2E509Cu, gen::fn_sub_2F6510_002f6510);
        if (v0 == 0) {
            goto L_002e50ac;
        }
        // 0x002e5870 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x160);
        return;
    }
L_002e50ac:
    charge(ctx, 3);
    lw(a0, s2, shot::kAction);
    if (a0 != 0) {
        // 0x002e50c4
        charge(ctx, 4);
        lw(v0, a0, act::kUnit);
        lbu(v0, v0, unit::kSide);
        if (v0 != 0) {
            // 0x002e5108
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v1, v0, gbtl::kCameraState);
            v0 = 31;
            if (v1 != v0) {
                // 0x002e511c
                charge(ctx, 3);
                v0 = 18;
                if (v1 == v0) {
                    goto L_002e5130;
                }
                // 0x002e5128
                charge(ctx, 2);
            L_002e513c:
                charge(ctx, 1);
                s0 = 1;
                goto L_002e5140;
            }
        L_002e5130:
            charge(ctx, 3);
            s0 = 0;
        } else {
            // 0x002e50d4
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v1, v0, gbtl::kCameraState);
            v0 = 29;
            if (v1 != v0) {
                // 0x002e50e8
                charge(ctx, 3);
                v0 = 28;
                if (v1 == v0) {
                    goto L_002e50fc;
                }
                // 0x002e50f4
                charge(ctx, 2);
                goto L_002e513c;
            }
        L_002e50fc:
            charge(ctx, 3);
            s0 = 0;
        }
    } else {
        // 0x002e50b8
        charge(ctx, 3);
        s0 = 1;
    }
L_002e5140:
    charge(ctx, 12);
    lw(s1, a0, act::kUnit);
    a0 = s1;
    a1 = addiu(sp, 0x120);
    jal(ctx, 0x2E514Cu, gen::fn_sub_27FFB0_0027ffb0);
    lw(v0, s2, shot::kAction);
    lw(v0, v0, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2E5160u, gen::fn_sub_30C3A0_0030c3a0);
    if (v0 != 0) {
        // 0x002e5170
        charge(ctx, 3);
        v0 = 1;
        if (s0 != v0) {
            goto L_002e55f0;
        }
        // 0x002e517c
        charge(ctx, 4);
        lhu(v1, s1, unit::kId);
        v0 = 272;
        if (v1 != v0) {
            // 0x002e518c
            charge(ctx, 3);
            v0 = 267;
            if (v1 == v0) {
                goto L_002e51a0;
            }
            // 0x002e5198
            charge(ctx, 2);
        L_002e51cc:
            charge(ctx, 1);
            s0 = 0;
            goto L_002e51d0;
        }
    L_002e51a0:
        charge(ctx, 8);
        a0 = s1;
        jal(ctx, 0x2E51A4u, gen::fn_sub_282C30_00282c30);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = 4;
        if (v1 == v0) {
            goto L_002e51cc;
        }
        // 0x002e51c0
        charge(ctx, 3);
        s0 = 1;
    L_002e51d0:
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x002e51d8
            charge(ctx, 11);
            lwc1(f1, s1, unit4::kHeight);
            lwc1(f0, s1, unit::kScale);
            mul_s(f3, f1, f0);
            v0 = 0x3E800000;
            mtc1(v0, f2);
            lwc1(f1, sp, 0x124);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f2, f3);
            swc1(f0, sp, 0x124);
        }
        // 0x002e5204
        charge(ctx, 5);
        lw(a0, s2, shot::kAction);
        jal(ctx, 0x2E5208u, gen::fn_sub_2D6290_002d6290);
        if (v0 == 0) {
            // 0x002e5238
            charge(ctx, 12);
            lw(v0, s2, shot::kAction);
            a0 = addiu(v0, 56);
            jal(ctx, 0x2E5240u, gen::fn_btlTargetGetSideMask_002d1600);
            a0 = v0 & 0xFFFF;
            a1 = 1;
            a2 = addiu(sp, 0x110);
            a3 = 0;
            t0 = 0;
            t1 = a1;
            jal(ctx, 0x2E5260u, gen::fn_sub_280870_00280870);
        } else {
            // 0x002e5218
            charge(ctx, 8);
            lw(v0, s2, shot::kAction);
            lw(v0, v0, act::kTargets);
            lw(a0, v0, act::kUnit);
            a1 = addiu(sp, 0x110);
            jal(ctx, 0x2E5228u, gen::fn_sub_27FFB0_0027ffb0);
        }
        // 0x002e5268
        charge(ctx, 14);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(sp, 0x120);
        a2 = addiu(sp, 0x110);
        jal(ctx, 0x2E5274u, gen::fn_sub_2D1DE0_002d1de0);
        a0 = addiu(sp, 0x140);
        a1 = 0x690000;
        a1 = addiu(a1, 30864);  // &0x697890
        a2 = 1;
        a3 = addiu(sp, 0xC0);
        jal(ctx, 0x2E5290u, gen::fn_sub_4BE1E0_004be1e0);
        if (s0 == 0) {
            // 0x002e52d4
            charge(ctx, 7);
            lwc1(f1, s1, unit::kScale);
            lwc1(f0, s1, unit::kRadius);
            mul_s(f1, f0, f1);
            lwc1(f0, gp, -32552);  // 0x7CADC8
            mul_s(f22, f0, f1);
            lwc1(f0, gp, -32548);  // 0x7CADCC
            mul_s(f20, f0, f1);
        } else {
            // 0x002e52a0
            charge(ctx, 13);
            lwc1(f1, s1, unit::kScale);
            lwc1(f0, s1, unit::kRadius);
            mul_s(f1, f0, f1);
            v0 = 0x40300000;
            mtc1(v0, f0);
            mul_s(f22, f0, f1);
            v0 = 0x40100000;
            mtc1(v0, f0);
            mul_s(f20, f0, f1);
        }
        // 0x002e52f0
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x002e5330
            charge(ctx, 6);
            a0 = 3;
            jal(ctx, 0x2E5334u, gen::fn_datCalcRand_002ffbc0);
            v1 = 1;
            if (v0 == v1) {
                // 0x002e5368
                charge(ctx, 4);
                v0 = lui(0xC1F0);
                mtc1(v0, f21);
            } else {
                // 0x002e5348
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002e5358
                    charge(ctx, 4);
                    v0 = 0x41F00000;
                    mtc1(v0, f21);
                } else {
                    // 0x002e5350
                    charge(ctx, 2);
                    // 0x002e5378
                    charge(ctx, 1);
                    mtc1(zero, f21);
                }
            }
        } else {
            // 0x002e52f8
            charge(ctx, 6);
            a0 = 0;
            jal(ctx, 0x2E52FCu, gen::fn_sub_357FD0_00357fd0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x002e5320
                charge(ctx, 2);
                v0 = lui(0xC1F0);
                mtc1(v0, f21);
            } else {
                // 0x002e5310
                charge(ctx, 4);
                v0 = 0x41F00000;
                mtc1(v0, f21);
            }
            // 0x002e5328
            charge(ctx, 2);
        }
        // 0x002e537c
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x002e5394
            charge(ctx, 6);
            a0 = 3;
            jal(ctx, 0x2E5398u, gen::fn_datCalcRand_002ffbc0);
            v1 = 1;
            if (v0 == v1) {
                // 0x002e53cc
                charge(ctx, 4);
                v0 = lui(0xC170);
                mtc1(v0, f12);
            } else {
                // 0x002e53ac
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002e53bc
                    charge(ctx, 4);
                    v0 = 0x41700000;
                    mtc1(v0, f12);
                } else {
                    // 0x002e53b4
                    charge(ctx, 2);
                    // 0x002e53dc
                    charge(ctx, 1);
                    mtc1(zero, f12);
                }
            }
        } else {
            // 0x002e5384
            charge(ctx, 4);
            v0 = lui(0xC220);
            mtc1(v0, f12);
        }
        // 0x002e53e0
        charge(ctx, 110);
        a0 = addiu(sp, 0xD0);
        a1 = 0x690000;
        a1 = addiu(a1, 30832);  // &0x697870
        a2 = 0;
        jal(ctx, 0x2E53F0u, gen::fn_sub_4C31B0_004c31b0);
        a0 = addiu(sp, 0xD0);
        a1 = 0x690000;
        a1 = addiu(a1, 30848);  // &0x697880
        mov_s(f12, f21);
        a2 = 2;
        jal(ctx, 0x2E540Cu, gen::fn_sub_4C31B0_004c31b0);
        a0 = addiu(sp, 0x150);
        a1 = addiu(sp, 0x140);
        a2 = addiu(sp, 0xD0);
        jal(ctx, 0x2E5420u, gen::fn_sub_4C6C60_004c6c60);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        lwc1(f0, s2, 184);
        mul_s(f1, f1, f0);
        lwc1(f0, gp, -32656);  // 0x7CAD60
        mul_s(f12, f0, f1);
        jal(ctx, 0x2E5440u, gen::fn_tanf_0052e930);
        div_s(f1, f22, f0);
        lwc1(f0, sp, 0x150);
        mul_s(f5, f0, f1);
        swc1(f5, sp, 0x150);
        lwc1(f0, sp, 0x154);
        mul_s(f4, f0, f1);
        swc1(f4, sp, 0x154);
        lwc1(f0, sp, 0x158);
        mul_s(f3, f0, f1);
        swc1(f3, sp, 0x158);
        lwc1(f0, sp, 0x120);
        swc1(f0, sp, 0x130);
        lwc1(f2, sp, 0x124);
        swc1(f2, sp, 0x134);
        lwc1(f1, sp, 0x128);
        swc1(f1, sp, 0x138);
        add_s(f0, f0, f5);
        swc1(f0, sp, 0x80);
        add_s(f0, f2, f4);
        swc1(f0, sp, 0x84);
        add_s(f0, f1, f3);
        swc1(f0, sp, 0x88);
        a0 = addiu(sp, 0x8C);
        a1 = addiu(sp, 0x80);
        a2 = addiu(sp, 0x130);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E54BCu, gen::fn_sub_2A4690_002a4690);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        lwc1(f0, s2, 184);
        mul_s(f1, f1, f0);
        lwc1(f0, gp, -32656);  // 0x7CAD60
        mul_s(f12, f0, f1);
        jal(ctx, 0x2E54DCu, gen::fn_tanf_0052e930);
        div_s(f1, f20, f0);
        lwc1(f0, sp, 0x140);
        mul_s(f5, f0, f1);
        swc1(f5, sp, 0x150);
        lwc1(f0, sp, 0x144);
        mul_s(f4, f0, f1);
        swc1(f4, sp, 0x154);
        lwc1(f0, sp, 0x148);
        mul_s(f3, f0, f1);
        swc1(f3, sp, 0x158);
        lwc1(f0, sp, 0x120);
        swc1(f0, sp, 0x130);
        lwc1(f2, sp, 0x124);
        swc1(f2, sp, 0x134);
        lwc1(f1, sp, 0x128);
        swc1(f1, sp, 0x138);
        add_s(f0, f0, f5);
        swc1(f0, sp, 0x9C);
        add_s(f0, f2, f4);
        swc1(f0, sp, 0xA0);
        add_s(f0, f1, f3);
        swc1(f0, sp, 0xA4);
        a0 = addiu(sp, 0xA8);
        a1 = addiu(sp, 0x9C);
        a2 = addiu(sp, 0x130);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E5558u, gen::fn_sub_2A4690_002a4690);
        mtc1(zero, f12);
        lw(a0, s2, shot::kAction);
        a1 = 0;
        a2 = 0;
        a3 = 1;
        jal(ctx, 0x2E5574u, gen::fn_sub_2A3E80_002a3e80);
        lwc1(f1, sp, 0x84);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x002e5598
            charge(ctx, 1);
            swc1(f0, sp, 0x84);
        }
        // 0x002e559c
        charge(ctx, 7);
        lwc1(f1, sp, 0xA0);
        v0 = 0x41C80000;
        mtc1(v0, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x002e55b8
            charge(ctx, 1);
            swc1(f0, sp, 0xA0);
        }
        // 0x002e55bc
        charge(ctx, 13);
        a0 = s2;
        a1 = addiu(sp, 0x80);
        a2 = addiu(sp, 0x9C);
        a3 = 1;
        jal(ctx, 0x2E55CCu, gen::fn_sub_2A2290_002a2290);
        v0 = 0x40400000;
        mtc1(v0, f12);
        a0 = s2;
        jal(ctx, 0x2E55E0u, gen::fn_sub_2A3110_002a3110);
        // 0x002e5870 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f22, sp, 0x8);
        lwc1(f21, sp, 0x4);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x160);
        return;
    }
L_002e55f0:
    charge(ctx, 25);
    lwc1(f1, s1, unit4::kHeight);
    lwc1(f0, s1, unit::kScale);
    mul_s(f3, f1, f0);
    lwc1(f2, gp, -32720);  // 0x7CAD20
    lwc1(f1, sp, 0x124);
    mtc1(zero, f0);
    adda_s(f0, f1);
    msub_s(f0, f2, f3);
    swc1(f0, sp, 0x124);
    a0 = 2;
    jal(ctx, 0x2E561Cu, gen::fn_datCalcRand_002ffbc0);
    v1 = sll(v0, 1);
    v1 = addu(v1, v0);
    v1 = sll(v1, 2);
    v0 = addu(v1, v0);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl4::kBossAiRows);
    v0 = addu(v0, v1);
    s1 = addiu(v0, 420);
    v0 = 1;
    if (s0 != v0) {
        // 0x002e5694
        charge(ctx, 5);
        a0 = addiu(sp, 0x80);
        a1 = addiu(s2, shot::kPoint);
        jal(ctx, 0x2E569Cu, gen::fn_sub_2A4470_002a4470);
        s0 = 0;
    } else {
        // 0x002e5654
        charge(ctx, 16);
        a0 = addiu(sp, 0x8C);
        a1 = addiu(s1, 4);
        a2 = addiu(s1, 16);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E5668u, gen::fn_sub_2A4690_002a4690);
        lwc1(f2, s1, 4);
        lwc1(f1, s1, 8);
        lwc1(f0, s1, 12);
        swc1(f2, sp, 0x80);
        swc1(f1, sp, 0x84);
        swc1(f0, sp, 0x88);
        s0 = 1;
    }
    // 0x002e56a8
    charge(ctx, 23);
    a0 = addiu(sp, 0xA8);
    a1 = addiu(sp, 0x80);
    a2 = addiu(sp, 0x120);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E56BCu, gen::fn_sub_2A4690_002a4690);
    lwc1(f2, sp, 0x80);
    lwc1(f1, sp, 0x84);
    lwc1(f0, sp, 0x88);
    swc1(f2, sp, 0x9C);
    swc1(f1, sp, 0xA0);
    swc1(f0, sp, 0xA4);
    a0 = addiu(sp, 0x8C);
    a1 = addiu(sp, 0xA8);
    a2 = addiu(sp, 0x50);
    jal(ctx, 0x2E56E8u, gen::fn_sub_4BE310_004be310);
    lwc1(f1, gp, -32628);  // 0x7CAD7C
    lwc1(f0, gp, -32544);  // 0x7CADD0
    lw(v0, sp, 0x74);
    if (v0 == 0) {
        // 0x002e5704
        charge(ctx, 39);
        lwc1(f12, sp, 0x70);
        mul_s(f4, f1, f12);
        mul_s(f3, f4, f4);
        lwc1(f11, gp, -32700);  // 0x7CAD34
        lwc1(f10, gp, -32696);  // 0x7CAD38
        mtc1(zero, f9);
        adda_s(f9, f10);
        madd_s(f1, f11, f3);
        lwc1(f8, gp, -32692);  // 0x7CAD3C
        adda_s(f9, f8);
        madd_s(f1, f3, f1);
        lwc1(f7, gp, -32688);  // 0x7CAD40
        adda_s(f9, f7);
        madd_s(f1, f3, f1);
        lwc1(f6, gp, -32684);  // 0x7CAD44
        adda_s(f9, f6);
        madd_s(f1, f3, f1);
        lwc1(f5, gp, -32680);  // 0x7CAD48
        adda_s(f9, f5);
        madd_s(f2, f3, f1);
        mul_s(f1, f3, f4);
        adda_s(f9, f4);
        madd_s(f1, f1, f2);
        mul_s(f4, f0, f12);
        mul_s(f3, f4, f4);
        adda_s(f9, f10);
        madd_s(f0, f11, f3);
        adda_s(f9, f8);
        madd_s(f0, f3, f0);
        adda_s(f9, f7);
        madd_s(f0, f3, f0);
        adda_s(f9, f6);
        madd_s(f0, f3, f0);
        adda_s(f9, f5);
        madd_s(f2, f3, f0);
        mul_s(f0, f3, f4);
        adda_s(f9, f4);
        madd_s(f0, f0, f2);
    }
    // 0x002e57a0
    charge(ctx, 38);
    lwc1(f2, sp, 0x50);
    mul_s(f6, f2, f1);
    swc1(f6, sp, 0xC0);
    lwc1(f2, sp, 0x54);
    mul_s(f5, f2, f1);
    swc1(f5, sp, 0xC4);
    lwc1(f2, sp, 0x58);
    mul_s(f4, f2, f1);
    swc1(f4, sp, 0xC8);
    lwc1(f2, sp, 0x60);
    mtc1(zero, f3);
    adda_s(f3, f6);
    madd_s(f2, f2, f0);
    swc1(f2, sp, 0xC0);
    lwc1(f2, sp, 0x64);
    adda_s(f3, f5);
    madd_s(f2, f2, f0);
    swc1(f2, sp, 0xC4);
    lwc1(f2, sp, 0x68);
    adda_s(f3, f4);
    madd_s(f2, f2, f0);
    swc1(f2, sp, 0xC8);
    lwc1(f3, sp, 0x5C);
    lwc1(f2, sp, 0x6C);
    mula_s(f2, f0);
    madd_s(f0, f3, f1);
    swc1(f0, sp, 0xCC);
    lwc1(f3, sp, 0xC0);
    lwc1(f2, sp, 0xC4);
    lwc1(f1, sp, 0xC8);
    lwc1(f0, sp, 0xCC);
    swc1(f3, sp, 0xA8);
    swc1(f2, sp, 0xAC);
    swc1(f1, sp, 0xB0);
    swc1(f0, sp, 0xB4);
    if (s0 != 0) {
        // 0x002e5838
        charge(ctx, 3);
        a0 = 8;
        jal(ctx, 0x2E583Cu, gen::fn_sub_351BB0_00351bb0);
    }
    // 0x002e5844
    charge(ctx, 11);
    a0 = s2;
    a1 = addiu(sp, 0x80);
    a2 = addiu(sp, 0x9C);
    a3 = 1;
    jal(ctx, 0x2E5854u, gen::fn_sub_2A2290_002a2290);
    v0 = 0x40000000;
    mtc1(v0, f12);
    a0 = s2;
    jal(ctx, 0x2E5868u, gen::fn_sub_2A3110_002a3110);
    // 0x002e5870 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x002E58A0 sub_2E58A0 -- 2184 bytes; frame 0x180: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Enemy actor shot: an enemy action first turns its party targets (sub_27FCF0); a party first target is framed
// from behind the actor (sub_27FCF0 / sub_280050 look points, sub_2D1FD0 / sub_2D1F30 distances, tanf); some cases take
// a random boss-row shot instead (sub_2E8E20 / sub_2E8F40).
// Arguments: a0 the camera shot.
void sub_2E58A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x002e58a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    lw(a0, a0, shot::kAction);
    if (a0 != 0) {
        // 0x002e58e0
        charge(ctx, 4);
        lw(s0, a0, act::kUnit);
        lbu(v0, s0, unit::kSide);
        if (v0 == 0) {
            // 0x002e58f0
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x002e5934
                charge(ctx, 6);
                lw(a0, s4, shot::kAction);
                v1 = s1 & 0xFFFF;
                lhu(v0, a0, act::kTargetCount);
                v0 = slt(v1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002e58fc
                charge(ctx, 9);
                v0 = s1 & 0xFFFF;
                v0 = sll(v0, 2);
                v0 = addu(a0, v0);
                lw(v0, v0, act::kTargets);
                lw(a0, v0, act::kUnit);
                lbu(v1, a0, unit::kSide);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002e5920
                    charge(ctx, 3);
                    a1 = addiu(s0, 4);
                    jal(ctx, 0x2E5924u, gen::fn_sub_27FCF0_0027fcf0);
                }
                // 0x002e592c
                charge(ctx, 2);
                v0 = addiu(s1, 1);
                s1 = v0 & 0xFFFF;
            }
        }
    }
    // 0x002e594c
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x002e5960
        charge(ctx, 4);
        lw(v0, a0, act::kUnit);
        lbu(v0, v0, unit::kSide);
        if (v0 != 0) {
            // 0x002e59a4
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v1, v0, gbtl::kCameraState);
            v0 = 31;
            if (v1 != v0) {
                // 0x002e59b8
                charge(ctx, 3);
                v0 = 18;
                if (v1 == v0) {
                    goto L_002e59cc;
                }
                // 0x002e59c4
                charge(ctx, 2);
            L_002e59d8:
                charge(ctx, 1);
                s0 = 1;
                goto L_002e59dc;
            }
        L_002e59cc:
            charge(ctx, 3);
            s0 = 0;
        } else {
            // 0x002e5970
            charge(ctx, 5);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v1, v0, gbtl::kCameraState);
            v0 = 29;
            if (v1 != v0) {
                // 0x002e5984
                charge(ctx, 3);
                v0 = 28;
                if (v1 == v0) {
                    goto L_002e5998;
                }
                // 0x002e5990
                charge(ctx, 2);
                goto L_002e59d8;
            }
        L_002e5998:
            charge(ctx, 3);
            s0 = 0;
        }
    } else {
        // 0x002e5954
        charge(ctx, 3);
        s0 = 1;
    }
L_002e59dc:
    charge(ctx, 4);
    lw(s2, a0, act::kUnit);
    lbu(v0, s2, unit::kSide);
    if (v0 != 0) {
        // 0x002e5a0c
        charge(ctx, 5);
        lw(v0, s4, shot::kAction);
        lw(v0, v0, act::kTargets);
        lw(s3, v0, act::kUnit);
        s1 = 1;
        s5 = 0;
    } else {
        // 0x002e59ec
        charge(ctx, 8);
        lw(v0, s4, shot::kAction);
        s3 = s2;
        lw(v0, v0, act::kTargets);
        lw(s2, v0, act::kUnit);
        s1 = 0;
        s5 = 1;
    }
    // 0x002e5a20
    charge(ctx, 4);
    lbu(a0, s3, unit::kSide);
    lbu(v0, s2, unit::kSide);
    if (a0 != v0) {
        // 0x002e5a60
        charge(ctx, 6);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v0, gbtl::kSetupEnemies);
        lhu(v1, v0, kGenusEncounter);
        v0 = 436;
        if (v1 != v0) {
            // 0x002e5a78
            charge(ctx, 2);
            goto L_002e5b74;
        }
        // 0x002e5a80
        charge(ctx, 2);
        if (a0 != 0) {
        L_002e5b74:
            charge(ctx, 85);
            a0 = addiu(sp, 0xE0);
            a1 = addiu(s4, shot::kPoint);
            jal(ctx, 0x2E5B7Cu, gen::fn_sub_2A4470_002a4470);
            a0 = s3;
            a1 = addiu(sp, 0x170);
            jal(ctx, 0x2E5B8Cu, gen::fn_sub_280050_00280050);
            a0 = s2;
            a1 = addiu(sp, 0x160);
            jal(ctx, 0x2E5B9Cu, gen::fn_sub_280050_00280050);
            lwc1(f1, s3, unit::kScale);
            lwc1(f0, s3, unit::kRadius);
            mul_s(f22, f0, f1);
            lwc1(f5, sp, 0x174);
            lwc1(f0, s3, unit4::kHeight);
            mul_s(f0, f0, f1);
            v0 = 0x3F000000;
            mtc1(v0, f4);
            mtc1(zero, f3);
            adda_s(f3, f5);
            madd_s(f21, f4, f0);
            lwc1(f2, sp, 0x164);
            lwc1(f1, s2, unit4::kHeight);
            lwc1(f0, s2, unit::kScale);
            mul_s(f0, f1, f0);
            adda_s(f3, f2);
            madd_s(f20, f4, f0);
            lwc1(f1, sp, 0x170);
            lwc1(f0, sp, 0x160);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            sub_s(f0, f5, f2);
            swc1(f0, sp, 0x134);
            lwc1(f1, sp, 0x178);
            lwc1(f0, sp, 0x168);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x138);
            a0 = addiu(sp, 0x130);
            a1 = a0;
            jal(ctx, 0x2E5C1Cu, gen::fn_sub_4C69F0_004c69f0);
            lwc1(f1, gp, -32620);  // 0x7CAD84
            mul_s(f1, f1, f0);
            lwc1(f0, sp, 0x130);
            mul_s(f2, f0, f1);
            swc1(f2, sp, 0x150);
            lwc1(f0, sp, 0x134);
            mul_s(f3, f0, f1);
            swc1(f3, sp, 0x154);
            lwc1(f0, sp, 0x138);
            mul_s(f1, f0, f1);
            swc1(f1, sp, 0x158);
            lwc1(f0, sp, 0x160);
            add_s(f2, f2, f0);
            swc1(f2, sp, 0x150);
            lwc1(f0, sp, 0x164);
            add_s(f0, f3, f0);
            swc1(f0, sp, 0x154);
            lwc1(f0, sp, 0x168);
            add_s(f1, f1, f0);
            swc1(f1, sp, 0x158);
            lwc1(f0, s4, 156);
            sub_s(f0, f0, f2);
            swc1(f0, sp, 0xD8);
            lwc1(f0, s4, 164);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0xDC);
            a0 = addiu(sp, 0xD8);
            a1 = a0;
            jal(ctx, 0x2E5C94u, gen::fn_sub_4C6B20_004c6b20);
            lwc1(f4, sp, 0x138);
            swc1(f4, sp, 0xD0);
            lwc1(f3, sp, 0x130);
            neg_s(f2, f3);
            swc1(f2, sp, 0xD4);
            lwc1(f1, sp, 0xD8);
            lwc1(f0, sp, 0xDC);
            mula_s(f2, f0);
            madd_s(f23, f4, f1);
            if (s1 != 0) {
                // 0x002e5ce0
                charge(ctx, 4);
                v0 = 0x40200000;
                mtc1(v0, f0);
                mul_s(f2, f0, f22);
            } else {
                // 0x002e5cc8
                charge(ctx, 6);
                v0 = 0x3FC00000;
                mtc1(v0, f0);
                mul_s(f2, f0, f22);
            }
            // 0x002e5cf0
            charge(ctx, 5);
            mtc1(zero, f1);
            c_lt_s(f23, f1);
            if (cond(ctx)) {
                // 0x002e5d2c
                charge(ctx, 8);
                lwc1(f0, sp, 0x170);
                adda_s(f1, f0);
                msub_s(f0, f4, f2);
                swc1(f0, sp, 0x140);
                lwc1(f0, sp, 0x178);
                adda_s(f1, f0);
                madd_s(f0, f3, f2);
                swc1(f0, sp, 0x148);
            } else {
                // 0x002e5d04
                charge(ctx, 10);
                lwc1(f0, sp, 0x170);
                adda_s(f1, f0);
                madd_s(f0, f4, f2);
                swc1(f0, sp, 0x140);
                lwc1(f0, sp, 0x178);
                adda_s(f1, f0);
                msub_s(f0, f3, f2);
                swc1(f0, sp, 0x148);
            }
            // 0x002e5d4c
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x002e5dcc
                charge(ctx, 12);
                swc1(f21, sp, 0x144);
                lwc1(f2, gp, -32620);  // 0x7CAD84
                lwc1(f1, sp, 0x154);
                mtc1(zero, f0);
                adda_s(f0, f1);
                msub_s(f0, f2, f20);
                swc1(f0, sp, 0x154);
                v0 = 0x40600000;
                mtc1(v0, f0);
                mul_s(f20, f0, f22);
            } else {
                // 0x002e5d54
                charge(ctx, 3);
                c_lt_s(f21, f20);
                if (!cond(ctx)) {
                    // 0x002e5d88
                    charge(ctx, 11);
                    lwc1(f2, gp, -32720);  // 0x7CAD20
                    lwc1(f0, sp, 0x174);
                    mtc1(zero, f1);
                    adda_s(f1, f0);
                    msub_s(f0, f2, f21);
                    swc1(f0, sp, 0x144);
                    lwc1(f0, sp, 0x154);
                    adda_s(f1, f0);
                    madd_s(f0, f2, f20);
                    swc1(f0, sp, 0x154);
                } else {
                    // 0x002e5d60
                    charge(ctx, 10);
                    swc1(f21, sp, 0x144);
                    lwc1(f2, gp, -32620);  // 0x7CAD84
                    lwc1(f1, sp, 0x154);
                    mtc1(zero, f0);
                    adda_s(f0, f1);
                    msub_s(f0, f2, f20);
                    swc1(f0, sp, 0x154);
                }
                // 0x002e5db4
                charge(ctx, 6);
                v0 = 0x40200000;
                mtc1(v0, f0);
                mul_s(f20, f0, f22);
            }
            // 0x002e5dfc
            charge(ctx, 62);
            a0 = addiu(sp, 0x108);
            a1 = addiu(sp, 0x140);
            a2 = addiu(sp, 0x150);
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E5E10u, gen::fn_sub_2A4690_002a4690);
            a0 = addiu(sp, 0x130);
            a1 = 0x690000;
            a1 = addiu(a1, 30880);  // &0x6978A0
            a2 = 1;
            a3 = addiu(sp, 0x108);
            jal(ctx, 0x2E5E2Cu, gen::fn_sub_4BE1E0_004be1e0);
            lwc1(f0, sp, 0x150);
            swc1(f0, sp, 0xC0);
            lwc1(f0, sp, 0x158);
            swc1(f0, sp, 0xC4);
            lwc1(f0, sp, 0x140);
            swc1(f0, sp, 0xC8);
            lwc1(f0, sp, 0x148);
            swc1(f0, sp, 0xCC);
            lwc1(f0, sp, 0x170);
            swc1(f0, sp, 0x128);
            lwc1(f0, sp, 0x178);
            swc1(f0, sp, 0x12C);
            a0 = addiu(sp, 0xC0);
            a1 = addiu(sp, 0xC8);
            a2 = addiu(sp, 0x128);
            a3 = addiu(sp, 0x120);
            jal(ctx, 0x2E5E74u, gen::fn_sub_2D1FD0_002d1fd0);
            add_s(f20, f0, f20);
            lwc1(f0, sp, 0x120);
            swc1(f0, sp, 0x140);
            lwc1(f0, sp, 0x124);
            swc1(f0, sp, 0x148);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            lwc1(f0, s4, 184);
            mul_s(f1, f1, f0);
            lwc1(f0, gp, -32656);  // 0x7CAD60
            mul_s(f12, f0, f1);
            jal(ctx, 0x2E5EA8u, gen::fn_tanf_0052e930);
            div_s(f20, f20, f0);
            lwc1(f0, sp, 0x130);
            mul_s(f0, f0, f20);
            swc1(f0, sp, 0x130);
            lwc1(f0, sp, 0x134);
            mul_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            lwc1(f0, sp, 0x138);
            mul_s(f0, f0, f20);
            swc1(f0, sp, 0x138);
            mtc1(zero, f0);
            c_lt_s(f23, f0);
            if (cond(ctx)) {
                // 0x002e5ef4
                charge(ctx, 37);
                v0 = 0x3F000000;
                mtc1(v0, f1);
                lwc1(f0, s4, 184);
                mul_s(f1, f1, f0);
                lwc1(f0, gp, -32656);  // 0x7CAD60
                mul_s(f12, f0, f1);
                jal(ctx, 0x2E5F0Cu, gen::fn_tanf_0052e930);
                mul_s(f1, f20, f0);
                v0 = 0x3E600000;
                mtc1(v0, f0);
                mul_s(f1, f1, f0);
                v0 = 0x3FA00000;
                mtc1(v0, f0);
                mul_s(f21, f1, f0);
                lwc1(f0, sp, 0x130);
                swc1(f0, sp, 0x118);
                lwc1(f0, sp, 0x138);
                swc1(f0, sp, 0x11C);
                a0 = addiu(sp, 0x118);
                a1 = a0;
                jal(ctx, 0x2E5F50u, gen::fn_sub_4C6B20_004c6b20);
                lwc1(f1, sp, 0x11C);
                lwc1(f0, sp, 0x140);
                mtc1(zero, f2);
                adda_s(f2, f0);
                madd_s(f0, f1, f21);
                swc1(f0, sp, 0x140);
                lwc1(f1, sp, 0x118);
                lwc1(f0, sp, 0x148);
                adda_s(f2, f0);
                msub_s(f0, f1, f21);
                swc1(f0, sp, 0x148);
            }
            // 0x002e5f88
            charge(ctx, 18);
            lwc1(f1, sp, 0x140);
            lwc1(f0, sp, 0x130);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xFC);
            lwc1(f1, sp, 0x144);
            lwc1(f0, sp, 0x134);
            add_s(f2, f1, f0);
            swc1(f2, sp, 0x100);
            lwc1(f1, sp, 0x148);
            lwc1(f0, sp, 0x138);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x104);
            v0 = 0x41C80000;
            mtc1(v0, f0);
            c_lt_s(f2, f0);
            if (cond(ctx)) {
                // 0x002e5fd0
                charge(ctx, 1);
                swc1(f0, sp, 0x100);
            }
            // 0x002e5fd4
            charge(ctx, 7);
            a0 = addiu(sp, 0xEC);
            a1 = addiu(sp, 0x108);
            jal(ctx, 0x2E5FDCu, gen::fn_sub_2D1F30_002d1f30);
            v0 = 1;
            if (s5 != v0) {
                // 0x002e5ff0
                charge(ctx, 4);
                lwc1(f1, gp, -32664);  // 0x7CAD58
                c_le_s(f0, f1);
                if (!cond(ctx)) {
                    goto L_002e6000;
                }
                goto L_002e60c4;
            }
        L_002e6000:
            charge(ctx, 3);
            a2 = 1;
            if (s0 == a2) {
                // 0x002e600c
                charge(ctx, 42);
                a3 = addiu(sp, 0x108);
                lwc1(f3, sp, 0x108);
                lwc1(f2, sp, 0x10C);
                lwc1(f1, sp, 0x110);
                lwc1(f0, sp, 0x114);
                swc1(f3, sp, 0xEC);
                swc1(f2, sp, 0xF0);
                swc1(f1, sp, 0xF4);
                swc1(f0, sp, 0xF8);
                a0 = addiu(sp, 0x130);
                a1 = 0x690000;
                a1 = addiu(a1, 30880);  // &0x6978A0
                jal(ctx, 0x2E603Cu, gen::fn_sub_4BE1E0_004be1e0);
                v0 = 0x43480000;
                mtc1(v0, f0);
                add_s(f2, f0, f20);
                lwc1(f0, sp, 0x130);
                mul_s(f3, f0, f2);
                swc1(f3, sp, 0x130);
                lwc1(f0, sp, 0x134);
                mul_s(f1, f0, f2);
                swc1(f1, sp, 0x134);
                lwc1(f0, sp, 0x138);
                mul_s(f2, f0, f2);
                swc1(f2, sp, 0x138);
                lwc1(f0, sp, 0x140);
                add_s(f0, f0, f3);
                swc1(f0, sp, 0xE0);
                lwc1(f0, sp, 0x144);
                add_s(f1, f0, f1);
                swc1(f1, sp, 0xE4);
                lwc1(f0, sp, 0x148);
                add_s(f0, f0, f2);
                swc1(f0, sp, 0xE8);
                v0 = 0x41C80000;
                mtc1(v0, f0);
                c_lt_s(f1, f0);
                if (cond(ctx)) {
                    // 0x002e60b4
                    charge(ctx, 1);
                    swc1(f0, sp, 0xE4);
                }
                // 0x002e60b8
                charge(ctx, 3);
                a0 = 8;
                jal(ctx, 0x2E60BCu, gen::fn_sub_351BB0_00351bb0);
            }
        L_002e60c4:
            charge(ctx, 11);
            a0 = s4;
            a1 = addiu(sp, 0xE0);
            a2 = addiu(sp, 0xFC);
            a3 = 1;
            jal(ctx, 0x2E60D4u, gen::fn_sub_2A2290_002a2290);
            v0 = 0x3FC00000;
            mtc1(v0, f12);
            a0 = s4;
            jal(ctx, 0x2E60E8u, gen::fn_sub_2A3110_002a3110);
        } else {
            // 0x002e5a88
            charge(ctx, 59);
            a0 = addiu(sp, 0x8C);
            a1 = 0x690000;
            a1 = addiu(a1, 31876);  // &0x697C84
            a2 = 0x690000;
            a2 = addiu(a2, 31888);  // &0x697C90
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E5AA4u, gen::fn_sub_2A4690_002a4690);
            v0 = 0x690000;
            lwc1(f2, v0, 31876);  // 0x697C84
            v0 = 0x690000;
            lwc1(f1, v0, 31880);  // 0x697C88
            v0 = 0x690000;
            lwc1(f0, v0, 31884);  // 0x697C8C
            swc1(f2, sp, 0x80);
            swc1(f1, sp, 0x84);
            swc1(f0, sp, 0x88);
            a0 = addiu(sp, 0xA8);
            a1 = 0x690000;
            a1 = addiu(a1, 31900);  // &0x697C9C
            a2 = 0x690000;
            a2 = addiu(a2, 31912);  // &0x697CA8
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E5AECu, gen::fn_sub_2A4690_002a4690);
            a2 = addiu(sp, 0x9C);
            v0 = 0x690000;
            lwc1(f2, v0, 31900);  // 0x697C9C
            v0 = 0x690000;
            lwc1(f1, v0, 31904);  // 0x697CA0
            v0 = 0x690000;
            lwc1(f0, v0, 31908);  // 0x697CA4
            swc1(f2, sp, 0x9C);
            swc1(f1, sp, 0xA0);
            swc1(f0, sp, 0xA4);
            v0 = 0x690000;
            lh(v0, v0, 31872);  // 0x697C80
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            div_s(f20, f1, f0);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            a0 = addiu(v0, gbtl7::kCamera);
            a1 = addiu(sp, 0x80);
            a3 = 1;
            jal(ctx, 0x2E5B50u, gen::fn_sub_2A2290_002a2290);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            a0 = addiu(v0, gbtl7::kCamera);
            mov_s(f12, f20);
            jal(ctx, 0x2E5B64u, gen::fn_sub_2A3110_002a3110);
        }
    } else {
        // 0x002e5a30
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x002e5a4c
            charge(ctx, 3);
            a0 = s4;
            jal(ctx, 0x2E5A50u, gen::fn_sub_2E8F40_002e8f40);
        } else {
            // 0x002e5a38
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x2E5A3Cu, gen::fn_sub_2E8E20_002e8e20);
        }
        // 0x002e5a58
        charge(ctx, 2);
    }
    // 0x002e60f0 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x180);
}

// 0x002E6130 sub_2E6130 -- 2288 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Two-unit look points (sub_2E6A20's helper): writes the look points of two units (sub_280130) to a2 / a3 and,
// for a party unit against an enemy or the reverse, raises each by a share of its height (+140 x +44) chosen by the
// first unit's id (a jump table on 0x101..). Returns the camera distance factor in $f0 (4.5 by default).
// Arguments: a0 btlUnit, a1 btlUnit, a2 / a3 f32[3] out.
void sub_2E6130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002e6130
    enter(ctx, 20);  // entry check point + this block's cycles
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
    a1 = s1;
    jal(ctx, 0x2E615Cu, gen::fn_sub_280130_00280130);
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x2E616Cu, gen::fn_sub_280130_00280130);
    lbu(a0, s3, unit::kSide);
    if (a0 == 0) {
        // 0x002e6180
        charge(ctx, 4);
        lbu(v1, s2, unit::kSide);
        v0 = 1;
        if (v1 != v0) {
            goto L_002e6758;
        }
        // 0x002e6190
        charge(ctx, 4);
        lhu(v0, s2, unit::kId);
        v1 = 241;
        if (v0 == v1) {
            // 0x002e66a4
            charge(ctx, 23);
            lwc1(f1, s3, unit4::kHeight);
            lwc1(f0, s3, unit::kScale);
            mul_s(f2, f1, f0);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            lwc1(f0, s1, 4);
            mtc1(zero, f3);
            adda_s(f3, f0);
            madd_s(f0, f1, f2);
            swc1(f0, s1, 4);
            lwc1(f1, s2, unit4::kHeight);
            lwc1(f0, s2, unit::kScale);
            mul_s(f2, f1, f0);
            lwc1(f1, gp, -32568);  // 0x7CADB8
            lwc1(f0, s0, 4);
            adda_s(f3, f0);
            msub_s(f0, f1, f2);
            swc1(f0, s0, 4);
            v0 = 0x40C00000;
            mtc1(v0, f0);
        } else {
            // 0x002e61a0
            charge(ctx, 3);
            v1 = 296;
            if (v0 != v1) {
                // 0x002e61ac
                charge(ctx, 3);
                v1 = 293;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e61b8
                charge(ctx, 3);
                v1 = 292;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e61c4
                charge(ctx, 3);
                v1 = 291;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e61d0
                charge(ctx, 3);
                v1 = 290;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e61dc
                charge(ctx, 3);
                v1 = 289;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e61e8
                charge(ctx, 3);
                v1 = 288;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e61f4
                charge(ctx, 3);
                v1 = 287;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e6200
                charge(ctx, 3);
                v1 = 286;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e620c
                charge(ctx, 3);
                v1 = 285;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e6218
                charge(ctx, 3);
                v1 = 284;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e6224
                charge(ctx, 3);
                v1 = 283;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e6230
                charge(ctx, 3);
                v1 = 282;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e623c
                charge(ctx, 3);
                v1 = 273;
                if (v0 == v1) {
                    goto L_002e6648;
                }
                // 0x002e6248
                charge(ctx, 3);
                v1 = 269;
                if (v0 == v1) {
                    // 0x002e65f0
                    charge(ctx, 22);
                    lwc1(f1, s3, unit4::kHeight);
                    lwc1(f0, s3, unit::kScale);
                    mul_s(f2, f1, f0);
                    lwc1(f1, gp, -32632);  // 0x7CAD78
                    lwc1(f0, s1, 4);
                    mtc1(zero, f3);
                    adda_s(f3, f0);
                    madd_s(f0, f1, f2);
                    swc1(f0, s1, 4);
                    lwc1(f1, s2, unit4::kHeight);
                    lwc1(f0, s2, unit::kScale);
                    mul_s(f2, f1, f0);
                    lwc1(f1, gp, -32720);  // 0x7CAD20
                    lwc1(f0, s0, 4);
                    adda_s(f3, f0);
                    msub_s(f0, f1, f2);
                    swc1(f0, s0, 4);
                    v0 = 0x40800000;
                    mtc1(v0, f0);
                } else {
                    // 0x002e6254
                    charge(ctx, 3);
                    v1 = 266;
                    if (v0 == v1) {
                        // 0x002e6598
                        charge(ctx, 22);
                        lwc1(f1, s3, unit4::kHeight);
                        lwc1(f0, s3, unit::kScale);
                        mul_s(f2, f1, f0);
                        lwc1(f1, gp, -32572);  // 0x7CADB4
                        lwc1(f0, s1, 4);
                        mtc1(zero, f3);
                        adda_s(f3, f0);
                        madd_s(f0, f1, f2);
                        swc1(f0, s1, 4);
                        lwc1(f1, s2, unit4::kHeight);
                        lwc1(f0, s2, unit::kScale);
                        mul_s(f2, f1, f0);
                        lwc1(f1, gp, -32620);  // 0x7CAD84
                        lwc1(f0, s0, 4);
                        adda_s(f3, f0);
                        msub_s(f0, f1, f2);
                        swc1(f0, s0, 4);
                        v0 = 0x40A00000;
                        mtc1(v0, f0);
                    } else {
                        // 0x002e6260
                        charge(ctx, 3);
                        v1 = 263;
                        if (v0 == v1) {
                            // 0x002e6540
                            charge(ctx, 22);
                            lwc1(f1, s3, unit4::kHeight);
                            lwc1(f0, s3, unit::kScale);
                            mul_s(f2, f1, f0);
                            lwc1(f1, gp, -32668);  // 0x7CAD54
                            lwc1(f0, s1, 4);
                            mtc1(zero, f3);
                            adda_s(f3, f0);
                            madd_s(f0, f1, f2);
                            swc1(f0, s1, 4);
                            lwc1(f1, s2, unit4::kHeight);
                            lwc1(f0, s2, unit::kScale);
                            mul_s(f2, f1, f0);
                            lwc1(f1, gp, -32620);  // 0x7CAD84
                            lwc1(f0, s0, 4);
                            adda_s(f3, f0);
                            msub_s(f0, f1, f2);
                            swc1(f0, s0, 4);
                            v0 = 0x40A00000;
                            mtc1(v0, f0);
                        } else {
                            // 0x002e626c
                            charge(ctx, 3);
                            v1 = 277;
                            if (v0 == v1) {
                                // 0x002e64e8
                                charge(ctx, 22);
                                lwc1(f1, s3, unit4::kHeight);
                                lwc1(f0, s3, unit::kScale);
                                mul_s(f2, f1, f0);
                                lwc1(f1, gp, -32616);  // 0x7CAD88
                                lwc1(f0, s1, 4);
                                mtc1(zero, f3);
                                adda_s(f3, f0);
                                madd_s(f0, f1, f2);
                                swc1(f0, s1, 4);
                                lwc1(f1, s2, unit4::kHeight);
                                lwc1(f0, s2, unit::kScale);
                                mul_s(f2, f1, f0);
                                lwc1(f1, gp, -32620);  // 0x7CAD84
                                lwc1(f0, s0, 4);
                                adda_s(f3, f0);
                                msub_s(f0, f1, f2);
                                swc1(f0, s0, 4);
                                v0 = 0x40900000;
                                mtc1(v0, f0);
                            } else {
                                // 0x002e6278
                                charge(ctx, 3);
                                v1 = 262;
                                if (v0 == v1) {
                                    // 0x002e6490
                                    charge(ctx, 22);
                                    lwc1(f1, s3, unit4::kHeight);
                                    lwc1(f0, s3, unit::kScale);
                                    mul_s(f2, f1, f0);
                                    lwc1(f1, gp, -32668);  // 0x7CAD54
                                    lwc1(f0, s1, 4);
                                    mtc1(zero, f3);
                                    adda_s(f3, f0);
                                    madd_s(f0, f1, f2);
                                    swc1(f0, s1, 4);
                                    lwc1(f1, s2, unit4::kHeight);
                                    lwc1(f0, s2, unit::kScale);
                                    mul_s(f2, f1, f0);
                                    lwc1(f1, gp, -32632);  // 0x7CAD78
                                    lwc1(f0, s0, 4);
                                    adda_s(f3, f0);
                                    msub_s(f0, f1, f2);
                                    swc1(f0, s0, 4);
                                    v0 = 0x40900000;
                                    mtc1(v0, f0);
                                } else {
                                    // 0x002e6284
                                    charge(ctx, 3);
                                    v1 = 261;
                                    if (v0 == v1) {
                                        // 0x002e6438
                                        charge(ctx, 22);
                                        lwc1(f1, s3, unit4::kHeight);
                                        lwc1(f0, s3, unit::kScale);
                                        mul_s(f2, f1, f0);
                                        lwc1(f1, gp, -32632);  // 0x7CAD78
                                        lwc1(f0, s1, 4);
                                        mtc1(zero, f3);
                                        adda_s(f3, f0);
                                        madd_s(f0, f1, f2);
                                        swc1(f0, s1, 4);
                                        lwc1(f1, s2, unit4::kHeight);
                                        lwc1(f0, s2, unit::kScale);
                                        mul_s(f2, f1, f0);
                                        lwc1(f1, gp, -32620);  // 0x7CAD84
                                        lwc1(f0, s0, 4);
                                        adda_s(f3, f0);
                                        msub_s(f0, f1, f2);
                                        swc1(f0, s0, 4);
                                        v0 = 0x40900000;
                                        mtc1(v0, f0);
                                    } else {
                                        // 0x002e6290
                                        charge(ctx, 3);
                                        v1 = 260;
                                        if (v0 == v1) {
                                            // 0x002e63e0
                                            charge(ctx, 22);
                                            lwc1(f1, s3, unit4::kHeight);
                                            lwc1(f0, s3, unit::kScale);
                                            mul_s(f2, f1, f0);
                                            lwc1(f1, gp, -32668);  // 0x7CAD54
                                            lwc1(f0, s1, 4);
                                            mtc1(zero, f3);
                                            adda_s(f3, f0);
                                            madd_s(f0, f1, f2);
                                            swc1(f0, s1, 4);
                                            lwc1(f1, s2, unit4::kHeight);
                                            lwc1(f0, s2, unit::kScale);
                                            mul_s(f2, f1, f0);
                                            lwc1(f1, gp, -32624);  // 0x7CAD80
                                            lwc1(f0, s0, 4);
                                            adda_s(f3, f0);
                                            msub_s(f0, f1, f2);
                                            swc1(f0, s0, 4);
                                            v0 = 0x40A00000;
                                            mtc1(v0, f0);
                                        } else {
                                            // 0x002e629c
                                            charge(ctx, 3);
                                            v1 = 259;
                                            if (v0 == v1) {
                                                // 0x002e6388
                                                charge(ctx, 22);
                                                lwc1(f1, s3, unit4::kHeight);
                                                lwc1(f0, s3, unit::kScale);
                                                mul_s(f2, f1, f0);
                                                lwc1(f1, gp, -32620);  // 0x7CAD84
                                                lwc1(f0, s1, 4);
                                                mtc1(zero, f3);
                                                adda_s(f3, f0);
                                                madd_s(f0, f1, f2);
                                                swc1(f0, s1, 4);
                                                lwc1(f1, s2, unit4::kHeight);
                                                lwc1(f0, s2, unit::kScale);
                                                mul_s(f2, f1, f0);
                                                lwc1(f1, gp, -32588);  // 0x7CADA4
                                                lwc1(f0, s0, 4);
                                                adda_s(f3, f0);
                                                msub_s(f0, f1, f2);
                                                swc1(f0, s0, 4);
                                                v0 = 0x40800000;
                                                mtc1(v0, f0);
                                            } else {
                                                // 0x002e62a8
                                                charge(ctx, 3);
                                                v1 = 258;
                                                if (v0 != v1) {
                                                    // 0x002e62b4
                                                    charge(ctx, 3);
                                                    v1 = 257;
                                                    if (v0 == v1) {
                                                        goto L_002e6330;
                                                    }
                                                    // 0x002e62c0
                                                    charge(ctx, 3);
                                                    v1 = 256;
                                                    if (v0 == v1) {
                                                        // 0x002e62d4
                                                        charge(ctx, 23);
                                                        lwc1(f1, s3, unit4::kHeight);
                                                        lwc1(f0, s3, unit::kScale);
                                                        mul_s(f2, f1, f0);
                                                        lwc1(f1, gp, -32720);  // 0x7CAD20
                                                        lwc1(f0, s1, 4);
                                                        mtc1(zero, f3);
                                                        adda_s(f3, f0);
                                                        madd_s(f0, f1, f2);
                                                        swc1(f0, s1, 4);
                                                        lwc1(f1, s2, unit4::kHeight);
                                                        lwc1(f0, s2, unit::kScale);
                                                        mul_s(f2, f1, f0);
                                                        v0 = 0x3E000000;
                                                        mtc1(v0, f1);
                                                        lwc1(f0, s0, 4);
                                                        adda_s(f3, f0);
                                                        msub_s(f0, f1, f2);
                                                        swc1(f0, s0, 4);
                                                        v0 = 0x40900000;
                                                        mtc1(v0, f0);
                                                    } else {
                                                        // 0x002e62cc
                                                        charge(ctx, 2);
                                                        // 0x002e6700
                                                        charge(ctx, 22);
                                                        lwc1(f1, s3, unit4::kHeight);
                                                        lwc1(f0, s3, unit::kScale);
                                                        mul_s(f2, f1, f0);
                                                        lwc1(f1, gp, -32720);  // 0x7CAD20
                                                        lwc1(f0, s1, 4);
                                                        mtc1(zero, f3);
                                                        adda_s(f3, f0);
                                                        madd_s(f0, f1, f2);
                                                        swc1(f0, s1, 4);
                                                        lwc1(f1, s2, unit4::kHeight);
                                                        lwc1(f0, s2, unit::kScale);
                                                        mul_s(f2, f1, f0);
                                                        lwc1(f1, gp, -32564);  // 0x7CADBC
                                                        lwc1(f0, s0, 4);
                                                        adda_s(f3, f0);
                                                        msub_s(f0, f1, f2);
                                                        swc1(f0, s0, 4);
                                                        v0 = 0x40800000;
                                                        mtc1(v0, f0);
                                                    }
                                                    // 0x002e6a00 (the shared epilogue, written out on this path)
                                                    charge(ctx, 8);
                                                    ld(ra, sp, 0x40);
                                                    lq(s3, sp, 0x30);
                                                    lq(s2, sp, 0x20);
                                                    lq(s1, sp, 0x10);
                                                    lq(s0, sp, 0x0);
                                                    sp = addiu(sp, 0x50);
                                                    return;
                                                }
                                            L_002e6330:
                                                charge(ctx, 22);
                                                lwc1(f1, s3, unit4::kHeight);
                                                lwc1(f0, s3, unit::kScale);
                                                mul_s(f2, f1, f0);
                                                lwc1(f1, gp, -32588);  // 0x7CADA4
                                                lwc1(f0, s1, 4);
                                                mtc1(zero, f3);
                                                adda_s(f3, f0);
                                                madd_s(f0, f1, f2);
                                                swc1(f0, s1, 4);
                                                lwc1(f1, s2, unit4::kHeight);
                                                lwc1(f0, s2, unit::kScale);
                                                mul_s(f2, f1, f0);
                                                lwc1(f1, gp, -32720);  // 0x7CAD20
                                                lwc1(f0, s0, 4);
                                                adda_s(f3, f0);
                                                msub_s(f0, f1, f2);
                                                swc1(f0, s0, 4);
                                                v0 = 0x40800000;
                                                mtc1(v0, f0);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                // 0x002e6a00 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x50);
                return;
            }
        L_002e6648:
            charge(ctx, 23);
            lwc1(f1, s3, unit4::kHeight);
            lwc1(f0, s3, unit::kScale);
            mul_s(f2, f1, f0);
            v0 = 0x3F000000;
            mtc1(v0, f1);
            lwc1(f0, s1, 4);
            mtc1(zero, f3);
            adda_s(f3, f0);
            madd_s(f0, f1, f2);
            swc1(f0, s1, 4);
            lwc1(f1, s2, unit4::kHeight);
            lwc1(f0, s2, unit::kScale);
            mul_s(f2, f1, f0);
            lwc1(f1, gp, -32568);  // 0x7CADB8
            lwc1(f0, s0, 4);
            adda_s(f3, f0);
            msub_s(f0, f1, f2);
            swc1(f0, s0, 4);
            v0 = 0x40C00000;
            mtc1(v0, f0);
        }
        // 0x002e6a00 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_002e6758:
    charge(ctx, 3);
    v0 = 1;
    if (a0 == v0) {
        // 0x002e6764
        charge(ctx, 3);
        lbu(v0, s2, unit::kSide);
        if (v0 != 0) {
            goto L_002e69f8;
        }
        // 0x002e6770
        charge(ctx, 5);
        lhu(v0, s3, unit::kId);
        v0 = addiu(v0, -257);
        at = sltiu(v0, 10);
        if (at != 0) {
            // 0x002e6784
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30304);  // &0x7B89A0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E67A0u:  // table[0, 1]
                // 0x002e67a0
                charge(ctx, 23);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f2, f1, f0);
                lwc1(f1, gp, -32660);  // 0x7CAD5C
                lwc1(f0, s1, 4);
                mtc1(zero, f3);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s1, 4);
                lwc1(f1, s2, unit4::kHeight);
                lwc1(f0, s2, unit::kScale);
                mul_s(f2, f1, f0);
                v0 = 0x3F000000;
                mtc1(v0, f1);
                lwc1(f0, s0, 4);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s0, 4);
                v0 = 0x40B00000;
                mtc1(v0, f0);
                break;
            case 0x2E67FCu:  // table[2]
                // 0x002e67fc
                charge(ctx, 23);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f2, f1, f0);
                v0 = 0x3E800000;
                mtc1(v0, f1);
                lwc1(f0, s1, 4);
                mtc1(zero, f3);
                adda_s(f3, f0);
                msub_s(f0, f1, f2);
                swc1(f0, s1, 4);
                lwc1(f1, s2, unit4::kHeight);
                lwc1(f0, s2, unit::kScale);
                mul_s(f2, f1, f0);
                lwc1(f1, gp, -32572);  // 0x7CADB4
                lwc1(f0, s0, 4);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s0, 4);
                v0 = 0x40B00000;
                mtc1(v0, f0);
                break;
            case 0x2E6858u:  // table[3]
                // 0x002e6858
                charge(ctx, 17);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f3, f1, f0);
                v0 = 0x3F000000;
                mtc1(v0, f2);
                lwc1(f1, s1, 4);
                mtc1(zero, f0);
                adda_s(f0, f1);
                msub_s(f0, f2, f3);
                swc1(f0, s1, 4);
                v0 = 0x432A0000;
                sw(v0, s0, 4);
                v0 = 0x40D00000;
                mtc1(v0, f0);
                break;
            case 0x2E689Cu:  // table[4]
                // 0x002e689c
                charge(ctx, 24);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f2, f1, f0);
                v0 = 0x3E800000;
                mtc1(v0, f1);
                lwc1(f0, s1, 4);
                mtc1(zero, f3);
                adda_s(f3, f0);
                msub_s(f0, f1, f2);
                swc1(f0, s1, 4);
                lwc1(f1, s2, unit4::kHeight);
                lwc1(f0, s2, unit::kScale);
                mul_s(f2, f1, f0);
                v0 = 0x3F000000;
                mtc1(v0, f1);
                lwc1(f0, s0, 4);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s0, 4);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                break;
            case 0x2E68FCu:  // table[6]
                // 0x002e68fc
                charge(ctx, 23);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f2, f1, f0);
                lwc1(f1, gp, -32720);  // 0x7CAD20
                lwc1(f0, s1, 4);
                mtc1(zero, f3);
                adda_s(f3, f0);
                msub_s(f0, f1, f2);
                swc1(f0, s1, 4);
                lwc1(f1, s2, unit4::kHeight);
                lwc1(f0, s2, unit::kScale);
                mul_s(f2, f1, f0);
                v0 = 0x3E800000;
                mtc1(v0, f1);
                lwc1(f0, s0, 4);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s0, 4);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                break;
            case 0x2E6958u:  // table[9]
                // 0x002e6958
                charge(ctx, 17);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f3, f1, f0);
                v0 = 0x3E800000;
                mtc1(v0, f2);
                lwc1(f1, s1, 4);
                mtc1(zero, f0);
                adda_s(f0, f1);
                msub_s(f0, f2, f3);
                swc1(f0, s1, 4);
                v0 = 0x432A0000;
                sw(v0, s0, 4);
                v0 = 0x40C00000;
                mtc1(v0, f0);
                break;
            case 0x2E699Cu:  // table[5, 7, 8]
            L_002e699c:
                charge(ctx, 23);
                lwc1(f1, s3, unit4::kHeight);
                lwc1(f0, s3, unit::kScale);
                mul_s(f2, f1, f0);
                lwc1(f1, gp, -32660);  // 0x7CAD5C
                lwc1(f0, s1, 4);
                mtc1(zero, f3);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s1, 4);
                lwc1(f1, s2, unit4::kHeight);
                lwc1(f0, s2, unit::kScale);
                mul_s(f2, f1, f0);
                v0 = 0x3F000000;
                mtc1(v0, f1);
                lwc1(f0, s0, 4);
                adda_s(f3, f0);
                madd_s(f0, f1, f2);
                swc1(f0, s0, 4);
                v0 = 0x40B00000;
                mtc1(v0, f0);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e6a00 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
        }
        goto L_002e699c;
    }
L_002e69f8:
    charge(ctx, 2);
    v0 = 0x40900000;
    mtc1(v0, f0);
    // 0x002e6a00 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002E7210 sub_2E7210 -- 268 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Shot start for a combatant action (flags2 bit 0): an enemy action turns its party targets (sub_27FCF0); then
// sub_2B0280(shot, 1, 0) for an enemy actor or (shot, 0, 1) for a party one.
// Arguments: a0 the camera shot.
void sub_2E7210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e7210
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(a0, a0, shot::kAction);
    if (a0 != 0) {
        // 0x002e7234
        charge(ctx, 4);
        lhu(v1, a0, act::kFlags2);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            // 0x002e7244
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x002e724c
                charge(ctx, 4);
                lw(s0, a0, act::kUnit);
                lbu(v0, s0, unit::kSide);
                if (v0 == 0) {
                    // 0x002e725c
                    charge(ctx, 3);
                    s1 = 0;
                    for (;;) {
                        // 0x002e72a0
                        charge(ctx, 6);
                        lw(a0, s2, shot::kAction);
                        v1 = s1 & 0xFFFF;
                        lhu(v0, a0, act::kTargetCount);
                        v0 = slt(v1, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002e7268
                        charge(ctx, 9);
                        v0 = s1 & 0xFFFF;
                        v0 = sll(v0, 2);
                        v0 = addu(a0, v0);
                        lw(v0, v0, act::kTargets);
                        lw(a0, v0, act::kUnit);
                        lbu(v1, a0, unit::kSide);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x002e728c
                            charge(ctx, 3);
                            a1 = addiu(s0, 4);
                            jal(ctx, 0x2E7290u, gen::fn_sub_27FCF0_0027fcf0);
                        }
                        // 0x002e7298
                        charge(ctx, 2);
                        v0 = addiu(s1, 1);
                        s1 = v0 & 0xFFFF;
                    }
                }
            }
            // 0x002e72b8
            charge(ctx, 4);
            lw(v0, a0, act::kUnit);
            lbu(v0, v0, unit::kSide);
            if (v0 != 0) {
                // 0x002e72e8
                charge(ctx, 6);
                mtc1(zero, f12);
                a0 = s2;
                a1 = 1;
                a2 = 0;
                jal(ctx, 0x2E72F8u, gen::fn_sub_2B0280_002b0280);
            } else {
                // 0x002e72c8
                charge(ctx, 8);
                mtc1(zero, f12);
                a0 = s2;
                a1 = 0;
                a2 = 1;
                jal(ctx, 0x2E72D8u, gen::fn_sub_2B0280_002b0280);
            }
        }
    }
    // 0x002e7300 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002E7330 sub_2E7330 -- 836 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Weapon / skill shot: only when sub_2F8A40 accepts the first target's unit; stores that target at shot +256 and
// picks the camera script table of a party actor by its id: 1 by the held weapon type (0x697CC0, 244-byte rows), 2
// 0x698460, 3 (or sub_2D5BF0) by sub_3093A0's kind (0x698748 / 0x698654, 0x698E40 for encounter 436), ...; then
// sub_2FDFA0 / sub_2B6BF0 / sub_2B1E00 / sub_2B6CD0 play it and sub_2A3E80 re-arms the action.
// Arguments: a0 the camera shot.
void sub_2E7330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e7330
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, shot::kAction);
    lw(v0, v0, act::kTargets);
    lw(a0, v0, act::kUnit);
    jal(ctx, 0x2E7358u, gen::fn_sub_2F8A40_002f8a40);
    if (v0 == 0) {
        // 0x002e75d4
        charge(ctx, 3);
        a0 = s2;
        jal(ctx, 0x2E75D8u, gen::fn_sub_2B1E00_002b1e00);
    L_002e75e0:
        charge(ctx, 5);
        a0 = addiu(s2, 236);
        jal(ctx, 0x2E75E4u, gen::fn_sub_2B6CD0_002b6cd0);
        if (v0 != 0) {
            // 0x002e75f4
            charge(ctx, 4);
            lhu(v0, v0, 28);
            a3 = 1;
            if (v0 != a3) {
                // 0x002e762c
                charge(ctx, 8);
                mtc1(zero, f12);
                lw(a0, s2, shot::kAction);
                a1 = 0;
                a2 = 0;
                a3 = 3;
                jal(ctx, 0x2E7640u, gen::fn_sub_2A3E80_002a3e80);
                sw(zero, s2, 272);
            } else {
                // 0x002e7604
                charge(ctx, 10);
                mtc1(zero, f12);
                lw(a0, s2, shot::kAction);
                a1 = 0;
                a2 = 0;
                jal(ctx, 0x2E7614u, gen::fn_sub_2A3E80_002a3e80);
                v1 = 1;
                sw(v1, s2, 272);
            }
        }
        // 0x002e764c
        charge(ctx, 2);
        v1 = 1;
        sw(v1, s2, 276);
    } else {
        // 0x002e7368
        charge(ctx, 8);
        lw(v1, s2, shot::kAction);
        lw(v1, v1, act::kTargets);
        sw(v1, s2, shot::kTarget);
        lw(v1, s2, shot::kAction);
        lw(s0, v1, act::kUnit);
        lbu(v1, s0, unit::kSide);
        if (v1 == 0) {
            // 0x002e7388
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x2E738Cu, gen::fn_sub_2D5BF0_002d5bf0);
            if (v0 == 0) {
                // 0x002e73a8
                charge(ctx, 1);
                lhu(v0, s0, unit::kId);
            } else {
                // 0x002e739c
                charge(ctx, 3);
                v0 = 3;
            }
            // 0x002e73ac
            charge(ctx, 4);
            v0 = v0 & 0xFFFF;
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x002e73bc
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -30256);  // &0x7B89D0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2E73D8u:  // table[1]
                    // 0x002e73d8
                    charge(ctx, 14);
                    lw(a0, s0, unit::kDat);
                    jal(ctx, 0x2E73DCu, gen::fn_datCalcGetHeldWeaponType_00308c60);
                    v1 = v0 & 0xFF;
                    v0 = sll(v1, 4);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    v0 = 0x690000;
                    v0 = addiu(v0, 31936);  // &0x697CC0
                    s1 = addu(v0, v1);
                    break;
                case 0x2E7410u:  // table[2]
                    // 0x002e7410
                    charge(ctx, 4);
                    s1 = 0x6A0000;
                    s1 = addiu(s1, -31648);  // &0x698460
                    break;
                case 0x2E7420u:  // table[3]
                    // 0x002e7420
                    charge(ctx, 7);
                    lw(a0, s0, unit::kDat);
                    jal(ctx, 0x2E7424u, gen::fn_sub_3093A0_003093a0);
                    v1 = v0 & 0xFF;
                    v0 = 3;
                    if (v1 == v0) {
                        // 0x002e74a4
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -30904);  // &0x698748
                    } else {
                        // 0x002e743c
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x002e746c
                            charge(ctx, 6);
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            lw(v0, v0, gbtl::kSetupEnemies);
                            lhu(v1, v0, kGenusEncounter);
                            v0 = 436;
                            if (v1 == v0) {
                                // 0x002e7494
                                charge(ctx, 4);
                                s1 = 0x6A0000;
                                s1 = addiu(s1, -29120);  // &0x698E40
                            } else {
                                // 0x002e7484
                                charge(ctx, 4);
                                s1 = 0x6A0000;
                                s1 = addiu(s1, -31148);  // &0x698654
                            }
                        } else {
                            // 0x002e7448
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x002e745c
                                charge(ctx, 4);
                                s1 = 0x6A0000;
                                s1 = addiu(s1, -31392);  // &0x698560
                            } else {
                                // 0x002e7454
                                charge(ctx, 2);
                            }
                        }
                    }
                    break;
                case 0x2E74B4u:  // table[4]
                    // 0x002e74b4
                    charge(ctx, 6);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kSetupEnemies);
                    lhu(v1, v0, kGenusEncounter);
                    v0 = 436;
                    if (v1 == v0) {
                        // 0x002e74dc
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -28864);  // &0x698F40
                    } else {
                        // 0x002e74cc
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -30656);  // &0x698840
                    }
                    break;
                case 0x2E74ECu:  // table[5]
                    // 0x002e74ec
                    charge(ctx, 4);
                    s1 = 0x6A0000;
                    s1 = addiu(s1, -30400);  // &0x698940
                    break;
                case 0x2E74FCu:  // table[7]
                    // 0x002e74fc
                    charge(ctx, 6);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kSetupEnemies);
                    lhu(v1, v0, kGenusEncounter);
                    v0 = 436;
                    if (v1 == v0) {
                        // 0x002e7524
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -28608);  // &0x699040
                    } else {
                        // 0x002e7514
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -30144);  // &0x698A40
                    }
                    break;
                case 0x2E7534u:  // table[8]
                    // 0x002e7534
                    charge(ctx, 6);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kSetupEnemies);
                    lhu(v1, v0, kGenusEncounter);
                    v0 = 436;
                    if (v1 == v0) {
                        // 0x002e755c
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -28352);  // &0x699140
                    } else {
                        // 0x002e754c
                        charge(ctx, 4);
                        s1 = 0x6A0000;
                        s1 = addiu(s1, -29888);  // &0x698B40
                    }
                    break;
                case 0x2E756Cu:  // table[9]
                    // 0x002e756c
                    charge(ctx, 4);
                    s1 = 0x6A0000;
                    s1 = addiu(s1, -29632);  // &0x698C40
                    break;
                case 0x2E757Cu:  // table[10]
                    // 0x002e757c
                    charge(ctx, 2);
                    s1 = 0x6A0000;
                    s1 = addiu(s1, -29376);  // &0x698D40
                    break;
                case 0x2E7584u:  // table[0, 6]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x002e7584
            charge(ctx, 6);
            s3 = 1;
            a0 = s0;
            jal(ctx, 0x2E758Cu, gen::fn_sub_2FDFA0_002fdfa0);
            if (v0 == 0) {
                // 0x002e75ac
                charge(ctx, 2);
                v0 = s3 | 0x8;
                t0 = v0 & 0xFFFF;
            } else {
                // 0x002e759c
                charge(ctx, 4);
                v0 = s3 | 0x4;
                t0 = v0 & 0xFFFF;
            }
            // 0x002e75b4
            charge(ctx, 8);
            lw(a1, s2, shot::kAction);
            a0 = addiu(s2, 236);
            lw(a2, a1, act::kTargets);
            a3 = s1;
            jal(ctx, 0x2E75C4u, gen::fn_sub_2B6BF0_002b6bf0);
            goto L_002e75e0;
        }
    }
    // 0x002e7654 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002E7890 sub_2E7890 -- 1300 bytes; frame 0x120: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Child-unit shot: the actor's child unit (+2560) plays its motion (sub_287510, sub_27F730 with its +48 / +50)
// unless sub_2A7830's kind (shot +272) is 1; then by that kind 0 / 1 / 2 / 4 sub_2AC540 or a random framing
// (datCalcRand, sub_2A4690, sub_2A2290 / sub_2A3110).
// Arguments: a0 the camera shot.
void sub_2E7890(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002e7890
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    lw(v0, a0, shot::kAction);
    lw(s0, v0, act::kUnit);
    lw(s2, s0, unit5::kChild);
    if (v0 != 0) {
        // 0x002e78c4
        charge(ctx, 3);
        lbu(v0, s0, unit::kSide);
        if (v0 == 0) {
            // 0x002e78d0
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x002e7914
                charge(ctx, 6);
                lw(a0, s3, shot::kAction);
                v1 = s1 & 0xFFFF;
                lhu(v0, a0, act::kTargetCount);
                v0 = slt(v1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002e78dc
                charge(ctx, 9);
                v0 = s1 & 0xFFFF;
                v0 = sll(v0, 2);
                v0 = addu(a0, v0);
                lw(v0, v0, act::kTargets);
                lw(a0, v0, act::kUnit);
                lbu(v1, a0, unit::kSide);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002e7900
                    charge(ctx, 3);
                    a1 = addiu(s0, 4);
                    jal(ctx, 0x2E7904u, gen::fn_sub_27FCF0_0027fcf0);
                }
                // 0x002e790c
                charge(ctx, 2);
                v0 = addiu(s1, 1);
                s1 = v0 & 0xFFFF;
            }
        }
    }
    // 0x002e792c
    charge(ctx, 7);
    a0 = s3;
    jal(ctx, 0x2E7930u, gen::fn_sub_2A7830_002a7830);
    sh(v0, s3, shot8::kKind);
    v0 = sltu(0, s2);
    if (v0 != 0) {
        // 0x002e7948
        charge(ctx, 5);
        lw(a0, s3, shot::kAction);
        a1 = s2;
        jal(ctx, 0x2E7950u, gen::fn_sub_2FDBB0_002fdbb0);
        v0 = sltu(0, v0);
    }
    // 0x002e795c
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x002e7964
        charge(ctx, 4);
        lhu(v1, s3, shot8::kKind);
        v0 = 1;
        if (v1 != v0) {
            // 0x002e7974
            charge(ctx, 14);
            a0 = s2;
            jal(ctx, 0x2E7978u, gen::fn_sub_287510_00287510);
            lbu(v0, s2, 48);
            sb(v0, sp, 0x11C);
            lbu(v0, s2, 49);
            sb(v0, sp, 0x11D);
            lbu(v0, s2, 50);
            sb(v0, sp, 0x11E);
            sb(zero, sp, 0x11F);
            a0 = s2;
            lw(a1, sp, 0x11C);
            jal(ctx, 0x2E79A4u, gen::fn_sub_27F730_0027f730);
        }
    }
    // 0x002e79ac
    charge(ctx, 8);
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x2E79B4u, gen::fn_sub_2880E0_002880e0);
    lhu(v1, s3, shot8::kKind);
    at = sltiu(v1, 7);
    if (at != 0) {
        // 0x002e79cc
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -30208);  // &0x7B8A00
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2E79E8u:  // table[0, 1, 2, 4]
            // 0x002e79e8
            charge(ctx, 8);
            a0 = s3;
            jal(ctx, 0x2E79ECu, gen::fn_sub_2AC540_002ac540);
            lw(a0, s3, shot::kAction);
            lhu(a1, a0, act::kTargetCount);
            v1 = 1;
            if (a1 == v1) {
                // 0x002e7a08
                charge(ctx, 4);
                lw(v1, a0, act::kUnit);
                lbu(v1, v1, unit::kSide);
                if (v1 == 0) {
                    // 0x002e7a18
                    charge(ctx, 3);
                    lw(v1, a0, act::kTargets);
                    if (a0 != v1) {
                        // 0x002e7a24
                        charge(ctx, 4);
                        lw(v1, v1, act::kUnit);
                        lbu(v1, v1, unit::kSide);
                        if (v1 == 0) {
                            // 0x002e7a34
                            charge(ctx, 8);
                            mtc1(zero, f12);
                            a1 = 0;
                            a2 = 0;
                            a3 = 8;
                            jal(ctx, 0x2E7A44u, gen::fn_sub_2A3E80_002a3e80);
                        }
                    }
                }
            }
            break;
        case 0x2E7A54u:  // table[3, 5]
            // 0x002e7a54
            charge(ctx, 77);
            lw(v0, s3, shot::kAction);
            lw(s0, v0, act::kUnit);
            a0 = 2;
            jal(ctx, 0x2E7A60u, gen::fn_datCalcRand_002ffbc0);
            a0 = v0 & 0xFFFF;
            lb(v1, s0, unit5::kSlot);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v0, gbtl4::kBossAiRows);
            v1 = addu(v0, v1);
            v0 = sll(a0, 1);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            s0 = addiu(v0, 4);
            a0 = addiu(sp, 0xEC);
            a1 = addiu(s0, 4);
            a2 = addiu(s0, 16);
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E7AC0u, gen::fn_sub_2A4690_002a4690);
            lwc1(f2, s0, 4);
            lwc1(f1, s0, 8);
            lwc1(f0, s0, 12);
            swc1(f2, sp, 0xE0);
            swc1(f1, sp, 0xE4);
            swc1(f0, sp, 0xE8);
            a0 = addiu(sp, 0x108);
            a1 = addiu(s0, 28);
            a2 = addiu(s0, 40);
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E7AF4u, gen::fn_sub_2A4690_002a4690);
            a2 = addiu(sp, 0xFC);
            lwc1(f2, s0, 28);
            lwc1(f1, s0, 32);
            lwc1(f0, s0, 36);
            swc1(f2, sp, 0xFC);
            swc1(f1, sp, 0x100);
            swc1(f0, sp, 0x104);
            lh(v0, s0, 0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            div_s(f20, f1, f0);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            a0 = addiu(v0, gbtl7::kCamera);
            a1 = addiu(sp, 0xE0);
            a3 = 1;
            jal(ctx, 0x2E7B48u, gen::fn_sub_2A2290_002a2290);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            a0 = addiu(v0, gbtl7::kCamera);
            mov_s(f12, f20);
            jal(ctx, 0x2E7B5Cu, gen::fn_sub_2A3110_002a3110);
            mtc1(zero, f12);
            lw(a0, s3, shot::kAction);
            a1 = 0;
            a2 = 0;
            a3 = 64;
            jal(ctx, 0x2E7B78u, gen::fn_sub_2A3E80_002a3e80);
            break;
        case 0x2E7B88u:  // table[6]
            // 0x002e7b88
            charge(ctx, 5);
            lw(a0, s3, shot::kAction);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002e7b9c
                charge(ctx, 4);
                lw(v0, a0, act::kUnit);
                lbu(v0, v0, unit::kSide);
                if (v0 != 0) {
                    // 0x002e7c78
                    charge(ctx, 59);
                    a0 = 2;
                    jal(ctx, 0x2E7C7Cu, gen::fn_datCalcRand_002ffbc0);
                    v1 = v0 & 0xFFFF;
                    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, a0, gbtl4::kBossAiRows);
                    v0 = addu(v0, v1);
                    s0 = addiu(v0, 524);
                    a0 = addiu(sp, 0x6C);
                    a1 = addiu(s0, 4);
                    a2 = addiu(s0, 16);
                    a3 = 0x690000;
                    a3 = addiu(a3, 30848);  // &0x697880
                    jal(ctx, 0x2E7CC0u, gen::fn_sub_2A4690_002a4690);
                    lwc1(f2, s0, 4);
                    lwc1(f1, s0, 8);
                    lwc1(f0, s0, 12);
                    swc1(f2, sp, 0x60);
                    swc1(f1, sp, 0x64);
                    swc1(f0, sp, 0x68);
                    a0 = addiu(sp, 0x88);
                    a1 = addiu(s0, 28);
                    a2 = addiu(s0, 40);
                    a3 = 0x690000;
                    a3 = addiu(a3, 30848);  // &0x697880
                    jal(ctx, 0x2E7CF4u, gen::fn_sub_2A4690_002a4690);
                    a2 = addiu(sp, 0x7C);
                    lwc1(f2, s0, 28);
                    lwc1(f1, s0, 32);
                    lwc1(f0, s0, 36);
                    swc1(f2, sp, 0x7C);
                    swc1(f1, sp, 0x80);
                    swc1(f0, sp, 0x84);
                    lh(v0, s0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41F00000;
                    mtc1(v0, f0);
                    div_s(f20, f1, f0);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    a0 = addiu(v0, gbtl7::kCamera);
                    a1 = addiu(sp, 0x60);
                    a3 = 1;
                    jal(ctx, 0x2E7D48u, gen::fn_sub_2A2290_002a2290);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    a0 = addiu(v0, gbtl7::kCamera);
                    mov_s(f12, f20);
                    jal(ctx, 0x2E7D5Cu, gen::fn_sub_2A3110_002a3110);
                } else {
                    // 0x002e7bac
                    charge(ctx, 51);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl4::kBossAiRows);
                    s0 = addiu(v0, 940);
                    a0 = addiu(sp, 0xAC);
                    a1 = addiu(s0, 4);
                    a2 = addiu(s0, 16);
                    a3 = 0x690000;
                    a3 = addiu(a3, 30848);  // &0x697880
                    jal(ctx, 0x2E7BCCu, gen::fn_sub_2A4690_002a4690);
                    lwc1(f2, s0, 4);
                    lwc1(f1, s0, 8);
                    lwc1(f0, s0, 12);
                    swc1(f2, sp, 0xA0);
                    swc1(f1, sp, 0xA4);
                    swc1(f0, sp, 0xA8);
                    a0 = addiu(sp, 0xC8);
                    a1 = addiu(s0, 28);
                    a2 = addiu(s0, 40);
                    a3 = 0x690000;
                    a3 = addiu(a3, 30848);  // &0x697880
                    jal(ctx, 0x2E7C00u, gen::fn_sub_2A4690_002a4690);
                    a2 = addiu(sp, 0xBC);
                    lwc1(f2, s0, 28);
                    lwc1(f1, s0, 32);
                    lwc1(f0, s0, 36);
                    swc1(f2, sp, 0xBC);
                    swc1(f1, sp, 0xC0);
                    swc1(f0, sp, 0xC4);
                    lh(v0, s0, 0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41F00000;
                    mtc1(v0, f0);
                    div_s(f20, f1, f0);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    a0 = addiu(v0, gbtl7::kCamera);
                    a1 = addiu(sp, 0xA0);
                    a3 = 1;
                    jal(ctx, 0x2E7C54u, gen::fn_sub_2A2290_002a2290);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    a0 = addiu(v0, gbtl7::kCamera);
                    mov_s(f12, f20);
                    jal(ctx, 0x2E7C68u, gen::fn_sub_2A3110_002a3110);
                }
                // 0x002e7d64
                charge(ctx, 7);
                mtc1(zero, f12);
                lw(a0, s3, shot::kAction);
                a1 = 0;
                a2 = 0;
                a3 = 64;
                jal(ctx, 0x2E7D78u, gen::fn_sub_2A3E80_002a3e80);
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002e7d80 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x002E7DB0 sub_2E7DB0 -- 1280 bytes; frame 0x130: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// Actor-and-target shot (sub_2E82B0's helper): the eye between the actor and its first target (sub_27FFB0 x2),
// half the actor's height (capped at 450), pulled towards the shot point (sub_4C69F0 / sub_4C6B20), rotated
// (sub_4BE1E0) and placed at a tan distance; cut (sub_2A3E80) or moved (sub_2A2290 / sub_2A3110).
// Arguments: a0 the camera shot.
void sub_2E7DB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x002e7db0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    lw(v0, a0, shot::kAction);
    lw(s0, v0, act::kUnit);
    lw(v0, v0, act::kTargets);
    lw(s1, v0, act::kUnit);
    a0 = s0;
    a1 = addiu(sp, 0x120);
    jal(ctx, 0x2E7DECu, gen::fn_sub_27FFB0_0027ffb0);
    a0 = s1;
    a1 = addiu(sp, 0x110);
    jal(ctx, 0x2E7DFCu, gen::fn_sub_27FFB0_0027ffb0);
    lwc1(f1, s0, unit::kScale);
    lwc1(f0, s0, unit4::kHeight);
    mul_s(f4, f0, f1);
    v0 = 0x3F000000;
    mtc1(v0, f0);
    lwc1(f3, sp, 0x124);
    mtc1(zero, f1);
    adda_s(f1, f3);
    madd_s(f2, f0, f4);
    v0 = 0x43E10000;
    mtc1(v0, f0);
    c_lt_s(f2, f0);
    if (!cond(ctx)) {
        // 0x002e7e44
        charge(ctx, 4);
        lwc1(f0, gp, -32720);  // 0x7CAD20
        adda_s(f1, f3);
        msub_s(f0, f0, f4);
        swc1(f0, sp, 0x124);
    }
    // 0x002e7e54
    charge(ctx, 82);
    lwc1(f1, sp, 0x120);
    lwc1(f0, sp, 0x110);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xE0);
    lwc1(f1, sp, 0x124);
    lwc1(f0, sp, 0x114);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xE4);
    lwc1(f1, sp, 0x128);
    lwc1(f0, sp, 0x118);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xE8);
    a0 = addiu(sp, 0xE0);
    a1 = a0;
    jal(ctx, 0x2E7E8Cu, gen::fn_sub_4C69F0_004c69f0);
    mov_s(f20, f0);
    lwc1(f1, s2, 156);
    lwc1(f0, sp, 0x120);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x98);
    lwc1(f1, s2, 164);
    lwc1(f0, sp, 0x128);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x9C);
    a0 = addiu(sp, 0x98);
    a1 = a0;
    jal(ctx, 0x2E7EC0u, gen::fn_sub_4C6B20_004c6b20);
    lwc1(f0, gp, -32616);  // 0x7CAD88
    mul_s(f2, f0, f20);
    lwc1(f0, sp, 0xE0);
    mul_s(f4, f0, f2);
    swc1(f4, sp, 0xF0);
    lwc1(f1, sp, 0xE4);
    mul_s(f3, f1, f2);
    swc1(f3, sp, 0xF4);
    lwc1(f6, sp, 0xE8);
    mul_s(f2, f6, f2);
    swc1(f2, sp, 0xF8);
    lwc1(f1, sp, 0x110);
    add_s(f1, f4, f1);
    swc1(f1, sp, 0xF0);
    lwc1(f1, sp, 0x114);
    add_s(f1, f3, f1);
    swc1(f1, sp, 0xF4);
    lwc1(f1, sp, 0x118);
    add_s(f1, f2, f1);
    swc1(f1, sp, 0xF8);
    swc1(f0, sp, 0x90);
    swc1(f6, sp, 0x94);
    ld(v0, sp, 0x110);
    lwc1(f1, sp, 0x118);
    sd(v0, sp, 0x100);
    swc1(f1, sp, 0x108);
    lwc1(f1, s1, unit::kRadius);
    lwc1(f5, s1, unit::kScale);
    mul_s(f2, f1, f5);
    v0 = 0x3FC00000;
    mtc1(v0, f1);
    mul_s(f4, f1, f2);
    swc1(f6, sp, 0x90);
    neg_s(f3, f0);
    swc1(f3, sp, 0x94);
    lwc1(f2, sp, 0x98);
    lwc1(f1, sp, 0x9C);
    mula_s(f3, f1);
    mtc1(zero, f3);
    madd_s(f22, f6, f2);
    lwc1(f20, sp, 0x104);
    lwc1(f1, s1, unit4::kHeight);
    mul_s(f2, f1, f5);
    v0 = 0x3E800000;
    mtc1(v0, f1);
    adda_s(f3, f20);
    madd_s(f1, f1, f2);
    swc1(f1, sp, 0xD4);
    c_lt_s(f22, f3);
    if (cond(ctx)) {
        // 0x002e7fc4
        charge(ctx, 8);
        lwc1(f1, sp, 0x100);
        adda_s(f3, f1);
        msub_s(f1, f6, f4);
        swc1(f1, sp, 0xD0);
        lwc1(f21, sp, 0x108);
        adda_s(f3, f21);
        madd_s(f0, f0, f4);
        swc1(f0, sp, 0xD8);
    } else {
        // 0x002e7f9c
        charge(ctx, 10);
        lwc1(f1, sp, 0x100);
        adda_s(f3, f1);
        madd_s(f1, f6, f4);
        swc1(f1, sp, 0xD0);
        lwc1(f21, sp, 0x108);
        adda_s(f3, f21);
        msub_s(f0, f0, f4);
        swc1(f0, sp, 0xD8);
    }
    // 0x002e7fe4
    charge(ctx, 66);
    ld(v0, sp, 0xE0);
    lwc1(f0, sp, 0xE8);
    sd(v0, sp, 0xC0);
    swc1(f0, sp, 0xC8);
    a0 = addiu(sp, 0x5C);
    a1 = addiu(sp, 0xD0);
    a2 = addiu(sp, 0xF0);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8008u, gen::fn_sub_2A4690_002a4690);
    a0 = addiu(sp, 0xE0);
    a1 = 0x690000;
    a1 = addiu(a1, 30880);  // &0x6978A0
    a2 = 1;
    a3 = addiu(sp, 0x5C);
    jal(ctx, 0x2E8024u, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(f0, sp, 0xF0);
    swc1(f0, sp, 0xA0);
    lwc1(f0, sp, 0xF8);
    swc1(f0, sp, 0xA4);
    lwc1(f0, sp, 0xD0);
    swc1(f0, sp, 0xA8);
    lwc1(f0, sp, 0xD8);
    swc1(f0, sp, 0xAC);
    lwc1(f0, sp, 0x100);
    swc1(f0, sp, 0xB8);
    swc1(f21, sp, 0xBC);
    a0 = addiu(sp, 0xA0);
    a1 = addiu(sp, 0xA8);
    a2 = addiu(sp, 0xB8);
    a3 = addiu(sp, 0xB0);
    jal(ctx, 0x2E8068u, gen::fn_sub_2D1FD0_002d1fd0);
    lwc1(f2, s1, unit::kRadius);
    lwc1(f1, s1, unit::kScale);
    mul_s(f3, f2, f1);
    v0 = 0x40600000;
    mtc1(v0, f2);
    mtc1(zero, f1);
    adda_s(f1, f0);
    madd_s(f21, f2, f3);
    lwc1(f0, sp, 0xB0);
    swc1(f0, sp, 0xD0);
    swc1(f20, sp, 0xD4);
    lwc1(f0, sp, 0xB4);
    swc1(f0, sp, 0xD8);
    v0 = 0x3F000000;
    mtc1(v0, f1);
    lwc1(f0, s2, 184);
    mul_s(f1, f1, f0);
    lwc1(f0, gp, -32656);  // 0x7CAD60
    mul_s(f12, f0, f1);
    jal(ctx, 0x2E80C0u, gen::fn_tanf_0052e930);
    div_s(f3, f21, f0);
    v0 = 0x43FA0000;
    mtc1(v0, f0);
    c_lt_s(f3, f0);
    if (cond(ctx)) {
        // 0x002e80ec
        charge(ctx, 1);
        mov_s(f3, f0);
    }
    // 0x002e80f0
    charge(ctx, 15);
    lwc1(f2, sp, 0xE0);
    v0 = 0x41700000;
    mtc1(v0, f0);
    sub_s(f4, f3, f0);
    mul_s(f13, f2, f4);
    lwc1(f1, sp, 0xE4);
    mul_s(f8, f1, f4);
    lwc1(f0, sp, 0xE8);
    mul_s(f12, f0, f4);
    mtc1(zero, f7);
    c_lt_s(f22, f7);
    if (!cond(ctx)) {
        // 0x002e812c
        charge(ctx, 13);
        lwc1(f5, s1, unit::kRadius);
        lwc1(f4, s1, unit::kScale);
        mul_s(f6, f5, f4);
        lwc1(f5, sp, 0xC8);
        lwc1(f4, sp, 0xD0);
        adda_s(f7, f4);
        msub_s(f4, f5, f6);
        swc1(f4, sp, 0xD0);
        lwc1(f5, sp, 0xC0);
        lwc1(f4, sp, 0xD8);
        adda_s(f7, f4);
        madd_s(f4, f5, f6);
        swc1(f4, sp, 0xD8);
    }
    // 0x002e8160
    charge(ctx, 46);
    lwc1(f5, s1, unit4::kHeight);
    lwc1(f4, s1, unit::kScale);
    mul_s(f5, f5, f4);
    v0 = 0x3E800000;
    mtc1(v0, f4);
    mtc1(zero, f10);
    adda_s(f10, f20);
    madd_s(f11, f4, f5);
    swc1(f11, sp, 0xD4);
    lwc1(f9, sp, 0xD0);
    add_s(f4, f9, f13);
    swc1(f4, sp, 0x50);
    add_s(f4, f11, f8);
    swc1(f4, sp, 0x54);
    lwc1(f8, sp, 0xD8);
    add_s(f4, f8, f12);
    swc1(f4, sp, 0x58);
    lwc1(f7, sp, 0x5C);
    lwc1(f6, sp, 0x60);
    lwc1(f5, sp, 0x64);
    lwc1(f4, sp, 0x68);
    swc1(f7, sp, 0x78);
    swc1(f6, sp, 0x7C);
    swc1(f5, sp, 0x80);
    swc1(f4, sp, 0x84);
    v0 = 0x42AA0000;
    mtc1(v0, f4);
    add_s(f3, f4, f3);
    adda_s(f10, f9);
    madd_s(f2, f2, f3);
    swc1(f2, sp, 0x6C);
    adda_s(f10, f11);
    madd_s(f1, f1, f3);
    swc1(f1, sp, 0x70);
    adda_s(f10, f8);
    madd_s(f0, f0, f3);
    swc1(f0, sp, 0x74);
    lwc1(f1, sp, 0x54);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x002e8218
        charge(ctx, 1);
        swc1(f0, sp, 0x54);
    }
    // 0x002e821c
    charge(ctx, 7);
    lwc1(f1, sp, 0x70);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x002e8238
        charge(ctx, 1);
        swc1(f0, sp, 0x70);
    }
    // 0x002e823c
    charge(ctx, 29);
    v0 = 0x42480000;
    mtc1(v0, f12);
    lw(a0, s2, shot::kAction);
    a1 = addiu(s0, 4);
    a2 = addiu(s1, 4);
    a3 = 3;
    jal(ctx, 0x2E8254u, gen::fn_sub_2A3E80_002a3e80);
    a0 = s2;
    a1 = addiu(sp, 0x50);
    a2 = addiu(sp, 0x6C);
    a3 = 1;
    jal(ctx, 0x2E826Cu, gen::fn_sub_2A2290_002a2290);
    v0 = 0x40000000;
    mtc1(v0, f12);
    a0 = s2;
    jal(ctx, 0x2E8280u, gen::fn_sub_2A3110_002a3110);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x002E82B0 sub_2E82B0 -- 1268 bytes; frame 0x100: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Boss action shot dispatcher: shot +272 = sub_2A7830's kind, the targets' side mask (btlTargetGetSideMask);
// an action with flags2 bit 4 plays its child unit's motion (sub_2880E0: ids 0xE9..0xF0 keep the child at shot +288
// with +292 = 1); then by kind sub_2AC540, sub_2E4A40, sub_2E7DB0, sub_2E6A20 or a random framing.
// Arguments: a0 the camera shot.
void sub_2E82B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002e82b0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x2E82C8u, gen::fn_sub_2A7830_002a7830);
    sh(v0, s1, shot8::kKind);
    lw(v0, s1, shot::kAction);
    a0 = addiu(v0, 56);
    jal(ctx, 0x2E82DCu, gen::fn_btlTargetGetSideMask_002d1600);
    s0 = v0 & 0xFFFF;
    sw(zero, s1, shot::kMotionUnit);
    lw(a0, s1, shot::kAction);
    lhu(v1, a0, act::kFlags2);
    v1 = v1 & 0x10;
    if (v1 != 0) {
        // 0x002e8300
        charge(ctx, 6);
        lw(a0, a0, act::kUnit);
        lhu(v0, a0, unit::kId);
        v0 = addiu(v0, -233);
        at = sltiu(v0, 8);
        if (at == 0) {
            // 0x002e8364
            charge(ctx, 4);
            lw(a0, a0, unit5::kChild);
            a1 = 1;
            jal(ctx, 0x2E836Cu, gen::fn_sub_2880E0_002880e0);
        } else {
            // 0x002e8318
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30144);  // &0x7B8A40
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E8334u:  // table[0, 1, 2, 3, 4, 5, 6, 7]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e8334
            charge(ctx, 12);
            lw(a0, a0, unit5::kChild);
            a1 = 0;
            jal(ctx, 0x2E833Cu, gen::fn_sub_2880E0_002880e0);
            lw(v1, s1, shot::kAction);
            lw(v1, v1, act::kUnit);
            lw(v1, v1, unit5::kChild);
            sw(v1, s1, shot::kMotionUnit);
            v1 = 1;
            sh(v1, s1, shot::kMotion);
        }
    }
    // 0x002e8374
    charge(ctx, 4);
    lhu(v1, s1, shot8::kKind);
    at = sltiu(v1, 7);
    if (at != 0) {
        // 0x002e8384
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -30176);  // &0x7B8A20
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2E83A0u:  // table[1]
            // 0x002e83a0
            charge(ctx, 5);
            lw(v0, s1, shot::kAction);
            lhu(v0, v0, act::kFlags2);
            v0 = v0 & 0x10;
            if (v0 != 0) {
                // 0x002e83c8
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x2E83CCu, gen::fn_sub_2AC540_002ac540);
            } else {
                // 0x002e83b4
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x2E83B8u, gen::fn_sub_2E4A40_002e4a40);
            }
            break;
        case 0x2E83DCu:  // table[2]
            // 0x002e83dc
            charge(ctx, 4);
            v1 = s0 & 0xFFFF;
            v1 = v1 & 0x2;
            if (v1 != 0) {
            L_002e8400:
                charge(ctx, 4);
                v1 = s0 & 0xFFFF;
                v1 = v1 & 0x2;
                if (v1 != 0) {
                L_002e8470:
                    charge(ctx, 4);
                    v1 = s0 & 0xFFFF;
                    v1 = v1 & 0x2;
                    if (v1 == 0) {
                    L_002e8590:
                        charge(ctx, 5);
                        lw(a0, s1, shot::kAction);
                        lhu(v1, a0, act::kFlags2);
                        v1 = v1 & 0x1;
                        if (v1 != 0) {
                            // 0x002e85a4
                            charge(ctx, 4);
                            lw(v0, a0, act::kUnit);
                            lbu(v0, v0, unit::kSide);
                            if (v0 != 0) {
                                // 0x002e8680
                                charge(ctx, 59);
                                a0 = 2;
                                jal(ctx, 0x2E8684u, gen::fn_datCalcRand_002ffbc0);
                                v1 = v0 & 0xFFFF;
                                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                v1 = sll(v0, 2);
                                lw(v0, a0, gbtl4::kBossAiRows);
                                v0 = addu(v0, v1);
                                s0 = addiu(v0, 524);
                                a0 = addiu(sp, 0x4C);
                                a1 = addiu(s0, 4);
                                a2 = addiu(s0, 16);
                                a3 = 0x690000;
                                a3 = addiu(a3, 30848);  // &0x697880
                                jal(ctx, 0x2E86C8u, gen::fn_sub_2A4690_002a4690);
                                lwc1(f2, s0, 4);
                                lwc1(f1, s0, 8);
                                lwc1(f0, s0, 12);
                                swc1(f2, sp, 0x40);
                                swc1(f1, sp, 0x44);
                                swc1(f0, sp, 0x48);
                                a0 = addiu(sp, 0x68);
                                a1 = addiu(s0, 28);
                                a2 = addiu(s0, 40);
                                a3 = 0x690000;
                                a3 = addiu(a3, 30848);  // &0x697880
                                jal(ctx, 0x2E86FCu, gen::fn_sub_2A4690_002a4690);
                                a2 = addiu(sp, 0x5C);
                                lwc1(f2, s0, 28);
                                lwc1(f1, s0, 32);
                                lwc1(f0, s0, 36);
                                swc1(f2, sp, 0x5C);
                                swc1(f1, sp, 0x60);
                                swc1(f0, sp, 0x64);
                                lh(v0, s0, 0);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                v0 = 0x41F00000;
                                mtc1(v0, f0);
                                div_s(f20, f1, f0);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                a0 = addiu(v0, gbtl7::kCamera);
                                a1 = addiu(sp, 0x40);
                                a3 = 1;
                                jal(ctx, 0x2E8750u, gen::fn_sub_2A2290_002a2290);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                a0 = addiu(v0, gbtl7::kCamera);
                                mov_s(f12, f20);
                                jal(ctx, 0x2E8764u, gen::fn_sub_2A3110_002a3110);
                            } else {
                                // 0x002e85b4
                                charge(ctx, 51);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lw(v0, v0, gbtl4::kBossAiRows);
                                s0 = addiu(v0, 940);
                                a0 = addiu(sp, 0x8C);
                                a1 = addiu(s0, 4);
                                a2 = addiu(s0, 16);
                                a3 = 0x690000;
                                a3 = addiu(a3, 30848);  // &0x697880
                                jal(ctx, 0x2E85D4u, gen::fn_sub_2A4690_002a4690);
                                lwc1(f2, s0, 4);
                                lwc1(f1, s0, 8);
                                lwc1(f0, s0, 12);
                                swc1(f2, sp, 0x80);
                                swc1(f1, sp, 0x84);
                                swc1(f0, sp, 0x88);
                                a0 = addiu(sp, 0xA8);
                                a1 = addiu(s0, 28);
                                a2 = addiu(s0, 40);
                                a3 = 0x690000;
                                a3 = addiu(a3, 30848);  // &0x697880
                                jal(ctx, 0x2E8608u, gen::fn_sub_2A4690_002a4690);
                                a2 = addiu(sp, 0x9C);
                                lwc1(f2, s0, 28);
                                lwc1(f1, s0, 32);
                                lwc1(f0, s0, 36);
                                swc1(f2, sp, 0x9C);
                                swc1(f1, sp, 0xA0);
                                swc1(f0, sp, 0xA4);
                                lh(v0, s0, 0);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                v0 = 0x41F00000;
                                mtc1(v0, f0);
                                div_s(f20, f1, f0);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                a0 = addiu(v0, gbtl7::kCamera);
                                a1 = addiu(sp, 0x80);
                                a3 = 1;
                                jal(ctx, 0x2E865Cu, gen::fn_sub_2A2290_002a2290);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                a0 = addiu(v0, gbtl7::kCamera);
                                mov_s(f12, f20);
                                jal(ctx, 0x2E8670u, gen::fn_sub_2A3110_002a3110);
                            }
                            // 0x002e876c
                            charge(ctx, 7);
                            mtc1(zero, f12);
                            lw(a0, s1, shot::kAction);
                            a1 = 0;
                            a2 = 0;
                            a3 = 64;
                            jal(ctx, 0x2E8780u, gen::fn_sub_2A3E80_002a3e80);
                        }
                    } else {
                        // 0x002e8480
                        charge(ctx, 68);
                        a0 = 2;
                        jal(ctx, 0x2E8484u, gen::fn_datCalcRand_002ffbc0);
                        v1 = v0 & 0xFFFF;
                        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        v0 = sll(v1, 1);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        v1 = sll(v0, 2);
                        lw(v0, a0, gbtl4::kBossAiRows);
                        v0 = addu(v0, v1);
                        s0 = addiu(v0, 420);
                        a0 = addiu(sp, 0xCC);
                        a1 = addiu(s0, 4);
                        a2 = addiu(s0, 16);
                        a3 = 0x690000;
                        a3 = addiu(a3, 30848);  // &0x697880
                        jal(ctx, 0x2E84C8u, gen::fn_sub_2A4690_002a4690);
                        lwc1(f2, s0, 4);
                        lwc1(f1, s0, 8);
                        lwc1(f0, s0, 12);
                        swc1(f2, sp, 0xC0);
                        swc1(f1, sp, 0xC4);
                        swc1(f0, sp, 0xC8);
                        a0 = addiu(sp, 0xE8);
                        a1 = addiu(s0, 28);
                        a2 = addiu(s0, 40);
                        a3 = 0x690000;
                        a3 = addiu(a3, 30848);  // &0x697880
                        jal(ctx, 0x2E84FCu, gen::fn_sub_2A4690_002a4690);
                        a2 = addiu(sp, 0xDC);
                        lwc1(f2, s0, 28);
                        lwc1(f1, s0, 32);
                        lwc1(f0, s0, 36);
                        swc1(f2, sp, 0xDC);
                        swc1(f1, sp, 0xE0);
                        swc1(f0, sp, 0xE4);
                        lh(v0, s0, 0);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x41F00000;
                        mtc1(v0, f0);
                        div_s(f20, f1, f0);
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        a0 = addiu(v0, gbtl7::kCamera);
                        a1 = addiu(sp, 0xC0);
                        a3 = 1;
                        jal(ctx, 0x2E8550u, gen::fn_sub_2A2290_002a2290);
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        a0 = addiu(v0, gbtl7::kCamera);
                        mov_s(f12, f20);
                        jal(ctx, 0x2E8564u, gen::fn_sub_2A3110_002a3110);
                        mtc1(zero, f12);
                        lw(a0, s1, shot::kAction);
                        a1 = 0;
                        a2 = 0;
                        a3 = 64;
                        jal(ctx, 0x2E8580u, gen::fn_sub_2A3E80_002a3e80);
                    }
                } else {
                    // 0x002e8410
                    charge(ctx, 7);
                    lw(v0, s1, shot::kAction);
                    lw(v0, v0, act::kUnit);
                    lw(a0, v0, unit::kDat);
                    jal(ctx, 0x2E841Cu, gen::fn_sub_30C3A0_0030c3a0);
                    if (v0 != 0) {
                        // 0x002e842c
                        charge(ctx, 5);
                        lw(a0, s1, shot::kAction);
                        jal(ctx, 0x2E8430u, gen::fn_sub_289F40_00289f40);
                        if (v0 == 0) {
                            goto L_002e845c;
                        }
                        // 0x002e8440
                        charge(ctx, 7);
                        v0 = 0x3F400000;
                        mtc1(v0, f12);
                        a0 = s1;
                        jal(ctx, 0x2E844Cu, gen::fn_sub_2E6A20_002e6a20);
                        break;
                    }
                L_002e845c:
                    charge(ctx, 5);
                    a0 = s1;
                    jal(ctx, 0x2E8460u, gen::fn_sub_2E7DB0_002e7db0);
                }
            } else {
                // 0x002e83ec
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x2E83F0u, gen::fn_sub_2E7DB0_002e7db0);
            }
            break;
        case 0x2E8400u:  // table[4]
            goto L_002e8400;
        case 0x2E8470u:  // table[3, 5]
            goto L_002e8470;
        case 0x2E8590u:  // table[6]
            goto L_002e8590;
        case 0x2E8788u:  // table[0]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002e8788 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x002E8820 sub_2E8820 -- 532 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss-row shot A: the row of sub_2F88C0's index in the boss rows (gBtl +2840, 24-byte steps): eye / target
// +676 / +688 when an enemy in the battle (flags bit 3) has a bad status (datCalcChkBadStatus), else +628 / +640. Cuts
// (sub_351BB0(8), sub_2A3E80(action, 0, 0, 64), sub_2A2170) unless the camera is in state 2 / 34 / 29, then moves
// (sub_2A2290 / sub_2A3110).
// Arguments: a0 the camera shot.
void sub_2E8820(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x002e8820
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, v0, gbtl::kCameraState);
    v0 = 2;
    if (v1 != v0) {
        // 0x002e8850
        charge(ctx, 3);
        v0 = 34;
        if (v1 == v0) {
            goto L_002e8870;
        }
        // 0x002e885c
        charge(ctx, 3);
        v0 = 29;
        if (v1 == v0) {
            goto L_002e8870;
        }
        // 0x002e8868
        charge(ctx, 2);
        // 0x002e887c
        charge(ctx, 1);
        s1 = 1;
        goto L_002e8880;
    }
L_002e8870:
    charge(ctx, 3);
    s1 = 0;
L_002e8880:
    charge(ctx, 7);
    jal(ctx, 0x2E8880u, gen::fn_sub_2F88C0_002f88c0);
    s0 = v0 & 0xFFFF;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s2, v0, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002e88d0
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e889c
        charge(ctx, 4);
        lw(v0, s2, unit::kFlags);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x002e88ac
            charge(ctx, 3);
            lw(a0, s2, unit::kDat);
            if (a0 == 0) {
                goto L_002e88cc;
            }
            // 0x002e88b8
            charge(ctx, 5);
            a1 = 0x100000;
            jal(ctx, 0x2E88BCu, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                goto L_002e88cc;
            }
            break;
        }
    L_002e88cc:
        charge(ctx, 1);
        lw(s2, s2, unit::kPrev);
    }
    // 0x002e88d8
    charge(ctx, 6);
    a0 = addiu(sp, 0x50);
    a1 = addiu(s3, shot::kPoint);
    jal(ctx, 0x2E88E0u, gen::fn_sub_2A4470_002a4470);
    if (s2 != 0) {
        // 0x002e894c
        charge(ctx, 21);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, a0, gbtl4::kBossAiRows);
        v0 = addu(v0, v1);
        s0 = addiu(v0, 676);
        a0 = addiu(sp, 0x78);
        a1 = s0;
        a2 = addiu(s0, 12);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E8980u, gen::fn_sub_2A4690_002a4690);
        lwc1(f2, s0, 0);
        lwc1(f1, s0, 4);
        lwc1(f0, s0, 8);
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        swc1(f0, sp, 0x74);
    } else {
        // 0x002e88f0
        charge(ctx, 23);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, a0, gbtl4::kBossAiRows);
        v0 = addu(v0, v1);
        s0 = addiu(v0, 628);
        a0 = addiu(sp, 0x78);
        a1 = s0;
        a2 = addiu(s0, 12);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E8924u, gen::fn_sub_2A4690_002a4690);
        lwc1(f2, s0, 0);
        lwc1(f1, s0, 4);
        lwc1(f0, s0, 8);
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        swc1(f0, sp, 0x74);
    }
    // 0x002e89a0
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x002e89e8
        charge(ctx, 11);
        a0 = s3;
        a1 = addiu(sp, 0x50);
        a2 = addiu(sp, 0x6C);
        a3 = 1;
        jal(ctx, 0x2E89F8u, gen::fn_sub_2A2290_002a2290);
        v0 = 0x3FA00000;
        mtc1(v0, f12);
        a0 = s3;
        jal(ctx, 0x2E8A0Cu, gen::fn_sub_2A3110_002a3110);
    } else {
        // 0x002e89a8
        charge(ctx, 16);
        a0 = 8;
        jal(ctx, 0x2E89ACu, gen::fn_sub_351BB0_00351bb0);
        mtc1(zero, f12);
        lw(a0, s3, shot::kAction);
        a1 = 0;
        a2 = 0;
        a3 = 64;
        jal(ctx, 0x2E89C8u, gen::fn_sub_2A3E80_002a3e80);
        a0 = s3;
        a1 = addiu(sp, 0x6C);
        jal(ctx, 0x2E89D8u, gen::fn_sub_2A2170_002a2170);
    }
    // 0x002e8a14 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x002E8A40 sub_2E8A40 -- 576 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss-row shot B: as sub_2E8820 with the rows +724 / +772 / +820 chosen by sub_2C09F0(the AI target record) = 2
// / 1 / other (camera states 2 / 34 / 28 move instead of cut).
// Arguments: a0 the camera shot.
void sub_2E8A40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x002e8a40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, v0, gbtl::kCameraState);
    v0 = 2;
    if (v1 != v0) {
        // 0x002e8a70
        charge(ctx, 3);
        v0 = 34;
        if (v1 == v0) {
            goto L_002e8a90;
        }
        // 0x002e8a7c
        charge(ctx, 3);
        v0 = 28;
        if (v1 == v0) {
            goto L_002e8a90;
        }
        // 0x002e8a88
        charge(ctx, 2);
        // 0x002e8a9c
        charge(ctx, 1);
        s1 = 1;
        goto L_002e8aa0;
    }
L_002e8a90:
    charge(ctx, 3);
    s1 = 0;
L_002e8aa0:
    charge(ctx, 16);
    jal(ctx, 0x2E8AA0u, gen::fn_sub_2F88C0_002f88c0);
    s0 = v0 & 0xFFFF;
    lw(v0, s2, shot::kAction);
    a0 = addiu(v0, 136);
    jal(ctx, 0x2E8AB4u, gen::fn_sub_2C09F0_002c09f0);
    s3 = v0 & 0xFFFF;
    a0 = addiu(sp, 0x50);
    a1 = addiu(s2, shot::kPoint);
    jal(ctx, 0x2E8AC8u, gen::fn_sub_2A4470_002a4470);
    v1 = s3 & 0xFFFF;
    v0 = 2;
    if (v1 != v0) {
        // 0x002e8b3c
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x002e8ba4
            charge(ctx, 21);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, a0, gbtl4::kBossAiRows);
            v0 = addu(v0, v1);
            s0 = addiu(v0, 820);
            a0 = addiu(sp, 0x78);
            a1 = s0;
            a2 = addiu(s0, 12);
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E8BD8u, gen::fn_sub_2A4690_002a4690);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, sp, 0x6C);
            swc1(f1, sp, 0x70);
            swc1(f0, sp, 0x74);
        } else {
            // 0x002e8b48
            charge(ctx, 23);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 3);
            lw(v0, a0, gbtl4::kBossAiRows);
            v0 = addu(v0, v1);
            s0 = addiu(v0, 772);
            a0 = addiu(sp, 0x78);
            a1 = s0;
            a2 = addiu(s0, 12);
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2E8B7Cu, gen::fn_sub_2A4690_002a4690);
            lwc1(f2, s0, 0);
            lwc1(f1, s0, 4);
            lwc1(f0, s0, 8);
            swc1(f2, sp, 0x6C);
            swc1(f1, sp, 0x70);
            swc1(f0, sp, 0x74);
        }
    } else {
        // 0x002e8ae0
        charge(ctx, 23);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 3);
        lw(v0, a0, gbtl4::kBossAiRows);
        v0 = addu(v0, v1);
        s0 = addiu(v0, 724);
        a0 = addiu(sp, 0x78);
        a1 = s0;
        a2 = addiu(s0, 12);
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2E8B14u, gen::fn_sub_2A4690_002a4690);
        lwc1(f2, s0, 0);
        lwc1(f1, s0, 4);
        lwc1(f0, s0, 8);
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        swc1(f0, sp, 0x74);
    }
    // 0x002e8bf8
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x002e8c34
        charge(ctx, 11);
        a0 = s2;
        a1 = addiu(sp, 0x50);
        a2 = addiu(sp, 0x6C);
        a3 = 1;
        jal(ctx, 0x2E8C44u, gen::fn_sub_2A2290_002a2290);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = s2;
        jal(ctx, 0x2E8C58u, gen::fn_sub_2A3110_002a3110);
    } else {
        // 0x002e8c00
        charge(ctx, 13);
        mtc1(zero, f12);
        lw(a0, s2, shot::kAction);
        a1 = 0;
        a2 = 0;
        a3 = 64;
        jal(ctx, 0x2E8C14u, gen::fn_sub_2A3E80_002a3e80);
        a0 = s2;
        a1 = addiu(sp, 0x6C);
        jal(ctx, 0x2E8C24u, gen::fn_sub_2A2170_002a2170);
    }
    // 0x002e8c60 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x002E8E20 sub_2E8E20 -- 276 bytes; frame 0x70: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Random boss-row shot on the battle camera (gBtl +32): one of two 52-byte rows at boss rows +524 (datCalcRand(2)):
// the eye +528 / +540 and the target +552 / +564 through sub_2A4690, then sub_2A2290 / sub_2A3110.
// Arguments: none.
void sub_2E8E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002e8e20
    enter(ctx, 69);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    a0 = 2;
    jal(ctx, 0x2E8E34u, gen::fn_datCalcRand_002ffbc0);
    v1 = v0 & 0xFFFF;
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, a0, gbtl4::kBossAiRows);
    v0 = addu(v0, v1);
    s0 = addiu(v0, 524);
    a0 = addiu(sp, 0x3C);
    a1 = addiu(s0, 4);
    a2 = addiu(s0, 16);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8E78u, gen::fn_sub_2A4690_002a4690);
    lwc1(f2, s0, 4);
    lwc1(f1, s0, 8);
    lwc1(f0, s0, 12);
    swc1(f2, sp, 0x30);
    swc1(f1, sp, 0x34);
    swc1(f0, sp, 0x38);
    a0 = addiu(sp, 0x58);
    a1 = addiu(s0, 28);
    a2 = addiu(s0, 40);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8EACu, gen::fn_sub_2A4690_002a4690);
    a2 = addiu(sp, 0x4C);
    lwc1(f2, s0, 28);
    lwc1(f1, s0, 32);
    lwc1(f0, s0, 36);
    swc1(f2, sp, 0x4C);
    swc1(f1, sp, 0x50);
    swc1(f0, sp, 0x54);
    lh(v0, s0, 0);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41F00000;
    mtc1(v0, f0);
    div_s(f20, f1, f0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, gbtl7::kCamera);
    a1 = addiu(sp, 0x30);
    a3 = 1;
    jal(ctx, 0x2E8F00u, gen::fn_sub_2A2290_002a2290);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, gbtl7::kCamera);
    mov_s(f12, f20);
    jal(ctx, 0x2E8F14u, gen::fn_sub_2A3110_002a3110);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002E8F40 sub_2E8F40 -- 276 bytes; frame 0x70: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// Random boss-row shot: as sub_2E8E20 with the rows at boss rows +420.
// Arguments: none.
void sub_2E8F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002e8f40
    enter(ctx, 69);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    a0 = 2;
    jal(ctx, 0x2E8F54u, gen::fn_datCalcRand_002ffbc0);
    v1 = v0 & 0xFFFF;
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, a0, gbtl4::kBossAiRows);
    v0 = addu(v0, v1);
    s0 = addiu(v0, 420);
    a0 = addiu(sp, 0x3C);
    a1 = addiu(s0, 4);
    a2 = addiu(s0, 16);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8F98u, gen::fn_sub_2A4690_002a4690);
    lwc1(f2, s0, 4);
    lwc1(f1, s0, 8);
    lwc1(f0, s0, 12);
    swc1(f2, sp, 0x30);
    swc1(f1, sp, 0x34);
    swc1(f0, sp, 0x38);
    a0 = addiu(sp, 0x58);
    a1 = addiu(s0, 28);
    a2 = addiu(s0, 40);
    a3 = 0x690000;
    a3 = addiu(a3, 30848);  // &0x697880
    jal(ctx, 0x2E8FCCu, gen::fn_sub_2A4690_002a4690);
    a2 = addiu(sp, 0x4C);
    lwc1(f2, s0, 28);
    lwc1(f1, s0, 32);
    lwc1(f0, s0, 36);
    swc1(f2, sp, 0x4C);
    swc1(f1, sp, 0x50);
    swc1(f0, sp, 0x54);
    lh(v0, s0, 0);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41F00000;
    mtc1(v0, f0);
    div_s(f20, f1, f0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, gbtl7::kCamera);
    a1 = addiu(sp, 0x30);
    a3 = 1;
    jal(ctx, 0x2E9020u, gen::fn_sub_2A2290_002a2290);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, gbtl7::kCamera);
    mov_s(f12, f20);
    jal(ctx, 0x2E9034u, gen::fn_sub_2A3110_002a3110);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002E9170 sub_2E9170 -- 324 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement (sub_2FA240's table): party id 1 at (-300, 200) with slot 0, the others at the origin;
// the enemies at the four points of 0x699BE0 in list order. Each position goes to the unit's cell (sub_2D2280 into
// +148 / +150) and to the unit (sub_27F650).
// Arguments: none.
void sub_2E9170(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002e9170
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 0x6A0000;
    lwc1(f3, v1, -25632);  // 0x699BE0
    v1 = 0x6A0000;
    lwc1(f2, v1, -25628);  // 0x699BE4
    v1 = 0x6A0000;
    lwc1(f1, v1, -25624);  // 0x699BE8
    v1 = 0x6A0000;
    lwc1(f0, v1, -25620);  // 0x699BEC
    swc1(f3, sp, 0x30);
    swc1(f2, sp, 0x34);
    swc1(f1, sp, 0x38);
    swc1(f0, sp, 0x3C);
    sw(zero, sp, 0x44);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002e9220
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e91c4
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002e91f0
            charge(ctx, 2);
            sw(zero, sp, 0x40);
            sw(zero, sp, 0x48);
        } else {
            // 0x002e91d4
            charge(ctx, 7);
            v0 = lui(0xC396);
            sw(v0, sp, 0x40);
            v0 = 0x43480000;
            sw(v0, sp, 0x48);
            sb(zero, s0, unit5::kSlot);
        }
        // 0x002e91f8
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x40);
        jal(ctx, 0x2E9204u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x2E9214u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002e9228
    charge(ctx, 5);
    s0 = 0;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002e9294
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e923c
        charge(ctx, 22);
        v0 = dsll32(s0, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 48);
        lwc1(f0, v0, 0);
        swc1(f0, sp, 0x40);
        lwc1(f0, v0, 4);
        swc1(f0, sp, 0x48);
        v0 = addiu(s0, 1);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x40);
        jal(ctx, 0x2E9278u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x2E9288u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002e929c
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002E92C0 sub_2E92C0 -- 396 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Boss battle placement: party ids 5 / 2 / 1 at fixed points with slots 1 / 2 / 0, the enemies by id (276, ...).
// Arguments: none.
void sub_2E92C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e92c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, sp, 0x24);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002e9384
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e92e0
        charge(ctx, 4);
        lhu(a0, s0, unit::kId);
        v0 = 5;
        if (a0 == v0) {
            // 0x002e9348
            charge(ctx, 5);
            sw(zero, sp, 0x20);
            v0 = 0x43C80000;
            sw(v0, sp, 0x28);
            v0 = 1;
            sb(v0, s0, unit5::kSlot);
        } else {
            // 0x002e92f0
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                // 0x002e932c
                charge(ctx, 7);
                v0 = 0x437A0000;
                sw(v0, sp, 0x20);
                v0 = 0x43FA0000;
                sw(v0, sp, 0x28);
                sb(v1, s0, unit5::kSlot);
            } else {
                // 0x002e92fc
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x002e9310
                    charge(ctx, 7);
                    v0 = lui(0xC37A);
                    sw(v0, sp, 0x20);
                    v0 = 0x43FA0000;
                    sw(v0, sp, 0x28);
                    sb(zero, s0, unit5::kSlot);
                } else {
                    // 0x002e9308
                    charge(ctx, 2);
                }
            }
        }
        // 0x002e935c
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2E9368u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2E9378u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002e938c
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002e9430
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e939c
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 276;
        if (v1 == v0) {
            // 0x002e93f8
            charge(ctx, 4);
            v0 = 0x43480000;
            sw(v0, sp, 0x20);
            v0 = 0x42C80000;
            sw(v0, sp, 0x28);
        } else {
            // 0x002e93ac
            charge(ctx, 3);
            v0 = 275;
            if (v1 == v0) {
                // 0x002e93e0
                charge(ctx, 6);
                v0 = lui(0xC348);
                sw(v0, sp, 0x20);
                v0 = 0x42C80000;
                sw(v0, sp, 0x28);
            } else {
                // 0x002e93b8
                charge(ctx, 3);
                v0 = 256;
                if (v1 == v0) {
                    // 0x002e93cc
                    charge(ctx, 5);
                    sw(zero, sp, 0x20);
                    v0 = lui(0xC3C8);
                    sw(v0, sp, 0x28);
                } else {
                    // 0x002e93c4
                    charge(ctx, 2);
                }
            }
        }
        // 0x002e9408
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2E9414u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2E9424u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002e9438
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E9450 sub_2E9450 -- 416 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss opening shot (sub_2FACC0's table): camera sequence sub_2B8F90(0) with script sub_2F87E0(1); the party
// units by id (1, 2, 5, others) and enemy 256; sub_2BC950's packet and sub_2BAF90(sequence, unit 1, enemy, 0, 512)
// queued (sub_27ED20), then sub_2B9030 closes the sequence.
// Arguments: none.
void sub_2E9450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e9450
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2E9468u, gen::fn_sub_2B8F90_002b8f90);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x2E9478u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x2E9488u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    a0 = 0;
    a1 = 0;
    a2 = 0;
    s1 = 0;
    lw(t1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(t2, t1, gbtl::kUnitTail0);
    a3 = 5;
    v1 = 2;
    v0 = 1;
    for (;;) {
        // 0x002e9510
        charge(ctx, 2);
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e94c0
        charge(ctx, 3);
        lhu(t0, t2, unit::kId);
        if (t0 == a3) {
            // 0x002e94fc
            charge(ctx, 3);
            a1 = t2;
        } else {
            // 0x002e94cc
            charge(ctx, 2);
            if (t0 == v1) {
                // 0x002e94f0
                charge(ctx, 3);
                a0 = t2;
            } else {
                // 0x002e94d4
                charge(ctx, 2);
                if (t0 == v0) {
                    // 0x002e94e4
                    charge(ctx, 3);
                    s2 = t2;
                } else {
                    // 0x002e94dc
                    charge(ctx, 2);
                    // 0x002e9508
                    charge(ctx, 1);
                    a2 = t2;
                }
            }
        }
        // 0x002e950c
        charge(ctx, 1);
        lw(t2, t2, unit::kPrev);
    }
    // 0x002e9518
    charge(ctx, 4);
    lw(a3, t1, 344);
    v0 = 256;
    for (;;) {
        // 0x002e9544
        charge(ctx, 2);
        if (a3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e9528
        charge(ctx, 3);
        lhu(v1, a3, unit::kId);
        if (v1 == v0) {
            // 0x002e953c
            charge(ctx, 1);
            s1 = a3;
        } else {
            // 0x002e9534
            charge(ctx, 2);
        }
        // 0x002e9540
        charge(ctx, 1);
        lw(a3, a3, unit::kPrev);
    }
    // 0x002e954c
    charge(ctx, 41);
    jal(ctx, 0x2E954Cu, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2E955Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = s2;
    a2 = s1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2E9578u, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2E958Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x2E95A0u, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2E95C0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2E95CCu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002E95F0 sub_2E95F0 -- 484 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk (sub_2FB690's table), enemy 256: clears gBtl flag 0x2000000, camera script 2, the voice file
// E1A0_99.ADX (sub_2DD690(3, ...)), the enemy's motion 18 (sub_284200), a wait (sub_2B8D60(3, 4095)), sub_27FE90 and
// sub_2A3B40 packets started after the motion packet (start condition kind 4 + its id), and the sequence's camera
// packet (sub_2BAF90).
// Arguments: none.
void sub_2E95F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e95f0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, gbtl::kFlags);
    a0 = 0;
    jal(ctx, 0x2E9620u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2E9630u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2E9640u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl8::kUnitTail1);
    v0 = 256;
    for (;;) {
        // 0x002e967c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e9660
        charge(ctx, 3);
        lhu(v1, a0, unit::kId);
        if (v1 == v0) {
            // 0x002e9674
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002e966c
            charge(ctx, 2);
        }
        // 0x002e9678
        charge(ctx, 1);
        lw(a0, a0, unit::kPrev);
    }
    // 0x002e9684
    charge(ctx, 84);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -25584);  // "E1A0_99.ADX"
    jal(ctx, 0x2E9690u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2E96A0u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2E96C0u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2E96DCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2E96ECu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2E970Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2E9728u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2E9748u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2E9758u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 0;
    jal(ctx, 0x2E9778u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2E9794u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2E97A4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2E97B0u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002E9950 sub_2E9950 -- 368 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// Boss battle placement: party ids 7 / 5 / 1 at fixed points with slots 1 / 2 / 0; enemies 258 / 257 / others
// at their points.
// Arguments: none.
void sub_2E9950(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e9950
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, sp, 0x24);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002e9a18
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e9970
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 7;
        if (v1 == v0) {
            // 0x002e99dc
            charge(ctx, 5);
            sw(zero, sp, 0x20);
            v0 = 0x43AF0000;
            sw(v0, sp, 0x28);
            v0 = 1;
            sb(v0, s0, unit5::kSlot);
        } else {
            // 0x002e9980
            charge(ctx, 3);
            v0 = 5;
            if (v1 == v0) {
                // 0x002e99bc
                charge(ctx, 8);
                v0 = 0x43960000;
                sw(v0, sp, 0x20);
                v0 = 0x437A0000;
                sw(v0, sp, 0x28);
                v0 = 2;
                sb(v0, s0, unit5::kSlot);
            } else {
                // 0x002e998c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002e99a0
                    charge(ctx, 7);
                    v0 = lui(0xC396);
                    sw(v0, sp, 0x20);
                    v0 = 0x437A0000;
                    sw(v0, sp, 0x28);
                    sb(zero, s0, unit5::kSlot);
                } else {
                    // 0x002e9998
                    charge(ctx, 2);
                }
            }
        }
        // 0x002e99f0
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2E99FCu, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2E9A0Cu, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002e9a20
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002e9aa4
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e9a30
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 258;
        if (v1 == v0) {
            // 0x002e9a6c
            charge(ctx, 4);
            v0 = 0x437A0000;
            sw(v0, sp, 0x20);
            v0 = lui(0xC3AF);
            sw(v0, sp, 0x28);
        } else {
            // 0x002e9a40
            charge(ctx, 3);
            v0 = 257;
            if (v1 == v0) {
                // 0x002e9a54
                charge(ctx, 6);
                v0 = lui(0xC37A);
                sw(v0, sp, 0x20);
                v0 = lui(0xC3AF);
                sw(v0, sp, 0x28);
            } else {
                // 0x002e9a4c
                charge(ctx, 2);
            }
        }
        // 0x002e9a7c
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2E9A88u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2E9A98u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002e9aac
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E9AC0 sub_2E9AC0 -- 352 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss opening shot: as sub_2E9450 with party ids 7 / 5 / 1 (sub_2BC950 with 7) and the leader framed alone.
// Arguments: none.
void sub_2E9AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e9ac0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2E9AD4u, gen::fn_sub_2B8F90_002b8f90);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x2E9AE4u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x2E9AF4u, gen::fn_sub_2B90D0_002b90d0);
    s1 = 0;
    a0 = 0;
    a1 = 0;
    a2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(t1, v0, gbtl::kUnitTail0);
    a3 = 7;
    v1 = 5;
    v0 = 1;
    for (;;) {
        // 0x002e9b78
        charge(ctx, 2);
        if (t1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002e9b28
        charge(ctx, 3);
        lhu(t0, t1, unit::kId);
        if (t0 == a3) {
            // 0x002e9b64
            charge(ctx, 3);
            a1 = t1;
        } else {
            // 0x002e9b34
            charge(ctx, 2);
            if (t0 == v1) {
                // 0x002e9b58
                charge(ctx, 3);
                a0 = t1;
            } else {
                // 0x002e9b3c
                charge(ctx, 2);
                if (t0 == v0) {
                    // 0x002e9b4c
                    charge(ctx, 3);
                    s1 = t1;
                } else {
                    // 0x002e9b44
                    charge(ctx, 2);
                    // 0x002e9b70
                    charge(ctx, 1);
                    a2 = t1;
                }
            }
        }
        // 0x002e9b74
        charge(ctx, 1);
        lw(t1, t1, unit::kPrev);
    }
    // 0x002e9b80
    charge(ctx, 40);
    jal(ctx, 0x2E9B80u, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2E9B90u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = s1;
    a2 = s1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2E9BACu, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2E9BC0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x2E9BD4u, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2E9BF4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2E9C00u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E9C20 sub_2E9C20 -- 748 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk packet for enemies 257 / 258 (a btlAction): sets gBtl flag 0x80000, clears 0x2000000; camera
// script 3 and E1A1_99.ADX for 258, script 2 and E1A1_98.ADX for 257; the motion 18 / wait / sub_27FE90 / sub_2A3B40
// chain owned by the action's uid; then by btlCountActiveUnits the support lines (sub_2DB890 / sub_2DB800).
// Arguments: a0 btlAction.
void sub_2E9C20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002e9c20
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a1, gbtl::kFlags);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a1, gbtl::kFlags);
    lw(s2, a0, act::kUnit);
    a0 = 0;
    jal(ctx, 0x2E9C70u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    lhu(v1, s2, unit::kId);
    v0 = 258;
    if (v1 == v0) {
        // 0x002e9ce8
        charge(ctx, 16);
        a0 = 3;
        jal(ctx, 0x2E9CECu, gen::fn_sub_2F87E0_002f87e0);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x2E9CFCu, gen::fn_sub_2B90D0_002b90d0);
        a0 = 3;
        a1 = 0x6A0000;
        a1 = addiu(a1, -25496);  // "E1A1_99.ADX"
        jal(ctx, 0x2E9D10u, gen::fn_sub_2DD690_002dd690);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2E9D20u, gen::fn_sub_27ED20_0027ed20);
    } else {
        // 0x002e9c8c
        charge(ctx, 3);
        v0 = 257;
        if (v1 == v0) {
            // 0x002e9ca0
            charge(ctx, 18);
            a0 = 2;
            jal(ctx, 0x2E9CA4u, gen::fn_sub_2F87E0_002f87e0);
            a0 = s1;
            a1 = v0;
            jal(ctx, 0x2E9CB4u, gen::fn_sub_2B90D0_002b90d0);
            a0 = 3;
            a1 = 0x6A0000;
            a1 = addiu(a1, -25512);  // "E1A1_98.ADX"
            jal(ctx, 0x2E9CC8u, gen::fn_sub_2DD690_002dd690);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2E9CD8u, gen::fn_sub_27ED20_0027ed20);
        } else {
            // 0x002e9c98
            charge(ctx, 2);
        }
    }
    // 0x002e9d28
    charge(ctx, 83);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2E9D40u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 2;
    sh(v1, v0, pkt::kStartDelay);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2E9D64u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2E9D74u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2E9D9Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2E9DB8u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2E9DE0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2E9DF0u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2E9E18u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2E9E34u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 2;
    jal(ctx, 0x2E9E4Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 2;
    a1 = 0x80000;
    jal(ctx, 0x2E9E5Cu, gen::fn_btlCountActiveUnits_002d4e10);
    v1 = v0 & 0xFFFF;
    v0 = 1;
    if (v1 == v0) {
        // 0x002e9e74
        charge(ctx, 18);
        jal(ctx, 0x2E9E74u, gen::fn_sub_2DB890_002db890);
        a0 = v0;
        v1 = 45;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2E9E8Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 32;
        a1 = 23;
        jal(ctx, 0x2E9E9Cu, gen::fn_sub_2DB800_002db800);
        a0 = v0;
        v1 = 45;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2E9EB4u, gen::fn_sub_27ED20_0027ed20);
    }
    // 0x002e9ebc
    charge(ctx, 20);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = 0x400000;
    v0 = v1 | v0;
    sw(v0, a0, gbtl::kFlags);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v0, v1, 24);
    v0 = v0 | 0x7;
    sh(v0, v1, 24);
    a0 = s1;
    jal(ctx, 0x2E9EE4u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002E9F10 sub_2E9F10 -- 328 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Its update: while another action is current (sub_29AD20) and the unit has flag 0x10 it waits; it waits for
// the action's packets (sub_27E390(uid, all)); then clears gBtl flag 0x80000, kills the unit (sub_2D7890(a, 0)),
// sub_29A320, sets flag 0x2000000 and queues the three colour fades (sub_29FA50(16), sub_2A1080(16, 4),
// sub_2A16C0(16)). Returns 1 while waiting, 0 when done.
// Arguments: a0 btlAction.
void sub_2E9F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e9f10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2E9F20u, gen::fn_sub_29AD20_0029ad20);
    if (s0 == v0) {
        // 0x002e9f50
        charge(ctx, 5);
        lw(a0, s0, act::kUnit);
        lw(v1, a0, unit::kFlags);
        v0 = si(-17);
        v0 = v1 & v0;
        sw(v0, a0, unit::kFlags);
    L_002e9f64:
        charge(ctx, 12);
        ld(a0, s0, 0);
        v0 = 0x3FFF0000;
        v0 = v0 | 0xFFFF;
        v1 = dsll32(v0, 0);
        v0 = 0xFFFF;
        v0 = dsll(v0, 16);
        v0 = v0 | 0xFFFF;
        a1 = v0 | v1;
        jal(ctx, 0x2E9F84u, gen::fn_sub_27E390_0027e390);
        if (v0 != 0) {
            // 0x002ea040
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x002e9f94
            charge(ctx, 43);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = lui(0xFFF7);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, gbtl::kFlags);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x2E9FB4u, gen::fn_sub_2D7890_002d7890);
            a0 = s0;
            jal(ctx, 0x2E9FC0u, gen::fn_sub_29A320_0029a320);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = 0x2000000;
            v0 = v1 | v0;
            sw(v0, a0, gbtl::kFlags);
            a0 = 16;
            jal(ctx, 0x2E9FE0u, gen::fn_sub_29FA50_0029fa50);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2E9FF0u, gen::fn_sub_27ED20_0027ed20);
            a0 = 16;
            a1 = 4;
            jal(ctx, 0x2EA000u, gen::fn_sub_2A1080_002a1080);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EA010u, gen::fn_sub_27ED20_0027ed20);
            a0 = 16;
            jal(ctx, 0x2EA01Cu, gen::fn_sub_2A16C0_002a16c0);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EA02Cu, gen::fn_sub_27ED20_0027ed20);
            v0 = 0;
        }
    } else {
        // 0x002e9f30
        charge(ctx, 5);
        lw(v0, s0, act::kUnit);
        lw(v0, v0, unit::kFlags);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            goto L_002e9f64;
        }
        // 0x002e9f44
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002ea044 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EA060 sub_2EA060 -- 428 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (150, 450) slot 2, id 2 at (-150, 450) slot 1, the others from 0x699C80
// with slots from 0x7CC988; enemy 259 at (0, -300).
// Arguments: none.
void sub_2EA060(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002ea060
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 0x6A0000;
    lwc1(f3, v1, -25472);  // 0x699C80
    v1 = 0x6A0000;
    lwc1(f2, v1, -25468);  // 0x699C84
    v1 = 0x6A0000;
    lwc1(f1, v1, -25464);  // 0x699C88
    v1 = 0x6A0000;
    lwc1(f0, v1, -25460);  // 0x699C8C
    swc1(f3, sp, 0x30);
    swc1(f2, sp, 0x34);
    swc1(f1, sp, 0x38);
    swc1(f0, sp, 0x3C);
    lh(a0, gp, -25448);  // 0x7CC988
    lh(v1, gp, -25446);  // 0x7CC98A
    sh(a0, sp, 0x4C);
    sh(v1, sp, 0x4E);
    s0 = 0;
    sw(zero, sp, 0x44);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002ea188
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea0c8
        charge(ctx, 4);
        lhu(a0, s1, unit::kId);
        v1 = 1;
        if (a0 != v1) {
            // 0x002ea0f8
            charge(ctx, 3);
            v0 = 2;
            if (a0 != v0) {
                // 0x002ea120
                charge(ctx, 16);
                v1 = dsll32(s0, 16);
                v1 = dsra32(v1, 16);
                v0 = sll(v1, 3);
                v0 = addu(v0, sp);
                v0 = addiu(v0, 48);
                lwc1(f0, v0, 0);
                swc1(f0, sp, 0x40);
                lwc1(f0, v0, 4);
                swc1(f0, sp, 0x48);
                v0 = sll(v1, 1);
                v0 = addu(v0, sp);
                lh(v0, v0, 76);
                sb(v0, s1, unit5::kSlot);
                v0 = addiu(s0, 1);
                s0 = dsll32(v0, 16);
                s0 = dsra32(s0, 16);
            } else {
                // 0x002ea104
                charge(ctx, 7);
                v0 = lui(0xC316);
                sw(v0, sp, 0x40);
                v0 = 0x43E10000;
                sw(v0, sp, 0x48);
                sb(v1, s1, unit5::kSlot);
            }
        } else {
            // 0x002ea0d8
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x40);
            v0 = 0x43E10000;
            sw(v0, sp, 0x48);
            v0 = 2;
            sb(v0, s1, unit5::kSlot);
        }
        // 0x002ea160
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x40);
        jal(ctx, 0x2EA16Cu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x2EA17Cu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002ea190
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ea1ec
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea1a0
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 259;
        if (v1 == v0) {
            // 0x002ea1b8
            charge(ctx, 3);
            sw(zero, sp, 0x40);
            v0 = lui(0xC396);
            sw(v0, sp, 0x48);
        } else {
            // 0x002ea1b0
            charge(ctx, 2);
        }
        // 0x002ea1c4
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x40);
        jal(ctx, 0x2EA1D0u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x2EA1E0u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ea1f4
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002EA210 sub_2EA210 -- 484 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk, enemy 259: as sub_2E95F0 with E1A2_99.ADX.
// Arguments: none.
void sub_2EA210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ea210
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, gbtl::kFlags);
    a0 = 0;
    jal(ctx, 0x2EA240u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2EA250u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2EA260u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl8::kUnitTail1);
    v0 = 259;
    for (;;) {
        // 0x002ea29c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea280
        charge(ctx, 3);
        lhu(v1, a0, unit::kId);
        if (v1 == v0) {
            // 0x002ea294
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002ea28c
            charge(ctx, 2);
        }
        // 0x002ea298
        charge(ctx, 1);
        lw(a0, a0, unit::kPrev);
    }
    // 0x002ea2a4
    charge(ctx, 84);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -25424);  // "E1A2_99.ADX"
    jal(ctx, 0x2EA2B0u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2EA2C0u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2EA2E0u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2EA2FCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EA30Cu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EA32Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EA348u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EA368u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EA378u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 0;
    jal(ctx, 0x2EA398u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EA3B4u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2EA3C4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2EA3D0u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002EA400 sub_2EA400 -- 400 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (150, 450) slot 2, the others from 0x699CC0 (slots 0x7CC990[0..1]).
// Arguments: none.
void sub_2EA400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002ea400
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -25408);  // &0x699CC0
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002ea420
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x002ea444
    charge(ctx, 12);
    lh(a1, gp, -25440);  // 0x7CC990
    lh(a0, gp, -25438);  // 0x7CC992
    lh(v1, gp, -25436);  // 0x7CC994
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002ea50c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea474
        charge(ctx, 4);
        lhu(v1, s1, unit::kId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002ea4a4
            charge(ctx, 16);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 48);
            lwc1(f0, v0, 0);
            swc1(f0, sp, 0x50);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0x58);
            v0 = sll(v1, 1);
            v0 = addu(v0, sp);
            lh(v0, v0, 72);
            sb(v0, s1, unit5::kSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002ea484
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 0x43E10000;
            sw(v0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, unit5::kSlot);
        }
        // 0x002ea4e4
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EA4F0u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EA500u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002ea514
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ea570
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea524
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 260;
        if (v1 == v0) {
            // 0x002ea53c
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002ea534
            charge(ctx, 2);
        }
        // 0x002ea548
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EA554u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EA564u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ea578
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EA590 sub_2EA590 -- 484 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk, enemy 260: as sub_2E95F0 with E1A3_99.ADX.
// Arguments: none.
void sub_2EA590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ea590
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, gbtl::kFlags);
    a0 = 0;
    jal(ctx, 0x2EA5C0u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2EA5D0u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2EA5E0u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl8::kUnitTail1);
    v0 = 260;
    for (;;) {
        // 0x002ea61c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea600
        charge(ctx, 3);
        lhu(v1, a0, unit::kId);
        if (v1 == v0) {
            // 0x002ea614
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002ea60c
            charge(ctx, 2);
        }
        // 0x002ea618
        charge(ctx, 1);
        lw(a0, a0, unit::kPrev);
    }
    // 0x002ea624
    charge(ctx, 84);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -25344);  // "E1A3_99.ADX"
    jal(ctx, 0x2EA630u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2EA640u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2EA660u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2EA67Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EA68Cu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EA6ACu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EA6C8u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EA6E8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EA6F8u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 0;
    jal(ctx, 0x2EA718u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EA734u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2EA744u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2EA750u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002EA780 sub_2EA780 -- 216 bytes; frame 0x10: ra sp+0x0
// Action start hook (sub_2F9C10's table) for enemies 261 / 262 / 277: 261 / 262 get unit flags 0x400, 0x100,
// 0x200, 0x40 (0x8 / 0x10 cleared), flags2 bit 3 cleared and sub_29A320; 277 gets DatUnit flag 0x40 and unit flag 0x400.
// Arguments: a0 btlAction.
void sub_2EA780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ea780
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v1, a0, act::kFlags2);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002ea798
        charge(ctx, 5);
        lw(a2, a0, act::kUnit);
        lbu(a1, a2, unit::kSide);
        v1 = 1;
        if (a1 == v1) {
            // 0x002ea7ac
            charge(ctx, 4);
            lhu(a1, a2, unit::kId);
            v1 = 262;
            if (a1 != v1) {
                // 0x002ea7bc
                charge(ctx, 3);
                v1 = 261;
                if (a1 == v1) {
                    // 0x002ea800
                    charge(ctx, 3);
                    lw(v0, a2, unit::kFlags);
                    v0 = v0 | 0x400;
                    sw(v0, a2, unit::kFlags);
                    goto L_002ea80c;
                }
                // 0x002ea7c8
                charge(ctx, 3);
                v1 = 277;
                if (a1 == v1) {
                    // 0x002ea7dc
                    charge(ctx, 9);
                    lw(a0, a2, unit::kDat);
                    lhu(v1, a0, 0);
                    v1 = v1 | 0x40;
                    sh(v1, a0, 0);
                    lw(v1, a2, unit::kFlags);
                    v1 = v1 | 0x400;
                    sw(v1, a2, unit::kFlags);
                } else {
                    // 0x002ea7d4
                    charge(ctx, 2);
                }
                // 0x002ea848 (the shared epilogue, written out on this path)
                charge(ctx, 4);
                ld(ra, sp, 0x0);
                sp = addiu(sp, 0x10);
                return;
            }
        L_002ea80c:
            charge(ctx, 15);
            lw(v0, a2, unit::kFlags);
            v0 = v0 | 0x100;
            sw(v0, a2, unit::kFlags);
            v0 = v0 | 0x200;
            sw(v0, a2, unit::kFlags);
            v1 = v0 | 0x40;
            sw(v1, a2, unit::kFlags);
            v0 = si(-9);
            v0 = v1 & v0;
            sw(v0, a2, unit::kFlags);
            lhu(v0, a0, act::kFlags2);
            v0 = v0 & 0xFFF7;
            sh(v0, a0, act::kFlags2);
            jal(ctx, 0x2EA840u, gen::fn_sub_29A320_0029a320);
        }
    }
    // 0x002ea848 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EA860 sub_2EA860 -- 468 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (-150, 450) slot 1, the others from 0x699D10 (slots 0x7CC990[2..3]).
// Arguments: none.
void sub_2EA860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002ea860
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -25328);  // &0x699D10
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002ea880
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x002ea8a4
    charge(ctx, 12);
    lh(a1, gp, -25432);  // 0x7CC998
    lh(a0, gp, -25430);  // 0x7CC99A
    lh(v1, gp, -25428);  // 0x7CC99C
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002ea968
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea8d4
        charge(ctx, 4);
        lhu(v0, s1, unit::kId);
        v1 = 1;
        if (v0 != v1) {
            // 0x002ea900
            charge(ctx, 16);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 48);
            lwc1(f0, v0, 0);
            swc1(f0, sp, 0x50);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0x58);
            v0 = sll(v1, 1);
            v0 = addu(v0, sp);
            lh(v0, v0, 72);
            sb(v0, s1, unit5::kSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002ea8e4
            charge(ctx, 7);
            v0 = lui(0xC316);
            sw(v0, sp, 0x50);
            v0 = 0x43E10000;
            sw(v0, sp, 0x58);
            sb(v1, s1, unit5::kSlot);
        }
        // 0x002ea940
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EA94Cu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EA95Cu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002ea970
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002eaa14
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ea980
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 277;
        if (v1 == v0) {
            // 0x002ea9e0
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC3C8);
            sw(v0, sp, 0x58);
        } else {
            // 0x002ea990
            charge(ctx, 3);
            v0 = 262;
            if (v1 == v0) {
                // 0x002ea9c8
                charge(ctx, 6);
                v0 = 0x43960000;
                sw(v0, sp, 0x50);
                v0 = lui(0xC3FA);
                sw(v0, sp, 0x58);
            } else {
                // 0x002ea99c
                charge(ctx, 3);
                v0 = 261;
                if (v1 == v0) {
                    // 0x002ea9b0
                    charge(ctx, 6);
                    v0 = lui(0xC396);
                    sw(v0, sp, 0x50);
                    v0 = lui(0xC3C8);
                    sw(v0, sp, 0x58);
                } else {
                    // 0x002ea9a8
                    charge(ctx, 2);
                }
            }
        }
        // 0x002ea9ec
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EA9F8u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EAA08u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002eaa1c
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EAB70 sub_2EAB70 -- 52 bytes; frame 0x10: ra sp+0x0
// Creates the form-change event packet sub_2EABF0 / sub_2EB250 (sub_2E4220, no owner).
// Arguments: none.
void sub_2EAB70(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002eab70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x2F0000;
    a0 = addiu(a0, -21520);  // &sub_2EABF0
    a1 = 0x2F0000;
    a1 = addiu(a1, -19888);  // &sub_2EB250
    a2 = 0;
    jal(ctx, 0x2EAB8Cu, gen::fn_sub_2E4220_002e4220);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EABB0 sub_2EABB0 -- 52 bytes; frame 0x10: ra sp+0x0
// Creates the reverse form-change event packet sub_2EB2C0 / sub_2EB9E0.
// Arguments: none.
void sub_2EABB0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002eabb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x2F0000;
    a0 = addiu(a0, -19776);  // &sub_2EB2C0
    a1 = 0x2F0000;
    a1 = addiu(a1, -17952);  // &sub_2EB9E0
    a2 = 0;
    jal(ctx, 0x2EABCCu, gen::fn_sub_2E4220_002e4220);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EABF0 sub_2EABF0 -- 1624 bytes; frame 0xF0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Form change (enemies 261 / 262 leave, 277 enters): sub_395170(5616), gBtl flag 0x80000; 261 / 262 are taken
// out (unit flag 0x8, flags2 bit 3, sub_29A2C0, sub_2D3E00, statuses cleared, sub_2831C0(u, 6)); 277 comes back
// (the reverse, sub_29A320 / sub_2D3FE0); then the HP hand-over (datCalcGetHp / GetMaxHp / SetHp), the camera sequence
// and the packets of the change.
// Arguments: none (packet data unused).
void sub_2EABF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002eabf0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 5616;
    jal(ctx, 0x2EAC10u, gen::fn_sub_395170_00395170);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a0, gbtl::kFlags);
    sw(zero, sp, 0xE8);
    sw(zero, sp, 0xEC);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    for (;;) {
        // 0x002ead88
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002eac44
        charge(ctx, 4);
        lhu(a0, s1, act::kFlags2);
        v0 = a0 & 0x1;
        if (v0 != 0) {
            // 0x002eac54
            charge(ctx, 5);
            lw(s0, s1, act::kUnit);
            lbu(v1, s0, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002eac68
                charge(ctx, 4);
                lhu(v1, s0, unit::kId);
                v0 = 262;
                if (v1 != v0) {
                    // 0x002eac78
                    charge(ctx, 3);
                    v0 = 261;
                    if (v1 == v0) {
                        goto L_002ead08;
                    }
                    // 0x002eac84
                    charge(ctx, 3);
                    v0 = 277;
                    if (v1 == v0) {
                        // 0x002eac98
                        charge(ctx, 3);
                        v0 = a0 & 0x8;
                        if (v0 != 0) {
                            // 0x002eaca4
                            charge(ctx, 22);
                            lw(v1, s0, unit::kFlags);
                            v0 = si(-9);
                            v0 = v1 & v0;
                            sw(v0, s0, unit::kFlags);
                            lhu(v0, s1, act::kFlags2);
                            v0 = v0 & 0xFFF7;
                            sh(v0, s1, act::kFlags2);
                            a0 = s1;
                            jal(ctx, 0x2EACC4u, gen::fn_sub_29A320_0029a320);
                            a0 = s0;
                            jal(ctx, 0x2EACD0u, gen::fn_sub_2D3FE0_002d3fe0);
                            lw(a0, s0, unit::kDat);
                            v0 = 0xFF0000;
                            a1 = v0 | 0xFFFF;  // &0xFFFFFF
                            jal(ctx, 0x2EACE4u, gen::fn_datCalcClearBadStatus_00300560);
                            a0 = s0;
                            a1 = 6;
                            jal(ctx, 0x2EACF4u, gen::fn_sub_2831C0_002831c0);
                        }
                        // 0x002eacfc
                        charge(ctx, 3);
                        s2 = s1;
                    } else {
                        // 0x002eac90
                        charge(ctx, 2);
                    }
                    goto L_002ead84;
                }
            L_002ead08:
                charge(ctx, 3);
                v0 = a0 & 0x8;
                if (v0 == 0) {
                    // 0x002ead14
                    charge(ctx, 22);
                    lw(v0, s0, unit::kFlags);
                    v0 = v0 | 0x8;
                    sw(v0, s0, unit::kFlags);
                    lhu(v0, s1, act::kFlags2);
                    v0 = v0 | 0x8;
                    sh(v0, s1, act::kFlags2);
                    a0 = s1;
                    jal(ctx, 0x2EAD30u, gen::fn_sub_29A2C0_0029a2c0);
                    a0 = s0;
                    a1 = 0;
                    jal(ctx, 0x2EAD40u, gen::fn_sub_2D3E00_002d3e00);
                    lw(a0, s0, unit::kDat);
                    v0 = 0xFF0000;
                    a1 = v0 | 0xFFFF;  // &0xFFFFFF
                    jal(ctx, 0x2EAD54u, gen::fn_datCalcClearBadStatus_00300560);
                    a0 = s0;
                    a1 = 6;
                    jal(ctx, 0x2EAD64u, gen::fn_sub_2831C0_002831c0);
                }
                // 0x002ead6c
                charge(ctx, 6);
                lhu(v0, s0, unit::kId);
                v0 = v0 ^ 0x105;
                v0 = sltu(0, v0);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                sw(s0, v0, 232);
            }
        }
    L_002ead84:
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002ead90
    charge(ctx, 9);
    jal(ctx, 0x2EAD90u, gen::fn_sub_1FDD40_001fdd40);
    lw(v0, s2, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EADA0u, gen::fn_datCalcGetHp_002ffd70);
    s3 = v0 & 0xFFFF;
    if (s3 == 0) {
        // 0x002eadb4
        charge(ctx, 1);
        s3 = 1;
    }
    // 0x002eadb8
    charge(ctx, 10);
    lw(v0, sp, 0xE8);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EADC0u, gen::fn_datCalcGetMaxHp_002ffdf0);
    a1 = v0 & 0xFFFF;
    s1 = s3 & 0xFFFF;
    lw(v0, sp, 0xE8);
    at = slt(a1, s1);
    if (at == 0) {
        // 0x002eade8
        charge(ctx, 1);
        a1 = s3;
    } else {
        // 0x002eade0
        charge(ctx, 2);
    }
    // 0x002eadec
    charge(ctx, 12);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EADF0u, gen::fn_datCalcSetHp_002ffd90);
    lw(v0, sp, 0xEC);
    s0 = addiu(v0, 2604);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EAE04u, gen::fn_datCalcGetMaxHp_002ffdf0);
    v0 = v0 & 0xFFFF;
    at = slt(v0, s1);
    if (at == 0) {
        // 0x002eae24
        charge(ctx, 1);
        v0 = s3;
    } else {
        // 0x002eae1c
        charge(ctx, 2);
    }
    // 0x002eae28
    charge(ctx, 85);
    a1 = v0 & 0xFFFF;
    lw(s3, sp, 0xEC);
    lw(a0, s0, 0);
    jal(ctx, 0x2EAE34u, gen::fn_datCalcSetHp_002ffd90);
    lw(a0, sp, 0xE8);
    a1 = 6;
    jal(ctx, 0x2EAE44u, gen::fn_sub_2831C0_002831c0);
    a0 = s3;
    a1 = 6;
    jal(ctx, 0x2EAE54u, gen::fn_sub_2831C0_002831c0);
    a0 = s2;
    jal(ctx, 0x2EAE60u, gen::fn_sub_2E4240_002e4240);
    a0 = 0;
    jal(ctx, 0x2EAE6Cu, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 358;
    a1 = addiu(sp, 0x60);
    jal(ctx, 0x2EAE80u, gen::fn_sub_2BB6F0_002bb6f0);
    a0 = s1;
    a1 = addiu(sp, 0x60);
    a2 = 0;
    jal(ctx, 0x2EAE94u, gen::fn_sub_2BAC00_002bac00);
    s0 = v0;
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2EAEB0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 358;
    a1 = 0;
    jal(ctx, 0x2EAEC0u, gen::fn_sub_2DD4A0_002dd4a0);
    s4 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x2EAEE4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    lw(a1, sp, 0xE8);
    a2 = s3;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2EAF00u, gen::fn_sub_2BAF90_002baf90);
    s3 = v0;
    a0 = 4;
    sb(a0, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sb(a0, v0, 16);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, 24);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s3;
    a1 = 2;
    jal(ctx, 0x2EAF38u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    jal(ctx, 0x2EAF44u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s3, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EAF64u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kBossWork0);
    if (v0 == 0) {
        // 0x002eaf7c
        charge(ctx, 21);
        jal(ctx, 0x2EAF7Cu, gen::fn_sub_2DB890_002db890);
        a0 = v0;
        v1 = 30;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2EAF94u, gen::fn_sub_27ED20_0027ed20);
        a0 = 32;
        a1 = 31;
        jal(ctx, 0x2EAFA4u, gen::fn_sub_2DB800_002db800);
        a0 = v0;
        v1 = 30;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2EAFBCu, gen::fn_sub_27ED20_0027ed20);
        v1 = 1;
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(v1, v0, gbtl::kBossWork0);
    }
    // 0x002eafd0
    charge(ctx, 158);
    lw(a0, s2, act::kUnit);
    jal(ctx, 0x2EAFD4u, gen::fn_sub_285F20_00285f20);
    s4 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s3, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s4;
    a1 = 0;
    jal(ctx, 0x2EB008u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s2, act::kUnit);
    a1 = 358;
    jal(ctx, 0x2EB018u, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 3;
    jal(ctx, 0x2EB040u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, sp, 0xE8);
    jal(ctx, 0x2EB04Cu, gen::fn_sub_285E50_00285e50);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB074u, gen::fn_sub_27ED20_0027ed20);
    lw(s0, sp, 0xEC);
    a0 = s0;
    jal(ctx, 0x2EB084u, gen::fn_sub_285E50_00285e50);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB0ACu, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, sp, 0xE8);
    a1 = 24;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x2EB0CCu, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB0F4u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s0;
    a1 = 24;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x2EB114u, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB13Cu, gen::fn_sub_27ED20_0027ed20);
    lw(a0, sp, 0xE8);
    a1 = 14;
    a2 = 0;
    a3 = 3;
    jal(ctx, 0x2EB154u, gen::fn_sub_2DD830_002dd830);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB17Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EB18Cu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB1B4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EB1C4u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s4, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s2, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB1ECu, gen::fn_sub_27ED20_0027ed20);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = 0x400000;
    v0 = v1 | v0;
    sw(v0, a0, gbtl::kFlags);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v0, v1, 24);
    v0 = v0 | 0x7;
    sh(v0, v1, 24);
    a0 = s1;
    jal(ctx, 0x2EB21Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x002EB250 sub_2EB250 -- 112 bytes; frame 0x10: ra sp+0x0
// Its end check: 1 while the packet's owner still has packets (sub_27E390); else clears gBtl flag 0x80000, 0.
// Arguments: a0 the packet data (u64 owner uid at +0).
void sub_2EB250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002eb250
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2EB278u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002eb2ac
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002eb288
        charge(ctx, 9);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        v0 = 0;
    }
    // 0x002eb2b0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EB2C0 sub_2EB2C0 -- 1816 bytes; frame 0x100: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Reverse form change (277 leaves, 261 / 262 return): as sub_2EABF0 with the roles swapped.
// Arguments: none.
void sub_2EB2C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002eb2c0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a0, gbtl::kFlags);
    sw(zero, sp, 0xF8);
    sw(zero, sp, 0xFC);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    for (;;) {
        // 0x002eb450
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002eb30c
        charge(ctx, 4);
        lhu(a0, s1, act::kFlags2);
        v0 = a0 & 0x1;
        if (v0 != 0) {
            // 0x002eb31c
            charge(ctx, 5);
            lw(s0, s1, act::kUnit);
            lbu(v1, s0, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002eb330
                charge(ctx, 4);
                lhu(v1, s0, unit::kId);
                v0 = 262;
                if (v1 != v0) {
                    // 0x002eb340
                    charge(ctx, 3);
                    v0 = 261;
                    if (v1 == v0) {
                        goto L_002eb3d0;
                    }
                    // 0x002eb34c
                    charge(ctx, 3);
                    v0 = 277;
                    if (v1 == v0) {
                        // 0x002eb360
                        charge(ctx, 3);
                        v0 = a0 & 0x8;
                        if (v0 == 0) {
                            // 0x002eb36c
                            charge(ctx, 22);
                            lw(v0, s0, unit::kFlags);
                            v0 = v0 | 0x8;
                            sw(v0, s0, unit::kFlags);
                            lhu(v0, s1, act::kFlags2);
                            v0 = v0 | 0x8;
                            sh(v0, s1, act::kFlags2);
                            a0 = s1;
                            jal(ctx, 0x2EB388u, gen::fn_sub_29A2C0_0029a2c0);
                            a0 = s0;
                            a1 = 0;
                            jal(ctx, 0x2EB398u, gen::fn_sub_2D3E00_002d3e00);
                            lw(a0, s0, unit::kDat);
                            v0 = 0xFF0000;
                            a1 = v0 | 0xFFFF;  // &0xFFFFFF
                            jal(ctx, 0x2EB3ACu, gen::fn_datCalcClearBadStatus_00300560);
                            a0 = s0;
                            a1 = 6;
                            jal(ctx, 0x2EB3BCu, gen::fn_sub_2831C0_002831c0);
                        }
                        // 0x002eb3c4
                        charge(ctx, 3);
                        s4 = s1;
                    } else {
                        // 0x002eb358
                        charge(ctx, 2);
                    }
                    goto L_002eb44c;
                }
            L_002eb3d0:
                charge(ctx, 3);
                v0 = a0 & 0x8;
                if (v0 != 0) {
                    // 0x002eb3dc
                    charge(ctx, 22);
                    lw(v1, s0, unit::kFlags);
                    v0 = si(-9);
                    v0 = v1 & v0;
                    sw(v0, s0, unit::kFlags);
                    lhu(v0, s1, act::kFlags2);
                    v0 = v0 & 0xFFF7;
                    sh(v0, s1, act::kFlags2);
                    a0 = s1;
                    jal(ctx, 0x2EB3FCu, gen::fn_sub_29A320_0029a320);
                    a0 = s0;
                    jal(ctx, 0x2EB408u, gen::fn_sub_2D3FE0_002d3fe0);
                    lw(a0, s0, unit::kDat);
                    v0 = 0xFF0000;
                    a1 = v0 | 0xFFFF;  // &0xFFFFFF
                    jal(ctx, 0x2EB41Cu, gen::fn_datCalcClearBadStatus_00300560);
                    a0 = s0;
                    a1 = 6;
                    jal(ctx, 0x2EB42Cu, gen::fn_sub_2831C0_002831c0);
                }
                // 0x002eb434
                charge(ctx, 6);
                lhu(v0, s0, unit::kId);
                v0 = v0 ^ 0x105;
                v0 = sltu(0, v0);
                v0 = sll(v0, 2);
                v0 = addu(v0, sp);
                sw(s0, v0, 248);
            }
        }
    L_002eb44c:
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002eb458
    charge(ctx, 17);
    jal(ctx, 0x2EB458u, gen::fn_sub_1FDD40_001fdd40);
    lw(v0, sp, 0xF8);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EB468u, gen::fn_datCalcGetHp_002ffd70);
    s0 = v0 & 0xFFFF;
    lw(v0, sp, 0xFC);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EB47Cu, gen::fn_datCalcGetHp_002ffd70);
    v1 = v0 & 0xFFFF;
    v0 = s0 & 0xFFFF;
    v1 = addu(v0, v1);
    v0 = sra(v1, 1);
    if (i64(v1) < 0) {
        // 0x002eb49c
        charge(ctx, 2);
        v0 = addiu(v1, 1);
        v0 = sra(v0, 1);
    }
    // 0x002eb4a4
    charge(ctx, 3);
    s0 = v0 & 0xFFFF;
    if (s0 == 0) {
        // 0x002eb4b0
        charge(ctx, 1);
        s0 = 1;
    }
    // 0x002eb4b4
    charge(ctx, 10);
    lw(v0, s4, act::kUnit);
    lw(a0, v0, unit::kDat);
    jal(ctx, 0x2EB4BCu, gen::fn_datCalcGetMaxHp_002ffdf0);
    a1 = v0 & 0xFFFF;
    lw(v1, s4, act::kUnit);
    v0 = s0 & 0xFFFF;
    at = slt(a1, v0);
    if (at == 0) {
        // 0x002eb4e4
        charge(ctx, 1);
        a1 = s0;
    } else {
        // 0x002eb4dc
        charge(ctx, 2);
    }
    // 0x002eb4e8
    charge(ctx, 316);
    lw(a0, v1, unit::kDat);
    jal(ctx, 0x2EB4ECu, gen::fn_datCalcSetHp_002ffd90);
    lw(a0, s4, act::kUnit);
    a1 = 6;
    jal(ctx, 0x2EB4FCu, gen::fn_sub_2831C0_002831c0);
    a0 = s4;
    jal(ctx, 0x2EB508u, gen::fn_sub_2E4240_002e4240);
    a0 = 0;
    jal(ctx, 0x2EB514u, gen::fn_sub_2B8F90_002b8f90);
    s3 = v0;
    a0 = 357;
    a1 = addiu(sp, 0x70);
    jal(ctx, 0x2EB528u, gen::fn_sub_2BB6F0_002bb6f0);
    a0 = s3;
    a1 = addiu(sp, 0x70);
    a2 = 0;
    jal(ctx, 0x2EB53Cu, gen::fn_sub_2BAC00_002bac00);
    s5 = v0;
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s5;
    a1 = 1;
    jal(ctx, 0x2EB558u, gen::fn_sub_27ED20_0027ed20);
    a0 = 357;
    a1 = 0;
    jal(ctx, 0x2EB568u, gen::fn_sub_2DD4A0_002dd4a0);
    s1 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s5, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x2EB58Cu, gen::fn_sub_27ED20_0027ed20);
    lw(s0, sp, 0xFC);
    a0 = s3;
    lw(a1, sp, 0xF8);
    a2 = s0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2EB5ACu, gen::fn_sub_2BAF90_002baf90);
    s2 = v0;
    a0 = 4;
    sb(a0, v0, 0);
    ld(v1, s5, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sb(a0, v0, 16);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, 24);
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x2EB5DCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    jal(ctx, 0x2EB5E8u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EB608u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EB618u, gen::fn_sub_2B8D60_002b8d60);
    s1 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x2EB64Cu, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s4, act::kUnit);
    a1 = 357;
    jal(ctx, 0x2EB65Cu, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 3;
    jal(ctx, 0x2EB684u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, sp, 0xF8);
    a1 = 23;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x2EB6A4u, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB6CCu, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s0;
    a1 = 23;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x2EB6ECu, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB714u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, sp, 0xF8);
    jal(ctx, 0x2EB720u, gen::fn_sub_284C90_00284c90);
    s5 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s5;
    a1 = 1;
    jal(ctx, 0x2EB74Cu, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, sp, 0xF8);
    a1 = 25;
    a2 = 8;
    a3 = 1;
    jal(ctx, 0x2EB76Cu, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s5, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB794u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2EB7A0u, gen::fn_sub_284C90_00284c90);
    s5 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s5;
    a1 = 1;
    jal(ctx, 0x2EB7CCu, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s0;
    a1 = 25;
    a2 = 8;
    a3 = 1;
    jal(ctx, 0x2EB7ECu, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s5, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EB814u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EB824u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB84Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 2;
    a1 = 4095;
    jal(ctx, 0x2EB85Cu, gen::fn_sub_2B8D60_002b8d60);
    s1 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x2EB888u, gen::fn_sub_27ED20_0027ed20);
    a0 = s4;
    a1 = 31;
    jal(ctx, 0x2EB898u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 30;
    sh(v1, v0, 74);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB8C8u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s4, act::kUnit);
    jal(ctx, 0x2EB8D4u, gen::fn_sub_285E50_00285e50);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB8FCu, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s4, act::kUnit);
    a1 = 0;
    jal(ctx, 0x2EB90Cu, gen::fn_sub_2843E0_002843e0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB934u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, sp, 0xF8);
    jal(ctx, 0x2EB940u, gen::fn_sub_285F20_00285f20);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB968u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2EB974u, gen::fn_sub_285F20_00285f20);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s4, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EB99Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s3;
    jal(ctx, 0x2EB9A8u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x100);
}

// 0x002EB9E0 sub_2EB9E0 -- 112 bytes; frame 0x10: ra sp+0x0
// Its end check: as sub_2EB250.
// Arguments: a0 the packet data.
void sub_2EB9E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002eb9e0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2EBA08u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002eba3c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002eba18
        charge(ctx, 9);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        v0 = 0;
    }
    // 0x002eba40 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EBA50 sub_2EBA50 -- 1124 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk when both enemies 261 and 262 are down (datCalcIsDead): finds unit 277's action when a0 is 0;
// sets gBtl flag 0x80000, clears 0x2000000; the speaker's line E1A4_97 / 98 / 99.ADX, camera script, motion 18 and the
// wait / sub_27FE90 / sub_2A3B40 chain.
// Arguments: a0 btlAction or 0.
void sub_2EBA50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002eba50
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s7 = a0;
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, a1, gbtl::kFlags);
    v1 = lui(0xFDFF);
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    sw(v1, a1, gbtl::kFlags);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, a1, gbtl::kFlags);
    v1 = 0x80000;
    v1 = a0 | v1;
    sw(v1, a1, gbtl::kFlags);
    s4 = s7;
    if (s4 == 0) {
        // 0x002ebab4
        charge(ctx, 6);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s4, v1, gbtl::kActionList);
        v1 = 277;
        a1 = 1;
        for (;;) {
            // 0x002ebafc
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002ebacc
            charge(ctx, 4);
            lhu(a0, s4, act::kFlags2);
            a0 = a0 & 0x1;
            if (a0 != 0) {
                // 0x002ebadc
                charge(ctx, 4);
                lw(a2, s4, act::kUnit);
                lbu(a0, a2, unit::kSide);
                if (a0 != a1) {
                    goto L_002ebaf8;
                }
                // 0x002ebaec
                charge(ctx, 3);
                lhu(a0, a2, unit::kId);
                if (a0 != v1) {
                    goto L_002ebaf8;
                }
                break;
            }
        L_002ebaf8:
            charge(ctx, 1);
            lw(s4, s4, act::kNext);
        }
    }
    // 0x002ebb04
    charge(ctx, 7);
    s2 = 0;
    sw(zero, sp, 0x90);
    sw(zero, sp, 0x94);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ebb70
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ebb20
        charge(ctx, 6);
        lw(a0, s0, unit::kDat);
        a1 = 0;
        jal(ctx, 0x2EBB28u, gen::fn_datCalcIsDead_0030b5a0);
        if (v0 != 0) {
            // 0x002ebb38
            charge(ctx, 4);
            lhu(a0, s0, unit::kId);
            v1 = 262;
            if (a0 == v1) {
                // 0x002ebb68
                charge(ctx, 1);
                sw(s0, sp, 0x94);
            } else {
                // 0x002ebb48
                charge(ctx, 3);
                v1 = 261;
                if (a0 == v1) {
                    // 0x002ebb5c
                    charge(ctx, 3);
                    sw(s0, sp, 0x90);
                } else {
                    // 0x002ebb54
                    charge(ctx, 2);
                }
            }
        }
        // 0x002ebb6c
        charge(ctx, 1);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ebb78
    charge(ctx, 3);
    lw(v1, sp, 0x90);
    if (v1 != 0) {
        // 0x002ebb84
        charge(ctx, 3);
        lw(s0, sp, 0x94);
        if (s0 == 0) {
            goto L_002ebb90;
        }
        // 0x002ebbfc
        charge(ctx, 6);
        a0 = 0;
        jal(ctx, 0x2EBC00u, gen::fn_sub_2B8F90_002b8f90);
        s5 = v0;
        if (s7 != 0) {
            // 0x002ebc54
            charge(ctx, 4);
            lw(v1, s4, act::kUnit);
            lw(v0, sp, 0x90);
            if (v1 != v0) {
                // 0x002ebca4
                charge(ctx, 2);
                if (v1 == s0) {
                    // 0x002ebcac
                    charge(ctx, 14);
                    s1 = s0;
                    sw(s1, sp, 0x98);
                    sw(zero, sp, 0x9C);
                    s6 = s1;
                    s2 = 4;
                    a0 = 3;
                    a1 = 0x6A0000;
                    a1 = addiu(a1, -25184);  // "E1A4_99.ADX"
                    jal(ctx, 0x2EBCCCu, gen::fn_sub_2DD690_002dd690);
                    a0 = v0;
                    a1 = 1;
                    jal(ctx, 0x2EBCDCu, gen::fn_sub_27ED20_0027ed20);
                }
            } else {
                // 0x002ebc64
                charge(ctx, 16);
                sw(v0, sp, 0x98);
                sw(zero, sp, 0x9C);
                s1 = v0;
                s6 = v0;
                s2 = 3;
                a0 = s2;
                a1 = 0x6A0000;
                a1 = addiu(a1, -25200);  // "E1A4_98.ADX"
                jal(ctx, 0x2EBC84u, gen::fn_sub_2DD690_002dd690);
                a0 = v0;
                a1 = 1;
                jal(ctx, 0x2EBC94u, gen::fn_sub_27ED20_0027ed20);
            }
        } else {
            // 0x002ebc14
            charge(ctx, 16);
            lw(s1, sp, 0x90);
            sw(s1, sp, 0x98);
            sw(s0, sp, 0x9C);
            s6 = s0;
            s2 = 2;
            a0 = 3;
            a1 = 0x6A0000;
            a1 = addiu(a1, -25216);  // "E1A4_97.ADX"
            jal(ctx, 0x2EBC34u, gen::fn_sub_2DD690_002dd690);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EBC44u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x002ebce4
        charge(ctx, 10);
        a0 = s2 & 0xFFFF;
        jal(ctx, 0x2EBCE8u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s5;
        a1 = v0;
        jal(ctx, 0x2EBCF8u, gen::fn_sub_2B90D0_002b90d0);
        s0 = 0;
        for (;;) {
            // 0x002ebd68
            charge(ctx, 3);
            v0 = slti(s0, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002ebd0c
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 152);
            lw(a0, v0, 0);
            if (a0 != 0) {
                // 0x002ebd24
                charge(ctx, 16);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a1 = 18;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x2EBD38u, gen::fn_sub_284200_00284200);
                s3 = v0;
                v1 = 3;
                sh(v1, v0, pkt::kStartDelay);
                ld(v1, s4, 0);
                sd(v1, v0, pkt::kOwner);
                a0 = s3;
                a1 = 1;
                jal(ctx, 0x2EBD5Cu, gen::fn_sub_27ED20_0027ed20);
            }
            // 0x002ebd64
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x002ebd74
        charge(ctx, 18);
        a0 = 3;
        a1 = 4095;
        jal(ctx, 0x2EBD7Cu, gen::fn_sub_2B8D60_002b8d60);
        a0 = v0;
        v1 = 4;
        sb(v1, v0, 0);
        ld(v1, s3, pkt::kId);
        sd(v1, v0, bcore::kCondArg);
        ld(v1, s4, 0);
        sd(v1, v0, pkt::kOwner);
        a1 = 1;
        jal(ctx, 0x2EBDA4u, gen::fn_sub_27ED20_0027ed20);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s0, v0, gbtl8::kUnitTail1);
        for (;;) {
            // 0x002ebe04
            charge(ctx, 2);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002ebdbc
            charge(ctx, 18);
            a0 = s0;
            a1 = 0;
            a2 = 0x690000;
            a2 = addiu(a2, 30896);  // &0x6978B0
            a3 = 0;
            jal(ctx, 0x2EBDD0u, gen::fn_sub_27FE90_0027fe90);
            a0 = v0;
            v1 = 4;
            sb(v1, v0, 0);
            ld(v1, s3, pkt::kId);
            sd(v1, v0, bcore::kCondArg);
            ld(v1, s4, 0);
            sd(v1, v0, pkt::kOwner);
            a1 = 1;
            jal(ctx, 0x2EBDF8u, gen::fn_sub_27ED20_0027ed20);
            lw(s0, s0, unit::kPrev);
        }
        // 0x002ebe0c
        charge(ctx, 30);
        a0 = 0;
        a1 = 1;
        jal(ctx, 0x2EBE14u, gen::fn_sub_2A3B40_002a3b40);
        a0 = v0;
        v1 = 4;
        sb(v1, v0, 0);
        ld(v1, s3, pkt::kId);
        sd(v1, v0, bcore::kCondArg);
        ld(v1, s4, 0);
        sd(v1, v0, pkt::kOwner);
        a1 = 0;
        jal(ctx, 0x2EBE3Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = s5;
        a1 = s1;
        a2 = s6;
        a3 = 0;
        t0 = 512;
        jal(ctx, 0x2EBE58u, gen::fn_sub_2BAF90_002baf90);
        a0 = v0;
        ld(v1, s4, 0);
        sd(v1, v0, pkt::kOwner);
        a1 = 2;
        jal(ctx, 0x2EBE70u, gen::fn_sub_27ED20_0027ed20);
        a0 = s5;
        jal(ctx, 0x2EBE7Cu, gen::fn_sub_2B9030_002b9030);
        // 0x002ebe84 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(ra, sp, 0x80);
        lq(s7, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xA0);
        return;
    }
L_002ebb90:
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x002ebbe8
        charge(ctx, 3);
        v1 = slti(s0, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ebb9c
        charge(ctx, 6);
        v1 = sll(s0, 2);
        v1 = addu(v1, sp);
        v1 = addiu(v1, 144);
        lw(a0, v1, 0);
        if (a0 != 0) {
            // 0x002ebbb4
            charge(ctx, 12);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            a1 = 18;
            a2 = 0;
            a3 = 2;
            jal(ctx, 0x2EBBC8u, gen::fn_sub_284200_00284200);
            s3 = v0;
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x2EBBDCu, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x002ebbe4
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x002ebbf4
    charge(ctx, 2);
    // 0x002ebe84 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x002EBEC0 sub_2EBEC0 -- 308 bytes; frame 0x10: ra sp+0x0
// Its update: unit 277's action when a0 is 0; 1 while its packets run; then clears gBtl flag 0x80000, sets
// 0x2000000 and queues the three colour fades; 0.
// Arguments: a0 btlAction or 0.
void sub_2EBEC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ebec0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x002ebed0
        charge(ctx, 6);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl::kActionList);
        v0 = 277;
        a1 = 1;
        for (;;) {
            // 0x002ebf18
            charge(ctx, 2);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002ebee8
            charge(ctx, 4);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x002ebef8
                charge(ctx, 4);
                lw(a2, a0, act::kUnit);
                lbu(v1, a2, unit::kSide);
                if (v1 != a1) {
                    goto L_002ebf14;
                }
                // 0x002ebf08
                charge(ctx, 3);
                lhu(v1, a2, unit::kId);
                if (v1 != v0) {
                    goto L_002ebf14;
                }
                break;
            }
        L_002ebf14:
            charge(ctx, 1);
            lw(a0, a0, act::kNext);
        }
    }
    // 0x002ebf20
    charge(ctx, 12);
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2EBF40u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002ebfe0
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002ebf50
        charge(ctx, 36);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = 0x2000000;
        v0 = v1 | v0;
        sw(v0, a0, gbtl::kFlags);
        a0 = 16;
        jal(ctx, 0x2EBF80u, gen::fn_sub_29FA50_0029fa50);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EBF90u, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        a1 = 4;
        jal(ctx, 0x2EBFA0u, gen::fn_sub_2A1080_002a1080);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EBFB0u, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        jal(ctx, 0x2EBFBCu, gen::fn_sub_2A16C0_002a16c0);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EBFCCu, gen::fn_sub_27ED20_0027ed20);
        v0 = 0;
    }
    // 0x002ebfe4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EC000 sub_2EC000 -- 400 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (150, 450) slot 2, the others from 0x699DB0 (slots 0x7CC990[4..5]).
// Arguments: none.
void sub_2EC000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002ec000
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -25168);  // &0x699DB0
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002ec020
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x002ec044
    charge(ctx, 12);
    lh(a1, gp, -25424);  // 0x7CC9A0
    lh(a0, gp, -25422);  // 0x7CC9A2
    lh(v1, gp, -25420);  // 0x7CC9A4
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002ec10c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ec074
        charge(ctx, 4);
        lhu(v1, s1, unit::kId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002ec0a4
            charge(ctx, 16);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 48);
            lwc1(f0, v0, 0);
            swc1(f0, sp, 0x50);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0x58);
            v0 = sll(v1, 1);
            v0 = addu(v0, sp);
            lh(v0, v0, 72);
            sb(v0, s1, unit5::kSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002ec084
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 0x43E10000;
            sw(v0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, unit5::kSlot);
        }
        // 0x002ec0e4
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EC0F0u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EC100u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002ec114
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ec170
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ec124
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 263;
        if (v1 == v0) {
            // 0x002ec13c
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC3C8);
            sw(v0, sp, 0x58);
        } else {
            // 0x002ec134
            charge(ctx, 2);
        }
        // 0x002ec148
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EC154u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EC164u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ec178
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EC2C0 sub_2EC2C0 -- 484 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk, enemy 263: as sub_2E95F0 with E1A5_99.ADX.
// Arguments: none.
void sub_2EC2C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ec2c0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, gbtl::kFlags);
    a0 = 0;
    jal(ctx, 0x2EC2F0u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2EC300u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2EC310u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl8::kUnitTail1);
    v0 = 263;
    for (;;) {
        // 0x002ec34c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ec330
        charge(ctx, 3);
        lhu(v1, a0, unit::kId);
        if (v1 == v0) {
            // 0x002ec344
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002ec33c
            charge(ctx, 2);
        }
        // 0x002ec348
        charge(ctx, 1);
        lw(a0, a0, unit::kPrev);
    }
    // 0x002ec354
    charge(ctx, 84);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -25104);  // "E1A5_99.ADX"
    jal(ctx, 0x2EC360u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2EC370u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2EC390u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2EC3ACu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EC3BCu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EC3DCu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EC3F8u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EC418u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EC428u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 0;
    jal(ctx, 0x2EC448u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EC464u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2EC474u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2EC480u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002EC5C0 sub_2EC5C0 -- 452 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (150, 550) slot 2, the others from 0x699E00 (slots 0x7CC990[6..7]).
// Arguments: none.
void sub_2EC5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002ec5c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -25088);  // &0x699E00
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002ec5e0
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x002ec604
    charge(ctx, 12);
    lh(a1, gp, -25416);  // 0x7CC9A8
    lh(a0, gp, -25414);  // 0x7CC9AA
    lh(v1, gp, -25412);  // 0x7CC9AC
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002ec6d8
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ec634
        charge(ctx, 4);
        lhu(v1, s1, unit::kId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002ec670
            charge(ctx, 16);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 48);
            lwc1(f0, v0, 0);
            swc1(f0, sp, 0x50);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0x58);
            v0 = sll(v1, 1);
            v0 = addu(v0, sp);
            lh(v0, v0, 72);
            sb(v0, s1, unit5::kSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002ec644
            charge(ctx, 11);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 550;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, unit5::kSlot);
        }
        // 0x002ec6b0
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EC6BCu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EC6CCu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002ec6e0
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ec764
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ec6f0
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 266;
        if (v1 == v0) {
            // 0x002ec72c
            charge(ctx, 4);
            v0 = 0x43C80000;
            sw(v0, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002ec700
            charge(ctx, 3);
            v0 = 265;
            if (v1 == v0) {
                // 0x002ec714
                charge(ctx, 6);
                v0 = lui(0xC3C8);
                sw(v0, sp, 0x50);
                v0 = lui(0xC396);
                sw(v0, sp, 0x58);
            } else {
                // 0x002ec70c
                charge(ctx, 2);
            }
        }
        // 0x002ec73c
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EC748u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EC758u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ec76c
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EC790 sub_2EC790 -- 508 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss opening shot for enemies 266 / 265: the camera sequence (script 1), sub_2BAF90(266, 265), motions 10 / 12
// of 266 (sub_2DD830, start delays 64 / 132) and the call packet sub_27F410(sub_2ECBE0, 265) at 140.
// Arguments: none.
void sub_2EC790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ec790
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a1, v0, gbtl8::kUnitTail1);
    v0 = 265;
    v1 = 266;
    for (;;) {
        // 0x002ec7f8
        charge(ctx, 2);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ec7c8
        charge(ctx, 3);
        lhu(a0, a1, unit::kId);
        if (a0 == v1) {
            // 0x002ec7f0
            charge(ctx, 1);
            s1 = a1;
        } else {
            // 0x002ec7d4
            charge(ctx, 2);
            if (a0 == v0) {
                // 0x002ec7e4
                charge(ctx, 3);
                s0 = a1;
            } else {
                // 0x002ec7dc
                charge(ctx, 2);
            }
        }
        // 0x002ec7f4
        charge(ctx, 1);
        lw(a1, a1, unit::kPrev);
    }
    // 0x002ec800
    charge(ctx, 99);
    a0 = 0;
    jal(ctx, 0x2EC804u, gen::fn_sub_2B8F90_002b8f90);
    s3 = v0;
    a0 = 1;
    jal(ctx, 0x2EC814u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s3;
    a1 = v0;
    jal(ctx, 0x2EC824u, gen::fn_sub_2B90D0_002b90d0);
    a0 = s3;
    a1 = s1;
    a2 = s0;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EC840u, gen::fn_sub_2BAF90_002baf90);
    s2 = v0;
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x2EC854u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = 10;
    a2 = 0;
    a3 = 6;
    jal(ctx, 0x2EC86Cu, gen::fn_sub_2DD830_002dd830);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 64;
    sh(v1, v0, pkt::kStartDelay);
    a1 = 1;
    jal(ctx, 0x2EC894u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = 12;
    a2 = 0;
    a3 = 7;
    jal(ctx, 0x2EC8ACu, gen::fn_sub_2DD830_002dd830);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 132;
    sh(v1, v0, pkt::kStartDelay);
    a1 = 1;
    jal(ctx, 0x2EC8D4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0x2F0000;
    a0 = addiu(a0, -13344);  // &sub_2ECBE0
    a1 = s0;
    jal(ctx, 0x2EC8E8u, gen::fn_sub_27F410_0027f410);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 140;
    sh(v1, v0, pkt::kStartDelay);
    a1 = 1;
    jal(ctx, 0x2EC910u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s0;
    a1 = 0;
    a2 = 0;
    a3 = 1;
    jal(ctx, 0x2EC930u, gen::fn_sub_284200_00284200);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 140;
    sh(v1, v0, pkt::kStartDelay);
    a1 = 1;
    jal(ctx, 0x2EC958u, gen::fn_sub_27ED20_0027ed20);
    a0 = s3;
    jal(ctx, 0x2EC964u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002EC990 sub_2EC990 -- 304 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Unit hook (sub_2FD520) for enemy 265 with a model: when gBtl +2896 is set and sub_318540(model, 0) is 6 it
// sets the model's +216 bit 0x80 and steps the unit's fade level (+67) down by 8 (to 1); otherwise clears the bit and fades
// it up by 8 (to 255); either step sets model flag 0x4.
// Arguments: a0 btlUnit.
void sub_2EC990(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ec990
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(a0, a0, unit::kSide);
    v1 = 1;
    if (a0 == v1) {
        // 0x002ec9b0
        charge(ctx, 4);
        lhu(a0, s0, unit::kId);
        v1 = 265;
        if (a0 == v1) {
            // 0x002ec9c0
            charge(ctx, 4);
            lw(v1, s0, unit::kModelFlags);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x002ec9d0
                charge(ctx, 9);
                lw(a0, s0, unit::kModel);
                a1 = 0;
                jal(ctx, 0x2EC9D8u, gen::fn_sub_318540_00318540);
                a0 = v0 & 0xFFFF;
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v1, v1, gbtl::kBossWork3);
                if (v1 != 0) {
                    // 0x002ec9f4
                    charge(ctx, 4);
                    a0 = a0 & 0xFFFF;
                    v1 = 6;
                    if (a0 != v1) {
                        goto L_002eca5c;
                    }
                    // 0x002eca04
                    charge(ctx, 8);
                    lw(a0, s0, unit::kModel);
                    lhu(v1, a0, 216);
                    v1 = v1 | 0x80;
                    sh(v1, a0, 216);
                    lbu(v1, s0, 67);
                    at = slti(v1, 2);
                    if (at == 0) {
                        // 0x002eca24
                        charge(ctx, 3);
                        at = slti(v1, 10);
                        if (at != 0) {
                            // 0x002eca40
                            charge(ctx, 2);
                            v1 = 1;
                            sb(v1, s0, 67);
                        } else {
                            // 0x002eca30
                            charge(ctx, 4);
                            v1 = addiu(v1, -8);
                            sb(v1, s0, 67);
                        }
                        // 0x002eca48
                        charge(ctx, 5);
                        lw(v1, s0, unit::kModelFlags);
                        v1 = v1 | 0x4;
                        sw(v1, s0, unit::kModelFlags);
                    }
                    // 0x002ecaac (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(ra, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x20);
                    return;
                }
            L_002eca5c:
                charge(ctx, 8);
                lw(a0, s0, unit::kModel);
                lhu(v1, a0, 216);
                v1 = v1 & 0xFF7F;
                sh(v1, a0, 216);
                lbu(v1, s0, 67);
                at = slti(v1, 255);
                if (at != 0) {
                    // 0x002eca7c
                    charge(ctx, 3);
                    at = slti(v1, 247);
                    if (at == 0) {
                        // 0x002eca98
                        charge(ctx, 2);
                        v1 = 255;
                        sb(v1, s0, 67);
                    } else {
                        // 0x002eca88
                        charge(ctx, 4);
                        v1 = addiu(v1, 8);
                        sb(v1, s0, 67);
                    }
                    // 0x002ecaa0
                    charge(ctx, 3);
                    lw(v1, s0, unit::kModelFlags);
                    v1 = v1 | 0x4;
                    sw(v1, s0, unit::kModelFlags);
                }
            }
        }
    }
    // 0x002ecaac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002ECB30 sub_2ECB30 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Boss command hook (sub_2D0AF0): gBtl +2900 = a1; a unit with bad status 4 attacks (command kind 1, skill
// sub_308930, sub_2C3770(a, 0)) and returns 0; else it creates the event packet sub_2ED350 / sub_2ED360 for the action
// and returns 1.
// Arguments: a0 btlAction, a1 u16.
void sub_2ECB30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ecb30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    sh(a1, v0, gbtl::kBossWork4);
    lw(v0, a0, act::kUnit);
    lw(a0, v0, unit::kDat);
    a1 = 4;
    jal(ctx, 0x2ECB54u, gen::fn_datCalcChkBadStatus_00300580);
    if (v0 != 0) {
        // 0x002ecb88
        charge(ctx, 14);
        v0 = 1;
        sh(v0, s0, act::kCmdKind);
        lw(v0, s0, act::kUnit);
        lw(a0, v0, unit::kDat);
        jal(ctx, 0x2ECB98u, gen::fn_sub_308930_00308930);
        sh(v0, s0, act::kCmdSkill);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x2ECBACu, gen::fn_sub_2C3770_002c3770);
        v0 = 0;
    } else {
        // 0x002ecb64
        charge(ctx, 9);
        a0 = 0x2F0000;
        a0 = addiu(a0, -11440);  // &sub_2ED350
        a1 = 0x2F0000;
        a1 = addiu(a1, -11424);  // &sub_2ED360
        a2 = s0;
        jal(ctx, 0x2ECB78u, gen::fn_sub_2E4220_002e4220);
        // 0x002ecbc0
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x002ecbc4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002ECBE0 sub_2ECBE0 -- 60 bytes; frame 0x10: ra sp+0x0
// Call packet (sub_27F410's callback, queued by sub_2EC790 for enemy 265): gBtl +2896 = 1 and the flags2 bit 3 of the
// unit's action (sub_29A1D0) cleared; returns 1.
// Arguments: a0 btlUnit.
void sub_2ECBE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ecbe0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2ECBE8u, gen::fn_sub_29A1D0_0029a1d0);
    a0 = 1;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(a0, v1, gbtl::kBossWork3);
    lhu(v1, v0, act::kFlags2);
    v1 = v1 & 0xFFF7;
    sh(v1, v0, act::kFlags2);
    v0 = a0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002ECC20 sub_2ECC20 -- 56 bytes; frame 0x10: ra sp+0x0
// Call packet: the reverse of sub_2ECBE0 (gBtl +2896 = 0, the unit's action's flags2 bit 3 set); returns 1.
// Arguments: a0 btlUnit.
void sub_2ECC20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ecc20
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2ECC28u, gen::fn_sub_29A1D0_0029a1d0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(zero, v1, gbtl::kBossWork3);
    lhu(v1, v0, act::kFlags2);
    v1 = v1 | 0x8;
    sh(v1, v0, act::kFlags2);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002ECC60 sub_2ECC60 -- 792 bytes; frame 0xF0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Picks the node pair for the event of sub_2ECF80: a table by gBtl +2884's unit id (226..230: 0x699E60 ..
// 0x699F90, 8-byte rows ended by -1), the nearest node of the first unit's model (sub_318ED0, sub_4C6B20) to node 21
// of the second's; writes the pick to a0 / a1 (s16, -1 when none).
// Arguments: a0 s16* out, a1 s16* out.
void sub_2ECC60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f20{ctx, 20}, f21{ctx, 21};
    // 0x002ecc60
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s5 = a1;
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, a0, gbtl::kBossWork0);
    lhu(v1, v0, unit::kId);
    v0 = 230;
    if (v1 == v0) {
        // 0x002ecd28
        charge(ctx, 2);
        s3 = 0x6A0000;
        s3 = addiu(s3, -24688);  // &0x699F90
    } else {
        // 0x002eccb0
        charge(ctx, 3);
        v0 = 229;
        if (v1 == v0) {
            // 0x002ecd18
            charge(ctx, 4);
            s3 = 0x6A0000;
            s3 = addiu(s3, -24752);  // &0x699F50
        } else {
            // 0x002eccbc
            charge(ctx, 3);
            v0 = 228;
            if (v1 == v0) {
                // 0x002ecd08
                charge(ctx, 4);
                s3 = 0x6A0000;
                s3 = addiu(s3, -24832);  // &0x699F00
            } else {
                // 0x002eccc8
                charge(ctx, 3);
                v0 = 227;
                if (v1 == v0) {
                    // 0x002eccf8
                    charge(ctx, 4);
                    s3 = 0x6A0000;
                    s3 = addiu(s3, -24912);  // &0x699EB0
                } else {
                    // 0x002eccd4
                    charge(ctx, 3);
                    v0 = 226;
                    if (v1 == v0) {
                        // 0x002ecce8
                        charge(ctx, 4);
                        s3 = 0x6A0000;
                        s3 = addiu(s3, -24992);  // &0x699E60
                    } else {
                        // 0x002ecce0
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    // 0x002ecd30
    charge(ctx, 10);
    s1 = si(-1);
    s6 = s1;
    lw(v0, a0, 2888);
    lw(a0, v0, unit::kModel);
    a1 = 21;
    a2 = addiu(sp, 0xE0);
    jal(ctx, 0x2ECD48u, gen::fn_sub_318ED0_00318ed0);
    if (v0 != 0) {
        // 0x002ecd58
        charge(ctx, 5);
        lwc1(f21, sp, 0xE0);
        lwc1(f20, sp, 0xE8);
        s2 = 0;
        for (;;) {
            // 0x002ecf08
            charge(ctx, 8);
            v1 = s2 & 0xFFFF;
            v1 = sll(v1, 3);
            s0 = addu(s3, v1);
            s7 = addiu(s0, 4);
            lh(a0, s0, 4);
            v1 = si(-1);
            if (a0 == v1) {
                break;
            }
            backedge(ctx);
            // 0x002ecd6c
            charge(ctx, 9);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v0, v0, gbtl::kBossWork0);
            lh(a1, s0, 0);
            lw(a0, v0, unit::kModel);
            a2 = addiu(sp, 0xC0);
            jal(ctx, 0x2ECD80u, gen::fn_sub_318ED0_00318ed0);
            if (v0 != 0) {
                // 0x002ecd90
                charge(ctx, 9);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kBossWork0);
                lh(a1, s0, 2);
                lw(a0, v0, unit::kModel);
                a2 = addiu(sp, 0xCC);
                jal(ctx, 0x2ECDA4u, gen::fn_sub_318ED0_00318ed0);
                if (v0 == 0) {
                    goto L_002ecf00;
                }
                // 0x002ecdb4
                charge(ctx, 73);
                lwc1(f1, sp, 0xCC);
                mtc1(zero, f3);
                lwc1(f0, sp, 0xC0);
                add_s(f0, f3, f0);
                add_s(f0, f1, f0);
                v0 = 0x40400000;
                mtc1(v0, f2);
                div_s(f0, f0, f2);
                sub_s(f0, f0, f3);
                swc1(f0, sp, 0xA0);
                lwc1(f1, sp, 0xD4);
                lwc1(f0, sp, 0xC8);
                add_s(f0, f3, f0);
                add_s(f0, f1, f0);
                div_s(f0, f0, f2);
                sub_s(f0, f0, f3);
                swc1(f0, sp, 0xA4);
                a0 = addiu(sp, 0xA0);
                a1 = a0;
                jal(ctx, 0x2ECE04u, gen::fn_sub_4C6B20_004c6b20);
                lwc1(f2, sp, 0xC8);
                lwc1(f0, sp, 0xC0);
                mtc1(zero, f1);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0xA8);
                sub_s(f0, f2, f1);
                swc1(f0, sp, 0xAC);
                a0 = addiu(sp, 0xA8);
                a1 = a0;
                jal(ctx, 0x2ECE34u, gen::fn_sub_4C6B20_004c6b20);
                lwc1(f0, sp, 0xCC);
                mtc1(zero, f1);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0xB0);
                lwc1(f0, sp, 0xD4);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0xB4);
                a0 = addiu(sp, 0xB0);
                a1 = a0;
                jal(ctx, 0x2ECE64u, gen::fn_sub_4C6B20_004c6b20);
                mtc1(zero, f1);
                sub_s(f0, f21, f1);
                swc1(f0, sp, 0xB8);
                sub_s(f0, f20, f1);
                swc1(f0, sp, 0xBC);
                a0 = addiu(sp, 0xB8);
                a1 = a0;
                jal(ctx, 0x2ECE8Cu, gen::fn_sub_4C6B20_004c6b20);
                lwc1(f5, sp, 0xA4);
                lwc1(f4, sp, 0xA0);
                lwc1(f1, sp, 0xB0);
                lwc1(f0, sp, 0xB4);
                mula_s(f5, f0);
                madd_s(f3, f4, f1);
                lwc1(f1, sp, 0xB8);
                lwc1(f0, sp, 0xBC);
                mula_s(f5, f0);
                madd_s(f2, f4, f1);
                lwc1(f1, sp, 0xA8);
                lwc1(f0, sp, 0xAC);
                mula_s(f5, f0);
                madd_s(f0, f4, f1);
                c_le_s(f0, f2);
                if (!cond(ctx)) {
                    goto L_002ecf00;
                }
                // 0x002eced8
                charge(ctx, 3);
                c_le_s(f3, f2);
                if (!cond(ctx)) {
                    goto L_002ecf00;
                }
                goto L_002ecee4_17;
            }
        L_002ecf00:
            charge(ctx, 2);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
    }
L_002ecf28:
    charge(ctx, 2);
    if (s4 != 0) {
        // 0x002ecf30
        charge(ctx, 1);
        sh(s1, s4, 0);
    }
    // 0x002ecf34
    charge(ctx, 2);
    if (s5 != 0) {
        // 0x002ecf3c
        charge(ctx, 1);
        sh(s6, s5, 0);
    }
    // 0x002ecf40 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
    return;
L_002ecee4_17:
    charge(ctx, 7);
    v1 = s2 & 0xFFFF;
    v1 = sll(v1, 3);
    lh(s1, s7, 0);
    v1 = addu(v1, s3);
    lh(s6, v1, 6);
    goto L_002ecf28;
}

// 0x002ECF80 sub_2ECF80 -- 964 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// Event packet update: follows gBtl +2888's model node 20 (sub_318D10, sub_4C6BE0, sub_2D1DE0, sub_27F680),
// picks the node pair (sub_2ECC60) and steps gBtl +2902's state (timer +2908, pick +2912 / +2914; sub_283C50,
// sub_1FF3D0 / sub_1FF410 / sub_1FF3F0, sub_2DD5E0 packets).
// Arguments: a0 the packet data (a btlAction).
void sub_2ECF80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x002ecf80
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl::kBossWork1);
    lw(v0, v1, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x002ecfa8
        charge(ctx, 7);
        lw(a0, v1, unit::kModel);
        a1 = 20;
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2ECFB4u, gen::fn_sub_318D10_00318d10);
        if (v0 != 0) {
            // 0x002ecfc4
            charge(ctx, 27);
            a0 = addiu(sp, 0x80);
            a1 = 0x690000;
            a1 = addiu(a1, 30864);  // &0x697890
            a2 = addiu(sp, 0x20);
            jal(ctx, 0x2ECFD4u, gen::fn_sub_4C6BE0_004c6be0);
            lwc1(f1, sp, 0x50);
            lwc1(f0, sp, 0x80);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x90);
            lwc1(f1, sp, 0x54);
            lwc1(f0, sp, 0x84);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x94);
            lwc1(f1, sp, 0x58);
            lwc1(f0, sp, 0x88);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x98);
            a0 = addiu(sp, 0x60);
            a1 = addiu(sp, 0x50);
            a2 = addiu(sp, 0x90);
            jal(ctx, 0x2ED018u, gen::fn_sub_2D1DE0_002d1de0);
            lw(a0, s0, act::kUnit);
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x2ED028u, gen::fn_sub_27F680_0027f680);
        }
    }
    // 0x002ed030
    charge(ctx, 10);
    a0 = addiu(sp, 0x9E);
    a1 = addiu(sp, 0x9C);
    jal(ctx, 0x2ED038u, gen::fn_sub_2ECC60_002ecc60);
    lw(a3, gp, kGpBtl);  // gBtl 0x7CE3EC
    a2 = addiu(a3, gbtl8::kEvState);
    lhu(a1, a3, gbtl8::kEvState);
    v0 = 3;
    if (a1 != v0) {
        // 0x002ed058
        charge(ctx, 3);
        a0 = 2;
        if (a1 == a0) {
            // 0x002ed178
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2382);  // gPadFlags
            v0 = v0 & 0x40;
            if (v0 == 0) {
                // 0x002ed18c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, 2392);  // 0x7E0958
                v0 = v0 & 0x40;
                if (v0 != 0) {
                    goto L_002ed1a0;
                }
                goto L_002ed2a0;
            }
        L_002ed1a0:
            charge(ctx, 13);
            v0 = 3;
            sh(v0, a2, 0);
            jal(ctx, 0x2ED1A8u, gen::fn_sub_1FF3F0_001ff3f0);
            a0 = 1;
            jal(ctx, 0x2ED1B4u, gen::fn_sub_2DD5E0_002dd5e0);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2ED1C4u, gen::fn_sub_27ED20_0027ed20);
        } else {
            // 0x002ed064
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x002ed0ec
                charge(ctx, 7);
                lwc1(f12, a3, 2908);
                v0 = 0x40400000;
                mtc1(v0, f0);
                c_lt_s(f12, f0);
                if (!cond(ctx)) {
                    // 0x002ed16c
                    charge(ctx, 3);
                    sh(a0, a2, 0);
                } else {
                    // 0x002ed108
                    charge(ctx, 22);
                    lw(a0, a3, 2884);
                    jal(ctx, 0x2ED10Cu, gen::fn_sub_283C50_00283c50);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(a0, v0, gbtl::kBossWork1);
                    lwc1(f12, v0, gbtl8::kEvTimer);
                    jal(ctx, 0x2ED120u, gen::fn_sub_283C50_00283c50);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lwc1(f1, v0, gbtl8::kEvTimer);
                    lwc1(f0, gp, -32004);  // 0x7CAFEC
                    add_s(f0, f1, f0);
                    swc1(f0, v0, gbtl8::kEvTimer);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    v1 = addiu(v0, gbtl8::kEvTimer);
                    lwc1(f1, v0, gbtl8::kEvTimer);
                    v0 = 0x40400000;
                    mtc1(v0, f0);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        // 0x002ed160
                        charge(ctx, 3);
                        swc1(f0, v1, 0);
                    }
                }
            } else {
                // 0x002ed070
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x002ed080
                    charge(ctx, 27);
                    sw(zero, a3, 2908);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sh(v1, v0, gbtl8::kEvState);
                    v1 = si(-1);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sh(v1, v0, gbtl8::kEvPick);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sh(v1, v0, gbtl8::kEvPick2);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sw(zero, v0, 2916);
                    v0 = 405;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x78);
                    v0 = 347;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x7C);
                    jal(ctx, 0x2ED0D0u, gen::fn_sub_1FF3D0_001ff3d0);
                    a0 = addiu(sp, 0x78);
                    jal(ctx, 0x2ED0DCu, gen::fn_sub_1FF410_001ff410);
                } else {
                    // 0x002ed078
                    charge(ctx, 2);
                }
            }
        }
        goto L_002ed2a0;
    }
    // 0x002ed1d4
    charge(ctx, 4);
    lh(v1, sp, 0x9E);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x002ed1e4
        charge(ctx, 4);
        sh(v1, a3, 2912);
        lh(v1, sp, 0x9C);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sh(v1, v0, gbtl8::kEvPick2);
    }
    // 0x002ed1f4
    charge(ctx, 7);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a0 = addiu(v0, gbtl8::kEvTimer);
    lwc1(f1, v0, gbtl8::kEvTimer);
    lwc1(f0, gp, -32052);  // 0x7CAFBC
    c_le_s(f1, f0);
    if (cond(ctx)) {
        // 0x002ed220
        charge(ctx, 4);
        lh(v1, v0, 2912);
        v0 = si(-1);
        if (v1 == v0) {
            // 0x002ed23c
            charge(ctx, 1);
            swc1(f0, a0, 0);
        } else {
            // 0x002ed230
            charge(ctx, 3);
            sw(zero, a0, 0);
        }
    } else {
        // 0x002ed210
        charge(ctx, 4);
        sub_s(f0, f1, f0);
        swc1(f0, a0, 0);
    }
    // 0x002ed240
    charge(ctx, 17);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kBossWork0);
    lwc1(f12, v0, gbtl8::kEvTimer);
    jal(ctx, 0x2ED24Cu, gen::fn_sub_283C50_00283c50);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kBossWork1);
    lwc1(f12, v0, gbtl8::kEvTimer);
    jal(ctx, 0x2ED260u, gen::fn_sub_283C50_00283c50);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lwc1(f1, v0, gbtl8::kEvTimer);
    mtc1(zero, f0);
    c_eq_s(f0, f1);
    if (!cond(ctx)) {
    L_002ed2a0:
        charge(ctx, 6);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v0, v1, gbtl::kBossWork1);
        lw(v0, v0, unit::kModelFlags);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x002ed2b8
            charge(ctx, 20);
            v0 = 0x40400000;
            mtc1(v0, f1);
            lwc1(f0, v1, 2908);
            div_s(f3, f0, f1);
            v0 = 0x3F000000;
            mtc1(v0, f2);
            lwc1(f1, v1, 2916);
            mtc1(zero, f0);
            adda_s(f0, f1);
            madd_s(f0, f2, f3);
            swc1(f0, v1, 2916);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lwc1(f1, v0, 2916);
            v0 = 0x3F800000;
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (!cond(ctx)) {
                // 0x002ed308
                charge(ctx, 9);
                a0 = 0;
                jal(ctx, 0x2ED30Cu, gen::fn_sub_2DD5E0_002dd5e0);
                a0 = v0;
                a1 = 1;
                jal(ctx, 0x2ED31Cu, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(zero, v0, 2916);
            }
        }
        // 0x002ed32c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002ed284
        charge(ctx, 4);
        lh(v1, v0, 2912);
        v0 = si(-1);
        if (v1 == v0) {
            goto L_002ed2a0;
        }
        // 0x002ed294
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002ed330 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x002ED360 sub_2ED360 -- 4820 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss event packet update (sub_2ECB30's): by gBtl +2904 -- state 2 runs sub_352C50 on the boss work units and,
// once the action's packets end, sets the command (kind 2, skill gBtl +2912), sub_2C3770 / sub_2D6620 and two camera
// sequences (scripts 5 / 6) with their packets; other states create units (btlUnitCreate), place them and queue the
// event's motions and calls.
// Arguments: a0 btlAction.
void sub_2ED360(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x002ed360
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
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
    ld(s0, a0, 0);
    lw(a2, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, a2, gbtl8::kEvState2);
    v0 = 3;
    if (v1 != v0) {
        // 0x002ed3a8
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x002ee000
            charge(ctx, 17);
            lw(a0, a2, 2888);
            lw(a1, a2, 2884);
            lw(a2, a2, 2892);
            jal(ctx, 0x2EE00Cu, gen::fn_sub_352C50_00352c50);
            ld(a0, s4, 0);
            v0 = 0x3FFF0000;
            v0 = v0 | 0xFFFF;
            v1 = dsll32(v0, 0);
            v0 = 0xFFFF;
            v0 = dsll(v0, 16);
            v0 = v0 | 0xFFFF;
            a1 = v0 | v1;
            jal(ctx, 0x2EE034u, gen::fn_sub_27E390_0027e390);
            if (v0 == 0) {
                // 0x002ee044
                charge(ctx, 15);
                v0 = 2;
                sh(v0, s4, act::kCmdKind);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lh(v0, v0, gbtl8::kEvPick);
                sh(v0, s4, act::kCmdSkill);
                a0 = s4;
                a1 = 0;
                jal(ctx, 0x2EE060u, gen::fn_sub_2C3770_002c3770);
                a0 = s4;
                jal(ctx, 0x2EE06Cu, gen::fn_sub_2D6620_002d6620);
                s1 = 0;
                for (;;) {
                    // 0x002ee0c0
                    charge(ctx, 3);
                    v0 = sltiu(s1, 2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002ee080
                    charge(ctx, 16);
                    v0 = sll(s1, 2);
                    v0 = addu(v0, sp);
                    s2 = addiu(v0, 264);
                    a0 = 0;
                    jal(ctx, 0x2EE090u, gen::fn_sub_2B8F90_002b8f90);
                    sw(v0, s2, 0);
                    v0 = addiu(s1, 5);
                    a0 = v0 & 0xFFFF;
                    jal(ctx, 0x2EE0A4u, gen::fn_sub_2F87E0_002f87e0);
                    lw(a0, s2, 0);
                    a1 = v0;
                    jal(ctx, 0x2EE0B4u, gen::fn_sub_2B90D0_002b90d0);
                    s1 = addiu(s1, 1);
                }
                // 0x002ee0cc
                charge(ctx, 29);
                lw(a1, s4, act::kUnit);
                lw(a0, sp, 0x108);
                a2 = a1;
                a3 = 0;
                t0 = 512;
                jal(ctx, 0x2EE0E0u, gen::fn_sub_2BAF90_002baf90);
                s6 = v0;
                sd(s0, v0, pkt::kOwner);
                a0 = s6;
                a1 = 2;
                jal(ctx, 0x2EE0F8u, gen::fn_sub_27ED20_0027ed20);
                a0 = 20;
                jal(ctx, 0x2EE104u, gen::fn_sub_2A16C0_002a16c0);
                a0 = v0;
                v1 = 5;
                sb(v1, v0, 0);
                ld(v1, s6, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EE128u, gen::fn_sub_27ED20_0027ed20);
                s7 = 0;
                s1 = 0;
                for (;;) {
                    // 0x002ee358
                    charge(ctx, 4);
                    lhu(v0, s4, act::kTargetCount);
                    v0 = sltu(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002ee140
                    charge(ctx, 30);
                    v0 = sll(s1, 2);
                    v0 = addu(s4, v0);
                    lw(s3, v0, act::kTargets);
                    lbu(v0, s3, 200);
                    sq(v0, sp, 0xA0);
                    lw(a0, s3, act::kUnit);
                    jal(ctx, 0x2EE158u, gen::fn_sub_2BD480_002bd480);
                    a0 = v0;
                    sd(s0, v0, pkt::kOwner);
                    a1 = 1;
                    jal(ctx, 0x2EE16Cu, gen::fn_sub_27ED20_0027ed20);
                    lw(a0, sp, 0x108);
                    lw(a1, s4, act::kUnit);
                    lw(a2, s3, act::kUnit);
                    a3 = 1;
                    t0 = 512;
                    jal(ctx, 0x2EE188u, gen::fn_sub_2BAF90_002baf90);
                    fp = v0;
                    sh(s7, v0, pkt::kStartDelay);
                    sd(s0, v0, pkt::kOwner);
                    a0 = fp;
                    a1 = 2;
                    jal(ctx, 0x2EE1A4u, gen::fn_sub_27ED20_0027ed20);
                    s2 = 0;
                    for (;;) {
                        // 0x002ee340
                        charge(ctx, 4);
                        lq(v0, sp, 0xA0);
                        v0 = sltu(s2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002ee1b8
                        charge(ctx, 24);
                        v0 = sll(s2, 3);
                        v0 = subu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(s3, v0);
                        lb(a1, v0, 248);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        lw(a0, s3, act::kUnit);
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x2EE1E0u, gen::fn_sub_284200_00284200);
                        s5 = v0;
                        v1 = 11;
                        sb(v1, v0, 0);
                        ld(v1, fp, 0x58);
                        sd(v1, v0, bcore::kCondArg);
                        sd(s0, v0, pkt::kOwner);
                        a0 = s5;
                        a1 = 1;
                        jal(ctx, 0x2EE208u, gen::fn_sub_27ED20_0027ed20);
                        if (s1 == 0) {
                            // 0x002ee218
                            charge(ctx, 2);
                            if (s2 == 0) {
                                // 0x002ee220
                                charge(ctx, 5);
                                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                                lh(a1, v0, gbtl8::kEvPick2);
                                v0 = si(-1);
                                if (a1 != v0) {
                                    // 0x002ee234
                                    charge(ctx, 12);
                                    lw(a0, s4, act::kUnit);
                                    jal(ctx, 0x2EE238u, gen::fn_sub_2BD850_002bd850);
                                    a0 = v0;
                                    v1 = 11;
                                    sb(v1, v0, 0);
                                    ld(v1, fp, 0x58);
                                    sd(v1, v0, bcore::kCondArg);
                                    sd(s0, v0, pkt::kOwner);
                                    a1 = 3;
                                    jal(ctx, 0x2EE25Cu, gen::fn_sub_27ED20_0027ed20);
                                }
                            }
                        }
                        // 0x002ee264
                        charge(ctx, 55);
                        v0 = sll(s2, 3);
                        v0 = subu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(s3, v0);
                        v0 = addiu(v0, 224);
                        sw(v0, sp, 0xC0);
                        lhu(a2, s4, act::kCmdSkill);
                        t1 = s2 & 0xFFFF;
                        lq(v0, sp, 0xA0);
                        t2 = v0 & 0xFFFF;
                        lw(a0, s4, act::kUnit);
                        lw(a1, s3, act::kUnit);
                        lhu(a3, s3, 204);
                        lhu(t0, s3, 206);
                        lw(t3, sp, 0xC0);
                        jal(ctx, 0x2EE2A0u, gen::fn_sub_2BDBD0_002bdbd0);
                        a0 = v0;
                        v1 = 5;
                        sb(v1, v0, 0);
                        ld(v1, s5, pkt::kId);
                        sd(v1, v0, bcore::kCondArg);
                        sd(s0, v0, pkt::kOwner);
                        a1 = 3;
                        jal(ctx, 0x2EE2C4u, gen::fn_sub_27ED20_0027ed20);
                        a0 = s4;
                        a1 = s3;
                        lw(a2, sp, 0xC0);
                        lhu(a3, s3, 204);
                        lhu(t0, s3, 206);
                        jal(ctx, 0x2EE2E0u, gen::fn_sub_2D7E20_002d7e20);
                        a0 = v0;
                        v1 = 5;
                        sb(v1, v0, 0);
                        ld(v1, s5, pkt::kId);
                        sd(v1, v0, bcore::kCondArg);
                        sd(s0, v0, pkt::kOwner);
                        a1 = 1;
                        jal(ctx, 0x2EE304u, gen::fn_sub_27ED20_0027ed20);
                        a0 = s3;
                        jal(ctx, 0x2EE310u, gen::fn_sub_2D8090_002d8090);
                        a0 = v0;
                        v1 = 5;
                        sb(v1, v0, 0);
                        ld(v1, s5, pkt::kId);
                        sd(v1, v0, bcore::kCondArg);
                        sd(s0, v0, pkt::kOwner);
                        a1 = 1;
                        jal(ctx, 0x2EE334u, gen::fn_sub_27ED20_0027ed20);
                        s2 = addiu(s2, 1);
                    }
                    // 0x002ee350
                    charge(ctx, 2);
                    s7 = addiu(s7, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x002ee368
                charge(ctx, 14);
                lw(a1, s4, act::kUnit);
                lw(a0, sp, 0x10C);
                a2 = a1;
                a3 = 0;
                t0 = 512;
                jal(ctx, 0x2EE37Cu, gen::fn_sub_2BAF90_002baf90);
                s1 = v0;
                a0 = 4;
                sb(a0, v0, 0);
                ld(v1, s6, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                if (s1 != 0) {
                    // 0x002ee3a0
                    charge(ctx, 3);
                    sb(a0, s1, 16);
                    ld(v0, s1, pkt::kId);
                    sd(v0, s1, 24);
                }
                // 0x002ee3ac
                charge(ctx, 85);
                sd(s0, s1, pkt::kOwner);
                a0 = s1;
                a1 = 2;
                jal(ctx, 0x2EE3B8u, gen::fn_sub_27ED20_0027ed20);
                jal(ctx, 0x2EE3C0u, gen::fn_sub_2F8810_002f8810);
                a0 = 3;
                a1 = v0;
                a2 = 2;
                jal(ctx, 0x2EE3D4u, gen::fn_sub_2DD760_002dd760);
                a0 = v0;
                v1 = 5;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EE3F8u, gen::fn_sub_27ED20_0027ed20);
                a0 = 16;
                jal(ctx, 0x2EE404u, gen::fn_sub_29FA50_0029fa50);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                lbu(v1, v0, 71);
                v1 = v1 & 0xDF;
                sb(v1, v0, 71);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EE434u, gen::fn_sub_27ED20_0027ed20);
                a0 = 16;
                a1 = 0;
                jal(ctx, 0x2EE444u, gen::fn_sub_2A1080_002a1080);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                lbu(v1, v0, 71);
                v1 = v1 & 0xDF;
                sb(v1, v0, 71);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EE474u, gen::fn_sub_27ED20_0027ed20);
                a0 = 16;
                jal(ctx, 0x2EE480u, gen::fn_sub_2A16C0_002a16c0);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                lbu(v1, v0, 71);
                v1 = v1 & 0xDF;
                sb(v1, v0, 71);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EE4B0u, gen::fn_sub_27ED20_0027ed20);
                a0 = 8;
                jal(ctx, 0x2EE4BCu, gen::fn_sub_2A1DB0_002a1db0);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                lbu(v1, v0, 71);
                v1 = v1 & 0xDF;
                sb(v1, v0, 71);
                sd(s0, v0, pkt::kOwner);
                a1 = 0;
                jal(ctx, 0x2EE4ECu, gen::fn_sub_27ED20_0027ed20);
                s0 = 0;
                for (;;) {
                    // 0x002ee518
                    charge(ctx, 3);
                    v0 = sltiu(s0, 2);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002ee500
                    charge(ctx, 6);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, sp);
                    lw(a0, v0, 264);
                    jal(ctx, 0x2EE50Cu, gen::fn_sub_2B9030_002b9030);
                    s0 = addiu(s0, 1);
                }
                // 0x002ee524
                charge(ctx, 5);
                v1 = 3;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sh(v1, v0, gbtl8::kEvState2);
            }
        } else {
            // 0x002ed3b4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x002ed3c4
                charge(ctx, 4);
                lw(a0, a2, 344);
                v0 = 266;
                for (;;) {
                    // 0x002ed414
                    charge(ctx, 2);
                    if (a0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002ed3d4
                    charge(ctx, 3);
                    lhu(v1, a0, unit::kId);
                    if (v1 == v0) {
                        goto L_002ed3e0_6;
                    }
                    // 0x002ed410
                    charge(ctx, 1);
                    lw(a0, a0, unit::kPrev);
                }
                // 0x002ed41c
                charge(ctx, 1);
                s6 = 0;
            L_002ed420:
                charge(ctx, 5);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lhu(s1, v1, gbtl::kBossWork4);
                v0 = 370;
                if (s1 == v0) {
                    // 0x002ed49c
                    charge(ctx, 1);
                    s2 = 230;
                } else {
                    // 0x002ed434
                    charge(ctx, 3);
                    v0 = 369;
                    if (s1 == v0) {
                        // 0x002ed490
                        charge(ctx, 3);
                        s2 = 229;
                    } else {
                        // 0x002ed440
                        charge(ctx, 3);
                        v0 = 367;
                        if (s1 == v0) {
                            // 0x002ed484
                            charge(ctx, 3);
                            s2 = 228;
                        } else {
                            // 0x002ed44c
                            charge(ctx, 3);
                            v0 = 366;
                            if (s1 == v0) {
                                // 0x002ed478
                                charge(ctx, 3);
                                s2 = 227;
                            } else {
                                // 0x002ed458
                                charge(ctx, 3);
                                v0 = 365;
                                if (s1 == v0) {
                                    // 0x002ed46c
                                    charge(ctx, 3);
                                    s2 = 226;
                                } else {
                                    // 0x002ed464
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
                // 0x002ed4a0
                charge(ctx, 68);
                sh(zero, v1, 2902);
                lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v1, a0, gbtl::kFlags);
                v0 = 0x80000;
                v0 = v1 | v0;
                sw(v0, a0, gbtl::kFlags);
                a0 = 1;
                jal(ctx, 0x2ED4BCu, gen::fn_btlUnitCreate_002875a0);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(v0, v1, gbtl::kBossWork0);
                a0 = 1;
                jal(ctx, 0x2ED4D0u, gen::fn_btlUnitCreate_002875a0);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(v0, v1, gbtl::kBossWork1);
                a0 = 1;
                jal(ctx, 0x2ED4E4u, gen::fn_btlUnitCreate_002875a0);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(v0, v1, gbtl::kBossWork2);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kBossWork0);
                sh(s2, v0, unit::kId);
                v1 = 231;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kBossWork1);
                sh(v1, v0, unit::kId);
                v1 = 232;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kBossWork2);
                sh(v1, v0, unit::kId);
                sw(zero, sp, 0xF8);
                sw(zero, sp, 0xFC);
                sw(zero, sp, 0x100);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork0);
                a1 = addiu(sp, 0xF8);
                jal(ctx, 0x2ED538u, gen::fn_sub_27F650_0027f650);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork1);
                a1 = addiu(sp, 0xF8);
                jal(ctx, 0x2ED54Cu, gen::fn_sub_27F650_0027f650);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork2);
                a1 = addiu(sp, 0xF8);
                jal(ctx, 0x2ED560u, gen::fn_sub_27F650_0027f650);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = 0x3F000000;
                mtc1(v0, f12);
                lw(a0, v1, gbtl::kBossWork0);
                jal(ctx, 0x2ED578u, gen::fn_sub_27F710_0027f710);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                v0 = 0x3F000000;
                mtc1(v0, f12);
                lw(a0, v1, gbtl::kBossWork1);
                jal(ctx, 0x2ED590u, gen::fn_sub_27F710_0027f710);
                lw(v1, gp, -18648);  // 0x7CE418
                v0 = 0x10000;
                v0 = addu(v1, v0);
                lhu(v0, v0, -11692);
                if (i64(v0) < 0) {
                    // 0x002ed5c4
                    charge(ctx, 7);
                    v1 = srl(v0, 1);
                    v0 = v0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x002ed5b0
                    charge(ctx, 5);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x002ed5e0
                charge(ctx, 24);
                v0 = 0x42C80000;
                mtc1(v0, f0);
                div_s(f12, f1, f0);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork2);
                jal(ctx, 0x2ED5FCu, gen::fn_sub_27F710_0027f710);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kBossWork0);
                sw(zero, v0, 2516);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kBossWork1);
                sw(zero, v0, 2516);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork1);
                lw(a1, v0, gbtl::kBossWork0);
                lw(a2, v0, gbtl::kBossWork2);
                jal(ctx, 0x2ED62Cu, gen::fn_sub_352C50_00352c50);
                s3 = 0;
                for (;;) {
                    // 0x002ed680
                    charge(ctx, 3);
                    v0 = sltiu(s3, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002ed640
                    charge(ctx, 16);
                    v0 = sll(s3, 2);
                    v0 = addu(v0, sp);
                    s5 = addiu(v0, 264);
                    a0 = 0;
                    jal(ctx, 0x2ED650u, gen::fn_sub_2B8F90_002b8f90);
                    sw(v0, s5, 0);
                    v0 = addiu(s3, 2);
                    a0 = v0 & 0xFFFF;
                    jal(ctx, 0x2ED664u, gen::fn_sub_2F87E0_002f87e0);
                    lw(a0, s5, 0);
                    a1 = v0;
                    jal(ctx, 0x2ED674u, gen::fn_sub_2B90D0_002b90d0);
                    s3 = addiu(s3, 1);
                }
                // 0x002ed68c
                charge(ctx, 11);
                lw(a0, s4, act::kUnit);
                a1 = s1;
                jal(ctx, 0x2ED694u, gen::fn_sub_2BD590_002bd590);
                a0 = v0;
                sd(s0, v0, pkt::kOwner);
                a1 = 3;
                jal(ctx, 0x2ED6A8u, gen::fn_sub_27ED20_0027ed20);
                if (s6 != 0) {
                    // 0x002ed6b8
                    charge(ctx, 10);
                    a0 = 0x2F0000;
                    a0 = addiu(a0, -13280);  // &sub_2ECC20
                    lw(a1, s4, act::kUnit);
                    jal(ctx, 0x2ED6C4u, gen::fn_sub_27F410_0027f410);
                    a0 = v0;
                    sd(s0, v0, pkt::kOwner);
                    a1 = 1;
                    jal(ctx, 0x2ED6D8u, gen::fn_sub_27ED20_0027ed20);
                }
                // 0x002ed6e0
                charge(ctx, 325);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x2ED6E8u, gen::fn_sub_2DD4A0_002dd4a0);
                fp = v0;
                sd(s0, v0, pkt::kOwner);
                a0 = fp;
                a1 = 1;
                jal(ctx, 0x2ED700u, gen::fn_sub_27ED20_0027ed20);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s4, act::kUnit);
                a1 = 7;
                a2 = 6;
                a3 = 0;
                jal(ctx, 0x2ED720u, gen::fn_sub_284200_00284200);
                s3 = v0;
                sd(s0, v0, pkt::kOwner);
                a0 = s3;
                a1 = 1;
                jal(ctx, 0x2ED738u, gen::fn_sub_27ED20_0027ed20);
                a0 = 3;
                a1 = 4095;
                jal(ctx, 0x2ED748u, gen::fn_sub_2B8D60_002b8d60);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 0;
                jal(ctx, 0x2ED76Cu, gen::fn_sub_27ED20_0027ed20);
                a0 = 0;
                a1 = 1;
                jal(ctx, 0x2ED77Cu, gen::fn_sub_2A3B40_002a3b40);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 0;
                jal(ctx, 0x2ED7A0u, gen::fn_sub_27ED20_0027ed20);
                a0 = s4;
                a1 = 17;
                jal(ctx, 0x2ED7B0u, gen::fn_sub_2A3B40_002a3b40);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 0;
                jal(ctx, 0x2ED7D4u, gen::fn_sub_27ED20_0027ed20);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s4, act::kUnit);
                a1 = 24;
                jal(ctx, 0x2ED7ECu, gen::fn_sub_2838D0_002838d0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                sq(v0, sp, 0xB0);
                ld(s5, s3, pkt::kId);
                a0 = s1;
                a1 = addiu(sp, 0x11C);
                a2 = addiu(sp, 0x118);
                jal(ctx, 0x2ED810u, gen::fn_sub_29EA60_0029ea60);
                lw(a0, sp, 0x11C);
                lw(a1, sp, 0x118);
                a2 = 16;
                jal(ctx, 0x2ED824u, gen::fn_sub_29F4B0_0029f4b0);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                sd(s5, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2ED844u, gen::fn_sub_27ED20_0027ed20);
                a0 = s1;
                jal(ctx, 0x2ED850u, gen::fn_sub_29EC00_0029ec00);
                s7 = v0;
                a0 = s1;
                a1 = addiu(sp, 0x11C);
                a2 = addiu(sp, 0x118);
                jal(ctx, 0x2ED868u, gen::fn_sub_29EC80_0029ec80);
                a0 = s7;
                lw(a1, sp, 0x11C);
                lw(a2, sp, 0x118);
                a3 = 16;
                t0 = 0;
                jal(ctx, 0x2ED884u, gen::fn_sub_2A0050_002a0050);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                sd(s5, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2ED8A4u, gen::fn_sub_27ED20_0027ed20);
                a0 = s1;
                jal(ctx, 0x2ED8B0u, gen::fn_sub_29EC50_0029ec50);
                a0 = v0;
                a1 = 16;
                jal(ctx, 0x2ED8C0u, gen::fn_sub_2A1280_002a1280);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                sd(s5, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2ED8E0u, gen::fn_sub_27ED20_0027ed20);
                a0 = s4;
                a1 = s1;
                a2 = 16;
                jal(ctx, 0x2ED8F4u, gen::fn_sub_2A1B00_002a1b00);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                sd(s5, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2ED914u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork0);
                a1 = s2;
                a2 = 30;
                jal(ctx, 0x2ED92Cu, gen::fn_sub_285690_00285690);
                s7 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                sd(s5, v0, bcore::kCondArg);
                sb(v1, v0, 16);
                ld(v1, fp, 0x58);
                sd(v1, v0, 24);
                lq(v1, sp, 0xB0);
                v1 = addiu(v1, 6);
                sh(v1, v0, pkt::kStartDelay);
                sd(s0, v0, pkt::kOwner);
                a0 = s7;
                a1 = 1;
                jal(ctx, 0x2ED968u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork1);
                a1 = 231;
                a2 = 30;
                jal(ctx, 0x2ED980u, gen::fn_sub_285690_00285690);
                s2 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s7, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x2ED9A8u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork2);
                a1 = 232;
                a2 = 30;
                jal(ctx, 0x2ED9C0u, gen::fn_sub_285690_00285690);
                s5 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a0 = s5;
                a1 = 1;
                jal(ctx, 0x2ED9E8u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork0);
                a1 = si(-1);
                a2 = 0;
                a3 = 0;
                t0 = 1;
                t1 = t0;
                jal(ctx, 0x2EDA0Cu, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s7, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                v1 = 2;
                sh(v1, v0, pkt::kStartDelay);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EDA38u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork1);
                a1 = si(-1);
                a2 = 0;
                a3 = 0;
                t0 = 1;
                t1 = t0;
                jal(ctx, 0x2EDA5Cu, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                v1 = 2;
                sh(v1, v0, pkt::kStartDelay);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EDA88u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, gbtl::kBossWork2);
                a1 = si(-1);
                a2 = 0;
                a3 = 0;
                t0 = 1;
                t1 = t0;
                jal(ctx, 0x2EDAACu, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s5, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                v1 = 2;
                sh(v1, v0, pkt::kStartDelay);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EDAD8u, gen::fn_sub_27ED20_0027ed20);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(a0, v0, 3240);
                lw(a1, s4, act::kUnit);
                a2 = 0;
                ld(a3, s5, pkt::kId);
                t0 = 768;
                jal(ctx, 0x2EDAF8u, gen::fn_sub_2BB2F0_002bb2f0);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EDB1Cu, gen::fn_sub_27ED20_0027ed20);
                a0 = 10;
                a1 = 2;
                a2 = 5;
                jal(ctx, 0x2EDB30u, gen::fn_sub_2DD100_002dd100);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                a1 = 1;
                jal(ctx, 0x2EDB50u, gen::fn_sub_27ED20_0027ed20);
                lw(a1, s4, act::kUnit);
                lw(a0, sp, 0x108);
                a2 = a1;
                a3 = 0;
                t0 = 512;
                jal(ctx, 0x2EDB6Cu, gen::fn_sub_2BAF90_002baf90);
                s3 = v0;
                a0 = 4;
                sb(a0, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sb(a0, v0, 16);
                ld(v1, s5, pkt::kId);
                sd(v1, v0, 24);
                sd(s0, v0, pkt::kOwner);
                a0 = s3;
                a1 = 2;
                jal(ctx, 0x2EDBA0u, gen::fn_sub_27ED20_0027ed20);
                jal(ctx, 0x2EDBA8u, gen::fn_sub_2F8810_002f8810);
                a0 = 3;
                a1 = v0;
                a2 = 0;
                jal(ctx, 0x2EDBBCu, gen::fn_sub_2DD760_002dd760);
                a0 = v0;
                v1 = 5;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                a1 = 1;
                jal(ctx, 0x2EDBDCu, gen::fn_sub_27ED20_0027ed20);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v1, 2920);
                if (v0 != 0) {
                    // 0x002edc70
                    charge(ctx, 3);
                    v0 = 369;
                    if (s1 == v0) {
                        // 0x002edc7c
                        charge(ctx, 3);
                        lw(v0, v1, 2924);
                        if (v0 != 0) {
                            goto L_002edd04;
                        }
                        // 0x002edc88
                        charge(ctx, 31);
                        jal(ctx, 0x2EDC88u, gen::fn_sub_2DB890_002db890);
                        a0 = v0;
                        v1 = 5;
                        sb(v1, v0, 0);
                        ld(v1, s3, pkt::kId);
                        sd(v1, v0, bcore::kCondArg);
                        v1 = 52;
                        sh(v1, v0, pkt::kStartDelay);
                        a1 = 1;
                        jal(ctx, 0x2EDCB0u, gen::fn_sub_27ED20_0027ed20);
                        a0 = 32;
                        a1 = 40;
                        jal(ctx, 0x2EDCC0u, gen::fn_sub_2DB800_002db800);
                        a0 = v0;
                        v1 = 5;
                        sb(v1, v0, 0);
                        ld(v1, s3, pkt::kId);
                        sd(v1, v0, bcore::kCondArg);
                        v1 = 52;
                        sh(v1, v0, pkt::kStartDelay);
                        a1 = 1;
                        jal(ctx, 0x2EDCE8u, gen::fn_sub_27ED20_0027ed20);
                        v1 = 1;
                        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                        sw(v1, v0, 2924);
                        goto L_002edd90;
                    }
                L_002edd04:
                    charge(ctx, 3);
                    v0 = 370;
                    if (s1 == v0) {
                        // 0x002edd10
                        charge(ctx, 3);
                        lw(v0, v1, 2928);
                        if (v0 == 0) {
                            // 0x002edd1c
                            charge(ctx, 29);
                            jal(ctx, 0x2EDD1Cu, gen::fn_sub_2DB890_002db890);
                            a0 = v0;
                            v1 = 5;
                            sb(v1, v0, 0);
                            ld(v1, s3, pkt::kId);
                            sd(v1, v0, bcore::kCondArg);
                            v1 = 52;
                            sh(v1, v0, pkt::kStartDelay);
                            a1 = 1;
                            jal(ctx, 0x2EDD44u, gen::fn_sub_27ED20_0027ed20);
                            a0 = 32;
                            a1 = 41;
                            jal(ctx, 0x2EDD54u, gen::fn_sub_2DB800_002db800);
                            a0 = v0;
                            v1 = 5;
                            sb(v1, v0, 0);
                            ld(v1, s3, pkt::kId);
                            sd(v1, v0, bcore::kCondArg);
                            v1 = 52;
                            sh(v1, v0, pkt::kStartDelay);
                            a1 = 1;
                            jal(ctx, 0x2EDD7Cu, gen::fn_sub_27ED20_0027ed20);
                            v1 = 1;
                            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                            sw(v1, v0, 2928);
                        }
                    }
                } else {
                    // 0x002edbf4
                    charge(ctx, 31);
                    jal(ctx, 0x2EDBF4u, gen::fn_sub_2DB890_002db890);
                    a0 = v0;
                    v1 = 5;
                    sb(v1, v0, 0);
                    ld(v1, s3, pkt::kId);
                    sd(v1, v0, bcore::kCondArg);
                    v1 = 40;
                    sh(v1, v0, pkt::kStartDelay);
                    a1 = 1;
                    jal(ctx, 0x2EDC1Cu, gen::fn_sub_27ED20_0027ed20);
                    a0 = 32;
                    a1 = 38;
                    jal(ctx, 0x2EDC2Cu, gen::fn_sub_2DB800_002db800);
                    a0 = v0;
                    v1 = 5;
                    sb(v1, v0, 0);
                    ld(v1, s3, pkt::kId);
                    sd(v1, v0, bcore::kCondArg);
                    v1 = 40;
                    sh(v1, v0, pkt::kStartDelay);
                    a1 = 1;
                    jal(ctx, 0x2EDC54u, gen::fn_sub_27ED20_0027ed20);
                    v1 = 1;
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    sw(v1, v0, 2920);
                }
            L_002edd90:
                charge(ctx, 77);
                lw(a1, s4, act::kUnit);
                lw(a0, sp, 0x10C);
                a2 = a1;
                a3 = 0;
                t0 = 512;
                jal(ctx, 0x2EDDA4u, gen::fn_sub_2BAF90_002baf90);
                s1 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s3, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a0 = s1;
                a1 = 2;
                jal(ctx, 0x2EDDCCu, gen::fn_sub_27ED20_0027ed20);
                lwc1(f0, gp, -32028);  // 0x7CAFD4
                swc1(f0, sp, 0xE8);
                lwc1(f0, gp, -32024);  // 0x7CAFD8
                swc1(f0, sp, 0xEC);
                lwc1(f0, gp, -32020);  // 0x7CAFDC
                swc1(f0, sp, 0xF0);
                lwc1(f0, gp, -32016);  // 0x7CAFE0
                swc1(f0, sp, 0xD8);
                lwc1(f0, gp, -32012);  // 0x7CAFE4
                swc1(f0, sp, 0xDC);
                lwc1(f0, gp, -32008);  // 0x7CAFE8
                swc1(f0, sp, 0xE0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a0 = s4;
                a1 = 0;
                a2 = 0;
                a3 = addiu(sp, 0xE8);
                t0 = addiu(sp, 0xD8);
                jal(ctx, 0x2EDE20u, gen::fn_sub_2A3D70_002a3d70);
                s2 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x2EDE48u, gen::fn_sub_27ED20_0027ed20);
                a0 = 0x2F0000;
                a0 = addiu(a0, -12416);  // &sub_2ECF80
                a1 = s4;
                jal(ctx, 0x2EDE5Cu, gen::fn_sub_27F410_0027f410);
                s1 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                v1 = 0x41F00000;
                mtc1(v1, f0);
                cvt_w_s(f0, f0);
                mfc1(v1, f0);
                v1 = dsll32(v1, 16);
                v1 = dsra32(v1, 16);
                v1 = addiu(v1, -4);
                sh(v1, v0, pkt::kStartDelay);
                v1 = 30;
                sh(v1, v0, 74);
                sd(s0, v0, pkt::kOwner);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x2EDEB4u, gen::fn_sub_27ED20_0027ed20);
                if (s6 != 0) {
                    // 0x002edec4
                    charge(ctx, 14);
                    a0 = 0x2F0000;
                    a0 = addiu(a0, -13344);  // &sub_2ECBE0
                    lw(a1, s4, act::kUnit);
                    jal(ctx, 0x2EDED0u, gen::fn_sub_27F410_0027f410);
                    a0 = v0;
                    v1 = 4;
                    sb(v1, v0, 0);
                    ld(v1, s1, pkt::kId);
                    sd(v1, v0, bcore::kCondArg);
                    sd(s0, v0, pkt::kOwner);
                    a1 = 1;
                    jal(ctx, 0x2EDEF4u, gen::fn_sub_27ED20_0027ed20);
                }
                // 0x002edefc
                charge(ctx, 51);
                lw(a1, s4, act::kUnit);
                lw(a0, sp, 0x110);
                a2 = a1;
                a3 = 0;
                t0 = 512;
                jal(ctx, 0x2EDF10u, gen::fn_sub_2BAF90_002baf90);
                s2 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s1, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a0 = s2;
                a1 = 2;
                jal(ctx, 0x2EDF38u, gen::fn_sub_27ED20_0027ed20);
                jal(ctx, 0x2EDF40u, gen::fn_sub_2F8810_002f8810);
                a0 = 3;
                a1 = v0;
                a2 = 1;
                jal(ctx, 0x2EDF54u, gen::fn_sub_2DD760_002dd760);
                a0 = v0;
                v1 = 5;
                sb(v1, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                a1 = 1;
                jal(ctx, 0x2EDF78u, gen::fn_sub_27ED20_0027ed20);
                a0 = si(-1);
                a1 = 20;
                jal(ctx, 0x2EDF88u, gen::fn_sub_2A1280_002a1280);
                a0 = v0;
                v1 = 5;
                sb(v1, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s0, v0, pkt::kOwner);
                v1 = 30;
                sh(v1, v0, pkt::kStartDelay);
                a1 = 1;
                jal(ctx, 0x2EDFB4u, gen::fn_sub_27ED20_0027ed20);
                s0 = 0;
                for (;;) {
                    // 0x002edfe0
                    charge(ctx, 3);
                    v0 = sltiu(s0, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002edfc8
                    charge(ctx, 6);
                    v0 = sll(s0, 2);
                    v0 = addu(v0, sp);
                    lw(a0, v0, 264);
                    jal(ctx, 0x2EDFD4u, gen::fn_sub_2B9030_002b9030);
                    s0 = addiu(s0, 1);
                }
                // 0x002edfec
                charge(ctx, 5);
                v1 = 2;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                sh(v1, v0, gbtl8::kEvState2);
            } else {
                // 0x002ed3bc
                charge(ctx, 2);
            }
        }
        goto L_002ee5fc;
    }
    // 0x002ee538
    charge(ctx, 17);
    lw(a0, a2, 2888);
    lw(a1, a2, 2884);
    lw(a2, a2, 2892);
    jal(ctx, 0x2EE544u, gen::fn_sub_352C50_00352c50);
    ld(a0, s4, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2EE56Cu, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
    L_002ee5fc:
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002ee57c
        charge(ctx, 32);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl::kBossWork0);
        jal(ctx, 0x2EE59Cu, gen::fn_sub_2878D0_002878d0);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl::kBossWork1);
        jal(ctx, 0x2EE5ACu, gen::fn_sub_2878D0_002878d0);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl::kBossWork2);
        jal(ctx, 0x2EE5BCu, gen::fn_sub_2878D0_002878d0);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v0, gbtl::kBossWork0);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v0, gbtl::kBossWork1);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        sw(zero, v0, gbtl::kBossWork2);
        a0 = 0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x2EE5E8u, gen::fn_sub_352C50_00352c50);
        v0 = 0;
    }
    // 0x002ee600 (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
    sp = addiu(sp, 0x120);
    return;
L_002ed3e0_6:
    charge(ctx, 6);
    lw(a0, a0, unit::kDat);
    a1 = 0;
    jal(ctx, 0x2ED3E8u, gen::fn_datCalcIsDead_0030b5a0);
    if (v0 != 0) {
        // 0x002ed404
        charge(ctx, 3);
        s6 = 0;
    } else {
        // 0x002ed3f8
        charge(ctx, 3);
        s6 = 1;
    }
    goto L_002ed420;
}

// 0x002EE640 sub_2EE640 -- 976 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk packet for enemies 265 / 266: gBtl flag 0x80000 set, 0x2000000 cleared, the unit busy (+160) + 1;
// camera script 8 and E1A6_99.ADX for 265, 7 and E1A6_98.ADX for 266 (which also finds 265); the motion / wait /
// sub_27FE90 / sub_2A3B40 chain, sub_2DD830 motions and a sub_27F410 call packet.
// Arguments: a0 btlAction.
void sub_2EE640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ee640
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a1, gbtl::kFlags);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a1, gbtl::kFlags);
    lw(s4, a0, act::kUnit);
    s0 = 0;
    lhu(v0, s4, unit::kBusy);
    v0 = addiu(v0, 1);
    sh(v0, s4, unit::kBusy);
    a0 = 0;
    jal(ctx, 0x2EE6A4u, gen::fn_sub_2B8F90_002b8f90);
    s3 = v0;
    lhu(v1, s4, unit::kId);
    v0 = 265;
    if (v1 == v0) {
        // 0x002ee71c
        charge(ctx, 16);
        a0 = 8;
        jal(ctx, 0x2EE720u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s3;
        a1 = v0;
        jal(ctx, 0x2EE730u, gen::fn_sub_2B90D0_002b90d0);
        a0 = 3;
        a1 = 0x6A0000;
        a1 = addiu(a1, -24592);  // "E1A6_99.ADX"
        jal(ctx, 0x2EE744u, gen::fn_sub_2DD690_002dd690);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EE754u, gen::fn_sub_27ED20_0027ed20);
    } else {
        // 0x002ee6c0
        charge(ctx, 3);
        v0 = 266;
        if (v1 == v0) {
            // 0x002ee6d4
            charge(ctx, 18);
            a0 = 7;
            jal(ctx, 0x2EE6D8u, gen::fn_sub_2F87E0_002f87e0);
            a0 = s3;
            a1 = v0;
            jal(ctx, 0x2EE6E8u, gen::fn_sub_2B90D0_002b90d0);
            a0 = 3;
            a1 = 0x6A0000;
            a1 = addiu(a1, -24608);  // "E1A6_98.ADX"
            jal(ctx, 0x2EE6FCu, gen::fn_sub_2DD690_002dd690);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EE70Cu, gen::fn_sub_27ED20_0027ed20);
        } else {
            // 0x002ee6cc
            charge(ctx, 2);
        }
    }
    // 0x002ee75c
    charge(ctx, 4);
    lhu(v1, s4, unit::kId);
    v0 = 266;
    if (v1 == v0) {
        // 0x002ee76c
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(s0, v0, gbtl8::kUnitTail1);
        v0 = 265;
        for (;;) {
            // 0x002ee790
            charge(ctx, 4);
            if (s0 != 0) {
                backedge(ctx);
                // 0x002ee780
                charge(ctx, 3);
                lhu(v1, s0, unit::kId);
                if (v1 != v0) {
                    // 0x002ee78c
                    charge(ctx, 1);
                    lw(s0, s0, unit::kPrev);
                    continue;
                }
            }
            break;
        }
    }
    // 0x002ee7a0
    charge(ctx, 77);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s4;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2EE7B8u, gen::fn_sub_284200_00284200);
    s2 = v0;
    v1 = 2;
    sh(v1, v0, pkt::kStartDelay);
    ld(v1, s1, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x2EE7DCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EE7ECu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s1, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EE814u, gen::fn_sub_27ED20_0027ed20);
    a0 = s4;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EE830u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s1, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EE858u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EE868u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s1, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EE890u, gen::fn_sub_27ED20_0027ed20);
    a0 = s3;
    a1 = s4;
    a2 = s4;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EE8ACu, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s1, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 2;
    jal(ctx, 0x2EE8C4u, gen::fn_sub_27ED20_0027ed20);
    if (s0 != 0) {
        // 0x002ee8d4
        charge(ctx, 67);
        a0 = s3;
        a1 = s0;
        a2 = s0;
        a3 = 1;
        t0 = 512;
        jal(ctx, 0x2EE8E8u, gen::fn_sub_2BAF90_002baf90);
        s2 = v0;
        ld(v1, s1, 0);
        sd(v1, v0, pkt::kOwner);
        a0 = s2;
        a1 = 2;
        jal(ctx, 0x2EE904u, gen::fn_sub_27ED20_0027ed20);
        a0 = s0;
        a1 = 10;
        a2 = 0;
        a3 = 7;
        jal(ctx, 0x2EE91Cu, gen::fn_sub_2DD830_002dd830);
        a0 = v0;
        v1 = 5;
        sb(v1, v0, 0);
        ld(v1, s2, pkt::kId);
        sd(v1, v0, bcore::kCondArg);
        ld(v1, s1, 0);
        sd(v1, v0, pkt::kOwner);
        v1 = 150;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2EE94Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 0x2F0000;
        a0 = addiu(a0, -13280);  // &sub_2ECC20
        a1 = s0;
        jal(ctx, 0x2EE960u, gen::fn_sub_27F410_0027f410);
        a0 = v0;
        v1 = 5;
        sb(v1, v0, 0);
        ld(v1, s2, pkt::kId);
        sd(v1, v0, bcore::kCondArg);
        v1 = 8;
        sh(v1, v0, pkt::kStartDelay);
        ld(v1, s1, 0);
        sd(v1, v0, pkt::kOwner);
        a1 = 1;
        jal(ctx, 0x2EE990u, gen::fn_sub_27ED20_0027ed20);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = s0;
        a1 = 0;
        a2 = 0;
        a3 = 1;
        jal(ctx, 0x2EE9B0u, gen::fn_sub_284200_00284200);
        a0 = v0;
        v1 = 5;
        sb(v1, v0, 0);
        ld(v1, s2, pkt::kId);
        sd(v1, v0, bcore::kCondArg);
        v1 = 8;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2EE9D8u, gen::fn_sub_27ED20_0027ed20);
    }
    // 0x002ee9e0
    charge(ctx, 12);
    a0 = s3;
    jal(ctx, 0x2EE9E4u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EEA10 sub_2EEA10 -- 344 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Its update: as sub_2E9F10, also taking the unit's busy count back.
// Arguments: a0 btlAction.
void sub_2EEA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002eea10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2EEA20u, gen::fn_sub_29AD20_0029ad20);
    if (s0 == v0) {
        // 0x002eea50
        charge(ctx, 5);
        lw(a0, s0, act::kUnit);
        lw(v1, a0, unit::kFlags);
        v0 = si(-17);
        v0 = v1 & v0;
        sw(v0, a0, unit::kFlags);
    L_002eea64:
        charge(ctx, 12);
        ld(a0, s0, 0);
        v0 = 0x3FFF0000;
        v0 = v0 | 0xFFFF;
        v1 = dsll32(v0, 0);
        v0 = 0xFFFF;
        v0 = dsll(v0, 16);
        v0 = v0 | 0xFFFF;
        a1 = v0 | v1;
        jal(ctx, 0x2EEA84u, gen::fn_sub_27E390_0027e390);
        if (v0 != 0) {
            // 0x002eeb50
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x002eea94
            charge(ctx, 47);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = lui(0xFFF7);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, gbtl::kFlags);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x2EEAB4u, gen::fn_sub_2D7890_002d7890);
            a0 = s0;
            jal(ctx, 0x2EEAC0u, gen::fn_sub_29A320_0029a320);
            lw(v1, s0, act::kUnit);
            lhu(v0, v1, unit::kBusy);
            v0 = addiu(v0, -1);
            sh(v0, v1, unit::kBusy);
            lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(v1, a0, gbtl::kFlags);
            v0 = 0x2000000;
            v0 = v1 | v0;
            sw(v0, a0, gbtl::kFlags);
            a0 = 16;
            jal(ctx, 0x2EEAF0u, gen::fn_sub_29FA50_0029fa50);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EEB00u, gen::fn_sub_27ED20_0027ed20);
            a0 = 16;
            a1 = 4;
            jal(ctx, 0x2EEB10u, gen::fn_sub_2A1080_002a1080);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EEB20u, gen::fn_sub_27ED20_0027ed20);
            a0 = 16;
            jal(ctx, 0x2EEB2Cu, gen::fn_sub_2A16C0_002a16c0);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2EEB3Cu, gen::fn_sub_27ED20_0027ed20);
            v0 = 0;
        }
    } else {
        // 0x002eea30
        charge(ctx, 5);
        lw(v0, s0, act::kUnit);
        lw(v0, v0, unit::kFlags);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            goto L_002eea64;
        }
        // 0x002eea44
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002eeb54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EEB70 sub_2EEB70 -- 228 bytes; frame 0x10: ra sp+0x0
// Action start hook for enemies 267 / 268: flags2 bit 4, unit flags 0x100 / 0x40 / 0x80, DatUnit flag 0x40;
// then the motion 209 (268) or 208 (267) through sub_288F80.
// Arguments: a0 btlAction.
void sub_2EEB70(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002eeb70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v1, a0, act::kFlags2);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002eeb88
        charge(ctx, 5);
        lw(a2, a0, act::kUnit);
        lbu(a1, a2, unit::kSide);
        v1 = 1;
        if (a1 == v1) {
            // 0x002eeb9c
            charge(ctx, 4);
            lhu(a1, a2, unit::kId);
            v1 = 268;
            if (a1 != v1) {
                // 0x002eebac
                charge(ctx, 3);
                v1 = 267;
                if (a1 == v1) {
                    goto L_002eebc0;
                }
                // 0x002eebb8
                charge(ctx, 2);
                goto L_002eebf8;
            }
        L_002eebc0:
            charge(ctx, 14);
            lhu(v1, a0, act::kFlags2);
            v1 = v1 | 0x10;
            sh(v1, a0, act::kFlags2);
            lw(v1, a2, unit::kFlags);
            v1 = v1 | 0x100;
            sw(v1, a2, unit::kFlags);
            v1 = v1 | 0x40;
            sw(v1, a2, unit::kFlags);
            v1 = v1 | 0x80;
            sw(v1, a2, unit::kFlags);
            lw(a0, a2, unit::kDat);
            lhu(v1, a0, 0);
            v1 = v1 | 0x40;
            sh(v1, a0, 0);
        L_002eebf8:
            charge(ctx, 4);
            lhu(a0, a2, unit::kId);
            v1 = 268;
            if (a0 == v1) {
                // 0x002eec34
                charge(ctx, 4);
                a0 = a2;
                a1 = 209;
                jal(ctx, 0x2EEC3Cu, gen::fn_sub_288F80_00288f80);
            } else {
                // 0x002eec08
                charge(ctx, 3);
                v1 = 267;
                if (a0 == v1) {
                    // 0x002eec1c
                    charge(ctx, 6);
                    a0 = a2;
                    a1 = 208;
                    jal(ctx, 0x2EEC24u, gen::fn_sub_288F80_00288f80);
                } else {
                    // 0x002eec14
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x002eec44 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EEC60 sub_2EEC60 -- 440 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (150, 350) slot 2, the others from 0x69A000 (slots 0x7CC990[8..9]).
// Arguments: none.
void sub_2EEC60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002eec60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -24576);  // &0x69A000
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002eec80
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x002eeca4
    charge(ctx, 12);
    lh(a1, gp, -25408);  // 0x7CC9B0
    lh(a0, gp, -25406);  // 0x7CC9B2
    lh(v1, gp, -25404);  // 0x7CC9B4
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002eed6c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002eecd4
        charge(ctx, 4);
        lhu(v1, s1, unit::kId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002eed04
            charge(ctx, 16);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 48);
            lwc1(f0, v0, 0);
            swc1(f0, sp, 0x50);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0x58);
            v0 = sll(v1, 1);
            v0 = addu(v0, sp);
            lh(v0, v0, 72);
            sb(v0, s1, unit5::kSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002eece4
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 0x43AF0000;
            sw(v0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, unit5::kSlot);
        }
        // 0x002eed44
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EED50u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EED60u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002eed74
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002eedf8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002eed84
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 268;
        if (v1 == v0) {
            // 0x002eedc0
            charge(ctx, 4);
            v0 = 0x43480000;
            sw(v0, sp, 0x50);
            v0 = lui(0xC3AF);
            sw(v0, sp, 0x58);
        } else {
            // 0x002eed94
            charge(ctx, 3);
            v0 = 267;
            if (v1 == v0) {
                // 0x002eeda8
                charge(ctx, 6);
                v0 = lui(0xC348);
                sw(v0, sp, 0x50);
                v0 = lui(0xC3AF);
                sw(v0, sp, 0x58);
            } else {
                // 0x002eeda0
                charge(ctx, 2);
            }
        }
        // 0x002eedd0
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EEDDCu, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EEDECu, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002eee00
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EF000 sub_2EF000 -- 588 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk packet for enemies 267 / 268: gBtl flag 0x80000 set, 0x2000000 cleared; the voice line 786
// (268, camera script 3) or 767 (267, script 2) through sub_2E2CB0; the motion 18 / wait / sub_27FE90 / sub_2A3B40
// chain owned by the action.
// Arguments: a0 btlAction.
void sub_2EF000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ef000
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a1, gbtl::kFlags);
    lw(a1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a1, gbtl::kFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a1, gbtl::kFlags);
    lw(s2, a0, act::kUnit);
    lhu(v1, s2, unit::kId);
    v0 = 268;
    if (v1 == v0) {
        // 0x002ef0a0
        charge(ctx, 10);
        s0 = 3;
        a0 = 786;
        jal(ctx, 0x2EF0A8u, gen::fn_sub_2E2CB0_002e2cb0);
        a0 = v0;
        v1 = s0;
        sh(v1, v0, pkt::kStartDelay);
        a1 = 1;
        jal(ctx, 0x2EF0C0u, gen::fn_sub_27ED20_0027ed20);
    } else {
        // 0x002ef05c
        charge(ctx, 3);
        v0 = 267;
        if (v1 == v0) {
            // 0x002ef070
            charge(ctx, 12);
            s0 = 2;
            a0 = 767;
            jal(ctx, 0x2EF078u, gen::fn_sub_2E2CB0_002e2cb0);
            a0 = v0;
            v1 = 3;
            sh(v1, v0, pkt::kStartDelay);
            a1 = 1;
            jal(ctx, 0x2EF090u, gen::fn_sub_27ED20_0027ed20);
        } else {
            // 0x002ef068
            charge(ctx, 2);
        }
    }
    // 0x002ef0c8
    charge(ctx, 97);
    a0 = 0;
    jal(ctx, 0x2EF0CCu, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x2EF0DCu, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2EF0ECu, gen::fn_sub_2B90D0_002b90d0);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2EF10Cu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, pkt::kStartDelay);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2EF130u, gen::fn_sub_27ED20_0027ed20);
    a0 = 1;
    a1 = 4095;
    jal(ctx, 0x2EF140u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EF168u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EF184u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2EF1ACu, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EF1BCu, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EF1E4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EF200u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, pkt::kOwner);
    a1 = 2;
    jal(ctx, 0x2EF218u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2EF224u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002EF250 sub_2EF250 -- 260 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Its update: 1 while the action's packets run; then gBtl flag 0x80000 cleared, the kill (sub_2D7890(a, 0)),
// sub_29A320, flag 0x2000000 and the three colour fades; 0.
// Arguments: a0 btlAction.
void sub_2EF250(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ef250
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2EF280u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002ef33c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002ef290
        charge(ctx, 43);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, gbtl::kFlags);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x2EF2B0u, gen::fn_sub_2D7890_002d7890);
        a0 = s0;
        jal(ctx, 0x2EF2BCu, gen::fn_sub_29A320_0029a320);
        lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(v1, a0, gbtl::kFlags);
        v0 = 0x2000000;
        v0 = v1 | v0;
        sw(v0, a0, gbtl::kFlags);
        a0 = 16;
        jal(ctx, 0x2EF2DCu, gen::fn_sub_29FA50_0029fa50);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EF2ECu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        a1 = 4;
        jal(ctx, 0x2EF2FCu, gen::fn_sub_2A1080_002a1080);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EF30Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        jal(ctx, 0x2EF318u, gen::fn_sub_2A16C0_002a16c0);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2EF328u, gen::fn_sub_27ED20_0027ed20);
        v0 = 0;
    }
    // 0x002ef340 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EF360 sub_2EF360 -- 576 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss battle placement: party id 1 at (150, 500) slot 2, the others from 0x69A060 (slots 0x7CC990[10..11]).
// Arguments: none.
void sub_2EF360(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002ef360
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -24480);  // &0x69A060
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002ef380
        charge(ctx, 9);
        lw(a0, a3, 0);
        lw(v1, a3, 4);
        a3 = addiu(a3, 8);
        a1 = addiu(a1, -1);
        sw(a0, a2, 0);
        sw(v1, a2, 4);
        a2 = addiu(a2, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x002ef3a4
    charge(ctx, 12);
    lh(a1, gp, -25400);  // 0x7CC9B8
    lh(a0, gp, -25398);  // 0x7CC9BA
    lh(v1, gp, -25396);  // 0x7CC9BC
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v1, gbtl::kUnitTail0);
    for (;;) {
        // 0x002ef46c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ef3d4
        charge(ctx, 4);
        lhu(v1, s1, unit::kId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002ef404
            charge(ctx, 16);
            v1 = dsll32(s0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 3);
            v0 = addu(v0, sp);
            v0 = addiu(v0, 48);
            lwc1(f0, v0, 0);
            swc1(f0, sp, 0x50);
            lwc1(f0, v0, 4);
            swc1(f0, sp, 0x58);
            v0 = sll(v1, 1);
            v0 = addu(v0, sp);
            lh(v0, v0, 72);
            sb(v0, s1, unit5::kSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002ef3e4
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 0x43FA0000;
            sw(v0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, unit5::kSlot);
        }
        // 0x002ef444
        charge(ctx, 10);
        a0 = addiu(s1, unit4::kCellX);
        a1 = addiu(s1, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EF450u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EF460u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, unit::kPrev);
    }
    // 0x002ef474
    charge(ctx, 4);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ef580
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ef484
        charge(ctx, 4);
        lhu(v1, s0, unit::kId);
        v0 = 295;
        if (v1 == v0) {
            // 0x002ef548
            charge(ctx, 4);
            v0 = 0x437A0000;
            sw(v0, sp, 0x50);
            v0 = 0x42C80000;
            sw(v0, sp, 0x58);
        } else {
            // 0x002ef494
            charge(ctx, 3);
            v0 = 281;
            if (v1 == v0) {
                // 0x002ef530
                charge(ctx, 6);
                v0 = lui(0xC37A);
                sw(v0, sp, 0x50);
                v0 = 0x42C80000;
                sw(v0, sp, 0x58);
            } else {
                // 0x002ef4a0
                charge(ctx, 3);
                v0 = 280;
                if (v1 == v0) {
                    // 0x002ef518
                    charge(ctx, 6);
                    v0 = 0x437A0000;
                    sw(v0, sp, 0x50);
                    v0 = lui(0xC3E1);
                    sw(v0, sp, 0x58);
                } else {
                    // 0x002ef4ac
                    charge(ctx, 3);
                    v0 = 279;
                    if (v1 == v0) {
                        // 0x002ef504
                        charge(ctx, 5);
                        sw(zero, sp, 0x50);
                        v0 = lui(0xC348);
                        sw(v0, sp, 0x58);
                    } else {
                        // 0x002ef4b8
                        charge(ctx, 3);
                        v0 = 278;
                        if (v1 == v0) {
                            // 0x002ef4ec
                            charge(ctx, 6);
                            v0 = lui(0xC37A);
                            sw(v0, sp, 0x50);
                            v0 = lui(0xC3E1);
                            sw(v0, sp, 0x58);
                        } else {
                            // 0x002ef4c4
                            charge(ctx, 3);
                            v0 = 269;
                            if (v1 == v0) {
                                // 0x002ef4d8
                                charge(ctx, 5);
                                sw(zero, sp, 0x50);
                                v0 = lui(0xC3FA);
                                sw(v0, sp, 0x58);
                            } else {
                                // 0x002ef4d0
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
        // 0x002ef558
        charge(ctx, 10);
        a0 = addiu(s0, unit4::kCellX);
        a1 = addiu(s0, unit4::kCellZ);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2EF564u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2EF574u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ef588
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002EF5A0 sub_2EF5A0 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Boss battle cleanup (sub_2FAAB0): enemy 295 clears gBtl +2908, 281 clears +2904 (both zero the model's
// +1053); 269 is put back (sub_2D3FE0) with model +904 bits 0x20 and 0x80.
// Arguments: none.
void sub_2EF5A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ef5a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s0, v1, gbtl8::kUnitTail1);
    for (;;) {
        // 0x002ef64c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ef5bc
        charge(ctx, 4);
        lhu(a0, s0, unit::kId);
        v1 = 295;
        if (a0 == v1) {
            // 0x002ef638
            charge(ctx, 4);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(zero, v1, gbtl8::kEvTimer);
            lw(v1, s0, unit::kModel);
            sb(zero, v1, 1053);
        } else {
            // 0x002ef5cc
            charge(ctx, 3);
            v1 = 281;
            if (a0 == v1) {
                // 0x002ef620
                charge(ctx, 6);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(zero, v1, gbtl8::kEvState2);
                lw(v1, s0, unit::kModel);
                sb(zero, v1, 1053);
            } else {
                // 0x002ef5d8
                charge(ctx, 3);
                v1 = 269;
                if (a0 == v1) {
                    // 0x002ef5ec
                    charge(ctx, 13);
                    a0 = s0;
                    jal(ctx, 0x2EF5F0u, gen::fn_sub_2D3FE0_002d3fe0);
                    lw(a0, s0, unit::kModel);
                    lbu(v1, a0, 904);
                    v1 = v1 | 0x20;
                    sb(v1, a0, 904);
                    lw(a0, s0, unit::kModel);
                    lbu(v1, a0, 904);
                    v1 = v1 | 0x80;
                    sb(v1, a0, 904);
                } else {
                    // 0x002ef5e4
                    charge(ctx, 2);
                }
            }
        }
        // 0x002ef648
        charge(ctx, 1);
        lw(s0, s0, unit::kPrev);
    }
    // 0x002ef654
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EF670 sub_2EF670 -- 356 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss opening shot: as sub_2E9450 with party id 1 framed and the other three passed to sub_2BC950.
// Arguments: none.
void sub_2EF670(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ef670
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2EF684u, gen::fn_sub_2B8F90_002b8f90);
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x2EF694u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x2EF6A4u, gen::fn_sub_2B90D0_002b90d0);
    a1 = 0;
    s1 = 0;
    sw(zero, sp, 0x30);
    sw(zero, sp, 0x34);
    sw(zero, sp, 0x38);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a2, v0, gbtl::kUnitTail0);
    a0 = 1;
    v1 = 2;
    for (;;) {
        // 0x002ef720
        charge(ctx, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ef6d8
        charge(ctx, 3);
        lhu(v0, a2, unit::kId);
        if (v0 == a0) {
            // 0x002ef6ec
            charge(ctx, 3);
            s1 = a2;
        } else {
            // 0x002ef6e4
            charge(ctx, 2);
            // 0x002ef6f8
            charge(ctx, 9);
            v0 = dsll32(a1, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v1, v0);
            v0 = sll(v0, 2);
            v0 = addu(v0, sp);
            sw(a2, v0, 48);
            v0 = addiu(a1, 1);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
        }
        // 0x002ef71c
        charge(ctx, 1);
        lw(a2, a2, unit::kPrev);
    }
    // 0x002ef728
    charge(ctx, 43);
    lw(a0, sp, 0x30);
    lw(a1, sp, 0x34);
    lw(a2, sp, 0x38);
    jal(ctx, 0x2EF734u, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2EF744u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = s1;
    a2 = s1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EF760u, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2EF774u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x2EF788u, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s1, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EF7A8u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2EF7B4u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002EF7E0 sub_2EF7E0 -- 484 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Boss talk, enemy 269: as sub_2E95F0 with camera script 9 and E1A8_99.ADX (motion start delay 2).
// Arguments: none.
void sub_2EF7E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002ef7e0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, a0, gbtl::kFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, gbtl::kFlags);
    a0 = 0;
    jal(ctx, 0x2EF810u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 9;
    jal(ctx, 0x2EF820u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2EF830u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl8::kUnitTail1);
    v0 = 269;
    for (;;) {
        // 0x002ef86c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ef850
        charge(ctx, 3);
        lhu(v1, a0, unit::kId);
        if (v1 == v0) {
            // 0x002ef864
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002ef85c
            charge(ctx, 2);
        }
        // 0x002ef868
        charge(ctx, 1);
        lw(a0, a0, unit::kPrev);
    }
    // 0x002ef874
    charge(ctx, 84);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -24328);  // "E1A8_99.ADX"
    jal(ctx, 0x2EF880u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2EF890u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2EF8B0u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 2;
    sh(v1, v0, pkt::kStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2EF8CCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EF8DCu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EF8FCu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EF918u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    jal(ctx, 0x2EF938u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EF948u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 0;
    jal(ctx, 0x2EF968u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2EF984u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2EF994u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2EF9A0u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002EFC90 sub_2EFC90 -- 52 bytes; frame 0x10: ra sp+0x0
// Creates the event packet sub_2EFE50 / sub_2F0580 for the action (sub_2E4220).
// Arguments: a0 btlAction.
void sub_2EFC90(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002efc90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    a0 = 0x2F0000;
    a0 = addiu(a0, -432);  // &sub_2EFE50
    a1 = 0x2F0000;
    a1 = addiu(a1, 1408);  // &sub_2F0580
    jal(ctx, 0x2EFCACu, gen::fn_sub_2E4220_002e4220);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EFCD0 sub_2EFCD0 -- 52 bytes; frame 0x10: ra sp+0x0
// Creates the event packet sub_2F05F0 / sub_2F0E30 for the action.
// Arguments: a0 btlAction.
void sub_2EFCD0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002efcd0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    a0 = 0x2F0000;
    a0 = addiu(a0, 1520);  // &sub_2F05F0
    a1 = 0x2F0000;
    a1 = addiu(a1, 3632);  // &sub_2F0E30
    jal(ctx, 0x2EFCECu, gen::fn_sub_2E4220_002e4220);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002EFD20 sub_2EFD20 -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Call packet: gBtl +2900 = 0, the unit's action's (sub_29A1D0) flags2 bit 3 cleared; the unit's status 0x100000 cleared
// (datCalcClearBadStatus, sub_2831C0(u, 6)), sub_2D3FE0, and with a model its +904 bit 0x20 set; returns 1.
// Arguments: a0 btlUnit.
void sub_2EFD20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002efd20
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2EFD30u, gen::fn_sub_29A1D0_0029a1d0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(zero, v1, gbtl::kBossWork4);
    lhu(v1, v0, act::kFlags2);
    v1 = v1 & 0xFFF7;
    sh(v1, v0, act::kFlags2);
    lw(a0, s0, unit::kDat);
    a1 = 0x100000;
    jal(ctx, 0x2EFD54u, gen::fn_datCalcClearBadStatus_00300560);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x2EFD64u, gen::fn_sub_2831C0_002831c0);
    a0 = s0;
    jal(ctx, 0x2EFD70u, gen::fn_sub_2D3FE0_002d3fe0);
    lw(v0, s0, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x002efd88
        charge(ctx, 4);
        lw(v1, s0, unit::kModel);
        lbu(v0, v1, 904);
        v0 = v0 | 0x20;
        sb(v0, v1, 904);
    }
    // 0x002efd98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EFDB0 sub_2EFDB0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Call packet: the reverse of sub_2EFD20 (gBtl +2900 = 1, bit 3 set, status 0x100000 set, sub_2D3E00, model
// +904 bit 0x20 cleared); returns 1.
// Arguments: a0 btlUnit.
void sub_2EFDB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002efdb0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2EFDC0u, gen::fn_sub_29A1D0_0029a1d0);
    a0 = 1;
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(a0, v1, gbtl::kBossWork4);
    lhu(v1, v0, act::kFlags2);
    v1 = v1 | 0x8;
    sh(v1, v0, act::kFlags2);
    lw(a0, s0, unit::kDat);
    a1 = 0x100000;
    jal(ctx, 0x2EFDE8u, gen::fn_datCalcSetBadStatus_003004f0);
    a0 = s0;
    a1 = 6;
    jal(ctx, 0x2EFDF8u, gen::fn_sub_2831C0_002831c0);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x2EFE08u, gen::fn_sub_2D3E00_002d3e00);
    lw(v0, s0, unit::kModelFlags);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x002efe20
        charge(ctx, 4);
        lw(v1, s0, unit::kModel);
        lbu(v0, v1, 904);
        v0 = v0 & 0xDF;
        sb(v0, v1, 904);
    }
    // 0x002efe30 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002EFE50 sub_2EFE50 -- 1832 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Event packet update (sub_2EFC90's): the camera script 7 (unit +118 = 281) or 8, the action's command motion
// (sub_2BD590(unit, skill +110)), motion 7 (sub_284200 / sub_2838D0), the wait / sub_27FE90 / sub_2A3B40 chain, the
// cell position (sub_2FDDB0) and the colour fades (sub_29EA60 ...).
// Arguments: a0 btlAction.
void sub_2EFE50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002efe50
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
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
    lh(s6, a0, 110);
    ld(s1, a0, 0);
    lh(s7, a0, 118);
    a0 = 0;
    jal(ctx, 0x2EFE90u, gen::fn_sub_2B8F90_002b8f90);
    s5 = v0;
    fp = dsll32(s7, 16);
    fp = dsra32(fp, 16);
    v0 = 281;
    if (fp != v0) {
        // 0x002efed4
        charge(ctx, 7);
        a0 = 8;
        jal(ctx, 0x2EFED8u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s5;
        a1 = v0;
        jal(ctx, 0x2EFEE8u, gen::fn_sub_2B90D0_002b90d0);
    } else {
        // 0x002efeb0
        charge(ctx, 9);
        a0 = 7;
        jal(ctx, 0x2EFEB4u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s5;
        a1 = v0;
        jal(ctx, 0x2EFEC4u, gen::fn_sub_2B90D0_002b90d0);
    }
    // 0x002efef0
    charge(ctx, 110);
    a1 = s6 & 0xFFFF;
    lw(a0, s4, act::kUnit);
    jal(ctx, 0x2EFEF8u, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    sd(s1, v0, pkt::kOwner);
    a1 = 3;
    jal(ctx, 0x2EFF0Cu, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, s4, act::kUnit);
    a1 = 7;
    a2 = 6;
    a3 = 2;
    jal(ctx, 0x2EFF2Cu, gen::fn_sub_284200_00284200);
    s2 = v0;
    sd(s1, v0, pkt::kOwner);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x2EFF44u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, s4, act::kUnit);
    a1 = 7;
    jal(ctx, 0x2EFF5Cu, gen::fn_sub_2838D0_002838d0);
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    sq(v0, sp, 0xA0);
    ld(s0, s2, pkt::kId);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2EFF7Cu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EFFA0u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s4, act::kUnit);
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2EFFBCu, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2EFFE0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2EFFF0u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2F0014u, gen::fn_sub_27ED20_0027ed20);
    a0 = s4;
    a1 = 17;
    jal(ctx, 0x2F0024u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2F0048u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s4, act::kUnit);
    a1 = addiu(sp, 0xB8);
    jal(ctx, 0x2F0058u, gen::fn_sub_2FDDB0_002fddb0);
    lw(a0, s4, act::kUnit);
    a1 = addiu(sp, 0xB8);
    a2 = 0;
    jal(ctx, 0x2F006Cu, gen::fn_sub_2822B0_002822b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F0090u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s3, v0, gbtl::kActionList);
    for (;;) {
        // 0x002f010c
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f00a8
        charge(ctx, 2);
        if (s4 != s3) {
            // 0x002f00b0
            charge(ctx, 4);
            lhu(v0, s3, act::kFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002f00c0
                charge(ctx, 18);
                lw(a0, s3, act::kUnit);
                v0 = 0xFF0000;
                a1 = v0 | 0xFFFF;  // &0xFFFFFF
                a2 = 0;
                a3 = 0;
                t0 = 2;
                t1 = 0;
                jal(ctx, 0x2F00DCu, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                ld(v1, s2, pkt::kId);
                sd(v1, v0, bcore::kCondArg);
                sd(s1, v0, pkt::kOwner);
                a1 = 0;
                jal(ctx, 0x2F0100u, gen::fn_sub_27ED20_0027ed20);
            }
        }
        // 0x002f0108
        charge(ctx, 1);
        lw(s3, s3, act::kNext);
    }
    // 0x002f0114
    charge(ctx, 174);
    s2 = s6 & 0xFFFF;
    a0 = s2;
    a1 = addiu(sp, 0xCC);
    a2 = addiu(sp, 0xC8);
    jal(ctx, 0x2F0124u, gen::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 0xCC);
    lw(a1, sp, 0xC8);
    a2 = 16;
    jal(ctx, 0x2F0138u, gen::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s0, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F0158u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    jal(ctx, 0x2F0164u, gen::fn_sub_29EC00_0029ec00);
    s3 = v0;
    a0 = s2;
    a1 = addiu(sp, 0xCC);
    a2 = addiu(sp, 0xC8);
    jal(ctx, 0x2F017Cu, gen::fn_sub_29EC80_0029ec80);
    a0 = s3;
    lw(a1, sp, 0xCC);
    lw(a2, sp, 0xC8);
    a3 = 16;
    t0 = 4;
    jal(ctx, 0x2F0198u, gen::fn_sub_2A0050_002a0050);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s0, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F01B8u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    jal(ctx, 0x2F01C4u, gen::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = 16;
    jal(ctx, 0x2F01D4u, gen::fn_sub_2A1280_002a1280);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s0, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F01F4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s4;
    a1 = s2;
    a2 = 16;
    jal(ctx, 0x2F0208u, gen::fn_sub_2A1B00_002a1b00);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s0, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F0228u, gen::fn_sub_27ED20_0027ed20);
    s3 = s7 & 0xFFFF;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kSetupEnemies);
    a1 = s3;
    jal(ctx, 0x2F0240u, gen::fn_datUnitEcAddEnemy_002ff540);
    a0 = 1;
    a1 = s3;
    a2 = v0;
    jal(ctx, 0x2F0254u, gen::fn_sub_289650_00289650);
    s6 = v0;
    lw(s2, v0, act::kUnit);
    a0 = s2;
    a1 = fp;
    jal(ctx, 0x2F026Cu, gen::fn_sub_2889C0_002889c0);
    jal(ctx, 0x2F0274u, gen::fn_sub_2B71E0_002b71e0);
    sw(zero, sp, 0xB8);
    v0 = lui(0xC47A);
    sw(v0, sp, 0xBC);
    sw(zero, sp, 0xC0);
    a0 = s2;
    a1 = addiu(sp, 0xB8);
    jal(ctx, 0x2F0294u, gen::fn_sub_27F650_0027f650);
    a0 = s2;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x2F02A8u, gen::fn_sub_352C50_00352c50);
    a0 = s2;
    a1 = s3;
    a2 = 126;
    jal(ctx, 0x2F02BCu, gen::fn_sub_285690_00285690);
    s3 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s0, v0, bcore::kCondArg);
    lq(v1, sp, 0xA0);
    v1 = addiu(v1, 6);
    sh(v1, v0, pkt::kStartDelay);
    sd(s1, v0, pkt::kOwner);
    a0 = s3;
    a1 = 1;
    jal(ctx, 0x2F02ECu, gen::fn_sub_27ED20_0027ed20);
    a0 = s5;
    lw(a1, s4, act::kUnit);
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F0308u, gen::fn_sub_2BAF90_002baf90);
    s0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s3, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    sd(s1, v0, pkt::kOwner);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x2F0330u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = si(-1);
    a2 = 0;
    a3 = 0;
    t0 = 1;
    t1 = t0;
    jal(ctx, 0x2F0350u, gen::fn_sub_285D30_00285d30);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s3, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    a1 = 1;
    sh(a1, v0, pkt::kStartDelay);
    sd(s1, v0, pkt::kOwner);
    jal(ctx, 0x2F0378u, gen::fn_sub_27ED20_0027ed20);
    a0 = s4;
    a1 = 37;
    jal(ctx, 0x2F0388u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    v1 = 30;
    sh(v1, v0, 74);
    sd(s1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2F03B4u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s2, v0, gbtl::kActionList);
    for (;;) {
        // 0x002f0434
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f03cc
        charge(ctx, 2);
        if (s4 != s2) {
            // 0x002f03d4
            charge(ctx, 2);
            if (s4 != s6) {
                // 0x002f03dc
                charge(ctx, 4);
                lhu(v0, s2, act::kFlags2);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x002f03ec
                    charge(ctx, 17);
                    lw(a0, s2, act::kUnit);
                    a1 = si(-1);
                    a2 = 0;
                    a3 = 0;
                    t0 = 1;
                    t1 = 0;
                    jal(ctx, 0x2F0404u, gen::fn_sub_285D30_00285d30);
                    a0 = v0;
                    v1 = 4;
                    sb(v1, v0, 0);
                    ld(v1, s0, pkt::kId);
                    sd(v1, v0, bcore::kCondArg);
                    sd(s1, v0, pkt::kOwner);
                    a1 = 0;
                    jal(ctx, 0x2F0428u, gen::fn_sub_27ED20_0027ed20);
                }
            }
        }
        // 0x002f0430
        charge(ctx, 1);
        lw(s2, s2, act::kNext);
    }
    // 0x002f043c
    charge(ctx, 79);
    jal(ctx, 0x2F043Cu, gen::fn_sub_1FDD40_001fdd40);
    a0 = 16;
    jal(ctx, 0x2F0448u, gen::fn_sub_29FA50_0029fa50);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F0478u, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    a1 = 4;
    jal(ctx, 0x2F0488u, gen::fn_sub_2A1080_002a1080);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F04B8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    jal(ctx, 0x2F04C4u, gen::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s1, v0, pkt::kOwner);
    a1 = 1;
    jal(ctx, 0x2F04F4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 8;
    jal(ctx, 0x2F0500u, gen::fn_sub_2A1DB0_002a1db0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s0, pkt::kId);
    sd(v1, v0, bcore::kCondArg);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s1, v0, pkt::kOwner);
    a1 = 0;
    jal(ctx, 0x2F0530u, gen::fn_sub_27ED20_0027ed20);
    a0 = s5;
    jal(ctx, 0x2F053Cu, gen::fn_sub_2B9030_002b9030);
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
    sp = addiu(sp, 0xD0);
}

}  // namespace p3fes::game
