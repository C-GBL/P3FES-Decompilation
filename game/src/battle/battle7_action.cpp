// The battle code, seventh pass (slice battle7, group action; docs/ANALYSIS/21_battle.md): the all-out attack state
// (ROUNDUP), the help window and command panel helpers, the camera script commands, kill / revive, the poison damage
// and ailment lines, the boss archive files, a unit's cell position. Siblings of the functions the six replay routes
// reach in 0x290000-0x2FFFFF (a first-call probe found 19 of the 371 still-recompiled functions of the band reached;
// the AI rows only run for enemies without an AI script). The bodies are p3fes_handgen's (frame, spills, $ra links,
// every register, cycle charges, check points); this file names their offsets (battle3.h b3::, battle4.h b4::,
// battle5.h b5::, battle7.h b7::) and gives each its role -- proposed names in brackets (ADR-0009), symbols in code
// are functions.json's. Still-recompiled callees are reached through their gen:: entry points.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle7.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_btlActionSetState_00299d60(p3fes::EEContext&);
void fn_btlGetEncounterId_002d5550(p3fes::EEContext&);
void fn_datCalcClearBadStatus_00300560(p3fes::EEContext&);
void fn_datCalcGetBadStatusNoDown_00300530(p3fes::EEContext&);
void fn_datCalcGetBadStatus_00300550(p3fes::EEContext&);
void fn_datCalcGetEffectState_00301750(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcSetBadStatus_003004f0(p3fes::EEContext&);
void fn_datCalcSetHp_002ffd90(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_scrGetFloatPara_0035ee60(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_1778B0_001778b0(p3fes::EEContext&);
void fn_sub_1FDEC0_001fdec0(p3fes::EEContext&);
void fn_sub_1FE3B0_001fe3b0(p3fes::EEContext&);
void fn_sub_1FE430_001fe430(p3fes::EEContext&);
void fn_sub_1FE9B0_001fe9b0(p3fes::EEContext&);
void fn_sub_1FEA10_001fea10(p3fes::EEContext&);
void fn_sub_1FF310_001ff310(p3fes::EEContext&);
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);
void fn_sub_282650_00282650(p3fes::EEContext&);
void fn_sub_284200_00284200(p3fes::EEContext&);
void fn_sub_284C90_00284c90(p3fes::EEContext&);
void fn_sub_28A780_0028a780(p3fes::EEContext&);
void fn_sub_298610_00298610(p3fes::EEContext&);
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
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);
void fn_sub_2A3D70_002a3d70(p3fes::EEContext&);
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);
void fn_sub_2B8F90_002b8f90(p3fes::EEContext&);
void fn_sub_2B9030_002b9030(p3fes::EEContext&);
void fn_sub_2B9640_002b9640(p3fes::EEContext&);
void fn_sub_2BAC00_002bac00(p3fes::EEContext&);
void fn_sub_2BAF90_002baf90(p3fes::EEContext&);
void fn_sub_2BB6F0_002bb6f0(p3fes::EEContext&);
void fn_sub_2BC950_002bc950(p3fes::EEContext&);
void fn_sub_2BCCD0_002bccd0(p3fes::EEContext&);
void fn_sub_2BD230_002bd230(p3fes::EEContext&);
void fn_sub_2BD480_002bd480(p3fes::EEContext&);
void fn_sub_2BD7E0_002bd7e0(p3fes::EEContext&);
void fn_sub_2BDBD0_002bdbd0(p3fes::EEContext&);
void fn_sub_2BEDD0_002bedd0(p3fes::EEContext&);
void fn_sub_2BF690_002bf690(p3fes::EEContext&);
void fn_sub_2BF850_002bf850(p3fes::EEContext&);
void fn_sub_2BF880_002bf880(p3fes::EEContext&);
void fn_sub_2BF8B0_002bf8b0(p3fes::EEContext&);
void fn_sub_2BF8E0_002bf8e0(p3fes::EEContext&);
void fn_sub_2BF910_002bf910(p3fes::EEContext&);
void fn_sub_2BF940_002bf940(p3fes::EEContext&);
void fn_sub_2C1CE0_002c1ce0(p3fes::EEContext&);
void fn_sub_2D0D70_002d0d70(p3fes::EEContext&);
void fn_sub_2D0DE0_002d0de0(p3fes::EEContext&);
void fn_sub_2D1030_002d1030(p3fes::EEContext&);
void fn_sub_2D10F0_002d10f0(p3fes::EEContext&);
void fn_sub_2D1180_002d1180(p3fes::EEContext&);
void fn_sub_2D19B0_002d19b0(p3fes::EEContext&);
void fn_sub_2D21E0_002d21e0(p3fes::EEContext&);
void fn_sub_2D4CC0_002d4cc0(p3fes::EEContext&);
void fn_sub_2D5CF0_002d5cf0(p3fes::EEContext&);
void fn_sub_2D5DC0_002d5dc0(p3fes::EEContext&);
void fn_sub_2D7890_002d7890(p3fes::EEContext&);
void fn_sub_2D7E20_002d7e20(p3fes::EEContext&);
void fn_sub_2D7FB0_002d7fb0(p3fes::EEContext&);
void fn_sub_2D8090_002d8090(p3fes::EEContext&);
void fn_sub_2DB800_002db800(p3fes::EEContext&);
void fn_sub_2DB890_002db890(p3fes::EEContext&);
void fn_sub_2DC670_002dc670(p3fes::EEContext&);
void fn_sub_2DC830_002dc830(p3fes::EEContext&);
void fn_sub_2DCA60_002dca60(p3fes::EEContext&);
void fn_sub_2DD100_002dd100(p3fes::EEContext&);
void fn_sub_2DD690_002dd690(p3fes::EEContext&);
void fn_sub_2E2BE0_002e2be0(p3fes::EEContext&);
void fn_sub_2E3C80_002e3c80(p3fes::EEContext&);
void fn_sub_2F87E0_002f87e0(p3fes::EEContext&);
void fn_sub_2F8810_002f8810(p3fes::EEContext&);
void fn_sub_2FA510_002fa510(p3fes::EEContext&);
void fn_sub_2FD160_002fd160(p3fes::EEContext&);
void fn_sub_2FDDB0_002fddb0(p3fes::EEContext&);
void fn_sub_3A4220_003a4220(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b7;  // this slice's additions (battle7.h)

// 0x00298610 sub_298610 -- 2784 bytes; frame 0x1F0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlActionUpdateStateRoundup] btlAction state 29 ROUNDUP (sBtlActionTbl, update): the all-out attack -- the
// participants (gBtl +2952) dash in, the dust-cloud packets with the "BOKO.ADX" sound, the colour fades and effect
// packets of the skill, the hit packets on every target, the damage and the end; then the next state.
// Arguments: a0 the leader's btlAction.
void sub_298610(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00298610
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1F0);
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
    ld(s0, a0, act::kUid);
    a0 = 1;
    // ROUNDUP: the camera packet, the participants' dash packets
    jal(ctx, 0x298648u, gen::fn_sub_2B8F90_002b8f90);
    sw(v0, sp, 0x124);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(s1, v0, gbtl::kActionList);
    // walk gBtl's action list (+1192 next)
    for (;;) {
        // 0x00298698
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00298664
        charge(ctx, 3);
        lbu(v0, s1, act::kOneMore);
        if (v0 != 0) {
            // 0x00298670
            charge(ctx, 9);
            a0 = s1;
            a1 = 2;
            jal(ctx, 0x298678u, gen::fn_sub_2D7FB0_002d7fb0);
            a0 = v0;
            sd(s0, v0, 96);
            a1 = 1;
            jal(ctx, 0x29868Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
        }
        // 0x00298694
        charge(ctx, 1);
        lw(s1, s1, act::kNext);
    }
    // 0x002986a0
    charge(ctx, 7);
    lh(s3, s4, act::kCmdSkill);
    lw(fp, s4, act::kTargets);
    a3 = 0;
    lw(a2, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(a1, a2, gbtl::kAllOutCount);
    for (;;) {
        // 0x002986e0
        charge(ctx, 4);
        v0 = a3 & 0xFFFF;
        v0 = slt(v0, a1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002986bc
        charge(ctx, 9);
        v0 = a3 & 0xFFFF;
        a0 = sll(v0, 2);
        v0 = addu(a2, a0);
        lw(v0, v0, 2952);
        lw(v1, v0, 48);
        v0 = addu(a0, sp);
        sw(v1, v0, 472);
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFFFF;
    }
    // 0x002986f0
    charge(ctx, 2);
    for (;;) {
        // 0x00298710
        charge(ctx, 4);
        v0 = a3 & 0xFFFF;
        v0 = sltiu(v0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002986f8
        charge(ctx, 6);
        v0 = a3 & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        sw(zero, v0, 472);
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFFFF;
    }
    // 0x00298720
    charge(ctx, 180);
    lw(a0, sp, 0x1D8);
    lw(a1, sp, 0x1DC);
    lw(a2, sp, 0x1E0);
    // the all-out attack packet with up to three participants (gBtl +2952)
    jal(ctx, 0x29872Cu, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    ld(v1, s4, act::kUid);
    sd(v1, v0, 96);
    a1 = 1;
    jal(ctx, 0x298744u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    jal(ctx, 0x29874Cu, gen::fn_sub_2E3C80_002e3c80);
    s1 = v0;
    a0 = 10;
    sb(a0, v0, 0);
    v1 = 3078;
    sh(v1, v0, 8);
    sb(a0, v0, 16);
    v1 = 3077;
    sh(v1, v0, 24);
    sd(s0, v0, 96);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x298780u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    lw(a0, s4, act::kAoaLinked);
    a1 = 5;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x29879Cu, gen::fn_sub_2E2BE0_002e2be0);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s1, 88);
    sd(v1, v0, 8);
    ld(v1, s4, act::kUid);
    sd(v1, v0, 96);
    a1 = 1;
    jal(ctx, 0x2987C4u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 3;
    a1 = 0x690000;
    // the dust cloud and its sound
    a1 = addiu(a1, 13144);  // "BOKO.ADX"
    jal(ctx, 0x2987D8u, gen::fn_sub_2DD690_002dd690);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    ld(v1, s1, 88);
    sd(v1, v0, 8);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x2987FCu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    ld(s6, s1, 88);
    s1 = s3 & 0xFFFF;
    a0 = s1;
    a1 = addiu(sp, 0x1EC);
    a2 = addiu(sp, 0x1E8);
    // the colour fades and effects of the skill (+110)
    jal(ctx, 0x298818u, gen::fn_sub_29EA60_0029ea60);
    lw(a0, sp, 0x1EC);
    lw(a1, sp, 0x1E8);
    a2 = 16;
    jal(ctx, 0x29882Cu, gen::fn_sub_29F4B0_0029f4b0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s6, v0, 8);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x29884Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = s1;
    jal(ctx, 0x298858u, gen::fn_sub_29EC00_0029ec00);
    s7 = v0;
    a0 = s1;
    a1 = addiu(sp, 0x1EC);
    a2 = addiu(sp, 0x1E8);
    jal(ctx, 0x298870u, gen::fn_sub_29EC80_0029ec80);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    sw(v0, sp, 0x100);
    lw(a0, gp, kGpEffectTbl);  // EFFECT.TBL section 0: 28-byte skill effect rows 0x7CE400
    v1 = sll(v0, 3);
    v0 = subu(v1, v0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lhu(v0, v0, 2);
    v0 = v0 & 0x2;
    v0 = sltu(0, v0);
    t0 = v0 & 0xFFFF;
    a0 = s7;
    lw(a1, sp, 0x1EC);
    lw(a2, sp, 0x1E8);
    a3 = 16;
    jal(ctx, 0x2988B8u, gen::fn_sub_2A0050_002a0050);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s6, v0, 8);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x2988D8u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    s3 = s3 & 0xFFFF;
    a0 = s3;
    jal(ctx, 0x2988E8u, gen::fn_sub_29EC50_0029ec50);
    a0 = v0;
    a1 = 16;
    jal(ctx, 0x2988F8u, gen::fn_sub_2A1280_002a1280);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s6, v0, 8);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x298918u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = s4;
    a1 = s3;
    a2 = 16;
    jal(ctx, 0x29892Cu, gen::fn_sub_2A1B00_002a1b00);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    sd(s6, v0, 8);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x29894Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = s3;
    a1 = addiu(sp, 0x130);
    jal(ctx, 0x29895Cu, gen::fn_sub_2BB6F0_002bb6f0);
    lw(a0, sp, 0x124);
    a1 = addiu(sp, 0x130);
    a2 = 0;
    jal(ctx, 0x298970u, gen::fn_sub_2BAC00_002bac00);
    sw(v0, sp, 0x12C);
    v1 = 4;
    sb(v1, v0, 0);
    sd(s6, v0, 8);
    sd(s0, v0, 96);
    a0 = v0;
    a1 = 1;
    jal(ctx, 0x298994u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    lw(a0, sp, 0x124);
    lw(a1, s4, act::kUnit);
    lw(a2, fp, act::kUnit);
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x2989B0u, gen::fn_sub_2BAF90_002baf90);
    sw(v0, sp, 0x128);
    v1 = 4;
    sb(v1, v0, 0);
    lw(v1, sp, 0x12C);
    ld(v1, v1, 88);
    sd(v1, v0, 8);
    sd(s0, v0, 96);
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2989DCu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    lw(v0, s4, act5::kAoaFinish);
    if (v0 == 0) {
        // 0x002989fc
        charge(ctx, 1);
        v0 = 20;
    } else {
        // 0x002989f0
        charge(ctx, 3);
        v0 = 19;
    }
    // 0x00298a00
    charge(ctx, 25);
    a2 = v0 & 0xFFFF;
    a0 = 12;
    a1 = 2;
    jal(ctx, 0x298A0Cu, gen::fn_sub_2DD100_002dd100);
    a0 = v0;
    v1 = 5;
    sb(v1, v0, 0);
    lw(v1, sp, 0x128);
    ld(v1, v1, 88);
    sd(v1, v0, 8);
    v1 = 15;
    sh(v1, v0, 72);
    a1 = 1;
    jal(ctx, 0x298A38u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    sh(zero, sp, 0x110);
    a0 = s1;
    jal(ctx, 0x298A48u, gen::fn_sub_2D4CC0_002d4cc0);
    v0 = v0 & 0xFFFF;
    sq(v0, sp, 0xD0);
    fp = 0;
    for (;;) {
        // 0x00298f4c
        charge(ctx, 6);
        v0 = fp & 0xFFFF;
        sw(v0, sp, 0xF0);
        lhu(v1, s4, act::kTargetCount);
        v0 = slt(v0, v1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00298a64
        charge(ctx, 11);
        v0 = fp & 0xFFFF;
        v0 = sll(v0, 2);
        v0 = addu(s4, v0);
        lw(s1, v0, 56);
        a0 = addiu(s1, 200);
        jal(ctx, 0x298A78u, gen::fn_sub_2B9640_002b9640);
        s5 = v0;
        lw(v0, s1, 212);
        if (v0 == 0) {
            // 0x00298a9c
            charge(ctx, 1);
            s3 = s1;
        } else {
            // 0x00298a90
            charge(ctx, 3);
            s3 = s4;
        }
        // 0x00298aa0
        charge(ctx, 44);
        lw(a0, s3, 48);
        jal(ctx, 0x298AA4u, gen::fn_sub_2BD480_002bd480);
        a0 = v0;
        sd(s0, v0, 96);
        a1 = 1;
        jal(ctx, 0x298AB8u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
        t0 = s5 | 0x1000;
        lw(a0, sp, 0x124);
        lw(a1, s4, act::kUnit);
        lw(a2, s3, 48);
        a3 = 1;
        jal(ctx, 0x298AD4u, gen::fn_sub_2BAF90_002baf90);
        s5 = v0;
        v1 = 4;
        sb(v1, v0, 0);
        lw(v1, sp, 0x12C);
        ld(v1, v1, 88);
        sd(v1, v0, 8);
        lhu(v1, sp, 0x110);
        sh(v1, v0, 72);
        sd(s0, v0, 96);
        a0 = s5;
        a1 = 2;
        jal(ctx, 0x298B08u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
        a0 = 10;
        a1 = 0;
        a2 = 4;
        jal(ctx, 0x298B1Cu, gen::fn_sub_2DD100_002dd100);
        a0 = v0;
        v1 = 11;
        sb(v1, v0, 0);
        ld(v1, s5, 88);
        sd(v1, v0, 8);
        a1 = 1;
        jal(ctx, 0x298B3Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
        lw(v0, s1, 212);
        if (v0 != 0) {
            // 0x00298b50
            charge(ctx, 16);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(a0, v0, gbtl4::kFxHandles + 104);
            lw(a1, s4, act::kUnit);
            lw(a2, s1, 48);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x298B68u, gen::fn_sub_2BAF90_002baf90);
            a0 = v0;
            v1 = 11;
            sb(v1, v0, 0);
            ld(v1, s5, 88);
            sd(v1, v0, 8);
            a1 = 1;
            jal(ctx, 0x298B88u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
        }
        // 0x00298b90
        charge(ctx, 4);
        lhu(v1, s1, 204);
        v0 = 1024;
        if (v1 == v0) {
            // 0x00298ba0
            charge(ctx, 16);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(a0, v0, gbtl4::kFxHandles + 108);
            lw(a1, s4, act::kUnit);
            lw(a2, s3, 48);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x298BB8u, gen::fn_sub_2BAF90_002baf90);
            a0 = v0;
            v1 = 11;
            sb(v1, v0, 0);
            ld(v1, s5, 88);
            sd(v1, v0, 8);
            a1 = 1;
            jal(ctx, 0x298BD8u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
        }
        // 0x00298be0
        charge(ctx, 3);
        s7 = 0;
        for (;;) {
            // 0x00298f1c
            charge(ctx, 6);
            v0 = s7 & 0xFFFF;
            sq(v0, sp, 0xA0);
            lbu(v1, s1, 200);
            v0 = slt(v0, v1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00298bec
            charge(ctx, 77);
            v1 = s7 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = subu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s1, v0);
            sq(v0, sp, 0xC0);
            lb(a1, v0, 248);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s3, 48);
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x298C1Cu, gen::fn_sub_284200_00284200);
            s2 = v0;
            v1 = 11;
            sb(v1, v0, 0);
            ld(v1, s5, 88);
            sd(v1, v0, 8);
            sd(s0, v0, 96);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x298C44u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
            lw(a0, s1, 48);
            lw(a1, s4, act::kUnit);
            a2 = 2;
            jal(ctx, 0x298C58u, gen::fn_sub_282650_00282650);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, 0);
            ld(v1, s2, 88);
            sd(v1, v0, 8);
            lbu(v1, v0, 71);
            v1 = v1 & 0xDF;
            sb(v1, v0, 71);
            sd(s0, v0, 96);
            a1 = 1;
            jal(ctx, 0x298C88u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
            lq(v0, sp, 0xC0);
            v0 = addiu(v0, 224);
            sw(v0, sp, 0xE0);
            a0 = s4;
            a1 = s3;
            a2 = v0;
            lhu(a3, s1, 204);
            lhu(t0, s1, 206);
            jal(ctx, 0x298CB0u, gen::fn_sub_2D7E20_002d7e20);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, 0);
            ld(v1, s2, 88);
            sd(v1, v0, 8);
            sd(s0, v0, 96);
            a1 = 1;
            jal(ctx, 0x298CD4u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
            a0 = s1;
            jal(ctx, 0x298CE0u, gen::fn_sub_2D8090_002d8090);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, 0);
            ld(v1, s2, 88);
            sd(v1, v0, 8);
            sd(s0, v0, 96);
            a1 = 1;
            jal(ctx, 0x298D04u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
            lhu(v0, s4, act::kTargetCount);
            v1 = addiu(v0, -1);
            lw(v0, sp, 0xF0);
            if (v0 == v1) {
                // 0x00298d20
                charge(ctx, 5);
                lbu(v0, s1, 200);
                v1 = addiu(v0, -1);
                lq(v0, sp, 0xA0);
                if (v0 == v1) {
                    // 0x00298d34
                    charge(ctx, 12);
                    a0 = s4;
                    jal(ctx, 0x298D38u, gen::fn_sub_2D8090_002d8090);
                    a0 = v0;
                    v1 = 5;
                    sb(v1, v0, 0);
                    ld(v1, s2, 88);
                    sd(v1, v0, 8);
                    sd(s0, v0, 96);
                    a1 = 1;
                    jal(ctx, 0x298D5Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
                }
            }
            // 0x00298d64
            charge(ctx, 3);
            lq(v0, sp, 0xA0);
            if (v0 == 0) {
                // 0x00298d70
                charge(ctx, 4);
                lw(v0, sp, 0xE0);
                lw(v0, v0, 0);
                if (v0 != 0) {
                    // 0x00298d80
                    charge(ctx, 17);
                    lw(a0, s3, 48);
                    a1 = 0;
                    a2 = 0;
                    jal(ctx, 0x298D8Cu, gen::fn_sub_2BD230_002bd230);
                    a0 = v0;
                    v1 = 5;
                    sb(v1, v0, 0);
                    ld(v1, s2, 88);
                    sd(v1, v0, 8);
                    lbu(v1, v0, 71);
                    v1 = v1 & 0xDF;
                    sb(v1, v0, 71);
                    sd(s0, v0, 96);
                    a1 = 3;
                    jal(ctx, 0x298DBCu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
                }
            }
            // 0x00298dc4
            charge(ctx, 8);
            lq(v0, sp, 0xC0);
            v0 = addiu(v0, 250);
            sq(v0, sp, 0xB0);
            lq(v0, sp, 0xC0);
            lhu(v0, v0, 250);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                // 0x00298de4
                charge(ctx, 25);
                a0 = addiu(sp, 0x1B0);
                jal(ctx, 0x298DE8u, gen::fn_sub_2D5DC0_002d5dc0);
                v0 = 0x100000;
                sw(v0, sp, 0x1BC);
                a0 = s1;
                a1 = s1;
                a2 = addiu(sp, 0x1B0);
                a3 = 1;
                t0 = a3;
                jal(ctx, 0x298E0Cu, gen::fn_sub_2D7E20_002d7e20);
                a0 = v0;
                v1 = 4;
                sb(v1, v0, 0);
                sd(s6, v0, 8);
                sd(s0, v0, 96);
                a1 = 1;
                jal(ctx, 0x298E2Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
                lq(v0, sp, 0xB0);
                lhu(v0, v0, 0);
                v0 = v0 & 0x2;
                if (v0 != 0) {
                    // 0x00298e48
                    charge(ctx, 29);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s1, 48);
                    a1 = 10;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x298E60u, gen::fn_sub_284200_00284200);
                    a0 = v0;
                    v1 = 4;
                    sb(v1, v0, 0);
                    ld(v1, s2, 88);
                    sd(v1, v0, 8);
                    sd(s0, v0, 96);
                    a1 = 1;
                    jal(ctx, 0x298E84u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
                    lw(a0, s1, 48);
                    jal(ctx, 0x298E90u, gen::fn_sub_284C90_00284c90);
                    a0 = v0;
                    v1 = 4;
                    sb(v1, v0, 0);
                    ld(v1, s2, 88);
                    sd(v1, v0, 8);
                    sd(s0, v0, 96);
                    a1 = 1;
                    jal(ctx, 0x298EB4u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
                }
            }
            // 0x00298ebc
            charge(ctx, 24);
            lbu(t2, s1, 200);
            lw(a0, s4, act::kUnit);
            lw(a1, s3, 48);
            lw(a2, sp, 0x100);
            lhu(a3, s1, 204);
            lhu(t0, s1, 206);
            t1 = s7;
            lw(t3, sp, 0xE0);
            jal(ctx, 0x298EDCu, gen::fn_sub_2BDBD0_002bdbd0);
            a0 = v0;
            v1 = 5;
            sb(v1, v0, 0);
            ld(v1, s2, 88);
            sd(v1, v0, 8);
            lbu(v1, v0, 71);
            v1 = v1 & 0xDF;
            sb(v1, v0, 71);
            sd(s0, v0, 96);
            a1 = 3;
            jal(ctx, 0x298F0Cu, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
            v0 = addiu(s7, 1);
            s7 = v0 & 0xFFFF;
        }
        // 0x00298f34
        charge(ctx, 6);
        lhu(v1, sp, 0x110);
        lq(v0, sp, 0xD0);
        v0 = addu(v1, v0);
        sh(v0, sp, 0x110);
        v0 = addiu(fp, 0x1);
        fp = v0 & 0xFFFF;
    }
    // 0x00298f64
    charge(ctx, 99);
    a0 = 16;
    jal(ctx, 0x298F68u, gen::fn_sub_29FA50_0029fa50);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, 88);
    sd(v1, v0, 8);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x298F98u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 16;
    a1 = 0;
    jal(ctx, 0x298FA8u, gen::fn_sub_2A1080_002a1080);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, 88);
    sd(v1, v0, 8);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x298FD8u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 16;
    jal(ctx, 0x298FE4u, gen::fn_sub_2A16C0_002a16c0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s2, 88);
    sd(v1, v0, 8);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x299014u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 8;
    jal(ctx, 0x299020u, gen::fn_sub_2A1DB0_002a1db0);
    a0 = v0;
    v1 = 4;
    sb(v1, v0, 0);
    ld(v1, s5, 88);
    sd(v1, v0, 8);
    lbu(v1, v0, 71);
    v1 = v1 & 0xDF;
    sb(v1, v0, 71);
    sd(s0, v0, 96);
    a1 = 0;
    jal(ctx, 0x299050u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x299064u, gen::fn_sub_2BC950_002bc950);
    a0 = v0;
    a1 = 4;
    sb(a1, v0, 0);
    ld(v1, s5, 88);
    sd(v1, v0, 8);
    sb(a1, v0, 16);
    lw(v1, sp, 0x128);
    ld(v1, v1, 88);
    sd(v1, v0, 24);
    sd(s0, v0, 96);
    a1 = 1;
    jal(ctx, 0x299098u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    lw(a0, sp, 0x124);
    jal(ctx, 0x2990A4u, gen::fn_sub_2B9030_002b9030);
    a0 = s4;
    a1 = 30;
    jal(ctx, 0x2990B4u, gen::fn_btlActionSetState_00299d60);
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
    sp = addiu(sp, 0x1F0);
}

// 0x002BCCD0 sub_2BCCD0 -- 268 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlHelpShow] Writes the battle help window (gBtl +2976): the unit's name by side (2 persona sub_173220, 1 enemy
// row *0x7CE4E8 + 19 id, 0 party sub_1778B0; sub_3A4220) and the text a1 (below 0x1000 a message id sub_1FEA10, else
// the item row *0x7CE4EC + 19 (a1 - 0x1000), sub_1FE9B0).
// Arguments: a0 the btlUnit or 0, a1 the text id.
void sub_2BCCD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bccd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    if (a0 != 0) {
        // 0x002bcce8
        charge(ctx, 5);
        lhu(a1, a0, unit::kId);
        lbu(a0, a0, unit::kSide);
        v1 = 2;
        if (a0 == v1) {
            // 0x002bcd54
            charge(ctx, 3);
            a0 = a1;
            jal(ctx, 0x2BCD58u, gen::fn_sub_173220_00173220);
        } else {
            // 0x002bccfc
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x002bcd30
                charge(ctx, 9);
                v1 = a1 & 0xFFFF;
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v1 = addu(v0, v1);
                lw(v0, gp, kGpEnemyNames);  // MSG.TBL section 2 0x7CE4E8
                v0 = addu(v0, v1);
            } else {
                // 0x002bcd08
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002bcd18
                    charge(ctx, 6);
                    a0 = dsll32(a1, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x2BCD20u, gen::fn_sub_1778B0_001778b0);
                } else {
                    // 0x002bcd10
                    charge(ctx, 2);
                }
            }
        }
        // 0x002bcd60
        charge(ctx, 6);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v1, gbtl7::kHelpWindow);
        a1 = 0;
        a2 = v0;
        jal(ctx, 0x2BCD70u, gen::fn_sub_3A4220_003a4220);
    }
    // 0x002bcd78
    charge(ctx, 3);
    at = sltiu(s0, 4096);
    if (at == 0) {
        // 0x002bcda0
        charge(ctx, 10);
        v0 = addiu(s0, -4096);
        v1 = v0 & 0xFFFF;
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v1 = addu(v0, v1);
        lw(v0, gp, kGpSkillNames);  // MSG.TBL section 1: 19-byte skill names 0x7CE4EC
        a0 = addu(v0, v1);
        jal(ctx, 0x2BCDC0u, gen::fn_sub_1FE9B0_001fe9b0);
    } else {
        // 0x002bcd84
        charge(ctx, 7);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl7::kHelpWindow);
        a1 = s0;
        jal(ctx, 0x2BCD90u, gen::fn_sub_1FEA10_001fea10);
    }
    // 0x002bcdc8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002BD7E0 sub_2BD7E0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Help window packet update: shows the text once (sub_2BCCD0), then holds 46 frames.
// Arguments: a0 the packet data {unit, text, frames}.
void sub_2BD7E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bd7e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 8);
    if (v0 == 0) {
        // 0x002bd7fc
        charge(ctx, 4);
        lw(a0, s0, 0);
        lw(a1, s0, 4);
        jal(ctx, 0x2BD804u, gen::fn_sub_2BCCD0_002bccd0);
    }
    // 0x002bd80c
    charge(ctx, 6);
    lw(v0, s0, 8);
    v0 = addiu(v0, 1);
    sw(v0, s0, 8);
    at = sltiu(v0, 46);
    if (at != 0) {
        // 0x002bd830
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x002bd824
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002bd834 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002BEDD0 sub_2BEDD0 -- 324 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlCommandMenuClose] Closes the command menu for a turn end: with gBtl +20 bit 0x2000000 a menu in state 3 goes to
// 6; otherwise the menu is closed (an item menu (+108 = 4) by sub_1FE430, or sub_1FE3B0 with the unit's uid without
// the bit; else sub_1FDEC0) and set to state 2.
// Arguments: a0 the btlAction.
void sub_2BEDD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bedd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v1, v0, gbtl4::kTestFlags);
    v0 = 0x2000000;
    v0 = v1 & v0;
    if (v0 == 0) {
        // 0x002beea0
        charge(ctx, 7);
        a0 = 0x690000;
        a0 = addiu(a0, 28496);  // "battle_command_calc"
        jal(ctx, 0x2BEEA8u, gen::fn_kwlnTaskGetTaskByName_00195340);
        a0 = v0;
        if (v0 != 0) {
            // 0x002beebc
            charge(ctx, 8);
            jal(ctx, 0x2BEEBCu, gen::fn_kwlnTaskGetWorkData_00195540);
            s0 = v0;
            lw(v1, v0, 4);
            lhu(a0, v1, 108);
            v1 = 4;
            if (a0 == v1) {
                // 0x002beee4
                charge(ctx, 4);
                lw(v0, s1, act::kUnit);
                lw(a0, v0, unit::kUid);
                jal(ctx, 0x2BEEECu, gen::fn_sub_1FE3B0_001fe3b0);
            } else {
                // 0x002beedc
                charge(ctx, 2);
            }
            // 0x002beef4
            charge(ctx, 2);
            v1 = 2;
            sh(v1, s0, 0);
        }
    } else {
        // 0x002bedfc
        charge(ctx, 7);
        a0 = 0x690000;
        a0 = addiu(a0, 28496);  // "battle_command_calc"
        jal(ctx, 0x2BEE04u, gen::fn_kwlnTaskGetTaskByName_00195340);
        a0 = v0;
        if (v0 != 0) {
            // 0x002bee18
            charge(ctx, 9);
            jal(ctx, 0x2BEE18u, gen::fn_kwlnTaskGetWorkData_00195540);
            s0 = v0;
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lw(a0, v1, gbtl4::kTestFlags);
            v1 = 0x2000000;
            v1 = a0 & v1;
            if (v1 == 0) {
                // 0x002bee5c
                charge(ctx, 5);
                lw(v0, s0, 4);
                lhu(v1, v0, 108);
                v0 = 4;
                if (v1 == v0) {
                    // 0x002bee78
                    charge(ctx, 4);
                    jal(ctx, 0x2BEE78u, gen::fn_sub_1FE430_001fe430);
                } else {
                    // 0x002bee70
                    charge(ctx, 2);
                    // 0x002bee88
                    charge(ctx, 2);
                    jal(ctx, 0x2BEE88u, gen::fn_sub_1FDEC0_001fdec0);
                }
                // 0x002bee90
                charge(ctx, 4);
                v1 = 2;
                sh(v1, s0, 0);
            } else {
                // 0x002bee3c
                charge(ctx, 4);
                lhu(a0, s0, 0);
                v1 = 3;
                if (a0 == v1) {
                    // 0x002bee4c
                    charge(ctx, 4);
                    v1 = 6;
                    sh(v1, s0, 0);
                }
            }
        }
    }
    // 0x002beefc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002BF690 sub_2BF690 -- 444 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlCommandHelpLine] The command panel's help line for a menu row: 12 / 6 (sub_2C1CE0 says the unit cannot) -> 215,
// 5 -> 214, 1..3 by the unit's ailments (0x20 -> 205, 0x40 -> 206, row 2 also 4 -> 208, row 3 on encounter 429 ->
// 209); written by sub_1FEA10.
// Arguments: a0 s16 the menu row.
void sub_2BF690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf690
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kCmdCalcTask);
    jal(ctx, 0x2BF6B0u, gen::fn_kwlnTaskGetWorkData_00195540);
    lw(s1, v0, 4);
    lw(v0, s1, 48);
    lw(a0, v0, 2604);
    jal(ctx, 0x2BF6C4u, gen::fn_datCalcGetBadStatus_00300550);
    s0 = 0;
    a0 = s2 & 0xFFFF;
    v1 = 12;
    if (a0 != v1) {
        // 0x002bf6e0
        charge(ctx, 3);
        v1 = 6;
        if (a0 != v1) {
            // 0x002bf6ec
            charge(ctx, 3);
            v1 = 5;
            if (a0 == v1) {
                // 0x002bf7ec
                charge(ctx, 3);
                s0 = 214;
            } else {
                // 0x002bf6f8
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x002bf79c
                    charge(ctx, 3);
                    v1 = v0 & 0x20;
                    if (v1 == 0) {
                        // 0x002bf7b4
                        charge(ctx, 3);
                        v1 = v0 & 0x40;
                        if (v1 == 0) {
                            // 0x002bf7cc
                            charge(ctx, 5);
                            jal(ctx, 0x2BF7CCu, gen::fn_btlGetEncounterId_002d5550);
                            v1 = 429;
                            if (v0 == v1) {
                                // 0x002bf7e0
                                charge(ctx, 3);
                                s0 = 209;
                            }
                        } else {
                            // 0x002bf7c0
                            charge(ctx, 3);
                            s0 = 206;
                        }
                    } else {
                        // 0x002bf7a8
                        charge(ctx, 3);
                        s0 = 205;
                    }
                } else {
                    // 0x002bf704
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x002bf754
                        charge(ctx, 3);
                        v1 = v0 & 0x20;
                        if (v1 == 0) {
                            // 0x002bf76c
                            charge(ctx, 3);
                            v1 = v0 & 0x40;
                            if (v1 == 0) {
                                // 0x002bf784
                                charge(ctx, 3);
                                v1 = v0 & 0x4;
                                if (v1 != 0) {
                                    // 0x002bf790
                                    charge(ctx, 3);
                                    s0 = 208;
                                }
                            } else {
                                // 0x002bf778
                                charge(ctx, 3);
                                s0 = 206;
                            }
                        } else {
                            // 0x002bf760
                            charge(ctx, 3);
                            s0 = 205;
                        }
                    } else {
                        // 0x002bf710
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x002bf724
                            charge(ctx, 3);
                            v1 = v0 & 0x20;
                            if (v1 == 0) {
                                // 0x002bf73c
                                charge(ctx, 3);
                                v1 = v0 & 0x40;
                                if (v1 != 0) {
                                    // 0x002bf748
                                    charge(ctx, 3);
                                    s0 = 206;
                                }
                            } else {
                                // 0x002bf730
                                charge(ctx, 3);
                                s0 = 205;
                            }
                        } else {
                            // 0x002bf71c
                            charge(ctx, 2);
                        }
                    }
                }
            }
            goto L_002bf814;
        }
    }
    charge(ctx, 6);
    a0 = s1;
    a1 = 0;
    jal(ctx, 0x2BF800u, gen::fn_sub_2C1CE0_002c1ce0);
    if (v0 == 0) {
        // 0x002bf810
        charge(ctx, 1);
        s0 = 215;
    }
