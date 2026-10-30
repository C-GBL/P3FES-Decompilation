// The boss-encounter scripts of 0x2F0580-0x2FB850 (slice battle9; battle9.h has the groups and the record names).
// The bodies come from p3fes_handgen: register for register and block for block as the recompiled bodies (frame,
// spills, $ra links, cycle charges and check points, game/include/p3fes/game/hg_cpu.h). On top of that the record
// offsets are named (bcore:: / b9::) and each function's role is given (ours in brackets, ADR-0009).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle9.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_MT_Misc_BitChk_003951d0(p3fes::EEContext&);
void fn_datCalcClearBadStatus_00300560(p3fes::EEContext&);
void fn_datCalcClearEffect_00301540(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcIsHpSkill_002d6370(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datCalcSetHp_002ffd90(p3fes::EEContext&);
void fn_datCalcSetSp_002ffdc0(p3fes::EEContext&);
void fn_datUnitEcAddEnemy_002ff540(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_sub_174E20_00174e20(p3fes::EEContext&);
void fn_sub_175130_00175130(p3fes::EEContext&);
void fn_sub_1757F0_001757f0(p3fes::EEContext&);
void fn_sub_17B220_0017b220(p3fes::EEContext&);
void fn_sub_1FDD40_001fdd40(p3fes::EEContext&);
void fn_sub_27CE50_0027ce50(p3fes::EEContext&);
void fn_sub_27E390_0027e390(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_27F410_0027f410(p3fes::EEContext&);
void fn_sub_27F650_0027f650(p3fes::EEContext&);
void fn_sub_27F730_0027f730(p3fes::EEContext&);
void fn_sub_27F930_0027f930(p3fes::EEContext&);
void fn_sub_27FE90_0027fe90(p3fes::EEContext&);
void fn_sub_2822B0_002822b0(p3fes::EEContext&);
void fn_sub_2831C0_002831c0(p3fes::EEContext&);
void fn_sub_2835E0_002835e0(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_285690_00285690(p3fes::EEContext&);
void fn_sub_285D30_00285d30(p3fes::EEContext&);
void fn_sub_287490_00287490(p3fes::EEContext&);
void fn_sub_287510_00287510(p3fes::EEContext&);
void fn_sub_287580_00287580(p3fes::EEContext&);
void fn_sub_287B20_00287b20(p3fes::EEContext&);
void fn_sub_2889C0_002889c0(p3fes::EEContext&);
void fn_sub_288F80_00288f80(p3fes::EEContext&);
void fn_sub_289650_00289650(p3fes::EEContext&);
void fn_sub_29A1D0_0029a1d0(p3fes::EEContext&);
void fn_sub_29A2C0_0029a2c0(p3fes::EEContext&);
void fn_sub_29A320_0029a320(p3fes::EEContext&);
void fn_sub_29A470_0029a470(p3fes::EEContext&);
void fn_sub_29A690_0029a690(p3fes::EEContext&);
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
void fn_sub_2A2290_002a2290(p3fes::EEContext&);
void fn_sub_2A3110_002a3110(p3fes::EEContext&);
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);
void fn_sub_2A3D70_002a3d70(p3fes::EEContext&);
void fn_sub_2A3E80_002a3e80(p3fes::EEContext&);
void fn_sub_2A4690_002a4690(p3fes::EEContext&);
void fn_sub_2B71E0_002b71e0(p3fes::EEContext&);
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);
void fn_sub_2B9030_002b9030(p3fes::EEContext&);
void fn_sub_2B90D0_002b90d0(p3fes::EEContext&);
void fn_sub_2B96E0_002b96e0(p3fes::EEContext&);
void fn_sub_2BAC00_002bac00(p3fes::EEContext&);
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);
void fn_sub_2BB2F0_002bb2f0(p3fes::EEContext&);
void fn_sub_2BB6F0_002bb6f0(p3fes::EEContext&);
void fn_sub_2BC7E0_002bc7e0(p3fes::EEContext&);
void fn_sub_2BC890_002bc890(p3fes::EEContext&);
void fn_sub_2BD480_002bd480(p3fes::EEContext&);
void fn_sub_2BD590_002bd590(p3fes::EEContext&);
void fn_sub_2BD850_002bd850(p3fes::EEContext&);
void fn_sub_2BDBD0_002bdbd0(p3fes::EEContext&);
void fn_sub_2C3770_002c3770(p3fes::EEContext&);
void fn_sub_2D1D00_002d1d00(p3fes::EEContext&);
void fn_sub_2D2280_002d2280(p3fes::EEContext&);
void fn_sub_2D5DC0_002d5dc0(p3fes::EEContext&);
void fn_sub_2D6620_002d6620(p3fes::EEContext&);
void fn_sub_2D7890_002d7890(p3fes::EEContext&);
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);
void fn_sub_2DB740_002db740(p3fes::EEContext&);
void fn_sub_2DB800_002db800(p3fes::EEContext&);
void fn_sub_2DB890_002db890(p3fes::EEContext&);
void fn_sub_2DCE90_002dce90(p3fes::EEContext&);
void fn_sub_2DD100_002dd100(p3fes::EEContext&);
void fn_sub_2DD4A0_002dd4a0(p3fes::EEContext&);
void fn_sub_2DD5E0_002dd5e0(p3fes::EEContext&);
void fn_sub_2DD690_002dd690(p3fes::EEContext&);
void fn_sub_2DD760_002dd760(p3fes::EEContext&);
void fn_sub_2E30A0_002e30a0(p3fes::EEContext&);
void fn_sub_2E4220_002e4220(p3fes::EEContext&);
void fn_sub_2E9450_002e9450(p3fes::EEContext&);
void fn_sub_2E95F0_002e95f0(p3fes::EEContext&);
void fn_sub_2E9AC0_002e9ac0(p3fes::EEContext&);
void fn_sub_2EA210_002ea210(p3fes::EEContext&);
void fn_sub_2EA590_002ea590(p3fes::EEContext&);
void fn_sub_2EC2C0_002ec2c0(p3fes::EEContext&);
void fn_sub_2EC790_002ec790(p3fes::EEContext&);
void fn_sub_2ECAC0_002ecac0(p3fes::EEContext&);
void fn_sub_2EF670_002ef670(p3fes::EEContext&);
void fn_sub_2EF7E0_002ef7e0(p3fes::EEContext&);
void fn_sub_2F0580_002f0580(p3fes::EEContext&);
void fn_sub_2F05F0_002f05f0(p3fes::EEContext&);
void fn_sub_2F0E30_002f0e30(p3fes::EEContext&);
void fn_sub_2F0EA0_002f0ea0(p3fes::EEContext&);
void fn_sub_2F14A0_002f14a0(p3fes::EEContext&);
void fn_sub_2F1680_002f1680(p3fes::EEContext&);
void fn_sub_2F1810_002f1810(p3fes::EEContext&);
void fn_sub_2F19D0_002f19d0(p3fes::EEContext&);
void fn_sub_2F1D40_002f1d40(p3fes::EEContext&);
void fn_sub_2F1F00_002f1f00(p3fes::EEContext&);
void fn_sub_2F2090_002f2090(p3fes::EEContext&);
void fn_sub_2F2250_002f2250(p3fes::EEContext&);
void fn_sub_2F2450_002f2450(p3fes::EEContext&);
void fn_sub_2F2490_002f2490(p3fes::EEContext&);
void fn_sub_2F2550_002f2550(p3fes::EEContext&);
void fn_sub_2F2840_002f2840(p3fes::EEContext&);
void fn_sub_2F2890_002f2890(p3fes::EEContext&);
void fn_sub_2F2B40_002f2b40(p3fes::EEContext&);
void fn_sub_2F2B90_002f2b90(p3fes::EEContext&);
void fn_sub_2F3190_002f3190(p3fes::EEContext&);
void fn_sub_2F3320_002f3320(p3fes::EEContext&);
void fn_sub_2F3520_002f3520(p3fes::EEContext&);
void fn_sub_2F3670_002f3670(p3fes::EEContext&);
void fn_sub_2F3760_002f3760(p3fes::EEContext&);
void fn_sub_2F3840_002f3840(p3fes::EEContext&);
void fn_sub_2F39B0_002f39b0(p3fes::EEContext&);
void fn_sub_2F3A80_002f3a80(p3fes::EEContext&);
void fn_sub_2F43A0_002f43a0(p3fes::EEContext&);
void fn_sub_2F4410_002f4410(p3fes::EEContext&);
void fn_sub_2F4490_002f4490(p3fes::EEContext&);
void fn_sub_2F4540_002f4540(p3fes::EEContext&);
void fn_sub_2F46D0_002f46d0(p3fes::EEContext&);
void fn_sub_2F4890_002f4890(p3fes::EEContext&);
void fn_sub_2F4950_002f4950(p3fes::EEContext&);
void fn_sub_2F4A40_002f4a40(p3fes::EEContext&);
void fn_sub_2F4C00_002f4c00(p3fes::EEContext&);
void fn_sub_2F4CE0_002f4ce0(p3fes::EEContext&);
void fn_sub_2F4E70_002f4e70(p3fes::EEContext&);
void fn_sub_2F5030_002f5030(p3fes::EEContext&);
void fn_sub_2F5330_002f5330(p3fes::EEContext&);
void fn_sub_2F5490_002f5490(p3fes::EEContext&);
void fn_sub_2F5660_002f5660(p3fes::EEContext&);
void fn_sub_2F5870_002f5870(p3fes::EEContext&);
void fn_sub_2F5980_002f5980(p3fes::EEContext&);
void fn_sub_2F5A70_002f5a70(p3fes::EEContext&);
void fn_sub_2F5D80_002f5d80(p3fes::EEContext&);
void fn_sub_2F6120_002f6120(p3fes::EEContext&);
void fn_sub_2F6330_002f6330(p3fes::EEContext&);
void fn_sub_2F6510_002f6510(p3fes::EEContext&);
void fn_sub_2F6840_002f6840(p3fes::EEContext&);
void fn_sub_2F6AB0_002f6ab0(p3fes::EEContext&);
void fn_sub_2F6C20_002f6c20(p3fes::EEContext&);
void fn_sub_2F7DC0_002f7dc0(p3fes::EEContext&);
void fn_sub_2F8460_002f8460(p3fes::EEContext&);
void fn_sub_2F87E0_002f87e0(p3fes::EEContext&);
void fn_sub_2F8810_002f8810(p3fes::EEContext&);
void fn_sub_2F88C0_002f88c0(p3fes::EEContext&);
void fn_sub_2F8A40_002f8a40(p3fes::EEContext&);
void fn_sub_2FAC80_002fac80(p3fes::EEContext&);
void fn_sub_2FACC0_002facc0(p3fes::EEContext&);
void fn_sub_2FB690_002fb690(p3fes::EEContext&);
void fn_sub_2FDDB0_002fddb0(p3fes::EEContext&);
void fn_sub_352C50_00352c50(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_395170_00395170(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x002F0580 sub_2F0580 -- 108 bytes; frame 0x10: ra sp+0x0
// [btlBossSummonDone] The summon scene's done callback ($a0 the action): 1 while the action still owns queued packets
// (sub_27E390 [btlPacketFindByOwner], mask 0x3FFFFFFFFFFFFFFF); then sub_352C50(0, 0, 0) and 0.
void sub_2F0580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f0580
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
    jal(ctx, 0x2F05A8u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f05d8
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f05b8
        charge(ctx, 8);
        a0 = 0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x2F05C4u, gen::fn_sub_352C50_00352c50);
        v0 = 0;
    }
    // 0x002f05dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F05F0 sub_2F05F0 -- 2108 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlBossSummon] The summon scene ($a0 the action): binds BED file 6 (sub_2F87E0) to a fresh handle; queues the
// actor's effect (sub_2BD590 with its skill +110), its motion (sub_284200) and a chain of packets that wait on that
// motion (sub_2B8D60(3, 4095), the transform sub_27FE90 with 0x6978B0, sub_2A3B40(0, 1) / (action, 17), the turn
// sub_2822B0 to the cell sub_2FDDB0 gives); sub_285D30 on every other action with a unit (+26 bit 0); the skill's
// camera set (sub_29EA60 .. sub_2A1B00); then adds the three enemies of the action's u16[3] at +118 (datUnitEcAddEnemy,
// sub_289650, sub_2889C0 with the signed id, sub_285690(.., 382) delayed 30, sub_285D30), places them (sub_352C50,
// sub_2B71E0, sub_27F650 at (0, -1024, 0)), sub_2BB2F0 on gBtl +3240, sub_2DD100(10, 2, 5), the unit effect, the call
// packet sub_2EFD20 (delay 120), sub_2B8D60, sub_2A3B40(action, 37), sub_285D30 back on the other actions and the four
// closing packets (sub_29FA50, sub_2A1080, sub_2A16C0, sub_2A1DB0; +71 bit 0x20 cleared); frees the handle.
void sub_2F05F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f05f0
    enter(ctx, 126);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
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
    s0 = a0;
    lh(s6, a0, b9::kActSkill);
    ld(s2, a0, 0);
    a0 = 0;
    jal(ctx, 0x2F062Cu, gen::fn_sub_2B8F90_002b8f90);
    fp = v0;
    a0 = 6;
    jal(ctx, 0x2F063Cu, gen::fn_sub_2F87E0_002f87e0);
    a0 = fp;
    a1 = v0;
    jal(ctx, 0x2F064Cu, gen::fn_sub_2B90D0_002b90d0);
    a1 = s6 & 0xFFFF;
    lw(a0, s0, bcore::kActUnit);
    jal(ctx, 0x2F065Cu, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    sd(s2, v0, bcore::kPktOwner);
    a1 = 3;
    jal(ctx, 0x2F0670u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, s0, bcore::kActUnit);
    a1 = 0;
    a2 = 0;
    a3 = 1;
    jal(ctx, 0x2F0690u, gen::fn_sub_284200_00284200);
    s4 = v0;
    sd(s2, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x2F06A8u, gen::fn_sub_27ED20_0027ed20);
    ld(s1, s4, bcore::kPktId);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F06BCu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F06E0u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s0, bcore::kActUnit);
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F06FCu, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F0720u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F0730u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F0754u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = 17;
    jal(ctx, 0x2F0764u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F0788u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s0, bcore::kActUnit);
    a1 = addiu(sp, 0xB8);
    jal(ctx, 0x2F0798u, gen::fn_sub_2FDDB0_002fddb0);
    lw(a0, s0, bcore::kActUnit);
    a1 = addiu(sp, 0xB8);
    a2 = 0;
    jal(ctx, 0x2F07ACu, gen::fn_sub_2822B0_002822b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F07D0u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(s3, v0, bcore::kBtlActionList);
    for (;;) {
        // 0x002f084c
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f07e8
        charge(ctx, 2);
        if (s0 != s3) {
            // 0x002f07f0
            charge(ctx, 4);
            lhu(v0, s3, bcore::kActFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002f0800
                charge(ctx, 18);
                lw(a0, s3, bcore::kActUnit);
                v0 = 0xFF0000;
                a1 = v0 | 0xFFFF;  // &0xFFFFFF
                a2 = 0;
                a3 = 0;
                t0 = 2;
                t1 = 0;
                jal(ctx, 0x2F081Cu, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, b9::kPktWaitKind0);
                ld(v1, s4, bcore::kPktId);
                sd(v1, v0, b9::kPktWaitId0);
                sd(s2, v0, bcore::kPktOwner);
                a1 = 0;
                jal(ctx, 0x2F0840u, gen::fn_sub_27ED20_0027ed20);
            }
        }
        // 0x002f0848
        charge(ctx, 1);
        lw(s3, s3, bcore::kActLinkNext);
    }
    // 0x002f0854
    charge(ctx, 75);
    s3 = s6 & 0xFFFF;
    a0 = s3;
    a1 = addiu(sp, 0xDC);
    a2 = addiu(sp, 0xD8);
    jal(ctx, 0x2F0864u, gen::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 0xDC);
    lw(a1, sp, 0xD8);
    a2 = 16;
    jal(ctx, 0x2F0878u, gen::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    sd(s1, v0, 8);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0898u, gen::fn_sub_27ED20_0027ed20);
    a0 = s3;
    jal(ctx, 0x2F08A4u, gen::fn_sub_29EC00_0029ec00);
    s6 = v0;
    a0 = s3;
    a1 = addiu(sp, 0xDC);
    a2 = addiu(sp, 0xD8);
    jal(ctx, 0x2F08BCu, gen::fn_sub_29EC80_0029ec80);
    a0 = s6;
    lw(a1, sp, 0xDC);
    lw(a2, sp, 0xD8);
    a3 = 16;
    t0 = 0;
    jal(ctx, 0x2F08D8u, gen::fn_sub_2A0050_002a0050);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    sd(s1, v0, 8);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F08F8u, gen::fn_sub_27ED20_0027ed20);
    a0 = s3;
    jal(ctx, 0x2F0904u, gen::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = 16;
    jal(ctx, 0x2F0914u, gen::fn_sub_2A1280_002a1280);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    sd(s1, v0, 8);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0934u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = s3;
    a2 = 16;
    jal(ctx, 0x2F0948u, gen::fn_sub_2A1B00_002a1b00);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    sd(s1, v0, 8);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0968u, gen::fn_sub_27ED20_0027ed20);
    s7 = 0;
    s6 = 0;
    for (;;) {
        // 0x002f0a8c
        charge(ctx, 5);
        v1 = dsll32(s6, 16);
        v1 = dsra32(v1, 16);
        v0 = slti(v1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f0980
        charge(ctx, 67);
        v0 = sll(v1, 1);
        v0 = addu(s0, v0);
        lh(v0, v0, 118);
        sq(v0, sp, 0xA0);
        s5 = v0 & 0xFFFF;
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(a0, v0, bcore::kBtlSetupEnemies);
        a1 = s5;
        jal(ctx, 0x2F09A0u, gen::fn_datUnitEcAddEnemy_002ff540);
        a0 = 1;
        a1 = s5;
        a2 = v0;
        jal(ctx, 0x2F09B4u, gen::fn_sub_289650_00289650);
        lw(s3, v0, bcore::kActUnit);
        v0 = dsll32(s7, 16);
        v0 = dsra32(v0, 16);
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        sw(s3, v0, 200);
        v0 = addiu(s7, 1);
        s7 = dsll32(v0, 16);
        s7 = dsra32(s7, 16);
        lq(v0, sp, 0xA0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s3;
        jal(ctx, 0x2F09F0u, gen::fn_sub_2889C0_002889c0);
        a0 = s3;
        a1 = s5;
        a2 = 382;
        jal(ctx, 0x2F0A04u, gen::fn_sub_285690_00285690);
        s5 = v0;
        v1 = 4;
        sb(v1, v0, b9::kPktWaitKind0);
        sd(s1, v0, 8);
        v1 = 30;
        sh(v1, v0, bcore::kPktStartDelay);
        sd(s2, v0, bcore::kPktOwner);
        a0 = s5;
        a1 = 1;
        jal(ctx, 0x2F0A30u, gen::fn_sub_27ED20_0027ed20);
        a0 = s3;
        a1 = si(-1);
        a2 = 0;
        a3 = 0;
        t0 = 1;
        t1 = t0;
        jal(ctx, 0x2F0A50u, gen::fn_sub_285D30_00285d30);
        a0 = v0;
        v1 = 4;
        sb(v1, v0, b9::kPktWaitKind0);
        ld(v1, s5, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId0);
        a1 = 1;
        sh(a1, v0, bcore::kPktStartDelay);
        sd(s2, v0, bcore::kPktOwner);
        jal(ctx, 0x2F0A78u, gen::fn_sub_27ED20_0027ed20);
        v0 = addiu(s6, 1);
        s6 = dsll32(v0, 16);
        s6 = dsra32(s6, 16);
    }
    // 0x002f0aa0
    charge(ctx, 14);
    lw(a0, sp, 0xC8);
    lw(a1, sp, 0xCC);
    lw(a2, sp, 0xD0);
    jal(ctx, 0x2F0AACu, gen::fn_sub_352C50_00352c50);
    jal(ctx, 0x2F0AB4u, gen::fn_sub_2B71E0_002b71e0);
    sw(zero, sp, 0xB8);
    v0 = lui(0xC47A);
    sw(v0, sp, 0xBC);
    sw(zero, sp, 0xC0);
    s1 = 0;
    for (;;) {
        // 0x002f0afc
        charge(ctx, 5);
        v1 = dsll32(s1, 16);
        v1 = dsra32(v1, 16);
        v0 = slti(v1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f0ad8
        charge(ctx, 9);
        v0 = sll(v1, 2);
        v0 = addu(v0, sp);
        lw(a0, v0, 200);
        a1 = addiu(sp, 0xB8);
        jal(ctx, 0x2F0AE8u, gen::fn_sub_27F650_0027f650);
        v0 = addiu(s1, 1);
        s1 = dsll32(v0, 16);
        s1 = dsra32(s1, 16);
    }
    // 0x002f0b10
    charge(ctx, 94);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtl3240);
    lw(a1, s0, bcore::kActUnit);
    a2 = 0;
    ld(a3, s5, bcore::kPktId);
    t0 = 768;
    jal(ctx, 0x2F0B28u, gen::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F0B48u, gen::fn_sub_27ED20_0027ed20);
    a0 = 10;
    a1 = 2;
    a2 = 5;
    jal(ctx, 0x2F0B5Cu, gen::fn_sub_2DD100_002dd100);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F0B7Cu, gen::fn_sub_27ED20_0027ed20);
    lw(a1, s0, bcore::kActUnit);
    a0 = fp;
    a2 = a1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F0B98u, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s5, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2F0BC0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0x2F0000;
    a0 = addiu(a0, -736);  // &sub_2EFD20
    lw(a1, s0, bcore::kActUnit);
    jal(ctx, 0x2F0BD4u, gen::fn_sub_27F410_0027f410);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    v1 = 120;
    sh(v1, v0, bcore::kPktStartDelay);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0C00u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F0C10u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0C34u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = 37;
    jal(ctx, 0x2F0C44u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    v1 = 30;
    sh(v1, v0, bcore::kPktEndDelay);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F0C70u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(s3, v0, bcore::kBtlActionList);
    for (;;) {
        // 0x002f0ce8
        charge(ctx, 2);
        if (s3 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f0c88
        charge(ctx, 2);
        if (s0 != s3) {
            // 0x002f0c90
            charge(ctx, 4);
            lhu(v0, s3, bcore::kActFlags2);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x002f0ca0
                charge(ctx, 17);
                lw(a0, s3, bcore::kActUnit);
                a1 = si(-1);
                a2 = 0;
                a3 = 0;
                t0 = 1;
                t1 = 0;
                jal(ctx, 0x2F0CB8u, gen::fn_sub_285D30_00285d30);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, b9::kPktWaitKind0);
                ld(v1, s1, bcore::kPktId);
                sd(v1, v0, b9::kPktWaitId0);
                sd(s2, v0, bcore::kPktOwner);
                a1 = 0;
                jal(ctx, 0x2F0CDCu, gen::fn_sub_27ED20_0027ed20);
            }
        }
        // 0x002f0ce4
        charge(ctx, 1);
        lw(s3, s3, bcore::kActLinkNext);
    }
    // 0x002f0cf0
    charge(ctx, 79);
    jal(ctx, 0x2F0CF0u, gen::fn_sub_1FDD40_001fdd40);
    a0 = 16;
    jal(ctx, 0x2F0CFCu, gen::fn_sub_29FA50_0029fa50);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0D2Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    a1 = 0;
    jal(ctx, 0x2F0D3Cu, gen::fn_sub_2A1080_002a1080);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0D6Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    jal(ctx, 0x2F0D78u, gen::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F0DA8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 8;
    jal(ctx, 0x2F0DB4u, gen::fn_sub_2A1DB0_002a1db0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s2, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F0DE4u, gen::fn_sub_27ED20_0027ed20);
    a0 = fp;
    jal(ctx, 0x2F0DF0u, gen::fn_sub_2B9030_002b9030);
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
    sp = addiu(sp, 0xE0);
}

// 0x002F0E30 sub_2F0E30 -- 108 bytes; frame 0x10: ra sp+0x0
// [btlBossSceneDone] As sub_2F0580: 1 while the action owns queued packets, else sub_352C50(0, 0, 0) and 0.
void sub_2F0E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f0e30
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
    jal(ctx, 0x2F0E58u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f0e88
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f0e68
        charge(ctx, 8);
        a0 = 0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x2F0E74u, gen::fn_sub_352C50_00352c50);
        v0 = 0;
    }
    // 0x002f0e8c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F0EA0 sub_2F0EA0 -- 1536 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl424ListedScene] Encounter 424's scene for the listed actions (gBtl +2884, count +2896; $a0 the action): pauses
// the turn order (gBtl flag 0x80000), counts the live adds 278..280 and finds the boss 269 among the enemies; binds BED
// 2 (one listed) or 3, and 5 when the live adds number the listed actions, else 4; for each listed action its motion
// 18, then sub_2DD760(3, sub_2F8810(), 0), sub_2B8D60, the transform, the shot, the unit effects (sub_2BAF90),
// sub_287B20(2) and sub_285D30 (delay 65); when the adds number them: the call packet sub_2EFDB0 on the boss, the
// current actor's +24 bit 3 and, once (gBtl +2912), sub_2DB890 / sub_2DB800(32, 49); then gBtl flag 0x400000 and +24 |=
// 7; frees both handles.
void sub_2F0EA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f0ea0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
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
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lhu(s0, a0, b9::kBoss2896);
    lw(v1, a0, bcore::kBtlFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a0, bcore::kBtlFlags);
    s6 = 0;
    s1 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(s2, v0, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f0f6c
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f0f00
        charge(ctx, 6);
        lw(a0, s2, bcore::kUnDat);
        a1 = 0;
        jal(ctx, 0x2F0F08u, gen::fn_datCalcIsDead_0030b5a0);
        if (v0 == 0) {
            // 0x002f0f18
            charge(ctx, 4);
            lhu(v1, s2, bcore::kUnId);
            v0 = 280;
            if (v1 != v0) {
                // 0x002f0f28
                charge(ctx, 3);
                v0 = 279;
                if (v1 == v0) {
                    goto L_002f0f60;
                }
                // 0x002f0f34
                charge(ctx, 3);
                v0 = 278;
                if (v1 == v0) {
                    goto L_002f0f60;
                }
                // 0x002f0f40
                charge(ctx, 3);
                v0 = 269;
                if (v1 == v0) {
                    // 0x002f0f54
                    charge(ctx, 3);
                    s6 = s2;
                } else {
                    // 0x002f0f4c
                    charge(ctx, 2);
                }
                goto L_002f0f68;
            }
        L_002f0f60:
            charge(ctx, 2);
            v0 = addiu(s1, 1);
            s1 = v0 & 0xFFFF;
        }
    L_002f0f68:
        charge(ctx, 1);
        lw(s2, s2, bcore::kUnPrev);
    }
    // 0x002f0f74
    charge(ctx, 15);
    s0 = s0 & 0xFFFF;
    v0 = s1 & 0xFFFF;
    fp = v0 ^ s0;
    fp = sltiu(fp, 1);
    a0 = 0;
    jal(ctx, 0x2F0F88u, gen::fn_sub_2B8F90_002b8f90);
    s2 = v0;
    a0 = 0;
    jal(ctx, 0x2F0F98u, gen::fn_sub_2B8F90_002b8f90);
    s7 = v0;
    v0 = 1;
    if (s0 != v0) {
        // 0x002f0fd4
        charge(ctx, 7);
        a0 = 3;
        jal(ctx, 0x2F0FD8u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s2;
        a1 = v0;
        jal(ctx, 0x2F0FE8u, gen::fn_sub_2B90D0_002b90d0);
    } else {
        // 0x002f0fb0
        charge(ctx, 9);
        a0 = 2;
        jal(ctx, 0x2F0FB4u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s2;
        a1 = v0;
        jal(ctx, 0x2F0FC4u, gen::fn_sub_2B90D0_002b90d0);
    }
    // 0x002f0ff0
    charge(ctx, 2);
    if (fp == 0) {
        // 0x002f101c
        charge(ctx, 7);
        a0 = 4;
        jal(ctx, 0x2F1020u, gen::fn_sub_2F87E0_002f87e0);
        a0 = s7;
        a1 = v0;
        jal(ctx, 0x2F1030u, gen::fn_sub_2B90D0_002b90d0);
    } else {
        // 0x002f0ff8
        charge(ctx, 9);
        a0 = 5;
        jal(ctx, 0x2F0FFCu, gen::fn_sub_2F87E0_002f87e0);
        a0 = s7;
        a1 = v0;
        jal(ctx, 0x2F100Cu, gen::fn_sub_2B90D0_002b90d0);
    }
    // 0x002f1038
    charge(ctx, 5);
    s3 = 0;
    s1 = 0;
    s5 = 0;
    for (;;) {
        // 0x002f10ac
        charge(ctx, 4);
        v0 = s5 & 0xFFFF;
        v0 = slt(v0, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f104c
        charge(ctx, 24);
        v0 = s5 & 0xFFFF;
        v1 = sll(v0, 2);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        v0 = addu(v0, v1);
        lw(s3, v0, 2884);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        lw(a0, s3, bcore::kActUnit);
        a1 = 18;
        a2 = 0;
        a3 = 2;
        jal(ctx, 0x2F1078u, gen::fn_sub_284200_00284200);
        s1 = v0;
        v1 = 2;
        sh(v1, v0, bcore::kPktStartDelay);
        ld(v1, s4, 0);
        sd(v1, v0, bcore::kPktOwner);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x2F109Cu, gen::fn_sub_27ED20_0027ed20);
        v0 = addiu(s5, 1);
        s5 = v0 & 0xFFFF;
    }
    // 0x002f10bc
    charge(ctx, 32);
    jal(ctx, 0x2F10BCu, gen::fn_sub_2F8810_002f8810);
    a0 = 3;
    a1 = v0;
    a2 = 0;
    jal(ctx, 0x2F10D0u, gen::fn_sub_2DD760_002dd760);
    a0 = v0;
    v1 = 2;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s4, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F10F0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F1100u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s4, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F1128u, gen::fn_sub_27ED20_0027ed20);
    s5 = 0;
    for (;;) {
        // 0x002f119c
        charge(ctx, 4);
        v0 = s5 & 0xFFFF;
        v0 = slt(v0, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f113c
        charge(ctx, 24);
        v0 = s5 & 0xFFFF;
        v1 = sll(v0, 2);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        v0 = addu(v0, v1);
        lw(s3, v0, 2884);
        lw(a0, s3, bcore::kActUnit);
        a1 = 0;
        a2 = 0x690000;
        a2 = addiu(a2, 30896);  // &0x6978B0
        a3 = 0;
        jal(ctx, 0x2F1164u, gen::fn_sub_27FE90_0027fe90);
        a0 = v0;
        v1 = 4;
        sb(v1, v0, b9::kPktWaitKind0);
        ld(v1, s1, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId0);
        ld(v1, s4, 0);
        sd(v1, v0, bcore::kPktOwner);
        a1 = 1;
        jal(ctx, 0x2F118Cu, gen::fn_sub_27ED20_0027ed20);
        v0 = addiu(s5, 1);
        s5 = v0 & 0xFFFF;
    }
    // 0x002f11ac
    charge(ctx, 31);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F11B4u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s4, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F11DCu, gen::fn_sub_27ED20_0027ed20);
    lw(a1, s3, bcore::kActUnit);
    a0 = s2;
    a2 = a1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F11F8u, gen::fn_sub_2BAF90_002baf90);
    s3 = v0;
    ld(v1, s4, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s3;
    a1 = 2;
    jal(ctx, 0x2F1214u, gen::fn_sub_27ED20_0027ed20);
    s1 = 0;
    for (;;) {
        // 0x002f12f4
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slt(v0, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f1228
        charge(ctx, 51);
        v0 = s1 & 0xFFFF;
        v1 = sll(v0, 2);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        v0 = addu(v0, v1);
        lw(s5, v0, 2884);
        lw(a1, s5, bcore::kActUnit);
        a0 = s2;
        a2 = a1;
        a3 = 1;
        t0 = 512;
        jal(ctx, 0x2F1250u, gen::fn_sub_2BAF90_002baf90);
        a0 = v0;
        v1 = 5;
        sb(v1, v0, b9::kPktWaitKind0);
        ld(v1, s3, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId0);
        v1 = 55;
        sh(v1, v0, bcore::kPktStartDelay);
        ld(v1, s4, 0);
        sd(v1, v0, bcore::kPktOwner);
        a1 = 2;
        jal(ctx, 0x2F1280u, gen::fn_sub_27ED20_0027ed20);
        lw(a0, s5, bcore::kActUnit);
        a1 = 2;
        jal(ctx, 0x2F1290u, gen::fn_sub_287B20_00287b20);
        lw(a0, s5, bcore::kActUnit);
        v0 = 0xFF0000;
        a1 = v0 | 0xFFFF;  // &0xFFFFFF
        a2 = 6;
        a3 = 0;
        t0 = 4;
        t1 = 0;
        jal(ctx, 0x2F12B4u, gen::fn_sub_285D30_00285d30);
        a0 = v0;
        v1 = 5;
        sb(v1, v0, b9::kPktWaitKind0);
        ld(v1, s3, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId0);
        v1 = 65;
        sh(v1, v0, bcore::kPktStartDelay);
        ld(v1, s4, 0);
        sd(v1, v0, bcore::kPktOwner);
        a1 = 1;
        jal(ctx, 0x2F12E4u, gen::fn_sub_27ED20_0027ed20);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x002f1304
    charge(ctx, 2);
    if (fp != 0) {
        // 0x002f130c
        charge(ctx, 17);
        a0 = 0x2F0000;
        a0 = addiu(a0, -592);  // &sub_2EFDB0
        a1 = s6;
        jal(ctx, 0x2F1318u, gen::fn_sub_27F410_0027f410);
        a0 = v0;
        v1 = 4;
        sb(v1, v0, b9::kPktWaitKind0);
        ld(v1, s3, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId0);
        a1 = 1;
        jal(ctx, 0x2F1338u, gen::fn_sub_27ED20_0027ed20);
        jal(ctx, 0x2F1340u, gen::fn_sub_29AD20_0029ad20);
        if (v0 != 0) {
            // 0x002f1350
            charge(ctx, 3);
            lhu(v1, v0, bcore::kActFlags);
            v1 = v1 | 0x8;
            sh(v1, v0, bcore::kActFlags);
        }
    }
    // 0x002f135c
    charge(ctx, 20);
    a0 = s7;
    a1 = s6;
    a2 = s6;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F1370u, gen::fn_sub_2BAF90_002baf90);
    s0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s4, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s0;
    a1 = 2;
    jal(ctx, 0x2F139Cu, gen::fn_sub_27ED20_0027ed20);
    if (fp != 0) {
        // 0x002f13ac
        charge(ctx, 4);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(v0, v0, b9::kBoss2912);
        if (v0 == 0) {
            // 0x002f13bc
            charge(ctx, 29);
            jal(ctx, 0x2F13BCu, gen::fn_sub_2DB890_002db890);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s0, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            v1 = 65;
            sh(v1, v0, bcore::kPktStartDelay);
            a1 = 1;
            jal(ctx, 0x2F13E4u, gen::fn_sub_27ED20_0027ed20);
            a0 = 32;
            a1 = 49;
            jal(ctx, 0x2F13F4u, gen::fn_sub_2DB800_002db800);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s0, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            v1 = 65;
            sh(v1, v0, bcore::kPktStartDelay);
            a1 = 1;
            jal(ctx, 0x2F141Cu, gen::fn_sub_27ED20_0027ed20);
            v1 = 1;
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(v1, v0, b9::kBoss2912);
        }
    }
    // 0x002f1430
    charge(ctx, 28);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = 0x400000;
    v0 = v1 | v0;
    sw(v0, a0, bcore::kBtlFlags);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lhu(v0, v1, b9::kBtlFlags24);
    v0 = v0 | 0x7;
    sh(v0, v1, b9::kBtlFlags24);
    a0 = s7;
    jal(ctx, 0x2F1458u, gen::fn_sub_2B9030_002b9030);
    a0 = s2;
    jal(ctx, 0x2F1464u, gen::fn_sub_2B9030_002b9030);
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
    sp = addiu(sp, 0xA0);
}

// 0x002F14A0 sub_2F14A0 -- 480 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl424ListedDone] Encounter 424's done callback: 1 while a listed action other than the current actor (sub_29AD20)
// still has unit flag 0x10 (the actor's flag is cleared) or packets remain; then resumes the order, kills and removes
// every listed action (sub_2D7890(a, 0), sub_29A320), clears the count, sets gBtl flag 0x2000000 and queues the three
// closing packets (sub_29FA50(16), sub_2A1080(16, 4), sub_2A16C0(16)); 0.
void sub_2F14A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f14a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lhu(s1, v0, b9::kBoss2896);
    s0 = 0;
    for (;;) {
        // 0x002f1530
        charge(ctx, 4);
        v0 = s0 & 0xFFFF;
        v0 = slt(v0, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f14d0
        charge(ctx, 9);
        v0 = s0 & 0xFFFF;
        v1 = sll(v0, 2);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        v0 = addu(v0, v1);
        lw(s3, v0, 2884);
        jal(ctx, 0x2F14E4u, gen::fn_sub_29AD20_0029ad20);
        if (s3 != v0) {
            // 0x002f14f4
            charge(ctx, 5);
            lw(v0, s3, bcore::kActUnit);
            lw(v0, v0, bcore::kUnFlags);
            v0 = v0 & 0x10;
            if (v0 == 0) {
                goto L_002f1528;
            }
            goto L_002f1508_3;
        }
        // 0x002f1514
        charge(ctx, 5);
        lw(a0, s3, bcore::kActUnit);
        lw(v1, a0, bcore::kUnFlags);
        v0 = si(-17);
        v0 = v1 & v0;
        sw(v0, a0, bcore::kUnFlags);
    L_002f1528:
        charge(ctx, 2);
        v0 = addiu(s0, 1);
        s0 = v0 & 0xFFFF;
    }
    // 0x002f1540
    charge(ctx, 12);
    ld(a0, s2, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2F1560u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f165c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f1570
        charge(ctx, 9);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, bcore::kBtlFlags);
        s0 = 0;
        for (;;) {
            // 0x002f15cc
            charge(ctx, 4);
            v0 = s0 & 0xFFFF;
            v0 = slt(v0, s1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002f1594
            charge(ctx, 14);
            v0 = s0 & 0xFFFF;
            v1 = sll(v0, 2);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            v0 = addu(v0, v1);
            lw(s2, v0, 2884);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x2F15B0u, gen::fn_sub_2D7890_002d7890);
            a0 = s2;
            jal(ctx, 0x2F15BCu, gen::fn_sub_29A320_0029a320);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x002f15dc
        charge(ctx, 32);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        sh(zero, v0, b9::kBoss2896);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = 0x2000000;
        v0 = v1 | v0;
        sw(v0, a0, bcore::kBtlFlags);
        a0 = 16;
        jal(ctx, 0x2F15FCu, gen::fn_sub_29FA50_0029fa50);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F160Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        a1 = 4;
        jal(ctx, 0x2F161Cu, gen::fn_sub_2A1080_002a1080);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F162Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        jal(ctx, 0x2F1638u, gen::fn_sub_2A16C0_002a16c0);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F1648u, gen::fn_sub_27ED20_0027ed20);
        v0 = 0;
    }
    // 0x002f1660 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_002f1508_3:
    charge(ctx, 3);
    v0 = 1;
    // 0x002f1660 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002F1680 sub_2F1680 -- 396 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl425Formation] Encounter 425's formation: the party's cells from the f32 {x, z} x3 table 0x69A110 and the u16
// slots 0x7CC9C0..0x7CC9C4 (the hero, id 1, at (-130, 200) slot 1); the enemies reuse the last cell, enemy 264 at (0,
// -300); each unit's grid cell (sub_2D2280 into +148 / +150) and position (sub_27F650).
void sub_2F1680(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f1680
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -24304);  // &0x69A110
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f16a0
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
    // 0x002f16c4
    charge(ctx, 12);
    lh(a1, gp, -25392);  // 0x7CC9C0
    lh(a0, gp, -25390);  // 0x7CC9C2
    lh(v1, gp, -25388);  // 0x7CC9C4
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f1788
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f16f4
        charge(ctx, 4);
        lhu(v0, s1, bcore::kUnId);
        v1 = 1;
        if (v0 != v1) {
            // 0x002f1720
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f1704
            charge(ctx, 7);
            v0 = lui(0xC302);
            sw(v0, sp, 0x50);
            v0 = 0x43480000;
            sw(v0, sp, 0x58);
            sb(v1, s1, bcore::kUnFormSlot);
        }
        // 0x002f1760
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F176Cu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F177Cu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f1790
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f17ec
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f17a0
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 264;
        if (v1 == v0) {
            // 0x002f17b8
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002f17b0
            charge(ctx, 2);
        }
        // 0x002f17c4
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F17D0u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F17E0u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f17f4
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F1810 sub_2F1810 -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl425DeathScene] Encounter 425's death scene: clears gBtl flag 0x2000000, binds BED 2, finds enemy 264 (the last
// match), its motion 18 (delay 3), then sub_2B8D60(3, 4095), the transform sub_27FE90 (0x6978B0) and the shot
// sub_2A3B40(0, 1) after it, and the unit effect; frees the handle.
void sub_2F1810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f1810
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F1840u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2F1850u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F1860u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 264;
    for (;;) {
        // 0x002f189c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f1880
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f1894
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f188c
            charge(ctx, 2);
        }
        // 0x002f1898
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f18a4
    charge(ctx, 75);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F18BCu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F18D8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F18E8u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F1908u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F1924u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F1944u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F1954u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F1974u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F1990u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F19A0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F19ACu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F19D0 sub_2F19D0 -- 396 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl426Formation] As sub_2F1680 for encounter 426: table 0x69A150, slots 0x7CC9C8.., enemy 271.
void sub_2F19D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f19d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -24240);  // &0x69A150
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f19f0
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
    // 0x002f1a14
    charge(ctx, 12);
    lh(a1, gp, -25384);  // 0x7CC9C8
    lh(a0, gp, -25382);  // 0x7CC9CA
    lh(v1, gp, -25380);  // 0x7CC9CC
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f1ad8
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f1a44
        charge(ctx, 4);
        lhu(v0, s1, bcore::kUnId);
        v1 = 1;
        if (v0 != v1) {
            // 0x002f1a70
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f1a54
            charge(ctx, 7);
            v0 = lui(0xC302);
            sw(v0, sp, 0x50);
            v0 = 0x43480000;
            sw(v0, sp, 0x58);
            sb(v1, s1, bcore::kUnFormSlot);
        }
        // 0x002f1ab0
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F1ABCu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F1ACCu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f1ae0
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f1b3c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f1af0
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 271;
        if (v1 == v0) {
            // 0x002f1b08
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002f1b00
            charge(ctx, 2);
        }
        // 0x002f1b14
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F1B20u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F1B30u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f1b44
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F1D40 sub_2F1D40 -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl426DeathScene] As sub_2F1810 for encounter 426 (enemy 271).
void sub_2F1D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f1d40
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F1D70u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2F1D80u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F1D90u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 271;
    for (;;) {
        // 0x002f1dcc
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f1db0
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f1dc4
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f1dbc
            charge(ctx, 2);
        }
        // 0x002f1dc8
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f1dd4
    charge(ctx, 75);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F1DECu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F1E08u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F1E18u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F1E38u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F1E54u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F1E74u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F1E84u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F1EA4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F1EC0u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F1ED0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F1EDCu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F1F00 sub_2F1F00 -- 396 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl427Formation] As sub_2F1680 for encounter 427: table 0x69A190, slots 0x7CC9D0.., enemy 272.
