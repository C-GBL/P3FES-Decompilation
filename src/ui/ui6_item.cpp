// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the item screen (its update; the item, equipment and material pages' layouts and element draws; the lists; the
// trade list builder).
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass gives each function its role, each jump-table case its state, names the record offsets,
// $gp words, pad words and sprite-file tables (ui6.h -- each constant equals the literal it replaces), gives the
// value of the float immediates and a note on the callees; it changes no statement. `// 0x00xxxxxx` lines name the
// original basic block a C++ block comes from; the remaining `goto`s jump to blocks the original shares.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/ui6.h"

namespace p3fes::recomp_gen {
void fn_H_Camp_MoveListCursor_0011abd0(p3fes::EEContext&);
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_K_FldDungeon_IsCurrentFloorExplorable_001bff50(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_nullsub_3_0011bba0(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_114450_00114450(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115AD0_00115ad0(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_11DA80_0011da80(p3fes::EEContext&);
void fn_sub_11E380_0011e380(p3fes::EEContext&);
void fn_sub_121DE0_00121de0(p3fes::EEContext&);
void fn_sub_122710_00122710(p3fes::EEContext&);
void fn_sub_13BCE0_0013bce0(p3fes::EEContext&);
void fn_sub_13BE50_0013be50(p3fes::EEContext&);
void fn_sub_13C6A0_0013c6a0(p3fes::EEContext&);
void fn_sub_13C780_0013c780(p3fes::EEContext&);
void fn_sub_13CC90_0013cc90(p3fes::EEContext&);
void fn_sub_13D1A0_0013d1a0(p3fes::EEContext&);
void fn_sub_13E710_0013e710(p3fes::EEContext&);
void fn_sub_13FCA0_0013fca0(p3fes::EEContext&);
void fn_sub_1406D0_001406d0(p3fes::EEContext&);
void fn_sub_140E30_00140e30(p3fes::EEContext&);
void fn_sub_141590_00141590(p3fes::EEContext&);
void fn_sub_141660_00141660(p3fes::EEContext&);
void fn_sub_141FB0_00141fb0(p3fes::EEContext&);
void fn_sub_142930_00142930(p3fes::EEContext&);
void fn_sub_1432F0_001432f0(p3fes::EEContext&);
void fn_sub_143A00_00143a00(p3fes::EEContext&);
void fn_sub_143EE0_00143ee0(p3fes::EEContext&);
void fn_sub_144910_00144910(p3fes::EEContext&);
void fn_sub_145350_00145350(p3fes::EEContext&);
void fn_sub_145520_00145520(p3fes::EEContext&);
void fn_sub_146710_00146710(p3fes::EEContext&);
void fn_sub_1474F0_001474f0(p3fes::EEContext&);
void fn_sub_1482F0_001482f0(p3fes::EEContext&);
void fn_sub_148880_00148880(p3fes::EEContext&);
void fn_sub_148C10_00148c10(p3fes::EEContext&);
void fn_sub_1496F0_001496f0(p3fes::EEContext&);
void fn_sub_14A490_0014a490(p3fes::EEContext&);
void fn_sub_14B210_0014b210(p3fes::EEContext&);
void fn_sub_14BCE0_0014bce0(p3fes::EEContext&);
void fn_sub_14C290_0014c290(p3fes::EEContext&);
void fn_sub_14C5C0_0014c5c0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_16F810_0016f810(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170E90_00170e90(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_173580_00173580(p3fes::EEContext&);
void fn_sub_174960_00174960(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_17B100_0017b100(p3fes::EEContext&);
void fn_sub_17BB40_0017bb40(p3fes::EEContext&);
void fn_sub_17BBB0_0017bbb0(p3fes::EEContext&);
void fn_sub_17BF70_0017bf70(p3fes::EEContext&);
void fn_sub_17BFA0_0017bfa0(p3fes::EEContext&);
void fn_sub_18B6D0_0018b6d0(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_3C7700_003c7700(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui6;  // the record offsets, $gp words, pad words and sprite tables of ui6.h

// 0x0013C780 sub_13C780 -- 1288 bytes; frame 0x310: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_BuildTradeList] (list): builds the equipment trade list: the hero stock's held indices 0..299 sorted by item
// id (qsort / sub_131000), then the 20-entry equipment table (owner -1) as 36-byte rows from +100: id, its lowest
// target bit (sub_13C6A0), kind, the two flag bytes, the source (index + 4096), the stats of its kind (power /
// accuracy, evasion, defence).
void sub_13C780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0013c780
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x310);
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
    s5 = a0;
    s3 = 0;
    s0 = 0;
    for (;;) {
        // 0x0013c7f0
        charge(ctx, 3);
        v1 = slti(s0, 300);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013c7c0
        charge(ctx, 7);
        a0 = 1;
        a1 = s0;
        jal(ctx, 0x13C7C8u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
        v1 = v0 & 0xFFFF;
        if (v1 != 0) {
            // 0x0013c7dc
            charge(ctx, 4);
            v1 = sll(s3, 1);
            v1 = addu(v1, sp);
            sh(s0, v1, 176);
            s3 = addiu(s3, 1);
        }
        // 0x0013c7ec
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0013c7fc
    charge(ctx, 3);
    at = slti(s3, 2);
    if (at == 0) {
        // 0x0013c808
        charge(ctx, 7);
        a0 = addiu(sp, 0xB0);
        a1 = s3;
        a2 = 2;
        a3 = 0x130000;
        a3 = addiu(a3, 4096);  // &sub_131000
        jal(ctx, 0x13C81Cu, gen::fn_qsort_005225f8);
    }
    // 0x0013c824
    charge(ctx, 4);
    s4 = 0;
    s2 = 0;
    for (;;) {
        // 0x0013c98c
        charge(ctx, 3);
        v1 = slti(s2, 20);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013c834
        charge(ctx, 7);
        a0 = si(-1);
        a1 = s2;
        jal(ctx, 0x13C83Cu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
        v1 = v0 & 0xFFFF;
        if (v1 != 0) {
            // 0x0013c850
            charge(ctx, 40);
            v0 = sll(s4, 3);
            v0 = addu(v0, s4);
            v0 = sll(v0, 2);
            s1 = addu(s5, v0);
            s0 = addiu(s1, 100);
            a0 = si(-1);
            a1 = s2;
            jal(ctx, 0x13C86Cu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            v0 = v0 & 0xFFFF;
            sw(v0, s0, 0);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x13C884u, gen::fn_sub_13C6A0_0013c6a0);  // the lowest target bit
            sw(v0, s1, 120);
            s6 = addiu(s1, 126);
            lh(a0, s0, 0);
            jal(ctx, 0x13C898u, gen::fn_sub_171250_00171250);  // [datGetItemKind] (id / 1000)
            sb(v0, s6, 0);
            a0 = si(-1);
            a1 = s2;
            jal(ctx, 0x13C8ACu, gen::fn_sub_16F900_0016f900);  // (owner, index)
            sb(v0, s1, 124);
            a0 = si(-1);
            a1 = s2;
            jal(ctx, 0x13C8C0u, gen::fn_sub_16F810_0016f810);  // (owner, index)
            sb(v0, s1, 125);
            v1 = addiu(s2, 4096);
            sw(v1, s1, 104);
            a1 = 1;
            sw(a1, s1, 112);
            sw(a1, s1, 116);
            lbu(a0, s6, 0);
            v1 = 3;
            if (a0 != v1) {
                // 0x0013c8f0
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x0013c970
                    charge(ctx, 5);
                    a0 = si(-1);
                    a1 = s2;
                    jal(ctx, 0x13C978u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                    sh(v0, s1, 134);
                } else {
                    // 0x0013c8fc
                    charge(ctx, 2);
                    if (a0 == a1) {
                        // 0x0013c954
                        charge(ctx, 7);
                        a0 = si(-1);
                        a1 = s2;
                        jal(ctx, 0x13C95Cu, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                        sh(v0, s1, 132);
                    } else {
                        // 0x0013c904
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0013c914
                            charge(ctx, 16);
                            v0 = sll(s4, 3);
                            v0 = addu(v0, s4);
                            v0 = sll(v0, 2);
                            s0 = addu(s5, v0);
                            a0 = si(-1);
                            a1 = s2;
                            jal(ctx, 0x13C92Cu, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                            sh(v0, s0, 128);
                            a0 = si(-1);
                            a1 = s2;
                            jal(ctx, 0x13C940u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                            sh(v0, s0, 130);
                        } else {
                            // 0x0013c90c
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0013c984
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x0013c988
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0013c998
    charge(ctx, 4);
    sw(s4, s5, 12);
    s2 = 0;
    for (;;) {
        // 0x0013cc1c
        charge(ctx, 3);
        v1 = slt(s2, s3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013c9a8
        charge(ctx, 10);
        v0 = sll(s2, 1);
        v0 = addu(v0, sp);
        s1 = addiu(v0, 176);
        lhu(a1, s1, 0);
        a0 = 1;
        jal(ctx, 0x13C9BCu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
        v1 = v0 & 0xFFFF;
        if (v1 != 0) {
            // 0x0013c9d0
            charge(ctx, 19);
            v0 = sll(s2, 1);
            v0 = addu(v0, sp);
            s7 = addiu(v0, 176);
            v0 = sll(s4, 3);
            v0 = addu(v0, s4);
            v0 = sll(v0, 2);
            s0 = addu(s5, v0);
            v0 = addiu(s0, 100);
            sq(v0, sp, 0xA0);
            lhu(a1, s7, 0);
            a0 = 1;
            jal(ctx, 0x13C9FCu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            v1 = v0 & 0xFFFF;
            lq(v0, sp, 0xA0);
            sw(v1, v0, 0);
            s6 = 0;
            for (;;) {
                // 0x0013ca50
                charge(ctx, 3);
                v0 = slti(s6, 21);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0013ca1c
                charge(ctx, 9);
                lhu(a1, s7, 0);
                a0 = 1;
                jal(ctx, 0x13CA24u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                v1 = 1;
                v1 = sllv(v1, s6);
                v0 = v1 & v0;
                if (v0 != 0) {
                    goto L_0013ca40_24;
                }
                // 0x0013ca4c
                charge(ctx, 1);
                s6 = addiu(s6, 1);
            }
        L_0013ca5c:
            charge(ctx, 35);
            v0 = sll(s4, 3);
            v0 = addu(v0, s4);
            v0 = sll(v0, 2);
            s6 = addu(s5, v0);
            fp = addiu(s6, 0x7E);
            lq(v0, sp, 0xA0);
            lh(a0, v0, 0);
            jal(ctx, 0x13CA78u, gen::fn_sub_171250_00171250);  // [datGetItemKind] (id / 1000)
            sb(v0, fp, 0x0);
            v0 = sll(s2, 1);
            v0 = addu(v0, sp);
            s7 = addiu(v0, 176);
            lhu(a1, s7, 0);
            a0 = 1;
            jal(ctx, 0x13CA98u, gen::fn_sub_16F900_0016f900);  // (owner, index)
            sb(v0, s6, 124);
            lhu(a1, s7, 0);
            a0 = 1;
            jal(ctx, 0x13CAACu, gen::fn_sub_16F810_0016f810);  // (owner, index)
            sb(v0, s6, 125);
            lhu(v0, s7, 0);
            sw(v0, s6, 104);
            sw(zero, s6, 112);
            lhu(s6, s7, 0);
            a0 = 1;
            a1 = 0;
            jal(ctx, 0x13CAD0u, gen::fn_datGetEquipmentIdx_0016cb80);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            if (s6 != v1) {
                // 0x0013cae8
                charge(ctx, 9);
                lhu(s6, s1, 0);
                a0 = 1;
                a1 = a0;
                jal(ctx, 0x13CAF4u, gen::fn_datGetEquipmentIdx_0016cb80);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                if (s6 == v1) {
                    goto L_0013cb54;
                }
                // 0x0013cb0c
                charge(ctx, 9);
                lhu(s6, s1, 0);
                a0 = 1;
                a1 = 2;
                jal(ctx, 0x13CB18u, gen::fn_datGetEquipmentIdx_0016cb80);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                if (s6 == v1) {
                    goto L_0013cb54;
                }
                // 0x0013cb30
                charge(ctx, 9);
                lhu(s6, s1, 0);
                a0 = 1;
                a1 = 3;
                jal(ctx, 0x13CB3Cu, gen::fn_datGetEquipmentIdx_0016cb80);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                if (s6 == v1) {
                    goto L_0013cb54;
                }
                // 0x0013cb60
                charge(ctx, 2);
                v1 = 1;
                sw(v1, s0, 116);
                goto L_0013cb68;
            }
        L_0013cb54:
            charge(ctx, 3);
            sw(zero, s0, 116);
        L_0013cb68:
            charge(ctx, 4);
            lbu(a1, fp, 0x0);
            v1 = 3;
            if (a1 != v1) {
                // 0x0013cb78
                charge(ctx, 3);
                v1 = 2;
                if (a1 == v1) {
                    // 0x0013cc00
                    charge(ctx, 5);
                    lhu(a1, s1, 0);
                    a0 = 1;
                    jal(ctx, 0x13CC08u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                    sh(v0, s0, 134);
                } else {
                    // 0x0013cb84
                    charge(ctx, 3);
                    a0 = 1;
                    if (a1 == a0) {
                        // 0x0013cbe8
                        charge(ctx, 6);
                        lhu(a1, s1, 0);
                        jal(ctx, 0x13CBECu, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                        sh(v0, s0, 132);
                    } else {
                        // 0x0013cb90
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x0013cba0
                            charge(ctx, 18);
                            v0 = sll(s2, 1);
                            v0 = addu(v0, sp);
                            s0 = addiu(v0, 176);
                            v0 = sll(s4, 3);
                            v0 = addu(v0, s4);
                            v0 = sll(v0, 2);
                            s1 = addu(s5, v0);
                            lhu(a1, s0, 0);
                            jal(ctx, 0x13CBC0u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                            sh(v0, s1, 128);
                            lhu(a1, s0, 0);
                            a0 = 1;
                            jal(ctx, 0x13CBD4u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                            sh(v0, s1, 130);
                        } else {
                            // 0x0013cb98
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0013cc14
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x0013cc18
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0013cc28
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x0013cc44
        charge(ctx, 3);
        v1 = slti(a0, 21);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013cc34
        charge(ctx, 4);
        v1 = sll(a0, 2);
        v1 = addu(s5, v1);
        sw(zero, v1, 12);
        a0 = addiu(a0, 1);
    }
    // 0x0013cc50
    charge(ctx, 14);
    sw(s4, s5, 11620);
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
    sp = addiu(sp, 0x310);
    return;
L_0013ca40_24:
    charge(ctx, 3);
    sw(s6, s0, 120);
    goto L_0013ca5c;
}

// 0x0013D1A0 sub_13D1A0 -- 5480 bytes; frame 0x210: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ItemDrawEquipList] (xy, list, alpha): the equipment page's list: the scroll marks when the list has rows
// (+2905 words = the count), the five visible rows from the scroll (+11628) with icon (camp file 0, by the kind table),
// name, the owner marks and the stat digits (font 1), the cursor row (+11624) highlighted.
void sub_13D1A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    // 0x0013d1a0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f31, sp, 0x2C);
    swc1(f30, sp, 0x28);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x108);
    mov_s(f29, f12);
    s2 = a1;
    s1 = a2;
    v0 = 255;
    s3 = subu(v0, s1);
    lw(v0, a1, 11620);
    if (v0 != 0) {
        // 0x0013d220
        charge(ctx, 49);
        lwc1(f1, sp, 0x10C);
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        lw(v1, s2, 11624);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x108);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 25;
        mov_s(f14, f29);
        jal(ctx, 0x13D284u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, s2, 11624);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 0x43F80000;  // 496.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x108);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 24;
        mov_s(f14, f29);
        jal(ctx, 0x13D2DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0013d2e4
    charge(ctx, 25);
    lwc1(f1, sp, 0x10C);
    v0 = 0x40C00000;  // 6.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 511;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x108);
    add_s(f20, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 26;
    mov_s(f12, f20);
    mov_s(f13, f21);
    mov_s(f14, f29);
    jal(ctx, 0x13D330u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s2, 11620);
    a0 = addiu(v0, -5);
    if (i64(a0) <= 0) {
        // 0x0013d36c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0013d348
        charge(ctx, 9);
        lw(v1, s2, 11628);
        v0 = 89;
        mult(v0, v1, v0);
        div(v0, a0);
        mflo(v0);
    }
    // 0x0013d370
    charge(ctx, 111);
    lwc1(f30, sp, 0x10C);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f1, f21, f0);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    a3 = s1 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 32;
    mov_s(f12, f20);
    mov_s(f14, f29);
    jal(ctx, 0x13D3B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s0 = 0;
    v1 = 0x40000000;  // 2.0f
    mtc1(v1, f0);
    add_s(f28, f0, f30);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f1);
    lwc1(f0, sp, 0x108);
    add_s(f27, f1, f0);
    v1 = si(-256);
    s7 = s3 | v1;
    cvt_w_s(f1, f30);
    cvt_s_w(f2, f1);
    v1 = 0x41300000;  // 11.0f
    mtc1(v1, f1);
    add_s(f26, f1, f2);
    cvt_w_s(f1, f0);
    cvt_s_w(f2, f1);
    v1 = 0x425C0000;  // 55.0f
    mtc1(v1, f1);
    add_s(f1, f1, f2);
    cvt_w_s(f1, f1);
    mfc1(fp, f1);
    v1 = 0x41100000;  // 9.0f
    mtc1(v1, f1);
    add_s(f25, f1, f30);
    v1 = 0x43900000;  // 288.0f
    mtc1(v1, f1);
    add_s(f24, f1, f0);
    v1 = 0x41800000;  // 16.0f
    mtc1(v1, f1);
    add_s(f23, f1, f30);
    v1 = 325;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f22, f1, f0);
    v1 = 341;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f21, f1, f0);
    v1 = 357;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f20, f1, f0);
    v1 = 0x43CA0000;  // 404.0f
    mtc1(v1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xDC);
    v1 = 441;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xD8);
    v1 = 457;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xD4);
    v1 = 473;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xD0);
    v1 = 0x43480000;  // 200.0f
    mtc1(v1, f1);
    add_s(f1, f1, f30);
    cvt_w_s(f1, f1);
    mfc1(v1, f1);
    sw(v1, sp, 0xF0);
    v1 = 0x41200000;  // 10.0f
    mtc1(v1, f1);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sw(v1, sp, 0xE0);
    for (;;) {
        // 0x0013e698
        charge(ctx, 3);
        v1 = slti(s0, 5);
        if (v1 != 0) {
            backedge(ctx);
            // 0x0013d52c
            charge(ctx, 6);
            lw(v1, s2, 11628);
            a0 = addu(s0, v1);
            lw(v1, s2, 11620);
            at = slt(a0, v1);
            if (at != 0) {
                // 0x0013d544
                charge(ctx, 3);
                lw(v0, s2, 11624);
                if (s0 != v0) {
                    // 0x0013de20
                    charge(ctx, 9);
                    v0 = 9;
                    v1 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s2, v1);
                    lw(v1, v1, 120);
                    at = sltiu(v1, 21);
                    if (at != 0) {
                        // 0x0013de44
                        charge(ctx, 7);
                        a0 = 0x7B0000;
                        a0 = addiu(a0, 23856);  // &0x7B5D30
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        lw(v1, v1, 0);
                        switch (v1.u()) {
                        case 0x13DE60u:  // table[0]
                            // 0x0013de60
                            charge(ctx, 3);
                            v0 = 1;
                            break;
                        case 0x13DE6Cu:  // table[1]
                            // 0x0013de6c
                            charge(ctx, 3);
                            v0 = 3;
                            break;
                        case 0x13DE78u:  // table[2]
                            // 0x0013de78
                            charge(ctx, 3);
                            v0 = 5;
                            break;
                        case 0x13DE84u:  // table[3]
                            // 0x0013de84
                            charge(ctx, 3);
                            v0 = 7;
                            break;
                        case 0x13DE90u:  // table[4]
                            // 0x0013de90
                            charge(ctx, 2);
                            break;
                        case 0x13DE98u:  // table[5]
                            // 0x0013de98
                            charge(ctx, 3);
                            v0 = 11;
                            break;
                        case 0x13DEA4u:  // table[6]
                            // 0x0013dea4
                            charge(ctx, 3);
                            v0 = 13;
                            break;
                        case 0x13DEB0u:  // table[7]
                            // 0x0013deb0
                            charge(ctx, 3);
                            v0 = 15;
                            break;
                        case 0x13DEBCu:  // table[8]
                            // 0x0013debc
                            charge(ctx, 3);
                            v0 = 1;
                            break;
                        case 0x13DEC8u:  // table[9]
                            // 0x0013dec8
                            charge(ctx, 3);
                            v0 = 3;
                            break;
                        case 0x13DED4u:  // table[10]
                            // 0x0013ded4
                            charge(ctx, 3);
                            v0 = 5;
                            break;
                        case 0x13DEE0u:  // table[11]
                            // 0x0013dee0
                            charge(ctx, 3);
                            v0 = 7;
                            break;
                        case 0x13DEECu:  // table[12]
                            // 0x0013deec
                            charge(ctx, 2);
                            break;
                        case 0x13DEF4u:  // table[13]
                            // 0x0013def4
                            charge(ctx, 3);
                            v0 = 11;
                            break;
                        case 0x13DF00u:  // table[14]
                            // 0x0013df00
                            charge(ctx, 3);
                            v0 = 13;
                            break;
                        case 0x13DF0Cu:  // table[15]
                            // 0x0013df0c
                            charge(ctx, 3);
                            v0 = 15;
                            break;
                        case 0x13DF18u:  // table[16]
                            // 0x0013df18
                            charge(ctx, 3);
                            v0 = 19;
                            break;
                        case 0x13DF24u:  // table[17]
                            // 0x0013df24
                            charge(ctx, 3);
                            v0 = 21;
                            break;
                        case 0x13DF30u:  // table[18]
                            // 0x0013df30
                            charge(ctx, 3);
                            v0 = 23;
                            break;
                        case 0x13DF3Cu:  // table[19]
                            // 0x0013df3c
                            charge(ctx, 3);
                            v0 = 27;
                            break;
                        case 0x13DF48u:  // table[20]
                            // 0x0013df48
                            charge(ctx, 1);
                            v0 = 27;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                    }
                    // 0x0013df4c
                    charge(ctx, 73);
                    v1 = sll(s0, 1);
                    v1 = addu(v1, s0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, s0);
                    s3 = sll(v1, 1);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f28, f0);
                    v1 = 0x3F800000;  // 1.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    a2 = addiu(v0, -1);
                    a3 = s1 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    mov_s(f12, f27);
                    t0 = 32;
                    t1 = 67;
                    t2 = 120;
                    mov_s(f14, f29);
                    jal(ctx, 0x13DFA8u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(s2, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x13DFDCu, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0x110);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x13DFF0u, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = fp;
                    mov_s(f12, f29);
                    a2 = s7;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0x110);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x13E040u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    lw(v1, s2, 11628);
                    a0 = addu(v1, s0);
                    v1 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s2, v1);
                    lbu(a0, v1, 126);
                    v1 = 3;
                    if (a0 != v1) {
                        // 0x0013e070
                        charge(ctx, 3);
                        v1 = 2;
                        if (a0 == v1) {
                            // 0x0013e508
                            charge(ctx, 24);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f25, f0);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 50;
                            mov_s(f12, f24);
                            mov_s(f14, f29);
                            jal(ctx, 0x13E534u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lw(v0, s2, 11628);
                            v1 = addu(v0, s0);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s2, v0);
                            lhu(s4, v0, 134);
                            s6 = 0;
                            v0 = slti(s4, 100);
                            if (v0 == 0) {
                                // 0x0013e568
                                charge(ctx, 26);
                                s6 = 1;
                                a0 = 2;
                                jal(ctx, 0x13E570u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 100;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f22);
                                mov_s(f14, f29);
                                jal(ctx, 0x13E5BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                v0 = 100;
                                div(s4, v0);
                                mfhi(s4);
                            }
                            // 0x0013e5d0
                            charge(ctx, 2);
                            if (s6 == 0) {
                                // 0x0013e5d8
                                charge(ctx, 3);
                                v0 = slti(s4, 10);
                                if (v0 == 0) {
                                    goto L_0013e5e4;
                                }
                                goto L_0013e63c;
                            }
                        L_0013e5e4:
                            charge(ctx, 22);
                            a0 = 2;
                            jal(ctx, 0x13E5E8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mflo(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f21);
                            mov_s(f14, f29);
                            jal(ctx, 0x13E634u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        L_0013e63c:
                            charge(ctx, 22);
                            a0 = 2;
                            jal(ctx, 0x13E640u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f20);
                            mov_s(f14, f29);
                            jal(ctx, 0x13E68Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x0013e07c
                            charge(ctx, 3);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x0013e374
                                charge(ctx, 24);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f25, f0);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 48;
                                mov_s(f12, f24);
                                mov_s(f14, f29);
                                jal(ctx, 0x13E3A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                lw(v0, s2, 11628);
                                v1 = addu(v0, s0);
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s2, v0);
                                lhu(s4, v0, 132);
                                s6 = 0;
                                v0 = slti(s4, 100);
                                if (v0 == 0) {
                                    // 0x0013e3d4
                                    charge(ctx, 26);
                                    s6 = 1;
                                    a0 = 2;
                                    jal(ctx, 0x13E3DCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 100;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f22);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E428u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    v0 = 100;
                                    div(s4, v0);
                                    mfhi(s4);
                                }
                                // 0x0013e43c
                                charge(ctx, 2);
                                if (s6 == 0) {
                                    // 0x0013e444
                                    charge(ctx, 3);
                                    v0 = slti(s4, 10);
                                    if (v0 == 0) {
                                        goto L_0013e450;
                                    }
                                    goto L_0013e4a8;
                                }
                            L_0013e450:
                                charge(ctx, 22);
                                a0 = 2;
                                jal(ctx, 0x13E454u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f21);
                                mov_s(f14, f29);
                                jal(ctx, 0x13E4A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            L_0013e4a8:
                                charge(ctx, 24);
                                a0 = 2;
                                jal(ctx, 0x13E4ACu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f20);
                                mov_s(f14, f29);
                                jal(ctx, 0x13E4F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x0013e088
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x0013e098
                                    charge(ctx, 25);
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f30, f25, f0);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 46;
                                    mov_s(f12, f24);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E0C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s4, v0, 128);
                                    s6 = 0;
                                    v0 = slti(s4, 100);
                                    if (v0 == 0) {
                                        // 0x0013e0fc
                                        charge(ctx, 26);
                                        s6 = 1;
                                        a0 = 2;
                                        jal(ctx, 0x13E104u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        mtc1(s3, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f1, f23, f0);
                                        v1 = 0x40400000;  // 3.0f
                                        mtc1(v1, f0);
                                        sub_s(f13, f1, f0);
                                        v1 = 100;
                                        div(s4, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        mov_s(f12, f22);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13E150u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s4, v0);
                                        mfhi(s4);
                                    }
                                    // 0x0013e164
                                    charge(ctx, 2);
                                    if (s6 == 0) {
                                        // 0x0013e16c
                                        charge(ctx, 3);
                                        v0 = slti(s4, 10);
                                        if (v0 == 0) {
                                            goto L_0013e178;
                                        }
                                        goto L_0013e1d0;
                                    }
                                L_0013e178:
                                    charge(ctx, 22);
                                    a0 = 2;
                                    jal(ctx, 0x13E17Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 10;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f21);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E1C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013e1d0:
                                    charge(ctx, 49);
                                    v0 = sll(s0, 1);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 1);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f31, f1, f0);
                                    a0 = 2;
                                    jal(ctx, 0x13E208u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s4, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f20);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E238u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 52;
                                    lwc1(f12, sp, 0xDC);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E260u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s3, v0, 130);
                                    s4 = 0;
                                    v0 = slti(s3, 100);
                                    if (v0 == 0) {
                                        // 0x0013e294
                                        charge(ctx, 19);
                                        s4 = 1;
                                        a0 = 2;
                                        jal(ctx, 0x13E29Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        v1 = 100;
                                        div(s3, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        lwc1(f12, sp, 0xD8);
                                        mov_s(f13, f31);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13E2CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s3, v0);
                                        mfhi(s3);
                                    }
                                    // 0x0013e2e0
                                    charge(ctx, 2);
                                    if (s4 == 0) {
                                        // 0x0013e2e8
                                        charge(ctx, 3);
                                        v0 = slti(s3, 10);
                                        if (v0 == 0) {
                                            goto L_0013e2f4;
                                        }
                                        goto L_0013e330;
                                    }
                                L_0013e2f4:
                                    charge(ctx, 15);
                                    a0 = 2;
                                    jal(ctx, 0x13E2F8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD4);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E328u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013e330:
                                    charge(ctx, 17);
                                    a0 = 2;
                                    jal(ctx, 0x13E334u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD0);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13E364u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x0013e090
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                } else {
                    // 0x0013d550
                    charge(ctx, 9);
                    v0 = 9;
                    v1 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s2, v1);
                    lw(v1, v1, 120);
                    at = sltiu(v1, 21);
                    if (at != 0) {
                        // 0x0013d574
                        charge(ctx, 7);
                        a0 = 0x7B0000;
                        a0 = addiu(a0, 23952);  // &0x7B5D90
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        lw(v1, v1, 0);
                        switch (v1.u()) {
                        case 0x13D590u:  // table[0]
                            // 0x0013d590
                            charge(ctx, 3);
                            v0 = 0;
                            break;
                        case 0x13D59Cu:  // table[1]
                            // 0x0013d59c
                            charge(ctx, 3);
                            v0 = 2;
                            break;
                        case 0x13D5A8u:  // table[2]
                            // 0x0013d5a8
                            charge(ctx, 3);
                            v0 = 4;
                            break;
                        case 0x13D5B4u:  // table[3]
                            // 0x0013d5b4
                            charge(ctx, 3);
                            v0 = 6;
                            break;
                        case 0x13D5C0u:  // table[4]
                            // 0x0013d5c0
                            charge(ctx, 3);
                            v0 = 8;
                            break;
                        case 0x13D5CCu:  // table[5]
                            // 0x0013d5cc
                            charge(ctx, 3);
                            v0 = 10;
                            break;
                        case 0x13D5D8u:  // table[6]
                            // 0x0013d5d8
                            charge(ctx, 3);
                            v0 = 12;
                            break;
                        case 0x13D5E4u:  // table[7]
                            // 0x0013d5e4
                            charge(ctx, 3);
                            v0 = 14;
                            break;
                        case 0x13D5F0u:  // table[8]
                            // 0x0013d5f0
                            charge(ctx, 3);
                            v0 = 0;
                            break;
                        case 0x13D5FCu:  // table[9]
                            // 0x0013d5fc
                            charge(ctx, 3);
                            v0 = 2;
                            break;
                        case 0x13D608u:  // table[10]
                            // 0x0013d608
                            charge(ctx, 3);
                            v0 = 4;
                            break;
                        case 0x13D614u:  // table[11]
                            // 0x0013d614
                            charge(ctx, 3);
                            v0 = 6;
                            break;
                        case 0x13D620u:  // table[12]
                            // 0x0013d620
                            charge(ctx, 3);
                            v0 = 8;
                            break;
                        case 0x13D62Cu:  // table[13]
                            // 0x0013d62c
                            charge(ctx, 3);
                            v0 = 10;
                            break;
                        case 0x13D638u:  // table[14]
                            // 0x0013d638
                            charge(ctx, 3);
                            v0 = 12;
                            break;
                        case 0x13D644u:  // table[15]
                            // 0x0013d644
                            charge(ctx, 3);
                            v0 = 14;
                            break;
                        case 0x13D650u:  // table[16]
                            // 0x0013d650
                            charge(ctx, 3);
                            v0 = 18;
                            break;
                        case 0x13D65Cu:  // table[17]
                            // 0x0013d65c
                            charge(ctx, 3);
                            v0 = 20;
                            break;
                        case 0x13D668u:  // table[18]
                            // 0x0013d668
                            charge(ctx, 3);
                            v0 = 22;
                            break;
                        case 0x13D674u:  // table[19]
                            // 0x0013d674
                            charge(ctx, 3);
                            v0 = 26;
                            break;
                        case 0x13D680u:  // table[20]
                            // 0x0013d680
                            charge(ctx, 1);
                            v0 = 28;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                    }
                    // 0x0013d684
                    charge(ctx, 71);
                    v1 = sll(s0, 1);
                    v1 = addu(v1, s0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, s0);
                    s3 = sll(v1, 1);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f28, f0);
                    v1 = 0x3F800000;  // 1.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    a2 = addiu(v0, 1);
                    a3 = s1 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    mov_s(f12, f27);
                    mov_s(f14, f29);
                    jal(ctx, 0x13D6D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(s2, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x13D708u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0x110);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x13D71Cu, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = fp;
                    mov_s(f12, f29);
                    a2 = s7;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0x110);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x13D770u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lbu(v1, v0, 126);
                    v0 = 3;
                    if (v1 != v0) {
                        // 0x0013d7a0
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x0013dc38
                            charge(ctx, 24);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f25, f0);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 51;
                            mov_s(f12, f24);
                            mov_s(f14, f29);
                            jal(ctx, 0x13DC64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lw(v0, s2, 11628);
                            v1 = addu(v0, s0);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s2, v0);
                            lhu(s4, v0, 134);
                            s6 = 0;
                            v0 = slti(s4, 100);
                            if (v0 == 0) {
                                // 0x0013dc98
                                charge(ctx, 26);
                                s6 = 1;
                                a0 = s6;
                                jal(ctx, 0x13DCA0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 100;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f22);
                                mov_s(f14, f29);
                                jal(ctx, 0x13DCECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                v0 = 100;
                                div(s4, v0);
                                mfhi(s4);
                            }
                            // 0x0013dd00
                            charge(ctx, 2);
                            if (s6 == 0) {
                                // 0x0013dd08
                                charge(ctx, 3);
                                v0 = slti(s4, 10);
                                if (v0 == 0) {
                                    goto L_0013dd14;
                                }
                                goto L_0013dd6c;
                            }
                        L_0013dd14:
                            charge(ctx, 22);
                            a0 = 1;
                            jal(ctx, 0x13DD18u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mflo(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f21);
                            mov_s(f14, f29);
                            jal(ctx, 0x13DD64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        L_0013dd6c:
                            charge(ctx, 22);
                            a0 = 1;
                            jal(ctx, 0x13DD70u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f20);
                            mov_s(f14, f29);
                            jal(ctx, 0x13DDBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x0013d7ac
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x0013daa4
                                charge(ctx, 24);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f25, f0);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 49;
                                mov_s(f12, f24);
                                mov_s(f14, f29);
                                jal(ctx, 0x13DAD0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                lw(v0, s2, 11628);
                                v1 = addu(v0, s0);
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s2, v0);
                                lhu(s4, v0, 132);
                                s6 = 0;
                                v0 = slti(s4, 100);
                                if (v0 == 0) {
                                    // 0x0013db04
                                    charge(ctx, 26);
                                    s6 = 1;
                                    a0 = s6;
                                    jal(ctx, 0x13DB0Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 100;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f22);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13DB58u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    v0 = 100;
                                    div(s4, v0);
                                    mfhi(s4);
                                }
                                // 0x0013db6c
                                charge(ctx, 2);
                                if (s6 == 0) {
                                    // 0x0013db74
                                    charge(ctx, 3);
                                    v0 = slti(s4, 10);
                                    if (v0 == 0) {
                                        goto L_0013db80;
                                    }
                                    goto L_0013dbd8;
                                }
                            L_0013db80:
                                charge(ctx, 22);
                                a0 = 1;
                                jal(ctx, 0x13DB84u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f21);
                                mov_s(f14, f29);
                                jal(ctx, 0x13DBD0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            L_0013dbd8:
                                charge(ctx, 24);
                                a0 = 1;
                                jal(ctx, 0x13DBDCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f20);
                                mov_s(f14, f29);
                                jal(ctx, 0x13DC28u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x0013d7b8
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x0013d7c8
                                    charge(ctx, 25);
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f30, f25, f0);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 47;
                                    mov_s(f12, f24);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13D7F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s4, v0, 128);
                                    s6 = 0;
                                    v0 = slti(s4, 100);
                                    if (v0 == 0) {
                                        // 0x0013d82c
                                        charge(ctx, 26);
                                        s6 = 1;
                                        a0 = s6;
                                        jal(ctx, 0x13D834u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        mtc1(s3, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f1, f23, f0);
                                        v1 = 0x40400000;  // 3.0f
                                        mtc1(v1, f0);
                                        sub_s(f13, f1, f0);
                                        v1 = 100;
                                        div(s4, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        mov_s(f12, f22);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13D880u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s4, v0);
                                        mfhi(s4);
                                    }
                                    // 0x0013d894
                                    charge(ctx, 2);
                                    if (s6 == 0) {
                                        // 0x0013d89c
                                        charge(ctx, 3);
                                        v0 = slti(s4, 10);
                                        if (v0 == 0) {
                                            goto L_0013d8a8;
                                        }
                                        goto L_0013d900;
                                    }
                                L_0013d8a8:
                                    charge(ctx, 22);
                                    a0 = 1;
                                    jal(ctx, 0x13D8ACu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 10;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f21);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13D8F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013d900:
                                    charge(ctx, 49);
                                    v0 = sll(s0, 1);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 1);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f31, f1, f0);
                                    a0 = 1;
                                    jal(ctx, 0x13D938u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s4, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f20);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13D968u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 53;
                                    lwc1(f12, sp, 0xDC);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13D990u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s3, v0, 130);
                                    s4 = 0;
                                    v0 = slti(s3, 100);
                                    if (v0 == 0) {
                                        // 0x0013d9c4
                                        charge(ctx, 19);
                                        s4 = 1;
                                        a0 = s4;
                                        jal(ctx, 0x13D9CCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        v1 = 100;
                                        div(s3, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        lwc1(f12, sp, 0xD8);
                                        mov_s(f13, f31);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13D9FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s3, v0);
                                        mfhi(s3);
                                    }
                                    // 0x0013da10
                                    charge(ctx, 2);
                                    if (s4 == 0) {
                                        // 0x0013da18
                                        charge(ctx, 3);
                                        v0 = slti(s3, 10);
                                        if (v0 == 0) {
                                            goto L_0013da24;
                                        }
                                        goto L_0013da60;
                                    }
                                L_0013da24:
                                    charge(ctx, 15);
                                    a0 = 1;
                                    jal(ctx, 0x13DA28u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD4);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13DA58u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013da60:
                                    charge(ctx, 17);
                                    a0 = 1;
                                    jal(ctx, 0x13DA64u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD0);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13DA94u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x0013d7c0
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                    // 0x0013ddc4
                    charge(ctx, 23);
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    a0 = addu(s2, v0);
                    lbu(v0, a0, 124);
                    v1 = sll(v0, 16);
                    v0 = lui(0xFFFF);
                    v1 = v1 & v0;
                    lhu(v0, a0, 100);
                    t2 = v0 | v1;
                    lw(a0, sp, 0xE0);
                    lw(a1, sp, 0xF0);
                    mov_s(f12, f29);
                    a2 = s7;
                    a3 = 1;
                    t0 = 10;
                    t1 = a3;
                    jal(ctx, 0x13DE10u, gen::fn_sub_3C7E20_003c7e20);  // a message text
                }
                // 0x0013e694
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0013e6a4 (the shared epilogue, written out on this path)
    charge(ctx, 25);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f31, sp, 0x2C);
    lwc1(f30, sp, 0x28);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x210);
}

// 0x0013E710 sub_13E710 -- 5508 bytes; frame 0x210: ra sp+0xC0, fp sp+0xB0 (sq), s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ItemDrawEquipList2] (xy, list, alpha): sub_13D1A0 at the trade layout (text 40 px higher, 14 px further
// right).
void sub_13E710(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    // 0x0013e710
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
    sd(ra, sp, 0xC0);
    sq(fp, sp, 0xB0);
    sq(s7, sp, 0xA0);
    sq(s6, sp, 0x90);
    sq(s5, sp, 0x80);
    sq(s4, sp, 0x70);
    sq(s3, sp, 0x60);
    sq(s2, sp, 0x50);
    sq(s1, sp, 0x40);
    sq(s0, sp, 0x30);
    swc1(f31, sp, 0x2C);
    swc1(f30, sp, 0x28);
    swc1(f29, sp, 0x24);
    swc1(f28, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x108);
    mov_s(f29, f12);
    s2 = a1;
    s1 = a2;
    v0 = 255;
    s3 = subu(v0, s1);
    lw(v0, a1, 11620);
    if (v0 != 0) {
        // 0x0013e790
        charge(ctx, 49);
        lwc1(f1, sp, 0x10C);
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        lw(v1, s2, 11624);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x108);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 25;
        mov_s(f14, f29);
        jal(ctx, 0x13E7F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, s2, 11624);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 0x43F80000;  // 496.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x108);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 24;
        mov_s(f14, f29);
        jal(ctx, 0x13E84Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0013e854
    charge(ctx, 25);
    lwc1(f1, sp, 0x10C);
    v0 = 0x40C00000;  // 6.0f
    mtc1(v0, f0);
    add_s(f21, f0, f1);
    v0 = 511;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x108);
    add_s(f20, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 26;
    mov_s(f12, f20);
    mov_s(f13, f21);
    mov_s(f14, f29);
    jal(ctx, 0x13E8A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s2, 11620);
    a0 = addiu(v0, -5);
    if (i64(a0) <= 0) {
        // 0x0013e8dc
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0013e8b8
        charge(ctx, 9);
        lw(v1, s2, 11628);
        v0 = 89;
        mult(v0, v1, v0);
        div(v0, a0);
        mflo(v0);
    }
    // 0x0013e8e0
    charge(ctx, 118);
    lwc1(f30, sp, 0x10C);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f1, f21, f0);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    a3 = s1 & 0xFF;
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 32;
    mov_s(f12, f20);
    mov_s(f14, f29);
    jal(ctx, 0x13E920u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s0 = 0;
    v1 = 0x40000000;  // 2.0f
    mtc1(v1, f0);
    add_s(f28, f0, f30);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f1);
    lwc1(f0, sp, 0x108);
    add_s(f27, f1, f0);
    v1 = si(-256);
    s7 = s3 | v1;
    cvt_w_s(f1, f30);
    cvt_s_w(f2, f1);
    v1 = 0x41300000;  // 11.0f
    mtc1(v1, f1);
    add_s(f26, f1, f2);
    cvt_w_s(f1, f0);
    cvt_s_w(f2, f1);
    v1 = 0x425C0000;  // 55.0f
    mtc1(v1, f1);
    add_s(f1, f1, f2);
    cvt_w_s(f1, f1);
    mfc1(fp, f1);
    v1 = 0x41100000;  // 9.0f
    mtc1(v1, f1);
    add_s(f25, f1, f30);
    v1 = 0x43900000;  // 288.0f
    mtc1(v1, f1);
    add_s(f24, f1, f0);
    v1 = 0x41800000;  // 16.0f
    mtc1(v1, f1);
    add_s(f23, f1, f30);
    v1 = 325;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f22, f1, f0);
    v1 = 341;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f21, f1, f0);
    v1 = 357;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f20, f1, f0);
    v1 = 0x43CA0000;  // 404.0f
    mtc1(v1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xDC);
    v1 = 441;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xD8);
    v1 = 457;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xD4);
    v1 = 473;
    mtc1(v1, f1);
    cvt_s_w(f1, f1);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0xD0);
    v1 = 0x43480000;  // 200.0f
    mtc1(v1, f1);
    add_s(f2, f1, f30);
    v1 = 0x42200000;  // 40.0f
    mtc1(v1, f1);
    sub_s(f1, f2, f1);
    cvt_w_s(f1, f1);
    mfc1(v1, f1);
    sw(v1, sp, 0xF0);
    v1 = 0x41600000;  // 14.0f
    mtc1(v1, f2);
    v1 = 0x41200000;  // 10.0f
    mtc1(v1, f1);
    add_s(f0, f1, f0);
    add_s(f0, f2, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sw(v1, sp, 0xE0);
    for (;;) {
        // 0x0013fc24
        charge(ctx, 3);
        v1 = slti(s0, 5);
        if (v1 != 0) {
            backedge(ctx);
            // 0x0013eab8
            charge(ctx, 6);
            lw(v1, s2, 11628);
            a0 = addu(s0, v1);
            lw(v1, s2, 11620);
            at = slt(a0, v1);
            if (at != 0) {
                // 0x0013ead0
                charge(ctx, 3);
                lw(v0, s2, 11624);
                if (s0 != v0) {
                    // 0x0013f3ac
                    charge(ctx, 9);
                    v0 = 9;
                    v1 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s2, v1);
                    lw(v1, v1, 120);
                    at = sltiu(v1, 21);
                    if (at != 0) {
                        // 0x0013f3d0
                        charge(ctx, 7);
                        a0 = 0x7B0000;
                        a0 = addiu(a0, 24048);  // &0x7B5DF0
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        lw(v1, v1, 0);
                        switch (v1.u()) {
                        case 0x13F3ECu:  // table[0]
                            // 0x0013f3ec
                            charge(ctx, 3);
                            v0 = 1;
                            break;
                        case 0x13F3F8u:  // table[1]
                            // 0x0013f3f8
                            charge(ctx, 3);
                            v0 = 3;
                            break;
                        case 0x13F404u:  // table[2]
                            // 0x0013f404
                            charge(ctx, 3);
                            v0 = 5;
                            break;
                        case 0x13F410u:  // table[3]
                            // 0x0013f410
                            charge(ctx, 3);
                            v0 = 7;
                            break;
                        case 0x13F41Cu:  // table[4]
                            // 0x0013f41c
                            charge(ctx, 2);
                            break;
                        case 0x13F424u:  // table[5]
                            // 0x0013f424
                            charge(ctx, 3);
                            v0 = 11;
                            break;
                        case 0x13F430u:  // table[6]
                            // 0x0013f430
                            charge(ctx, 3);
                            v0 = 13;
                            break;
                        case 0x13F43Cu:  // table[7]
                            // 0x0013f43c
                            charge(ctx, 3);
                            v0 = 15;
                            break;
                        case 0x13F448u:  // table[8]
                            // 0x0013f448
                            charge(ctx, 3);
                            v0 = 1;
                            break;
                        case 0x13F454u:  // table[9]
                            // 0x0013f454
                            charge(ctx, 3);
                            v0 = 3;
                            break;
                        case 0x13F460u:  // table[10]
                            // 0x0013f460
                            charge(ctx, 3);
                            v0 = 5;
                            break;
                        case 0x13F46Cu:  // table[11]
                            // 0x0013f46c
                            charge(ctx, 3);
                            v0 = 7;
                            break;
                        case 0x13F478u:  // table[12]
                            // 0x0013f478
                            charge(ctx, 2);
                            break;
                        case 0x13F480u:  // table[13]
                            // 0x0013f480
                            charge(ctx, 3);
                            v0 = 11;
                            break;
                        case 0x13F48Cu:  // table[14]
                            // 0x0013f48c
                            charge(ctx, 3);
                            v0 = 13;
                            break;
                        case 0x13F498u:  // table[15]
                            // 0x0013f498
                            charge(ctx, 3);
                            v0 = 15;
                            break;
                        case 0x13F4A4u:  // table[16]
                            // 0x0013f4a4
                            charge(ctx, 3);
                            v0 = 19;
                            break;
                        case 0x13F4B0u:  // table[17]
                            // 0x0013f4b0
                            charge(ctx, 3);
                            v0 = 21;
                            break;
                        case 0x13F4BCu:  // table[18]
                            // 0x0013f4bc
                            charge(ctx, 3);
                            v0 = 23;
                            break;
                        case 0x13F4C8u:  // table[19]
                            // 0x0013f4c8
                            charge(ctx, 3);
                            v0 = 27;
                            break;
                        case 0x13F4D4u:  // table[20]
                            // 0x0013f4d4
                            charge(ctx, 1);
                            v0 = 27;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                    }
                    // 0x0013f4d8
                    charge(ctx, 73);
                    v1 = sll(s0, 1);
                    v1 = addu(v1, s0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, s0);
                    s3 = sll(v1, 1);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f28, f0);
                    v1 = 0x3F800000;  // 1.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    a2 = addiu(v0, -1);
                    a3 = s1 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    mov_s(f12, f27);
                    t0 = 32;
                    t1 = 67;
                    t2 = 120;
                    mov_s(f14, f29);
                    jal(ctx, 0x13F534u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(s2, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x13F568u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0x110);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x13F57Cu, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = fp;
                    mov_s(f12, f29);
                    a2 = s7;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0x110);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x13F5CCu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v1, s2, 11628);
                    a0 = addu(v1, s0);
                    v1 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s2, v1);
                    lbu(a0, v1, 126);
                    v1 = 3;
                    if (a0 != v1) {
                        // 0x0013f5fc
                        charge(ctx, 3);
                        v1 = 2;
                        if (a0 == v1) {
                            // 0x0013fa94
                            charge(ctx, 24);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f25, f0);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 50;
                            mov_s(f12, f24);
                            mov_s(f14, f29);
                            jal(ctx, 0x13FAC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lw(v0, s2, 11628);
                            v1 = addu(v0, s0);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s2, v0);
                            lhu(s4, v0, 134);
                            s6 = 0;
                            v0 = slti(s4, 100);
                            if (v0 == 0) {
                                // 0x0013faf4
                                charge(ctx, 26);
                                s6 = 1;
                                a0 = 2;
                                jal(ctx, 0x13FAFCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 100;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f22);
                                mov_s(f14, f29);
                                jal(ctx, 0x13FB48u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                v0 = 100;
                                div(s4, v0);
                                mfhi(s4);
                            }
                            // 0x0013fb5c
                            charge(ctx, 2);
                            if (s6 == 0) {
                                // 0x0013fb64
                                charge(ctx, 3);
                                v0 = slti(s4, 10);
                                if (v0 == 0) {
                                    goto L_0013fb70;
                                }
                                goto L_0013fbc8;
                            }
                        L_0013fb70:
                            charge(ctx, 22);
                            a0 = 2;
                            jal(ctx, 0x13FB74u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mflo(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f21);
                            mov_s(f14, f29);
                            jal(ctx, 0x13FBC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        L_0013fbc8:
                            charge(ctx, 22);
                            a0 = 2;
                            jal(ctx, 0x13FBCCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f20);
                            mov_s(f14, f29);
                            jal(ctx, 0x13FC18u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x0013f608
                            charge(ctx, 3);
                            v1 = 1;
                            if (a0 == v1) {
                                // 0x0013f900
                                charge(ctx, 24);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f25, f0);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 48;
                                mov_s(f12, f24);
                                mov_s(f14, f29);
                                jal(ctx, 0x13F92Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                lw(v0, s2, 11628);
                                v1 = addu(v0, s0);
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s2, v0);
                                lhu(s4, v0, 132);
                                s6 = 0;
                                v0 = slti(s4, 100);
                                if (v0 == 0) {
                                    // 0x0013f960
                                    charge(ctx, 26);
                                    s6 = 1;
                                    a0 = 2;
                                    jal(ctx, 0x13F968u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 100;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f22);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F9B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    v0 = 100;
                                    div(s4, v0);
                                    mfhi(s4);
                                }
                                // 0x0013f9c8
                                charge(ctx, 2);
                                if (s6 == 0) {
                                    // 0x0013f9d0
                                    charge(ctx, 3);
                                    v0 = slti(s4, 10);
                                    if (v0 == 0) {
                                        goto L_0013f9dc;
                                    }
                                    goto L_0013fa34;
                                }
                            L_0013f9dc:
                                charge(ctx, 22);
                                a0 = 2;
                                jal(ctx, 0x13F9E0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f21);
                                mov_s(f14, f29);
                                jal(ctx, 0x13FA2Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            L_0013fa34:
                                charge(ctx, 24);
                                a0 = 2;
                                jal(ctx, 0x13FA38u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f20);
                                mov_s(f14, f29);
                                jal(ctx, 0x13FA84u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x0013f614
                                charge(ctx, 2);
                                if (a0 == 0) {
                                    // 0x0013f624
                                    charge(ctx, 25);
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f30, f25, f0);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 46;
                                    mov_s(f12, f24);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F654u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s4, v0, 128);
                                    s6 = 0;
                                    v0 = slti(s4, 100);
                                    if (v0 == 0) {
                                        // 0x0013f688
                                        charge(ctx, 26);
                                        s6 = 1;
                                        a0 = 2;
                                        jal(ctx, 0x13F690u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        mtc1(s3, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f1, f23, f0);
                                        v1 = 0x40400000;  // 3.0f
                                        mtc1(v1, f0);
                                        sub_s(f13, f1, f0);
                                        v1 = 100;
                                        div(s4, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        mov_s(f12, f22);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13F6DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s4, v0);
                                        mfhi(s4);
                                    }
                                    // 0x0013f6f0
                                    charge(ctx, 2);
                                    if (s6 == 0) {
                                        // 0x0013f6f8
                                        charge(ctx, 3);
                                        v0 = slti(s4, 10);
                                        if (v0 == 0) {
                                            goto L_0013f704;
                                        }
                                        goto L_0013f75c;
                                    }
                                L_0013f704:
                                    charge(ctx, 22);
                                    a0 = 2;
                                    jal(ctx, 0x13F708u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 10;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f21);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F754u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013f75c:
                                    charge(ctx, 49);
                                    v0 = sll(s0, 1);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 1);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f31, f1, f0);
                                    a0 = 2;
                                    jal(ctx, 0x13F794u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s4, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f20);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F7C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 52;
                                    lwc1(f12, sp, 0xDC);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F7ECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s3, v0, 130);
                                    s4 = 0;
                                    v0 = slti(s3, 100);
                                    if (v0 == 0) {
                                        // 0x0013f820
                                        charge(ctx, 19);
                                        s4 = 1;
                                        a0 = 2;
                                        jal(ctx, 0x13F828u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        v1 = 100;
                                        div(s3, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        lwc1(f12, sp, 0xD8);
                                        mov_s(f13, f31);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13F858u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s3, v0);
                                        mfhi(s3);
                                    }
                                    // 0x0013f86c
                                    charge(ctx, 2);
                                    if (s4 == 0) {
                                        // 0x0013f874
                                        charge(ctx, 3);
                                        v0 = slti(s3, 10);
                                        if (v0 == 0) {
                                            goto L_0013f880;
                                        }
                                        goto L_0013f8bc;
                                    }
                                L_0013f880:
                                    charge(ctx, 15);
                                    a0 = 2;
                                    jal(ctx, 0x13F884u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD4);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F8B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013f8bc:
                                    charge(ctx, 17);
                                    a0 = 2;
                                    jal(ctx, 0x13F8C0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD0);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F8F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x0013f61c
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                } else {
                    // 0x0013eadc
                    charge(ctx, 9);
                    v0 = 9;
                    v1 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(s2, v1);
                    lw(v1, v1, 120);
                    at = sltiu(v1, 21);
                    if (at != 0) {
                        // 0x0013eb00
                        charge(ctx, 7);
                        a0 = 0x7B0000;
                        a0 = addiu(a0, 24144);  // &0x7B5E50
                        v1 = sll(v1, 2);
                        v1 = addu(v1, a0);
                        lw(v1, v1, 0);
                        switch (v1.u()) {
                        case 0x13EB1Cu:  // table[0]
                            // 0x0013eb1c
                            charge(ctx, 3);
                            v0 = 0;
                            break;
                        case 0x13EB28u:  // table[1]
                            // 0x0013eb28
                            charge(ctx, 3);
                            v0 = 2;
                            break;
                        case 0x13EB34u:  // table[2]
                            // 0x0013eb34
                            charge(ctx, 3);
                            v0 = 4;
                            break;
                        case 0x13EB40u:  // table[3]
                            // 0x0013eb40
                            charge(ctx, 3);
                            v0 = 6;
                            break;
                        case 0x13EB4Cu:  // table[4]
                            // 0x0013eb4c
                            charge(ctx, 3);
                            v0 = 8;
                            break;
                        case 0x13EB58u:  // table[5]
                            // 0x0013eb58
                            charge(ctx, 3);
                            v0 = 10;
                            break;
                        case 0x13EB64u:  // table[6]
                            // 0x0013eb64
                            charge(ctx, 3);
                            v0 = 12;
                            break;
                        case 0x13EB70u:  // table[7]
                            // 0x0013eb70
                            charge(ctx, 3);
                            v0 = 14;
                            break;
                        case 0x13EB7Cu:  // table[8]
                            // 0x0013eb7c
                            charge(ctx, 3);
                            v0 = 0;
                            break;
                        case 0x13EB88u:  // table[9]
                            // 0x0013eb88
                            charge(ctx, 3);
                            v0 = 2;
                            break;
                        case 0x13EB94u:  // table[10]
                            // 0x0013eb94
                            charge(ctx, 3);
                            v0 = 4;
                            break;
                        case 0x13EBA0u:  // table[11]
                            // 0x0013eba0
                            charge(ctx, 3);
                            v0 = 6;
                            break;
                        case 0x13EBACu:  // table[12]
                            // 0x0013ebac
                            charge(ctx, 3);
                            v0 = 8;
                            break;
                        case 0x13EBB8u:  // table[13]
                            // 0x0013ebb8
                            charge(ctx, 3);
                            v0 = 10;
                            break;
                        case 0x13EBC4u:  // table[14]
                            // 0x0013ebc4
                            charge(ctx, 3);
                            v0 = 12;
                            break;
                        case 0x13EBD0u:  // table[15]
                            // 0x0013ebd0
                            charge(ctx, 3);
                            v0 = 14;
                            break;
                        case 0x13EBDCu:  // table[16]
                            // 0x0013ebdc
                            charge(ctx, 3);
                            v0 = 18;
                            break;
                        case 0x13EBE8u:  // table[17]
                            // 0x0013ebe8
                            charge(ctx, 3);
                            v0 = 20;
                            break;
                        case 0x13EBF4u:  // table[18]
                            // 0x0013ebf4
                            charge(ctx, 3);
                            v0 = 22;
                            break;
                        case 0x13EC00u:  // table[19]
                            // 0x0013ec00
                            charge(ctx, 3);
                            v0 = 26;
                            break;
                        case 0x13EC0Cu:  // table[20]
                            // 0x0013ec0c
                            charge(ctx, 1);
                            v0 = 28;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v1.u());
                            return;
                        }
                    }
                    // 0x0013ec10
                    charge(ctx, 71);
                    v1 = sll(s0, 1);
                    v1 = addu(v1, s0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, s0);
                    s3 = sll(v1, 1);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f28, f0);
                    v1 = 0x3F800000;  // 1.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    a2 = addiu(v0, 1);
                    a3 = s1 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    mov_s(f12, f27);
                    mov_s(f14, f29);
                    jal(ctx, 0x13EC60u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(s2, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x13EC94u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0x110);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x13ECA8u, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = fp;
                    mov_s(f12, f29);
                    a2 = s7;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0x110);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x13ECFCu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lbu(v1, v0, 126);
                    v0 = 3;
                    if (v1 != v0) {
                        // 0x0013ed2c
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x0013f1c4
                            charge(ctx, 24);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f25, f0);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 51;
                            mov_s(f12, f24);
                            mov_s(f14, f29);
                            jal(ctx, 0x13F1F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lw(v0, s2, 11628);
                            v1 = addu(v0, s0);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(s2, v0);
                            lhu(s4, v0, 134);
                            s6 = 0;
                            v0 = slti(s4, 100);
                            if (v0 == 0) {
                                // 0x0013f224
                                charge(ctx, 26);
                                s6 = 1;
                                a0 = s6;
                                jal(ctx, 0x13F22Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 100;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f22);
                                mov_s(f14, f29);
                                jal(ctx, 0x13F278u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                v0 = 100;
                                div(s4, v0);
                                mfhi(s4);
                            }
                            // 0x0013f28c
                            charge(ctx, 2);
                            if (s6 == 0) {
                                // 0x0013f294
                                charge(ctx, 3);
                                v0 = slti(s4, 10);
                                if (v0 == 0) {
                                    goto L_0013f2a0;
                                }
                                goto L_0013f2f8;
                            }
                        L_0013f2a0:
                            charge(ctx, 22);
                            a0 = 1;
                            jal(ctx, 0x13F2A4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mflo(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f21);
                            mov_s(f14, f29);
                            jal(ctx, 0x13F2F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        L_0013f2f8:
                            charge(ctx, 22);
                            a0 = 1;
                            jal(ctx, 0x13F2FCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f23, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f13, f1, f0);
                            v1 = 10;
                            div(s4, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f20);
                            mov_s(f14, f29);
                            jal(ctx, 0x13F348u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x0013ed38
                            charge(ctx, 3);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x0013f030
                                charge(ctx, 24);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f25, f0);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 49;
                                mov_s(f12, f24);
                                mov_s(f14, f29);
                                jal(ctx, 0x13F05Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                lw(v0, s2, 11628);
                                v1 = addu(v0, s0);
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(s2, v0);
                                lhu(s4, v0, 132);
                                s6 = 0;
                                v0 = slti(s4, 100);
                                if (v0 == 0) {
                                    // 0x0013f090
                                    charge(ctx, 26);
                                    s6 = 1;
                                    a0 = s6;
                                    jal(ctx, 0x13F098u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 100;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f22);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F0E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    v0 = 100;
                                    div(s4, v0);
                                    mfhi(s4);
                                }
                                // 0x0013f0f8
                                charge(ctx, 2);
                                if (s6 == 0) {
                                    // 0x0013f100
                                    charge(ctx, 3);
                                    v0 = slti(s4, 10);
                                    if (v0 == 0) {
                                        goto L_0013f10c;
                                    }
                                    goto L_0013f164;
                                }
                            L_0013f10c:
                                charge(ctx, 22);
                                a0 = 1;
                                jal(ctx, 0x13F110u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f21);
                                mov_s(f14, f29);
                                jal(ctx, 0x13F15Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            L_0013f164:
                                charge(ctx, 24);
                                a0 = 1;
                                jal(ctx, 0x13F168u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f23, f0);
                                v1 = 0x40400000;  // 3.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                v1 = 10;
                                div(s4, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                a1 = v0;
                                mov_s(f12, f20);
                                mov_s(f14, f29);
                                jal(ctx, 0x13F1B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x0013ed44
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x0013ed54
                                    charge(ctx, 25);
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f30, f25, f0);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 47;
                                    mov_s(f12, f24);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13ED84u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s4, v0, 128);
                                    s6 = 0;
                                    v0 = slti(s4, 100);
                                    if (v0 == 0) {
                                        // 0x0013edb8
                                        charge(ctx, 26);
                                        s6 = 1;
                                        a0 = s6;
                                        jal(ctx, 0x13EDC0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        mtc1(s3, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f1, f23, f0);
                                        v1 = 0x40400000;  // 3.0f
                                        mtc1(v1, f0);
                                        sub_s(f13, f1, f0);
                                        v1 = 100;
                                        div(s4, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        mov_s(f12, f22);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13EE0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s4, v0);
                                        mfhi(s4);
                                    }
                                    // 0x0013ee20
                                    charge(ctx, 2);
                                    if (s6 == 0) {
                                        // 0x0013ee28
                                        charge(ctx, 3);
                                        v0 = slti(s4, 10);
                                        if (v0 == 0) {
                                            goto L_0013ee34;
                                        }
                                        goto L_0013ee8c;
                                    }
                                L_0013ee34:
                                    charge(ctx, 22);
                                    a0 = 1;
                                    jal(ctx, 0x13EE38u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v1 = 0x40400000;  // 3.0f
                                    mtc1(v1, f0);
                                    sub_s(f13, f1, f0);
                                    v1 = 10;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f21);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13EE84u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013ee8c:
                                    charge(ctx, 49);
                                    v0 = sll(s0, 1);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 1);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f23, f0);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f31, f1, f0);
                                    a0 = 1;
                                    jal(ctx, 0x13EEC4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s4, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    mov_s(f12, f20);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13EEF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 53;
                                    lwc1(f12, sp, 0xDC);
                                    mov_s(f13, f30);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13EF1Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v0, s2, 11628);
                                    v1 = addu(v0, s0);
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    v0 = addu(s2, v0);
                                    lhu(s3, v0, 130);
                                    s4 = 0;
                                    v0 = slti(s3, 100);
                                    if (v0 == 0) {
                                        // 0x0013ef50
                                        charge(ctx, 19);
                                        s4 = 1;
                                        a0 = s4;
                                        jal(ctx, 0x13EF58u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        v1 = 100;
                                        div(s3, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        a3 = s1 & 0xFF;
                                        a0 = s5;
                                        a1 = v0;
                                        lwc1(f12, sp, 0xD8);
                                        mov_s(f13, f31);
                                        mov_s(f14, f29);
                                        jal(ctx, 0x13EF88u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        v0 = 100;
                                        div(s3, v0);
                                        mfhi(s3);
                                    }
                                    // 0x0013ef9c
                                    charge(ctx, 2);
                                    if (s4 == 0) {
                                        // 0x0013efa4
                                        charge(ctx, 3);
                                        v0 = slti(s3, 10);
                                        if (v0 == 0) {
                                            goto L_0013efb0;
                                        }
                                        goto L_0013efec;
                                    }
                                L_0013efb0:
                                    charge(ctx, 15);
                                    a0 = 1;
                                    jal(ctx, 0x13EFB4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD4);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13EFE4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                L_0013efec:
                                    charge(ctx, 17);
                                    a0 = 1;
                                    jal(ctx, 0x13EFF0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s3, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    a3 = s1 & 0xFF;
                                    a0 = s5;
                                    a1 = v0;
                                    lwc1(f12, sp, 0xD0);
                                    mov_s(f13, f31);
                                    mov_s(f14, f29);
                                    jal(ctx, 0x13F020u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x0013ed4c
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                    // 0x0013f350
                    charge(ctx, 23);
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    a0 = addu(s2, v0);
                    lbu(v0, a0, 124);
                    v1 = sll(v0, 16);
                    v0 = lui(0xFFFF);
                    v1 = v1 & v0;
                    lhu(v0, a0, 100);
                    t2 = v0 | v1;
                    lw(a0, sp, 0xE0);
                    lw(a1, sp, 0xF0);
                    mov_s(f12, f29);
                    a2 = s7;
                    a3 = 1;
                    t0 = 10;
                    t1 = a3;
                    jal(ctx, 0x13F39Cu, gen::fn_sub_3C7E20_003c7e20);  // a message text
                }
                // 0x0013fc20
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0013fc30 (the shared epilogue, written out on this path)
    charge(ctx, 25);
    ld(ra, sp, 0xC0);
    lq(fp, sp, 0xB0);
    lq(s7, sp, 0xA0);
    lq(s6, sp, 0x90);
    lq(s5, sp, 0x80);
    lq(s4, sp, 0x70);
    lq(s3, sp, 0x60);
    lq(s2, sp, 0x50);
    lq(s1, sp, 0x40);
    lq(s0, sp, 0x30);
    lwc1(f31, sp, 0x2C);
    lwc1(f30, sp, 0x28);
    lwc1(f29, sp, 0x24);
    lwc1(f28, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x210);
}

// 0x0013FCA0 sub_13FCA0 -- 2604 bytes; frame 0x190: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ItemDrawEquipDetail] (xy, list, alpha): the selected equipment row's detail: its kind icon (jump table
// 0x7B5EB0 on the row's kind: 0..5 -> sprite 0, 2, 4 ...), name and stat digits.
void sub_13FCA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0013fca0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
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
    sd(a0, sp, 0x88);
    mov_s(f22, f12);
    s2 = a1;
    s1 = a2;
    v0 = 255;
    s4 = subu(v0, s1);
    lw(s3, a1, 11624);
    a0 = 9;
    lw(v0, a1, 11628);
    v1 = addu(v0, s3);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, s2);
    lw(v0, v0, 120);
    at = sltiu(v0, 21);
    if (at != 0) {
        // 0x0013fd14
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 24240);  // &0x7B5EB0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x13FD30u:  // table[0]
            // 0x0013fd30
            charge(ctx, 3);
            a0 = 0;
            break;
        case 0x13FD3Cu:  // table[1]
            // 0x0013fd3c
            charge(ctx, 3);
            a0 = 2;
            break;
        case 0x13FD48u:  // table[2]
            // 0x0013fd48
            charge(ctx, 3);
            a0 = 4;
            break;
        case 0x13FD54u:  // table[3]
            // 0x0013fd54
            charge(ctx, 3);
            a0 = 6;
            break;
        case 0x13FD60u:  // table[4]
            // 0x0013fd60
            charge(ctx, 3);
            a0 = 8;
            break;
        case 0x13FD6Cu:  // table[5]
            // 0x0013fd6c
            charge(ctx, 3);
            a0 = 10;
            break;
        case 0x13FD78u:  // table[6]
            // 0x0013fd78
            charge(ctx, 3);
            a0 = 12;
            break;
        case 0x13FD84u:  // table[7]
            // 0x0013fd84
            charge(ctx, 3);
            a0 = 14;
            break;
        case 0x13FD90u:  // table[8]
            // 0x0013fd90
            charge(ctx, 3);
            a0 = 0;
            break;
        case 0x13FD9Cu:  // table[9]
            // 0x0013fd9c
            charge(ctx, 3);
            a0 = 2;
            break;
        case 0x13FDA8u:  // table[10]
            // 0x0013fda8
            charge(ctx, 3);
            a0 = 4;
            break;
        case 0x13FDB4u:  // table[11]
            // 0x0013fdb4
            charge(ctx, 3);
            a0 = 6;
            break;
        case 0x13FDC0u:  // table[12]
            // 0x0013fdc0
            charge(ctx, 3);
            a0 = 8;
            break;
        case 0x13FDCCu:  // table[13]
            // 0x0013fdcc
            charge(ctx, 3);
            a0 = 10;
            break;
        case 0x13FDD8u:  // table[14]
            // 0x0013fdd8
            charge(ctx, 3);
            a0 = 12;
            break;
        case 0x13FDE4u:  // table[15]
            // 0x0013fde4
            charge(ctx, 3);
            a0 = 14;
            break;
        case 0x13FDF0u:  // table[16]
            // 0x0013fdf0
            charge(ctx, 3);
            a0 = 18;
            break;
        case 0x13FDFCu:  // table[17]
            // 0x0013fdfc
            charge(ctx, 3);
            a0 = 20;
            break;
        case 0x13FE08u:  // table[18]
            // 0x0013fe08
            charge(ctx, 3);
            a0 = 22;
            break;
        case 0x13FE14u:  // table[19]
            // 0x0013fe14
            charge(ctx, 3);
            a0 = 26;
            break;
        case 0x13FE20u:  // table[20]
            // 0x0013fe20
            charge(ctx, 1);
            a0 = 26;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x0013fe24
    charge(ctx, 80);
    lwc1(f20, sp, 0x8C);
    a2 = addiu(a0, 1);
    v0 = 0x41700000;  // 15.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x88);
    add_s(f12, f1, f0);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
    mov_s(f14, f22);
    jal(ctx, 0x13FE70u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s2, 11628);
    v1 = addu(v0, s3);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v1 = addu(v0, s2);
    lh(v0, v1, 100);
    a0 = v0;
    lbu(v0, v1, 125);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x13FEA4u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
    a0 = addiu(sp, 0x90);
    a1 = addiu(gp, -30340);  // "%s"
    a2 = v0;
    jal(ctx, 0x13FEB8u, gen::fn_sprintf_00523ac8);
    lwc1(f0, sp, 0x88);
    cvt_w_s(f0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x425C0000;  // 55.0f
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(a0, f0);
    cvt_w_s(f0, f20);
    cvt_s_w(f1, f0);
    v0 = 0x41300000;  // 11.0f
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(a1, f0);
    v0 = si(-256);
    a2 = s4 | v0;
    mov_s(f12, f22);
    a3 = 10;
    t0 = 1;
    t1 = addiu(sp, 0x90);
    t2 = 16;
    t3 = 0;
    jal(ctx, 0x13FF34u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
    lw(v1, s2, 11628);
    a0 = addu(v1, s3);
    v1 = sll(a0, 3);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, s2);
    lbu(a0, v1, 126);
    v1 = 3;
    if (a0 != v1) {
        // 0x0013ff64
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x001404c4
            charge(ctx, 27);
            v0 = 0x43900000;  // 288.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x41100000;  // 9.0f
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s1 & 0xFF;
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 50;
            mov_s(f14, f22);
            jal(ctx, 0x1404FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v0, s2, 11628);
            v1 = addu(v0, s3);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            lhu(s3, v0, 134);
            s2 = 0;
            v0 = slti(s3, 100);
            if (v0 == 0) {
                // 0x00140530
                charge(ctx, 31);
                s2 = 1;
                a0 = 2;
                jal(ctx, 0x140538u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                v1 = 100;
                div(s3, v1);
                mflo(v1);
                a2 = addiu(v1, 11);
                v1 = 325;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0x88);
                add_s(f12, f1, f0);
                v1 = 0x41800000;  // 16.0f
                mtc1(v1, f0);
                add_s(f1, f0, f20);
                v1 = 0x40400000;  // 3.0f
                mtc1(v1, f0);
                sub_s(f13, f1, f0);
                a3 = s1 & 0xFF;
                a0 = s0;
                a1 = v0;
                mov_s(f14, f22);
                jal(ctx, 0x140598u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 100;
                div(s3, v0);
                mfhi(s3);
            }
            // 0x001405ac
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x001405b4
                charge(ctx, 3);
                v0 = slti(s3, 10);
                if (v0 == 0) {
                    goto L_001405c0;
                }
                goto L_0014062c;
            }
        L_001405c0:
            charge(ctx, 27);
            a0 = 2;
            jal(ctx, 0x1405C4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s3, v1);
            mflo(v1);
            a2 = addiu(v1, 11);
            v1 = 341;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v1 = 0x41800000;  // 16.0f
            mtc1(v1, f0);
            add_s(f1, f0, f20);
            v1 = 0x40400000;  // 3.0f
            mtc1(v1, f0);
            sub_s(f13, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s0;
            a1 = v0;
            mov_s(f14, f22);
            jal(ctx, 0x140624u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        L_0014062c:
            charge(ctx, 27);
            a0 = 2;
            jal(ctx, 0x140630u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s3, v1);
            mfhi(v1);
            a2 = addiu(v1, 11);
            v1 = 357;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v1 = 0x41800000;  // 16.0f
            mtc1(v1, f0);
            add_s(f1, f0, f20);
            v1 = 0x40400000;  // 3.0f
            mtc1(v1, f0);
            sub_s(f13, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s0;
            a1 = v0;
            mov_s(f14, f22);
            jal(ctx, 0x140690u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x0013ff70
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x001402e8
                charge(ctx, 27);
                v0 = 0x43900000;  // 288.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x88);
                add_s(f12, f1, f0);
                v0 = 0x41100000;  // 9.0f
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s1 & 0xFF;
                a0 = s0;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                a2 = 48;
                mov_s(f14, f22);
                jal(ctx, 0x140320u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, s2, 11628);
                v1 = addu(v0, s3);
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s2);
                lhu(s3, v0, 132);
                s2 = 0;
                v0 = slti(s3, 100);
                if (v0 == 0) {
                    // 0x00140354
                    charge(ctx, 31);
                    s2 = 1;
                    a0 = 2;
                    jal(ctx, 0x14035Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 100;
                    div(s3, v1);
                    mflo(v1);
                    a2 = addiu(v1, 11);
                    v1 = 325;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    v1 = 0x41800000;  // 16.0f
                    mtc1(v1, f0);
                    add_s(f1, f0, f20);
                    v1 = 0x40400000;  // 3.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    a1 = v0;
                    mov_s(f14, f22);
                    jal(ctx, 0x1403BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 100;
                    div(s3, v0);
                    mfhi(s3);
                }
                // 0x001403d0
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x001403d8
                    charge(ctx, 3);
                    v0 = slti(s3, 10);
                    if (v0 == 0) {
                        goto L_001403e4;
                    }
                    goto L_00140450;
                }
            L_001403e4:
                charge(ctx, 27);
                a0 = 2;
                jal(ctx, 0x1403E8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                v1 = 10;
                div(s3, v1);
                mflo(v1);
                a2 = addiu(v1, 11);
                v1 = 341;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0x88);
                add_s(f12, f1, f0);
                v1 = 0x41800000;  // 16.0f
                mtc1(v1, f0);
                add_s(f1, f0, f20);
                v1 = 0x40400000;  // 3.0f
                mtc1(v1, f0);
                sub_s(f13, f1, f0);
                a3 = s1 & 0xFF;
                a0 = s0;
                a1 = v0;
                mov_s(f14, f22);
                jal(ctx, 0x140448u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            L_00140450:
                charge(ctx, 29);
                a0 = 2;
                jal(ctx, 0x140454u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                v1 = 10;
                div(s3, v1);
                mfhi(v1);
                a2 = addiu(v1, 11);
                v1 = 357;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0x88);
                add_s(f12, f1, f0);
                v1 = 0x41800000;  // 16.0f
                mtc1(v1, f0);
                add_s(f1, f0, f20);
                v1 = 0x40400000;  // 3.0f
                mtc1(v1, f0);
                sub_s(f13, f1, f0);
                a3 = s1 & 0xFF;
                a0 = s0;
                a1 = v0;
                mov_s(f14, f22);
                jal(ctx, 0x1404B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0013ff7c
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0013ff8c
                    charge(ctx, 28);
                    v0 = 0x41100000;  // 9.0f
                    mtc1(v0, f0);
                    add_s(f21, f0, f20);
                    v0 = 0x43900000;  // 288.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                    a2 = 46;
                    mov_s(f13, f21);
                    mov_s(f14, f22);
                    jal(ctx, 0x13FFC8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s3);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s2);
                    lhu(s5, v0, 128);
                    s4 = 0;
                    v0 = slti(s5, 100);
                    if (v0 == 0) {
                        // 0x0013fffc
                        charge(ctx, 31);
                        s4 = 1;
                        a0 = 2;
                        jal(ctx, 0x140004u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        v1 = 100;
                        div(s5, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        v1 = 325;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, sp, 0x88);
                        add_s(f12, f1, f0);
                        v1 = 0x41800000;  // 16.0f
                        mtc1(v1, f0);
                        add_s(f1, f0, f20);
                        v1 = 0x40400000;  // 3.0f
                        mtc1(v1, f0);
                        sub_s(f13, f1, f0);
                        a3 = s1 & 0xFF;
                        a0 = s0;
                        a1 = v0;
                        mov_s(f14, f22);
                        jal(ctx, 0x140064u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = 100;
                        div(s5, v0);
                        mfhi(s5);
                    }
                    // 0x00140078
                    charge(ctx, 2);
                    if (s4 == 0) {
                        // 0x00140080
                        charge(ctx, 3);
                        v0 = slti(s5, 10);
                        if (v0 == 0) {
                            goto L_0014008c;
                        }
                        goto L_001400f8;
                    }
                L_0014008c:
                    charge(ctx, 27);
                    a0 = 2;
                    jal(ctx, 0x140090u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 10;
                    div(s5, v1);
                    mflo(v1);
                    a2 = addiu(v1, 11);
                    v1 = 341;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    v1 = 0x41800000;  // 16.0f
                    mtc1(v1, f0);
                    add_s(f1, f0, f20);
                    v1 = 0x40400000;  // 3.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    a1 = v0;
                    mov_s(f14, f22);
                    jal(ctx, 0x1400F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                L_001400f8:
                    charge(ctx, 53);
                    lwc1(f1, sp, 0x8C);
                    v0 = 0x41800000;  // 16.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = 0x40400000;  // 3.0f
                    mtc1(v0, f0);
                    sub_s(f20, f1, f0);
                    a0 = 2;
                    jal(ctx, 0x140120u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 10;
                    div(s5, v1);
                    mfhi(v1);
                    a2 = addiu(v1, 11);
                    v1 = 357;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    a1 = v0;
                    mov_s(f13, f20);
                    mov_s(f14, f22);
                    jal(ctx, 0x140164u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 0x43CA0000;  // 404.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                    a2 = 52;
                    mov_s(f13, f21);
                    mov_s(f14, f22);
                    jal(ctx, 0x140198u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s2, 11628);
                    v1 = addu(v0, s3);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s2);
                    lhu(s3, v0, 130);
                    s2 = 0;
                    v0 = slti(s3, 100);
                    if (v0 == 0) {
                        // 0x001401cc
                        charge(ctx, 24);
                        s2 = 1;
                        a0 = 2;
                        jal(ctx, 0x1401D4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        v1 = 100;
                        div(s3, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        v1 = 441;
                        mtc1(v1, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, sp, 0x88);
                        add_s(f12, f1, f0);
                        a3 = s1 & 0xFF;
                        a0 = s0;
                        a1 = v0;
                        mov_s(f13, f20);
                        mov_s(f14, f22);
                        jal(ctx, 0x140218u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = 100;
                        div(s3, v0);
                        mfhi(s3);
                    }
                    // 0x0014022c
                    charge(ctx, 2);
                    if (s2 == 0) {
                        // 0x00140234
                        charge(ctx, 3);
                        v0 = slti(s3, 10);
                        if (v0 == 0) {
                            goto L_00140240;
                        }
                        goto L_00140290;
                    }
                L_00140240:
                    charge(ctx, 20);
                    a0 = 2;
                    jal(ctx, 0x140244u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 10;
                    div(s3, v1);
                    mflo(v1);
                    a2 = addiu(v1, 11);
                    v1 = 457;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    a1 = v0;
                    mov_s(f13, f20);
                    mov_s(f14, f22);
                    jal(ctx, 0x140288u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                L_00140290:
                    charge(ctx, 22);
                    a0 = 2;
                    jal(ctx, 0x140294u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 10;
                    div(s3, v1);
                    mfhi(v1);
                    a2 = addiu(v1, 11);
                    v1 = 473;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, sp, 0x88);
                    add_s(f12, f1, f0);
                    a3 = s1 & 0xFF;
                    a0 = s0;
                    a1 = v0;
                    mov_s(f13, f20);
                    mov_s(f14, f22);
                    jal(ctx, 0x1402D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x0013ff84
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00140698 (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
    sp = addiu(sp, 0x190);
}

// 0x001406D0 sub_1406D0 -- 1880 bytes; frame 0x1E0: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ItemDrawItemList] (xy, list, alpha): the item page's list: the scroll marks, the five visible rows (+2420
// scroll) with the item name (sub_17B100 -> sprintf -> sub_3B32D0) and the count as two digits of font 1, the cursor
// row (+2416) with sprite 27 of camp file 0.
void sub_1406D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    // 0x001406d0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xD8);
    mov_s(f27, f12);
    s4 = a1;
    s3 = a2;
    v0 = 255;
    s0 = subu(v0, s3);
    lw(v0, a1, 2412);
    if (v0 != 0) {
        // 0x00140740
        charge(ctx, 51);
        lwc1(f1, sp, 0xDC);
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        lw(v1, s4, 2416);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xD8);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 23;
        mov_s(f14, f27);
        jal(ctx, 0x1407A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, s4, 2416);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 317;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0xD8);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 22;
        mov_s(f14, f27);
        jal(ctx, 0x140804u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0014080c
    charge(ctx, 24);
    lwc1(f2, sp, 0xDC);
    v0 = 331;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xD8);
    add_s(f21, f1, f0);
    v0 = 0x40C00000;  // 6.0f
    mtc1(v0, f0);
    add_s(f13, f0, f2);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 26;
    mov_s(f12, f21);
    mov_s(f14, f27);
    jal(ctx, 0x140854u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s4, 2412);
    a0 = addiu(v0, -5);
    if (i64(a0) <= 0) {
        // 0x00140890
        charge(ctx, 1);
        v1 = 0;
    } else {
        // 0x0014086c
        charge(ctx, 9);
        lw(v1, s4, 2420);
        v0 = 89;
        mult(v0, v1, v0);
        div(v0, a0);
        mflo(v1);
    }
    // 0x00140894
    charge(ctx, 80);
    lwc1(f20, sp, 0xDC);
    v0 = 0x41200000;  // 10.0f
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 32;
    mov_s(f12, f21);
    mov_s(f14, f27);
    jal(ctx, 0x1408D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s1 = 0;
    v1 = 0x40000000;  // 2.0f
    mtc1(v1, f0);
    add_s(f26, f0, f20);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f0);
    lwc1(f2, sp, 0xD8);
    add_s(f25, f0, f2);
    v1 = si(-256);
    s2 = s0 | v1;
    cvt_w_s(f0, f20);
    cvt_s_w(f1, f0);
    v1 = 0x41300000;  // 11.0f
    mtc1(v1, f0);
    add_s(f24, f0, f1);
    cvt_w_s(f0, f2);
    cvt_s_w(f1, f0);
    v1 = 0x425C0000;  // 55.0f
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s7, f0);
    v1 = 0x41800000;  // 16.0f
    mtc1(v1, f0);
    add_s(f23, f0, f20);
    v1 = 277;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f22, f0, f2);
    v1 = 293;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f21, f0, f2);
    v1 = 0x43480000;  // 200.0f
    mtc1(v1, f0);
    add_s(f1, f0, f20);
    v1 = 0x42200000;  // 40.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(fp, f0);
    v1 = 0x41600000;  // 14.0f
    mtc1(v1, f1);
    v1 = 0x41200000;  // 10.0f
    mtc1(v1, f0);
    add_s(f0, f0, f2);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sw(v1, sp, 0xC0);
    for (;;) {
        // 0x00140dc8
        charge(ctx, 3);
        v1 = slti(s1, 5);
        if (v1 != 0) {
            backedge(ctx);
            // 0x001409d4
            charge(ctx, 6);
            lw(a0, s4, 2412);
            lw(v1, s4, 2420);
            v1 = addu(s1, v1);
            at = slt(v1, a0);
            if (at != 0) {
                // 0x001409ec
                charge(ctx, 3);
                lw(v0, s4, 2416);
                if (s1 != v0) {
                    // 0x00140bf8
                    charge(ctx, 66);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    s0 = sll(v0, 1);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f13, f1, f0);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    a2 = 26;
                    mov_s(f12, f25);
                    t0 = 32;
                    t1 = 67;
                    t2 = 120;
                    mov_s(f14, f27);
                    jal(ctx, 0x140C54u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x140C70u, gen::fn_sub_17B100_0017b100);  // an item name
                    a0 = addiu(sp, 0xE0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x140C84u, gen::fn_sprintf_00523ac8);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f24, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f27);
                    a2 = s2;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0xE0);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x140CD8u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lw(s5, v0, 16);
                    v0 = slti(s5, 10);
                    if (v0 == 0) {
                        // 0x00140d00
                        charge(ctx, 22);
                        a0 = 2;
                        jal(ctx, 0x140D04u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f23, f0);
                        v1 = 0x40400000;  // 3.0f
                        mtc1(v1, f0);
                        sub_s(f13, f1, f0);
                        v1 = 10;
                        div(s5, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        a3 = s3 & 0xFF;
                        a0 = s6;
                        a1 = v0;
                        mov_s(f12, f22);
                        mov_s(f14, f27);
                        jal(ctx, 0x140D50u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x00140d58
                    charge(ctx, 27);
                    a0 = 2;
                    jal(ctx, 0x140D5Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f23, f0);
                    v1 = 0x40400000;  // 3.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    lw(v1, s4, 2420);
                    v1 = addu(v1, s1);
                    v1 = sll(v1, 3);
                    v1 = addu(s4, v1);
                    lw(a0, v1, 16);
                    v1 = 10;
                    div(a0, v1);
                    mfhi(v1);
                    a2 = addiu(v1, 11);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    a1 = v0;
                    mov_s(f12, f21);
                    mov_s(f14, f27);
                    jal(ctx, 0x140DBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x001409f8
                    charge(ctx, 63);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    s0 = sll(v0, 1);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f13, f1, f0);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    a2 = 27;
                    mov_s(f12, f25);
                    mov_s(f14, f27);
                    jal(ctx, 0x140A48u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x140A64u, gen::fn_sub_17B100_0017b100);  // an item name
                    a0 = addiu(sp, 0xE0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x140A78u, gen::fn_sprintf_00523ac8);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f24, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f27);
                    a2 = s2;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0xE0);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x140ACCu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lw(s5, v0, 16);
                    v0 = slti(s5, 10);
                    if (v0 == 0) {
                        // 0x00140af4
                        charge(ctx, 22);
                        a0 = 1;
                        jal(ctx, 0x140AF8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f23, f0);
                        v1 = 0x40400000;  // 3.0f
                        mtc1(v1, f0);
                        sub_s(f13, f1, f0);
                        v1 = 10;
                        div(s5, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        a3 = s3 & 0xFF;
                        a0 = s6;
                        a1 = v0;
                        mov_s(f12, f22);
                        mov_s(f14, f27);
                        jal(ctx, 0x140B44u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x00140b4c
                    charge(ctx, 43);
                    a0 = 1;
                    jal(ctx, 0x140B50u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f23, f0);
                    v1 = 0x40400000;  // 3.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    lw(v1, s4, 2420);
                    v1 = addu(v1, s1);
                    v1 = sll(v1, 3);
                    v1 = addu(s4, v1);
                    lw(a0, v1, 16);
                    v1 = 10;
                    div(a0, v1);
                    mfhi(v1);
                    a2 = addiu(v1, 11);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    a1 = v0;
                    mov_s(f12, f21);
                    mov_s(f14, f27);
                    jal(ctx, 0x140BB0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lw(a0, sp, 0xC0);
                    a1 = fp;
                    mov_s(f12, f27);
                    a2 = s2;
                    a3 = 1;
                    t0 = 10;
                    t1 = 0;
                    lw(t2, v0, 12);
                    jal(ctx, 0x140BE8u, gen::fn_sub_3C7E20_003c7e20);  // a message text
                }
                // 0x00140dc4
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x00140dd4 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    ld(ra, sp, 0xB0);
    lq(fp, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x00140E30 sub_140E30 -- 1880 bytes; frame 0x1E0: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ItemDrawMaterialList] (xy, list, alpha): sub_1406D0 for the material page (cursor sprite 29).
void sub_140E30(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27};
    // 0x00140e30
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0xB0);
    sq(fp, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f27, sp, 0x1C);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xD8);
    mov_s(f27, f12);
    s4 = a1;
    s3 = a2;
    v0 = 255;
    s0 = subu(v0, s3);
    lw(v0, a1, 2412);
    if (v0 != 0) {
        // 0x00140ea0
        charge(ctx, 51);
        lwc1(f1, sp, 0xDC);
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        lw(v1, s4, 2416);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xD8);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 23;
        mov_s(f14, f27);
        jal(ctx, 0x140F04u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, s4, 2416);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f20, f0);
        v0 = 317;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0xD8);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 22;
        mov_s(f14, f27);
        jal(ctx, 0x140F64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00140f6c
    charge(ctx, 24);
    lwc1(f2, sp, 0xDC);
    v0 = 331;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xD8);
    add_s(f21, f1, f0);
    v0 = 0x40C00000;  // 6.0f
    mtc1(v0, f0);
    add_s(f13, f0, f2);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 26;
    mov_s(f12, f21);
    mov_s(f14, f27);
    jal(ctx, 0x140FB4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s4, 2412);
    a0 = addiu(v0, -5);
    if (i64(a0) <= 0) {
        // 0x00140ff0
        charge(ctx, 1);
        v1 = 0;
    } else {
        // 0x00140fcc
        charge(ctx, 9);
        lw(v1, s4, 2420);
        v0 = 89;
        mult(v0, v1, v0);
        div(v0, a0);
        mflo(v1);
    }
    // 0x00140ff4
    charge(ctx, 80);
    lwc1(f20, sp, 0xDC);
    v0 = 0x41200000;  // 10.0f
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
    a2 = 32;
    mov_s(f12, f21);
    mov_s(f14, f27);
    jal(ctx, 0x141034u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s1 = 0;
    v1 = 0x40000000;  // 2.0f
    mtc1(v1, f0);
    add_s(f26, f0, f20);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f0);
    lwc1(f2, sp, 0xD8);
    add_s(f25, f0, f2);
    v1 = si(-256);
    s2 = s0 | v1;
    cvt_w_s(f0, f20);
    cvt_s_w(f1, f0);
    v1 = 0x41300000;  // 11.0f
    mtc1(v1, f0);
    add_s(f24, f0, f1);
    cvt_w_s(f0, f2);
    cvt_s_w(f1, f0);
    v1 = 0x425C0000;  // 55.0f
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s7, f0);
    v1 = 0x41800000;  // 16.0f
    mtc1(v1, f0);
    add_s(f23, f0, f20);
    v1 = 277;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f22, f0, f2);
    v1 = 293;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f21, f0, f2);
    v1 = 0x43480000;  // 200.0f
    mtc1(v1, f0);
    add_s(f1, f0, f20);
    v1 = 0x42200000;  // 40.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(fp, f0);
    v1 = 0x41600000;  // 14.0f
    mtc1(v1, f1);
    v1 = 0x41200000;  // 10.0f
    mtc1(v1, f0);
    add_s(f0, f0, f2);
    add_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sw(v1, sp, 0xC0);
    for (;;) {
        // 0x00141528
        charge(ctx, 3);
        v1 = slti(s1, 5);
        if (v1 != 0) {
            backedge(ctx);
            // 0x00141134
            charge(ctx, 6);
            lw(a0, s4, 2412);
            lw(v1, s4, 2420);
            v1 = addu(s1, v1);
            at = slt(v1, a0);
            if (at != 0) {
                // 0x0014114c
                charge(ctx, 3);
                lw(v0, s4, 2416);
                if (s1 != v0) {
                    // 0x00141358
                    charge(ctx, 66);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    s0 = sll(v0, 1);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f13, f1, f0);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    a2 = 28;
                    mov_s(f12, f25);
                    t0 = 32;
                    t1 = 67;
                    t2 = 120;
                    mov_s(f14, f27);
                    jal(ctx, 0x1413B4u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x1413D0u, gen::fn_sub_17B100_0017b100);  // an item name
                    a0 = addiu(sp, 0xE0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x1413E4u, gen::fn_sprintf_00523ac8);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f24, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f27);
                    a2 = s2;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0xE0);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x141438u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lw(s5, v0, 16);
                    v0 = slti(s5, 10);
                    if (v0 == 0) {
                        // 0x00141460
                        charge(ctx, 22);
                        a0 = 2;
                        jal(ctx, 0x141464u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f23, f0);
                        v1 = 0x40400000;  // 3.0f
                        mtc1(v1, f0);
                        sub_s(f13, f1, f0);
                        v1 = 10;
                        div(s5, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        a3 = s3 & 0xFF;
                        a0 = s6;
                        a1 = v0;
                        mov_s(f12, f22);
                        mov_s(f14, f27);
                        jal(ctx, 0x1414B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x001414b8
                    charge(ctx, 27);
                    a0 = 2;
                    jal(ctx, 0x1414BCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f23, f0);
                    v1 = 0x40400000;  // 3.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    lw(v1, s4, 2420);
                    v1 = addu(v1, s1);
                    v1 = sll(v1, 3);
                    v1 = addu(s4, v1);
                    lw(a0, v1, 16);
                    v1 = 10;
                    div(a0, v1);
                    mfhi(v1);
                    a2 = addiu(v1, 11);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    a1 = v0;
                    mov_s(f12, f21);
                    mov_s(f14, f27);
                    jal(ctx, 0x14151Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x00141158
                    charge(ctx, 63);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    s0 = sll(v0, 1);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f26, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    sub_s(f13, f1, f0);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    a2 = 29;
                    mov_s(f12, f25);
                    mov_s(f14, f27);
                    jal(ctx, 0x1411A8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x1411C4u, gen::fn_sub_17B100_0017b100);  // an item name
                    a0 = addiu(sp, 0xE0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x1411D8u, gen::fn_sprintf_00523ac8);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f24, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f27);
                    a2 = s2;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0xE0);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x14122Cu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lw(s5, v0, 16);
                    v0 = slti(s5, 10);
                    if (v0 == 0) {
                        // 0x00141254
                        charge(ctx, 22);
                        a0 = 1;
                        jal(ctx, 0x141258u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f23, f0);
                        v1 = 0x40400000;  // 3.0f
                        mtc1(v1, f0);
                        sub_s(f13, f1, f0);
                        v1 = 10;
                        div(s5, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        a3 = s3 & 0xFF;
                        a0 = s6;
                        a1 = v0;
                        mov_s(f12, f22);
                        mov_s(f14, f27);
                        jal(ctx, 0x1412A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x001412ac
                    charge(ctx, 43);
                    a0 = 1;
                    jal(ctx, 0x1412B0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f23, f0);
                    v1 = 0x40400000;  // 3.0f
                    mtc1(v1, f0);
                    sub_s(f13, f1, f0);
                    lw(v1, s4, 2420);
                    v1 = addu(v1, s1);
                    v1 = sll(v1, 3);
                    v1 = addu(s4, v1);
                    lw(a0, v1, 16);
                    v1 = 10;
                    div(a0, v1);
                    mfhi(v1);
                    a2 = addiu(v1, 11);
                    a3 = s3 & 0xFF;
                    a0 = s6;
                    a1 = v0;
                    mov_s(f12, f21);
                    mov_s(f14, f27);
                    jal(ctx, 0x141310u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s4, 2420);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    lw(a0, sp, 0xC0);
                    a1 = fp;
                    mov_s(f12, f27);
                    a2 = s2;
                    a3 = 1;
                    t0 = 10;
                    t1 = 0;
                    lw(t2, v0, 12);
                    jal(ctx, 0x141348u, gen::fn_sub_3C7E20_003c7e20);  // a message text
                }
                // 0x00141524
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
        }
        break;
    }
    // 0x00141534 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    ld(ra, sp, 0xB0);
    lq(fp, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f27, sp, 0x1C);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1E0);
}

// 0x00141660 sub_141660 -- 2376 bytes; frame 0xF0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemOpenLayout] (item work): starts the item page's slide-in on the 80 tween records (+188): every panel from
// 50 px right of its place over frames 6..13.
void sub_141660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00141660
    enter(ctx, 279);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0xE0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0xE8);
    lwc1(f1, sp, 0xE8);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xE8);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xE8);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1416E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xE0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x68);
    lwc1(f1, sp, 0x68);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x141758u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0xE0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x70);
    lwc1(f1, sp, 0x70);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1417CCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xE0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x78);
    lwc1(f1, sp, 0x78);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x78);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14184Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0xE0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x80);
    lwc1(f1, sp, 0x80);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x80);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1418C0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xE0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x88);
    lwc1(f1, sp, 0x88);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x88);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x141940u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0xE0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x90);
    lwc1(f1, sp, 0x90);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x90);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x90);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1419B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0xE0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0x98);
    lwc1(f1, sp, 0x98);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x98);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x98);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x141A28u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xE0);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0xA0);
    lwc1(f1, sp, 0xA0);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x141AA8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x00141e74
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00141abc
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x00141e08
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00141acc
            charge(ctx, 207);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xE0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xA8);
            lwc1(f1, sp, 0xA8);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xA8);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA8);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x141B8Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xE0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xB0);
            lwc1(f1, sp, 0xB0);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xB0);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x141C1Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xB8);
            lwc1(f1, sp, 0xB8);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xB8);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xB8);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x141CACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xC0);
            lwc1(f1, sp, 0xC0);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xC0);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC0);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x141D3Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xE0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xC8);
            lwc1(f1, sp, 0xC8);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xC8);
            v0 = 3;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC8);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x141DCCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        }
        // 0x00141e70
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00141e80
    charge(ctx, 74);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0xE0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0xD0);
    lwc1(f1, sp, 0xD0);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xD0);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD0);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x141EF8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, item::kTweens);
    sw(zero, v0, 4832);
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0xE0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xE4);
    ld(v0, sp, 0xE0);
    sd(v0, sp, 0xD8);
    lwc1(f1, sp, 0xD8);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xD8);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD8);
    ld(t1, sp, 0xE0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x141F80u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xF0);
}

// 0x00141FB0 sub_141FB0 -- 2432 bytes; frame 0xC0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f21 sp+0x14, f20 sp+0x10
// [H_Camp_ItemTargetOpenLayout] (item work): moves the item page's panels for the target choice (the list to x 110, the
// target panels in).
void sub_141FB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00141fb0
    enter(ctx, 243);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0xB8);
    v0 = 0x42DC0000;  // 110.0f
    sw(v0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142020u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142070u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x60);
    v0 = 531;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1420D8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142128u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142184u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1421D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142230u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0xB0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x68);
    v0 = 297;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142298u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0xB0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x70);
    v0 = 297;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142300u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x78);
    v0 = 0x44310000;  // 708.0f
    sw(v0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142368u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0014278c
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014237c
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x00142720
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x0014238c
            charge(ctx, 14);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            a0 = addu(v1, v0);
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f21, f0, f1);
            lw(v1, s2, item::kTargetCursor);
            if (s1 != v1) {
                // 0x001423c4
                charge(ctx, 3);
                v0 = si(-2);
                if (v1 == v0) {
                    goto L_001423d0;
                }
                // 0x00142468
                charge(ctx, 6);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f20);
                v1 = sll(a0, 3);
                lw(v0, s2, item::kTweens);
                v0 = addu(v0, v1);
                sw(zero, v0, 2452);
                goto L_00142480;
            }
        L_001423d0:
            charge(ctx, 38);
            v0 = 0x42400000;  // 48.0f
            mtc1(v0, f20);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x80);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            v0 = sll(v0, 1);
            v1 = addiu(v0, 36);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142458u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        L_00142480:
            charge(ctx, 168);
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x88);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xB0);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142500u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x90);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14257Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x98);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1425F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0xA0);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142674u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0xA8);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1426F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
        }
        // 0x00142788
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00142798
    charge(ctx, 102);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1427ECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42BE0000;  // 95.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4828);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142848u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1428A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 453;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 5032);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142904u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f21, sp, 0x14);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x00142930 sub_142930 -- 2488 bytes; frame 0xC0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f21 sp+0x14, f20 sp+0x10