L_002bf814:
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x002bf81c
        charge(ctx, 5);
        lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
        lw(a0, v0, gbtl7::kHelpWindow);
        a1 = s0;
        jal(ctx, 0x2BF828u, gen::fn_sub_1FEA10_001fea10);
    }
    // 0x002bf830 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002BF850 sub_2BF850 -- 36 bytes; frame 0x10: ra sp+0x0
// The command panel row 1's help callback: sub_2BF690(1).
// Arguments: none.
void sub_2BF850(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf850
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    jal(ctx, 0x2BF85Cu, gen::fn_sub_2BF690_002bf690);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BF880 sub_2BF880 -- 36 bytes; frame 0x10: ra sp+0x0
// The command panel row 2's help callback: sub_2BF690(2).
// Arguments: none.
void sub_2BF880(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf880
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 6;
    jal(ctx, 0x2BF88Cu, gen::fn_sub_2BF690_002bf690);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BF8B0 sub_2BF8B0 -- 36 bytes; frame 0x10: ra sp+0x0
// The command panel row 3's help callback: sub_2BF690(3).
// Arguments: none.
void sub_2BF8B0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf8b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2;
    jal(ctx, 0x2BF8BCu, gen::fn_sub_2BF690_002bf690);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BF8E0 sub_2BF8E0 -- 36 bytes; frame 0x10: ra sp+0x0
// The command panel row 5's help callback: sub_2BF690(5).
// Arguments: none.
void sub_2BF8E0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf8e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 3;
    jal(ctx, 0x2BF8ECu, gen::fn_sub_2BF690_002bf690);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BF910 sub_2BF910 -- 36 bytes; frame 0x10: ra sp+0x0
// The command panel row 6's help callback: sub_2BF690(6).
// Arguments: none.
void sub_2BF910(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf910
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 5;
    jal(ctx, 0x2BF91Cu, gen::fn_sub_2BF690_002bf690);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002BF940 sub_2BF940 -- 36 bytes; frame 0x10: ra sp+0x0
// The command panel row 12's help callback: sub_2BF690(12).
// Arguments: none.
void sub_2BF940(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002bf940
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 7;
    jal(ctx, 0x2BF94Cu, gen::fn_sub_2BF690_002bf690);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D0D70 sub_2D0D70 -- 112 bytes; frame 0x10: ra sp+0x0
// Battle script command (COMM): the hero's camera reset -- queues sub_28A780's packets, a camera packet
// (sub_2B8D60(3, 4095)) and the shot 37 on the hero (sub_2A3B40); returns 1.
// Arguments: none.
void sub_2D0D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d0d70
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    jal(ctx, 0x2D0D80u, gen::fn_sub_28A780_0028a780);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2D0D90u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D0DA0u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    a1 = 37;
    jal(ctx, 0x2D0DB4u, gen::fn_sub_2A3B40_002a3b40);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D0DC4u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D0DE0 sub_2D0DE0 -- 260 bytes; frame 0x50: ra sp+0x0
// Battle script command (COMM): as sub_2D0D70 with an explicit camera move (sub_2A3D70) from the script's six float
// parameters (position, target).
// Arguments: none.
void sub_2D0DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x002d0de0
    enter(ctx, 65);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    jal(ctx, 0x2D0DF0u, gen::fn_sub_28A780_0028a780);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2D0E00u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D0E10u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 0;
    jal(ctx, 0x2D0E1Cu, gen::fn_scrGetFloatPara_0035ee60);
    swc1(f0, sp, 0x40);
    a0 = 1;
    jal(ctx, 0x2D0E2Cu, gen::fn_scrGetFloatPara_0035ee60);
    swc1(f0, sp, 0x44);
    a0 = 2;
    jal(ctx, 0x2D0E3Cu, gen::fn_scrGetFloatPara_0035ee60);
    swc1(f0, sp, 0x48);
    a0 = 3;
    jal(ctx, 0x2D0E4Cu, gen::fn_scrGetFloatPara_0035ee60);
    swc1(f0, sp, 0x20);
    a0 = 4;
    jal(ctx, 0x2D0E5Cu, gen::fn_scrGetFloatPara_0035ee60);
    swc1(f0, sp, 0x24);
    a0 = 5;
    jal(ctx, 0x2D0E6Cu, gen::fn_scrGetFloatPara_0035ee60);
    swc1(f0, sp, 0x28);
    a1 = addiu(sp, 0x40);
    a3 = addiu(sp, 0x30);
    ld(v0, sp, 0x40);
    lwc1(f0, sp, 0x48);
    sd(v0, sp, 0x30);
    swc1(f0, sp, 0x38);
    a2 = addiu(sp, 0x20);
    t0 = addiu(sp, 0x10);
    ld(v0, sp, 0x20);
    lwc1(f0, sp, 0x28);
    sd(v0, sp, 0x10);
    swc1(f0, sp, 0x18);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    v0 = 0x3F800000;
    mtc1(v0, f12);
    lw(a0, v1, gbtl::kPlayerAction);
    jal(ctx, 0x2D0EB8u, gen::fn_sub_2A3D70_002a3d70);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D0EC8u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002D1030 sub_2D1030 -- 180 bytes; frame 0x10: ra sp+0x0
// Battle script command (COMM): as sub_2D0D70 with the camera move to the fixed points 0x957140..0x957170.
// Arguments: none.
void sub_2D1030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x002d1030
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    jal(ctx, 0x2D1040u, gen::fn_sub_28A780_0028a780);
    a0 = 3;
    a1 = 4095;
    jal(ctx, 0x2D1050u, gen::fn_sub_2B8D60_002b8d60);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D1060u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 0;
    jal(ctx, 0x2D106Cu, gen::fn_scrGetIntPara_0035ed20);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x41F00000;
    mtc1(v0, f0);
    div_s(f12, f1, f0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl::kPlayerAction);
    a1 = 0x950000;
    a1 = addiu(a1, 29040);  // &0x957170
    a2 = 0x950000;
    a2 = addiu(a2, 29008);  // &0x957150
    a3 = 0x950000;
    a3 = addiu(a3, 29024);  // &0x957160
    t0 = 0x950000;
    t0 = addiu(t0, 28992);  // &0x957140
    jal(ctx, 0x2D10B8u, gen::fn_sub_2A3D70_002a3d70);
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x2D10C8u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D10F0 sub_2D10F0 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Battle script command (COMM): a navigator wait packet (sub_2DB890) and a support line packet (sub_2DB800(32,
// parameter 0)), both with the delay parameter 1.
// Arguments: none.
void sub_2D10F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d10f0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D1104u, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x2D1114u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    jal(ctx, 0x2D1120u, gen::fn_sub_2DB890_002db890);
    a0 = v0;
    sh(s0, v0, 72);
    a1 = 1;
    jal(ctx, 0x2D1134u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    a0 = 32;
    a1 = s1;
    jal(ctx, 0x2D1144u, gen::fn_sub_2DB800_002db800);
    a0 = v0;
    sh(s0, v0, 72);
    a1 = 1;
    jal(ctx, 0x2D1158u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002D1180 sub_2D1180 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Battle script command (COMM): a navigator wait packet (sub_2DB890) with the delay parameter 0.
// Arguments: none.
void sub_2D1180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1180
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D1190u, gen::fn_scrGetIntPara_0035ed20);
    s0 = v0;
    jal(ctx, 0x2D119Cu, gen::fn_sub_2DB890_002db890);
    a0 = v0;
    sh(s0, v0, 72);
    a1 = 1;
    jal(ctx, 0x2D11B0u, gen::fn_sub_27ED20_0027ed20);  // queue the packet ($a1: the queue)
    v0 = 1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D19B0 sub_2D19B0 -- 88 bytes; frame 0x10: ra sp+0x0
// Starts the battle music once (gBtl flag 0x2000): sub_10A4E0(0, 15, 0, 3) and sub_1FF310.
// Arguments: none.
void sub_2D19B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d19b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    a1 = addiu(v1, 12);
    lw(a0, v1, gbtl::kFlags);
    v1 = a0 & 0x2000;
    if (v1 == 0) {
        // 0x002d19d0
        charge(ctx, 10);
        v0 = a0 | 0x2000;
        sw(v0, a1, 0);
        a0 = 0;
        a1 = 15;
        a2 = 0;
        a3 = 3;
        jal(ctx, 0x2D19E8u, gen::fn_sub_10A4E0_0010a4e0);
        jal(ctx, 0x2D19F0u, gen::fn_sub_1FF310_001ff310);
    }
    // 0x002d19f8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D21E0 sub_2D21E0 -- 148 bytes; leaf frame (no stack)
// A camera spring step: moves a value toward a target over half the remaining distance (f12 the step), returns 1.0
// when arrived, else 0.5 (floats as the original computes them).
// Arguments: a0 f32[5] the spring, f12 the step.
void sub_2D21E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f12{ctx, 12};
    // 0x002d21e0
    enter(ctx, 9);  // entry check point + this block's cycles
    lwc1(f0, a0, 4);
    lwc1(f3, a0, 12);
    lwc1(f4, a0, 16);
    sub_s(f5, f0, f12);
    mtc1(zero, f2);
    c_le_s(f5, f2);
    if (!cond(ctx)) {
        // 0x002d2214
        charge(ctx, 7);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        lwc1(f0, a0, 0);
        mul_s(f0, f1, f0);
        c_lt_s(f5, f0);
        if (!cond(ctx)) {
            // 0x002d2244
            charge(ctx, 3);
            lwc1(f0, a0, 8);
            adda_s(f2, f3);
            madd_s(f1, f0, f12);
        } else {
            // 0x002d2230
            charge(ctx, 5);
            lwc1(f0, a0, 8);
            adda_s(f2, f3);
            msub_s(f1, f0, f12);
        }
        // 0x002d2250
        charge(ctx, 7);
        mtc1(zero, f0);
        adda_s(f0, f4);
        madd_s(f0, f1, f12);
        swc1(f5, a0, 4);
        swc1(f1, a0, 12);
        swc1(f0, a0, 16);
    } else {
        // 0x002d2204
        charge(ctx, 4);
        v0 = 0x3F800000;
        mtc1(v0, f0);
    }
    // 0x002d226c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D5CF0 sub_2D5CF0 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Whether a party unit wears the accessory 1054 (Junpei / Yukari only: DatUnit id 4 or 2, equipment slot 1,
// sub_16F630).
// Arguments: a0 the btlUnit.
void sub_2D5CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d5cf0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lbu(v0, a0, unit::kSide);
    if (v0 == 0) {
        // 0x002d5d18
        charge(ctx, 3);
        lw(v0, s0, unit::kDat);
        if (v0 != 0) {
            // 0x002d5d30
            charge(ctx, 4);
            lhu(v1, v0, dat::kId);
            v0 = 4;
            if (v1 != v0) {
                // 0x002d5d40
                charge(ctx, 3);
                v0 = 2;
                if (v1 != v0) {
                    // 0x002d5d4c
                    charge(ctx, 2);
                L_002d5da0:
                    charge(ctx, 1);
                    v0 = 0;
                    // 0x002d5da4 (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(ra, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x20);
                    return;
                }
            }
            charge(ctx, 16);
            a0 = dsll32(v1, 16);
            a0 = dsra32(a0, 16);
            a1 = 1;
            jal(ctx, 0x2D5D60u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lw(v0, s0, 2604);
            lh(a0, v0, 2);
            jal(ctx, 0x2D5D78u, gen::fn_sub_16F630_0016f630);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = 1054;
            if (v1 != v0) {
                goto L_002d5da0;
            }
            // 0x002d5d94
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x002d5d24
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x002d5d0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x002d5da4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D7890 sub_2D7890 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlUnitSetDead] Kills or revives an action's unit: revive (a1 = 1) sets HP 1 (not for skill 438 at +1120), clears
// the dead status and sets the revived flag; otherwise HP 0, every status cleared, dead set, the died flag set and
// the revived flag cleared. sub_2FA510 first.
// Arguments: a0 the btlAction, a1 1 revive / 0 kill.
void sub_2D7890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d7890
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(s0, a0, act::kUnit);
    jal(ctx, 0x2D78B0u, gen::fn_sub_2FA510_002fa510);
    a1 = 1;
    if (s1 != a1) {
        // 0x002d7904
        charge(ctx, 19);
        lw(a0, s0, unit::kDat);
        a1 = 0;
        jal(ctx, 0x2D790Cu, gen::fn_datCalcSetHp_002ffd90);
        lw(a0, s0, unit::kDat);
        v0 = 0xFF0000;
        a1 = v0 | 0xFFFF;  // &0xFFFFFF
        jal(ctx, 0x2D7920u, gen::fn_datCalcClearBadStatus_00300560);
        lw(a0, s0, unit::kDat);
        a1 = 0x80000;
        jal(ctx, 0x2D7930u, gen::fn_datCalcSetBadStatus_003004f0);
        lw(v1, s0, unit::kFlags);
        a0 = v1 | 0x1;
        sw(a0, s0, unit::kFlags);
        v1 = si(-17);
        v1 = a0 & v1;
        sw(v1, s0, unit::kFlags);
    } else {
        // 0x002d78c4
        charge(ctx, 4);
        lhu(v1, s2, act5::kReviveSkill);
        v0 = 438;
        if (v1 != v0) {
            // 0x002d78d4
            charge(ctx, 3);
            lw(a0, s0, unit::kDat);
            jal(ctx, 0x2D78D8u, gen::fn_datCalcSetHp_002ffd90);
        }
        // 0x002d78e0
        charge(ctx, 9);
        lw(a0, s0, unit::kDat);
        a1 = 0x80000;
        jal(ctx, 0x2D78E8u, gen::fn_datCalcClearBadStatus_00300560);
        lw(v1, s0, unit::kFlags);
        v1 = v1 | 0x10;
        sw(v1, s0, unit::kFlags);
    }
    // 0x002d7950 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DC670 sub_2DC670 -- 440 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlPoisonDamage] The poison damage of a turn: for the ailment 128, -(max HP / 500) for a party unit; an enemy by
// its table flags (0x400 / 0x800 / 0x1000 / 0x2000: -50 / -100 / -150 / -200, else -(max HP * 100 / 333)); never
// kills (1 - HP when it would).
// Arguments: a0 the btlAction.
void sub_2DC670(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dc670
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lw(s0, v0, unit::kDat);
    s1 = 0;
    a0 = s0;
    // only the ailment 128 (poison) hurts
    jal(ctx, 0x2DC690u, gen::fn_datCalcGetBadStatusNoDown_00300530);
    v1 = 128;
    if (v0 == v1) {
        // 0x002dc6ac
        charge(ctx, 8);
        a0 = s0;
        jal(ctx, 0x2DC6B0u, gen::fn_datCalcGetMaxHp_002ffdf0);
        a0 = v0 & 0xFFFF;
        lhu(v0, s0, dat::kFlags);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x002dc704
            charge(ctx, 10);
            lhu(v1, s0, dat::kId);
            v0 = sll(v1, 5);
            v0 = subu(v0, v1);
            v1 = sll(v0, 1);
            lw(v0, gp, kGpEnemyTbl);  // gBtlEnemyTbl
            v0 = addu(v0, v1);
            lhu(v1, v0, 0);
            v0 = v1 & 0x400;
            if (v0 == 0) {
                // 0x002dc738
                charge(ctx, 3);
                v0 = v1 & 0x800;
                if (v0 == 0) {
                    // 0x002dc750
                    charge(ctx, 3);
                    v0 = v1 & 0x1000;
                    if (v0 == 0) {
                        // 0x002dc768
                        charge(ctx, 3);
                        v0 = v1 & 0x2000;
                        if (v0 == 0) {
                            // 0x002dc780
                            charge(ctx, 12);
                            v1 = a0 & 0xFFFF;
                            v0 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v0 = sll(v0, 2);
                            v1 = subu(0, v0);
                            v0 = 333;
                            div(v1, v0);
                            mflo(v0);
                            s1 = dsll32(v0, 16);
                            s1 = dsra32(s1, 16);
                        } else {
                            // 0x002dc774
                            charge(ctx, 3);
                            s1 = si(-200);
                        }
                    } else {
                        // 0x002dc75c
                        charge(ctx, 3);
                        s1 = si(-150);
                    }
                } else {
                    // 0x002dc744
                    charge(ctx, 3);
                    s1 = si(-100);
                }
            } else {
                // 0x002dc72c
                charge(ctx, 3);
                s1 = si(-50);
            }
            // 0x002dc7b0
            charge(ctx, 5);
            v0 = dsll32(s1, 16);
            v0 = dsra32(v0, 16);
            at = slti(v0, 1000);
            if (at == 0) {
                // 0x002dc7c4
                charge(ctx, 1);
                s1 = 999;
            }
        } else {
            // 0x002dc6cc
            charge(ctx, 14);
            v1 = a0 & 0xFFFF;
            v0 = sll(v1, 2);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            v1 = subu(0, v0);
            v0 = 500;
            div(v1, v0);
            mflo(v0);
            s1 = dsll32(v0, 16);
            s1 = dsra32(s1, 16);
        }
    } else {
        // 0x002dc6a4
        charge(ctx, 2);
    }
    // 0x002dc7c8
    charge(ctx, 7);
    a1 = dsll32(s1, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    // never kill: leave 1 HP
    jal(ctx, 0x2DC7D4u, gen::fn_datCalcIsDead_0030b5a0);
    if (v0 == 0) {
        // 0x002dc80c
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x002dc7e4
        charge(ctx, 10);
        a0 = s0;
        jal(ctx, 0x2DC7E8u, gen::fn_datCalcGetHp_002ffd70);
        v0 = v0 & 0xFFFF;
        v0 = addiu(v0, -1);
        v0 = subu(0, v0);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
    }
    // 0x002dc810 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002DC830 sub_2DC830 -- 560 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAilmentTurnLine] The ailment message of a turn start: by the ailment and the command kind (+108) a line 6..20,
// +1 for an enemy; -1 for none.
// Arguments: a0 the btlAction.
void sub_2DC830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dc830
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lhu(v0, a0, act::kFlags2);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x002dc864
        charge(ctx, 8);
        lw(s0, s2, act::kUnit);
        s1 = si(-1);
        lw(a0, s0, unit::kDat);
        jal(ctx, 0x2DC870u, gen::fn_datCalcGetBadStatusNoDown_00300530);
        v1 = 512;
        if (v0 == v1) {
            // 0x002dc9e0
            charge(ctx, 4);
            lhu(v1, s2, act::kCmdKind);
            v0 = 11;
            if (v1 != v0) {
                // 0x002dc9f0
                charge(ctx, 3);
                v0 = 8;
                if (v1 != v0) {
                    // 0x002dc9fc
                    charge(ctx, 3);
                    v0 = 7;
                    if (v1 != v0) {
                        // 0x002dca08
                        charge(ctx, 2);
                        goto L_002dca14;
                    }
                }
            }
            charge(ctx, 1);
            s1 = 20;
        } else {
            // 0x002dc884
            charge(ctx, 3);
            v1 = 128;
            if (v0 != v1) {
                // 0x002dc890
                charge(ctx, 3);
                v1 = 64;
                if (v0 == v1) {
                    // 0x002dc9bc
                    charge(ctx, 4);
                    lhu(v1, s2, act::kCmdKind);
                    v0 = 11;
                    if (v1 == v0) {
                        // 0x002dc9d4
                        charge(ctx, 3);
                        s1 = 12;
                    } else {
                        // 0x002dc9cc
                        charge(ctx, 2);
                    }
                } else {
                    // 0x002dc89c
                    charge(ctx, 3);
                    v1 = 32;
                    if (v0 == v1) {
                        // 0x002dc998
                        charge(ctx, 4);
                        lhu(v1, s2, act::kCmdKind);
                        v0 = 11;
                        if (v1 == v0) {
                            // 0x002dc9b0
                            charge(ctx, 3);
                            s1 = 10;
                        } else {
                            // 0x002dc9a8
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x002dc8a8
                        charge(ctx, 3);
                        v1 = 16;
                        if (v0 == v1) {
                            // 0x002dc974
                            charge(ctx, 3);
                            lbu(v0, s2, act::kOneMore);
                            if (v0 == 0) {
                                // 0x002dc980
                                charge(ctx, 3);
                                lbu(v0, s2, act5::kWakeTimer);
                                if (v0 == 0) {
                                    // 0x002dc98c
                                    charge(ctx, 3);
                                    s1 = 18;
                                }
                            }
                        } else {
                            // 0x002dc8b4
                            charge(ctx, 3);
                            a0 = 8;
                            if (v0 == a0) {
                                // 0x002dc918
                                charge(ctx, 4);
                                lhu(v1, s2, act::kCmdKind);
                                v0 = 11;
                                if (v1 != v0) {
                                    // 0x002dc928
                                    charge(ctx, 2);
                                    if (v1 != a0) {
                                        // 0x002dc930
                                        charge(ctx, 3);
                                        v0 = 7;
                                        if (v1 != v0) {
                                            // 0x002dc93c
                                            charge(ctx, 3);
                                            v0 = 12;
                                            if (v1 != v0) {
                                                // 0x002dc948
                                                charge(ctx, 3);
                                                v0 = 6;
                                                if (v1 != v0) {
                                                    // 0x002dc954
                                                    charge(ctx, 2);
                                                    goto L_002dca14;
                                                }
                                            }
                                            charge(ctx, 3);
                                            s1 = 14;
                                            goto L_002dca14;
                                        }
                                    }
                                }
                                charge(ctx, 3);
                                s1 = 16;
                            } else {
                                // 0x002dc8c0
                                charge(ctx, 3);
                                v1 = 4;
                                if (v0 != v1) {
                                    // 0x002dc8cc
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (v0 != v1) {
                                        // 0x002dc8d8
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (v0 == v1) {
                                            // 0x002dc8ec
                                            charge(ctx, 3);
                                            lhu(v0, s2, act::kCmdKind);
                                            if (v0 == v1) {
                                                // 0x002dc900
                                                charge(ctx, 3);
                                                s1 = 6;
                                            } else {
                                                // 0x002dc8f8
                                                charge(ctx, 2);
                                                // 0x002dc90c
                                                charge(ctx, 3);
                                                s1 = a0;
                                            }
                                        } else {
                                            // 0x002dc8e4
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    L_002dca14:
        charge(ctx, 2);
        if (i64(s1) >= 0) {
            // 0x002dca28
            charge(ctx, 3);
            lbu(v0, s0, unit::kSide);
            if (v0 != 0) {
                // 0x002dca3c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            } else {
                // 0x002dca34
                charge(ctx, 2);
            }
            // 0x002dca40
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x002dca1c
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002dc858
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002dca44 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DCA60 sub_2DCA60 -- 352 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlAilmentLine] The ailment message of a "bad" state: the line 40..56 by the ailment (1..512), +1 for an enemy; -1
// for none.
// Arguments: a0 the btlAction.
void sub_2DCA60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dca60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(v0, a0, act::kFlags2);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x002dca8c
        charge(ctx, 8);
        lw(s0, a0, act::kUnit);
        s1 = si(-1);
        lw(a0, s0, unit::kDat);
        jal(ctx, 0x2DCA98u, gen::fn_datCalcGetBadStatusNoDown_00300530);
        v1 = 512;
        if (v0 == v1) {
            // 0x002dcb74
            charge(ctx, 1);
            s1 = 56;
        } else {
            // 0x002dcaac
            charge(ctx, 3);
            v1 = 256;
            if (v0 == v1) {
                // 0x002dcb68
                charge(ctx, 3);
                s1 = 54;
            } else {
                // 0x002dcab8
                charge(ctx, 3);
                v1 = 64;
                if (v0 == v1) {
                    // 0x002dcb5c
                    charge(ctx, 3);
                    s1 = 52;
                } else {
                    // 0x002dcac4
                    charge(ctx, 3);
                    v1 = 32;
                    if (v0 == v1) {
                        // 0x002dcb50
                        charge(ctx, 3);
                        s1 = 50;
                    } else {
                        // 0x002dcad0
                        charge(ctx, 3);
                        v1 = 16;
                        if (v0 == v1) {
                            // 0x002dcb44
                            charge(ctx, 3);
                            s1 = 48;
                        } else {
                            // 0x002dcadc
                            charge(ctx, 3);
                            v1 = 8;
                            if (v0 == v1) {
                                // 0x002dcb38
                                charge(ctx, 3);
                                s1 = 46;
                            } else {
                                // 0x002dcae8
                                charge(ctx, 3);
                                v1 = 4;
                                if (v0 == v1) {
                                    // 0x002dcb2c
                                    charge(ctx, 3);
                                    s1 = 44;
                                } else {
                                    // 0x002dcaf4
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (v0 == v1) {
                                        // 0x002dcb20
                                        charge(ctx, 3);
                                        s1 = 42;
                                    } else {
                                        // 0x002dcb00
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (v0 == v1) {
                                            // 0x002dcb14
                                            charge(ctx, 3);
                                            s1 = 40;
                                        } else {
                                            // 0x002dcb0c
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // 0x002dcb78
        charge(ctx, 2);
        if (i64(s1) >= 0) {
            // 0x002dcb8c
            charge(ctx, 3);
            lbu(v0, s0, unit::kSide);
            if (v0 != 0) {
                // 0x002dcba0
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            } else {
                // 0x002dcb98
                charge(ctx, 2);
            }
            // 0x002dcba4
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x002dcb80
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002dca80
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002dcba8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002F87E0 sub_2F87E0 -- 48 bytes; frame 0x20: ra sp+0x0
// [btlBossArchiveFile] The file a0 of the boss archive (gBtl +2836; H_Cdvd_ArchiveGetFile).
// Arguments: a0 u16 the index.
void sub_2F87E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f87e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    a1 = a0 & 0xFFFF;
    lw(a0, v0, gbtl4::kBossBlock);
    a2 = addiu(sp, 0x1C);
    jal(ctx, 0x2F87F8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002F8810 sub_2F8810 -- 48 bytes; frame 0x20: ra sp+0x0
// [btlBossArchiveFile0] The file 0 of the boss archive (gBtl +2836).
// Arguments: none.
void sub_2F8810(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002f8810
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(a0, v0, gbtl4::kBossBlock);
    a1 = 0;
    a2 = addiu(sp, 0x1C);
    jal(ctx, 0x2F8828u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002FD160 sub_2FD160 -- 180 bytes; frame 0x10: ra sp+0x0
// Encounter 428's hook: an enemy action with the effect state 11 returns the boss work word gBtl +2884; else 0.
// Arguments: a0 the btlAction.
void sub_2FD160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002fd160
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lw(v0, v0, gbtl::kSetupEnemies);
    lhu(v1, v0, 8);
    v0 = 428;
    if (v1 == v0) {
        // 0x002fd188
        charge(ctx, 4);
        lhu(v0, a0, act::kFlags2);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x002fd1a4
            charge(ctx, 5);
            lw(a0, a0, act::kUnit);
            lbu(v1, a0, unit::kSide);
            v0 = 1;
            if (v1 == v0) {
                // 0x002fd1c4
                charge(ctx, 8);
                lw(a0, a0, unit::kDat);
                a1 = 11;
                jal(ctx, 0x2FD1CCu, gen::fn_datCalcGetEffectState_00301750);
                v0 = dsll32(v0, 24);
                v0 = dsra32(v0, 24);
                if (i64(v0) <= 0) {
                    // 0x002fd1f4
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x002fd1e4
                    charge(ctx, 4);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kBossWork0);
                }
            } else {
                // 0x002fd1b8
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x002fd198
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x002fd1f8
        charge(ctx, 2);
    } else {
        // 0x002fd180
        charge(ctx, 2);
        // 0x002fd200
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x002fd204 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002FDDB0 sub_2FDDB0 -- 140 bytes; leaf frame (no stack)
// [btlUnitCellPos] A unit's cell position: x = 25 * cell x (+148) - 1750, y = the unit's y, z = 25 * cell z (+150) -
// 1750 + (200 + radius * scale) (the R5900 multiply-add of the original).
// Arguments: a0 the btlUnit, a1 f32[3] out.
void sub_2FDDB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x002fddb0
    enter(ctx, 35);  // entry check point + this block's cycles
    lh(a2, a0, unit4::kCellX);
    v1 = sll(a2, 2);
    a2 = addu(v1, a2);
    v1 = sll(a2, 2);
    v1 = addu(a2, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, a1, 0);
    lwc1(f0, a0, unit4::kPos + 4);
    swc1(f0, a1, 4);
    lh(a2, a0, unit4::kCellZ);
    v1 = sll(a2, 2);
    a2 = addu(v1, a2);
    v1 = sll(a2, 2);
    v1 = addu(a2, v1);
    v1 = addiu(v1, -1750);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, a1, 8);
    lwc1(f3, a0, unit::kRadius);
    lwc1(f2, a0, unit::kScale);
    v1 = 0x43480000;
    mtc1(v1, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f3, f2);
    lwc1(f0, a1, 8);
    add_s(f0, f0, f1);
    swc1(f0, a1, 8);
}

}  // namespace p3fes::game