void sub_2F1F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f1f00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -24176);  // &0x69A190
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f1f20
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
    // 0x002f1f44
    charge(ctx, 12);
    lh(a1, gp, -25376);  // 0x7CC9D0
    lh(a0, gp, -25374);  // 0x7CC9D2
    lh(v1, gp, -25372);  // 0x7CC9D4
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f2008
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f1f74
        charge(ctx, 4);
        lhu(v0, s1, bcore::kUnId);
        v1 = 1;
        if (v0 != v1) {
            // 0x002f1fa0
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f1f84
            charge(ctx, 7);
            v0 = lui(0xC302);
            sw(v0, sp, 0x50);
            v0 = 0x43480000;
            sw(v0, sp, 0x58);
            sb(v1, s1, bcore::kUnFormSlot);
        }
        // 0x002f1fe0
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F1FECu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F1FFCu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f2010
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f206c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f2020
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 272;
        if (v1 == v0) {
            // 0x002f2038
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002f2030
            charge(ctx, 2);
        }
        // 0x002f2044
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F2050u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F2060u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f2074
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F2090 sub_2F2090 -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl427DeathScene] As sub_2F1810 for encounter 427 (enemy 272).
void sub_2F2090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f2090
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F20C0u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2F20D0u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F20E0u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 272;
    for (;;) {
        // 0x002f211c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f2100
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f2114
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f210c
            charge(ctx, 2);
        }
        // 0x002f2118
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f2124
    charge(ctx, 75);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F213Cu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F2158u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F2168u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F2188u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F21A4u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F21C4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F21D4u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F21F4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F2210u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F2220u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F222Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F2250 sub_2F2250 -- 376 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFormationFar] A formation: the party's cells from 0x69A210 / slots 0x7CC9D8.. (the hero at (150, 500) slot 2);
// every enemy at (0, -500).
void sub_2F2250(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f2250
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -24048);  // &0x69A210
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f2270
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
    // 0x002f2294
    charge(ctx, 12);
    lh(a1, gp, -25368);  // 0x7CC9D8
    lh(a0, gp, -25366);  // 0x7CC9DA
    lh(v1, gp, -25364);  // 0x7CC9DC
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f235c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f22c4
        charge(ctx, 4);
        lhu(v1, s1, bcore::kUnId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002f22f4
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f22d4
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 0x43FA0000;
            sw(v0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, bcore::kUnFormSlot);
        }
        // 0x002f2334
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F2340u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F2350u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f2364
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f23a8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f2374
        charge(ctx, 13);
        sw(zero, sp, 0x50);
        v0 = lui(0xC3FA);
        sw(v0, sp, 0x58);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F238Cu, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F239Cu, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f23b0
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F2450 sub_2F2450 -- 64 bytes; frame 0x10: ra sp+0x0
// [btlBossEvent102] Starts the event task (sub_2E4220) of the scene sub_2F2550 with the done callback sub_2F2840 for
// the event $a0, after copying its +32 to gBtl +2892.
void sub_2F2450(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f2450
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    lw(v1, a0, 32);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    sw(v1, v0, b9::kBoss2892);
    a0 = 0x2F0000;
    a0 = addiu(a0, 9552);  // &sub_2F2550
    a1 = 0x2F0000;
    a1 = addiu(a1, 10304);  // &sub_2F2840
    jal(ctx, 0x2F2478u, gen::fn_sub_2E4220_002e4220);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F2490 sub_2F2490 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlBossEvent103] Starts the event task of the scene sub_2F2890 with the done callback sub_2F2B40.
void sub_2F2490(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f2490
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    a0 = 0x2F0000;
    a0 = addiu(a0, 10384);  // &sub_2F2890
    a1 = 0x2F0000;
    a1 = addiu(a1, 11072);  // &sub_2F2B40
    jal(ctx, 0x2F24ACu, gen::fn_sub_2E4220_002e4220);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F2550 sub_2F2550 -- 752 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlBossEffect102Scene] The scene of effect 102 on the enemy side's last unit ($a0 the action): binds BED 3, queues
