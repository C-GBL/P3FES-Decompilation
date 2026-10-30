// The battle code, seventh pass (slice battle7, group voice; docs/ANALYSIS/21_battle.md): the party voice line
// pickers (the table 0x697C10) and the navigator line pickers (0x6978F0), the voice bank and voice line packets, the
// sound / motion / support line packets and their creators, the support events, the analysed-enemy navigator line.
// Siblings of the functions the six replay routes reach in 0x290000-0x2FFFFF (a first-call probe found 19 of the 371
// still-recompiled functions of the band reached; the AI rows only run for enemies without an AI script). The bodies
// are p3fes_handgen's (frame, spills, $ra links, every register, cycle charges, check points); this file names their
// offsets (battle3.h b3::, battle4.h b4::, battle5.h b5::, battle7.h b7::) and gives each its role -- proposed names
// in brackets (ADR-0009), symbols in code are functions.json's. Still-recompiled callees are reached through their
// gen:: entry points.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/battle7.h"

namespace p3fes::recomp_gen {
void fn_btlGetEncounterId_002d5550(p3fes::EEContext&);
void fn_btlSupportRequestLine_002db9f0(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_datCalcGetAffinity_00306e80(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_sub_10A0E0_0010a0e0(p3fes::EEContext&);
void fn_sub_10A100_0010a100(p3fes::EEContext&);
void fn_sub_10A240_0010a240(p3fes::EEContext&);
void fn_sub_10A2E0_0010a2e0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10A500_0010a500(p3fes::EEContext&);
void fn_sub_10A720_0010a720(p3fes::EEContext&);
void fn_sub_10A770_0010a770(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_289030_00289030(p3fes::EEContext&);
void fn_sub_2D86C0_002d86c0(p3fes::EEContext&);
void fn_sub_2D8850_002d8850(p3fes::EEContext&);
void fn_sub_2DB2A0_002db2a0(p3fes::EEContext&);
void fn_sub_2DB480_002db480(p3fes::EEContext&);
void fn_sub_2DB650_002db650(p3fes::EEContext&);
void fn_sub_2DB7D0_002db7d0(p3fes::EEContext&);
void fn_sub_2DB800_002db800(p3fes::EEContext&);
void fn_sub_2DBAC0_002dbac0(p3fes::EEContext&);
void fn_sub_2DBB00_002dbb00(p3fes::EEContext&);
void fn_sub_2DD180_002dd180(p3fes::EEContext&);
void fn_sub_2DD1B0_002dd1b0(p3fes::EEContext&);
void fn_sub_2DD1F0_002dd1f0(p3fes::EEContext&);
void fn_sub_2DD720_002dd720(p3fes::EEContext&);
void fn_sub_2DD760_002dd760(p3fes::EEContext&);
void fn_sub_2DD7D0_002dd7d0(p3fes::EEContext&);
void fn_sub_2DD830_002dd830(p3fes::EEContext&);
void fn_sub_2DDDC0_002dddc0(p3fes::EEContext&);
void fn_sub_2DDF10_002ddf10(p3fes::EEContext&);
void fn_sub_2DE030_002de030(p3fes::EEContext&);
void fn_sub_2DEFE0_002defe0(p3fes::EEContext&);
void fn_sub_2E0350_002e0350(p3fes::EEContext&);
void fn_sub_2E0540_002e0540(p3fes::EEContext&);
void fn_sub_2E1CD0_002e1cd0(p3fes::EEContext&);
void fn_sub_2E1DF0_002e1df0(p3fes::EEContext&);
void fn_sub_2E1F10_002e1f10(p3fes::EEContext&);
void fn_sub_2E2030_002e2030(p3fes::EEContext&);
void fn_sub_2E2110_002e2110(p3fes::EEContext&);
void fn_sub_2E22A0_002e22a0(p3fes::EEContext&);
void fn_sub_2E2920_002e2920(p3fes::EEContext&);
void fn_sub_2E2A60_002e2a60(p3fes::EEContext&);
void fn_sub_2E2C70_002e2c70(p3fes::EEContext&);
void fn_sub_2E2CB0_002e2cb0(p3fes::EEContext&);
void fn_sub_2E2D00_002e2d00(p3fes::EEContext&);
void fn_sub_2E2D40_002e2d40(p3fes::EEContext&);
void fn_sub_2E3010_002e3010(p3fes::EEContext&);
void fn_sub_2E30A0_002e30a0(p3fes::EEContext&);
void fn_sub_31F6D0_0031f6d0(p3fes::EEContext&);
void fn_sub_357FD0_00357fd0(p3fes::EEContext&);
void fn_sub_3C8F40_003c8f40(p3fes::EEContext&);
void fn_sub_3C8FA0_003c8fa0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace b3;  // the record offsets and $gp slots of battle3.h
using namespace b4;  // battle4.h's additions
using namespace b5;  // battle5.h's additions
using namespace b7;  // this slice's additions (battle7.h)

// 0x002D86C0 sub_2D86C0 -- 180 bytes; leaf frame (no stack)
// [btlNaviLineMember] Navigator line picker 3 (table 0x6978F0): the line 96..103 of the acting party member (unit ids
// 2..5, 7..10); -1 for others.
// Arguments: a0 the btlAction.
void sub_2D86C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x002d86c0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002d86dc
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d86ec
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32160);  // &0x7B7DA0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D8708u:  // table[2]: unit id 2
                // 0x002d8708
                charge(ctx, 3);
                v0 = 96;
                break;
            case 0x2D8714u:  // table[3]: unit id 3
                // 0x002d8714
                charge(ctx, 3);
                v0 = 97;
                break;
            case 0x2D8720u:  // table[4]: unit id 4
                // 0x002d8720
                charge(ctx, 3);
                v0 = 98;
                break;
            case 0x2D872Cu:  // table[5]: unit id 5
                // 0x002d872c
                charge(ctx, 3);
                v0 = 99;
                break;
            case 0x2D8738u:  // table[7]: unit id 7
                // 0x002d8738
                charge(ctx, 3);
                v0 = 100;
                break;
            case 0x2D8744u:  // table[8]: unit id 8
                // 0x002d8744
                charge(ctx, 3);
                v0 = 101;
                break;
            case 0x2D8750u:  // table[9]: unit id 9
                // 0x002d8750
                charge(ctx, 3);
                v0 = 102;
                break;
            case 0x2D875Cu:  // table[10]: unit id 10
                // 0x002d875c
                charge(ctx, 3);
                v0 = 103;
                break;
            case 0x2D8768u:  // table[0, 1, 6]
            L_002d8768:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d876c (the shared epilogue, written out on this path)
            charge(ctx, 2);
            return;
        }
        goto L_002d8768;
    }
    // 0x002d86d0
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d876c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x002D8850 sub_2D8850 -- 392 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlNaviLineMember2] Navigator line picker 6 (table 0x6978F0): the acting party member's line 113..128, the odd one
// of its pair when sub_2DB480 says so.
// Arguments: a0 the btlAction.
void sub_2D8850(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d8850
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002d887c
        charge(ctx, 10);
        jal(ctx, 0x2D887Cu, gen::fn_sub_2DB480_002db480);
        v0 = v0 & 0xFFFF;
        a0 = v0;
        a0 = sltiu(a0, 1);
        lw(v0, s0, act::kUnit);
        lhu(v0, v0, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002d88a4
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 32208);  // &0x7B7DD0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2D88C0u:  // table[2]: unit id 2
                // 0x002d88c0
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d88d4
                    charge(ctx, 1);
                    v0 = 113;
                } else {
                    // 0x002d88c8
                    charge(ctx, 3);
                    v0 = 114;
                }
                // 0x002d88d8
                charge(ctx, 2);
                break;
            case 0x2D88E0u:  // table[3]: unit id 3
                // 0x002d88e0
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d88f4
                    charge(ctx, 1);
                    v0 = 115;
                } else {
                    // 0x002d88e8
                    charge(ctx, 3);
                    v0 = 116;
                }
                // 0x002d88f8
                charge(ctx, 2);
                break;
            case 0x2D8900u:  // table[4]: unit id 4
                // 0x002d8900
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d8914
                    charge(ctx, 1);
                    v0 = 117;
                } else {
                    // 0x002d8908
                    charge(ctx, 3);
                    v0 = 118;
                }
                // 0x002d8918
                charge(ctx, 2);
                break;
            case 0x2D8920u:  // table[5]: unit id 5
                // 0x002d8920
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d8934
                    charge(ctx, 1);
                    v0 = 119;
                } else {
                    // 0x002d8928
                    charge(ctx, 3);
                    v0 = 120;
                }
                // 0x002d8938
                charge(ctx, 2);
                break;
            case 0x2D8940u:  // table[7]: unit id 7
                // 0x002d8940
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d8954
                    charge(ctx, 1);
                    v0 = 121;
                } else {
                    // 0x002d8948
                    charge(ctx, 3);
                    v0 = 122;
                }
                // 0x002d8958
                charge(ctx, 2);
                break;
            case 0x2D8960u:  // table[8]: unit id 8
                // 0x002d8960
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d8974
                    charge(ctx, 1);
                    v0 = 123;
                } else {
                    // 0x002d8968
                    charge(ctx, 3);
                    v0 = 124;
                }
                // 0x002d8978
                charge(ctx, 2);
                break;
            case 0x2D8980u:  // table[9]: unit id 9
                // 0x002d8980
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d8994
                    charge(ctx, 1);
                    v0 = 125;
                } else {
                    // 0x002d8988
                    charge(ctx, 3);
                    v0 = 126;
                }
                // 0x002d8998
                charge(ctx, 2);
                break;
            case 0x2D89A0u:  // table[10]: unit id 10
                // 0x002d89a0
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x002d89b4
                    charge(ctx, 1);
                    v0 = 127;
                } else {
                    // 0x002d89a8
                    charge(ctx, 3);
                    v0 = 128;
                }
                // 0x002d89b8
                charge(ctx, 2);
                break;
            case 0x2D89C0u:  // table[0, 1, 6]
            L_002d89c0:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002d89c4 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
        goto L_002d89c0;
    }
    // 0x002d8870
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002d89c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002DB2A0 sub_2DB2A0 -- 380 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportArm] Arms the support event a0 (gBtl +2564 bit): event 0 / 1 wait 2..4 / 2..3 turns (datCalcRand), event
// 2 3..4 or 4..5 turns by the flags 320 / 321; resets its counter (+2552 + 4a0) and sets its limit (+2554 + 4a0);
// event 0 also clears the member +2576.
// Arguments: a0 u16 the event.
void sub_2DB2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db2a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a3 = s1 & 0xFFFF;
    a2 = 1;
    v1 = sllv(a2, a3);
    a1 = v1 & 0xFFFF;
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, a0, gbtl5::kSupportEvents);
    v1 = v1 | a1;
    sh(v1, a0, gbtl5::kSupportEvents);
    a0 = 2;
    // arm the event bit, then the event's turn limit
    if (a3 == a0) {
        // 0x002db37c
        charge(ctx, 5);
        a0 = 320;
        jal(ctx, 0x2DB380u, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x002db3b4
            charge(ctx, 5);
            a0 = 321;
            jal(ctx, 0x2DB3B8u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x002db3c8
                charge(ctx, 7);
                s0 = 3;
                a0 = 2;
                jal(ctx, 0x2DB3D0u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v1 = v0 & 0xFFFF;
                v1 = addu(s0, v1);
                s0 = v1 & 0xFFFF;
            }
        } else {
            // 0x002db390
            charge(ctx, 9);
            a0 = 2;
            s0 = 2;
            jal(ctx, 0x2DB398u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
            v1 = v0 & 0xFFFF;
            v1 = addu(s0, v1);
            s0 = v1 & 0xFFFF;
        }
        // 0x002db3e4
        charge(ctx, 8);
        v1 = s1 & 0xFFFF;
        a0 = sll(v1, 2);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = addu(a0, v1);
        sh(zero, v1, 2552);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        v1 = addu(a0, v1);
        sh(s0, v1, 2554);
    } else {
        // 0x002db2e0
        charge(ctx, 2);
        if (a3 == a2) {
            // 0x002db33c
            charge(ctx, 16);
            s0 = a0 & 0xFFFF;
            a0 = a2;
            jal(ctx, 0x2DB344u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
            v1 = v0 & 0xFFFF;
            a1 = addu(s0, v1);
            v1 = s1 & 0xFFFF;
            a0 = sll(v1, 2);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = addu(a0, v1);
            sh(zero, v1, 2552);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            v1 = addu(a0, v1);
            sh(a1, v1, 2554);
        } else {
            // 0x002db2e8
            charge(ctx, 2);
            if (a3 == 0) {
                // 0x002db2f8
                charge(ctx, 17);
                s0 = a0 & 0xFFFF;
                jal(ctx, 0x2DB2FCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v1 = v0 & 0xFFFF;
                a1 = addu(s0, v1);
                v1 = s1 & 0xFFFF;
                a0 = sll(v1, 2);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                v1 = addu(a0, v1);
                sh(zero, v1, 2552);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                v1 = addu(a0, v1);
                sh(a1, v1, 2554);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                sw(zero, v1, gbtl5::kSupportMember);
            } else {
                // 0x002db2f0
                charge(ctx, 2);
            }
        }
    }
    // 0x002db404 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002DB650 sub_2DB650 -- 56 bytes; frame 0x10: ra sp+0x0
// [btlSupportWatch] Remembers the unit the support event watches: its uid (+2568) and, through sub_289030, its unit
// id (+2572).
// Arguments: a0 a unit uid.
void sub_2DB650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db650
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    sw(a0, v0, gbtl7::kSupportUid);
    a0 = a0 & 0xFFFF;
    jal(ctx, 0x2DB664u, gen::fn_sub_289030_00289030);
    lhu(a0, v0, unit::kId);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sh(a0, v1, gbtl5::kSupportEnemy);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DB7D0 sub_2DB7D0 -- 48 bytes; frame 0x10: ra sp+0x0
// Support line packet update: btlSupportRequestLine(data +0, data +4); returns 1.
// Arguments: a0 the packet data {u16 line, u32 arg}.
void sub_2DB7D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db7d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0;
    lhu(a0, a0, 0);
    lw(a1, v0, 4);
    jal(ctx, 0x2DB7E4u, gen::fn_btlSupportRequestLine_002db9f0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DB800 sub_2DB800 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlSupportLinePktCreate] Creates the support line packet of sub_2DB7D0 (kind 2049, 8 data bytes).
// Arguments: a0 s16 the line, a1 its argument.
void sub_2DB800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002db800
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 2049;
    a1 = 8;
    jal(ctx, 0x2DB820u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    v1 = 0x2E0000;
    v1 = addiu(v1, -18480);  // &sub_2DB7D0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s1, v1, 0);
    sw(s0, v1, 4);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002DBAC0 sub_2DBAC0 -- 64 bytes; frame 0x10: ra sp+0x0
// [btlNaviStop] Stops the navigator line: sub_3C8F40 / sub_3C8FA0, then clears the pending word (+2584) and the
// playing bit (+2582 bit 0).
// Arguments: none.
void sub_2DBAC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dbac0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2DBAC8u, gen::fn_sub_3C8F40_003c8f40);
    jal(ctx, 0x2DBAD0u, gen::fn_sub_3C8FA0_003c8fa0);
    lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
    sh(zero, v1, gbtl5::kNaviPending);
    lw(a0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v1, a0, gbtl5::kNaviFlags);
    v1 = v1 & 0xFFFE;
    sh(v1, a0, gbtl5::kNaviFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DBB00 sub_2DBB00 -- 944 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlNaviAnalysisLine] Navigator line for an analysed enemy: -1 in the FES boss fights 433..435 or for an enemy
// marked silent (gBtlEnemyTbl +30 bit 0x20); else from the 18-byte element rows (0x697980 with flag 321, else
// 0x697A50): its weaknesses' lines (one of them, or 521 / 980 for two or more), else its null / repel / drain lines,
// else the generic row (encounter 417 takes each row's first line). K_Assert for an id >= 0x150.
// Arguments: a0 the enemy btlUnit.
void sub_2DBB00(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dbb00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    // no line in the FES boss fights 433..435
    jal(ctx, 0x2DBB28u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x002dbb38
        charge(ctx, 5);
        jal(ctx, 0x2DBB38u, gen::fn_btlGetEncounterId_002d5550);
        v1 = 435;
        if (v0 != v1) {
            // 0x002dbb4c
            charge(ctx, 3);
            v1 = 434;
            if (v0 != v1) {
                // 0x002dbb58
                charge(ctx, 3);
                v1 = 433;
                if (v0 != v1) {
                    // 0x002dbb64
                    charge(ctx, 2);
                    goto L_002dbb78;
                }
            }
        }
        charge(ctx, 3);
        v0 = si(-1);
        // 0x002dbe84 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(ra, sp, 0x70);
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
L_002dbb78:
    charge(ctx, 4);
    // K_Assert for an enemy id beyond the table (336 rows)
    lhu(v0, s4, unit::kId);
    v0 = slti(v0, 336);
    if (v0 == 0) {
        // 0x002dbb88
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, 31512);  // "btlSupport.c"
        a1 = 2415;
        jal(ctx, 0x2DBB94u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002dbb9c
    charge(ctx, 10);
    lhu(v1, s4, unit::kId);
    v0 = sll(v1, 5);
    v0 = subu(v0, v1);
    v1 = sll(v0, 1);
    // an enemy marked silent (gBtlEnemyTbl row +30 bit 0x20): no line
    lw(v0, gp, kGpEnemyTbl);  // gBtlEnemyTbl
    v0 = addu(v1, v0);
    lhu(v0, v0, 30);
    v0 = v0 & 0x20;
    if (v0 == 0) {
        // 0x002dbbd0
        charge(ctx, 5);
        // the element rows: 0x697980 with flag 321, else 0x697A50 (10 rows of 18 bytes)
        a0 = 321;
        jal(ctx, 0x2DBBD4u, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x002dbbf4
            charge(ctx, 2);
            s0 = 0x690000;
            s0 = addiu(s0, 31312);  // &0x697A50
        } else {
            // 0x002dbbe4
            charge(ctx, 4);
            s0 = 0x690000;
            s0 = addiu(s0, 31104);  // &0x697980
        }
        // 0x002dbbfc
        charge(ctx, 5);
        s1 = 0;
        s2 = 0;
        s3 = 0;
        // each element the enemy is weak to (affinity 0x8000000): one of its row's lines
        // (encounter 417: the first)
        for (;;) {
            // 0x002dbce8
            charge(ctx, 5);
            v1 = dsll32(s3, 16);
            v1 = dsra32(v1, 16);
            v0 = slti(v1, 10);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x002dbc10
            charge(ctx, 8);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            s5 = addu(s0, v0);
            s6 = addiu(s5, 6);
            lbu(v0, s5, 6);
            if (v0 != 0) {
                // 0x002dbc30
                charge(ctx, 8);
                lw(a0, s4, unit::kDat);
                a1 = s3;
                jal(ctx, 0x2DBC38u, gen::fn_datCalcGetAffinity_00306e80);
                v1 = 0x8000000;
                v0 = v0 & v1;
                if (v0 != 0) {
                    // 0x002dbc50
                    charge(ctx, 6);
                    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                    lw(v0, v0, gbtl::kSetupEnemies);
                    lhu(v1, v0, 8);
                    v0 = 417;
                    if (v1 == v0) {
                        // 0x002dbc70
                        charge(ctx, 7);
                        lhu(v1, s5, 8);
                        v0 = s2 & 0xFFFF;
                        v0 = sll(v0, 1);
                        v0 = addu(v0, sp);
                        sh(v1, v0, 128);
                    } else {
                        // 0x002dbc68
                        charge(ctx, 2);
                        // 0x002dbc8c
                        charge(ctx, 16);
                        v1 = dsll32(s3, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 1);
                        s5 = addu(s0, v0);
                        lbu(a0, s6, 0);
                        jal(ctx, 0x2DBCA8u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                        v0 = sll(v0, 1);
                        v0 = addu(s5, v0);
                        lhu(v1, v0, 0);
                        v0 = s2 & 0xFFFF;
                        v0 = sll(v0, 1);
                        v0 = addu(v0, sp);
                        sh(v1, v0, 128);
                    }
                    // 0x002dbccc
                    charge(ctx, 4);
                    v0 = addiu(s2, 1);
                    s2 = v0 & 0xFFFF;
                    v0 = addiu(s1, 1);
                    s1 = v0 & 0xFFFF;
                }
            }
            // 0x002dbcdc
            charge(ctx, 3);
            v0 = addiu(s3, 1);
            s3 = dsll32(v0, 16);
            s3 = dsra32(s3, 16);
        }
        // 0x002dbcfc
        charge(ctx, 3);
        a0 = s2 & 0xFFFF;
        // no weakness: the null / repel / drain lines (affinity 0x7000000), else the generic row;
        // two or more weaknesses: 521 / 980
        if (i64(a0) <= 0) {
            // 0x002dbd60
            charge(ctx, 4);
            s3 = 0;
            s2 = 0;
            for (;;) {
                // 0x002dbe04
                charge(ctx, 5);
                v1 = dsll32(s2, 16);
                v1 = dsra32(v1, 16);
                v0 = slti(v1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x002dbd70
                charge(ctx, 8);
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v0 = addu(s0, v0);
                s1 = addiu(v0, 16);
                lbu(v0, v0, 16);
                if (v0 != 0) {
                    // 0x002dbd90
                    charge(ctx, 8);
                    lw(a0, s4, unit::kDat);
                    a1 = s2;
                    jal(ctx, 0x2DBD98u, gen::fn_datCalcGetAffinity_00306e80);
                    v1 = 0x7000000;
                    v0 = v0 & v1;
                    if (v0 != 0) {
                        // 0x002dbdb0
                        charge(ctx, 18);
                        v1 = dsll32(s2, 16);
                        v1 = dsra32(v1, 16);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 1);
                        s5 = addu(s0, v0);
                        lbu(a0, s1, 0);
                        jal(ctx, 0x2DBDCCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                        v0 = sll(v0, 1);
                        v0 = addu(s5, v0);
                        lhu(v1, v0, 10);
                        v0 = s3 & 0xFFFF;
                        v0 = sll(v0, 1);
                        v0 = addu(v0, sp);
                        sh(v1, v0, 128);
                        v0 = addiu(s3, 1);
                        s3 = v0 & 0xFFFF;
                    }
                }
                // 0x002dbdf8
                charge(ctx, 3);
                v0 = addiu(s2, 1);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
            }
            // 0x002dbe18
            charge(ctx, 3);
            a0 = s3 & 0xFFFF;
            if (i64(a0) <= 0) {
                // 0x002dbe40
                charge(ctx, 6);
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(v0, v0, gbtl::kSetupEnemies);
                lhu(v1, v0, 8);
                v0 = 417;
                if (v1 == v0) {
                    // 0x002dbe60
                    charge(ctx, 3);
                    lhu(v0, s0, 188);
                } else {
                    // 0x002dbe58
                    charge(ctx, 2);
                    // 0x002dbe6c
                    charge(ctx, 6);
                    lbu(a0, s0, 186);
                    jal(ctx, 0x2DBE70u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s0);
                    lhu(v0, v0, 180);
                }
            } else {
                // 0x002dbe24
                charge(ctx, 7);
                jal(ctx, 0x2DBE24u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sll(v0, 1);
                v0 = addu(v0, sp);
                lhu(v0, v0, 128);
            }
        } else {
            // 0x002dbd08
            charge(ctx, 4);
            v0 = s1 & 0xFFFF;
            at = slti(v0, 2);
            if (at != 0) {
                // 0x002dbd44
                charge(ctx, 7);
                jal(ctx, 0x2DBD44u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sll(v0, 1);
                v0 = addu(v0, sp);
                lhu(v0, v0, 128);
            } else {
                // 0x002dbd18
                charge(ctx, 5);
                a0 = 321;
                jal(ctx, 0x2DBD1Cu, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x002dbd38
                    charge(ctx, 1);
                    v0 = 980;
                } else {
                    // 0x002dbd2c
                    charge(ctx, 3);
                    v0 = 521;
                }
                // 0x002dbd3c
                charge(ctx, 2);
            }
        }
    } else {
        // 0x002dbbc4
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002dbe84 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x002DD180 sub_2DD180 -- 40 bytes; frame 0x10: ra sp+0x0
// Sound packet start callback: sub_10A0E0(0, id at data +0).
// Arguments: a0 the packet data {s16 id, ...}.
void sub_2DD180(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd180
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(a1, a0, 0);
    a0 = 0;
    jal(ctx, 0x2DD190u, gen::fn_sub_10A0E0_0010a0e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DD1B0 sub_2DD1B0 -- 52 bytes; frame 0x10: ra sp+0x0
// Sound packet update: sub_10A4E0(0, data +0, +2, +4); returns 1.
// Arguments: a0 the packet data {s16 x3}.
void sub_2DD1B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd1b0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(a1, a0, 0);
    lh(a2, a0, 2);
    lh(a3, a0, 4);
    a0 = 0;
    jal(ctx, 0x2DD1C8u, gen::fn_sub_10A4E0_0010a4e0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DD1F0 sub_2DD1F0 -- 116 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the sound packet of sub_2DD180 / sub_2DD1B0 (kind 2305, 6 data bytes) for three shorts.
// Arguments: a0..a2 s16.
void sub_2DD1F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd1f0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 2305;
    a1 = 6;
    jal(ctx, 0x2DD218u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    v1 = 0x2E0000;
    v1 = addiu(v1, -11904);  // &sub_2DD180
    sw(v1, v0, pkt::kOnQueue);
    v1 = 0x2E0000;
    v1 = addiu(v1, -11856);  // &sub_2DD1B0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s2, v1, 0);
    sh(s1, v1, 2);
    sh(s0, v1, 4);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DD720 sub_2DD720 -- 52 bytes; frame 0x10: ra sp+0x0
// Sound packet update: sub_10A240(data +0, +4, +8); returns 1.
// Arguments: a0 the packet data {s16, u32, s16}.
void sub_2DD720(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd720
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0;
    lh(a2, a0, 8);
    lh(a0, a0, 0);
    lw(a1, v0, 4);
    jal(ctx, 0x2DD738u, gen::fn_sub_10A240_0010a240);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DD760 sub_2DD760 -- 104 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the sound packet of sub_2DD720 (kind 2311, 12 data bytes).
// Arguments: a0 s16, a1 u32, a2 u32.
void sub_2DD760(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd760
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 2311;
    a1 = 12;
    jal(ctx, 0x2DD788u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    v1 = 0x2E0000;
    v1 = addiu(v1, -10464);  // &sub_2DD720
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s2, v1, 0);
    sw(s1, v1, 4);
    sw(s0, v1, 8);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002DD7D0 sub_2DD7D0 -- 92 bytes; frame 0x10: ra sp+0x0
// Motion packet update: when the unit's model is loaded (+152 bit 1) plays the motion (sub_31F6D0 on the model +1016)
// with the three shorts of the data; returns 1.
// Arguments: a0 the packet data {btlUnit, u16 x3}.
void sub_2DD7D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd7d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a3 = a0;
    lw(v1, a0, 0);
    lw(v0, v1, 152);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        // 0x002dd7fc
        charge(ctx, 8);
        lw(v0, v1, 2548);
        a0 = addiu(v0, 1016);
        lhu(a1, a3, 4);
        lhu(a2, a3, 6);
        lhu(a3, a3, 8);
        jal(ctx, 0x2DD810u, gen::fn_sub_31F6D0_0031f6d0);
        v0 = 1;
    } else {
        // 0x002dd7f0
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002dd81c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DD830 sub_2DD830 -- 120 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the motion packet of sub_2DD7D0 (kind 2312, 12 data bytes).
// Arguments: a0 the btlUnit, a1..a3 u16.
void sub_2DD830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dd830
    enter(ctx, 30);  // entry check point + this block's cycles
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
    a0 = 2312;
    a1 = 12;
    jal(ctx, 0x2DD860u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    v1 = 0x2E0000;
    v1 = addiu(v1, -10288);  // &sub_2DD7D0
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sw(s3, v1, 0);
    sh(s2, v1, 4);
    sh(s1, v1, 6);
    sh(s0, v1, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x002DDDC0 sub_2DDDC0 -- 328 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlVoicePick1] Party voice picker 1 (table 0x697C10): with flag 388 set, the acting member's line (146, 219 / 220
// by the flag *0x697BE4, 328, 401, 474, 547, 620 / 1117, 685); -1 otherwise. returns -1 for a non-party unit; the
// party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
// Arguments: a0 the btlAction.
void sub_2DDDC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002dddc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 388;
    jal(ctx, 0x2DDDD4u, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x002dddf0
        charge(ctx, 4);
        lw(v1, s0, act::kUnit);
        lbu(v0, v1, unit::kSide);
        if (v0 == 0) {
            // 0x002dde0c
            charge(ctx, 4);
            lhu(v0, v1, unit::kId);
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x002dde1c
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -32704);  // &0x7B8040
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2DDE38u:  // table[2]: unit id 2
                    // 0x002dde38
                    charge(ctx, 3);
                    v0 = 146;
                    break;
                case 0x2DDE44u:  // table[3]: unit id 3
                    // 0x002dde44
                    charge(ctx, 5);
                    v0 = 0x690000;
                    lw(a0, v0, 31716);  // 0x697BE4
                    v0 = si(-1);
                    if (a0 != v0) {
                        // 0x002dde64
                        charge(ctx, 2);
                        jal(ctx, 0x2DDE64u, gen::fn_datGetFlag_0016f190);
                    } else {
                        // 0x002dde58
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x002dde6c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x002dde80
                        charge(ctx, 1);
                        v0 = 219;
                    } else {
                        // 0x002dde74
                        charge(ctx, 3);
                        v0 = 220;
                    }
                    // 0x002dde84
                    charge(ctx, 2);
                    break;
                case 0x2DDE8Cu:  // table[4]: unit id 4
                    // 0x002dde8c
                    charge(ctx, 3);
                    v0 = 328;
                    break;
                case 0x2DDE98u:  // table[5]: unit id 5
                    // 0x002dde98
                    charge(ctx, 3);
                    v0 = 401;
                    break;
                case 0x2DDEA4u:  // table[7]: unit id 7
                    // 0x002ddea4
                    charge(ctx, 3);
                    v0 = 474;
                    break;
                case 0x2DDEB0u:  // table[8]: unit id 8
                    // 0x002ddeb0
                    charge(ctx, 3);
                    v0 = 547;
                    break;
                case 0x2DDEBCu:  // table[9]: unit id 9
                    // 0x002ddebc
                    charge(ctx, 4);
                    jal(ctx, 0x2DDEBCu, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x002dded8
                        charge(ctx, 1);
                        v0 = 620;
                    } else {
                        // 0x002ddecc
                        charge(ctx, 3);
                        v0 = 1117;
                    }
                    // 0x002ddedc
                    charge(ctx, 2);
                    break;
                case 0x2DDEE4u:  // table[10]: unit id 10
                    // 0x002ddee4
                    charge(ctx, 3);
                    v0 = 685;
                    break;
                case 0x2DDEF0u:  // table[0, 1, 6]
                L_002ddef0:
                    charge(ctx, 1);
                    v0 = si(-1);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
                // 0x002ddef4 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
            goto L_002ddef0;
        }
        // 0x002dde00
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x002ddde4
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002ddef4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002DDF10 sub_2DDF10 -- 284 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick2] Party voice picker 2 (table 0x697C10): the acting member's line 147, 221 / 222, 329, 402, 475, 548,
// 621 / 1118, 686. returns -1 for a non-party unit; the party members 2..10 each have their own line (unit id 9 two,
// by sub_17D800).
// Arguments: a0 the btlAction.
void sub_2DDF10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ddf10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002ddf34
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002ddf44
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -32656);  // &0x7B8070
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2DDF60u:  // table[2]: unit id 2
                // 0x002ddf60
                charge(ctx, 3);
                v0 = 147;
                break;
            case 0x2DDF6Cu:  // table[3]: unit id 3
                // 0x002ddf6c
                charge(ctx, 5);
                v0 = 0x690000;
                lw(a0, v0, 31716);  // 0x697BE4
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x002ddf8c
                    charge(ctx, 2);
                    jal(ctx, 0x2DDF8Cu, gen::fn_datGetFlag_0016f190);
                } else {
                    // 0x002ddf80
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x002ddf94
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002ddfa8
                    charge(ctx, 1);
                    v0 = 221;
                } else {
                    // 0x002ddf9c
                    charge(ctx, 3);
                    v0 = 222;
                }
                // 0x002ddfac
                charge(ctx, 2);
                break;
            case 0x2DDFB4u:  // table[4]: unit id 4
                // 0x002ddfb4
                charge(ctx, 3);
                v0 = 329;
                break;
            case 0x2DDFC0u:  // table[5]: unit id 5
                // 0x002ddfc0
                charge(ctx, 3);
                v0 = 402;
                break;
            case 0x2DDFCCu:  // table[7]: unit id 7
                // 0x002ddfcc
                charge(ctx, 3);
                v0 = 475;
                break;
            case 0x2DDFD8u:  // table[8]: unit id 8
                // 0x002ddfd8
                charge(ctx, 3);
                v0 = 548;
                break;
            case 0x2DDFE4u:  // table[9]: unit id 9
                // 0x002ddfe4
                charge(ctx, 4);
                jal(ctx, 0x2DDFE4u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002de000
                    charge(ctx, 1);
                    v0 = 621;
                } else {
                    // 0x002ddff4
                    charge(ctx, 3);
                    v0 = 1118;
                }
                // 0x002de004
                charge(ctx, 2);
                break;
            case 0x2DE00Cu:  // table[10]: unit id 10
                // 0x002de00c
                charge(ctx, 3);
                v0 = 686;
                break;
            case 0x2DE018u:  // table[0, 1, 6]
            L_002de018:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002de01c (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002de018;
    }
    // 0x002ddf28
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002de01c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DE030 sub_2DE030 -- 284 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick3] Party voice picker 3 (table 0x697C10): the next row of the same scheme (148, 223 / 224, 330, ...).
// returns -1 for a non-party unit; the party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
// Arguments: a0 the btlAction.
void sub_2DE030(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002de030
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002de054
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002de064
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -32608);  // &0x7B80A0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2DE080u:  // table[2]: unit id 2
                // 0x002de080
                charge(ctx, 3);
                v0 = 148;
                break;
            case 0x2DE08Cu:  // table[3]: unit id 3
                // 0x002de08c
                charge(ctx, 5);
                v0 = 0x690000;
                lw(a0, v0, 31716);  // 0x697BE4
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x002de0ac
                    charge(ctx, 2);
                    jal(ctx, 0x2DE0ACu, gen::fn_datGetFlag_0016f190);
                } else {
                    // 0x002de0a0
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x002de0b4
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002de0c8
                    charge(ctx, 1);
                    v0 = 223;
                } else {
                    // 0x002de0bc
                    charge(ctx, 3);
                    v0 = 224;
                }
                // 0x002de0cc
                charge(ctx, 2);
                break;
            case 0x2DE0D4u:  // table[4]: unit id 4
                // 0x002de0d4
                charge(ctx, 3);
                v0 = 330;
                break;
            case 0x2DE0E0u:  // table[5]: unit id 5
                // 0x002de0e0
                charge(ctx, 3);
                v0 = 403;
                break;
            case 0x2DE0ECu:  // table[7]: unit id 7
                // 0x002de0ec
                charge(ctx, 3);
                v0 = 476;
                break;
            case 0x2DE0F8u:  // table[8]: unit id 8
                // 0x002de0f8
                charge(ctx, 3);
                v0 = 549;
                break;
            case 0x2DE104u:  // table[9]: unit id 9
                // 0x002de104
                charge(ctx, 4);
                jal(ctx, 0x2DE104u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002de120
                    charge(ctx, 1);
                    v0 = 622;
                } else {
                    // 0x002de114
                    charge(ctx, 3);
                    v0 = 1119;
                }
                // 0x002de124
                charge(ctx, 2);
                break;
            case 0x2DE12Cu:  // table[10]: unit id 10
                // 0x002de12c
                charge(ctx, 3);
                v0 = 687;
                break;
            case 0x2DE138u:  // table[0, 1, 6]
            L_002de138:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002de13c (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002de138;
    }
    // 0x002de048
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002de13c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002DEFE0 sub_2DEFE0 -- 4964 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlVoicePickAboutMember] Party voice picker 9 (table 0x697C10): a line about another member: -1 while bank 4 plays
// (sub_10A500) or the speaker is not a living party member; else a random living, ailment-free member other than the
// hero is drawn and the line is looked up by speaker x subject (each pair two lines, 50 % each; unit 9 by
// sub_17D800).
// Arguments: a0 the btlAction.
void sub_2DEFE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002defe0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    a0 = 4;
    jal(ctx, 0x2DEFFCu, gen::fn_sub_10A500_0010a500);
    a1 = 1;
    if (v0 != a1) {
        // 0x002df01c
        charge(ctx, 4);
        lw(v1, s2, act::kUnit);
        lbu(v0, v1, unit::kSide);
        if (v0 == 0) {
            // 0x002df038
            charge(ctx, 5);
            lw(a0, v1, unit::kDat);
            jal(ctx, 0x2DF03Cu, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                // 0x002df058
                charge(ctx, 5);
                s0 = 0;
                lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
                lw(s1, v0, gbtl::kUnitTail0);
                for (;;) {
                    // 0x002df0cc
                    charge(ctx, 2);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x002df06c
                    charge(ctx, 6);
                    lw(a0, s1, unit::kDat);
                    a1 = 0;
                    jal(ctx, 0x2DF074u, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x002df084
                        charge(ctx, 7);
                        lw(a0, s1, unit::kDat);
                        v0 = 0x180000;
                        a1 = v0 | 0x375;  // the statuses that keep a member quiet (0x180375)
                        jal(ctx, 0x2DF090u, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 == 0) {
                            // 0x002df0a0
                            charge(ctx, 4);
                            lhu(v1, s1, unit::kId);
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x002df0b0
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
                    // 0x002df0c8
                    charge(ctx, 1);
                    lw(s1, s1, unit::kPrev);
                }
                // 0x002df0d4
                charge(ctx, 3);
                a0 = s0 & 0xFFFF;
                if (a0 != 0) {
                    // 0x002df0ec
                    charge(ctx, 7);
                    jal(ctx, 0x2DF0ECu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                    v0 = sll(v0, 2);
                    v0 = addu(v0, sp);
                    lw(s0, v0, 64);
                    if (s0 != 0) {
                        // 0x002df114
                        charge(ctx, 5);
                        lw(v0, s2, act::kUnit);
                        lhu(v0, v0, unit::kId);
                        at = sltiu(v0, 11);
                        if (at != 0) {
                            // 0x002df128
                            charge(ctx, 7);
                            v1 = 0x7C0000;
                            v1 = addiu(v1, -31744);  // &0x7B8400
                            v0 = sll(v0, 2);
                            v0 = addu(v0, v1);
                            lw(v0, v0, 0);
                            switch (v0.u()) {
                            case 0x2DF144u:  // table[1]: unit id 1
                                // 0x002df144
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                L_002e0324:
                                    charge(ctx, 1);
                                    v0 = si(-1);
                                } else {
                                    // 0x002df154
                                    charge(ctx, 7);
                                    v1 = 0x7C0000;
                                    v1 = addiu(v1, -31792);  // &0x7B83D0
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x2DF170u:  // table[2]: unit id 2
                                        // 0x002df170
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF174u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df194
                                            charge(ctx, 1);
                                            v0 = 178;
                                        } else {
                                            // 0x002df188
                                            charge(ctx, 3);
                                            v0 = 177;
                                        }
                                        // 0x002df198
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DF1A0u:  // table[3]: unit id 3
                                        // 0x002df1a0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF1A4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df1c4
                                            charge(ctx, 1);
                                            v0 = 272;
                                        } else {
                                            // 0x002df1b8
                                            charge(ctx, 3);
                                            v0 = 271;
                                        }
                                        // 0x002df1c8
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DF1D0u:  // table[4]: unit id 4
                                        // 0x002df1d0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF1D4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df1f4
                                            charge(ctx, 1);
                                            v0 = 360;
                                        } else {
                                            // 0x002df1e8
                                            charge(ctx, 3);
                                            v0 = 359;
                                        }
                                        // 0x002df1f8
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DF200u:  // table[5]: unit id 5
                                        // 0x002df200
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF204u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df224
                                            charge(ctx, 1);
                                            v0 = 433;
                                        } else {
                                            // 0x002df218
                                            charge(ctx, 3);
                                            v0 = 432;
                                        }
                                        // 0x002df228
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DF230u:  // table[7]: unit id 7
                                        // 0x002df230
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF234u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df254
                                            charge(ctx, 1);
                                            v0 = 506;
                                        } else {
                                            // 0x002df248
                                            charge(ctx, 3);
                                            v0 = 505;
                                        }
                                        // 0x002df258
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DF260u:  // table[8]: unit id 8
                                        // 0x002df260
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF264u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df284
                                            charge(ctx, 1);
                                            v0 = 579;
                                        } else {
                                            // 0x002df278
                                            charge(ctx, 3);
                                            v0 = 578;
                                        }
                                        // 0x002df288
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DF290u:  // table[9]: unit id 9
                                        // 0x002df290
                                        charge(ctx, 4);
                                        jal(ctx, 0x2DF290u, gen::fn_sub_17D800_0017d800);
                                        if (v0 != 0) {
                                            // 0x002df2d0
                                            charge(ctx, 6);
                                            a0 = 100;
                                            jal(ctx, 0x2DF2D4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                            v0 = sltiu(v0, 50);
                                            if (v0 != 0) {
                                                // 0x002df2f4
                                                charge(ctx, 1);
                                                v0 = 1151;
                                            } else {
                                                // 0x002df2e8
                                                charge(ctx, 3);
                                                v0 = 1150;
                                            }
                                            // 0x002df2f8
                                            charge(ctx, 2);
                                        } else {
                                            // 0x002df2a0
                                            charge(ctx, 6);
                                            a0 = 100;
                                            jal(ctx, 0x2DF2A4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                            v0 = sltiu(v0, 50);
                                            if (v0 != 0) {
                                                // 0x002df2c4
                                                charge(ctx, 1);
                                                v0 = 644;
                                            } else {
                                                // 0x002df2b8
                                                charge(ctx, 3);
                                                v0 = 643;
                                            }
                                            // 0x002df2c8
                                            charge(ctx, 2);
                                        }
                                        break;
                                    case 0x2DF300u:  // table[10]: unit id 10
                                        // 0x002df300
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                        break;
                                    case 0x2E0324u:  // table[0, 1, 6]
                                        goto L_002e0324;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                }
                                break;
                            case 0x2DF30Cu:  // table[2]: unit id 2
                                // 0x002df30c
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002df31c
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -31840);  // &0x7B83A0
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2DF338u:  // table[2]: unit id 2
                                    // 0x002df338
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF33Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df35c
                                        charge(ctx, 1);
                                        v0 = 180;
                                    } else {
                                        // 0x002df350
                                        charge(ctx, 3);
                                        v0 = 179;
                                    }
                                    // 0x002df360
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF368u:  // table[3]: unit id 3
                                    // 0x002df368
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF36Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df38c
                                        charge(ctx, 1);
                                        v0 = 274;
                                    } else {
                                        // 0x002df380
                                        charge(ctx, 3);
                                        v0 = 273;
                                    }
                                    // 0x002df390
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF398u:  // table[4]: unit id 4
                                    // 0x002df398
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF39Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df3bc
                                        charge(ctx, 1);
                                        v0 = 362;
                                    } else {
                                        // 0x002df3b0
                                        charge(ctx, 3);
                                        v0 = 361;
                                    }
                                    // 0x002df3c0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF3C8u:  // table[5]: unit id 5
                                    // 0x002df3c8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF3CCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df3ec
                                        charge(ctx, 1);
                                        v0 = 435;
                                    } else {
                                        // 0x002df3e0
                                        charge(ctx, 3);
                                        v0 = 434;
                                    }
                                    // 0x002df3f0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF3F8u:  // table[7]: unit id 7
                                    // 0x002df3f8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF3FCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df41c
                                        charge(ctx, 1);
                                        v0 = 508;
                                    } else {
                                        // 0x002df410
                                        charge(ctx, 3);
                                        v0 = 507;
                                    }
                                    // 0x002df420
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF428u:  // table[8]: unit id 8
                                    // 0x002df428
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF42Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df44c
                                        charge(ctx, 1);
                                        v0 = 581;
                                    } else {
                                        // 0x002df440
                                        charge(ctx, 3);
                                        v0 = 580;
                                    }
                                    // 0x002df450
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF458u:  // table[9]: unit id 9
                                    // 0x002df458
                                    charge(ctx, 4);
                                    jal(ctx, 0x2DF458u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002df498
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF49Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df4bc
                                            charge(ctx, 1);
                                            v0 = 1153;
                                        } else {
                                            // 0x002df4b0
                                            charge(ctx, 3);
                                            v0 = 1152;
                                        }
                                        // 0x002df4c0
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002df468
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF46Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df48c
                                            charge(ctx, 1);
                                            v0 = 646;
                                        } else {
                                            // 0x002df480
                                            charge(ctx, 3);
                                            v0 = 645;
                                        }
                                        // 0x002df490
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2DF4C8u:  // table[10]: unit id 10
                                    // 0x002df4c8
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2DF4D4u:  // table[3]: unit id 3
                                // 0x002df4d4
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002df4e4
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -31888);  // &0x7B8370
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2DF500u:  // table[2]: unit id 2
                                    // 0x002df500
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF504u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df524
                                        charge(ctx, 1);
                                        v0 = 182;
                                    } else {
                                        // 0x002df518
                                        charge(ctx, 3);
                                        v0 = 181;
                                    }
                                    // 0x002df528
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF530u:  // table[3]: unit id 3
                                    // 0x002df530
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF534u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df554
                                        charge(ctx, 1);
                                        v0 = 276;
                                    } else {
                                        // 0x002df548
                                        charge(ctx, 3);
                                        v0 = 275;
                                    }
                                    // 0x002df558
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF560u:  // table[4]: unit id 4
                                    // 0x002df560
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF564u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df584
                                        charge(ctx, 1);
                                        v0 = 364;
                                    } else {
                                        // 0x002df578
                                        charge(ctx, 3);
                                        v0 = 363;
                                    }
                                    // 0x002df588
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF590u:  // table[5]: unit id 5
                                    // 0x002df590
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF594u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df5b4
                                        charge(ctx, 1);
                                        v0 = 437;
                                    } else {
                                        // 0x002df5a8
                                        charge(ctx, 3);
                                        v0 = 436;
                                    }
                                    // 0x002df5b8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF5C0u:  // table[7]: unit id 7
                                    // 0x002df5c0
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF5C4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df5e4
                                        charge(ctx, 1);
                                        v0 = 510;
                                    } else {
                                        // 0x002df5d8
                                        charge(ctx, 3);
                                        v0 = 509;
                                    }
                                    // 0x002df5e8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF5F0u:  // table[8]: unit id 8
                                    // 0x002df5f0
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF5F4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df614
                                        charge(ctx, 1);
                                        v0 = 583;
                                    } else {
                                        // 0x002df608
                                        charge(ctx, 3);
                                        v0 = 582;
                                    }
                                    // 0x002df618
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF620u:  // table[9]: unit id 9
                                    // 0x002df620
                                    charge(ctx, 4);
                                    jal(ctx, 0x2DF620u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002df660
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF664u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df684
                                            charge(ctx, 1);
                                            v0 = 1155;
                                        } else {
                                            // 0x002df678
                                            charge(ctx, 3);
                                            v0 = 1154;
                                        }
                                        // 0x002df688
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002df630
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF634u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df654
                                            charge(ctx, 1);
                                            v0 = 648;
                                        } else {
                                            // 0x002df648
                                            charge(ctx, 3);
                                            v0 = 647;
                                        }
                                        // 0x002df658
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2DF690u:  // table[10]: unit id 10
                                    // 0x002df690
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2DF69Cu:  // table[4]: unit id 4
                                // 0x002df69c
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002df6ac
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -31936);  // &0x7B8340
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2DF6C8u:  // table[2]: unit id 2
                                    // 0x002df6c8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF6CCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df6ec
                                        charge(ctx, 1);
                                        v0 = 184;
                                    } else {
                                        // 0x002df6e0
                                        charge(ctx, 3);
                                        v0 = 183;
                                    }
                                    // 0x002df6f0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF6F8u:  // table[3]: unit id 3
                                    // 0x002df6f8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF6FCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df71c
                                        charge(ctx, 1);
                                        v0 = 278;
                                    } else {
                                        // 0x002df710
                                        charge(ctx, 3);
                                        v0 = 277;
                                    }
                                    // 0x002df720
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF728u:  // table[4]: unit id 4
                                    // 0x002df728
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF72Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df74c
                                        charge(ctx, 1);
                                        v0 = 366;
                                    } else {
                                        // 0x002df740
                                        charge(ctx, 3);
                                        v0 = 365;
                                    }
                                    // 0x002df750
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF758u:  // table[5]: unit id 5
                                    // 0x002df758
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF75Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df77c
                                        charge(ctx, 1);
                                        v0 = 439;
                                    } else {
                                        // 0x002df770
                                        charge(ctx, 3);
                                        v0 = 438;
                                    }
                                    // 0x002df780
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF788u:  // table[7]: unit id 7
                                    // 0x002df788
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF78Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df7ac
                                        charge(ctx, 1);
                                        v0 = 512;
                                    } else {
                                        // 0x002df7a0
                                        charge(ctx, 3);
                                        v0 = 511;
                                    }
                                    // 0x002df7b0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF7B8u:  // table[8]: unit id 8
                                    // 0x002df7b8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF7BCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df7dc
                                        charge(ctx, 1);
                                        v0 = 585;
                                    } else {
                                        // 0x002df7d0
                                        charge(ctx, 3);
                                        v0 = 584;
                                    }
                                    // 0x002df7e0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF7E8u:  // table[9]: unit id 9
                                    // 0x002df7e8
                                    charge(ctx, 4);
                                    jal(ctx, 0x2DF7E8u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002df828
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF82Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df84c
                                            charge(ctx, 1);
                                            v0 = 1157;
                                        } else {
                                            // 0x002df840
                                            charge(ctx, 3);
                                            v0 = 1156;
                                        }
                                        // 0x002df850
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002df7f8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF7FCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df81c
                                            charge(ctx, 1);
                                            v0 = 650;
                                        } else {
                                            // 0x002df810
                                            charge(ctx, 3);
                                            v0 = 649;
                                        }
                                        // 0x002df820
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2DF858u:  // table[10]: unit id 10
                                    // 0x002df858
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2DF864u:  // table[5]: unit id 5
                                // 0x002df864
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002df874
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -31984);  // &0x7B8310
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2DF890u:  // table[2]: unit id 2
                                    // 0x002df890
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF894u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df8b4
                                        charge(ctx, 1);
                                        v0 = 186;
                                    } else {
                                        // 0x002df8a8
                                        charge(ctx, 3);
                                        v0 = 185;
                                    }
                                    // 0x002df8b8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF8C0u:  // table[3]: unit id 3
                                    // 0x002df8c0
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF8C4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df8e4
                                        charge(ctx, 1);
                                        v0 = 280;
                                    } else {
                                        // 0x002df8d8
                                        charge(ctx, 3);
                                        v0 = 279;
                                    }
                                    // 0x002df8e8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF8F0u:  // table[4]: unit id 4
                                    // 0x002df8f0
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF8F4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df914
                                        charge(ctx, 1);
                                        v0 = 368;
                                    } else {
                                        // 0x002df908
                                        charge(ctx, 3);
                                        v0 = 367;
                                    }
                                    // 0x002df918
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF920u:  // table[5]: unit id 5
                                    // 0x002df920
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF924u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df944
                                        charge(ctx, 1);
                                        v0 = 441;
                                    } else {
                                        // 0x002df938
                                        charge(ctx, 3);
                                        v0 = 440;
                                    }
                                    // 0x002df948
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF950u:  // table[7]: unit id 7
                                    // 0x002df950
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF954u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df974
                                        charge(ctx, 1);
                                        v0 = 514;
                                    } else {
                                        // 0x002df968
                                        charge(ctx, 3);
                                        v0 = 513;
                                    }
                                    // 0x002df978
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF980u:  // table[8]: unit id 8
                                    // 0x002df980
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DF984u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002df9a4
                                        charge(ctx, 1);
                                        v0 = 587;
                                    } else {
                                        // 0x002df998
                                        charge(ctx, 3);
                                        v0 = 586;
                                    }
                                    // 0x002df9a8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DF9B0u:  // table[9]: unit id 9
                                    // 0x002df9b0
                                    charge(ctx, 4);
                                    jal(ctx, 0x2DF9B0u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002df9f0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF9F4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfa14
                                            charge(ctx, 1);
                                            v0 = 1159;
                                        } else {
                                            // 0x002dfa08
                                            charge(ctx, 3);
                                            v0 = 1158;
                                        }
                                        // 0x002dfa18
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002df9c0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DF9C4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002df9e4
                                            charge(ctx, 1);
                                            v0 = 652;
                                        } else {
                                            // 0x002df9d8
                                            charge(ctx, 3);
                                            v0 = 651;
                                        }
                                        // 0x002df9e8
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2DFA20u:  // table[10]: unit id 10
                                    // 0x002dfa20
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2DFA2Cu:  // table[7]: unit id 7
                                // 0x002dfa2c
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002dfa3c
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -32032);  // &0x7B82E0
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2DFA58u:  // table[2]: unit id 2
                                    // 0x002dfa58
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFA5Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfa7c
                                        charge(ctx, 1);
                                        v0 = 188;
                                    } else {
                                        // 0x002dfa70
                                        charge(ctx, 3);
                                        v0 = 187;
                                    }
                                    // 0x002dfa80
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFA88u:  // table[3]: unit id 3
                                    // 0x002dfa88
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFA8Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfaac
                                        charge(ctx, 1);
                                        v0 = 282;
                                    } else {
                                        // 0x002dfaa0
                                        charge(ctx, 3);
                                        v0 = 281;
                                    }
                                    // 0x002dfab0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFAB8u:  // table[4]: unit id 4
                                    // 0x002dfab8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFABCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfadc
                                        charge(ctx, 1);
                                        v0 = 370;
                                    } else {
                                        // 0x002dfad0
                                        charge(ctx, 3);
                                        v0 = 369;
                                    }
                                    // 0x002dfae0
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFAE8u:  // table[5]: unit id 5
                                    // 0x002dfae8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFAECu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfb0c
                                        charge(ctx, 1);
                                        v0 = 443;
                                    } else {
                                        // 0x002dfb00
                                        charge(ctx, 3);
                                        v0 = 442;
                                    }
                                    // 0x002dfb10
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFB18u:  // table[7]: unit id 7
                                    // 0x002dfb18
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFB1Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfb3c
                                        charge(ctx, 1);
                                        v0 = 516;
                                    } else {
                                        // 0x002dfb30
                                        charge(ctx, 3);
                                        v0 = 515;
                                    }
                                    // 0x002dfb40
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFB48u:  // table[8]: unit id 8
                                    // 0x002dfb48
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFB4Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfb6c
                                        charge(ctx, 1);
                                        v0 = 589;
                                    } else {
                                        // 0x002dfb60
                                        charge(ctx, 3);
                                        v0 = 588;
                                    }
                                    // 0x002dfb70
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFB78u:  // table[9]: unit id 9
                                    // 0x002dfb78
                                    charge(ctx, 4);
                                    jal(ctx, 0x2DFB78u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002dfbb8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFBBCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfbdc
                                            charge(ctx, 1);
                                            v0 = 1161;
                                        } else {
                                            // 0x002dfbd0
                                            charge(ctx, 3);
                                            v0 = 1160;
                                        }
                                        // 0x002dfbe0
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002dfb88
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFB8Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfbac
                                            charge(ctx, 1);
                                            v0 = 654;
                                        } else {
                                            // 0x002dfba0
                                            charge(ctx, 3);
                                            v0 = 653;
                                        }
                                        // 0x002dfbb0
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2DFBE8u:  // table[10]: unit id 10
                                    // 0x002dfbe8
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2DFBF4u:  // table[8]: unit id 8
                                // 0x002dfbf4
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002dfc04
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -32080);  // &0x7B82B0
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2DFC20u:  // table[2]: unit id 2
                                    // 0x002dfc20
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFC24u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfc44
                                        charge(ctx, 1);
                                        v0 = 190;
                                    } else {
                                        // 0x002dfc38
                                        charge(ctx, 3);
                                        v0 = 189;
                                    }
                                    // 0x002dfc48
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFC50u:  // table[3]: unit id 3
                                    // 0x002dfc50
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFC54u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfc74
                                        charge(ctx, 1);
                                        v0 = 284;
                                    } else {
                                        // 0x002dfc68
                                        charge(ctx, 3);
                                        v0 = 283;
                                    }
                                    // 0x002dfc78
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFC80u:  // table[4]: unit id 4
                                    // 0x002dfc80
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFC84u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfca4
                                        charge(ctx, 1);
                                        v0 = 372;
                                    } else {
                                        // 0x002dfc98
                                        charge(ctx, 3);
                                        v0 = 371;
                                    }
                                    // 0x002dfca8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFCB0u:  // table[5]: unit id 5
                                    // 0x002dfcb0
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFCB4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfcd4
                                        charge(ctx, 1);
                                        v0 = 445;
                                    } else {
                                        // 0x002dfcc8
                                        charge(ctx, 3);
                                        v0 = 444;
                                    }
                                    // 0x002dfcd8
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFCE0u:  // table[7]: unit id 7
                                    // 0x002dfce0
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFCE4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfd04
                                        charge(ctx, 1);
                                        v0 = 518;
                                    } else {
                                        // 0x002dfcf8
                                        charge(ctx, 3);
                                        v0 = 517;
                                    }
                                    // 0x002dfd08
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFD10u:  // table[8]: unit id 8
                                    // 0x002dfd10
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2DFD14u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002dfd34
                                        charge(ctx, 1);
                                        v0 = 591;
                                    } else {
                                        // 0x002dfd28
                                        charge(ctx, 3);
                                        v0 = 590;
                                    }
                                    // 0x002dfd38
                                    charge(ctx, 2);
                                    break;
                                case 0x2DFD40u:  // table[9]: unit id 9
                                    // 0x002dfd40
                                    charge(ctx, 4);
                                    jal(ctx, 0x2DFD40u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002dfd80
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFD84u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfda4
                                            charge(ctx, 1);
                                            v0 = 1161;
                                        } else {
                                            // 0x002dfd98
                                            charge(ctx, 3);
                                            v0 = 1160;
                                        }
                                        // 0x002dfda8
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002dfd50
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFD54u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfd74
                                            charge(ctx, 1);
                                            v0 = 656;
                                        } else {
                                            // 0x002dfd68
                                            charge(ctx, 3);
                                            v0 = 655;
                                        }
                                        // 0x002dfd78
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2DFDB0u:  // table[10]: unit id 10
                                    // 0x002dfdb0
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2DFDBCu:  // table[9]: unit id 9
                                // 0x002dfdbc
                                charge(ctx, 4);
                                jal(ctx, 0x2DFDBCu, gen::fn_sub_17D800_0017d800);
                                if (v0 != 0) {
                                    // 0x002dff94
                                    charge(ctx, 4);
                                    lhu(v0, s0, 164);
                                    at = sltiu(v0, 11);
                                    if (at == 0) {
                                        goto L_002e0324;
                                    }
                                    // 0x002dffa4
                                    charge(ctx, 7);
                                    v1 = 0x7C0000;
                                    v1 = addiu(v1, -32176);  // &0x7B8250
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x2DFFC0u:  // table[2]: unit id 2
                                        // 0x002dffc0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFFC4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dffe4
                                            charge(ctx, 1);
                                            v0 = 196;
                                        } else {
                                            // 0x002dffd8
                                            charge(ctx, 3);
                                            v0 = 195;
                                        }
                                        // 0x002dffe8
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFFF0u:  // table[3]: unit id 3
                                        // 0x002dfff0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFFF4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e0014
                                            charge(ctx, 1);
                                            v0 = 290;
                                        } else {
                                            // 0x002e0008
                                            charge(ctx, 3);
                                            v0 = 289;
                                        }
                                        // 0x002e0018
                                        charge(ctx, 2);
                                        break;
                                    case 0x2E0020u:  // table[4]: unit id 4
                                        // 0x002e0020
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2E0024u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e0044
                                            charge(ctx, 1);
                                            v0 = 378;
                                        } else {
                                            // 0x002e0038
                                            charge(ctx, 3);
                                            v0 = 377;
                                        }
                                        // 0x002e0048
                                        charge(ctx, 2);
                                        break;
                                    case 0x2E0050u:  // table[5]: unit id 5
                                        // 0x002e0050
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2E0054u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e0074
                                            charge(ctx, 1);
                                            v0 = 451;
                                        } else {
                                            // 0x002e0068
                                            charge(ctx, 3);
                                            v0 = 450;
                                        }
                                        // 0x002e0078
                                        charge(ctx, 2);
                                        break;
                                    case 0x2E0080u:  // table[7]: unit id 7
                                        // 0x002e0080
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2E0084u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e00a4
                                            charge(ctx, 1);
                                            v0 = 524;
                                        } else {
                                            // 0x002e0098
                                            charge(ctx, 3);
                                            v0 = 523;
                                        }
                                        // 0x002e00a8
                                        charge(ctx, 2);
                                        break;
                                    case 0x2E00B0u:  // table[8]: unit id 8
                                        // 0x002e00b0
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2E00B4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e00d4
                                            charge(ctx, 1);
                                            v0 = 597;
                                        } else {
                                            // 0x002e00c8
                                            charge(ctx, 3);
                                            v0 = 596;
                                        }
                                        // 0x002e00d8
                                        charge(ctx, 2);
                                        break;
                                    case 0x2E00E0u:  // table[9]: unit id 9
                                        // 0x002e00e0
                                        charge(ctx, 4);
                                        jal(ctx, 0x2E00E0u, gen::fn_sub_17D800_0017d800);
                                        if (v0 != 0) {
                                            // 0x002e0120
                                            charge(ctx, 6);
                                            a0 = 100;
                                            jal(ctx, 0x2E0124u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                            v0 = sltiu(v0, 50);
                                            if (v0 != 0) {
                                                // 0x002e0144
                                                charge(ctx, 1);
                                                v0 = 1153;
                                            } else {
                                                // 0x002e0138
                                                charge(ctx, 3);
                                                v0 = 1152;
                                            }
                                            // 0x002e0148
                                            charge(ctx, 2);
                                        } else {
                                            // 0x002e00f0
                                            charge(ctx, 6);
                                            a0 = 100;
                                            jal(ctx, 0x2E00F4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                            v0 = sltiu(v0, 50);
                                            if (v0 != 0) {
                                                // 0x002e0114
                                                charge(ctx, 1);
                                                v0 = 662;
                                            } else {
                                                // 0x002e0108
                                                charge(ctx, 3);
                                                v0 = 661;
                                            }
                                            // 0x002e0118
                                            charge(ctx, 2);
                                        }
                                        break;
                                    case 0x2E0150u:  // table[10]: unit id 10
                                        // 0x002e0150
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                        break;
                                    case 0x2E0324u:  // table[0, 1, 6]
                                        goto L_002e0324;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                } else {
                                    // 0x002dfdcc
                                    charge(ctx, 4);
                                    lhu(v0, s0, 164);
                                    at = sltiu(v0, 11);
                                    if (at == 0) {
                                        goto L_002e0324;
                                    }
                                    // 0x002dfddc
                                    charge(ctx, 7);
                                    v1 = 0x7C0000;
                                    v1 = addiu(v1, -32128);  // &0x7B8280
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x2DFDF8u:  // table[2]: unit id 2
                                        // 0x002dfdf8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFDFCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfe1c
                                            charge(ctx, 1);
                                            v0 = 192;
                                        } else {
                                            // 0x002dfe10
                                            charge(ctx, 3);
                                            v0 = 191;
                                        }
                                        // 0x002dfe20
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFE28u:  // table[3]: unit id 3
                                        // 0x002dfe28
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFE2Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfe4c
                                            charge(ctx, 1);
                                            v0 = 286;
                                        } else {
                                            // 0x002dfe40
                                            charge(ctx, 3);
                                            v0 = 285;
                                        }
                                        // 0x002dfe50
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFE58u:  // table[4]: unit id 4
                                        // 0x002dfe58
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFE5Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfe7c
                                            charge(ctx, 1);
                                            v0 = 374;
                                        } else {
                                            // 0x002dfe70
                                            charge(ctx, 3);
                                            v0 = 373;
                                        }
                                        // 0x002dfe80
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFE88u:  // table[5]: unit id 5
                                        // 0x002dfe88
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFE8Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfeac
                                            charge(ctx, 1);
                                            v0 = 447;
                                        } else {
                                            // 0x002dfea0
                                            charge(ctx, 3);
                                            v0 = 446;
                                        }
                                        // 0x002dfeb0
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFEB8u:  // table[7]: unit id 7
                                        // 0x002dfeb8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFEBCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dfedc
                                            charge(ctx, 1);
                                            v0 = 520;
                                        } else {
                                            // 0x002dfed0
                                            charge(ctx, 3);
                                            v0 = 519;
                                        }
                                        // 0x002dfee0
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFEE8u:  // table[8]: unit id 8
                                        // 0x002dfee8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2DFEECu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002dff0c
                                            charge(ctx, 1);
                                            v0 = 593;
                                        } else {
                                            // 0x002dff00
                                            charge(ctx, 3);
                                            v0 = 592;
                                        }
                                        // 0x002dff10
                                        charge(ctx, 2);
                                        break;
                                    case 0x2DFF18u:  // table[9]: unit id 9
                                        // 0x002dff18
                                        charge(ctx, 4);
                                        jal(ctx, 0x2DFF18u, gen::fn_sub_17D800_0017d800);
                                        if (v0 != 0) {
                                            // 0x002dff58
                                            charge(ctx, 6);
                                            a0 = 100;
                                            jal(ctx, 0x2DFF5Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                            v0 = sltiu(v0, 50);
                                            if (v0 != 0) {
                                                // 0x002dff7c
                                                charge(ctx, 1);
                                                v0 = 1163;
                                            } else {
                                                // 0x002dff70
                                                charge(ctx, 3);
                                                v0 = 1162;
                                            }
                                            // 0x002dff80
                                            charge(ctx, 2);
                                        } else {
                                            // 0x002dff28
                                            charge(ctx, 6);
                                            a0 = 100;
                                            jal(ctx, 0x2DFF2Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                            v0 = sltiu(v0, 50);
                                            if (v0 != 0) {
                                                // 0x002dff4c
                                                charge(ctx, 1);
                                                v0 = 658;
                                            } else {
                                                // 0x002dff40
                                                charge(ctx, 3);
                                                v0 = 657;
                                            }
                                            // 0x002dff50
                                            charge(ctx, 2);
                                        }
                                        break;
                                    case 0x2DFF88u:  // table[10]: unit id 10
                                        // 0x002dff88
                                        charge(ctx, 3);
                                        v0 = si(-1);
                                        break;
                                    case 0x2E0324u:  // table[0, 1, 6]
                                        goto L_002e0324;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                }
                                break;
                            case 0x2E015Cu:  // table[10]: unit id 10
                                // 0x002e015c
                                charge(ctx, 4);
                                lhu(v0, s0, 164);
                                at = sltiu(v0, 11);
                                if (at == 0) {
                                    goto L_002e0324;
                                }
                                // 0x002e016c
                                charge(ctx, 7);
                                v1 = 0x7C0000;
                                v1 = addiu(v1, -32224);  // &0x7B8220
                                v0 = sll(v0, 2);
                                v0 = addu(v0, v1);
                                lw(v0, v0, 0);
                                switch (v0.u()) {
                                case 0x2E0188u:  // table[2]: unit id 2
                                    // 0x002e0188
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2E018Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002e01ac
                                        charge(ctx, 1);
                                        v0 = 194;
                                    } else {
                                        // 0x002e01a0
                                        charge(ctx, 3);
                                        v0 = 193;
                                    }
                                    // 0x002e01b0
                                    charge(ctx, 2);
                                    break;
                                case 0x2E01B8u:  // table[3]: unit id 3
                                    // 0x002e01b8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2E01BCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002e01dc
                                        charge(ctx, 1);
                                        v0 = 288;
                                    } else {
                                        // 0x002e01d0
                                        charge(ctx, 3);
                                        v0 = 287;
                                    }
                                    // 0x002e01e0
                                    charge(ctx, 2);
                                    break;
                                case 0x2E01E8u:  // table[4]: unit id 4
                                    // 0x002e01e8
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2E01ECu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002e020c
                                        charge(ctx, 1);
                                        v0 = 376;
                                    } else {
                                        // 0x002e0200
                                        charge(ctx, 3);
                                        v0 = 375;
                                    }
                                    // 0x002e0210
                                    charge(ctx, 2);
                                    break;
                                case 0x2E0218u:  // table[5]: unit id 5
                                    // 0x002e0218
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2E021Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002e023c
                                        charge(ctx, 1);
                                        v0 = 449;
                                    } else {
                                        // 0x002e0230
                                        charge(ctx, 3);
                                        v0 = 448;
                                    }
                                    // 0x002e0240
                                    charge(ctx, 2);
                                    break;
                                case 0x2E0248u:  // table[7]: unit id 7
                                    // 0x002e0248
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2E024Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002e026c
                                        charge(ctx, 1);
                                        v0 = 522;
                                    } else {
                                        // 0x002e0260
                                        charge(ctx, 3);
                                        v0 = 521;
                                    }
                                    // 0x002e0270
                                    charge(ctx, 2);
                                    break;
                                case 0x2E0278u:  // table[8]: unit id 8
                                    // 0x002e0278
                                    charge(ctx, 6);
                                    a0 = 100;
                                    jal(ctx, 0x2E027Cu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                    v0 = sltiu(v0, 50);
                                    if (v0 != 0) {
                                        // 0x002e029c
                                        charge(ctx, 1);
                                        v0 = 595;
                                    } else {
                                        // 0x002e0290
                                        charge(ctx, 3);
                                        v0 = 594;
                                    }
                                    // 0x002e02a0
                                    charge(ctx, 2);
                                    break;
                                case 0x2E02A8u:  // table[9]: unit id 9
                                    // 0x002e02a8
                                    charge(ctx, 4);
                                    jal(ctx, 0x2E02A8u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x002e02e8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2E02ECu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e030c
                                            charge(ctx, 1);
                                            v0 = 1165;
                                        } else {
                                            // 0x002e0300
                                            charge(ctx, 3);
                                            v0 = 1164;
                                        }
                                        // 0x002e0310
                                        charge(ctx, 2);
                                    } else {
                                        // 0x002e02b8
                                        charge(ctx, 6);
                                        a0 = 100;
                                        jal(ctx, 0x2E02BCu, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                                        v0 = sltiu(v0, 50);
                                        if (v0 != 0) {
                                            // 0x002e02dc
                                            charge(ctx, 1);
                                            v0 = 660;
                                        } else {
                                            // 0x002e02d0
                                            charge(ctx, 3);
                                            v0 = 659;
                                        }
                                        // 0x002e02e0
                                        charge(ctx, 2);
                                    }
                                    break;
                                case 0x2E0318u:  // table[10]: unit id 10
                                    // 0x002e0318
                                    charge(ctx, 3);
                                    v0 = si(-1);
                                    break;
                                case 0x2E0324u:  // table[0, 1, 6]
                                    goto L_002e0324;
                                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                    tail(ctx, v0.u());
                                    return;
                                }
                                break;
                            case 0x2E0324u:  // table[0, 6]
                                goto L_002e0324;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, v0.u());
                                return;
                            }
                            // 0x002e0328 (the shared epilogue, written out on this path)
                            charge(ctx, 7);
                            ld(ra, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0x70);
                            return;
                        }
                        goto L_002e0324;
                    }
                    // 0x002df108
                    charge(ctx, 3);
                    v0 = si(-1);
                } else {
                    // 0x002df0e0
                    charge(ctx, 3);
                    v0 = si(-1);
                }
            } else {
                // 0x002df04c
                charge(ctx, 3);
                v0 = si(-1);
            }
        } else {
            // 0x002df02c
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x002df010
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e0328 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x002E0350 sub_2E0350 -- 488 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick10] Party voice picker 10 (table 0x697C10): one of the acting member's two lines, 50 % each (215 /
// 216, 309 / 310, 397 / 398, ...; unit 9: 1187 with sub_17D800 after one draw).
// Arguments: a0 the btlAction.
void sub_2E0350(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e0350
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e0374
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e0384
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -31696);  // &0x7B8430
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E03A0u:  // table[2]: unit id 2
                // 0x002e03a0
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2E03A4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sltiu(v0, 50);
                if (v0 != 0) {
                    // 0x002e03c4
                    charge(ctx, 1);
                    v0 = 216;
                } else {
                    // 0x002e03b8
                    charge(ctx, 3);
                    v0 = 215;
                }
                // 0x002e03c8
                charge(ctx, 2);
                break;
            case 0x2E03D0u:  // table[3]: unit id 3
                // 0x002e03d0
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2E03D4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sltiu(v0, 50);
                if (v0 != 0) {
                    // 0x002e03f4
                    charge(ctx, 1);
                    v0 = 310;
                } else {
                    // 0x002e03e8
                    charge(ctx, 3);
                    v0 = 309;
                }
                // 0x002e03f8
                charge(ctx, 2);
                break;
            case 0x2E0400u:  // table[4]: unit id 4
                // 0x002e0400
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2E0404u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sltiu(v0, 50);
                if (v0 != 0) {
                    // 0x002e0424
                    charge(ctx, 1);
                    v0 = 398;
                } else {
                    // 0x002e0418
                    charge(ctx, 3);
                    v0 = 397;
                }
                // 0x002e0428
                charge(ctx, 2);
                break;
            case 0x2E0430u:  // table[5]: unit id 5
                // 0x002e0430
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2E0434u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sltiu(v0, 50);
                if (v0 != 0) {
                    // 0x002e0454
                    charge(ctx, 1);
                    v0 = 471;
                } else {
                    // 0x002e0448
                    charge(ctx, 3);
                    v0 = 470;
                }
                // 0x002e0458
                charge(ctx, 2);
                break;
            case 0x2E0460u:  // table[7]: unit id 7
                // 0x002e0460
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2E0464u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sltiu(v0, 50);
                if (v0 != 0) {
                    // 0x002e0484
                    charge(ctx, 1);
                    v0 = 544;
                } else {
                    // 0x002e0478
                    charge(ctx, 3);
                    v0 = 543;
                }
                // 0x002e0488
                charge(ctx, 2);
                break;
            case 0x2E0490u:  // table[8]: unit id 8
                // 0x002e0490
                charge(ctx, 6);
                a0 = 100;
                jal(ctx, 0x2E0494u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                v0 = sltiu(v0, 50);
                if (v0 != 0) {
                    // 0x002e04b4
                    charge(ctx, 1);
                    v0 = 617;
                } else {
                    // 0x002e04a8
                    charge(ctx, 3);
                    v0 = 616;
                }
                // 0x002e04b8
                charge(ctx, 2);
                break;
            case 0x2E04C0u:  // table[9]: unit id 9
                // 0x002e04c0
                charge(ctx, 4);
                jal(ctx, 0x2E04C0u, gen::fn_sub_17D800_0017d800);
                if (v0 != 0) {
                    // 0x002e0500
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E0504u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                    v0 = 1187;
                } else {
                    // 0x002e04d0
                    charge(ctx, 6);
                    a0 = 100;
                    jal(ctx, 0x2E04D4u, gen::fn_datCalcRand_002ffbc0);  // the battle random stream
                    v0 = sltiu(v0, 50);
                    if (v0 != 0) {
                        // 0x002e04f4
                        charge(ctx, 1);
                        v0 = 682;
                    } else {
                        // 0x002e04e8
                        charge(ctx, 3);
                        v0 = 681;
                    }
                    // 0x002e04f8
                    charge(ctx, 2);
                }
                break;
            case 0x2E0518u:  // table[10]: unit id 10
                // 0x002e0518
                charge(ctx, 3);
                v0 = si(-1);
                break;
            case 0x2E0524u:  // table[0, 1, 6]
            L_002e0524:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e0528 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e0524;
    }
    // 0x002e0368
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e0528 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E0540 sub_2E0540 -- 224 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick11] Party voice picker 11 (table 0x697C10): the acting member's line 217, 326, 399, 472, 545, 618, 683
// / 1202; -1 for unit 10 and the others.
// Arguments: a0 the btlAction.
void sub_2E0540(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e0540
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e0564
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e0574
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -31648);  // &0x7B8460
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E0590u:  // table[2]: unit id 2
                // 0x002e0590
                charge(ctx, 3);
                v0 = 217;
                break;
            case 0x2E059Cu:  // table[3]: unit id 3
                // 0x002e059c
                charge(ctx, 3);
                v0 = 326;
                break;
            case 0x2E05A8u:  // table[4]: unit id 4
                // 0x002e05a8
                charge(ctx, 3);
                v0 = 399;
                break;
            case 0x2E05B4u:  // table[5]: unit id 5
                // 0x002e05b4
                charge(ctx, 3);
                v0 = 472;
                break;
            case 0x2E05C0u:  // table[7]: unit id 7
                // 0x002e05c0
                charge(ctx, 3);
                v0 = 545;
                break;
            case 0x2E05CCu:  // table[8]: unit id 8
                // 0x002e05cc
                charge(ctx, 3);
                v0 = 618;
                break;
            case 0x2E05D8u:  // table[9]: unit id 9
                // 0x002e05d8
                charge(ctx, 4);
                jal(ctx, 0x2E05D8u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002e05f4
                    charge(ctx, 1);
                    v0 = 683;
                } else {
                    // 0x002e05e8
                    charge(ctx, 3);
                    v0 = 1202;
                }
                // 0x002e05f8
                charge(ctx, 2);
                break;
            case 0x2E0600u:  // table[10]: unit id 10
                // 0x002e0600
                charge(ctx, 3);
                v0 = si(-1);
                break;
            case 0x2E060Cu:  // table[0, 1, 6]
            L_002e060c:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e0610 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e060c;
    }
    // 0x002e0558
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e0610 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E1CD0 sub_2E1CD0 -- 284 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick17] Party voice picker 17 (table 0x697C10): the line 155, 235 / 236, 337, 410, 483, 556, 629 / 1126,
// 694. returns -1 for a non-party unit; the party members 2..10 each have their own line (unit id 9 two, by
// sub_17D800).
// Arguments: a0 the btlAction.
void sub_2E1CD0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e1cd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e1cf4
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e1d04
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30656);  // &0x7B8840
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E1D20u:  // table[2]: unit id 2
                // 0x002e1d20
                charge(ctx, 3);
                v0 = 155;
                break;
            case 0x2E1D2Cu:  // table[3]: unit id 3
                // 0x002e1d2c
                charge(ctx, 5);
                v0 = 0x690000;
                lw(a0, v0, 31716);  // 0x697BE4
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x002e1d4c
                    charge(ctx, 2);
                    jal(ctx, 0x2E1D4Cu, gen::fn_datGetFlag_0016f190);
                } else {
                    // 0x002e1d40
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x002e1d54
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002e1d68
                    charge(ctx, 1);
                    v0 = 235;
                } else {
                    // 0x002e1d5c
                    charge(ctx, 3);
                    v0 = 236;
                }
                // 0x002e1d6c
                charge(ctx, 2);
                break;
            case 0x2E1D74u:  // table[4]: unit id 4
                // 0x002e1d74
                charge(ctx, 3);
                v0 = 337;
                break;
            case 0x2E1D80u:  // table[5]: unit id 5
                // 0x002e1d80
                charge(ctx, 3);
                v0 = 410;
                break;
            case 0x2E1D8Cu:  // table[7]: unit id 7
                // 0x002e1d8c
                charge(ctx, 3);
                v0 = 483;
                break;
            case 0x2E1D98u:  // table[8]: unit id 8
                // 0x002e1d98
                charge(ctx, 3);
                v0 = 556;
                break;
            case 0x2E1DA4u:  // table[9]: unit id 9
                // 0x002e1da4
                charge(ctx, 4);
                jal(ctx, 0x2E1DA4u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002e1dc0
                    charge(ctx, 1);
                    v0 = 629;
                } else {
                    // 0x002e1db4
                    charge(ctx, 3);
                    v0 = 1126;
                }
                // 0x002e1dc4
                charge(ctx, 2);
                break;
            case 0x2E1DCCu:  // table[10]: unit id 10
                // 0x002e1dcc
                charge(ctx, 3);
                v0 = 694;
                break;
            case 0x2E1DD8u:  // table[0, 1, 6]
            L_002e1dd8:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e1ddc (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e1dd8;
    }
    // 0x002e1ce8
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e1ddc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E1DF0 sub_2E1DF0 -- 284 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick18] Party voice picker 18 (table 0x697C10): the next row of the same scheme. returns -1 for a
// non-party unit; the party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
// Arguments: a0 the btlAction.
void sub_2E1DF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e1df0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e1e14
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e1e24
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30608);  // &0x7B8870
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E1E40u:  // table[2]: unit id 2
                // 0x002e1e40
                charge(ctx, 3);
                v0 = 150;
                break;
            case 0x2E1E4Cu:  // table[3]: unit id 3
                // 0x002e1e4c
                charge(ctx, 5);
                v0 = 0x690000;
                lw(a0, v0, 31716);  // 0x697BE4
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x002e1e6c
                    charge(ctx, 2);
                    jal(ctx, 0x2E1E6Cu, gen::fn_datGetFlag_0016f190);
                } else {
                    // 0x002e1e60
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x002e1e74
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002e1e88
                    charge(ctx, 1);
                    v0 = 226;
                } else {
                    // 0x002e1e7c
                    charge(ctx, 3);
                    v0 = 227;
                }
                // 0x002e1e8c
                charge(ctx, 2);
                break;
            case 0x2E1E94u:  // table[4]: unit id 4
                // 0x002e1e94
                charge(ctx, 3);
                v0 = 332;
                break;
            case 0x2E1EA0u:  // table[5]: unit id 5
                // 0x002e1ea0
                charge(ctx, 3);
                v0 = 405;
                break;
            case 0x2E1EACu:  // table[7]: unit id 7
                // 0x002e1eac
                charge(ctx, 3);
                v0 = 478;
                break;
            case 0x2E1EB8u:  // table[8]: unit id 8
                // 0x002e1eb8
                charge(ctx, 3);
                v0 = 551;
                break;
            case 0x2E1EC4u:  // table[9]: unit id 9
                // 0x002e1ec4
                charge(ctx, 4);
                jal(ctx, 0x2E1EC4u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002e1ee0
                    charge(ctx, 1);
                    v0 = 624;
                } else {
                    // 0x002e1ed4
                    charge(ctx, 3);
                    v0 = 1121;
                }
                // 0x002e1ee4
                charge(ctx, 2);
                break;
            case 0x2E1EECu:  // table[10]: unit id 10
                // 0x002e1eec
                charge(ctx, 3);
                v0 = 689;
                break;
            case 0x2E1EF8u:  // table[0, 1, 6]
            L_002e1ef8:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e1efc (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e1ef8;
    }
    // 0x002e1e08
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e1efc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E1F10 sub_2E1F10 -- 284 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick19] Party voice picker 19 (table 0x697C10): the next row of the same scheme. returns -1 for a
// non-party unit; the party members 2..10 each have their own line (unit id 9 two, by sub_17D800).
// Arguments: a0 the btlAction.
void sub_2E1F10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e1f10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e1f34
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e1f44
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30560);  // &0x7B88A0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E1F60u:  // table[2]: unit id 2
                // 0x002e1f60
                charge(ctx, 3);
                v0 = 152;
                break;
            case 0x2E1F6Cu:  // table[3]: unit id 3
                // 0x002e1f6c
                charge(ctx, 5);
                v0 = 0x690000;
                lw(a0, v0, 31716);  // 0x697BE4
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x002e1f8c
                    charge(ctx, 2);
                    jal(ctx, 0x2E1F8Cu, gen::fn_datGetFlag_0016f190);
                } else {
                    // 0x002e1f80
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x002e1f94
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x002e1fa8
                    charge(ctx, 1);
                    v0 = 230;
                } else {
                    // 0x002e1f9c
                    charge(ctx, 3);
                    v0 = 231;
                }
                // 0x002e1fac
                charge(ctx, 2);
                break;
            case 0x2E1FB4u:  // table[4]: unit id 4
                // 0x002e1fb4
                charge(ctx, 3);
                v0 = 334;
                break;
            case 0x2E1FC0u:  // table[5]: unit id 5
                // 0x002e1fc0
                charge(ctx, 3);
                v0 = 407;
                break;
            case 0x2E1FCCu:  // table[7]: unit id 7
                // 0x002e1fcc
                charge(ctx, 3);
                v0 = 480;
                break;
            case 0x2E1FD8u:  // table[8]: unit id 8
                // 0x002e1fd8
                charge(ctx, 3);
                v0 = 553;
                break;
            case 0x2E1FE4u:  // table[9]: unit id 9
                // 0x002e1fe4
                charge(ctx, 4);
                jal(ctx, 0x2E1FE4u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002e2000
                    charge(ctx, 1);
                    v0 = 626;
                } else {
                    // 0x002e1ff4
                    charge(ctx, 3);
                    v0 = 1123;
                }
                // 0x002e2004
                charge(ctx, 2);
                break;
            case 0x2E200Cu:  // table[10]: unit id 10
                // 0x002e200c
                charge(ctx, 3);
                v0 = 691;
                break;
            case 0x2E2018u:  // table[0, 1, 6]
            L_002e2018:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e201c (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e2018;
    }
    // 0x002e1f28
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e201c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2030 sub_2E2030 -- 224 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick20] Party voice picker 20 (table 0x697C10): the line 149, 225, 331, 404, 477, 550, 623 / 1120, 688.
// Arguments: a0 the btlAction.
void sub_2E2030(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2030
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, act::kUnit);
    lbu(v0, v1, unit::kSide);
    if (v0 == 0) {
        // 0x002e2054
        charge(ctx, 4);
        lhu(v0, v1, unit::kId);
        at = sltiu(v0, 11);
        if (at != 0) {
            // 0x002e2064
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30512);  // &0x7B88D0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E2080u:  // table[2]: unit id 2
                // 0x002e2080
                charge(ctx, 3);
                v0 = 149;
                break;
            case 0x2E208Cu:  // table[3]: unit id 3
                // 0x002e208c
                charge(ctx, 3);
                v0 = 225;
                break;
            case 0x2E2098u:  // table[4]: unit id 4
                // 0x002e2098
                charge(ctx, 3);
                v0 = 331;
                break;
            case 0x2E20A4u:  // table[5]: unit id 5
                // 0x002e20a4
                charge(ctx, 3);
                v0 = 404;
                break;
            case 0x2E20B0u:  // table[7]: unit id 7
                // 0x002e20b0
                charge(ctx, 3);
                v0 = 477;
                break;
            case 0x2E20BCu:  // table[8]: unit id 8
                // 0x002e20bc
                charge(ctx, 3);
                v0 = 550;
                break;
            case 0x2E20C8u:  // table[9]: unit id 9
                // 0x002e20c8
                charge(ctx, 4);
                jal(ctx, 0x2E20C8u, gen::fn_sub_17D800_0017d800);
                if (v0 == 0) {
                    // 0x002e20e4
                    charge(ctx, 1);
                    v0 = 623;
                } else {
                    // 0x002e20d8
                    charge(ctx, 3);
                    v0 = 1120;
                }
                // 0x002e20e8
                charge(ctx, 2);
                break;
            case 0x2E20F0u:  // table[10]: unit id 10
                // 0x002e20f0
                charge(ctx, 3);
                v0 = 688;
                break;
            case 0x2E20FCu:  // table[0, 1, 6]
            L_002e20fc:
                charge(ctx, 1);
                v0 = si(-1);
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            // 0x002e2100 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            return;
        }
        goto L_002e20fc;
    }
    // 0x002e2048
    charge(ctx, 3);
    v0 = si(-1);
    // 0x002e2100 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2110 sub_2E2110 -- 396 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick21] Party voice picker 21 (table 0x697C10): a party unit's line by sub_357FD0(0) -- with sub_17D800
