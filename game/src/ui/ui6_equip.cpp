// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the equipment screen (its update, the slot menu and candidate list panels) and the persona screen (its update,
// list rows).
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
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_11B370_0011b370(p3fes::EEContext&);
void fn_sub_11E380_0011e380(p3fes::EEContext&);
void fn_sub_12C430_0012c430(p3fes::EEContext&);
void fn_sub_12DC20_0012dc20(p3fes::EEContext&);
void fn_sub_12DCF0_0012dcf0(p3fes::EEContext&);
void fn_sub_12DDC0_0012ddc0(p3fes::EEContext&);
void fn_sub_12DF50_0012df50(p3fes::EEContext&);
void fn_sub_12E170_0012e170(p3fes::EEContext&);
void fn_sub_12E3B0_0012e3b0(p3fes::EEContext&);
void fn_sub_12F6D0_0012f6d0(p3fes::EEContext&);
void fn_sub_131090_00131090(p3fes::EEContext&);
void fn_sub_1311D0_001311d0(p3fes::EEContext&);
void fn_sub_1339A0_001339a0(p3fes::EEContext&);
void fn_sub_133A80_00133a80(p3fes::EEContext&);
void fn_sub_133B80_00133b80(p3fes::EEContext&);
void fn_sub_133E10_00133e10(p3fes::EEContext&);
void fn_sub_1344B0_001344b0(p3fes::EEContext&);
void fn_sub_134900_00134900(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C860_0016c860(p3fes::EEContext&);
void fn_sub_16C910_0016c910(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16DA50_0016da50(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_16F810_0016f810(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_174960_00174960(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_174C10_00174c10(p3fes::EEContext&);
void fn_sub_175200_00175200(p3fes::EEContext&);
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

// 0x0012C430 sub_12C430 -- 6124 bytes; frame 0x160: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_UpdateSoubi1DrawTask] Update of the equipment screen "H_CampSoubi1Draw" (jump table 0x7B5BC0, state at +4): 0
// waits for flash 15, allocates the three tween arrays (+696 / +700 / +704) and requests camp/camp_equip.pak (+0); 1
// takes its two sprite files (+688 / +692); 2 waits for them; 3 slides the five slot panels in; 4 is the slot menu
// (confirm 0x40 -> 7, cancel 0x20 -> 5, up / down move the slot +28 with wrap on a fresh press); 5 / 6 close (-1); 7
// waits for flash 16 and collects the candidates (sub_131090 into +40, count +684); 8 / 9 swap the panels; 0xA is the
// candidate list (H_Camp_MoveListCursor 5 rows, +36 scroll / +32 cursor): confirm equips (datSetEquipmentIdx) and
// rescales HP / SP to the new maxima (cur * newMax / oldMax), cancel goes back; 0xB / 0xC return to the slot menu.
// Every state draws the backdrop (sub_12DDC0) and the panels (sub_12DC20 / sub_12DCF0).
void sub_12C430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x0012c430
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(s4, a0, 60);
    lw(v0, s4, equip::kState);
    at = sltiu(v0, 13);
    if (at != 0) {
        // 0x0012c460
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23488);  // &0x7B5BC0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x12C47Cu:  // table[0]: state 0: wait for flash 15, tweens, request camp_equip.pak
            // 0x0012c47c
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 15;
            jal(ctx, 0x12C484u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0012c4a0
                charge(ctx, 22);
                a0 = 10;
                jal(ctx, 0x12C4A4u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s4, equip::kSlotTweens);
                a0 = 10;
                jal(ctx, 0x12C4B4u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s4, equip::kListTweens);
                a0 = 1;
                jal(ctx, 0x12C4C4u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s4, equip::kBackdrop);
                a0 = 0x5E0000;
                a0 = addiu(a0, -20224);  // "camp/camp_equip.pak"
                a1 = 1;
                jal(ctx, 0x12C4DCu, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s4, equip::kPak);
                v0 = 1;
                sw(v0, s4, equip::kState);
            L_0012dbf4:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0012c494
                charge(ctx, 3);
                v0 = 0;
            }
            break;
        case 0x12C4F8u:  // table[1]: state 1: take the pak's sprite files
            // 0x0012c4f8
            charge(ctx, 5);
            lw(a0, s4, equip::kPak);
            jal(ctx, 0x12C4FCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0012c50c
                charge(ctx, 40);
                sw(zero, sp, 0x148);
                v0 = 0x43BF0000;  // 382.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lw(a0, s4, equip::kBackdrop);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12C54Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, equip::kPak);
                a1 = 0;
                a2 = addiu(sp, 0x15C);
                jal(ctx, 0x12C560u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x12C56Cu, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s4, equip::kFile0);
                lw(a0, s4, equip::kPak);
                a1 = 1;
                a2 = addiu(sp, 0x15C);
                jal(ctx, 0x12C584u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x12C590u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s4, equip::kFile1);
                v0 = 2;
                sw(v0, s4, equip::kState);
            }
            goto L_0012dbf4;
        case 0x12C5ACu:  // table[2]: state 2: wait for the files
            // 0x0012c5ac
            charge(ctx, 5);
            lw(a0, s4, equip::kFile0);
            jal(ctx, 0x12C5B0u, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x0012c5c0
                charge(ctx, 5);
                lw(a0, s4, equip::kFile1);
                jal(ctx, 0x12C5C4u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x0012c5d4
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s4, equip::kState);
                }
            }
            goto L_0012dbf4;
        case 0x12C5E4u:  // table[3]: state 3: slide the slot panels in
            // 0x0012c5e4
            charge(ctx, 204);
            sw(zero, sp, 0x148);
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x150);
            lwc1(f1, sp, 0x150);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x150);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s4, equip::kSlotTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x150);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C644u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x148);
            v0 = 0x42B40000;  // 90.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x78);
            lwc1(f1, sp, 0x78);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x78);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x78);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C6B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x148);
            v0 = 0x42F00000;  // 120.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x80);
            lwc1(f1, sp, 0x80);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x80);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x80);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C71Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x148);
            v0 = 0x43160000;  // 150.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x88);
            lwc1(f1, sp, 0x88);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x88);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x88);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C788u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 487;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x148);
            v0 = 0x436A0000;  // 234.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x90);
            lwc1(f0, sp, 0x90);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f1);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x90);
            lwc1(f0, sp, 0x94);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x94);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x90);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C810u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43360000;  // 182.0f
            sw(v0, sp, 0x148);
            v0 = 0x43720000;  // 242.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x98);
            lwc1(f1, sp, 0x98);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x98);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x98);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C880u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41E00000;  // 28.0f
            sw(v0, sp, 0x148);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0xA0);
            lwc1(f1, sp, 0xA0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA0);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12C8FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 4;
            sw(v0, s4, equip::kState);
            goto L_0012dbf4;
        case 0x12C914u:  // table[4]: state 4: the slot menu (input)
            // 0x0012c914
            charge(ctx, 3);
            lw(v0, s4, equip::kSlotsArrived);
            if (v0 != 0) {
                // 0x0012c920
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                v0 = v1 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x0012c95c
                    charge(ctx, 3);
                    v0 = v1 & 0x20;
                    if (v0 == 0) {
                        // 0x0012c990
                        charge(ctx, 4);
                        v0 = v1 & 0x1000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x0012c9a0
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x1000;  // cursor - 1
                            v0 = sltu(0, v0);
                        }
                        // 0x0012c9b0
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x0012c9f0
                            charge(ctx, 4);
                            v0 = v1 & 0x4000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x0012ca00
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x4000;  // cursor + 1
                                v0 = sltu(0, v0);
                            }
                            // 0x0012ca10
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x0012ca18
                                charge(ctx, 4);
                                lh(v1, s4, equip::kSlot);
                                v0 = 3;
                                if (v1 != v0) {
                                    // 0x0012ca28
                                    charge(ctx, 9);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x12CA38u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lh(v0, s4, equip::kSlot);
                                    v0 = addiu(v0, 1);
                                    sh(v0, s4, equip::kSlot);
                                }
                            }
                        } else {
                            // 0x0012c9b8
                            charge(ctx, 3);
                            lh(v0, s4, equip::kSlot);
                            if (v0 != 0) {
                                // 0x0012c9c4
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x12C9D4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lh(v0, s4, equip::kSlot);
                                v0 = addiu(v0, -1);
                                sh(v0, s4, equip::kSlot);
                            }
                        }
                    } else {
                        // 0x0012c968
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x12C978u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 5;
                        sw(v0, s4, equip::kState);
                    }
                } else {
                    // 0x0012c934
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x12C944u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 7;
                    sw(v0, s4, equip::kState);
                }
            }
            // 0x0012ca4c
            charge(ctx, 9);
            a0 = s4;
            jal(ctx, 0x12CA50u, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12CA5Cu, gen::fn_sub_12DC20_0012dc20);
            sw(v0, s4, equip::kSlotsArrived);
            goto L_0012dbf4;
        case 0x12CA70u:  // table[5]: state 5: slide out
            // 0x0012ca70
            charge(ctx, 218);
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xA8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s4, equip::kSlotTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CACCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x42B40000;  // 90.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xB0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CB34u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x42F00000;  // 120.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xB8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CB9Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x43160000;  // 150.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xC0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CC04u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 487;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x148);
            v0 = 0x436A0000;  // 234.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xC8);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CC78u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            a0 = s4;
            jal(ctx, 0x12CC84u, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12CC90u, gen::fn_sub_12DC20_0012dc20);
            v0 = 0x43360000;  // 182.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x148);
            v0 = 0x43720000;  // 242.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xD0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CCFCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x148);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xD8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CD74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s4, equip::kBackdrop);
            lwc1(f0, a0, 56);
            swc1(f0, sp, 0x148);
            lwc1(f0, a0, 60);
            swc1(f0, sp, 0x14C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x148);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CDC0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 6;
            sw(v0, s4, equip::kState);
            goto L_0012dbf4;
        case 0x12CDD8u:  // table[6]: state 6: done (-1)
            // 0x0012cdd8
            charge(ctx, 8);
            a0 = s4;
            jal(ctx, 0x12CDDCu, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12CDE8u, gen::fn_sub_12DC20_0012dc20);
            if (v0 == 0) {
                goto L_0012dbf4;
            }
            // 0x0012cdf8
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x12CE04u:  // table[7]: state 7: wait for flash 16, collect the candidates
            // 0x0012ce04
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 16;
            jal(ctx, 0x12CE0Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0012ce1c
                charge(ctx, 11);
                sw(zero, s4, equip::kScroll);
                sw(zero, s4, equip::kCursor);
                lhu(a2, s4, equip::kPc);
                lh(a3, s4, equip::kSlot);
                a0 = addiu(s4, equip::kCandidates);
                a1 = addiu(s4, equip::kCandidateTail);
                jal(ctx, 0x12CE34u, gen::fn_sub_131090_00131090);  // collect the candidates
                sw(v0, s4, equip::kCandidateCount);
                v0 = 8;
                sw(v0, s4, equip::kState);
            }
            // 0x0012ce48
            charge(ctx, 8);
            a0 = s4;
            jal(ctx, 0x12CE4Cu, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12CE58u, gen::fn_sub_12DC20_0012dc20);
            goto L_0012dbf4;
        case 0x12CE68u:  // table[8]: state 8: swap to the list panels
            // 0x0012ce68
            charge(ctx, 419);
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xE0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s4, equip::kSlotTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CEC4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x42B40000;  // 90.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xE8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CF2Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x42F00000;  // 120.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xF0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CF94u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x148);
            v0 = 0x43160000;  // 150.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0xF8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12CFFCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 487;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x148);
            v0 = 0x436A0000;  // 234.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0x100);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D070u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43360000;  // 182.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x148);
            v0 = 0x43720000;  // 242.0f
            sw(v0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0x108);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D0DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x148);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x14C);
            ld(t0, sp, 0x148);
            sd(t0, sp, 0x110);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x148);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kSlotTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D154u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x148);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x118);
            lwc1(f1, sp, 0x118);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x118);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s4, equip::kListTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x118);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D1C0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 419;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x148);
            v0 = 0x42140000;  // 37.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x120);
            lwc1(f1, sp, 0x120);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x120);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x120);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D23Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f3);
            sw(zero, sp, 0x148);
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x14C);
            sw(zero, sp, 0x120);
            lh(v0, s4, equip::kSlot);
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
            v0 = 0x41F00000;  // 30.0f
            mtc1(v0, f1);
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f0);
            adda_s(f3, f0);
            madd_s(f1, f1, f2);
            v0 = 0x40A00000;  // 5.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x124);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x120);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D2D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(v0, s4, equip::kListTweens);
            sw(zero, v0, 200);
            v0 = 0x42EA0000;  // 117.0f
            sw(v0, sp, 0x148);
            v0 = 0x42D80000;  // 108.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x128);
            lwc1(f0, sp, 0x128);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0x128);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v0, s4, equip::kListTweens);
            a0 = addiu(v0, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x128);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D340u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 487;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x148);
            v0 = 365;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x130);
            lwc1(f0, sp, 0x130);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0x130);
            lwc1(f0, sp, 0x134);
            sub_s(f0, f0, f12);
            swc1(f0, sp, 0x134);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v0, s4, equip::kListTweens);
            a0 = addiu(v0, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x130);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D3CCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43290000;  // 169.0f
            sw(v0, sp, 0x148);
            v0 = 0x43720000;  // 242.0f
            sw(v0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x138);
            lwc1(f1, sp, 0x138);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x138);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x138);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D43Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41E00000;  // 28.0f
            sw(v0, sp, 0x148);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x14C);
            ld(v0, sp, 0x148);
            sd(v0, sp, 0x140);
            lwc1(f1, sp, 0x140);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x140);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s4, equip::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x140);
            ld(t1, sp, 0x148);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x12D4B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            a0 = s4;
            jal(ctx, 0x12D4C4u, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12D4D0u, gen::fn_sub_12DC20_0012dc20);
            a0 = s4;
            jal(ctx, 0x12D4DCu, gen::fn_sub_12DCF0_0012dcf0);
            v0 = 9;
            sw(v0, s4, equip::kState);
            goto L_0012dbf4;
        case 0x12D4F4u:  // table[9]: state 9: wait for the list
            // 0x0012d4f4
            charge(ctx, 11);
            a0 = s4;
            jal(ctx, 0x12D4F8u, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12D504u, gen::fn_sub_12DC20_0012dc20);
            a0 = s4;
            jal(ctx, 0x12D510u, gen::fn_sub_12DCF0_0012dcf0);
            if (v0 != 0) {
                // 0x0012d520
                charge(ctx, 4);
                v0 = 10;
                sw(v0, s4, equip::kState);
            }
            goto L_0012dbf4;
        case 0x12D530u:  // table[10]: state 10: the candidate list (input; equip)
            // 0x0012d530
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
            v0 = v1 & 0x40;  // confirm
            if (v0 == 0) {
                // 0x0012d66c
                charge(ctx, 3);
                v0 = v1 & 0x20;
                if (v0 == 0) {
                    // 0x0012d6a0
                    charge(ctx, 6);
                    lw(a0, s4, equip::kCandidateCount);
                    a1 = 5;
                    a2 = addiu(s4, equip::kScroll);
                    a3 = addiu(s4, equip::kCursor);
                    jal(ctx, 0x12D6B0u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                } else {
                    // 0x0012d678
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x12D688u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 11;
                    sw(v0, s4, equip::kState);
                }
            } else {
                // 0x0012d544
                charge(ctx, 38);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 7;
                jal(ctx, 0x12D554u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                lh(a0, s4, equip::kPc);
                jal(ctx, 0x12D560u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
                s3 = v0 & 0xFFFF;
                lh(a0, s4, equip::kPc);
                jal(ctx, 0x12D570u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
                s2 = v0 & 0xFFFF;
                lh(a0, s4, equip::kPc);
                jal(ctx, 0x12D580u, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
                s1 = v0 & 0xFFFF;
                lh(a0, s4, equip::kPc);
                jal(ctx, 0x12D590u, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
                s0 = v0 & 0xFFFF;
                lw(v1, s4, equip::kScroll);
                lw(v0, s4, equip::kCursor);
                v0 = addu(v1, v0);
                v0 = sll(v0, 1);
                v0 = addu(v0, s4);
                lh(a2, v0, 40);
                lh(a0, s4, equip::kPc);
                lh(a1, s4, equip::kSlot);
                jal(ctx, 0x12D5BCu, gen::fn_sub_16DA50_0016da50);  // [datSetEquipmentIdx] (pc, slot, index)
                lh(a0, s4, equip::kPc);
                jal(ctx, 0x12D5C8u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
                v0 = v0 & 0xFFFF;
                if (s3 != v0) {
                    // 0x0012d5dc
                    charge(ctx, 14);
                    lh(a0, s4, equip::kPc);
                    jal(ctx, 0x12D5E0u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
                    v0 = v0 & 0xFFFF;
                    mult(v0, s2, v0);
                    div(v0, s3);
                    mflo(v0);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    lh(a0, s4, equip::kPc);
                    jal(ctx, 0x12D60Cu, gen::fn_sub_16CF40_0016cf40);  // [datSetPcHp]
                }
                // 0x0012d614
                charge(ctx, 6);
                lh(a0, s4, equip::kPc);
                jal(ctx, 0x12D618u, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
                v0 = v0 & 0xFFFF;
                if (s1 != v0) {
                    // 0x0012d62c
                    charge(ctx, 16);
                    lh(a0, s4, equip::kPc);
                    jal(ctx, 0x12D630u, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
                    v0 = v0 & 0xFFFF;
                    mult(v0, s0, v0);
                    div(v0, s1);
                    mflo(v0);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    lh(a0, s4, equip::kPc);
                    jal(ctx, 0x12D65Cu, gen::fn_sub_16CF90_0016cf90);  // [datSetPcSp]
                }
            }
            // 0x0012d6b8
            charge(ctx, 8);
            a0 = s4;
            jal(ctx, 0x12D6BCu, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12D6C8u, gen::fn_sub_12DCF0_0012dcf0);
            goto L_0012dbf4;
        case 0x12D6D8u:  // table[11]: state 11: wait for flash 15, panels back
            // 0x0012d6d8
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 15;
            jal(ctx, 0x12D6E0u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0012d6f0
                charge(ctx, 293);
                sw(zero, sp, 0x148);
                v0 = 0x42700000;  // 60.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lw(a0, s4, equip::kSlotTweens);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D730u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, sp, 0x148);
                v0 = 0x42B40000;  // 90.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kSlotTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 68);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D77Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, sp, 0x148);
                v0 = 0x42F00000;  // 120.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kSlotTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 136);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D7C8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, sp, 0x148);
                v0 = 0x43160000;  // 150.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kSlotTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 204);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D814u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 487;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x148);
                v0 = 0x436A0000;  // 234.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kSlotTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 340);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D870u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x43360000;  // 182.0f
                sw(v0, sp, 0x148);
                v0 = 0x43720000;  // 242.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kSlotTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 272);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D8C0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x41E00000;  // 28.0f
                sw(v0, sp, 0x148);
                v0 = 415;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kSlotTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 408);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D91Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x41980000;  // 19.0f
                sw(v0, sp, 0x148);
                v0 = 0x42100000;  // 36.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lw(a0, s4, equip::kListTweens);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D968u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 419;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x148);
                v0 = 0x42140000;  // 37.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kListTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 68);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12D9C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, sp, 0x148);
                v0 = 0x42700000;  // 60.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kListTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 136);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12DA10u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42EA0000;  // 117.0f
                sw(v0, sp, 0x148);
                v0 = 0x42D80000;  // 108.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kListTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 204);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12DA60u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 487;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x148);
                v0 = 365;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kListTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 272);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12DAC8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 12;
                sw(v0, s4, equip::kState);
                v0 = 0x43290000;  // 169.0f
                sw(v0, sp, 0x148);
                v0 = 0x43720000;  // 242.0f
                sw(v0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kListTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 408);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12DB20u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x41E00000;  // 28.0f
                sw(v0, sp, 0x148);
                v0 = 415;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x14C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s4, equip::kListTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 476);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x148);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x12DB7Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            }
            // 0x0012db84
            charge(ctx, 8);
            a0 = s4;
            jal(ctx, 0x12DB88u, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12DB94u, gen::fn_sub_12DCF0_0012dcf0);
            goto L_0012dbf4;
        case 0x12DBA4u:  // table[12]: state 12: back to the slot menu
            // 0x0012dba4
            charge(ctx, 9);
            s0 = 1;
            a0 = s4;
            jal(ctx, 0x12DBACu, gen::fn_sub_12DDC0_0012ddc0);  // the equipment backdrop
            a0 = s4;
            jal(ctx, 0x12DBB8u, gen::fn_sub_12DC20_0012dc20);
            if (v0 == 0) {
                // 0x0012dbc8
                charge(ctx, 1);
                s0 = 0;
            }
            // 0x0012dbcc
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x12DBD0u, gen::fn_sub_12DCF0_0012dcf0);
            if (v0 == 0) {
                // 0x0012dbe0
                charge(ctx, 1);
                s0 = 0;
            }
            // 0x0012dbe4
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0012dbec
                charge(ctx, 2);
                v0 = 4;
                sw(v0, s4, equip::kState);
            }
            goto L_0012dbf4;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0012dbf8 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        sp = addiu(sp, 0x160);
        return;
    }
    goto L_0012dbf4;
}

// 0x0012DC20 sub_12DC20 -- 208 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_EquipRunSlotTweens] (equip work): steps the 10 slot-panel tweens (+696), draws each active one (sub_12E3B0)
// and returns 1 when all finished.
void sub_12DC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0012dc20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 1;
    s1 = 0;
    for (;;) {
        // 0x0012dcc0
        charge(ctx, 3);
        v0 = slti(s1, 10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012dc4c
        charge(ctx, 8);
        lw(v1, s2, equip::kSlotTweens);
        v0 = sll(s1, 4);
        v0 = addu(v0, s1);
        s3 = sll(v0, 2);
        a0 = addu(v1, s3);
        lw(v0, a0, 4);
        if (v0 != 0) {
            // 0x0012dc6c
            charge(ctx, 4);
            jal(ctx, 0x12DC6Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x0012dc7c
                charge(ctx, 6);
                lw(v0, s2, equip::kSlotTweens);
                a2 = addu(v0, s3);
                a0 = s2;
                a1 = s1;
                jal(ctx, 0x12DC8Cu, gen::fn_sub_12E3B0_0012e3b0);
            }
            // 0x0012dc94
            charge(ctx, 9);
            lw(v1, s2, equip::kSlotTweens);
            v0 = sll(s1, 4);
            v0 = addu(v0, s1);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x0012dcb8
                charge(ctx, 1);
                s0 = 0;
            }
        }
        // 0x0012dcbc
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0012dccc
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0012DCF0 sub_12DCF0 -- 208 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_EquipRunListTweens] (equip work): the same for the 10 candidate-list tweens (+700, sub_12F6D0).
void sub_12DCF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0012dcf0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 1;
    s1 = 0;
    for (;;) {
        // 0x0012dd90
        charge(ctx, 3);
        v0 = slti(s1, 10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012dd1c
        charge(ctx, 8);
        lw(v1, s2, equip::kListTweens);
        v0 = sll(s1, 4);
        v0 = addu(v0, s1);
        s3 = sll(v0, 2);
        a0 = addu(v1, s3);
        lw(v0, a0, 4);
        if (v0 != 0) {
            // 0x0012dd3c
            charge(ctx, 4);
            jal(ctx, 0x12DD3Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x0012dd4c
                charge(ctx, 6);
                lw(v0, s2, equip::kListTweens);
                a2 = addu(v0, s3);
                a0 = s2;
                a1 = s1;
                jal(ctx, 0x12DD5Cu, gen::fn_sub_12F6D0_0012f6d0);
            }
            // 0x0012dd64
            charge(ctx, 9);
            lw(v1, s2, equip::kListTweens);
            v0 = sll(s1, 4);
            v0 = addu(v0, s1);
            v0 = sll(v0, 2);
            v0 = addu(v1, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x0012dd88
                charge(ctx, 1);
                s0 = 0;
            }
        }
        // 0x0012dd8c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0012dd9c
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0012E3B0 sub_12E3B0 -- 4896 bytes; frame 0x4B0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_EquipDrawSlotPanel] (equip work, element, tween): one panel of the slot menu (jump table 0x7B5C00): elements
// 0..3 the weapon / armour / boots / accessory slots of the member (+18: the equipped entry's icon from its mask
// (sub_12DF50), name (datGetItemName), and power / accuracy / evasion / defence through sub_12E170, highlighted when it
// is the slot +28), the rest the frame, the member's HP / SP and the help line.
void sub_12E3B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0012e3b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4B0);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    s4 = 0;
    for (;;) {
        // 0x0012e490
        charge(ctx, 3);
        v1 = slti(s4, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012e3ec
        charge(ctx, 41);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        lh(a0, s2, equip::kPc);
        jal(ctx, 0x12E3F8u, gen::fn_datGetEquipmentIdx_0016cb80);
        s3 = dsll32(v0, 16);
        s3 = dsra32(s3, 16);
        a0 = 1;
        a1 = s3;
        jal(ctx, 0x12E410u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
        a0 = v0;
        jal(ctx, 0x12E41Cu, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
        v1 = sll(s4, 2);
        v1 = addu(v1, sp);
        sw(v0, v1, 1168);
        lh(a0, s2, equip::kPc);
        a1 = s3;
        jal(ctx, 0x12E438u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
        s6 = dsll32(v0, 16);
        s6 = dsra32(s6, 16);
        lh(a0, s2, equip::kPc);
        a1 = s3;
        jal(ctx, 0x12E450u, gen::fn_sub_16F810_0016f810);  // (owner, index)
        v0 = v0 & 0xFF;
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s6;
        jal(ctx, 0x12E468u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
        v1 = sll(s4, 8);
        v1 = addu(v1, sp);
        a0 = addiu(v1, 144);
        a1 = addiu(gp, -30340);  // "%s"
        a2 = v0;
        jal(ctx, 0x12E484u, gen::fn_sprintf_00523ac8);
        s4 = addiu(s4, 1);
    }
    // 0x0012e49c
    charge(ctx, 3);
    at = sltiu(s1, 7);
    if (at != 0) {
        // 0x0012e4a8
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 23552);  // &0x7B5C00
        v1 = sll(s1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x12E4C4u:  // table[0]: element 0: the weapon slot
            // 0x0012e4c4
            charge(ctx, 23);
            lh(a0, s2, equip::kPc);
            a1 = 0;
            jal(ctx, 0x12E4CCu, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s2, equip::kPc);
            jal(ctx, 0x12E4E0u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
            s3 = v0 & 0xFFFF;
            lh(a0, s2, equip::kPc);
            a1 = 0;
            jal(ctx, 0x12E4F4u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s2, equip::kPc);
            jal(ctx, 0x12E508u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
            s1 = v0 & 0xFFFF;
            lh(v0, s2, equip::kSlot);
            if (v0 != 0) {
                // 0x0012e7cc
                charge(ctx, 164);
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 1;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E808u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x490);
                a2 = sll(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E860u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x90);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12E8CCu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s0, tw::kX);
                v0 = 0x43CB0000;  // 406.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 10;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E910u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 507;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f12, f1, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 16;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E958u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 443;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 2;
                jal(ctx, 0x12E998u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s3, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12E9D4u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                lwc1(f1, s0, tw::kX);
                v0 = 0x44080000;  // 544.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 2;
                jal(ctx, 0x12EA10u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s1, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12EA4Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            } else {
                // 0x0012e520
                charge(ctx, 171);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 24;
                lwc1(f12, s0, tw::kX);
                lwc1(f13, s0, tw::kY);
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E53Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 0;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E580u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x490);
                v0 = sll(v0, 1);
                a2 = addiu(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E5D0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x90);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12E63Cu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s0, tw::kX);
                v0 = 0x43CB0000;  // 406.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 9;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E680u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 507;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f12, f1, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 15;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12E6C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 443;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 1;
                jal(ctx, 0x12E708u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s3, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12E744u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                lwc1(f1, s0, tw::kX);
                v0 = 0x44080000;  // 544.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 1;
                jal(ctx, 0x12E780u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s1, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12E7BCu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            }
            break;
        case 0x12EA5Cu:  // table[1]: element 1: the armour slot
            // 0x0012ea5c
            charge(ctx, 14);
            lh(a0, s2, equip::kPc);
            a1 = 1;
            jal(ctx, 0x12EA64u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s2, equip::kPc);
            jal(ctx, 0x12EA78u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
            s1 = v0 & 0xFFFF;
            lh(v1, s2, equip::kSlot);
            v0 = 1;
            if (v1 != v0) {
                // 0x0012ec80
                charge(ctx, 116);
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 3;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12ECBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x494);
                a2 = sll(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12ED14u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x190);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12ED80u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s0, tw::kX);
                v0 = 0x43CB0000;  // 406.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 12;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EDC4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 443;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 2;
                jal(ctx, 0x12EE04u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s1, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12EE40u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            } else {
                // 0x0012ea94
                charge(ctx, 123);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 24;
                lwc1(f12, s0, tw::kX);
                lwc1(f13, s0, tw::kY);
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EAB0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 2;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EAF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x494);
                v0 = sll(v0, 1);
                a2 = addiu(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EB44u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x190);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12EBB0u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s0, tw::kX);
                v0 = 0x43CB0000;  // 406.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 11;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EBF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 443;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 1;
                jal(ctx, 0x12EC34u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s1, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12EC70u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            }
            break;
        case 0x12EE50u:  // table[2]: element 2: the boots slot
            // 0x0012ee50
            charge(ctx, 14);
            lh(a0, s2, equip::kPc);
            a1 = 2;
            jal(ctx, 0x12EE58u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s2, equip::kPc);
            jal(ctx, 0x12EE6Cu, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
            s1 = v0 & 0xFFFF;
            lh(v1, s2, equip::kSlot);
            v0 = 2;
            if (v1 != v0) {
                // 0x0012f074
                charge(ctx, 116);
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 5;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F0B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x498);
                a2 = sll(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F108u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x290);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12F174u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s0, tw::kX);
                v0 = 0x43CB0000;  // 406.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 14;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F1B8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 443;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 2;
                jal(ctx, 0x12F1F8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s1, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12F234u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            } else {
                // 0x0012ee88
                charge(ctx, 123);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 24;
                lwc1(f12, s0, tw::kX);
                lwc1(f13, s0, tw::kY);
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EEA4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 4;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EEE8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x498);
                v0 = sll(v0, 1);
                a2 = addiu(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EF38u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x290);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12EFA4u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s0, tw::kX);
                v0 = 0x43CB0000;  // 406.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 13;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12EFE8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 443;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s0, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x4A8);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x4AC);
                a0 = 1;
                jal(ctx, 0x12F028u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s0, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s1, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x4A8);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s0, tw::kAlpha);
                jal(ctx, 0x12F064u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            }
            break;
        case 0x12F244u:  // table[3]: element 3: the accessory slot
            // 0x0012f244
            charge(ctx, 4);
            lh(v1, s2, equip::kSlot);
            v0 = 3;
            if (v1 != v0) {
                // 0x0012f380
                charge(ctx, 68);
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 7;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F3BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x49C);
                a2 = sll(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F414u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x390);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12F480u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            } else {
                // 0x0012f254
                charge(ctx, 75);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 24;
                lwc1(f12, s0, tw::kX);
                lwc1(f13, s0, tw::kY);
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F270u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s0, tw::kX);
                v0 = 0x41E00000;  // 28.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, equip::kFile0);
                a2 = 6;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F2B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v0, sp, 0x49C);
                v0 = sll(v0, 1);
                a2 = addiu(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x430B0000;  // 139.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F304u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43330000;  // 179.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x390);
                t2 = 16;
                t3 = 120;
                jal(ctx, 0x12F370u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            }
            break;
        case 0x12F490u:  // table[4]
            // 0x0012f490
            charge(ctx, 45);
            lw(v1, s0, tw::kAlpha);
            v0 = 255;
            s5 = subu(v0, v1);
            lwc1(f0, s0, tw::kX);
            cvt_w_s(f0, f0);
            mfc1(s4, f0);
            lwc1(f0, s0, tw::kY);
            cvt_w_s(f0, f0);
            mfc1(s3, f0);
            lh(a0, s2, equip::kPc);
            lh(a1, s2, equip::kSlot);
            jal(ctx, 0x12F4BCu, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s2, equip::kPc);
            jal(ctx, 0x12F4D0u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s1 = v0 & 0xFFFF;
            lh(a0, s2, equip::kPc);
            lh(a1, s2, equip::kSlot);
            jal(ctx, 0x12F4E4u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s2, equip::kPc);
            jal(ctx, 0x12F4F8u, gen::fn_sub_16F900_0016f900);  // (owner, index)
            v0 = v0 & 0xFF;
            v1 = sll(v0, 16);
            v0 = lui(0xFFFF);
            v0 = v1 & v0;
            t2 = s1 | v0;
            v0 = si(-256);
            a2 = s5 | v0;
            a0 = s4;
            a1 = s3;
            lwc1(f12, s0, tw::kZ);
            a3 = 1;
            t0 = 10;
            t1 = a3;
            jal(ctx, 0x12F534u, gen::fn_sub_3C7E20_003c7e20);  // a message text
            break;
        case 0x12F544u:  // table[5]
            // 0x0012f544
            charge(ctx, 25);
            a0 = 0;
            lw(a1, s2, equip::kFile0);
            a2 = 26;
            jal(ctx, 0x12F550u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s5 = v0;
            lwc1(f0, s0, tw::kZ);
            swc1(f0, v0, 44);
            lwc1(f0, s0, tw::kX);
            swc1(f0, v0, 16);
            lwc1(f0, s0, tw::kY);
            swc1(f0, v0, 20);
            lw(v1, s0, tw::kAlpha);
            sb(v1, v0, 24);
            v1 = lui(0xC234);
            sw(v1, v0, 32);
            a0 = s5;
            a1 = 1;
            jal(ctx, 0x12F58Cu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s5;
            jal(ctx, 0x12F598u, gen::fn_sub_115980_00115980);  // draw and release the handle
            break;
        case 0x12F5A8u:  // table[6]
            // 0x0012f5a8
            charge(ctx, 63);
            lbu(a3, s0, tw::kAlpha);
            a0 = s5;
            lw(a1, s2, equip::kFile1);
            a2 = 0;
            lwc1(f12, s0, tw::kX);
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x12F5C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s0, tw::kX);
            v0 = 0x42300000;  // 44.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s5;
            lw(a1, s2, equip::kFile1);
            a2 = 5;
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x12F608u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s0, tw::kX);
            v0 = 0x43F30000;  // 486.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 0;
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x12F650u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 561;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s0, tw::kX);
            add_s(f1, f1, f0);
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 1;
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x12F69Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0012f6a4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x4B0);
}

// 0x0012F6D0 sub_12F6D0 -- 5988 bytes; frame 0x2B0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_EquipDrawListPanel] (equip work, element, tween): one panel of the candidate list (jump table 0x7B5C20): the
// slot header, the five visible candidates (+40 from +36) with icon, name and the stat of the slot's kind, the cursor
// row, the comparison arrows of the selected candidate against the equipped item, the scroll marks.
void sub_12F6D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0012f6d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2B0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    s0 = a2;
    at = sltiu(a1, 8);
    if (at != 0) {
        // 0x0012f710
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 23584);  // &0x7B5C20
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x12F72Cu:  // table[0]: element 0: the list frame
            // 0x0012f72c
            charge(ctx, 11);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            lw(a1, s1, equip::kFile0);
            a2 = 23;
            lwc1(f12, s0, tw::kX);
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x12F748u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x12F758u:  // table[1]: element 1: the slot header
            // 0x0012f758
            charge(ctx, 8);
            lh(a0, s1, equip::kPc);
            lh(a1, s1, equip::kSlot);
            jal(ctx, 0x12F760u, gen::fn_datGetEquipmentIdx_0016cb80);
            lh(a0, s1, equip::kSlot);
            v1 = 2;
            if (a0 == v1) {
                // 0x0012f840
                charge(ctx, 19);
                lwc1(f1, s0, tw::kX);
                v0 = 0x42300000;  // 44.0f
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                v0 = 0x42200000;  // 40.0f
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                lbu(a3, s0, tw::kAlpha);
                a0 = s4;
                lw(a1, s1, equip::kFile0);
                a2 = 20;
                lwc1(f13, s0, tw::kY);
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12F87Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0012f778
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x0012f7f4
                    charge(ctx, 19);
                    lwc1(f1, s0, tw::kX);
                    v0 = 0x42300000;  // 44.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = 0x42200000;  // 40.0f
                    mtc1(v0, f0);
                    sub_s(f12, f1, f0);
                    lbu(a3, s0, tw::kAlpha);
                    a0 = s4;
                    lw(a1, s1, equip::kFile0);
                    a2 = 19;
                    lwc1(f13, s0, tw::kY);
                    lwc1(f14, s0, tw::kZ);
                    jal(ctx, 0x12F830u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x0012f784
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x0012f794
                        charge(ctx, 24);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s1, equip::kFile0);
                        a2 = 18;
                        lwc1(f12, s0, tw::kX);
                        lwc1(f13, s0, tw::kY);
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x12F7B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x42B20000;  // 89.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s1, equip::kFile0);
                        a2 = 21;
                        lwc1(f13, s0, tw::kY);
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x12F7E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x0012f78c
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x12F88Cu:  // table[2]: element 2: the equipped item
            // 0x0012f88c
            charge(ctx, 39);
            lh(a0, s1, equip::kPc);
            lh(a1, s1, equip::kSlot);
            jal(ctx, 0x12F894u, gen::fn_datGetEquipmentIdx_0016cb80);
            s3 = dsll32(v0, 16);
            s3 = dsra32(s3, 16);
            a0 = 1;
            a1 = s3;
            jal(ctx, 0x12F8ACu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
            a0 = v0;
            jal(ctx, 0x12F8B8u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
            s2 = v0;
            lh(a0, s1, equip::kPc);
            a1 = s3;
            jal(ctx, 0x12F8CCu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s5 = dsll32(v0, 16);
            s5 = dsra32(s5, 16);
            lh(a0, s1, equip::kPc);
            a1 = s3;
            jal(ctx, 0x12F8E4u, gen::fn_sub_16F810_0016f810);  // (owner, index)
            v0 = v0 & 0xFF;
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s5;
            jal(ctx, 0x12F8FCu, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
            a0 = addiu(sp, 0x1A0);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x12F910u, gen::fn_sprintf_00523ac8);
            lh(a0, s1, equip::kSlot);
            v1 = 3;
            if (a0 == v1) {
                // 0x0012ff4c
                charge(ctx, 78);
                lbu(a3, s0, tw::kAlpha);
                a0 = s4;
                lw(a1, s1, equip::kFile0);
                a2 = 24;
                lwc1(f12, s0, tw::kX);
                lwc1(f13, s0, tw::kY);
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12FF68u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s0, tw::kX);
                v0 = 0x41980000;  // 19.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s4;
                lw(a1, s1, equip::kFile0);
                a2 = 6;
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12FFACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = sll(s2, 1);
                a2 = addiu(v0, 1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x43020000;  // 130.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s0, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s0, tw::kAlpha);
                a0 = s4;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f14, s0, tw::kZ);
                jal(ctx, 0x12FFF8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v1, s0, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s0, tw::kX);
                v0 = 0x432A0000;  // 170.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s0, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s0, tw::kZ);
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x1A0);
                t2 = 16;
                t3 = 0;
                jal(ctx, 0x130074u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
            } else {
                // 0x0012f928
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x0012fd80
                    charge(ctx, 115);
                    lbu(a3, s0, tw::kAlpha);
                    a0 = s4;
                    lw(a1, s1, equip::kFile0);
                    a2 = 24;
                    lwc1(f12, s0, tw::kX);
                    lwc1(f13, s0, tw::kY);
                    lwc1(f14, s0, tw::kZ);
                    jal(ctx, 0x12FD9Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lwc1(f1, s0, tw::kX);
                    v0 = 0x41980000;  // 19.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    lwc1(f1, s0, tw::kY);
                    v0 = 0x40C00000;  // 6.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s0, tw::kAlpha);
                    a0 = s4;
                    lw(a1, s1, equip::kFile0);
                    a2 = 4;
                    lwc1(f14, s0, tw::kZ);
                    jal(ctx, 0x12FDE0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = sll(s2, 1);
                    a2 = addiu(v0, 1);
                    lwc1(f1, s0, tw::kX);
                    v0 = 0x43020000;  // 130.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    lwc1(f1, s0, tw::kY);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s0, tw::kAlpha);
                    a0 = s4;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    lwc1(f14, s0, tw::kZ);
                    jal(ctx, 0x12FE2Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v1, s0, tw::kAlpha);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    lwc1(f1, s0, tw::kX);
                    v0 = 0x432A0000;  // 170.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    lwc1(f1, s0, tw::kY);
                    v0 = 0x41200000;  // 10.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = 0x40400000;  // 3.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    lwc1(f12, s0, tw::kZ);
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0x1A0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x12FEA8u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    lwc1(f1, s0, tw::kX);
                    v0 = 0x43D90000;  // 434.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x2A8);
                    lwc1(f1, s0, tw::kY);
                    v0 = 0x41700000;  // 15.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x2AC);
                    a0 = 1;
                    jal(ctx, 0x12FEE4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    s4 = v0;
                    lwc1(f0, s0, tw::kZ);
                    cvt_w_s(f0, f0);
                    mfc1(s2, f0);
                    lh(a0, s1, equip::kPc);
                    a1 = s3;
                    jal(ctx, 0x12FF04u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                    v0 = v0 & 0xFFFF;
                    sd(v0, sp, 0x0);
                    v0 = 3;
                    sd(v0, sp, 0x8);
                    a0 = s4;
                    a1 = 11;
                    ld(a2, sp, 0x2A8);
                    a3 = s2;
                    t0 = 255;
                    t1 = t0;
                    t2 = t0;
                    lw(t3, s0, tw::kAlpha);
                    jal(ctx, 0x12FF3Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                } else {
                    // 0x0012f934
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0012fbb4
                        charge(ctx, 115);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s1, equip::kFile0);
                        a2 = 24;
                        lwc1(f12, s0, tw::kX);
                        lwc1(f13, s0, tw::kY);
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x12FBD0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x41980000;  // 19.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x40C00000;  // 6.0f
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s1, equip::kFile0);
                        a2 = 2;
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x12FC14u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = sll(s2, 1);
                        a2 = addiu(v0, 1);
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x43020000;  // 130.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x3F800000;  // 1.0f
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x12FC60u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lw(v1, s0, tw::kAlpha);
                        v0 = 255;
                        v1 = subu(v0, v1);
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x432A0000;  // 170.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x41200000;  // 10.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40400000;  // 3.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        lwc1(f12, s0, tw::kZ);
                        a3 = 6;
                        t0 = 1;
                        t1 = addiu(sp, 0x1A0);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x12FCDCu, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x43D90000;  // 434.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x2A8);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x41700000;  // 15.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x2AC);
                        a0 = 1;
                        jal(ctx, 0x12FD18u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        s4 = v0;
                        lwc1(f0, s0, tw::kZ);
                        cvt_w_s(f0, f0);
                        mfc1(s2, f0);
                        lh(a0, s1, equip::kPc);
                        a1 = s3;
                        jal(ctx, 0x12FD38u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                        v0 = v0 & 0xFFFF;
                        sd(v0, sp, 0x0);
                        v0 = 3;
                        sd(v0, sp, 0x8);
                        a0 = s4;
                        a1 = 11;
                        ld(a2, sp, 0x2A8);
                        a3 = s2;
                        t0 = 255;
                        t1 = t0;
                        t2 = t0;
                        lw(t3, s0, tw::kAlpha);
                        jal(ctx, 0x12FD70u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                    } else {
                        // 0x0012f940
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0012f950
                            charge(ctx, 153);
                            lbu(a3, s0, tw::kAlpha);
                            a0 = s4;
                            lw(a1, s1, equip::kFile0);
                            a2 = 24;
                            lwc1(f12, s0, tw::kX);
                            lwc1(f13, s0, tw::kY);
                            lwc1(f14, s0, tw::kZ);
                            jal(ctx, 0x12F96Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lwc1(f1, s0, tw::kX);
                            v0 = 0x41980000;  // 19.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s0, tw::kY);
                            v0 = 0x40C00000;  // 6.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s0, tw::kAlpha);
                            a0 = s4;
                            lw(a1, s1, equip::kFile0);
                            a2 = 0;
                            lwc1(f14, s0, tw::kZ);
                            jal(ctx, 0x12F9B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            v0 = sll(s2, 1);
                            a2 = addiu(v0, 1);
                            lwc1(f1, s0, tw::kX);
                            v0 = 0x43020000;  // 130.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s0, tw::kY);
                            v0 = 0x3F800000;  // 1.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s0, tw::kAlpha);
                            a0 = s4;
                            v0 = 0x830000;
                            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                            lwc1(f14, s0, tw::kZ);
                            jal(ctx, 0x12F9FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lw(v1, s0, tw::kAlpha);
                            v0 = 255;
                            v1 = subu(v0, v1);
                            lwc1(f1, s0, tw::kX);
                            v0 = 0x432A0000;  // 170.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f1, s0, tw::kY);
                            v0 = 0x41200000;  // 10.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x40400000;  // 3.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = si(-256);
                            a2 = v1 | v0;
                            lwc1(f12, s0, tw::kZ);
                            a3 = 6;
                            t0 = 1;
                            t1 = addiu(sp, 0x1A0);
                            t2 = 16;
                            t3 = 0;
                            jal(ctx, 0x12FA78u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                            lwc1(f1, s0, tw::kX);
                            v0 = 0x43D90000;  // 434.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x2A8);
                            lwc1(f1, s0, tw::kY);
                            v0 = 0x41700000;  // 15.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x2AC);
                            a0 = 1;
                            jal(ctx, 0x12FAB4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            s4 = v0;
                            lwc1(f0, s0, tw::kZ);
                            cvt_w_s(f0, f0);
                            mfc1(s2, f0);
                            lh(a0, s1, equip::kPc);
                            a1 = s3;
                            jal(ctx, 0x12FAD4u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                            v0 = v0 & 0xFFFF;
                            sd(v0, sp, 0x0);
                            v0 = 3;
                            sd(v0, sp, 0x8);
                            a0 = s4;
                            a1 = 11;
                            ld(a2, sp, 0x2A8);
                            a3 = s2;
                            t0 = 255;
                            t1 = t0;
                            t2 = t0;
                            lw(t3, s0, tw::kAlpha);
                            jal(ctx, 0x12FB0Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                            v0 = 525;
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, s0, tw::kX);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x2A8);
                            lwc1(f1, s0, tw::kY);
                            v0 = 0x41700000;  // 15.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x2AC);
                            a0 = 1;
                            jal(ctx, 0x12FB4Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            s4 = v0;
                            lwc1(f0, s0, tw::kZ);
                            cvt_w_s(f0, f0);
                            mfc1(s2, f0);
                            lh(a0, s1, equip::kPc);
                            a1 = s3;
                            jal(ctx, 0x12FB6Cu, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                            v0 = v0 & 0xFFFF;
                            sd(v0, sp, 0x0);
                            v0 = 3;
                            sd(v0, sp, 0x8);
                            a0 = s4;
                            a1 = 11;
                            ld(a2, sp, 0x2A8);
                            a3 = s2;
                            t0 = 255;
                            t1 = t0;
                            t2 = t0;
                            lw(t3, s0, tw::kAlpha);
                            jal(ctx, 0x12FBA4u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                        } else {
                            // 0x0012f948
                            charge(ctx, 2);
                        }
                    }
                }
            }
            break;
        case 0x130084u:  // table[3]
            // 0x00130084
            charge(ctx, 22);
            v0 = 483;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s0, tw::kX);
            add_s(f12, f1, f0);
            lwc1(f1, s0, tw::kY);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            lw(a1, s1, equip::kFile0);
            a2 = 39;
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x1300C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v0, s1, equip::kCandidateCount);
            a0 = addiu(v0, -5);
            if (i64(a0) <= 0) {
                // 0x00130104
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001300dc
                charge(ctx, 10);
                lw(v1, s1, equip::kScroll);
                v0 = sll(v1, 4);
                v1 = subu(v0, v1);
                v0 = sll(v1, 2);
                v0 = subu(v0, v1);
                v0 = sll(v0, 1);
                div(v0, a0);
                mflo(v0);
            }
            // 0x00130108
            charge(ctx, 32);
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
            lwc1(f1, s0, tw::kY);
            v0 = 0x40400000;  // 3.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            add_s(f13, f0, f2);
            v0 = 483;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s0, tw::kX);
            add_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            lw(a1, s1, equip::kFile0);
            a2 = 40;
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x130158u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lh(a0, s1, equip::kPc);
            lh(a1, s1, equip::kSlot);
            jal(ctx, 0x130168u, gen::fn_datGetEquipmentIdx_0016cb80);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
            lh(a0, s1, equip::kSlot);
            v1 = 2;
            if (a0 == v1) {
                // 0x001301fc
                charge(ctx, 6);
                lh(a0, s1, equip::kPc);
                a1 = s2;
                jal(ctx, 0x130204u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                v1 = v0 & 0xFFFF;
                sw(v1, sp, 0x160);
            } else {
                // 0x00130188
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x001301dc
                    charge(ctx, 8);
                    lh(a0, s1, equip::kPc);
                    a1 = s2;
                    jal(ctx, 0x1301E4u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                    v1 = v0 & 0xFFFF;
                    sw(v1, sp, 0x170);
                } else {
                    // 0x00130194
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x001301a4
                        charge(ctx, 14);
                        lh(a0, s1, equip::kPc);
                        a1 = s2;
                        jal(ctx, 0x1301ACu, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                        v0 = v0 & 0xFFFF;
                        sw(v0, sp, 0x190);
                        lh(a0, s1, equip::kPc);
                        a1 = s2;
                        jal(ctx, 0x1301C4u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                        v1 = v0 & 0xFFFF;
                        sw(v1, sp, 0x180);
                    } else {
                        // 0x0013019c
                        charge(ctx, 2);
                    }
                }
            }
            // 0x00130214
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00130bc8
                charge(ctx, 3);
                v1 = slti(s2, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00130220
                charge(ctx, 6);
                lw(v1, s1, equip::kScroll);
                a0 = addu(v1, s2);
                lw(v1, s1, equip::kCandidateCount);
                at = slt(a0, v1);
                if (at != 0) {
                    // 0x00130238
                    charge(ctx, 42);
                    v0 = sll(a0, 1);
                    v0 = addu(s1, v0);
                    lhu(a1, v0, 40);
                    lh(a0, s1, equip::kPc);
                    jal(ctx, 0x130248u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                    a0 = v0;
                    jal(ctx, 0x130254u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                    sq(v0, sp, 0xF0);
                    lw(v0, s1, equip::kScroll);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 1);
                    v0 = addu(s1, v0);
                    lhu(a1, v0, 40);
                    lh(a0, s1, equip::kPc);
                    jal(ctx, 0x130278u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                    s3 = dsll32(v0, 16);
                    s3 = dsra32(s3, 16);
                    lw(v0, s1, equip::kScroll);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 1);
                    v0 = addu(s1, v0);
                    lhu(a1, v0, 40);
                    lh(a0, s1, equip::kPc);
                    jal(ctx, 0x1302A0u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                    v0 = v0 & 0xFF;
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    a0 = s3;
                    jal(ctx, 0x1302B8u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0x1A0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x1302CCu, gen::fn_sprintf_00523ac8);
                    lw(v1, s1, equip::kCursor);
                    if (v1 != s2) {
                        // 0x00130314
                        charge(ctx, 9);
                        v0 = 10;
                        sw(v0, sp, 0x130);
                        s6 = 2;
                        s7 = 31;
                        fp = 0x21;
                        s5 = 255;
                        sb(s5, sp, 0x100);
                        sb(s5, sp, 0x110);
                        sw(zero, sp, 0x12C);
                    } else {
                        // 0x001302e0
                        charge(ctx, 13);
                        v0 = 6;
                        sw(v0, sp, 0x130);
                        s6 = 1;
                        s7 = 30;
                        fp = 0x20;
                        s5 = 243;
                        v0 = 179;
                        sb(v0, sp, 0x100);
                        v0 = 189;
                        sb(v0, sp, 0x110);
                        sw(s6, sp, 0x12C);
                    }
                    // 0x00130338
                    charge(ctx, 2);
                    if (v1 == s2) {
                        // 0x00130340
                        charge(ctx, 35);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s2);
                        s3 = sll(v0, 1);
                        lwc1(f1, s0, tw::kY);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s1, equip::kFile0);
                        a2 = 37;
                        lwc1(f12, s0, tw::kX);
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x130380u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s0, tw::kY);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x43EB0000;  // 470.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s1, equip::kFile0);
                        a2 = 38;
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x1303C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x001303cc
                    charge(ctx, 3);
                    lw(v0, sp, 0x12C);
                    if (v0 != 0) {
                        // 0x00130464
                        charge(ctx, 30);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s2);
                        s3 = sll(v0, 1);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x40A00000;  // 5.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lq(v0, sp, 0xF0);
                        v1 = sll(v0, 1);
                        lw(v0, sp, 0x12C);
                        a2 = addu(v0, v1);
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x41500000;  // 13.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x1304D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x001303d8
                        charge(ctx, 35);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s2);
                        s3 = sll(v0, 1);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x40A00000;  // 5.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lq(v0, sp, 0xF0);
                        v1 = sll(v0, 1);
                        lw(v0, sp, 0x12C);
                        a2 = addu(v0, v1);
                        lwc1(f1, s0, tw::kX);
                        v0 = 0x41500000;  // 13.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s0, tw::kAlpha);
                        a0 = s4;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        t0 = 32;
                        t1 = 67;
                        t2 = 120;
                        lwc1(f14, s0, tw::kZ);
                        jal(ctx, 0x130454u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    }
                    // 0x001304dc
                    charge(ctx, 40);
                    lw(v1, s0, tw::kAlpha);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    lwc1(f1, s0, tw::kX);
                    v0 = 0x42540000;  // 53.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    lwc1(f1, s0, tw::kY);
                    v0 = 0x41100000;  // 9.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f1, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    lb(v0, sp, 0x130);
                    a3 = v0;
                    lwc1(f12, s0, tw::kZ);
                    t0 = 1;
                    t1 = addiu(sp, 0x1A0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x130564u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    lh(a0, s1, equip::kSlot);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x00130a34
                        charge(ctx, 31);
                        lw(v0, s1, equip::kScroll);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 1);
                        v0 = addu(s1, v0);
                        lhu(a1, v0, 40);
                        lh(a0, s1, equip::kPc);
                        jal(ctx, 0x130A4Cu, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                        v0 = v0 & 0xFFFF;
                        sq(v0, sp, 0xB0);
                        v0 = 317;
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s0, tw::kX);
                        add_s(f2, f1, f0);
                        swc1(f2, sp, 0x2A8);
                        lwc1(f1, s0, tw::kY);
                        v0 = 0x41100000;  // 9.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f1, f0);
                        swc1(f1, sp, 0x2AC);
                        lw(v1, sp, 0x160);
                        lq(v0, sp, 0xB0);
                        if (v1 != v0) {
                            // 0x00130ac4
                            charge(ctx, 5);
                            paddub(v1, v0, zero);
                            lw(v0, sp, 0x160);
                            at = slt(v0, v1);
                            if (at == 0) {
                                // 0x00130b30
                                charge(ctx, 18);
                                v0 = 0x42440000;  // 49.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f2);
                                v0 = 0x40400000;  // 3.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s0, tw::kAlpha);
                                a0 = s4;
                                lw(a1, s1, equip::kFile0);
                                a2 = fp;
                                lwc1(f14, s0, tw::kZ);
                                jal(ctx, 0x130B64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                s3 = 255;
                                s5 = s3;
                                s7 = s3;
                            } else {
                                // 0x00130ad8
                                charge(ctx, 22);
                                v0 = 0x42440000;  // 49.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f2);
                                v0 = 0x40400000;  // 3.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s0, tw::kAlpha);
                                a0 = s4;
                                lw(a1, s1, equip::kFile0);
                                a2 = s7;
                                lwc1(f14, s0, tw::kZ);
                                jal(ctx, 0x130B0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                s3 = s5 & 0xFF;
                                lbu(v0, sp, 0x100);
                                s5 = v0;
                                lbu(v0, sp, 0x110);
                                s7 = v0;
                            }
                        } else {
                            // 0x00130ab0
                            charge(ctx, 5);
                            s3 = 255;
                            s5 = s3;
                            s7 = s3;
                        }
                        // 0x00130b78
                        charge(ctx, 19);
                        a0 = s6;
                        jal(ctx, 0x130B7Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        lwc1(f0, s0, tw::kZ);
                        cvt_w_s(f0, f0);
                        mfc1(a3, f0);
                        lq(v1, sp, 0xB0);
                        sd(v1, sp, 0x0);
                        v1 = 3;
                        sd(v1, sp, 0x8);
                        a0 = v0;
                        a1 = 11;
                        ld(a2, sp, 0x2A8);
                        t0 = s3;
                        t1 = s5;
                        t2 = s7;
                        lw(t3, s0, tw::kAlpha);
                        jal(ctx, 0x130BBCu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                    } else {
                        // 0x0013057c
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0013089c
                            charge(ctx, 31);
                            lw(v0, s1, equip::kScroll);
                            v0 = addu(v0, s2);
                            v0 = sll(v0, 1);
                            v0 = addu(s1, v0);
                            lhu(a1, v0, 40);
                            lh(a0, s1, equip::kPc);
                            jal(ctx, 0x1308B4u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                            v0 = v0 & 0xFFFF;
                            sq(v0, sp, 0xC0);
                            v0 = 317;
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, s0, tw::kX);
                            add_s(f2, f1, f0);
                            swc1(f2, sp, 0x2A8);
                            lwc1(f1, s0, tw::kY);
                            v0 = 0x41100000;  // 9.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f1, f0);
                            swc1(f1, sp, 0x2AC);
                            lw(v1, sp, 0x170);
                            lq(v0, sp, 0xC0);
                            if (v1 != v0) {
                                // 0x0013092c
                                charge(ctx, 5);
                                paddub(v1, v0, zero);
                                lw(v0, sp, 0x170);
                                at = slt(v0, v1);
                                if (at == 0) {
                                    // 0x00130998
                                    charge(ctx, 18);
                                    v0 = 0x42440000;  // 49.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f2);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s0, tw::kAlpha);
                                    a0 = s4;
                                    lw(a1, s1, equip::kFile0);
                                    a2 = fp;
                                    lwc1(f14, s0, tw::kZ);
                                    jal(ctx, 0x1309CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s3 = 255;
                                    s5 = s3;
                                    s7 = s3;
                                } else {
                                    // 0x00130940
                                    charge(ctx, 22);
                                    v0 = 0x42440000;  // 49.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f2);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s0, tw::kAlpha);
                                    a0 = s4;
                                    lw(a1, s1, equip::kFile0);
                                    a2 = s7;
                                    lwc1(f14, s0, tw::kZ);
                                    jal(ctx, 0x130974u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s3 = s5 & 0xFF;
                                    lbu(v0, sp, 0x100);
                                    s5 = v0;
                                    lbu(v0, sp, 0x110);
                                    s7 = v0;
                                }
                            } else {
                                // 0x00130918
                                charge(ctx, 5);
                                s3 = 255;
                                s5 = s3;
                                s7 = s3;
                            }
                            // 0x001309e0
                            charge(ctx, 21);
                            a0 = s6;
                            jal(ctx, 0x1309E4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            lwc1(f0, s0, tw::kZ);
                            cvt_w_s(f0, f0);
                            mfc1(a3, f0);
                            lq(v1, sp, 0xC0);
                            sd(v1, sp, 0x0);
                            v1 = 3;
                            sd(v1, sp, 0x8);
                            a0 = v0;
                            a1 = 11;
                            ld(a2, sp, 0x2A8);
                            t0 = s3;
                            t1 = s5;
                            t2 = s7;
                            lw(t3, s0, tw::kAlpha);
                            jal(ctx, 0x130A24u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                        } else {
                            // 0x00130588
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x00130598
                                charge(ctx, 31);
                                lw(v0, s1, equip::kScroll);
                                v0 = addu(v0, s2);
                                v0 = sll(v0, 1);
                                v0 = addu(s1, v0);
                                lhu(a1, v0, 40);
                                lh(a0, s1, equip::kPc);
                                jal(ctx, 0x1305B0u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                                v0 = v0 & 0xFFFF;
                                sq(v0, sp, 0xE0);
                                v0 = 317;
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lwc1(f0, s0, tw::kX);
                                add_s(f2, f1, f0);
                                swc1(f2, sp, 0x2A8);
                                lwc1(f1, s0, tw::kY);
                                v0 = 0x41100000;  // 9.0f
                                mtc1(v0, f0);
                                add_s(f1, f0, f1);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                swc1(f1, sp, 0x2AC);
                                lw(v1, sp, 0x190);
                                lq(v0, sp, 0xE0);
                                if (v1 != v0) {
                                    // 0x00130628
                                    charge(ctx, 5);
                                    paddub(v1, v0, zero);
                                    lw(v0, sp, 0x190);
                                    at = slt(v0, v1);
                                    if (at == 0) {
                                        // 0x00130694
                                        charge(ctx, 18);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f2);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s0, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s1, equip::kFile0);
                                        a2 = fp;
                                        lwc1(f14, s0, tw::kZ);
                                        jal(ctx, 0x1306C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = 255;
                                        sb(s3, sp, 0x150);
                                        sb(s3, sp, 0x140);
                                    } else {
                                        // 0x0013063c
                                        charge(ctx, 22);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f2);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s0, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s1, equip::kFile0);
                                        a2 = s7;
                                        lwc1(f14, s0, tw::kZ);
                                        jal(ctx, 0x130670u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = s5 & 0xFF;
                                        lbu(v0, sp, 0x100);
                                        sb(v0, sp, 0x150);
                                        lbu(v0, sp, 0x110);
                                        sb(v0, sp, 0x140);
                                    }
                                } else {
                                    // 0x00130614
                                    charge(ctx, 5);
                                    s3 = 255;
                                    sb(s3, sp, 0x150);
                                    sb(s3, sp, 0x140);
                                }
                                // 0x001306dc
                                charge(ctx, 39);
                                a0 = s6;
                                jal(ctx, 0x1306E0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f0, s0, tw::kZ);
                                cvt_w_s(f0, f0);
                                mfc1(a3, f0);
                                lq(v1, sp, 0xE0);
                                sd(v1, sp, 0x0);
                                v1 = 3;
                                sd(v1, sp, 0x8);
                                a0 = v0;
                                a1 = 11;
                                ld(a2, sp, 0x2A8);
                                t0 = s3;
                                lbu(t1, sp, 0x150);
                                lbu(t2, sp, 0x140);
                                lw(t3, s0, tw::kAlpha);
                                jal(ctx, 0x130720u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                                lw(v0, s1, equip::kScroll);
                                v0 = addu(v0, s2);
                                v0 = sll(v0, 1);
                                v0 = addu(s1, v0);
                                lhu(a1, v0, 40);
                                lh(a0, s1, equip::kPc);
                                jal(ctx, 0x130740u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                                v0 = v0 & 0xFFFF;
                                sq(v0, sp, 0xD0);
                                lwc1(f1, sp, 0x2A8);
                                v0 = 0x42B60000;  // 91.0f
                                mtc1(v0, f0);
                                add_s(f1, f1, f0);
                                swc1(f1, sp, 0x2A8);
                                lw(v1, sp, 0x180);
                                lq(v0, sp, 0xD0);
                                if (v1 != v0) {
                                    // 0x0013078c
                                    charge(ctx, 5);
                                    paddub(v1, v0, zero);
                                    lw(v0, sp, 0x180);
                                    at = slt(v0, v1);
                                    if (at == 0) {
                                        // 0x001307fc
                                        charge(ctx, 19);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f1);
                                        lwc1(f1, sp, 0x2AC);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s0, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s1, equip::kFile0);
                                        a2 = fp;
                                        lwc1(f14, s0, tw::kZ);
                                        jal(ctx, 0x130834u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = 255;
                                        s5 = s3;
                                        s7 = s3;
                                    } else {
                                        // 0x001307a0
                                        charge(ctx, 23);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f1);
                                        lwc1(f1, sp, 0x2AC);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s0, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s1, equip::kFile0);
                                        a2 = s7;
                                        lwc1(f14, s0, tw::kZ);
                                        jal(ctx, 0x1307D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = s5 & 0xFF;
                                        lbu(v0, sp, 0x100);
                                        s5 = v0;
                                        lbu(v0, sp, 0x110);
                                        s7 = v0;
                                    }
                                } else {
                                    // 0x00130778
                                    charge(ctx, 5);
                                    s3 = 255;
                                    s5 = s3;
                                    s7 = s3;
                                }
                                // 0x00130848
                                charge(ctx, 21);
                                a0 = s6;
                                jal(ctx, 0x13084Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f0, s0, tw::kZ);
                                cvt_w_s(f0, f0);
                                mfc1(a3, f0);
                                lq(v1, sp, 0xD0);
                                sd(v1, sp, 0x0);
                                v1 = 3;
                                sd(v1, sp, 0x8);
                                a0 = v0;
                                a1 = 11;
                                ld(a2, sp, 0x2A8);
                                t0 = s3;
                                t1 = s5;
                                t2 = s7;
                                lw(t3, s0, tw::kAlpha);
                                jal(ctx, 0x13088Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                            } else {
                                // 0x00130590
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00130bc4
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00130bd4
            charge(ctx, 2);
            break;
        case 0x130BDCu:  // table[4]
            // 0x00130bdc
            charge(ctx, 25);
            a0 = 0;
            lw(a1, s1, equip::kFile0);
            a2 = 27;
            jal(ctx, 0x130BE8u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s4 = v0;
            lwc1(f0, s0, tw::kZ);
            swc1(f0, v0, 44);
            lwc1(f0, s0, tw::kX);
            swc1(f0, v0, 16);
            lwc1(f0, s0, tw::kY);
            swc1(f0, v0, 20);
            lw(v1, s0, tw::kAlpha);
            sb(v1, v0, 24);
            v1 = lui(0xC234);
            sw(v1, v0, 32);
            a0 = s4;
            a1 = 1;
            jal(ctx, 0x130C24u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s4;
            jal(ctx, 0x130C30u, gen::fn_sub_115980_00115980);  // draw and release the handle
            break;
        case 0x130C40u:  // table[6]
            // 0x00130c40
            charge(ctx, 45);
            lw(v1, s0, tw::kAlpha);
            v0 = 255;
            s5 = subu(v0, v1);
            lwc1(f0, s0, tw::kX);
            cvt_w_s(f0, f0);
            mfc1(s4, f0);
            lwc1(f0, s0, tw::kY);
            cvt_w_s(f0, f0);
            mfc1(s3, f0);
            lw(v1, s1, equip::kCursor);
            lw(v0, s1, equip::kScroll);
            v0 = addu(v1, v0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s1);
            lhu(a1, v0, 40);
            lh(a0, s1, equip::kPc);
            jal(ctx, 0x130C80u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s2 = v0 & 0xFFFF;
            lw(v1, s1, equip::kCursor);
            lw(v0, s1, equip::kScroll);
            v0 = addu(v1, v0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s1);
            lhu(a1, v0, 40);
            lh(a0, s1, equip::kPc);
            jal(ctx, 0x130CA8u, gen::fn_sub_16F900_0016f900);  // (owner, index)
            v0 = v0 & 0xFF;
            v1 = sll(v0, 16);
            v0 = lui(0xFFFF);
            v0 = v1 & v0;
            t2 = s2 | v0;
            v0 = si(-256);
            a2 = s5 | v0;
            a0 = s4;
            a1 = s3;
            lwc1(f12, s0, tw::kZ);
            a3 = 1;
            t0 = 10;
            t1 = a3;
            jal(ctx, 0x130CE4u, gen::fn_sub_3C7E20_003c7e20);  // a message text
            break;
        case 0x130CF4u:  // table[7]
            // 0x00130cf4
            charge(ctx, 67);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            lw(a1, s1, equip::kFile1);
            a2 = 0;
            lwc1(f12, s0, tw::kX);
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x130D10u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s0, tw::kX);
            v0 = 0x42300000;  // 44.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            lw(a1, s1, equip::kFile1);
            a2 = 6;
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x130D54u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s0, tw::kX);
            v0 = 0x43F30000;  // 486.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            v0 = 0x41F00000;  // 30.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 2;
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x130DACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 561;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s0, tw::kX);
            add_s(f1, f1, f0);
            v0 = 0x41E00000;  // 28.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s0, tw::kAlpha);
            a0 = s4;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 1;
            lwc1(f13, s0, tw::kY);
            lwc1(f14, s0, tw::kZ);
            jal(ctx, 0x130DF8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x130E00u:  // table[5]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00130e00 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x2B0);
}

// 0x001311D0 sub_1311D0 -- 8108 bytes; frame 0xF0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_UpdateCampStatusPersonaDrawTask] Update of the persona screen "H_CampStatusPersonaDraw" (jump table
// 0x7B5C40): 0 waits for flash 4, allocates the tweens (+100 x100, +104 x10), requests camp/camp_per.pak (+80) and
// lists the used stock slots (ids +26, slots +50, count +74; printf "stock ID = %d"); 1 takes its three sprite files
// and creates the persona picture (+84); 2 waits; 3 slides the rows in (y 73 + 29 row); 4 is the list (confirm -> 7
// detail, 0x80 -> 11 release, cancel -> 5; up / down with wrap on a fresh press, the picture follows the cursor through
// sub_133B80); 5 / 6 close; 7..10 the detail view (sub_134900) and back; 0xB..0xD release a persona (the active one
// refused with message 2, else message 1 yes / no -> sub_174C10, the list rebuilt); 0xE / 0xF make the selected persona
// the protagonist's (message 3 -> datPersonaSelectSlot, sub_11B370).
void sub_1311D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x001311d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, per::kState);
    at = sltiu(v0, 16);
    if (at != 0) {
        // 0x00131204
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23616);  // &0x7B5C40
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x131220u:  // table[0]: state 0: wait for flash 4, tweens, camp_per.pak, list the stock
            // 0x00131220
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 4;
            jal(ctx, 0x131228u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00131244
                charge(ctx, 18);
                a0 = 100;
                jal(ctx, 0x131248u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, per::kTweens);
                a0 = 10;
                jal(ctx, 0x131258u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, per::kDetailTweens);
                a0 = 0x5E0000;
                a0 = addiu(a0, -20160);  // "camp/camp_per.pak"
                a1 = 1;
                jal(ctx, 0x131270u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, per::kPak);
                s3 = 0;
                s4 = 0;
                for (;;) {
                    // 0x001312f8
                    charge(ctx, 3);
                    v0 = slti(s4, 12);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0013128c
                    charge(ctx, 10);
                    v0 = sll(s3, 1);
                    v0 = addu(s0, v0);
                    s2 = addiu(v0, 26);
                    sh(zero, v0, 26);
                    a0 = dsll32(s4, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x1312A4u, gen::fn_sub_174960_00174960);  // [datPersonaIsSlotUsed]
                    if (v0 != 0) {
                        // 0x001312b4
                        charge(ctx, 16);
                        a0 = dsll32(s4, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x1312BCu, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
                        s1 = v0;
                        lhu(a1, v0, 2);
                        a0 = 0x5E0000;
                        a0 = addiu(a0, -20136);  // "stock ID = %d\n"
                        jal(ctx, 0x1312D4u, gen::fn_printf_005225a8);
                        v0 = sll(s3, 1);
                        v1 = addu(s0, v0);
                        lhu(v0, s1, 2);
                        sh(v0, s2, 0);
                        sh(s4, v1, 50);
                        s3 = addiu(s3, 1);
                    }
                    // 0x001312f4
                    charge(ctx, 1);
                    s4 = addiu(s4, 1);
                }
                // 0x00131304
                charge(ctx, 5);
                sh(s3, s0, per::kCount);
                v0 = 1;
                sw(v0, s0, per::kState);
            L_00133154:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00131238
                charge(ctx, 3);
                v0 = 0;
            }
            break;
        case 0x131318u:  // table[1]: state 1: sprite files, persona picture
            // 0x00131318
            charge(ctx, 5);
            lw(a0, s0, per::kPak);
            jal(ctx, 0x13131Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0013132c
                charge(ctx, 40);
                lw(a0, s0, per::kPak);
                a1 = 0;
                a2 = addiu(sp, 0xEC);
                jal(ctx, 0x131338u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x131344u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, per::kFiles);
                lw(a0, s0, per::kPak);
                a1 = 1;
                a2 = addiu(sp, 0xEC);
                jal(ctx, 0x13135Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x131368u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, per::kFile1);
                lw(a0, s0, per::kPak);
                a1 = 2;
                a2 = addiu(sp, 0xEC);
                jal(ctx, 0x131380u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x13138Cu, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, per::kFile2);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lhu(a2, s0, per::kIds);
                a0 = s1;
                a1 = 6335;
                a3 = si(-1);
                jal(ctx, 0x1313B0u, gen::fn_sub_1339A0_001339a0);  // [H_Camp_CreatePersonaDispCtlDrawTask]
                sw(v0, s0, per::kPicture);
                v0 = 2;
                sw(v0, s0, per::kState);
            }
            goto L_00133154;
        case 0x1313CCu:  // table[2]: state 2: wait for the files
            // 0x001313cc
            charge(ctx, 5);
            lw(a0, s0, per::kFiles);
            jal(ctx, 0x1313D0u, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x001313e0
                charge(ctx, 5);
                lw(a0, s0, per::kFile1);
                jal(ctx, 0x1313E4u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x001313f4
                    charge(ctx, 5);
                    lw(a0, s0, per::kFile2);
                    jal(ctx, 0x1313F8u, gen::fn_sprFileIsReady_00111f30);
                    if (v0 != 0) {
                        // 0x00131408
                        charge(ctx, 4);
                        v0 = 3;
                        sw(v0, s0, per::kState);
                    }
                }
            }
            goto L_00133154;
        case 0x131418u:  // table[3]: state 3: slide the rows in
            // 0x00131418
            charge(ctx, 20);
            sw(zero, sp, 0xD8);
            sw(zero, sp, 0xDC);
            v0 = 5;
            sd(v0, sp, 0x0);
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, per::kTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xD8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x131454u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            s1 = 0;
            for (;;) {
                // 0x00131538
                charge(ctx, 4);
                lh(v0, s0, per::kCount);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00131468
                charge(ctx, 18);
                v0 = 0x42EE0000;  // 119.0f
                mtc1(v0, f2);
                sw(v0, sp, 0xD8);
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42920000;  // 73.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xDC);
                lw(v0, s0, per::kCursor);
                if (s1 == v0) {
                    // 0x001314b0
                    charge(ctx, 5);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0xD8);
                }
                // 0x001314c4
                charge(ctx, 29);
                ld(v0, sp, 0xD8);
                sd(v0, sp, 0xE0);
                lwc1(f1, sp, 0xE0);
                v0 = 0x44160000;  // 600.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0xE0);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 1);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, per::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xE0);
                ld(t1, sp, 0xD8);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x13152Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00131548
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00131624
                charge(ctx, 4);
                lh(v0, s0, per::kCount);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00131554
                charge(ctx, 18);
                v0 = lui(0xC130);
                mtc1(v0, f2);
                sw(v0, sp, 0xD8);
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x427C0000;  // 63.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xDC);
                lw(v0, s0, per::kCursor);
                if (s1 == v0) {
                    // 0x0013159c
                    charge(ctx, 5);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0xD8);
                }
                // 0x001315b0
                charge(ctx, 29);
                ld(v0, sp, 0xD8);
                sd(v0, sp, 0x70);
                lwc1(f1, sp, 0x70);
                v0 = 0x44160000;  // 600.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x70);
                sd(zero, sp, 0x0);
                v0 = 6;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 14);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, per::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x70);
                ld(t1, sp, 0xD8);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x131618u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00131634
            charge(ctx, 66);
            v0 = 497;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xD8);
            v0 = 0x41D00000;  // 26.0f
            sw(v0, sp, 0xDC);
            ld(v0, sp, 0xD8);
            sd(v0, sp, 0x78);
            lwc1(f1, sp, 0x78);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x78);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, per::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1836);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x78);
            ld(t1, sp, 0xD8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1316A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42080000;  // 34.0f
            sw(v0, sp, 0xD8);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xDC);
            ld(v0, sp, 0xD8);
            sd(v0, sp, 0x80);
            lwc1(f1, sp, 0x80);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x80);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, per::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1904);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x80);
            ld(t1, sp, 0xD8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x131724u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 4;
            sw(v0, s0, per::kState);
            goto L_00133154;
        case 0x13173Cu:  // table[4]: state 4: the list (input)
            // 0x0013173c
            charge(ctx, 3);
            lw(v0, s0, per::kArrived);
            if (v0 != 0) {
                // 0x00131748
                charge(ctx, 6);
                lw(s2, s0, per::kCursor);
                v0 = 0x7E0000;
                lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a0 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x00131788
                    charge(ctx, 3);
                    v0 = a0 & 0x80;
                    if (v0 == 0) {
                        // 0x001317bc
                        charge(ctx, 3);
                        v0 = a0 & 0x20;
                        if (v0 == 0) {
                            // 0x001317f0
                            charge(ctx, 6);
                            a1 = 1;
                            v0 = 0x7E0000;
                            lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                            v0 = v1 & 0x1000;  // cursor - 1
                            if (v0 == 0) {
                                // 0x00131808
                                charge(ctx, 5);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x1000;  // cursor - 1
                                if (v0 == 0) {
                                    // 0x0013181c
                                    charge(ctx, 1);
                                    a1 = 0;
                                }
                            }
                            // 0x00131820
                            charge(ctx, 2);
                            if (a1 == 0) {
                                // 0x001318c0
                                charge(ctx, 4);
                                v0 = v1 & 0x4000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x001318d0
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                    v0 = v0 & 0x4000;  // cursor + 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x001318e0
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x001318e8
                                    charge(ctx, 4);
                                    lh(v1, s0, per::kCount);
                                    v0 = addiu(v1, -1);
                                    if (s2 == v0) {
                                        // 0x00131924
                                        charge(ctx, 4);
                                        v0 = a0 & 0x4000;
                                        v0 = sltu(0, v0);
                                        if (v0 == 0) {
                                            // 0x00131934
                                            charge(ctx, 4);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                            v0 = v0 & 0x4000;  // cursor + 1
                                            v0 = sltu(0, v0);
                                        }
                                        // 0x00131944
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0013194c
                                            charge(ctx, 3);
                                            v0 = 1;
                                            if (v1 != v0) {
                                                // 0x00131958
                                                charge(ctx, 7);
                                                a0 = 0;
                                                a1 = 0;
                                                a2 = 0;
                                                a3 = 0;
                                                jal(ctx, 0x131968u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                                sw(zero, s0, per::kCursor);
                                            }
                                        }
                                    } else {
                                        // 0x001318f8
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x131908u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, per::kCursor);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, per::kCursor);
                                    }
                                }
                            } else {
                                // 0x00131828
                                charge(ctx, 2);
                                if (s2 == 0) {
                                    // 0x0013185c
                                    charge(ctx, 4);
                                    v0 = a0 & 0x1000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0013186c
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x1000;  // cursor - 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0013187c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00131884
                                        charge(ctx, 4);
                                        lh(v1, s0, per::kCount);
                                        v0 = 1;
                                        if (v1 != v0) {
                                            // 0x00131894
                                            charge(ctx, 11);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x1318A4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            lh(v0, s0, per::kCount);
                                            v0 = addiu(v0, -1);
                                            sw(v0, s0, per::kCursor);
                                        }
                                    }
                                } else {
                                    // 0x00131830
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x131840u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, per::kCursor);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s0, per::kCursor);
                                }
                            }
                        } else {
                            // 0x001317c8
                            charge(ctx, 10);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 2;
                            jal(ctx, 0x1317D8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            v0 = 5;
                            sw(v0, s0, per::kState);
                        }
                    } else {
                        // 0x00131794
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x1317A4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 11;
                        sw(v0, s0, per::kState);
                    }
                } else {
                    // 0x00131760
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x131770u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 7;
                    sw(v0, s0, per::kState);
                }
                // 0x00131974
                charge(ctx, 3);
                lw(v0, s0, per::kCursor);
                if (v0 != s2) {
                    // 0x00131980
                    charge(ctx, 158);
                    v0 = 0x42EE0000;  // 119.0f
                    sw(v0, sp, 0xD8);
                    v0 = sll(s2, 3);
                    v0 = subu(v0, s2);
                    v0 = sll(v0, 2);
                    s1 = addu(v0, s2);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f1);
                    mtc1(s1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xDC);
                    ld(v0, sp, 0xD8);
                    sd(v0, sp, 0x88);
                    lwc1(f1, sp, 0x88);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x88);
                    sd(zero, sp, 0x0);
                    a2 = 2;
                    sd(a2, sp, 0x8);
                    v1 = addiu(s2, 1);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a3 = 0;
                    ld(t0, sp, 0x88);
                    ld(t1, sp, 0xD8);
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x131A18u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    v0 = lui(0xC130);
                    sw(v0, sp, 0xD8);
                    v0 = 0x427C0000;  // 63.0f
                    mtc1(v0, f1);
                    mtc1(s1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0xDC);
                    ld(v0, sp, 0xD8);
                    sd(v0, sp, 0x90);
                    lwc1(f1, sp, 0x90);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x90);
                    sd(zero, sp, 0x0);
                    a2 = 2;
                    sd(a2, sp, 0x8);
                    v1 = addiu(s2, 14);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a3 = 0;
                    ld(t0, sp, 0x90);
                    ld(t1, sp, 0xD8);
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x131AA8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    v0 = 0x42EE0000;  // 119.0f
                    mtc1(v0, f2);
                    sw(v0, sp, 0xD8);
                    lw(v1, s0, per::kCursor);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xDC);
                    ld(t0, sp, 0xD8);
                    sd(t0, sp, 0x98);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0xD8);
                    sd(zero, sp, 0x0);
                    a2 = 2;
                    sd(a2, sp, 0x8);
                    v1 = addiu(v1, 1);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a3 = 0;
                    ld(t1, sp, 0xD8);
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x131B4Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    v0 = lui(0xC130);
                    mtc1(v0, f2);
                    sw(v0, sp, 0xD8);
                    lw(v1, s0, per::kCursor);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x427C0000;  // 63.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xDC);
                    ld(t0, sp, 0xD8);
                    sd(t0, sp, 0xA0);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0xD8);
                    sd(zero, sp, 0x0);
                    a2 = 2;
                    sd(a2, sp, 0x8);
                    v1 = addiu(v1, 14);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a3 = 0;
                    ld(t1, sp, 0xD8);
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x131BF0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                }
                // 0x00131bf8
                charge(ctx, 8);
                lw(v0, s0, per::kCursor);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                lhu(a1, v0, 26);
                lw(a0, s0, per::kPicture);
                a2 = si(-1);
                jal(ctx, 0x131C10u, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            }
            // 0x00131c18
            charge(ctx, 12);
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x131C1Cu, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x131C34u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            sw(v0, s0, per::kArrived);
            goto L_00133154;
        case 0x131C48u:  // table[5]: state 5: slide out
            // 0x00131c48
            charge(ctx, 22);
            lw(a0, s0, per::kTweens);
            lwc1(f1, a0, 56);
            lwc1(f0, a0, 60);
            swc1(f1, sp, 0xD8);
            swc1(f0, sp, 0xDC);
            v0 = 5;
            sd(v0, sp, 0x0);
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xD8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x131C8Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            s1 = 0;
            for (;;) {
                // 0x00131d50
                charge(ctx, 4);
                lh(v0, s0, per::kCount);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00131ca0
                charge(ctx, 18);
                v0 = 0x42EE0000;  // 119.0f
                mtc1(v0, f2);
                sw(v0, sp, 0xD8);
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42920000;  // 73.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xDC);
                lw(v0, s0, per::kCursor);
                if (s1 == v0) {
                    // 0x00131ce8
                    charge(ctx, 5);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0xD8);
                }
                // 0x00131cfc
                charge(ctx, 21);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 1);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, per::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x131D44u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00131d60
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00131e1c
                charge(ctx, 4);
                lh(v0, s0, per::kCount);
                v0 = slt(s1, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00131d6c
                charge(ctx, 18);
                v0 = lui(0xC130);
                mtc1(v0, f2);
                sw(v0, sp, 0xD8);
                v0 = sll(s1, 3);
                v0 = subu(v0, s1);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x427C0000;  // 63.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0xDC);
                lw(v0, s0, per::kCursor);
                if (s1 == v0) {
                    // 0x00131db4
                    charge(ctx, 5);
                    v0 = 0x41A80000;  // 21.0f
                    mtc1(v0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0xD8);
                }
                // 0x00131dc8
                charge(ctx, 21);
                sd(zero, sp, 0x0);
                v0 = 6;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 14);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, per::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x131E10u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00131e2c
            charge(ctx, 56);
            v0 = 497;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xD8);
            v0 = 0x41D00000;  // 26.0f
            sw(v0, sp, 0xDC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, per::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1836);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xD8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x131E80u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42080000;  // 34.0f
            sw(v0, sp, 0xD8);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xDC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, per::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1904);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xD8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x131EDCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x131EF4u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            v0 = 6;
            sw(v0, s0, per::kState);
            goto L_00133154;
        case 0x131F0Cu:  // table[6]: state 6: done (-1)
            // 0x00131f0c
            charge(ctx, 8);
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x131F1Cu, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            if (v0 == 0) {
                goto L_00133154;
            }
            // 0x00131f2c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x131F38u:  // table[7]: state 7: wait for flash 5, open the detail
            // 0x00131f38
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 5;
            jal(ctx, 0x131F40u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00131f50
                charge(ctx, 22);
                lw(a0, s0, per::kTweens);
                lwc1(f1, a0, 56);
                lwc1(f0, a0, 60);
                swc1(f1, sp, 0xD0);
                swc1(f0, sp, 0xD4);
                v0 = 5;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD0);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x131F94u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = 0;
                for (;;) {
                    // 0x00132058
                    charge(ctx, 4);
                    lh(v0, s0, per::kCount);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00131fa8
                    charge(ctx, 18);
                    v0 = 0x42EE0000;  // 119.0f
                    mtc1(v0, f2);
                    sw(v0, sp, 0xD0);
                    v0 = sll(s1, 3);
                    v0 = subu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xD4);
                    lw(v0, s0, per::kCursor);
                    if (s1 == v0) {
                        // 0x00131ff0
                        charge(ctx, 5);
                        v0 = 0x41A80000;  // 21.0f
                        mtc1(v0, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, sp, 0xD0);
                    }
                    // 0x00132004
                    charge(ctx, 21);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v1 = addiu(s1, 1);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a2 = 2;
                    a3 = a2;
                    ld(t0, sp, 0xD0);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x13204Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    s1 = addiu(s1, 1);
                }
                // 0x00132068
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00132124
                    charge(ctx, 4);
                    lh(v0, s0, per::kCount);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00132074
                    charge(ctx, 18);
                    v0 = lui(0xC130);
                    mtc1(v0, f2);
                    sw(v0, sp, 0xD0);
                    v0 = sll(s1, 3);
                    v0 = subu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x427C0000;  // 63.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xD4);
                    lw(v0, s0, per::kCursor);
                    if (s1 == v0) {
                        // 0x001320bc
                        charge(ctx, 5);
                        v0 = 0x41A80000;  // 21.0f
                        mtc1(v0, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, sp, 0xD0);
                    }
                    // 0x001320d0
                    charge(ctx, 21);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v1 = addiu(s1, 14);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a2 = 2;
                    a3 = a2;
                    ld(t0, sp, 0xD0);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x132118u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    s1 = addiu(s1, 1);
                }
                // 0x00132134
                charge(ctx, 170);
                v0 = 497;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xD0);
                v0 = 0x41D00000;  // 26.0f
                sw(v0, sp, 0xD4);
                ld(t0, sp, 0xD0);
                sd(t0, sp, 0xA8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                add_s(f0, f0, f12);
                swc1(f0, sp, 0xD0);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v0, s0, per::kTweens);
                a0 = addiu(v0, 1836);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t1, sp, 0xD0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132198u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42080000;  // 34.0f
                mtc1(v0, f1);
                sw(v0, sp, 0xD0);
                v0 = 415;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xD4);
                ld(t0, sp, 0xD0);
                sd(t0, sp, 0xB0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                sub_s(f0, f1, f12);
                swc1(f0, sp, 0xD0);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v0, s0, per::kTweens);
                a0 = addiu(v0, 1904);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t1, sp, 0xD0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132208u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, sp, 0xD0);
                sw(zero, sp, 0xD4);
                ld(v0, sp, 0xD0);
                sd(v0, sp, 0xB8);
                lwc1(f1, sp, 0xB8);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0xB8);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lw(a0, s0, per::kDetailTweens);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xB8);
                ld(t1, sp, 0xD0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x13226Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42280000;  // 42.0f
                sw(v0, sp, 0xD0);
                v0 = 0x41400000;  // 12.0f
                sw(v0, sp, 0xD4);
                v0 = 8;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 136);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD0);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x1322BCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 519;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xD0);
                v0 = 0x41400000;  // 12.0f
                sw(v0, sp, 0xD4);
                v0 = 8;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 204);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD0);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132318u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x432A0000;  // 170.0f
                sw(v0, sp, 0xD0);
                v0 = 0x41000000;  // 8.0f
                sw(v0, sp, 0xD4);
                v0 = 8;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 272);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD0);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132368u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42080000;  // 34.0f
                sw(v0, sp, 0xD0);
                v0 = 415;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xD4);
                v0 = 8;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 340);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD0);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x1323C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, s0, 8);
                sw(zero, s0, per::kArrived);
                v0 = 8;
                sw(v0, s0, per::kState);
            }
            // 0x001323dc
            charge(ctx, 19);
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lhu(a1, v0, 26);
            lw(a0, s0, per::kPicture);
            a2 = si(-1);
            jal(ctx, 0x1323F4u, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132400u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132418u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            goto L_00133154;
        case 0x132428u:  // table[8]: state 8: the detail (input)
            // 0x00132428
            charge(ctx, 3);
            lw(v0, s0, per::kArrived);
            if (v0 != 0) {
                // 0x00132434
                charge(ctx, 7);
                lw(v0, s0, per::kCursor);
                sw(v0, s0, per::kPrevCursor);
                v0 = 0x7E0000;
                lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a0 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x00132478
                    charge(ctx, 3);
                    v0 = a0 & 0x20;
                    if (v0 == 0) {
                        // 0x001324ac
                        charge(ctx, 3);
                        v1 = a0 & 0x4;
                        if (v1 == 0) {
                            // 0x00132534
                            charge(ctx, 3);
                            a1 = a0 & 0x8;
                            if (a1 != 0) {
                                // 0x00132540
                                charge(ctx, 5);
                                lh(a0, s0, per::kCount);
                                lw(v1, s0, per::kCursor);
                                v0 = addiu(a0, -1);
                                if (v1 == v0) {
                                    // 0x00132580
                                    charge(ctx, 2);
                                    if (a1 != 0) {
                                        // 0x00132588
                                        charge(ctx, 3);
                                        v0 = 1;
                                        if (a0 != v0) {
                                            // 0x00132594
                                            charge(ctx, 7);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x1325A4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            sw(zero, s0, per::kCursor);
                                        }
                                    }
                                } else {
                                    // 0x00132554
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x132564u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, per::kCursor);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, per::kCursor);
                                }
                            }
                        } else {
                            // 0x001324b8
                            charge(ctx, 3);
                            lw(v0, s0, per::kCursor);
                            if (v0 == 0) {
                                // 0x001324f0
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    // 0x001324f8
                                    charge(ctx, 4);
                                    lh(v1, s0, per::kCount);
                                    v0 = 1;
                                    if (v1 != v0) {
                                        // 0x00132508
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x132518u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lh(v0, s0, per::kCount);
                                        v0 = addiu(v0, -1);
                                        sw(v0, s0, per::kCursor);
                                    }
                                }
                            } else {
                                // 0x001324c4
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x1324D4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, per::kCursor);
                                v0 = addiu(v0, -1);
                                sw(v0, s0, per::kCursor);
                            }
                        }
                    } else {
                        // 0x00132484
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x132494u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 9;
                        sw(v0, s0, per::kState);
                    }
                } else {
                    // 0x00132450
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x132460u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 14;
                    sw(v0, s0, per::kState);
                }
                // 0x001325b0
                charge(ctx, 4);
                lw(v1, s0, per::kCursor);
                lw(v0, s0, per::kPrevCursor);
                if (v1 != v0) {
                    // 0x001325c0
                    charge(ctx, 34);
                    sw(zero, sp, 0xD8);
                    sw(zero, sp, 0xDC);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    lw(a0, s0, per::kDetailTweens);
                    a1 = 0;
                    a2 = 2;
                    a3 = 1;
                    ld(t0, sp, 0xD8);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x1325FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    lw(v1, s0, per::kDetailTweens);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = addiu(v1, 68);
                    a1 = 0;
                    a2 = 2;
                    a3 = a2;
                    ld(t0, sp, 0xD8);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x13263Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    sw(zero, s0, per::kArrived);
                }
            }
            // 0x00132648
            charge(ctx, 27);
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lhu(a1, v0, 26);
            lw(a0, s0, per::kPicture);
            a2 = si(-1);
            jal(ctx, 0x132660u, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x13266Cu, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132684u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            lh(a3, s0, per::kCursor);
            lh(t0, s0, per::kPrevCursor);
            lw(a0, s0, per::kDetailTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x1326A0u, gen::fn_sub_134900_00134900);
            sw(v0, s0, per::kArrived);
            goto L_00133154;
        case 0x1326B4u:  // table[9]: state 9: wait for flash 4, back to the list
            // 0x001326b4
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 4;
            jal(ctx, 0x1326BCu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x001326cc
                charge(ctx, 20);
                sw(zero, sp, 0xD8);
                sw(zero, sp, 0xDC);
                v0 = 5;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lw(a0, s0, per::kTweens);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132708u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = 0;
                for (;;) {
                    // 0x001327cc
                    charge(ctx, 4);
                    lh(v0, s0, per::kCount);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0013271c
                    charge(ctx, 18);
                    v0 = 0x42EE0000;  // 119.0f
                    mtc1(v0, f2);
                    sw(v0, sp, 0xD8);
                    v0 = sll(s1, 3);
                    v0 = subu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xDC);
                    lw(v0, s0, per::kCursor);
                    if (s1 == v0) {
                        // 0x00132764
                        charge(ctx, 5);
                        v0 = 0x41A80000;  // 21.0f
                        mtc1(v0, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, sp, 0xD8);
                    }
                    // 0x00132778
                    charge(ctx, 21);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v1 = addiu(s1, 1);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a2 = 2;
                    a3 = 1;
                    ld(t0, sp, 0xD8);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x1327C0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    s1 = addiu(s1, 1);
                }
                // 0x001327dc
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00132898
                    charge(ctx, 4);
                    lh(v0, s0, per::kCount);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001327e8
                    charge(ctx, 18);
                    v0 = lui(0xC130);
                    mtc1(v0, f2);
                    sw(v0, sp, 0xD8);
                    v0 = sll(s1, 3);
                    v0 = subu(v0, s1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x427C0000;  // 63.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0xDC);
                    lw(v0, s0, per::kCursor);
                    if (s1 == v0) {
                        // 0x00132830
                        charge(ctx, 5);
                        v0 = 0x41A80000;  // 21.0f
                        mtc1(v0, f0);
                        add_s(f0, f2, f0);
                        swc1(f0, sp, 0xD8);
                    }
                    // 0x00132844
                    charge(ctx, 21);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v1 = addiu(s1, 14);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, per::kTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a2 = 2;
                    a3 = 1;
                    ld(t0, sp, 0xD8);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x13288Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    s1 = addiu(s1, 1);
                }
                // 0x001328a8
                charge(ctx, 153);
                v0 = 497;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xD8);
                v0 = 0x41D00000;  // 26.0f
                sw(v0, sp, 0xDC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 1836);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x1328FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42080000;  // 34.0f
                sw(v0, sp, 0xD8);
                v0 = 415;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xDC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 1904);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132958u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, sp, 0xD8);
                sw(zero, sp, 0xDC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                lw(a0, s0, per::kDetailTweens);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x13299Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42280000;  // 42.0f
                sw(v0, sp, 0xD8);
                v0 = 0x41400000;  // 12.0f
                sw(v0, sp, 0xDC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 136);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x1329ECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 519;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xD8);
                v0 = 0x41400000;  // 12.0f
                sw(v0, sp, 0xDC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 204);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132A48u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x432A0000;  // 170.0f
                sw(v0, sp, 0xD8);
                v0 = 0x41000000;  // 8.0f
                sw(v0, sp, 0xDC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 272);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132A98u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                v0 = 0x42080000;  // 34.0f
                sw(v0, sp, 0xD8);
                v0 = 415;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0xDC);
                v0 = 8;
                sd(v0, sp, 0x0);
                sd(v0, sp, 0x8);
                lw(v1, s0, per::kDetailTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 340);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0xD8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x132AF4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                sw(zero, s0, 8);
                sw(zero, s0, per::kArrived);
                v0 = 10;
                sw(v0, s0, per::kState);
            }
            // 0x00132b0c
            charge(ctx, 21);
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lhu(a1, v0, 26);
            lw(a0, s0, per::kPicture);
            a2 = si(-1);
            jal(ctx, 0x132B24u, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132B30u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lh(t0, s0, per::kPrevCursor);
            lw(a0, s0, per::kDetailTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132B4Cu, gen::fn_sub_134900_00134900);
            sw(zero, s0, per::kArrived);
            goto L_00133154;
        case 0x132B60u:  // table[10]: state 10: the list again
            // 0x00132b60
            charge(ctx, 8);
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132B70u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            if (v0 != 0) {
                // 0x00132b80
                charge(ctx, 2);
                v0 = 4;
                sw(v0, s0, per::kState);
            }
            // 0x00132b88
            charge(ctx, 20);
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lhu(a1, v0, 26);
            lw(a0, s0, per::kPicture);
            a2 = si(-1);
            jal(ctx, 0x132BA0u, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132BACu, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lh(t0, s0, per::kPrevCursor);
            lw(a0, s0, per::kDetailTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132BC8u, gen::fn_sub_134900_00134900);
            goto L_00133154;
        case 0x132BD8u:  // table[14]: state 14: make it the protagonist's persona: message 3
            // 0x00132bd8
            charge(ctx, 31);
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lhu(a1, v0, 26);
            lw(a0, s0, per::kPicture);
            a2 = si(-1);
            jal(ctx, 0x132BF0u, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132BFCu, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lh(t0, s0, per::kPrevCursor);
            lw(a0, s0, per::kDetailTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132C18u, gen::fn_sub_134900_00134900);
            a0 = 3;
            jal(ctx, 0x132C24u, gen::fn_msgWinRequestMessage_003c7430);
            a0 = 0;
            jal(ctx, 0x132C30u, gen::fn_sub_3C74E0_003c74e0);
            a0 = 0;
            jal(ctx, 0x132C3Cu, gen::fn_msgWinSetType_003c7560);
            v0 = 15;
            sw(v0, s0, per::kState);
            goto L_00133154;
        case 0x132C54u:  // table[15]: state 15: the answer (datPersonaSelectSlot)
            // 0x00132c54
            charge(ctx, 22);
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lhu(a1, v0, 26);
            lw(a0, s0, per::kPicture);
            a2 = si(-1);
            jal(ctx, 0x132C6Cu, gen::fn_sub_133B80_00133b80);  // [H_Camp_PersonaDispCtlSetPersona]
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132C78u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lh(t0, s0, per::kPrevCursor);
            lw(a0, s0, per::kDetailTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132C94u, gen::fn_sub_134900_00134900);
            jal(ctx, 0x132C9Cu, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x00132cac
                charge(ctx, 5);
                jal(ctx, 0x132CACu, gen::fn_msgWinLastSelection_003c7610);
                a0 = 1;
                if (v0 != a0) {
                    // 0x00132cc0
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00132cd0
                        charge(ctx, 17);
                        a1 = 0;
                        a2 = 2;
                        a3 = 4;
                        jal(ctx, 0x132CDCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        lw(v0, s0, per::kCursor);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s0);
                        lh(a0, v0, 50);
                        jal(ctx, 0x132CF4u, gen::fn_sub_175200_00175200);  // [datPersonaSelectSlot]
                        a0 = 1;
                        jal(ctx, 0x132D00u, gen::fn_sub_16C860_0016c860);  // [datGetPcPersonaId]
                        a0 = v0;
                        jal(ctx, 0x132D0Cu, gen::fn_sub_11B370_0011b370);  // [H_Camp_PersonaTexSetPersona]
                    } else {
                        // 0x00132cc8
                        charge(ctx, 2);
                    }
                }
                // 0x00132d14
                charge(ctx, 6);
                jal(ctx, 0x132D14u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 8;
                sw(v0, s0, per::kState);
            }
            goto L_00133154;
        case 0x132D2Cu:  // table[11]: state 11: release: the active persona is refused (message 2), else message 1
            // 0x00132d2c
            charge(ctx, 18);
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132D30u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132D48u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            lw(v0, s0, per::kCursor);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lh(s1, v0, 50);
            a0 = 1;
            jal(ctx, 0x132D64u, gen::fn_sub_16C910_0016c910);  // [datGetHeroPersonaIdx]
            if (s1 != v0) {
                // 0x00132d90
                charge(ctx, 13);
                a0 = 1;
                jal(ctx, 0x132D94u, gen::fn_msgWinRequestMessage_003c7430);
                a0 = 0;
                jal(ctx, 0x132DA0u, gen::fn_sub_3C74E0_003c74e0);
                a0 = 0;
                jal(ctx, 0x132DACu, gen::fn_msgWinSetType_003c7560);
                v0 = 12;
                sw(v0, s0, per::kState);
            } else {
                // 0x00132d74
                charge(ctx, 7);
                a0 = 2;
                jal(ctx, 0x132D78u, gen::fn_msgWinRequestMessage_003c7430);
                v0 = 13;
                sw(v0, s0, per::kState);
            }
            goto L_00133154;
        case 0x132DC4u:  // table[12]: state 12: release: the answer (yes -> datPersonaRemoveSlot, rebuild)
            // 0x00132dc4
            charge(ctx, 13);
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x132DC8u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x132DE0u, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            jal(ctx, 0x132DE8u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x00132df8
                charge(ctx, 5);
                jal(ctx, 0x132DF8u, gen::fn_msgWinLastSelection_003c7610);
                v1 = 1;
                if (v0 != v1) {
                    // 0x00132e0c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x00132e1c
                        charge(ctx, 10);
                        lw(v0, s0, per::kCursor);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, s0);
                        lh(a0, v0, 50);
                        jal(ctx, 0x132E2Cu, gen::fn_sub_174C10_00174c10);  // [datPersonaRemoveSlot]
                        s4 = 0;
                        s3 = 0;
                        for (;;) {
                            // 0x00132eb0
                            charge(ctx, 3);
                            v0 = slti(s3, 12);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00132e44
                            charge(ctx, 10);
                            v0 = sll(s4, 1);
                            v0 = addu(s0, v0);
                            s2 = addiu(v0, 26);
                            sh(zero, v0, 26);
                            a0 = dsll32(s3, 16);
                            a0 = dsra32(a0, 16);
                            jal(ctx, 0x132E5Cu, gen::fn_sub_174960_00174960);  // [datPersonaIsSlotUsed]
                            if (v0 != 0) {
                                // 0x00132e6c
                                charge(ctx, 16);
                                a0 = dsll32(s3, 16);
                                a0 = dsra32(a0, 16);
                                jal(ctx, 0x132E74u, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
                                s1 = v0;
                                lhu(a1, v0, 2);
                                a0 = 0x5E0000;
                                a0 = addiu(a0, -20136);  // "stock ID = %d\n"
                                jal(ctx, 0x132E8Cu, gen::fn_printf_005225a8);
                                v0 = sll(s4, 1);
                                v1 = addu(s0, v0);
                                lhu(v0, s1, 2);
                                sh(v0, s2, 0);
                                sh(s3, v1, 50);
                                s4 = addiu(s4, 1);
                            }
                            // 0x00132eac
                            charge(ctx, 1);
                            s3 = addiu(s3, 1);
                        }
                        // 0x00132ebc
                        charge(ctx, 8);
                        sh(s4, s0, per::kCount);
                        v0 = dsll32(s4, 16);
                        v0 = dsra32(v0, 16);
                        v1 = addiu(v0, -1);
                        lw(v0, s0, per::kCursor);
                        at = slt(v1, v0);
                        if (at != 0) {
                            // 0x00132edc
                            charge(ctx, 1);
                            sw(v1, s0, per::kCursor);
                        }
                        // 0x00132ee0
                        charge(ctx, 3);
                        a0 = 0;
                        for (;;) {
                            // 0x00132f14
                            charge(ctx, 3);
                            v0 = slti(a0, 12);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00132eec
                            charge(ctx, 10);
                            v0 = sll(a0, 4);
                            v0 = addu(v0, a0);
                            v1 = sll(v0, 2);
                            lw(v0, s0, per::kTweens);
                            v0 = addu(v0, v1);
                            sw(zero, v0, 72);
                            lw(v0, s0, per::kTweens);
                            v0 = addu(v0, v1);
                            sw(zero, v0, 956);
                            a0 = addiu(a0, 1);
                        }
                        // 0x00132f20
                        charge(ctx, 3);
                        s1 = 0;
                        for (;;) {
                            // 0x00132ffc
                            charge(ctx, 4);
                            lh(v0, s0, per::kCount);
                            v0 = slt(s1, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00132f2c
                            charge(ctx, 18);
                            v0 = 0x42EE0000;  // 119.0f
                            mtc1(v0, f2);
                            sw(v0, sp, 0xD8);
                            v0 = sll(s1, 3);
                            v0 = subu(v0, s1);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, s1);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x42920000;  // 73.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0xDC);
                            lw(v0, s0, per::kCursor);
                            if (s1 == v0) {
                                // 0x00132f74
                                charge(ctx, 5);
                                v0 = 0x41A80000;  // 21.0f
                                mtc1(v0, f0);
                                add_s(f0, f2, f0);
                                swc1(f0, sp, 0xD8);
                            }
                            // 0x00132f88
                            charge(ctx, 29);
                            ld(v0, sp, 0xD8);
                            sd(v0, sp, 0xC0);
                            lwc1(f1, sp, 0xC0);
                            v0 = 0x44160000;  // 600.0f
                            mtc1(v0, f0);
                            sub_s(f0, f1, f0);
                            swc1(f0, sp, 0xC0);
                            sd(zero, sp, 0x0);
                            v0 = 10;
                            sd(v0, sp, 0x8);
                            v1 = addiu(s1, 1);
                            v0 = sll(v1, 4);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            lw(v0, s0, per::kTweens);
                            a0 = addu(v0, v1);
                            v0 = 0x42C80000;  // 100.0f
                            mtc1(v0, f12);
                            a1 = 0;
                            a2 = 2;
                            a3 = 1;
                            ld(t0, sp, 0xC0);
                            ld(t1, sp, 0xD8);
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x132FF0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                            s1 = addiu(s1, 1);
                        }
                        // 0x0013300c
                        charge(ctx, 3);
                        s1 = 0;
                        for (;;) {
                            // 0x001330e8
                            charge(ctx, 4);
                            lh(v0, s0, per::kCount);
                            v0 = slt(s1, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00133018
                            charge(ctx, 18);
                            v0 = lui(0xC130);
                            mtc1(v0, f2);
                            sw(v0, sp, 0xD8);
                            v0 = sll(s1, 3);
                            v0 = subu(v0, s1);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, s1);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x427C0000;  // 63.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0xDC);
                            lw(v0, s0, per::kCursor);
                            if (s1 == v0) {
                                // 0x00133060
                                charge(ctx, 5);
                                v0 = 0x41A80000;  // 21.0f
                                mtc1(v0, f0);
                                add_s(f0, f2, f0);
                                swc1(f0, sp, 0xD8);
                            }
                            // 0x00133074
                            charge(ctx, 29);
                            ld(v0, sp, 0xD8);
                            sd(v0, sp, 0xC8);
                            lwc1(f1, sp, 0xC8);
                            v0 = 0x44160000;  // 600.0f
                            mtc1(v0, f0);
                            sub_s(f0, f1, f0);
                            swc1(f0, sp, 0xC8);
                            sd(zero, sp, 0x0);
                            v0 = 6;
                            sd(v0, sp, 0x8);
                            v1 = addiu(s1, 14);
                            v0 = sll(v1, 4);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            lw(v0, s0, per::kTweens);
                            a0 = addu(v0, v1);
                            v0 = 0x42C80000;  // 100.0f
                            mtc1(v0, f12);
                            a1 = 0;
                            a2 = 2;
                            a3 = 1;
                            ld(t0, sp, 0xC8);
                            ld(t1, sp, 0xD8);
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x1330DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                            s1 = addiu(s1, 1);
                        }
                    } else {
                        // 0x00132e14
                        charge(ctx, 2);
                    }
                }
                // 0x001330f8
                charge(ctx, 6);
                jal(ctx, 0x1330F8u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 4;
                sw(v0, s0, per::kState);
            }
            goto L_00133154;
        case 0x133110u:  // table[13]: state 13: wait for the message
            // 0x00133110
            charge(ctx, 13);
            lw(a0, s0, per::kPicture);
            jal(ctx, 0x133114u, gen::fn_sub_133A80_00133a80);  // draw the persona picture
            lh(a3, s0, per::kCursor);
            lw(a0, s0, per::kTweens);
            a1 = addiu(s0, per::kFiles);
            a2 = addiu(s0, per::kSlots);
            jal(ctx, 0x13312Cu, gen::fn_sub_1344B0_001344b0);  // the persona list's tweens (sub_133E10)
            jal(ctx, 0x133134u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x00133144
                charge(ctx, 4);
                jal(ctx, 0x133144u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 4;
                sw(v0, s0, per::kState);
            }
            goto L_00133154;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00133158 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(ra, sp, 0x60);
        lq(s4, sp, 0x50);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        sp = addiu(sp, 0xF0);
        return;
    }
    goto L_00133154;
}

// 0x00133E10 sub_133E10 -- 1688 bytes; frame 0x170: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_PersonaDrawRow] (tween, files, element, ids, cursor): one element of the persona list: 28 the header, 27 the
// frame, 1..13 a row (the persona name from datGetPersonaName, highlighted on the cursor), 14..26 its level digits
// (font 1 / font 2) and the "active" marks when it is the protagonist's persona; then the scrolling backdrop pair (+48
// moving by -1, wrapping at 750).
void sub_133E10(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00133e10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = t0;
    v1 = 29;
    if (a2 != v1) {
        // 0x00133e48
        charge(ctx, 3);
        v0 = 28;
        if (a2 == v0) {
            // 0x00133fcc
            charge(ctx, 72);
            lbu(a3, s2, tw::kAlpha);
            a0 = s5;
            lw(a1, s1, 8);
            a2 = 0;
            lwc1(f12, s2, tw::kX);
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x133FE8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s2, tw::kX);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lbu(a3, s2, tw::kAlpha);
            a0 = s5;
            lw(a1, s1, 8);
            a2 = 1;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x13402Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 431;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s2, tw::kX);
            add_s(f12, f1, f0);
            lbu(a3, s2, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 1;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x134068u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 527;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s2, tw::kX);
            add_s(f12, f1, f0);
            lbu(a3, s2, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 3;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x1340A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s2, tw::kX);
            v0 = 0x43A80000;  // 336.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s2, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
            a2 = 4;
            lwc1(f13, s2, tw::kY);
            lwc1(f14, s2, tw::kZ);
            jal(ctx, 0x1340DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x00133e54
            charge(ctx, 3);
            v0 = 27;
            if (a2 == v0) {
                // 0x00133fa0
                charge(ctx, 11);
                lbu(a3, s2, tw::kAlpha);
                a0 = s5;
                lw(a1, s1, 0);
                a2 = 4;
                lwc1(f12, s2, tw::kX);
                lwc1(f13, s2, tw::kY);
                lwc1(f14, s2, tw::kZ);
                jal(ctx, 0x133FBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x00133e60
                charge(ctx, 2);
                if (a2 == 0) {
                    // 0x00133e70
                    charge(ctx, 68);
                    a0 = 0;
                    lw(a1, s1, 0);
                    a2 = 0;
                    jal(ctx, 0x133E7Cu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                    s0 = v0;
                    lwc1(f0, s2, tw::kZ);
                    swc1(f0, v0, 44);
                    lwc1(f1, s2, tw::kX);
                    v1 = 0x437A0000;  // 250.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, v0, 16);
                    lwc1(f0, s2, tw::kY);
                    swc1(f0, v0, 20);
                    lw(v1, s2, tw::kAlpha);
                    sb(v1, v0, 24);
                    a0 = s0;
                    a1 = 1;
                    jal(ctx, 0x133EC0u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                    a0 = s0;
                    jal(ctx, 0x133ECCu, gen::fn_sub_115980_00115980);  // draw and release the handle
                    a0 = 0;
                    lw(a1, s1, 0);
                    a2 = 0;
                    jal(ctx, 0x133EE0u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                    s0 = v0;
                    lwc1(f0, s2, tw::kZ);
                    swc1(f0, v0, 44);
                    v1 = 750;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s2, tw::kX);
                    add_s(f1, f1, f0);
                    v1 = 0x437A0000;  // 250.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, v0, 16);
                    lwc1(f0, s2, tw::kY);
                    swc1(f0, v0, 20);
                    lw(v1, s2, tw::kAlpha);
                    sb(v1, v0, 24);
                    a0 = s0;
                    a1 = 1;
                    jal(ctx, 0x133F38u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                    a0 = s0;
                    jal(ctx, 0x133F44u, gen::fn_sub_115980_00115980);  // draw and release the handle
                    lwc1(f1, s2, 48);
                    v1 = 0x3F800000;  // 1.0f
                    mtc1(v1, f0);
                    sub_s(f1, f1, f0);
                    swc1(f1, s2, 48);
                    v1 = si(-750);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    c_lt_s(f1, f0);
                    if (cond(ctx)) {
                        // 0x00133f80
                        charge(ctx, 8);
                        v1 = 750;
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f1, f0);
                        swc1(f0, s2, 48);
                    }
                } else {
                    // 0x00133e68
                    charge(ctx, 2);
                    // 0x001340ec
                    charge(ctx, 3);
                    at = slti(a2, 14);
                    if (at == 0) {
                        // 0x00134188
                        charge(ctx, 11);
                        s4 = addiu(a2, -14);
                        v0 = sll(s4, 1);
                        v0 = addu(a3, v0);
                        lh(a0, v0, 0);
                        jal(ctx, 0x134198u, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
                        s3 = v0;
                        v0 = dsll32(s0, 16);
                        v0 = dsra32(v0, 16);
                        if (s4 != v0) {
                            // 0x001342ec
                            charge(ctx, 6);
                            lhu(s0, s3, 2);
                            a0 = 1;
                            jal(ctx, 0x1342F4u, gen::fn_sub_16C860_0016c860);  // [datGetPcPersonaId]
                            if (s0 != v0) {
                                // 0x00134350
                                charge(ctx, 17);
                                lwc1(f1, s2, tw::kX);
                                v0 = 0x42700000;  // 60.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s2, tw::kY);
                                v0 = 0x40400000;  // 3.0f
                                mtc1(v0, f0);
                                add_s(f13, f0, f1);
                                lbu(a3, s2, tw::kAlpha);
                                a0 = s5;
                                lw(a1, s1, 4);
                                a2 = 7;
                                lwc1(f14, s2, tw::kZ);
                                jal(ctx, 0x13438Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x00134304
                                charge(ctx, 19);
                                lwc1(f1, s2, tw::kX);
                                v0 = 0x42700000;  // 60.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s2, tw::kY);
                                v0 = 0x40400000;  // 3.0f
                                mtc1(v0, f0);
                                add_s(f13, f0, f1);
                                lbu(a3, s2, tw::kAlpha);
                                a0 = s5;
                                lw(a1, s1, 0);
                                a2 = 5;
                                lwc1(f14, s2, tw::kZ);
                                jal(ctx, 0x134340u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                            // 0x00134394
                            charge(ctx, 4);
                            lbu(s0, s3, 4);
                            v0 = slti(s0, 10);
                            if (v0 == 0) {
                                // 0x001343a4
                                charge(ctx, 27);
                                a0 = 2;
                                jal(ctx, 0x1343A8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                v1 = 10;
                                div(s0, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s2, tw::kX);
                                v1 = 0x42B00000;  // 88.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s2, tw::kY);
                                v1 = 0x41300000;  // 11.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                add_s(f13, f0, f1);
                                lbu(a3, s2, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s2, tw::kZ);
                                jal(ctx, 0x134408u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                            // 0x00134410
                            charge(ctx, 28);
                            a0 = 2;
                            jal(ctx, 0x134414u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            lbu(a0, s3, 4);
                            v1 = 10;
                            div(a0, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            lwc1(f1, s2, tw::kX);
                            v1 = 0x42D00000;  // 104.0f
                            mtc1(v1, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s2, tw::kY);
                            v1 = 0x41300000;  // 11.0f
                            mtc1(v1, f0);
                            add_s(f1, f0, f1);
                            v1 = 0x3F800000;  // 1.0f
                            mtc1(v1, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s2, tw::kAlpha);
                            a0 = s5;
                            a1 = v0;
                            lwc1(f14, s2, tw::kZ);
                            jal(ctx, 0x134478u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x001341b4
                            charge(ctx, 21);
                            lwc1(f1, s2, tw::kX);
                            v0 = 0x42700000;  // 60.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s2, tw::kY);
                            v0 = 0x40400000;  // 3.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s2, tw::kAlpha);
                            a0 = s5;
                            lw(a1, s1, 4);
                            a2 = 8;
                            lwc1(f14, s2, tw::kZ);
                            jal(ctx, 0x1341F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lbu(s0, s3, 4);
                            v0 = slti(s0, 10);
                            if (v0 == 0) {
                                // 0x00134208
                                charge(ctx, 27);
                                a0 = 1;
                                jal(ctx, 0x13420Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                v1 = 10;
                                div(s0, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s2, tw::kX);
                                v1 = 0x42B00000;  // 88.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s2, tw::kY);
                                v1 = 0x41300000;  // 11.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                add_s(f13, f0, f1);
                                lbu(a3, s2, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s2, tw::kZ);
                                jal(ctx, 0x13426Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                            // 0x00134274
                            charge(ctx, 30);
                            a0 = 1;
                            jal(ctx, 0x134278u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            lbu(a0, s3, 4);
                            v1 = 10;
                            div(a0, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            lwc1(f1, s2, tw::kX);
                            v1 = 0x42D00000;  // 104.0f
                            mtc1(v1, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s2, tw::kY);
                            v1 = 0x41300000;  // 11.0f
                            mtc1(v1, f0);
                            add_s(f1, f0, f1);
                            v1 = 0x3F800000;  // 1.0f
                            mtc1(v1, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s2, tw::kAlpha);
                            a0 = s5;
                            a1 = v0;
                            lwc1(f14, s2, tw::kZ);
                            jal(ctx, 0x1342DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x001340f8
                        charge(ctx, 36);
                        v0 = addiu(a2, -1);
                        v0 = sll(v0, 1);
                        v0 = addu(a3, v0);
                        lh(a0, v0, 0);
                        jal(ctx, 0x134108u, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
                        lhu(a0, v0, 2);
                        jal(ctx, 0x134114u, gen::fn_sub_173220_00173220);  // [datGetPersonaName]
                        a0 = addiu(sp, 0x70);
                        a1 = addiu(gp, -30340);  // "%s"
                        a2 = v0;
                        jal(ctx, 0x134128u, gen::fn_sprintf_00523ac8);
                        lw(v1, s2, tw::kAlpha);
                        v0 = 255;
                        v1 = subu(v0, v1);
                        lwc1(f0, s2, tw::kX);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        lwc1(f0, s2, tw::kY);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = 0x42C80000;  // 100.0f
                        mtc1(v0, f12);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a3 = 10;
                        t0 = 1;
                        t1 = addiu(sp, 0x70);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x134178u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    }
                }
            }
        }
    }
    // 0x00134480 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x001344B0 sub_1344B0 -- 244 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_PersonaRunListTweens] (tweens, files, ids, cursor): steps the 100 list tweens, draws each active one
// (sub_133E10), returns 1 when all finished.
void sub_1344B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001344b0
    enter(ctx, 17);  // entry check point + this block's cycles
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
    s6 = a3;
    s1 = 1;
    s2 = 0;
    for (;;) {
        // 0x00134568
        charge(ctx, 3);
        v0 = slti(s2, 100);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001344f4
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x00134510
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x134514u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x00134524
                charge(ctx, 7);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                jal(ctx, 0x134538u, gen::fn_sub_133E10_00133e10);
            }
            // 0x00134540
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x00134560
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x00134564
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00134574
    charge(ctx, 12);
    v0 = s1;
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

}  // namespace p3fes::game