// sub_2BD590(unit, 102), sub_2B8D60(3, 4095) and sub_2BC7E0(8) (delay 3), sub_2A3D70 on the hero's action with the
// tables 0x69A250 / 0x69A270 / 0x69A290 / 0x69A2B0, sub_2DD4A0(102), the unit effects 0 / 1 each followed by
// sub_2DD5E0, the motion 69 (sub_2BD850, delay 155, an end condition) and the call packet sub_2F23D0; frees the handle.
void sub_2F2550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f2550
    enter(ctx, 188);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(s3, v0, b9::kBtlEnemyTail);
    a0 = 0;
    jal(ctx, 0x2F257Cu, gen::fn_sub_2B8F90_002b8f90);
    s2 = v0;
    a0 = 3;
    jal(ctx, 0x2F258Cu, gen::fn_sub_2F87E0_002f87e0);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x2F259Cu, gen::fn_sub_2B90D0_002b90d0);
    a0 = s3;
    a1 = 102;
    jal(ctx, 0x2F25ACu, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 3;
    jal(ctx, 0x2F25C4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F25D4u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F25F4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 8;
    jal(ctx, 0x2F2600u, gen::fn_sub_2BC7E0_002bc7e0);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F2620u, gen::fn_sub_27ED20_0027ed20);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, bcore::kBtlPlayerAction);
    a1 = 0x6A0000;
    a1 = addiu(a1, -23984);  // &0x69A250
    a2 = 0x6A0000;
    a2 = addiu(a2, -23952);  // &0x69A270
    a3 = 0x6A0000;
    a3 = addiu(a3, -23920);  // &0x69A290
    t0 = 0x6A0000;
    t0 = addiu(t0, -23888);  // &0x69A2B0
    lwc1(f12, gp, -32032);  // 0x7CAFD0
    jal(ctx, 0x2F2654u, gen::fn_sub_2A3D70_002a3d70);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F2674u, gen::fn_sub_27ED20_0027ed20);
    a0 = 102;
    a1 = 0;
    jal(ctx, 0x2F2684u, gen::fn_sub_2DD4A0_002dd4a0);
    s4 = v0;
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x2F26A0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = s3;
    a2 = s3;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F26BCu, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2F26E8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    jal(ctx, 0x2F26F4u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F2714u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = s3;
    a2 = s3;
    a3 = 1;
    t0 = 512;
    jal(ctx, 0x2F2730u, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2F275Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 1;
    jal(ctx, 0x2F2768u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F2788u, gen::fn_sub_27ED20_0027ed20);
    a0 = s3;
    a1 = 69;
    jal(ctx, 0x2F2798u, gen::fn_sub_2BD850_002bd850);
    s4 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktEndKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktEndId0);
    v1 = 155;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 3;
    jal(ctx, 0x2F27CCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 0x2F0000;
    a0 = addiu(a0, 9168);  // &sub_2F23D0
    a1 = s3;
    jal(ctx, 0x2F27E0u, gen::fn_sub_27F410_0027f410);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s0, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F2808u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    jal(ctx, 0x2F2814u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F2840 sub_2F2840 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlSceneBusy] 1 while the action $a0 owns queued packets, else 0.
void sub_2F2840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f2840
    enter(ctx, 17);  // entry check point + this block's cycles
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
    jal(ctx, 0x2F2868u, gen::fn_sub_27E390_0027e390);
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F2890 sub_2F2890 -- 680 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlBossEffect103Scene] As sub_2F2550 for effect 103 (BED 4), with one of two camera sets (datCalcRand(100) < 50
// takes the second rows of 0x69A2D0 / 0x69A2F0 / 0x69A310 / 0x69A330), motion 71 (delay 40) and the call packet
// sub_2F2410.
void sub_2F2890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f2890
    enter(ctx, 170);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v0, b9::kBtlEnemyTail);
    a0 = 0;
    jal(ctx, 0x2F28BCu, gen::fn_sub_2B8F90_002b8f90);
    s0 = v0;
    a0 = 4;
    jal(ctx, 0x2F28CCu, gen::fn_sub_2F87E0_002f87e0);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x2F28DCu, gen::fn_sub_2B90D0_002b90d0);
    a0 = s1;
    a1 = 103;
    jal(ctx, 0x2F28ECu, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 3;
    jal(ctx, 0x2F2904u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F2914u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F2934u, gen::fn_sub_27ED20_0027ed20);
    a0 = 8;
    jal(ctx, 0x2F2940u, gen::fn_sub_2BC7E0_002bc7e0);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F2960u, gen::fn_sub_27ED20_0027ed20);
    a0 = 100;
    jal(ctx, 0x2F296Cu, gen::fn_datCalcRand_002ffbc0);
    v1 = sltiu(v0, 50);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a0 = sll(v0, 2);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    v0 = 0x6A0000;
    v0 = addiu(v0, -23856);  // &0x69A2D0
    a1 = addu(v0, a0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23824);  // &0x69A2F0
    a2 = addu(v0, a0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23792);  // &0x69A310
    a3 = addu(v0, a0);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23760);  // &0x69A330
    t0 = addu(v0, a0);
    lw(a0, v1, bcore::kBtlPlayerAction);
    lwc1(f12, gp, -32036);  // 0x7CAFCC
    jal(ctx, 0x2F29C0u, gen::fn_sub_2A3D70_002a3d70);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F29E0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 103;
    a1 = 0;
    jal(ctx, 0x2F29F0u, gen::fn_sub_2DD4A0_002dd4a0);
    s3 = v0;
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s3;
    a1 = 1;
    jal(ctx, 0x2F2A0Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = s1;
    a2 = s1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F2A28u, gen::fn_sub_2BAF90_002baf90);
    s4 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 2;
    jal(ctx, 0x2F2A54u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    jal(ctx, 0x2F2A60u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F2A80u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = 71;
    jal(ctx, 0x2F2A90u, gen::fn_sub_2BD850_002bd850);
    s3 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktEndKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktEndId0);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    v1 = 40;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s3;
    a1 = 3;
    jal(ctx, 0x2F2AC4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0x2F0000;
    a0 = addiu(a0, 9232);  // &sub_2F2410
    a1 = s1;
    jal(ctx, 0x2F2AD8u, gen::fn_sub_27F410_0027f410);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F2B00u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2F2B0Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F2B40 sub_2F2B40 -- 68 bytes; frame 0x10: ra sp+0x0
// [btlSceneBusyB] As sub_2F2840: 1 while the action $a0 owns queued packets, else 0.
void sub_2F2B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f2b40
    enter(ctx, 17);  // entry check point + this block's cycles
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
    jal(ctx, 0x2F2B68u, gen::fn_sub_27E390_0027e390);
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F2B90 sub_2F2B90 -- 1524 bytes; frame 0x120: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlNyxTarotChange] The Nyx arcana change scene ($a0 the action): the next arcana's effect from the u16 table
// 0x69A1D2 by gBtl +2888; binds BED 5 and a second handle; sub_2D1D00(action, 2, "NYX_TAROT_CHANGE") (delay 30), the
// shot, sub_2BB2F0 with sub_2835E0(unit, 23) + 6, the motion 23, sub_2B8D60, the effect, the skill camera set,
// sub_2BB6F0 / sub_2BAC00 (delayed by sub_2835E0's value), sub_2DD4A0, the unit effects 0 / 1 with sub_2DD5E0, the four
// closing packets (wait kind 11); then gBtl flag 0x400000 and +24 |= 7; frees both handles.
void sub_2F2B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f2b90
    enter(ctx, 381);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    ld(s0, a0, 0);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, a0, bcore::kActUnit);
    a1 = 23;
    jal(ctx, 0x2F2BD0u, gen::fn_sub_2835E0_002835e0);
    s7 = dsll32(v0, 16);
    s7 = dsra32(s7, 16);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lhu(v0, v0, b9::kBoss2888);
    v1 = sll(v0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, -24110);  // &0x69A1D2
    v0 = addu(v0, v1);
    lhu(s1, v0, 0);
    a0 = 0;
    jal(ctx, 0x2F2C00u, gen::fn_sub_2B8F90_002b8f90);
    s6 = v0;
    a0 = 1;
    jal(ctx, 0x2F2C10u, gen::fn_sub_2B8F90_002b8f90);
    s5 = v0;
    a0 = 5;
    jal(ctx, 0x2F2C20u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s6;
    a1 = v0;
    jal(ctx, 0x2F2C30u, gen::fn_sub_2B90D0_002b90d0);
    a0 = s2;
    a1 = 2;
    a2 = 0x6A0000;
    a2 = addiu(a2, -23728);  // "NYX_TAROT_CHANGE"
    jal(ctx, 0x2F2C48u, gen::fn_sub_2D1D00_002d1d00);
    s4 = v0;
    v1 = 30;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 0;
    jal(ctx, 0x2F2C6Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F2C7Cu, gen::fn_sub_2A3B40_002a3b40);
    s3 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    v1 = 16;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s3;
    a1 = 0;
    jal(ctx, 0x2F2CA8u, gen::fn_sub_27ED20_0027ed20);
    v0 = dsll32(s7, 16);
    v0 = dsra32(v0, 16);
    a2 = addiu(v0, 6);
    a0 = s6;
    lw(a1, s2, bcore::kActUnit);
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F2CCCu, gen::fn_sub_2BB2F0_002bb2f0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 2;
    jal(ctx, 0x2F2CF4u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, s2, bcore::kActUnit);
    a1 = 23;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x2F2D14u, gen::fn_sub_284200_00284200);
    s4 = v0;
    a0 = 4;
    sb(a0, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sh(a0, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x2F2D44u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F2D54u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F2D74u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, s2, bcore::kActUnit);
    a1 = s1;
    jal(ctx, 0x2F2D84u, gen::fn_sub_2BD590_002bd590);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 3;
    jal(ctx, 0x2F2DA8u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = addiu(sp, 0x11C);
    a2 = addiu(sp, 0x118);
    jal(ctx, 0x2F2DBCu, gen::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 0x11C);
    lw(a1, sp, 0x118);
    a2 = 16;
    jal(ctx, 0x2F2DD0u, gen::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F2DF4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F2E00u, gen::fn_sub_29EC00_0029ec00);
    s4 = v0;
    a0 = s1;
    a1 = addiu(sp, 0x11C);
    a2 = addiu(sp, 0x118);
    jal(ctx, 0x2F2E18u, gen::fn_sub_29EC80_0029ec80);
    a0 = s4;
    lw(a1, sp, 0x11C);
    lw(a2, sp, 0x118);
    a3 = 16;
    t0 = 4;
    jal(ctx, 0x2F2E34u, gen::fn_sub_2A0050_002a0050);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F2E58u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F2E64u, gen::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = 16;
    jal(ctx, 0x2F2E74u, gen::fn_sub_2A1280_002a1280);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F2E98u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = s1;
    a2 = 16;
    jal(ctx, 0x2F2EACu, gen::fn_sub_2A1B00_002a1b00);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F2ED0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = addiu(sp, 0x90);
    jal(ctx, 0x2F2EE0u, gen::fn_sub_2BB6F0_002bb6f0);
    a0 = s5;
    a1 = addiu(sp, 0x90);
    a2 = 0;
    jal(ctx, 0x2F2EF4u, gen::fn_sub_2BAC00_002bac00);
    s4 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sh(s7, v0, bcore::kPktStartDelay);
    sd(s0, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x2F2F20u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x2F2F30u, gen::fn_sub_2DD4A0_002dd4a0);
    s1 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x2F2F54u, gen::fn_sub_27ED20_0027ed20);
    lw(a1, s2, bcore::kActUnit);
    a0 = s5;
    a2 = a1;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2F2F70u, gen::fn_sub_2BAF90_002baf90);
    s3 = v0;
    a0 = 4;
    sb(a0, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sb(a0, v0, 16);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId1);
    sd(s0, v0, bcore::kPktOwner);
    a0 = s3;
    a1 = 2;
    jal(ctx, 0x2F2FA4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    jal(ctx, 0x2F2FB0u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s3, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F2FD0u, gen::fn_sub_27ED20_0027ed20);
    lw(a1, s2, bcore::kActUnit);
    a0 = s5;
    a2 = a1;
    a3 = 1;
    t0 = 0;
    jal(ctx, 0x2F2FECu, gen::fn_sub_2BAF90_002baf90);
    s2 = v0;
    a0 = 4;
    sb(a0, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sb(a0, v0, 16);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId1);
    sd(s0, v0, bcore::kPktOwner);
    a0 = s2;
    a1 = 2;
    jal(ctx, 0x2F3020u, gen::fn_sub_27ED20_0027ed20);
    a0 = 1;
    jal(ctx, 0x2F302Cu, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s2, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F304Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    jal(ctx, 0x2F3058u, gen::fn_sub_29FA50_0029fa50);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s2, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F307Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    a1 = 4;
    jal(ctx, 0x2F308Cu, gen::fn_sub_2A1080_002a1080);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s2, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F30B0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    jal(ctx, 0x2F30BCu, gen::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s2, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F30E0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 8;
    jal(ctx, 0x2F30ECu, gen::fn_sub_2A1DB0_002a1db0);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s2, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s0, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F3110u, gen::fn_sub_27ED20_0027ed20);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = 0x400000;
    v0 = v1 | v0;
    sw(v0, a0, bcore::kBtlFlags);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lhu(v0, v1, b9::kBtlFlags24);
    v0 = v0 | 0x7;
    sh(v0, v1, b9::kBtlFlags24);
    a0 = s5;
    jal(ctx, 0x2F3140u, gen::fn_sub_2B9030_002b9030);
    a0 = s6;
    jal(ctx, 0x2F314Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x120);
}

// 0x002F3190 sub_2F3190 -- 396 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlNyxTarotChangeDone] The arcana change's done callback: 1 while packets remain; then resumes the order and turns
// the DatUnit into the next arcana (u16 table 0x69A1D0 by gBtl +2888 into DatUnit +2 / +4, sub_2889C0), full HP and SP,
// every bad status cleared, sub_17B220(id), sub_27CE50, the effects 13..16 cleared, sub_2831C0(unit, 6), the phase
// counter + 1, sub_1FDD40; 0.
void sub_2F3190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f3190
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x2F31C8u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f32fc
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f31d8
        charge(ctx, 73);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, bcore::kBtlFlags);
        lw(a0, s1, bcore::kActUnit);
        lw(s0, a0, bcore::kUnDat);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lhu(v0, v0, b9::kBoss2888);
        v1 = sll(v0, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, -24112);  // &0x69A1D0
        v0 = addu(v0, v1);
        lhu(s2, v0, 0);
        a1 = s2;
        jal(ctx, 0x2F3218u, gen::fn_sub_2889C0_002889c0);
        sh(s2, s0, 2);
        sh(s2, s0, 4);
        a0 = s0;
        jal(ctx, 0x2F322Cu, gen::fn_datCalcGetMaxHp_002ffdf0);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x2F323Cu, gen::fn_datCalcSetHp_002ffd90);
        a0 = s0;
        jal(ctx, 0x2F3248u, gen::fn_datCalcGetMaxSp_00300100);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x2F3258u, gen::fn_datCalcSetSp_002ffdc0);
        a0 = s0;
        v0 = 0xFF0000;
        a1 = v0 | 0xFFFF;  // &0xFFFFFF
        jal(ctx, 0x2F326Cu, gen::fn_datCalcClearBadStatus_00300560);
        a0 = s2;
        jal(ctx, 0x2F3278u, gen::fn_sub_17B220_0017b220);
        jal(ctx, 0x2F3280u, gen::fn_sub_27CE50_0027ce50);
        a0 = s0;
        a1 = 13;
        jal(ctx, 0x2F3290u, gen::fn_datCalcClearEffect_00301540);
        a0 = s0;
        a1 = 14;
        jal(ctx, 0x2F32A0u, gen::fn_datCalcClearEffect_00301540);
        a0 = s0;
        a1 = 15;
        jal(ctx, 0x2F32B0u, gen::fn_datCalcClearEffect_00301540);
        a0 = s0;
        a1 = 16;
        jal(ctx, 0x2F32C0u, gen::fn_datCalcClearEffect_00301540);
        lw(a0, s1, bcore::kActUnit);
        a1 = 6;
        jal(ctx, 0x2F32D0u, gen::fn_sub_2831C0_002831c0);
        lw(v1, gp, bcore::kGpBtl);  // gBtl
        lhu(v0, v1, b9::kBoss2888);
        v0 = addiu(v0, 1);
        sh(v0, v1, b9::kBoss2888);
        jal(ctx, 0x2F32E8u, gen::fn_sub_1FDD40_001fdd40);
        v0 = 0;
    }
    // 0x002f3300 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F3320 sub_2F3320 -- 500 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlBossExitScene] An enemy's exit scene ($a0 the action): clears gBtl flag 0x2000000, pauses the order, binds BED 6,
// the ADX stream request sub_2DD690(3, "E1AC_99.ADX"), the motion 18 (delay 2), sub_2B8D60(1, 4095), the transform, the
// shot and the unit effect; frees the handle.
void sub_2F3320(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f3320
    enter(ctx, 125);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a1, bcore::kBtlFlags);
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a1, bcore::kBtlFlags);
    lw(s2, a0, bcore::kActUnit);
    a0 = 0;
    jal(ctx, 0x2F3370u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 6;
    jal(ctx, 0x2F3380u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F3390u, gen::fn_sub_2B90D0_002b90d0);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -23704);  // "E1AC_99.ADX"
    jal(ctx, 0x2F33A4u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2F33B4u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F33D4u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 2;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F33F8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 1;
    a1 = 4095;
    jal(ctx, 0x2F3408u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3430u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F344Cu, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3474u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F3484u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F34ACu, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F34C8u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 2;
    jal(ctx, 0x2F34E0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F34ECu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002F3520 sub_2F3520 -- 328 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlBossExitDone] The exit's done callback: 1 while the action is not the current actor and its unit has flag 0x10
// (the actor's flag is cleared), or packets remain; then resumes the order, kills and removes the action, sets gBtl
// flag 0x2000000 and queues the three closing packets; 0.
void sub_2F3520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f3520
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2F3530u, gen::fn_sub_29AD20_0029ad20);
    if (s0 == v0) {
        // 0x002f3560
        charge(ctx, 5);
        lw(a0, s0, bcore::kActUnit);
        lw(v1, a0, bcore::kUnFlags);
        v0 = si(-17);
        v0 = v1 & v0;
        sw(v0, a0, bcore::kUnFlags);
    L_002f3574:
        charge(ctx, 12);
        ld(a0, s0, 0);
        v0 = 0x3FFF0000;
        v0 = v0 | 0xFFFF;
        v1 = dsll32(v0, 0);
        v0 = 0xFFFF;
        v0 = dsll(v0, 16);
        v0 = v0 | 0xFFFF;
        a1 = v0 | v1;
        jal(ctx, 0x2F3594u, gen::fn_sub_27E390_0027e390);
        if (v0 != 0) {
            // 0x002f3650
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x002f35a4
            charge(ctx, 43);
            lw(a0, gp, bcore::kGpBtl);  // gBtl
            lw(v1, a0, bcore::kBtlFlags);
            v0 = lui(0xFFF7);
            v0 = v0 | 0xFFFF;
            v0 = v1 & v0;
            sw(v0, a0, bcore::kBtlFlags);
            a0 = s0;
            a1 = 0;
            jal(ctx, 0x2F35C4u, gen::fn_sub_2D7890_002d7890);
            a0 = s0;
            jal(ctx, 0x2F35D0u, gen::fn_sub_29A320_0029a320);
            lw(a0, gp, bcore::kGpBtl);  // gBtl
            lw(v1, a0, bcore::kBtlFlags);
            v0 = 0x2000000;
            v0 = v1 | v0;
            sw(v0, a0, bcore::kBtlFlags);
            a0 = 16;
            jal(ctx, 0x2F35F0u, gen::fn_sub_29FA50_0029fa50);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2F3600u, gen::fn_sub_27ED20_0027ed20);
            a0 = 16;
            a1 = 4;
            jal(ctx, 0x2F3610u, gen::fn_sub_2A1080_002a1080);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2F3620u, gen::fn_sub_27ED20_0027ed20);
            a0 = 16;
            jal(ctx, 0x2F362Cu, gen::fn_sub_2A16C0_002a16c0);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x2F363Cu, gen::fn_sub_27ED20_0027ed20);
            v0 = 0;
        }
    } else {
        // 0x002f3540
        charge(ctx, 5);
        lw(v0, s0, bcore::kActUnit);
        lw(v0, v0, bcore::kUnFlags);
        v0 = v0 & 0x10;
        if (v0 == 0) {
            goto L_002f3574;
        }
        // 0x002f3554
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002f3654 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F3670 sub_2F3670 -- 228 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btl429UnitInit] Encounter 429's unit init ($a0 the action, with a unit): the hero (side 0, id 1) gets sub_1757F0,
// sub_174E20(191), sub_175130(191), sub_288F80(unit, 191) and every bad status cleared; enemy 274 gets unit flags 0x100
// | 0x40 | 0x400.
void sub_2F3670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f3670
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(v1, a0, bcore::kActFlags2);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002f368c
        charge(ctx, 4);
        lw(s0, a0, bcore::kActUnit);
        lbu(a0, s0, bcore::kUnSide);
        if (a0 != 0) {
            // 0x002f3700
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x002f370c
                charge(ctx, 4);
                lhu(a0, s0, bcore::kUnId);
                v1 = 274;
                if (a0 == v1) {
                    // 0x002f3724
                    charge(ctx, 7);
                    lw(v1, s0, bcore::kUnFlags);
                    v1 = v1 | 0x100;
                    sw(v1, s0, bcore::kUnFlags);
                    v1 = v1 | 0x40;
                    sw(v1, s0, bcore::kUnFlags);
                    v1 = v1 | 0x400;
                    sw(v1, s0, bcore::kUnFlags);
                } else {
                    // 0x002f371c
                    charge(ctx, 2);
                }
            }
        } else {
            // 0x002f369c
            charge(ctx, 4);
            lhu(a0, s0, bcore::kUnId);
            v1 = 1;
            if (a0 == v1) {
                // 0x002f36b4
                charge(ctx, 19);
                jal(ctx, 0x2F36B4u, gen::fn_sub_1757F0_001757f0);
                a0 = 191;
                jal(ctx, 0x2F36C0u, gen::fn_sub_174E20_00174e20);
                a0 = 191;
                jal(ctx, 0x2F36CCu, gen::fn_sub_175130_00175130);
                a0 = s0;
                a1 = 191;
                jal(ctx, 0x2F36DCu, gen::fn_sub_288F80_00288f80);
                lw(a0, s0, bcore::kUnDat);
                v0 = 0xFF0000;
                a1 = v0 | 0xFFFF;  // &0xFFFFFF
                jal(ctx, 0x2F36F0u, gen::fn_datCalcClearBadStatus_00300560);
            } else {
                // 0x002f36ac
                charge(ctx, 2);
            }
        }
    }
    // 0x002f3740 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F3760 sub_2F3760 -- 224 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [btlFormationNear] A formation: the hero at (0, 500) slot 0, the rest of the party at (0, 0); every enemy at (0,
// -500).
void sub_2F3760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f3760
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, sp, 0x24);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f37d8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f3780
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002f37a8
            charge(ctx, 2);
            sw(zero, sp, 0x20);
            sw(zero, sp, 0x28);
        } else {
            // 0x002f3790
            charge(ctx, 6);
            sw(zero, sp, 0x20);
            v0 = 0x43FA0000;
            sw(v0, sp, 0x28);
            sb(zero, s0, bcore::kUnFormSlot);
        }
        // 0x002f37b0
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2F37BCu, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2F37CCu, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f37e0
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f3824
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f37f0
        charge(ctx, 13);
        sw(zero, sp, 0x20);
        v0 = lui(0xC3FA);
        sw(v0, sp, 0x28);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2F3808u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2F3818u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f382c
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002F3840 sub_2F3840 -- 368 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl429DeathScene] Encounter 429's death scene: sub_2DCE90, clears gBtl flag 0x2000000, binds BED 3, sub_2B8D60 and
// the shot (delay 3), the unit effect from the hero's unit to enemy 274, sub_2BC890(0x7CC970, 12) (delay 229); frees
// the handle.
void sub_2F3840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f3840
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2F3854u, gen::fn_sub_2DCE90_002dce90);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F3878u, gen::fn_sub_2B8F90_002b8f90);
    s0 = v0;
    a0 = 3;
    jal(ctx, 0x2F3888u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x2F3898u, gen::fn_sub_2B90D0_002b90d0);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(v0, v1, bcore::kBtlPlayerAction);
    lw(s2, v0, bcore::kActUnit);
    s1 = 0;
    lw(a0, v1, b9::kBtlEnemyTail);
    v0 = 274;
    for (;;) {
        // 0x002f38dc
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f38c0
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f38d4
            charge(ctx, 1);
            s1 = a0;
        } else {
            // 0x002f38cc
            charge(ctx, 2);
        }
        // 0x002f38d8
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f38e4
    charge(ctx, 51);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F38ECu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a1 = 1;
    jal(ctx, 0x2F3904u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F3914u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a1 = 0;
    jal(ctx, 0x2F392Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = s2;
    a2 = s1;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F3948u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F3958u, gen::fn_sub_27ED20_0027ed20);
    a0 = addiu(gp, -25472);  // &0x7CC970
    a1 = 12;
    jal(ctx, 0x2F3968u, gen::fn_sub_2BC890_002bc890);
    a0 = v0;
    v1 = 229;
    sh(v1, v0, bcore::kPktStartDelay);
    a1 = 1;
    jal(ctx, 0x2F3980u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2F398Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F39B0 sub_2F39B0 -- 204 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btl429ActionHook] Encounter 429's action hook ($a0 the event): with a current actor (sub_29AD20), skill 343 starts
// the event sub_2F4410 / sub_2F4480; otherwise an actor that is enemy 274 starts its phase scene sub_2F3A80 /
// sub_2F43A0, except the first time (gBtl +2888 = 0 -> 1).
void sub_2F39B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f39b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x2F39C0u, gen::fn_sub_29AD20_0029ad20);
    if (v0 != 0) {
        // 0x002f39d0
        charge(ctx, 4);
        lhu(a0, v0, b9::kActSkill);
        v1 = 343;
        if (a0 != v1) {
            // 0x002f3a04
            charge(ctx, 5);
            lw(a1, v0, bcore::kActUnit);
            lbu(a0, a1, bcore::kUnSide);
            v1 = 1;
            if (a0 == v1) {
                // 0x002f3a18
                charge(ctx, 4);
                lhu(a0, a1, bcore::kUnId);
                v1 = 274;
                if (a0 == v1) {
                    // 0x002f3a28
                    charge(ctx, 5);
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    a0 = addiu(v1, 2888);
                    lhu(v1, v1, b9::kBoss2888);
                    if (v1 != 0) {
                        // 0x002f3a4c
                        charge(ctx, 7);
                        a0 = 0x2F0000;
                        a0 = addiu(a0, 14976);  // &sub_2F3A80
                        a1 = 0x2F0000;
                        a1 = addiu(a1, 17312);  // &sub_2F43A0
                        a2 = s0;
                        jal(ctx, 0x2F3A60u, gen::fn_sub_2E4220_002e4220);
                    } else {
                        // 0x002f3a3c
                        charge(ctx, 4);
                        v1 = addiu(v1, 1);
                        sh(v1, a0, 0);
                    }
                }
            }
        } else {
            // 0x002f39e0
            charge(ctx, 9);
            a0 = 0x2F0000;
            a0 = addiu(a0, 17424);  // &sub_2F4410
            a1 = 0x2F0000;
            a1 = addiu(a1, 17536);  // &sub_2F4480
            a2 = s0;
            jal(ctx, 0x2F39F4u, gen::fn_sub_2E4220_002e4220);
        }
    }
    // 0x002f3a68 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F3A80 sub_2F3A80 -- 2328 bytes; frame 0x1C0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl429PhaseScene] Enemy 274's phase attack ($a0 the action): by the stage gBtl +2888 (0 / 1 / 2) the skill 108 / 97
