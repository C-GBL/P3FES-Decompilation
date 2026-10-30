// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the party-status screens ("H_CampPartyStatusDraw" and its root, the equipment list) and the equipment trade / drop
// screens ("H_CampTradeDraw" and its sub-task, the COMM that opens it).
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
void fn_brItem_CreateStockOverBgTask_0025f370(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_115DE0_00115de0(p3fes::EEContext&);
void fn_sub_119F10_00119f10(p3fes::EEContext&);
void fn_sub_121DE0_00121de0(p3fes::EEContext&);
void fn_sub_122710_00122710(p3fes::EEContext&);
void fn_sub_12DF50_0012df50(p3fes::EEContext&);
void fn_sub_12E170_0012e170(p3fes::EEContext&);
void fn_sub_13C240_0013c240(p3fes::EEContext&);
void fn_sub_13C780_0013c780(p3fes::EEContext&);
void fn_sub_13CF80_0013cf80(p3fes::EEContext&);
void fn_sub_13D1A0_0013d1a0(p3fes::EEContext&);
void fn_sub_13FCA0_0013fca0(p3fes::EEContext&);
void fn_sub_161D90_00161d90(p3fes::EEContext&);
void fn_sub_163330_00163330(p3fes::EEContext&);
void fn_sub_164920_00164920(p3fes::EEContext&);
void fn_sub_166A50_00166a50(p3fes::EEContext&);
void fn_sub_166C70_00166c70(p3fes::EEContext&);
void fn_sub_167EF0_00167ef0(p3fes::EEContext&);
void fn_sub_167F10_00167f10(p3fes::EEContext&);
void fn_sub_167F30_00167f30(p3fes::EEContext&);
void fn_sub_167F40_00167f40(p3fes::EEContext&);
void fn_sub_1685D0_001685d0(p3fes::EEContext&);
void fn_sub_1685E0_001685e0(p3fes::EEContext&);
void fn_sub_168810_00168810(p3fes::EEContext&);
void fn_sub_169110_00169110(p3fes::EEContext&);
void fn_sub_1691F0_001691f0(p3fes::EEContext&);
void fn_sub_169470_00169470(p3fes::EEContext&);
void fn_sub_169B90_00169b90(p3fes::EEContext&);
void fn_sub_16A030_0016a030(p3fes::EEContext&);
void fn_sub_16A700_0016a700(p3fes::EEContext&);
void fn_sub_16AF90_0016af90(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_16F810_0016f810(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_16FF90_0016ff90(p3fes::EEContext&);
void fn_sub_170080_00170080(p3fes::EEContext&);
void fn_sub_170170_00170170(p3fes::EEContext&);
void fn_sub_170260_00170260(p3fes::EEContext&);
void fn_sub_170350_00170350(p3fes::EEContext&);
void fn_sub_170440_00170440(p3fes::EEContext&);
void fn_sub_170530_00170530(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170A40_00170a40(p3fes::EEContext&);
void fn_sub_170AB0_00170ab0(p3fes::EEContext&);
void fn_sub_170B20_00170b20(p3fes::EEContext&);
void fn_sub_170B90_00170b90(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_177C10_00177c10(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_1830C0_001830c0(p3fes::EEContext&);
void fn_sub_18B6D0_0018b6d0(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_25F570_0025f570(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_3C7700_003c7700(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui6;  // the record offsets, $gp words, pad words and sprite tables of ui6.h

// 0x00161D90 sub_161D90 -- 5532 bytes; frame 0x1A0: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_PartyDrawElement] (tween, element, party work): one tween element of "H_CampPartyStatusDraw" (jump table
// 0x7B6210): 0 the character picture strips (sub_1140D0 of the texture +28, +52 scrolling to -1064), the frames, the
// four equipment slots (icon from the mask, name, the slot's stats through sub_12E170), the member's HP / SP and level.
void sub_161D90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00161d90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1A0);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s1 = a0;
    s0 = a2;
    at = sltiu(a1, 9);
    if (at != 0) {
        // 0x00161dc8
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 25104);  // &0x7B6210
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x161DE4u:  // table[2]
            // 0x00161de4
            charge(ctx, 41);
            lh(a0, s0, pty::kPc);
            a1 = 0;
            jal(ctx, 0x161DECu, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s0, pty::kPc);
            jal(ctx, 0x161E00u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
            s3 = v0 & 0xFFFF;
            lh(a0, s0, pty::kPc);
            a1 = 0;
            jal(ctx, 0x161E14u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s0, pty::kPc);
            jal(ctx, 0x161E28u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
            s2 = v0 & 0xFFFF;
            lwc1(f1, s1, tw::kX);
            v0 = 0x41700000;  // 15.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 36;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x161E74u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v0, s0, pty::kSlot);
            if (v0 == 0) {
                // 0x00161e88
                charge(ctx, 3);
                lw(v0, s0, 20);
                if (v0 != 0) {
                    goto L_00162190;
                }
                // 0x00161e94
                charge(ctx, 191);
                lwc1(f1, s1, tw::kX);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                sub_s(f13, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 42;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x161ED4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lh(a0, s0, pty::kPc);
                a1 = 0;
                jal(ctx, 0x161EE4u, gen::fn_datGetEquipmentIdx_0016cb80);
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                lh(a0, s0, pty::kPc);
                a1 = s4;
                jal(ctx, 0x161EFCu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                a0 = v0;
                jal(ctx, 0x161F08u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                a2 = sll(v0, 1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x161F3Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lh(a0, s0, pty::kPc);
                a1 = s4;
                jal(ctx, 0x161F4Cu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                s6 = dsll32(v0, 16);
                s6 = dsra32(s6, 16);
                lh(a0, s0, pty::kPc);
                a1 = s4;
                jal(ctx, 0x161F64u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                v0 = v0 & 0xFF;
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = s6;
                jal(ctx, 0x161F7Cu, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                a0 = addiu(sp, 0x90);
                a1 = addiu(gp, -30340);  // "%s"
                a2 = v0;
                jal(ctx, 0x161F90u, gen::fn_sprintf_00523ac8);
                lw(v1, s1, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s1, tw::kX);
                v0 = 0x42200000;  // 40.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41300000;  // 11.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s1, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x90);
                t2 = 16;
                t3 = 118;
                jal(ctx, 0x161FFCu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s1, tw::kX);
                v0 = 0x43770000;  // 247.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40E00000;  // 7.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 38;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162044u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x438E0000;  // 284.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x198);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x19C);
                a0 = 2;
                jal(ctx, 0x162080u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s1, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s3, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x198);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s1, tw::kAlpha);
                jal(ctx, 0x1620BCu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                lwc1(f1, s1, tw::kX);
                v0 = 0x43AE0000;  // 348.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40E00000;  // 7.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 39;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162104u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 385;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s1, tw::kX);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x198);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x19C);
                a0 = 2;
                jal(ctx, 0x162144u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s1, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s2, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x198);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s1, tw::kAlpha);
                jal(ctx, 0x162180u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                break;
            }
        L_00162190:
            charge(ctx, 171);
            lh(a0, s0, pty::kPc);
            a1 = 0;
            jal(ctx, 0x162198u, gen::fn_datGetEquipmentIdx_0016cb80);
            s4 = dsll32(v0, 16);
            s4 = dsra32(s4, 16);
            lh(a0, s0, pty::kPc);
            a1 = s4;
            jal(ctx, 0x1621B0u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
            a0 = v0;
            jal(ctx, 0x1621BCu, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
            v0 = sll(v0, 1);
            a2 = addiu(v0, 1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x1621E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lh(a0, s0, pty::kPc);
            a1 = s4;
            jal(ctx, 0x1621F8u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s6 = dsll32(v0, 16);
            s6 = dsra32(s6, 16);
            lh(a0, s0, pty::kPc);
            a1 = s4;
            jal(ctx, 0x162210u, gen::fn_sub_16F810_0016f810);  // (owner, index)
            v0 = v0 & 0xFF;
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s6;
            jal(ctx, 0x162228u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
            a0 = addiu(sp, 0x90);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x16223Cu, gen::fn_sprintf_00523ac8);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            v1 = subu(v0, v1);
            lwc1(f1, s1, tw::kX);
            v0 = 0x42200000;  // 40.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41300000;  // 11.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            v0 = si(-256);
            a2 = v1 | v0;
            lwc1(f12, s1, tw::kZ);
            a3 = 6;
            t0 = 1;
            t1 = addiu(sp, 0x90);
            t2 = 16;
            t3 = 118;
            jal(ctx, 0x1622A8u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            lwc1(f1, s1, tw::kX);
            v0 = 0x43770000;  // 247.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40E00000;  // 7.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 32;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x1622F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x438E0000;  // 284.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x198);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x19C);
            a0 = 1;
            jal(ctx, 0x16232Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            lwc1(f0, s1, tw::kZ);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            sd(s3, sp, 0x0);
            v1 = 3;
            sd(v1, sp, 0x8);
            a0 = v0;
            a1 = 11;
            ld(a2, sp, 0x198);
            t0 = 255;
            t1 = t0;
            t2 = t0;
            lw(t3, s1, tw::kAlpha);
            jal(ctx, 0x162368u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            lwc1(f1, s1, tw::kX);
            v0 = 0x43AE0000;  // 348.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40E00000;  // 7.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 33;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x1623B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, tw::kX);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x198);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x19C);
            a0 = 1;
            jal(ctx, 0x1623F0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            lwc1(f0, s1, tw::kZ);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            sd(s2, sp, 0x0);
            v1 = 3;
            sd(v1, sp, 0x8);
            a0 = v0;
            a1 = 11;
            ld(a2, sp, 0x198);
            t0 = 255;
            t1 = t0;
            t2 = t0;
            lw(t3, s1, tw::kAlpha);
            jal(ctx, 0x16242Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            break;
        case 0x16243Cu:  // table[3]
            // 0x0016243c
            charge(ctx, 32);
            lh(a0, s0, pty::kPc);
            a1 = 1;
            jal(ctx, 0x162444u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s0, pty::kPc);
            jal(ctx, 0x162458u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
            s2 = v0 & 0xFFFF;
            lwc1(f1, s1, tw::kX);
            v0 = 0x41700000;  // 15.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 36;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x1624A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v1, s0, pty::kSlot);
            v0 = 1;
            if (v1 == v0) {
                // 0x001624bc
                charge(ctx, 3);
                lw(v0, s0, 20);
                if (v0 != 0) {
                    goto L_00162700;
                }
                // 0x001624c8
                charge(ctx, 142);
                lwc1(f1, s1, tw::kX);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                sub_s(f13, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 42;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162508u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lh(a0, s0, pty::kPc);
                a1 = 1;
                jal(ctx, 0x162518u, gen::fn_datGetEquipmentIdx_0016cb80);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lh(a0, s0, pty::kPc);
                a1 = s3;
                jal(ctx, 0x162530u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                a0 = v0;
                jal(ctx, 0x16253Cu, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                a2 = sll(v0, 1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162570u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lh(a0, s0, pty::kPc);
                a1 = s3;
                jal(ctx, 0x162580u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                lh(a0, s0, pty::kPc);
                a1 = s3;
                jal(ctx, 0x162598u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                v0 = v0 & 0xFF;
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = s4;
                jal(ctx, 0x1625B0u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                a0 = addiu(sp, 0x90);
                a1 = addiu(gp, -30340);  // "%s"
                a2 = v0;
                jal(ctx, 0x1625C4u, gen::fn_sprintf_00523ac8);
                lw(v1, s1, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s1, tw::kX);
                v0 = 0x42200000;  // 40.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41300000;  // 11.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s1, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x90);
                t2 = 16;
                t3 = 118;
                jal(ctx, 0x162630u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s1, tw::kX);
                v0 = 0x43770000;  // 247.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40E00000;  // 7.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 40;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162678u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x438E0000;  // 284.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x198);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x19C);
                a0 = 2;
                jal(ctx, 0x1626B4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s1, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s2, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x198);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s1, tw::kAlpha);
                jal(ctx, 0x1626F0u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                break;
            }
        L_00162700:
            charge(ctx, 122);
            lh(a0, s0, pty::kPc);
            a1 = 1;
            jal(ctx, 0x162708u, gen::fn_datGetEquipmentIdx_0016cb80);
            s3 = dsll32(v0, 16);
            s3 = dsra32(s3, 16);
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x162720u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
            a0 = v0;
            jal(ctx, 0x16272Cu, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
            v0 = sll(v0, 1);
            a2 = addiu(v0, 1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162758u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x162768u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s4 = dsll32(v0, 16);
            s4 = dsra32(s4, 16);
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x162780u, gen::fn_sub_16F810_0016f810);  // (owner, index)
            v0 = v0 & 0xFF;
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s4;
            jal(ctx, 0x162798u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
            a0 = addiu(sp, 0x90);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x1627ACu, gen::fn_sprintf_00523ac8);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            v1 = subu(v0, v1);
            lwc1(f1, s1, tw::kX);
            v0 = 0x42200000;  // 40.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41300000;  // 11.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            v0 = si(-256);
            a2 = v1 | v0;
            lwc1(f12, s1, tw::kZ);
            a3 = 6;
            t0 = 1;
            t1 = addiu(sp, 0x90);
            t2 = 16;
            t3 = 118;
            jal(ctx, 0x162818u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            lwc1(f1, s1, tw::kX);
            v0 = 0x43770000;  // 247.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40E00000;  // 7.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 34;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162860u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x438E0000;  // 284.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x198);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x19C);
            a0 = 1;
            jal(ctx, 0x16289Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            lwc1(f0, s1, tw::kZ);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            sd(s2, sp, 0x0);
            v1 = 3;
            sd(v1, sp, 0x8);
            a0 = v0;
            a1 = 11;
            ld(a2, sp, 0x198);
            t0 = 255;
            t1 = t0;
            t2 = t0;
            lw(t3, s1, tw::kAlpha);
            jal(ctx, 0x1628D8u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            break;
        case 0x1628E8u:  // table[4]
            // 0x001628e8
            charge(ctx, 32);
            lh(a0, s0, pty::kPc);
            a1 = 2;
            jal(ctx, 0x1628F0u, gen::fn_datGetEquipmentIdx_0016cb80);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            lh(a0, s0, pty::kPc);
            jal(ctx, 0x162904u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
            s2 = v0 & 0xFFFF;
            lwc1(f1, s1, tw::kX);
            v0 = 0x41700000;  // 15.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 36;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162950u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v1, s0, pty::kSlot);
            v0 = 2;
            if (v1 == v0) {
                // 0x00162968
                charge(ctx, 3);
                lw(v0, s0, 20);
                if (v0 != 0) {
                    goto L_00162bac;
                }
                // 0x00162974
                charge(ctx, 142);
                lwc1(f1, s1, tw::kX);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                sub_s(f13, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 42;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1629B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lh(a0, s0, pty::kPc);
                a1 = 2;
                jal(ctx, 0x1629C4u, gen::fn_datGetEquipmentIdx_0016cb80);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lh(a0, s0, pty::kPc);
                a1 = s3;
                jal(ctx, 0x1629DCu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                a0 = v0;
                jal(ctx, 0x1629E8u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                a2 = sll(v0, 1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162A1Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lh(a0, s0, pty::kPc);
                a1 = s3;
                jal(ctx, 0x162A2Cu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                s4 = dsll32(v0, 16);
                s4 = dsra32(s4, 16);
                lh(a0, s0, pty::kPc);
                a1 = s3;
                jal(ctx, 0x162A44u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                v0 = v0 & 0xFF;
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = s4;
                jal(ctx, 0x162A5Cu, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                a0 = addiu(sp, 0x90);
                a1 = addiu(gp, -30340);  // "%s"
                a2 = v0;
                jal(ctx, 0x162A70u, gen::fn_sprintf_00523ac8);
                lw(v1, s1, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s1, tw::kX);
                v0 = 0x42200000;  // 40.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41300000;  // 11.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s1, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x90);
                t2 = 16;
                t3 = 118;
                jal(ctx, 0x162ADCu, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                lwc1(f1, s1, tw::kX);
                v0 = 0x43770000;  // 247.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40E00000;  // 7.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 41;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162B24u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x438E0000;  // 284.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x198);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x19C);
                a0 = 2;
                jal(ctx, 0x162B60u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                lwc1(f0, s1, tw::kZ);
                cvt_w_s(f0, f0);
                mfc1(a3, f0);
                sd(s2, sp, 0x0);
                v1 = 3;
                sd(v1, sp, 0x8);
                a0 = v0;
                a1 = 11;
                ld(a2, sp, 0x198);
                t0 = 255;
                t1 = t0;
                t2 = t0;
                lw(t3, s1, tw::kAlpha);
                jal(ctx, 0x162B9Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                break;
            }
        L_00162bac:
            charge(ctx, 122);
            lh(a0, s0, pty::kPc);
            a1 = 2;
            jal(ctx, 0x162BB4u, gen::fn_datGetEquipmentIdx_0016cb80);
            s3 = dsll32(v0, 16);
            s3 = dsra32(s3, 16);
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x162BCCu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
            a0 = v0;
            jal(ctx, 0x162BD8u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
            v0 = sll(v0, 1);
            a2 = addiu(v0, 1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162C04u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x162C14u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s4 = dsll32(v0, 16);
            s4 = dsra32(s4, 16);
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x162C2Cu, gen::fn_sub_16F810_0016f810);  // (owner, index)
            v0 = v0 & 0xFF;
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s4;
            jal(ctx, 0x162C44u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
            a0 = addiu(sp, 0x90);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x162C58u, gen::fn_sprintf_00523ac8);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            v1 = subu(v0, v1);
            lwc1(f1, s1, tw::kX);
            v0 = 0x42200000;  // 40.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41300000;  // 11.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            v0 = si(-256);
            a2 = v1 | v0;
            lwc1(f12, s1, tw::kZ);
            a3 = 6;
            t0 = 1;
            t1 = addiu(sp, 0x90);
            t2 = 16;
            t3 = 118;
            jal(ctx, 0x162CC4u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            lwc1(f1, s1, tw::kX);
            v0 = 0x43770000;  // 247.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40E00000;  // 7.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 35;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162D0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x438E0000;  // 284.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x198);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x19C);
            a0 = 1;
            jal(ctx, 0x162D48u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            lwc1(f0, s1, tw::kZ);
            cvt_w_s(f0, f0);
            mfc1(a3, f0);
            sd(s2, sp, 0x0);
            v1 = 3;
            sd(v1, sp, 0x8);
            a0 = v0;
            a1 = 11;
            ld(a2, sp, 0x198);
            t0 = 255;
            t1 = t0;
            t2 = t0;
            lw(t3, s1, tw::kAlpha);
            jal(ctx, 0x162D84u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
            break;
        case 0x162D94u:  // table[5]
            // 0x00162d94
            charge(ctx, 22);
            lwc1(f1, s1, tw::kX);
            v0 = 0x41700000;  // 15.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
            a2 = 36;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162DD4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v1, s0, pty::kSlot);
            v0 = 3;
            if (v1 == v0) {
                // 0x00162dec
                charge(ctx, 3);
                lw(v0, s0, 20);
                if (v0 != 0) {
                    goto L_00162f70;
                }
                // 0x00162df8
                charge(ctx, 94);
                lwc1(f1, s1, tw::kX);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40400000;  // 3.0f
                mtc1(v0, f0);
                sub_s(f13, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(9));  // 0x833B94: camp sprite file 9
                a2 = 42;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162E38u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lh(a0, s0, pty::kPc);
                a1 = 3;
                jal(ctx, 0x162E48u, gen::fn_datGetEquipmentIdx_0016cb80);
                s2 = dsll32(v0, 16);
                s2 = dsra32(s2, 16);
                lh(a0, s0, pty::kPc);
                a1 = s2;
                jal(ctx, 0x162E60u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                a0 = v0;
                jal(ctx, 0x162E6Cu, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                a2 = sll(v0, 1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                t0 = 32;
                t1 = 67;
                t2 = 120;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x162EA0u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                lh(a0, s0, pty::kPc);
                a1 = s2;
                jal(ctx, 0x162EB0u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lh(a0, s0, pty::kPc);
                a1 = s2;
                jal(ctx, 0x162EC8u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                v0 = v0 & 0xFF;
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = s3;
                jal(ctx, 0x162EE0u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                a0 = addiu(sp, 0x90);
                a1 = addiu(gp, -30340);  // "%s"
                a2 = v0;
                jal(ctx, 0x162EF4u, gen::fn_sprintf_00523ac8);
                lw(v1, s1, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s1, tw::kX);
                v0 = 0x42200000;  // 40.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41300000;  // 11.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s1, tw::kZ);
                a3 = 10;
                t0 = 1;
                t1 = addiu(sp, 0x90);
                t2 = 16;
                t3 = 118;
                jal(ctx, 0x162F60u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                break;
            }
        L_00162f70:
            charge(ctx, 74);
            lh(a0, s0, pty::kPc);
            a1 = 3;
            jal(ctx, 0x162F78u, gen::fn_datGetEquipmentIdx_0016cb80);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
            lh(a0, s0, pty::kPc);
            a1 = s2;
            jal(ctx, 0x162F90u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
            a0 = v0;
            jal(ctx, 0x162F9Cu, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
            v0 = sll(v0, 1);
            a2 = addiu(v0, 1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x162FC8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lh(a0, s0, pty::kPc);
            a1 = s2;
            jal(ctx, 0x162FD8u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s3 = dsll32(v0, 16);
            s3 = dsra32(s3, 16);
            lh(a0, s0, pty::kPc);
            a1 = s2;
            jal(ctx, 0x162FF0u, gen::fn_sub_16F810_0016f810);  // (owner, index)
            v0 = v0 & 0xFF;
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s3;
            jal(ctx, 0x163008u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
            a0 = addiu(sp, 0x90);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x16301Cu, gen::fn_sprintf_00523ac8);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            v1 = subu(v0, v1);
            lwc1(f1, s1, tw::kX);
            v0 = 0x42200000;  // 40.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x41300000;  // 11.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            v0 = si(-256);
            a2 = v1 | v0;
            lwc1(f12, s1, tw::kZ);
            a3 = 6;
            t0 = 1;
            t1 = addiu(sp, 0x90);
            t2 = 16;
            t3 = 118;
            jal(ctx, 0x163088u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
            break;
        case 0x163098u:  // table[0]: element 0: the character picture strips
            // 0x00163098
            charge(ctx, 20);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            s2 = subu(v0, v1);
            v0 = si(-256);
            a0 = s2 | v0;
            lwc1(f12, s1, tw::kZ);
            lwc1(f13, s1, tw::kX);
            lwc1(f14, s1, tw::kY);
            a1 = 512;
            a2 = 1024;
            lw(a3, s0, pty::kTexture);
            jal(ctx, 0x1630C4u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
            lwc1(f2, s1, tw::kY);
            v1 = lui(0xC41A);
            mtc1(v1, f0);
            c_lt_s(f2, f0);
            if (cond(ctx)) {
                // 0x001630e8
                charge(ctx, 16);
                v0 = si(-256);
                a0 = s2 | v0;
                v0 = 0x42200000;  // 40.0f
                mtc1(v0, f1);
                v0 = 0x44800000;  // 1024.0f
                mtc1(v0, f0);
                add_s(f0, f0, f2);
                add_s(f14, f1, f0);
                lwc1(f12, s1, tw::kZ);
                lwc1(f13, s1, tw::kX);
                a1 = 512;
                a2 = 1024;
                lw(a3, s0, pty::kTexture);
                jal(ctx, 0x163120u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
            }
            // 0x00163128
            charge(ctx, 12);
            lwc1(f1, s1, 52);
            v1 = 0x3F800000;  // 1.0f
            mtc1(v1, f0);
            sub_s(f1, f1, f0);
            swc1(f1, s1, 52);
            v1 = lui(0xC485);
            mtc1(v1, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x00163158
                charge(ctx, 3);
                sw(zero, s1, 52);
            }
            break;
        case 0x163164u:  // table[7]
            // 0x00163164
            charge(ctx, 11);
            lbu(a3, s1, tw::kAlpha);
            a0 = s5;
            lw(a1, s0, pty::kFile0);
            a2 = 1;
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x163180u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x163190u:  // table[8]
            // 0x00163190
            charge(ctx, 3);
            lw(v0, s0, 20);
            if (v0 == 0) {
                // 0x00163250
                charge(ctx, 44);
                lwc1(f1, s1, tw::kX);
                v0 = 0x43680000;  // 232.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                a2 = 4;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x163280u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 451;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s1, tw::kX);
                add_s(f12, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                a2 = 2;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1632BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 561;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s1, tw::kX);
                add_s(f12, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                a2 = 1;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1632F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0016319c
                charge(ctx, 45);
                lwc1(f1, s1, tw::kX);
                v0 = 0x43360000;  // 182.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                a2 = 8;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1631CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x43AB0000;  // 342.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                a2 = 4;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x163204u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 561;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s1, tw::kX);
                add_s(f12, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
                a2 = 1;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x163240u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
            break;
        case 0x163300u:  // table[1, 6]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00163300 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x1A0);
}

// 0x00163330 sub_163330 -- 5612 bytes; frame 0x2B0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [H_Camp_PartyDrawEquipListElement] (tween, element, party work): one element of the party-status equipment list (as
// sub_12F6D0 for the member +8 and slot +16): slot header, candidates, cursor, comparison.
void sub_163330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00163330
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
        // 0x00163370
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 25152);  // &0x7B6240
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x16338Cu:  // table[0]: element 0: the list frame
            // 0x0016338c
            charge(ctx, 11);
            lbu(a3, s1, tw::kAlpha);
            a0 = s4;
            lw(a1, s0, pty::kFile1);
            a2 = 23;
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x1633A8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1633B8u:  // table[1]
            // 0x001633b8
            charge(ctx, 8);
            lh(a0, s0, pty::kPc);
            lh(a1, s0, pty::kSlot);
            jal(ctx, 0x1633C0u, gen::fn_datGetEquipmentIdx_0016cb80);
            lw(a0, s0, pty::kSlot);
            v1 = 2;
            if (a0 == v1) {
                // 0x00163490
                charge(ctx, 15);
                lwc1(f1, s1, tw::kX);
                v0 = 0x40800000;  // 4.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s4;
                lw(a1, s0, pty::kFile1);
                a2 = 20;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1634BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x001633d8
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00163454
                    charge(ctx, 15);
                    lwc1(f1, s1, tw::kX);
                    v0 = 0x40800000;  // 4.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s4;
                    lw(a1, s0, pty::kFile1);
                    a2 = 19;
                    lwc1(f13, s1, tw::kY);
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x163480u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x001633e4
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x001633f4
                        charge(ctx, 24);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s0, pty::kFile1);
                        a2 = 18;
                        lwc1(f12, s1, tw::kX);
                        lwc1(f13, s1, tw::kY);
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163410u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x42B20000;  // 89.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s0, pty::kFile1);
                        a2 = 21;
                        lwc1(f13, s1, tw::kY);
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163444u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x001633ec
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x1634CCu:  // table[2]
            // 0x001634cc
            charge(ctx, 39);
            lh(a0, s0, pty::kPc);
            lh(a1, s0, pty::kSlot);
            jal(ctx, 0x1634D4u, gen::fn_datGetEquipmentIdx_0016cb80);
            s3 = dsll32(v0, 16);
            s3 = dsra32(s3, 16);
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x1634ECu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
            a0 = v0;
            jal(ctx, 0x1634F8u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
            s2 = v0;
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x16350Cu, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            s5 = dsll32(v0, 16);
            s5 = dsra32(s5, 16);
            lh(a0, s0, pty::kPc);
            a1 = s3;
            jal(ctx, 0x163524u, gen::fn_sub_16F810_0016f810);  // (owner, index)
            v0 = v0 & 0xFF;
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            a0 = s5;
            jal(ctx, 0x16353Cu, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
            a0 = addiu(sp, 0x1A0);
            a1 = addiu(gp, -30340);  // "%s"
            a2 = v0;
            jal(ctx, 0x163550u, gen::fn_sprintf_00523ac8);
            lw(a0, s0, pty::kSlot);
            v1 = 3;
            if (a0 == v1) {
                // 0x00163b5c
                charge(ctx, 74);
                lbu(a3, s1, tw::kAlpha);
                a0 = s4;
                lw(a1, s0, pty::kFile1);
                a2 = 24;
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x163B78u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x41980000;  // 19.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s1, tw::kY);
                v0 = 0x40C00000;  // 6.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s4;
                lw(a1, s0, pty::kFile1);
                a2 = 6;
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x163BBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = sll(s2, 1);
                a2 = addiu(v0, 1);
                lwc1(f1, s1, tw::kX);
                v0 = 0x43020000;  // 130.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lwc1(f1, s1, tw::kY);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                add_s(f13, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s4;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x163C08u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lw(v1, s1, tw::kAlpha);
                v0 = 255;
                v1 = subu(v0, v1);
                lwc1(f1, s1, tw::kX);
                v0 = 0x432A0000;  // 170.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                lwc1(f1, s1, tw::kY);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = si(-256);
                a2 = v1 | v0;
                lwc1(f12, s1, tw::kZ);
                a3 = 6;
                t0 = 1;
                t1 = addiu(sp, 0x1A0);
                t2 = 16;
                t3 = 0;
                jal(ctx, 0x163C74u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
            } else {
                // 0x00163568
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x001639a0
                    charge(ctx, 111);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s4;
                    lw(a1, s0, pty::kFile1);
                    a2 = 24;
                    lwc1(f12, s1, tw::kX);
                    lwc1(f13, s1, tw::kY);
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x1639BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lwc1(f1, s1, tw::kX);
                    v0 = 0x41980000;  // 19.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x40C00000;  // 6.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s4;
                    lw(a1, s0, pty::kFile1);
                    a2 = 4;
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x163A00u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = sll(s2, 1);
                    a2 = addiu(v0, 1);
                    lwc1(f1, s1, tw::kX);
                    v0 = 0x43020000;  // 130.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s4;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x163A4Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v1, s1, tw::kAlpha);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    lwc1(f1, s1, tw::kX);
                    v0 = 0x432A0000;  // 170.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x41200000;  // 10.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    lwc1(f12, s1, tw::kZ);
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0x1A0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x163AB8u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    lwc1(f1, s1, tw::kX);
                    v0 = 0x43D90000;  // 434.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x2A8);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x41700000;  // 15.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x2AC);
                    a0 = 1;
                    jal(ctx, 0x163AF4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                    s4 = v0;
                    lwc1(f0, s1, tw::kZ);
                    cvt_w_s(f0, f0);
                    mfc1(s2, f0);
                    lh(a0, s0, pty::kPc);
                    a1 = s3;
                    jal(ctx, 0x163B14u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
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
                    lw(t3, s1, tw::kAlpha);
                    jal(ctx, 0x163B4Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                } else {
                    // 0x00163574
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x001637e4
                        charge(ctx, 111);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s0, pty::kFile1);
                        a2 = 24;
                        lwc1(f12, s1, tw::kX);
                        lwc1(f13, s1, tw::kY);
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163800u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x41980000;  // 19.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x40C00000;  // 6.0f
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s0, pty::kFile1);
                        a2 = 2;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163844u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = sll(s2, 1);
                        a2 = addiu(v0, 1);
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x43020000;  // 130.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x3F800000;  // 1.0f
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163890u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lw(v1, s1, tw::kAlpha);
                        v0 = 255;
                        v1 = subu(v0, v1);
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x432A0000;  // 170.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x41200000;  // 10.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        lwc1(f12, s1, tw::kZ);
                        a3 = 6;
                        t0 = 1;
                        t1 = addiu(sp, 0x1A0);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x1638FCu, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x43D90000;  // 434.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x2A8);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x41700000;  // 15.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x2AC);
                        a0 = 1;
                        jal(ctx, 0x163938u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        s4 = v0;
                        lwc1(f0, s1, tw::kZ);
                        cvt_w_s(f0, f0);
                        mfc1(s2, f0);
                        lh(a0, s0, pty::kPc);
                        a1 = s3;
                        jal(ctx, 0x163958u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
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
                        lw(t3, s1, tw::kAlpha);
                        jal(ctx, 0x163990u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                    } else {
                        // 0x00163580
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x00163590
                            charge(ctx, 149);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s4;
                            lw(a1, s0, pty::kFile1);
                            a2 = 24;
                            lwc1(f12, s1, tw::kX);
                            lwc1(f13, s1, tw::kY);
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x1635ACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x41980000;  // 19.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x40C00000;  // 6.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s4;
                            lw(a1, s0, pty::kFile1);
                            a2 = 0;
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x1635F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            v0 = sll(s2, 1);
                            a2 = addiu(v0, 1);
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x43020000;  // 130.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x3F800000;  // 1.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s4;
                            v0 = 0x830000;
                            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x16363Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lw(v1, s1, tw::kAlpha);
                            v0 = 255;
                            v1 = subu(v0, v1);
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x432A0000;  // 170.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x41200000;  // 10.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = si(-256);
                            a2 = v1 | v0;
                            lwc1(f12, s1, tw::kZ);
                            a3 = 6;
                            t0 = 1;
                            t1 = addiu(sp, 0x1A0);
                            t2 = 16;
                            t3 = 0;
                            jal(ctx, 0x1636A8u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x43D90000;  // 434.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x2A8);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x41700000;  // 15.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x2AC);
                            a0 = 1;
                            jal(ctx, 0x1636E4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            s4 = v0;
                            lwc1(f0, s1, tw::kZ);
                            cvt_w_s(f0, f0);
                            mfc1(s2, f0);
                            lh(a0, s0, pty::kPc);
                            a1 = s3;
                            jal(ctx, 0x163704u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
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
                            lw(t3, s1, tw::kAlpha);
                            jal(ctx, 0x16373Cu, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                            v0 = 525;
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, s1, tw::kX);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x2A8);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x41700000;  // 15.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x2AC);
                            a0 = 1;
                            jal(ctx, 0x16377Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            s4 = v0;
                            lwc1(f0, s1, tw::kZ);
                            cvt_w_s(f0, f0);
                            mfc1(s2, f0);
                            lh(a0, s0, pty::kPc);
                            a1 = s3;
                            jal(ctx, 0x16379Cu, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
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
                            lw(t3, s1, tw::kAlpha);
                            jal(ctx, 0x1637D4u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                        } else {
                            // 0x00163588
                            charge(ctx, 2);
                        }
                    }
                }
            }
            break;
        case 0x163C84u:  // table[3]
            // 0x00163c84
            charge(ctx, 23);
            v0 = 483;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, tw::kX);
            add_s(f12, f1, f0);
            lwc1(f1, s1, tw::kY);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            add_s(f13, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s4;
            lw(a1, s0, pty::kFile1);
            a2 = 39;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x163CC4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lw(v1, s0, pty::kList);
            lw(v0, v1, 11620);
            a0 = addiu(v0, -5);
            if (i64(a0) <= 0) {
                // 0x00163d08
                charge(ctx, 1);
                v1 = 0;
            } else {
                // 0x00163ce0
                charge(ctx, 10);
                lw(v1, v1, 11628);
                v0 = sll(v1, 4);
                v1 = subu(v0, v1);
                v0 = sll(v1, 2);
                v0 = subu(v0, v1);
                v0 = sll(v0, 1);
                div(v0, a0);
                mflo(v1);
            }
            // 0x00163d0c
            charge(ctx, 32);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40400000;  // 3.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v0 = 483;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s1, tw::kX);
            add_s(f12, f1, f0);
            lbu(a3, s1, tw::kAlpha);
            a0 = s4;
            lw(a1, s0, pty::kFile1);
            a2 = 40;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x163D5Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lh(a0, s0, pty::kPc);
            lh(a1, s0, pty::kSlot);
            jal(ctx, 0x163D6Cu, gen::fn_datGetEquipmentIdx_0016cb80);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
            lw(a0, s0, pty::kSlot);
            v1 = 2;
            if (a0 == v1) {
                // 0x00163e00
                charge(ctx, 6);
                lh(a0, s0, pty::kPc);
                a1 = s2;
                jal(ctx, 0x163E08u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                v1 = v0 & 0xFFFF;
                sw(v1, sp, 0x160);
            } else {
                // 0x00163d8c
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00163de0
                    charge(ctx, 8);
                    lh(a0, s0, pty::kPc);
                    a1 = s2;
                    jal(ctx, 0x163DE8u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                    v1 = v0 & 0xFFFF;
                    sw(v1, sp, 0x170);
                } else {
                    // 0x00163d98
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00163da8
                        charge(ctx, 14);
                        lh(a0, s0, pty::kPc);
                        a1 = s2;
                        jal(ctx, 0x163DB0u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                        v0 = v0 & 0xFFFF;
                        sw(v0, sp, 0x190);
                        lh(a0, s0, pty::kPc);
                        a1 = s2;
                        jal(ctx, 0x163DC8u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                        v1 = v0 & 0xFFFF;
                        sw(v1, sp, 0x180);
                    } else {
                        // 0x00163da0
                        charge(ctx, 2);
                    }
                }
            }
            // 0x00163e18
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00164784
                charge(ctx, 3);
                v1 = slti(s2, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00163e24
                charge(ctx, 7);
                lw(a1, s0, pty::kList);
                lw(v1, a1, 11628);
                a0 = addu(v1, s2);
                lw(v1, a1, 11620);
                at = slt(a0, v1);
                if (at != 0) {
                    // 0x00163e40
                    charge(ctx, 31);
                    v0 = sll(a0, 3);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 2);
                    v0 = addu(a1, v0);
                    lw(a0, v0, 120);
                    jal(ctx, 0x163E54u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                    sq(v0, sp, 0xF0);
                    lw(a0, s0, pty::kList);
                    lw(v0, a0, 11628);
                    v1 = addu(v0, s2);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(a0, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x163E90u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0x1A0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x163EA4u, gen::fn_sprintf_00523ac8);
                    lw(v0, s0, pty::kList);
                    lw(v1, v0, 11624);
                    if (v1 != s2) {
                        // 0x00163ef0
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
                        // 0x00163ebc
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
                    // 0x00163f14
                    charge(ctx, 2);
                    if (v1 == s2) {
                        // 0x00163f1c
                        charge(ctx, 35);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s2);
                        s3 = sll(v0, 1);
                        lwc1(f1, s1, tw::kY);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s0, pty::kFile1);
                        a2 = 37;
                        lwc1(f12, s1, tw::kX);
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163F5Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s1, tw::kY);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x43EB0000;  // 470.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        lw(a1, s0, pty::kFile1);
                        a2 = 38;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x163FA0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x00163fa8
                    charge(ctx, 3);
                    lw(v0, sp, 0x12C);
                    if (v0 != 0) {
                        // 0x00164040
                        charge(ctx, 30);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s2);
                        s3 = sll(v0, 1);
                        lwc1(f1, s1, tw::kY);
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
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x41500000;  // 13.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x1640B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x00163fb4
                        charge(ctx, 35);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s2);
                        s3 = sll(v0, 1);
                        lwc1(f1, s1, tw::kY);
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
                        lwc1(f1, s1, tw::kX);
                        v0 = 0x41500000;  // 13.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s4;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        t0 = 32;
                        t1 = 67;
                        t2 = 120;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x164030u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    }
                    // 0x001640b8
                    charge(ctx, 36);
                    lw(v1, s1, tw::kAlpha);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    lwc1(f1, s1, tw::kX);
                    v0 = 0x42540000;  // 53.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x41100000;  // 9.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    lb(v0, sp, 0x130);
                    a3 = v0;
                    lwc1(f12, s1, tw::kZ);
                    t0 = 1;
                    t1 = addiu(sp, 0x1A0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x164130u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    lw(a0, s0, pty::kSlot);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x001645f4
                        charge(ctx, 30);
                        lw(a0, s0, pty::kList);
                        lw(v0, a0, 11628);
                        v1 = addu(v0, s2);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(a0, v0);
                        lhu(v0, v0, 134);
                        sq(v0, sp, 0xB0);
                        v0 = 317;
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s1, tw::kX);
                        add_s(f2, f1, f0);
                        swc1(f2, sp, 0x2A8);
                        lwc1(f1, s1, tw::kY);
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
                            // 0x00164680
                            charge(ctx, 5);
                            paddub(v1, v0, zero);
                            lw(v0, sp, 0x160);
                            at = slt(v0, v1);
                            if (at == 0) {
                                // 0x001646ec
                                charge(ctx, 18);
                                v0 = 0x42440000;  // 49.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f2);
                                v0 = 0x40400000;  // 3.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s4;
                                lw(a1, s0, pty::kFile1);
                                a2 = fp;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x164720u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                s3 = 255;
                                s5 = s3;
                                s7 = s3;
                            } else {
                                // 0x00164694
                                charge(ctx, 22);
                                v0 = 0x42440000;  // 49.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f2);
                                v0 = 0x40400000;  // 3.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s4;
                                lw(a1, s0, pty::kFile1);
                                a2 = s7;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x1646C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                s3 = s5 & 0xFF;
                                lbu(v0, sp, 0x100);
                                s5 = v0;
                                lbu(v0, sp, 0x110);
                                s7 = v0;
                            }
                        } else {
                            // 0x0016466c
                            charge(ctx, 5);
                            s3 = 255;
                            s5 = s3;
                            s7 = s3;
                        }
                        // 0x00164734
                        charge(ctx, 19);
                        a0 = s6;
                        jal(ctx, 0x164738u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        lwc1(f0, s1, tw::kZ);
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
                        lw(t3, s1, tw::kAlpha);
                        jal(ctx, 0x164778u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                    } else {
                        // 0x00164148
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x00164460
                            charge(ctx, 30);
                            lw(a0, s0, pty::kList);
                            lw(v0, a0, 11628);
                            v1 = addu(v0, s2);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(a0, v0);
                            lhu(v0, v0, 132);
                            sq(v0, sp, 0xC0);
                            v0 = 317;
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, s1, tw::kX);
                            add_s(f2, f1, f0);
                            swc1(f2, sp, 0x2A8);
                            lwc1(f1, s1, tw::kY);
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
                                // 0x001644ec
                                charge(ctx, 5);
                                paddub(v1, v0, zero);
                                lw(v0, sp, 0x170);
                                at = slt(v0, v1);
                                if (at == 0) {
                                    // 0x00164558
                                    charge(ctx, 18);
                                    v0 = 0x42440000;  // 49.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f2);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s4;
                                    lw(a1, s0, pty::kFile1);
                                    a2 = fp;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x16458Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s3 = 255;
                                    s5 = s3;
                                    s7 = s3;
                                } else {
                                    // 0x00164500
                                    charge(ctx, 22);
                                    v0 = 0x42440000;  // 49.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f2);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s4;
                                    lw(a1, s0, pty::kFile1);
                                    a2 = s7;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x164534u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s3 = s5 & 0xFF;
                                    lbu(v0, sp, 0x100);
                                    s5 = v0;
                                    lbu(v0, sp, 0x110);
                                    s7 = v0;
                                }
                            } else {
                                // 0x001644d8
                                charge(ctx, 5);
                                s3 = 255;
                                s5 = s3;
                                s7 = s3;
                            }
                            // 0x001645a0
                            charge(ctx, 21);
                            a0 = s6;
                            jal(ctx, 0x1645A4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            lwc1(f0, s1, tw::kZ);
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
                            lw(t3, s1, tw::kAlpha);
                            jal(ctx, 0x1645E4u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                        } else {
                            // 0x00164154
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x00164164
                                charge(ctx, 30);
                                lw(a0, s0, pty::kList);
                                lw(v0, a0, 11628);
                                v1 = addu(v0, s2);
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(a0, v0);
                                lhu(v0, v0, 128);
                                sq(v0, sp, 0xE0);
                                v0 = 317;
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lwc1(f0, s1, tw::kX);
                                add_s(f2, f1, f0);
                                swc1(f2, sp, 0x2A8);
                                lwc1(f1, s1, tw::kY);
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
                                    // 0x001641f0
                                    charge(ctx, 5);
                                    paddub(v1, v0, zero);
                                    lw(v0, sp, 0x190);
                                    at = slt(v0, v1);
                                    if (at == 0) {
                                        // 0x0016425c
                                        charge(ctx, 18);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f2);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s1, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s0, pty::kFile1);
                                        a2 = fp;
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x164290u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = 255;
                                        sb(s3, sp, 0x150);
                                        sb(s3, sp, 0x140);
                                    } else {
                                        // 0x00164204
                                        charge(ctx, 22);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f2);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s1, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s0, pty::kFile1);
                                        a2 = s7;
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x164238u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = s5 & 0xFF;
                                        lbu(v0, sp, 0x100);
                                        sb(v0, sp, 0x150);
                                        lbu(v0, sp, 0x110);
                                        sb(v0, sp, 0x140);
                                    }
                                } else {
                                    // 0x001641dc
                                    charge(ctx, 5);
                                    s3 = 255;
                                    sb(s3, sp, 0x150);
                                    sb(s3, sp, 0x140);
                                }
                                // 0x001642a4
                                charge(ctx, 38);
                                a0 = s6;
                                jal(ctx, 0x1642A8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f0, s1, tw::kZ);
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
                                lw(t3, s1, tw::kAlpha);
                                jal(ctx, 0x1642E8u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                                lw(a0, s0, pty::kList);
                                lw(v0, a0, 11628);
                                v1 = addu(v0, s2);
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                v0 = addu(a0, v0);
                                lhu(v0, v0, 130);
                                sq(v0, sp, 0xD0);
                                lwc1(f1, sp, 0x2A8);
                                v0 = 0x42B60000;  // 91.0f
                                mtc1(v0, f0);
                                add_s(f1, f1, f0);
                                swc1(f1, sp, 0x2A8);
                                lw(v1, sp, 0x180);
                                lq(v0, sp, 0xD0);
                                if (v1 != v0) {
                                    // 0x00164350
                                    charge(ctx, 5);
                                    paddub(v1, v0, zero);
                                    lw(v0, sp, 0x180);
                                    at = slt(v0, v1);
                                    if (at == 0) {
                                        // 0x001643c0
                                        charge(ctx, 19);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f1);
                                        lwc1(f1, sp, 0x2AC);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s1, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s0, pty::kFile1);
                                        a2 = fp;
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x1643F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = 255;
                                        s5 = s3;
                                        s7 = s3;
                                    } else {
                                        // 0x00164364
                                        charge(ctx, 23);
                                        v0 = 0x42440000;  // 49.0f
                                        mtc1(v0, f0);
                                        add_s(f12, f0, f1);
                                        lwc1(f1, sp, 0x2AC);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        sub_s(f13, f1, f0);
                                        lbu(a3, s1, tw::kAlpha);
                                        a0 = s4;
                                        lw(a1, s0, pty::kFile1);
                                        a2 = s7;
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x16439Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        s3 = s5 & 0xFF;
                                        lbu(v0, sp, 0x100);
                                        s5 = v0;
                                        lbu(v0, sp, 0x110);
                                        s7 = v0;
                                    }
                                } else {
                                    // 0x0016433c
                                    charge(ctx, 5);
                                    s3 = 255;
                                    s5 = s3;
                                    s7 = s3;
                                }
                                // 0x0016440c
                                charge(ctx, 21);
                                a0 = s6;
                                jal(ctx, 0x164410u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f0, s1, tw::kZ);
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
                                lw(t3, s1, tw::kAlpha);
                                jal(ctx, 0x164450u, gen::fn_sub_12E170_0012e170);  // (file, first sprite, xy, z, r, g, b, alpha, value, digits) number
                            } else {
                                // 0x0016415c
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x00164780
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00164790
            charge(ctx, 2);
            break;
        case 0x164798u:  // table[4]
            // 0x00164798
            charge(ctx, 25);
            a0 = 0;
            lw(a1, s0, pty::kFile1);
            a2 = 27;
            jal(ctx, 0x1647A4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s4 = v0;
            lwc1(f0, s1, tw::kZ);
            swc1(f0, v0, 44);
            lwc1(f0, s1, tw::kX);
            swc1(f0, v0, 16);
            lwc1(f0, s1, tw::kY);
            swc1(f0, v0, 20);
            lw(v1, s1, tw::kAlpha);
            sb(v1, v0, 24);
            v1 = lui(0xC234);
            sw(v1, v0, 32);
            a0 = s4;
            a1 = 1;
            jal(ctx, 0x1647E0u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s4;
            jal(ctx, 0x1647ECu, gen::fn_sub_115980_00115980);  // draw and release the handle
            break;
        case 0x1647FCu:  // table[6]
            // 0x001647fc
            charge(ctx, 33);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            a2 = subu(v0, v1);
            lw(a3, s0, pty::kList);
            lw(v1, a3, 11628);
            lw(v0, a3, 11624);
            v1 = addu(v0, v1);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lwc1(f0, s1, tw::kX);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            lwc1(f0, s1, tw::kY);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            v0 = si(-256);
            a2 = a2 | v0;
            a3 = addu(v1, a3);
            lbu(v0, a3, 124);
            v1 = sll(v0, 16);
            v0 = lui(0xFFFF);
            v1 = v1 & v0;
            lhu(v0, a3, 100);
            t2 = v0 | v1;
            lwc1(f12, s1, tw::kZ);
            a3 = 1;
            t0 = 10;
            t1 = a3;
            jal(ctx, 0x164870u, gen::fn_sub_3C7E20_003c7e20);  // a message text
            break;
        case 0x164880u:  // table[7]
            // 0x00164880
            charge(ctx, 26);
            lbu(a3, s1, tw::kAlpha);
            a0 = s4;
            lw(a1, s0, pty::kFile1);
            a2 = 36;
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x16489Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x41700000;  // 15.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lwc1(f1, s1, tw::kY);
            v0 = 0x40A00000;  // 5.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s1, tw::kAlpha);
            a0 = s4;
            lw(a1, s0, pty::kFile1);
            a2 = 35;
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x1648E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x1648E8u:  // table[5]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x001648e8 (the shared epilogue, written out on this path)
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

// 0x00164920 sub_164920 -- 8324 bytes; frame 0x260: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_Camp_UpdatePartyStatusDrawTask] Update of "H_CampPartyStatusDraw" (jump table 0x7B6260): 0 waits for
// camp_fr%02d.pak (+24) and starts the character picture build (camp/chara/i_camp_hum_blue_%02d.tmx; The Answer: AGS_
// variants for members 1 / 3 / 9); 1 takes the texture (+28) and the sprite files, requests flash 1, allocates the
// tweens (+44); 2 slides in and sets the portraits to screen 2; 3 is the input state (confirm -> 9 equipment, cancel ->
// close, page switch); 4..7 the exits; 9..0xB the equipment list (+52 = an 11,632-byte list from sub_13C240; confirm
// equips through the equipment setters 0x16FEA0..0x170530), 0xC / 0xD back (RwFree of the list).
void sub_164920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00164920
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x260);
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
    s4 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, pty::kState);
    at = sltiu(v0, 14);
    if (at != 0) {
        // 0x00164964
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25184);  // &0x7B6260
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x164980u:  // table[0]: state 0: the pak, start the character picture build
            // 0x00164980
            charge(ctx, 5);
            lw(a0, s0, pty::kPak);
            jal(ctx, 0x164984u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00164994
                charge(ctx, 4);
                jal(ctx, 0x164994u, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
                if (v0 == 0) {
                    // 0x00164a28
                    charge(ctx, 6);
                    a0 = addiu(sp, 0xE0);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -16896);  // "camp/chara/i_camp_hum_blue_%02d.tmx"
                    lw(a2, s0, pty::kPc);
                    jal(ctx, 0x164A38u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x001649a4
                    charge(ctx, 4);
                    lw(a2, s0, pty::kPc);
                    v0 = 9;
                    if (a2 == v0) {
                        // 0x001649f0
                        charge(ctx, 7);
                        a0 = addiu(sp, 0xE0);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -16944);  // "camp/chara/AGS_i_camp_hum_blue_%02d.tmx"
                        jal(ctx, 0x1649FCu, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x001649b4
                        charge(ctx, 3);
                        v0 = 3;
                        if (a2 != v0) {
                            // 0x001649c0
                            charge(ctx, 3);
                            v0 = 1;
                            if (a2 == v0) {
                                goto L_001649d4;
                            }
                            // 0x001649cc
                            charge(ctx, 2);
                            // 0x00164a0c
                            charge(ctx, 7);
                            a0 = addiu(sp, 0xE0);
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -16896);  // "camp/chara/i_camp_hum_blue_%02d.tmx"
                            jal(ctx, 0x164A18u, gen::fn_sprintf_00523ac8);
                            goto L_00164a40;
                        }
                    L_001649d4:
                        charge(ctx, 7);
                        a0 = addiu(sp, 0xE0);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -16992);  // "camp/chara/AGS_i_camp_hum_blue_03.tmx"
                        jal(ctx, 0x1649E0u, gen::fn_sprintf_00523ac8);
                    }
                }
            L_00164a40:
                charge(ctx, 40);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, -16848);  // "_h_camp_fr_status.c"
                sd(v0, sp, 0x10);
                v0 = 1036;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = addiu(sp, 0xE0);
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x164A7Cu, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                sw(v0, s0, pty::kBuild);
                lw(a0, s0, pty::kPak);
                a1 = 0;
                a2 = addiu(sp, 0x25C);
                jal(ctx, 0x164A94u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x164AA0u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, pty::kFile0);
                lw(a0, s0, pty::kPak);
                a1 = 1;
                a2 = addiu(sp, 0x25C);
                jal(ctx, 0x164AB8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x164AC4u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, pty::kFile1);
                v0 = 1;
                sw(v0, s0, pty::kState);
            }
        L_0016696c:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x164AE0u:  // table[1]: state 1: texture and sprite files, flash 1, tweens
            // 0x00164ae0
            charge(ctx, 4);
            s1 = 1;
            lw(v0, s0, pty::kTexture);
            if (v0 == 0) {
                // 0x00164af0
                charge(ctx, 9);
                lw(a0, s0, pty::kBuild);
                a1 = addiu(sp, 0x258);
                a2 = 0;
                jal(ctx, 0x164AFCu, gen::fn_sub_10C3A0_0010c3a0);  // poll the texture build
                sw(v0, s0, pty::kTexture);
                lw(v0, sp, 0x258);
                if (v0 == 0) {
                    // 0x00164b14
                    charge(ctx, 2);
                    sw(zero, s0, pty::kTexture);
                    s1 = 0;
                }
            }
            // 0x00164b1c
            charge(ctx, 5);
            lw(a0, s0, pty::kFile0);
            jal(ctx, 0x164B20u, gen::fn_sprFileIsReady_00111f30);
            if (v0 == 0) {
                // 0x00164b30
                charge(ctx, 1);
                s1 = 0;
            }
            // 0x00164b34
            charge(ctx, 5);
            lw(a0, s0, pty::kFile0);
            jal(ctx, 0x164B38u, gen::fn_sprFileIsReady_00111f30);
            if (v0 == 0) {
                // 0x00164b48
                charge(ctx, 1);
                s1 = 0;
            }
            // 0x00164b4c
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00164b54
                charge(ctx, 16);
                lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
                a1 = 1;
                jal(ctx, 0x164B5Cu, gen::fn_sub_1685E0_001685e0);  // [H_Camp_FrStatusFlashRequest]
                a0 = 10;
                jal(ctx, 0x164B68u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, pty::kTweens);
                a0 = 10;
                jal(ctx, 0x164B78u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, pty::kListTweens);
                v0 = 2;
                sw(v0, s0, pty::kState);
            }
            goto L_0016696c;
        case 0x164B94u:  // table[2]: state 2: slide in, portraits to screen 2
            // 0x00164b94
            charge(ctx, 11);
            lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
            a1 = 2;
            jal(ctx, 0x164B9Cu, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
            lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
            a1 = 2;
            jal(ctx, 0x164BACu, gen::fn_sub_122710_00122710);  // [H_Camp_PersonaKaniSetScreen]
            s1 = 0;
            for (;;) {
                // 0x00164c98
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00164bc0
                charge(ctx, 18);
                v0 = 0x41700000;  // 15.0f
                sw(v0, sp, 0x248);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x423C0000;  // 47.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x24C);
                ld(v0, sp, 0x248);
                sd(v0, sp, 0x250);
                lw(v0, s0, 4);
                if (v0 != 0) {
                    // 0x00164c28
                    charge(ctx, 6);
                    lwc1(f1, sp, 0x250);
                    v0 = 0x43960000;  // 300.0f
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    swc1(f0, sp, 0x250);
                } else {
                    // 0x00164c08
                    charge(ctx, 8);
                    lwc1(f1, sp, 0x254);
                    v0 = 0x43960000;  // 300.0f
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, sp, 0x254);
                }
                // 0x00164c40
                charge(ctx, 22);
                v0 = sll(s1, 1);
                sd(v0, sp, 0x0);
                v0 = addiu(v0, 10);
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 2);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, pty::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x250);
                ld(t1, sp, 0x248);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x164C8Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00164ca4
            charge(ctx, 27);
            v0 = 0x43C80000;  // 400.0f
            sw(v0, sp, 0x248);
            sw(zero, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x164CE8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x433C0000;  // 188.0f
            sw(v0, sp, 0x248);
            sw(zero, sp, 0x24C);
            ld(v0, sp, 0x248);
            sd(v0, sp, 0x1E0);
            lw(v0, s0, 4);
            if (v0 != 0) {
                // 0x00164d30
                charge(ctx, 6);
                lwc1(f1, sp, 0x1E0);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x1E0);
            } else {
                // 0x00164d10
                charge(ctx, 8);
                lwc1(f1, sp, 0x1E4);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x1E4);
            }
            // 0x00164d48
            charge(ctx, 24);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, pty::kTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1E0);
            ld(t1, sp, 0x248);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x164D7Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B30000;  // 358.0f
            sw(v0, sp, 0x248);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x24C);
            ld(v0, sp, 0x248);
            sd(v0, sp, 0x1E8);
            lw(v0, s0, 4);
            if (v0 != 0) {
                // 0x00164dc8
                charge(ctx, 6);
                lwc1(f1, sp, 0x1E8);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x1E8);
            } else {
                // 0x00164da8
                charge(ctx, 8);
                lwc1(f1, sp, 0x1EC);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x1EC);
            }
            // 0x00164de0
            charge(ctx, 27);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1E8);
            ld(t1, sp, 0x248);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x164E18u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x248);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x24C);
            ld(v0, sp, 0x248);
            sd(v0, sp, 0x1F0);
            lw(v0, s0, 4);
            if (v0 != 0) {
                // 0x00164e6c
                charge(ctx, 6);
                lwc1(f1, sp, 0x1F0);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x1F0);
            } else {
                // 0x00164e4c
                charge(ctx, 8);
                lwc1(f1, sp, 0x1F4);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x1F4);
            }
            // 0x00164e84
            charge(ctx, 20);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1F0);
            ld(t1, sp, 0x248);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x164EBCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 3;
            sw(v0, s0, pty::kState);
            goto L_0016696c;
        case 0x164ED4u:  // table[3]: state 3: input
            // 0x00164ed4
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00164f58
                charge(ctx, 3);
                v0 = slti(s2, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00164ee4
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00164f04
                    charge(ctx, 4);
                    jal(ctx, 0x164F04u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00164f14
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x164F24u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                    // 0x00164f2c
                    charge(ctx, 9);
                    lw(v1, s0, pty::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x00164f50
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00164f54
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00164f64
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00164f6c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v1 = v0 & 0x40;  // confirm
                if (v1 == 0) {
                    // 0x00164fb4
                    charge(ctx, 3);
                    v1 = v0 & 0x20;
                    if (v1 == 0) {
                        // 0x00164ff0
                        charge(ctx, 6);
                        a1 = 1;
                        v1 = 0x7E0000;
                        lhu(a0, v1, 2386);  // 0x7E0952
                        v1 = a0 & 0x2000;
                        if (v1 == 0) {
                            // 0x00165008
                            charge(ctx, 5);
                            v1 = 0x7E0000;
                            lhu(v1, v1, 2394);  // 0x7E095A
                            v1 = v1 & 0x2000;
                            if (v1 == 0) {
                                // 0x0016501c
                                charge(ctx, 1);
                                a1 = 0;
                            }
                        }
                        // 0x00165020
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x00165058
                            charge(ctx, 4);
                            v1 = a0 & 0x1000;
                            v1 = sltu(0, v1);
                            if (v1 == 0) {
                                // 0x00165068
                                charge(ctx, 4);
                                v1 = 0x7E0000;
                                lhu(v1, v1, 2394);  // 0x7E095A
                                v1 = v1 & 0x1000;
                                v1 = sltu(0, v1);
                            }
                            // 0x00165078
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x00165080
                                charge(ctx, 3);
                                lw(v1, s0, 20);
                                if (v1 != 0) {
                                    goto L_00165114;
                                }
                                // 0x0016508c
                                charge(ctx, 3);
                                lw(v1, s0, pty::kSlot);
                                if (v1 != 0) {
                                    // 0x001650e8
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x1650F8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, pty::kSlot);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s0, pty::kSlot);
                                } else {
                                    // 0x00165098
                                    charge(ctx, 4);
                                    v0 = v0 & 0x1000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x001650a8
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x1000;  // cursor - 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x001650b8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x001650c0
                                        charge(ctx, 10);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x1650D0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        v0 = 3;
                                        sw(v0, s0, pty::kSlot);
                                    }
                                }
                                goto L_0016696c;
                            }
                        L_00165114:
                            charge(ctx, 4);
                            v1 = a0 & 0x4000;
                            v1 = sltu(0, v1);
                            if (v1 == 0) {
                                // 0x00165124
                                charge(ctx, 4);
                                v1 = 0x7E0000;
                                lhu(v1, v1, 2394);  // 0x7E095A
                                v1 = v1 & 0x4000;
                                v1 = sltu(0, v1);
                            }
                            // 0x00165134
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x0016513c
                                charge(ctx, 3);
                                lw(v1, s0, 20);
                                if (v1 != 0) {
                                    goto L_001651d0;
                                }
                                // 0x00165148
                                charge(ctx, 4);
                                lw(a0, s0, pty::kSlot);
                                v1 = 3;
                                if (a0 != v1) {
                                    // 0x001651a4
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x1651B4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, pty::kSlot);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, pty::kSlot);
                                } else {
                                    // 0x00165158
                                    charge(ctx, 4);
                                    v0 = v0 & 0x4000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x00165168
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x00165178
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00165180
                                        charge(ctx, 9);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x165190u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        sw(zero, s0, pty::kSlot);
                                    }
                                }
                                goto L_0016696c;
                            }
                        L_001651d0:
                            charge(ctx, 3);
                            lw(v0, s0, 20);
                            if (v0 != 0) {
                                // 0x001651dc
                                charge(ctx, 3);
                                v0 = a0 & 0x4;
                                if (v0 == 0) {
                                    // 0x00165218
                                    charge(ctx, 3);
                                    v0 = a0 & 0x8;
                                    if (v0 != 0) {
                                        // 0x00165224
                                        charge(ctx, 12);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x165234u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        v0 = 2;
                                        sw(v0, s0, 12);
                                        v0 = 8;
                                        sw(v0, s0, pty::kState);
                                    }
                                } else {
                                    // 0x001651e8
                                    charge(ctx, 12);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x1651F8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    v0 = 3;
                                    sw(v0, s0, 12);
                                    v0 = 8;
                                    sw(v0, s0, pty::kState);
                                }
                            }
                        } else {
                            // 0x00165028
                            charge(ctx, 12);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x165038u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            v0 = 1;
                            sw(v0, s0, 12);
                            v0 = 8;
                            sw(v0, s0, pty::kState);
                        }
                    } else {
                        // 0x00164fc0
                        charge(ctx, 12);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x164FD0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = si(-1);
                        sw(v0, s0, 12);
                        v0 = 8;
                        sw(v0, s0, pty::kState);
                    }
                } else {
                    // 0x00164f80
                    charge(ctx, 3);
                    lw(v0, s0, 20);
                    if (v0 == 0) {
                        // 0x00164f8c
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x164F9Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 9;
                        sw(v0, s0, pty::kState);
                    }
                }
            }
            goto L_0016696c;
        case 0x165254u:  // table[4]: state 4: slide out (close)
            // 0x00165254
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001652ac
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165260
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00165280
                    charge(ctx, 4);
                    jal(ctx, 0x165280u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00165290
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x1652A0u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                }
                // 0x001652a8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x001652b8
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0016534c
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001652c4
                charge(ctx, 34);
                v0 = 0x41700000;  // 15.0f
                sw(v0, sp, 0x248);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x423C0000;  // 47.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x24C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 2);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, pty::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x248);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x165340u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00165358
            charge(ctx, 90);
            v0 = 0x43C80000;  // 400.0f
            sw(v0, sp, 0x248);
            sw(zero, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x16539Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, pty::kTweens);
            lwc1(f1, a0, 48);
            lwc1(f0, a0, 52);
            swc1(f1, sp, 0x1F8);
            swc1(f0, sp, 0x1FC);
            ld(v0, sp, 0x1F8);
            sd(v0, sp, 0x248);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1F8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1653F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B30000;  // 358.0f
            sw(v0, sp, 0x248);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165440u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x248);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165498u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
            a1 = 0;
            jal(ctx, 0x1654A8u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
            v0 = 5;
            sw(v0, s0, pty::kState);
            goto L_0016696c;
        case 0x1654C0u:  // table[5]: state 5: done (-1)
            // 0x001654c0
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00165544
                charge(ctx, 3);
                v0 = slti(s2, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001654d0
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x001654f0
                    charge(ctx, 4);
                    jal(ctx, 0x1654F0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00165500
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x165510u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                    // 0x00165518
                    charge(ctx, 9);
                    lw(v1, s0, pty::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0016553c
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00165540
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00165550
            charge(ctx, 2);
            if (s1 == 0) {
                goto L_0016696c;
            }
            // 0x00165558
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x165564u:  // table[6]: state 6: slide out (page switch)
            // 0x00165564
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001655bc
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165570
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00165590
                    charge(ctx, 4);
                    jal(ctx, 0x165590u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x001655a0
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x1655B0u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                }
                // 0x001655b8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x001655c8
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00165678
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001655d4
                charge(ctx, 41);
                v0 = 0x41700000;  // 15.0f
                mtc1(v0, f2);
                sw(v0, sp, 0x248);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x423C0000;  // 47.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x24C);
                ld(t0, sp, 0x248);
                sd(t0, sp, 0x200);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                sub_s(f0, f2, f0);
                swc1(f0, sp, 0x248);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 2);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, pty::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t1, sp, 0x248);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x16566Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00165684
            charge(ctx, 110);
            v0 = 0x43C80000;  // 400.0f
            sw(v0, sp, 0x248);
            sw(zero, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1656C8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, pty::kTweens);
            lwc1(f1, a0, 48);
            lwc1(f0, a0, 52);
            swc1(f1, sp, 0x208);
            swc1(f0, sp, 0x20C);
            ld(v0, sp, 0x208);
            sd(v0, sp, 0x230);
            lwc1(f1, sp, 0x230);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x230);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x208);
            ld(t1, sp, 0x230);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165734u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B30000;  // 358.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x230);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x234);
            ld(t0, sp, 0x230);
            sd(t0, sp, 0x210);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x230);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x230);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1657A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            mtc1(zero, f1);
            sw(zero, sp, 0x230);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x234);
            ld(t0, sp, 0x230);
            sd(t0, sp, 0x218);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x230);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x230);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165814u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
            a1 = 0;
            jal(ctx, 0x165824u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
            v0 = 7;
            sw(v0, s0, pty::kState);
            goto L_0016696c;
        case 0x16583Cu:  // table[7]: state 7: done (-1)
            // 0x0016583c
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x001658c0
                charge(ctx, 3);
                v0 = slti(s2, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0016584c
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0016586c
                    charge(ctx, 4);
                    jal(ctx, 0x16586Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0016587c
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x16588Cu, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                    // 0x00165894
                    charge(ctx, 9);
                    lw(v1, s0, pty::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x001658b8
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x001658bc
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x001658cc
            charge(ctx, 2);
            if (s1 == 0) {
                goto L_0016696c;
            }
            // 0x001658d4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x1658E0u:  // table[8]: state 8
            // 0x001658e0
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00165938
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001658ec
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0016590c
                    charge(ctx, 4);
                    jal(ctx, 0x16590Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0016591c
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x16592Cu, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                }
                // 0x00165934
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00165944
            charge(ctx, 2);
            goto L_0016696c;
        case 0x16594Cu:  // table[9]: state 9: open the equipment list (flash 4)
            // 0x0016594c
            charge(ctx, 14);
            lw(v0, s4, 76);
            lw(v0, v0, 60);
            sw(zero, v0, 44);
            a0 = 1;
            a1 = 11632;
            a2 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, 388);  // 0x960184
            jalr(ctx, 0x16596Cu, v0.u());
            a1 = 0;
            a0 = si(-1);
            for (;;) {
                // 0x001659a8
                charge(ctx, 3);
                v1 = slti(a1, 320);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165984
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
            // 0x001659b4
            charge(ctx, 17);
            sw(v0, s0, pty::kList);
            lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
            a1 = 4;
            jal(ctx, 0x1659C0u, gen::fn_sub_1685E0_001685e0);  // [H_Camp_FrStatusFlashRequest]
            lh(a1, s0, pty::kPc);
            lh(a2, s0, pty::kSlot);
            lw(a0, s0, pty::kList);
            jal(ctx, 0x1659D4u, gen::fn_sub_13C240_0013c240);  // a member slot's candidate list
            lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
            a1 = 0;
            jal(ctx, 0x1659E4u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
            s1 = 0;
            for (;;) {
                // 0x00165a44
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001659f8
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00165a18
                    charge(ctx, 4);
                    jal(ctx, 0x165A18u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00165a28
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x165A38u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                }
                // 0x00165a40
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00165a50
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00165ae4
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165a5c
                charge(ctx, 34);
                v0 = 0x41700000;  // 15.0f
                sw(v0, sp, 0x248);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x423C0000;  // 47.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x24C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 2);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, pty::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x248);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x165AD8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x00165af0
            charge(ctx, 230);
            v0 = 0x43C80000;  // 400.0f
            sw(v0, sp, 0x248);
            sw(zero, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165B34u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, pty::kTweens);
            lwc1(f1, a0, 48);
            lwc1(f0, a0, 52);
            swc1(f1, sp, 0x220);
            swc1(f0, sp, 0x224);
            ld(v0, sp, 0x220);
            sd(v0, sp, 0x238);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x220);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165B88u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B30000;  // 358.0f
            sw(v0, sp, 0x238);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165BD8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x238);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165C30u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x238);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, pty::kListTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165C7Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 419;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x238);
            v0 = 0x42140000;  // 37.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165CD8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x238);
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165D24u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42EA0000;  // 117.0f
            sw(v0, sp, 0x238);
            v0 = 0x42D80000;  // 108.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165D74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43F20000;  // 484.0f
            sw(v0, sp, 0x238);
            v0 = 0x43B60000;  // 364.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165DC4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43360000;  // 182.0f
            sw(v0, sp, 0x238);
            v0 = 0x43720000;  // 242.0f
            sw(v0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165E14u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41E00000;  // 28.0f
            sw(v0, sp, 0x238);
            v0 = 421;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x23C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x238);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x165E70u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 10;
            sw(v0, s0, pty::kState);
            goto L_0016696c;
        case 0x165E88u:  // table[10]: state 10: arrived
            // 0x00165e88
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00165f0c
                charge(ctx, 3);
                v0 = slti(s2, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165e98
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00165eb8
                    charge(ctx, 4);
                    jal(ctx, 0x165EB8u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00165ec8
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x165ED8u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                    // 0x00165ee0
                    charge(ctx, 9);
                    lw(v1, s0, pty::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x00165f04
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00165f08
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00165f18
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00165f20
                charge(ctx, 2);
                v0 = 11;
                sw(v0, s0, pty::kState);
            }
            // 0x00165f28
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00165f80
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165f34
                charge(ctx, 8);
                lw(v1, s0, pty::kListTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00165f54
                    charge(ctx, 4);
                    jal(ctx, 0x165F54u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00165f64
                        charge(ctx, 6);
                        lw(v0, s0, pty::kListTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x165F74u, gen::fn_sub_163330_00163330);  // the party equipment list's element draw
                    }
                }
                // 0x00165f7c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00165f8c
            charge(ctx, 2);
            goto L_0016696c;
        case 0x165F94u:  // table[11]: state 11: the equipment list (input; equip)
            // 0x00165f94
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00166018
                charge(ctx, 3);
                v0 = slti(s2, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00165fa4
                charge(ctx, 8);
                lw(v1, s0, pty::kListTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00165fc4
                    charge(ctx, 4);
                    jal(ctx, 0x165FC4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00165fd4
                        charge(ctx, 6);
                        lw(v0, s0, pty::kListTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x165FE4u, gen::fn_sub_163330_00163330);  // the party equipment list's element draw
                    }
                    // 0x00165fec
                    charge(ctx, 9);
                    lw(v1, s0, pty::kListTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x00166010
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00166014
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00166024
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0016602c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v1 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x00166068
                    charge(ctx, 3);
                    v0 = v1 & 0x40;
                    if (v0 == 0) {
                        // 0x00166360
                        charge(ctx, 9);
                        lw(v0, s0, pty::kList);
                        lw(a0, v0, 11620);
                        a1 = 5;
                        a2 = addiu(v0, 11628);
                        a3 = addiu(v0, 11624);
                        jal(ctx, 0x166374u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                    } else {
                        // 0x00166074
                        charge(ctx, 12);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 7;
                        jal(ctx, 0x166084u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        lw(v0, s0, pty::kList);
                        lw(v1, v0, 11624);
                        lw(v0, v0, 11628);
                        v0 = addu(v1, v0);
                        if (v0 != 0) {
                            // 0x001660a4
                            charge(ctx, 171);
                            lh(a0, s0, pty::kPc);
                            lh(a1, s0, pty::kSlot);
                            jal(ctx, 0x1660ACu, gen::fn_datGetEquipmentIdx_0016cb80);
                            s5 = dsll32(v0, 16);
                            s5 = dsra32(s5, 16);
                            lw(a0, s0, pty::kList);
                            lw(v1, a0, 11628);
                            lw(v0, a0, 11624);
                            v1 = addu(v1, v0);
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, a0);
                            lw(s4, v0, 104);
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x1660E8u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                            s3 = v0 & 0xFFFF;
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x1660FCu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                            s2 = v0;
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x166110u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                            s1 = v0 & 0xFF;
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x166124u, gen::fn_sub_16F900_0016f900);  // (owner, index)
                            s6 = v0 & 0xFF;
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x166138u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                            s7 = v0 & 0xFFFF;
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x16614Cu, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                            fp = v0 & 0xFFFF;
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x166160u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                            sh(v0, sp, 0xD0);
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x166174u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                            sh(v0, sp, 0xC0);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x166188u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x16619Cu, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x1661ACu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x1661C0u, gen::fn_sub_16FF90_0016ff90);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x1661D0u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x1661E4u, gen::fn_sub_170080_00170080);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x1661F4u, gen::fn_sub_16F900_0016f900);  // (owner, index)
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x166208u, gen::fn_sub_170170_00170170);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x166218u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x16622Cu, gen::fn_sub_170350_00170350);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x16623Cu, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x166250u, gen::fn_sub_170440_00170440);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x166260u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x166274u, gen::fn_sub_170530_00170530);
                            a0 = 1;
                            a1 = s4;
                            jal(ctx, 0x166284u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                            lh(a0, s0, pty::kPc);
                            a1 = s5;
                            a2 = v0;
                            jal(ctx, 0x166298u, gen::fn_sub_170260_00170260);
                            a0 = 1;
                            a1 = s4;
                            a2 = s3;
                            jal(ctx, 0x1662ACu, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                            a0 = 1;
                            a1 = s4;
                            a2 = s2;
                            jal(ctx, 0x1662C0u, gen::fn_sub_16FF90_0016ff90);
                            a0 = 1;
                            a1 = s4;
                            a2 = s1;
                            jal(ctx, 0x1662D4u, gen::fn_sub_170080_00170080);
                            a0 = 1;
                            a1 = s4;
                            a2 = s6;
                            jal(ctx, 0x1662E8u, gen::fn_sub_170170_00170170);
                            a0 = 1;
                            a1 = s4;
                            a2 = fp;
                            jal(ctx, 0x1662FCu, gen::fn_sub_170350_00170350);
                            a0 = 1;
                            a1 = s4;
                            lhu(a2, sp, 0xD0);
                            jal(ctx, 0x166310u, gen::fn_sub_170440_00170440);
                            a0 = 1;
                            a1 = s4;
                            lhu(a2, sp, 0xC0);
                            jal(ctx, 0x166324u, gen::fn_sub_170530_00170530);
                            a0 = 1;
                            a1 = s4;
                            a2 = s7;
                            jal(ctx, 0x166338u, gen::fn_sub_170260_00170260);
                            lw(a0, s0, pty::kPc);
                            a1 = s5;
                            jal(ctx, 0x166348u, gen::fn_sub_177C10_00177c10);
                        }
                        // 0x00166350
                        charge(ctx, 4);
                        v0 = 12;
                        sw(v0, s0, pty::kState);
                    }
                } else {
                    // 0x00166040
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x166050u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 12;
                    sw(v0, s0, pty::kState);
                }
            }
            goto L_0016696c;
        case 0x166384u:  // table[12]: state 12: back (flash 1)
            // 0x00166384
            charge(ctx, 11);
            lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
            a1 = 2;
            jal(ctx, 0x16638Cu, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
            lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
            a1 = 1;
            jal(ctx, 0x16639Cu, gen::fn_sub_1685E0_001685e0);  // [H_Camp_FrStatusFlashRequest]
            s1 = 0;
            for (;;) {
                // 0x001663fc
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001663b0
                charge(ctx, 8);
                lw(v1, s0, pty::kListTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x001663d0
                    charge(ctx, 4);
                    jal(ctx, 0x1663D0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x001663e0
                        charge(ctx, 6);
                        lw(v0, s0, pty::kListTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x1663F0u, gen::fn_sub_163330_00163330);  // the party equipment list's element draw
                    }
                }
                // 0x001663f8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00166408
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0016649c
                charge(ctx, 3);
                v0 = slti(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00166414
                charge(ctx, 34);
                v0 = 0x41700000;  // 15.0f
                sw(v0, sp, 0x248);
                v0 = sll(s1, 3);
                v0 = addu(v0, s1);
                v0 = sll(v0, 2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x423C0000;  // 47.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x24C);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 2);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, pty::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x248);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x166490u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x001664a8
            charge(ctx, 230);
            v0 = 0x43C80000;  // 400.0f
            sw(v0, sp, 0x248);
            sw(zero, sp, 0x24C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x248);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1664ECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, pty::kTweens);
            lwc1(f1, a0, 48);
            lwc1(f0, a0, 52);
            swc1(f1, sp, 0x228);
            swc1(f0, sp, 0x22C);
            ld(v0, sp, 0x228);
            sd(v0, sp, 0x240);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x228);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x166540u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B30000;  // 358.0f
            sw(v0, sp, 0x240);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x166590u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x240);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1665E8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x240);
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, pty::kListTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x166634u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 419;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x240);
            v0 = 0x42140000;  // 37.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x166690u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x240);
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1666DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42EA0000;  // 117.0f
            sw(v0, sp, 0x240);
            v0 = 0x42D80000;  // 108.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x16672Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43F20000;  // 484.0f
            sw(v0, sp, 0x240);
            v0 = 0x43B60000;  // 364.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x16677Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43360000;  // 182.0f
            sw(v0, sp, 0x240);
            v0 = 0x43720000;  // 242.0f
            sw(v0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1667CCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41E00000;  // 28.0f
            sw(v0, sp, 0x240);
            v0 = 421;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x244);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, pty::kListTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x240);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x166828u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 13;
            sw(v0, s0, pty::kState);
            goto L_0016696c;
        case 0x166840u:  // table[13]: state 13: free the list, input again
            // 0x00166840
            charge(ctx, 4);
            s2 = 1;
            s3 = 0;
            for (;;) {
                // 0x001668c4
                charge(ctx, 3);
                v0 = slti(s3, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00166850
                charge(ctx, 8);
                lw(v1, s0, pty::kListTweens);
                v0 = sll(s3, 4);
                v0 = addu(v0, s3);
                s1 = sll(v0, 2);
                a0 = addu(v1, s1);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00166870
                    charge(ctx, 4);
                    jal(ctx, 0x166870u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00166880
                        charge(ctx, 6);
                        lw(v0, s0, pty::kListTweens);
                        a0 = addu(v0, s1);
                        a1 = s3;
                        a2 = s0;
                        jal(ctx, 0x166890u, gen::fn_sub_163330_00163330);  // the party equipment list's element draw
                    }
                    // 0x00166898
                    charge(ctx, 9);
                    lw(v1, s0, pty::kListTweens);
                    v0 = sll(s3, 4);
                    v0 = addu(v0, s3);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x001668bc
                        charge(ctx, 1);
                        s2 = 0;
                    }
                }
                // 0x001668c0
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x001668d0
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x001668d8
                charge(ctx, 12);
                v1 = 1;
                lw(v0, s4, 76);
                lw(v0, v0, 60);
                sw(v1, v0, 44);
                lw(a0, s0, pty::kList);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x1668F4u, v0.u());
                sw(zero, s0, pty::kList);
                v0 = 3;
                sw(v0, s0, pty::kState);
            }
            // 0x00166908
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00166960
                charge(ctx, 3);
                v0 = slti(s1, 10);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00166914
                charge(ctx, 8);
                lw(v1, s0, pty::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00166934
                    charge(ctx, 4);
                    jal(ctx, 0x166934u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00166944
                        charge(ctx, 6);
                        lw(v0, s0, pty::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x166954u, gen::fn_sub_161D90_00161d90);  // the party page's element draw
                    }
                }
                // 0x0016695c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            goto L_0016696c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00166970 (the shared epilogue, written out on this path)
        charge(ctx, 13);
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
        sp = addiu(sp, 0x260);
        return;
    }
    goto L_0016696c;
}

// 0x00166C70 sub_166C70 -- 2356 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdatePartyStatusRootTask] Update of "H_CampPartyStatusRoot" (the party-status screen opened on the whole
// party; jump table 0x7B62A0): 0 lists the members present (flags 322..330 -> ids 2..) into +36 (+56 count); 1 waits
// for the flash; 2 / 3 switch between members and pages (sub_166A50 / sub_167F40 into +20); 5 / 6 wait for the page
// task, destroy the side portraits and recreate them. Draws the frame sprite of camp file 11 (twice).
void sub_166C70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00166c70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 7);
    if (at != 0) {
        // 0x00166ca8
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25248);  // &0x7B62A0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x166CC4u:  // table[0]: state 0: list the members present (flags 322..)
            // 0x00166cc4
            charge(ctx, 8);
            v0 = 0x43A00000;  // 320.0f
            sw(v0, s0, 64);
            sw(zero, s0, 68);
            a0 = 322;
            jal(ctx, 0x166CD4u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166ce4
                charge(ctx, 8);
                v1 = 2;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166d04
            charge(ctx, 5);
            a0 = 323;
            jal(ctx, 0x166D08u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166d18
                charge(ctx, 8);
                v1 = 3;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166d38
            charge(ctx, 5);
            a0 = 324;
            jal(ctx, 0x166D3Cu, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166d4c
                charge(ctx, 8);
                v1 = 4;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166d6c
            charge(ctx, 5);
            a0 = 325;
            jal(ctx, 0x166D70u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166d80
                charge(ctx, 8);
                v1 = 5;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166da0
            charge(ctx, 5);
            a0 = 326;
            jal(ctx, 0x166DA4u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166db4
                charge(ctx, 8);
                v1 = 7;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166dd4
            charge(ctx, 5);
            a0 = 327;
            jal(ctx, 0x166DD8u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166de8
                charge(ctx, 8);
                v1 = 8;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166e08
            charge(ctx, 5);
            a0 = 328;
            jal(ctx, 0x166E0Cu, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166e1c
                charge(ctx, 8);
                v1 = 9;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166e3c
            charge(ctx, 5);
            a0 = 329;
            jal(ctx, 0x166E40u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166e50
                charge(ctx, 8);
                v1 = 10;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166e70
            charge(ctx, 5);
            a0 = 330;
            jal(ctx, 0x166E74u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                // 0x00166e84
                charge(ctx, 8);
                v1 = 6;
                lh(v0, s0, 56);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                sh(v1, v0, 36);
                lh(v0, s0, 56);
                v0 = addiu(v0, 1);
                sh(v0, s0, 56);
            }
            // 0x00166ea4
            charge(ctx, 15);
            lh(v0, s0, 58);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lh(s2, v0, 36);
            s4 = 0x960000;
            s4 = addiu(s4, rw::kCallocSlot);  // &0x960184: RwCalloc
            a0 = 1;
            a1 = 24;
            a2 = 0x40000;
            lw(v0, s4, 0);  // 0x960184
            jalr(ctx, 0x166ECCu, v0.u());
            s3 = v0;
            if (s3 != 0) {
                // 0x00166eec
                charge(ctx, 13);
                a0 = s1;
                a1 = 0x5E0000;
                a1 = addiu(a1, -20528);  // "h_camp_pc_kani_control"
                a2 = 6337;
                a3 = 0x120000;
                a3 = addiu(a3, 8176);  // &sub_121FF0
                t0 = 0x120000;
                t0 = addiu(t0, 9776);  // &sub_122630
                t1 = s3;
                jal(ctx, 0x166F10u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                if (v0 != 0) {
                    // 0x00166f2c
                    charge(ctx, 2);
                    sw(zero, s3, 12);
                    sh(s2, s3, 20);
                } else {
                    // 0x00166f20
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x00166ee0
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00166f34
            charge(ctx, 18);
            sw(v0, gp, g::kCampPcKani);  // 0x7CDF54
            lh(v0, s0, 58);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lh(s3, v0, 36);
            a0 = s3 & 0xFFFF;
            jal(ctx, 0x166F4Cu, gen::fn_datPersonaGetByPcId_00174800);
            s2 = v0;
            a0 = 1;
            a1 = 28;
            a2 = 0x40000;
            lw(v0, s4, 0);
            jalr(ctx, 0x166F68u, v0.u());
            s4 = v0;
            if (s4 != 0) {
                // 0x00166f88
                charge(ctx, 13);
                a0 = s1;
                a1 = 0x5E0000;
                a1 = addiu(a1, -20496);  // "h_camp_persona_kani_control"
                a2 = 6337;
                a3 = 0x120000;
                a3 = addiu(a3, 10560);  // &sub_122940
                t0 = 0x120000;
                t0 = addiu(t0, 12240);  // &sub_122FD0
                t1 = s4;
                jal(ctx, 0x166FACu, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                if (v0 != 0) {
                    // 0x00166fc8
                    charge(ctx, 3);
                    sw(zero, s4, 12);
                    sw(s2, s4, 16);
                    sh(s3, s4, 24);
                } else {
                    // 0x00166fbc
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x00166f7c
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x00166fd4
            charge(ctx, 17);
            sw(v0, gp, g::kCampPersonaKani);  // 0x7CDF58
            sw(zero, s0, 4);
            lh(v0, s0, 58);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            a0 = s1;
            a1 = 6334;
            lh(a2, v0, 36);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x166FFCu, gen::fn_sub_166A50_00166a50);  // [H_Camp_CreatePartyStatusDrawTask]
            sw(v0, s0, 20);
            v0 = 1;
            sw(v0, s0, 0);
        L_0016746c:
            charge(ctx, 3);
            lw(v0, s0, 60);
            if (v0 != 0) {
                // 0x00167478
                charge(ctx, 6);
                lw(v0, s0, 16);
                v0 = addiu(v0, 1);
                sw(v0, s0, 16);
                v0 = slti(v0, 10);
                if (v0 == 0) {
                    // 0x00167490
                    charge(ctx, 2);
                    v0 = 10;
                    sw(v0, s0, 16);
                }
                // 0x00167498
                charge(ctx, 25);
                lw(v1, s0, 16);
                v0 = sll(v1, 8);
                v1 = subu(v0, v1);
                v0 = 10;
                div(v1, v0);
                mflo(v1);
                v0 = 255;
                s1 = subu(v0, v1);
                a3 = s1 & 0xFF;
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f14);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(11));  // 0x833B9C: camp sprite file 11
                a2 = 0;
                lwc1(f12, s0, 64);
                lwc1(f13, s0, 68);
                jal(ctx, 0x1674DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s0, 64);
                mtc1(zero, f0);
                c_lt_s(f1, f0);
                if (cond(ctx)) {
                    // 0x001674fc
                    charge(ctx, 14);
                    v0 = 0x44200000;  // 640.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    a3 = s1 & 0xFF;
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f14);
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(11));  // 0x833B9C: camp sprite file 11
                    a2 = 0;
                    lwc1(f13, s0, 68);
                    jal(ctx, 0x16752Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
                // 0x00167534
                charge(ctx, 12);
                lwc1(f1, s0, 64);
                v0 = 0x3F800000;  // 1.0f
                mtc1(v0, f0);
                sub_s(f1, f1, f0);
                swc1(f1, s0, 64);
                v0 = lui(0xC420);
                mtc1(v0, f0);
                c_lt_s(f1, f0);
                if (cond(ctx)) {
                    // 0x00167564
                    charge(ctx, 5);
                    v0 = 0x44200000;  // 640.0f
                    mtc1(v0, f0);
                    add_s(f0, f1, f0);
                    swc1(f0, s0, 64);
                }
            }
            // 0x00167578
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x167018u:  // table[1]: state 1: wait for the flash
            // 0x00167018
            charge(ctx, 5);
            lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
            jal(ctx, 0x16701Cu, gen::fn_sub_1685D0_001685d0);
            if (v0 != 0) {
                // 0x0016702c
                charge(ctx, 7);
                v0 = 1;
                sw(v0, s0, 60);
                sw(zero, s0, 16);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_0016746c;
        case 0x167048u:  // table[2]: state 2: page answer
            // 0x00167048
            charge(ctx, 3);
            lw(v0, s0, 4);
            if (v0 != 0) {
                // 0x00167084
                charge(ctx, 4);
                lw(a0, s0, 20);
                jal(ctx, 0x167088u, gen::fn_sub_167F30_00167f30);
                s1 = v0;
            } else {
                // 0x00167054
                charge(ctx, 6);
                lw(v0, s0, 20);
                lw(a0, v0, 60);
                lw(v1, a0, 0);
                v0 = 8;
                if (v1 != v0) {
                    // 0x00167078
                    charge(ctx, 1);
                    s1 = 0;
                } else {
                    // 0x0016706c
                    charge(ctx, 3);
                    lw(s1, a0, 12);
                }
                // 0x0016707c
                charge(ctx, 2);
            }
            // 0x00167094
            charge(ctx, 3);
            v0 = si(-1);
            if (s1 != v0) {
                // 0x00167108
                charge(ctx, 3);
                v1 = 1;
                if (s1 != v1) {
                    // 0x00167124
                    charge(ctx, 4);
                    v0 = addiu(s1, -2);
                    at = sltiu(v0, 2);
                    if (at != 0) {
                        // 0x00167134
                        charge(ctx, 3);
                        lw(v0, s0, 4);
                        if (v0 == v1) {
                            // 0x00167168
                            charge(ctx, 3);
                            lw(a0, s0, 20);
                            jal(ctx, 0x16716Cu, gen::fn_sub_167EF0_00167ef0);
                        } else {
                            // 0x00167140
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x00167150
                                charge(ctx, 6);
                                v1 = 6;
                                lw(v0, s0, 20);
                                lw(v0, v0, 60);
                                sw(v1, v0, 0);
                            } else {
                                // 0x00167148
                                charge(ctx, 2);
                            }
                        }
                        // 0x00167174
                        charge(ctx, 3);
                        v0 = 2;
                        if (s1 != v0) {
                            // 0x001671b0
                            charge(ctx, 7);
                            lh(v0, s0, 58);
                            v0 = addiu(v0, -1);
                            sh(v0, s0, 58);
                            v0 = dsll32(v0, 16);
                            v0 = dsra32(v0, 16);
                            if (i64(v0) < 0) {
                                // 0x001671cc
                                charge(ctx, 3);
                                lh(v0, s0, 56);
                                v0 = addiu(v0, -1);
                                sh(v0, s0, 58);
                            }
                        } else {
                            // 0x00167180
                            charge(ctx, 9);
                            lh(v0, s0, 58);
                            v0 = addiu(v0, 1);
                            sh(v0, s0, 58);
                            v1 = dsll32(v0, 16);
                            v1 = dsra32(v1, 16);
                            lh(v0, s0, 56);
                            v0 = slt(v1, v0);
                            if (v0 == 0) {
                                // 0x001671a4
                                charge(ctx, 3);
                                sh(zero, s0, 58);
                            }
                        }
                        // 0x001671d8
                        charge(ctx, 4);
                        v0 = 6;
                        sw(v0, s0, 0);
                    }
                } else {
                    // 0x00167114
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001670a0
                charge(ctx, 4);
                lw(v1, s0, 4);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001670d8
                    charge(ctx, 3);
                    lw(a0, s0, 20);
                    jal(ctx, 0x1670DCu, gen::fn_sub_167EF0_00167ef0);
                } else {
                    // 0x001670b0
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x001670c0
                        charge(ctx, 6);
                        v1 = 4;
                        lw(v0, s0, 20);
                        lw(v0, v0, 60);
                        sw(v1, v0, 0);
                    } else {
                        // 0x001670b8
                        charge(ctx, 2);
                    }
                }
                // 0x001670e4
                charge(ctx, 9);
                lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
                a1 = 3;
                jal(ctx, 0x1670ECu, gen::fn_sub_1685E0_001685e0);  // [H_Camp_FrStatusFlashRequest]
                sw(zero, s0, 60);
                v0 = 5;
                sw(v0, s0, 0);
            }
            goto L_0016746c;
        case 0x1671E8u:  // table[3]: state 3: next page / member
            // 0x001671e8
            charge(ctx, 4);
            lw(v0, s0, 4);
            t1 = 1;
            if (v0 == t1) {
                // 0x00167258
                charge(ctx, 15);
                lw(a0, s0, 20);
                jal(ctx, 0x16725Cu, gen::fn_sub_167F10_00167f10);
                sw(zero, s0, 4);
                lh(v0, s0, 58);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                a0 = s1;
                a1 = 6334;
                lh(a2, v0, 36);
                a3 = 1;
                t0 = a3;
                jal(ctx, 0x167288u, gen::fn_sub_166A50_00166a50);  // [H_Camp_CreatePartyStatusDrawTask]
                sw(v0, s0, 20);
            } else {
                // 0x001671f8
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x00167208
                    charge(ctx, 20);
                    v1 = 6;
                    lw(v0, s0, 20);
                    lw(v0, v0, 60);
                    sw(v1, v0, 0);
                    mtc1(zero, f12);
                    sw(zero, sp, 0x78);
                    sw(zero, sp, 0x7C);
                    sw(t1, s0, 4);
                    lh(v0, s0, 58);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, s0);
                    a1 = 6334;
                    ld(a2, sp, 0x78);
                    lh(a3, v0, 36);
                    t0 = 0;
                    jal(ctx, 0x167244u, gen::fn_sub_167F40_00167f40);  // [H_Camp_CreateFrStatusPersonaDrawTask]
                    sw(v0, s0, 20);
                } else {
                    // 0x00167200
                    charge(ctx, 2);
                }
            }
            // 0x00167294
            charge(ctx, 4);
            v0 = 2;
            sw(v0, s0, 0);
            goto L_0016746c;
        case 0x1672A4u:  // table[5]: state 5: wait for the page task
            // 0x001672a4
            charge(ctx, 6);
            lw(a0, s0, 20);
            jal(ctx, 0x1672A8u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 != v1) {
                goto L_0016746c;
            }
            // 0x001672bc
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x1672C8u:  // table[6]: state 6: recreate the portraits
            // 0x001672c8
            charge(ctx, 6);
            lw(a0, s0, 20);
            jal(ctx, 0x1672CCu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x001672e0
                charge(ctx, 21);
                lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
                jal(ctx, 0x1672E4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
                jal(ctx, 0x1672F0u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                lh(v0, s0, 58);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                lh(s2, v0, 36);
                s4 = 0x960000;
                s4 = addiu(s4, rw::kCallocSlot);  // &0x960184: RwCalloc
                a0 = 1;
                a1 = 24;
                a2 = 0x40000;
                lw(v0, s4, 0);  // 0x960184
                jalr(ctx, 0x167320u, v0.u());
                s3 = v0;
                if (s3 != 0) {
                    // 0x00167340
                    charge(ctx, 13);
                    a0 = s1;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20528);  // "h_camp_pc_kani_control"
                    a2 = 6337;
                    a3 = 0x120000;
                    a3 = addiu(a3, 8176);  // &sub_121FF0
                    t0 = 0x120000;
                    t0 = addiu(t0, 9776);  // &sub_122630
                    t1 = s3;
                    jal(ctx, 0x167364u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                    if (v0 != 0) {
                        // 0x00167380
                        charge(ctx, 2);
                        sw(zero, s3, 12);
                        sh(s2, s3, 20);
                    } else {
                        // 0x00167374
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x00167334
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x00167388
                charge(ctx, 18);
                sw(v0, gp, g::kCampPcKani);  // 0x7CDF54
                lh(v0, s0, 58);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                lh(s3, v0, 36);
                a0 = s3 & 0xFFFF;
                jal(ctx, 0x1673A0u, gen::fn_datPersonaGetByPcId_00174800);
                s2 = v0;
                a0 = 1;
                a1 = 28;
                a2 = 0x40000;
                lw(v0, s4, 0);
                jalr(ctx, 0x1673BCu, v0.u());
                s4 = v0;
                if (s4 != 0) {
                    // 0x001673dc
                    charge(ctx, 13);
                    a0 = s1;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20496);  // "h_camp_persona_kani_control"
                    a2 = 6337;
                    a3 = 0x120000;
                    a3 = addiu(a3, 10560);  // &sub_122940
                    t0 = 0x120000;
                    t0 = addiu(t0, 12240);  // &sub_122FD0
                    t1 = s4;
                    jal(ctx, 0x167400u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                    if (v0 != 0) {
                        // 0x0016741c
                        charge(ctx, 3);
                        sw(zero, s4, 12);
                        sw(s2, s4, 16);
                        sh(s3, s4, 24);
                    } else {
                        // 0x00167410
                        charge(ctx, 3);
                        v0 = 0;
                    }
                } else {
                    // 0x001673d0
                    charge(ctx, 3);
                    v0 = 0;
                }
                // 0x00167428
                charge(ctx, 17);
                sw(v0, gp, g::kCampPersonaKani);  // 0x7CDF58
                sw(zero, s0, 4);
                lh(v0, s0, 58);
                v0 = sll(v0, 1);
                v0 = addu(v0, s0);
                a0 = s1;
                a1 = 6334;
                lh(a2, v0, 36);
                a3 = 1;
                t0 = a3;
                jal(ctx, 0x167450u, gen::fn_sub_166A50_00166a50);  // [H_Camp_CreatePartyStatusDrawTask]
                sw(v0, s0, 20);
                v0 = 30;
                sw(v0, s0, 8);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_0016746c;
        case 0x16746Cu:  // table[4]
            goto L_0016746c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0016757c (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
    goto L_0016746c;
}

// 0x00168810 sub_168810 -- 2096 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateTradeSubTask] Update of the equipment trade sub-task (jump table 0x7B6300): 0 takes the pak's two
// sprite files (+20 / +24, also 0x833A50 / 0x833A54) and starts a camp sprite set-up (sub_119F10(task, 1)); then the
// trade list (sub_13CF80 / sub_169110 draws) with H_Camp_MoveListCursor; confirm moves the selected equipment between
// the stock and the member (the 0x16F630..0x170530 setters, sub_177C10), a full stock shows a message.
void sub_168810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00168810
    enter(ctx, 17);  // entry check point + this block's cycles
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
    s1 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 8);
    if (at != 0) {
        // 0x00168854
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25344);  // &0x7B6300
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x168870u:  // table[0]: state 0: the pak's sprite files, camp sprite set-up
            // 0x00168870
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x168874u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00168884
                charge(ctx, 33);
                lw(a0, s0, 16);
                a1 = 0;
                a2 = addiu(sp, 0xCC);
                jal(ctx, 0x168890u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x16889Cu, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, 20);
                lw(a0, s0, 16);
                a1 = 1;
                a2 = addiu(sp, 0xCC);
                jal(ctx, 0x1688B4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x1688C0u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, 24);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x1688D4u, gen::fn_sub_119F10_00119f10);  // [H_Camp_CreateCampSprSetupFileTask]
                sw(v0, s0, 36);
                lw(v1, s0, 20);
                v0 = 0x830000;
                sw(v1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                lw(v1, s0, 24);
                v0 = 0x830000;
                sw(v1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                v0 = 1;
                sw(v0, s0, 0);
            }
        L_00169008:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x168908u:  // table[1]: state 1: wait for them, the lists
            // 0x00168908
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00168944
                charge(ctx, 3);
                v0 = slti(s2, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00168918
                charge(ctx, 5);
                v0 = sll(s2, 2);
                v0 = addu(s0, v0);
                lw(a0, v0, 20);
                if (a0 != 0) {
                    // 0x0016892c
                    charge(ctx, 4);
                    jal(ctx, 0x16892Cu, gen::fn_sprFileIsReady_00111f30);
                    if (v0 == 0) {
                        // 0x0016893c
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00168940
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00168950
            charge(ctx, 3);
            lw(v0, gp, g::kCampSetupTask);  // 0x7CDF48
            if (v0 != 0) {
                // 0x00168968
                charge(ctx, 5);
                lw(v0, v0, 60);
                lw(v1, v0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x00168988
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x0016897c
                    charge(ctx, 3);
                    v0 = 1;
                }
            } else {
                // 0x0016895c
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x0016898c
            charge(ctx, 3);
            a0 = 1;
            if (v0 == a0) {
                // 0x00168998
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x001689a0
                    charge(ctx, 12);
                    sw(zero, s0, 8);
                    s1 = 0x960000;
                    s1 = addiu(s1, rw::kCallocSlot);  // &0x960184: RwCalloc
                    a1 = 11632;
                    a2 = 0x40000;
                    lw(v0, s1, 0);  // 0x960184
                    jalr(ctx, 0x1689B8u, v0.u());
                    a1 = 0;
                    a0 = si(-1);
                    for (;;) {
                        // 0x001689f4
                        charge(ctx, 3);
                        v1 = slti(a1, 320);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001689d0
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
                    // 0x00168a00
                    charge(ctx, 11);
                    sw(v0, s0, 28);
                    a0 = 1;
                    a1 = 11632;
                    a2 = 0x40000;
                    lw(v0, s1, 0);
                    jalr(ctx, 0x168A14u, v0.u());
                    a1 = 0;
                    a0 = si(-1);
                    for (;;) {
                        // 0x00168a50
                        charge(ctx, 3);
                        v1 = slti(a1, 320);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00168a2c
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
                    // 0x00168a5c
                    charge(ctx, 9);
                    sw(v0, s0, 32);
                    lw(a0, s0, 12);
                    lw(a1, s0, 28);
                    jal(ctx, 0x168A68u, gen::fn_sub_13CF80_0013cf80);  // a member's list by slot
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            }
            goto L_00169008;
        case 0x168A80u:  // table[2]: state 2
            // 0x00168a80
            charge(ctx, 6);
            lw(v0, s0, 8);
            v0 = addiu(v0, 1);
            sw(v0, s0, 8);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x00168a98
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s0, 0);
            }
            // 0x00168aa0
            charge(ctx, 17);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            a3 = subu(v0, v1);
            sw(zero, sp, 0xC4);
            sw(zero, sp, 0xC0);
            lh(a0, s0, 12);
            ld(a1, sp, 0xC0);
            lw(a2, s0, 28);
            jal(ctx, 0x168AD4u, gen::fn_sub_169110_00169110);
            goto L_00169008;
        case 0x168AE4u:  // table[3]: state 3: the member list (input)
            // 0x00168ae4
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
            v0 = v1 & 0x20;  // cancel
            if (v0 == 0) {
                // 0x00168b20
                charge(ctx, 3);
                v0 = v1 & 0x40;
                if (v0 == 0) {
                    // 0x00168b98
                    charge(ctx, 7);
                    lw(v0, s0, 28);
                    lw(a0, v0, 11620);
                    a1 = 5;
                    a2 = addiu(v0, 11628);
                    a3 = addiu(v0, 11624);
                    jal(ctx, 0x168BACu, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                } else {
                    // 0x00168b2c
                    charge(ctx, 16);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x168B3Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    lh(a1, s0, 12);
                    lw(v0, s0, 28);
                    lh(a2, v0, 11624);
                    lw(a0, s0, 32);
                    jal(ctx, 0x168B54u, gen::fn_sub_13C240_0013c240);  // a member slot's candidate list
                    lw(v0, s0, 32);
                    lw(v0, v0, 11620);
                    if (v0 == 0) {
                        // 0x00168b7c
                        charge(ctx, 7);
                        a0 = 4;
                        jal(ctx, 0x168B80u, gen::fn_msgWinRequestMessage_003c7430);
                        v0 = 5;
                        sw(v0, s0, 0);
                    } else {
                        // 0x00168b6c
                        charge(ctx, 4);
                        v0 = 4;
                        sw(v0, s0, 0);
                    }
                }
            } else {
                // 0x00168af8
                charge(ctx, 10);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x168B08u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                v0 = 6;
                sw(v0, s0, 0);
            }
            // 0x00168bb4
            charge(ctx, 10);
            sw(zero, sp, 0xC4);
            sw(zero, sp, 0xC0);
            lh(a0, s0, 12);
            ld(a1, sp, 0xC0);
            lw(a2, s0, 28);
            a3 = 0;
            jal(ctx, 0x168BCCu, gen::fn_sub_169110_00169110);
            goto L_00169008;
        case 0x168BDCu:  // table[4]: state 4: the equipment list (input; move the item)
            // 0x00168bdc
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
            v0 = v1 & 0x20;  // cancel
            if (v0 == 0) {
                // 0x00168c18
                charge(ctx, 3);
                v0 = v1 & 0x40;
                if (v0 == 0) {
                    // 0x00168f0c
                    charge(ctx, 7);
                    lw(v0, s0, 32);
                    lw(a0, v0, 11620);
                    a1 = 5;
                    a2 = addiu(v0, 11628);
                    a3 = addiu(v0, 11624);
                    jal(ctx, 0x168F20u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                } else {
                    // 0x00168c24
                    charge(ctx, 186);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x168C34u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    lw(a0, s0, 28);
                    lw(v1, a0, 11624);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, a0);
                    lw(s5, v0, 104);
                    lw(a0, s0, 32);
                    lw(v1, a0, 11628);
                    lw(v0, a0, 11624);
                    v1 = addu(v1, v0);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, a0);
                    lw(s4, v0, 104);
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168C84u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                    s3 = v0 & 0xFFFF;
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168C98u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                    s2 = v0;
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168CACu, gen::fn_sub_16F810_0016f810);  // (owner, index)
                    s1 = v0 & 0xFF;
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168CC0u, gen::fn_sub_16F900_0016f900);  // (owner, index)
                    s6 = v0 & 0xFF;
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168CD4u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                    s7 = v0 & 0xFFFF;
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168CE8u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                    fp = v0 & 0xFFFF;
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168CFCu, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                    sh(v0, sp, 0xB0);
                    lh(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168D10u, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                    sh(v0, sp, 0xA0);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168D24u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168D38u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168D48u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168D5Cu, gen::fn_sub_16FF90_0016ff90);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168D6Cu, gen::fn_sub_16F810_0016f810);  // (owner, index)
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168D80u, gen::fn_sub_170080_00170080);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168D90u, gen::fn_sub_16F900_0016f900);  // (owner, index)
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168DA4u, gen::fn_sub_170170_00170170);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168DB4u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168DC8u, gen::fn_sub_170350_00170350);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168DD8u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168DECu, gen::fn_sub_170440_00170440);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168DFCu, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168E10u, gen::fn_sub_170530_00170530);
                    a0 = 1;
                    a1 = s4;
                    jal(ctx, 0x168E20u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                    lh(a0, s0, 12);
                    a1 = s5;
                    a2 = v0;
                    jal(ctx, 0x168E34u, gen::fn_sub_170260_00170260);
                    a0 = 1;
                    a1 = s4;
                    a2 = s3;
                    jal(ctx, 0x168E48u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                    a0 = 1;
                    a1 = s4;
                    a2 = s2;
                    jal(ctx, 0x168E5Cu, gen::fn_sub_16FF90_0016ff90);
                    a0 = 1;
                    a1 = s4;
                    a2 = s1;
                    jal(ctx, 0x168E70u, gen::fn_sub_170080_00170080);
                    a0 = 1;
                    a1 = s4;
                    a2 = s6;
                    jal(ctx, 0x168E84u, gen::fn_sub_170170_00170170);
                    a0 = 1;
                    a1 = s4;
                    a2 = fp;
                    jal(ctx, 0x168E98u, gen::fn_sub_170350_00170350);
                    a0 = 1;
                    a1 = s4;
                    lhu(a2, sp, 0xB0);
                    jal(ctx, 0x168EACu, gen::fn_sub_170440_00170440);
                    a0 = 1;
                    a1 = s4;
                    lhu(a2, sp, 0xA0);
                    jal(ctx, 0x168EC0u, gen::fn_sub_170530_00170530);
                    a0 = 1;
                    a1 = s4;
                    a2 = s7;
                    jal(ctx, 0x168ED4u, gen::fn_sub_170260_00170260);
                    lw(a0, s0, 12);
                    a1 = s5;
                    jal(ctx, 0x168EE4u, gen::fn_sub_177C10_00177c10);
                    lw(a0, s0, 12);
                    lw(a1, s0, 28);
                    jal(ctx, 0x168EF4u, gen::fn_sub_13CF80_0013cf80);  // a member's list by slot
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x00168bf0
                charge(ctx, 10);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x168C00u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                v0 = 3;
                sw(v0, s0, 0);
            }
            // 0x00168f28
            charge(ctx, 11);
            sw(zero, sp, 0xC4);
            sw(zero, sp, 0xC0);
            lh(a0, s0, 12);
            ld(a1, sp, 0xC0);
            lw(a2, s0, 28);
            lw(a3, s0, 32);
            t0 = 0;
            jal(ctx, 0x168F44u, gen::fn_sub_1691F0_001691f0);
            goto L_00169008;
        case 0x168F54u:  // table[5]: state 5: wait for the message
            // 0x00168f54
            charge(ctx, 4);
            jal(ctx, 0x168F54u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x00168f64
                charge(ctx, 4);
                jal(ctx, 0x168F64u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 3;
                sw(v0, s0, 0);
            }
            // 0x00168f74
            charge(ctx, 10);
            sw(zero, sp, 0xC4);
            sw(zero, sp, 0xC0);
            lh(a0, s0, 12);
            ld(a1, sp, 0xC0);
            lw(a2, s0, 28);
            a3 = 0;
            jal(ctx, 0x168F8Cu, gen::fn_sub_169110_00169110);
            goto L_00169008;
        case 0x168F9Cu:  // table[6]: state 6
            // 0x00168f9c
            charge(ctx, 5);
            lw(v0, s0, 8);
            v0 = addiu(v0, -1);
            sw(v0, s0, 8);
            if (i64(v0) <= 0) {
                // 0x00168fb0
                charge(ctx, 2);
                v0 = 7;
                sw(v0, s0, 0);
            }
            // 0x00168fb8
            charge(ctx, 17);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            a3 = subu(v0, v1);
            sw(zero, sp, 0xC4);
            sw(zero, sp, 0xC0);
            lh(a0, s0, 12);
            ld(a1, sp, 0xC0);
            lw(a2, s0, 28);
            jal(ctx, 0x168FECu, gen::fn_sub_169110_00169110);
            goto L_00169008;
        case 0x168FFCu:  // table[7]: state 7: done (-1)
            // 0x00168ffc
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0016900c (the shared epilogue, written out on this path)
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
        sp = addiu(sp, 0xD0);
        return;
    }
    goto L_00169008;
}

// 0x00169110 sub_169110 -- 224 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_TradeDrawList] (?, xy, list, alpha): the trade list over a dimmed screen: sub_21EA00(41), a 640 x 448
// rectangle (sub_113A30), sub_21EA00(40), then the list (sub_13D1A0) at +40 / +50.
void sub_169110(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00169110
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    sd(a1, sp, 0x50);
    s2 = a2;
    s1 = a3;
    v0 = 255;
    s0 = subu(v0, s1);
    v0 = 0x42200000;  // 40.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x50);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x54);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x5C);
    s3 = 0x960000;
    s3 = addiu(s3, 136);  // &g_rwIm2DNearScreenZ
    a0 = 41;
    jal(ctx, 0x169170u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    v0 = 0x20800000;
    v0 = v0 | 0x8000;
    a0 = s0 | v0;
    mtc1(zero, f13);
    mov_s(f14, f13);
    a1 = 640;
    a2 = 448;
    jal(ctx, 0x1691A0u, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
    a0 = 40;
    jal(ctx, 0x1691ACu, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    ld(a0, sp, 0x58);
    a1 = s2;
    a2 = s1;
    jal(ctx, 0x1691C8u, gen::fn_sub_13D1A0_0013d1a0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001691F0 sub_1691F0 -- 320 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0, f20 sp+0x78, f20 sp+0x78
// [H_Camp_TradeDrawListDetail] (?, xy, detail, list, alpha): sub_169110 with the detail (sub_13FCA0) above the list
// (+80).
void sub_1691F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x001691f0
    enter(ctx, 80);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a1, sp, 0x70);
    s4 = a2;
    s3 = a3;
    s2 = t0;
    lwc1(f21, sp, 0x74);
    v0 = 255;
    s1 = subu(v0, s2);
    s0 = 0x960000;
    s0 = addiu(s0, 136);  // &g_rwIm2DNearScreenZ
    a0 = 41;
    jal(ctx, 0x16923Cu, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s0, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    v0 = 0x20800000;
    v0 = v0 | 0x8000;
    a0 = s1 | v0;
    mtc1(zero, f13);
    mov_s(f14, f13);
    a1 = 640;
    a2 = 448;
    jal(ctx, 0x16926Cu, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
    v0 = 0x42200000;  // 40.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x70);
    add_s(f20, f1, f0);
    swc1(f20, sp, 0x78);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x7C);
    a0 = 40;
    jal(ctx, 0x1692A0u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s0, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    ld(a0, sp, 0x78);
    a1 = s4;
    a2 = s2;
    jal(ctx, 0x1692BCu, gen::fn_sub_13FCA0_0013fca0);
    swc1(f20, sp, 0x78);
    v0 = 0x42A00000;  // 80.0f
    mtc1(v0, f0);
    add_s(f0, f0, f21);
    swc1(f0, sp, 0x7C);
    a0 = 40;
    jal(ctx, 0x1692E0u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s0, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    ld(a0, sp, 0x78);
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x1692FCu, gen::fn_sub_13D1A0_0013d1a0);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00169470 sub_169470 -- 1648 bytes; frame 0x80: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateTradeDrawTask] Update of "H_CampTradeDraw" (jump table 0x7B6320): 0 takes the pak's sprite files and
// its camp sprite set-up; 1 builds the trade list (sub_13C780) and the stock-over background
// (brItem_CreateStockOverBgTask); then the list (sub_169B90 draws, H_Camp_MoveListCursor): confirm asks (message) and
// moves the item (sub_16FEA0 and the stock setters), cancel ends.
void sub_169470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00169470
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(s1, a0, 60);
    lw(v0, s1, 0);
    at = sltiu(v0, 8);
    if (at != 0) {
        // 0x001694a0
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25376);  // &0x7B6320
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1694BCu:  // table[0]: state 0: the pak's sprite files, camp sprite set-up
            // 0x001694bc
            charge(ctx, 5);
            lw(a0, s1, 12);
            jal(ctx, 0x1694C0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x001694d0
                charge(ctx, 27);
                lw(a0, s1, 12);
                a1 = 0;
                a2 = addiu(sp, 0x7C);
                jal(ctx, 0x1694DCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x1694E8u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s1, 16);
                lw(a0, s1, 12);
                a1 = 1;
                a2 = addiu(sp, 0x7C);
                jal(ctx, 0x169500u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x16950Cu, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s1, 20);
                a0 = s3;
                a1 = 1;
                jal(ctx, 0x169520u, gen::fn_sub_119F10_00119f10);  // [H_Camp_CreateCampSprSetupFileTask]
                sw(v0, s1, 28);
                v0 = 1;
                sw(v0, s1, 0);
            }
        L_00169abc:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x16953Cu:  // table[1]: state 1: the trade list, the stock-over background
            // 0x0016953c
            charge(ctx, 4);
            s0 = 1;
            s2 = 0;
            for (;;) {
                // 0x00169578
                charge(ctx, 3);
                v0 = slti(s2, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0016954c
                charge(ctx, 5);
                v0 = sll(s2, 2);
                v0 = addu(s1, v0);
                lw(a0, v0, 16);
                if (a0 != 0) {
                    // 0x00169560
                    charge(ctx, 4);
                    jal(ctx, 0x169560u, gen::fn_sprFileIsReady_00111f30);
                    if (v0 == 0) {
                        // 0x00169570
                        charge(ctx, 1);
                        s0 = 0;
                    }
                }
                // 0x00169574
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00169584
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x0016958c
                charge(ctx, 12);
                sw(zero, s1, 8);
                a0 = 1;
                a1 = 11632;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1695A4u, v0.u());
                a1 = 0;
                a0 = si(-1);
                for (;;) {
                    // 0x001695e0
                    charge(ctx, 3);
                    v1 = slti(a1, 320);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001695bc
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
                // 0x001695ec
                charge(ctx, 13);
                sw(v0, s1, 24);
                a0 = v0;
                jal(ctx, 0x1695F4u, gen::fn_sub_13C780_0013c780);
                v0 = 2;
                sw(v0, s1, 0);
                a0 = s3;
                lw(a1, s1, 20);
                jal(ctx, 0x16960Cu, gen::fn_brItem_CreateStockOverBgTask_0025f370);
                sw(v0, s1, 32);
            }
            goto L_00169abc;
        case 0x169620u:  // table[2]: state 2
            // 0x00169620
            charge(ctx, 6);
            lw(v0, s1, 8);
            v0 = addiu(v0, 1);
            sw(v0, s1, 8);
            v0 = slti(v0, 20);
            if (v0 == 0) {
                // 0x00169638
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s1, 0);
            }
            // 0x00169640
            charge(ctx, 17);
            lw(v1, s1, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 20;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            a3 = subu(v0, v1);
            sw(zero, sp, 0x6C);
            sw(zero, sp, 0x68);
            a0 = addiu(s1, 16);
            ld(a1, sp, 0x68);
            lw(a2, s1, 24);
            jal(ctx, 0x169674u, gen::fn_sub_169B90_00169b90);
            goto L_00169abc;
        case 0x169684u:  // table[3]: state 3: the list (input; message 5)
            // 0x00169684
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
            v0 = v0 & 0x40;  // confirm
            if (v0 == 0) {
                // 0x0016972c
                charge(ctx, 19);
                lw(v0, s1, 24);
                lw(v0, v0, 11628);
                sw(v0, sp, 0x74);
                lw(v0, s1, 24);
                lw(v0, v0, 11624);
                sw(v0, sp, 0x78);
                lw(v0, s1, 24);
                lw(a0, v0, 11620);
                a1 = 6;
                a2 = addiu(sp, 0x74);
                a3 = addiu(sp, 0x78);
                jal(ctx, 0x169758u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                lw(v1, sp, 0x74);
                lw(v0, s1, 24);
                sw(v1, v0, 11628);
                lw(v1, sp, 0x78);
                lw(v0, s1, 24);
                sw(v1, v0, 11624);
            } else {
                // 0x00169698
                charge(ctx, 17);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 1;
                jal(ctx, 0x1696A8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                lw(a0, s1, 24);
                lw(v1, a0, 11628);
                lw(v0, a0, 11624);
                v1 = addu(v1, v0);
                v0 = sll(v1, 3);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                v0 = addu(v0, a0);
                lw(v0, v0, 116);
                if (v0 == 0) {
                    // 0x00169710
                    charge(ctx, 7);
                    a0 = 6;
                    jal(ctx, 0x169714u, gen::fn_msgWinRequestMessage_003c7430);
                    v0 = 5;
                    sw(v0, s1, 0);
                } else {
                    // 0x001696dc
                    charge(ctx, 13);
                    a0 = 5;
                    jal(ctx, 0x1696E0u, gen::fn_msgWinRequestMessage_003c7430);
                    a0 = 0;
                    jal(ctx, 0x1696ECu, gen::fn_sub_3C74E0_003c74e0);
                    a0 = 0;
                    jal(ctx, 0x1696F8u, gen::fn_msgWinSetType_003c7560);
                    v0 = 4;
                    sw(v0, s1, 0);
                }
            }
            // 0x00169778
            charge(ctx, 10);
            sw(zero, sp, 0x6C);
            sw(zero, sp, 0x68);
            a0 = addiu(s1, 16);
            ld(a1, sp, 0x68);
            lw(a2, s1, 24);
            a3 = 0;
            jal(ctx, 0x169790u, gen::fn_sub_169B90_00169b90);
            goto L_00169abc;
        case 0x1697A0u:  // table[4]: state 4: the answer (move the item)
            // 0x001697a0
            charge(ctx, 4);
            jal(ctx, 0x1697A0u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x001697b0
                charge(ctx, 5);
                jal(ctx, 0x1697B0u, gen::fn_msgWinLastSelection_003c7610);
                a0 = 1;
                if (v0 != a0) {
                    // 0x001697c4
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001697d4
                        charge(ctx, 12);
                        lw(a1, s1, 24);
                        lw(v1, a1, 11628);
                        lw(v0, a1, 11624);
                        v1 = addu(v1, v0);
                        v0 = sll(v1, 3);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, a1);
                        lw(a1, v0, 104);
                        v0 = slti(a1, 4096);
                        if (v0 != 0) {
                            // 0x00169820
                            charge(ctx, 3);
                            a2 = 0;
                            jal(ctx, 0x169824u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                        } else {
                            // 0x00169804
                            charge(ctx, 7);
                            a1 = addiu(a1, -4096);
                            a0 = si(-1);
                            a2 = 0;
                            jal(ctx, 0x169810u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                        }
                        // 0x0016982c
                        charge(ctx, 10);
                        lw(a0, s1, 24);
                        lw(s2, a0, 11628);
                        lw(s0, a0, 11624);
                        jal(ctx, 0x169838u, gen::fn_sub_13C780_0013c780);
                        lw(v1, s1, 24);
                        lw(v0, v1, 11620);
                        at = slti(v0, 6);
                        if (at == 0) {
                            // 0x00169888
                            charge(ctx, 4);
                            v0 = addiu(v0, -6);
                            at = slt(v0, s2);
                            if (at != 0) {
                                // 0x00169898
                                charge(ctx, 3);
                                sw(v0, v1, 11628);
                                lw(v0, s1, 24);
                                sw(s0, v0, 11624);
                            }
                        } else {
                            // 0x00169854
                            charge(ctx, 7);
                            sw(zero, v1, 11628);
                            lw(v1, s1, 24);
                            lw(v0, v1, 11620);
                            v0 = addiu(v0, -1);
                            at = slt(v0, s0);
                            if (at == 0) {
                                // 0x0016987c
                                charge(ctx, 3);
                                sw(s0, v1, 11624);
                            } else {
                                // 0x00169870
                                charge(ctx, 3);
                                sw(v0, v1, 11624);
                            }
                        }
                    } else {
                        // 0x001697cc
                        charge(ctx, 2);
                    }
                }
                // 0x001698a4
                charge(ctx, 7);
                jal(ctx, 0x1698A4u, gen::fn_sub_3C7700_003c7700);  // close the message window
                lw(v0, s1, 24);
                lw(v0, v0, 11620);
                at = slti(v0, 301);
                if (at == 0) {
                    // 0x001699d8
                    charge(ctx, 2);
                    v0 = 3;
                    sw(v0, s1, 0);
                } else {
                    // 0x001698c0
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x001699ac
                        charge(ctx, 3);
                        v0 = slti(s0, 20);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001698cc
                        charge(ctx, 7);
                        a0 = si(-1);
                        a1 = s0;
                        jal(ctx, 0x1698D4u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                        v0 = v0 & 0xFFFF;
                        if (v0 != 0) {
                            // 0x001698e8
                            charge(ctx, 48);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x1698F0u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                            sh(v0, sp, 0x50);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x169904u, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                            sw(v0, sp, 0x54);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x169918u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                            sb(v0, sp, 0x58);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x16992Cu, gen::fn_sub_16F900_0016f900);  // (owner, index)
                            sb(v0, sp, 0x59);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x169940u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                            sh(v0, sp, 0x5A);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x169954u, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                            sh(v0, sp, 0x5C);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x169968u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                            sh(v0, sp, 0x5E);
                            a0 = si(-1);
                            a1 = s0;
                            jal(ctx, 0x16997Cu, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                            sh(v0, sp, 0x60);
                            a0 = si(-1);
                            a1 = s0;
                            a2 = 0;
                            jal(ctx, 0x169994u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                            a0 = addiu(sp, 0x50);
                            jal(ctx, 0x1699A0u, gen::fn_sub_1830C0_001830c0);
                        }
                        // 0x001699a8
                        charge(ctx, 1);
                        s0 = addiu(s0, 1);
                    }
                    // 0x001699b8
                    charge(ctx, 8);
                    jal(ctx, 0x1699B8u, gen::fn_sub_25F570_0025f570);
                    v0 = 10;
                    sw(v0, s1, 8);
                    v0 = 6;
                    sw(v0, s1, 0);
                }
            }
            // 0x001699e0
            charge(ctx, 10);
            sw(zero, sp, 0x6C);
            sw(zero, sp, 0x68);
            a0 = addiu(s1, 16);
            ld(a1, sp, 0x68);
            lw(a2, s1, 24);
            a3 = 0;
            jal(ctx, 0x1699F8u, gen::fn_sub_169B90_00169b90);
            goto L_00169abc;
        case 0x169A08u:  // table[5]: state 5: wait for the message
            // 0x00169a08
            charge(ctx, 4);
            jal(ctx, 0x169A08u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x00169a18
                charge(ctx, 4);
                jal(ctx, 0x169A18u, gen::fn_sub_3C7700_003c7700);  // close the message window
                v0 = 3;
                sw(v0, s1, 0);
            }
            // 0x00169a28
            charge(ctx, 10);
            sw(zero, sp, 0x6C);
            sw(zero, sp, 0x68);
            a0 = addiu(s1, 16);
            ld(a1, sp, 0x68);
            lw(a2, s1, 24);
            a3 = 0;
            jal(ctx, 0x169A40u, gen::fn_sub_169B90_00169b90);
            goto L_00169abc;
        case 0x169A50u:  // table[6]: state 6
            // 0x00169a50
            charge(ctx, 5);
            lw(v0, s1, 8);
            v0 = addiu(v0, -1);
            sw(v0, s1, 8);
            if (i64(v0) <= 0) {
                // 0x00169a64
                charge(ctx, 2);
                v0 = 7;
                sw(v0, s1, 0);
            }
            // 0x00169a6c
            charge(ctx, 17);
            lw(v1, s1, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            a3 = subu(v0, v1);
            sw(zero, sp, 0x6C);
            sw(zero, sp, 0x68);
            a0 = addiu(s1, 16);
            ld(a1, sp, 0x68);
            lw(a2, s1, 24);
            jal(ctx, 0x169AA0u, gen::fn_sub_169B90_00169b90);
            goto L_00169abc;
        case 0x169AB0u:  // table[7]: state 7: done (-1)
            // 0x00169ab0
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00169ac0 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x80);
        return;
    }
    goto L_00169abc;
}

// 0x00169B90 sub_169B90 -- 1172 bytes; frame 0x90: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0, f20 sp+0x8C, f20 sp+0x8C
// [H_Camp_TradeDraw] (trade work, xy, list, alpha): the trade screen: the two lists (sub_16A700, sub_16AF90) and the
// frame sprites (49 ...) of the trade file, with sub_21EA00 render-state switches between them.
void sub_169B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00169b90
    enter(ctx, 126);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    sd(a1, sp, 0x80);
    s0 = a2;
    s1 = a3;
    lwc1(f20, sp, 0x84);
    lwc1(f0, sp, 0x80);
    swc1(f0, sp, 0x88);
    swc1(f20, sp, 0x8C);
    s3 = 0x960000;
    s3 = addiu(s3, 136);  // &g_rwIm2DNearScreenZ
    a0 = 40;
    jal(ctx, 0x169BE4u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    a0 = s2;
    ld(a1, sp, 0x88);
    a2 = s0;
    a3 = s1;
    jal(ctx, 0x169C04u, gen::fn_sub_16A700_0016a700);
    lwc1(f0, sp, 0x80);
    swc1(f0, sp, 0x88);
    swc1(f20, sp, 0x8C);
    a0 = 40;
    jal(ctx, 0x169C1Cu, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f12, f1, f0);
    a0 = s2;
    ld(a1, sp, 0x88);
    a2 = s0;
    a3 = s1;
    jal(ctx, 0x169C3Cu, gen::fn_sub_16AF90_0016af90);
    v0 = 0x41900000;  // 18.0f
    mtc1(v0, f0);
    add_s(f21, f0, f20);
    a0 = 40;
    jal(ctx, 0x169C58u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 0x43700000;  // 240.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 49;
    mov_s(f13, f21);
    jal(ctx, 0x169C8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = 40;
    jal(ctx, 0x169C98u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 0x43D00000;  // 416.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    a3 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 50;
    mov_s(f13, f21);
    jal(ctx, 0x169CCCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43EA0000;  // 468.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f21, f1, f0);
    a0 = 40;
    jal(ctx, 0x169CE8u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 0x43CC0000;  // 408.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a3 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 56;
    mov_s(f12, f21);
    jal(ctx, 0x169D1Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a0 = 40;
    jal(ctx, 0x169D28u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 0x43C10000;  // 386.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    v0 = 379;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f13, f0, f20);
    a3 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 51;
    jal(ctx, 0x169D6Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(s0, s0, 11620);
    s5 = 0;
    v0 = slti(s0, 100);
    if (v0 == 0) {
        // 0x00169d88
        charge(ctx, 26);
        s5 = 1;
        a0 = 40;
        jal(ctx, 0x169D90u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
        lwc1(f1, s3, 0);
        sub_s(f14, f1, f0);
        v0 = 100;
        div(s0, v0);
        mflo(v0);
        a2 = addiu(v0, 39);
        v0 = 0x43C00000;  // 384.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s1 & 0xFF;
        a0 = s4;
        lw(a1, s2, 4);
        mov_s(f12, f21);
        t0 = 98;
        t1 = 174;
        t2 = 255;
        jal(ctx, 0x169DDCu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
        v0 = 100;
        div(s0, v0);
        mfhi(s0);
    }
    // 0x00169df0
    charge(ctx, 2);
    if (s5 == 0) {
        // 0x00169df8
        charge(ctx, 3);
        v0 = slti(s0, 10);
        if (v0 == 0) {
            goto L_00169e04;
        }
        goto L_00169e70;
    }
L_00169e04:
    charge(ctx, 27);
    a0 = 40;
    jal(ctx, 0x169E08u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);
    sub_s(f14, f1, f0);
    v0 = 10;
    div(s0, v0);
    mflo(v0);
    a2 = addiu(v0, 39);
    v0 = 495;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    v0 = 0x43C00000;  // 384.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a3 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    t0 = 98;
    t1 = 174;
    t2 = 255;
    jal(ctx, 0x169E68u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
L_00169e70:
    charge(ctx, 109);
    s3 = 0x960000;
    s3 = addiu(s3, 136);  // &g_rwIm2DNearScreenZ
    a0 = 40;
    jal(ctx, 0x169E7Cu, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 10;
    div(s0, v0);
    mfhi(v0);
    a2 = addiu(v0, 39);
    v0 = 522;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    v0 = 0x43C00000;  // 384.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a3 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    t0 = 98;
    t1 = 174;
    t2 = 255;
    jal(ctx, 0x169EDCu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
    v0 = 0x43CA0000;  // 404.0f
    mtc1(v0, f0);
    add_s(f20, f0, f20);
    a0 = 40;
    jal(ctx, 0x169EF8u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 565;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    t0 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 42;
    mov_s(f13, f20);
    a3 = 2990;
    t1 = 4;
    t2 = a2;
    t3 = 70;
    jal(ctx, 0x169F44u, gen::fn_sub_115DE0_00115de0);
    a0 = 40;
    jal(ctx, 0x169F50u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 0x44120000;  // 584.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    t0 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 39;
    mov_s(f13, f20);
    a3 = 2990;
    t1 = 4;
    t2 = 42;
    t3 = 70;
    jal(ctx, 0x169F94u, gen::fn_sub_115DE0_00115de0);
    a0 = 40;
    jal(ctx, 0x169FA0u, gen::fn_sub_21EA00_0021ea00);  // render state $a0
    lwc1(f1, s3, 0);  // g_rwIm2DNearScreenZ
    sub_s(f14, f1, f0);
    v0 = 603;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    t0 = s1 & 0xFF;
    a0 = s4;
    lw(a1, s2, 4);
    a2 = 39;
    mov_s(f13, f20);
    a3 = 2990;
    t1 = 4;
    t2 = 42;
    t3 = 70;
    jal(ctx, 0x169FECu, gen::fn_sub_115DE0_00115de0);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0016A030 sub_16A030 -- 1640 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_OpenTradeDraw] COMM: the drop / trade screen for scrGetIntPara(0): member 1 merges every item 4000..4299 of
// the member's pouch (owner id + 256) into the hero stock (capped at 99), else moves the member's equipment entries
// back; then creates "H_CampTradeDraw" (update sub_169470) with camp/camp_drop.pak into gp-19828.
void sub_16A030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016a030
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x16A050u, gen::fn_scrGetIntPara_0035ed20);
    s3 = v0;
    v0 = 1;
    if (s3 != v0) {
        // 0x0016a074
        charge(ctx, 1);
        s2 = addiu(s3, 256);
    } else {
        // 0x0016a068
        charge(ctx, 3);
        s2 = si(-1);
    }
    // 0x0016a078
    charge(ctx, 3);
    v0 = 1;
    if (s3 != v0) {
        // 0x0016a15c
        charge(ctx, 3);
        s4 = 0;
        for (;;) {
            // 0x0016a270
            charge(ctx, 3);
            v0 = slti(s4, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016a168
            charge(ctx, 9);
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x16A178u, gen::fn_sub_170A40_00170a40);  // [datGetPouchItemId] (pc, i)
            v0 = v0 & 0xFFFF;
            if (v0 != 0) {
                // 0x0016a18c
                charge(ctx, 10);
                a0 = dsll32(s3, 16);
                a0 = dsra32(a0, 16);
                a1 = dsll32(s4, 16);
                a1 = dsra32(a1, 16);
                jal(ctx, 0x16A19Cu, gen::fn_sub_170AB0_00170ab0);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (v0 != 0) {
                    // 0x0016a1b4
                    charge(ctx, 25);
                    a0 = dsll32(s3, 16);
                    a0 = dsra32(a0, 16);
                    a1 = dsll32(s4, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x16A1C4u, gen::fn_sub_170A40_00170a40);  // [datGetPouchItemId] (pc, i)
                    s1 = v0 & 0xFFFF;
                    a0 = dsll32(s3, 16);
                    a0 = dsra32(a0, 16);
                    a1 = dsll32(s4, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x16A1E0u, gen::fn_sub_170AB0_00170ab0);
                    s0 = dsll32(v0, 16);
                    s0 = dsra32(s0, 16);
                    a1 = dsll32(s1, 16);
                    a1 = dsra32(a1, 16);
                    a0 = 1;
                    jal(ctx, 0x16A1FCu, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
                    v0 = v0 & 0xFFFF;
                    v0 = addu(s0, v0);
                    at = slti(v0, 100);
                    if (at == 0) {
                        // 0x0016a218
                        charge(ctx, 1);
                        v0 = 99;
                    }
                    // 0x0016a21c
                    charge(ctx, 20);
                    a1 = dsll32(s1, 16);
                    a1 = dsra32(a1, 16);
                    a2 = v0 & 0xFFFF;
                    a0 = 1;
                    jal(ctx, 0x16A22Cu, gen::fn_sub_170860_00170860);  // [datSetItemNum] (owner, id, count)
                    a0 = dsll32(s3, 16);
                    a0 = dsra32(a0, 16);
                    a1 = dsll32(s4, 16);
                    a1 = dsra32(a1, 16);
                    a2 = 0;
                    jal(ctx, 0x16A248u, gen::fn_sub_170B20_00170b20);
                    a0 = dsll32(s3, 16);
                    a0 = dsra32(a0, 16);
                    a1 = dsll32(s4, 16);
                    a1 = dsra32(a1, 16);
                    a2 = 0;
                    jal(ctx, 0x16A264u, gen::fn_sub_170B90_00170b90);
                }
            }
            // 0x0016a26c
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
    } else {
        // 0x0016a084
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0016a148
            charge(ctx, 3);
            v0 = slti(s0, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016a090
            charge(ctx, 10);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            v0 = addiu(s0, 4000);
            a1 = dsll32(v0, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x16A0A4u, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
            v0 = v0 & 0xFFFF;
            if (v0 != 0) {
                // 0x0016a0b8
                charge(ctx, 19);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                v0 = addiu(s0, 4000);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                jal(ctx, 0x16A0CCu, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
                s1 = v0 & 0xFFFF;
                v0 = addiu(s0, 4000);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a0 = 1;
                jal(ctx, 0x16A0E8u, gen::fn_sub_170760_00170760);  // [datGetItemNum] (owner, id)
                v0 = v0 & 0xFFFF;
                v1 = addu(s1, v0);
                at = slti(v1, 100);
                if (at == 0) {
                    // 0x0016a104
                    charge(ctx, 1);
                    v1 = 99;
                }
                // 0x0016a108
                charge(ctx, 15);
                v0 = addiu(s0, 4000);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a2 = v1 & 0xFFFF;
                a0 = 1;
                jal(ctx, 0x16A11Cu, gen::fn_sub_170860_00170860);  // [datSetItemNum] (owner, id, count)
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                v0 = addiu(s0, 4000);
                a1 = dsll32(v0, 16);
                a1 = dsra32(a1, 16);
                a2 = 0;
                jal(ctx, 0x16A13Cu, gen::fn_sub_170860_00170860);  // [datSetItemNum] (owner, id, count)
            }
            // 0x0016a144
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x0016a154
        charge(ctx, 2);
    }
    // 0x0016a27c
    charge(ctx, 4);
    s3 = 0;
    s0 = 0;
    for (;;) {
        // 0x0016a2b4
        charge(ctx, 3);
        v0 = slti(s0, 20);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016a28c
        charge(ctx, 8);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        a1 = s0;
        jal(ctx, 0x16A298u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
        v0 = v0 & 0xFFFF;
        if (v0 != 0) {
            // 0x0016a2ac
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x0016a2b0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0016a2c0
    charge(ctx, 4);
    s1 = 0;
    s0 = 0;
    for (;;) {
        // 0x0016a2f4
        charge(ctx, 3);
        v0 = slti(s0, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016a2d0
        charge(ctx, 7);
        a0 = 1;
        a1 = s0;
        jal(ctx, 0x16A2D8u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
        v0 = v0 & 0xFFFF;
        if (v0 != 0) {
            // 0x0016a2ec
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x0016a2f0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0016a300
    charge(ctx, 4);
    v0 = addu(s3, s1);
    at = slti(v0, 301);
    if (at != 0) {
        // 0x0016a54c
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0016a660
            charge(ctx, 3);
            v0 = slti(s0, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0016a558
            charge(ctx, 8);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            a1 = s0;
            jal(ctx, 0x16A564u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
            v0 = v0 & 0xFFFF;
            if (v0 != 0) {
                // 0x0016a578
                charge(ctx, 57);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A584u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                sh(v0, sp, 0x60);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A59Cu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                sw(v0, sp, 0x64);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A5B4u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                sb(v0, sp, 0x68);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A5CCu, gen::fn_sub_16F900_0016f900);  // (owner, index)
                sb(v0, sp, 0x69);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A5E4u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                sh(v0, sp, 0x6A);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A5FCu, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                sh(v0, sp, 0x6C);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A614u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                sh(v0, sp, 0x6E);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A62Cu, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                sh(v0, sp, 0x70);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                a2 = 0;
                jal(ctx, 0x16A648u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                a0 = addiu(sp, 0x60);
                jal(ctx, 0x16A654u, gen::fn_sub_1830C0_001830c0);
            }
            // 0x0016a65c
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x0016a66c
        charge(ctx, 1);
        sw(zero, gp, g::kScreenTaskC);  // 0x7CDF7C
    } else {
        // 0x0016a310
        charge(ctx, 3);
        v0 = si(-1);
        if (s2 != v0) {
            // 0x0016a31c
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x0016a4a4
                charge(ctx, 3);
                v0 = slti(s0, 20);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0016a328
                charge(ctx, 8);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                a1 = s0;
                jal(ctx, 0x16A334u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                v0 = v0 & 0xFFFF;
                if (v0 != 0) {
                    // 0x0016a348
                    charge(ctx, 86);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A354u, gen::fn_sub_16F630_0016f630);  // [datGetEquipmentItemId] (owner, index)
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A368u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A37Cu, gen::fn_sub_16F720_0016f720);  // (owner, index): a flag word (sub_12DF50 makes it an icon)
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A390u, gen::fn_sub_16FF90_0016ff90);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A3A4u, gen::fn_sub_16F810_0016f810);  // (owner, index)
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A3B8u, gen::fn_sub_170080_00170080);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A3CCu, gen::fn_sub_16F900_0016f900);  // (owner, index)
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A3E0u, gen::fn_sub_170170_00170170);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A3F4u, gen::fn_sub_16F9F0_0016f9f0);  // [datGetEquipmentPower]
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A408u, gen::fn_sub_170260_00170260);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A41Cu, gen::fn_sub_16FAE0_0016fae0);  // [datGetEquipmentAccuracy]
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A430u, gen::fn_sub_170350_00170350);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A444u, gen::fn_sub_16FBD0_0016fbd0);  // [datGetEquipmentEvasion]
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A458u, gen::fn_sub_170440_00170440);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    jal(ctx, 0x16A46Cu, gen::fn_sub_16FCC0_0016fcc0);  // [datGetEquipmentDefense]
                    a0 = si(-1);
                    a1 = s0;
                    a2 = v0;
                    jal(ctx, 0x16A480u, gen::fn_sub_170530_00170530);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    a1 = s0;
                    a2 = 0;
                    jal(ctx, 0x16A498u, gen::fn_sub_16FEA0_0016fea0);  // [datSetEquipmentItemId] (owner, index, id)
                }
                // 0x0016a4a0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
        }
        // 0x0016a4b0
        charge(ctx, 10);
        a0 = 1;
        a1 = 36;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x16A4C4u, v0.u());
        s0 = v0;
        if (s0 != 0) {
            // 0x0016a4e4
            charge(ctx, 14);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, -16352);  // "H_CampTradeDraw"
            a2 = 6335;
            a3 = 0x170000;
            a3 = addiu(a3, -27536);  // &sub_169470
            t0 = 0x170000;
            t0 = addiu(t0, -25888);  // &sub_169AE0
            t1 = s0;
            jal(ctx, 0x16A508u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
            s1 = v0;
            if (s1 != 0) {
                // 0x0016a528
                charge(ctx, 6);
                a0 = 0x5E0000;
                a0 = addiu(a0, -16336);  // "camp/camp_drop.pak"
                a1 = 1;
                jal(ctx, 0x16A534u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, 12);
            } else {
                // 0x0016a51c
                charge(ctx, 3);
                s1 = 0;
            }
        } else {
            // 0x0016a4d8
            charge(ctx, 3);
            s1 = 0;
        }
        // 0x0016a540
        charge(ctx, 3);
        sw(s1, gp, g::kScreenTaskC);  // 0x7CDF7C
    }
    // 0x0016a670 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = 1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0016A700 sub_16A700 -- 2184 bytes; frame 0x1C0: ra sp+0xA0, s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_TradeDrawStock] (trade work, xy, list, alpha): the stock column of the trade screen: frames 68..70, the six
// visible rows with their owner marks, names (datGetItemName) and the cursor (+2906 words).
void sub_16A700(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x0016a700
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1C0);
    sd(ra, sp, 0xA0);
    sq(s7, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    sd(a1, sp, 0xB8);
    mov_s(f25, f12);
    s1 = a2;
    s0 = a3;
    v0 = 255;
    s6 = subu(v0, s0);
    lwc1(f20, sp, 0xBC);
    v0 = 541;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xB8);
    add_s(f21, f1, f0);
    v0 = 0x42180000;  // 38.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a3 = s0 & 0xFF;
    a0 = s5;
    lw(a1, s2, 4);
    a2 = 68;
    mov_s(f12, f21);
    mov_s(f14, f25);
    jal(ctx, 0x16A7A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x436B0000;  // 235.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a3 = s0 & 0xFF;
    a0 = s5;
    lw(a1, s2, 4);
    a2 = 69;
    mov_s(f12, f21);
    mov_s(f14, f25);
    jal(ctx, 0x16A7D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s1, 11620);
    a0 = addiu(v0, -6);
    if (i64(a0) <= 0) {
        // 0x0016a810
        charge(ctx, 1);
        v1 = 0;
    } else {
        // 0x0016a7ec
        charge(ctx, 9);
        lw(v1, s1, 11628);
        v0 = 151;
        mult(v0, v1, v0);
        div(v0, a0);
        mflo(v1);
    }
    // 0x0016a814
    charge(ctx, 37);
    lwc1(f20, sp, 0xBC);
    v0 = 0x422C0000;  // 43.0f
    mtc1(v0, f0);
    add_s(f24, f0, f20);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f13, f24, f0);
    a3 = s0 & 0xFF;
    a0 = s5;
    lw(a1, s2, 4);
    a2 = 70;
    mov_s(f12, f21);
    mov_s(f14, f25);
    jal(ctx, 0x16A850u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s4 = 0;
    v1 = 0x42740000;  // 61.0f
    mtc1(v1, f0);
    add_s(f23, f0, f20);
    v1 = 0x43440000;  // 196.0f
    mtc1(v1, f0);
    lwc1(f1, sp, 0xB8);
    add_s(f22, f0, f1);
    v1 = 0x43760000;  // 246.0f
    mtc1(v1, f0);
    add_s(f21, f0, f1);
    v1 = 525;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    add_s(f20, f0, f1);
    for (;;) {
        // 0x0016aa98
        charge(ctx, 3);
        v1 = slti(s4, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016a8a8
        charge(ctx, 3);
        lw(v0, s1, 11624);
        if (v0 != s4) {
            // 0x0016a978
            charge(ctx, 9);
            lw(v0, s1, 11628);
            v1 = addu(v0, s4);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s1, v0);
            lw(v0, v0, 112);
            if (v0 == 0) {
                // 0x0016aa34
                charge(ctx, 24);
                v0 = sll(s4, 5);
                v0 = addu(v0, s4);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f26, f24, f0);
                a3 = s0 & 0xFF;
                a0 = s5;
                lw(a1, s2, 4);
                a2 = 60;
                mov_s(f12, f21);
                mov_s(f13, f26);
                mov_s(f14, f25);
                jal(ctx, 0x16AA68u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                a3 = s0 & 0xFF;
                a0 = s5;
                lw(a1, s2, 4);
                a2 = 61;
                mov_s(f12, f20);
                mov_s(f13, f26);
                mov_s(f14, f25);
                jal(ctx, 0x16AA8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0016a99c
                charge(ctx, 38);
                v0 = sll(s4, 5);
                s3 = addu(v0, s4);
                mtc1(s3, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f23, f0);
                a3 = s0 & 0xFF;
                a0 = s5;
                lw(a1, s2, 4);
                a2 = 37;
                mov_s(f12, f22);
                mov_s(f14, f25);
                jal(ctx, 0x16A9CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                mtc1(s3, f0);
                cvt_s_w(f0, f0);
                add_s(f26, f24, f0);
                a3 = s0 & 0xFF;
                a0 = s5;
                lw(a1, s2, 4);
                a2 = 62;
                mov_s(f12, f21);
                mov_s(f13, f26);
                mov_s(f14, f25);
                jal(ctx, 0x16AA00u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                a3 = s0 & 0xFF;
                a0 = s5;
                lw(a1, s2, 4);
                a2 = 63;
                mov_s(f12, f20);
                mov_s(f13, f26);
                mov_s(f14, f25);
                jal(ctx, 0x16AA24u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
        } else {
            // 0x0016a8b4
            charge(ctx, 9);
            lw(v0, s1, 11628);
            v1 = addu(v0, s4);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s1, v0);
            lw(v0, v0, 112);
            if (v0 != 0) {
                // 0x0016a8d8
                charge(ctx, 14);
                v0 = sll(s4, 5);
                v0 = addu(v0, s4);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f23, f0);
                a3 = s0 & 0xFF;
                a0 = s5;
                lw(a1, s2, 4);
                a2 = 37;
                mov_s(f12, f22);
                mov_s(f14, f25);
                jal(ctx, 0x16A908u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
            // 0x0016a910
            charge(ctx, 26);
            v0 = sll(s4, 5);
            v0 = addu(v0, s4);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f26, f24, f0);
            a3 = s0 & 0xFF;
            a0 = s5;
            lw(a1, s2, 4);
            a2 = 64;
            mov_s(f12, f21);
            mov_s(f13, f26);
            mov_s(f14, f25);
            jal(ctx, 0x16A944u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a3 = s0 & 0xFF;
            a0 = s5;
            lw(a1, s2, 4);
            a2 = 65;
            mov_s(f12, f20);
            mov_s(f13, f26);
            mov_s(f14, f25);
            jal(ctx, 0x16A968u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
        // 0x0016aa94
        charge(ctx, 1);
        s4 = addiu(s4, 1);
    }
    // 0x0016aaa4
    charge(ctx, 24);
    s4 = 0;
    lwc1(f1, sp, 0xBC);
    v1 = 0x437C0000;  // 252.0f
    mtc1(v1, f0);
    lwc1(f2, sp, 0xB8);
    add_s(f21, f0, f2);
    v1 = si(-256);
    s6 = s6 | v1;
    cvt_w_s(f0, f1);
    cvt_s_w(f1, f0);
    v1 = 0x42500000;  // 52.0f
    mtc1(v1, f0);
    add_s(f20, f0, f1);
    cvt_w_s(f0, f2);
    cvt_s_w(f1, f0);
    v1 = 0x43920000;  // 292.0f
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s7, f0);
    for (;;) {
        // 0x0016af30
        charge(ctx, 3);
        v1 = slti(s4, 6);
        if (v1 != 0) {
            backedge(ctx);
            // 0x0016ab04
            charge(ctx, 6);
            lw(v1, s1, 11628);
            a0 = addu(s4, v1);
            lw(v1, s1, 11620);
            at = slt(a0, v1);
            if (at != 0) {
                // 0x0016ab1c
                charge(ctx, 3);
                lw(v0, s1, 11624);
                if (s4 != v0) {
                    // 0x0016ad34
                    charge(ctx, 9);
                    a1 = 9;
                    v0 = sll(a0, 3);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    lw(v0, v0, 120);
                    at = sltiu(v0, 21);
                    if (at != 0) {
                        // 0x0016ad58
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 25408);  // &0x7B6340
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x16AD74u:  // table[0]
                            // 0x0016ad74
                            charge(ctx, 3);
                            a1 = 1;
                            break;
                        case 0x16AD80u:  // table[1]
                            // 0x0016ad80
                            charge(ctx, 3);
                            a1 = 3;
                            break;
                        case 0x16AD8Cu:  // table[2]
                            // 0x0016ad8c
                            charge(ctx, 3);
                            a1 = 5;
                            break;
                        case 0x16AD98u:  // table[3]
                            // 0x0016ad98
                            charge(ctx, 3);
                            a1 = 7;
                            break;
                        case 0x16ADA4u:  // table[4]
                            // 0x0016ada4
                            charge(ctx, 2);
                            break;
                        case 0x16ADACu:  // table[5]
                            // 0x0016adac
                            charge(ctx, 3);
                            a1 = 11;
                            break;
                        case 0x16ADB8u:  // table[6]
                            // 0x0016adb8
                            charge(ctx, 3);
                            a1 = 13;
                            break;
                        case 0x16ADC4u:  // table[7]
                            // 0x0016adc4
                            charge(ctx, 3);
                            a1 = 15;
                            break;
                        case 0x16ADD0u:  // table[8]
                            // 0x0016add0
                            charge(ctx, 3);
                            a1 = 1;
                            break;
                        case 0x16ADDCu:  // table[9]
                            // 0x0016addc
                            charge(ctx, 3);
                            a1 = 3;
                            break;
                        case 0x16ADE8u:  // table[10]
                            // 0x0016ade8
                            charge(ctx, 3);
                            a1 = 5;
                            break;
                        case 0x16ADF4u:  // table[11]
                            // 0x0016adf4
                            charge(ctx, 3);
                            a1 = 7;
                            break;
                        case 0x16AE00u:  // table[12]
                            // 0x0016ae00
                            charge(ctx, 2);
                            break;
                        case 0x16AE08u:  // table[13]
                            // 0x0016ae08
                            charge(ctx, 3);
                            a1 = 11;
                            break;
                        case 0x16AE14u:  // table[14]
                            // 0x0016ae14
                            charge(ctx, 3);
                            a1 = 13;
                            break;
                        case 0x16AE20u:  // table[15]
                            // 0x0016ae20
                            charge(ctx, 3);
                            a1 = 15;
                            break;
                        case 0x16AE2Cu:  // table[16]
                            // 0x0016ae2c
                            charge(ctx, 3);
                            a1 = 19;
                            break;
                        case 0x16AE38u:  // table[17]
                            // 0x0016ae38
                            charge(ctx, 3);
                            a1 = 21;
                            break;
                        case 0x16AE44u:  // table[18]
                            // 0x0016ae44
                            charge(ctx, 3);
                            a1 = 23;
                            break;
                        case 0x16AE50u:  // table[19]
                            // 0x0016ae50
                            charge(ctx, 3);
                            a1 = 27;
                            break;
                        case 0x16AE5Cu:  // table[20]
                            // 0x0016ae5c
                            charge(ctx, 1);
                            a1 = 27;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                    // 0x0016ae60
                    charge(ctx, 51);
                    v0 = sll(s4, 5);
                    s3 = addu(v0, s4);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f24, f0);
                    a2 = addiu(a1, -1);
                    a3 = s0 & 0xFF;
                    a0 = s5;
                    lw(a1, s2, 0);
                    mov_s(f12, f21);
                    t0 = 32;
                    t1 = 67;
                    t2 = 120;
                    mov_s(f14, f25);
                    jal(ctx, 0x16AE9Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    lw(v0, s1, 11628);
                    v1 = addu(v0, s4);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(s1, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x16AED0u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0xC0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x16AEE4u, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f20, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f25);
                    a2 = s6;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0xC0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x16AF24u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                } else {
                    // 0x0016ab28
                    charge(ctx, 9);
                    a1 = 9;
                    v0 = sll(a0, 3);
                    v0 = addu(v0, a0);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    lw(v0, v0, 120);
                    at = sltiu(v0, 21);
                    if (at != 0) {
                        // 0x0016ab4c
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 25504);  // &0x7B63A0
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x16AB68u:  // table[0]
                            // 0x0016ab68
                            charge(ctx, 3);
                            a1 = 0;
                            break;
                        case 0x16AB74u:  // table[1]
                            // 0x0016ab74
                            charge(ctx, 3);
                            a1 = 2;
                            break;
                        case 0x16AB80u:  // table[2]
                            // 0x0016ab80
                            charge(ctx, 3);
                            a1 = 4;
                            break;
                        case 0x16AB8Cu:  // table[3]
                            // 0x0016ab8c
                            charge(ctx, 3);
                            a1 = 6;
                            break;
                        case 0x16AB98u:  // table[4]
                            // 0x0016ab98
                            charge(ctx, 3);
                            a1 = 8;
                            break;
                        case 0x16ABA4u:  // table[5]
                            // 0x0016aba4
                            charge(ctx, 3);
                            a1 = 10;
                            break;
                        case 0x16ABB0u:  // table[6]
                            // 0x0016abb0
                            charge(ctx, 3);
                            a1 = 12;
                            break;
                        case 0x16ABBCu:  // table[7]
                            // 0x0016abbc
                            charge(ctx, 3);
                            a1 = 14;
                            break;
                        case 0x16ABC8u:  // table[8]
                            // 0x0016abc8
                            charge(ctx, 3);
                            a1 = 0;
                            break;
                        case 0x16ABD4u:  // table[9]
                            // 0x0016abd4
                            charge(ctx, 3);
                            a1 = 2;
                            break;
                        case 0x16ABE0u:  // table[10]
                            // 0x0016abe0
                            charge(ctx, 3);
                            a1 = 4;
                            break;
                        case 0x16ABECu:  // table[11]
                            // 0x0016abec
                            charge(ctx, 3);
                            a1 = 6;
                            break;
                        case 0x16ABF8u:  // table[12]
                            // 0x0016abf8
                            charge(ctx, 3);
                            a1 = 8;
                            break;
                        case 0x16AC04u:  // table[13]
                            // 0x0016ac04
                            charge(ctx, 3);
                            a1 = 10;
                            break;
                        case 0x16AC10u:  // table[14]
                            // 0x0016ac10
                            charge(ctx, 3);
                            a1 = 12;
                            break;
                        case 0x16AC1Cu:  // table[15]
                            // 0x0016ac1c
                            charge(ctx, 3);
                            a1 = 14;
                            break;
                        case 0x16AC28u:  // table[16]
                            // 0x0016ac28
                            charge(ctx, 3);
                            a1 = 18;
                            break;
                        case 0x16AC34u:  // table[17]
                            // 0x0016ac34
                            charge(ctx, 3);
                            a1 = 20;
                            break;
                        case 0x16AC40u:  // table[18]
                            // 0x0016ac40
                            charge(ctx, 3);
                            a1 = 22;
                            break;
                        case 0x16AC4Cu:  // table[19]
                            // 0x0016ac4c
                            charge(ctx, 3);
                            a1 = 26;
                            break;
                        case 0x16AC58u:  // table[20]
                            // 0x0016ac58
                            charge(ctx, 1);
                            a1 = 26;
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                    // 0x0016ac5c
                    charge(ctx, 54);
                    v0 = sll(s4, 5);
                    s3 = addu(v0, s4);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f24, f0);
                    a2 = addiu(a1, 1);
                    a3 = s0 & 0xFF;
                    a0 = s5;
                    lw(a1, s2, 0);
                    mov_s(f12, f21);
                    mov_s(f14, f25);
                    jal(ctx, 0x16AC8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s1, 11628);
                    v1 = addu(v0, s4);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v1 = addu(s1, v0);
                    lh(v0, v1, 100);
                    a0 = v0;
                    lbu(v0, v1, 125);
                    a1 = dsll32(v0, 16);
                    a1 = dsra32(a1, 16);
                    jal(ctx, 0x16ACC0u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                    a0 = addiu(sp, 0xC0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x16ACD4u, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f20, f0);
                    v0 = 0x3F800000;  // 1.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f25);
                    a2 = s6;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0xC0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x16AD24u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                }
                // 0x0016af2c
                charge(ctx, 1);
                s4 = addiu(s4, 1);
                continue;
            }
        }
        break;
    }
    // 0x0016af3c (the shared epilogue, written out on this path)
    charge(ctx, 19);
    ld(ra, sp, 0xA0);
    lq(s7, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1C0);
}

// 0x0016AF90 sub_16AF90 -- 2668 bytes; frame 0x1D0: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_TradeDrawDetail] (trade work, xy, list, alpha): the detail column: frames 72..78, the selected row's stats
// (sprintf + sub_40EB50) and its help line (sub_3C7E20).
void sub_16AF90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26};
    // 0x0016af90
    enter(ctx, 122);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1D0);
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
    swc1(f26, sp, 0x18);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s4 = a0;
    sd(a1, sp, 0xC8);
    mov_s(f22, f12);
    s3 = a2;
    s2 = a3;
    v0 = 255;
    s5 = subu(v0, s2);
    lwc1(f21, sp, 0xCC);
    v0 = 0x43720000;  // 242.0f
    mtc1(v0, f0);
    add_s(f20, f0, f21);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC8);
    add_s(f12, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 72;
    mov_s(f13, f20);
    mov_s(f14, f22);
    jal(ctx, 0x16B030u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43AE0000;  // 348.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC8);
    add_s(f12, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 73;
    mov_s(f13, f20);
    mov_s(f14, f22);
    jal(ctx, 0x16B060u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x425C0000;  // 55.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC8);
    add_s(f20, f1, f0);
    v0 = 0x437C0000;  // 252.0f
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 74;
    mov_s(f12, f20);
    mov_s(f14, f22);
    jal(ctx, 0x16B0A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x438F0000;  // 286.0f
    mtc1(v0, f0);
    add_s(f24, f0, f21);
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 75;
    mov_s(f12, f20);
    mov_s(f13, f24);
    mov_s(f14, f22);
    jal(ctx, 0x16B0D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43460000;  // 198.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC8);
    add_s(f23, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 76;
    mov_s(f12, f23);
    mov_s(f13, f24);
    mov_s(f14, f22);
    jal(ctx, 0x16B108u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 313;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f24, f0, f21);
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 77;
    mov_s(f12, f20);
    mov_s(f13, f24);
    mov_s(f14, f22);
    jal(ctx, 0x16B140u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    a3 = s2 & 0xFF;
    a0 = s6;
    lw(a1, s4, 4);
    a2 = 78;
    mov_s(f12, f23);
    mov_s(f13, f24);
    mov_s(f14, f22);
    jal(ctx, 0x16B164u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(v0, s3, 11620);
    if (v0 == 0) {
        // 0x0016b894
        charge(ctx, 70);
        mov_s(f23, f21);
        v0 = 0x438F0000;  // 286.0f
        mtc1(v0, f0);
        add_s(f1, f0, f23);
        v0 = 0x41000000;  // 8.0f
        mtc1(v0, f0);
        add_s(f21, f0, f1);
        v0 = 0x425C0000;  // 55.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xC8);
        add_s(f1, f1, f0);
        v0 = 0x42940000;  // 74.0f
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        a3 = s2 & 0xFF;
        a0 = s6;
        lw(a1, s4, 4);
        a2 = 79;
        mov_s(f12, f20);
        mov_s(f13, f21);
        mov_s(f14, f22);
        jal(ctx, 0x16B8F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43460000;  // 198.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xC8);
        add_s(f1, f1, f0);
        v0 = 0x42940000;  // 74.0f
        mtc1(v0, f0);
        add_s(f24, f0, f1);
        a3 = s2 & 0xFF;
        a0 = s6;
        lw(a1, s4, 4);
        a2 = 79;
        mov_s(f12, f24);
        mov_s(f13, f21);
        mov_s(f14, f22);
        jal(ctx, 0x16B938u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 313;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f23);
        v0 = 0x41000000;  // 8.0f
        mtc1(v0, f0);
        add_s(f21, f0, f1);
        a3 = s2 & 0xFF;
        a0 = s6;
        lw(a1, s4, 4);
        a2 = 79;
        mov_s(f12, f20);
        mov_s(f13, f21);
        mov_s(f14, f22);
        jal(ctx, 0x16B980u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a3 = s2 & 0xFF;
        a0 = s6;
        lw(a1, s4, 4);
        a2 = 79;
        mov_s(f12, f24);
        mov_s(f13, f21);
        mov_s(f14, f22);
        jal(ctx, 0x16B9A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x0016b178
        charge(ctx, 11);
        lw(v1, s3, 11628);
        lw(v0, s3, 11624);
        s0 = addu(v1, v0);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        s7 = sll(v0, 2);
        v0 = addu(s7, s3);
        lw(v0, v0, 120);
        at = sltiu(v0, 21);
        if (at != 0) {
            // 0x0016b1a4
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 25600);  // &0x7B6400
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x16B1C0u:  // table[0]
                // 0x0016b1c0
                charge(ctx, 3);
                s1 = 81;
                break;
            case 0x16B1CCu:  // table[1]
                // 0x0016b1cc
                charge(ctx, 3);
                s1 = 82;
                break;
            case 0x16B1D8u:  // table[2]
                // 0x0016b1d8
                charge(ctx, 3);
                s1 = 83;
                break;
            case 0x16B1E4u:  // table[3]
                // 0x0016b1e4
                charge(ctx, 3);
                s1 = 84;
                break;
            case 0x16B1F0u:  // table[4]
                // 0x0016b1f0
                charge(ctx, 3);
                s1 = 85;
                break;
            case 0x16B1FCu:  // table[5]
                // 0x0016b1fc
                charge(ctx, 3);
                s1 = 86;
                break;
            case 0x16B208u:  // table[6]
                // 0x0016b208
                charge(ctx, 3);
                s1 = 91;
                break;
            case 0x16B214u:  // table[7]
                // 0x0016b214
                charge(ctx, 3);
                s1 = 87;
                break;
            case 0x16B220u:  // table[8]
                // 0x0016b220
                charge(ctx, 3);
                s1 = 81;
                break;
            case 0x16B22Cu:  // table[9]
                // 0x0016b22c
                charge(ctx, 3);
                s1 = 82;
                break;
            case 0x16B238u:  // table[10]
                // 0x0016b238
                charge(ctx, 3);
                s1 = 83;
                break;
            case 0x16B244u:  // table[11]
                // 0x0016b244
                charge(ctx, 3);
                s1 = 84;
                break;
            case 0x16B250u:  // table[12]
                // 0x0016b250
                charge(ctx, 3);
                s1 = 85;
                break;
            case 0x16B25Cu:  // table[13]
                // 0x0016b25c
                charge(ctx, 3);
                s1 = 86;
                break;
            case 0x16B268u:  // table[14]
                // 0x0016b268
                charge(ctx, 3);
                s1 = 91;
                break;
            case 0x16B274u:  // table[15]
                // 0x0016b274
                charge(ctx, 3);
                s1 = 87;
                break;
            case 0x16B280u:  // table[16]
                // 0x0016b280
                charge(ctx, 3);
                s1 = 88;
                break;
            case 0x16B28Cu:  // table[17]
                // 0x0016b28c
                charge(ctx, 3);
                s1 = 89;
                break;
            case 0x16B298u:  // table[18]
                // 0x0016b298
                charge(ctx, 3);
                s1 = 90;
                break;
            case 0x16B2A4u:  // table[19]
                // 0x0016b2a4
                charge(ctx, 3);
                s1 = 90;
                break;
            case 0x16B2B0u:  // table[20]
                // 0x0016b2b0
                charge(ctx, 1);
                s1 = 90;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x0016b2b4
        charge(ctx, 20);
        v0 = 0x42FE0000;  // 127.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xC8);
        add_s(f12, f1, f0);
        v0 = 0x437D0000;  // 253.0f
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s2 & 0xFF;
        a0 = s6;
        lw(a1, s4, 4);
        a2 = s1;
        mov_s(f14, f22);
        jal(ctx, 0x16B2E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a0 = addu(s7, s3);
        lbu(v1, a0, 126);
        v0 = 2;
        if (v1 == v0) {
            // 0x0016b5d0
            charge(ctx, 79);
            lhu(a2, a0, 134);
            a0 = addiu(sp, 0xD0);
            a1 = addiu(gp, -30312);  // "%3d"
            jal(ctx, 0x16B5DCu, gen::fn_sprintf_00523ac8);
            lwc1(f25, sp, 0xCC);
            v0 = 313;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f0, f25);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f23, f0, f1);
            v0 = 0x43460000;  // 198.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0xC8);
            add_s(f1, f1, f0);
            v0 = 0x42940000;  // 74.0f
            mtc1(v0, f0);
            add_s(f24, f0, f1);
            cvt_w_s(f0, f24);
            mfc1(a0, f0);
            cvt_w_s(f0, f23);
            mfc1(a1, f0);
            a2 = s5 & 0xFF;
            mov_s(f12, f22);
            a3 = 4;
            t0 = addiu(sp, 0xD0);
            t1 = 0;
            jal(ctx, 0x16B650u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
            v0 = 0x438F0000;  // 286.0f
            mtc1(v0, f0);
            add_s(f1, f0, f25);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f26, f0, f1);
            v0 = 0x425C0000;  // 55.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0xC8);
            add_s(f1, f1, f0);
            v0 = 0x42940000;  // 74.0f
            mtc1(v0, f0);
            add_s(f25, f0, f1);
            a3 = s2 & 0xFF;
            a0 = s6;
            lw(a1, s4, 4);
            a2 = 79;
            mov_s(f12, f25);
            mov_s(f13, f26);
            mov_s(f14, f22);
            jal(ctx, 0x16B6B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a3 = s2 & 0xFF;
            a0 = s6;
            lw(a1, s4, 4);
            a2 = 79;
            mov_s(f12, f24);
            mov_s(f13, f26);
            mov_s(f14, f22);
            jal(ctx, 0x16B6D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a3 = s2 & 0xFF;
            a0 = s6;
            lw(a1, s4, 4);
            a2 = 79;
            mov_s(f12, f25);
            mov_s(f13, f23);
            mov_s(f14, f22);
            jal(ctx, 0x16B6FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x0016b304
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0016b494
                charge(ctx, 79);
                lhu(a2, a0, 132);
                a0 = addiu(sp, 0xD0);
                a1 = addiu(gp, -30312);  // "%3d"
                jal(ctx, 0x16B4A0u, gen::fn_sprintf_00523ac8);
                lwc1(f24, sp, 0xCC);
                v0 = 313;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f1, f0, f24);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f23, f0, f1);
                v0 = 0x425C0000;  // 55.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0xC8);
                add_s(f1, f1, f0);
                v0 = 0x42940000;  // 74.0f
                mtc1(v0, f0);
                add_s(f26, f0, f1);
                cvt_w_s(f0, f26);
                mfc1(a0, f0);
                cvt_w_s(f0, f23);
                mfc1(a1, f0);
                a2 = s5 & 0xFF;
                mov_s(f12, f22);
                a3 = 4;
                t0 = addiu(sp, 0xD0);
                t1 = 0;
                jal(ctx, 0x16B514u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
                v0 = 0x438F0000;  // 286.0f
                mtc1(v0, f0);
                add_s(f1, f0, f24);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                add_s(f25, f0, f1);
                a3 = s2 & 0xFF;
                a0 = s6;
                lw(a1, s4, 4);
                a2 = 79;
                mov_s(f12, f26);
                mov_s(f13, f25);
                mov_s(f14, f22);
                jal(ctx, 0x16B558u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                v0 = 0x43460000;  // 198.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0xC8);
                add_s(f1, f1, f0);
                v0 = 0x42940000;  // 74.0f
                mtc1(v0, f0);
                add_s(f24, f0, f1);
                a3 = s2 & 0xFF;
                a0 = s6;
                lw(a1, s4, 4);
                a2 = 79;
                mov_s(f12, f24);
                mov_s(f13, f25);
                mov_s(f14, f22);
                jal(ctx, 0x16B59Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                a3 = s2 & 0xFF;
                a0 = s6;
                lw(a1, s4, 4);
                a2 = 79;
                mov_s(f12, f24);
                mov_s(f13, f23);
                mov_s(f14, f22);
                jal(ctx, 0x16B5C0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0016b310
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x0016b320
                    charge(ctx, 93);
                    v0 = sll(s0, 3);
                    v0 = addu(v0, s0);
                    s7 = sll(v0, 2);
                    v0 = addu(s7, s3);
                    lhu(a2, v0, 128);
                    a0 = addiu(sp, 0xD0);
                    a1 = addiu(gp, -30312);  // "%3d"
                    jal(ctx, 0x16B33Cu, gen::fn_sprintf_00523ac8);
                    v0 = 255;
                    fp = subu(v0, s2);
                    lwc1(f24, sp, 0xCC);
                    v0 = 0x438F0000;  // 286.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f24);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(s1, f0);
                    v0 = 0x425C0000;  // 55.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xC8);
                    add_s(f1, f1, f0);
                    v0 = 0x42940000;  // 74.0f
                    mtc1(v0, f0);
                    add_s(f23, f0, f1);
                    cvt_w_s(f0, f23);
                    mfc1(a0, f0);
                    a2 = fp & 0xFF;
                    a1 = s1;
                    mov_s(f12, f22);
                    a3 = 4;
                    t0 = addiu(sp, 0xD0);
                    t1 = 0;
                    jal(ctx, 0x16B3B8u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
                    v0 = addu(s7, s3);
                    lhu(a2, v0, 130);
                    a0 = addiu(sp, 0xD0);
                    a1 = addiu(gp, -30312);  // "%3d"
                    jal(ctx, 0x16B3D0u, gen::fn_sprintf_00523ac8);
                    v0 = 0x43460000;  // 198.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xC8);
                    add_s(f1, f1, f0);
                    v0 = 0x42940000;  // 74.0f
                    mtc1(v0, f0);
                    add_s(f25, f0, f1);
                    cvt_w_s(f0, f25);
                    mfc1(a0, f0);
                    a2 = fp & 0xFF;
                    a1 = s1;
                    mov_s(f12, f22);
                    a3 = 4;
                    t0 = addiu(sp, 0xD0);
                    t1 = 0;
                    jal(ctx, 0x16B418u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
                    v0 = 313;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f0, f24);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    add_s(f24, f0, f1);
                    a3 = s2 & 0xFF;
                    a0 = s6;
                    lw(a1, s4, 4);
                    a2 = 79;
                    mov_s(f12, f23);
                    mov_s(f13, f24);
                    mov_s(f14, f22);
                    jal(ctx, 0x16B460u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    a3 = s2 & 0xFF;
                    a0 = s6;
                    lw(a1, s4, 4);
                    a2 = 79;
                    mov_s(f12, f25);
                    mov_s(f13, f24);
                    mov_s(f14, f22);
                    jal(ctx, 0x16B484u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x0016b318
                    charge(ctx, 2);
                    // 0x0016b70c
                    charge(ctx, 70);
                    lwc1(f25, sp, 0xCC);
                    v0 = 0x438F0000;  // 286.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f25);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    add_s(f24, f0, f1);
                    v0 = 0x425C0000;  // 55.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xC8);
                    add_s(f1, f1, f0);
                    v0 = 0x42940000;  // 74.0f
                    mtc1(v0, f0);
                    add_s(f23, f0, f1);
                    a3 = s2 & 0xFF;
                    a0 = s6;
                    lw(a1, s4, 4);
                    a2 = 79;
                    mov_s(f12, f23);
                    mov_s(f13, f24);
                    mov_s(f14, f22);
                    jal(ctx, 0x16B76Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 0x43460000;  // 198.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xC8);
                    add_s(f1, f1, f0);
                    v0 = 0x42940000;  // 74.0f
                    mtc1(v0, f0);
                    add_s(f26, f0, f1);
                    a3 = s2 & 0xFF;
                    a0 = s6;
                    lw(a1, s4, 4);
                    a2 = 79;
                    mov_s(f12, f26);
                    mov_s(f13, f24);
                    mov_s(f14, f22);
                    jal(ctx, 0x16B7B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = 313;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f0, f25);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    add_s(f24, f0, f1);
                    a3 = s2 & 0xFF;
                    a0 = s6;
                    lw(a1, s4, 4);
                    a2 = 79;
                    mov_s(f12, f23);
                    mov_s(f13, f24);
                    mov_s(f14, f22);
                    jal(ctx, 0x16B7F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    a3 = s2 & 0xFF;
                    a0 = s6;
                    lw(a1, s4, 4);
                    a2 = 79;
                    mov_s(f12, f26);
                    mov_s(f13, f24);
                    mov_s(f14, f22);
                    jal(ctx, 0x16B81Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
            }
        }
        // 0x0016b824
        charge(ctx, 28);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        cvt_w_s(f0, f20);
        mfc1(a0, f0);
        v0 = 0x43B20000;  // 356.0f
        mtc1(v0, f0);
        add_s(f0, f0, f21);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = si(-256);
        a2 = s5 | v0;
        a3 = addu(v1, s3);
        lbu(v0, a3, 124);
        v1 = sll(v0, 16);
        v0 = lui(0xFFFF);
        v1 = v1 & v0;
        lhu(v0, a3, 100);
        t2 = v0 | v1;
        mov_s(f12, f22);
        a3 = 1;
        t0 = 10;
        t1 = a3;
        jal(ctx, 0x16B884u, gen::fn_sub_3C7E20_003c7e20);  // a message text
    }
    // 0x0016b9ac (the shared epilogue, written out on this path)
    charge(ctx, 20);
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
    lwc1(f26, sp, 0x18);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
}

}  // namespace p3fes::game