// [H_Camp_ItemTargetCloseLayout] (item work): moves the panels back from the target choice to the item list.
void sub_142930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00142930
    enter(ctx, 251);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0xB8);
    v0 = 0x42DC0000;  // 110.0f
    sw(v0, sp, 0xB8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0xB8);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1429A4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0x60);
    v0 = 531;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x60);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x60);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142A10u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 531;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142A6Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142ABCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142B18u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142B68u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142BC4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0xB0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0x68);
    v0 = 297;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142C30u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0xB0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0x70);
    v0 = 297;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x70);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142C9Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0x78);
    v0 = 0x44310000;  // 708.0f
    sw(v0, sp, 0x78);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x142D08u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x00143144
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00142d1c
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x001430d8
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00142d2c
            charge(ctx, 14);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            a0 = addu(v1, v0);
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f21, f0, f1);
            lw(v1, s2, item::kTargetCursor);
            if (s1 != v1) {
                // 0x00142d64
                charge(ctx, 3);
                v0 = si(-2);
                if (v1 == v0) {
                    goto L_00142d70;
                }
                // 0x00142e0c
                charge(ctx, 6);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f20);
                v1 = sll(a0, 3);
                lw(v0, s2, item::kTweens);
                v0 = addu(v0, v1);
                sw(zero, v0, 2452);
                goto L_00142e24;
            }
        L_00142d70:
            charge(ctx, 39);
            v0 = 0x42400000;  // 48.0f
            mtc1(v0, f20);
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x80);
            lwc1(f0, sp, 0x80);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x80);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            v0 = sll(v0, 1);
            v1 = addiu(v0, 36);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x80);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142DFCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        L_00142e24:
            charge(ctx, 173);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x88);
            lwc1(f0, sp, 0x88);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x88);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x88);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142EA8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x90);
            lwc1(f0, sp, 0x90);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x90);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x90);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142F28u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x98);
            lwc1(f0, sp, 0x98);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x98);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x98);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x142FA8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0xA0);
            lwc1(f0, sp, 0xA0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0xA0);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x143028u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0xA8);
            lwc1(f0, sp, 0xA8);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xA8);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0xA8);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1430A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
        }
        // 0x00143140
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00143150
    charge(ctx, 102);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1431A4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42BE0000;  // 95.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4828);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143200u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143258u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 453;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 5032);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1432BCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f21, sp, 0x14);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x001432F0 sub_1432F0 -- 1800 bytes; frame 0x70: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemCloseLayout] (item work): the item page's slide-out (every panel in place, mode 2 / curve 2 over 5