// / 98, the motion 284 / 282 / 283, three sub_2DB740(action, 31, id, 0, 1) packets (-1 none; stage 0's third is
// sub_2E30A0(gBtl +2818, 2, 902, 1)) and the camera row of 0x69A3A0 / 0x69A3D0 / 0x69A400 / 0x69A430; the stage + 1;
// the action's command becomes kind 2 with that skill (sub_2C3770, sub_2D6620); binds BED 1; sub_2B8D60, sub_2A3D70,
// those packets chained, the skill camera set, sub_2BB6F0 / sub_2BAC00, sub_2DD4A0, the unit effect; for each target
// action (+56, count +106): sub_2BD480, its unit effect and sub_2DD5E0, then per row (+200 rows of 28 bytes at +224)
// the motion of the row's +24 byte, on the first row sub_2BD850, then sub_2BDBD0 and sub_2D7E20; skill 97 adds the
// motion 10 (delay 161) and sub_2D7E20 on a sub_2D5DC0 record with 0x100000; the four closing packets; frees the
// handle.
void sub_2F3A80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x002f3a80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
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
    s2 = a0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    a0 = addiu(v0, 2888);
    lhu(v1, v0, b9::kBoss2888);
    s1 = 2;
    if (v1 == s1) {
        // 0x002f3b18
        charge(ctx, 15);
        s0 = 98;
        s5 = 283;
        v0 = 463;
        sw(v0, sp, 0x1A8);
        v0 = 471;
        sw(v0, sp, 0x1AC);
        v0 = 466;
        sw(v0, sp, 0x1B0);
        v0 = si(-1);
        sw(v0, sp, 0x198);
        sw(v0, sp, 0x19C);
        sw(v0, sp, 0x1A0);
        s1 = 1;
    } else {
        // 0x002f3ac8
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x002f3adc
            charge(ctx, 15);
            s0 = 97;
            s5 = 282;
            v0 = 468;
            sw(v0, sp, 0x1A8);
            v0 = 467;
            sw(v0, sp, 0x1AC);
            v0 = 465;
            sw(v0, sp, 0x1B0);
            v0 = si(-1);
            sw(v0, sp, 0x198);
            sw(v0, sp, 0x19C);
            sw(v0, sp, 0x1A0);
            s1 = 0;
        } else {
            // 0x002f3ad4
            charge(ctx, 2);
            // 0x002f3b54
            charge(ctx, 12);
            s0 = 108;
            s5 = 284;
            v0 = 470;
            sw(v0, sp, 0x1A8);
            v0 = 464;
            sw(v0, sp, 0x1AC);
            v0 = si(-1);
            sw(v0, sp, 0x1B0);
            sw(v0, sp, 0x198);
            sw(v0, sp, 0x19C);
            v0 = 902;
            sw(v0, sp, 0x1A0);
        }
    }
    // 0x002f3b84
    charge(ctx, 70);
    lhu(v0, a0, 0);
    v0 = addiu(v0, 1);
    sh(v0, a0, 0);
    ld(s3, s2, 0);
    v0 = 2;
    sh(v0, s2, b9::kActCmdKind);
    sh(s0, s2, b9::kActSkill);
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x2F3BA8u, gen::fn_sub_2C3770_002c3770);
    a0 = s2;
    jal(ctx, 0x2F3BB4u, gen::fn_sub_2D6620_002d6620);
    a0 = 1;
    jal(ctx, 0x2F3BC0u, gen::fn_sub_2B8F90_002b8f90);
    s6 = v0;
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F3BD4u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    sh(zero, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F3BF0u, gen::fn_sub_27ED20_0027ed20);
    v0 = sll(s1, 1);
    v0 = addu(v0, s1);
    v1 = sll(v0, 2);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    v0 = 0x6A0000;
    v0 = addiu(v0, -23648);  // &0x69A3A0
    a1 = addu(v0, v1);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23600);  // &0x69A3D0
    a2 = addu(v0, v1);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23552);  // &0x69A400
    a3 = addu(v0, v1);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23504);  // &0x69A430
    t0 = addu(v0, v1);
    v1 = sll(s1, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, -23464);  // &0x69A458
    v1 = addu(v0, v1);
    v0 = 0x41F00000;
    mtc1(v0, f1);
    lwc1(f0, v1, 0);
    div_s(f12, f0, f1);
    lw(a0, a0, bcore::kBtlPlayerAction);
    jal(ctx, 0x2F3C64u, gen::fn_sub_2A3D70_002a3d70);
    s4 = v0;
    sh(zero, v0, bcore::kPktStartDelay);
    ld(v1, s2, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s4;
    a1 = 0;
    jal(ctx, 0x2F3C84u, gen::fn_sub_27ED20_0027ed20);
    s7 = 0;
    s1 = 0;
    for (;;) {
        // 0x002f3d3c
        charge(ctx, 4);
        v0 = s1 & 0xFFFF;
        v0 = slti(v0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f3c9c
        charge(ctx, 8);
        v0 = s1 & 0xFFFF;
        v0 = sll(v0, 2);
        a0 = addu(v0, sp);
        v0 = addiu(a0, 424);
        lw(a2, v0, 0);
        v1 = si(-1);
        if (a2 != v1) {
            // 0x002f3cbc
            charge(ctx, 9);
            a0 = s2;
            a1 = 31;
            a3 = 0;
            t0 = 1;
            jal(ctx, 0x2F3CCCu, gen::fn_sub_2DB740_002db740);
            s4 = v0;
            goto L_002f3d0c;
        }
        // 0x002f3ce0
        charge(ctx, 3);
        lw(v0, a0, 408);
        if (v0 != v1) {
            // 0x002f3cec
            charge(ctx, 8);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lhu(a0, v0, b9::kBtl2818);
            a1 = 2;
            a2 = 902;
            a3 = 1;
            jal(ctx, 0x2F3D00u, gen::fn_sub_2E30A0_002e30a0);
            s4 = v0;
        L_002f3d0c:
            charge(ctx, 10);
            v0 = 4;
            sb(v0, s4, b9::kPktWaitKind0);
            sd(s7, s4, 8);
            sh(zero, s4, bcore::kPktStartDelay);
            sd(s3, s4, bcore::kPktOwner);
            a0 = s4;
            a1 = 0;
            jal(ctx, 0x2F3D28u, gen::fn_sub_27ED20_0027ed20);
            ld(s7, s4, bcore::kPktId);
        }
        // 0x002f3d34
        charge(ctx, 2);
        v0 = addiu(s1, 1);
        s1 = v0 & 0xFFFF;
    }
    // 0x002f3d4c
    charge(ctx, 149);
    a0 = s0;
    a1 = addiu(sp, 0x1BC);
    a2 = addiu(sp, 0x1B8);
    jal(ctx, 0x2F3D58u, gen::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 0x1BC);
    lw(a1, sp, 0x1B8);
    a2 = 16;
    jal(ctx, 0x2F3D6Cu, gen::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3D90u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2F3D9Cu, gen::fn_sub_29EC00_0029ec00);
    s1 = v0;
    a0 = s0;
    a1 = addiu(sp, 0x1BC);
    a2 = addiu(sp, 0x1B8);
    jal(ctx, 0x2F3DB4u, gen::fn_sub_29EC80_0029ec80);
    a0 = s1;
    lw(a1, sp, 0x1BC);
    lw(a2, sp, 0x1B8);
    a3 = 16;
    t0 = 4;
    jal(ctx, 0x2F3DD0u, gen::fn_sub_2A0050_002a0050);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3DF4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    jal(ctx, 0x2F3E00u, gen::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = 16;
    jal(ctx, 0x2F3E10u, gen::fn_sub_2A1280_002a1280);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3E34u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = s0;
    a2 = 16;
    jal(ctx, 0x2F3E48u, gen::fn_sub_2A1B00_002a1b00);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3E6Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = addiu(sp, 0xF0);
    jal(ctx, 0x2F3E7Cu, gen::fn_sub_2BB6F0_002bb6f0);
    a0 = s6;
    a1 = addiu(sp, 0xF0);
    a2 = 0;
    jal(ctx, 0x2F3E90u, gen::fn_sub_2BAC00_002bac00);
    fp = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sh(zero, v0, bcore::kPktStartDelay);
    sd(s3, v0, bcore::kPktOwner);
    a0 = fp;
    a1 = 1;
    jal(ctx, 0x2F3EBCu, gen::fn_sub_27ED20_0027ed20);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x2F3ECCu, gen::fn_sub_2DD4A0_002dd4a0);
    sw(v0, sp, 0xEC);
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s4, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2F3EF4u, gen::fn_sub_27ED20_0027ed20);
    lw(a1, s2, bcore::kActUnit);
    a0 = s6;
    a2 = a1;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2F3F10u, gen::fn_sub_2BAF90_002baf90);
    s1 = v0;
    a0 = 4;
    sb(a0, v0, b9::kPktWaitKind0);
    ld(v1, fp, 0x58);
    sd(v1, v0, 8);
    sb(a0, v0, 16);
    lw(v1, sp, 0xEC);
    ld(v1, v1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId1);
    sd(s3, v0, bcore::kPktOwner);
    a0 = s1;
    a1 = 2;
    jal(ctx, 0x2F3F48u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    jal(ctx, 0x2F3F54u, gen::fn_sub_2DD5E0_002dd5e0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F3F78u, gen::fn_sub_27ED20_0027ed20);
    s4 = 0;
    v0 = dsll32(s5, 16);
    v0 = dsra32(v0, 16);
    sw(v0, sp, 0xD0);
    v0 = s0 & 0xFFFF;
    sq(v0, sp, 0xB0);
    for (;;) {
        // 0x002f4280
        charge(ctx, 5);
        v1 = s4 & 0xFFFF;
        lhu(v0, s2, b9::kActTargetCount);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f3fa0
        charge(ctx, 48);
        v0 = s4 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(s2, v0);
        lw(s5, v0, 56);
        lw(a0, s5, bcore::kActUnit);
        jal(ctx, 0x2F3FB4u, gen::fn_sub_2BD480_002bd480);
        a0 = v0;
        sd(s3, v0, bcore::kPktOwner);
        a1 = 1;
        jal(ctx, 0x2F3FC8u, gen::fn_sub_27ED20_0027ed20);
        lw(a1, s5, bcore::kActUnit);
        a0 = s6;
        a2 = a1;
        a3 = 1;
        t0 = 0;
        jal(ctx, 0x2F3FE4u, gen::fn_sub_2BAF90_002baf90);
        s1 = v0;
        a0 = 4;
        sb(a0, v0, b9::kPktWaitKind0);
        ld(v1, fp, 0x58);
        sd(v1, v0, 8);
        sb(a0, v0, 16);
        lw(v1, sp, 0xEC);
        ld(v1, v1, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId1);
        sd(s3, v0, bcore::kPktOwner);
        a0 = s1;
        a1 = 2;
        jal(ctx, 0x2F401Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 1;
        jal(ctx, 0x2F4028u, gen::fn_sub_2DD5E0_002dd5e0);
        a0 = v0;
        v1 = 5;
        sb(v1, v0, b9::kPktWaitKind0);
        ld(v1, s1, bcore::kPktId);
        sd(v1, v0, b9::kPktWaitId0);
        sd(s3, v0, bcore::kPktOwner);
        a1 = 1;
        jal(ctx, 0x2F404Cu, gen::fn_sub_27ED20_0027ed20);
        s0 = 0;
        for (;;) {
            // 0x002f41ac
            charge(ctx, 6);
            v0 = s0 & 0xFFFF;
            sq(v0, sp, 0xA0);
            lbu(v1, s5, 200);
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002f4060
            charge(ctx, 26);
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lb(a1, v0, 248);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s5, bcore::kActUnit);
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x2F408Cu, gen::fn_sub_284200_00284200);
            s7 = v0;
            v1 = 11;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s1, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            sd(s3, v0, bcore::kPktOwner);
            a0 = s7;
            a1 = 1;
            jal(ctx, 0x2F40B4u, gen::fn_sub_27ED20_0027ed20);
            lq(v0, sp, 0xA0);
            if (v0 == 0) {
                // 0x002f40c8
                charge(ctx, 13);
                lw(a0, s5, bcore::kActUnit);
                lw(a1, sp, 0xD0);
                jal(ctx, 0x2F40D0u, gen::fn_sub_2BD850_002bd850);
                a0 = v0;
                v1 = 11;
                sb(v1, v0, b9::kPktWaitKind0);
                ld(v1, s1, bcore::kPktId);
                sd(v1, v0, b9::kPktWaitId0);
                sd(s3, v0, bcore::kPktOwner);
                a1 = 3;
                jal(ctx, 0x2F40F4u, gen::fn_sub_27ED20_0027ed20);
            }
            // 0x002f40fc
            charge(ctx, 44);
            v1 = s0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            v0 = addiu(v0, 224);
            sw(v0, sp, 0xC0);
            lhu(a2, s2, b9::kActSkill);
            lbu(t2, s5, 200);
            lw(a0, s2, bcore::kActUnit);
            lw(a1, s5, bcore::kActUnit);
            lhu(a3, s5, 204);
            lhu(t0, s5, 206);
            t1 = s0;
            t3 = v0;
            jal(ctx, 0x2F4138u, gen::fn_sub_2BDBD0_002bdbd0);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s7, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            sd(s3, v0, bcore::kPktOwner);
            a1 = 3;
            jal(ctx, 0x2F415Cu, gen::fn_sub_27ED20_0027ed20);
            a0 = s2;
            a1 = s5;
            lw(a2, sp, 0xC0);
            lhu(a3, s5, 204);
            lhu(t0, s5, 206);
            jal(ctx, 0x2F4178u, gen::fn_sub_2D7E20_002d7e20);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s7, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            sd(s3, v0, bcore::kPktOwner);
            a1 = 1;
            jal(ctx, 0x2F419Cu, gen::fn_sub_27ED20_0027ed20);
            v0 = addiu(s0, 1);
            s0 = v0 & 0xFFFF;
        }
        // 0x002f41c4
        charge(ctx, 4);
        v1 = 97;
        lq(v0, sp, 0xB0);
        if (v0 == v1) {
            // 0x002f41d4
            charge(ctx, 41);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s5, bcore::kActUnit);
            a1 = 10;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x2F41ECu, gen::fn_sub_284200_00284200);
            s0 = v0;
            v1 = 5;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s1, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            v1 = 161;
            sh(v1, v0, bcore::kPktStartDelay);
            sd(s3, v0, bcore::kPktOwner);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x2F421Cu, gen::fn_sub_27ED20_0027ed20);
            a0 = addiu(sp, 0x170);
            jal(ctx, 0x2F4228u, gen::fn_sub_2D5DC0_002d5dc0);
            v0 = 0x100000;
            sw(v0, sp, 0x17C);
            a0 = s2;
            a1 = s5;
            a2 = addiu(sp, 0x170);
            a3 = 1;
            t0 = a3;
            jal(ctx, 0x2F424Cu, gen::fn_sub_2D7E20_002d7e20);
            a0 = v0;
            v1 = 4;
            sb(v1, v0, b9::kPktWaitKind0);
            ld(v1, s0, bcore::kPktId);
            sd(v1, v0, b9::kPktWaitId0);
            sd(s3, v0, bcore::kPktOwner);
            a1 = 1;
            jal(ctx, 0x2F4270u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x002f4278
        charge(ctx, 2);
        v0 = addiu(s4, 1);
        s4 = v0 & 0xFFFF;
    }
    // 0x002f4294
    charge(ctx, 65);
    a0 = 16;
    jal(ctx, 0x2F4298u, gen::fn_sub_29FA50_0029fa50);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F42BCu, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    a1 = 4;
    jal(ctx, 0x2F42CCu, gen::fn_sub_2A1080_002a1080);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F42F0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 16;
    jal(ctx, 0x2F42FCu, gen::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F4320u, gen::fn_sub_27ED20_0027ed20);
    a0 = 8;
    jal(ctx, 0x2F432Cu, gen::fn_sub_2A1DB0_002a1db0);
    a0 = v0;
    v1 = 11;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s1, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    sd(s3, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F4350u, gen::fn_sub_27ED20_0027ed20);
    a0 = s6;
    jal(ctx, 0x2F435Cu, gen::fn_sub_2B9030_002b9030);
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
    sp = addiu(sp, 0x1C0);
}

// 0x002F43A0 sub_2F43A0 -- 112 bytes; frame 0x10: ra sp+0x0
// [btlPhaseDone] 1 while the action owns queued packets; then resumes the turn order (gBtl flag 0x80000 cleared); 0.
void sub_2F43A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f43a0
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
    jal(ctx, 0x2F43C8u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f43fc
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f43d8
        charge(ctx, 9);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, bcore::kBtlFlags);
        v0 = 0;
    }
    // 0x002f4400 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F4410 sub_2F4410 -- 100 bytes; frame 0x10: ra sp+0x0
// [btlSkill343Kill] Finds enemy 274 among the enemies (or 0) and kills its action (sub_29A1D0, sub_2D7890(a, 0)).
void sub_2F4410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f4410
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 274;
    for (;;) {
        // 0x002f443c
        charge(ctx, 4);
        if (a0 != 0) {
            backedge(ctx);
            // 0x002f442c
            charge(ctx, 3);
            lhu(v1, a0, bcore::kUnId);
            if (v1 != v0) {
                // 0x002f4438
                charge(ctx, 1);
                lw(a0, a0, bcore::kUnPrev);
                continue;
            }
        }
        break;
    }
    // 0x002f444c
    charge(ctx, 10);
    jal(ctx, 0x2F444Cu, gen::fn_sub_29A1D0_0029a1d0);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2F445Cu, gen::fn_sub_2D7890_002d7890);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F4490 sub_2F4490 -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btl430UnitInit] Encounter 430's unit init: enemy 294 gets action +26 bit 0x10, unit flags 0x100 | 0x40 | 0x80,
// sub_29A2C0, and sub_288F80(unit, 7).
void sub_2F4490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f4490
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(a2, a0, bcore::kActFlags2);
    v1 = a2 & 0x1;
    if (v1 != 0) {
        // 0x002f44ac
        charge(ctx, 5);
        lw(s0, a0, bcore::kActUnit);
        lbu(a1, s0, bcore::kUnSide);
        v1 = 1;
        if (a1 == v1) {
            // 0x002f44c0
            charge(ctx, 4);
            lhu(a1, s0, bcore::kUnId);
            v1 = 294;
            if (a1 == v1) {
                // 0x002f44d8
                charge(ctx, 11);
                v0 = a2 | 0x10;
                sh(v0, a0, bcore::kActFlags2);
                lw(v0, s0, bcore::kUnFlags);
                v0 = v0 | 0x100;
                sw(v0, s0, bcore::kUnFlags);
                v0 = v0 | 0x40;
                sw(v0, s0, bcore::kUnFlags);
                v0 = v0 | 0x80;
                sw(v0, s0, bcore::kUnFlags);
                jal(ctx, 0x2F44FCu, gen::fn_sub_29A2C0_0029a2c0);
            } else {
                // 0x002f44d0
                charge(ctx, 2);
            }
            // 0x002f4504
            charge(ctx, 4);
            lhu(a0, s0, bcore::kUnId);
            v1 = 294;
            if (a0 == v1) {
                // 0x002f451c
                charge(ctx, 4);
                a0 = s0;
                a1 = 7;
                jal(ctx, 0x2F4524u, gen::fn_sub_288F80_00288f80);
            } else {
                // 0x002f4514
                charge(ctx, 2);
            }
        }
    }
    // 0x002f452c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F4540 sub_2F4540 -- 396 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl430Formation] As sub_2F1680 for encounter 430: table 0x69A470, slots 0x7CC9E0.., enemy 294.
void sub_2F4540(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f4540
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -23440);  // &0x69A470
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f4560
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
    // 0x002f4584
    charge(ctx, 12);
    lh(a1, gp, -25360);  // 0x7CC9E0
    lh(a0, gp, -25358);  // 0x7CC9E2
    lh(v1, gp, -25356);  // 0x7CC9E4
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f4648
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f45b4
        charge(ctx, 4);
        lhu(v0, s1, bcore::kUnId);
        v1 = 1;
        if (v0 != v1) {
            // 0x002f45e0
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f45c4
            charge(ctx, 7);
            v0 = lui(0xC302);
            sw(v0, sp, 0x50);
            v0 = 0x43480000;
            sw(v0, sp, 0x58);
            sb(v1, s1, bcore::kUnFormSlot);
        }
        // 0x002f4620
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F462Cu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F463Cu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f4650
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f46ac
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4660
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 294;
        if (v1 == v0) {
            // 0x002f4678
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002f4670
            charge(ctx, 2);
        }
        // 0x002f4684
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F4690u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F46A0u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f46b4
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F46D0 sub_2F46D0 -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl430DeathScene] As sub_2F1810 for encounter 430 (enemy 294).
void sub_2F46D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f46d0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F4700u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2F4710u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F4720u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 294;
    for (;;) {
        // 0x002f475c
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4740
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f4754
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f474c
            charge(ctx, 2);
        }
        // 0x002f4758
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f4764
    charge(ctx, 75);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F477Cu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F4798u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F47A8u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F47C8u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F47E4u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F4804u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F4814u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F4834u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F4850u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F4860u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F486Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F4890 sub_2F4890 -- 180 bytes; frame 0x10: ra sp+0x0
// [btl431UnitInit] Encounter 431's unit init: enemy 233 gets action +26 bit 0x10, unit flags 0x100 | 0x40 | 0x80 and
// sub_288F80(unit, 211); a non-enemy's action gets +24 bit 0x40.
void sub_2F4890(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f4890
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(a2, a0, bcore::kActFlags2);
    v1 = a2 & 0x1;
    if (v1 != 0) {
        // 0x002f48a8
        charge(ctx, 5);
        lw(a3, a0, bcore::kActUnit);
        lbu(a1, a3, bcore::kUnSide);
        v1 = 1;
        if (a1 == v1) {
            // 0x002f48d0
            charge(ctx, 4);
            lhu(a1, a3, bcore::kUnId);
            v1 = 233;
            if (a1 == v1) {
                // 0x002f48e8
                charge(ctx, 9);
                v1 = a2 | 0x10;
                sh(v1, a0, bcore::kActFlags2);
                lw(v1, a3, bcore::kUnFlags);
                v1 = v1 | 0x100;
                sw(v1, a3, bcore::kUnFlags);
                v1 = v1 | 0x40;
                sw(v1, a3, bcore::kUnFlags);
                v1 = v1 | 0x80;
                sw(v1, a3, bcore::kUnFlags);
            } else {
                // 0x002f48e0
                charge(ctx, 2);
            }
            // 0x002f490c
            charge(ctx, 4);
            lhu(a0, a3, bcore::kUnId);
            v1 = 233;
            if (a0 == v1) {
                // 0x002f4924
                charge(ctx, 4);
                a0 = a3;
                a1 = 211;
                jal(ctx, 0x2F492Cu, gen::fn_sub_288F80_00288f80);
            } else {
                // 0x002f491c
                charge(ctx, 2);
            }
        } else {
            // 0x002f48bc
            charge(ctx, 5);
            lhu(v1, a0, bcore::kActFlags);
            v1 = v1 | 0x40;
            sh(v1, a0, bcore::kActFlags);
        }
    }
    // 0x002f4934 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F4950 sub_2F4950 -- 232 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [btl431Formation] Encounter 431's formation: the hero at (0, 300) slot 0 (the others reuse the cell last written);
// enemy 233 at (0, -300), the other enemies reuse it.
void sub_2F4950(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f4950
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, sp, 0x24);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f49b8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4970
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 1;
        if (v1 == v0) {
            // 0x002f4980
            charge(ctx, 4);
            sw(zero, sp, 0x20);
            v0 = 0x43960000;
            sw(v0, sp, 0x28);
            sb(zero, s0, bcore::kUnFormSlot);
        }
        // 0x002f4990
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2F499Cu, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2F49ACu, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f49c0
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f4a1c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f49d0
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 233;
        if (v1 == v0) {
            // 0x002f49e8
            charge(ctx, 3);
            sw(zero, sp, 0x20);
            v0 = lui(0xC396);
            sw(v0, sp, 0x28);
        } else {
            // 0x002f49e0
            charge(ctx, 2);
        }
        // 0x002f49f4
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2F4A00u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2F4A10u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f4a24
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002F4A40 sub_2F4A40 -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl431DeathScene] As sub_2F1810 for encounter 431 (enemy 233).
void sub_2F4A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f4a40
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F4A70u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2F4A80u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F4A90u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 233;
    for (;;) {
        // 0x002f4acc
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4ab0
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f4ac4
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f4abc
            charge(ctx, 2);
        }
        // 0x002f4ac8
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f4ad4
    charge(ctx, 75);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F4AECu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F4B08u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F4B18u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F4B38u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F4B54u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F4B74u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F4B84u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F4BA4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F4BC0u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F4BD0u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F4BDCu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F4C00 sub_2F4C00 -- 224 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btl432UnitInit] Encounter 432's unit init: enemy 234 gets action +26 bit 0x10, unit flags 0x100 | 0x40 | 0x80, the
// boss work's start (copied member 1, skill 225 at +2904, the copy counts cleared, the hero's count 1) and its idle
// effect 6.
void sub_2F4C00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f4c00
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(a3, a0, bcore::kActFlags2);
    v1 = a3 & 0x1;
    if (v1 != 0) {
        // 0x002f4c1c
        charge(ctx, 5);
        lw(s0, a0, bcore::kActUnit);
        lbu(v1, s0, bcore::kUnSide);
        a2 = 1;
        if (v1 == a2) {
            // 0x002f4c30
            charge(ctx, 4);
            lhu(a1, s0, bcore::kUnId);
            v1 = 234;
            if (a1 == v1) {
                // 0x002f4c48
                charge(ctx, 23);
                v0 = a3 | 0x10;
                sh(v0, a0, bcore::kActFlags2);
                lw(v0, s0, bcore::kUnFlags);
                v0 = v0 | 0x100;
                sw(v0, s0, bcore::kUnFlags);
                v0 = v0 | 0x40;
                sw(v0, s0, bcore::kUnFlags);
                v0 = v0 | 0x80;
                sw(v0, s0, bcore::kUnFlags);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                sw(a2, v0, b9::kBoss2900);
                v1 = 225;
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                sw(v1, v0, b9::kBoss2904);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                a0 = addiu(v0, 2908);
                a1 = 0;
                a2 = 22;
                jal(ctx, 0x2F4C90u, gen::fn_memset_00521408);
                a0 = 1;
                lw(v1, gp, bcore::kGpBtl);  // gBtl
                sh(a0, v1, b9::kBoss2910);
            } else {
                // 0x002f4c40
                charge(ctx, 2);
            }
            // 0x002f4ca4
            charge(ctx, 4);
            lhu(a0, s0, bcore::kUnId);
            v1 = 234;
            if (a0 == v1) {
                // 0x002f4cbc
                charge(ctx, 4);
                a0 = s0;
                a1 = 6;
                jal(ctx, 0x2F4CC4u, gen::fn_sub_288F80_00288f80);
            } else {
                // 0x002f4cb4
                charge(ctx, 2);
            }
        }
    }
    // 0x002f4ccc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F4CE0 sub_2F4CE0 -- 396 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl432Formation] As sub_2F1680 for encounter 432: table 0x69A4F0, slots 0x7CC9E8.., enemy 234.
void sub_2F4CE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f4ce0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -23312);  // &0x69A4F0
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f4d00
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
    // 0x002f4d24
    charge(ctx, 12);
    lh(a1, gp, -25352);  // 0x7CC9E8
    lh(a0, gp, -25350);  // 0x7CC9EA
    lh(v1, gp, -25348);  // 0x7CC9EC
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f4de8
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4d54
        charge(ctx, 4);
        lhu(v0, s1, bcore::kUnId);
        v1 = 1;
        if (v0 != v1) {
            // 0x002f4d80
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f4d64
            charge(ctx, 7);
            v0 = lui(0xC302);
            sw(v0, sp, 0x50);
            v0 = 0x43480000;
            sw(v0, sp, 0x58);
            sb(v1, s1, bcore::kUnFormSlot);
        }
        // 0x002f4dc0
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F4DCCu, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F4DDCu, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f4df0
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f4e4c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4e00
        charge(ctx, 4);
        lhu(v1, s0, bcore::kUnId);
        v0 = 234;
        if (v1 == v0) {
            // 0x002f4e18
            charge(ctx, 3);
            sw(zero, sp, 0x50);
            v0 = lui(0xC396);
            sw(v0, sp, 0x58);
        } else {
            // 0x002f4e10
            charge(ctx, 2);
        }
        // 0x002f4e24
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F4E30u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F4E40u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f4e54
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F4E70 sub_2F4E70 -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl432DeathScene] As sub_2F1810 for encounter 432 (enemy 234).
void sub_2F4E70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f4e70
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F4EA0u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 2;
    jal(ctx, 0x2F4EB0u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F4EC0u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 234;
    for (;;) {
        // 0x002f4efc
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f4ee0
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f4ef4
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f4eec
            charge(ctx, 2);
        }
        // 0x002f4ef8
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f4f04
    charge(ctx, 75);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F4F1Cu, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F4F38u, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F4F48u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F4F68u, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F4F84u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F4FA4u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F4FB4u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F4FD4u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F4FF0u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F5000u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F500Cu, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F5030 sub_2F5030 -- 748 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl432PickCopy] Encounter 432: the party member the boss ($a0 its action) copies next -- among the party units other