// one of 1188..1195 (value & 7), else one of 311..319 (value % 9); -1 for an enemy.
// Arguments: a0 the btlAction.
void sub_2E2110(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2110
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002e2134
        charge(ctx, 4);
        jal(ctx, 0x2E2134u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x002e21f0
            charge(ctx, 7);
            a0 = 0;
            jal(ctx, 0x2E21F4u, gen::fn_sub_357FD0_00357fd0);
            v0 = v0 & 0x7;
            at = sltiu(v0, 8);
            if (at == 0) {
            L_002e2288:
                charge(ctx, 1);
                v0 = si(-1);
            } else {
                // 0x002e220c
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -30464);  // "(\"."
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x2E2228u:  // table[0]
                    // 0x002e2228
                    charge(ctx, 3);
                    v0 = 1188;
                    break;
                case 0x2E2234u:  // table[1]
                    // 0x002e2234
                    charge(ctx, 3);
                    v0 = 1189;
                    break;
                case 0x2E2240u:  // table[2]
                    // 0x002e2240
                    charge(ctx, 3);
                    v0 = 1190;
                    break;
                case 0x2E224Cu:  // table[3]
                    // 0x002e224c
                    charge(ctx, 3);
                    v0 = 1191;
                    break;
                case 0x2E2258u:  // table[4]
                    // 0x002e2258
                    charge(ctx, 3);
                    v0 = 1192;
                    break;
                case 0x2E2264u:  // table[5]
                    // 0x002e2264
                    charge(ctx, 3);
                    v0 = 1193;
                    break;
                case 0x2E2270u:  // table[6]
                    // 0x002e2270
                    charge(ctx, 3);
                    v0 = 1194;
                    break;
                case 0x2E227Cu:  // table[7]
                    // 0x002e227c
                    charge(ctx, 3);
                    v0 = 1195;
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
        } else {
            // 0x002e2144
            charge(ctx, 9);
            a0 = 0;
            jal(ctx, 0x2E2148u, gen::fn_sub_357FD0_00357fd0);
            v1 = 9;
            divu(v0, v1);
            mfhi(v0);
            at = sltiu(v0, 9);
            if (at == 0) {
                goto L_002e2288;
            }
            // 0x002e2168
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -30432);  // &0x7B8920
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x2E2184u:  // table[0]
                // 0x002e2184
                charge(ctx, 3);
                v0 = 311;
                break;
            case 0x2E2190u:  // table[1]
                // 0x002e2190
                charge(ctx, 3);
                v0 = 312;
                break;
            case 0x2E219Cu:  // table[2]
                // 0x002e219c
                charge(ctx, 3);
                v0 = 313;
                break;
            case 0x2E21A8u:  // table[3]
                // 0x002e21a8
                charge(ctx, 3);
                v0 = 314;
                break;
            case 0x2E21B4u:  // table[4]
                // 0x002e21b4
                charge(ctx, 3);
                v0 = 315;
                break;
            case 0x2E21C0u:  // table[5]
                // 0x002e21c0
                charge(ctx, 3);
                v0 = 316;
                break;
            case 0x2E21CCu:  // table[6]
                // 0x002e21cc
                charge(ctx, 3);
                v0 = 317;
                break;
            case 0x2E21D8u:  // table[7]
                // 0x002e21d8
                charge(ctx, 3);
                v0 = 318;
                break;
            case 0x2E21E4u:  // table[8]
                // 0x002e21e4
                charge(ctx, 3);
                v0 = 319;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    } else {
        // 0x002e2128
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e228c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E22A0 sub_2E22A0 -- 368 bytes; frame 0x10: ra sp+0x0
// [btlVoicePick22] Party voice picker 22 (table 0x697C10): as picker 21 with the next line ranges.
// Arguments: a0 the btlAction.
void sub_2E22A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e22a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, act::kUnit);
    lbu(v0, v0, unit::kSide);
    if (v0 == 0) {
        // 0x002e22c4
        charge(ctx, 4);
        jal(ctx, 0x2E22C4u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x002e2368
            charge(ctx, 9);
            a0 = 0;
            jal(ctx, 0x2E236Cu, gen::fn_sub_357FD0_00357fd0);
            v1 = 5;
            divu(v0, v1);
            mfhi(v1);
            v0 = 4;
            if (v1 == v0) {
                // 0x002e23f0
                charge(ctx, 3);
                v0 = 1200;
            } else {
                // 0x002e238c
                charge(ctx, 3);
                v0 = 3;
                if (v1 == v0) {
                    // 0x002e23e4
                    charge(ctx, 3);
                    v0 = 1199;
                } else {
                    // 0x002e2398
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x002e23d8
                        charge(ctx, 3);
                        v0 = 1198;
                    } else {
                        // 0x002e23a4
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x002e23cc
                            charge(ctx, 3);
                            v0 = 1197;
                        } else {
                            // 0x002e23b0
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x002e23c0
                                charge(ctx, 3);
                                v0 = 1196;
                            } else {
                                // 0x002e23b8
                                charge(ctx, 2);
                            L_002e23fc:
                                charge(ctx, 1);
                                v0 = si(-1);
                            }
                        }
                    }
                }
            }
        } else {
            // 0x002e22d4
            charge(ctx, 9);
            a0 = 0;
            jal(ctx, 0x2E22D8u, gen::fn_sub_357FD0_00357fd0);
            v1 = 5;
            divu(v0, v1);
            mfhi(v1);
            v0 = 4;
            if (v1 == v0) {
                // 0x002e235c
                charge(ctx, 3);
                v0 = 324;
            } else {
                // 0x002e22f8
                charge(ctx, 3);
                v0 = 3;
                if (v1 == v0) {
                    // 0x002e2350
                    charge(ctx, 3);
                    v0 = 323;
                } else {
                    // 0x002e2304
                    charge(ctx, 3);
                    v0 = 2;
                    if (v1 == v0) {
                        // 0x002e2344
                        charge(ctx, 3);
                        v0 = 322;
                    } else {
                        // 0x002e2310
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x002e2338
                            charge(ctx, 3);
                            v0 = 321;
                        } else {
                            // 0x002e231c
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x002e2324
                                charge(ctx, 2);
                                goto L_002e23fc;
                            }
                            // 0x002e232c
                            charge(ctx, 3);
                            v0 = 320;
                        }
                    }
                }
            }
        }
    } else {
        // 0x002e22b8
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x002e2400 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2920 sub_2E2920 -- 240 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [btlVoiceBankLoadPkt] Party voice bank load packet update: the first call (unless the voices are off, *0x7CE4FC)
// allocates the 256 KiB bank buffer (RwMalloc, gBtl +2812) and requests bank +2808's 450 voices (sub_10A770); then
// returns 1 once the request is done (sub_10A720) and sets the ready bit gBtl +2806.
// Arguments: a0 the packet data {request, started}.
void sub_2E2920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2920
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    // the first call: request the voice bank (unless the voices are off)
    lw(v0, a0, 4);
    if (v0 == 0) {
        // 0x002e293c
        charge(ctx, 3);
        lw(v0, gp, -18420);  // 0x7CE4FC
        if (v0 != 0) {
            // 0x002e2998
            charge(ctx, 1);
            sw(zero, s0, 0);
        } else {
            // 0x002e2948
            charge(ctx, 20);
            a0 = 2764;
            a1 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            jalr(ctx, 0x2E2958u, v0.u());
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            sw(v0, v1, gbtl7::kVoiceBuf);
            lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(a1, v0, gbtl5::kSoundBank);
            lw(a0, v0, gbtl4::kTask);
            lw(a2, v0, gbtl7::kVoiceBuf);
            a3 = 4;
            t0 = 450;
            t1 = 1;
            jal(ctx, 0x2E2984u, gen::fn_sub_10A770_0010a770);
            sw(v0, s0, 0);
        }
        // 0x002e299c
        charge(ctx, 2);
        v0 = 1;
        sw(v0, s0, 4);
    }
    // 0x002e29a4
    charge(ctx, 3);
    // done when there is no request or it has finished; then the bank is ready
    lw(a0, s0, 0);
    if (a0 == 0) {
        // 0x002e29dc
        charge(ctx, 7);
        lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
        lhu(v0, v1, gbtl7::kVoiceReady);
        v0 = v0 | 0x1;
        sh(v0, v1, gbtl7::kVoiceReady);
        v0 = 1;
    } else {
        // 0x002e29b0
        charge(ctx, 4);
        jal(ctx, 0x2E29B0u, gen::fn_sub_10A720_0010a720);
        if (v0 == 0) {
            // 0x002e29f8
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x002e29c0
            charge(ctx, 7);
            lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
            lhu(v0, v1, gbtl7::kVoiceReady);
            v0 = v0 | 0x1;
            sh(v0, v1, gbtl7::kVoiceReady);
            v0 = 1;
        }
    }
    // 0x002e29fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E2A60 sub_2E2A60 -- 380 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [btlVoiceLinePkt] Party voice line packet update: without the ready bank (gBtl +2806 bit 0) or a live speaker it is
// done; the first call asks the picker of the situation (+4, table 0x697C10) for the line and plays it on channel 4
// (sub_10A2E0); while channel 4 plays (sub_10A500) it keeps the speaker's model mouth flag (model +1022 bit 0x20)
// set, cleared when the line ends.
// Arguments: a0 the packet data {speaker action, u16 situation, args +8 / +12, started +20}.
void sub_2E2A60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2a60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    // without the voice bank the packet is done
    lhu(v0, v0, gbtl7::kVoiceReady);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x002e2a94
        charge(ctx, 4);
        lw(s0, s1, 0);
        lw(v0, s1, 20);
        if (v0 != 0) {
            // 0x002e2b34
            charge(ctx, 6);
            a0 = 4;
            // later calls: while channel 4 plays, keep the speaker's voice flag set
            jal(ctx, 0x2E2B38u, gen::fn_sub_10A500_0010a500);
            v1 = 1;
            if (v0 == v1) {
            L_002e2b84:
                charge(ctx, 4);
                lw(v1, s1, 20);
                v0 = 1;
                if (v1 == v0) {
                    // 0x002e2b94
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x002e2b9c
                        charge(ctx, 5);
                        lw(v1, s0, act::kUnit);
                        lw(v0, v1, unit::kModelFlags);
                        v0 = v0 & 0x2;
                        if (v0 != 0) {
                            // 0x002e2bb0
                            charge(ctx, 4);
                            lw(v1, v1, unit::kModel);
                            lhu(v0, v1, mdl7::kVoiceFlags);
                            v0 = v0 & 0xFFDF;
                            sh(v0, v1, mdl7::kVoiceFlags);
                        }
                    }
                }
                // 0x002e2bc0
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x002e2b4c
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x002e2b54
                    charge(ctx, 5);
                    lw(v1, s0, act::kUnit);
                    lw(v0, v1, unit::kModelFlags);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x002e2b68
                        charge(ctx, 4);
                        lw(v1, v1, unit::kModel);
                        lhu(v0, v1, mdl7::kVoiceFlags);
                        v0 = v0 | 0x20;
                        sh(v0, v1, mdl7::kVoiceFlags);
                    }
                }
                // 0x002e2b78
                charge(ctx, 3);
                v0 = 1;
            }
        } else {
            // 0x002e2aa4
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x002e2aac
                charge(ctx, 4);
                // the first call: a speaker no longer in the battle -> done
                lhu(v0, s0, act::kFlags2);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x002e2abc
                    charge(ctx, 3);
                    v0 = 1;
                    // 0x002e2bc4 (the shared epilogue, written out on this path)
                    charge(ctx, 6);
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            }
            charge(ctx, 14);
            a0 = s0;
            lw(a1, s1, 8);
            lw(a2, s1, 12);
            // the picker of the situation (+4) gives the line (-1: none, done)
            lhu(v0, s1, 4);
            v1 = sll(v0, 2);
            v0 = 0x690000;
            v0 = addiu(v0, 31760);  // &0x697C10
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            jalr(ctx, 0x2E2AECu, v0.u());
            v1 = si(-1);
            if (v0 != v1) {
                // 0x002e2b0c
                charge(ctx, 10);
                lw(v1, gp, kGpBtl);  // gBtl 0x7CE3EC
                lhu(a0, v1, gbtl5::kSoundBank);
                a2 = v0 & 0xFFFF;
                a1 = 4;
                jal(ctx, 0x2E2B1Cu, gen::fn_sub_10A2E0_0010a2e0);
                v0 = 1;
                sw(v0, s1, 20);
                goto L_002e2b84;
            }
            // 0x002e2b00
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x002e2a88
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x002e2bc4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002E2C70 sub_2E2C70 -- 56 bytes; frame 0x10: ra sp+0x0
// Sound packet update: plays the id at data +0 on bank gBtl +2808, channel 4 (sub_10A2E0); returns 1.
// Arguments: a0 the packet data {u16 id}.
void sub_2E2C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2c70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v0, v0, gbtl5::kSoundBank);
    lhu(a2, a0, 0);
    a0 = v0;
    a1 = 4;
    jal(ctx, 0x2E2C8Cu, gen::fn_sub_10A2E0_0010a2e0);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2CB0 sub_2E2CB0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates a sound packet (kind 2562, 2 data bytes, update sub_2E2C70) for the id a0.