// frames).
void sub_1432F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001432f0
    enter(ctx, 198);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0x68);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143350u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x68);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1433A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0x68);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1433F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14344Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0x68);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14349Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1434F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0x68);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143548u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0x68);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143598u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1435F4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0014390c
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00143608
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x001438a0
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00143618
            charge(ctx, 162);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x68);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x6C);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1436B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x68);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x6C);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x143720u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x68);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x6C);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14378Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x68);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x6C);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1437F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0x68);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x6C);
            sd(zero, sp, 0x0);
            v0 = 5;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x143864u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        }
        // 0x00143908
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00143918
    charge(ctx, 56);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0x68);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14396Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, item::kTweens);
    sw(zero, v0, 4832);
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0x68);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x6C);
    sd(zero, sp, 0x0);
    v0 = 5;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x68);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1439D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x00143A00 sub_143A00 -- 1236 bytes; frame 0xC0: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f22 sp+0x18, f21 sp+0x14, f20 sp+0x10
// [H_Camp_ItemMoveTargetCursor] (item work, previous): moves the target highlight: the target rows (85 px apart from y
// 62) of the new cursor (+84) and of `previous` restart their tweens.
void sub_143A00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00143a00
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f22, sp, 0x18);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    s4 = a0;
    s3 = a1;
    s2 = 0;
    for (;;) {
        // 0x00143e98
        charge(ctx, 3);
        v1 = slti(s2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00143a3c
        charge(ctx, 4);
        lw(v1, s4, item::kTargetCount);
        at = slt(s2, v1);
        if (at != 0) {
            // 0x00143a4c
            charge(ctx, 14);
            v1 = sll(s2, 4);
            a0 = addu(v1, s2);
            v1 = sll(a0, 2);
            a1 = addu(a0, v1);
            mtc1(a1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x42780000;  // 62.0f
            mtc1(v1, f0);
            add_s(f22, f0, f1);
            lw(v1, s4, item::kTargetCursor);
            if (s2 == v1) {
                // 0x00143a84
                charge(ctx, 44);
                v0 = 0x42400000;  // 48.0f
                mtc1(v0, f21);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f2);
                sw(v0, sp, 0xB0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                add_s(f20, f0, f22);
                swc1(f20, sp, 0xB4);
                ld(v0, sp, 0xB0);
                sd(v0, sp, 0xB8);
                lwc1(f1, sp, 0xB8);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0xB8);
                add_s(f0, f2, f21);
                swc1(f0, sp, 0xB0);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = sll(v0, 1);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(v0, 36);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s4, item::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 1;
                ld(t0, sp, 0xB8);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143B24u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                goto L_00143bdc;
            }
            // 0x00143b34
            charge(ctx, 2);
            if (s2 == s3) {
                // 0x00143b3c
                charge(ctx, 40);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f21);
                lw(a0, s4, item::kTweens);
                v0 = sll(a1, 3);
                v0 = addu(a0, v0);
                lwc1(f1, v0, 2504);
                lwc1(f0, v0, 2508);
                swc1(f1, sp, 0x80);
                swc1(f0, sp, 0x84);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f1);
                sw(v0, sp, 0xB0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                add_s(f20, f0, f22);
                swc1(f20, sp, 0xB4);
                add_s(f0, f1, f21);
                swc1(f0, sp, 0xB0);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = sll(v0, 1);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(v0, 36);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = a2;
                ld(t0, sp, 0x80);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143BD4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            L_00143bdc:
                charge(ctx, 174);
                lw(a0, s4, item::kTweens);
                v0 = sll(s2, 4);
                v1 = addu(v0, s2);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                s1 = sll(v0, 3);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 2096);
                lwc1(f0, v0, 2100);
                swc1(f1, sp, 0x88);
                swc1(f0, sp, 0x8C);
                v0 = 0x42820000;  // 65.0f
                mtc1(v0, f1);
                sw(v0, sp, 0xB0);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f0, f0, f22);
                swc1(f0, sp, 0xB4);
                add_s(f0, f1, f21);
                swc1(f0, sp, 0xB0);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                s0 = sll(v0, 1);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 30);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0x88);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143C7Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, item::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 2164);
                lwc1(f0, v0, 2168);
                swc1(f1, sp, 0x90);
                swc1(f0, sp, 0x94);
                v0 = 0x42820000;  // 65.0f
                mtc1(v0, f1);
                sw(v0, sp, 0xB0);
                v0 = 0x41F80000;  // 31.0f
                mtc1(v0, f0);
                add_s(f0, f0, f22);
                swc1(f0, sp, 0xB4);
                add_s(f0, f1, f21);
                swc1(f0, sp, 0xB0);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 31);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0x90);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143D04u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, item::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 2232);
                lwc1(f0, v0, 2236);
                swc1(f1, sp, 0x98);
                swc1(f0, sp, 0x9C);
                v0 = 0x42820000;  // 65.0f
                mtc1(v0, f1);
                sw(v0, sp, 0xB0);
                v0 = 0x42340000;  // 45.0f
                mtc1(v0, f0);
                add_s(f0, f0, f22);
                swc1(f0, sp, 0xB4);
                add_s(f0, f1, f21);
                swc1(f0, sp, 0xB0);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 32);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0x98);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143D8Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, item::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 2300);
                lwc1(f0, v0, 2304);
                swc1(f1, sp, 0xA0);
                swc1(f0, sp, 0xA4);
                v0 = 0x42820000;  // 65.0f
                mtc1(v0, f1);
                sw(v0, sp, 0xB0);
                v0 = 0x42800000;  // 64.0f
                mtc1(v0, f0);
                add_s(f0, f0, f22);
                swc1(f0, sp, 0xB4);
                add_s(f0, f1, f21);
                swc1(f0, sp, 0xB0);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 33);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0xA0);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143E14u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, item::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 2368);
                lwc1(f0, v0, 2372);
                swc1(f1, sp, 0xA8);
                swc1(f0, sp, 0xAC);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                sw(v0, sp, 0xB0);
                swc1(f20, sp, 0xB4);
                add_s(f0, f0, f21);
                swc1(f0, sp, 0xB0);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 34);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0xA8);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x143E8Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            }
        }
        // 0x00143e94
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00143ea4
    charge(ctx, 12);
    ld(ra, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f22, sp, 0x18);
    lwc1(f21, sp, 0x14);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x00143EE0 sub_143EE0 -- 2600 bytes; frame 0xC0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemPersonaOpenLayout] (item work): the panels for the persona choice (an item used on a persona: incense).