// than the last copied one (gBtl +2900) and id 9, those with the fewest copies (u16 by id at +2908), one by
// datCalcRand; a first copy clears the action's +24 bit 0x40 and calls sub_17B220(the boss's id); records the id,
// counts the copy and by the member (jump table 0x7B8A60: ids 1, 2, 4, 5, 7, 8, 9, 10) sets the skill (+2904: 225, 224,
// 226, 227, 228, 229, 231, 230) and the boss DatUnit's +4 (297..303; id 9: the boss's own id).
void sub_2F5030(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f5030
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v1 = 0xFFFF;
    t2 = v1 & 0xFFFF;
    a3 = 0;
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(t0, v1, b9::kBtlPartyTail);
    a2 = 9;
    for (;;) {
        // 0x002f50b8
        charge(ctx, 2);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f5064
        charge(ctx, 4);
        lhu(a1, t0, bcore::kUnId);
        lw(a0, v1, 2900);
        if (a0 != a1) {
            // 0x002f5074
            charge(ctx, 2);
            if (a1 != a2) {
                // 0x002f507c
                charge(ctx, 11);
                a0 = a3 & 0xFFFF;
                a0 = sll(a0, 2);
                a0 = addu(a0, sp);
                sw(t0, a0, 64);
                a0 = sll(a1, 1);
                a0 = addu(v1, a0);
                lhu(a1, a0, 2908);
                a0 = t2 & 0xFFFF;
                at = slt(a1, a0);
                if (at != 0) {
                    // 0x002f50a8
                    charge(ctx, 1);
                    t2 = a1;
                }
                // 0x002f50ac
                charge(ctx, 2);
                a0 = addiu(a3, 1);
                a3 = a0 & 0xFFFF;
            }
        }
        // 0x002f50b4
        charge(ctx, 1);
        lw(t0, t0, bcore::kUnPrev);
    }
    // 0x002f50c0
    charge(ctx, 3);
    a3 = a3 & 0xFFFF;
    if (a3 != 0) {
        // 0x002f50cc
        charge(ctx, 5);
        t1 = 0;
        t0 = 0;
        a2 = t2 & 0xFFFF;
        for (;;) {
            // 0x002f5130
            charge(ctx, 4);
            a0 = t0 & 0xFFFF;
            a0 = slt(a0, a3);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002f50e0
            charge(ctx, 12);
            a0 = t0 & 0xFFFF;
            a0 = sll(a0, 2);
            a0 = addu(a0, sp);
            a0 = addiu(a0, 64);
            lw(a1, a0, 0);
            lhu(a0, a1, bcore::kUnId);
            a0 = sll(a0, 1);
            a0 = addu(v1, a0);
            lhu(a0, a0, 2908);
            at = slt(a2, a0);
            if (at == 0) {
                // 0x002f5110
                charge(ctx, 6);
                a0 = t1 & 0xFFFF;
                a0 = sll(a0, 2);
                a0 = addu(a0, sp);
                sw(a1, a0, 48);
                a0 = addiu(t1, 1);
                t1 = a0 & 0xFFFF;
            }
            // 0x002f5128
            charge(ctx, 2);
            a0 = addiu(t0, 1);
            t0 = a0 & 0xFFFF;
        }
        // 0x002f5140
        charge(ctx, 3);
        a0 = t1 & 0xFFFF;
        if (a0 != 0) {
            // 0x002f514c
            charge(ctx, 12);
            jal(ctx, 0x2F514Cu, gen::fn_datCalcRand_002ffbc0);
            v1 = sll(v0, 2);
            v1 = addu(v1, sp);
            lw(s0, v1, bcore::kActUnit);
            lhu(v1, s0, bcore::kUnId);
            a0 = sll(v1, 1);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            v1 = addu(a0, v1);
            lhu(v1, v1, 2908);
            if (v1 == 0) {
                // 0x002f517c
                charge(ctx, 7);
                lhu(v0, s1, bcore::kActFlags);
                v0 = v0 & 0xFFBF;
                sh(v0, s1, bcore::kActFlags);
                lw(v0, s1, bcore::kActUnit);
                lhu(a0, v0, bcore::kUnId);
                jal(ctx, 0x2F5190u, gen::fn_sub_17B220_0017b220);
            }
            // 0x002f5198
            charge(ctx, 14);
            lhu(a0, s0, bcore::kUnId);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(a0, v1, b9::kBoss2900);
            lhu(v1, s0, bcore::kUnId);
            a0 = sll(v1, 1);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            a0 = addu(a0, v1);
            lhu(v1, a0, 2908);
            v1 = addiu(v1, 1);
            sh(v1, a0, 2908);
            lhu(v1, s0, bcore::kUnId);
            at = sltiu(v1, 11);
            if (at != 0) {
                // 0x002f51d0
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -30112);  // &0x7B8A60
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x2F51ECu:  // table[1]
                    // 0x002f51ec
                    charge(ctx, 9);
                    a0 = 225;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 297;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F5210u:  // table[2]
                    // 0x002f5210
                    charge(ctx, 9);
                    a0 = 224;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 298;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F5234u:  // table[4]
                    // 0x002f5234
                    charge(ctx, 9);
                    a0 = 226;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 299;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F5258u:  // table[5]
                    // 0x002f5258
                    charge(ctx, 9);
                    a0 = 227;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 300;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F527Cu:  // table[7]
                    // 0x002f527c
                    charge(ctx, 9);
                    a0 = 228;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 301;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F52A0u:  // table[8]
                    // 0x002f52a0
                    charge(ctx, 9);
                    a0 = 229;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 302;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F52C4u:  // table[9]
                    // 0x002f52c4
                    charge(ctx, 9);
                    a0 = 231;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    lw(v1, s1, bcore::kActUnit);
                    lhu(a0, v1, bcore::kUnId);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F52E8u:  // table[10]
                    // 0x002f52e8
                    charge(ctx, 7);
                    a0 = 230;
                    lw(v1, gp, bcore::kGpBtl);  // gBtl
                    sw(a0, v1, b9::kBoss2904);
                    a0 = 303;
                    lw(v1, s1, bcore::kActUnit);
                    lw(v1, v1, bcore::kUnDat);
                    sh(a0, v1, 4);
                    break;
                case 0x2F5304u:  // table[0, 3, 6]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
        }
    }
    // 0x002f5304 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002F5330 sub_2F5330 -- 344 bytes; frame 0x10: ra sp+0x0
// [btl434UnitInit] Encounter 434's unit init: enemies 235..240 get action +26 bit 0x10, unit flags 0x100 | 0x40 | 0x80,
// DatUnit flag 0x40 and sub_288F80(unit, 203 / 205 / 199 / 207 / 193 / 197).
void sub_2F5330(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f5330
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(a3, a0, bcore::kActFlags2);
    v1 = a3 & 0x1;
    if (v1 != 0) {
        // 0x002f5348
        charge(ctx, 5);
        lw(v1, a0, bcore::kActUnit);
        lbu(a2, v1, bcore::kUnSide);
        a1 = 1;
        if (a2 == a1) {
            // 0x002f535c
            charge(ctx, 5);
            lhu(a1, v1, bcore::kUnId);
            a1 = addiu(a1, -235);
            at = sltiu(a1, 6);
            if (at != 0) {
                // 0x002f5370
                charge(ctx, 7);
                a2 = 0x7C0000;
                a2 = addiu(a2, -30032);  // &0x7B8AB0
                a1 = sll(a1, 2);
                a1 = addu(a1, a2);
                lw(a1, a1, 0);
                switch (a1.u()) {
                case 0x2F538Cu:  // table[0, 1, 2, 3, 4, 5]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, a1.u());
                    return;
                }
                // 0x002f538c
                charge(ctx, 13);
                a1 = a3 | 0x10;
                sh(a1, a0, bcore::kActFlags2);
                lw(a0, v1, bcore::kUnFlags);
                a0 = a0 | 0x100;
                sw(a0, v1, bcore::kUnFlags);
                a0 = a0 | 0x40;
                sw(a0, v1, bcore::kUnFlags);
                a0 = a0 | 0x80;
                sw(a0, v1, bcore::kUnFlags);
                lw(a1, v1, bcore::kUnDat);
                lhu(a0, a1, 0);
                a0 = a0 | 0x40;
                sh(a0, a1, 0);
            }
            // 0x002f53c0
            charge(ctx, 5);
            lhu(a0, v1, bcore::kUnId);
            a0 = addiu(a0, -235);
            at = sltiu(a0, 6);
            if (at != 0) {
                // 0x002f53d4
                charge(ctx, 7);
                a1 = 0x7C0000;
                a1 = addiu(a1, -30064);  // &0x7B8A90
                a0 = sll(a0, 2);
                a0 = addu(a0, a1);
                lw(a0, a0, 0);
                switch (a0.u()) {
                case 0x2F53F0u:  // table[0]
                    // 0x002f53f0
                    charge(ctx, 6);
                    a0 = v1;
                    a1 = 203;
                    jal(ctx, 0x2F53F8u, gen::fn_sub_288F80_00288f80);
                    break;
                case 0x2F5408u:  // table[2]
                    // 0x002f5408
                    charge(ctx, 6);
                    a0 = v1;
                    a1 = 199;
                    jal(ctx, 0x2F5410u, gen::fn_sub_288F80_00288f80);
                    break;
                case 0x2F5420u:  // table[4]
                    // 0x002f5420
                    charge(ctx, 6);
                    a0 = v1;
                    a1 = 193;
                    jal(ctx, 0x2F5428u, gen::fn_sub_288F80_00288f80);
                    break;
                case 0x2F5438u:  // table[1]
                    // 0x002f5438
                    charge(ctx, 6);
                    a0 = v1;
                    a1 = 205;
                    jal(ctx, 0x2F5440u, gen::fn_sub_288F80_00288f80);
                    break;
                case 0x2F5450u:  // table[3]
                    // 0x002f5450
                    charge(ctx, 6);
                    a0 = v1;
                    a1 = 207;
                    jal(ctx, 0x2F5458u, gen::fn_sub_288F80_00288f80);
                    break;
                case 0x2F5468u:  // table[5]
                    // 0x002f5468
                    charge(ctx, 4);
                    a0 = v1;
                    a1 = 197;
                    jal(ctx, 0x2F5470u, gen::fn_sub_288F80_00288f80);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, a0.u());
                    return;
                }
            }
        }
    }
    // 0x002f5478 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F5490 sub_2F5490 -- 456 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [btl434Formation] Encounter 434's formation: in encounter 434 member 9 at (-150, 300) slot 0 and the hero at (150,
// 300) slot 1, elsewhere the other way round (the others reuse the cell last written); enemies 235, 238, 239 at (-150,
// -300), 236, 237, 240 at (150, -300).
void sub_2F5490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f5490
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, sp, 0x24);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f55a4
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f54b0
        charge(ctx, 6);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(v0, v0, bcore::kBtlSetupEnemies);
        lhu(v1, v0, 8);
        v0 = 434;
        if (v1 != v0) {
            // 0x002f5524
            charge(ctx, 4);
            lhu(v1, s0, bcore::kUnId);
            v0 = 9;
            if (v1 == v0) {
                // 0x002f5564
                charge(ctx, 6);
                v0 = 0x43160000;
                sw(v0, sp, 0x20);
                v0 = 0x43960000;
                sw(v0, sp, 0x28);
                v0 = 1;
                sb(v0, s0, bcore::kUnFormSlot);
            } else {
                // 0x002f5534
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002f5548
                    charge(ctx, 7);
                    v0 = lui(0xC316);
                    sw(v0, sp, 0x20);
                    v0 = 0x43960000;
                    sw(v0, sp, 0x28);
                    sb(zero, s0, bcore::kUnFormSlot);
                } else {
                    // 0x002f5540
                    charge(ctx, 2);
                }
            }
        } else {
            // 0x002f54c8
            charge(ctx, 4);
            lhu(a0, s0, bcore::kUnId);
            v0 = 9;
            if (a0 == v0) {
                // 0x002f5508
                charge(ctx, 7);
                v0 = lui(0xC316);
                sw(v0, sp, 0x20);
                v0 = 0x43960000;
                sw(v0, sp, 0x28);
                sb(zero, s0, bcore::kUnFormSlot);
            } else {
                // 0x002f54d8
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x002f54ec
                    charge(ctx, 7);
                    v0 = 0x43160000;
                    sw(v0, sp, 0x20);
                    v0 = 0x43960000;
                    sw(v0, sp, 0x28);
                    sb(v1, s0, bcore::kUnFormSlot);
                } else {
                    // 0x002f54e4
                    charge(ctx, 2);
                }
            }
        }
        // 0x002f557c
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2F5588u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2F5598u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f55ac
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f563c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f55bc
        charge(ctx, 5);
        lhu(v0, s0, bcore::kUnId);
        v0 = addiu(v0, -235);
        at = sltiu(v0, 6);
        if (at != 0) {
            // 0x002f55d0
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30000);  // &0x7B8AD0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2F55ECu:  // table[0, 3, 4]
                // 0x002f55ec
                charge(ctx, 6);
                v0 = lui(0xC316);
                sw(v0, sp, 0x20);
                v0 = lui(0xC396);
                sw(v0, sp, 0x28);
                break;
            case 0x2F5604u:  // table[1, 2, 5]
                // 0x002f5604
                charge(ctx, 4);
                v0 = 0x43160000;
                sw(v0, sp, 0x20);
                v0 = lui(0xC396);
                sw(v0, sp, 0x28);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x002f5614
        charge(ctx, 10);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2F5620u, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x20);
        jal(ctx, 0x2F5630u, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f5644
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002F5660 sub_2F5660 -- 528 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl434LeaveScene] One of 434's enemies leaves ($a0 its action): clears gBtl flag 0x2000000, pauses the order, binds
// BED 2 (235, 237, 239) or 3 (236, 238, 240), the motion 18 (delay 3), sub_2B8D60(1, 4095), the transform, the shot and
// the unit effect; frees the handle.
void sub_2F5660(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f5660
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a1, bcore::kBtlFlags);
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a1, bcore::kBtlFlags);
    lw(s2, a0, bcore::kActUnit);
    lhu(v0, s2, bcore::kUnId);
    v0 = addiu(v0, -235);
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x002f56c0
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -29968);  // &0x7B8AF0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x2F56DCu:  // table[0, 2, 4]
            // 0x002f56dc
            charge(ctx, 3);
            s0 = 2;
            break;
        case 0x2F56E8u:  // table[1, 3, 5]
            // 0x002f56e8
            charge(ctx, 1);
            s0 = 3;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x002f56ec
    charge(ctx, 97);
    a0 = 0;
    jal(ctx, 0x2F56F0u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x2F5700u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F5710u, gen::fn_sub_2B90D0_002b90d0);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F5730u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F5754u, gen::fn_sub_27ED20_0027ed20);
    a0 = 1;
    a1 = 4095;
    jal(ctx, 0x2F5764u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F578Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F57A8u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F57D0u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F57E0u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F5808u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F5824u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 2;
    jal(ctx, 0x2F583Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F5848u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002F5870 sub_2F5870 -- 260 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btl434LeaveDone] The leave's done callback: 1 while packets remain; then resumes the order, kills and removes the
// action, sets gBtl flag 0x2000000 and queues the three closing packets; 0.
void sub_2F5870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f5870
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
    jal(ctx, 0x2F58A0u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f595c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f58b0
        charge(ctx, 43);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, bcore::kBtlFlags);
        a0 = s0;
        a1 = 0;
        jal(ctx, 0x2F58D0u, gen::fn_sub_2D7890_002d7890);
        a0 = s0;
        jal(ctx, 0x2F58DCu, gen::fn_sub_29A320_0029a320);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = 0x2000000;
        v0 = v1 | v0;
        sw(v0, a0, bcore::kBtlFlags);
        a0 = 16;
        jal(ctx, 0x2F58FCu, gen::fn_sub_29FA50_0029fa50);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F590Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        a1 = 4;
        jal(ctx, 0x2F591Cu, gen::fn_sub_2A1080_002a1080);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F592Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        jal(ctx, 0x2F5938u, gen::fn_sub_2A16C0_002a16c0);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F5948u, gen::fn_sub_27ED20_0027ed20);
        v0 = 0;
    }
    // 0x002f5960 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F5980 sub_2F5980 -- 236 bytes; frame 0x10: ra sp+0x0