// Arguments: a0 u16 the sound id.
void sub_2E2CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2cb0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 2562;
    a1 = 2;
    jal(ctx, 0x2E2CC8u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    v1 = 0x2E0000;
    v1 = addiu(v1, 11376);  // &sub_2E2C70
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s0, v1, 0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E2D00 sub_2E2D00 -- 52 bytes; frame 0x10: ra sp+0x0
// Plays the id a0 on the special voice track (gBtl +2818), channel 2 (sub_10A2E0).
// Arguments: a0 u16 the sound id.
void sub_2E2D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2d00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, kGpBtl);  // gBtl 0x7CE3EC
    lhu(v0, v0, gbtl5::kVoiceTrack);
    a2 = a0 & 0xFFFF;
    a0 = v0;
    a1 = 2;
    jal(ctx, 0x2E2D1Cu, gen::fn_sub_10A2E0_0010a2e0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E2D40 sub_2E2D40 -- 44 bytes; frame 0x10: ra sp+0x0
// Stops channel 2 (sub_10A100(2, 0, 8)).
// Arguments: none.
void sub_2E2D40(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e2d40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 2;
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x2E2D54u, gen::fn_sub_10A100_0010a100);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002E3010 sub_2E3010 -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Sound packet update: the first call plays {bank, channel, id} (sub_10A2E0); with flag bit 0 (+6) it waits until the
// channel stops (sub_10A500) -- returns 1 when done.
// Arguments: a0 the packet data {u16 bank, channel, id, flags, started +8}.
void sub_2E3010(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e3010
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 8);
    if (v0 == 0) {
        // 0x002e302c
        charge(ctx, 7);
        lhu(a0, s0, 0);
        lhu(a1, s0, 2);
        lhu(a2, s0, 4);
        jal(ctx, 0x2E3038u, gen::fn_sub_10A2E0_0010a2e0);
        v0 = 1;
        sw(v0, s0, 8);
    }
    // 0x002e3048
    charge(ctx, 4);
    lhu(v0, s0, 6);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x002e3058
        charge(ctx, 6);
        lh(a0, s0, 2);
        jal(ctx, 0x2E305Cu, gen::fn_sub_10A500_0010a500);
        v1 = 1;
        if (v0 == v1) {
            // 0x002e3070
            charge(ctx, 3);
            v0 = 0;
            // 0x002e3080 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    }
    charge(ctx, 1);
    v0 = 1;
    // 0x002e3080 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002E30A0 sub_2E30A0 -- 124 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Creates the sound packet of sub_2E3010 (kind 2564, 12 data bytes) for {bank, channel, id, flags}.
// Arguments: a0..a3 u16 bank, channel, id, flags.
void sub_2E30A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002e30a0
    enter(ctx, 31);  // entry check point + this block's cycles
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
    a0 = 2564;
    a1 = 12;
    jal(ctx, 0x2E30D0u, gen::fn_sub_27EC10_0027ec10);  // create a packet (kind $a0, $a1 data bytes)
    v1 = 0x2E0000;
    v1 = addiu(v1, 12304);  // &sub_2E3010
    sw(v1, v0, pkt::kUpdate);
    lw(v1, v0, pkt::kData);
    sh(s3, v1, 0);
    sh(s2, v1, 2);
    sh(s1, v1, 4);
    sh(s0, v1, 6);
    sw(zero, v1, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game