void sub_143EE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00143ee0
    enter(ctx, 242);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0xB8);
    v0 = 0x42DC0000;  // 110.0f
    sw(v0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143F4Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x143F9Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x60);
    v0 = 531;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144004u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144054u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1440B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144100u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14415Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0xB0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x68);
    v0 = 297;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1441C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0xB0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x70);
    v0 = 297;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14422Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0xB4);
    ld(t0, sp, 0xB0);
    sd(t0, sp, 0x78);
    v0 = 0x44310000;  // 708.0f
    sw(v0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144294u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0014462c
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001442a8
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x001445c0
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x001442b8
            charge(ctx, 194);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x80);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144370u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x88);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1443F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x90);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144480u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0x98);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144508u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0xA0);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144590u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
        }
        // 0x00144628
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00144638
    charge(ctx, 96);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14468Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41D00000;  // 26.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4896);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1446E8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144740u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 453;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 5032);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1447A4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x001448dc
        charge(ctx, 3);
        v1 = slti(s0, 12);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001447b8
        charge(ctx, 4);
        lw(v1, s2, item::kPersonaCount);
        at = slt(s0, v1);
        if (at == 0) {
            // 0x001448c0
            charge(ctx, 6);
            v1 = sll(s0, 4);
            v1 = addu(v1, s0);
            a0 = sll(v1, 2);
            lw(v1, s2, item::kTweens);
            v1 = addu(v1, a0);
            sw(zero, v1, 684);
        } else {
            // 0x001447c8
            charge(ctx, 3);
            lw(v0, s2, item::kPersonaCursor);
            if (s0 != v0) {
                // 0x00144814
                charge(ctx, 13);
                sw(zero, sp, 0xB0);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42740000;  // 61.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xB4);
            } else {
                // 0x001447d4
                charge(ctx, 16);
                v0 = 0x41A80000;  // 21.0f
                sw(v0, sp, 0xB0);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42740000;  // 61.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xB4);
            }
            // 0x00144848
            charge(ctx, 30);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0xA8);
            lwc1(f1, sp, 0xA8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xA8);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42CE0000;  // 103.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA8);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1448B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x001448d8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001448e8
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x00144910 sub_144910 -- 2624 bytes; frame 0xC0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemPersonaCloseLayout] (item work): back from the persona choice.
void sub_144910(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00144910
    enter(ctx, 244);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0xB8);
    v0 = 0x42DC0000;  // 110.0f
    sw(v0, sp, 0xB8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0xB8);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144980u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0x60);
    v0 = 531;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x60);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x60);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1449ECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 531;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144A48u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144A98u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144AF4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144B44u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144BA0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v1, s2, item::kTweens);
    lwc1(f1, v1, 532);
    lwc1(f0, v1, 536);
    swc1(f1, sp, 0x68);
    swc1(f0, sp, 0x6C);
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0xB0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144C00u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v1, s2, item::kTweens);
    lwc1(f1, v1, 600);
    lwc1(f0, v1, 604);
    swc1(f1, sp, 0x70);
    swc1(f0, sp, 0x74);
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0xB0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144C60u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v1, s2, item::kTweens);
    lwc1(f1, v1, 2096);
    lwc1(f0, v1, 2100);
    swc1(f1, sp, 0x78);
    swc1(f0, sp, 0x7C);
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x144CCCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x00145078
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00144ce0
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x0014500c
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00144cf0
            charge(ctx, 199);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x80);
            lwc1(f1, sp, 0x80);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x80);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x80);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144DACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x88);
            lwc1(f1, sp, 0x88);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x88);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x88);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144E38u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x90);
            lwc1(f1, sp, 0x90);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x90);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x90);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144EC4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x98);
            lwc1(f1, sp, 0x98);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x98);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x98);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144F50u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0xA0);
            lwc1(f1, sp, 0xA0);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA0);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x144FDCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
        }
        // 0x00145074
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00145084
    charge(ctx, 96);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1450D8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41D00000;  // 26.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4896);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x145134u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14518Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 453;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 5032);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1451F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x00145324
        charge(ctx, 3);
        v1 = slti(s0, 12);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00145204
        charge(ctx, 4);
        lw(v1, s2, item::kPersonaCount);
        at = slt(s0, v1);
        if (at == 0) {
            // 0x00145308
            charge(ctx, 6);
            v1 = sll(s0, 4);
            v1 = addu(v1, s0);
            a0 = sll(v1, 2);
            lw(v1, s2, item::kTweens);
            v1 = addu(v1, a0);
            sw(zero, v1, 684);
        } else {
            // 0x00145214
            charge(ctx, 3);
            lw(v0, s2, item::kPersonaCursor);
            if (s0 != v0) {
                // 0x00145260
                charge(ctx, 13);
                sw(zero, sp, 0xB0);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42740000;  // 61.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xB4);
            } else {
                // 0x00145220
                charge(ctx, 16);
                v0 = 0x41A80000;  // 21.0f
                sw(v0, sp, 0xB0);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42740000;  // 61.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xB4);
            }
            // 0x00145294
            charge(ctx, 29);
            ld(t0, sp, 0xB0);
            sd(t0, sp, 0xA8);
            lwc1(f1, sp, 0xB0);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42CE0000;  // 103.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1452F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x00145320
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00145330
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x00145520 sub_145520 -- 4584 bytes; frame 0x190: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_ItemDrawElement] (tween, element, item work): one tween element of the item page (jump table 0x7B5F10): the
// page frames and tabs (camp file 0 sprites 43, 39, 33 ...), the item list (sub_1406D0), the selected item's
// description, the target panels (name, HP / SP digits and gauges, condition: sub_177790, datGetPcHp / MaxHp / Sp /
// MaxSp, sub_16C970 / datGetPcCondition), the persona panels (stats raised by the item: sub_17BF70 / sub_17BFA0 /
// sub_173580), the ribbon.
void sub_145520(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00145520
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    at = sltiu(s3, 75);
    if (at != 0) {
        // 0x0014555c
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 24336);  // &0x7B5F10
        v1 = sll(s3, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x145578u:  // table[0]: element 0: frame (sprite 43)
            // 0x00145578
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 43;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145598u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1455A8u:  // table[1]: element 1: frame (sprite 39)
            // 0x001455a8
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 39;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1455C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1455D8u:  // table[2]: element 2: frame (sprite 33)
            // 0x001455d8
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 33;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1455F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145608u:  // table[3]
            // 0x00145608
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 36;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145628u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145638u:  // table[4]
            // 0x00145638
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 34;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145658u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145668u:  // table[5]
            // 0x00145668
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 36;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145688u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145698u:  // table[6]
            // 0x00145698
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
            a2 = 35;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1456B8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1456C8u:  // table[7]
            // 0x001456c8
            charge(ctx, 12);
            lwc1(f0, s4, tw::kX);
            swc1(f0, sp, 0x188);
            lwc1(f0, s4, tw::kY);
            swc1(f0, sp, 0x18C);
            ld(a0, sp, 0x188);
            lwc1(f12, s4, tw::kZ);
            lw(a1, s2, 164);
            lw(a2, s4, tw::kAlpha);
            jal(ctx, 0x1456E8u, gen::fn_sub_1406D0_001406d0);
            break;
        case 0x1456F8u:  // table[30, 40, 50, 60]
            // 0x001456f8
            charge(ctx, 37);
            lw(v1, s4, tw::kAlpha);
            v0 = 255;
            s0 = subu(v0, v1);
            v1 = addiu(s3, -30);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            lh(a0, v0, 12);
            jal(ctx, 0x145720u, gen::fn_sub_177790_00177790);  // a member's name
            a0 = addiu(sp, 0x80);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x145734u, gen::fn_sprintf_00523ac8);
            lwc1(f0, s4, tw::kX);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            lwc1(f0, s4, tw::kY);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            a1 = addiu(v0, 3);
            v0 = si(-256);
            a2 = s0 | v0;
            lwc1(f12, s4, tw::kZ);
            a3 = 10;
            t0 = 1;
            t1 = addiu(sp, 0x80);
            t2 = 16;
            t3 = 120;
            jal(ctx, 0x14577Cu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            break;
        case 0x14578Cu:  // table[31, 41, 51, 61]
            // 0x0014578c
            charge(ctx, 15);
            v1 = addiu(s3, -31);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            s0 = addiu(v0, 12);
            lh(a0, v0, 12);
            jal(ctx, 0x1457ACu, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
            s2 = v0 & 0xFFFF;
            s1 = 0;
            v0 = slti(s2, 100);
            if (v0 == 0) {
                // 0x001457c8
                charge(ctx, 20);
                s1 = 1;
                a0 = 2;
                jal(ctx, 0x1457D0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                v1 = 100;
                div(s2, v1);
                mflo(v1);
                a2 = addiu(v1, 11);
                lbu(t0, s4, tw::kAlpha);
                a0 = s5;
                a1 = v0;
                lwc1(f12, s4, tw::kX);
                lwc1(f13, s4, tw::kY);
                a3 = 39;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x145804u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                v0 = 100;
                div(s2, v0);
                mfhi(s2);
            }
            // 0x00145818
            charge(ctx, 3);
            at = slti(s2, 10);
            if (at != 0) {
                // 0x00145824
                charge(ctx, 2);
                if (s1 != 0) {
                    goto L_0014582c;
                }
                goto L_00145888;
            }
        L_0014582c:
            charge(ctx, 23);
            a0 = 2;
            jal(ctx, 0x145830u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s2, v1);
            mflo(v1);
            a2 = addiu(v1, 11);
            lwc1(f1, s4, tw::kX);
            v1 = 0x41800000;  // 16.0f
            mtc1(v1, f0);
            add_s(f12, f0, f1);
            lbu(t0, s4, tw::kAlpha);
            a0 = s5;
            a1 = v0;
            lwc1(f13, s4, tw::kY);
            a3 = 39;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145874u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            v0 = 10;
            div(s2, v0);
            mfhi(s2);
        L_00145888:
            charge(ctx, 82);
            a0 = 2;
            jal(ctx, 0x14588Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s2, v1);
            mfhi(v1);
            a2 = addiu(v1, 11);
            lwc1(f1, s4, tw::kX);
            v1 = 0x42000000;  // 32.0f
            mtc1(v1, f0);
            add_s(f12, f0, f1);
            lbu(t0, s4, tw::kAlpha);
            a0 = s5;
            a1 = v0;
            lwc1(f13, s4, tw::kY);
            a3 = 39;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1458D0u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            lw(s0, s0, 0);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1458E4u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            s1 = sll(v0, 2);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x14590Cu, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
            v0 = v0 & 0xFFFF;
            div(s1, v0);
            mflo(v1);
            v0 = 76;
            s0 = subu(v0, v1);
            lwc1(f1, s4, tw::kX);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s4, tw::kY);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 13;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145968u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s4, tw::kX);
            v0 = 0x425C0000;  // 55.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s4, tw::kY);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 11;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1459C0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            if (s0 != 0) {
                // 0x001459d0
                charge(ctx, 27);
                lwc1(f1, s4, tw::kX);
                v0 = 0x42600000;  // 56.0f
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                v0 = 76;
                v0 = subu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f1, f0);
                lwc1(f0, s4, tw::kZ);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f2);
                sub_s(f12, f0, f2);
                lwc1(f1, s4, tw::kY);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                sub_s(f14, f0, f2);
                a0 = si(-256);
                a1 = s0;
                a2 = 10;
                jal(ctx, 0x145A34u, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
            }
            // 0x00145a3c
            charge(ctx, 24);
            lwc1(f1, s4, tw::kX);
            v0 = 0x425C0000;  // 55.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s4, tw::kY);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 9;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145A8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145A9Cu:  // table[32, 42, 52, 62]
            // 0x00145a9c
            charge(ctx, 15);
            v1 = addiu(s3, -32);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            s0 = addiu(v0, 12);
            lh(a0, v0, 12);
            jal(ctx, 0x145ABCu, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
            s1 = v0 & 0xFFFF;
            s2 = 0;
            v0 = slti(s1, 100);
            if (v0 == 0) {
                // 0x00145ad8
                charge(ctx, 20);
                s2 = 1;
                a0 = 2;
                jal(ctx, 0x145AE0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                v1 = 100;
                div(s1, v1);
                mflo(v1);
                a2 = addiu(v1, 11);
                lbu(t0, s4, tw::kAlpha);
                a0 = s5;
                a1 = v0;
                lwc1(f12, s4, tw::kX);
                lwc1(f13, s4, tw::kY);
                a3 = 39;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x145B14u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                v0 = 100;
                div(s1, v0);
                mfhi(s1);
            }
            // 0x00145b28
            charge(ctx, 3);
            at = slti(s1, 10);
            if (at != 0) {
                // 0x00145b34
                charge(ctx, 2);
                if (s2 != 0) {
                    goto L_00145b3c;
                }
                goto L_00145b98;
            }
        L_00145b3c:
            charge(ctx, 23);
            a0 = 2;
            jal(ctx, 0x145B40u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s1, v1);
            mflo(v1);
            a2 = addiu(v1, 11);
            lwc1(f1, s4, tw::kX);
            v1 = 0x41800000;  // 16.0f
            mtc1(v1, f0);
            add_s(f12, f0, f1);
            lbu(t0, s4, tw::kAlpha);
            a0 = s5;
            a1 = v0;
            lwc1(f13, s4, tw::kY);
            a3 = 39;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145B84u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            v0 = 10;
            div(s1, v0);
            mfhi(s1);
        L_00145b98:
            charge(ctx, 82);
            a0 = 2;
            jal(ctx, 0x145B9Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s1, v1);
            mfhi(v1);
            a2 = addiu(v1, 11);
            lwc1(f1, s4, tw::kX);
            v1 = 0x42000000;  // 32.0f
            mtc1(v1, f0);
            add_s(f12, f0, f1);
            lbu(t0, s4, tw::kAlpha);
            a0 = s5;
            a1 = v0;
            lwc1(f13, s4, tw::kY);
            a3 = 39;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145BE0u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            lw(s0, s0, 0);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x145BF4u, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
            v1 = v0 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            s1 = sll(v0, 2);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x145C1Cu, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
            v0 = v0 & 0xFFFF;
            div(s1, v0);
            mflo(v1);
            v0 = 76;
            s0 = subu(v0, v1);
            lwc1(f1, s4, tw::kX);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s4, tw::kY);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 13;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145C78u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s4, tw::kX);
            v0 = 0x425C0000;  // 55.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s4, tw::kY);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 12;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145CD0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            if (s0 != 0) {
                // 0x00145ce0
                charge(ctx, 27);
                lwc1(f1, s4, tw::kX);
                v0 = 0x42600000;  // 56.0f
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                v0 = 76;
                v0 = subu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f1, f0);
                lwc1(f0, s4, tw::kZ);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f2);
                sub_s(f12, f0, f2);
                lwc1(f1, s4, tw::kY);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                sub_s(f14, f0, f2);
                a0 = si(-256);
                a1 = s0;
                a2 = 10;
                jal(ctx, 0x145D44u, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
            }
            // 0x00145d4c
            charge(ctx, 24);
            lwc1(f1, s4, tw::kX);
            v0 = 0x425C0000;  // 55.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s4, tw::kY);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 10;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145D9Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145DACu:  // table[33, 43, 53, 63]
            // 0x00145dac
            charge(ctx, 14);
            v1 = addiu(s3, -32);
            v0 = 10;
            div(v1, v0);
            mflo(v0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s2);
            s0 = addiu(v0, 12);
            lh(a0, v0, 12);
            jal(ctx, 0x145DCCu, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
            s1 = v0 & 0xFF;
            v0 = slti(s1, 10);
            if (v0 == 0) {
                // 0x00145de4
                charge(ctx, 19);
                a0 = 2;
                jal(ctx, 0x145DE8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                v1 = 10;
                div(s1, v1);
                mflo(v1);
                a2 = addiu(v1, 11);
                lbu(t0, s4, tw::kAlpha);
                a0 = s5;
                a1 = v0;
                lwc1(f12, s4, tw::kX);
                lwc1(f13, s4, tw::kY);
                a3 = 39;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x145E1Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                v0 = 10;
                div(s1, v0);
                mfhi(s1);
            }
            // 0x00145e30
            charge(ctx, 27);
            a0 = 2;
            jal(ctx, 0x145E34u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            v1 = 10;
            div(s1, v1);
            mfhi(v1);
            a2 = addiu(v1, 11);
            lwc1(f1, s4, tw::kX);
            v1 = 0x41800000;  // 16.0f
            mtc1(v1, f0);
            add_s(f12, f0, f1);
            lbu(t0, s4, tw::kAlpha);
            a0 = s5;
            a1 = v0;
            lwc1(f13, s4, tw::kY);
            a3 = 39;
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145E78u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
            lh(a0, s0, 0);
            jal(ctx, 0x145E84u, gen::fn_sub_16C970_0016c970);  // [datGetPcBadStatus]
            v1 = 0x80000;
            v1 = v0 & v1;
            if (v1 == 0) {
                // 0x00145ea8
                charge(ctx, 6);
                lh(a0, s0, 0);
                jal(ctx, 0x145EACu, gen::fn_sub_16C970_0016c970);  // [datGetPcBadStatus]
                v1 = v0 & 0x80;
                if (v1 == 0) {
                    // 0x00145ecc
                    charge(ctx, 7);
                    lh(a0, s0, 0);
                    jal(ctx, 0x145ED0u, gen::fn_sub_16C920_0016c920);  // [datGetPcCondition]
                    a0 = v0 & 0xFFFF;
                    v1 = 5;
                    if (a0 == v1) {
                        // 0x00145f20
                        charge(ctx, 3);
                        a2 = 1;
                    } else {
                        // 0x00145ee8
                        charge(ctx, 3);
                        v1 = 4;
                        if (a0 == v1) {
                            // 0x00145f14
                            charge(ctx, 3);
                            a2 = 0;
                        } else {
                            // 0x00145ef4
                            charge(ctx, 3);
                            v1 = 3;
                            if (a0 == v1) {
                                // 0x00145f08
                                charge(ctx, 3);
                                a2 = 2;
                            } else {
                                // 0x00145f00
                                charge(ctx, 2);
                                // 0x00145f2c
                                charge(ctx, 1);
                                a2 = si(-1);
                            }
                        }
                    }
                } else {
                    // 0x00145ec0
                    charge(ctx, 3);
                    a2 = 15;
                }
            } else {
                // 0x00145e9c
                charge(ctx, 3);
                a2 = 14;
            }
            // 0x00145f30
            charge(ctx, 3);
            v1 = si(-1);
            if (a2 != v1) {
                // 0x00145f3c
                charge(ctx, 19);
                lwc1(f1, s4, tw::kX);
                v0 = 0x42300000;  // 44.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s4, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                sub_s(f13, f1, f0);
                lbu(a3, s4, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x145F78u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
            break;
        case 0x145F88u:  // table[34, 44, 54, 64]
            // 0x00145f88
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 3;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145FA8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145FB8u:  // table[35, 45, 55, 65]
            // 0x00145fb8
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 3;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x145FD8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x145FE8u:  // table[36, 46, 56, 66]
            // 0x00145fe8
            charge(ctx, 12);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
            a2 = 4;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x146008u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x146018u:  // table[10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
            // 0x00146018
            charge(ctx, 11);
            v0 = addiu(s3, -10);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x146024u, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
            s0 = v0;
            s1 = 0;
            lw(v1, s2, 88);
            v0 = addiu(s3, -10);
            if (v1 == v0) {
                // 0x00146044
                charge(ctx, 1);
                s1 = 1;
            }
            // 0x00146048
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x001460ac
                charge(ctx, 21);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f20);
                lwc1(f1, s4, tw::kX);
                v0 = 0x42700000;  // 60.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                sub_s(f12, f0, f20);
                lwc1(f1, s4, tw::kY);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s4, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                a2 = 7;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x1460F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x00146050
                charge(ctx, 23);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f20);
                lwc1(f1, s4, tw::kX);
                v0 = 0x42700000;  // 60.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                sub_s(f12, f0, f20);
                lwc1(f1, s4, tw::kY);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s4, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                a2 = 8;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x14609Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
            // 0x00146100
            charge(ctx, 9);
            s3 = 0;
            lh(a0, gp, g::kItemSelected);  // 0x7CDF94
            jal(ctx, 0x146108u, gen::fn_sub_170E90_00170e90);  // the item record (section 6)
            lhu(a0, v0, 8);
            jal(ctx, 0x146114u, gen::fn_sub_17BF70_0017bf70);
            if (v0 != 0) {
                // 0x00146124
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x00146180
                    charge(ctx, 3);
                    v0 = slti(s2, 5);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00146130
                    charge(ctx, 10);
                    lh(a0, gp, g::kItemSelected);  // 0x7CDF94
                    jal(ctx, 0x146134u, gen::fn_sub_170E90_00170e90);  // the item record (section 6)
                    lhu(a0, v0, 8);
                    a1 = s2 & 0xFF;
                    jal(ctx, 0x146144u, gen::fn_sub_17BFA0_0017bfa0);
                    v0 = v0 & 0xFF;
                    if (v0 != 0) {
                        // 0x00146158
                        charge(ctx, 8);
                        a1 = s2 & 0xFFFF;
                        a0 = s0;
                        jal(ctx, 0x146160u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
                        v1 = v0 & 0xFF;
                        v0 = 99;
                        if (v1 != v0) {
                            // 0x00146178
                            charge(ctx, 1);
                            s3 = 1;
                        }
                    }
                    // 0x0014617c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
            }
            // 0x0014618c
            charge(ctx, 2);
            if (s3 != 0) {
                // 0x00146194
                charge(ctx, 2);
                if (s1 == 0) {
                    // 0x001461f0
                    charge(ctx, 19);
                    lwc1(f1, s4, tw::kX);
                    v0 = 0x41900000;  // 18.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    sub_s(f12, f0, f20);
                    lwc1(f1, s4, tw::kY);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s4, tw::kAlpha);
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                    a2 = 37;
                    lwc1(f14, s4, tw::kZ);
                    jal(ctx, 0x146234u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x0014619c
                    charge(ctx, 21);
                    lwc1(f1, s4, tw::kX);
                    v0 = 0x41980000;  // 19.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    sub_s(f12, f0, f20);
                    lwc1(f1, s4, tw::kY);
                    v0 = 0x41100000;  // 9.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s4, tw::kAlpha);
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                    a2 = 38;
                    lwc1(f14, s4, tw::kZ);
                    jal(ctx, 0x1461E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
            }
            // 0x0014623c
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x00146320
                charge(ctx, 4);
                lbu(s1, s0, 4);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    // 0x00146330
                    charge(ctx, 24);
                    a0 = 2;
                    jal(ctx, 0x146334u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 10;
                    div(s1, v1);
                    mflo(v1);
                    a2 = addiu(v1, 11);
                    lwc1(f1, s4, tw::kX);
                    v1 = 0x42B00000;  // 88.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    sub_s(f12, f0, f20);
                    lwc1(f1, s4, tw::kY);
                    v1 = 0x41300000;  // 11.0f
                    mtc1(v1, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s4, tw::kAlpha);
                    a0 = s5;
                    a1 = v0;
                    lwc1(f14, s4, tw::kZ);
                    jal(ctx, 0x146388u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
                // 0x00146390
                charge(ctx, 25);
                a0 = 2;
                jal(ctx, 0x146394u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lbu(a0, s0, 4);
                v1 = 10;
                div(a0, v1);
                mfhi(v1);
                a2 = addiu(v1, 11);
                lwc1(f1, s4, tw::kX);
                v1 = 0x42D00000;  // 104.0f
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                sub_s(f12, f0, f20);
                lwc1(f1, s4, tw::kY);
                v1 = 0x41300000;  // 11.0f
                mtc1(v1, f0);
                add_s(f13, f0, f1);
                lbu(a3, s4, tw::kAlpha);
                a0 = s5;
                a1 = v0;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x1463ECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x00146244
                charge(ctx, 4);
                lbu(s1, s0, 4);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    // 0x00146254
                    charge(ctx, 24);
                    a0 = 1;
                    jal(ctx, 0x146258u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    v1 = 10;
                    div(s1, v1);
                    mflo(v1);
                    a2 = addiu(v1, 11);
                    lwc1(f1, s4, tw::kX);
                    v1 = 0x42B00000;  // 88.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    sub_s(f12, f0, f20);
                    lwc1(f1, s4, tw::kY);
                    v1 = 0x41300000;  // 11.0f
                    mtc1(v1, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s4, tw::kAlpha);
                    a0 = s5;
                    a1 = v0;
                    lwc1(f14, s4, tw::kZ);
                    jal(ctx, 0x1462ACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
                // 0x001462b4
                charge(ctx, 27);
                a0 = 1;
                jal(ctx, 0x1462B8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lbu(a0, s0, 4);
                v1 = 10;
                div(a0, v1);
                mfhi(v1);
                a2 = addiu(v1, 11);
                lwc1(f1, s4, tw::kX);
                v1 = 0x42D00000;  // 104.0f
                mtc1(v1, f0);
                add_s(f0, f0, f1);
                sub_s(f12, f0, f20);
                lwc1(f1, s4, tw::kY);
                v1 = 0x41300000;  // 11.0f
                mtc1(v1, f0);
                add_s(f13, f0, f1);
                lbu(a3, s4, tw::kAlpha);
                a0 = s5;
                a1 = v0;
                lwc1(f14, s4, tw::kZ);
                jal(ctx, 0x146310u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
            // 0x001463f4
            charge(ctx, 40);
            lw(v1, s4, tw::kAlpha);
            v0 = 255;
            s2 = subu(v0, v1);
            lwc1(f0, s4, tw::kX);
            cvt_w_s(f0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x43020000;  // 130.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            v0 = 0x41200000;  // 10.0f
            mtc1(v0, f1);
            sub_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(s1, f0);
            lwc1(f0, s4, tw::kY);
            cvt_w_s(f0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(s3, f0);
            lhu(a0, s0, 2);
            jal(ctx, 0x146450u, gen::fn_sub_173220_00173220);  // [datGetPersonaName]
            v1 = 0x42C80000;  // 100.0f
            mtc1(v1, f12);
            v1 = si(-256);
            a2 = s2 | v1;
            a0 = s1;
            a1 = s3;
            a3 = 10;
            t0 = 1;
            t1 = v0;
            t2 = 16;
            t3 = 0;
            jal(ctx, 0x146484u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
            break;
        case 0x146494u:  // table[70]
            // 0x00146494
            charge(ctx, 26);
            lwc1(f1, s4, tw::kX);
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 8;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1464C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 1;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1464ECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1464FCu:  // table[71]
            // 0x001464fc
            charge(ctx, 26);
            lwc1(f1, s4, tw::kX);
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 8;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x14652Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 2;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x146554u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x146564u:  // table[72]
            // 0x00146564
            charge(ctx, 26);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 8;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x146584u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s4, tw::kX);
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 3;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1465BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1465CCu:  // table[73]
            // 0x001465cc
            charge(ctx, 40);
            lwc1(f1, s4, tw::kX);
            v0 = 0x43760000;  // 246.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 0;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1465FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s4, tw::kX);
            v0 = 0x43A10000;  // 322.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 3;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x146634u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 5;
            lwc1(f12, s4, tw::kX);
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x14665Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x14666Cu:  // table[74]
            // 0x0014666c
            charge(ctx, 28);
            lwc1(f1, s4, tw::kX);
            v0 = 0x42000000;  // 32.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 0;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x14669Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s4, tw::kX);
            v0 = 0x42D80000;  // 108.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s4, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 3;
            lwc1(f13, s4, tw::kY);
            lwc1(f14, s4, tw::kZ);
            jal(ctx, 0x1466D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1466DCu:  // table[8, 9, 22, 23, 24, 25, 26, 27, 28, 29, 37, 38, 39, 47, 48, 49, 57, 58, 59, 67, 68, 69]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x001466dc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x00146710 sub_146710 -- 3548 bytes; frame 0x140: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemPageLeftLayout] (item work): slides the item page out to the left (-100) for a page change.
void sub_146710(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00146710
    enter(ctx, 258);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x138);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14678Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x68);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1467F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x70);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146864u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x78);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1468D8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x80);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146944u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x88);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1469B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x90);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146A24u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x98);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146A90u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x130);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xA0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146B04u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x00146ea8
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00146b18
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x00146e3c
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00146b28
            charge(ctx, 197);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x130);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(t0, sp, 0x130);
            sd(t0, sp, 0xA8);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x146BE0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x130);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(t0, sp, 0x130);
            sd(t0, sp, 0xB0);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x146C68u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x130);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(t0, sp, 0x130);
            sd(t0, sp, 0xB8);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x146CF0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x130);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(t0, sp, 0x130);
            sd(t0, sp, 0xC0);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x146D78u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x130);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(t0, sp, 0x130);
            sd(t0, sp, 0xC8);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x130);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x146E00u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        }
        // 0x00146ea4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00146eb4
    charge(ctx, 226);
    v0 = 0x42780000;  // 62.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xD0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146F24u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, item::kTweens);
    sw(zero, v0, 4832);
    v0 = 0x436F0000;  // 239.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xD8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x146FA4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 379;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xE0);
    lwc1(f0, sp, 0xE0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xE0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(a0, s2, item::kEquipTweens);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xE0);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147014u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xE8);
    lwc1(f0, sp, 0xE8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xE8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xE8);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14707Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xF0);
    lwc1(f0, sp, 0xF0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xF0);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1470E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xF8);
    lwc1(f0, sp, 0xF8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xF8);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14714Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x438B0000;  // 278.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x100);
    lwc1(f0, sp, 0x100);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x100);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x100);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1471B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x108);
    lwc1(f0, sp, 0x108);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x108);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x108);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147228u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x001472fc
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014723c
        charge(ctx, 5);
        lw(v0, s2, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x001472e0
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kEquipTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x00147250
            charge(ctx, 36);
            v0 = 0x41F00000;  // 30.0f
            sw(v0, sp, 0x130);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x134);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kEquipTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x130);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1472D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x001472f8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00147308
    charge(ctx, 121);
    v0 = 0x42D00000;  // 104.0f
    sw(v0, sp, 0x130);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x110);
    lwc1(f0, sp, 0x110);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 1360);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x110);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147368u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42F80000;  // 124.0f
    sw(v0, sp, 0x130);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x118);
    lwc1(f0, sp, 0x118);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x118);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 1428);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x118);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1473D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    sw(v0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x120);
    lwc1(f0, sp, 0x120);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 2108);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x120);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147444u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 439;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x128);
    lwc1(f0, sp, 0x128);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x128);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 2176);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x128);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1474C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x140);
}