// [btl436UnitInit] Encounter 436's unit init: enemy 242 gets DatUnit flag 0x40, unit flags 0x100 | 0x40 | 0x400 |
// 0x2000 (0x8 cleared), action +26 bit 0x8 cleared, is removed from the order (sub_29A320) and gBtl +2896 = 0; enemy
// 241 gets unit flags 0x100 | 0x40 | 0x400 | 0x2000.
void sub_2F5980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f5980
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v1, a0, bcore::kActFlags2);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x002f5998
        charge(ctx, 5);
        lw(v1, a0, bcore::kActUnit);
        lbu(a2, v1, bcore::kUnSide);
        a1 = 1;
        if (a2 == a1) {
            // 0x002f59ac
            charge(ctx, 4);
            lhu(a2, v1, bcore::kUnId);
            a1 = 242;
            if (a2 == a1) {
                // 0x002f59fc
                charge(ctx, 24);
                lw(a1, v1, bcore::kUnDat);
                lhu(v0, a1, 0);
                v0 = v0 | 0x40;
                sh(v0, a1, 0);
                lw(v0, v1, bcore::kUnFlags);
                v0 = v0 | 0x100;
                sw(v0, v1, bcore::kUnFlags);
                a1 = v0 | 0x40;
                sw(a1, v1, bcore::kUnFlags);
                v0 = si(-9);
                v0 = a1 & v0;
                sw(v0, v1, bcore::kUnFlags);
                lhu(v0, a0, bcore::kActFlags2);
                v0 = v0 & 0xFFF7;
                sh(v0, a0, bcore::kActFlags2);
                lw(v0, v1, bcore::kUnFlags);
                v0 = v0 | 0x400;
                sw(v0, v1, bcore::kUnFlags);
                v0 = v0 | 0x2000;
                sw(v0, v1, bcore::kUnFlags);
                jal(ctx, 0x2F5A4Cu, gen::fn_sub_29A320_0029a320);
                lw(v1, gp, bcore::kGpBtl);  // gBtl
                sw(zero, v1, b9::kBoss2896);
            } else {
                // 0x002f59bc
                charge(ctx, 3);
                a0 = 241;
                if (a2 == a0) {
                    // 0x002f59d0
                    charge(ctx, 11);
                    lw(a0, v1, bcore::kUnFlags);
                    a0 = a0 | 0x100;
                    sw(a0, v1, bcore::kUnFlags);
                    a0 = a0 | 0x40;
                    sw(a0, v1, bcore::kUnFlags);
                    a0 = a0 | 0x400;
                    sw(a0, v1, bcore::kUnFlags);
                    a0 = a0 | 0x2000;
                    sw(a0, v1, bcore::kUnFlags);
                } else {
                    // 0x002f59c8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x002f5a5c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F5A70 sub_2F5A70 -- 376 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlFormationFar2] As sub_2F2250 with the table 0x69A550 and the slots 0x7CC9F0...
void sub_2F5A70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002f5a70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a3 = 0x6A0000;
    a3 = addiu(a3, -23216);  // &0x69A550
    a2 = addiu(sp, 0x30);
    a1 = 3;
    for (;;) {
        // 0x002f5a90
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
    // 0x002f5ab4
    charge(ctx, 12);
    lh(a1, gp, -25344);  // 0x7CC9F0
    lh(a0, gp, -25342);  // 0x7CC9F2
    lh(v1, gp, -25340);  // 0x7CC9F4
    sh(a1, sp, 0x48);
    sh(a0, sp, 0x4A);
    sh(v1, sp, 0x4C);
    s0 = 0;
    sw(zero, sp, 0x54);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s1, v1, b9::kBtlPartyTail);
    for (;;) {
        // 0x002f5b7c
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f5ae4
        charge(ctx, 4);
        lhu(v1, s1, bcore::kUnId);
        v0 = 1;
        if (v1 != v0) {
            // 0x002f5b14
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
            sb(v0, s1, bcore::kUnFormSlot);
            v0 = addiu(s0, 1);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
        } else {
            // 0x002f5af4
            charge(ctx, 8);
            v0 = 0x43160000;
            sw(v0, sp, 0x50);
            v0 = 0x43FA0000;
            sw(v0, sp, 0x58);
            v0 = 2;
            sb(v0, s1, bcore::kUnFormSlot);
        }
        // 0x002f5b54
        charge(ctx, 10);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F5B60u, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F5B70u, gen::fn_sub_27F650_0027f650);
        lw(s1, s1, bcore::kUnPrev);
    }
    // 0x002f5b84
    charge(ctx, 4);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(s0, v1, b9::kBtlEnemyTail);
    for (;;) {
        // 0x002f5bc8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f5b94
        charge(ctx, 13);
        sw(zero, sp, 0x50);
        v0 = lui(0xC3FA);
        sw(v0, sp, 0x58);
        a0 = addiu(s0, 148);
        a1 = addiu(s0, 150);
        a2 = addiu(sp, 0x50);
        jal(ctx, 0x2F5BACu, gen::fn_sub_2D2280_002d2280);
        a0 = s0;
        a1 = addiu(sp, 0x50);
        jal(ctx, 0x2F5BBCu, gen::fn_sub_27F650_0027f650);
        lw(s0, s0, bcore::kUnPrev);
    }
    // 0x002f5bd0
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F5D80 sub_2F5D80 -- 920 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl436Fade] Per frame of enemy 241's unit ($a0, with a model: +152 bit 2): enemy 242's fade. While the countdown
// gBtl +2900 runs, mode +2896 != 0 keeps it hidden and mode 0 shown (opaque); after it, mode != 0 fades in (alpha 255 *
// frame / length: +2904 / +2902) and mode 0 fades out (255 - that) until the frame reaches the length (then hidden); a
// shown unit takes the colour (sub_27F730, alpha in the top byte) and sub_287490 when 241 is visible (sub_287580 and
// the +3 byte of sub_27F930's record), else sub_287510.
void sub_2F5D80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x002f5d80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lbu(a0, a0, bcore::kUnSide);
    v1 = 1;
    if (a0 == v1) {
        // 0x002f5dac
        charge(ctx, 4);
        lhu(a0, s1, bcore::kUnId);
        v1 = 241;
        if (a0 == v1) {
            // 0x002f5dbc
            charge(ctx, 4);
            lw(v1, s1, 152);
            v1 = v1 & 0x2;
            if (v1 != 0) {
                // 0x002f5dcc
                charge(ctx, 5);
                lw(a1, gp, bcore::kGpBtl);  // gBtl
                lw(s0, a1, b9::kBtlEnemyTail);
                v1 = 242;
                for (;;) {
                    // 0x002f60f0
                    charge(ctx, 2);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002f5de0
                    charge(ctx, 3);
                    lhu(a0, s0, bcore::kUnId);
                    if (a0 == v1) {
                        goto L_002f5dec_5;
                    }
                    // 0x002f60ec
                    charge(ctx, 1);
                    lw(s0, s0, bcore::kUnPrev);
                }
            }
        }
    }
    // 0x002f60f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_002f5dec_5:
    charge(ctx, 4);
    v1 = addiu(a1, 2900);
    lhu(v0, a1, 2900);
    if (i64(v0) <= 0) {
        // 0x002f5e10
        charge(ctx, 1);
        a0 = 0;
    } else {
        // 0x002f5dfc
        charge(ctx, 5);
        a0 = 1;
        v0 = addiu(v0, -1);
        sh(v0, v1, 0);
    }
    // 0x002f5e14
    charge(ctx, 9);
    v0 = 255;
    sb(v0, sp, 0x5C);
    sb(v0, sp, 0x5D);
    sb(v0, sp, 0x5E);
    sb(v0, sp, 0x5F);
    lw(v1, gp, bcore::kGpBtl);  // gBtl
    lw(v0, v1, b9::kBoss2896);
    if (v0 == 0) {
        // 0x002f5f50
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x002f5f64
            charge(ctx, 6);
            lhu(a2, v1, 2902);
            a1 = addiu(v1, 2904);
            lhu(a0, v1, 2904);
            at = slt(a0, a2);
            if (at == 0) {
                // 0x002f6074
                charge(ctx, 1);
                s3 = 0;
            } else {
                // 0x002f5f7c
                charge(ctx, 4);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                if (i64(a0) < 0) {
                    // 0x002f5fa0
                    charge(ctx, 7);
                    v1 = srl(a0, 1);
                    v0 = a0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x002f5f8c
                    charge(ctx, 5);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x002f5fbc
                charge(ctx, 3);
                mul_s(f1, f1, f0);
                if (i64(a2) < 0) {
                    // 0x002f5fdc
                    charge(ctx, 7);
                    v1 = srl(a2, 1);
                    v0 = a2 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x002f5fc8
                    charge(ctx, 5);
                    mtc1(a2, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x002f5ff8
                charge(ctx, 9);
                div_s(f1, f1, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002f6034
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002f601c
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002f604c
                charge(ctx, 10);
                v1 = v1 & 0xFF;
                v0 = 255;
                v0 = subu(v0, v1);
                sb(v0, sp, 0x5F);
                lhu(v0, a1, 0);
                v0 = addiu(v0, 1);
                sh(v0, a1, 0);
                s3 = 1;
            }
        } else {
            // 0x002f5f58
            charge(ctx, 3);
            s3 = 1;
        }
    } else {
        // 0x002f5e38
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x002f5e4c
            charge(ctx, 6);
            lhu(a2, v1, 2902);
            a1 = addiu(v1, 2904);
            lhu(a0, v1, 2904);
            at = slt(a0, a2);
            if (at != 0) {
                // 0x002f5e64
                charge(ctx, 4);
                v0 = 0x437F0000;
                mtc1(v0, f1);
                if (i64(a0) < 0) {
                    // 0x002f5e88
                    charge(ctx, 7);
                    v1 = srl(a0, 1);
                    v0 = a0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x002f5e74
                    charge(ctx, 5);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x002f5ea4
                charge(ctx, 3);
                mul_s(f1, f1, f0);
                if (i64(a2) < 0) {
                    // 0x002f5ec4
                    charge(ctx, 7);
                    v1 = srl(a2, 1);
                    v0 = a2 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x002f5eb0
                    charge(ctx, 5);
                    mtc1(a2, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x002f5ee0
                charge(ctx, 9);
                div_s(f1, f1, f0);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x002f5f1c
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x002f5f04
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x002f5f34
                charge(ctx, 4);
                sb(v1, sp, 0x5F);
                lhu(v0, a1, 0);
                v0 = addiu(v0, 1);
                sh(v0, a1, 0);
            }
            // 0x002f5f44
            charge(ctx, 3);
            s3 = 1;
        } else {
            // 0x002f5e40
            charge(ctx, 3);
            s3 = 0;
        }
    }
    // 0x002f6078
    charge(ctx, 7);
    a0 = s1;
    jal(ctx, 0x2F607Cu, gen::fn_sub_27F930_0027f930);
    s2 = v0;
    v0 = 1;
    if (s3 == v0) {
        // 0x002f6094
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x2F6098u, gen::fn_sub_287580_00287580);
        if (v0 == 0) {
            goto L_002f60d8;
        }
        // 0x002f60a8
        charge(ctx, 3);
        lbu(v0, s2, 3);
        if (i64(v0) <= 0) {
            goto L_002f60d8;
        }
        // 0x002f60b4
        charge(ctx, 9);
        a0 = s0;
        lw(a1, sp, 0x5C);
        jal(ctx, 0x2F60BCu, gen::fn_sub_27F730_0027f730);
        a0 = s0;
        jal(ctx, 0x2F60C8u, gen::fn_sub_287490_00287490);
        // 0x002f60f8 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x60);
        return;
    }
L_002f60d8:
    charge(ctx, 5);
    a0 = s0;
    jal(ctx, 0x2F60DCu, gen::fn_sub_287510_00287510);
    // 0x002f60f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F6120 sub_2F6120 -- 524 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl436DeathScene] Encounter 436's death scene: clears gBtl flag 0x2000000, binds BED 4, finds enemy 241, the ADX
// stream request sub_2DD690(3, "E1B4_99.ADX"), its motion 18 (delay 3), sub_2B8D60, the transform, the shot, the unit
// effect and sub_2BC890(0x7CC970, 24) (delay 200); frees the handle.
void sub_2F6120(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x002f6120
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a0, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a0, bcore::kBtlFlags);
    a0 = 0;
    jal(ctx, 0x2F6150u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = 4;
    jal(ctx, 0x2F6160u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F6170u, gen::fn_sub_2B90D0_002b90d0);
    s2 = 0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, b9::kBtlEnemyTail);
    v0 = 241;
    for (;;) {
        // 0x002f61ac
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002f6190
        charge(ctx, 3);
        lhu(v1, a0, bcore::kUnId);
        if (v1 == v0) {
            // 0x002f61a4
            charge(ctx, 1);
            s2 = a0;
        } else {
            // 0x002f619c
            charge(ctx, 2);
        }
        // 0x002f61a8
        charge(ctx, 1);
        lw(a0, a0, bcore::kUnPrev);
    }
    // 0x002f61b4
    charge(ctx, 94);
    a0 = 3;
    a1 = 0x6A0000;
    a1 = addiu(a1, -23112);  // "E1B4_99.ADX"
    jal(ctx, 0x2F61C0u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x2F61D0u, gen::fn_sub_27ED20_0027ed20);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a0 = s2;
    a1 = 18;
    a2 = 0;
    a3 = 2;
    jal(ctx, 0x2F61F0u, gen::fn_sub_284200_00284200);
    s0 = v0;
    v1 = 3;
    sh(v1, v0, bcore::kPktStartDelay);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x2F620Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2F621Cu, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F623Cu, gen::fn_sub_27ED20_0027ed20);
    a0 = s2;
    a1 = 0;
    a2 = 0x690000;
    a2 = addiu(a2, 30896);  // &0x6978B0
    a3 = 0;
    jal(ctx, 0x2F6258u, gen::fn_sub_27FE90_0027fe90);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 1;
    jal(ctx, 0x2F6278u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F6288u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, b9::kPktWaitKind0);
    ld(v1, s0, bcore::kPktId);
    sd(v1, v0, b9::kPktWaitId0);
    a1 = 0;
    jal(ctx, 0x2F62A8u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F62C4u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2F62D4u, gen::fn_sub_27ED20_0027ed20);
    a0 = addiu(gp, -25472);  // &0x7CC970
    a1 = 24;
    jal(ctx, 0x2F62E4u, gen::fn_sub_2BC890_002bc890);
    a0 = v0;
    v1 = 200;
    sh(v1, v0, bcore::kPktStartDelay);
    a1 = 1;
    jal(ctx, 0x2F62FCu, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    jal(ctx, 0x2F6308u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002F6330 sub_2F6330 -- 480 bytes; frame 0x60: ra sp+0x10, s0 sp+0x0 (sq)
// [btl436CameraShot] The camera shot callback ($a0 the shot) when the shot's action (+224) is enemy 241's: one of two
// {position, target} pairs (0x69A5C8 / 0x69A5D8 with the offsets 0x69A5E8 / 0x69A5F8, sub_2A4690 against 0x697880; the
// order by sub_357FD0(0) & 1), the camera move (sub_2A2290, sub_2A3110), sub_2A3E80(action, 0, 0, 8); gBtl +2944 = 1;
// returns 1 (0 for any other action).
void sub_2F6330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x002f6330
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 224);
    lw(a0, v0, bcore::kActUnit);
    lbu(v1, a0, bcore::kUnSide);
    v0 = 1;
    if (v1 == v0) {
        // 0x002f6364
        charge(ctx, 4);
        lhu(v1, a0, bcore::kUnId);
        v0 = 241;
        if (v1 == v0) {
            // 0x002f6380
            charge(ctx, 6);
            a0 = 0;
            jal(ctx, 0x2F6384u, gen::fn_sub_357FD0_00357fd0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x002f6424
                charge(ctx, 33);
                a0 = addiu(sp, 0x48);
                a1 = 0x6A0000;
                a1 = addiu(a1, -23096);  // &0x69A5C8
                a2 = 0x6A0000;
                a2 = addiu(a2, -23064);  // &0x69A5E8
                a3 = 0x690000;
                a3 = addiu(a3, 30848);  // &0x697880
                jal(ctx, 0x2F6440u, gen::fn_sub_2A4690_002a4690);
                v0 = 0x6A0000;
                lwc1(f2, v0, -23096);  // 0x69A5C8
                v0 = 0x6A0000;
                lwc1(f1, v0, -23092);  // 0x69A5CC
                v0 = 0x6A0000;
                lwc1(f0, v0, -23088);  // 0x69A5D0
                swc1(f2, sp, 0x3C);
                swc1(f1, sp, 0x40);
                swc1(f0, sp, 0x44);
                a0 = addiu(sp, 0x2C);
                a1 = 0x6A0000;
                a1 = addiu(a1, -23080);  // &0x69A5D8
                a2 = 0x6A0000;
                a2 = addiu(a2, -23048);  // &0x69A5F8
                a3 = 0x690000;
                a3 = addiu(a3, 30848);  // &0x697880
                jal(ctx, 0x2F6488u, gen::fn_sub_2A4690_002a4690);
                v0 = 0x6A0000;
                ld(v1, v0, -23080);  // 0x69A5D8
                v0 = 0x6A0000;
                lwc1(f0, v0, -23072);  // 0x69A5E0
                sd(v1, sp, 0x20);
                swc1(f0, sp, 0x28);
            } else {
                // 0x002f6398
                charge(ctx, 35);
                a0 = addiu(sp, 0x2C);
                a1 = 0x6A0000;
                a1 = addiu(a1, -23096);  // &0x69A5C8
                a2 = 0x6A0000;
                a2 = addiu(a2, -23064);  // &0x69A5E8
                a3 = 0x690000;
                a3 = addiu(a3, 30848);  // &0x697880
                jal(ctx, 0x2F63B4u, gen::fn_sub_2A4690_002a4690);
                v0 = 0x6A0000;
                ld(v1, v0, -23096);  // 0x69A5C8
                v0 = 0x6A0000;
                lwc1(f0, v0, -23088);  // 0x69A5D0
                sd(v1, sp, 0x20);
                swc1(f0, sp, 0x28);
                a0 = addiu(sp, 0x48);
                a1 = 0x6A0000;
                a1 = addiu(a1, -23080);  // &0x69A5D8
                a2 = 0x6A0000;
                a2 = addiu(a2, -23048);  // &0x69A5F8
                a3 = 0x690000;
                a3 = addiu(a3, 30848);  // &0x697880
                jal(ctx, 0x2F63F0u, gen::fn_sub_2A4690_002a4690);
                v0 = 0x6A0000;
                lwc1(f2, v0, -23080);  // 0x69A5D8
                v0 = 0x6A0000;
                lwc1(f1, v0, -23076);  // 0x69A5DC
                v0 = 0x6A0000;
                lwc1(f0, v0, -23072);  // 0x69A5E0
                swc1(f2, sp, 0x3C);
                swc1(f1, sp, 0x40);
                swc1(f0, sp, 0x44);
            }
            // 0x002f64a8
            charge(ctx, 21);
            a0 = s0;
            a1 = addiu(sp, 0x20);
            a2 = addiu(sp, 0x3C);
            a3 = 1;
            jal(ctx, 0x2F64B8u, gen::fn_sub_2A2290_002a2290);
            v0 = 0x40A00000;
            mtc1(v0, f12);
            a0 = s0;
            jal(ctx, 0x2F64CCu, gen::fn_sub_2A3110_002a3110);
            mtc1(zero, f12);
            lw(a0, s0, 224);
            a1 = 0;
            a2 = 0;
            a3 = 8;
            jal(ctx, 0x2F64E8u, gen::fn_sub_2A3E80_002a3e80);
            v0 = 1;
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2944);
        } else {
            // 0x002f6374
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002f6358
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002f64fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002F6510 sub_2F6510 -- 816 bytes; frame 0x90: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [btlBossCameraShot] The camera shot callback ($a0 the shot) by the skill in gBtl +2908: 294 the pair 0x69A648 /
// 0x69A658, 293 / 295 / 296 the pair 0x69A608 / 0x69A618 (both with the target motion flag 64), otherwise a row of
// 0x69A690 / 0x69A6B0 picked by datCalcIsHpSkill and sub_2F6C20 (flag 1); the camera move on gBtl +32 (sub_2A2290,
// sub_2A3110), sub_2A3E80; gBtl +2908 = -1; returns 1.
void sub_2F6510(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x002f6510
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(v1, v0, b9::kBoss2908);
    v0 = 294;
    if (v1 == v0) {
        // 0x002f6608
        charge(ctx, 39);
        a0 = addiu(sp, 0x5C);
        a1 = 0x6A0000;
        a1 = addiu(a1, -22968);  // &0x69A648
        a2 = 0x6A0000;
        a2 = addiu(a2, -22936);  // &0x69A668
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2F6624u, gen::fn_sub_2A4690_002a4690);
        v0 = 0x6A0000;
        ld(v1, v0, -22968);  // 0x69A648
        v0 = 0x6A0000;
        lwc1(f0, v0, -22960);  // 0x69A650
        sd(v1, sp, 0x50);
        swc1(f0, sp, 0x58);
        a0 = addiu(sp, 0x78);
        a1 = 0x6A0000;
        a1 = addiu(a1, -22952);  // &0x69A658
        a2 = 0x6A0000;
        a2 = addiu(a2, -22920);  // &0x69A678
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2F6660u, gen::fn_sub_2A4690_002a4690);
        v0 = 0x6A0000;
        lwc1(f2, v0, -22952);  // 0x69A658
        v0 = 0x6A0000;
        lwc1(f1, v0, -22948);  // 0x69A65C
        v0 = 0x6A0000;
        lwc1(f0, v0, -22944);  // 0x69A660
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        swc1(f0, sp, 0x74);
        v0 = 0x40000000;
        mtc1(v0, f20);
        s2 = 1;
        s0 = s2;
    } else {
        // 0x002f6540
        charge(ctx, 3);
        v0 = 296;
        if (v1 != v0) {
            // 0x002f654c
            charge(ctx, 3);
            v0 = 295;
            if (v1 == v0) {
                goto L_002f656c;
            }
            // 0x002f6558
            charge(ctx, 3);
            v0 = 293;
            if (v1 == v0) {
                goto L_002f656c;
            }
            // 0x002f6564
            charge(ctx, 2);
            // 0x002f66a4
            charge(ctx, 7);
            lw(v0, s1, 224);
            lh(a0, v0, b9::kActSkill);
            jal(ctx, 0x2F66ACu, gen::fn_datCalcIsHpSkill_002d6370);
            v1 = 1;
            if (v0 == v1) {
                // 0x002f66c0
                charge(ctx, 4);
                jal(ctx, 0x2F66C0u, gen::fn_sub_2F6C20_002f6c20);
                if (v0 != 0) {
                    goto L_002f66dc;
                }
                // 0x002f66d0
                charge(ctx, 3);
                v0 = 0;
                goto L_002f66e0;
            }
        L_002f66dc:
            charge(ctx, 1);
            v0 = 1;
        L_002f66e0:
            charge(ctx, 44);
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            s0 = sll(v0, 2);
            v0 = 0x6A0000;
            v0 = addiu(v0, -22896);  // &0x69A690
            s2 = addu(v0, s0);
            v0 = 0x6A0000;
            v0 = addiu(v0, -22832);  // &0x69A6D0
            a2 = addu(v0, s0);
            a0 = addiu(sp, 0x5C);
            a1 = s2;
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2F6718u, gen::fn_sub_2A4690_002a4690);
            lwc1(f2, s2, 0);
            lwc1(f1, s2, 4);
            lwc1(f0, s2, 8);
            swc1(f2, sp, 0x50);
            swc1(f1, sp, 0x54);
            swc1(f0, sp, 0x58);
            v0 = 0x6A0000;
            v0 = addiu(v0, -22864);  // &0x69A6B0
            s2 = addu(v0, s0);
            v0 = 0x6A0000;
            v0 = addiu(v0, -22800);  // &0x69A6F0
            a2 = addu(v0, s0);
            a0 = addiu(sp, 0x78);
            a1 = s2;
            a3 = 0x690000;
            a3 = addiu(a3, 30848);  // &0x697880
            jal(ctx, 0x2F6760u, gen::fn_sub_2A4690_002a4690);
            lwc1(f2, s2, 0);
            lwc1(f1, s2, 4);
            lwc1(f0, s2, 8);
            swc1(f2, sp, 0x6C);
            swc1(f1, sp, 0x70);
            swc1(f0, sp, 0x74);
            v0 = 0x40400000;
            mtc1(v0, f20);
            s2 = 0;
            s0 = 1;
            goto L_002f6790;
        }
    L_002f656c:
        charge(ctx, 39);
        a0 = addiu(sp, 0x5C);
        a1 = 0x6A0000;
        a1 = addiu(a1, -23032);  // &0x69A608
        a2 = 0x6A0000;
        a2 = addiu(a2, -23000);  // &0x69A628
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2F6588u, gen::fn_sub_2A4690_002a4690);
        v0 = 0x6A0000;
        ld(v1, v0, -23032);  // 0x69A608
        v0 = 0x6A0000;
        lwc1(f0, v0, -23024);  // 0x69A610
        sd(v1, sp, 0x50);
        swc1(f0, sp, 0x58);
        a0 = addiu(sp, 0x78);
        a1 = 0x6A0000;
        a1 = addiu(a1, -23016);  // &0x69A618
        a2 = 0x6A0000;
        a2 = addiu(a2, -22984);  // &0x69A638
        a3 = 0x690000;
        a3 = addiu(a3, 30848);  // &0x697880
        jal(ctx, 0x2F65C4u, gen::fn_sub_2A4690_002a4690);
        v0 = 0x6A0000;
        lwc1(f2, v0, -23016);  // 0x69A618
        v0 = 0x6A0000;
        lwc1(f1, v0, -23012);  // 0x69A61C
        v0 = 0x6A0000;
        lwc1(f0, v0, -23008);  // 0x69A620
        swc1(f2, sp, 0x6C);
        swc1(f1, sp, 0x70);
        swc1(f0, sp, 0x74);
        v0 = 0x40000000;
        mtc1(v0, f20);
        s2 = 1;
        s0 = s2;
    }
L_002f6790:
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x002f6798
        charge(ctx, 14);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        a0 = addiu(v0, 32);
        a1 = addiu(sp, 0x50);
        a2 = addiu(sp, 0x6C);
        a3 = 1;
        jal(ctx, 0x2F67ACu, gen::fn_sub_2A2290_002a2290);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        a0 = addiu(v0, 32);
        mov_s(f12, f20);
        jal(ctx, 0x2F67C0u, gen::fn_sub_2A3110_002a3110);
        if (s2 == 0) {
            // 0x002f67f4
            charge(ctx, 7);
            mtc1(zero, f12);
            lw(a0, s1, 224);
            a1 = 0;
            a2 = 0;
            a3 = 1;
            jal(ctx, 0x2F6808u, gen::fn_sub_2A3E80_002a3e80);
        } else {
            // 0x002f67d0
            charge(ctx, 9);
            mtc1(zero, f12);
            lw(a0, s1, 224);
            a1 = 0;
            a2 = 0;
            a3 = 64;
            jal(ctx, 0x2F67E4u, gen::fn_sub_2A3E80_002a3e80);
        }
    }
    // 0x002f6810 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v1 = si(-1);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    sw(v1, v0, b9::kBoss2908);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x002F6840 sub_2F6840 -- 624 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btl436EnemyScene] Encounter 436's scene ($a0 the action): clears gBtl flag 0x2000000, pauses the order; binds BED 2
// (gBtl +2892 > 0) or 3; sub_2B8D60(1, 4095), the shot, the unit effects 0 / 1; with BED 3 arms enemy 242's fade (+2896
// = 0, countdown 30, length 4, frame 0), sub_2DD760(3, sub_2F8810(30, 242), 4) (delay 30) and, once (flag 5631:
// MT_Misc_BitChk / sub_395170), sub_2DB890 / sub_2DB800(32, 478); frees the handle.
void sub_2F6840(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f6840
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlFlags);
    v0 = lui(0xFDFF);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, a1, bcore::kBtlFlags);
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlFlags);
    v0 = 0x80000;
    v0 = v1 | v0;
    sw(v0, a1, bcore::kBtlFlags);
    lw(s2, a0, bcore::kActUnit);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(v0, v0, b9::kBoss2892);
    if (i64(v0) <= 0) {
        // 0x002f68a8
        charge(ctx, 1);
        s0 = 3;
    } else {
        // 0x002f689c
        charge(ctx, 3);
        s0 = 2;
    }
    // 0x002f68ac
    charge(ctx, 60);
    a0 = 0;
    jal(ctx, 0x2F68B0u, gen::fn_sub_2B8F90_002b8f90);
    s1 = v0;
    a0 = s0 & 0xFFFF;
    jal(ctx, 0x2F68C0u, gen::fn_sub_2F87E0_002f87e0);
    a0 = s1;
    a1 = v0;
    jal(ctx, 0x2F68D0u, gen::fn_sub_2B90D0_002b90d0);
    a0 = 1;
    a1 = 4095;
    jal(ctx, 0x2F68E0u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 1;
    jal(ctx, 0x2F68F8u, gen::fn_sub_27ED20_0027ed20);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x2F6908u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 0;
    jal(ctx, 0x2F6920u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 0;
    t0 = 512;
    jal(ctx, 0x2F693Cu, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 2;
    jal(ctx, 0x2F6954u, gen::fn_sub_27ED20_0027ed20);
    a0 = s1;
    a1 = s2;
    a2 = s2;
    a3 = 1;
    t0 = 512;
    jal(ctx, 0x2F6970u, gen::fn_sub_2BAF90_002baf90);
    a0 = v0;
    ld(v1, s3, 0);
    sd(v1, v0, bcore::kPktOwner);
    a1 = 2;
    jal(ctx, 0x2F6988u, gen::fn_sub_27ED20_0027ed20);
    v0 = 3;
    if (s0 == v0) {
        // 0x002f699c
        charge(ctx, 7);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(a2, v0, b9::kBtlEnemyTail);
        a0 = 30;
        v1 = 4;
        a1 = 242;
        for (;;) {
            // 0x002f69e8
            charge(ctx, 2);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002f69b8
            charge(ctx, 3);
            lhu(v0, a2, bcore::kUnId);
            if (v0 == a1) {
                // 0x002f69c4
                charge(ctx, 8);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                sw(zero, v0, b9::kBoss2896);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                sh(a0, v0, b9::kBoss2900);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                sh(v1, v0, b9::kBoss2902);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                sh(zero, v0, b9::kBoss2904);
            }
            // 0x002f69e4
            charge(ctx, 1);
            lw(a2, a2, bcore::kUnPrev);
        }
        // 0x002f69f0
        charge(ctx, 18);
        jal(ctx, 0x2F69F0u, gen::fn_sub_2F8810_002f8810);
        a0 = 3;
        a1 = v0;
        a2 = 4;
        jal(ctx, 0x2F6A04u, gen::fn_sub_2DD760_002dd760);
        a0 = v0;
        v1 = 30;
        sh(v1, v0, bcore::kPktStartDelay);
        a1 = 1;
        jal(ctx, 0x2F6A1Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 5631;
        jal(ctx, 0x2F6A28u, gen::fn_MT_Misc_BitChk_003951d0);
        if (v0 == 0) {
            // 0x002f6a38
            charge(ctx, 19);
            a0 = 5631;
            jal(ctx, 0x2F6A3Cu, gen::fn_sub_395170_00395170);
            jal(ctx, 0x2F6A44u, gen::fn_sub_2DB890_002db890);
            a0 = v0;
            sh(zero, v0, bcore::kPktStartDelay);
            a1 = 1;
            jal(ctx, 0x2F6A58u, gen::fn_sub_27ED20_0027ed20);
            a0 = 32;
            a1 = 478;
            jal(ctx, 0x2F6A68u, gen::fn_sub_2DB800_002db800);
            a0 = v0;
            sh(zero, v0, bcore::kPktStartDelay);
            a1 = 1;
            jal(ctx, 0x2F6A7Cu, gen::fn_sub_27ED20_0027ed20);
        }
    }
    // 0x002f6a84
    charge(ctx, 11);
    a0 = s1;
    jal(ctx, 0x2F6A88u, gen::fn_sub_2B9030_002b9030);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002F6AB0 sub_2F6AB0 -- 260 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btl436EnemyDone] The scene's done callback: 1 while packets remain; then gBtl +2888 = 0, the DatUnit flag 0x40
// cleared, resumes the order, sets gBtl flag 0x2000000 and queues the three closing packets; 0.
void sub_2F6AB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f6ab0
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
    jal(ctx, 0x2F6AE0u, gen::fn_sub_27E390_0027e390);
    if (v0 != 0) {
        // 0x002f6b9c
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x002f6af0
        charge(ctx, 43);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        sw(zero, v0, b9::kBoss2888);
        lw(v0, s0, bcore::kActUnit);
        lw(v1, v0, bcore::kUnDat);
        lhu(v0, v1, 0);
        v0 = v0 & 0xFFBF;
        sh(v0, v1, 0);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = lui(0xFFF7);
        v0 = v0 | 0xFFFF;
        v0 = v1 & v0;
        sw(v0, a0, bcore::kBtlFlags);
        lw(a0, gp, bcore::kGpBtl);  // gBtl
        lw(v1, a0, bcore::kBtlFlags);
        v0 = 0x2000000;
        v0 = v1 | v0;
        sw(v0, a0, bcore::kBtlFlags);
        a0 = 16;
        jal(ctx, 0x2F6B3Cu, gen::fn_sub_29FA50_0029fa50);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F6B4Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        a1 = 4;
        jal(ctx, 0x2F6B5Cu, gen::fn_sub_2A1080_002a1080);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F6B6Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = 16;
        jal(ctx, 0x2F6B78u, gen::fn_sub_2A16C0_002a16c0);
        a0 = v0;
        a1 = 1;
        jal(ctx, 0x2F6B88u, gen::fn_sub_27ED20_0027ed20);
        v0 = 0;
    }
    // 0x002f6ba0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F7DC0 sub_2F7DC0 -- 1688 bytes; frame 0x10: ra sp+0x0
// [btlBossBedBind] Binds the encounter's BED files (sub_2B8F90(2) + sub_2B96E0 with sub_2F87E0(n)) into gBtl +2884.. by
// the encounter (jump table 0x7B8C10): 423, 433..435: 4, 5, 6; 425..427, 431: 3, 4, 5; 428 / 429: 2; 430 / 432: 3, 4,
// 5, 6 (+2896 too); 436: 5; 424 clears +2896 / +2900.
void sub_2F7DC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f7dc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlSetupEnemies);
    lhu(v1, v1, 8);
    v1 = addiu(v1, -423);
    at = sltiu(v1, 14);
    if (at != 0) {
        // 0x002f7de4
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -29680);  // &0x7B8C10
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2F7E00u:  // table[0]
            // 0x002f7e00
            charge(ctx, 41);
            a0 = 2;
            jal(ctx, 0x2F7E04u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 4;
            jal(ctx, 0x2F7E18u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F7E2Cu, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F7E38u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 5;
            jal(ctx, 0x2F7E4Cu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F7E60u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F7E6Cu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 6;
            jal(ctx, 0x2F7E80u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F7E94u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F7EA4u:  // table[1]
            // 0x002f7ea4
            charge(ctx, 5);
            sh(zero, a1, 2896);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2900);
            break;
        case 0x2F7EB8u:  // table[2]
            // 0x002f7eb8
            charge(ctx, 41);
            a0 = 2;
            jal(ctx, 0x2F7EBCu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 3;
            jal(ctx, 0x2F7ED0u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F7EE4u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F7EF0u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 4;
            jal(ctx, 0x2F7F04u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F7F18u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F7F24u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 5;
            jal(ctx, 0x2F7F38u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F7F4Cu, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F7F5Cu:  // table[3]
            // 0x002f7f5c
            charge(ctx, 41);
            a0 = 2;
            jal(ctx, 0x2F7F60u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 3;
            jal(ctx, 0x2F7F74u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F7F88u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F7F94u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 4;
            jal(ctx, 0x2F7FA8u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F7FBCu, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F7FC8u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 5;
            jal(ctx, 0x2F7FDCu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F7FF0u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F8000u:  // table[4]
            // 0x002f8000
            charge(ctx, 41);
            a0 = 2;
            jal(ctx, 0x2F8004u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 3;
            jal(ctx, 0x2F8018u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F802Cu, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F8038u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 4;
            jal(ctx, 0x2F804Cu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F8060u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F806Cu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 5;
            jal(ctx, 0x2F8080u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F8094u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F80A4u:  // table[5]
            // 0x002f80a4
            charge(ctx, 15);
            a0 = 2;
            jal(ctx, 0x2F80A8u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 2;
            jal(ctx, 0x2F80BCu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F80D0u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F80E0u:  // table[6]
            // 0x002f80e0
            charge(ctx, 15);
            a0 = 2;
            jal(ctx, 0x2F80E4u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 2;
            jal(ctx, 0x2F80F8u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F810Cu, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F811Cu:  // table[7]
            // 0x002f811c
            charge(ctx, 54);
            a0 = 2;
            jal(ctx, 0x2F8120u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 3;
            jal(ctx, 0x2F8134u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F8148u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F8154u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 4;
            jal(ctx, 0x2F8168u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F817Cu, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F8188u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 5;
            jal(ctx, 0x2F819Cu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F81B0u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F81BCu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2896);
            a0 = 6;
            jal(ctx, 0x2F81D0u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2896);
            a1 = v0;
            jal(ctx, 0x2F81E4u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F81F4u:  // table[8]
            // 0x002f81f4
            charge(ctx, 41);
            a0 = 2;
            jal(ctx, 0x2F81F8u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 3;
            jal(ctx, 0x2F820Cu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F8220u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F822Cu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 4;
            jal(ctx, 0x2F8240u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F8254u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F8260u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 5;
            jal(ctx, 0x2F8274u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F8288u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F8298u:  // table[9]
            // 0x002f8298
            charge(ctx, 54);
            a0 = 2;
            jal(ctx, 0x2F829Cu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 3;
            jal(ctx, 0x2F82B0u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F82C4u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F82D0u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 4;
            jal(ctx, 0x2F82E4u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F82F8u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F8304u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 5;
            jal(ctx, 0x2F8318u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F832Cu, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F8338u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2896);
            a0 = 6;
            jal(ctx, 0x2F834Cu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2896);
            a1 = v0;
            jal(ctx, 0x2F8360u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F8370u:  // table[10, 11, 12]
            // 0x002f8370
            charge(ctx, 41);
            a0 = 2;
            jal(ctx, 0x2F8374u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 4;
            jal(ctx, 0x2F8388u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F839Cu, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F83A8u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2888);
            a0 = 5;
            jal(ctx, 0x2F83BCu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2888);
            a1 = v0;
            jal(ctx, 0x2F83D0u, gen::fn_sub_2B96E0_002b96e0);
            a0 = 2;
            jal(ctx, 0x2F83DCu, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2892);
            a0 = 6;
            jal(ctx, 0x2F83F0u, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2892);
            a1 = v0;
            jal(ctx, 0x2F8404u, gen::fn_sub_2B96E0_002b96e0);
            break;
        case 0x2F8414u:  // table[13]
            // 0x002f8414
            charge(ctx, 13);
            a0 = 2;
            jal(ctx, 0x2F8418u, gen::fn_sub_2B8F90_002b8f90);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(v0, v1, b9::kBoss2884);
            a0 = 5;
            jal(ctx, 0x2F842Cu, gen::fn_sub_2F87E0_002f87e0);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v1, b9::kBoss2884);
            a1 = v0;
            jal(ctx, 0x2F8440u, gen::fn_sub_2B96E0_002b96e0);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002f8448 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F8460 sub_2F8460 -- 812 bytes; frame 0x10: ra sp+0x0
// [btlBossBedFree] Frees the handles sub_2F7DC0 bound (sub_2B9030) and zeroes their words, by the encounter (jump table
// 0x7B8C50).
void sub_2F8460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f8460
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, gp, bcore::kGpBtl);  // gBtl
    lw(v1, a1, bcore::kBtlSetupEnemies);
    lhu(v1, v1, 8);
    v1 = addiu(v1, -423);
    at = sltiu(v1, 14);
    if (at != 0) {
        // 0x002f8484
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -29616);  // &0x7B8C50
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x2F84A0u:  // table[0]
            // 0x002f84a0
            charge(ctx, 19);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F84A4u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F84BCu, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F84D4u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2892);
            break;
        case 0x2F84ECu:  // table[2]
            // 0x002f84ec
            charge(ctx, 19);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F84F0u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F8508u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F8520u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2892);
            break;
        case 0x2F8538u:  // table[3]
            // 0x002f8538
            charge(ctx, 19);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F853Cu, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F8554u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F856Cu, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2892);
            break;
        case 0x2F8584u:  // table[4]
            // 0x002f8584
            charge(ctx, 19);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F8588u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F85A0u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F85B8u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2892);
            break;
        case 0x2F85D0u:  // table[5]
            // 0x002f85d0
            charge(ctx, 7);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F85D4u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2884);
            break;
        case 0x2F85ECu:  // table[6]
            // 0x002f85ec
            charge(ctx, 7);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F85F0u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2884);
            break;
        case 0x2F8608u:  // table[7]
            // 0x002f8608
            charge(ctx, 25);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F860Cu, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F8624u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F863Cu, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2892);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2896);
            jal(ctx, 0x2F8654u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2896);
            break;
        case 0x2F866Cu:  // table[8]
            // 0x002f866c
            charge(ctx, 19);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F8670u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F8688u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F86A0u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2892);
            break;
        case 0x2F86B8u:  // table[9]
            // 0x002f86b8
            charge(ctx, 25);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F86BCu, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F86D4u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F86ECu, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2892);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2896);
            jal(ctx, 0x2F8704u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2896);
            break;
        case 0x2F871Cu:  // table[10, 11, 12]
            // 0x002f871c
            charge(ctx, 19);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F8720u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2884);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2888);
            jal(ctx, 0x2F8738u, gen::fn_sub_2B9030_002b9030);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v0, b9::kBoss2888);
            lw(v0, gp, bcore::kGpBtl);  // gBtl
            lw(a0, v0, b9::kBoss2892);
            jal(ctx, 0x2F8750u, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2892);
            break;
        case 0x2F8768u:  // table[13]
            // 0x002f8768
            charge(ctx, 5);
            lw(a0, a1, 2884);
            jal(ctx, 0x2F876Cu, gen::fn_sub_2B9030_002b9030);
            lw(v1, gp, bcore::kGpBtl);  // gBtl
            sw(zero, v1, b9::kBoss2884);
            break;
        case 0x2F877Cu:  // table[1]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x002f877c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002F88C0 sub_2F88C0 -- 376 bytes; frame 0x10: ra sp+0x0
// [btlBossTurnQuery] The encounter's turn query: 424: gBtl +2900 == 1; 422: sub_2ECAC0() != 1; 420: an enemy 261 / 262
// with unit flag 0x8 before any 277 with it; 416: an enemy 275 / 276 is present; otherwise 0.
void sub_2F88C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f88c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, bcore::kGpBtl);  // gBtl
    lw(v0, a0, bcore::kBtlSetupEnemies);
    lhu(v1, v0, 8);
    v0 = 424;
    if (v1 == v0) {
        // 0x002f8a10
        charge(ctx, 5);
        lw(v0, a0, 2900);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x002f88e0
        charge(ctx, 3);
        v0 = 422;
        if (v1 == v0) {
            // 0x002f89f8
            charge(ctx, 6);
            jal(ctx, 0x2F89F8u, gen::fn_sub_2ECAC0_002ecac0);
            v0 = v0 ^ 0x1;
            v0 = sltu(0, v0);
        } else {
            // 0x002f88ec
            charge(ctx, 3);
            v0 = 420;
            if (v1 == v0) {
                // 0x002f896c
                charge(ctx, 6);
                lw(a2, a0, 344);
                v1 = 277;
                a0 = 261;
                a1 = 262;
                for (;;) {
                    // 0x002f89e4
                    charge(ctx, 2);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002f8984
                    charge(ctx, 3);
                    lhu(v0, a2, bcore::kUnId);
                    if (v0 != a1) {
                        // 0x002f8990
                        charge(ctx, 2);
                        if (v0 == a0) {
                            goto L_002f89c4;
                        }
                        // 0x002f8998
                        charge(ctx, 2);
                        if (v0 != v1) {
                            // 0x002f89a0
                            charge(ctx, 2);
                            goto L_002f89e0;
                        }
                        // 0x002f89a8
                        charge(ctx, 4);
                        lw(v0, a2, bcore::kUnFlags);
                        v0 = v0 & 0x8;
                        if (v0 != 0) {
                            goto L_002f89b8_21;
                        }
                    L_002f89e0:
                        charge(ctx, 1);
                        lw(a2, a2, bcore::kUnPrev);
                        continue;
                    }
                L_002f89c4:
                    charge(ctx, 4);
                    lw(v0, a2, bcore::kUnFlags);
                    v0 = v0 & 0x8;
                    if (v0 == 0) {
                        goto L_002f89e0;
                    }
                    goto L_002f89d4_23;
                }
                // 0x002f89ec
                charge(ctx, 1);
                v0 = 0;
            L_002f89f0:
                charge(ctx, 2);
            } else {
                // 0x002f88f8
                charge(ctx, 3);
                v0 = 416;
                if (v1 == v0) {
                    // 0x002f890c
                    charge(ctx, 6);
                    lw(a2, a0, 344);
                    a0 = 276;
                    v1 = 275;
                    v0 = 256;
                    for (;;) {
                        // 0x002f8958
                        charge(ctx, 2);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x002f8924
                        charge(ctx, 3);
                        lhu(a1, a2, bcore::kUnId);
                        if (a1 == a0) {
                            goto L_002f8948;
                        }
                        // 0x002f8930
                        charge(ctx, 2);
                        if (a1 == v1) {
                            goto L_002f8948;
                        }
                        // 0x002f8938
                        charge(ctx, 2);
                        if (a1 != v0) {
                            // 0x002f8940
                            charge(ctx, 2);
                        }
                        // 0x002f8954
                        charge(ctx, 1);
                        lw(a2, a2, bcore::kUnPrev);
                    }
                    // 0x002f8960
                    charge(ctx, 1);
                    v0 = 0;
                L_002f8964:
                    charge(ctx, 2);
                } else {
                    // 0x002f8904
                    charge(ctx, 2);
                    // 0x002f8a24
                    charge(ctx, 1);
                    v0 = 0;
                }
            }
        }
    }
    // 0x002f8a28 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    return;
L_002f8948:
    charge(ctx, 3);
    v0 = 1;
    goto L_002f8964;
L_002f89b8_21:
    charge(ctx, 3);
    v0 = 0;
    goto L_002f89f0;
L_002f89d4_23:
    charge(ctx, 3);
    v0 = 1;
    goto L_002f89f0;
}

// 0x002F8A40 sub_2F8A40 -- 1112 bytes; leaf frame (no stack)
// [btlIsBossUnit] Whether the unit $a0 is the encounter's boss (jump table by the encounter): 436 / 428 any enemy; 429:
// 274; 424: 269; 422: 266; 421: 263; 420: 261 / 262 / 277; 419: 260; 418: 259; 417: 257 / 258; 416: 256; otherwise 0.
void sub_2F8A40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x002f8a40
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(v0, v0, bcore::kBtlSetupEnemies);
    lhu(v0, v0, 8);
    v1 = 436;
    if (v0 == v1) {
        // 0x002f8e78
        charge(ctx, 5);
        lbu(v0, a0, bcore::kUnSide);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x002f8a58
        charge(ctx, 3);
        v1 = 435;
        if (v0 != v1) {
            // 0x002f8a64
            charge(ctx, 3);
            v1 = 434;
            if (v0 == v1) {
                goto L_002f8e6c;
            }
            // 0x002f8a70
            charge(ctx, 3);
            v1 = 433;
            if (v0 == v1) {
                goto L_002f8e6c;
            }
            // 0x002f8a7c
            charge(ctx, 3);
            v1 = 432;
            if (v0 == v1) {
                goto L_002f8e6c;
            }
            // 0x002f8a88
            charge(ctx, 3);
            v1 = 431;
            if (v0 == v1) {
                goto L_002f8e6c;
            }
            // 0x002f8a94
            charge(ctx, 3);
            v1 = 430;
            if (v0 == v1) {
                // 0x002f8e60
                charge(ctx, 3);
                v0 = 0;
            } else {
                // 0x002f8aa0
                charge(ctx, 3);
                v1 = 429;
                if (v0 == v1) {
                    // 0x002f8e18
                    charge(ctx, 4);
                    lbu(v1, a0, bcore::kUnSide);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x002f8e34
                        charge(ctx, 4);
                        lhu(a0, a0, bcore::kUnId);
                        v1 = 274;
                        if (a0 == v1) {
                            // 0x002f8e4c
                            charge(ctx, 2);
                        } else {
                            // 0x002f8e44
                            charge(ctx, 2);
                            // 0x002f8e54
                            charge(ctx, 1);
                            v0 = 0;
                        }
                    } else {
                        // 0x002f8e28
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002f8e58
                    charge(ctx, 2);
                } else {
                    // 0x002f8aac
                    charge(ctx, 3);
                    v1 = 428;
                    if (v0 == v1) {
                        // 0x002f8e04
                        charge(ctx, 5);
                        lbu(v0, a0, bcore::kUnSide);
                        v0 = v0 ^ 0x1;
                        v0 = sltiu(v0, 1);
                    } else {
                        // 0x002f8ab8
                        charge(ctx, 3);
                        v1 = 427;
                        if (v0 == v1) {
                            // 0x002f8df8
                            charge(ctx, 3);
                            v0 = 0;
                        } else {
                            // 0x002f8ac4
                            charge(ctx, 3);
                            v1 = 426;
                            if (v0 == v1) {
                                // 0x002f8dec
                                charge(ctx, 3);
                                v0 = 0;
                            } else {
                                // 0x002f8ad0
                                charge(ctx, 3);
                                v1 = 425;
                                if (v0 == v1) {
                                    // 0x002f8de0
                                    charge(ctx, 3);
                                    v0 = 0;
                                } else {
                                    // 0x002f8adc
                                    charge(ctx, 3);
                                    v1 = 424;
                                    if (v0 == v1) {
                                        // 0x002f8d98
                                        charge(ctx, 4);
                                        lbu(v1, a0, bcore::kUnSide);
                                        v0 = 1;
                                        if (v1 == v0) {
                                            // 0x002f8db4
                                            charge(ctx, 4);
                                            lhu(a0, a0, bcore::kUnId);
                                            v1 = 269;
                                            if (a0 == v1) {
                                                // 0x002f8dcc
                                                charge(ctx, 2);
                                            } else {
                                                // 0x002f8dc4
                                                charge(ctx, 2);
                                                // 0x002f8dd4
                                                charge(ctx, 1);
                                                v0 = 0;
                                            }
                                        } else {
                                            // 0x002f8da8
                                            charge(ctx, 3);
                                            v0 = 0;
                                        }
                                        // 0x002f8dd8
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002f8ae8
                                        charge(ctx, 3);
                                        v1 = 423;
                                        if (v0 == v1) {
                                            // 0x002f8d8c
                                            charge(ctx, 3);
                                            v0 = 0;
                                        } else {
                                            // 0x002f8af4
                                            charge(ctx, 3);
                                            v1 = 422;
                                            if (v0 == v1) {
                                                // 0x002f8d44
                                                charge(ctx, 4);
                                                lbu(v1, a0, bcore::kUnSide);
                                                v0 = 1;
                                                if (v1 == v0) {
                                                    // 0x002f8d60
                                                    charge(ctx, 4);
                                                    lhu(a0, a0, bcore::kUnId);
                                                    v1 = 266;
                                                    if (a0 == v1) {
                                                        // 0x002f8d78
                                                        charge(ctx, 2);
                                                    } else {
                                                        // 0x002f8d70
                                                        charge(ctx, 2);
                                                        // 0x002f8d80
                                                        charge(ctx, 1);
                                                        v0 = 0;
                                                    }
                                                } else {
                                                    // 0x002f8d54
                                                    charge(ctx, 3);
                                                    v0 = 0;
                                                }
                                                // 0x002f8d84
                                                charge(ctx, 2);
                                            } else {
                                                // 0x002f8b00
                                                charge(ctx, 3);
                                                v1 = 421;
                                                if (v0 == v1) {
                                                    // 0x002f8cfc
                                                    charge(ctx, 4);
                                                    lbu(v1, a0, bcore::kUnSide);
                                                    v0 = 1;
                                                    if (v1 == v0) {
                                                        // 0x002f8d18
                                                        charge(ctx, 4);
                                                        lhu(a0, a0, bcore::kUnId);
                                                        v1 = 263;
                                                        if (a0 == v1) {
                                                            // 0x002f8d30
                                                            charge(ctx, 2);
                                                        } else {
                                                            // 0x002f8d28
                                                            charge(ctx, 2);
                                                            // 0x002f8d38
                                                            charge(ctx, 1);
                                                            v0 = 0;
                                                        }
                                                    } else {
                                                        // 0x002f8d0c
                                                        charge(ctx, 3);
                                                        v0 = 0;
                                                    }
                                                    // 0x002f8d3c
                                                    charge(ctx, 2);
                                                } else {
                                                    // 0x002f8b0c
                                                    charge(ctx, 3);
                                                    v1 = 420;
                                                    if (v0 == v1) {
                                                        // 0x002f8c98
                                                        charge(ctx, 4);
                                                        lbu(v1, a0, bcore::kUnSide);
                                                        v0 = 1;
                                                        if (v1 == v0) {
                                                            // 0x002f8cb4
                                                            charge(ctx, 4);
                                                            lhu(v1, a0, bcore::kUnId);
                                                            v0 = 262;
                                                            if (v1 != v0) {
                                                                // 0x002f8cc4
                                                                charge(ctx, 3);
                                                                v0 = 261;
                                                                if (v1 == v0) {
                                                                    goto L_002f8ce4;
                                                                }
                                                                // 0x002f8cd0
                                                                charge(ctx, 3);
                                                                v0 = 277;
                                                                if (v1 == v0) {
                                                                    goto L_002f8ce4;
                                                                }
                                                                // 0x002f8cdc
                                                                charge(ctx, 2);
                                                                // 0x002f8cf0
                                                                charge(ctx, 1);
                                                                v0 = 0;
                                                                goto L_002f8cf4;
                                                            }
                                                        L_002f8ce4:
                                                            charge(ctx, 3);
                                                            v0 = 1;
                                                        } else {
                                                            // 0x002f8ca8
                                                            charge(ctx, 3);
                                                            v0 = 0;
                                                        }
                                                    L_002f8cf4:
                                                        charge(ctx, 2);
                                                    } else {
                                                        // 0x002f8b18
                                                        charge(ctx, 3);
                                                        v1 = 419;
                                                        if (v0 == v1) {
                                                            // 0x002f8c50
                                                            charge(ctx, 4);
                                                            lbu(v1, a0, bcore::kUnSide);
                                                            v0 = 1;
                                                            if (v1 == v0) {
                                                                // 0x002f8c6c
                                                                charge(ctx, 4);
                                                                lhu(a0, a0, bcore::kUnId);
                                                                v1 = 260;
                                                                if (a0 == v1) {
                                                                    // 0x002f8c84
                                                                    charge(ctx, 2);
                                                                } else {
                                                                    // 0x002f8c7c
                                                                    charge(ctx, 2);
                                                                    // 0x002f8c8c
                                                                    charge(ctx, 1);
                                                                    v0 = 0;
                                                                }
                                                            } else {
                                                                // 0x002f8c60
                                                                charge(ctx, 3);
                                                                v0 = 0;
                                                            }
                                                            // 0x002f8c90
                                                            charge(ctx, 2);
                                                        } else {
                                                            // 0x002f8b24
                                                            charge(ctx, 3);
                                                            v1 = 418;
                                                            if (v0 == v1) {
                                                                // 0x002f8c08
                                                                charge(ctx, 4);
                                                                lbu(v1, a0, bcore::kUnSide);
                                                                v0 = 1;
                                                                if (v1 == v0) {
                                                                    // 0x002f8c24
                                                                    charge(ctx, 4);
                                                                    lhu(a0, a0, bcore::kUnId);
                                                                    v1 = 259;
                                                                    if (a0 == v1) {
                                                                        // 0x002f8c3c
                                                                        charge(ctx, 2);
                                                                    } else {
                                                                        // 0x002f8c34
                                                                        charge(ctx, 2);
                                                                        // 0x002f8c44
                                                                        charge(ctx, 1);
                                                                        v0 = 0;
                                                                    }
                                                                } else {
                                                                    // 0x002f8c18
                                                                    charge(ctx, 3);
                                                                    v0 = 0;
                                                                }
                                                                // 0x002f8c48
                                                                charge(ctx, 2);
                                                            } else {
                                                                // 0x002f8b30
                                                                charge(ctx, 3);
                                                                v1 = 417;
                                                                if (v0 == v1) {
                                                                    // 0x002f8bb0
                                                                    charge(ctx, 4);
                                                                    lbu(v1, a0, bcore::kUnSide);
                                                                    v0 = 1;
                                                                    if (v1 == v0) {
                                                                        // 0x002f8bcc
                                                                        charge(ctx, 4);
                                                                        lhu(v1, a0, bcore::kUnId);
                                                                        v0 = 258;
                                                                        if (v1 != v0) {
                                                                            // 0x002f8bdc
                                                                            charge(ctx, 3);
                                                                            v0 = 257;
                                                                            if (v1 == v0) {
                                                                                goto L_002f8bf0;
                                                                            }
                                                                            // 0x002f8be8
                                                                            charge(ctx, 2);
                                                                            // 0x002f8bfc
                                                                            charge(ctx, 1);
                                                                            v0 = 0;
                                                                            goto L_002f8c00;
                                                                        }
                                                                    L_002f8bf0:
                                                                        charge(ctx, 3);
                                                                        v0 = 1;
                                                                    } else {
                                                                        // 0x002f8bc0
                                                                        charge(ctx, 3);
                                                                        v0 = 0;
                                                                    }
                                                                L_002f8c00:
                                                                    charge(ctx, 2);
                                                                } else {
                                                                    // 0x002f8b3c
                                                                    charge(ctx, 3);
                                                                    v1 = 416;
                                                                    if (v0 == v1) {
                                                                        // 0x002f8b68
                                                                        charge(ctx, 4);
                                                                        lbu(v1, a0, bcore::kUnSide);
                                                                        v0 = 1;
                                                                        if (v1 == v0) {
                                                                            // 0x002f8b84
                                                                            charge(ctx, 4);
                                                                            lhu(a0, a0, bcore::kUnId);
                                                                            v1 = 256;
                                                                            if (a0 == v1) {
                                                                                // 0x002f8b9c
                                                                                charge(ctx, 2);
                                                                            } else {
                                                                                // 0x002f8b94
                                                                                charge(ctx, 2);
                                                                                // 0x002f8ba4
                                                                                charge(ctx, 1);
                                                                                v0 = 0;
                                                                            }
                                                                        } else {
                                                                            // 0x002f8b78
                                                                            charge(ctx, 3);
                                                                            v0 = 0;
                                                                        }
                                                                        // 0x002f8ba8
                                                                        charge(ctx, 2);
                                                                    } else {
                                                                        // 0x002f8b48
                                                                        charge(ctx, 3);
                                                                        v1 = 456;
                                                                        if (v0 == v1) {
                                                                            // 0x002f8b5c
                                                                            charge(ctx, 3);
                                                                            v0 = 0;
                                                                        } else {
                                                                            // 0x002f8b54
                                                                            charge(ctx, 2);
                                                                            // 0x002f8e8c
                                                                            charge(ctx, 1);
                                                                            v0 = 0;
                                                                        }
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // 0x002f8e90 (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
    L_002f8e6c:
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002f8e90 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002FAC80 sub_2FAC80 -- 52 bytes; frame 0x10: ra sp+0x0
// [btlBossUnitCreate] The UNIT_CREATE hook: sub_29A690(0), then sub_29A470(the hero's action).
void sub_2FAC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fac80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2FAC8Cu, gen::fn_sub_29A690_0029a690);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(a0, v0, bcore::kBtlPlayerAction);
    jal(ctx, 0x2FAC9Cu, gen::fn_sub_29A470_0029a470);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FACC0 sub_2FACC0 -- 2500 bytes; frame 0x60: ra sp+0x10, s0 sp+0x0 (sq)
// [btlBossStart] The START hook: for most boss encounters the boss archive's file 1 (file 0 for 456;
// H_Cdvd_ArchiveGetFile on gBtl +2836) bound to a handle and played as a unit effect on the hero, returning 1 (0 for
// 425..427); 424 / 422 / 417 / 416 call sub_2EF670 / sub_2EC790 / sub_2E9AC0 / sub_2E9450; others 0.
void sub_2FACC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002facc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(v0, v0, bcore::kBtlSetupEnemies);
    lhu(v0, v0, 8);
    v1 = 436;
    if (v0 == v1) {
        // 0x002fb5e8
        charge(ctx, 33);
        a0 = 0;
        jal(ctx, 0x2FB5ECu, gen::fn_sub_2B8F90_002b8f90);
        s0 = v0;
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(a0, v0, b9::kBtlBossArchive);
        a1 = 1;
        a2 = addiu(sp, 0x20);
        jal(ctx, 0x2FB608u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x2FB618u, gen::fn_sub_2B90D0_002b90d0);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(v0, v0, bcore::kBtlPlayerAction);
        lw(a1, v0, bcore::kActUnit);
        a0 = s0;
        a2 = a1;
        a3 = 0;
        t0 = 512;
        jal(ctx, 0x2FB63Cu, gen::fn_sub_2BAF90_002baf90);
        a0 = v0;
        a1 = 2;
        jal(ctx, 0x2FB64Cu, gen::fn_sub_27ED20_0027ed20);
        a0 = s0;
        jal(ctx, 0x2FB658u, gen::fn_sub_2B9030_002b9030);
        v0 = 1;
    } else {
        // 0x002face4
        charge(ctx, 3);
        v1 = 435;
        if (v0 != v1) {
            // 0x002facf0
            charge(ctx, 3);
            v1 = 434;
            if (v0 == v1) {
                goto L_002fb564;
            }
            // 0x002facfc
            charge(ctx, 3);
            v1 = 433;
            if (v0 == v1) {
                goto L_002fb564;
            }
            // 0x002fad08
            charge(ctx, 3);
            v1 = 432;
            if (v0 == v1) {
                // 0x002fb4e0
                charge(ctx, 33);
                a0 = 0;
                jal(ctx, 0x2FB4E4u, gen::fn_sub_2B8F90_002b8f90);
                s0 = v0;
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                lw(a0, v0, b9::kBtlBossArchive);
                a1 = 1;
                a2 = addiu(sp, 0x28);
                jal(ctx, 0x2FB500u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                a0 = s0;
                a1 = v0;
                jal(ctx, 0x2FB510u, gen::fn_sub_2B90D0_002b90d0);
                lw(v0, gp, bcore::kGpBtl);  // gBtl
                lw(v0, v0, bcore::kBtlPlayerAction);
                lw(a1, v0, bcore::kActUnit);
                a0 = s0;
                a2 = a1;
                a3 = 0;
                t0 = 512;
                jal(ctx, 0x2FB534u, gen::fn_sub_2BAF90_002baf90);
                a0 = v0;
                a1 = 2;
                jal(ctx, 0x2FB544u, gen::fn_sub_27ED20_0027ed20);
                a0 = s0;
                jal(ctx, 0x2FB550u, gen::fn_sub_2B9030_002b9030);
                v0 = 1;
            } else {
                // 0x002fad14
                charge(ctx, 3);
                v1 = 431;
                if (v0 == v1) {
                    // 0x002fb45c
                    charge(ctx, 33);
                    a0 = 0;
                    jal(ctx, 0x2FB460u, gen::fn_sub_2B8F90_002b8f90);
                    s0 = v0;
                    lw(v0, gp, bcore::kGpBtl);  // gBtl
                    lw(a0, v0, b9::kBtlBossArchive);
                    a1 = 1;
                    a2 = addiu(sp, 0x2C);
                    jal(ctx, 0x2FB47Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = s0;
                    a1 = v0;
                    jal(ctx, 0x2FB48Cu, gen::fn_sub_2B90D0_002b90d0);
                    lw(v0, gp, bcore::kGpBtl);  // gBtl
                    lw(v0, v0, bcore::kBtlPlayerAction);
                    lw(a1, v0, bcore::kActUnit);
                    a0 = s0;
                    a2 = a1;
                    a3 = 0;
                    t0 = 512;
                    jal(ctx, 0x2FB4B0u, gen::fn_sub_2BAF90_002baf90);
                    a0 = v0;
                    a1 = 2;
                    jal(ctx, 0x2FB4C0u, gen::fn_sub_27ED20_0027ed20);
                    a0 = s0;
                    jal(ctx, 0x2FB4CCu, gen::fn_sub_2B9030_002b9030);
                    v0 = 1;
                } else {
                    // 0x002fad20
                    charge(ctx, 3);
                    v1 = 430;
                    if (v0 == v1) {
                        // 0x002fb3d8
                        charge(ctx, 33);
                        a0 = 0;
                        jal(ctx, 0x2FB3DCu, gen::fn_sub_2B8F90_002b8f90);
                        s0 = v0;
                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                        lw(a0, v0, b9::kBtlBossArchive);
                        a1 = 1;
                        a2 = addiu(sp, 0x30);
                        jal(ctx, 0x2FB3F8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = s0;
                        a1 = v0;
                        jal(ctx, 0x2FB408u, gen::fn_sub_2B90D0_002b90d0);
                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                        lw(v0, v0, bcore::kBtlPlayerAction);
                        lw(a1, v0, bcore::kActUnit);
                        a0 = s0;
                        a2 = a1;
                        a3 = 0;
                        t0 = 512;
                        jal(ctx, 0x2FB42Cu, gen::fn_sub_2BAF90_002baf90);
                        a0 = v0;
                        a1 = 2;
                        jal(ctx, 0x2FB43Cu, gen::fn_sub_27ED20_0027ed20);
                        a0 = s0;
                        jal(ctx, 0x2FB448u, gen::fn_sub_2B9030_002b9030);
                        v0 = 1;
                    } else {
                        // 0x002fad2c
                        charge(ctx, 3);
                        v1 = 429;
                        if (v0 == v1) {
                            // 0x002fb354
                            charge(ctx, 33);
                            a0 = 0;
                            jal(ctx, 0x2FB358u, gen::fn_sub_2B8F90_002b8f90);
                            s0 = v0;
                            lw(v0, gp, bcore::kGpBtl);  // gBtl
                            lw(a0, v0, b9::kBtlBossArchive);
                            a1 = 1;
                            a2 = addiu(sp, 0x34);
                            jal(ctx, 0x2FB374u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                            a0 = s0;
                            a1 = v0;
                            jal(ctx, 0x2FB384u, gen::fn_sub_2B90D0_002b90d0);
                            lw(v0, gp, bcore::kGpBtl);  // gBtl
                            lw(v0, v0, bcore::kBtlPlayerAction);
                            lw(a1, v0, bcore::kActUnit);
                            a0 = s0;
                            a2 = a1;
                            a3 = 0;
                            t0 = 512;
                            jal(ctx, 0x2FB3A8u, gen::fn_sub_2BAF90_002baf90);
                            a0 = v0;
                            a1 = 2;
                            jal(ctx, 0x2FB3B8u, gen::fn_sub_27ED20_0027ed20);
                            a0 = s0;
                            jal(ctx, 0x2FB3C4u, gen::fn_sub_2B9030_002b9030);
                            v0 = 1;
                        } else {
                            // 0x002fad38
                            charge(ctx, 3);
                            v1 = 428;
                            if (v0 == v1) {
                                // 0x002fb2d0
                                charge(ctx, 33);
                                a0 = 0;
                                jal(ctx, 0x2FB2D4u, gen::fn_sub_2B8F90_002b8f90);
                                s0 = v0;
                                lw(v0, gp, bcore::kGpBtl);  // gBtl
                                lw(a0, v0, b9::kBtlBossArchive);
                                a1 = 1;
                                a2 = addiu(sp, 0x38);
                                jal(ctx, 0x2FB2F0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                a0 = s0;
                                a1 = v0;
                                jal(ctx, 0x2FB300u, gen::fn_sub_2B90D0_002b90d0);
                                lw(v0, gp, bcore::kGpBtl);  // gBtl
                                lw(v0, v0, bcore::kBtlPlayerAction);
                                lw(a1, v0, bcore::kActUnit);
                                a0 = s0;
                                a2 = a1;
                                a3 = 0;
                                t0 = 512;
                                jal(ctx, 0x2FB324u, gen::fn_sub_2BAF90_002baf90);
                                a0 = v0;
                                a1 = 2;
                                jal(ctx, 0x2FB334u, gen::fn_sub_27ED20_0027ed20);
                                a0 = s0;
                                jal(ctx, 0x2FB340u, gen::fn_sub_2B9030_002b9030);
                                v0 = 1;
                            } else {
                                // 0x002fad44
                                charge(ctx, 3);
                                v1 = 427;
                                if (v0 == v1) {
                                    // 0x002fb250
                                    charge(ctx, 32);
                                    a0 = 0;
                                    jal(ctx, 0x2FB254u, gen::fn_sub_2B8F90_002b8f90);
                                    s0 = v0;
                                    lw(v0, gp, bcore::kGpBtl);  // gBtl
                                    lw(a0, v0, b9::kBtlBossArchive);
                                    a1 = 1;
                                    a2 = addiu(sp, 0x3C);
                                    jal(ctx, 0x2FB270u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                    a0 = s0;
                                    a1 = v0;
                                    jal(ctx, 0x2FB280u, gen::fn_sub_2B90D0_002b90d0);
                                    lw(v0, gp, bcore::kGpBtl);  // gBtl
                                    lw(v0, v0, bcore::kBtlPlayerAction);
                                    lw(a1, v0, bcore::kActUnit);
                                    a0 = s0;
                                    a2 = a1;
                                    a3 = 0;
                                    t0 = 512;
                                    jal(ctx, 0x2FB2A4u, gen::fn_sub_2BAF90_002baf90);
                                    a0 = v0;
                                    a1 = 2;
                                    jal(ctx, 0x2FB2B4u, gen::fn_sub_27ED20_0027ed20);
                                    a0 = s0;
                                    jal(ctx, 0x2FB2C0u, gen::fn_sub_2B9030_002b9030);
                                L_002fb66c:
                                    charge(ctx, 1);
                                    v0 = 0;
                                } else {
                                    // 0x002fad50
                                    charge(ctx, 3);
                                    v1 = 426;
                                    if (v0 == v1) {
                                        // 0x002fb1d0
                                        charge(ctx, 32);
                                        a0 = 0;
                                        jal(ctx, 0x2FB1D4u, gen::fn_sub_2B8F90_002b8f90);
                                        s0 = v0;
                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                        lw(a0, v0, b9::kBtlBossArchive);
                                        a1 = 1;
                                        a2 = addiu(sp, 0x40);
                                        jal(ctx, 0x2FB1F0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                        a0 = s0;
                                        a1 = v0;
                                        jal(ctx, 0x2FB200u, gen::fn_sub_2B90D0_002b90d0);
                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                        lw(v0, v0, bcore::kBtlPlayerAction);
                                        lw(a1, v0, bcore::kActUnit);
                                        a0 = s0;
                                        a2 = a1;
                                        a3 = 0;
                                        t0 = 512;
                                        jal(ctx, 0x2FB224u, gen::fn_sub_2BAF90_002baf90);
                                        a0 = v0;
                                        a1 = 2;
                                        jal(ctx, 0x2FB234u, gen::fn_sub_27ED20_0027ed20);
                                        a0 = s0;
                                        jal(ctx, 0x2FB240u, gen::fn_sub_2B9030_002b9030);
                                        goto L_002fb66c;
                                    }
                                    // 0x002fad5c
                                    charge(ctx, 3);
                                    v1 = 425;
                                    if (v0 == v1) {
                                        // 0x002fb150
                                        charge(ctx, 32);
                                        a0 = 0;
                                        jal(ctx, 0x2FB154u, gen::fn_sub_2B8F90_002b8f90);
                                        s0 = v0;
                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                        lw(a0, v0, b9::kBtlBossArchive);
                                        a1 = 1;
                                        a2 = addiu(sp, 0x44);
                                        jal(ctx, 0x2FB170u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                        a0 = s0;
                                        a1 = v0;
                                        jal(ctx, 0x2FB180u, gen::fn_sub_2B90D0_002b90d0);
                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                        lw(v0, v0, bcore::kBtlPlayerAction);
                                        lw(a1, v0, bcore::kActUnit);
                                        a0 = s0;
                                        a2 = a1;
                                        a3 = 0;
                                        t0 = 512;
                                        jal(ctx, 0x2FB1A4u, gen::fn_sub_2BAF90_002baf90);
                                        a0 = v0;
                                        a1 = 2;
                                        jal(ctx, 0x2FB1B4u, gen::fn_sub_27ED20_0027ed20);
                                        a0 = s0;
                                        jal(ctx, 0x2FB1C0u, gen::fn_sub_2B9030_002b9030);
                                        goto L_002fb66c;
                                    }
                                    // 0x002fad68
                                    charge(ctx, 3);
                                    v1 = 424;
                                    if (v0 == v1) {
                                        // 0x002fb13c
                                        charge(ctx, 5);
                                        jal(ctx, 0x2FB13Cu, gen::fn_sub_2EF670_002ef670);
                                        v0 = 1;
                                    } else {
                                        // 0x002fad74
                                        charge(ctx, 3);
                                        v1 = 423;
                                        if (v0 == v1) {
                                            // 0x002fb0b8
                                            charge(ctx, 33);
                                            a0 = 0;
                                            jal(ctx, 0x2FB0BCu, gen::fn_sub_2B8F90_002b8f90);
                                            s0 = v0;
                                            lw(v0, gp, bcore::kGpBtl);  // gBtl
                                            lw(a0, v0, b9::kBtlBossArchive);
                                            a1 = 1;
                                            a2 = addiu(sp, 0x48);
                                            jal(ctx, 0x2FB0D8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                            a0 = s0;
                                            a1 = v0;
                                            jal(ctx, 0x2FB0E8u, gen::fn_sub_2B90D0_002b90d0);
                                            lw(v0, gp, bcore::kGpBtl);  // gBtl
                                            lw(v0, v0, bcore::kBtlPlayerAction);
                                            lw(a1, v0, bcore::kActUnit);
                                            a0 = s0;
                                            a2 = a1;
                                            a3 = 0;
                                            t0 = 512;
                                            jal(ctx, 0x2FB10Cu, gen::fn_sub_2BAF90_002baf90);
                                            a0 = v0;
                                            a1 = 2;
                                            jal(ctx, 0x2FB11Cu, gen::fn_sub_27ED20_0027ed20);
                                            a0 = s0;
                                            jal(ctx, 0x2FB128u, gen::fn_sub_2B9030_002b9030);
                                            v0 = 1;
                                        } else {
                                            // 0x002fad80
                                            charge(ctx, 3);
                                            v1 = 422;
                                            if (v0 == v1) {
                                                // 0x002fb0a4
                                                charge(ctx, 5);
                                                jal(ctx, 0x2FB0A4u, gen::fn_sub_2EC790_002ec790);
                                                v0 = 1;
                                            } else {
                                                // 0x002fad8c
                                                charge(ctx, 3);
                                                v1 = 421;
                                                if (v0 == v1) {
                                                    // 0x002fb020
                                                    charge(ctx, 33);
                                                    a0 = 0;
                                                    jal(ctx, 0x2FB024u, gen::fn_sub_2B8F90_002b8f90);
                                                    s0 = v0;
                                                    lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                    lw(a0, v0, b9::kBtlBossArchive);
                                                    a1 = 1;
                                                    a2 = addiu(sp, 0x4C);
                                                    jal(ctx, 0x2FB040u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                                    a0 = s0;
                                                    a1 = v0;
                                                    jal(ctx, 0x2FB050u, gen::fn_sub_2B90D0_002b90d0);
                                                    lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                    lw(v0, v0, bcore::kBtlPlayerAction);
                                                    lw(a1, v0, bcore::kActUnit);
                                                    a0 = s0;
                                                    a2 = a1;
                                                    a3 = 0;
                                                    t0 = 512;
                                                    jal(ctx, 0x2FB074u, gen::fn_sub_2BAF90_002baf90);
                                                    a0 = v0;
                                                    a1 = 2;
                                                    jal(ctx, 0x2FB084u, gen::fn_sub_27ED20_0027ed20);
                                                    a0 = s0;
                                                    jal(ctx, 0x2FB090u, gen::fn_sub_2B9030_002b9030);
                                                    v0 = 1;
                                                } else {
                                                    // 0x002fad98
                                                    charge(ctx, 3);
                                                    v1 = 420;
                                                    if (v0 == v1) {
                                                        // 0x002faf9c
                                                        charge(ctx, 33);
                                                        a0 = 0;
                                                        jal(ctx, 0x2FAFA0u, gen::fn_sub_2B8F90_002b8f90);
                                                        s0 = v0;
                                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                        lw(a0, v0, b9::kBtlBossArchive);
                                                        a1 = 1;
                                                        a2 = addiu(sp, 0x50);
                                                        jal(ctx, 0x2FAFBCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                                        a0 = s0;
                                                        a1 = v0;
                                                        jal(ctx, 0x2FAFCCu, gen::fn_sub_2B90D0_002b90d0);
                                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                        lw(v0, v0, bcore::kBtlPlayerAction);
                                                        lw(a1, v0, bcore::kActUnit);
                                                        a0 = s0;
                                                        a2 = a1;
                                                        a3 = 0;
                                                        t0 = 512;
                                                        jal(ctx, 0x2FAFF0u, gen::fn_sub_2BAF90_002baf90);
                                                        a0 = v0;
                                                        a1 = 2;
                                                        jal(ctx, 0x2FB000u, gen::fn_sub_27ED20_0027ed20);
                                                        a0 = s0;
                                                        jal(ctx, 0x2FB00Cu, gen::fn_sub_2B9030_002b9030);
                                                        v0 = 1;
                                                    } else {
                                                        // 0x002fada4
                                                        charge(ctx, 3);
                                                        v1 = 419;
                                                        if (v0 == v1) {
                                                            // 0x002faf18
                                                            charge(ctx, 33);
                                                            a0 = 0;
                                                            jal(ctx, 0x2FAF1Cu, gen::fn_sub_2B8F90_002b8f90);
                                                            s0 = v0;
                                                            lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                            lw(a0, v0, b9::kBtlBossArchive);
                                                            a1 = 1;
                                                            a2 = addiu(sp, 0x54);
                                                            jal(ctx, 0x2FAF38u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                                            a0 = s0;
                                                            a1 = v0;
                                                            jal(ctx, 0x2FAF48u, gen::fn_sub_2B90D0_002b90d0);
                                                            lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                            lw(v0, v0, bcore::kBtlPlayerAction);
                                                            lw(a1, v0, bcore::kActUnit);
                                                            a0 = s0;
                                                            a2 = a1;
                                                            a3 = 0;
                                                            t0 = 512;
                                                            jal(ctx, 0x2FAF6Cu, gen::fn_sub_2BAF90_002baf90);
                                                            a0 = v0;
                                                            a1 = 2;
                                                            jal(ctx, 0x2FAF7Cu, gen::fn_sub_27ED20_0027ed20);
                                                            a0 = s0;
                                                            jal(ctx, 0x2FAF88u, gen::fn_sub_2B9030_002b9030);
                                                            v0 = 1;
                                                        } else {
                                                            // 0x002fadb0
                                                            charge(ctx, 3);
                                                            v1 = 418;
                                                            if (v0 == v1) {
                                                                // 0x002fae94
                                                                charge(ctx, 33);
                                                                a0 = 0;
                                                                jal(ctx, 0x2FAE98u, gen::fn_sub_2B8F90_002b8f90);
                                                                s0 = v0;
                                                                lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                                lw(a0, v0, b9::kBtlBossArchive);
                                                                a1 = 1;
                                                                a2 = addiu(sp, 0x58);
                                                                jal(ctx, 0x2FAEB4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                                                a0 = s0;
                                                                a1 = v0;
                                                                jal(ctx, 0x2FAEC4u, gen::fn_sub_2B90D0_002b90d0);
                                                                lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                                lw(v0, v0, bcore::kBtlPlayerAction);
                                                                lw(a1, v0, bcore::kActUnit);
                                                                a0 = s0;
                                                                a2 = a1;
                                                                a3 = 0;
                                                                t0 = 512;
                                                                jal(ctx, 0x2FAEE8u, gen::fn_sub_2BAF90_002baf90);
                                                                a0 = v0;
                                                                a1 = 2;
                                                                jal(ctx, 0x2FAEF8u, gen::fn_sub_27ED20_0027ed20);
                                                                a0 = s0;
                                                                jal(ctx, 0x2FAF04u, gen::fn_sub_2B9030_002b9030);
                                                                v0 = 1;
                                                            } else {
                                                                // 0x002fadbc
                                                                charge(ctx, 3);
                                                                v1 = 417;
                                                                if (v0 == v1) {
                                                                    // 0x002fae80
                                                                    charge(ctx, 5);
                                                                    jal(ctx, 0x2FAE80u, gen::fn_sub_2E9AC0_002e9ac0);
                                                                    v0 = 1;
                                                                } else {
                                                                    // 0x002fadc8
                                                                    charge(ctx, 3);
                                                                    v1 = 416;
                                                                    if (v0 == v1) {
                                                                        // 0x002fae6c
                                                                        charge(ctx, 5);
                                                                        jal(ctx, 0x2FAE6Cu, gen::fn_sub_2E9450_002e9450);
                                                                        v0 = 1;
                                                                    } else {
                                                                        // 0x002fadd4
                                                                        charge(ctx, 3);
                                                                        v1 = 456;
                                                                        if (v0 != v1) {
                                                                            // 0x002fade0
                                                                            charge(ctx, 2);
                                                                            goto L_002fb66c;
                                                                        }
                                                                        // 0x002fade8
                                                                        charge(ctx, 33);
                                                                        a0 = 0;
                                                                        jal(ctx, 0x2FADECu, gen::fn_sub_2B8F90_002b8f90);
                                                                        s0 = v0;
                                                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                                        lw(a0, v0, b9::kBtlBossArchive);
                                                                        a1 = 0;
                                                                        a2 = addiu(sp, 0x5C);
                                                                        jal(ctx, 0x2FAE08u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                                                                        a0 = s0;
                                                                        a1 = v0;
                                                                        jal(ctx, 0x2FAE18u, gen::fn_sub_2B90D0_002b90d0);
                                                                        lw(v0, gp, bcore::kGpBtl);  // gBtl
                                                                        lw(v0, v0, bcore::kBtlPlayerAction);
                                                                        lw(a1, v0, bcore::kActUnit);
                                                                        a0 = s0;
                                                                        a2 = a1;
                                                                        a3 = 0;
                                                                        t0 = 512;
                                                                        jal(ctx, 0x2FAE3Cu, gen::fn_sub_2BAF90_002baf90);
                                                                        a0 = v0;
                                                                        a1 = 2;
                                                                        jal(ctx, 0x2FAE4Cu, gen::fn_sub_27ED20_0027ed20);
                                                                        a0 = s0;
                                                                        jal(ctx, 0x2FAE58u, gen::fn_sub_2B9030_002b9030);
                                                                        v0 = 1;
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            // 0x002fb670 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_002fb564:
        charge(ctx, 33);
        a0 = 0;
        jal(ctx, 0x2FB568u, gen::fn_sub_2B8F90_002b8f90);
        s0 = v0;
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(a0, v0, b9::kBtlBossArchive);
        a1 = 1;
        a2 = addiu(sp, 0x24);
        jal(ctx, 0x2FB584u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x2FB594u, gen::fn_sub_2B90D0_002b90d0);
        lw(v0, gp, bcore::kGpBtl);  // gBtl
        lw(v0, v0, bcore::kBtlPlayerAction);
        lw(a1, v0, bcore::kActUnit);
        a0 = s0;
        a2 = a1;
        a3 = 0;
        t0 = 512;
        jal(ctx, 0x2FB5B8u, gen::fn_sub_2BAF90_002baf90);
        a0 = v0;
        a1 = 2;
        jal(ctx, 0x2FB5C8u, gen::fn_sub_27ED20_0027ed20);
        a0 = s0;
        jal(ctx, 0x2FB5D4u, gen::fn_sub_2B9030_002b9030);
        v0 = 1;
    }
    // 0x002fb670 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x002FB690 sub_2FB690 -- 464 bytes; frame 0x10: ra sp+0x0
// [btlBossEnemyDead] The ENEMY_DEAD hook: the encounter's death scene (436, 432, 431, 430, 429, 427, 426, 425 here; 424
// / 421 / 419 / 418 / 416 elsewhere) and 1, or 0.
void sub_2FB690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fb690
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, bcore::kGpBtl);  // gBtl
    lw(v0, v0, bcore::kBtlSetupEnemies);
    lhu(v1, v0, 8);
    v0 = 436;
    if (v1 == v0) {
        // 0x002fb838
        charge(ctx, 5);
        jal(ctx, 0x2FB838u, gen::fn_sub_2F6120_002f6120);
        v0 = 1;
    } else {
        // 0x002fb6b0
        charge(ctx, 3);
        v0 = 432;
        if (v1 == v0) {
            // 0x002fb824
            charge(ctx, 5);
            jal(ctx, 0x2FB824u, gen::fn_sub_2F4E70_002f4e70);
            v0 = 1;
        } else {
            // 0x002fb6bc
            charge(ctx, 3);
            v0 = 431;
            if (v1 == v0) {
                // 0x002fb810
                charge(ctx, 5);
                jal(ctx, 0x2FB810u, gen::fn_sub_2F4A40_002f4a40);
                v0 = 1;
            } else {
                // 0x002fb6c8
                charge(ctx, 3);
                v0 = 430;
                if (v1 == v0) {
                    // 0x002fb7fc
                    charge(ctx, 5);
                    jal(ctx, 0x2FB7FCu, gen::fn_sub_2F46D0_002f46d0);
                    v0 = 1;
                } else {
                    // 0x002fb6d4
                    charge(ctx, 3);
                    v0 = 429;
                    if (v1 == v0) {
                        // 0x002fb7e8
                        charge(ctx, 5);
                        jal(ctx, 0x2FB7E8u, gen::fn_sub_2F3840_002f3840);
                        v0 = 1;
                    } else {
                        // 0x002fb6e0
                        charge(ctx, 3);
                        v0 = 427;
                        if (v1 == v0) {
                            // 0x002fb7d4
                            charge(ctx, 5);
                            jal(ctx, 0x2FB7D4u, gen::fn_sub_2F2090_002f2090);
                            v0 = 1;
                        } else {
                            // 0x002fb6ec
                            charge(ctx, 3);
                            v0 = 426;
                            if (v1 == v0) {
                                // 0x002fb7c0
                                charge(ctx, 5);
                                jal(ctx, 0x2FB7C0u, gen::fn_sub_2F1D40_002f1d40);
                                v0 = 1;
                            } else {
                                // 0x002fb6f8
                                charge(ctx, 3);
                                v0 = 425;
                                if (v1 == v0) {
                                    // 0x002fb7ac
                                    charge(ctx, 5);
                                    jal(ctx, 0x2FB7ACu, gen::fn_sub_2F1810_002f1810);
                                    v0 = 1;
                                } else {
                                    // 0x002fb704
                                    charge(ctx, 3);
                                    v0 = 424;
                                    if (v1 == v0) {
                                        // 0x002fb798
                                        charge(ctx, 5);
                                        jal(ctx, 0x2FB798u, gen::fn_sub_2EF7E0_002ef7e0);
                                        v0 = 1;
                                    } else {
                                        // 0x002fb710
                                        charge(ctx, 3);
                                        v0 = 421;
                                        if (v1 == v0) {
                                            // 0x002fb784
                                            charge(ctx, 5);
                                            jal(ctx, 0x2FB784u, gen::fn_sub_2EC2C0_002ec2c0);
                                            v0 = 1;
                                        } else {
                                            // 0x002fb71c
                                            charge(ctx, 3);
                                            v0 = 419;
                                            if (v1 == v0) {
                                                // 0x002fb770
                                                charge(ctx, 5);
                                                jal(ctx, 0x2FB770u, gen::fn_sub_2EA590_002ea590);
                                                v0 = 1;
                                            } else {
                                                // 0x002fb728
                                                charge(ctx, 3);
                                                v0 = 418;
                                                if (v1 == v0) {
                                                    // 0x002fb75c
                                                    charge(ctx, 5);
                                                    jal(ctx, 0x2FB75Cu, gen::fn_sub_2EA210_002ea210);
                                                    v0 = 1;
                                                } else {
                                                    // 0x002fb734
                                                    charge(ctx, 3);
                                                    v0 = 416;
                                                    if (v1 == v0) {
                                                        // 0x002fb748
                                                        charge(ctx, 5);
                                                        jal(ctx, 0x2FB748u, gen::fn_sub_2E95F0_002e95f0);
                                                        v0 = 1;
                                                    } else {
                                                        // 0x002fb740
                                                        charge(ctx, 2);
                                                        // 0x002fb84c
                                                        charge(ctx, 1);
                                                        v0 = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x002fb850 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