// 0x001474F0 sub_1474F0 -- 3572 bytes; frame 0x140: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemPageFromLeftLayout] (item work): slides the item page in from the left.
void sub_1474F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001474f0
    enter(ctx, 270);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0x130);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x138);
    lwc1(f1, sp, 0x138);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x138);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x138);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147570u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x68);
    lwc1(f1, sp, 0x68);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1475E0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x70);
    lwc1(f1, sp, 0x70);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147650u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x78);
    lwc1(f1, sp, 0x78);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x78);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1476CCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x80);
    lwc1(f1, sp, 0x80);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x80);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14773Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x88);
    lwc1(f1, sp, 0x88);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x88);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1477B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0x130);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x90);
    lwc1(f1, sp, 0x90);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x90);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x90);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147828u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0x130);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0x98);
    lwc1(f1, sp, 0x98);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x98);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 544);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x98);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147898u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xA0);
    lwc1(f1, sp, 0xA0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147914u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x00147ccc
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00147928
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x00147c60
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00147938
            charge(ctx, 202);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x130);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(v0, sp, 0x130);
            sd(v0, sp, 0xA8);
            lwc1(f1, sp, 0xA8);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xA8);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA8);
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1479F4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x130);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(v0, sp, 0x130);
            sd(v0, sp, 0xB0);
            lwc1(f1, sp, 0xB0);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xB0);
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x147A80u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x130);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(v0, sp, 0x130);
            sd(v0, sp, 0xB8);
            lwc1(f1, sp, 0xB8);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB8);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xB8);
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x147B0Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x130);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(v0, sp, 0x130);
            sd(v0, sp, 0xC0);
            lwc1(f1, sp, 0xC0);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xC0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC0);
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x147B98u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0x130);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x134);
            ld(v0, sp, 0x130);
            sd(v0, sp, 0xC8);
            lwc1(f1, sp, 0xC8);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xC8);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC8);
            ld(t1, sp, 0x130);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x147C24u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        }
        // 0x00147cc8
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00147cd8
    charge(ctx, 220);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xD0);
    lwc1(f1, sp, 0xD0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xD0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4760);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD0);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147D4Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, item::kTweens);
    sw(zero, v0, 4832);
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(v0, sp, 0x130);
    sd(v0, sp, 0xD8);
    lwc1(f1, sp, 0xD8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xD8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 4964);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD8);
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147DD0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 379;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xE0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(a0, s2, item::kEquipTweens);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147E38u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xE8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147E9Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xF0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147F00u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0xF8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147F64u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x438B0000;  // 278.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x100);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x147FC8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x130);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x108);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148034u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x00148108
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00148048
        charge(ctx, 5);
        lw(v0, s2, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x001480ec
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kEquipTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014805c
            charge(ctx, 36);
            v0 = 0x41F00000;  // 30.0f
            sw(v0, sp, 0x130);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x134);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kEquipTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x130);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1480DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x00148104
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00148114
    charge(ctx, 116);
    v0 = 0x42D00000;  // 104.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x130);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x110);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 1360);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148170u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42F80000;  // 124.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x130);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x118);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 1428);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1481D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x120);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f1, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 2108);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148244u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 439;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x130);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x134);
    ld(t0, sp, 0x130);
    sd(t0, sp, 0x128);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f1, f12);
    swc1(f0, sp, 0x130);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kEquipTweens);
    a0 = addiu(v0, 2176);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x130);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1482BCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x140);
}

// 0x001482F0 sub_1482F0 -- 1424 bytes; frame 0xA0: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_EquipPageCloseLayout] (item work): the equipment page's slide-out (the 40 records +192).
void sub_1482F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x001482f0
    enter(ctx, 175);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    v0 = 379;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x98);
    lwc1(f1, sp, 0x98);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x98);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 192);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x98);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148370u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x40);
    lwc1(f1, sp, 0x40);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x40);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x40);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1483DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x48);
    lwc1(f1, sp, 0x48);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x48);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148448u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x50);
    lwc1(f1, sp, 0x50);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x50);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1484B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x438B0000;  // 278.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x58);
    lwc1(f1, sp, 0x58);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148520u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x60);
    lwc1(f1, sp, 0x60);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148598u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x00148688
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001485ac
        charge(ctx, 5);
        lw(v0, s1, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x0014866c
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kEquipTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x001485c0
            charge(ctx, 43);
            v0 = 0x41F00000;  // 30.0f
            sw(v0, sp, 0x90);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x94);
            ld(v0, sp, 0x90);
            sd(v0, sp, 0x68);
            lwc1(f1, sp, 0x68);
            mtc1(zero, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x68);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kEquipTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            ld(t1, sp, 0x90);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14865Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x00148684
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00148694
    charge(ctx, 123);
    v0 = 0x42D00000;  // 104.0f
    sw(v0, sp, 0x90);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x70);
    lwc1(f1, sp, 0x70);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1360);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1486F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42F80000;  // 124.0f
    sw(v0, sp, 0x90);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x78);
    lwc1(f1, sp, 0x78);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x78);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1428);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148764u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    sw(v0, sp, 0x90);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x80);
    lwc1(f1, sp, 0x80);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2108);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x80);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1487DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 439;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x88);
    lwc1(f1, sp, 0x88);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2176);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x88);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148860u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xA0);
}

// 0x00148880 sub_148880 -- 900 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_ItemDrawEquipElement] (tween, element, item work): one element of the equipment page: 32 / 31 frames, 20 the
// list (sub_13E710 of +168), 21 the detail, the rest frame sprites of camp files 0..2 and 13.
void sub_148880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00148880
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v1 = 32;
    if (a1 == v1) {
        // 0x00148b1c
        charge(ctx, 52);
        lwc1(f1, s1, tw::kX);
        v0 = 0x41A00000;  // 20.0f
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 5;
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x148B4Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s1, tw::kX);
        v0 = 0x42C20000;  // 97.0f
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        v0 = 389;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, tw::kY);
        add_s(f1, f1, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 9;
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x148BACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s1, tw::kX);
        v0 = 0x42F40000;  // 122.0f
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 3;
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x148BE4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x001488a0
        charge(ctx, 3);
        v1 = 31;
        if (a1 == v1) {
            // 0x00148ab4
            charge(ctx, 26);
            lbu(a3, s1, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 8;
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x148AD4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 4;
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x148B0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x001488ac
            charge(ctx, 3);
            v1 = 21;
            if (a1 != v1) {
                // 0x001488b8
                charge(ctx, 3);
                v1 = 20;
                if (a1 == v1) {
                    // 0x00148a90
                    charge(ctx, 9);
                    ldr(a0, s1, 56);
                    ldl(a0, s1, 63);
                    lwc1(f12, s1, tw::kZ);
                    lw(a1, a2, 168);
                    lw(a2, s1, tw::kAlpha);
                    jal(ctx, 0x148AA4u, gen::fn_sub_13E710_0013e710);
                } else {
                    // 0x001488c4
                    charge(ctx, 3);
                    v1 = 13;
                    if (a1 != v1) {
                        // 0x001488d0
                        charge(ctx, 3);
                        v1 = 12;
                        if (a1 == v1) {
                            goto L_00148a60;
                        }
                        // 0x001488dc
                        charge(ctx, 3);
                        v1 = 11;
                        if (a1 == v1) {
                            goto L_00148a60;
                        }
                        // 0x001488e8
                        charge(ctx, 3);
                        v1 = 10;
                        if (a1 == v1) {
                            goto L_00148a60;
                        }
                        // 0x001488f4
                        charge(ctx, 3);
                        v1 = 5;
                        if (a1 == v1) {
                            // 0x00148a30
                            charge(ctx, 12);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s0;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 35;
                            lwc1(f12, s1, tw::kX);
                            lwc1(f13, s1, tw::kY);
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x148A50u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x00148900
                            charge(ctx, 3);
                            v1 = 4;
                            if (a1 == v1) {
                                // 0x00148a00
                                charge(ctx, 12);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s0;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 36;
                                lwc1(f12, s1, tw::kX);
                                lwc1(f13, s1, tw::kY);
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x148A20u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x0014890c
                                charge(ctx, 3);
                                v1 = 3;
                                if (a1 == v1) {
                                    // 0x001489d0
                                    charge(ctx, 12);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s0;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 40;
                                    lwc1(f12, s1, tw::kX);
                                    lwc1(f13, s1, tw::kY);
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x1489F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x00148918
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (a1 == v1) {
                                        // 0x001489a0
                                        charge(ctx, 12);
                                        lbu(a3, s1, tw::kAlpha);
                                        a0 = s0;
                                        v0 = 0x830000;
                                        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                        a2 = 36;
                                        lwc1(f12, s1, tw::kX);
                                        lwc1(f13, s1, tw::kY);
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x1489C0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    } else {
                                        // 0x00148924
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (a1 == v1) {
                                            // 0x00148970
                                            charge(ctx, 12);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s0;
                                            v0 = 0x830000;
                                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                            a2 = 33;
                                            lwc1(f12, s1, tw::kX);
                                            lwc1(f13, s1, tw::kY);
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x148990u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        } else {
                                            // 0x00148930
                                            charge(ctx, 2);
                                            if (a1 == 0) {
                                                // 0x00148940
                                                charge(ctx, 12);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s0;
                                                v0 = 0x830000;
                                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                                a2 = 44;
                                                lwc1(f12, s1, tw::kX);
                                                lwc1(f13, s1, tw::kY);
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x148960u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            } else {
                                                // 0x00148938
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // 0x00148bec (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        ld(ra, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x30);
                        return;
                    }
                L_00148a60:
                    charge(ctx, 12);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                    a2 = 5;
                    lwc1(f12, s1, tw::kX);
                    lwc1(f13, s1, tw::kY);
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x148A80u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
            }
        }
    }
    // 0x00148bec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00148C10 sub_148C10 -- 2772 bytes; frame 0x100: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_EquipPageLeftLayout] (item work): slides the equipment page out to the left.
void sub_148C10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00148c10
    enter(ctx, 173);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    v0 = 379;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0xF0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xF8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 192);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148C8Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x48);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148CF8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x50);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148D64u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x58);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148DD0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x438B0000;  // 278.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x60);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148E3Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x68);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x148EB0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x00148fa0
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00148ec4
        charge(ctx, 5);
        lw(v0, s1, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x00148f84
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kEquipTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x00148ed8
            charge(ctx, 43);
            v0 = 0x41F00000;  // 30.0f
            mtc1(v0, f2);
            sw(v0, sp, 0xF0);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xF4);
            ld(t0, sp, 0xF0);
            sd(t0, sp, 0x70);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f2, f0);
            swc1(f0, sp, 0xF0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kEquipTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xF0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x148F74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x00148f9c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00148fac
    charge(ctx, 283);
    v0 = 0x42D00000;  // 104.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x78);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1360);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149010u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42F80000;  // 124.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x80);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1428);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14907Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x88);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2108);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1490F4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 439;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x90);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2176);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149174u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 381;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x98);
    lwc1(f0, sp, 0x98);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x98);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(a0, s1, item::kMaterialTweens);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x98);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1491E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xA0);
    lwc1(f0, sp, 0xA0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xA0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14924Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xA8);
    lwc1(f0, sp, 0xA8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xA8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA8);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1492B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xB0);
    lwc1(f0, sp, 0xB0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14931Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 273;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xB8);
    lwc1(f0, sp, 0xB8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xB8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB8);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149390u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xC0);
    lwc1(f0, sp, 0xC0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xC0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xC0);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149404u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x001494fc
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00149418
        charge(ctx, 5);
        lw(v0, s1, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x001494e0
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014942c
            charge(ctx, 45);
            v0 = 610;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xF0);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xF4);
            ld(v0, sp, 0xF0);
            sd(v0, sp, 0xC8);
            lwc1(f0, sp, 0xC8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0xC8);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kMaterialTweens);
            a0 = addu(v0, v1);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC8);
            ld(t1, sp, 0xF0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1494D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x001494f8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x00149508
    charge(ctx, 119);
    v0 = 0x423C0000;  // 47.0f
    sw(v0, sp, 0xF0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xD0);
    lwc1(f0, sp, 0xD0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xD0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 1360);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD0);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149568u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0xF0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xD8);
    lwc1(f0, sp, 0xD8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xD8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 1428);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD8);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1495D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    sw(v0, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xE0);
    lwc1(f0, sp, 0xE0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xE0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xE0);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149644u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xE8);
    lwc1(f0, sp, 0xE8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xE8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 2108);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xE8);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1496C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x100);
}

// 0x001496F0 sub_1496F0 -- 3488 bytes; frame 0x130: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemPageRightLayout] (item work): slides the item page in from the right (+100).
void sub_1496F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001496f0
    enter(ctx, 253);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s3 = a0;
    v0 = 0x42200000;  // 40.0f
    sw(v0, sp, 0x120);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0x128);
    lwc1(f0, sp, 0x128);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x128);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x128);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14976Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0x78);
    lwc1(f0, sp, 0x78);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x78);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1497D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    sw(v0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0x80);
    lwc1(f0, sp, 0x80);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x80);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x80);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14983Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0x88);
    lwc1(f0, sp, 0x88);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x88);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x88);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1498B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    sw(v0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0x90);
    lwc1(f0, sp, 0x90);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x90);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x90);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149918u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0x98);
    lwc1(f0, sp, 0x98);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x98);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 408);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x98);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14998Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    sw(v0, sp, 0x120);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0xA0);
    lwc1(f0, sp, 0xA0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xA0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 476);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1499F4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0x120);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0xA8);
    lwc1(f0, sp, 0xA8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xA8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 544);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA8);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149A5Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x120);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0xB0);
    lwc1(f0, sp, 0xB0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xB0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149AD0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s2 = 0;
    for (;;) {
        // 0x00149e08
        charge(ctx, 3);
        v0 = slti(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00149ae4
        charge(ctx, 4);
        lw(v0, s3, item::kTargetCount);
        at = slt(s2, v0);
        if (at == 0) {
            // 0x00149d9c
            charge(ctx, 26);
            v0 = sll(s2, 4);
            v1 = addu(v0, s2);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x00149af4
            charge(ctx, 170);
            v0 = sll(s2, 4);
            v1 = addu(v0, s2);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x120);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x124);
            v0 = sll(s2, 2);
            v0 = addu(v0, s2);
            s1 = sll(v0, 1);
            v0 = 7;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x120);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x149B94u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x120);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x124);
            v0 = 7;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x120);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x149C04u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x120);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x124);
            v0 = 7;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x120);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x149C74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x120);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x124);
            v0 = 7;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x120);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x149CE4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0x120);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x124);
            v0 = sll(s2, 4);
            v1 = addu(v0, s2);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            s0 = sll(v0, 3);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, s0);
            sw(zero, v0, 2376);
            v0 = 9;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x120);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x149D74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, s0);
            sw(zero, v0, 2384);
            lw(v0, s3, item::kTweens);
            v0 = addu(v0, s0);
            sw(zero, v0, 2452);
        }
        // 0x00149e04
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00149e14
    charge(ctx, 230);
    v0 = 0x42780000;  // 62.0f
    sw(v0, sp, 0x120);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0xB8);
    lwc1(f0, sp, 0xB8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xB8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 4760);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB8);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149E80u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s3, item::kTweens);
    sw(zero, v0, 4832);
    v0 = 0x436F0000;  // 239.0f
    sw(v0, sp, 0x120);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x124);
    ld(v0, sp, 0x120);
    sd(v0, sp, 0xC0);
    lwc1(f0, sp, 0xC0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xC0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s3, item::kTweens);
    a0 = addiu(v0, 4964);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xC0);
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149EFCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 381;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x120);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0xC8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, s3, item::kMaterialTweens);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149F6Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0xD0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x149FD8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0xD8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A044u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0xE0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A0B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 273;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0xE8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A124u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x120);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0xF0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A198u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x0014a290
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014a1ac
        charge(ctx, 5);
        lw(v0, s3, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x0014a274
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014a1c0
            charge(ctx, 45);
            v0 = 610;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x120);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            v0 = addu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x124);
            ld(t0, sp, 0x120);
            sd(t0, sp, 0xF8);
            v0 = lui(0xC234);
            sw(v0, sp, 0x120);
            lw(v0, s3, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 744);
            sd(zero, sp, 0x0);
            v0 = 8;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s3, item::kMaterialTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0x120);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14A264u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x0014a28c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014a29c
    charge(ctx, 125);
    v0 = 0x423C0000;  // 47.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x120);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0x100);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1360);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A300u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42860000;  // 67.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x120);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0x108);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1428);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A36Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x120);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0x110);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A3E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x120);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x124);
    ld(t0, sp, 0x120);
    sd(t0, sp, 0x118);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x120);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s3, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2108);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x120);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A464u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x130);
}

// 0x0014A490 sub_14A490 -- 3452 bytes; frame 0x120: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_ItemPageToRightLayout] (item work): slides the item page out to the right.
void sub_14A490(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0014a490
    enter(ctx, 240);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x42200000;  // 40.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x110);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x118);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(a0, a0, 188);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A504u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x435B0000;  // 219.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x68);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A568u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x439F0000;  // 318.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x70);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A5CCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 341;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x78);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A638u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F20000;  // 484.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x80);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A69Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 507;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x88);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 408);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A708u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43630000;  // 227.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x110);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x90);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 476);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A76Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    mtc1(v0, f0);
    sw(v0, sp, 0x110);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0x98);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 544);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A7D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 558;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0xA0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 2040);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14A83Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0014ab50
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014a850
        charge(ctx, 4);
        lw(v0, s2, item::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x0014aae4
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2044);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2112);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2180);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2248);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2316);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        } else {
            // 0x0014a860
            charge(ctx, 161);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42780000;  // 62.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x110);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x114);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 4;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 30);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x110);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14A8FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x110);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x114);
            sd(zero, sp, 0x0);
            v0 = 4;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 31);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x110);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14A968u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x110);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x114);
            sd(zero, sp, 0x0);
            v0 = 4;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 32);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x110);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14A9D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x110);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x114);
            sd(zero, sp, 0x0);
            v0 = 4;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 33);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x110);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14AA40u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0x110);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x114);
            sd(zero, sp, 0x0);
            a2 = 2;
            sd(a2, sp, 0x8);
            v1 = addiu(s0, 34);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a3 = a2;
            ld(t0, sp, 0x110);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14AAA8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2384);
            lw(v0, s2, item::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 2452);
        }
        // 0x0014ab4c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0014ab5c
    charge(ctx, 237);
    v0 = 0x42780000;  // 62.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x110);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0xA8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f1, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 4760);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14ABC4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, item::kTweens);
    sw(zero, v0, 4832);
    v0 = 0x436F0000;  // 239.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x110);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x114);
    ld(t0, sp, 0x110);
    sd(t0, sp, 0xB0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f1, f12);
    swc1(f0, sp, 0x110);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s2, item::kTweens);
    a0 = addiu(v0, 4964);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14AC3Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 381;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xB8);
    lwc1(f1, sp, 0xB8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xB8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, s2, item::kMaterialTweens);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB8);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14ACB4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    sw(v0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xC0);
    lwc1(f1, sp, 0xC0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xC0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xC0);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14AD24u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    sw(v0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xC8);
    lwc1(f1, sp, 0xC8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xC8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xC8);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14AD94u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    sw(v0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xD0);
    lwc1(f1, sp, 0xD0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xD0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD0);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14AE04u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 273;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xD8);
    lwc1(f1, sp, 0xD8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xD8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xD8);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14AE80u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xE0);
    lwc1(f1, sp, 0xE0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xE0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xE0);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14AEFCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x0014affc
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014af10
        charge(ctx, 5);
        lw(v0, s2, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x0014afe0
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014af24
            charge(ctx, 47);
            v0 = 610;
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
            swc1(f2, sp, 0x110);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            v0 = addu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x114);
            ld(v0, sp, 0x110);
            sd(v0, sp, 0xE8);
            lwc1(f0, sp, 0xE8);
            sub_s(f0, f0, f2);
            swc1(f0, sp, 0xE8);
            lw(v0, s2, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 744);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, item::kMaterialTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0xE8);
            ld(t1, sp, 0x110);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14AFD0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x0014aff8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014b008
    charge(ctx, 129);
    v0 = 0x423C0000;  // 47.0f
    sw(v0, sp, 0x110);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xF0);
    lwc1(f1, sp, 0xF0);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1360);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xF0);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B070u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x110);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0xF8);
    lwc1(f1, sp, 0xF8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1428);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xF8);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B0E0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    sw(v0, sp, 0x110);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0x100);
    lwc1(f1, sp, 0x100);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x100);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x100);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B15Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x110);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x114);
    ld(v0, sp, 0x110);
    sd(v0, sp, 0x108);
    lwc1(f1, sp, 0x108);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x108);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2108);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x108);
    ld(t1, sp, 0x110);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B1E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x120);
}

// 0x0014B210 sub_14B210 -- 2764 bytes; frame 0x100: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_EquipPageFromLeftLayout] (item work): slides the equipment page in from the left.
void sub_14B210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x0014b210
    enter(ctx, 181);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    v0 = 379;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0xF8);
    lwc1(f1, sp, 0xF8);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xF8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 192);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xF8);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B294u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x48);
    lwc1(f1, sp, 0x48);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x48);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x48);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B304u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x50);
    lwc1(f1, sp, 0x50);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x50);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B374u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x58);
    lwc1(f1, sp, 0x58);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B3E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x438B0000;  // 278.0f
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x60);
    lwc1(f1, sp, 0x60);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x60);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B454u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x68);
    lwc1(f1, sp, 0x68);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B4D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x0014b5c4
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014b4e4
        charge(ctx, 5);
        lw(v0, s1, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x0014b5a8
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kEquipTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014b4f8
            charge(ctx, 44);
            v0 = 0x41F00000;  // 30.0f
            sw(v0, sp, 0xF0);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xF4);
            ld(v0, sp, 0xF0);
            sd(v0, sp, 0x70);
            lwc1(f1, sp, 0x70);
            v0 = lui(0xC2C8);
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x70);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kEquipTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x70);
            ld(t1, sp, 0xF0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14B598u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x0014b5c0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014b5d0
    charge(ctx, 279);
    v0 = 0x42D00000;  // 104.0f
    sw(v0, sp, 0xF0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x78);
    lwc1(f1, sp, 0x78);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x78);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1360);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B638u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42F80000;  // 124.0f
    sw(v0, sp, 0xF0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x80);
    lwc1(f1, sp, 0x80);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1428);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x80);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B6A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    sw(v0, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x88);
    lwc1(f1, sp, 0x88);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2108);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x88);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B724u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 439;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(v0, sp, 0xF0);
    sd(v0, sp, 0x90);
    lwc1(f1, sp, 0x90);
    v0 = lui(0xC2C8);
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x90);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kEquipTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2176);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x90);
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B7ACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 381;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0x98);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(a0, s1, item::kMaterialTweens);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B814u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    mtc1(v0, f0);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xA0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B878u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    mtc1(v0, f0);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xA8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B8DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    mtc1(v0, f0);
    sw(v0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xB0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B940u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 273;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xB8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14B9ACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF0);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xC0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BA18u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x0014bb08
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014ba2c
        charge(ctx, 5);
        lw(v0, s1, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x0014baec
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014ba40
            charge(ctx, 43);
            v0 = 610;
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
            swc1(f2, sp, 0xF0);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xF4);
            ld(t0, sp, 0xF0);
            sd(t0, sp, 0xC8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f2, f12);
            swc1(f0, sp, 0xF0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kMaterialTweens);
            a0 = addu(v0, v1);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xF0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14BADCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x0014bb04
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014bb14
    charge(ctx, 114);
    v0 = 0x423C0000;  // 47.0f
    mtc1(v0, f0);
    sw(v0, sp, 0xF0);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xD0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 1360);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BB70u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42860000;  // 67.0f
    mtc1(v0, f0);
    sw(v0, sp, 0xF0);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xD8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f0, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 1428);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BBD4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xE0);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f1, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 2040);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BC44u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0xF0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xF4);
    ld(t0, sp, 0xF0);
    sd(t0, sp, 0xE8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    add_s(f0, f1, f12);
    swc1(f0, sp, 0xF0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s1, item::kMaterialTweens);
    a0 = addiu(v0, 2108);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xF0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BCBCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x100);
}

// 0x0014BCE0 sub_14BCE0 -- 1448 bytes; frame 0xA0: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_MaterialPageCloseLayout] (item work): the material page's slide-out (the 40 records +196).
void sub_14BCE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0014bce0
    enter(ctx, 178);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    v0 = 381;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 0x41400000;  // 12.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x98);
    lwc1(f1, sp, 0x98);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x98);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, a0, 196);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x98);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BD60u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41500000;  // 13.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x40);
    lwc1(f1, sp, 0x40);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x40);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x40);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BDCCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42E00000;  // 112.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x48);
    lwc1(f1, sp, 0x48);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x48);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BE38u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43070000;  // 135.0f
    sw(v0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x50);
    lwc1(f1, sp, 0x50);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x50);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x50);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BEA4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 273;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x58);
    lwc1(f1, sp, 0x58);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BF1Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 301;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 0x41D80000;  // 27.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x60);
    lwc1(f1, sp, 0x60);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14BF94u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s0 = 0;
    for (;;) {
        // 0x0014c090
        charge(ctx, 3);
        v0 = slti(s0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014bfa8
        charge(ctx, 5);
        lw(v0, s1, item::kTargetCount);
        v0 = addiu(v0, -1);
        at = slt(v0, s0);
        if (at != 0) {
            // 0x0014c074
            charge(ctx, 6);
            v0 = sll(s0, 4);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kMaterialTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
        } else {
            // 0x0014bfbc
            charge(ctx, 46);
            v0 = 610;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x90);
            v0 = sll(s0, 4);
            v1 = addu(v0, s0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x94);
            ld(v0, sp, 0x90);
            sd(v0, sp, 0x68);
            lwc1(f1, sp, 0x68);
            mtc1(zero, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x68);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 10);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s1, item::kMaterialTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x68);
            ld(t1, sp, 0x90);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x14C064u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        }
        // 0x0014c08c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014c09c
    charge(ctx, 123);
    v0 = 0x423C0000;  // 47.0f
    sw(v0, sp, 0x90);
    v0 = 0x42740000;  // 61.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x70);
    lwc1(f1, sp, 0x70);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1360);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14C100u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x42860000;  // 67.0f
    sw(v0, sp, 0x90);
    v0 = 0x435B0000;  // 219.0f
    sw(v0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x78);
    lwc1(f1, sp, 0x78);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x78);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 1428);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x78);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14C16Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43620000;  // 226.0f
    sw(v0, sp, 0x90);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x80);
    lwc1(f1, sp, 0x80);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x80);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2040);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x80);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14C1E4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x90);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x94);
    ld(v0, sp, 0x90);
    sd(v0, sp, 0x88);
    lwc1(f1, sp, 0x88);
    mtc1(zero, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x88);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s1, item::kMaterialTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 2108);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x88);
    ld(t1, sp, 0x90);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14C268u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0xA0);
}

// 0x0014C290 sub_14C290 -- 812 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_ItemDrawMaterialElement] (tween, element, item work): one element of the material page: 31 / 30 frames, 20
// the list (sub_140E30 of +172), 21 the detail, the rest frame sprites.
void sub_14C290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0014c290
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v1 = 31;
    if (a1 == v1) {
        // 0x0014c52c
        charge(ctx, 30);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 3;
        lwc1(f12, s1, tw::kX);
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x14C54Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s1, tw::kX);
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f1, f1, f0);
        v0 = 459;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f12, f0, f1);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 5;
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x14C59Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x0014c2b0
        charge(ctx, 3);
        v1 = 30;
        if (a1 == v1) {
            // 0x0014c4c4
            charge(ctx, 26);
            lbu(a3, s1, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 8;
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x14C4E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 4;
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x14C51Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x0014c2bc
            charge(ctx, 3);
            v1 = 21;
            if (a1 != v1) {
                // 0x0014c2c8
                charge(ctx, 3);
                v1 = 20;
                if (a1 == v1) {
                    // 0x0014c4a0
                    charge(ctx, 9);
                    ldr(a0, s1, 56);
                    ldl(a0, s1, 63);
                    lwc1(f12, s1, tw::kZ);
                    lw(a1, a2, 172);
                    lw(a2, s1, tw::kAlpha);
                    jal(ctx, 0x14C4B4u, gen::fn_sub_140E30_00140e30);
                } else {
                    // 0x0014c2d4
                    charge(ctx, 3);
                    v1 = 13;
                    if (a1 != v1) {
                        // 0x0014c2e0
                        charge(ctx, 3);
                        v1 = 12;
                        if (a1 == v1) {
                            goto L_0014c470;
                        }
                        // 0x0014c2ec
                        charge(ctx, 3);
                        v1 = 11;
                        if (a1 == v1) {
                            goto L_0014c470;
                        }
                        // 0x0014c2f8
                        charge(ctx, 3);
                        v1 = 10;
                        if (a1 == v1) {
                            goto L_0014c470;
                        }
                        // 0x0014c304
                        charge(ctx, 3);
                        v1 = 5;
                        if (a1 == v1) {
                            // 0x0014c440
                            charge(ctx, 12);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s0;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 41;
                            lwc1(f12, s1, tw::kX);
                            lwc1(f13, s1, tw::kY);
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x14C460u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x0014c310
                            charge(ctx, 3);
                            v1 = 4;
                            if (a1 == v1) {
                                // 0x0014c410
                                charge(ctx, 12);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s0;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 36;
                                lwc1(f12, s1, tw::kX);
                                lwc1(f13, s1, tw::kY);
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x14C430u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x0014c31c
                                charge(ctx, 3);
                                v1 = 3;
                                if (a1 == v1) {
                                    // 0x0014c3e0
                                    charge(ctx, 12);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s0;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                    a2 = 34;
                                    lwc1(f12, s1, tw::kX);
                                    lwc1(f13, s1, tw::kY);
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x14C400u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x0014c328
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (a1 == v1) {
                                        // 0x0014c3b0
                                        charge(ctx, 12);
                                        lbu(a3, s1, tw::kAlpha);
                                        a0 = s0;
                                        v0 = 0x830000;
                                        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                        a2 = 36;
                                        lwc1(f12, s1, tw::kX);
                                        lwc1(f13, s1, tw::kY);
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x14C3D0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    } else {
                                        // 0x0014c334
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (a1 == v1) {
                                            // 0x0014c380
                                            charge(ctx, 12);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s0;
                                            v0 = 0x830000;
                                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                            a2 = 33;
                                            lwc1(f12, s1, tw::kX);
                                            lwc1(f13, s1, tw::kY);
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x14C3A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        } else {
                                            // 0x0014c340
                                            charge(ctx, 2);
                                            if (a1 == 0) {
                                                // 0x0014c350
                                                charge(ctx, 12);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s0;
                                                v0 = 0x830000;
                                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                                a2 = 45;
                                                lwc1(f12, s1, tw::kX);
                                                lwc1(f13, s1, tw::kY);
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x14C370u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            } else {
                                                // 0x0014c348
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        // 0x0014c5a4 (the shared epilogue, written out on this path)
                        charge(ctx, 6);
                        ld(ra, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x30);
                        return;
                    }
                L_0014c470:
                    charge(ctx, 12);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                    a2 = 6;
                    lwc1(f12, s1, tw::kX);
                    lwc1(f13, s1, tw::kY);
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x14C490u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
            }
        }
    }
    // 0x0014c5a4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0014C5C0 sub_14C5C0 -- 10072 bytes; frame 0xB0: ra sp+0x90, s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f21 sp+0x14, f20 sp+0x10
// [H_Camp_UpdateNewItemTask] Update of the item screen "H_CampNewItem" (jump table 0x7B6040, 31 states): 0 takes
// camp_item.pak's three sprite files (+176.., copied to 0x833A50); 1 allocates the tweens (+188 x80, +192 / +196 x40)
// and the three lists (items +164, equipment +168, materials +172); 2 fades in over 8 frames; 3 waits for flash 9,
// fills the lists (items 4000..4223 of the hero stock, the equipment list, materials = flags 513..639 as ids
// 5001..5127), the targets (protagonist + party) and the persona slots; 4 is the item list: confirm on a usable item
// (record +4 of sub_170E90 is 0 or 2) -> 9 the persona choice when sub_17BBB0 has bit 4, else the target kind
// sub_17BB40 into +92 (3 = no target; non-zero = everyone, +84 = -2) and 6; cancel -> 5, R1 -> 16 equipment page, L1 ->
// 29 material page, else the list cursor; 5 closes (-1); 6..8 the target choice (sub_13BE50 uses the item; an item
// whose record +8 is 233 used in an explorable floor (K_FldDungeon_IsCurrentFloorExplorable) drops by one, sets flag
// 0x1417 and ends the menu); 9..11 the persona choice (stats raised up to 99); 16..24 the equipment page (sell /
// discard with message 6 when equipped); 25..30 the material page. Every state steps and draws its page's tweens
// (sub_145520 / sub_148880 / sub_14C290).
void sub_14C5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0014c5c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    lw(s4, a0, 60);
    lw(v0, s4, item::kRibbonActive);
    if (v0 != 0) {
        // 0x0014c5fc
        charge(ctx, 5);
        a0 = addiu(s4, item::kRibbon);
        jal(ctx, 0x14C600u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
        if (v0 != 0) {
            // 0x0014c610
            charge(ctx, 3);
            lw(a0, s4, item::kRibbonAlpha);
            jal(ctx, 0x14C614u, gen::fn_sub_13BCE0_0013bce0);  // the item ribbon
        }
    }
    // 0x0014c61c
    charge(ctx, 4);
    lw(v0, s4, item::kState);
    at = sltiu(v0, 31);
    if (at != 0) {
        // 0x0014c62c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 24640);  // &0x7B6040
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x14C648u:  // table[0]: state 0: camp_item.pak -> three sprite files
            // 0x0014c648
            charge(ctx, 7);
            v0 = 300;
            sw(v0, gp, g::kItemRibbonX);  // 0x7CDF90
            lw(a0, s4, item::kPak);
            jal(ctx, 0x14C654u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0014c664
                charge(ctx, 32);
                lw(a0, s4, item::kPak);
                a1 = 0;
                a2 = addiu(sp, 0xAC);
                jal(ctx, 0x14C670u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x14C67Cu, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s4, item::kFiles);
                lw(a0, s4, item::kPak);
                a1 = 1;
                a2 = addiu(sp, 0xAC);
                jal(ctx, 0x14C694u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x14C6A0u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s4, item::kFile1);
                lw(a0, s4, item::kPak);
                a1 = 2;
                a2 = addiu(sp, 0xAC);
                jal(ctx, 0x14C6B8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x14C6C4u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s4, item::kFile2);
                a2 = 0;
                v1 = 0x830000;
                v1 = addiu(v1, spr::screen(0));  // &0x833A50: the screen's sprite file 0
                for (;;) {
                    // 0x0014c6fc
                    charge(ctx, 3);
                    v0 = slti(a2, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0014c6e4
                    charge(ctx, 6);
                    a1 = sll(a2, 2);
                    v0 = addu(s4, a1);
                    lw(a0, v0, 176);
                    v0 = addu(v1, a1);
                    sw(a0, v0, 0);
                    a2 = addiu(a2, 1);
                }
                // 0x0014c708
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s4, item::kState);
            }
        L_0014ece0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x14C718u:  // table[1]: state 1: tweens and the three lists
            // 0x0014c718
            charge(ctx, 5);
            lw(a0, s4, item::kFiles);
            jal(ctx, 0x14C71Cu, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x0014c72c
                charge(ctx, 5);
                lw(a0, s4, item::kFile1);
                jal(ctx, 0x14C730u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x0014c740
                    charge(ctx, 5);
                    lw(a0, s4, item::kFile2);
                    jal(ctx, 0x14C744u, gen::fn_sprFileIsReady_00111f30);
                    if (v0 != 0) {
                        // 0x0014c754
                        charge(ctx, 24);
                        a0 = 80;
                        jal(ctx, 0x14C758u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                        sw(v0, s4, item::kTweens);
                        a0 = 40;
                        jal(ctx, 0x14C768u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                        sw(v0, s4, item::kEquipTweens);
                        a0 = 40;
                        jal(ctx, 0x14C778u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                        sw(v0, s4, item::kMaterialTweens);
                        s0 = 0x960000;
                        s0 = addiu(s0, rw::kCallocSlot);  // &0x960184: RwCalloc
                        a0 = 1;
                        a1 = 2424;
                        a2 = 0x40000;
                        lw(v0, s0, 0);  // 0x960184
                        jalr(ctx, 0x14C79Cu, v0.u());
                        a1 = 0;
                        a0 = si(-1);
                        for (;;) {
                            // 0x0014c7c8
                            charge(ctx, 3);
                            v1 = slti(a1, 300);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0014c7b4
                            charge(ctx, 5);
                            v1 = sll(a1, 3);
                            v1 = addu(v0, v1);
                            sw(a0, v1, 12);
                            sw(zero, v1, 16);
                            a1 = addiu(a1, 1);
                        }
                        // 0x0014c7d4
                        charge(ctx, 11);
                        sw(v0, s4, item::kItemList);
                        a0 = 1;
                        a1 = 11632;
                        a2 = 0x40000;
                        lw(v0, s0, 0);
                        jalr(ctx, 0x14C7E8u, v0.u());
                        a1 = 0;
                        a0 = si(-1);
                        for (;;) {
                            // 0x0014c824
                            charge(ctx, 3);
                            v1 = slti(a1, 320);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0014c800
                            charge(ctx, 9);
                            v1 = sll(a1, 3);
                            v1 = addu(v1, a1);
                            v1 = sll(v1, 2);
                            v1 = addu(v0, v1);
                            sw(a0, v1, 100);
                            sw(zero, v1, 108);
                            sw(a0, v1, 104);
                            sw(zero, v1, 112);
                            a1 = addiu(a1, 1);
                        }
                        // 0x0014c830
                        charge(ctx, 11);
                        sw(v0, s4, item::kEquipList);
                        a0 = 1;
                        a1 = 2424;
                        a2 = 0x40000;
                        lw(v0, s0, 0);
                        jalr(ctx, 0x14C844u, v0.u());
                        a1 = 0;
                        a0 = si(-1);
                        for (;;) {
                            // 0x0014c870
                            charge(ctx, 3);
                            v1 = slti(a1, 300);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0014c85c
                            charge(ctx, 5);
                            v1 = sll(a1, 3);
                            v1 = addu(v0, v1);
                            sw(a0, v1, 12);
                            sw(zero, v1, 16);
                            a1 = addiu(a1, 1);
                        }
                        // 0x0014c87c
                        charge(ctx, 5);
                        sw(v0, s4, item::kMaterialList);
                        v0 = 3;
                        sw(v0, s4, item::kState);
                    }
                }
            }
            goto L_0014ece0;
        case 0x14C890u:  // table[2]: state 2: fade in (8 frames)
            // 0x0014c890
            charge(ctx, 4);
            lw(a0, s4, item::kTimer);
            at = slti(a0, 8);
            if (at == 0) {
                // 0x0014cb20
                charge(ctx, 3);
                sw(zero, s4, item::kState);
            } else {
                // 0x0014c8a0
                charge(ctx, 2);
                if (i64(a0) <= 0) {
                    // 0x0014c910
                    charge(ctx, 4);
                    mtc1(zero, f21);
                    mov_s(f20, f21);
                    s0 = 0;
                } else {
                    // 0x0014c8a8
                    charge(ctx, 3);
                    at = slti(a0, 8);
                    if (at != 0) {
                        // 0x0014c8b4
                        charge(ctx, 8);
                        v0 = sll(a0, 4);
                        v1 = subu(v0, a0);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v1 = sll(v0, 2);
                        v0 = sra(v1, 3);
                        if (i64(v1) < 0) {
                            // 0x0014c8d4
                            charge(ctx, 2);
                            v0 = addiu(v1, 7);
                            v0 = sra(v0, 3);
                        }
                        // 0x0014c8dc
                        charge(ctx, 9);
                        mtc1(v0, f0);
                        cvt_s_w(f21, f0);
                        mtc1(zero, f20);
                        v0 = sll(a0, 8);
                        v0 = subu(v0, a0);
                        s0 = sra(v0, 3);
                        if (i64(v0) < 0) {
                            // 0x0014c900
                            charge(ctx, 2);
                            v0 = addiu(v0, 7);
                            s0 = sra(v0, 3);
                        }
                        // 0x0014c908
                        charge(ctx, 2);
                    }
                }
                // 0x0014c920
                charge(ctx, 3);
                lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
                if (v0 != 0) {
                    // 0x0014c938
                    charge(ctx, 5);
                    lw(a0, v0, 60);
                    lw(v1, a0, 0);
                    v0 = 3;
                    if (v1 != v0) {
                        // 0x0014c958
                        charge(ctx, 1);
                        t0 = 0;
                    } else {
                        // 0x0014c94c
                        charge(ctx, 3);
                        lw(t0, a0, 12);
                    }
                } else {
                    // 0x0014c92c
                    charge(ctx, 3);
                    t0 = 0;
                }
                // 0x0014c95c
                charge(ctx, 2);
                if (t0 != 0) {
                    // 0x0014c964
                    charge(ctx, 8);
                    v1 = dsll32(s0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    a1 = v1;
                    v0 = sltiu(v1, 25);
                    if (v0 == 0) {
                        // 0x0014c984
                        charge(ctx, 1);
                        a1 = 25;
                    }
                    // 0x0014c988
                    charge(ctx, 16);
                    v0 = 0x42CC0000;  // 102.0f
                    mtc1(v0, f12);
                    v0 = si(-256);
                    a0 = v1 | v0;
                    v0 = 0x4FA40000;
                    v0 = v0 | 0xFF00;
                    a1 = a1 | v0;
                    v0 = lui(0xC2AE);
                    mtc1(v0, f0);
                    add_s(f14, f0, f20);
                    mov_s(f13, f21);
                    a2 = 640;
                    a3 = a2;
                    jal(ctx, 0x14C9C0u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
                }
                // 0x0014c9c8
                charge(ctx, 13);
                mtc1(zero, f12);
                v0 = 0x42CC0000;  // 102.0f
                mtc1(v0, f14);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                mov_s(f13, f12);
                a1 = 0;
                jal(ctx, 0x14C9E4u, gen::fn_nullsub_3_0011bba0);
                lw(a0, s4, item::kTimer);
                at = slti(a0, 6);
                if (at != 0) {
                    // 0x0014c9fc
                    charge(ctx, 43);
                    v0 = sll(a0, 4);
                    v1 = subu(v0, a0);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 3);
                    v1 = 6;
                    div(v0, v1);
                    mflo(v0);
                    mtc1(v0, f0);
                    cvt_s_w(f21, f0);
                    v0 = sll(a0, 8);
                    v0 = subu(v0, a0);
                    div1(v0, v1);
                    mflo1(s0);
                    a0 = 0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
                    a2 = 0;
                    jal(ctx, 0x14CA48u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                    s1 = v0;
                    v1 = 0x42CA0000;  // 101.0f
                    sw(v1, v0, 44);
                    v1 = 0x43D60000;  // 428.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f21);
                    swc1(f0, v0, 16);
                    v1 = 0x41D80000;  // 27.0f
                    sw(v1, v0, 20);
                    v1 = dsll32(s0, 16);
                    v1 = dsra32(v1, 16);
                    sb(v1, v0, 24);
                    sh(zero, v0, 40);
                    sh(zero, v0, 42);
                    a0 = s1;
                    a1 = 1;
                    jal(ctx, 0x14CA94u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                    a0 = s1;
                    jal(ctx, 0x14CAA0u, gen::fn_sub_115980_00115980);  // draw and release the handle
                }
                // 0x0014caa8
                charge(ctx, 3);
                lw(v0, s4, item::kTimer);
                if (v0 == 0) {
                    // 0x0014cab4
                    charge(ctx, 10);
                    lw(v0, gp, g::kCampRootTask);  // 0x7CDF5C
                    lw(s0, v0, 60);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = s0;
                    jal(ctx, 0x14CAC8u, gen::fn_sub_11DA80_0011da80);  // [H_Camp_RootFadeOut2]
                    v0 = 9;
                    sw(v0, s0, 0);
                    sw(zero, s0, 4);
                }
                // 0x0014cadc
                charge(ctx, 4);
                lw(v1, s4, item::kTimer);
                v0 = 4;
                if (v1 == v0) {
                    // 0x0014caec
                    charge(ctx, 8);
                    lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
                    a1 = 9;
                    jal(ctx, 0x14CAF4u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
                    lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
                    a1 = 9;
                    jal(ctx, 0x14CB04u, gen::fn_sub_122710_00122710);  // [H_Camp_PersonaKaniSetScreen]
                }
                // 0x0014cb0c
                charge(ctx, 5);
                lw(v0, s4, item::kTimer);
                v0 = addiu(v0, 1);
                sw(v0, s4, item::kTimer);
            }
            goto L_0014ece0;
        case 0x14CB2Cu:  // table[3]: state 3: wait for flash 9, fill the lists, targets, personas
            // 0x0014cb2c
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 9;
            jal(ctx, 0x14CB34u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014cb44
                charge(ctx, 5);
                lw(s0, s4, item::kItemList);
                s1 = 0;
                s2 = 4000;
                for (;;) {
                    // 0x0014cba8
                    charge(ctx, 3);
                    v0 = slti(s2, 4224);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0014cb58
                    charge(ctx, 8);
                    a1 = dsll32(s2, 16);
                    a1 = dsra32(a1, 16);
                    a0 = 1;
                    jal(ctx, 0x14CB64u, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
                    v0 = v0 & 0xFFFF;
                    if (v0 != 0) {
                        // 0x0014cb78
                        charge(ctx, 11);
                        v0 = sll(s1, 3);
                        s3 = addu(s0, v0);
                        sw(s2, s3, 12);
                        a1 = dsll32(s2, 16);
                        a1 = dsra32(a1, 16);
                        a0 = 1;
                        jal(ctx, 0x14CB90u, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
                        v0 = v0 & 0xFFFF;
                        sw(v0, s3, 16);
                        s1 = addiu(s1, 1);
                    }
                    // 0x0014cba4
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0014cbb4
                charge(ctx, 10);
                sw(s1, s0, 2412);
                lw(a0, s4, item::kEquipList);
                jal(ctx, 0x14CBBCu, gen::fn_sub_13CC90_0013cc90);  // build the equipment list
                lw(s0, s4, item::kMaterialList);
                s2 = 0;
                s1 = 5001;
                s3 = s1;
                for (;;) {
                    // 0x0014cc10
                    charge(ctx, 3);
                    v0 = slti(s3, 5128);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0014cbdc
                    charge(ctx, 5);
                    a0 = addiu(s3, -4488);
                    jal(ctx, 0x14CBE0u, gen::fn_datGetFlag_0016f190);
                    if (v0 != 0) {
                        // 0x0014cbf0
                        charge(ctx, 6);
                        v0 = sll(s2, 3);
                        v1 = addu(s0, v0);
                        sw(s1, v1, 12);
                        v0 = 1;
                        sw(v0, v1, 16);
                        s2 = addiu(s2, 1);
                    }
                    // 0x0014cc08
                    charge(ctx, 2);
                    s1 = addiu(s1, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x0014cc1c
                charge(ctx, 7);
                sw(s2, s0, 2412);
                v0 = 1;
                sw(v0, s4, item::kTargets);
                sw(v0, s4, item::kTargetCount);
                s0 = 0;
                for (;;) {
                    // 0x0014cc88
                    charge(ctx, 3);
                    v0 = slti(s0, 3);
                    if (v0 != 0) {
                        backedge(ctx);
                        // 0x0014cc38
                        charge(ctx, 7);
                        a0 = s0;
                        jal(ctx, 0x14CC3Cu, gen::fn_sub_16DD60_0016dd60);  // [datGetPartyMember]
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        if (v0 != 0) {
                            // 0x0014cc54
                            charge(ctx, 13);
                            a0 = s0;
                            jal(ctx, 0x14CC58u, gen::fn_sub_16DD60_0016dd60);  // [datGetPartyMember]
                            v1 = dsll32(v0, 16);
                            v1 = dsra32(v1, 16);
                            lw(v0, s4, item::kTargetCount);
                            v0 = sll(v0, 2);
                            v0 = addu(s4, v0);
                            sw(v1, v0, 12);
                            lw(v0, s4, item::kTargetCount);
                            v0 = addiu(v0, 1);
                            sw(v0, s4, item::kTargetCount);
                            s0 = addiu(s0, 1);
                            continue;
                        }
                    }
                    break;
                }
                // 0x0014cc94
                charge(ctx, 4);
                sw(zero, s4, item::kPersonaCount);
                s0 = 0;
                for (;;) {
                    // 0x0014ccd8
                    charge(ctx, 3);
                    v0 = slti(s0, 12);
                    if (v0 != 0) {
                        backedge(ctx);
                        // 0x0014cca4
                        charge(ctx, 6);
                        a0 = dsll32(s0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x14CCACu, gen::fn_sub_174960_00174960);  // [datPersonaIsSlotUsed]
                        if (v0 != 0) {
                            // 0x0014ccbc
                            charge(ctx, 7);
                            v0 = sll(s0, 2);
                            v0 = addu(s4, v0);
                            sw(s0, v0, 32);
                            lw(v0, s4, item::kPersonaCount);
                            v0 = addiu(v0, 1);
                            sw(v0, s4, item::kPersonaCount);
                            s0 = addiu(s0, 1);
                            continue;
                        }
                    }
                    break;
                }
                // 0x0014cce4
                charge(ctx, 25);
                a0 = s4;
                jal(ctx, 0x14CCE8u, gen::fn_sub_141660_00141660);
                sw(zero, sp, 0xA0);
                sw(zero, sp, 0xA4);
                v0 = 3;
                sd(v0, sp, 0x0);
                v0 = 13;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(s4, item::kRibbon);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xA0);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x14CD30u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 4;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14CD48u:  // table[4]: state 4: the item list (input)
            // 0x0014cd48
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x0014cdcc
                charge(ctx, 3);
                v0 = slti(s2, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014cd58
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s0 = sll(v0, 2);
                a0 = addu(v1, s0);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014cd78
                    charge(ctx, 4);
                    jal(ctx, 0x14CD78u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014cd88
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s0);
                        a1 = s2;
                        a2 = s4;
                        jal(ctx, 0x14CD98u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                    // 0x0014cda0
                    charge(ctx, 9);
                    lw(v1, s4, item::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014cdc4
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x0014cdc8
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0014cdd8
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0014cde0
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v1 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x0014ceec
                    charge(ctx, 3);
                    v0 = v1 & 0x20;
                    if (v0 == 0) {
                        // 0x0014cf70
                        charge(ctx, 6);
                        a0 = 1;
                        v0 = 0x7E0000;
                        lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                        v0 = v1 & 0x2000;  // next page
                        if (v0 == 0) {
                            // 0x0014cf88
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x2000;  // next page
                            if (v0 == 0) {
                                // 0x0014cf9c
                                charge(ctx, 1);
                                a0 = 0;
                            }
                        }
                        // 0x0014cfa0
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0014cfb8
                            charge(ctx, 4);
                            v0 = v1 & 0x8000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x0014cfc8
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x8000;  // previous page
                                v0 = sltu(0, v0);
                            }
                            // 0x0014cfd8
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x0014cff0
                                charge(ctx, 9);
                                lw(v0, s4, item::kItemList);
                                lw(a0, v0, 2412);
                                a1 = 5;
                                a2 = addiu(v0, 2420);
                                a3 = addiu(v0, 2416);
                                jal(ctx, 0x14D004u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                            } else {
                                // 0x0014cfe0
                                charge(ctx, 4);
                                v0 = 29;
                                sw(v0, s4, item::kState);
                            }
                        } else {
                            // 0x0014cfa8
                            charge(ctx, 4);
                            v0 = 16;
                            sw(v0, s4, item::kState);
                        }
                    } else {
                        // 0x0014cef8
                        charge(ctx, 30);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x14CF08u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        sw(zero, sp, 0xA0);
                        sw(zero, sp, 0xA4);
                        sd(zero, sp, 0x0);
                        v0 = 10;
                        sd(v0, sp, 0x8);
                        v0 = 0x42C80000;  // 100.0f
                        mtc1(v0, f12);
                        a0 = addiu(s4, item::kRibbon);
                        a1 = 0;
                        a2 = 2;
                        a3 = a2;
                        ld(t0, sp, 0xA0);
                        t1 = t0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x14CF4Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                        a0 = s4;
                        jal(ctx, 0x14CF58u, gen::fn_sub_1432F0_001432f0);
                        v0 = 5;
                        sw(v0, s4, item::kState);
                    }
                } else {
                    // 0x0014cdf4
                    charge(ctx, 6);
                    lw(a0, s4, item::kItemList);
                    lw(v1, a0, 2416);
                    lw(v0, a0, 2412);
                    at = slt(v1, v0);
                    if (at != 0) {
                        // 0x0014ce0c
                        charge(ctx, 14);
                        lw(v0, a0, 2420);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 3);
                        v0 = addu(v0, a0);
                        lw(v0, v0, 12);
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        sh(v0, gp, g::kItemSelected);  // 0x7CDF94
                        jal(ctx, 0x14CE2Cu, gen::fn_sub_170E90_00170e90);  // the item record (section 6)
                        s0 = v0;
                        lw(v1, v0, 4);
                        if (v1 != 0) {
                            // 0x0014ce44
                            charge(ctx, 3);
                            v0 = 2;
                            if (v1 == v0) {
                                goto L_0014ce50;
                            }
                            // 0x0014cecc
                            charge(ctx, 8);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 8;
                            jal(ctx, 0x14CEDCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            goto L_0014ece0;
                        }
                    L_0014ce50:
                        charge(ctx, 7);
                        lhu(a0, s0, 8);
                        jal(ctx, 0x14CE54u, gen::fn_sub_17BBB0_0017bbb0);
                        v0 = v0 & 0xFFFF;
                        v0 = v0 & 0x4;
                        if (v0 == 0) {
                            // 0x0014ce80
                            charge(ctx, 8);
                            lhu(a0, s0, 8);
                            jal(ctx, 0x14CE84u, gen::fn_sub_17BB40_0017bb40);
                            sh(v0, s4, item::kTargetKind);
                            lhu(v1, s4, item::kTargetKind);
                            v0 = 3;
                            if (v1 != v0) {
                                // 0x0014cea0
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    // 0x0014ceb4
                                    charge(ctx, 2);
                                    v0 = si(-2);
                                    sw(v0, s4, item::kTargetCursor);
                                } else {
                                    // 0x0014cea8
                                    charge(ctx, 3);
                                    sw(zero, s4, item::kTargetCursor);
                                }
                                // 0x0014cebc
                                charge(ctx, 4);
                                v0 = 6;
                                sw(v0, s4, item::kState);
                            }
                        } else {
                            // 0x0014ce6c
                            charge(ctx, 5);
                            sw(zero, s4, item::kPersonaCursor);
                            v0 = 9;
                            sw(v0, s4, item::kState);
                        }
                    }
                }
            }
            goto L_0014ece0;
        case 0x14D014u:  // table[5]: state 5: slide out, done (-1)
            // 0x0014d014
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014d098
                charge(ctx, 3);
                v0 = slti(s1, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014d024
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014d044
                    charge(ctx, 4);
                    jal(ctx, 0x14D044u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014d054
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14D064u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                    // 0x0014d06c
                    charge(ctx, 9);
                    lw(v1, s4, item::kTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014d090
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014d094
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014d0a4
            charge(ctx, 2);
            if (s0 == 0) {
                goto L_0014ece0;
            }
            // 0x0014d0ac
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x14D0B8u:  // table[6]: state 6: wait for flash 10, open the target choice
            // 0x0014d0b8
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014d110
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014d0c4
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014d0e4
                    charge(ctx, 4);
                    jal(ctx, 0x14D0E4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014d0f4
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14D104u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014d10c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014d11c
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 10;
            jal(ctx, 0x14D124u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014d134
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14D138u, gen::fn_sub_141FB0_00141fb0);
                v0 = 7;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14D150u:  // table[7]: state 7: the target choice (input; use the item)
            // 0x0014d150
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014d1d4
                charge(ctx, 3);
                v0 = slti(s1, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014d160
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014d180
                    charge(ctx, 4);
                    jal(ctx, 0x14D180u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014d190
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14D1A0u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                    // 0x0014d1a8
                    charge(ctx, 9);
                    lw(v1, s4, item::kTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014d1cc
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014d1d0
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014d1e0
            charge(ctx, 2);
            if (s0 == 0) {
                goto L_0014ece0;
            }
            // 0x0014d1e8
            charge(ctx, 6);
            lw(s0, s4, item::kTargetCursor);
            v0 = 0x7E0000;
            lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
            v0 = a0 & 0x40;  // confirm
            if (v0 == 0) {
                // 0x0014d3b8
                charge(ctx, 3);
                v0 = a0 & 0x20;
                if (v0 == 0) {
                    // 0x0014d3ec
                    charge(ctx, 6);
                    a1 = 1;
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                    v0 = v1 & 0x1000;  // cursor - 1
                    if (v0 == 0) {
                        // 0x0014d404
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                        v0 = v0 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x0014d418
                            charge(ctx, 1);
                            a1 = 0;
                        }
                    }
                    // 0x0014d41c
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x0014d480
                        charge(ctx, 4);
                        v0 = v1 & 0x4000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x0014d490
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x4000;  // cursor + 1
                            v0 = sltu(0, v0);
                        }
                        // 0x0014d4a0
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x0014d4a8
                            charge(ctx, 3);
                            v0 = si(-2);
                            if (s0 != v0) {
                                // 0x0014d4b4
                                charge(ctx, 4);
                                lw(v0, s4, item::kTargetCount);
                                v0 = addiu(v0, -1);
                                if (s0 == v0) {
                                    // 0x0014d4d8
                                    charge(ctx, 3);
                                    v0 = a0 & 0x4000;
                                    if (v0 == 0) {
                                        // 0x0014d4e4
                                        charge(ctx, 5);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        if (v0 != 0) {
                                            goto L_0014d4f8;
                                        }
                                        goto L_0014d4fc;
                                    }
                                L_0014d4f8:
                                    charge(ctx, 1);
                                    sw(zero, s4, item::kTargetCursor);
                                } else {
                                    // 0x0014d4c4
                                    charge(ctx, 5);
                                    lw(v0, s4, item::kTargetCursor);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s4, item::kTargetCursor);
                                }
                            }
                        }
                    } else {
                        // 0x0014d424
                        charge(ctx, 3);
                        v0 = si(-2);
                        if (s0 != v0) {
                            // 0x0014d430
                            charge(ctx, 2);
                            if (s0 == 0) {
                                // 0x0014d44c
                                charge(ctx, 3);
                                v0 = a0 & 0x1000;
                                if (v0 == 0) {
                                    // 0x0014d458
                                    charge(ctx, 5);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x1000;  // cursor - 1
                                    if (v0 != 0) {
                                        goto L_0014d46c;
                                    }
                                    goto L_0014d4fc;
                                }
                            L_0014d46c:
                                charge(ctx, 5);
                                lw(v0, s4, item::kTargetCount);
                                v0 = addiu(v0, -1);
                                sw(v0, s4, item::kTargetCursor);
                            } else {
                                // 0x0014d438
                                charge(ctx, 5);
                                lw(v0, s4, item::kTargetCursor);
                                v0 = addiu(v0, -1);
                                sw(v0, s4, item::kTargetCursor);
                            }
                        }
                    }
                } else {
                    // 0x0014d3c4
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x14D3D4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 8;
                    sw(v0, s4, item::kState);
                }
            L_0014d4fc:
                charge(ctx, 3);
                lw(v0, s4, item::kTargetCursor);
                if (s0 != v0) {
                    // 0x0014d508
                    charge(ctx, 12);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x14D518u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    a0 = s4;
                    a1 = s0;
                    jal(ctx, 0x14D528u, gen::fn_sub_143A00_00143a00);
                }
                goto L_0014ece0;
            }
            // 0x0014d200
            charge(ctx, 13);
            lw(a0, s4, item::kItemList);
            lw(v1, a0, 2416);
            lw(v0, a0, 2420);
            v0 = addu(v1, v0);
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            lh(a0, v0, 12);
            jal(ctx, 0x14D21Cu, gen::fn_sub_170E90_00170e90);  // the item record (section 6)
            lw(v1, v0, 8);
            v0 = 233;
            if (v1 != v0) {
                // 0x0014d2ec
                charge(ctx, 3);
                lhu(v0, s4, item::kTargetKind);
                if (v0 != 0) {
                    // 0x0014d358
                    charge(ctx, 6);
                    lw(a0, s4, item::kItemList);
                    lw(a1, s4, item::kTargetCursor);
                    jal(ctx, 0x14D360u, gen::fn_sub_13BE50_0013be50);  // [H_Camp_ItemUseOnTarget]
                    if (v0 == 0) {
                        // 0x0014d398
                        charge(ctx, 8);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 8;
                        jal(ctx, 0x14D3A8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    } else {
                        // 0x0014d370
                        charge(ctx, 10);
                        a0 = 1;
                        a1 = 0;
                        a2 = 3;
                        a3 = a0;
                        jal(ctx, 0x14D380u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 8;
                        sw(v0, s4, item::kState);
                    }
                } else {
                    // 0x0014d2f8
                    charge(ctx, 6);
                    lw(a0, s4, item::kItemList);
                    lw(a1, s4, item::kTargetCursor);
                    jal(ctx, 0x14D300u, gen::fn_sub_13BE50_0013be50);  // [H_Camp_ItemUseOnTarget]
                    if (v0 == 0) {
                        // 0x0014d338
                        charge(ctx, 8);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 8;
                        jal(ctx, 0x14D348u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    } else {
                        // 0x0014d310
                        charge(ctx, 10);
                        a0 = 1;
                        a1 = 0;
                        a2 = 3;
                        a3 = a0;
                        jal(ctx, 0x14D320u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 8;
                        sw(v0, s4, item::kState);
                    }
                }
                goto L_0014d4fc;
            }
            // 0x0014d234
            charge(ctx, 4);
            jal(ctx, 0x14D234u, gen::fn_K_FldDungeon_IsCurrentFloorExplorable_001bff50);
            if (v0 == 0) {
                // 0x0014d2cc
                charge(ctx, 8);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 8;
                jal(ctx, 0x14D2DCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                goto L_0014d4fc;
            }
            // 0x0014d244
            charge(ctx, 34);
            lw(a0, s4, item::kItemList);
            lw(v1, a0, 2416);
            lw(v0, a0, 2420);
            v0 = addu(v1, v0);
            v0 = sll(v0, 3);
            v0 = addu(v0, a0);
            lh(s0, v0, 12);
            a0 = 1;
            a1 = s0;
            jal(ctx, 0x14D268u, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            v0 = addiu(v0, -1);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            a2 = v0 & 0xFFFF;
            a0 = 1;
            a1 = s0;
            jal(ctx, 0x14D290u, gen::fn_sub_170860_00170860);  // [datSetItemNum] (owner, id, count)
            a0 = 5143;
            a1 = 1;
            jal(ctx, 0x14D2A0u, gen::fn_datSetFlag_0016f1f0);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 1;
            jal(ctx, 0x14D2B8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
            v0 = si(-1);
            break;
        case 0x14D538u:  // table[8]: state 8: wait for flash 9, back to the list
            // 0x0014d538
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014d590
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014d544
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014d564
                    charge(ctx, 4);
                    jal(ctx, 0x14D564u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014d574
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14D584u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014d58c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014d59c
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 9;
            jal(ctx, 0x14D5A4u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014d5b4
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14D5B8u, gen::fn_sub_142930_00142930);
                v0 = 4;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14D5D0u:  // table[9]: state 9: wait for flash 10, open the persona choice
            // 0x0014d5d0
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014d628
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014d5dc
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014d5fc
                    charge(ctx, 4);
                    jal(ctx, 0x14D5FCu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014d60c
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14D61Cu, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014d624
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014d634
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 10;
            jal(ctx, 0x14D63Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014d64c
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14D650u, gen::fn_sub_143EE0_00143ee0);
                v0 = 10;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14D668u:  // table[10]: state 10: the persona choice (input; raise the stats up to 99)
            // 0x0014d668
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x0014d6ec
                charge(ctx, 3);
                v0 = slti(s2, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014d678
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s0 = sll(v0, 2);
                a0 = addu(v1, s0);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014d698
                    charge(ctx, 4);
                    jal(ctx, 0x14D698u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014d6a8
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s0);
                        a1 = s2;
                        a2 = s4;
                        jal(ctx, 0x14D6B8u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                    // 0x0014d6c0
                    charge(ctx, 9);
                    lw(v1, s4, item::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014d6e4
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x0014d6e8
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0014d6f8
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0014d700
                charge(ctx, 6);
                lw(s1, s4, item::kPersonaCursor);
                v0 = 0x7E0000;
                lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a0 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x0014d95c
                    charge(ctx, 3);
                    v0 = a0 & 0x20;
                    if (v0 == 0) {
                        // 0x0014d990
                        charge(ctx, 6);
                        a1 = 1;
                        v0 = 0x7E0000;
                        lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                        v0 = v1 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x0014d9a8
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x1000;  // cursor - 1
                            if (v0 == 0) {
                                // 0x0014d9bc
                                charge(ctx, 1);
                                a1 = 0;
                            }
                        }
                        // 0x0014d9c0
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x0014da20
                            charge(ctx, 4);
                            v0 = v1 & 0x4000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x0014da30
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x4000;  // cursor + 1
                                v0 = sltu(0, v0);
                            }
                            // 0x0014da40
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x0014da48
                                charge(ctx, 4);
                                lw(v0, s4, item::kPersonaCount);
                                v0 = addiu(v0, -1);
                                if (s1 == v0) {
                                    // 0x0014da6c
                                    charge(ctx, 4);
                                    v0 = a0 & 0x4000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0014da7c
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0014da8c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0014da94
                                        charge(ctx, 1);
                                        sw(zero, s4, item::kPersonaCursor);
                                    }
                                } else {
                                    // 0x0014da58
                                    charge(ctx, 5);
                                    lw(v0, s4, item::kPersonaCursor);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s4, item::kPersonaCursor);
                                }
                            }
                        } else {
                            // 0x0014d9c8
                            charge(ctx, 2);
                            if (s1 == 0) {
                                // 0x0014d9e4
                                charge(ctx, 4);
                                v0 = a0 & 0x1000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x0014d9f4
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x1000;  // cursor - 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x0014da04
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0014da0c
                                    charge(ctx, 5);
                                    lw(v0, s4, item::kPersonaCount);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s4, item::kPersonaCursor);
                                }
                            } else {
                                // 0x0014d9d0
                                charge(ctx, 5);
                                lw(v0, s4, item::kPersonaCursor);
                                v0 = addiu(v0, -1);
                                sw(v0, s4, item::kPersonaCursor);
                            }
                        }
                    } else {
                        // 0x0014d968
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x14D978u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 11;
                        sw(v0, s4, item::kState);
                    }
                } else {
                    // 0x0014d718
                    charge(ctx, 14);
                    lh(a0, gp, g::kItemSelected);  // 0x7CDF94
                    jal(ctx, 0x14D71Cu, gen::fn_sub_170E90_00170e90);  // the item record (section 6)
                    s6 = v0;
                    lh(a0, s4, item::kPersonaCursor);
                    jal(ctx, 0x14D72Cu, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
                    s5 = v0;
                    s3 = 0;
                    lhu(a0, s6, 8);
                    jal(ctx, 0x14D740u, gen::fn_sub_17BF70_0017bf70);
                    if (v0 != 0) {
                        // 0x0014d750
                        charge(ctx, 3);
                        s0 = 0;
                        for (;;) {
                            // 0x0014d7cc
                            charge(ctx, 3);
                            v0 = slti(s0, 5);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0014d75c
                            charge(ctx, 7);
                            lhu(a0, s6, 8);
                            a1 = s0 & 0xFF;
                            jal(ctx, 0x14D764u, gen::fn_sub_17BFA0_0017bfa0);
                            s2 = v0 & 0xFF;
                            if (s2 != 0) {
                                // 0x0014d778
                                charge(ctx, 8);
                                a1 = s0 & 0xFFFF;
                                a0 = s5;
                                jal(ctx, 0x14D780u, gen::fn_sub_173580_00173580);  // (persona, stat): the stat without the bonus
                                v1 = v0 & 0xFF;
                                v0 = 99;
                                if (v1 != v0) {
                                    // 0x0014d798
                                    charge(ctx, 4);
                                    v0 = addu(v1, s2);
                                    at = slti(v0, 100);
                                    if (at == 0) {
                                        // 0x0014d7a8
                                        charge(ctx, 2);
                                        v0 = addiu(v1, -99);
                                        s2 = addu(s2, v0);
                                    }
                                    // 0x0014d7b0
                                    charge(ctx, 6);
                                    a0 = addu(s5, s0);
                                    v1 = s2 & 0xFF;
                                    lbu(v0, a0, 33);
                                    v0 = addu(v0, v1);
                                    sb(v0, a0, 33);
                                    s3 = 1;
                                }
                            }
                            // 0x0014d7c8
                            charge(ctx, 1);
                            s0 = addiu(s0, 1);
                        }
                        // 0x0014d7d8
                        charge(ctx, 2);
                        if (s3 != 0) {
                            // 0x0014d7e0
                            charge(ctx, 11);
                            lw(s0, s4, item::kItemList);
                            lw(v1, s0, 2416);
                            lw(v0, s0, 2420);
                            s2 = addu(v1, v0);
                            v0 = sll(s2, 3);
                            v0 = addu(v0, s0);
                            v1 = addiu(v0, 16);
                            lw(v0, v0, 16);
                            a0 = 1;
                            if (v0 != a0) {
                                // 0x0014d8f4
                                charge(ctx, 6);
                                v0 = addiu(v0, -1);
                                sw(v0, v1, 0);
                                lhu(a2, v1, 0);
                                lh(a1, gp, g::kItemSelected);  // 0x7CDF94
                                jal(ctx, 0x14D904u, gen::fn_sub_170860_00170860);  // [datSetItemNum] (owner, id, count)
                            } else {
                                // 0x0014d80c
                                charge(ctx, 6);
                                lh(a1, gp, g::kItemSelected);  // 0x7CDF94
                                a2 = 0;
                                jal(ctx, 0x14D814u, gen::fn_sub_170860_00170860);  // [datSetItemNum] (owner, id, count)
                                for (;;) {
                                    // 0x0014d840
                                    charge(ctx, 5);
                                    lw(a0, s0, 2412);
                                    v0 = addiu(a0, -1);
                                    v0 = slt(s2, v0);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0014d824
                                    charge(ctx, 7);
                                    v0 = sll(s2, 3);
                                    v0 = addu(s0, v0);
                                    lwc1(f1, v0, 20);
                                    lwc1(f0, v0, 24);
                                    swc1(f1, v0, 12);
                                    swc1(f0, v0, 16);
                                    s2 = addiu(s2, 1);
                                }
                                // 0x0014d854
                                charge(ctx, 13);
                                v1 = si(-1);
                                v0 = sll(a0, 3);
                                v0 = addu(v0, s0);
                                sw(v1, v0, 12);
                                lw(v0, s0, 2412);
                                v0 = sll(v0, 3);
                                v0 = addu(v0, s0);
                                sw(zero, v0, 16);
                                lw(v0, s0, 2412);
                                v1 = addiu(v0, -1);
                                sw(v1, s0, 2412);
                                if (v1 != 0) {
                                    // 0x0014d898
                                    charge(ctx, 4);
                                    lw(v0, s0, 2416);
                                    v0 = slt(v0, v1);
                                    if (v0 != 0) {
                                        // 0x0014d8bc
                                        charge(ctx, 3);
                                        at = slti(v1, 5);
                                        if (at == 0) {
                                            // 0x0014d8d4
                                            charge(ctx, 5);
                                            v1 = addiu(v1, -5);
                                            lw(v0, s0, 2420);
                                            at = slt(v1, v0);
                                            if (at != 0) {
                                                // 0x0014d8e8
                                                charge(ctx, 3);
                                                sw(v1, s0, 2420);
                                            }
                                        } else {
                                            // 0x0014d8c8
                                            charge(ctx, 3);
                                            sw(zero, s0, 2420);
                                        }
                                    } else {
                                        // 0x0014d8a8
                                        charge(ctx, 5);
                                        v0 = addiu(v1, -1);
                                        sw(v0, s0, 2416);
                                        sw(zero, s0, 2420);
                                    }
                                } else {
                                    // 0x0014d888
                                    charge(ctx, 4);
                                    sw(zero, s0, 2420);
                                    sw(zero, s0, 2416);
                                }
                            }
                        }
                    }
                    // 0x0014d90c
                    charge(ctx, 2);
                    if (s3 == 0) {
                        // 0x0014d93c
                        charge(ctx, 8);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 8;
                        jal(ctx, 0x14D94Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    } else {
                        // 0x0014d914
                        charge(ctx, 10);
                        a0 = 1;
                        a1 = 0;
                        a2 = 3;
                        a3 = a0;
                        jal(ctx, 0x14D924u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 11;
                        sw(v0, s4, item::kState);
                    }
                }
                // 0x0014da98
                charge(ctx, 3);
                lw(v0, s4, item::kPersonaCursor);
                if (v0 != s1) {
                    // 0x0014daa4
                    charge(ctx, 12);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x14DAB4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    a0 = s4;
                    a1 = s1;
                    jal(ctx, 0x14DAC4u, gen::fn_sub_145350_00145350);
                }
            }
            goto L_0014ece0;
        case 0x14DAD4u:  // table[11]: state 11: wait for flash 9, back
            // 0x0014dad4
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014db2c
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014dae0
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014db00
                    charge(ctx, 4);
                    jal(ctx, 0x14DB00u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014db10
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14DB20u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014db28
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014db38
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 9;
            jal(ctx, 0x14DB40u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014db50
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14DB54u, gen::fn_sub_144910_00144910);
                v0 = 4;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14DB6Cu:  // table[12]: state 12: item page -> equipment page
            // 0x0014db6c
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014dbc4
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014db78
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014db98
                    charge(ctx, 4);
                    jal(ctx, 0x14DB98u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014dba8
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14DBB8u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014dbc0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014dbd0
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 9;
            jal(ctx, 0x14DBD8u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014dbe8
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14DBECu, gen::fn_sub_1474F0_001474f0);
                v0 = 13;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14DC04u:  // table[13]: state 13: equipment page arrived
            // 0x0014dc04
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014dc88
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014dc14
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014dc34
                    charge(ctx, 4);
                    jal(ctx, 0x14DC34u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014dc44
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14DC54u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                    // 0x0014dc5c
                    charge(ctx, 9);
                    lw(v1, s4, item::kEquipTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014dc80
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014dc84
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014dc94
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014dc9c
                charge(ctx, 2);
                v0 = 4;
                sw(v0, s4, item::kState);
            }
            // 0x0014dca4
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014dcfc
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014dcb0
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014dcd0
                    charge(ctx, 4);
                    jal(ctx, 0x14DCD0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014dce0
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14DCF0u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014dcf8
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014dd08
            charge(ctx, 2);
            goto L_0014ece0;
        case 0x14DD10u:  // table[14]: state 14: item page -> material page
            // 0x0014dd10
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014dd68
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014dd1c
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014dd3c
                    charge(ctx, 4);
                    jal(ctx, 0x14DD3Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014dd4c
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14DD5Cu, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                }
                // 0x0014dd64
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014dd74
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 9;
            jal(ctx, 0x14DD7Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014dd8c
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14DD90u, gen::fn_sub_1496F0_001496f0);
                v0 = 15;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14DDA8u:  // table[15]: state 15: material page arrived
            // 0x0014dda8
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014de2c
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014ddb8
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014ddd8
                    charge(ctx, 4);
                    jal(ctx, 0x14DDD8u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014dde8
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14DDF8u, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                    // 0x0014de00
                    charge(ctx, 9);
                    lw(v1, s4, item::kMaterialTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014de24
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014de28
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014de38
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014de40
                charge(ctx, 2);
                v0 = 4;
                sw(v0, s4, item::kState);
            }
            // 0x0014de48
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014dea0
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014de54
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014de74
                    charge(ctx, 4);
                    jal(ctx, 0x14DE74u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014de84
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14DE94u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014de9c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014deac
            charge(ctx, 2);
            goto L_0014ece0;
        case 0x14DEB4u:  // table[16]: state 16: wait for flash 11, the equipment page in
            // 0x0014deb4
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014df0c
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014dec0
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014dee0
                    charge(ctx, 4);
                    jal(ctx, 0x14DEE0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014def0
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14DF00u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014df08
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014df18
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 11;
            jal(ctx, 0x14DF20u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014df30
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14DF34u, gen::fn_sub_146710_00146710);
                v0 = 17;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14DF4Cu:  // table[17]: state 17: equipment page arrived
            // 0x0014df4c
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014dfd0
                charge(ctx, 3);
                v0 = slti(s1, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014df5c
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014df7c
                    charge(ctx, 4);
                    jal(ctx, 0x14DF7Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014df8c
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14DF9Cu, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                    // 0x0014dfa4
                    charge(ctx, 9);
                    lw(v1, s4, item::kTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014dfc8
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014dfcc
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014dfdc
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014dfe4
                charge(ctx, 2);
                v0 = 18;
                sw(v0, s4, item::kState);
            }
            // 0x0014dfec
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e044
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014dff8
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e018
                    charge(ctx, 4);
                    jal(ctx, 0x14E018u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e028
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E038u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014e040
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e050
            charge(ctx, 2);
            goto L_0014ece0;
        case 0x14E058u:  // table[18]: state 18: the equipment list (input)
            // 0x0014e058
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014e0dc
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e068
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e088
                    charge(ctx, 4);
                    jal(ctx, 0x14E088u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e098
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14E0A8u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                    // 0x0014e0b0
                    charge(ctx, 9);
                    lw(v1, s4, item::kEquipTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014e0d4
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014e0d8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014e0e8
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014e0f0
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v0 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x0014e17c
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                    v0 = v1 & 0x80;  // the third button
                    if (v0 == 0) {
                        // 0x0014e1b8
                        charge(ctx, 4);
                        v0 = v1 & 0x8000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x0014e1c8
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x8000;  // previous page
                            v0 = sltu(0, v0);
                        }
                        // 0x0014e1d8
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x0014e1f0
                            charge(ctx, 4);
                            v0 = v1 & 0x2000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x0014e200
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x2000;  // next page
                                v0 = sltu(0, v0);
                            }
                            // 0x0014e210
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x0014e228
                                charge(ctx, 9);
                                lw(v0, s4, item::kEquipList);
                                lw(a0, v0, 11620);
                                a1 = 5;
                                a2 = addiu(v0, 11628);
                                a3 = addiu(v0, 11624);
                                jal(ctx, 0x14E23Cu, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                            } else {
                                // 0x0014e218
                                charge(ctx, 4);
                                v0 = 25;
                                sw(v0, s4, item::kState);
                            }
                        } else {
                            // 0x0014e1e0
                            charge(ctx, 4);
                            v0 = 12;
                            sw(v0, s4, item::kState);
                        }
                    } else {
                        // 0x0014e190
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x14E1A0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 22;
                        sw(v0, s4, item::kState);
                    }
                } else {
                    // 0x0014e104
                    charge(ctx, 30);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x14E114u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    sw(zero, sp, 0xA0);
                    sw(zero, sp, 0xA4);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = addiu(s4, item::kRibbon);
                    a1 = 0;
                    a2 = 2;
                    a3 = a2;
                    ld(t0, sp, 0xA0);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x14E158u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    a0 = s4;
                    jal(ctx, 0x14E164u, gen::fn_sub_1482F0_001482f0);
                    v0 = 19;
                    sw(v0, s4, item::kState);
                }
            }
            goto L_0014ece0;
        case 0x14E24Cu:  // table[22]: state 22: discard: message 6 when equipped
            // 0x0014e24c
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e2a4
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e258
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e278
                    charge(ctx, 4);
                    jal(ctx, 0x14E278u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e288
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E298u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014e2a0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e2b0
            charge(ctx, 17);
            lw(a0, s4, item::kEquipList);
            lw(v1, a0, 11628);
            lw(v0, a0, 11624);
            v1 = addu(v1, v0);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            lw(s0, v0, 104);
            a0 = 1;
            a1 = 0;
            jal(ctx, 0x14E2DCu, gen::fn_datGetEquipmentIdx_0016cb80);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (s0 != v0) {
                // 0x0014e2f4
                charge(ctx, 8);
                a0 = 1;
                a1 = a0;
                jal(ctx, 0x14E2FCu, gen::fn_datGetEquipmentIdx_0016cb80);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (s0 == v0) {
                    goto L_0014e354;
                }
                // 0x0014e314
                charge(ctx, 8);
                a0 = 1;
                a1 = 2;
                jal(ctx, 0x14E31Cu, gen::fn_datGetEquipmentIdx_0016cb80);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (s0 == v0) {
                    goto L_0014e354;
                }
                // 0x0014e334
                charge(ctx, 8);
                a0 = 1;
                a1 = 3;
                jal(ctx, 0x14E33Cu, gen::fn_datGetEquipmentIdx_0016cb80);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (s0 == v0) {
                    goto L_0014e354;
                }
                // 0x0014e370
                charge(ctx, 13);
                a0 = 5;
                jal(ctx, 0x14E374u, gen::fn_msgWinRequestMessage_003c7430);
                a0 = 0;
                jal(ctx, 0x14E380u, gen::fn_sub_3C74E0_003c74e0);
                a0 = 0;
                jal(ctx, 0x14E38Cu, gen::fn_msgWinSetType_003c7560);
                v0 = 24;
                sw(v0, s4, item::kState);
                goto L_0014ece0;
            }
        L_0014e354:
            charge(ctx, 7);
            a0 = 6;
            jal(ctx, 0x14E358u, gen::fn_msgWinRequestMessage_003c7430);
            v0 = 23;
            sw(v0, s4, item::kState);
            goto L_0014ece0;
        case 0x14E3A4u:  // table[23]: state 23: wait for the message
            // 0x0014e3a4
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e3fc
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e3b0
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e3d0
                    charge(ctx, 4);
                    jal(ctx, 0x14E3D0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e3e0
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E3F0u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014e3f8
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e408
            charge(ctx, 4);
            jal(ctx, 0x14E408u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x0014e418
                charge(ctx, 6);
                jal(ctx, 0x14E418u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 18;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14E430u:  // table[24]: state 24: the answer
            // 0x0014e430
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e488
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e43c
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e45c
                    charge(ctx, 4);
                    jal(ctx, 0x14E45Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e46c
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E47Cu, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014e484
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e494
            charge(ctx, 4);
            jal(ctx, 0x14E494u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x0014e4a4
                charge(ctx, 5);
                jal(ctx, 0x14E4A4u, gen::fn_msgWinLastSelection_003c7610);
                v1 = 1;
                if (v0 != v1) {
                    // 0x0014e4b8
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x0014e4c8
                        charge(ctx, 3);
                        lw(a0, s4, item::kEquipList);
                        jal(ctx, 0x14E4CCu, gen::fn_sub_141590_00141590);  // rebuild the list after a stock change
                    } else {
                        // 0x0014e4c0
                        charge(ctx, 2);
                    }
                }
                // 0x0014e4d4
                charge(ctx, 6);
                jal(ctx, 0x14E4D4u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 18;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14E4ECu:  // table[19]: state 19: equipment page out, done (-1)
            // 0x0014e4ec
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014e570
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e4fc
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e51c
                    charge(ctx, 4);
                    jal(ctx, 0x14E51Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e52c
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14E53Cu, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                    // 0x0014e544
                    charge(ctx, 9);
                    lw(v1, s4, item::kEquipTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014e568
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014e56c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014e57c
            charge(ctx, 2);
            if (s0 == 0) {
                goto L_0014ece0;
            }
            // 0x0014e584
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x14E590u:  // table[20]: state 20: material -> equipment page
            // 0x0014e590
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e5e8
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e59c
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e5bc
                    charge(ctx, 4);
                    jal(ctx, 0x14E5BCu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e5cc
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E5DCu, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                }
                // 0x0014e5e4
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e5f4
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 11;
            jal(ctx, 0x14E5FCu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014e60c
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14E610u, gen::fn_sub_14B210_0014b210);
                v0 = 21;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14E628u:  // table[21]: state 21: arrived
            // 0x0014e628
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014e6ac
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e638
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e658
                    charge(ctx, 4);
                    jal(ctx, 0x14E658u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e668
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14E678u, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                    // 0x0014e680
                    charge(ctx, 9);
                    lw(v1, s4, item::kMaterialTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014e6a4
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014e6a8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014e6b8
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014e6c0
                charge(ctx, 2);
                v0 = 18;
                sw(v0, s4, item::kState);
            }
            // 0x0014e6c8
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e720
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e6d4
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e6f4
                    charge(ctx, 4);
                    jal(ctx, 0x14E6F4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e704
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E714u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014e71c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e72c
            charge(ctx, 2);
            goto L_0014ece0;
        case 0x14E734u:  // table[25]: state 25: wait for flash 12, material page in
            // 0x0014e734
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e78c
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e740
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e760
                    charge(ctx, 4);
                    jal(ctx, 0x14E760u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e770
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E780u, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                }
                // 0x0014e788
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e798
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 12;
            jal(ctx, 0x14E7A0u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014e7b0
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14E7B4u, gen::fn_sub_148C10_00148c10);
                v0 = 26;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14E7CCu:  // table[26]: state 26: arrived
            // 0x0014e7cc
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014e850
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e7dc
                charge(ctx, 8);
                lw(v1, s4, item::kEquipTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e7fc
                    charge(ctx, 4);
                    jal(ctx, 0x14E7FCu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e80c
                        charge(ctx, 6);
                        lw(v0, s4, item::kEquipTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14E81Cu, gen::fn_sub_148880_00148880);  // the equipment page's element draw
                    }
                    // 0x0014e824
                    charge(ctx, 9);
                    lw(v1, s4, item::kEquipTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014e848
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014e84c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014e85c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014e864
                charge(ctx, 2);
                v0 = 27;
                sw(v0, s4, item::kState);
            }
            // 0x0014e86c
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014e8c4
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e878
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e898
                    charge(ctx, 4);
                    jal(ctx, 0x14E898u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e8a8
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14E8B8u, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                }
                // 0x0014e8c0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014e8d0
            charge(ctx, 2);
            goto L_0014ece0;
        case 0x14E8D8u:  // table[27]: state 27: the material list (input)
            // 0x0014e8d8
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014e95c
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014e8e8
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014e908
                    charge(ctx, 4);
                    jal(ctx, 0x14E908u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014e918
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14E928u, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                    // 0x0014e930
                    charge(ctx, 9);
                    lw(v1, s4, item::kMaterialTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014e954
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014e958
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014e968
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014e970
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v0 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x0014e9fc
                    charge(ctx, 6);
                    a0 = 1;
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                    v0 = v1 & 0x8000;  // previous page
                    if (v0 == 0) {
                        // 0x0014ea14
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                        v0 = v0 & 0x8000;  // previous page
                        if (v0 == 0) {
                            // 0x0014ea28
                            charge(ctx, 1);
                            a0 = 0;
                        }
                    }
                    // 0x0014ea2c
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0014ea44
                        charge(ctx, 4);
                        v0 = v1 & 0x2000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x0014ea54
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x2000;  // next page
                            v0 = sltu(0, v0);
                        }
                        // 0x0014ea64
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x0014ea7c
                            charge(ctx, 9);
                            lw(v0, s4, item::kMaterialList);
                            lw(a0, v0, 2412);
                            a1 = 5;
                            a2 = addiu(v0, 2420);
                            a3 = addiu(v0, 2416);
                            jal(ctx, 0x14EA90u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                        } else {
                            // 0x0014ea6c
                            charge(ctx, 4);
                            v0 = 14;
                            sw(v0, s4, item::kState);
                        }
                    } else {
                        // 0x0014ea34
                        charge(ctx, 4);
                        v0 = 20;
                        sw(v0, s4, item::kState);
                    }
                } else {
                    // 0x0014e984
                    charge(ctx, 30);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x14E994u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    sw(zero, sp, 0xA0);
                    sw(zero, sp, 0xA4);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = addiu(s4, item::kRibbon);
                    a1 = 0;
                    a2 = 2;
                    a3 = a2;
                    ld(t0, sp, 0xA0);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x14E9D8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    a0 = s4;
                    jal(ctx, 0x14E9E4u, gen::fn_sub_14BCE0_0014bce0);
                    v0 = 28;
                    sw(v0, s4, item::kState);
                }
            }
            goto L_0014ece0;
        case 0x14EAA0u:  // table[28]: state 28: material page out, done (-1)
            // 0x0014eaa0
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014eb24
                charge(ctx, 3);
                v0 = slti(s1, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014eab0
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014ead0
                    charge(ctx, 4);
                    jal(ctx, 0x14EAD0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014eae0
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14EAF0u, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                    // 0x0014eaf8
                    charge(ctx, 9);
                    lw(v1, s4, item::kMaterialTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014eb1c
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014eb20
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014eb30
            charge(ctx, 2);
            if (s0 == 0) {
                goto L_0014ece0;
            }
            // 0x0014eb38
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x14EB44u:  // table[29]: state 29: wait for flash 12, item page -> material page
            // 0x0014eb44
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014eb9c
                charge(ctx, 3);
                v0 = slti(s0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014eb50
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014eb70
                    charge(ctx, 4);
                    jal(ctx, 0x14EB70u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014eb80
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14EB90u, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                }
                // 0x0014eb98
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x0014eba8
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 12;
            jal(ctx, 0x14EBB0u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014ebc0
                charge(ctx, 7);
                a0 = s4;
                jal(ctx, 0x14EBC4u, gen::fn_sub_14A490_0014a490);
                v0 = 30;
                sw(v0, s4, item::kState);
            }
            goto L_0014ece0;
        case 0x14EBDCu:  // table[30]: state 30: arrived
            // 0x0014ebdc
            charge(ctx, 4);
            s0 = 1;
            s1 = 0;
            for (;;) {
                // 0x0014ec60
                charge(ctx, 3);
                v0 = slti(s1, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014ebec
                charge(ctx, 8);
                lw(v1, s4, item::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014ec0c
                    charge(ctx, 4);
                    jal(ctx, 0x14EC0Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014ec1c
                        charge(ctx, 6);
                        lw(v0, s4, item::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s4;
                        jal(ctx, 0x14EC2Cu, gen::fn_sub_145520_00145520);  // the item page's element draw
                    }
                    // 0x0014ec34
                    charge(ctx, 9);
                    lw(v1, s4, item::kTweens);
                    v0 = sll(s1, 4);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0014ec58
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x0014ec5c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0014ec6c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0014ec74
                charge(ctx, 2);
                v0 = 27;
                sw(v0, s4, item::kState);
            }
            // 0x0014ec7c
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0014ecd4
                charge(ctx, 3);
                v0 = slti(s0, 40);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0014ec88
                charge(ctx, 8);
                lw(v1, s4, item::kMaterialTweens);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0014eca8
                    charge(ctx, 4);
                    jal(ctx, 0x14ECA8u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0014ecb8
                        charge(ctx, 6);
                        lw(v0, s4, item::kMaterialTweens);
                        a0 = addu(v0, s1);
                        a1 = s0;
                        a2 = s4;
                        jal(ctx, 0x14ECC8u, gen::fn_sub_14C290_0014c290);  // the material page's element draw
                    }
                }
                // 0x0014ecd0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            goto L_0014ece0;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0014ece4 (the shared epilogue, written out on this path)
        charge(ctx, 13);
        ld(ra, sp, 0x90);
        lq(s6, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        lwc1(f21, sp, 0x14);
        lwc1(f20, sp, 0x10);
        sp = addiu(sp, 0xB0);
        return;
    }
    goto L_0014ece0;
}

}  // namespace p3fes::game
