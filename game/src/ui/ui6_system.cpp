// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the system menu (its update; the menu, config, help, fusion-spell, request and calendar pages) and the title
// screen's config ("H_ConfigMenuDraw").
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
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_clndGetMonthFromDaysSinceApr5_0017d830(p3fes::EEContext&);
void fn_clndGetMoonPhase_00181b50(p3fes::EEContext&);
void fn_clndGetWeekDay_0017dae0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_103C30_00103c30(p3fes::EEContext&);
void fn_sub_103CB0_00103cb0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115AD0_00115ad0(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_11E380_0011e380(p3fes::EEContext&);
void fn_sub_12DF50_0012df50(p3fes::EEContext&);
void fn_sub_14EF60_0014ef60(p3fes::EEContext&);
void fn_sub_14F320_0014f320(p3fes::EEContext&);
void fn_sub_14F680_0014f680(p3fes::EEContext&);
void fn_sub_14F7D0_0014f7d0(p3fes::EEContext&);
void fn_sub_154970_00154970(p3fes::EEContext&);
void fn_sub_154F70_00154f70(p3fes::EEContext&);
void fn_sub_155070_00155070(p3fes::EEContext&);
void fn_sub_155710_00155710(p3fes::EEContext&);
void fn_sub_155830_00155830(p3fes::EEContext&);
void fn_sub_156140_00156140(p3fes::EEContext&);
void fn_sub_156240_00156240(p3fes::EEContext&);
void fn_sub_156E80_00156e80(p3fes::EEContext&);
void fn_sub_156F80_00156f80(p3fes::EEContext&);
void fn_sub_159900_00159900(p3fes::EEContext&);
void fn_sub_1599F0_001599f0(p3fes::EEContext&);
void fn_sub_15B330_0015b330(p3fes::EEContext&);
void fn_sub_15B430_0015b430(p3fes::EEContext&);
void fn_sub_170ED0_00170ed0(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_17AE30_0017ae30(p3fes::EEContext&);
void fn_sub_17C670_0017c670(p3fes::EEContext&);
void fn_sub_17C6C0_0017c6c0(p3fes::EEContext&);
void fn_sub_17C6E0_0017c6e0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_17DB40_0017db40(p3fes::EEContext&);
void fn_sub_17F990_0017f990(p3fes::EEContext&);
void fn_sub_18B6D0_0018b6d0(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_1BA8D0_001ba8d0(p3fes::EEContext&);
void fn_sub_30C220_0030c220(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3C3FE0_003c3fe0(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_3C7700_003c7700(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7D80_003c7d80(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
void fn_sub_403380_00403380(p3fes::EEContext&);
void fn_sub_403740_00403740(p3fes::EEContext&);
void fn_sub_403800_00403800(p3fes::EEContext&);
void fn_sub_403830_00403830(p3fes::EEContext&);
void fn_sub_403880_00403880(p3fes::EEContext&);
void fn_sub_403900_00403900(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui6;  // the record offsets, $gp words, pad words and sprite tables of ui6.h

// 0x0014F7D0 sub_14F7D0 -- 20380 bytes; frame 0x1E0: ra sp+0x60, s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_Camp_UpdateSystemMenuDrawTask] Update of "H_CampSystemMenuDraw" (jump table 0x7B60E0): 0 waits for flash 6, builds
// the status texture (+28), allocates the tweens (+12 x10, +16 x100), requests camp/datMixraidHelp.bmd (+36),
// facility/msg_quest.bmd (+40) and camp/camp_sys.pak (+44); 1 / 2 load them (messages 12 / 8, sprite files +20 / +24)
// and slide in; 3 is the menu (entries 0..5: confirm -> 26 calendar, 21 quest list, 16 fusion-spell list, 11 help list,
// 6 config, 5 -> message 7 "return to title"; cancel -> 4; up / down with wrap, The Answer skipping entries); 4 / 5
// close; 6..10 the config page (values +344 from flags 387.., written back on confirm); 11..15, 16..20, 21..25 the
// three lists; 26..30 the calendar (+332 month, +336 day; L1 / R1 change the month); 31..33 quit to the title (flag
// 5149, the fade +376, sub_17F990 / sub_1BA8D0).
void sub_14F7D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0014f7d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1E0);
    sd(ra, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    lw(s0, a0, 60);
    lw(v0, s0, sys::kState);
    at = sltiu(v0, 34);
    if (at != 0) {
        // 0x0014f7fc
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 24800);  // &0x7B60E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x14F818u:  // table[0]: state 0: wait for flash 6, texture, tweens, the three files
            // 0x0014f818
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 6;
            jal(ctx, 0x14F820u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0014f83c
                charge(ctx, 4);
                jal(ctx, 0x14F83Cu, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
                if (v0 == 0) {
                    // 0x0014f8a0
                    charge(ctx, 19);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -17280);  // "_h_camp_system.c"
                    sd(v0, sp, 0x10);
                    v0 = 437;
                    sd(v0, sp, 0x18);
                    a0 = 0;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20320);  // "camp/status/i_camp_hum_blue.tmx"
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x14F8E0u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    sw(v0, s0, sys::kBuild);
                } else {
                    // 0x0014f84c
                    charge(ctx, 21);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -17280);  // "_h_camp_system.c"
                    sd(v0, sp, 0x10);
                    v0 = 435;
                    sd(v0, sp, 0x18);
                    a0 = 0;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20400);  // "camp/status/AGS_i_camp_hum_blue_03.tmx"
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x14F88Cu, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    sw(v0, s0, sys::kBuild);
                }
                // 0x0014f8ec
                charge(ctx, 30);
                a0 = 10;
                jal(ctx, 0x14F8F0u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, sys::kMenuTweens);
                a0 = 100;
                jal(ctx, 0x14F900u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, sys::kPageTweens);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17248);  // "camp/datMixraidHelp.bmd"
                a1 = 0;
                jal(ctx, 0x14F918u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, sys::kHelpFile);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17216);  // "facility/msg_quest.bmd"
                a1 = 0;
                jal(ctx, 0x14F930u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, sys::kQuestFile);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17184);  // "camp/camp_sys.pak"
                a1 = 1;
                jal(ctx, 0x14F948u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, sys::kPak);
                v0 = 1;
                sw(v0, s0, sys::kState);
            L_00154748:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0014f830
                charge(ctx, 3);
                v0 = 0;
            }
            break;
        case 0x14F964u:  // table[1]: state 1: load the messages and sprite files
            // 0x0014f964
            charge(ctx, 3);
            lw(v0, s0, sys::kTexture);
            if (v0 == 0) {
                // 0x0014f970
                charge(ctx, 9);
                lw(a0, s0, sys::kBuild);
                a1 = addiu(sp, 0x1D8);
                a2 = 0;
                jal(ctx, 0x14F97Cu, gen::fn_sub_10C3A0_0010c3a0);  // poll the texture build
                sw(v0, s0, sys::kTexture);
                lw(v0, sp, 0x1D8);
                if (v0 != 0) {
                    goto L_0014f9a4;
                }
                // 0x0014f994
                charge(ctx, 4);
                sw(zero, s0, sys::kTexture);
                v0 = 0;
                break;
            }
        L_0014f9a4:
            charge(ctx, 5);
            lw(a0, s0, sys::kHelpFile);
            jal(ctx, 0x14F9A8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0014f9b8
                charge(ctx, 5);
                lw(a0, s0, sys::kQuestFile);
                jal(ctx, 0x14F9BCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0014f9cc
                    charge(ctx, 5);
                    lw(a0, s0, sys::kPak);
                    jal(ctx, 0x14F9D0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        // 0x0014f9e0
                        charge(ctx, 32);
                        lw(v0, s0, sys::kHelpFile);
                        a0 = 12;
                        lw(a1, v0, 272);
                        jal(ctx, 0x14F9ECu, gen::fn_sub_3C7D80_003c7d80);
                        lw(v0, s0, sys::kQuestFile);
                        a0 = 8;
                        lw(a1, v0, 272);
                        jal(ctx, 0x14FA00u, gen::fn_sub_3C7D80_003c7d80);
                        lw(a0, s0, sys::kPak);
                        a1 = 0;
                        a2 = addiu(sp, 0x1DC);
                        jal(ctx, 0x14FA14u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                        a0 = v0;
                        jal(ctx, 0x14FA20u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                        sw(v0, s0, sys::kFiles);
                        lw(a0, s0, sys::kPak);
                        a1 = 1;
                        a2 = addiu(sp, 0x1DC);
                        jal(ctx, 0x14FA38u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                        a0 = v0;
                        jal(ctx, 0x14FA44u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                        sw(v0, s0, sys::kFile1);
                        v0 = 2;
                        sw(v0, s0, sys::kState);
                    }
                }
            }
            goto L_00154748;
        case 0x14FA60u:  // table[2]: state 2: slide the menu in
            // 0x0014fa60
            charge(ctx, 5);
            lw(a0, s0, sys::kFiles);
            jal(ctx, 0x14FA64u, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x0014fa74
                charge(ctx, 5);
                lw(a0, s0, sys::kFile1);
                jal(ctx, 0x14FA78u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x0014fa88
                    charge(ctx, 26);
                    a0 = s0;
                    jal(ctx, 0x14FA8Cu, gen::fn_sub_14EF60_0014ef60);  // the system menu's slide-in
                    v0 = 0x423C0000;  // 47.0f
                    sw(v0, sp, 0x1C8);
                    v0 = lui(0xC160);
                    sw(v0, sp, 0x1CC);
                    v0 = 5;
                    sd(v0, sp, 0x0);
                    sd(v0, sp, 0x8);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    lw(a0, s0, sys::kMenuTweens);
                    a1 = 0;
                    a2 = 2;
                    a3 = 1;
                    ld(t0, sp, 0x1C8);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x14FAD8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    v0 = 3;
                    sw(v0, s0, sys::kState);
                }
            }
            goto L_00154748;
        case 0x14FAF0u:  // table[3]: state 3: the menu (input)
            // 0x0014faf0
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x0014fafc
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v1 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x0014fbd8
                    charge(ctx, 3);
                    v0 = v1 & 0x20;
                    if (v0 == 0) {
                        // 0x0014fc0c
                        charge(ctx, 6);
                        a0 = 1;
                        v0 = 0x7E0000;
                        lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                        v0 = v1 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x0014fc24
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x1000;  // cursor - 1
                            if (v0 == 0) {
                                // 0x0014fc38
                                charge(ctx, 1);
                                a0 = 0;
                            }
                        }
                        // 0x0014fc3c
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0014fd78
                            charge(ctx, 4);
                            v0 = v1 & 0x4000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x0014fd88
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x4000;  // cursor + 1
                                v0 = sltu(0, v0);
                            }
                            // 0x0014fd98
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x0014fda0
                                charge(ctx, 4);
                                jal(ctx, 0x14FDA0u, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
                                if (v0 == 0) {
                                    // 0x0014fe44
                                    charge(ctx, 4);
                                    lw(v1, s0, sys::kCursor);
                                    v0 = 5;
                                    if (v1 == v0) {
                                        // 0x0014fe80
                                        charge(ctx, 6);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        v0 = sltu(0, v0);
                                        if (v0 == 0) {
                                            // 0x0014fe98
                                            charge(ctx, 4);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                            v0 = v0 & 0x4000;  // cursor + 1
                                            v0 = sltu(0, v0);
                                        }
                                        // 0x0014fea8
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0014feb0
                                            charge(ctx, 7);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x14FEC0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            sw(zero, s0, sys::kCursor);
                                        }
                                    } else {
                                        // 0x0014fe54
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x14FE64u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, sys::kCursor);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, sys::kCursor);
                                    }
                                } else {
                                    // 0x0014fdb0
                                    charge(ctx, 4);
                                    lw(v1, s0, sys::kCursor);
                                    v0 = 5;
                                    if (v1 == v0) {
                                        // 0x0014fdec
                                        charge(ctx, 6);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        v0 = sltu(0, v0);
                                        if (v0 == 0) {
                                            // 0x0014fe04
                                            charge(ctx, 4);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                            v0 = v0 & 0x4000;  // cursor + 1
                                            v0 = sltu(0, v0);
                                        }
                                        // 0x0014fe14
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x0014fe1c
                                            charge(ctx, 10);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x14FE2Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            v0 = 4;
                                            sw(v0, s0, sys::kCursor);
                                        }
                                    } else {
                                        // 0x0014fdc0
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x14FDD0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, sys::kCursor);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, sys::kCursor);
                                    }
                                }
                            }
                        } else {
                            // 0x0014fc44
                            charge(ctx, 4);
                            jal(ctx, 0x14FC44u, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
                            if (v0 == 0) {
                                // 0x0014fce8
                                charge(ctx, 3);
                                lw(v0, s0, sys::kCursor);
                                if (v0 == 0) {
                                    // 0x0014fd20
                                    charge(ctx, 6);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                                    v0 = v0 & 0x1000;  // cursor - 1
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0014fd38
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x1000;  // cursor - 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0014fd48
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0014fd50
                                        charge(ctx, 10);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x14FD60u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        v0 = 5;
                                        sw(v0, s0, sys::kCursor);
                                    }
                                } else {
                                    // 0x0014fcf4
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x14FD04u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, sys::kCursor);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s0, sys::kCursor);
                                }
                            } else {
                                // 0x0014fc54
                                charge(ctx, 4);
                                lw(v1, s0, sys::kCursor);
                                v0 = 4;
                                if (v1 == v0) {
                                    // 0x0014fc90
                                    charge(ctx, 6);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                                    v0 = v0 & 0x1000;  // cursor - 1
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0014fca8
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x1000;  // cursor - 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0014fcb8
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0014fcc0
                                        charge(ctx, 10);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x14FCD0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        v0 = 5;
                                        sw(v0, s0, sys::kCursor);
                                    }
                                } else {
                                    // 0x0014fc64
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x14FC74u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, sys::kCursor);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s0, sys::kCursor);
                                }
                            }
                        }
                    } else {
                        // 0x0014fbe4
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x14FBF4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 4;
                        sw(v0, s0, sys::kState);
                    }
                } else {
                    // 0x0014fb10
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x14FB20u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    lw(v0, s0, sys::kCursor);
                    at = sltiu(v0, 6);
                    if (at != 0) {
                        // 0x0014fb38
                        charge(ctx, 7);
                        v1 = 0x7B0000;
                        v1 = addiu(v1, 24768);  // &0x7B60C0
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x14FB54u:  // table[0]: entry 0: the calendar (state 26)
                            // 0x0014fb54
                            charge(ctx, 4);
                            v0 = 26;
                            sw(v0, s0, sys::kState);
                            break;
                        case 0x14FB64u:  // table[1]: entry 1: the request list (21)
                            // 0x0014fb64
                            charge(ctx, 4);
                            v0 = 21;
                            sw(v0, s0, sys::kState);
                            break;
                        case 0x14FB74u:  // table[2]: entry 2: the fusion-spell list (16)
                            // 0x0014fb74
                            charge(ctx, 4);
                            v0 = 16;
                            sw(v0, s0, sys::kState);
                            break;
                        case 0x14FB84u:  // table[3]: entry 3: the help list (11)
                            // 0x0014fb84
                            charge(ctx, 4);
                            v0 = 11;
                            sw(v0, s0, sys::kState);
                            break;
                        case 0x14FB94u:  // table[4]: entry 4: config (6)
                            // 0x0014fb94
                            charge(ctx, 4);
                            v0 = 6;
                            sw(v0, s0, sys::kState);
                            break;
                        case 0x14FBA4u:  // table[5]: entry 5: return to the title (message 7, 31)
                            // 0x0014fba4
                            charge(ctx, 13);
                            a0 = 7;
                            jal(ctx, 0x14FBA8u, gen::fn_msgWinRequestMessage_003c7430);
                            a0 = 0;
                            jal(ctx, 0x14FBB4u, gen::fn_sub_3C74E0_003c74e0);
                            a0 = 1;
                            jal(ctx, 0x14FBC0u, gen::fn_msgWinSetType_003c7560);
                            v0 = 31;
                            sw(v0, s0, sys::kState);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                }
                // 0x0014fecc
                charge(ctx, 39);
                v0 = 590;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x1C8);
                lw(v1, s0, sys::kCursor);
                v0 = sll(v1, 5);
                v0 = addu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42F80000;  // 124.0f
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x1CC);
                ld(v0, sp, 0x1C8);
                sd(v0, sp, 0x1C0);
                lwc1(f1, sp, 0x1C4);
                v0 = 0x43960000;  // 300.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, sp, 0x1C4);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                lw(v1, s0, sys::kMenuTweens);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a0 = addiu(v1, 136);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x1C0);
                ld(t1, sp, 0x1C8);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x14FF60u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            }
            // 0x0014ff68
            charge(ctx, 9);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x14FF78u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            sw(v0, s0, sys::kArrived);
            goto L_00154748;
        case 0x14FF8Cu:  // table[31]: state 31: quit: message 7 (yes / no)
            // 0x0014ff8c
            charge(ctx, 10);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x14FF9Cu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            jal(ctx, 0x14FFA4u, gen::fn_sub_3C7850_003c7850);  // message window done?
            if (v0 == 0) {
                // 0x0014ffb4
                charge(ctx, 4);
                jal(ctx, 0x14FFB4u, gen::fn_msgWinLastSelection_003c7610);
                if (v0 == 0) {
                    // 0x0014ffcc
                    charge(ctx, 4);
                    v0 = 32;
                    sw(v0, s0, sys::kState);
                } else {
                    // 0x0014ffc4
                    charge(ctx, 2);
                    // 0x0014ffdc
                    charge(ctx, 2);
                    v0 = 3;
                    sw(v0, s0, sys::kState);
                }
                // 0x0014ffe4
                charge(ctx, 4);
                jal(ctx, 0x14FFE4u, gen::fn_sub_3C7700_003c7700);  // close the message window
            }
            goto L_00154748;
        case 0x14FFF4u:  // table[32]: state 32: quit: flag 5149
            // 0x0014fff4
            charge(ctx, 15);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x150004u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            sw(zero, s0, sys::kQuitFade);
            a0 = 5149;
            a1 = 1;
            jal(ctx, 0x150018u, gen::fn_datSetFlag_0016f1f0);
            v0 = 33;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x150030u:  // table[33]: state 33: quit: fade, to the title
            // 0x00150030
            charge(ctx, 28);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x150040u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            lw(v1, s0, sys::kQuitFade);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            mtc1(zero, f12);
            v0 = 0xF1F0000;
            v0 = v0 | 0x2800;
            a0 = v1 | v0;
            mov_s(f13, f12);
            mov_s(f14, f12);
            a1 = 640;
            a2 = 448;
            jal(ctx, 0x150080u, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
            lw(v0, s0, sys::kQuitFade);
            v0 = addiu(v0, 1);
            sw(v0, s0, sys::kQuitFade);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x001500a0
                charge(ctx, 8);
                v0 = 10;
                sw(v0, s0, sys::kQuitFade);
                jal(ctx, 0x1500A8u, gen::fn_sub_17F990_0017f990);
                jal(ctx, 0x1500B0u, gen::fn_sub_1BA8D0_001ba8d0);
            }
            goto L_00154748;
        case 0x1500C0u:  // table[4]: state 4: slide out
            // 0x001500c0
            charge(ctx, 201);
            lw(a0, s0, sys::kMenuTweens);
            lwc1(f1, a0, 48);
            lwc1(f0, a0, 52);
            swc1(f1, sp, 0x1C8);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150104u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 590;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            lw(v1, s0, sys::kCursor);
            v0 = sll(v1, 5);
            v0 = addu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42F80000;  // 124.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150184u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C50000;  // 394.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42FA0000;  // 125.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1501D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C90000;  // 402.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42FC0000;  // 126.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150224u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 321;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x41700000;  // 15.0f
            sw(v0, sp, 0x1CC);
            lw(v0, s0, sys::kMenuTweens);
            sw(zero, v0, 336);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150288u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 355;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42F80000;  // 124.0f
            sw(v0, sp, 0x1CC);
            lw(v0, s0, sys::kMenuTweens);
            sw(zero, v0, 404);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1502ECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x423C0000;  // 47.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            lw(v0, s0, sys::kMenuTweens);
            sw(zero, v0, 404);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150350u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C40000;  // 392.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            lw(v0, s0, sys::kMenuTweens);
            sw(zero, v0, 404);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kMenuTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1503B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x1503CCu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            v0 = 5;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x1503E4u:  // table[5]: state 5: done (-1)
            // 0x001503e4
            charge(ctx, 8);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x1503F4u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            if (v0 == 0) {
                // 0x00150410
                charge(ctx, 7);
                lw(v0, s0, sys::kMenuTweens);
                lwc1(f1, v0, 48);
                lwc1(f0, v0, 52);
                swc1(f1, v0, 40);
                swc1(f0, v0, 44);
                goto L_00154748;
            }
            // 0x00150404
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x15042Cu:  // table[6]: state 6: config: slide in, read flags 387..
            // 0x0015042c
            charge(ctx, 192);
            sw(zero, s0, sys::kConfigCursor);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x150440u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            a0 = s0;
            jal(ctx, 0x15044Cu, gen::fn_sub_14F320_0014f320);  // the system menu's slide-out
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43570000;  // 215.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x70);
            lwc1(f1, sp, 0x74);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x74);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x70);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1504B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43830000;  // 262.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x78);
            lwc1(f1, sp, 0x7C);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x7C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x78);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150528u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150578u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x80);
            lwc1(f1, sp, 0x84);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x84);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x80);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1505E8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150638u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x88);
            lwc1(f1, sp, 0x8C);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x8C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x88);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1506A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42BE0000;  // 95.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x90);
            lwc1(f1, sp, 0x90);
            v0 = 0x43480000;  // 200.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x90);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x90);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150718u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            s1 = 0;
            for (;;) {
                // 0x00150748
                charge(ctx, 3);
                v0 = slti(s1, 7);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015072c
                charge(ctx, 7);
                a0 = addiu(s1, 387);
                jal(ctx, 0x150730u, gen::fn_datGetFlag_0016f190);
                v1 = sll(s1, 2);
                v1 = addu(s0, v1);
                sw(v0, v1, 344);
                s1 = addiu(s1, 1);
            }
            // 0x00150754
            charge(ctx, 28);
            v0 = 0x43C40000;  // 392.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1507A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, s0, sys::kArrived);
            v0 = 7;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x1507C4u:  // table[7]: state 7: config arrived
            // 0x001507c4
            charge(ctx, 8);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x1507D4u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            if (v0 != 0) {
                // 0x001507e4
                charge(ctx, 2);
                v0 = 8;
                sw(v0, s0, sys::kState);
            }
            // 0x001507ec
            charge(ctx, 8);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kConfigCursor);
            a3 = addiu(s0, sys::kConfigValues);
            jal(ctx, 0x1507FCu, gen::fn_sub_156140_00156140);  // the config page's tweens (sub_155830)
            goto L_00154748;
        case 0x15080Cu:  // table[8]: state 8: config (input; write the flags)
            // 0x0015080c
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x00150818
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a0 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x00150904
                    charge(ctx, 3);
                    v0 = a0 & 0x20;
                    if (v0 == 0) {
                        // 0x00150938
                        charge(ctx, 6);
                        a1 = 1;
                        v0 = 0x7E0000;
                        lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                        v0 = v1 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x00150950
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x1000;  // cursor - 1
                            if (v0 == 0) {
                                // 0x00150964
                                charge(ctx, 1);
                                a1 = 0;
                            }
                        }
                        // 0x00150968
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x001509f8
                            charge(ctx, 4);
                            v0 = v1 & 0x4000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x00150a08
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x4000;  // cursor + 1
                                v0 = sltu(0, v0);
                            }
                            // 0x00150a18
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x00150aa8
                                charge(ctx, 4);
                                v0 = a0 & 0x2000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x00150ab8
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x2000;  // next page
                                    v0 = sltu(0, v0);
                                }
                                // 0x00150ac8
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x00150b24
                                    charge(ctx, 4);
                                    v0 = a0 & 0x8000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x00150b34
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x8000;  // previous page
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x00150b44
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00150b4c
                                        charge(ctx, 4);
                                        lw(v1, s0, sys::kConfigCursor);
                                        v0 = 7;
                                        if (v1 != v0) {
                                            // 0x00150b5c
                                            charge(ctx, 5);
                                            v0 = sll(v1, 2);
                                            v0 = addu(v0, s0);
                                            lw(v0, v0, 344);
                                            if (v0 == 0) {
                                                // 0x00150b70
                                                charge(ctx, 6);
                                                a0 = 0;
                                                a1 = 0;
                                                a2 = 0;
                                                a3 = 5;
                                                jal(ctx, 0x150B80u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            }
                                            // 0x00150b88
                                            charge(ctx, 3);
                                            lw(v0, s0, sys::kConfigCursor);
                                            if (v0 == 0) {
                                                // 0x00150b94
                                                charge(ctx, 3);
                                                lw(v0, s0, sys::kConfigValues);
                                                if (v0 == 0) {
                                                    // 0x00150ba0
                                                    charge(ctx, 6);
                                                    a0 = 10;
                                                    a1 = 150;
                                                    a2 = a0;
                                                    a3 = 0;
                                                    jal(ctx, 0x150BB0u, gen::fn_sub_103C30_00103c30);
                                                }
                                            }
                                            // 0x00150bb8
                                            charge(ctx, 5);
                                            v1 = 1;
                                            lw(v0, s0, sys::kConfigCursor);
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, s0);
                                            sw(v1, v0, 344);
                                        }
                                    }
                                } else {
                                    // 0x00150ad0
                                    charge(ctx, 4);
                                    lw(v1, s0, sys::kConfigCursor);
                                    v0 = 7;
                                    if (v1 != v0) {
                                        // 0x00150ae0
                                        charge(ctx, 5);
                                        v0 = sll(v1, 2);
                                        v0 = addu(v0, s0);
                                        lw(v0, v0, 344);
                                        if (v0 != 0) {
                                            // 0x00150af4
                                            charge(ctx, 12);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 5;
                                            jal(ctx, 0x150B04u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            lw(v0, s0, sys::kConfigCursor);
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, s0);
                                            sw(zero, v0, 344);
                                        }
                                    }
                                }
                            } else {
                                // 0x00150a20
                                charge(ctx, 4);
                                lw(v1, s0, sys::kConfigCursor);
                                v0 = 7;
                                if (v1 == v0) {
                                    // 0x00150a5c
                                    charge(ctx, 4);
                                    v0 = a0 & 0x4000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x00150a6c
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x00150a7c
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x00150a84
                                        charge(ctx, 9);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x150A94u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        sw(zero, s0, sys::kConfigCursor);
                                    }
                                } else {
                                    // 0x00150a30
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x150A40u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, sys::kConfigCursor);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, sys::kConfigCursor);
                                }
                            }
                        } else {
                            // 0x00150970
                            charge(ctx, 3);
                            lw(v0, s0, sys::kConfigCursor);
                            if (v0 == 0) {
                                // 0x001509a8
                                charge(ctx, 4);
                                v0 = a0 & 0x1000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x001509b8
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x1000;  // cursor - 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x001509c8
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x001509d0
                                    charge(ctx, 10);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x1509E0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    v0 = 7;
                                    sw(v0, s0, sys::kConfigCursor);
                                }
                            } else {
                                // 0x0015097c
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x15098Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, sys::kConfigCursor);
                                v0 = addiu(v0, -1);
                                sw(v0, s0, sys::kConfigCursor);
                            }
                        }
                    } else {
                        // 0x00150910
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x150920u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 9;
                        sw(v0, s0, sys::kState);
                    }
                } else {
                    // 0x0015082c
                    charge(ctx, 4);
                    lw(v1, s0, sys::kConfigCursor);
                    v0 = 7;
                    if (v1 == v0) {
                        // 0x0015083c
                        charge(ctx, 9);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x15084Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        s1 = 0;
                        for (;;) {
                            // 0x001508cc
                            charge(ctx, 3);
                            v0 = slti(s1, 7);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00150860
                            charge(ctx, 3);
                            v0 = 2;
                            if (s1 != v0) {
                                // 0x001508b0
                                charge(ctx, 6);
                                a0 = addiu(s1, 387);
                                v0 = sll(s1, 2);
                                v0 = addu(s0, v0);
                                lw(a1, v0, 344);
                                jal(ctx, 0x1508C0u, gen::fn_datSetFlag_0016f1f0);
                            } else {
                                // 0x0015086c
                                charge(ctx, 3);
                                lw(v0, s0, 348);
                                if (v0 != 0) {
                                    // 0x00150890
                                    charge(ctx, 8);
                                    a0 = addiu(s1, 387);
                                    v0 = sll(s1, 2);
                                    v0 = addu(s0, v0);
                                    lw(a1, v0, 344);
                                    jal(ctx, 0x1508A0u, gen::fn_datSetFlag_0016f1f0);
                                } else {
                                    // 0x00150878
                                    charge(ctx, 6);
                                    a0 = addiu(s1, 387);
                                    a1 = 0;
                                    jal(ctx, 0x150880u, gen::fn_datSetFlag_0016f1f0);
                                }
                            }
                            // 0x001508c8
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x001508d8
                        charge(ctx, 5);
                        a0 = 387;
                        jal(ctx, 0x1508DCu, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            // 0x001508ec
                            charge(ctx, 2);
                            jal(ctx, 0x1508ECu, gen::fn_sub_103CB0_00103cb0);
                        }
                        // 0x001508f4
                        charge(ctx, 4);
                        v0 = 9;
                        sw(v0, s0, sys::kState);
                    }
                }
            }
            // 0x00150bcc
            charge(ctx, 9);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kConfigCursor);
            a3 = addiu(s0, sys::kConfigValues);
            jal(ctx, 0x150BDCu, gen::fn_sub_156140_00156140);  // the config page's tweens (sub_155830)
            sw(v0, s0, sys::kArrived);
            goto L_00154748;
        case 0x150BF0u:  // table[9]: state 9: config out
            // 0x00150bf0
            charge(ctx, 202);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kConfigCursor);
            a3 = addiu(s0, sys::kConfigValues);
            jal(ctx, 0x150C00u, gen::fn_sub_156140_00156140);  // the config page's tweens (sub_155830)
            a0 = s0;
            jal(ctx, 0x150C0Cu, gen::fn_sub_14EF60_0014ef60);  // the system menu's slide-in
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43570000;  // 215.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x98);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150C74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43830000;  // 262.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0xA0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150CE0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150D30u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0xA8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150D9Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150DECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B80000;  // 92.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0xB0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150E58u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42BE0000;  // 95.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150EA8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v1 = 10;
            sw(v1, s0, sys::kState);
            v0 = 0x43C40000;  // 392.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            sd(v1, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x150F08u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            goto L_00154748;
        case 0x150F18u:  // table[10]: state 10: back to the menu
            // 0x00150f18
            charge(ctx, 8);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kConfigCursor);
            a3 = addiu(s0, sys::kConfigValues);
            jal(ctx, 0x150F28u, gen::fn_sub_156140_00156140);  // the config page's tweens (sub_155830)
            if (v0 != 0) {
                // 0x00150f38
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s0, sys::kState);
            }
            // 0x00150f40
            charge(ctx, 8);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x150F50u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            goto L_00154748;
        case 0x150F60u:  // table[11]: state 11: help list: slide in (flags 656..)
            // 0x00150f60
            charge(ctx, 15);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x150F70u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            a0 = s0;
            jal(ctx, 0x150F7Cu, gen::fn_sub_14F320_0014f320);  // the system menu's slide-out
            sw(zero, s0, 316);
            sw(zero, s0, 312);
            s2 = 0;
            s1 = 0;
            for (;;) {
                // 0x00150fc4
                charge(ctx, 3);
                v0 = slti(s1, 64);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00150f9c
                charge(ctx, 5);
                a0 = addiu(s1, 656);
                jal(ctx, 0x150FA0u, gen::fn_datGetFlag_0016f190);
                if (v0 != 0) {
                    // 0x00150fb0
                    charge(ctx, 4);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    sw(s1, v0, 52);
                    s2 = addiu(s2, 1);
                }
                // 0x00150fc0
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00150fd0
            charge(ctx, 219);
            sw(s2, s0, 308);
            sw(zero, s0, 316);
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42840000;  // 66.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xB8);
            lwc1(f0, sp, 0xB8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0xB8);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xB8);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151034u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42C00000;  // 96.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151084u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42040000;  // 33.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43060000;  // 134.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1510D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 305;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 341;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xC0);
            lwc1(f1, sp, 0xC4);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xC4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC0);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15115Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(v1, s0, 316);
            v0 = sll(v1, 3);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 599;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xC8);
            lwc1(f1, sp, 0xCC);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xCC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xC8);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1511FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 355;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42BE0000;  // 95.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xD0);
            lwc1(f1, sp, 0xD0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xD0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xD0);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151278u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x44190000;  // 612.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43830000;  // 262.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1512C8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151324u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 12;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x15133Cu:  // table[12]: state 12: arrived
            // 0x0015133c
            charge(ctx, 8);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x15134Cu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            if (v0 != 0) {
                // 0x0015135c
                charge(ctx, 2);
                v0 = 13;
                sw(v0, s0, sys::kState);
            }
            // 0x00151364
            charge(ctx, 11);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            a2 = addiu(s0, 52);
            lw(a3, s0, 308);
            lw(t0, s0, 312);
            lw(t1, s0, 316);
            jal(ctx, 0x15137Cu, gen::fn_sub_155710_00155710);  // the help list's tweens (sub_155070)
            sw(zero, s0, sys::kArrived);
            goto L_00154748;
        case 0x151390u:  // table[13]: state 13: help list (input)
            // 0x00151390
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x0015139c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(a3, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a3 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x001513d8
                    charge(ctx, 6);
                    a0 = 1;
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                    v0 = v1 & 0x1000;  // cursor - 1
                    if (v0 == 0) {
                        // 0x001513f0
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                        v0 = v0 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x00151404
                            charge(ctx, 1);
                            a0 = 0;
                        }
                    }
                    // 0x00151408
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00151544
                        charge(ctx, 4);
                        v0 = v1 & 0x4000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x00151554
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x4000;  // cursor + 1
                            v0 = sltu(0, v0);
                        }
                        // 0x00151564
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x0015156c
                            charge(ctx, 7);
                            lw(a2, s0, 316);
                            lw(a1, s0, 312);
                            lw(a0, s0, 308);
                            v0 = addu(a1, a2);
                            v0 = addiu(v0, 1);
                            if (a0 != v0) {
                                // 0x001515d8
                                charge(ctx, 3);
                                v0 = 6;
                                if (a2 == v0) {
                                    // 0x001515e4
                                    charge(ctx, 5);
                                    v1 = addiu(a0, -1);
                                    v0 = addiu(a1, 7);
                                    at = slt(v0, v1);
                                    if (at == 0) {
                                        goto L_00151624;
                                    }
                                    // 0x001515f8
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x151608u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, 312);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, 312);
                                    goto L_00151664;
                                }
                            L_00151624:
                                charge(ctx, 3);
                                v0 = 7;
                                if (a2 != v0) {
                                    // 0x00151630
                                    charge(ctx, 4);
                                    v0 = addiu(a0, -1);
                                    at = slt(a2, v0);
                                    if (at != 0) {
                                        // 0x00151640
                                        charge(ctx, 9);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x151650u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, 316);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, 316);
                                    }
                                }
                            } else {
                                // 0x00151588
                                charge(ctx, 4);
                                v0 = a3 & 0x4000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x00151598
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x4000;  // cursor + 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x001515a8
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x001515b0
                                    charge(ctx, 10);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x1515C0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    sw(zero, s0, 316);
                                    sw(zero, s0, 312);
                                }
                            }
                        }
                    } else {
                        // 0x00151410
                        charge(ctx, 3);
                        lw(v1, s0, 316);
                        if (v1 == 0) {
                            // 0x0015141c
                            charge(ctx, 3);
                            lw(v0, s0, 312);
                            if (v0 != 0) {
                                goto L_001514cc;
                            }
                            // 0x00151428
                            charge(ctx, 4);
                            v0 = a3 & 0x1000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x00151438
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                v0 = v0 & 0x1000;  // cursor - 1
                                v0 = sltu(0, v0);
                            }
                            // 0x00151448
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00151450
                                charge(ctx, 3);
                                lw(v0, s0, 308);
                                if (v0 != 0) {
                                    // 0x0015145c
                                    charge(ctx, 3);
                                    at = slti(v0, 8);
                                    if (at == 0) {
                                        // 0x00151498
                                        charge(ctx, 13);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x1514A8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        v0 = 7;
                                        sw(v0, s0, 316);
                                        lw(v0, s0, 308);
                                        v0 = addiu(v0, -8);
                                        sw(v0, s0, 312);
                                    } else {
                                        // 0x00151468
                                        charge(ctx, 12);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x151478u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, 308);
                                        v0 = addiu(v0, -1);
                                        sw(v0, s0, 316);
                                        sw(zero, s0, 312);
                                    }
                                }
                            }
                            goto L_00151664;
                        }
                    L_001514cc:
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 == v0) {
                            // 0x001514d8
                            charge(ctx, 3);
                            lw(v0, s0, 312);
                            if (v0 == 0) {
                                goto L_00151510;
                            }
                            // 0x001514e4
                            charge(ctx, 11);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x1514F4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s0, 312);
                            v0 = addiu(v0, -1);
                            sw(v0, s0, 312);
                            goto L_00151664;
                        }
                    L_00151510:
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x00151518
                            charge(ctx, 11);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x151528u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s0, 316);
                            v0 = addiu(v0, -1);
                            sw(v0, s0, 316);
                        }
                    }
                } else {
                    // 0x001513b0
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x1513C0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 14;
                    sw(v0, s0, sys::kState);
                }
            }
        L_00151664:
            charge(ctx, 11);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            a2 = addiu(s0, 52);
            lw(a3, s0, 308);
            lw(t0, s0, 312);
            lw(t1, s0, 316);
            jal(ctx, 0x15167Cu, gen::fn_sub_155710_00155710);  // the help list's tweens (sub_155070)
            sw(v0, s0, sys::kArrived);
            goto L_00154748;
        case 0x151690u:  // table[14]: state 14: out
            // 0x00151690
            charge(ctx, 204);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            a2 = addiu(s0, 52);
            lw(a3, s0, 308);
            lw(t0, s0, 312);
            lw(t1, s0, 316);
            jal(ctx, 0x1516A8u, gen::fn_sub_155710_00155710);  // the help list's tweens (sub_155070)
            a0 = s0;
            jal(ctx, 0x1516B4u, gen::fn_sub_14EF60_0014ef60);  // the system menu's slide-in
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42840000;  // 66.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151700u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42C00000;  // 96.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151750u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42040000;  // 33.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43060000;  // 134.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1517A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 305;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 341;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0xD8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151820u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(v1, s0, 316);
            v0 = sll(v1, 3);
            v1 = subu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 599;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1518A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 355;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42BE0000;  // 95.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1518FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x44190000;  // 612.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43830000;  // 262.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15194Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1519A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 15;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x1519C0u:  // table[15]: state 15: back to the menu
            // 0x001519c0
            charge(ctx, 10);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            a2 = addiu(s0, 52);
            lw(a3, s0, 308);
            lw(t0, s0, 312);
            lw(t1, s0, 316);
            jal(ctx, 0x1519D8u, gen::fn_sub_155710_00155710);  // the help list's tweens (sub_155070)
            if (v0 != 0) {
                // 0x001519e8
                charge(ctx, 3);
                sw(zero, s0, sys::kArrived);
                v0 = 3;
                sw(v0, s0, sys::kState);
            }
            // 0x001519f4
            charge(ctx, 8);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x151A04u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            goto L_00154748;
        case 0x151A14u:  // table[16]: state 16: fusion-spell list: slide in
            // 0x00151a14
            charge(ctx, 213);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x151A24u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            a0 = s0;
            jal(ctx, 0x151A30u, gen::fn_sub_14F320_0014f320);  // the system menu's slide-out
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42840000;  // 66.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xE0);
            lwc1(f1, sp, 0xE0);
            v0 = 0x43480000;  // 200.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xE0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xE0);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151A9Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42040000;  // 33.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B40000;  // 90.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151AECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42040000;  // 33.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x433B0000;  // 187.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151B3Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x439A0000;  // 308.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43B80000;  // 368.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xE8);
            lwc1(f1, sp, 0xEC);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xEC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xE8);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151BACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 341;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151C08u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 599;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xF0);
            lwc1(f1, sp, 0xF4);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xF4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xF0);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151C84u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B00000;  // 352.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42AC0000;  // 86.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0xF8);
            lwc1(f1, sp, 0xF8);
            v0 = 0x43480000;  // 200.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xF8);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xF8);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151CF4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x151D50u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 17;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x151D68u:  // table[17]: state 17: arrived
            // 0x00151d68
            charge(ctx, 8);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x151D78u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            if (v0 != 0) {
                // 0x00151d88
                charge(ctx, 2);
                v0 = 18;
                sw(v0, s0, sys::kState);
            }
            // 0x00151d90
            charge(ctx, 9);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kSpellScroll);
            lw(a3, s0, sys::kSpellCursor);
            jal(ctx, 0x151DA0u, gen::fn_sub_156E80_00156e80);  // the fusion-spell list's tweens (sub_156240)
            sw(zero, s0, sys::kArrived);
            goto L_00154748;
        case 0x151DB4u:  // table[18]: state 18: fusion-spell list (input)
            // 0x00151db4
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x00151dc0
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v1 = v0 & 0x20;  // cancel
                if (v1 == 0) {
                    // 0x00151dfc
                    charge(ctx, 6);
                    a1 = 1;
                    v1 = 0x7E0000;
                    lhu(a0, v1, 2386);  // 0x7E0952
                    v1 = a0 & 0x1000;
                    if (v1 == 0) {
                        // 0x00151e14
                        charge(ctx, 5);
                        v1 = 0x7E0000;
                        lhu(v1, v1, 2394);  // 0x7E095A
                        v1 = v1 & 0x1000;
                        if (v1 == 0) {
                            // 0x00151e28
                            charge(ctx, 1);
                            a1 = 0;
                        }
                    }
                    // 0x00151e2c
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x00151f0c
                        charge(ctx, 4);
                        v1 = a0 & 0x4000;
                        v1 = sltu(0, v1);
                        if (v1 == 0) {
                            // 0x00151f1c
                            charge(ctx, 4);
                            v1 = 0x7E0000;
                            lhu(v1, v1, 2394);  // 0x7E095A
                            v1 = v1 & 0x4000;
                            v1 = sltu(0, v1);
                        }
                        // 0x00151f2c
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x00151f34
                            charge(ctx, 4);
                            lw(a0, s0, sys::kSpellScroll);
                            v1 = 10;
                            if (a0 != v1) {
                                // 0x00151f44
                                charge(ctx, 4);
                                lw(a0, s0, sys::kSpellCursor);
                                v1 = 6;
                                if (a0 != v1) {
                                    goto L_00151f80;
                                }
                                // 0x00151f54
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x151F64u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, sys::kSpellScroll);
                                v0 = addiu(v0, 1);
                                sw(v0, s0, sys::kSpellScroll);
                                goto L_00152004;
                            }
                        L_00151f80:
                            charge(ctx, 4);
                            lw(a0, s0, sys::kSpellCursor);
                            v1 = 7;
                            if (a0 == v1) {
                                // 0x00151fbc
                                charge(ctx, 4);
                                v0 = v0 & 0x4000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x00151fcc
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x4000;  // cursor + 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x00151fdc
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x00151fe4
                                    charge(ctx, 8);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x151FF4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    sw(zero, s0, sys::kSpellScroll);
                                    sw(zero, s0, sys::kSpellCursor);
                                }
                            } else {
                                // 0x00151f90
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x151FA0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, sys::kSpellCursor);
                                v0 = addiu(v0, 1);
                                sw(v0, s0, sys::kSpellCursor);
                            }
                        }
                    } else {
                        // 0x00151e34
                        charge(ctx, 3);
                        lw(v1, s0, sys::kSpellScroll);
                        if (v1 != 0) {
                            // 0x00151e40
                            charge(ctx, 4);
                            lw(a0, s0, sys::kSpellCursor);
                            v1 = 1;
                            if (a0 != v1) {
                                goto L_00151e7c;
                            }
                            // 0x00151e50
                            charge(ctx, 11);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x151E60u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s0, sys::kSpellScroll);
                            v0 = addiu(v0, -1);
                            sw(v0, s0, sys::kSpellScroll);
                            goto L_00152004;
                        }
                    L_00151e7c:
                        charge(ctx, 3);
                        lw(v1, s0, sys::kSpellCursor);
                        if (v1 == 0) {
                            // 0x00151eb4
                            charge(ctx, 4);
                            v0 = v0 & 0x1000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x00151ec4
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                v0 = v0 & 0x1000;  // cursor - 1
                                v0 = sltu(0, v0);
                            }
                            // 0x00151ed4
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00151edc
                                charge(ctx, 12);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x151EECu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                v0 = 7;
                                sw(v0, s0, sys::kSpellCursor);
                                v0 = 10;
                                sw(v0, s0, sys::kSpellScroll);
                            }
                        } else {
                            // 0x00151e88
                            charge(ctx, 11);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x151E98u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s0, sys::kSpellCursor);
                            v0 = addiu(v0, -1);
                            sw(v0, s0, sys::kSpellCursor);
                        }
                    }
                } else {
                    // 0x00151dd4
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x151DE4u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 19;
                    sw(v0, s0, sys::kState);
                }
            }
        L_00152004:
            charge(ctx, 9);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kSpellScroll);
            lw(a3, s0, sys::kSpellCursor);
            jal(ctx, 0x152014u, gen::fn_sub_156E80_00156e80);  // the fusion-spell list's tweens (sub_156240)
            sw(v0, s0, sys::kArrived);
            goto L_00154748;
        case 0x152028u:  // table[19]: state 19: out
            // 0x00152028
            charge(ctx, 194);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x152038u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kSpellScroll);
            lw(a3, s0, sys::kSpellCursor);
            jal(ctx, 0x152050u, gen::fn_sub_156E80_00156e80);  // the fusion-spell list's tweens (sub_156240)
            a0 = s0;
            jal(ctx, 0x15205Cu, gen::fn_sub_14EF60_0014ef60);  // the system menu's slide-in
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42840000;  // 66.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1520A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42040000;  // 33.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42B40000;  // 90.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1520F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42040000;  // 33.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x433B0000;  // 187.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152148u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x439A0000;  // 308.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43B80000;  // 368.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x100);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1521B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 341;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152210u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 599;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15226Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43B00000;  // 352.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42AC0000;  // 86.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1522BCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152318u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 20;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x152330u:  // table[20]: state 20: back to the menu
            // 0x00152330
            charge(ctx, 14);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x152340u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kSpellScroll);
            lw(a3, s0, sys::kSpellCursor);
            jal(ctx, 0x152358u, gen::fn_sub_156E80_00156e80);  // the fusion-spell list's tweens (sub_156240)
            if (v0 != 0) {
                // 0x00152368
                charge(ctx, 5);
                sw(zero, s0, sys::kArrived);
                v0 = 3;
                sw(v0, s0, sys::kState);
            }
            goto L_00154748;
        case 0x15237Cu:  // table[21]: state 21: request list: slide in
            // 0x0015237c
            charge(ctx, 398);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x15238Cu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            sw(zero, s0, sys::kQuestCursor);
            a0 = s0;
            jal(ctx, 0x15239Cu, gen::fn_sub_14F320_0014f320);  // the system menu's slide-out
            v0 = 0x41B00000;  // 22.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43460000;  // 198.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x108);
            lwc1(f1, sp, 0x10C);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x10C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x108);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152408u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41C80000;  // 25.0f
            sw(v0, sp, 0x1C8);
            v0 = 369;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x110);
            lwc1(f1, sp, 0x114);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x114);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x110);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152484u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x1C8);
            v0 = 0x42440000;  // 49.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 3;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1524D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42740000;  // 61.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42240000;  // 41.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x118);
            lwc1(f1, sp, 0x118);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x118);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x118);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152540u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43880000;  // 272.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42240000;  // 41.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x120);
            lwc1(f1, sp, 0x120);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x120);
            a2 = 2;
            sd(a2, sp, 0x0);
            v0 = 12;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a3 = 1;
            ld(t0, sp, 0x120);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1525B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 553;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42240000;  // 41.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x128);
            lwc1(f1, sp, 0x128);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x128);
            v0 = 4;
            sd(v0, sp, 0x0);
            v0 = 14;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x128);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152630u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42480000;  // 50.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152680u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x130);
            lwc1(f1, sp, 0x134);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x134);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x130);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1526F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42D80000;  // 108.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x138);
            lwc1(f1, sp, 0x138);
            v0 = 0x43480000;  // 200.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x138);
            v0 = 5;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x138);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152764u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42480000;  // 50.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43790000;  // 249.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 612);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1527B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43800000;  // 256.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 680);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152804u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 619;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 329;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x140);
            lwc1(f1, sp, 0x144);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x144);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 748);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x140);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15288Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x426C0000;  // 59.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43AA0000;  // 340.0f
            sw(v0, sp, 0x1CC);
            v0 = 10;
            sd(v0, sp, 0x0);
            v0 = 15;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 816);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1528E0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42EE0000;  // 119.0f
            sw(v0, sp, 0x1C8);
            v0 = 333;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            v0 = 13;
            sd(v0, sp, 0x0);
            v0 = 17;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 884);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152940u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15299Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 22;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x1529B4u:  // table[22]: state 22: arrived
            // 0x001529b4
            charge(ctx, 13);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kQuestCursor);
            jal(ctx, 0x1529C0u, gen::fn_sub_159900_00159900);  // the request list's tweens (sub_156F80)
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x1529D8u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            if (v0 != 0) {
                // 0x001529e8
                charge(ctx, 5);
                sw(zero, s0, sys::kArrived);
                v0 = 23;
                sw(v0, s0, sys::kState);
            }
            goto L_00154748;
        case 0x1529FCu:  // table[23]: state 23: request list (input)
            // 0x001529fc
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x00152a08
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a0 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x00152a44
                    charge(ctx, 6);
                    a1 = 1;
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                    v0 = v1 & 0x1000;  // cursor - 1
                    if (v0 == 0) {
                        // 0x00152a5c
                        charge(ctx, 5);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                        v0 = v0 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x00152a70
                            charge(ctx, 1);
                            a1 = 0;
                        }
                    }
                    // 0x00152a74
                    charge(ctx, 2);
                    if (a1 == 0) {
                        // 0x00152b04
                        charge(ctx, 4);
                        v0 = v1 & 0x4000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x00152b14
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x4000;  // cursor + 1
                            v0 = sltu(0, v0);
                        }
                        // 0x00152b24
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x00152b2c
                            charge(ctx, 4);
                            lw(v1, s0, sys::kQuestCursor);
                            v0 = 2;
                            if (v1 != v0) {
                                // 0x00152b88
                                charge(ctx, 9);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x152B98u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, sys::kQuestCursor);
                                v0 = addiu(v0, 1);
                                sw(v0, s0, sys::kQuestCursor);
                            } else {
                                // 0x00152b3c
                                charge(ctx, 4);
                                v0 = a0 & 0x4000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x00152b4c
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x4000;  // cursor + 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x00152b5c
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x00152b64
                                    charge(ctx, 9);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x152B74u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    sw(zero, s0, sys::kQuestCursor);
                                }
                            }
                        }
                    } else {
                        // 0x00152a7c
                        charge(ctx, 3);
                        lw(v0, s0, sys::kQuestCursor);
                        if (v0 != 0) {
                            // 0x00152ad8
                            charge(ctx, 11);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x152AE8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s0, sys::kQuestCursor);
                            v0 = addiu(v0, -1);
                            sw(v0, s0, sys::kQuestCursor);
                        } else {
                            // 0x00152a88
                            charge(ctx, 4);
                            v0 = a0 & 0x1000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x00152a98
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                v0 = v0 & 0x1000;  // cursor - 1
                                v0 = sltu(0, v0);
                            }
                            // 0x00152aa8
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00152ab0
                                charge(ctx, 10);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x152AC0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                v0 = 2;
                                sw(v0, s0, sys::kQuestCursor);
                            }
                        }
                    }
                } else {
                    // 0x00152a1c
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x152A2Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 24;
                    sw(v0, s0, sys::kState);
                }
            }
            // 0x00152bac
            charge(ctx, 8);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kQuestCursor);
            jal(ctx, 0x152BB8u, gen::fn_sub_159900_00159900);  // the request list's tweens (sub_156F80)
            sw(v0, s0, sys::kArrived);
            goto L_00154748;
        case 0x152BCCu:  // table[24]: state 24: out
            // 0x00152bcc
            charge(ctx, 368);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kQuestCursor);
            jal(ctx, 0x152BD8u, gen::fn_sub_159900_00159900);  // the request list's tweens (sub_156F80)
            a0 = s0;
            jal(ctx, 0x152BE4u, gen::fn_sub_14EF60_0014ef60);  // the system menu's slide-in
            v0 = 0x41B00000;  // 22.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43460000;  // 198.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x148);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152C4Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41C80000;  // 25.0f
            sw(v0, sp, 0x1C8);
            v0 = 369;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x150);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152CC0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, sp, 0x1C8);
            v0 = 0x42440000;  // 49.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 3;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152D0Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42740000;  // 61.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42240000;  // 41.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152D5Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43880000;  // 272.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42240000;  // 41.0f
            sw(v0, sp, 0x1CC);
            a2 = 2;
            sd(a2, sp, 0x0);
            v0 = 12;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152DACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 553;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42240000;  // 41.0f
            sw(v0, sp, 0x1CC);
            v0 = 4;
            sd(v0, sp, 0x0);
            v0 = 14;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152E0Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42480000;  // 50.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152E5Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42BA0000;  // 93.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x158);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152EC8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42700000;  // 60.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42D80000;  // 108.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 544);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152F18u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42480000;  // 50.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43790000;  // 249.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 612);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152F68u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43800000;  // 256.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 680);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x152FB8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 619;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 329;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x160);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 748);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153038u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x426C0000;  // 59.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x43AA0000;  // 340.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x168);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 816);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1530A4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42EE0000;  // 119.0f
            sw(v0, sp, 0x1C8);
            v0 = 333;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x170);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 884);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153118u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153174u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 25;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x15318Cu:  // table[25]: state 25: back to the menu
            // 0x0015318c
            charge(ctx, 13);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x15319Cu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kQuestCursor);
            jal(ctx, 0x1531B0u, gen::fn_sub_159900_00159900);  // the request list's tweens (sub_156F80)
            if (v0 != 0) {
                // 0x001531c0
                charge(ctx, 5);
                sw(zero, s0, sys::kArrived);
                v0 = 3;
                sw(v0, s0, sys::kState);
            }
            goto L_00154748;
        case 0x1531D4u:  // table[26]: state 26: calendar: today's month / day, slide in
            // 0x001531d4
            charge(ctx, 217);
            jal(ctx, 0x1531D4u, gen::fn_clndGetCurrentMonth_0017d920);
            sw(v0, s0, sys::kMonth);
            jal(ctx, 0x1531E0u, gen::fn_clndGetCurrentDay_0017da40);
            sw(v0, s0, sys::kDay);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x1531FCu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            a0 = s0;
            jal(ctx, 0x153208u, gen::fn_sub_14F320_0014f320);  // the system menu's slide-out
            v0 = 291;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x43A20000;  // 324.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x178);
            lwc1(f1, sp, 0x17C);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x17C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x178);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153280u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x180);
            lwc1(f1, sp, 0x180);
            v0 = 0x43480000;  // 200.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x180);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x180);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1532F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42F00000;  // 120.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153340u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42C40000;  // 98.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x188);
            lwc1(f0, sp, 0x188);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0x188);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v0, s0, sys::kPageTweens);
            a0 = addiu(v0, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x188);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1533A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42280000;  // 42.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42FA0000;  // 125.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x190);
            lwc1(f0, sp, 0x190);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0x190);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v0, s0, sys::kPageTweens);
            a0 = addiu(v0, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x190);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153410u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 325;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42480000;  // 50.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15346Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C50000;  // 394.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x198);
            lwc1(f0, sp, 0x198);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            add_s(f0, f0, f12);
            swc1(f0, sp, 0x198);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v0, s0, sys::kPageTweens);
            a0 = addiu(v0, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x198);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1534D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43A30000;  // 326.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42AA0000;  // 85.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153524u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            s1 = 0;
            for (;;) {
                // 0x001535e8
                charge(ctx, 3);
                v0 = slti(s1, 7);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00153538
                charge(ctx, 44);
                v0 = 335;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = sll(s1, 2);
                v0 = addu(v0, s1);
                v0 = sll(v0, 3);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x1C8);
                v0 = 0x42A00000;  // 80.0f
                sw(v0, sp, 0x1CC);
                ld(v0, sp, 0x1C8);
                sd(v0, sp, 0x1A0);
                lwc1(f0, sp, 0x1A0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                add_s(f0, f0, f12);
                swc1(f0, sp, 0x1A0);
                v1 = sll(s1, 1);
                v0 = addiu(v1, 10);
                sd(v0, sp, 0x0);
                v0 = addiu(v1, 15);
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 8);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, sys::kPageTweens);
                a0 = addu(v0, v1);
                a1 = 0;
                a2 = 2;
                a3 = 1;
                ld(t0, sp, 0x1A0);
                ld(t1, sp, 0x1C8);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x1535DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x001535f4
            charge(ctx, 172);
            v0 = 0x43A30000;  // 326.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42CC0000;  // 102.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1020);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15363Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 327;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42CE0000;  // 103.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1088);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153698u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 327;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42CE0000;  // 103.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1156);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1536F4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 327;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42CE0000;  // 103.0f
            sw(v0, sp, 0x1CC);
            ld(v0, sp, 0x1C8);
            sd(v0, sp, 0x1A8);
            lwc1(f1, sp, 0x1AC);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x1AC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1224);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1A8);
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153770u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43A80000;  // 336.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42D40000;  // 106.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1292);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1537C0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43A80000;  // 336.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42E80000;  // 116.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1360);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x153810u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15386Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, sys::kMonth);
            a1 = 1;
            jal(ctx, 0x15387Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
            a0 = v0;
            jal(ctx, 0x153888u, gen::fn_clndGetWeekDay_0017dae0);
            s1 = v0;
            s3 = 0;
            s2 = 1;
            for (;;) {
                // 0x0015397c
                charge(ctx, 10);
                lw(a0, s0, sys::kMonth);
                v1 = sll(a0, 1);
                v0 = 0x5E0000;
                v0 = addiu(v0, 15200);  // &tbl_clndMonthLengths
                v0 = addu(v0, v1);
                lh(v0, v0, -2);
                v0 = addiu(v0, 1);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001538a4
                charge(ctx, 5);
                a1 = s2;
                jal(ctx, 0x1538A8u, gen::fn_sub_14F680_0014f680);  // (kind, id): unlocked?
                if (v0 != 0) {
                    // 0x001538b8
                    charge(ctx, 48);
                    v0 = addu(s1, s2);
                    a1 = addiu(v0, -1);
                    a0 = 7;
                    div(a1, a0);
                    mfhi(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, v1);
                    v0 = addiu(v0, 327);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x1D0);
                    div(a1, a0);
                    mflo(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addiu(v0, 103);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x1D4);
                    v0 = addiu(s3, 10);
                    sd(v0, sp, 0x0);
                    v0 = addiu(s3, 15);
                    sd(v0, sp, 0x8);
                    v1 = addiu(s3, 21);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, sys::kPageTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a2 = 2;
                    a3 = 1;
                    ld(t0, sp, 0x1D0);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x15396Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    s3 = addiu(s3, 1);
                }
                // 0x00153978
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x001539a4
            charge(ctx, 4);
            v0 = 27;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x1539B4u:  // table[27]: state 27: arrived
            // 0x001539b4
            charge(ctx, 14);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kMonth);
            lw(a3, s0, sys::kDay);
            jal(ctx, 0x1539C4u, gen::fn_sub_15B330_0015b330);  // the calendar's tweens (sub_1599F0)
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x1539DCu, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            if (v0 != 0) {
                // 0x001539ec
                charge(ctx, 5);
                sw(zero, s0, sys::kArrived);
                v0 = 28;
                sw(v0, s0, sys::kState);
            }
            goto L_00154748;
        case 0x153A00u:  // table[28]: state 28: calendar (input; month with 0x8 / 0x4, days)
            // 0x00153a00
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x00153a0c
                charge(ctx, 11);
                lw(a0, s0, sys::kMonth);
                lw(a1, s0, sys::kDay);
                jal(ctx, 0x153A14u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                s2 = v0;
                lw(s1, s0, sys::kMonth);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v0 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x00153a60
                    charge(ctx, 5);
                    v0 = 0x7E0000;
                    lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                    v0 = v1 & 0x8;  // calendar month key
                    if (v0 == 0) {
                        // 0x00153b14
                        charge(ctx, 3);
                        v0 = v1 & 0x4;
                        if (v0 == 0) {
                            // 0x00153bbc
                            charge(ctx, 4);
                            v0 = v1 & 0x1000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x00153bcc
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x1000;  // cursor - 1
                                v0 = sltu(0, v0);
                            }
                            // 0x00153bdc
                            charge(ctx, 2);
                            if (v0 == 0) {
                                // 0x00153c74
                                charge(ctx, 4);
                                v0 = v1 & 0x4000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x00153c84
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                    v0 = v0 & 0x4000;  // cursor + 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x00153c94
                                charge(ctx, 2);
                                if (v0 == 0) {
                                    // 0x00153d40
                                    charge(ctx, 4);
                                    v0 = v1 & 0x8000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x00153d50
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                        v0 = v0 & 0x8000;  // previous page
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x00153d60
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        // 0x00153db8
                                        charge(ctx, 4);
                                        v0 = v1 & 0x2000;
                                        v0 = sltu(0, v0);
                                        if (v0 == 0) {
                                            // 0x00153dc8
                                            charge(ctx, 4);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                            v0 = v0 & 0x2000;  // next page
                                            v0 = sltu(0, v0);
                                        }
                                        // 0x00153dd8
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x00153de0
                                            charge(ctx, 10);
                                            a0 = s2;
                                            jal(ctx, 0x153DE4u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                            v0 = 0x5E0000;
                                            lh(a1, v0, 15204);  // 0x5E3B64
                                            a0 = 3;
                                            jal(ctx, 0x153DF8u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                                            if (s2 != v0) {
                                                // 0x00153e08
                                                charge(ctx, 7);
                                                a0 = 0;
                                                a1 = 0;
                                                a2 = 0;
                                                a3 = 0;
                                                jal(ctx, 0x153E18u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                                s2 = addiu(s2, 1);
                                            }
                                            // 0x00153e24
                                            charge(ctx, 8);
                                            a0 = s2;
                                            jal(ctx, 0x153E28u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                            sw(v0, s0, sys::kMonth);
                                            a0 = s2;
                                            jal(ctx, 0x153E38u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                                            sw(v0, s0, sys::kDay);
                                        }
                                    } else {
                                        // 0x00153d68
                                        charge(ctx, 3);
                                        v0 = 2;
                                        if (s2 != v0) {
                                            // 0x00153d74
                                            charge(ctx, 7);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x153D84u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            s2 = addiu(s2, -1);
                                        }
                                        // 0x00153d90
                                        charge(ctx, 10);
                                        a0 = s2;
                                        jal(ctx, 0x153D94u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                        sw(v0, s0, sys::kMonth);
                                        a0 = s2;
                                        jal(ctx, 0x153DA4u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                                        sw(v0, s0, sys::kDay);
                                    }
                                } else {
                                    // 0x00153c9c
                                    charge(ctx, 13);
                                    a0 = s2;
                                    jal(ctx, 0x153CA0u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                    v0 = 0x5E0000;
                                    lh(a1, v0, 15204);  // 0x5E3B64
                                    a0 = 3;
                                    jal(ctx, 0x153CB4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                                    s3 = v0;
                                    v0 = addiu(s2, 7);
                                    at = slt(s3, v0);
                                    if (at == 0) {
                                        // 0x00153cfc
                                        charge(ctx, 7);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x153D0Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        s2 = addiu(s2, 7);
                                    } else {
                                        // 0x00153cd0
                                        charge(ctx, 2);
                                        if (s3 != s2) {
                                            // 0x00153cd8
                                            charge(ctx, 9);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x153CE8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            s2 = s3;
                                        }
                                    }
                                    // 0x00153d18
                                    charge(ctx, 10);
                                    a0 = s2;
                                    jal(ctx, 0x153D1Cu, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                    sw(v0, s0, sys::kMonth);
                                    a0 = s2;
                                    jal(ctx, 0x153D2Cu, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                                    sw(v0, s0, sys::kDay);
                                }
                            } else {
                                // 0x00153be4
                                charge(ctx, 3);
                                at = slti(s2, 7);
                                if (at == 0) {
                                    // 0x00153c20
                                    charge(ctx, 10);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x153C30u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    s2 = addiu(s2, -7);
                                    at = slti(s2, 2);
                                    if (at != 0) {
                                        // 0x00153c48
                                        charge(ctx, 1);
                                        s2 = 2;
                                    }
                                } else {
                                    // 0x00153bf0
                                    charge(ctx, 3);
                                    v0 = 2;
                                    if (s2 != v0) {
                                        // 0x00153bfc
                                        charge(ctx, 9);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x153C0Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        s2 = 2;
                                    }
                                }
                                // 0x00153c4c
                                charge(ctx, 10);
                                a0 = s2;
                                jal(ctx, 0x153C50u, gen::fn_clndGetMonthFromDaysSinceApr5_0017d830);
                                sw(v0, s0, sys::kMonth);
                                a0 = s2;
                                jal(ctx, 0x153C60u, gen::fn_clndGetDayOfMonthFromDaysSinceApr5_0017d9c0);
                                sw(v0, s0, sys::kDay);
                            }
                        } else {
                            // 0x00153b20
                            charge(ctx, 3);
                            v0 = 4;
                            if (s1 != v0) {
                                // 0x00153b2c
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x153B3Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, sys::kMonth);
                                v0 = addiu(v0, -1);
                                sw(v0, s0, sys::kMonth);
                                if (v0 == 0) {
                                    // 0x00153b58
                                    charge(ctx, 2);
                                    v0 = 12;
                                    sw(v0, s0, sys::kMonth);
                                }
                                // 0x00153b60
                                charge(ctx, 10);
                                lw(v0, s0, sys::kMonth);
                                v1 = sll(v0, 1);
                                v0 = 0x5E0000;
                                v0 = addiu(v0, 15198);  // &0x5E3B5E
                                v0 = addu(v0, v1);
                                lh(v1, v0, 0);
                                lw(v0, s0, sys::kDay);
                                at = slt(v1, v0);
                                if (at != 0) {
                                    // 0x00153b88
                                    charge(ctx, 1);
                                    sw(v1, s0, sys::kDay);
                                }
                                // 0x00153b8c
                                charge(ctx, 4);
                                lw(v1, s0, sys::kMonth);
                                v0 = 4;
                                if (v1 == v0) {
                                    // 0x00153b9c
                                    charge(ctx, 4);
                                    lw(v0, s0, sys::kDay);
                                    at = slti(v0, 7);
                                    if (at != 0) {
                                        // 0x00153bac
                                        charge(ctx, 4);
                                        v0 = 7;
                                        sw(v0, s0, sys::kDay);
                                    }
                                }
                            }
                        }
                    } else {
                        // 0x00153a74
                        charge(ctx, 3);
                        v0 = 3;
                        if (s1 != v0) {
                            // 0x00153a80
                            charge(ctx, 12);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x153A90u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s0, sys::kMonth);
                            v1 = addiu(v0, 1);
                            sw(v1, s0, sys::kMonth);
                            v0 = 13;
                            if (v1 == v0) {
                                // 0x00153ab0
                                charge(ctx, 2);
                                v0 = 1;
                                sw(v0, s0, sys::kMonth);
                            }
                            // 0x00153ab8
                            charge(ctx, 10);
                            lw(v0, s0, sys::kMonth);
                            v1 = sll(v0, 1);
                            v0 = 0x5E0000;
                            v0 = addiu(v0, 15198);  // &0x5E3B5E
                            v0 = addu(v0, v1);
                            lh(v1, v0, 0);
                            lw(v0, s0, sys::kDay);
                            at = slt(v1, v0);
                            if (at != 0) {
                                // 0x00153ae0
                                charge(ctx, 1);
                                sw(v1, s0, sys::kDay);
                            }
                            // 0x00153ae4
                            charge(ctx, 4);
                            lw(v1, s0, sys::kMonth);
                            v0 = 4;
                            if (v1 == v0) {
                                // 0x00153af4
                                charge(ctx, 4);
                                lw(v0, s0, sys::kDay);
                                at = slti(v0, 7);
                                if (at != 0) {
                                    // 0x00153b04
                                    charge(ctx, 4);
                                    v0 = 7;
                                    sw(v0, s0, sys::kDay);
                                }
                            }
                        }
                    }
                } else {
                    // 0x00153a38
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x153A48u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 29;
                    sw(v0, s0, sys::kState);
                }
                // 0x00153e44
                charge(ctx, 3);
                lw(v0, s0, sys::kMonth);
                if (s1 != v0) {
                    // 0x00153e50
                    charge(ctx, 3);
                    a0 = 21;
                    for (;;) {
                        // 0x00153e78
                        charge(ctx, 3);
                        v0 = slti(a0, 53);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00153e5c
                        charge(ctx, 7);
                        v0 = sll(a0, 4);
                        v0 = addu(v0, a0);
                        v1 = sll(v0, 2);
                        lw(v0, s0, sys::kPageTweens);
                        v0 = addu(v0, v1);
                        sw(zero, v0, 4);
                        a0 = addiu(a0, 1);
                    }
                    // 0x00153e84
                    charge(ctx, 12);
                    lw(a0, s0, sys::kMonth);
                    a1 = 1;
                    jal(ctx, 0x153E8Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                    a0 = v0;
                    jal(ctx, 0x153E98u, gen::fn_clndGetWeekDay_0017dae0);
                    s1 = v0;
                    s3 = 0;
                    s2 = 1;
                    for (;;) {
                        // 0x00153f84
                        charge(ctx, 10);
                        lw(a0, s0, sys::kMonth);
                        v1 = sll(a0, 1);
                        v0 = 0x5E0000;
                        v0 = addiu(v0, 15200);  // &tbl_clndMonthLengths
                        v0 = addu(v0, v1);
                        lh(v0, v0, -2);
                        v0 = addiu(v0, 1);
                        v0 = slt(s2, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00153eb4
                        charge(ctx, 5);
                        a1 = s2;
                        jal(ctx, 0x153EB8u, gen::fn_sub_14F680_0014f680);  // (kind, id): unlocked?
                        if (v0 != 0) {
                            // 0x00153ec8
                            charge(ctx, 46);
                            v0 = addu(s1, s2);
                            a1 = addiu(v0, -1);
                            a0 = 7;
                            div(a1, a0);
                            mfhi(v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 3);
                            v0 = addu(v0, v1);
                            v0 = addiu(v0, 327);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            swc1(f0, sp, 0x1D0);
                            div(a1, a0);
                            mflo(v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addiu(v0, 103);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            swc1(f0, sp, 0x1D4);
                            a3 = 1;
                            sd(a3, sp, 0x0);
                            sd(a3, sp, 0x8);
                            v1 = addiu(s3, 21);
                            v0 = sll(v1, 4);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 2);
                            lw(v0, s0, sys::kPageTweens);
                            a0 = addu(v0, v1);
                            v0 = 0x42C80000;  // 100.0f
                            mtc1(v0, f12);
                            a1 = 0;
                            a2 = 2;
                            ld(t0, sp, 0x1D0);
                            t1 = t0;
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x153F74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                            s3 = addiu(s3, 1);
                        }
                        // 0x00153f80
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                }
            }
            // 0x00153fac
            charge(ctx, 9);
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kMonth);
            lw(a3, s0, sys::kDay);
            jal(ctx, 0x153FBCu, gen::fn_sub_15B330_0015b330);  // the calendar's tweens (sub_1599F0)
            sw(v0, s0, sys::kArrived);
            goto L_00154748;
        case 0x153FD0u:  // table[29]: state 29: out
            // 0x00153fd0
            charge(ctx, 184);
            a0 = s0;
            jal(ctx, 0x153FD4u, gen::fn_sub_14EF60_0014ef60);  // the system menu's slide-in
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kMonth);
            lw(a3, s0, sys::kDay);
            jal(ctx, 0x153FECu, gen::fn_sub_15B330_0015b330);  // the calendar's tweens (sub_1599F0)
            v0 = 291;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x43A20000;  // 324.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x1B0);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x154060u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1540B0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41980000;  // 19.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42F00000;  // 120.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x154100u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42100000;  // 36.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42C40000;  // 98.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x154150u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42280000;  // 42.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42FA0000;  // 125.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1541A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 325;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42480000;  // 50.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1541FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C50000;  // 394.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15424Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43A30000;  // 326.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42AA0000;  // 85.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 476);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15429Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            s1 = 0;
            for (;;) {
                // 0x00154340
                charge(ctx, 3);
                v0 = slti(s1, 7);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001542b0
                charge(ctx, 36);
                v0 = 335;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = sll(s1, 2);
                v0 = addu(v0, s1);
                v0 = sll(v0, 3);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x1C8);
                v0 = 0x42A00000;  // 80.0f
                sw(v0, sp, 0x1CC);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v1 = addiu(s1, 8);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s0, sys::kPageTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a2 = 2;
                a3 = a2;
                ld(t0, sp, 0x1C8);
                t1 = t0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x154334u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                s1 = addiu(s1, 1);
            }
            // 0x0015434c
            charge(ctx, 171);
            v0 = 0x43A30000;  // 326.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42CC0000;  // 102.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1020);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x154394u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 327;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42CE0000;  // 103.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1088);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1543F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 327;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42CE0000;  // 103.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1156);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15444Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 327;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1C8);
            v0 = 0x42CE0000;  // 103.0f
            mtc1(v0, f1);
            sw(v0, sp, 0x1CC);
            ld(t0, sp, 0x1C8);
            sd(t0, sp, 0x1B8);
            v0 = 0x43960000;  // 300.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1224);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0x1C8);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1544C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43A80000;  // 336.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42D40000;  // 106.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1292);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x154514u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43A80000;  // 336.0f
            sw(v0, sp, 0x1C8);
            v0 = 0x42E80000;  // 116.0f
            sw(v0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 1360);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x154564u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41F80000;  // 31.0f
            sw(v0, sp, 0x1C8);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0x1CC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x1C8);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x1545C0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            lw(a0, s0, sys::kMonth);
            a1 = 1;
            jal(ctx, 0x1545D0u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
            a0 = v0;
            jal(ctx, 0x1545DCu, gen::fn_clndGetWeekDay_0017dae0);
            s1 = v0;
            s3 = 0;
            s2 = 1;
            for (;;) {
                // 0x001546cc
                charge(ctx, 10);
                lw(a0, s0, sys::kMonth);
                v1 = sll(a0, 1);
                v0 = 0x5E0000;
                v0 = addiu(v0, 15200);  // &tbl_clndMonthLengths
                v0 = addu(v0, v1);
                lh(v0, v0, -2);
                v0 = addiu(v0, 1);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001545f8
                charge(ctx, 5);
                a1 = s2;
                jal(ctx, 0x1545FCu, gen::fn_sub_14F680_0014f680);  // (kind, id): unlocked?
                if (v0 != 0) {
                    // 0x0015460c
                    charge(ctx, 47);
                    v0 = addu(s1, s2);
                    a1 = addiu(v0, -1);
                    a0 = 7;
                    div(a1, a0);
                    mfhi(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, v1);
                    v0 = addiu(v0, 327);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x1D0);
                    div(a1, a0);
                    mflo(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addiu(v0, 103);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    swc1(f0, sp, 0x1D4);
                    sd(zero, sp, 0x0);
                    v0 = 10;
                    sd(v0, sp, 0x8);
                    v1 = addiu(s3, 21);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v1 = sll(v0, 2);
                    lw(v0, s0, sys::kPageTweens);
                    a0 = addu(v0, v1);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a1 = 0;
                    a2 = 2;
                    a3 = a2;
                    ld(t0, sp, 0x1D0);
                    t1 = t0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x1546BCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                    s3 = addiu(s3, 1);
                }
                // 0x001546c8
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x001546f4
            charge(ctx, 4);
            v0 = 30;
            sw(v0, s0, sys::kState);
            goto L_00154748;
        case 0x154704u:  // table[30]: state 30: back to the menu
            // 0x00154704
            charge(ctx, 14);
            lw(a0, s0, sys::kMenuTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kTexture);
            lw(a3, s0, sys::kCursor);
            jal(ctx, 0x154714u, gen::fn_sub_154F70_00154f70);  // the system menu's tweens (sub_154970)
            lw(a0, s0, sys::kPageTweens);
            a1 = addiu(s0, sys::kFiles);
            lw(a2, s0, sys::kMonth);
            lw(a3, s0, sys::kDay);
            jal(ctx, 0x15472Cu, gen::fn_sub_15B330_0015b330);  // the calendar's tweens (sub_1599F0)
            if (v0 != 0) {
                // 0x0015473c
                charge(ctx, 3);
                sw(zero, s0, sys::kArrived);
                v0 = 3;
                sw(v0, s0, sys::kState);
            }
            goto L_00154748;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0015474c (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        sp = addiu(sp, 0x1E0);
        return;
    }
    goto L_00154748;
}

// 0x00154970 sub_154970 -- 1532 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemDrawMenuElement] (tween, files, element, ...): one element of the system menu (jump table 0x7B6170): 0
// the scrolling background (two sub_1140D0 strips, +52 moving by -1, wrapping at -1000), 1 the six row frames, 2 the
// title, 3 the entries (The Answer's set greyed), the cursor and the status picture.
void sub_154970(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00154970
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s4 = a3;
    s1 = t0;
    at = sltiu(a2, 8);
    if (at != 0) {
        // 0x001549a8
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 24944);  // &0x7B6170
        v1 = sll(a2, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x1549C4u:  // table[0]: element 0: the scrolling background
            // 0x001549c4
            charge(ctx, 46);
            lw(v1, s3, tw::kAlpha);
            v0 = 255;
            v1 = subu(v0, v1);
            v0 = si(-256);
            s0 = v1 | v0;
            lwc1(f1, s3, tw::kX);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lwc1(f12, s3, tw::kZ);
            a0 = s0;
            lwc1(f14, s3, tw::kY);
            a1 = 460;
            a2 = 921;
            jal(ctx, 0x154A00u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
            lwc1(f1, s3, tw::kX);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f13, f1, f0);
            lwc1(f1, s3, tw::kY);
            v0 = 0x447A0000;  // 1000.0f
            mtc1(v0, f0);
            add_s(f14, f0, f1);
            lwc1(f12, s3, tw::kZ);
            a0 = s0;
            a1 = 460;
            a2 = 921;
            a3 = s4;
            jal(ctx, 0x154A44u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
            lwc1(f1, s3, 52);
            v1 = 0x3F800000;  // 1.0f
            mtc1(v1, f0);
            sub_s(f1, f1, f0);
            swc1(f1, s3, 52);
            v1 = lui(0xC47A);
            mtc1(v1, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x00154a7c
                charge(ctx, 7);
                v1 = 0x447A0000;  // 1000.0f
                mtc1(v1, f0);
                add_s(f0, f1, f0);
                swc1(f0, s3, 52);
            }
            break;
        case 0x154A98u:  // table[2]: element 2: the title
            // 0x00154a98
            charge(ctx, 11);
            lbu(a3, s3, tw::kAlpha);
            a0 = s0;
            lw(a1, s2, 0);
            a2 = 13;
            lwc1(f12, s3, tw::kX);
            lwc1(f13, s3, tw::kY);
            lwc1(f14, s3, tw::kZ);
            jal(ctx, 0x154AB4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x154AC4u:  // table[1]: element 1: the six row frames
            // 0x00154ac4
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00154b10
                charge(ctx, 3);
                v1 = slti(s1, 6);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00154ad0
                charge(ctx, 16);
                lwc1(f1, s3, tw::kY);
                v0 = sll(s1, 5);
                v0 = addu(v0, s1);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f1, f0);
                lbu(a3, s3, tw::kAlpha);
                a0 = s0;
                lw(a1, s2, 0);
                a2 = 14;
                lwc1(f12, s3, tw::kX);
                lwc1(f14, s3, tw::kZ);
                jal(ctx, 0x154B04u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                s1 = addiu(s1, 1);
            }
            // 0x00154b1c
            charge(ctx, 2);
            break;
        case 0x154B24u:  // table[3]: element 3: the entries
            // 0x00154b24
            charge(ctx, 4);
            jal(ctx, 0x154B24u, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
            if (v0 == 0) {
                // 0x00154c34
                charge(ctx, 3);
                s4 = 0;
                for (;;) {
                    // 0x00154ccc
                    charge(ctx, 3);
                    v1 = slti(s4, 6);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00154c40
                    charge(ctx, 2);
                    if (s1 != s4) {
                        // 0x00154c8c
                        charge(ctx, 15);
                        lwc1(f1, s3, tw::kY);
                        v0 = sll(s4, 5);
                        v0 = addu(v0, s4);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        a2 = addiu(s4, 6);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s2, 0);
                        lwc1(f12, s3, tw::kX);
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x154CC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x00154c48
                        charge(ctx, 17);
                        lwc1(f1, s3, tw::kY);
                        v0 = sll(s4, 5);
                        v0 = addu(v0, s4);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s2, 0);
                        a2 = s4;
                        lwc1(f12, s3, tw::kX);
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x154C7Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x00154cc8
                    charge(ctx, 1);
                    s4 = addiu(s4, 1);
                }
                // 0x00154cd8
                charge(ctx, 2);
            } else {
                // 0x00154b34
                charge(ctx, 3);
                s4 = 0;
                for (;;) {
                    // 0x00154c20
                    charge(ctx, 3);
                    v1 = slti(s4, 6);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00154b40
                    charge(ctx, 2);
                    if (s1 != s4) {
                        // 0x00154b8c
                        charge(ctx, 3);
                        at = sltiu(s4, 4);
                        if (at == 0) {
                            // 0x00154be0
                            charge(ctx, 15);
                            lwc1(f1, s3, tw::kY);
                            v0 = sll(s4, 5);
                            v0 = addu(v0, s4);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            a2 = addiu(s4, 6);
                            lbu(a3, s3, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s2, 0);
                            lwc1(f12, s3, tw::kX);
                            lwc1(f14, s3, tw::kZ);
                            jal(ctx, 0x154C14u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x00154b98
                            charge(ctx, 18);
                            lwc1(f1, s3, tw::kY);
                            v0 = sll(s4, 5);
                            v0 = addu(v0, s4);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            a2 = addiu(s4, 6);
                            lbu(t0, s3, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s2, 0);
                            lwc1(f12, s3, tw::kX);
                            a3 = 128;
                            lwc1(f14, s3, tw::kZ);
                            jal(ctx, 0x154BD0u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                        }
                    } else {
                        // 0x00154b48
                        charge(ctx, 17);
                        lwc1(f1, s3, tw::kY);
                        v0 = sll(s4, 5);
                        v0 = addu(v0, s4);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s2, 0);
                        a2 = s4;
                        lwc1(f12, s3, tw::kX);
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x154B7Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x00154c1c
                    charge(ctx, 1);
                    s4 = addiu(s4, 1);
                }
                // 0x00154c2c
                charge(ctx, 2);
            }
            break;
        case 0x154CE0u:  // table[4]
            // 0x00154ce0
            charge(ctx, 29);
            a0 = 0;
            lw(a1, s2, 0);
            a2 = 25;
            jal(ctx, 0x154CECu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s0 = v0;
            lwc1(f0, s3, tw::kZ);
            swc1(f0, v0, 44);
            lwc1(f0, s3, tw::kX);
            swc1(f0, v0, 16);
            lwc1(f1, s3, tw::kY);
            v1 = 0x43480000;  // 200.0f
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, v0, 20);
            lw(v1, s3, tw::kAlpha);
            sb(v1, v0, 24);
            v1 = lui(0xC2B4);
            sw(v1, v0, 32);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x154D38u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s0;
            jal(ctx, 0x154D44u, gen::fn_sub_115980_00115980);  // draw and release the handle
            break;
        case 0x154D54u:  // table[5]
            // 0x00154d54
            charge(ctx, 29);
            a0 = 0;
            lw(a1, s2, 0);
            a2 = 15;
            jal(ctx, 0x154D60u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s0 = v0;
            lwc1(f0, s3, tw::kZ);
            swc1(f0, v0, 44);
            lwc1(f0, s3, tw::kX);
            swc1(f0, v0, 16);
            lwc1(f1, s3, tw::kY);
            v1 = 0x43480000;  // 200.0f
            mtc1(v1, f0);
            add_s(f0, f0, f1);
            swc1(f0, v0, 20);
            lw(v1, s3, tw::kAlpha);
            sb(v1, v0, 24);
            v1 = lui(0xC2B4);
            sw(v1, v0, 32);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x154DACu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s0;
            jal(ctx, 0x154DB8u, gen::fn_sub_115980_00115980);  // draw and release the handle
            break;
        case 0x154DC8u:  // table[6]
            // 0x00154dc8
            charge(ctx, 11);
            a2 = addiu(s1, 2);
            lbu(a3, s3, tw::kAlpha);
            a0 = s0;
            lw(a1, s2, 4);
            lwc1(f12, s3, tw::kX);
            lwc1(f13, s3, tw::kY);
            lwc1(f14, s3, tw::kZ);
            jal(ctx, 0x154DE4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        case 0x154DF4u:  // table[7]
            // 0x00154df4
            charge(ctx, 85);
            lbu(a3, s3, tw::kAlpha);
            a0 = s0;
            lw(a1, s2, 4);
            a2 = 0;
            lwc1(f12, s3, tw::kX);
            lwc1(f13, s3, tw::kY);
            lwc1(f14, s3, tw::kZ);
            jal(ctx, 0x154E10u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s3, tw::kX);
            v0 = 0x43CC0000;  // 408.0f
            mtc1(v0, f0);
            add_s(f1, f0, f1);
            v0 = 0x43C40000;  // 392.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s3, tw::kY);
            add_s(f0, f1, f0);
            sub_s(f13, f0, f1);
            lbu(a3, s3, tw::kAlpha);
            a0 = s0;
            lw(a1, s2, 4);
            a2 = 1;
            lwc1(f14, s3, tw::kZ);
            jal(ctx, 0x154E6Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s3, tw::kX);
            v0 = 0x42CC0000;  // 102.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s3, tw::kY);
            add_s(f1, f1, f0);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s3, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 0;
            lwc1(f14, s3, tw::kZ);
            jal(ctx, 0x154ECCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 561;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s3, tw::kX);
            add_s(f1, f1, f0);
            v0 = 0x43C40000;  // 392.0f
            mtc1(v0, f0);
            sub_s(f12, f1, f0);
            v0 = 415;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, s3, tw::kY);
            add_s(f1, f1, f0);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            sub_s(f13, f1, f0);
            lbu(a3, s3, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
            a2 = 1;
            lwc1(f14, s3, tw::kZ);
            jal(ctx, 0x154F40u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00154f48 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00154F70 sub_154F70 -- 244 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemRunMenuTweens] (tweens, files, texture, cursor): steps the menu's 10 tweens, draws each active one
// (sub_154970), returns 1 when all finished.
void sub_154F70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00154f70
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
        // 0x00155028
        charge(ctx, 3);
        v0 = slti(s2, 10);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00154fb4
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x00154fd0
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x154FD4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x00154fe4
                charge(ctx, 7);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                jal(ctx, 0x154FF8u, gen::fn_sub_154970_00154970);
            }
            // 0x00155000
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x00155020
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x00155024
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00155034
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

// 0x00155070 sub_155070 -- 1692 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemDrawHelpElement] (tween, files, element, table, count, scroll, cursor): one element of the help list:
// 99 the frame, 6 the header, 5 the eight visible rows of the text table off_5DA500 (sub_3B32D0, the cursor row
// highlighted), the scroll marks.
void sub_155070(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00155070
    enter(ctx, 18);  // entry check point + this block's cycles
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
    s6 = a3;
    s3 = t0;
    s2 = t1;
    s1 = t2;
    v1 = 99;
    if (a2 == v1) {
        // 0x00155604
        charge(ctx, 55);
        lbu(a3, s5, tw::kAlpha);
        a0 = s0;
        lw(a1, s4, 4);
        a2 = 0;
        lwc1(f12, s5, tw::kX);
        lwc1(f13, s5, tw::kY);
        lwc1(f14, s5, tw::kZ);
        jal(ctx, 0x155620u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s5, tw::kX);
        v0 = 0x423C0000;  // 47.0f
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lbu(a3, s5, tw::kAlpha);
        a0 = s0;
        lw(a1, s4, 4);
        a2 = 12;
        lwc1(f13, s5, tw::kY);
        lwc1(f14, s5, tw::kZ);
        jal(ctx, 0x155664u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s5, tw::kX);
        add_s(f1, f1, f0);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s5, tw::kY);
        add_s(f1, f1, f0);
        v0 = 385;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s5, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        lwc1(f14, s5, tw::kZ);
        jal(ctx, 0x1556D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x001550b8
        charge(ctx, 3);
        v1 = 6;
        if (a2 == v1) {
            // 0x00155570
            charge(ctx, 12);
            lbu(a3, s5, tw::kAlpha);
            a0 = s0;
            lw(a1, s4, 0);
            a2 = 33;
            lwc1(f12, s5, tw::kX);
            lwc1(f13, s5, tw::kY);
            lwc1(f14, s5, tw::kZ);
            jal(ctx, 0x15558Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v1 = addiu(s3, -8);
            if (i64(v1) <= 0) {
                // 0x001555b4
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001555a0
                charge(ctx, 5);
                v0 = sll(s2, 6);
                div(v0, v1);
                mflo(v0);
            }
            // 0x001555b8
            charge(ctx, 19);
            mtc1(v0, f0);
            cvt_s_w(f2, f0);
            lwc1(f1, s5, tw::kY);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            add_s(f13, f0, f2);
            lbu(a3, s5, tw::kAlpha);
            a0 = s0;
            lw(a1, s4, 0);
            a2 = 34;
            lwc1(f12, s5, tw::kX);
            lwc1(f14, s5, tw::kZ);
            jal(ctx, 0x1555F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x001550c4
            charge(ctx, 3);
            v1 = 5;
            if (a2 == v1) {
                // 0x00155420
                charge(ctx, 10);
                lw(a0, s5, tw::kAlpha);
                v1 = 255;
                a0 = subu(v1, a0);
                s0 = 0;
                v1 = sll(s2, 2);
                s6 = addu(s6, v1);
                v1 = si(-256);
                s4 = a0 | v1;
                for (;;) {
                    // 0x0015555c
                    charge(ctx, 3);
                    v1 = slti(s0, 8);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00155448
                    charge(ctx, 4);
                    v1 = addu(s2, s0);
                    at = slt(v1, s3);
                    if (at != 0) {
                        // 0x00155458
                        charge(ctx, 2);
                        if (s0 != s1) {
                            // 0x001554e0
                            charge(ctx, 30);
                            lwc1(f0, s5, tw::kX);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f0, s5, tw::kY);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = sll(s0, 3);
                            v1 = subu(v0, s0);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v0 = addu(a1, v0);
                            a1 = addiu(v0, 3);
                            v0 = sll(s0, 2);
                            v0 = addu(s6, v0);
                            lw(v1, v0, 0);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 2);
                            v0 = 0x5E0000;
                            v0 = addiu(v0, -23296);  // &0x5DA500
                            v0 = addu(v0, v1);
                            lwc1(f12, s5, tw::kZ);
                            a2 = s4;
                            a3 = 10;
                            t0 = 1;
                            lw(t1, v0, 0);
                            t2 = 16;
                            t3 = 120;
                            jal(ctx, 0x155550u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                        } else {
                            // 0x00155460
                            charge(ctx, 32);
                            lwc1(f0, s5, tw::kX);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f0, s5, tw::kY);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = sll(s0, 3);
                            v1 = subu(v0, s0);
                            v0 = sll(v1, 2);
                            v0 = addu(v1, v0);
                            v0 = addu(a1, v0);
                            a1 = addiu(v0, 3);
                            v0 = sll(s0, 2);
                            v0 = addu(s6, v0);
                            lw(v1, v0, 0);
                            v0 = sll(v1, 3);
                            v0 = subu(v0, v1);
                            v1 = sll(v0, 2);
                            v0 = 0x5E0000;
                            v0 = addiu(v0, -23296);  // &0x5DA500
                            v0 = addu(v0, v1);
                            lwc1(f12, s5, tw::kZ);
                            a2 = s4;
                            a3 = 6;
                            t0 = 1;
                            lw(t1, v0, 0);
                            t2 = 16;
                            t3 = 120;
                            jal(ctx, 0x1554D0u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                        }
                    }
                    // 0x00155558
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x00155568
                charge(ctx, 2);
            } else {
                // 0x001550d0
                charge(ctx, 3);
                v1 = 4;
                if (a2 == v1) {
                    // 0x0015536c
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x001553c8
                        charge(ctx, 3);
                        v0 = slti(s2, 8);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00155378
                        charge(ctx, 20);
                        v0 = sll(s2, 3);
                        v1 = subu(v0, s2);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v0 = addiu(v0, 87);
                        mtc1(v0, f0);
                        cvt_s_w(f13, f0);
                        v0 = 341;
                        mtc1(v0, f0);
                        cvt_s_w(f12, f0);
                        lbu(a3, s5, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s4, 0);
                        a2 = 41;
                        lwc1(f14, s5, tw::kZ);
                        jal(ctx, 0x1553BCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        s2 = addiu(s2, 1);
                    }
                    // 0x001553d4
                    charge(ctx, 19);
                    lwc1(f1, s5, tw::kY);
                    v0 = sll(s1, 3);
                    v1 = subu(v0, s1);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f1, f0);
                    lbu(a3, s5, tw::kAlpha);
                    a0 = s0;
                    lw(a1, s4, 0);
                    a2 = 32;
                    lwc1(f12, s5, tw::kX);
                    lwc1(f14, s5, tw::kZ);
                    jal(ctx, 0x155410u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x001550dc
                    charge(ctx, 3);
                    v1 = 3;
                    if (a2 == v1) {
                        // 0x00155308
                        charge(ctx, 25);
                        a0 = 0;
                        lw(a1, s4, 0);
                        a2 = 17;
                        jal(ctx, 0x155314u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                        s0 = v0;
                        lwc1(f0, s5, tw::kZ);
                        swc1(f0, v0, 44);
                        lwc1(f0, s5, tw::kX);
                        swc1(f0, v0, 16);
                        lwc1(f0, s5, tw::kY);
                        swc1(f0, v0, 20);
                        lw(v1, s5, tw::kAlpha);
                        sb(v1, v0, 24);
                        v1 = lui(0xC2B4);
                        sw(v1, v0, 32);
                        a0 = s0;
                        a1 = 1;
                        jal(ctx, 0x155350u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                        a0 = s0;
                        jal(ctx, 0x15535Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
                    } else {
                        // 0x001550e8
                        charge(ctx, 3);
                        v1 = 2;
                        if (a2 == v1) {
                            // 0x00155210
                            charge(ctx, 4);
                            a1 = addu(s2, s1);
                            at = slt(a1, s3);
                            if (at != 0) {
                                // 0x00155220
                                charge(ctx, 10);
                                lw(a0, s5, tw::kAlpha);
                                v1 = 255;
                                a0 = subu(v1, a0);
                                s2 = 0;
                                v1 = sll(a1, 2);
                                s0 = addu(s6, v1);
                                v1 = si(-256);
                                s1 = a0 | v1;
                                for (;;) {
                                    // 0x001552f4
                                    charge(ctx, 3);
                                    v1 = slti(s2, 6);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x00155248
                                    charge(ctx, 43);
                                    lwc1(f0, s5, tw::kX);
                                    cvt_w_s(f0, f0);
                                    mfc1(a0, f0);
                                    lwc1(f0, s5, tw::kY);
                                    cvt_w_s(f0, f0);
                                    mfc1(v1, f0);
                                    v0 = sll(s2, 1);
                                    v0 = addu(v0, s2);
                                    v0 = sll(v0, 3);
                                    v0 = addu(v1, v0);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    v0 = 0x40A00000;  // 5.0f
                                    mtc1(v0, f1);
                                    add_s(f0, f1, f0);
                                    sub_s(f1, f0, f1);
                                    v0 = 0x40800000;  // 4.0f
                                    mtc1(v0, f0);
                                    sub_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(a1, f0);
                                    lw(v1, s0, 0);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 2);
                                    v0 = 0x5E0000;
                                    v0 = addiu(v0, -23296);  // &0x5DA500
                                    v1 = addu(v0, v1);
                                    v0 = sll(s2, 2);
                                    v0 = addu(v0, v1);
                                    lwc1(f12, s5, tw::kZ);
                                    a2 = s1;
                                    a3 = 10;
                                    t0 = 1;
                                    lw(t1, v0, 4);
                                    t2 = 16;
                                    t3 = 120;
                                    jal(ctx, 0x1552E8u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                                    s2 = addiu(s2, 1);
                                }
                                // 0x00155300
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x001550f4
                            charge(ctx, 3);
                            v1 = 1;
                            if (a2 == v1) {
                                // 0x0015513c
                                charge(ctx, 21);
                                lwc1(f1, s5, tw::kX);
                                v0 = 0x436C0000;  // 236.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s5, tw::kY);
                                v0 = lui(0xC110);
                                mtc1(v0, f0);
                                add_s(f13, f0, f1);
                                lbu(a3, s5, tw::kAlpha);
                                a0 = s0;
                                lw(a1, s4, 0);
                                a2 = 40;
                                lwc1(f14, s5, tw::kZ);
                                jal(ctx, 0x155178u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                a3 = addu(s2, s1);
                                at = slt(a3, s3);
                                if (at != 0) {
                                    // 0x00155190
                                    charge(ctx, 32);
                                    lw(v1, s5, tw::kAlpha);
                                    v0 = 255;
                                    v1 = subu(v0, v1);
                                    lwc1(f0, s5, tw::kX);
                                    cvt_w_s(f0, f0);
                                    mfc1(a0, f0);
                                    lwc1(f0, s5, tw::kY);
                                    cvt_w_s(f0, f0);
                                    mfc1(v0, f0);
                                    a1 = addiu(v0, 2);
                                    v0 = si(-256);
                                    a2 = v1 | v0;
                                    v0 = sll(a3, 2);
                                    v0 = addu(s6, v0);
                                    lw(v1, v0, 0);
                                    v0 = sll(v1, 3);
                                    v0 = subu(v0, v1);
                                    v1 = sll(v0, 2);
                                    v0 = 0x5E0000;
                                    v0 = addiu(v0, -23296);  // &0x5DA500
                                    v0 = addu(v0, v1);
                                    lwc1(f12, s5, tw::kZ);
                                    a3 = 6;
                                    t0 = 1;
                                    lw(t1, v0, 0);
                                    t2 = 16;
                                    t3 = 118;
                                    jal(ctx, 0x155200u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                                }
                            } else {
                                // 0x00155100
                                charge(ctx, 2);
                                if (a2 == 0) {
                                    // 0x00155110
                                    charge(ctx, 11);
                                    lbu(a3, s5, tw::kAlpha);
                                    a0 = s0;
                                    lw(a1, s4, 0);
                                    a2 = 27;
                                    lwc1(f12, s5, tw::kX);
                                    lwc1(f13, s5, tw::kY);
                                    lwc1(f14, s5, tw::kZ);
                                    jal(ctx, 0x15512Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x00155108
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x001556e0 (the shared epilogue, written out on this path)
    charge(ctx, 11);
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

// 0x00155710 sub_155710 -- 276 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemRunHelpTweens] (tweens, files, ...): steps the help list's tweens and draws them (sub_155070); 1 when
// all finished.
void sub_155710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00155710
    enter(ctx, 21);  // entry check point + this block's cycles
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
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s6 = a3;
    s7 = t0;
    fp = t1;
    s1 = 1;
    s2 = 0;
    for (;;) {
        // 0x001557e0
        charge(ctx, 3);
        v0 = slti(s2, 100);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00155764
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x00155780
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x155784u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x00155794
                charge(ctx, 9);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                t1 = s7;
                t2 = fp;
                jal(ctx, 0x1557B0u, gen::fn_sub_155070_00155070);
            }
            // 0x001557b8
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x001557d8
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x001557dc
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001557ec
    charge(ctx, 14);
    v0 = s1;
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

// 0x00155830 sub_155830 -- 2308 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemDrawConfigElement] (tween, files, element, cursor, values): one element of the config page: 99 the
// frame with the page title (sprite 15 + cursor), 6 the eight option rows (sprites 140..150; the cursor row lit), the
// option values (on / off and the level marks of each option's value).
void sub_155830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00155830
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a3;
    s1 = t0;
    v1 = 99;
    if (a2 == v1) {
        // 0x00155f8c
        charge(ctx, 96);
        lbu(a3, s4, tw::kAlpha);
        a0 = s0;
        lw(a1, s3, 4);
        a2 = 0;
        lwc1(f12, s4, tw::kX);
        lwc1(f13, s4, tw::kY);
        lwc1(f14, s4, tw::kZ);
        jal(ctx, 0x155FA8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s4, tw::kX);
        v0 = 0x43CC0000;  // 408.0f
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x43C40000;  // 392.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lbu(a3, s4, tw::kAlpha);
        a0 = s0;
        lw(a1, s3, 4);
        a2 = 13;
        lwc1(f13, s4, tw::kY);
        lwc1(f14, s4, tw::kZ);
        jal(ctx, 0x155FECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a2 = addiu(s2, 15);
        lwc1(f1, s4, tw::kX);
        v0 = 0x423C0000;  // 47.0f
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x43C40000;  // 392.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lbu(a3, s4, tw::kAlpha);
        a0 = s0;
        lw(a1, s3, 4);
        lwc1(f13, s4, tw::kY);
        lwc1(f14, s4, tw::kZ);
        jal(ctx, 0x156030u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s4, tw::kX);
        v0 = 0x42CC0000;  // 102.0f
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s4, tw::kY);
        add_s(f1, f1, f0);
        v0 = 385;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s4, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 0;
        lwc1(f14, s4, tw::kZ);
        jal(ctx, 0x156090u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s4, tw::kX);
        add_s(f1, f1, f0);
        v0 = 0x43C40000;  // 392.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s4, tw::kY);
        add_s(f1, f1, f0);
        v0 = 385;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s4, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        lwc1(f14, s4, tw::kZ);
        jal(ctx, 0x156104u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x0015586c
        charge(ctx, 3);
        v1 = 6;
        if (a2 == v1) {
            // 0x00155cf8
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00155f78
                charge(ctx, 3);
                v1 = slti(s1, 8);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00155d04
                charge(ctx, 2);
                if (s2 != s1) {
                    // 0x00155e44
                    charge(ctx, 3);
                    v0 = 5;
                    if (s1 != v0) {
                        // 0x00155ee8
                        charge(ctx, 3);
                        at = slti(s1, 6);
                        if (at != 0) {
                            // 0x00155f38
                            charge(ctx, 15);
                            lwc1(f1, s4, tw::kY);
                            v0 = sll(s1, 5);
                            v0 = addu(v0, s1);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            a2 = addiu(s1, 135);
                            lbu(a3, s4, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s3, 0);
                            lwc1(f12, s4, tw::kX);
                            lwc1(f14, s4, tw::kZ);
                            jal(ctx, 0x155F6Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x00155ef4
                            charge(ctx, 17);
                            lwc1(f1, s4, tw::kY);
                            v0 = sll(s1, 5);
                            v0 = addu(v0, s1);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            a2 = addiu(s1, 136);
                            lbu(a3, s4, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s3, 0);
                            lwc1(f12, s4, tw::kX);
                            lwc1(f14, s4, tw::kZ);
                            jal(ctx, 0x155F28u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x00155e50
                        charge(ctx, 38);
                        v0 = sll(s1, 5);
                        s5 = addu(v0, s1);
                        lwc1(f1, s4, tw::kY);
                        mtc1(s5, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 140;
                        lwc1(f12, s4, tw::kX);
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155E84u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s4, tw::kY);
                        mtc1(s5, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s4, tw::kX);
                        v0 = 0x43660000;  // 230.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x42BE0000;  // 95.0f
                        mtc1(v0, f0);
                        sub_s(f12, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 141;
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155ED8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                } else {
                    // 0x00155d0c
                    charge(ctx, 3);
                    v0 = 5;
                    if (s1 != v0) {
                        // 0x00155db0
                        charge(ctx, 3);
                        at = slti(s1, 6);
                        if (at != 0) {
                            // 0x00155e00
                            charge(ctx, 17);
                            lwc1(f1, s4, tw::kY);
                            v0 = sll(s1, 5);
                            v0 = addu(v0, s1);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            a2 = addiu(s1, 144);
                            lbu(a3, s4, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s3, 0);
                            lwc1(f12, s4, tw::kX);
                            lwc1(f14, s4, tw::kZ);
                            jal(ctx, 0x155E34u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x00155dbc
                            charge(ctx, 17);
                            lwc1(f1, s4, tw::kY);
                            v0 = sll(s1, 5);
                            v0 = addu(v0, s1);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            a2 = addiu(s1, 145);
                            lbu(a3, s4, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s3, 0);
                            lwc1(f12, s4, tw::kX);
                            lwc1(f14, s4, tw::kZ);
                            jal(ctx, 0x155DF0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x00155d18
                        charge(ctx, 38);
                        v0 = sll(s1, 5);
                        s5 = addu(v0, s1);
                        lwc1(f1, s4, tw::kY);
                        mtc1(s5, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 149;
                        lwc1(f12, s4, tw::kX);
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155D4Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lwc1(f1, s4, tw::kY);
                        mtc1(s5, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s4, tw::kX);
                        v0 = 0x43660000;  // 230.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x42BE0000;  // 95.0f
                        mtc1(v0, f0);
                        sub_s(f12, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 150;
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155DA0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                }
                // 0x00155f74
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00155f84
            charge(ctx, 2);
        } else {
            // 0x00155878
            charge(ctx, 3);
            v1 = 5;
            if (a2 == v1) {
                // 0x00155b88
                charge(ctx, 3);
                s5 = 0;
                for (;;) {
                    // 0x00155c68
                    charge(ctx, 3);
                    v0 = slti(s5, 7);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00155b94
                    charge(ctx, 3);
                    v0 = 2;
                    if (s5 == v0) {
                        // 0x00155ba0
                        charge(ctx, 3);
                        lw(v0, s1, 4);
                        if (v0 != 0) {
                            goto L_00155bac;
                        }
                        goto L_00155c64;
                    }
                L_00155bac:
                    charge(ctx, 6);
                    v0 = sll(s5, 2);
                    v0 = addu(s1, v0);
                    lw(v1, v0, 0);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x00155c08
                        charge(ctx, 23);
                        lwc1(f1, s4, tw::kY);
                        v0 = sll(s5, 5);
                        v0 = addu(v0, s5);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s4, tw::kX);
                        v0 = 0x43D80000;  // 432.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x43C20000;  // 388.0f
                        mtc1(v0, f0);
                        sub_s(f12, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 157;
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155C5Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x00155bc4
                        charge(ctx, 17);
                        lwc1(f1, s4, tw::kY);
                        v0 = sll(s5, 5);
                        v0 = addu(v0, s5);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 156;
                        lwc1(f12, s4, tw::kX);
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155BF8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                L_00155c64:
                    charge(ctx, 1);
                    s5 = addiu(s5, 1);
                }
                // 0x00155c74
                charge(ctx, 3);
                v0 = 7;
                if (s2 == v0) {
                    // 0x00155cbc
                    charge(ctx, 15);
                    lwc1(f1, s4, tw::kY);
                    v0 = 0x43670000;  // 231.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s4, tw::kAlpha);
                    a0 = s0;
                    lw(a1, s3, 0);
                    a2 = 166;
                    lwc1(f12, s4, tw::kX);
                    lwc1(f14, s4, tw::kZ);
                    jal(ctx, 0x155CE8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x00155c80
                    charge(ctx, 15);
                    lwc1(f1, s4, tw::kY);
                    v0 = 0x43670000;  // 231.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s4, tw::kAlpha);
                    a0 = s0;
                    lw(a1, s3, 0);
                    a2 = 165;
                    lwc1(f12, s4, tw::kX);
                    lwc1(f14, s4, tw::kZ);
                    jal(ctx, 0x155CACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
            } else {
                // 0x00155884
                charge(ctx, 3);
                v1 = 4;
                if (a2 == v1) {
                    // 0x00155a88
                    charge(ctx, 3);
                    s2 = 0;
                    for (;;) {
                        // 0x00155b74
                        charge(ctx, 3);
                        v1 = slti(s2, 7);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00155a94
                        charge(ctx, 3);
                        v0 = 2;
                        if (s2 != v0) {
                            // 0x00155b34
                            charge(ctx, 15);
                            lwc1(f1, s4, tw::kY);
                            v0 = sll(s2, 5);
                            v0 = addu(v0, s2);
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f1, f0);
                            lbu(a3, s4, tw::kAlpha);
                            a0 = s0;
                            lw(a1, s3, 0);
                            a2 = 154;
                            lwc1(f12, s4, tw::kX);
                            lwc1(f14, s4, tw::kZ);
                            jal(ctx, 0x155B68u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x00155aa0
                            charge(ctx, 3);
                            lw(v0, s1, 4);
                            if (v0 != 0) {
                                // 0x00155af0
                                charge(ctx, 17);
                                lwc1(f1, s4, tw::kY);
                                v0 = sll(s2, 5);
                                v0 = addu(v0, s2);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f1, f0);
                                lbu(a3, s4, tw::kAlpha);
                                a0 = s0;
                                lw(a1, s3, 0);
                                a2 = 154;
                                lwc1(f12, s4, tw::kX);
                                lwc1(f14, s4, tw::kZ);
                                jal(ctx, 0x155B24u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x00155aac
                                charge(ctx, 17);
                                lwc1(f1, s4, tw::kY);
                                v0 = sll(s2, 5);
                                v0 = addu(v0, s2);
                                mtc1(v0, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f1, f0);
                                lbu(a3, s4, tw::kAlpha);
                                a0 = s0;
                                lw(a1, s3, 0);
                                a2 = 155;
                                lwc1(f12, s4, tw::kX);
                                lwc1(f14, s4, tw::kZ);
                                jal(ctx, 0x155AE0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                        }
                        // 0x00155b70
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                    // 0x00155b80
                    charge(ctx, 2);
                } else {
                    // 0x00155890
                    charge(ctx, 3);
                    v1 = 3;
                    if (a2 == v1) {
                        // 0x00155a44
                        charge(ctx, 17);
                        lwc1(f1, s4, tw::kY);
                        v0 = sll(s2, 5);
                        v0 = addu(v0, s2);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s4, tw::kAlpha);
                        a0 = s0;
                        lw(a1, s3, 0);
                        a2 = 153;
                        lwc1(f12, s4, tw::kX);
                        lwc1(f14, s4, tw::kZ);
                        jal(ctx, 0x155A78u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x0015589c
                        charge(ctx, 3);
                        v1 = 2;
                        if (a2 == v1) {
                            // 0x0015598c
                            charge(ctx, 3);
                            s1 = 0;
                            for (;;) {
                                // 0x00155a30
                                charge(ctx, 3);
                                v1 = slti(s1, 8);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x00155998
                                charge(ctx, 38);
                                v0 = sll(s1, 5);
                                s2 = addu(v0, s1);
                                lwc1(f1, s4, tw::kY);
                                mtc1(s2, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f1, f0);
                                lbu(a3, s4, tw::kAlpha);
                                a0 = s0;
                                lw(a1, s3, 0);
                                a2 = 14;
                                lwc1(f12, s4, tw::kX);
                                lwc1(f14, s4, tw::kZ);
                                jal(ctx, 0x1559CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                lwc1(f1, s4, tw::kY);
                                mtc1(s2, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f1, f0);
                                v0 = 379;
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lwc1(f0, s4, tw::kX);
                                add_s(f1, f1, f0);
                                v0 = 0x42AE0000;  // 87.0f
                                mtc1(v0, f0);
                                sub_s(f12, f1, f0);
                                lbu(a3, s4, tw::kAlpha);
                                a0 = s0;
                                lw(a1, s3, 0);
                                a2 = 14;
                                lwc1(f14, s4, tw::kZ);
                                jal(ctx, 0x155A24u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                s1 = addiu(s1, 1);
                            }
                            // 0x00155a3c
                            charge(ctx, 2);
                        } else {
                            // 0x001558a8
                            charge(ctx, 3);
                            v1 = 1;
                            if (a2 == v1) {
                                // 0x00155928
                                charge(ctx, 25);
                                a0 = 0;
                                lw(a1, s3, 0);
                                a2 = 20;
                                jal(ctx, 0x155934u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                                s0 = v0;
                                lwc1(f0, s4, tw::kZ);
                                swc1(f0, v0, 44);
                                lwc1(f0, s4, tw::kX);
                                swc1(f0, v0, 16);
                                lwc1(f0, s4, tw::kY);
                                swc1(f0, v0, 20);
                                lw(v1, s4, tw::kAlpha);
                                sb(v1, v0, 24);
                                v1 = lui(0xC2B4);
                                sw(v1, v0, 32);
                                a0 = s0;
                                a1 = 1;
                                jal(ctx, 0x155970u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                                a0 = s0;
                                jal(ctx, 0x15597Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
                            } else {
                                // 0x001558b4
                                charge(ctx, 2);
                                if (a2 == 0) {
                                    // 0x001558c4
                                    charge(ctx, 25);
                                    a0 = 0;
                                    lw(a1, s3, 0);
                                    a2 = 30;
                                    jal(ctx, 0x1558D0u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                                    s0 = v0;
                                    lwc1(f0, s4, tw::kZ);
                                    swc1(f0, v0, 44);
                                    lwc1(f0, s4, tw::kX);
                                    swc1(f0, v0, 16);
                                    lwc1(f0, s4, tw::kY);
                                    swc1(f0, v0, 20);
                                    lw(v1, s4, tw::kAlpha);
                                    sb(v1, v0, 24);
                                    v1 = lui(0xC2B4);
                                    sw(v1, v0, 32);
                                    a0 = s0;
                                    a1 = 1;
                                    jal(ctx, 0x15590Cu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                                    a0 = s0;
                                    jal(ctx, 0x155918u, gen::fn_sub_115980_00115980);  // draw and release the handle
                                } else {
                                    // 0x001558bc
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x0015610c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00156140 sub_156140 -- 244 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemRunConfigTweens] (tweens, files, cursor, values): steps the config page's tweens and draws them
// (sub_155830); 1 when all finished.
void sub_156140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00156140
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
        // 0x001561f8
        charge(ctx, 3);
        v0 = slti(s2, 100);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00156184
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x001561a0
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x1561A4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x001561b4
                charge(ctx, 7);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                jal(ctx, 0x1561C8u, gen::fn_sub_155830_00155830);
            }
            // 0x001561d0
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x001561f0
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x001561f4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00156204
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

// 0x00156240 sub_156240 -- 3136 bytes; frame 0x190: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemDrawSpellElement] (tween, files, element, scroll, cursor): one element of the fusion-spell list: 99 the
// frame, 6 the eight rows of skills 272 + scroll + i that flags 5072 + scroll + i unlocked (names from the skill table
// 0x7CE4EC, 19-byte rows), the cursor row tinted, the selected skill's section-2 record (sub_30C220) and the personas
// it needs (datGetPersonaName).
void sub_156240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00156240
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a3;
    s0 = t0;
    v1 = 99;
    if (a2 == v1) {
        // 0x00156d74
        charge(ctx, 55);
        lbu(a3, s3, tw::kAlpha);
        a0 = s5;
        lw(a1, s2, 4);
        a2 = 0;
        lwc1(f12, s3, tw::kX);
        lwc1(f13, s3, tw::kY);
        lwc1(f14, s3, tw::kZ);
        jal(ctx, 0x156D90u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s3, tw::kX);
        v0 = 0x423C0000;  // 47.0f
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lbu(a3, s3, tw::kAlpha);
        a0 = s5;
        lw(a1, s2, 4);
        a2 = 11;
        lwc1(f13, s3, tw::kY);
        lwc1(f14, s3, tw::kZ);
        jal(ctx, 0x156DD4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s3, tw::kX);
        add_s(f1, f1, f0);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s3, tw::kY);
        add_s(f1, f1, f0);
        v0 = 385;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s3, tw::kAlpha);
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        lwc1(f14, s3, tw::kZ);
        jal(ctx, 0x156E48u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x00156284
        charge(ctx, 3);
        v1 = 6;
        if (a2 == v1) {
            // 0x001569f4
            charge(ctx, 3);
            s4 = 0;
            for (;;) {
                // 0x00156d60
                charge(ctx, 3);
                v1 = slti(s4, 8);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00156a00
                charge(ctx, 6);
                v0 = addiu(s4, 5072);
                a0 = addu(v0, s1);
                jal(ctx, 0x156A08u, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x00156c84
                    charge(ctx, 2);
                    if (s0 != s4) {
                        // 0x00156cf8
                        charge(ctx, 25);
                        lwc1(f1, s3, tw::kY);
                        v0 = 0x41700000;  // 15.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = sll(s4, 3);
                        v1 = subu(v0, s4);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s3, tw::kX);
                        v0 = 0x42C60000;  // 99.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s2, 0);
                        a2 = 28;
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x156D54u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x00156c8c
                        charge(ctx, 27);
                        lwc1(f1, s3, tw::kY);
                        v0 = 0x41700000;  // 15.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = sll(s4, 3);
                        v1 = subu(v0, s4);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lwc1(f1, s3, tw::kX);
                        v0 = 0x42C60000;  // 99.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f1);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s2, 0);
                        a2 = 21;
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x156CE8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                } else {
                    // 0x00156a18
                    charge(ctx, 2);
                    if (s0 != s4) {
                        // 0x00156a8c
                        charge(ctx, 25);
                        v0 = sll(s4, 3);
                        v1 = subu(v0, s4);
                        v0 = sll(v1, 2);
                        s6 = addu(v1, v0);
                        lwc1(f1, s3, tw::kY);
                        mtc1(s6, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f1, f0);
                        v0 = 0x3F800000;  // 1.0f
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        a2 = 30;
                        lwc1(f12, s3, tw::kX);
                        t0 = 32;
                        t1 = 67;
                        t2 = 120;
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x156AE8u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    } else {
                        // 0x00156a20
                        charge(ctx, 27);
                        v0 = sll(s4, 3);
                        v1 = subu(v0, s4);
                        v0 = sll(v1, 2);
                        s6 = addu(v1, v0);
                        lwc1(f1, s3, tw::kY);
                        mtc1(s6, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f1, f0);
                        v0 = 0x3F800000;  // 1.0f
                        mtc1(v0, f0);
                        add_s(f13, f0, f1);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                        a2 = 31;
                        lwc1(f12, s3, tw::kX);
                        t0 = 255;
                        t1 = 190;
                        t2 = 95;
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x156A7Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    }
                    // 0x00156af0
                    charge(ctx, 17);
                    lw(v1, s3, tw::kAlpha);
                    v0 = 255;
                    s7 = subu(v0, v1);
                    v0 = addiu(s1, 272);
                    v1 = addu(v0, s4);
                    v0 = sll(v1, 3);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v1 = addu(v0, v1);
                    lw(v0, gp, g::kSkillTable);  // 0x7CE4EC
                    a2 = addu(v0, v1);
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(gp, -30340);  // "%s"
                    jal(ctx, 0x156B24u, gen::fn_sprintf_00523ac8);
                    if (s0 != s4) {
                        // 0x00156bdc
                        charge(ctx, 42);
                        lwc1(f1, s3, tw::kX);
                        v0 = 0x420C0000;  // 35.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        lwc1(f1, s3, tw::kY);
                        v0 = 0x41100000;  // 9.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        mtc1(s6, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f1, f0);
                        v0 = 0x41000000;  // 8.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40400000;  // 3.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        v0 = 0x40000000;  // 2.0f
                        mtc1(v0, f0);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = si(-256);
                        a2 = s7 | v0;
                        lwc1(f12, s3, tw::kZ);
                        a3 = 10;
                        t0 = 1;
                        t1 = addiu(sp, 0x90);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x156C74u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    } else {
                        // 0x00156b34
                        charge(ctx, 42);
                        lwc1(f1, s3, tw::kX);
                        v0 = 0x420C0000;  // 35.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        lwc1(f1, s3, tw::kY);
                        v0 = 0x41100000;  // 9.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        mtc1(s6, f0);
                        cvt_s_w(f0, f0);
                        add_s(f1, f1, f0);
                        v0 = 0x41000000;  // 8.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 0x40400000;  // 3.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        v0 = 0x40000000;  // 2.0f
                        mtc1(v0, f0);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = si(-256);
                        a2 = s7 | v0;
                        lwc1(f12, s3, tw::kZ);
                        a3 = 6;
                        t0 = 1;
                        t1 = addiu(sp, 0x90);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x156BCCu, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    }
                }
                // 0x00156d5c
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x00156d6c
            charge(ctx, 2);
        } else {
            // 0x00156290
            charge(ctx, 3);
            v1 = 5;
            if (a2 == v1) {
                // 0x001569a8
                charge(ctx, 19);
                lwc1(f1, s3, tw::kY);
                v0 = sll(s0, 3);
                v1 = subu(v0, s0);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f1, f0);
                lbu(a3, s3, tw::kAlpha);
                a0 = s5;
                lw(a1, s2, 0);
                a2 = 32;
                lwc1(f12, s3, tw::kX);
                lwc1(f14, s3, tw::kZ);
                jal(ctx, 0x1569E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0015629c
                charge(ctx, 3);
                v1 = 4;
                if (a2 == v1) {
                    // 0x00156890
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x001568e4
                        charge(ctx, 3);
                        v0 = slti(s0, 8);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0015689c
                        charge(ctx, 18);
                        lwc1(f1, s3, tw::kY);
                        v0 = sll(s0, 3);
                        v1 = subu(v0, s0);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f1, f0);
                        lbu(a3, s3, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s2, 0);
                        a2 = 41;
                        lwc1(f12, s3, tw::kX);
                        lwc1(f14, s3, tw::kZ);
                        jal(ctx, 0x1568D8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        s0 = addiu(s0, 1);
                    }
                    // 0x001568f0
                    charge(ctx, 46);
                    v0 = 271;
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s3, tw::kX);
                    add_s(f12, f1, f0);
                    lwc1(f1, s3, tw::kY);
                    v0 = 0x432F0000;  // 175.0f
                    mtc1(v0, f0);
                    add_s(f13, f0, f1);
                    lbu(a3, s3, tw::kAlpha);
                    a0 = s5;
                    lw(a1, s2, 0);
                    a2 = 33;
                    lwc1(f14, s3, tw::kZ);
                    jal(ctx, 0x156930u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v1 = sll(s1, 6);
                    v0 = 10;
                    div(v1, v0);
                    mflo(v1);
                    lwc1(f1, s3, tw::kY);
                    v0 = 0x43330000;  // 179.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f1, f0);
                    v0 = 271;
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s3, tw::kX);
                    add_s(f12, f1, f0);
                    lbu(a3, s3, tw::kAlpha);
                    a0 = s5;
                    lw(a1, s2, 0);
                    a2 = 34;
                    lwc1(f14, s3, tw::kZ);
                    jal(ctx, 0x156998u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x001562a8
                    charge(ctx, 3);
                    v1 = 3;
                    if (a2 == v1) {
                        // 0x001567c0
                        charge(ctx, 52);
                        a0 = 0;
                        lw(a1, s2, 0);
                        a2 = 18;
                        jal(ctx, 0x1567CCu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                        s5 = v0;
                        lwc1(f0, s3, tw::kZ);
                        swc1(f0, v0, 44);
                        lwc1(f0, s3, tw::kX);
                        swc1(f0, v0, 16);
                        lwc1(f0, s3, tw::kY);
                        swc1(f0, v0, 20);
                        lw(v1, s3, tw::kAlpha);
                        sb(v1, v0, 24);
                        v1 = lui(0xC2B4);
                        sw(v1, v0, 32);
                        a0 = s5;
                        a1 = 1;
                        jal(ctx, 0x156808u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                        a0 = s5;
                        jal(ctx, 0x156814u, gen::fn_sub_115980_00115980);  // draw and release the handle
                        a0 = 0;
                        lw(a1, s2, 0);
                        a2 = 168;
                        jal(ctx, 0x156828u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                        s0 = v0;
                        lwc1(f0, s3, tw::kZ);
                        swc1(f0, v0, 44);
                        lwc1(f0, s3, tw::kX);
                        swc1(f0, v0, 16);
                        lwc1(f1, s3, tw::kY);
                        v1 = 0x436B0000;  // 235.0f
                        mtc1(v1, f0);
                        sub_s(f0, f1, f0);
                        swc1(f0, v0, 20);
                        lw(v1, s3, tw::kAlpha);
                        sb(v1, v0, 24);
                        v1 = lui(0xC2B4);
                        sw(v1, v0, 32);
                        a0 = s0;
                        a1 = 1;
                        jal(ctx, 0x156874u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                        a0 = s0;
                        jal(ctx, 0x156880u, gen::fn_sub_115980_00115980);  // draw and release the handle
                    } else {
                        // 0x001562b4
                        charge(ctx, 3);
                        v1 = 2;
                        if (a2 == v1) {
                            // 0x00156758
                            charge(ctx, 9);
                            lw(v1, s3, tw::kAlpha);
                            v0 = 255;
                            s2 = subu(v0, v1);
                            v0 = addiu(s0, 5072);
                            a0 = addu(v0, s1);
                            jal(ctx, 0x15676Cu, gen::fn_datGetFlag_0016f190);
                            if (v0 != 0) {
                                // 0x0015677c
                                charge(ctx, 17);
                                lwc1(f0, s3, tw::kX);
                                cvt_w_s(f0, f0);
                                mfc1(a0, f0);
                                lwc1(f0, s3, tw::kY);
                                cvt_w_s(f0, f0);
                                mfc1(a1, f0);
                                v0 = si(-256);
                                a2 = s2 | v0;
                                t2 = addu(s0, s1);
                                lwc1(f12, s3, tw::kZ);
                                a3 = 1;
                                t0 = 10;
                                t1 = 8;
                                jal(ctx, 0x1567B0u, gen::fn_sub_3C7E20_003c7e20);  // a message text
                            }
                        } else {
                            // 0x001562c0
                            charge(ctx, 3);
                            v1 = 1;
                            if (a2 == v1) {
                                // 0x00156308
                                charge(ctx, 3);
                                s4 = 0;
                                for (;;) {
                                    // 0x0015639c
                                    charge(ctx, 3);
                                    v0 = slti(s4, 2);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x00156314
                                    charge(ctx, 34);
                                    lwc1(f1, s3, tw::kY);
                                    v0 = 0x42EA0000;  // 117.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = sll(s4, 3);
                                    v0 = subu(v0, s4);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, s4);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f1, f0);
                                    v0 = 0x42AE0000;  // 87.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lwc1(f1, s3, tw::kX);
                                    v0 = 0x41B80000;  // 23.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42040000;  // 33.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    lbu(a3, s3, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s2, 0);
                                    a2 = 42;
                                    lwc1(f14, s3, tw::kZ);
                                    jal(ctx, 0x156390u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s4 = addiu(s4, 1);
                                }
                                // 0x001563a8
                                charge(ctx, 28);
                                lwc1(f1, s3, tw::kX);
                                v0 = 0x43880000;  // 272.0f
                                mtc1(v0, f0);
                                add_s(f1, f0, f1);
                                v0 = 0x42040000;  // 33.0f
                                mtc1(v0, f0);
                                sub_s(f12, f1, f0);
                                lwc1(f0, s3, tw::kY);
                                v0 = 0x42AE0000;  // 87.0f
                                mtc1(v0, f1);
                                add_s(f0, f1, f0);
                                sub_s(f13, f0, f1);
                                lbu(a3, s3, tw::kAlpha);
                                a0 = s5;
                                lw(a1, s2, 0);
                                a2 = 40;
                                lwc1(f14, s3, tw::kZ);
                                jal(ctx, 0x1563F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                v0 = addiu(s0, 5072);
                                a0 = addu(v0, s1);
                                jal(ctx, 0x156408u, gen::fn_datGetFlag_0016f190);
                                if (v0 == 0) {
                                    // 0x00156690
                                    charge(ctx, 50);
                                    lwc1(f0, s3, tw::kX);
                                    v0 = 0x42FE0000;  // 127.0f
                                    mtc1(v0, f2);
                                    add_s(f1, f2, f0);
                                    v0 = 0x42040000;  // 33.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    lwc1(f0, s3, tw::kY);
                                    add_s(f1, f2, f0);
                                    v0 = 0x42AE0000;  // 87.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s3, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s2, 0);
                                    a2 = 28;
                                    lwc1(f14, s3, tw::kZ);
                                    jal(ctx, 0x1566E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lwc1(f0, s3, tw::kX);
                                    v0 = 0x42FE0000;  // 127.0f
                                    mtc1(v0, f2);
                                    add_s(f1, f2, f0);
                                    v0 = 0x42040000;  // 33.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    lwc1(f0, s3, tw::kY);
                                    add_s(f1, f2, f0);
                                    v0 = 0x42AE0000;  // 87.0f
                                    mtc1(v0, f0);
                                    sub_s(f1, f1, f0);
                                    v0 = 0x41E00000;  // 28.0f
                                    mtc1(v0, f0);
                                    add_s(f13, f0, f1);
                                    lbu(a3, s3, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s2, 0);
                                    a2 = 28;
                                    lwc1(f14, s3, tw::kZ);
                                    jal(ctx, 0x156748u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x00156418
                                    charge(ctx, 158);
                                    lbu(a3, s3, tw::kAlpha);
                                    a0 = s5;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                                    a2 = 31;
                                    lwc1(f12, s3, tw::kX);
                                    lwc1(f13, s3, tw::kY);
                                    lwc1(f14, s3, tw::kZ);
                                    jal(ctx, 0x156438u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lw(v1, s3, tw::kAlpha);
                                    v0 = 255;
                                    s2 = subu(v0, v1);
                                    v0 = addiu(s1, 272);
                                    s0 = addu(v0, s0);
                                    v0 = sll(s0, 3);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 1);
                                    v1 = addu(v0, s0);
                                    lw(v0, gp, g::kSkillTable);  // 0x7CE4EC
                                    a2 = addu(v0, v1);
                                    a0 = addiu(sp, 0x90);
                                    a1 = addiu(gp, -30340);  // "%s"
                                    jal(ctx, 0x156474u, gen::fn_sprintf_00523ac8);
                                    v0 = si(-256);
                                    s1 = s2 | v0;
                                    lwc1(f1, s3, tw::kX);
                                    v0 = 0x42880000;  // 68.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42040000;  // 33.0f
                                    mtc1(v0, f0);
                                    sub_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(a0, f0);
                                    lwc1(f1, s3, tw::kY);
                                    v0 = 0x42C00000;  // 96.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42AE0000;  // 87.0f
                                    mtc1(v0, f0);
                                    sub_s(f1, f1, f0);
                                    v0 = 0x40000000;  // 2.0f
                                    mtc1(v0, f0);
                                    add_s(f0, f0, f1);
                                    cvt_w_s(f0, f0);
                                    mfc1(a1, f0);
                                    lwc1(f12, s3, tw::kZ);
                                    a2 = s1;
                                    a3 = 6;
                                    t0 = 1;
                                    t1 = addiu(sp, 0x90);
                                    t2 = 16;
                                    t3 = 0;
                                    jal(ctx, 0x156508u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                                    a0 = s0 & 0xFFFF;
                                    jal(ctx, 0x156514u, gen::fn_sub_30C220_0030c220);  // [datGetSkillSection2]
                                    s0 = v0;
                                    lhu(a0, v0, 2);
                                    jal(ctx, 0x156524u, gen::fn_sub_173220_00173220);  // [datGetPersonaName]
                                    a0 = addiu(sp, 0x90);
                                    a1 = addiu(gp, -30340);  // "%s"
                                    a2 = v0;
                                    jal(ctx, 0x156538u, gen::fn_sprintf_00523ac8);
                                    lwc1(f1, s3, tw::kX);
                                    v0 = 0x42880000;  // 68.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42040000;  // 33.0f
                                    mtc1(v0, f0);
                                    sub_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(a0, f0);
                                    lwc1(f1, s3, tw::kY);
                                    v0 = 0x42F40000;  // 122.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42AE0000;  // 87.0f
                                    mtc1(v0, f0);
                                    sub_s(f1, f1, f0);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    add_s(f0, f0, f1);
                                    cvt_w_s(f0, f0);
                                    mfc1(a1, f0);
                                    lwc1(f12, s3, tw::kZ);
                                    a2 = s1;
                                    a3 = 10;
                                    t0 = 1;
                                    t1 = addiu(sp, 0x90);
                                    t2 = 16;
                                    t3 = 0;
                                    jal(ctx, 0x1565C4u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                                    lhu(a0, s0, 4);
                                    jal(ctx, 0x1565D0u, gen::fn_sub_173220_00173220);  // [datGetPersonaName]
                                    a0 = addiu(sp, 0x90);
                                    a1 = addiu(gp, -30340);  // "%s"
                                    a2 = v0;
                                    jal(ctx, 0x1565E4u, gen::fn_sprintf_00523ac8);
                                    lwc1(f1, s3, tw::kX);
                                    v0 = 0x42880000;  // 68.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42040000;  // 33.0f
                                    mtc1(v0, f0);
                                    sub_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(a0, f0);
                                    lwc1(f1, s3, tw::kY);
                                    v0 = 0x42F40000;  // 122.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42AE0000;  // 87.0f
                                    mtc1(v0, f0);
                                    sub_s(f1, f1, f0);
                                    v0 = 0x41E80000;  // 29.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    add_s(f0, f0, f1);
                                    cvt_w_s(f0, f0);
                                    mfc1(a1, f0);
                                    lwc1(f12, s3, tw::kZ);
                                    a2 = s1;
                                    a3 = 10;
                                    t0 = 1;
                                    t1 = addiu(sp, 0x90);
                                    t2 = 16;
                                    t3 = 0;
                                    jal(ctx, 0x156680u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                                }
                            } else {
                                // 0x001562cc
                                charge(ctx, 2);
                                if (a2 == 0) {
                                    // 0x001562dc
                                    charge(ctx, 11);
                                    lbu(a3, s3, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s2, 0);
                                    a2 = 27;
                                    lwc1(f12, s3, tw::kX);
                                    lwc1(f13, s3, tw::kY);
                                    lwc1(f14, s3, tw::kZ);
                                    jal(ctx, 0x1562F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x001562d4
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x00156e50 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x190);
}

// 0x00156E80 sub_156E80 -- 244 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemRunSpellTweens] (tweens, files, scroll, cursor): steps the fusion-spell list's tweens and draws them
// (sub_156240); 1 when all finished.
void sub_156E80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00156e80
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
        // 0x00156f38
        charge(ctx, 3);
        v0 = slti(s2, 100);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00156ec4
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x00156ee0
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x156EE4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x00156ef4
                charge(ctx, 7);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                jal(ctx, 0x156F08u, gen::fn_sub_156240_00156240);
            }
            // 0x00156f10
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x00156f30
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x00156f34
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x00156f44
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

// 0x00156F80 sub_156F80 -- 10616 bytes; frame 0x1D0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [H_Camp_SystemDrawQuestElement] (tween, files, element, ...): one element of the quest (request) list: 99 the frame,
// 13 the selected request's detail (datBlock27Get, the request record sub_403880: the reward item's icon / name, the
// required items and their counts, the state marks), the list rows with their numbers (font 1 / 2) and state sprites.
void sub_156F80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00156f80
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1D0);
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
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s7 = a3;
    v1 = 99;
    if (a2 == v1) {
        // 0x001597e0
        charge(ctx, 55);
        lbu(a3, s1, tw::kAlpha);
        a0 = s5;
        lw(a1, s0, 4);
        a2 = 0;
        lwc1(f12, s1, tw::kX);
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x1597FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s1, tw::kX);
        v0 = 0x423C0000;  // 47.0f
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lbu(a3, s1, tw::kAlpha);
        a0 = s5;
        lw(a1, s0, 4);
        a2 = 10;
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x159840u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, tw::kX);
        add_s(f1, f1, f0);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s1, tw::kY);
        add_s(f1, f1, f0);
        v0 = 385;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s1, tw::kAlpha);
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x1598B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x00156fcc
        charge(ctx, 3);
        v1 = 13;
        if (a2 == v1) {
            // 0x00158b98
            charge(ctx, 9);
            lw(v1, s1, tw::kAlpha);
            v0 = 255;
            s3 = subu(v0, v1);
            a0 = s7;
            jal(ctx, 0x158BA8u, gen::fn_sub_17C670_0017c670);  // [datBlock27Get]
            s6 = v0;
            if (s6 != 0) {
                // 0x00158d0c
                charge(ctx, 8);
                lh(a0, s6, 0);
                jal(ctx, 0x158D10u, gen::fn_sub_403880_00403880);
                s2 = v0;
                lbu(v1, v0, 6);
                v0 = 3;
                if (v1 == v0) {
                    // 0x0015958c
                    charge(ctx, 60);
                    lw(a2, s2, 8);
                    lwc1(f0, s1, tw::kX);
                    v0 = 0x42EE0000;  // 119.0f
                    mtc1(v0, f1);
                    add_s(f0, f1, f0);
                    sub_s(f21, f0, f1);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x43AD0000;  // 346.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = 333;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    sub_s(f20, f1, f0);
                    a0 = addiu(sp, 0xC0);
                    a1 = addiu(gp, -30332);  // "%7d"
                    jal(ctx, 0x1595D8u, gen::fn_sprintf_00523ac8);
                    cvt_w_s(f0, f21);
                    mfc1(a0, f0);
                    cvt_w_s(f0, f20);
                    mfc1(a1, f0);
                    lw(v1, s1, tw::kAlpha);
                    v0 = 255;
                    v0 = subu(v0, v1);
                    a2 = v0 & 0xFF;
                    lwc1(f12, s1, tw::kZ);
                    a3 = 3;
                    t0 = addiu(sp, 0xC0);
                    t1 = 8;
                    jal(ctx, 0x159610u, gen::fn_sub_40EB50_0040eb50);  // text / number at (x, y)
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f21, f0);
                    v0 = 0x40400000;  // 3.0f
                    mtc1(v0, f0);
                    add_s(f12, f0, f1);
                    lwc1(f1, s1, tw::kY);
                    v0 = 0x43AA0000;  // 340.0f
                    mtc1(v0, f0);
                    add_s(f1, f0, f1);
                    v0 = 333;
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    sub_s(f13, f1, f0);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s5;
                    lw(a1, s0, 0);
                    a2 = 53;
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x159674u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x00158d2c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x00158d3c
                        charge(ctx, 6);
                        lh(a0, s2, 8);
                        jal(ctx, 0x158D40u, gen::fn_sub_171250_00171250);  // [datGetItemKind] (id / 1000)
                        v1 = 4;
                        if (v0 == v1) {
                            // 0x00158d5c
                            charge(ctx, 87);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                            a2 = 27;
                            lwc1(f12, s1, tw::kX);
                            lwc1(f13, s1, tw::kY);
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x158D7Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lb(v0, s2, 10);
                            a1 = dsll32(v0, 28);
                            a1 = dsra32(a1, 28);
                            lh(a0, s2, 8);
                            jal(ctx, 0x158D94u, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                            a0 = addiu(sp, 0xC0);
                            a1 = addiu(gp, -30340);  // "%s"
                            a2 = v0;
                            jal(ctx, 0x158DA8u, gen::fn_sprintf_00523ac8);
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x431A0000;  // 154.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x42EE0000;  // 119.0f
                            mtc1(v0, f0);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x41100000;  // 9.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x40000000;  // 2.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = si(-256);
                            a2 = s3 | v0;
                            lwc1(f12, s1, tw::kZ);
                            a3 = 6;
                            t0 = 1;
                            t1 = addiu(sp, 0xC0);
                            t2 = 17;
                            t3 = 0;
                            jal(ctx, 0x158E28u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                            s4 = v0;
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x431A0000;  // 154.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x42EE0000;  // 119.0f
                            mtc1(v0, f0);
                            sub_s(f1, f1, f0);
                            mtc1(s4, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f1, f0);
                            v0 = 0x40C00000;  // 6.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x40E00000;  // 7.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s5;
                            lw(a1, s0, 0);
                            a2 = 51;
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x158EA0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lbu(s3, s2, 7);
                            v0 = slti(s3, 10);
                            if (v0 != 0) {
                                // 0x00159060
                                charge(ctx, 53);
                                a0 = 1;
                                jal(ctx, 0x159064u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x431A0000;  // 154.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x42EE0000;  // 119.0f
                                mtc1(v1, f0);
                                sub_s(f1, f1, f0);
                                mtc1(s4, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40C00000;  // 6.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x40A00000;  // 5.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41200000;  // 10.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                v1 = 10;
                                div(s3, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kY);
                                v1 = 0x41500000;  // 13.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x159124u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x00158eb8
                                charge(ctx, 106);
                                a0 = 1;
                                jal(ctx, 0x158EBCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x431A0000;  // 154.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x42EE0000;  // 119.0f
                                mtc1(v1, f0);
                                sub_s(f1, f1, f0);
                                mtc1(s4, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40C00000;  // 6.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x40A00000;  // 5.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41200000;  // 10.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                v1 = 10;
                                div(s3, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kY);
                                v1 = 0x41500000;  // 13.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x158F7Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                a0 = 1;
                                jal(ctx, 0x158F88u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x431A0000;  // 154.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x42EE0000;  // 119.0f
                                mtc1(v1, f0);
                                sub_s(f1, f1, f0);
                                mtc1(s4, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40C00000;  // 6.0f
                                mtc1(v1, f0);
                                add_s(f0, f0, f1);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f1);
                                add_s(f0, f1, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40A00000;  // 5.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41200000;  // 10.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                lbu(a0, s2, 7);
                                v1 = 10;
                                div(a0, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kY);
                                v1 = 0x41500000;  // 13.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x159050u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                        } else {
                            // 0x00158d54
                            charge(ctx, 2);
                            // 0x00159134
                            charge(ctx, 9);
                            lh(a0, s2, 8);
                            a1 = addiu(sp, 0x1CC);
                            jal(ctx, 0x15913Cu, gen::fn_sub_170ED0_00170ed0);
                            a0 = 0;
                            lw(a1, sp, 0x1CC);
                            v1 = 3;
                            if (a1 == v1) {
                                // 0x001591a4
                                charge(ctx, 1);
                                lw(a0, v0, 0);
                            } else {
                                // 0x00159158
                                charge(ctx, 3);
                                v1 = 2;
                                if (a1 == v1) {
                                    // 0x00159198
                                    charge(ctx, 3);
                                    lw(a0, v0, 4);
                                } else {
                                    // 0x00159164
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (a1 == v1) {
                                        // 0x0015918c
                                        charge(ctx, 3);
                                        lw(a0, v0, 4);
                                    } else {
                                        // 0x00159170
                                        charge(ctx, 2);
                                        if (a1 == 0) {
                                            // 0x00159180
                                            charge(ctx, 3);
                                            lw(a0, v0, 4);
                                        } else {
                                            // 0x00159178
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                            // 0x001591a8
                            charge(ctx, 90);
                            jal(ctx, 0x1591A8u, gen::fn_sub_12DF50_0012df50);  // mask -> icon index
                            v0 = sll(v0, 1);
                            a2 = addiu(v0, 1);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                            lwc1(f12, s1, tw::kX);
                            lwc1(f13, s1, tw::kY);
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x1591D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lb(v0, s2, 10);
                            a1 = dsll32(v0, 28);
                            a1 = dsra32(a1, 28);
                            lh(a0, s2, 8);
                            jal(ctx, 0x1591ECu, gen::fn_sub_171110_00171110);  // [datGetItemName] (id, column)
                            a0 = addiu(sp, 0xC0);
                            a1 = addiu(gp, -30340);  // "%s"
                            a2 = v0;
                            jal(ctx, 0x159200u, gen::fn_sprintf_00523ac8);
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x431A0000;  // 154.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x42EE0000;  // 119.0f
                            mtc1(v0, f0);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x41100000;  // 9.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x40000000;  // 2.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = si(-256);
                            a2 = s3 | v0;
                            lwc1(f12, s1, tw::kZ);
                            a3 = 6;
                            t0 = 1;
                            t1 = addiu(sp, 0xC0);
                            t2 = 17;
                            t3 = 0;
                            jal(ctx, 0x159280u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                            s4 = v0;
                            lwc1(f1, s1, tw::kX);
                            v0 = 0x431A0000;  // 154.0f
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x42EE0000;  // 119.0f
                            mtc1(v0, f0);
                            sub_s(f1, f1, f0);
                            mtc1(s4, f0);
                            cvt_s_w(f0, f0);
                            add_s(f1, f1, f0);
                            v0 = 0x40C00000;  // 6.0f
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, tw::kY);
                            v0 = 0x40E00000;  // 7.0f
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s5;
                            lw(a1, s0, 0);
                            a2 = 51;
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x1592F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            lbu(s3, s2, 7);
                            v0 = slti(s3, 10);
                            if (v0 != 0) {
                                // 0x001594b8
                                charge(ctx, 53);
                                a0 = 1;
                                jal(ctx, 0x1594BCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x431A0000;  // 154.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x42EE0000;  // 119.0f
                                mtc1(v1, f0);
                                sub_s(f1, f1, f0);
                                mtc1(s4, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40C00000;  // 6.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x40A00000;  // 5.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41200000;  // 10.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                v1 = 10;
                                div(s3, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kY);
                                v1 = 0x41500000;  // 13.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x15957Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            } else {
                                // 0x00159310
                                charge(ctx, 106);
                                a0 = 1;
                                jal(ctx, 0x159314u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x431A0000;  // 154.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x42EE0000;  // 119.0f
                                mtc1(v1, f0);
                                sub_s(f1, f1, f0);
                                mtc1(s4, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40C00000;  // 6.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x40A00000;  // 5.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41200000;  // 10.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                v1 = 10;
                                div(s3, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kY);
                                v1 = 0x41500000;  // 13.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x1593D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                a0 = 1;
                                jal(ctx, 0x1593E0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x431A0000;  // 154.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x42EE0000;  // 119.0f
                                mtc1(v1, f0);
                                sub_s(f1, f1, f0);
                                mtc1(s4, f0);
                                cvt_s_w(f0, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40C00000;  // 6.0f
                                mtc1(v1, f0);
                                add_s(f0, f0, f1);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f1);
                                add_s(f0, f1, f0);
                                add_s(f1, f1, f0);
                                v1 = 0x40A00000;  // 5.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x41200000;  // 10.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                lbu(a0, s2, 7);
                                v1 = 10;
                                div(a0, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kY);
                                v1 = 0x41500000;  // 13.0f
                                mtc1(v1, f0);
                                add_s(f1, f0, f1);
                                v1 = 0x3F800000;  // 1.0f
                                mtc1(v1, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s5;
                                a1 = v0;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x1594A8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                        }
                    } else {
                        // 0x00158d34
                        charge(ctx, 2);
                    }
                }
                // 0x0015967c
                charge(ctx, 7);
                lh(a0, s6, 0);
                jal(ctx, 0x159680u, gen::fn_sub_403900_00403900);
                s2 = v0;
                s3 = 0;
                for (;;) {
                    // 0x001597cc
                    charge(ctx, 3);
                    v1 = slti(s3, 5);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00159698
                    charge(ctx, 4);
                    v0 = addiu(s3, 1);
                    v0 = slt(s2, v0);
                    if (v0 != 0) {
                        // 0x0015973c
                        charge(ctx, 35);
                        v0 = 499;
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s1, tw::kX);
                        add_s(f1, f1, f0);
                        v0 = 0x42EE0000;  // 119.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        v0 = sll(s3, 1);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, s3);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f12, f1, f0);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x43AA0000;  // 340.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 333;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f13, f1, f0);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s0, 0);
                        a2 = 162;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x1597C0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x001596a8
                        charge(ctx, 37);
                        v0 = 499;
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s1, tw::kX);
                        add_s(f1, f1, f0);
                        v0 = 0x42EE0000;  // 119.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        v0 = sll(s3, 1);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, s3);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f12, f1, f0);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x43AA0000;  // 340.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 333;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f13, f1, f0);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s0, 0);
                        a2 = 161;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x15972Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x001597c8
                    charge(ctx, 1);
                    s3 = addiu(s3, 1);
                }
                // 0x001597d8
                charge(ctx, 2);
            } else {
                // 0x00158bbc
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x00158cf8
                    charge(ctx, 3);
                    v1 = slti(s2, 5);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00158bc8
                    charge(ctx, 3);
                    v0 = addiu(s2, 1);
                    if (i64(v0) > 0) {
                        // 0x00158c68
                        charge(ctx, 35);
                        v0 = 499;
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s1, tw::kX);
                        add_s(f1, f1, f0);
                        v0 = 0x42EE0000;  // 119.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, s2);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f12, f1, f0);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x43AA0000;  // 340.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 333;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f13, f1, f0);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s0, 0);
                        a2 = 162;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x158CECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x00158bd4
                        charge(ctx, 37);
                        v0 = 499;
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        lwc1(f0, s1, tw::kX);
                        add_s(f1, f1, f0);
                        v0 = 0x42EE0000;  // 119.0f
                        mtc1(v0, f0);
                        sub_s(f1, f1, f0);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 3);
                        v0 = subu(v0, s2);
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f12, f1, f0);
                        lwc1(f1, s1, tw::kY);
                        v0 = 0x43AA0000;  // 340.0f
                        mtc1(v0, f0);
                        add_s(f1, f0, f1);
                        v0 = 333;
                        mtc1(v0, f0);
                        cvt_s_w(f0, f0);
                        sub_s(f13, f1, f0);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s0, 0);
                        a2 = 161;
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x158C58u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                    // 0x00158cf4
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00158d04
                charge(ctx, 2);
            }
        } else {
            // 0x00156fd8
            charge(ctx, 3);
            v1 = 12;
            if (a2 == v1) {
                // 0x00158b28
                charge(ctx, 28);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                lw(a1, s0, 0);
                a2 = 50;
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x158B44u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x43D40000;  // 424.0f
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                v0 = 0x426C0000;  // 59.0f
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                lbu(a3, s1, tw::kAlpha);
                a0 = s5;
                lw(a1, s0, 0);
                a2 = 160;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x158B88u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x00156fe4
                charge(ctx, 3);
                v1 = 11;
                if (a2 == v1) {
                    // 0x00158afc
                    charge(ctx, 11);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s5;
                    lw(a1, s0, 0);
                    a2 = 44;
                    lwc1(f12, s1, tw::kX);
                    lwc1(f13, s1, tw::kY);
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x158B18u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x00156ff0
                    charge(ctx, 3);
                    v1 = 10;
                    if (a2 == v1) {
                        // 0x00158a74
                        charge(ctx, 8);
                        lw(v1, s1, tw::kAlpha);
                        v0 = 255;
                        s0 = subu(v0, v1);
                        a0 = s7;
                        jal(ctx, 0x158A84u, gen::fn_sub_17C670_0017c670);  // [datBlock27Get]
                        if (v0 != 0) {
                            // 0x00158a94
                            charge(ctx, 26);
                            lwc1(f0, s1, tw::kX);
                            cvt_w_s(f0, f0);
                            mfc1(a0, f0);
                            lwc1(f1, s1, tw::kY);
                            v1 = 0x40000000;  // 2.0f
                            mtc1(v1, f0);
                            sub_s(f1, f1, f0);
                            v1 = 0x40400000;  // 3.0f
                            mtc1(v1, f0);
                            sub_s(f0, f1, f0);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            lwc1(f0, s1, tw::kZ);
                            cvt_w_s(f0, f0);
                            mfc1(a2, f0);
                            v1 = si(-256);
                            a3 = s0 | v1;
                            lh(t2, v0, 0);
                            t0 = 1;
                            t1 = 10;
                            jal(ctx, 0x158AECu, gen::fn_sub_17C6E0_0017c6e0);
                        }
                    } else {
                        // 0x00156ffc
                        charge(ctx, 3);
                        v1 = 9;
                        if (a2 == v1) {
                            // 0x00158a48
                            charge(ctx, 11);
                            lbu(a3, s1, tw::kAlpha);
                            a0 = s5;
                            lw(a1, s0, 0);
                            a2 = 45;
                            lwc1(f12, s1, tw::kX);
                            lwc1(f13, s1, tw::kY);
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x158A64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        } else {
                            // 0x00157008
                            charge(ctx, 3);
                            v1 = 8;
                            if (a2 == v1) {
                                // 0x00157460
                                charge(ctx, 9);
                                lw(a0, s1, tw::kAlpha);
                                v1 = 255;
                                a0 = subu(v1, a0);
                                s3 = 0;
                                v1 = si(-256);
                                v1 = a0 | v1;
                                sw(v1, sp, 0xB0);
                                for (;;) {
                                    // 0x00158a34
                                    charge(ctx, 3);
                                    v1 = slti(s3, 3);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x00157484
                                    charge(ctx, 37);
                                    lwc1(f1, s1, tw::kX);
                                    v0 = 0x42F00000;  // 120.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42700000;  // 60.0f
                                    mtc1(v0, f0);
                                    sub_s(f21, f1, f0);
                                    v0 = 0x420C0000;  // 35.0f
                                    mtc1(v0, f3);
                                    mtc1(s3, f0);
                                    cvt_s_w(f2, f0);
                                    lwc1(f1, s1, tw::kY);
                                    v0 = 0x42CC0000;  // 102.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42D80000;  // 108.0f
                                    mtc1(v0, f0);
                                    sub_s(f1, f1, f0);
                                    mtc1(zero, f0);
                                    adda_s(f0, f1);
                                    madd_s(f1, f3, f2);
                                    v0 = 0x40400000;  // 3.0f
                                    mtc1(v0, f0);
                                    sub_s(f20, f1, f0);
                                    a0 = s3;
                                    jal(ctx, 0x157504u, gen::fn_sub_17C670_0017c670);  // [datBlock27Get]
                                    s2 = v0;
                                    if (s2 == 0) {
                                        // 0x00158918
                                        charge(ctx, 2);
                                        if (s7 != s3) {
                                            // 0x001589ac
                                            charge(ctx, 33);
                                            lwc1(f1, s1, tw::kY);
                                            v0 = 0x42DA0000;  // 109.0f
                                            mtc1(v0, f0);
                                            add_s(f1, f0, f1);
                                            v0 = 0x42D80000;  // 108.0f
                                            mtc1(v0, f0);
                                            sub_s(f1, f1, f0);
                                            v0 = sll(s3, 3);
                                            v1 = subu(v0, s3);
                                            v0 = sll(v1, 2);
                                            v0 = addu(v1, v0);
                                            mtc1(v0, f0);
                                            cvt_s_w(f0, f0);
                                            add_s(f13, f1, f0);
                                            lwc1(f1, s1, tw::kX);
                                            v0 = 0x43C00000;  // 384.0f
                                            mtc1(v0, f0);
                                            add_s(f1, f0, f1);
                                            v0 = 0x42700000;  // 60.0f
                                            mtc1(v0, f0);
                                            sub_s(f12, f1, f0);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 29;
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x158A28u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        } else {
                                            // 0x00158920
                                            charge(ctx, 35);
                                            lwc1(f1, s1, tw::kY);
                                            v0 = 0x42DA0000;  // 109.0f
                                            mtc1(v0, f0);
                                            add_s(f1, f0, f1);
                                            v0 = 0x42D80000;  // 108.0f
                                            mtc1(v0, f0);
                                            sub_s(f1, f1, f0);
                                            v0 = sll(s3, 3);
                                            v1 = subu(v0, s3);
                                            v0 = sll(v1, 2);
                                            v0 = addu(v1, v0);
                                            mtc1(v0, f0);
                                            cvt_s_w(f0, f0);
                                            add_s(f13, f1, f0);
                                            lwc1(f1, s1, tw::kX);
                                            v0 = 0x43C00000;  // 384.0f
                                            mtc1(v0, f0);
                                            add_s(f1, f0, f1);
                                            v0 = 0x42700000;  // 60.0f
                                            mtc1(v0, f0);
                                            sub_s(f12, f1, f0);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 164;
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x15899Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        }
                                    } else {
                                        // 0x00157518
                                        charge(ctx, 2);
                                        if (s7 != s3) {
                                            // 0x00157cd0
                                            charge(ctx, 6);
                                            lh(a0, s2, 0);
                                            jal(ctx, 0x157CD4u, gen::fn_sub_403380_00403380);
                                            v1 = 2;
                                            if (v0 != v1) {
                                                // 0x00157d74
                                                charge(ctx, 7);
                                                lh(a0, s2, 0);
                                                jal(ctx, 0x157D78u, gen::fn_sub_403800_00403800);
                                                s6 = dsll32(v0, 16);
                                                s6 = dsra32(s6, 16);
                                                if (s6 == 0) {
                                                    // 0x001582f4
                                                    charge(ctx, 33);
                                                    v0 = sll(s3, 3);
                                                    v1 = subu(v0, s3);
                                                    v0 = sll(v1, 2);
                                                    s4 = addu(v1, v0);
                                                    lwc1(f1, s1, tw::kY);
                                                    v0 = 0x42CA0000;  // 101.0f
                                                    mtc1(v0, f0);
                                                    add_s(f1, f0, f1);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f1, f1, f0);
                                                    v0 = 0x42D80000;  // 108.0f
                                                    mtc1(v0, f0);
                                                    sub_s(f13, f1, f0);
                                                    lwc1(f1, s1, tw::kX);
                                                    v0 = 0x44070000;  // 540.0f
                                                    mtc1(v0, f0);
                                                    add_s(f1, f0, f1);
                                                    v0 = 0x42700000;  // 60.0f
                                                    mtc1(v0, f0);
                                                    sub_s(f12, f1, f0);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    lw(a1, s0, 0);
                                                    a2 = 167;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x158370u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                } else {
                                                    // 0x00157d90
                                                    charge(ctx, 3);
                                                    v0 = slti(s6, 10);
                                                    if (v0 == 0) {
                                                        // 0x00157d9c
                                                        charge(ctx, 31);
                                                        a0 = 2;
                                                        jal(ctx, 0x157DA0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        v1 = sll(s3, 3);
                                                        a0 = subu(v1, s3);
                                                        v1 = sll(a0, 2);
                                                        v1 = addu(a0, v1);
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        lw(a0, s1, tw::kAlpha);
                                                        v1 = 255;
                                                        v1 = subu(v1, a0);
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f3, f0);
                                                        lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                        v1 = 0x437F0000;  // 255.0f
                                                        mtc1(v1, f1);
                                                        mtc1(zero, f0);
                                                        adda_s(f0, f1);
                                                        msub_s(f1, f2, f3);
                                                        v1 = 0x4F000000;
                                                        mtc1(v1, f0);
                                                        c_le_s(f0, f1);
                                                        if (cond(ctx)) {
                                                            // 0x00157e30
                                                            charge(ctx, 6);
                                                            sub_s(f0, f1, f0);
                                                            cvt_w_s(f0, f0);
                                                            mfc1(a3, f0);
                                                            v1 = lui(0x8000);
                                                            a3 = a3 | v1;
                                                            a3 = a3 & 0xFF;
                                                        } else {
                                                            // 0x00157e18
                                                            charge(ctx, 6);
                                                            cvt_w_s(f0, f1);
                                                            mfc1(a3, f0);
                                                            a3 = a3 & 0xFF;
                                                        }
                                                        // 0x00157e48
                                                        charge(ctx, 18);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mflo(v1);
                                                        a2 = addiu(v1, 11);
                                                        lwc1(f1, s1, tw::kX);
                                                        v1 = 0x44080000;  // 544.0f
                                                        mtc1(v1, f0);
                                                        add_s(f1, f0, f1);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f12, f1, f0);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x157E88u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    }
                                                    // 0x00157e90
                                                    charge(ctx, 31);
                                                    v0 = sll(s3, 3);
                                                    v1 = subu(v0, s3);
                                                    v0 = sll(v1, 2);
                                                    s4 = addu(v1, v0);
                                                    a0 = 2;
                                                    jal(ctx, 0x157EA4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    lw(a0, s1, tw::kAlpha);
                                                    v1 = 255;
                                                    v1 = subu(v1, a0);
                                                    mtc1(v1, f0);
                                                    cvt_s_w(f3, f0);
                                                    lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                    v1 = 0x437F0000;  // 255.0f
                                                    mtc1(v1, f1);
                                                    mtc1(zero, f0);
                                                    adda_s(f0, f1);
                                                    msub_s(f1, f2, f3);
                                                    v1 = 0x4F000000;
                                                    mtc1(v1, f0);
                                                    c_le_s(f0, f1);
                                                    if (cond(ctx)) {
                                                        // 0x00157f24
                                                        charge(ctx, 6);
                                                        sub_s(f0, f1, f0);
                                                        cvt_w_s(f0, f0);
                                                        mfc1(a3, f0);
                                                        v1 = lui(0x8000);
                                                        a3 = a3 | v1;
                                                        a3 = a3 & 0xFF;
                                                    } else {
                                                        // 0x00157f0c
                                                        charge(ctx, 6);
                                                        cvt_w_s(f0, f1);
                                                        mfc1(a3, f0);
                                                        a3 = a3 & 0xFF;
                                                    }
                                                    // 0x00157f3c
                                                    charge(ctx, 52);
                                                    v1 = 10;
                                                    div(s6, v1);
                                                    mfhi(v1);
                                                    a2 = addiu(v1, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x44080000;  // 544.0f
                                                    mtc1(v1, f0);
                                                    add_s(f1, f0, f1);
                                                    v1 = 0x42700000;  // 60.0f
                                                    mtc1(v1, f0);
                                                    sub_s(f1, f1, f0);
                                                    v1 = 0x41800000;  // 16.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157F8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    v0 = 575;
                                                    mtc1(v0, f0);
                                                    cvt_s_w(f1, f0);
                                                    lwc1(f0, s1, tw::kX);
                                                    add_s(f1, f1, f0);
                                                    v0 = 0x42700000;  // 60.0f
                                                    mtc1(v0, f0);
                                                    sub_s(f12, f1, f0);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    lw(a1, s0, 0);
                                                    a2 = 35;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157FE4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    lh(a0, s2, 0);
                                                    jal(ctx, 0x157FF0u, gen::fn_sub_403830_00403830);
                                                    s6 = dsll32(v0, 16);
                                                    s6 = dsra32(s6, 16);
                                                    v0 = slti(s6, 10);
                                                    if (v0 != 0) {
                                                        // 0x00158204
                                                        charge(ctx, 27);
                                                        a0 = 2;
                                                        jal(ctx, 0x158208u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        mtc1(s4, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        lw(a0, s1, tw::kAlpha);
                                                        v1 = 255;
                                                        v1 = subu(v1, a0);
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f3, f0);
                                                        lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                        v1 = 0x437F0000;  // 255.0f
                                                        mtc1(v1, f1);
                                                        mtc1(zero, f0);
                                                        adda_s(f0, f1);
                                                        msub_s(f1, f2, f3);
                                                        v1 = 0x4F000000;
                                                        mtc1(v1, f0);
                                                        c_le_s(f0, f1);
                                                        if (cond(ctx)) {
                                                            // 0x00158288
                                                            charge(ctx, 6);
                                                            sub_s(f0, f1, f0);
                                                            cvt_w_s(f0, f0);
                                                            mfc1(a3, f0);
                                                            v1 = lui(0x8000);
                                                            a3 = a3 | v1;
                                                            a3 = a3 & 0xFF;
                                                        } else {
                                                            // 0x00158270
                                                            charge(ctx, 6);
                                                            cvt_w_s(f0, f1);
                                                            mfc1(a3, f0);
                                                            a3 = a3 & 0xFF;
                                                        }
                                                        // 0x001582a0
                                                        charge(ctx, 21);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mfhi(v1);
                                                        a2 = addiu(v1, 11);
                                                        v1 = 586;
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f1, f0);
                                                        lwc1(f0, s1, tw::kX);
                                                        add_s(f1, f1, f0);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f12, f1, f0);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x1582E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    } else {
                                                        // 0x0015800c
                                                        charge(ctx, 31);
                                                        v0 = sll(s3, 3);
                                                        v1 = subu(v0, s3);
                                                        v0 = sll(v1, 2);
                                                        fp = addu(v1, v0);
                                                        a0 = 2;
                                                        jal(ctx, 0x158020u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        mtc1(fp, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        lw(a0, s1, tw::kAlpha);
                                                        v1 = 255;
                                                        v1 = subu(v1, a0);
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f3, f0);
                                                        lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                        v1 = 0x437F0000;  // 255.0f
                                                        mtc1(v1, f1);
                                                        mtc1(zero, f0);
                                                        adda_s(f0, f1);
                                                        msub_s(f1, f2, f3);
                                                        v1 = 0x4F000000;
                                                        mtc1(v1, f0);
                                                        c_le_s(f0, f1);
                                                        if (cond(ctx)) {
                                                            // 0x001580a0
                                                            charge(ctx, 6);
                                                            sub_s(f0, f1, f0);
                                                            cvt_w_s(f0, f0);
                                                            mfc1(a3, f0);
                                                            v1 = lui(0x8000);
                                                            a3 = a3 | v1;
                                                            a3 = a3 & 0xFF;
                                                        } else {
                                                            // 0x00158088
                                                            charge(ctx, 6);
                                                            cvt_w_s(f0, f1);
                                                            mfc1(a3, f0);
                                                            a3 = a3 & 0xFF;
                                                        }
                                                        // 0x001580b8
                                                        charge(ctx, 46);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mflo(v1);
                                                        a2 = addiu(v1, 11);
                                                        v1 = 586;
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f1, f0);
                                                        lwc1(f0, s1, tw::kX);
                                                        add_s(f1, f1, f0);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f12, f1, f0);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x1580FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                        a0 = 2;
                                                        jal(ctx, 0x158108u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        mtc1(fp, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        lw(a0, s1, tw::kAlpha);
                                                        v1 = 255;
                                                        v1 = subu(v1, a0);
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f3, f0);
                                                        lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                        v1 = 0x437F0000;  // 255.0f
                                                        mtc1(v1, f1);
                                                        mtc1(zero, f0);
                                                        adda_s(f0, f1);
                                                        msub_s(f1, f2, f3);
                                                        v1 = 0x4F000000;
                                                        mtc1(v1, f0);
                                                        c_le_s(f0, f1);
                                                        if (cond(ctx)) {
                                                            // 0x00158188
                                                            charge(ctx, 6);
                                                            sub_s(f0, f1, f0);
                                                            cvt_w_s(f0, f0);
                                                            mfc1(a3, f0);
                                                            v1 = lui(0x8000);
                                                            a3 = a3 | v1;
                                                            a3 = a3 & 0xFF;
                                                        } else {
                                                            // 0x00158170
                                                            charge(ctx, 6);
                                                            cvt_w_s(f0, f1);
                                                            mfc1(a3, f0);
                                                            a3 = a3 & 0xFF;
                                                        }
                                                        // 0x001581a0
                                                        charge(ctx, 25);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mfhi(v1);
                                                        a2 = addiu(v1, 11);
                                                        v1 = 586;
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f1, f0);
                                                        lwc1(f0, s1, tw::kX);
                                                        add_s(f1, f1, f0);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f1, f1, f0);
                                                        v1 = 0x41800000;  // 16.0f
                                                        mtc1(v1, f0);
                                                        add_s(f12, f0, f1);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x1581F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    }
                                                }
                                            } else {
                                                // 0x00157ce8
                                                charge(ctx, 35);
                                                v0 = sll(s3, 3);
                                                v1 = subu(v0, s3);
                                                v0 = sll(v1, 2);
                                                s4 = addu(v1, v0);
                                                lwc1(f1, s1, tw::kY);
                                                v0 = 0x42CA0000;  // 101.0f
                                                mtc1(v0, f0);
                                                add_s(f1, f0, f1);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f1, f1, f0);
                                                v0 = 0x42D80000;  // 108.0f
                                                mtc1(v0, f0);
                                                sub_s(f13, f1, f0);
                                                lwc1(f1, s1, tw::kX);
                                                v0 = 0x44070000;  // 540.0f
                                                mtc1(v0, f0);
                                                add_s(f1, f0, f1);
                                                v0 = 0x42700000;  // 60.0f
                                                mtc1(v0, f0);
                                                sub_s(f12, f1, f0);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s5;
                                                lw(a1, s0, 0);
                                                a2 = 163;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x157D64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            }
                                            // 0x00158378
                                            charge(ctx, 8);
                                            lh(a0, s2, 0);
                                            jal(ctx, 0x15837Cu, gen::fn_sub_403740_00403740);
                                            s6 = dsll32(v0, 16);
                                            s6 = dsra32(s6, 16);
                                            v0 = slti(s6, 100);
                                            if (v0 != 0) {
                                                // 0x00158628
                                                charge(ctx, 3);
                                                v0 = slti(s6, 10);
                                                if (v0 != 0) {
                                                    // 0x00158804
                                                    charge(ctx, 27);
                                                    a0 = 2;
                                                    jal(ctx, 0x158808u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    lw(a0, s1, tw::kAlpha);
                                                    v1 = 255;
                                                    v1 = subu(v1, a0);
                                                    mtc1(v1, f0);
                                                    cvt_s_w(f3, f0);
                                                    lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                    v1 = 0x437F0000;  // 255.0f
                                                    mtc1(v1, f1);
                                                    mtc1(zero, f0);
                                                    adda_s(f0, f1);
                                                    msub_s(f1, f2, f3);
                                                    v1 = 0x4F000000;
                                                    mtc1(v1, f0);
                                                    c_le_s(f0, f1);
                                                    if (cond(ctx)) {
                                                        // 0x00158888
                                                        charge(ctx, 6);
                                                        sub_s(f0, f1, f0);
                                                        cvt_w_s(f0, f0);
                                                        mfc1(a3, f0);
                                                        v1 = lui(0x8000);
                                                        a3 = a3 | v1;
                                                        a3 = a3 & 0xFF;
                                                    } else {
                                                        // 0x00158870
                                                        charge(ctx, 6);
                                                        cvt_w_s(f0, f1);
                                                        mfc1(a3, f0);
                                                        a3 = a3 & 0xFF;
                                                    }
                                                    // 0x001588a0
                                                    charge(ctx, 11);
                                                    a2 = addiu(s6, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x41600000;  // 14.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x1588C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                } else {
                                                    // 0x00158634
                                                    charge(ctx, 31);
                                                    v0 = sll(s3, 3);
                                                    v1 = subu(v0, s3);
                                                    v0 = sll(v1, 2);
                                                    s4 = addu(v1, v0);
                                                    a0 = 2;
                                                    jal(ctx, 0x158648u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    lw(a0, s1, tw::kAlpha);
                                                    v1 = 255;
                                                    v1 = subu(v1, a0);
                                                    mtc1(v1, f0);
                                                    cvt_s_w(f3, f0);
                                                    lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                    v1 = 0x437F0000;  // 255.0f
                                                    mtc1(v1, f1);
                                                    mtc1(zero, f0);
                                                    adda_s(f0, f1);
                                                    msub_s(f1, f2, f3);
                                                    v1 = 0x4F000000;
                                                    mtc1(v1, f0);
                                                    c_le_s(f0, f1);
                                                    if (cond(ctx)) {
                                                        // 0x001586c8
                                                        charge(ctx, 6);
                                                        sub_s(f0, f1, f0);
                                                        cvt_w_s(f0, f0);
                                                        mfc1(a3, f0);
                                                        v1 = lui(0x8000);
                                                        a3 = a3 | v1;
                                                        a3 = a3 & 0xFF;
                                                    } else {
                                                        // 0x001586b0
                                                        charge(ctx, 6);
                                                        cvt_w_s(f0, f1);
                                                        mfc1(a3, f0);
                                                        a3 = a3 & 0xFF;
                                                    }
                                                    // 0x001586e0
                                                    charge(ctx, 41);
                                                    v1 = 10;
                                                    div(s6, v1);
                                                    mflo(v1);
                                                    a2 = addiu(v1, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x40E00000;  // 7.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x158710u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    a0 = 2;
                                                    jal(ctx, 0x15871Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    lw(a0, s1, tw::kAlpha);
                                                    v1 = 255;
                                                    v1 = subu(v1, a0);
                                                    mtc1(v1, f0);
                                                    cvt_s_w(f3, f0);
                                                    lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                    v1 = 0x437F0000;  // 255.0f
                                                    mtc1(v1, f1);
                                                    mtc1(zero, f0);
                                                    adda_s(f0, f1);
                                                    msub_s(f1, f2, f3);
                                                    v1 = 0x4F000000;
                                                    mtc1(v1, f0);
                                                    c_le_s(f0, f1);
                                                    if (cond(ctx)) {
                                                        // 0x0015879c
                                                        charge(ctx, 6);
                                                        sub_s(f0, f1, f0);
                                                        cvt_w_s(f0, f0);
                                                        mfc1(a3, f0);
                                                        v1 = lui(0x8000);
                                                        a3 = a3 | v1;
                                                        a3 = a3 & 0xFF;
                                                    } else {
                                                        // 0x00158784
                                                        charge(ctx, 6);
                                                        cvt_w_s(f0, f1);
                                                        mfc1(a3, f0);
                                                        a3 = a3 & 0xFF;
                                                    }
                                                    // 0x001587b4
                                                    charge(ctx, 20);
                                                    v1 = 10;
                                                    div(s6, v1);
                                                    mfhi(v1);
                                                    a2 = addiu(v1, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x40E00000;  // 7.0f
                                                    mtc1(v1, f0);
                                                    add_s(f1, f0, f1);
                                                    v1 = 0x41800000;  // 16.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x1587F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                }
                                            } else {
                                                // 0x00158398
                                                charge(ctx, 31);
                                                v0 = sll(s3, 3);
                                                v1 = subu(v0, s3);
                                                v0 = sll(v1, 2);
                                                s4 = addu(v1, v0);
                                                a0 = 2;
                                                jal(ctx, 0x1583ACu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                lwc1(f1, s1, tw::kY);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f13, f1, f0);
                                                lw(a0, s1, tw::kAlpha);
                                                v1 = 255;
                                                v1 = subu(v1, a0);
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                v1 = 0x437F0000;  // 255.0f
                                                mtc1(v1, f1);
                                                mtc1(zero, f0);
                                                adda_s(f0, f1);
                                                msub_s(f1, f2, f3);
                                                v1 = 0x4F000000;
                                                mtc1(v1, f0);
                                                c_le_s(f0, f1);
                                                if (cond(ctx)) {
                                                    // 0x0015842c
                                                    charge(ctx, 6);
                                                    sub_s(f0, f1, f0);
                                                    cvt_w_s(f0, f0);
                                                    mfc1(a3, f0);
                                                    v1 = lui(0x8000);
                                                    a3 = a3 | v1;
                                                    a3 = a3 & 0xFF;
                                                } else {
                                                    // 0x00158414
                                                    charge(ctx, 6);
                                                    cvt_w_s(f0, f1);
                                                    mfc1(a3, f0);
                                                    a3 = a3 & 0xFF;
                                                }
                                                // 0x00158444
                                                charge(ctx, 40);
                                                v1 = 100;
                                                div(s6, v1);
                                                mflo(v1);
                                                a2 = addiu(v1, 11);
                                                a0 = s5;
                                                a1 = v0;
                                                lwc1(f12, s1, tw::kX);
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x158464u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                v0 = 100;
                                                div(s6, v0);
                                                mfhi(s6);
                                                a0 = 2;
                                                jal(ctx, 0x15847Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                lwc1(f1, s1, tw::kY);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f13, f1, f0);
                                                lw(a0, s1, tw::kAlpha);
                                                v1 = 255;
                                                v1 = subu(v1, a0);
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                v1 = 0x437F0000;  // 255.0f
                                                mtc1(v1, f1);
                                                mtc1(zero, f0);
                                                adda_s(f0, f1);
                                                msub_s(f1, f2, f3);
                                                v1 = 0x4F000000;
                                                mtc1(v1, f0);
                                                c_le_s(f0, f1);
                                                if (cond(ctx)) {
                                                    // 0x001584fc
                                                    charge(ctx, 6);
                                                    sub_s(f0, f1, f0);
                                                    cvt_w_s(f0, f0);
                                                    mfc1(a3, f0);
                                                    v1 = lui(0x8000);
                                                    a3 = a3 | v1;
                                                    a3 = a3 & 0xFF;
                                                } else {
                                                    // 0x001584e4
                                                    charge(ctx, 6);
                                                    cvt_w_s(f0, f1);
                                                    mfc1(a3, f0);
                                                    a3 = a3 & 0xFF;
                                                }
                                                // 0x00158514
                                                charge(ctx, 41);
                                                v1 = 10;
                                                div(s6, v1);
                                                mflo(v1);
                                                a2 = addiu(v1, 11);
                                                lwc1(f1, s1, tw::kX);
                                                v1 = 0x41800000;  // 16.0f
                                                mtc1(v1, f0);
                                                add_s(f12, f0, f1);
                                                a0 = s5;
                                                a1 = v0;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x158544u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                a0 = 2;
                                                jal(ctx, 0x158550u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                lwc1(f1, s1, tw::kY);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f13, f1, f0);
                                                lw(a0, s1, tw::kAlpha);
                                                v1 = 255;
                                                v1 = subu(v1, a0);
                                                mtc1(v1, f0);
                                                cvt_s_w(f3, f0);
                                                lwc1(f2, gp, g::kFloat7CADB4);  // 0x7CADB4
                                                v1 = 0x437F0000;  // 255.0f
                                                mtc1(v1, f1);
                                                mtc1(zero, f0);
                                                adda_s(f0, f1);
                                                msub_s(f1, f2, f3);
                                                v1 = 0x4F000000;
                                                mtc1(v1, f0);
                                                c_le_s(f0, f1);
                                                if (cond(ctx)) {
                                                    // 0x001585d0
                                                    charge(ctx, 6);
                                                    sub_s(f0, f1, f0);
                                                    cvt_w_s(f0, f0);
                                                    mfc1(a3, f0);
                                                    v1 = lui(0x8000);
                                                    a3 = a3 | v1;
                                                    a3 = a3 & 0xFF;
                                                } else {
                                                    // 0x001585b8
                                                    charge(ctx, 6);
                                                    cvt_w_s(f0, f1);
                                                    mfc1(a3, f0);
                                                    a3 = a3 & 0xFF;
                                                }
                                                // 0x001585e8
                                                charge(ctx, 16);
                                                v1 = 10;
                                                div(s6, v1);
                                                mfhi(v1);
                                                a2 = addiu(v1, 11);
                                                lwc1(f1, s1, tw::kX);
                                                v1 = 0x42000000;  // 32.0f
                                                mtc1(v1, f0);
                                                add_s(f12, f0, f1);
                                                a0 = s5;
                                                a1 = v0;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x158618u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            }
                                            // 0x001588cc
                                            charge(ctx, 19);
                                            cvt_w_s(f0, f21);
                                            mfc1(a0, f0);
                                            v0 = 0x40000000;  // 2.0f
                                            mtc1(v0, f0);
                                            sub_s(f0, f20, f0);
                                            cvt_w_s(f0, f0);
                                            mfc1(a1, f0);
                                            lwc1(f0, s1, tw::kZ);
                                            cvt_w_s(f0, f0);
                                            mfc1(a2, f0);
                                            lh(t2, s2, 0);
                                            lw(a3, sp, 0xB0);
                                            t0 = 1;
                                            t1 = 10;
                                            jal(ctx, 0x158908u, gen::fn_sub_17C6C0_0017c6c0);
                                        } else {
                                            // 0x00157520
                                            charge(ctx, 6);
                                            lh(a0, s2, 0);
                                            jal(ctx, 0x157524u, gen::fn_sub_403380_00403380);
                                            v1 = 2;
                                            if (v0 != v1) {
                                                // 0x001575c4
                                                charge(ctx, 7);
                                                lh(a0, s2, 0);
                                                jal(ctx, 0x1575C8u, gen::fn_sub_403800_00403800);
                                                s6 = dsll32(v0, 16);
                                                s6 = dsra32(s6, 16);
                                                if (s6 == 0) {
                                                    // 0x00157934
                                                    charge(ctx, 33);
                                                    v0 = sll(s3, 3);
                                                    v1 = subu(v0, s3);
                                                    v0 = sll(v1, 2);
                                                    s4 = addu(v1, v0);
                                                    lwc1(f1, s1, tw::kY);
                                                    v0 = 0x42CA0000;  // 101.0f
                                                    mtc1(v0, f0);
                                                    add_s(f1, f0, f1);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f1, f1, f0);
                                                    v0 = 0x42D80000;  // 108.0f
                                                    mtc1(v0, f0);
                                                    sub_s(f13, f1, f0);
                                                    lwc1(f1, s1, tw::kX);
                                                    v0 = 0x44070000;  // 540.0f
                                                    mtc1(v0, f0);
                                                    add_s(f1, f0, f1);
                                                    v0 = 0x42700000;  // 60.0f
                                                    mtc1(v0, f0);
                                                    sub_s(f12, f1, f0);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    lw(a1, s0, 0);
                                                    a2 = 167;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x1579B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                } else {
                                                    // 0x001575e0
                                                    charge(ctx, 3);
                                                    v0 = slti(s6, 10);
                                                    if (v0 == 0) {
                                                        // 0x001575ec
                                                        charge(ctx, 34);
                                                        a0 = 1;
                                                        jal(ctx, 0x1575F0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        v1 = sll(s3, 3);
                                                        a0 = subu(v1, s3);
                                                        v1 = sll(a0, 2);
                                                        v1 = addu(a0, v1);
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mflo(v1);
                                                        a2 = addiu(v1, 11);
                                                        lwc1(f1, s1, tw::kX);
                                                        v1 = 0x44080000;  // 544.0f
                                                        mtc1(v1, f0);
                                                        add_s(f1, f0, f1);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f12, f1, f0);
                                                        lbu(a3, s1, tw::kAlpha);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        t0 = 255;
                                                        t1 = 190;
                                                        t2 = 95;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x15766Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                    }
                                                    // 0x00157674
                                                    charge(ctx, 71);
                                                    v0 = sll(s3, 3);
                                                    v1 = subu(v0, s3);
                                                    v0 = sll(v1, 2);
                                                    s4 = addu(v1, v0);
                                                    a0 = 1;
                                                    jal(ctx, 0x157688u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    v1 = 10;
                                                    div(s6, v1);
                                                    mfhi(v1);
                                                    a2 = addiu(v1, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x44080000;  // 544.0f
                                                    mtc1(v1, f0);
                                                    add_s(f1, f0, f1);
                                                    v1 = 0x42700000;  // 60.0f
                                                    mtc1(v1, f0);
                                                    sub_s(f1, f1, f0);
                                                    v1 = 0x41800000;  // 16.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    t0 = 255;
                                                    t1 = 190;
                                                    t2 = 95;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157704u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    v0 = 575;
                                                    mtc1(v0, f0);
                                                    cvt_s_w(f1, f0);
                                                    lwc1(f0, s1, tw::kX);
                                                    add_s(f1, f1, f0);
                                                    v0 = 0x42700000;  // 60.0f
                                                    mtc1(v0, f0);
                                                    sub_s(f12, f1, f0);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    lw(a1, s0, 0);
                                                    a2 = 36;
                                                    t0 = 255;
                                                    t1 = 190;
                                                    t2 = 95;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157768u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                    lh(a0, s2, 0);
                                                    jal(ctx, 0x157774u, gen::fn_sub_403830_00403830);
                                                    s6 = dsll32(v0, 16);
                                                    s6 = dsra32(s6, 16);
                                                    v0 = slti(s6, 10);
                                                    if (v0 != 0) {
                                                        // 0x001578b0
                                                        charge(ctx, 33);
                                                        a0 = 1;
                                                        jal(ctx, 0x1578B4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        mtc1(s4, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mfhi(v1);
                                                        a2 = addiu(v1, 11);
                                                        v1 = 586;
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f1, f0);
                                                        lwc1(f0, s1, tw::kX);
                                                        add_s(f1, f1, f0);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f12, f1, f0);
                                                        lbu(a3, s1, tw::kAlpha);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        t0 = 255;
                                                        t1 = 190;
                                                        t2 = 95;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x157924u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                    } else {
                                                        // 0x00157790
                                                        charge(ctx, 72);
                                                        v0 = sll(s3, 3);
                                                        v1 = subu(v0, s3);
                                                        v0 = sll(v1, 2);
                                                        fp = addu(v1, v0);
                                                        a0 = 1;
                                                        jal(ctx, 0x1577A4u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        mtc1(fp, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mflo(v1);
                                                        a2 = addiu(v1, 11);
                                                        v1 = 586;
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f1, f0);
                                                        lwc1(f0, s1, tw::kX);
                                                        add_s(f1, f1, f0);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f12, f1, f0);
                                                        lbu(a3, s1, tw::kAlpha);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        t0 = 255;
                                                        t1 = 190;
                                                        t2 = 95;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x157814u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                        a0 = 1;
                                                        jal(ctx, 0x157820u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                        lwc1(f1, s1, tw::kY);
                                                        mtc1(fp, f0);
                                                        cvt_s_w(f0, f0);
                                                        add_s(f13, f1, f0);
                                                        v1 = 10;
                                                        div(s6, v1);
                                                        mfhi(v1);
                                                        a2 = addiu(v1, 11);
                                                        v1 = 586;
                                                        mtc1(v1, f0);
                                                        cvt_s_w(f1, f0);
                                                        lwc1(f0, s1, tw::kX);
                                                        add_s(f1, f1, f0);
                                                        v1 = 0x42700000;  // 60.0f
                                                        mtc1(v1, f0);
                                                        sub_s(f1, f1, f0);
                                                        v1 = 0x41800000;  // 16.0f
                                                        mtc1(v1, f0);
                                                        add_s(f12, f0, f1);
                                                        lbu(a3, s1, tw::kAlpha);
                                                        a0 = s5;
                                                        a1 = v0;
                                                        t0 = 255;
                                                        t1 = 190;
                                                        t2 = 95;
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x1578A0u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                    }
                                                }
                                            } else {
                                                // 0x00157538
                                                charge(ctx, 35);
                                                v0 = sll(s3, 3);
                                                v1 = subu(v0, s3);
                                                v0 = sll(v1, 2);
                                                s4 = addu(v1, v0);
                                                lwc1(f1, s1, tw::kY);
                                                v0 = 0x42CA0000;  // 101.0f
                                                mtc1(v0, f0);
                                                add_s(f1, f0, f1);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f1, f1, f0);
                                                v0 = 0x42D80000;  // 108.0f
                                                mtc1(v0, f0);
                                                sub_s(f13, f1, f0);
                                                lwc1(f1, s1, tw::kX);
                                                v0 = 0x44070000;  // 540.0f
                                                mtc1(v0, f0);
                                                add_s(f1, f0, f1);
                                                v0 = 0x42700000;  // 60.0f
                                                mtc1(v0, f0);
                                                sub_s(f12, f1, f0);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s5;
                                                lw(a1, s0, 0);
                                                a2 = 163;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x1575B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            }
                                            // 0x001579b8
                                            charge(ctx, 8);
                                            lh(a0, s2, 0);
                                            jal(ctx, 0x1579BCu, gen::fn_sub_403740_00403740);
                                            s6 = dsll32(v0, 16);
                                            s6 = dsra32(s6, 16);
                                            v0 = slti(s6, 100);
                                            if (v0 != 0) {
                                                // 0x00157b24
                                                charge(ctx, 3);
                                                v0 = slti(s6, 10);
                                                if (v0 != 0) {
                                                    // 0x00157c28
                                                    charge(ctx, 23);
                                                    a0 = 1;
                                                    jal(ctx, 0x157C2Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    a2 = addiu(s6, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x41600000;  // 14.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    t0 = 255;
                                                    t1 = 190;
                                                    t2 = 95;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157C7Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                } else {
                                                    // 0x00157b30
                                                    charge(ctx, 62);
                                                    v0 = sll(s3, 3);
                                                    v1 = subu(v0, s3);
                                                    v0 = sll(v1, 2);
                                                    s4 = addu(v1, v0);
                                                    a0 = 1;
                                                    jal(ctx, 0x157B44u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    v1 = 10;
                                                    div(s6, v1);
                                                    mflo(v1);
                                                    a2 = addiu(v1, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x40E00000;  // 7.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    t0 = 255;
                                                    t1 = 190;
                                                    t2 = 95;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157BA0u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                    a0 = 1;
                                                    jal(ctx, 0x157BACu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                    lwc1(f1, s1, tw::kY);
                                                    mtc1(s4, f0);
                                                    cvt_s_w(f0, f0);
                                                    add_s(f13, f1, f0);
                                                    v1 = 10;
                                                    div(s6, v1);
                                                    mfhi(v1);
                                                    a2 = addiu(v1, 11);
                                                    lwc1(f1, s1, tw::kX);
                                                    v1 = 0x40E00000;  // 7.0f
                                                    mtc1(v1, f0);
                                                    add_s(f1, f0, f1);
                                                    v1 = 0x41800000;  // 16.0f
                                                    mtc1(v1, f0);
                                                    add_s(f12, f0, f1);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    a1 = v0;
                                                    t0 = 255;
                                                    t1 = 190;
                                                    t2 = 95;
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157C18u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                }
                                            } else {
                                                // 0x001579d8
                                                charge(ctx, 83);
                                                v0 = sll(s3, 3);
                                                v1 = subu(v0, s3);
                                                v0 = sll(v1, 2);
                                                s4 = addu(v1, v0);
                                                a0 = 1;
                                                jal(ctx, 0x1579ECu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                lwc1(f1, s1, tw::kY);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f13, f1, f0);
                                                v1 = 100;
                                                div(s6, v1);
                                                mflo(v1);
                                                a2 = addiu(v1, 11);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s5;
                                                a1 = v0;
                                                lwc1(f12, s1, tw::kX);
                                                t0 = 255;
                                                t1 = 190;
                                                t2 = 95;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x157A38u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                v0 = 100;
                                                div(s6, v0);
                                                mfhi(s6);
                                                a0 = 1;
                                                jal(ctx, 0x157A50u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                lwc1(f1, s1, tw::kY);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f13, f1, f0);
                                                v1 = 10;
                                                div(s6, v1);
                                                mflo(v1);
                                                a2 = addiu(v1, 11);
                                                lwc1(f1, s1, tw::kX);
                                                v1 = 0x41800000;  // 16.0f
                                                mtc1(v1, f0);
                                                add_s(f12, f0, f1);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s5;
                                                a1 = v0;
                                                t0 = 255;
                                                t1 = 190;
                                                t2 = 95;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x157AACu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                a0 = 1;
                                                jal(ctx, 0x157AB8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                lwc1(f1, s1, tw::kY);
                                                mtc1(s4, f0);
                                                cvt_s_w(f0, f0);
                                                add_s(f13, f1, f0);
                                                v1 = 10;
                                                div(s6, v1);
                                                mfhi(v1);
                                                a2 = addiu(v1, 11);
                                                lwc1(f1, s1, tw::kX);
                                                v1 = 0x42000000;  // 32.0f
                                                mtc1(v1, f0);
                                                add_s(f12, f0, f1);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s5;
                                                a1 = v0;
                                                t0 = 255;
                                                t1 = 190;
                                                t2 = 95;
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x157B14u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                            }
                                            // 0x00157c84
                                            charge(ctx, 19);
                                            cvt_w_s(f0, f21);
                                            mfc1(a0, f0);
                                            v0 = 0x40000000;  // 2.0f
                                            mtc1(v0, f0);
                                            sub_s(f0, f20, f0);
                                            cvt_w_s(f0, f0);
                                            mfc1(a1, f0);
                                            lwc1(f0, s1, tw::kZ);
                                            cvt_w_s(f0, f0);
                                            mfc1(a2, f0);
                                            lh(t2, s2, 0);
                                            lw(a3, sp, 0xB0);
                                            t0 = 1;
                                            t1 = 6;
                                            jal(ctx, 0x157CC0u, gen::fn_sub_17C6C0_0017c6c0);
                                        }
                                    }
                                    // 0x00158a30
                                    charge(ctx, 1);
                                    s3 = addiu(s3, 1);
                                }
                                // 0x00158a40
                                charge(ctx, 2);
                            } else {
                                // 0x00157014
                                charge(ctx, 3);
                                v1 = 7;
                                if (a2 == v1) {
                                    // 0x00157368
                                    charge(ctx, 62);
                                    v0 = sll(s7, 3);
                                    v1 = subu(v0, s7);
                                    v0 = sll(v1, 2);
                                    s2 = addu(v1, v0);
                                    lwc1(f1, s1, tw::kY);
                                    mtc1(s2, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f13, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s0, 0);
                                    a2 = 37;
                                    lwc1(f12, s1, tw::kX);
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x1573A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lwc1(f1, s1, tw::kY);
                                    mtc1(s2, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f13, f1, f0);
                                    lwc1(f1, s1, tw::kX);
                                    v0 = 0x42D80000;  // 108.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x424C0000;  // 51.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s0, 0);
                                    a2 = 38;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x1573F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lwc1(f1, s1, tw::kY);
                                    mtc1(s2, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f13, f1, f0);
                                    v0 = 534;
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    lwc1(f0, s1, tw::kX);
                                    add_s(f1, f1, f0);
                                    v0 = 0x424C0000;  // 51.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s0, 0);
                                    a2 = 39;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x157450u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x00157020
                                    charge(ctx, 3);
                                    v1 = 6;
                                    if (a2 == v1) {
                                        // 0x001571f0
                                        charge(ctx, 3);
                                        s3 = 0;
                                        for (;;) {
                                            // 0x00157354
                                            charge(ctx, 3);
                                            v1 = slti(s3, 3);
                                            if (v1 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                            // 0x001571fc
                                            charge(ctx, 86);
                                            v0 = sll(s3, 3);
                                            v1 = subu(v0, s3);
                                            v0 = sll(v1, 2);
                                            s2 = addu(v1, v0);
                                            lwc1(f1, s1, tw::kY);
                                            mtc1(s2, f0);
                                            cvt_s_w(f0, f0);
                                            add_s(f13, f1, f0);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 54;
                                            lwc1(f12, s1, tw::kX);
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x157238u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            lwc1(f1, s1, tw::kY);
                                            mtc1(s2, f0);
                                            cvt_s_w(f0, f0);
                                            add_s(f13, f1, f0);
                                            lwc1(f1, s1, tw::kX);
                                            v0 = 0x42D60000;  // 107.0f
                                            mtc1(v0, f0);
                                            add_s(f1, f0, f1);
                                            v0 = 0x42480000;  // 50.0f
                                            mtc1(v0, f0);
                                            sub_s(f12, f1, f0);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 55;
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x15728Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            lwc1(f1, s1, tw::kY);
                                            mtc1(s2, f0);
                                            cvt_s_w(f0, f0);
                                            add_s(f13, f1, f0);
                                            v0 = 533;
                                            mtc1(v0, f0);
                                            cvt_s_w(f1, f0);
                                            lwc1(f0, s1, tw::kX);
                                            add_s(f1, f1, f0);
                                            v0 = 0x42480000;  // 50.0f
                                            mtc1(v0, f0);
                                            sub_s(f12, f1, f0);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 55;
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x1572E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            lwc1(f1, s1, tw::kY);
                                            mtc1(s2, f0);
                                            cvt_s_w(f0, f0);
                                            add_s(f1, f1, f0);
                                            v0 = 0x3F800000;  // 1.0f
                                            mtc1(v0, f0);
                                            add_s(f13, f0, f1);
                                            lwc1(f1, s1, tw::kX);
                                            v0 = 0x441B0000;  // 620.0f
                                            mtc1(v0, f0);
                                            add_s(f1, f0, f1);
                                            v0 = 0x42480000;  // 50.0f
                                            mtc1(v0, f0);
                                            sub_s(f12, f1, f0);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 14;
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x157348u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            s3 = addiu(s3, 1);
                                        }
                                        // 0x00157360
                                        charge(ctx, 2);
                                    } else {
                                        // 0x0015702c
                                        charge(ctx, 3);
                                        v1 = 5;
                                        if (a2 == v1) {
                                            // 0x001571c4
                                            charge(ctx, 11);
                                            lbu(a3, s1, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s0, 0);
                                            a2 = 48;
                                            lwc1(f12, s1, tw::kX);
                                            lwc1(f13, s1, tw::kY);
                                            lwc1(f14, s1, tw::kZ);
                                            jal(ctx, 0x1571E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        } else {
                                            // 0x00157038
                                            charge(ctx, 3);
                                            v1 = 4;
                                            if (a2 == v1) {
                                                // 0x00157198
                                                charge(ctx, 11);
                                                lbu(a3, s1, tw::kAlpha);
                                                a0 = s5;
                                                lw(a1, s0, 0);
                                                a2 = 47;
                                                lwc1(f12, s1, tw::kX);
                                                lwc1(f13, s1, tw::kY);
                                                lwc1(f14, s1, tw::kZ);
                                                jal(ctx, 0x1571B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            } else {
                                                // 0x00157044
                                                charge(ctx, 3);
                                                v1 = 3;
                                                if (a2 == v1) {
                                                    // 0x0015716c
                                                    charge(ctx, 11);
                                                    lbu(a3, s1, tw::kAlpha);
                                                    a0 = s5;
                                                    lw(a1, s0, 0);
                                                    a2 = 46;
                                                    lwc1(f12, s1, tw::kX);
                                                    lwc1(f13, s1, tw::kY);
                                                    lwc1(f14, s1, tw::kZ);
                                                    jal(ctx, 0x157188u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                } else {
                                                    // 0x00157050
                                                    charge(ctx, 3);
                                                    v1 = 2;
                                                    if (a2 == v1) {
                                                        // 0x00157140
                                                        charge(ctx, 11);
                                                        lbu(a3, s1, tw::kAlpha);
                                                        a0 = s5;
                                                        lw(a1, s0, 0);
                                                        a2 = 49;
                                                        lwc1(f12, s1, tw::kX);
                                                        lwc1(f13, s1, tw::kY);
                                                        lwc1(f14, s1, tw::kZ);
                                                        jal(ctx, 0x15715Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    } else {
                                                        // 0x0015705c
                                                        charge(ctx, 3);
                                                        v1 = 1;
                                                        if (a2 == v1) {
                                                            // 0x001570dc
                                                            charge(ctx, 25);
                                                            a0 = 0;
                                                            lw(a1, s0, 0);
                                                            a2 = 27;
                                                            jal(ctx, 0x1570E8u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                                                            s0 = v0;
                                                            lwc1(f0, s1, tw::kZ);
                                                            swc1(f0, v0, 44);
                                                            lwc1(f0, s1, tw::kX);
                                                            swc1(f0, v0, 16);
                                                            lwc1(f0, s1, tw::kY);
                                                            swc1(f0, v0, 20);
                                                            lw(v1, s1, tw::kAlpha);
                                                            sb(v1, v0, 24);
                                                            v1 = lui(0xC2B4);
                                                            sw(v1, v0, 32);
                                                            a0 = s0;
                                                            a1 = 1;
                                                            jal(ctx, 0x157124u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                                                            a0 = s0;
                                                            jal(ctx, 0x157130u, gen::fn_sub_115980_00115980);  // draw and release the handle
                                                        } else {
                                                            // 0x00157068
                                                            charge(ctx, 2);
                                                            if (a2 == 0) {
                                                                // 0x00157078
                                                                charge(ctx, 25);
                                                                a0 = 0;
                                                                lw(a1, s0, 0);
                                                                a2 = 19;
                                                                jal(ctx, 0x157084u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                                                                s5 = v0;
                                                                lwc1(f0, s1, tw::kZ);
                                                                swc1(f0, v0, 44);
                                                                lwc1(f0, s1, tw::kX);
                                                                swc1(f0, v0, 16);
                                                                lwc1(f0, s1, tw::kY);
                                                                swc1(f0, v0, 20);
                                                                lw(v1, s1, tw::kAlpha);
                                                                sb(v1, v0, 24);
                                                                v1 = lui(0xC2B4);
                                                                sw(v1, v0, 32);
                                                                a0 = s5;
                                                                a1 = 1;
                                                                jal(ctx, 0x1570C0u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                                                                a0 = s5;
                                                                jal(ctx, 0x1570CCu, gen::fn_sub_115980_00115980);  // draw and release the handle
                                                            } else {
                                                                // 0x00157070
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
                        }
                    }
                }
            }
        }
    }
    // 0x001598bc (the shared epilogue, written out on this path)
    charge(ctx, 15);
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
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
}

// 0x00159900 sub_159900 -- 228 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemRunQuestTweens] (tweens, files, cursor): steps the quest list's tweens and draws them (sub_156F80); 1
// when all finished.
void sub_159900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00159900
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s1 = 1;
    s2 = 0;
    for (;;) {
        // 0x001599ac
        charge(ctx, 3);
        v0 = slti(s2, 100);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015993c
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x00159958
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x15995Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x0015996c
                charge(ctx, 6);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                jal(ctx, 0x15997Cu, gen::fn_sub_156F80_00156f80);
            }
            // 0x00159984
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x001599a4
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x001599a8
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001599b8
    charge(ctx, 11);
    v0 = s1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001599F0 sub_1599F0 -- 6456 bytes; frame 0x1D0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [H_Camp_SystemDrawCalendarElement] (tween, files, element, month, day): one element of the calendar: 99 the frame, 20
// the month grid (tbl_clndMonthLengths, weekdays through clndGetWeekDay / clndGetDaysSinceStartFromDate, the moon phase
// icons for days 29 / 6 / 14 ... of clndGetMoonPhase, holidays sub_17DB40, today's mark from clndGetCurrentMonth / Day,
// the event marks from sub_17AE30 and flags), the year "2009", the selected day's event text (strcpy / strcat,
// sub_3C3FE0).
void sub_1599F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x001599f0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1D0);
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
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a3;
    fp = t0;
    v1 = 99;
    if (a2 == v1) {
        // 0x0015b1cc
        charge(ctx, 57);
        lbu(a3, s2, tw::kAlpha);
        a0 = s5;
        lw(a1, s1, 4);
        a2 = 0;
        lwc1(f12, s2, tw::kX);
        lwc1(f13, s2, tw::kY);
        lwc1(f14, s2, tw::kZ);
        jal(ctx, 0x15B1E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s2, tw::kX);
        v0 = 0x423C0000;  // 47.0f
        mtc1(v0, f0);
        add_s(f1, f0, f1);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lbu(a3, s2, tw::kAlpha);
        a0 = s5;
        lw(a1, s1, 4);
        a2 = 9;
        lwc1(f13, s2, tw::kY);
        lwc1(f14, s2, tw::kZ);
        jal(ctx, 0x15B22Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s2, tw::kX);
        add_s(f1, f1, f0);
        v0 = 0x41F80000;  // 31.0f
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, s2, tw::kY);
        add_s(f1, f1, f0);
        v0 = 385;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        sub_s(f13, f1, f0);
        lbu(a3, s2, tw::kAlpha);
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        lwc1(f14, s2, tw::kZ);
        jal(ctx, 0x15B2A0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x00159a40
        charge(ctx, 3);
        v1 = 20;
        if (a2 == v1) {
            // 0x0015afb0
            charge(ctx, 15);
            a0 = s0;
            a1 = 1;
            jal(ctx, 0x15AFB8u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
            a0 = v0;
            jal(ctx, 0x15AFC4u, gen::fn_clndGetWeekDay_0017dae0);
            s3 = v0;
            s4 = 1;
            a0 = sll(s0, 1);
            v1 = 0x5E0000;
            v1 = addiu(v1, 15200);  // &tbl_clndMonthLengths
            s6 = addu(v1, a0);
            for (;;) {
                // 0x0015b1b0
                charge(ctx, 5);
                lh(v1, s6, -2);
                v1 = addiu(v1, 1);
                v1 = slt(s4, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015afec
                charge(ctx, 37);
                v0 = addu(s3, s4);
                a1 = addiu(v0, -1);
                a0 = 7;
                div(a1, a0);
                mfhi(v1);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v0 = addu(v0, v1);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s2, tw::kX);
                add_s(f21, f0, f1);
                div(a1, a0);
                mflo(v1);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v0 = sll(v0, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, s2, tw::kY);
                add_s(f20, f0, f1);
                a0 = s0;
                a1 = s4;
                jal(ctx, 0x15B05Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                a0 = v0;
                jal(ctx, 0x15B068u, gen::fn_clndGetMoonPhase_00181b50);
                v1 = v0 & 0xFF;
                v0 = 29;
                if (v1 != v0) {
                    // 0x0015b0ac
                    charge(ctx, 11);
                    a0 = s0;
                    a1 = s4;
                    jal(ctx, 0x15B0B4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                    a0 = v0;
                    jal(ctx, 0x15B0C0u, gen::fn_clndGetMoonPhase_00181b50);
                    v1 = v0 & 0xFF;
                    v0 = 6;
                    if (v1 != v0) {
                        // 0x0015b104
                        charge(ctx, 11);
                        a0 = s0;
                        a1 = s4;
                        jal(ctx, 0x15B10Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                        a0 = v0;
                        jal(ctx, 0x15B118u, gen::fn_clndGetMoonPhase_00181b50);
                        v1 = v0 & 0xFF;
                        v0 = 14;
                        if (v1 != v0) {
                            // 0x0015b15c
                            charge(ctx, 11);
                            a0 = s0;
                            a1 = s4;
                            jal(ctx, 0x15B164u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                            a0 = v0;
                            jal(ctx, 0x15B170u, gen::fn_clndGetMoonPhase_00181b50);
                            a0 = v0 & 0xFF;
                            v1 = 22;
                            if (a0 == v1) {
                                // 0x0015b188
                                charge(ctx, 9);
                                lbu(a3, s2, tw::kAlpha);
                                a0 = s5;
                                lw(a1, s1, 0);
                                a2 = 71;
                                mov_s(f12, f21);
                                mov_s(f13, f20);
                                lwc1(f14, s2, tw::kZ);
                                jal(ctx, 0x15B1A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                        } else {
                            // 0x0015b130
                            charge(ctx, 11);
                            lbu(a3, s2, tw::kAlpha);
                            a0 = s5;
                            lw(a1, s1, 0);
                            a2 = 69;
                            mov_s(f12, f21);
                            mov_s(f13, f20);
                            lwc1(f14, s2, tw::kZ);
                            jal(ctx, 0x15B14Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x0015b0d8
                        charge(ctx, 11);
                        lbu(a3, s2, tw::kAlpha);
                        a0 = s5;
                        lw(a1, s1, 0);
                        a2 = 70;
                        mov_s(f12, f21);
                        mov_s(f13, f20);
                        lwc1(f14, s2, tw::kZ);
                        jal(ctx, 0x15B0F4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                } else {
                    // 0x0015b080
                    charge(ctx, 11);
                    lbu(a3, s2, tw::kAlpha);
                    a0 = s5;
                    lw(a1, s1, 0);
                    a2 = 72;
                    mov_s(f12, f21);
                    mov_s(f13, f20);
                    lwc1(f14, s2, tw::kZ);
                    jal(ctx, 0x15B09Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                }
                // 0x0015b1ac
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x0015b1c4
            charge(ctx, 2);
        } else {
            // 0x00159a4c
            charge(ctx, 3);
            v1 = 19;
            if (a2 == v1) {
                // 0x0015acd0
                charge(ctx, 16);
                a0 = s0;
                a1 = 1;
                jal(ctx, 0x15ACD8u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                a0 = v0;
                jal(ctx, 0x15ACE4u, gen::fn_clndGetWeekDay_0017dae0);
                sq(v0, sp, 0xC0);
                s7 = 1;
                a0 = sll(s0, 1);
                v1 = 0x5E0000;
                v1 = addiu(v1, 15200);  // &tbl_clndMonthLengths
                v1 = addu(v1, a0);
                sq(v1, sp, 0xB0);
                for (;;) {
                    // 0x0015af90
                    charge(ctx, 6);
                    lq(v1, sp, 0xB0);
                    lh(v1, v1, -2);
                    v1 = addiu(v1, 1);
                    v1 = slt(s7, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0015ad10
                    charge(ctx, 36);
                    lq(v0, sp, 0xC0);
                    v0 = addu(v0, s7);
                    a1 = addiu(v0, -1);
                    a0 = 7;
                    div(a1, a0);
                    mfhi(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s2, tw::kX);
                    add_s(f21, f0, f1);
                    div(a1, a0);
                    mflo(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s2, tw::kY);
                    add_s(f20, f0, f1);
                    a0 = s0;
                    a1 = s7;
                    jal(ctx, 0x15AD84u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                    a0 = v0;
                    jal(ctx, 0x15AD90u, gen::fn_clndGetWeekDay_0017dae0);
                    if (v0 != 0) {
                        // 0x0015adc8
                        charge(ctx, 10);
                        a0 = s0;
                        a1 = s7;
                        jal(ctx, 0x15ADD0u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                        a0 = dsll32(v0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x15ADE0u, gen::fn_sub_17DB40_0017db40);  // [clndIsHolidayOrSundayFromDays]
                        if (v0 == 0) {
                            // 0x0015ae18
                            charge(ctx, 10);
                            a0 = s0;
                            a1 = s7;
                            jal(ctx, 0x15AE20u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                            a0 = v0;
                            jal(ctx, 0x15AE2Cu, gen::fn_clndGetWeekDay_0017dae0);
                            v1 = 6;
                            if (v0 != v1) {
                                // 0x0015ae68
                                charge(ctx, 5);
                                s4 = 104;
                                s3 = 113;
                                s6 = 119;
                                if (fp == s7) {
                                    // 0x0015ae7c
                                    charge(ctx, 3);
                                    s4 = addiu(s4, 120);
                                    s3 = addiu(s3, 120);
                                    s6 = addiu(s6, 120);
                                }
                            } else {
                                // 0x0015ae40
                                charge(ctx, 5);
                                s4 = 64;
                                s3 = 110;
                                s6 = 255;
                                if (fp == s7) {
                                    // 0x0015ae54
                                    charge(ctx, 5);
                                    s4 = addiu(s4, 90);
                                    s3 = addiu(s3, 90);
                                    s6 = addiu(s6, 100);
                                }
                            }
                        } else {
                            // 0x0015adf0
                            charge(ctx, 5);
                            s4 = 148;
                            s3 = 69;
                            s6 = 93;
                            if (fp == s7) {
                                // 0x0015ae04
                                charge(ctx, 5);
                                s4 = addiu(s4, 100);
                                s3 = addiu(s3, 100);
                                s6 = addiu(s6, 100);
                            }
                        }
                    } else {
                        // 0x0015ada0
                        charge(ctx, 5);
                        s4 = 148;
                        s3 = 69;
                        s6 = 93;
                        if (fp == s7) {
                            // 0x0015adb4
                            charge(ctx, 5);
                            s4 = addiu(s4, 100);
                            s3 = addiu(s3, 100);
                            s6 = addiu(s6, 100);
                        }
                    }
                    // 0x0015ae88
                    charge(ctx, 3);
                    at = slti(s4, 256);
                    if (at == 0) {
                        // 0x0015ae94
                        charge(ctx, 1);
                        s4 = 255;
                    }
                    // 0x0015ae98
                    charge(ctx, 3);
                    at = slti(s3, 256);
                    if (at == 0) {
                        // 0x0015aea4
                        charge(ctx, 1);
                        s3 = 255;
                    }
                    // 0x0015aea8
                    charge(ctx, 3);
                    at = slti(s6, 256);
                    if (at == 0) {
                        // 0x0015aeb4
                        charge(ctx, 1);
                        s6 = 255;
                    }
                    // 0x0015aeb8
                    charge(ctx, 3);
                    v0 = slti(s7, 10);
                    if (v0 != 0) {
                        // 0x0015af50
                        charge(ctx, 15);
                        a2 = addiu(s7, 91);
                        v0 = 0x41800000;  // 16.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f21);
                        lbu(a3, s2, tw::kAlpha);
                        t0 = s4 & 0xFF;
                        t1 = s3 & 0xFF;
                        t2 = s6 & 0xFF;
                        a0 = s5;
                        lw(a1, s1, 0);
                        mov_s(f13, f20);
                        lwc1(f14, s2, tw::kZ);
                        jal(ctx, 0x15AF84u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    } else {
                        // 0x0015aec4
                        charge(ctx, 35);
                        v0 = 10;
                        div(s7, v0);
                        mflo(v0);
                        a2 = addiu(v0, 91);
                        lbu(a3, s2, tw::kAlpha);
                        t0 = s4 & 0xFF;
                        t1 = s3 & 0xFF;
                        t2 = s6 & 0xFF;
                        a0 = s5;
                        lw(a1, s1, 0);
                        mov_s(f12, f21);
                        mov_s(f13, f20);
                        lwc1(f14, s2, tw::kZ);
                        jal(ctx, 0x15AEF8u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                        v0 = 10;
                        div(s7, v0);
                        mfhi(v0);
                        a2 = addiu(v0, 91);
                        v0 = 0x41800000;  // 16.0f
                        mtc1(v0, f0);
                        add_s(f12, f0, f21);
                        lbu(a3, s2, tw::kAlpha);
                        t0 = s4 & 0xFF;
                        t1 = s3 & 0xFF;
                        t2 = s6 & 0xFF;
                        a0 = s5;
                        lw(a1, s1, 0);
                        mov_s(f13, f20);
                        lwc1(f14, s2, tw::kZ);
                        jal(ctx, 0x15AF40u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    }
                    // 0x0015af8c
                    charge(ctx, 1);
                    s7 = addiu(s7, 1);
                }
                // 0x0015afa8
                charge(ctx, 2);
            } else {
                // 0x00159a58
                charge(ctx, 3);
                v1 = 18;
                if (a2 == v1) {
                    // 0x0015ac28
                    charge(ctx, 42);
                    a0 = s0;
                    a1 = 1;
                    jal(ctx, 0x15AC30u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                    a0 = v0;
                    jal(ctx, 0x15AC3Cu, gen::fn_clndGetWeekDay_0017dae0);
                    v0 = addu(v0, fp);
                    a1 = addiu(v0, -1);
                    a0 = 7;
                    div(a1, a0);
                    mfhi(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(v0, v1);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s2, tw::kX);
                    add_s(f12, f0, f1);
                    div(a1, a0);
                    mflo(v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, s2, tw::kY);
                    add_s(f13, f0, f1);
                    lbu(a3, s2, tw::kAlpha);
                    a0 = s5;
                    lw(a1, s1, 0);
                    a2 = 73;
                    lwc1(f14, s2, tw::kZ);
                    jal(ctx, 0x15ACC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                } else {
                    // 0x00159a64
                    charge(ctx, 3);
                    v1 = 17;
                    if (a2 == v1) {
                        // 0x0015ab64
                        charge(ctx, 4);
                        jal(ctx, 0x15AB64u, gen::fn_clndGetCurrentMonth_0017d920);
                        if (s0 == v0) {
                            // 0x0015ab74
                            charge(ctx, 45);
                            a0 = s0;
                            a1 = 1;
                            jal(ctx, 0x15AB7Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                            a0 = v0;
                            jal(ctx, 0x15AB88u, gen::fn_clndGetWeekDay_0017dae0);
                            s0 = v0;
                            jal(ctx, 0x15AB94u, gen::fn_clndGetCurrentDay_0017da40);
                            v0 = addu(s0, v0);
                            a1 = addiu(v0, -1);
                            a0 = 7;
                            div(a1, a0);
                            mfhi(v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 3);
                            v0 = addu(v0, v1);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, s2, tw::kX);
                            add_s(f12, f0, f1);
                            div(a1, a0);
                            mflo(v1);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            lwc1(f0, s2, tw::kY);
                            add_s(f13, f0, f1);
                            lbu(a3, s2, tw::kAlpha);
                            a0 = s5;
                            lw(a1, s1, 0);
                            a2 = 90;
                            lwc1(f14, s2, tw::kZ);
                            jal(ctx, 0x15AC18u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x00159a70
                        charge(ctx, 3);
                        v1 = 16;
                        if (a2 == v1) {
                            // 0x0015aa40
                            charge(ctx, 15);
                            a0 = s0;
                            a1 = 1;
                            jal(ctx, 0x15AA48u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                            a0 = v0;
                            jal(ctx, 0x15AA54u, gen::fn_clndGetWeekDay_0017dae0);
                            s3 = v0;
                            s4 = 1;
                            a0 = sll(s0, 1);
                            v1 = 0x5E0000;
                            v1 = addiu(v1, 15200);  // &tbl_clndMonthLengths
                            s0 = addu(v1, a0);
                            for (;;) {
                                // 0x0015ab48
                                charge(ctx, 5);
                                lh(a0, s0, -2);
                                v1 = addiu(a0, 2);
                                v1 = slt(s4, v1);
                                if (v1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x0015aa7c
                                charge(ctx, 29);
                                v0 = addu(s3, s4);
                                a2 = addiu(v0, -1);
                                a1 = 7;
                                div(a2, a1);
                                mfhi(v1);
                                v0 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 3);
                                v0 = addu(v0, v1);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lwc1(f0, s2, tw::kX);
                                add_s(f12, f0, f1);
                                div(a2, a1);
                                mflo(v1);
                                v0 = sll(v1, 2);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 1);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 2);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                lwc1(f0, s2, tw::kY);
                                add_s(f13, f0, f1);
                                v0 = addiu(a0, 1);
                                if (s4 != v0) {
                                    // 0x0015ab28
                                    charge(ctx, 7);
                                    lbu(a3, s2, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s1, 0);
                                    a2 = 89;
                                    lwc1(f14, s2, tw::kZ);
                                    jal(ctx, 0x15AB3Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x0015aaf0
                                    charge(ctx, 14);
                                    v0 = 0x3F800000;  // 1.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f12, f0);
                                    sub_s(f13, f13, f0);
                                    lbu(a3, s2, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s1, 0);
                                    a2 = 86;
                                    lwc1(f14, s2, tw::kZ);
                                    jal(ctx, 0x15AB18u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                }
                                // 0x0015ab44
                                charge(ctx, 1);
                                s4 = addiu(s4, 1);
                            }
                            // 0x0015ab5c
                            charge(ctx, 2);
                        } else {
                            // 0x00159a7c
                            charge(ctx, 3);
                            a0 = 15;
                            if (a2 == a0) {
                                // 0x0015a89c
                                charge(ctx, 3);
                                s0 = 0;
                                for (;;) {
                                    // 0x0015a94c
                                    charge(ctx, 3);
                                    v1 = slti(s0, 6);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0015a8a8
                                    charge(ctx, 41);
                                    v0 = sll(s0, 2);
                                    v0 = addu(v0, s0);
                                    v0 = sll(v0, 1);
                                    v0 = addu(v0, s0);
                                    s3 = sll(v0, 2);
                                    lwc1(f1, s2, tw::kY);
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f13, f1, f0);
                                    lbu(a3, s2, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s1, 0);
                                    a2 = 86;
                                    lwc1(f12, s2, tw::kX);
                                    lwc1(f14, s2, tw::kZ);
                                    jal(ctx, 0x15A8E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lwc1(f1, s2, tw::kY);
                                    mtc1(s3, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f13, f1, f0);
                                    v0 = 613;
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    lwc1(f0, s2, tw::kX);
                                    add_s(f1, f1, f0);
                                    v0 = 0x43A30000;  // 326.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    lbu(a3, s2, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s1, 0);
                                    a2 = 86;
                                    lwc1(f14, s2, tw::kZ);
                                    jal(ctx, 0x15A940u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s0 = addiu(s0, 1);
                                }
                                // 0x0015a958
                                charge(ctx, 3);
                                s0 = 1;
                                for (;;) {
                                    // 0x0015aa2c
                                    charge(ctx, 3);
                                    v1 = slti(s0, 43);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x0015a964
                                    charge(ctx, 50);
                                    a1 = addiu(s0, -1);
                                    a0 = 7;
                                    div(a1, a0);
                                    mfhi(v1);
                                    v0 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 3);
                                    v0 = addu(v0, v1);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    lwc1(f0, s2, tw::kX);
                                    add_s(f1, f0, f1);
                                    v0 = 327;
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x43A30000;  // 326.0f
                                    mtc1(v0, f0);
                                    sub_s(f12, f1, f0);
                                    div(a1, a0);
                                    mflo(v1);
                                    v0 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 1);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 2);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    lwc1(f0, s2, tw::kY);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42CE0000;  // 103.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x42CC0000;  // 102.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s2, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s1, 0);
                                    a2 = 88;
                                    lwc1(f14, s2, tw::kZ);
                                    jal(ctx, 0x15AA20u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    s0 = addiu(s0, 1);
                                }
                                // 0x0015aa38
                                charge(ctx, 2);
                            } else {
                                // 0x00159a88
                                charge(ctx, 3);
                                a0 = 14;
                                if (a2 == a0) {
                                    // 0x0015a870
                                    charge(ctx, 11);
                                    lbu(a3, s2, tw::kAlpha);
                                    a0 = s5;
                                    lw(a1, s1, 0);
                                    a2 = 83;
                                    lwc1(f12, s2, tw::kX);
                                    lwc1(f13, s2, tw::kY);
                                    lwc1(f14, s2, tw::kZ);
                                    jal(ctx, 0x15A88Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                } else {
                                    // 0x00159a94
                                    charge(ctx, 3);
                                    a0 = 13;
                                    if (a2 == a0) {
                                        // 0x0015a844
                                        charge(ctx, 11);
                                        lbu(a3, s2, tw::kAlpha);
                                        a0 = s5;
                                        lw(a1, s1, 0);
                                        a2 = 82;
                                        lwc1(f12, s2, tw::kX);
                                        lwc1(f13, s2, tw::kY);
                                        lwc1(f14, s2, tw::kZ);
                                        jal(ctx, 0x15A860u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    } else {
                                        // 0x00159aa0
                                        charge(ctx, 3);
                                        a0 = 12;
                                        if (a2 == a0) {
                                            // 0x0015a818
                                            charge(ctx, 11);
                                            lbu(a3, s2, tw::kAlpha);
                                            a0 = s5;
                                            lw(a1, s1, 0);
                                            a2 = 81;
                                            lwc1(f12, s2, tw::kX);
                                            lwc1(f13, s2, tw::kY);
                                            lwc1(f14, s2, tw::kZ);
                                            jal(ctx, 0x15A834u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                        } else {
                                            // 0x00159aac
                                            charge(ctx, 3);
                                            a0 = 11;
                                            if (a2 == a0) {
                                                // 0x0015a7ec
                                                charge(ctx, 11);
                                                lbu(a3, s2, tw::kAlpha);
                                                a0 = s5;
                                                lw(a1, s1, 0);
                                                a2 = 80;
                                                lwc1(f12, s2, tw::kX);
                                                lwc1(f13, s2, tw::kY);
                                                lwc1(f14, s2, tw::kZ);
                                                jal(ctx, 0x15A808u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                            } else {
                                                // 0x00159ab8
                                                charge(ctx, 3);
                                                a0 = 10;
                                                if (a2 == a0) {
                                                    // 0x0015a7c0
                                                    charge(ctx, 11);
                                                    lbu(a3, s2, tw::kAlpha);
                                                    a0 = s5;
                                                    lw(a1, s1, 0);
                                                    a2 = 79;
                                                    lwc1(f12, s2, tw::kX);
                                                    lwc1(f13, s2, tw::kY);
                                                    lwc1(f14, s2, tw::kZ);
                                                    jal(ctx, 0x15A7DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                } else {
                                                    // 0x00159ac4
                                                    charge(ctx, 3);
                                                    a0 = 9;
                                                    if (a2 == a0) {
                                                        // 0x0015a794
                                                        charge(ctx, 11);
                                                        lbu(a3, s2, tw::kAlpha);
                                                        a0 = s5;
                                                        lw(a1, s1, 0);
                                                        a2 = 78;
                                                        lwc1(f12, s2, tw::kX);
                                                        lwc1(f13, s2, tw::kY);
                                                        lwc1(f14, s2, tw::kZ);
                                                        jal(ctx, 0x15A7B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                    } else {
                                                        // 0x00159ad0
                                                        charge(ctx, 3);
                                                        a0 = 8;
                                                        if (a2 == a0) {
                                                            // 0x0015a768
                                                            charge(ctx, 11);
                                                            lbu(a3, s2, tw::kAlpha);
                                                            a0 = s5;
                                                            lw(a1, s1, 0);
                                                            a2 = 84;
                                                            lwc1(f12, s2, tw::kX);
                                                            lwc1(f13, s2, tw::kY);
                                                            lwc1(f14, s2, tw::kZ);
                                                            jal(ctx, 0x15A784u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                        } else {
                                                            // 0x00159adc
                                                            charge(ctx, 3);
                                                            a0 = 7;
                                                            if (a2 == a0) {
                                                                // 0x0015a73c
                                                                charge(ctx, 11);
                                                                lbu(a3, s2, tw::kAlpha);
                                                                a0 = s5;
                                                                lw(a1, s1, 0);
                                                                a2 = 85;
                                                                lwc1(f12, s2, tw::kX);
                                                                lwc1(f13, s2, tw::kY);
                                                                lwc1(f14, s2, tw::kZ);
                                                                jal(ctx, 0x15A758u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                            } else {
                                                                // 0x00159ae8
                                                                charge(ctx, 3);
                                                                a0 = 6;
                                                                if (a2 == a0) {
                                                                    // 0x0015a478
                                                                    charge(ctx, 3);
                                                                    at = slti(s0, 4);
                                                                    if (at == 0) {
                                                                        // 0x0015a49c
                                                                        charge(ctx, 4);
                                                                        a0 = addiu(sp, 0xD0);
                                                                        a1 = addiu(gp, -30320);  // "2009"
                                                                        jal(ctx, 0x15A4A4u, gen::fn_sprintf_00523ac8);
                                                                    } else {
                                                                        // 0x0015a484
                                                                        charge(ctx, 6);
                                                                        a0 = addiu(sp, 0xD0);
                                                                        a1 = addiu(gp, -30328);  // "2010"
                                                                        jal(ctx, 0x15A48Cu, gen::fn_sprintf_00523ac8);
                                                                    }
                                                                    // 0x0015a4ac
                                                                    charge(ctx, 9);
                                                                    lwc1(f1, s2, tw::kX);
                                                                    v0 = 0x42820000;  // 65.0f
                                                                    mtc1(v0, f0);
                                                                    add_s(f21, f0, f1);
                                                                    lwc1(f20, s2, tw::kY);
                                                                    s3 = 0;
                                                                    for (;;) {
                                                                        // 0x0015a5dc
                                                                        charge(ctx, 3);
                                                                        v0 = slti(s3, 4);
                                                                        if (v0 == 0) {
                                                                            break;
                                                                        }
                                                                        backedge(ctx);
                                                                        // 0x0015a4d0
                                                                        charge(ctx, 7);
                                                                        a0 = si(-1);
                                                                        v0 = addu(s3, sp);
                                                                        v0 = addiu(v0, 208);
                                                                        lb(v1, v0, 0);
                                                                        v0 = 48;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a4ec
                                                                            charge(ctx, 1);
                                                                            a0 = 0;
                                                                        }
                                                                        // 0x0015a4f0
                                                                        charge(ctx, 3);
                                                                        v0 = 49;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a4fc
                                                                            charge(ctx, 1);
                                                                            a0 = 1;
                                                                        }
                                                                        // 0x0015a500
                                                                        charge(ctx, 3);
                                                                        v0 = 50;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a50c
                                                                            charge(ctx, 1);
                                                                            a0 = 2;
                                                                        }
                                                                        // 0x0015a510
                                                                        charge(ctx, 3);
                                                                        v0 = 51;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a51c
                                                                            charge(ctx, 1);
                                                                            a0 = 3;
                                                                        }
                                                                        // 0x0015a520
                                                                        charge(ctx, 3);
                                                                        v0 = 52;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a52c
                                                                            charge(ctx, 1);
                                                                            a0 = 4;
                                                                        }
                                                                        // 0x0015a530
                                                                        charge(ctx, 3);
                                                                        v0 = 53;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a53c
                                                                            charge(ctx, 1);
                                                                            a0 = 5;
                                                                        }
                                                                        // 0x0015a540
                                                                        charge(ctx, 3);
                                                                        v0 = 54;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a54c
                                                                            charge(ctx, 1);
                                                                            a0 = 6;
                                                                        }
                                                                        // 0x0015a550
                                                                        charge(ctx, 3);
                                                                        v0 = 55;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a55c
                                                                            charge(ctx, 1);
                                                                            a0 = 7;
                                                                        }
                                                                        // 0x0015a560
                                                                        charge(ctx, 3);
                                                                        v0 = 56;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a56c
                                                                            charge(ctx, 1);
                                                                            a0 = 8;
                                                                        }
                                                                        // 0x0015a570
                                                                        charge(ctx, 3);
                                                                        v0 = 57;
                                                                        if (v1 == v0) {
                                                                            // 0x0015a57c
                                                                            charge(ctx, 1);
                                                                            a0 = 9;
                                                                        }
                                                                        // 0x0015a580
                                                                        charge(ctx, 3);
                                                                        v0 = si(-1);
                                                                        if (a0 != v0) {
                                                                            // 0x0015a58c
                                                                            charge(ctx, 15);
                                                                            a2 = addiu(a0, 124);
                                                                            v0 = 0x3F800000;  // 1.0f
                                                                            mtc1(v0, f0);
                                                                            sub_s(f13, f20, f0);
                                                                            lbu(a3, s2, tw::kAlpha);
                                                                            a0 = s5;
                                                                            lw(a1, s1, 0);
                                                                            mov_s(f12, f21);
                                                                            t0 = 220;
                                                                            t1 = 243;
                                                                            t2 = 255;
                                                                            lwc1(f14, s2, tw::kZ);
                                                                            jal(ctx, 0x15A5C0u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                                                                        }
                                                                        // 0x0015a5c8
                                                                        charge(ctx, 5);
                                                                        v0 = 0x41880000;  // 17.0f
                                                                        mtc1(v0, f0);
                                                                        add_s(f21, f21, f0);
                                                                        s3 = addiu(s3, 1);
                                                                    }
                                                                    // 0x0015a5e8
                                                                    charge(ctx, 28);
                                                                    lwc1(f1, s2, tw::kX);
                                                                    v0 = 0x42200000;  // 40.0f
                                                                    mtc1(v0, f0);
                                                                    add_s(f12, f0, f1);
                                                                    lwc1(f1, s2, tw::kY);
                                                                    v0 = 0x42440000;  // 49.0f
                                                                    mtc1(v0, f0);
                                                                    add_s(f1, f0, f1);
                                                                    v0 = 0x424C0000;  // 51.0f
                                                                    mtc1(v0, f0);
                                                                    sub_s(f1, f1, f0);
                                                                    v0 = 0x3F800000;  // 1.0f
                                                                    mtc1(v0, f0);
                                                                    sub_s(f13, f1, f0);
                                                                    lbu(a3, s2, tw::kAlpha);
                                                                    a0 = s5;
                                                                    lw(a1, s1, 0);
                                                                    a2 = 76;
                                                                    lwc1(f14, s2, tw::kZ);
                                                                    jal(ctx, 0x15A644u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                    v0 = slti(s0, 10);
                                                                    if (v0 != 0) {
                                                                        // 0x0015a6e4
                                                                        charge(ctx, 22);
                                                                        lwc1(f1, s2, tw::kX);
                                                                        v0 = 0x41880000;  // 17.0f
                                                                        mtc1(v0, f0);
                                                                        add_s(f12, f0, f1);
                                                                        lwc1(f1, s2, tw::kY);
                                                                        v0 = 0x3F800000;  // 1.0f
                                                                        mtc1(v0, f0);
                                                                        sub_s(f13, f1, f0);
                                                                        v0 = 10;
                                                                        div(s0, v0);
                                                                        mfhi(v0);
                                                                        a2 = addiu(v0, 124);
                                                                        lbu(a3, s2, tw::kAlpha);
                                                                        a0 = s5;
                                                                        lw(a1, s1, 0);
                                                                        lwc1(f14, s2, tw::kZ);
                                                                        jal(ctx, 0x15A72Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                    } else {
                                                                        // 0x0015a658
                                                                        charge(ctx, 35);
                                                                        lwc1(f21, s2, tw::kX);
                                                                        lwc1(f1, s2, tw::kY);
                                                                        v0 = 0x3F800000;  // 1.0f
                                                                        mtc1(v0, f0);
                                                                        sub_s(f20, f1, f0);
                                                                        v0 = 10;
                                                                        div(s0, v0);
                                                                        mflo(v0);
                                                                        a2 = addiu(v0, 124);
                                                                        lbu(a3, s2, tw::kAlpha);
                                                                        a0 = s5;
                                                                        lw(a1, s1, 0);
                                                                        mov_s(f12, f21);
                                                                        mov_s(f13, f20);
                                                                        lwc1(f14, s2, tw::kZ);
                                                                        jal(ctx, 0x15A698u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                        v0 = 10;
                                                                        div(s0, v0);
                                                                        mfhi(v0);
                                                                        a2 = addiu(v0, 124);
                                                                        v0 = 0x41880000;  // 17.0f
                                                                        mtc1(v0, f0);
                                                                        add_s(f12, f0, f21);
                                                                        lbu(a3, s2, tw::kAlpha);
                                                                        a0 = s5;
                                                                        lw(a1, s1, 0);
                                                                        mov_s(f13, f20);
                                                                        lwc1(f14, s2, tw::kZ);
                                                                        jal(ctx, 0x15A6D4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                    }
                                                                } else {
                                                                    // 0x00159af4
                                                                    charge(ctx, 3);
                                                                    a0 = 5;
                                                                    if (a2 == a0) {
                                                                        // 0x0015a400
                                                                        charge(ctx, 30);
                                                                        lbu(a3, s2, tw::kAlpha);
                                                                        a0 = s5;
                                                                        lw(a1, s1, 0);
                                                                        a2 = 74;
                                                                        lwc1(f12, s2, tw::kX);
                                                                        lwc1(f13, s2, tw::kY);
                                                                        lwc1(f14, s2, tw::kZ);
                                                                        jal(ctx, 0x15A41Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                        v0 = 574;
                                                                        mtc1(v0, f0);
                                                                        cvt_s_w(f1, f0);
                                                                        lwc1(f0, s2, tw::kX);
                                                                        add_s(f1, f1, f0);
                                                                        v0 = 325;
                                                                        mtc1(v0, f0);
                                                                        cvt_s_w(f0, f0);
                                                                        sub_s(f12, f1, f0);
                                                                        lbu(a3, s2, tw::kAlpha);
                                                                        a0 = s5;
                                                                        lw(a1, s1, 0);
                                                                        a2 = 75;
                                                                        lwc1(f13, s2, tw::kY);
                                                                        lwc1(f14, s2, tw::kZ);
                                                                        jal(ctx, 0x15A468u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                    } else {
                                                                        // 0x00159b00
                                                                        charge(ctx, 3);
                                                                        a0 = 4;
                                                                        if (a2 == a0) {
                                                                            // 0x0015a1b4
                                                                            charge(ctx, 9);
                                                                            lw(a0, s2, tw::kAlpha);
                                                                            v1 = 255;
                                                                            a0 = subu(v1, a0);
                                                                            s1 = 0;
                                                                            s3 = 0;
                                                                            v1 = si(-256);
                                                                            s6 = a0 | v1;
                                                                            for (;;) {
                                                                                // 0x0015a308
                                                                                charge(ctx, 3);
                                                                                v1 = slti(s3, 9999);
                                                                                if (v1 != 0) {
                                                                                    backedge(ctx);
                                                                                    // 0x0015a1d8
                                                                                    charge(ctx, 9);
                                                                                    s4 = 0;
                                                                                    lw(a0, gp, g::kUnlockTable);  // 0x7CDFB8
                                                                                    v1 = sll(s3, 1);
                                                                                    v1 = addu(v1, s3);
                                                                                    s5 = sll(v1, 2);
                                                                                    a0 = addu(a0, s5);
                                                                                    lh(v1, a0, 0);
                                                                                    if (v1 != 0) {
                                                                                        // 0x0015a1fc
                                                                                        charge(ctx, 2);
                                                                                        if (s0 == v1) {
                                                                                            // 0x0015a204
                                                                                            charge(ctx, 3);
                                                                                            lh(v1, a0, 2);
                                                                                            if (fp == v1) {
                                                                                                // 0x0015a210
                                                                                                charge(ctx, 3);
                                                                                                lw(a0, a0, 4);
                                                                                                if (a0 != 0) {
                                                                                                    // 0x0015a228
                                                                                                    charge(ctx, 4);
                                                                                                    jal(ctx, 0x15A228u, gen::fn_datGetFlag_0016f190);
                                                                                                    if (v0 != 0) {
                                                                                                        // 0x0015a238
                                                                                                        charge(ctx, 1);
                                                                                                        s4 = 1;
                                                                                                    }
                                                                                                } else {
                                                                                                    // 0x0015a21c
                                                                                                    charge(ctx, 3);
                                                                                                    s4 = 1;
                                                                                                }
                                                                                                // 0x0015a23c
                                                                                                charge(ctx, 6);
                                                                                                lw(v1, gp, g::kUnlockTable);  // 0x7CDFB8
                                                                                                a1 = addu(v1, s5);
                                                                                                lh(a0, a1, 0);
                                                                                                v1 = 3;
                                                                                                if (a0 == v1) {
                                                                                                    // 0x0015a254
                                                                                                    charge(ctx, 4);
                                                                                                    lh(a0, a1, 8);
                                                                                                    v1 = 19;
                                                                                                    if (a0 == v1) {
                                                                                                        // 0x0015a264
                                                                                                        charge(ctx, 1);
                                                                                                        s4 = 1;
                                                                                                    }
                                                                                                }
                                                                                                // 0x0015a268
                                                                                                charge(ctx, 2);
                                                                                                if (s4 != 0) {
                                                                                                    // 0x0015a270
                                                                                                    charge(ctx, 37);
                                                                                                    lh(v0, a1, 8);
                                                                                                    v1 = sll(v0, 2);
                                                                                                    v0 = 0x840000;
                                                                                                    v0 = addiu(v0, -21856);  // &0x83AAA0
                                                                                                    v0 = addu(v0, v1);
                                                                                                    a0 = addiu(sp, 0xD0);
                                                                                                    a1 = addiu(gp, -30340);  // "%s"
                                                                                                    lw(a2, v0, 0);
                                                                                                    jal(ctx, 0x15A290u, gen::fn_sprintf_00523ac8);
                                                                                                    lwc1(f0, s2, tw::kX);
                                                                                                    cvt_w_s(f0, f0);
                                                                                                    mfc1(a0, f0);
                                                                                                    lwc1(f1, s2, tw::kY);
                                                                                                    v0 = sll(s1, 3);
                                                                                                    v0 = subu(v0, s1);
                                                                                                    v0 = sll(v0, 2);
                                                                                                    mtc1(v0, f0);
                                                                                                    cvt_s_w(f0, f0);
                                                                                                    add_s(f1, f1, f0);
                                                                                                    v0 = 0x40000000;  // 2.0f
                                                                                                    mtc1(v0, f0);
                                                                                                    add_s(f0, f0, f1);
                                                                                                    cvt_w_s(f0, f0);
                                                                                                    mfc1(a1, f0);
                                                                                                    mtc1(zero, f12);
                                                                                                    a2 = s6;
                                                                                                    a3 = 10;
                                                                                                    t0 = 1;
                                                                                                    t1 = addiu(sp, 0xD0);
                                                                                                    t2 = 16;
                                                                                                    t3 = 0;
                                                                                                    jal(ctx, 0x15A2F8u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                                                                                                    s1 = addiu(s1, 1);
                                                                                                }
                                                                                            }
                                                                                        }
                                                                                        // 0x0015a304
                                                                                        charge(ctx, 1);
                                                                                        s3 = addiu(s3, 1);
                                                                                        continue;
                                                                                    }
                                                                                }
                                                                                break;
                                                                            }
                                                                            // 0x0015a314
                                                                            charge(ctx, 3);
                                                                            s3 = 0;
                                                                            for (;;) {
                                                                                // 0x0015a3ec
                                                                                charge(ctx, 3);
                                                                                v1 = slti(s3, 256);
                                                                                if (v1 == 0) {
                                                                                    goto L_0015a3f8_64;
                                                                                }
                                                                                backedge(ctx);
                                                                                // 0x0015a320
                                                                                charge(ctx, 7);
                                                                                a0 = s3;
                                                                                jal(ctx, 0x15A324u, gen::fn_sub_17AE30_0017ae30);
                                                                                s4 = v0;
                                                                                lbu(v1, v0, 0);
                                                                                if (v1 != 0) {
                                                                                    // 0x0015a33c
                                                                                    charge(ctx, 2);
                                                                                    if (v1 == s0) {
                                                                                        // 0x0015a344
                                                                                        charge(ctx, 3);
                                                                                        lbu(v1, s4, 1);
                                                                                        if (v1 == fp) {
                                                                                            // 0x0015a350
                                                                                            charge(ctx, 38);
                                                                                            a0 = addiu(sp, 0xD0);
                                                                                            lw(a1, gp, g::kWord7CB574);  // 0x7CB574
                                                                                            jal(ctx, 0x15A358u, gen::fn_strcpy_00524270);
                                                                                            lbu(a0, s4, 2);
                                                                                            jal(ctx, 0x15A364u, gen::fn_sub_3C3FE0_003c3fe0);  // [comuGetPartnerName]
                                                                                            a0 = addiu(sp, 0xD0);
                                                                                            a1 = v0;
                                                                                            jal(ctx, 0x15A374u, gen::fn_strcat_00523e68);
                                                                                            lwc1(f0, s2, tw::kX);
                                                                                            cvt_w_s(f0, f0);
                                                                                            mfc1(a0, f0);
                                                                                            lwc1(f1, s2, tw::kY);
                                                                                            v0 = sll(s1, 3);
                                                                                            v0 = subu(v0, s1);
                                                                                            v0 = sll(v0, 2);
                                                                                            mtc1(v0, f0);
                                                                                            cvt_s_w(f0, f0);
                                                                                            add_s(f1, f1, f0);
                                                                                            v0 = 0x40000000;  // 2.0f
                                                                                            mtc1(v0, f0);
                                                                                            add_s(f0, f0, f1);
                                                                                            cvt_w_s(f0, f0);
                                                                                            mfc1(a1, f0);
                                                                                            mtc1(zero, f12);
                                                                                            a2 = s6;
                                                                                            a3 = 10;
                                                                                            t0 = 1;
                                                                                            t1 = addiu(sp, 0xD0);
                                                                                            t2 = 16;
                                                                                            t3 = 0;
                                                                                            jal(ctx, 0x15A3DCu, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                                                                                            s1 = addiu(s1, 1);
                                                                                        }
                                                                                    }
                                                                                    // 0x0015a3e8
                                                                                    charge(ctx, 1);
                                                                                    s3 = addiu(s3, 1);
                                                                                    continue;
                                                                                }
                                                                                break;
                                                                            }
                                                                        } else {
                                                                            // 0x00159b0c
                                                                            charge(ctx, 3);
                                                                            a0 = 3;
                                                                            if (a2 == a0) {
                                                                                // 0x00159ccc
                                                                                charge(ctx, 28);
                                                                                lwc1(f1, s2, tw::kX);
                                                                                v0 = 0x438B0000;  // 278.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42100000;  // 36.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f12, f1, f0);
                                                                                lwc1(f1, s2, tw::kY);
                                                                                v0 = 0x42AE0000;  // 87.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42C40000;  // 98.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f13, f1, f0);
                                                                                lbu(a3, s2, tw::kAlpha);
                                                                                a0 = s5;
                                                                                lw(a1, s1, 0);
                                                                                a2 = 57;
                                                                                lwc1(f14, s2, tw::kZ);
                                                                                jal(ctx, 0x159D28u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                v0 = slti(s0, 10);
                                                                                if (v0 != 0) {
                                                                                    // 0x00159dd4
                                                                                    charge(ctx, 18);
                                                                                    v0 = 0x41800000;  // 16.0f
                                                                                    mtc1(v0, f20);
                                                                                    a0 = 1;
                                                                                    jal(ctx, 0x159DE0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                                                    a2 = addiu(s0, 11);
                                                                                    lwc1(f1, s2, tw::kX);
                                                                                    v1 = 0x41800000;  // 16.0f
                                                                                    mtc1(v1, f0);
                                                                                    add_s(f12, f0, f1);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    a1 = v0;
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159E14u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                } else {
                                                                                    // 0x00159d3c
                                                                                    charge(ctx, 38);
                                                                                    a0 = 1;
                                                                                    jal(ctx, 0x159D40u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                                                    v1 = 10;
                                                                                    div(s0, v1);
                                                                                    mflo(v1);
                                                                                    a2 = addiu(v1, 11);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    a1 = v0;
                                                                                    lwc1(f12, s2, tw::kX);
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159D70u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    v0 = 0x41800000;  // 16.0f
                                                                                    mtc1(v0, f20);
                                                                                    a0 = 1;
                                                                                    jal(ctx, 0x159D84u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                                                    v1 = 10;
                                                                                    div(s0, v1);
                                                                                    mfhi(v1);
                                                                                    a2 = addiu(v1, 11);
                                                                                    lwc1(f1, s2, tw::kX);
                                                                                    v1 = 0x41800000;  // 16.0f
                                                                                    mtc1(v1, f0);
                                                                                    add_s(f12, f0, f1);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    a1 = v0;
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159DC4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                }
                                                                                // 0x00159e1c
                                                                                charge(ctx, 32);
                                                                                lwc1(f1, s2, tw::kX);
                                                                                v0 = 0x42700000;  // 60.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42100000;  // 36.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f1, f1, f0);
                                                                                v0 = 0x41200000;  // 10.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f12, f0, f1);
                                                                                lwc1(f1, s2, tw::kY);
                                                                                v0 = 0x42C00000;  // 96.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42C40000;  // 98.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f13, f1, f0);
                                                                                lbu(a3, s2, tw::kAlpha);
                                                                                a0 = s5;
                                                                                lw(a1, s1, 0);
                                                                                a2 = 68;
                                                                                lwc1(f14, s2, tw::kZ);
                                                                                jal(ctx, 0x159E88u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                v0 = slti(fp, 10);
                                                                                if (v0 != 0) {
                                                                                    // 0x00159f60
                                                                                    charge(ctx, 20);
                                                                                    a0 = 1;
                                                                                    jal(ctx, 0x159F64u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                                                    a2 = addiu(fp, 0xB);
                                                                                    lwc1(f1, s2, tw::kX);
                                                                                    v1 = 0x42B00000;  // 88.0f
                                                                                    mtc1(v1, f0);
                                                                                    add_s(f1, f0, f1);
                                                                                    v1 = 0x42100000;  // 36.0f
                                                                                    mtc1(v1, f0);
                                                                                    sub_s(f12, f1, f0);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    a1 = v0;
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159FA8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                } else {
                                                                                    // 0x00159e9c
                                                                                    charge(ctx, 49);
                                                                                    a0 = 1;
                                                                                    jal(ctx, 0x159EA0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                                                    v1 = 10;
                                                                                    div(fp, v1);
                                                                                    mflo(v1);
                                                                                    a2 = addiu(v1, 11);
                                                                                    lwc1(f1, s2, tw::kX);
                                                                                    v1 = 0x42B00000;  // 88.0f
                                                                                    mtc1(v1, f0);
                                                                                    add_s(f1, f0, f1);
                                                                                    v1 = 0x42100000;  // 36.0f
                                                                                    mtc1(v1, f0);
                                                                                    sub_s(f12, f1, f0);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    a1 = v0;
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159EF0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    a0 = 1;
                                                                                    jal(ctx, 0x159EFCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                                                                    v1 = 10;
                                                                                    div(fp, v1);
                                                                                    mfhi(v1);
                                                                                    a2 = addiu(v1, 11);
                                                                                    lwc1(f1, s2, tw::kX);
                                                                                    v1 = 0x42B00000;  // 88.0f
                                                                                    mtc1(v1, f0);
                                                                                    add_s(f1, f0, f1);
                                                                                    v1 = 0x42100000;  // 36.0f
                                                                                    mtc1(v1, f0);
                                                                                    sub_s(f0, f1, f0);
                                                                                    add_s(f12, f20, f0);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    a1 = v0;
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159F50u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                }
                                                                                // 0x00159fb0
                                                                                charge(ctx, 39);
                                                                                lwc1(f1, s2, tw::kX);
                                                                                v0 = 0x43130000;  // 147.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42100000;  // 36.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f1, f1, f0);
                                                                                v0 = 0x41900000;  // 18.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f12, f1, f0);
                                                                                lwc1(f1, s2, tw::kY);
                                                                                v0 = 0x42C00000;  // 96.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42C40000;  // 98.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f13, f1, f0);
                                                                                lbu(a3, s2, tw::kAlpha);
                                                                                a0 = s5;
                                                                                lw(a1, s1, 0);
                                                                                a2 = 66;
                                                                                lwc1(f14, s2, tw::kZ);
                                                                                jal(ctx, 0x15A01Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                a0 = s0;
                                                                                a1 = fp;
                                                                                jal(ctx, 0x15A02Cu, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);  // (month, day)
                                                                                a0 = v0;
                                                                                jal(ctx, 0x15A038u, gen::fn_clndGetWeekDay_0017dae0);
                                                                                at = sltiu(v0, 7);
                                                                                if (at != 0) {
                                                                                    // 0x0015a04c
                                                                                    charge(ctx, 7);
                                                                                    v1 = 0x7B0000;
                                                                                    v1 = addiu(v1, 24976);  // &0x7B6190
                                                                                    v0 = sll(v0, 2);
                                                                                    v0 = addu(v0, v1);
                                                                                    lw(v0, v0, 0);
                                                                                    switch (v0.u()) {
                                                                                    case 0x15A068u:  // table[0]
                                                                                        // 0x0015a068
                                                                                        charge(ctx, 3);
                                                                                        s3 = 65;
                                                                                        break;
                                                                                    case 0x15A074u:  // table[1]
                                                                                        // 0x0015a074
                                                                                        charge(ctx, 3);
                                                                                        s3 = 59;
                                                                                        break;
                                                                                    case 0x15A080u:  // table[2]
                                                                                        // 0x0015a080
                                                                                        charge(ctx, 3);
                                                                                        s3 = 60;
                                                                                        break;
                                                                                    case 0x15A08Cu:  // table[3]
                                                                                        // 0x0015a08c
                                                                                        charge(ctx, 3);
                                                                                        s3 = 61;
                                                                                        break;
                                                                                    case 0x15A098u:  // table[4]
                                                                                        // 0x0015a098
                                                                                        charge(ctx, 3);
                                                                                        s3 = 62;
                                                                                        break;
                                                                                    case 0x15A0A4u:  // table[5]
                                                                                        // 0x0015a0a4
                                                                                        charge(ctx, 3);
                                                                                        s3 = 63;
                                                                                        break;
                                                                                    case 0x15A0B0u:  // table[6]
                                                                                        // 0x0015a0b0
                                                                                        charge(ctx, 1);
                                                                                        s3 = 64;
                                                                                        break;
                                                                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                                                                        tail(ctx, v0.u());
                                                                                        return;
                                                                                    }
                                                                                }
                                                                                // 0x0015a0b4
                                                                                charge(ctx, 64);
                                                                                lwc1(f1, s2, tw::kX);
                                                                                v0 = 0x431E0000;  // 158.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42100000;  // 36.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f1, f1, f0);
                                                                                v0 = 0x41900000;  // 18.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f12, f1, f0);
                                                                                lwc1(f1, s2, tw::kY);
                                                                                v0 = 0x42C00000;  // 96.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42C40000;  // 98.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f13, f1, f0);
                                                                                lbu(a3, s2, tw::kAlpha);
                                                                                a0 = s5;
                                                                                lw(a1, s1, 0);
                                                                                a2 = s3;
                                                                                lwc1(f14, s2, tw::kZ);
                                                                                jal(ctx, 0x15A120u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                lwc1(f1, s2, tw::kX);
                                                                                v0 = 0x43340000;  // 180.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42100000;  // 36.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f1, f1, f0);
                                                                                v0 = 0x40000000;  // 2.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x41900000;  // 18.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f12, f1, f0);
                                                                                lwc1(f1, s2, tw::kY);
                                                                                v0 = 0x42C00000;  // 96.0f
                                                                                mtc1(v0, f0);
                                                                                add_s(f1, f0, f1);
                                                                                v0 = 0x42C40000;  // 98.0f
                                                                                mtc1(v0, f0);
                                                                                sub_s(f13, f1, f0);
                                                                                lbu(a3, s2, tw::kAlpha);
                                                                                a0 = s5;
                                                                                lw(a1, s1, 0);
                                                                                a2 = 67;
                                                                                lwc1(f14, s2, tw::kZ);
                                                                                jal(ctx, 0x15A1A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                            } else {
                                                                                // 0x00159b18
                                                                                charge(ctx, 3);
                                                                                a0 = 2;
                                                                                if (a2 == a0) {
                                                                                    // 0x00159bd0
                                                                                    charge(ctx, 63);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    lw(a1, s1, 0);
                                                                                    a2 = 42;
                                                                                    lwc1(f12, s2, tw::kX);
                                                                                    lwc1(f13, s2, tw::kY);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159BECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    lwc1(f1, s2, tw::kY);
                                                                                    v0 = 0x41E00000;  // 28.0f
                                                                                    mtc1(v0, f0);
                                                                                    add_s(f13, f0, f1);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    lw(a1, s1, 0);
                                                                                    a2 = 42;
                                                                                    lwc1(f12, s2, tw::kX);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159C20u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    lwc1(f1, s2, tw::kY);
                                                                                    v0 = 0x42600000;  // 56.0f
                                                                                    mtc1(v0, f0);
                                                                                    add_s(f13, f0, f1);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    lw(a1, s1, 0);
                                                                                    a2 = 42;
                                                                                    lwc1(f12, s2, tw::kX);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159C54u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    lwc1(f1, s2, tw::kY);
                                                                                    v0 = 0x42A80000;  // 84.0f
                                                                                    mtc1(v0, f0);
                                                                                    add_s(f13, f0, f1);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    lw(a1, s1, 0);
                                                                                    a2 = 42;
                                                                                    lwc1(f12, s2, tw::kX);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159C88u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    lwc1(f1, s2, tw::kY);
                                                                                    v0 = 0x42E00000;  // 112.0f
                                                                                    mtc1(v0, f0);
                                                                                    add_s(f13, f0, f1);
                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                    a0 = s5;
                                                                                    lw(a1, s1, 0);
                                                                                    a2 = 42;
                                                                                    lwc1(f12, s2, tw::kX);
                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                    jal(ctx, 0x159CBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                } else {
                                                                                    // 0x00159b24
                                                                                    charge(ctx, 3);
                                                                                    a0 = 1;
                                                                                    if (a2 == a0) {
                                                                                        // 0x00159ba4
                                                                                        charge(ctx, 11);
                                                                                        lbu(a3, s2, tw::kAlpha);
                                                                                        a0 = s5;
                                                                                        lw(a1, s1, 0);
                                                                                        a2 = 26;
                                                                                        lwc1(f12, s2, tw::kX);
                                                                                        lwc1(f13, s2, tw::kY);
                                                                                        lwc1(f14, s2, tw::kZ);
                                                                                        jal(ctx, 0x159BC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                                                    } else {
                                                                                        // 0x00159b30
                                                                                        charge(ctx, 2);
                                                                                        if (a2 == 0) {
                                                                                            // 0x00159b40
                                                                                            charge(ctx, 25);
                                                                                            a0 = 0;
                                                                                            lw(a1, s1, 0);
                                                                                            a2 = v1;
                                                                                            jal(ctx, 0x159B4Cu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                                                                                            s5 = v0;
                                                                                            lwc1(f0, s2, tw::kZ);
                                                                                            swc1(f0, v0, 44);
                                                                                            lwc1(f0, s2, tw::kX);
                                                                                            swc1(f0, v0, 16);
                                                                                            lwc1(f0, s2, tw::kY);
                                                                                            swc1(f0, v0, 20);
                                                                                            lw(v1, s2, tw::kAlpha);
                                                                                            sb(v1, v0, 24);
                                                                                            v1 = lui(0xC2B4);
                                                                                            sw(v1, v0, 32);
                                                                                            a0 = s5;
                                                                                            a1 = 1;
                                                                                            jal(ctx, 0x159B88u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                                                                                            a0 = s5;
                                                                                            jal(ctx, 0x159B94u, gen::fn_sub_115980_00115980);  // draw and release the handle
                                                                                        } else {
                                                                                            // 0x00159b38
                                                                                            charge(ctx, 2);
                                                                                            // 0x0015b2b0
                                                                                            charge(ctx, 3);
                                                                                            v1 = slti(a2, 21);
                                                                                            if (v1 == 0) {
                                                                                                // 0x0015b2bc
                                                                                                charge(ctx, 3);
                                                                                                at = slti(a2, 53);
                                                                                                if (at != 0) {
                                                                                                    // 0x0015b2c8
                                                                                                    charge(ctx, 9);
                                                                                                    lbu(a3, s2, tw::kAlpha);
                                                                                                    a0 = s5;
                                                                                                    lw(a1, s1, 0);
                                                                                                    a2 = 87;
                                                                                                    lwc1(f12, s2, tw::kX);
                                                                                                    lwc1(f13, s2, tw::kY);
                                                                                                    lwc1(f14, s2, tw::kZ);
                                                                                                    jal(ctx, 0x15B2E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
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
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x0015b2ec (the shared epilogue, written out on this path)
    charge(ctx, 15);
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
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
    return;
L_0015a3f8_64:
    charge(ctx, 2);
    // 0x0015b2ec (the shared epilogue, written out on this path)
    charge(ctx, 15);
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
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
}

// 0x0015B330 sub_15B330 -- 244 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SystemRunCalendarTweens] (tweens, files, month, day): steps the calendar's tweens and draws them
// (sub_1599F0); 1 when all finished.
void sub_15B330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0015b330
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
        // 0x0015b3e8
        charge(ctx, 3);
        v0 = slti(s2, 100);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015b374
        charge(ctx, 7);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        s0 = addu(s5, v0);
        lw(v0, s0, 4);
        if (v0 != 0) {
            // 0x0015b390
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x15B394u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
            if (v0 != 0) {
                // 0x0015b3a4
                charge(ctx, 7);
                a0 = s0;
                a1 = s4;
                a2 = s2;
                a3 = s3;
                t0 = s6;
                jal(ctx, 0x15B3B8u, gen::fn_sub_1599F0_001599f0);
            }
            // 0x0015b3c0
            charge(ctx, 8);
            v0 = sll(s2, 4);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            lw(v1, v0, 24);
            lw(v0, v0, 32);
            if (v1 != v0) {
                // 0x0015b3e0
                charge(ctx, 1);
                s1 = 0;
            }
        }
        // 0x0015b3e4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0015b3f4
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

// 0x0015B430 sub_15B430 -- 4140 bytes; frame 0xF0: ra sp+0x80, s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_Camp_UpdateConfigMenuDrawTask] Update of "H_ConfigMenuDraw" (the title screen's config; jump table 0x7B61B0):
// every frame the backdrop sub_113A30 at alpha 255 * +372 / 10; 0 waits for its camp sprite set-up task (gp-19880) and
// builds the status texture; 1 / 2 load the files as sub_14F7D0 does; then the config page alone (sub_155830, the
// values of flags 387.., written back with datSetFlag on confirm, sub_103CB0 / sub_103C30 applying them) and the close.
void sub_15B430(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0015b430
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    lw(s0, a0, 60);
    lw(v1, s0, sys::kFade);
    v0 = sll(v1, 8);
    v1 = subu(v0, v1);
    v0 = 10;
    div(v1, v0);
    mflo(v1);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    v0 = 0x72B50000;
    v0 = v0 | 0xFF00;
    a0 = v1 | v0;
    mtc1(zero, f13);
    v0 = 0x41A00000;  // 20.0f
    mtc1(v0, f14);
    a1 = 640;
    a2 = 410;
    jal(ctx, 0x15B494u, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
    lw(v0, s0, sys::kState);
    at = sltiu(v0, 11);
    if (at != 0) {
        // 0x0015b4ac
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25008);  // &0x7B61B0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x15B4C8u:  // table[0]: state 0: wait for the camp sprite set-up, texture build, tweens
            // 0x0015b4c8
            charge(ctx, 3);
            lw(v0, gp, g::kCampSetupTask);  // 0x7CDF48
            if (v0 != 0) {
                // 0x0015b4e0
                charge(ctx, 5);
                lw(v0, v0, 60);
                lw(v1, v0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x0015b500
                    charge(ctx, 1);
                    v1 = 0;
                } else {
                    // 0x0015b4f4
                    charge(ctx, 3);
                    v1 = 1;
                }
            } else {
                // 0x0015b4d4
                charge(ctx, 3);
                v1 = si(-1);
            }
            // 0x0015b504
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x0015b51c
                charge(ctx, 4);
                jal(ctx, 0x15B51Cu, gen::fn_sub_17D800_0017d800);  // 1 in The Answer
                if (v0 == 0) {
                    // 0x0015b580
                    charge(ctx, 19);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -17280);  // "_h_camp_system.c"
                    sd(v0, sp, 0x10);
                    v0 = 3835;
                    sd(v0, sp, 0x18);
                    a0 = 0;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20320);  // "camp/status/i_camp_hum_blue.tmx"
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x15B5C0u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    sw(v0, s0, sys::kBuild);
                } else {
                    // 0x0015b52c
                    charge(ctx, 21);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -17280);  // "_h_camp_system.c"
                    sd(v0, sp, 0x10);
                    v0 = 3833;
                    sd(v0, sp, 0x18);
                    a0 = 0;
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -20400);  // "camp/status/AGS_i_camp_hum_blue_03.tmx"
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x15B56Cu, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    sw(v0, s0, sys::kBuild);
                }
                // 0x0015b5cc
                charge(ctx, 30);
                a0 = 10;
                jal(ctx, 0x15B5D0u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, sys::kMenuTweens);
                a0 = 100;
                jal(ctx, 0x15B5E0u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
                sw(v0, s0, sys::kPageTweens);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17248);  // "camp/datMixraidHelp.bmd"
                a1 = 0;
                jal(ctx, 0x15B5F8u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, sys::kHelpFile);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17216);  // "facility/msg_quest.bmd"
                a1 = 0;
                jal(ctx, 0x15B610u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, sys::kQuestFile);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17184);  // "camp/camp_sys.pak"
                a1 = 1;
                jal(ctx, 0x15B628u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, sys::kPak);
                v0 = 1;
                sw(v0, s0, sys::kState);
            L_0015c430:
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0015b510
                charge(ctx, 3);
                v0 = 0;
            }
            break;
        case 0x15B644u:  // table[1]: state 1: load the files
            // 0x0015b644
            charge(ctx, 3);
            lw(v0, s0, sys::kTexture);
            if (v0 == 0) {
                // 0x0015b650
                charge(ctx, 9);
                lw(a0, s0, sys::kBuild);
                a1 = addiu(sp, 0xE8);
                a2 = 0;
                jal(ctx, 0x15B65Cu, gen::fn_sub_10C3A0_0010c3a0);  // poll the texture build
                sw(v0, s0, sys::kTexture);
                lw(v0, sp, 0xE8);
                if (v0 != 0) {
                    goto L_0015b684;
                }
                // 0x0015b674
                charge(ctx, 4);
                sw(zero, s0, sys::kTexture);
                v0 = 0;
                break;
            }
        L_0015b684:
            charge(ctx, 5);
            lw(a0, s0, sys::kHelpFile);
            jal(ctx, 0x15B688u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0015b698
                charge(ctx, 5);
                lw(a0, s0, sys::kQuestFile);
                jal(ctx, 0x15B69Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0015b6ac
                    charge(ctx, 5);
                    lw(a0, s0, sys::kPak);
                    jal(ctx, 0x15B6B0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        // 0x0015b6c0
                        charge(ctx, 32);
                        lw(v0, s0, sys::kHelpFile);
                        a0 = 12;
                        lw(a1, v0, 272);
                        jal(ctx, 0x15B6CCu, gen::fn_sub_3C7D80_003c7d80);
                        lw(v0, s0, sys::kQuestFile);
                        a0 = 8;
                        lw(a1, v0, 272);
                        jal(ctx, 0x15B6E0u, gen::fn_sub_3C7D80_003c7d80);
                        lw(a0, s0, sys::kPak);
                        a1 = 0;
                        a2 = addiu(sp, 0xEC);
                        jal(ctx, 0x15B6F4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                        a0 = v0;
                        jal(ctx, 0x15B700u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                        sw(v0, s0, sys::kFiles);
                        lw(a0, s0, sys::kPak);
                        a1 = 1;
                        a2 = addiu(sp, 0xEC);
                        jal(ctx, 0x15B718u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                        a0 = v0;
                        jal(ctx, 0x15B724u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                        sw(v0, s0, sys::kFile1);
                        v0 = 2;
                        sw(v0, s0, sys::kState);
                    }
                }
            }
            goto L_0015c430;
        case 0x15B740u:  // table[2]: state 2: wait for the sprite files
            // 0x0015b740
            charge(ctx, 5);
            lw(a0, s0, sys::kFiles);
            jal(ctx, 0x15B744u, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x0015b754
                charge(ctx, 5);
                lw(a0, s0, sys::kFile1);
                jal(ctx, 0x15B758u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x0015b768
                    charge(ctx, 4);
                    v0 = 6;
                    sw(v0, s0, sys::kState);
                }
            }
            goto L_0015c430;
        case 0x15B778u:  // table[6]: state 6: read flags 387..
            // 0x0015b778
            charge(ctx, 183);
            sw(zero, s0, sys::kConfigCursor);
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0xE0);
            v0 = 0x43570000;  // 215.0f
            sw(v0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xD8);
            lwc1(f1, sp, 0xDC);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xDC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xD8);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15B7E0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0xE0);
            v0 = 0x43830000;  // 262.0f
            sw(v0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0x98);
            lwc1(f1, sp, 0x9C);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x9C);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x98);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15B850u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15B8A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xA0);
            lwc1(f1, sp, 0xA4);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xA4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA0);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15B910u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15B960u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xA8);
            lwc1(f1, sp, 0xAC);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0xAC);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xA8);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15B9D0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42BE0000;  // 95.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0xE4);
            ld(v0, sp, 0xE0);
            sd(v0, sp, 0xB0);
            lwc1(f1, sp, 0xB0);
            v0 = 0x43480000;  // 200.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xB0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xB0);
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15BA40u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            s1 = 0;
            for (;;) {
                // 0x0015ba70
                charge(ctx, 3);
                v0 = slti(s1, 7);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015ba54
                charge(ctx, 7);
                a0 = addiu(s1, 387);
                jal(ctx, 0x15BA58u, gen::fn_datGetFlag_0016f190);
                v1 = sll(s1, 2);
                v1 = addu(s0, v1);
                sw(v0, v1, 344);
                s1 = addiu(s1, 1);
            }
            // 0x0015ba7c
            charge(ctx, 28);
            v0 = 0x43C40000;  // 392.0f
            sw(v0, sp, 0xE0);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15BAD0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            sw(zero, s0, sys::kArrived);
            v0 = 7;
            sw(v0, s0, sys::kState);
            goto L_0015c430;
        case 0x15BAECu:  // table[7]
            // 0x0015baec
            charge(ctx, 7);
            v0 = 8;
            sw(v0, s0, sys::kState);
            lw(s3, s0, sys::kConfigCursor);
            lw(s1, s0, sys::kPageTweens);
            s2 = 0;
            for (;;) {
                // 0x0015bb58
                charge(ctx, 3);
                v0 = slti(s2, 100);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015bb08
                charge(ctx, 7);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                v0 = sll(v0, 2);
                s4 = addu(s1, v0);
                lw(v0, s4, 4);
                if (v0 != 0) {
                    // 0x0015bb24
                    charge(ctx, 5);
                    a0 = s4;
                    jal(ctx, 0x15BB28u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0015bb38
                        charge(ctx, 7);
                        a0 = s4;
                        a1 = addiu(s0, sys::kFiles);
                        a2 = s2;
                        a3 = s3;
                        t0 = addiu(s0, sys::kConfigValues);
                        jal(ctx, 0x15BB4Cu, gen::fn_sub_155830_00155830);
                    }
                }
                // 0x0015bb54
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0015bb64
            charge(ctx, 2);
            goto L_0015c430;
        case 0x15BB6Cu:  // table[8]: state 8: config (input; write the flags)
            // 0x0015bb6c
            charge(ctx, 6);
            lw(v0, s0, sys::kFade);
            v0 = addiu(v0, 1);
            sw(v0, s0, sys::kFade);
            at = slti(v0, 11);
            if (at == 0) {
                // 0x0015bb84
                charge(ctx, 2);
                v0 = 10;
                sw(v0, s0, sys::kFade);
            }
            // 0x0015bb8c
            charge(ctx, 3);
            lw(v0, s0, sys::kArrived);
            if (v0 != 0) {
                // 0x0015bb98
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v1 = v0 & 0x40;  // confirm
                if (v1 == 0) {
                    // 0x0015bc8c
                    charge(ctx, 3);
                    v1 = v0 & 0x20;
                    if (v1 == 0) {
                        // 0x0015bcc0
                        charge(ctx, 6);
                        a1 = 1;
                        v1 = 0x7E0000;
                        lhu(a0, v1, 2386);  // 0x7E0952
                        v1 = a0 & 0x1000;
                        if (v1 == 0) {
                            // 0x0015bcd8
                            charge(ctx, 5);
                            v1 = 0x7E0000;
                            lhu(v1, v1, 2394);  // 0x7E095A
                            v1 = v1 & 0x1000;
                            if (v1 == 0) {
                                // 0x0015bcec
                                charge(ctx, 1);
                                a1 = 0;
                            }
                        }
                        // 0x0015bcf0
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x0015bd80
                            charge(ctx, 4);
                            v1 = a0 & 0x4000;
                            v1 = sltu(0, v1);
                            if (v1 == 0) {
                                // 0x0015bd90
                                charge(ctx, 4);
                                v1 = 0x7E0000;
                                lhu(v1, v1, 2394);  // 0x7E095A
                                v1 = v1 & 0x4000;
                                v1 = sltu(0, v1);
                            }
                            // 0x0015bda0
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x0015be30
                                charge(ctx, 4);
                                v1 = v0 & 0x2000;
                                v1 = sltu(0, v1);
                                if (v1 == 0) {
                                    // 0x0015be40
                                    charge(ctx, 4);
                                    v1 = 0x7E0000;
                                    lhu(v1, v1, 2392);  // 0x7E0958
                                    v1 = v1 & 0x2000;
                                    v1 = sltu(0, v1);
                                }
                                // 0x0015be50
                                charge(ctx, 2);
                                if (v1 == 0) {
                                    // 0x0015beac
                                    charge(ctx, 4);
                                    v0 = v0 & 0x8000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0015bebc
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x8000;  // previous page
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0015becc
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0015bed4
                                        charge(ctx, 4);
                                        lw(v1, s0, sys::kConfigCursor);
                                        v0 = 7;
                                        if (v1 != v0) {
                                            // 0x0015bee4
                                            charge(ctx, 5);
                                            v0 = sll(v1, 2);
                                            v0 = addu(v0, s0);
                                            lw(v0, v0, 344);
                                            if (v0 == 0) {
                                                // 0x0015bef8
                                                charge(ctx, 6);
                                                a0 = 0;
                                                a1 = 0;
                                                a2 = 0;
                                                a3 = 5;
                                                jal(ctx, 0x15BF08u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            }
                                            // 0x0015bf10
                                            charge(ctx, 3);
                                            lw(v0, s0, sys::kConfigCursor);
                                            if (v0 == 0) {
                                                // 0x0015bf1c
                                                charge(ctx, 3);
                                                lw(v0, s0, sys::kConfigValues);
                                                if (v0 == 0) {
                                                    // 0x0015bf28
                                                    charge(ctx, 6);
                                                    a0 = 10;
                                                    a1 = 150;
                                                    a2 = a0;
                                                    a3 = 0;
                                                    jal(ctx, 0x15BF38u, gen::fn_sub_103C30_00103c30);
                                                }
                                            }
                                            // 0x0015bf40
                                            charge(ctx, 5);
                                            v1 = 1;
                                            lw(v0, s0, sys::kConfigCursor);
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, s0);
                                            sw(v1, v0, 344);
                                        }
                                    }
                                } else {
                                    // 0x0015be58
                                    charge(ctx, 4);
                                    lw(v1, s0, sys::kConfigCursor);
                                    v0 = 7;
                                    if (v1 != v0) {
                                        // 0x0015be68
                                        charge(ctx, 5);
                                        v0 = sll(v1, 2);
                                        v0 = addu(v0, s0);
                                        lw(v0, v0, 344);
                                        if (v0 != 0) {
                                            // 0x0015be7c
                                            charge(ctx, 12);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 5;
                                            jal(ctx, 0x15BE8Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            lw(v0, s0, sys::kConfigCursor);
                                            v0 = sll(v0, 2);
                                            v0 = addu(v0, s0);
                                            sw(zero, v0, 344);
                                        }
                                    }
                                }
                            } else {
                                // 0x0015bda8
                                charge(ctx, 4);
                                lw(a0, s0, sys::kConfigCursor);
                                v1 = 7;
                                if (a0 == v1) {
                                    // 0x0015bde4
                                    charge(ctx, 4);
                                    v0 = v0 & 0x4000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0015bdf4
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x4000;  // cursor + 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0015be04
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0015be0c
                                        charge(ctx, 9);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x15BE1Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        sw(zero, s0, sys::kConfigCursor);
                                    }
                                } else {
                                    // 0x0015bdb8
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x15BDC8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, sys::kConfigCursor);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, sys::kConfigCursor);
                                }
                            }
                        } else {
                            // 0x0015bcf8
                            charge(ctx, 3);
                            lw(v1, s0, sys::kConfigCursor);
                            if (v1 == 0) {
                                // 0x0015bd30
                                charge(ctx, 4);
                                v0 = v0 & 0x1000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x0015bd40
                                    charge(ctx, 4);
                                    v0 = 0x7E0000;
                                    lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                    v0 = v0 & 0x1000;  // cursor - 1
                                    v0 = sltu(0, v0);
                                }
                                // 0x0015bd50
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0015bd58
                                    charge(ctx, 10);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x15BD68u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    v0 = 7;
                                    sw(v0, s0, sys::kConfigCursor);
                                }
                            } else {
                                // 0x0015bd04
                                charge(ctx, 11);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x15BD14u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s0, sys::kConfigCursor);
                                v0 = addiu(v0, -1);
                                sw(v0, s0, sys::kConfigCursor);
                            }
                        }
                    } else {
                        // 0x0015bc98
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 2;
                        jal(ctx, 0x15BCA8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 9;
                        sw(v0, s0, sys::kState);
                    }
                } else {
                    // 0x0015bbac
                    charge(ctx, 4);
                    lw(v1, s0, sys::kConfigCursor);
                    v0 = 7;
                    if (v1 == v0) {
                        // 0x0015bbbc
                        charge(ctx, 9);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x15BBCCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        s1 = 0;
                        for (;;) {
                            // 0x0015bc4c
                            charge(ctx, 3);
                            v0 = slti(s1, 7);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x0015bbe0
                            charge(ctx, 3);
                            v0 = 2;
                            if (s1 != v0) {
                                // 0x0015bc30
                                charge(ctx, 6);
                                a0 = addiu(s1, 387);
                                v0 = sll(s1, 2);
                                v0 = addu(s0, v0);
                                lw(a1, v0, 344);
                                jal(ctx, 0x15BC40u, gen::fn_datSetFlag_0016f1f0);
                            } else {
                                // 0x0015bbec
                                charge(ctx, 3);
                                lw(v0, s0, 348);
                                if (v0 != 0) {
                                    // 0x0015bc10
                                    charge(ctx, 8);
                                    a0 = addiu(s1, 387);
                                    v0 = sll(s1, 2);
                                    v0 = addu(s0, v0);
                                    lw(a1, v0, 344);
                                    jal(ctx, 0x15BC20u, gen::fn_datSetFlag_0016f1f0);
                                } else {
                                    // 0x0015bbf8
                                    charge(ctx, 6);
                                    a0 = addiu(s1, 387);
                                    a1 = 0;
                                    jal(ctx, 0x15BC00u, gen::fn_datSetFlag_0016f1f0);
                                }
                            }
                            // 0x0015bc48
                            charge(ctx, 1);
                            s1 = addiu(s1, 1);
                        }
                        // 0x0015bc58
                        charge(ctx, 5);
                        a0 = 387;
                        jal(ctx, 0x15BC5Cu, gen::fn_datGetFlag_0016f190);
                        if (v0 == 0) {
                            // 0x0015bc6c
                            charge(ctx, 2);
                            jal(ctx, 0x15BC6Cu, gen::fn_sub_103CB0_00103cb0);
                        }
                        // 0x0015bc74
                        charge(ctx, 6);
                        v0 = 1;
                        sw(v0, gp, g::kConfigFlag);  // 0x7CDF78
                        v0 = 9;
                        sw(v0, s0, sys::kState);
                    }
                }
            }
            // 0x0015bf54
            charge(ctx, 6);
            lw(s5, s0, sys::kConfigCursor);
            lw(s1, s0, sys::kPageTweens);
            s3 = 1;
            s4 = 0;
            for (;;) {
                // 0x0015bfe0
                charge(ctx, 3);
                v0 = slti(s4, 100);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015bf6c
                charge(ctx, 7);
                v0 = sll(s4, 4);
                v0 = addu(v0, s4);
                v0 = sll(v0, 2);
                s2 = addu(s1, v0);
                lw(v0, s2, 4);
                if (v0 != 0) {
                    // 0x0015bf88
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x15BF8Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0015bf9c
                        charge(ctx, 7);
                        a0 = s2;
                        a1 = addiu(s0, sys::kFiles);
                        a2 = s4;
                        a3 = s5;
                        t0 = addiu(s0, sys::kConfigValues);
                        jal(ctx, 0x15BFB0u, gen::fn_sub_155830_00155830);
                    }
                    // 0x0015bfb8
                    charge(ctx, 8);
                    v0 = sll(s4, 4);
                    v0 = addu(v0, s4);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0015bfd8
                        charge(ctx, 1);
                        s3 = 0;
                    }
                }
                // 0x0015bfdc
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x0015bfec
            charge(ctx, 3);
            sw(s3, s0, sys::kArrived);
            goto L_0015c430;
        case 0x15BFF8u:  // table[9]
            // 0x0015bff8
            charge(ctx, 5);
            lw(s3, s0, sys::kConfigCursor);
            lw(s1, s0, sys::kPageTweens);
            s2 = 0;
            for (;;) {
                // 0x0015c05c
                charge(ctx, 3);
                v0 = slti(s2, 100);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015c00c
                charge(ctx, 7);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                v0 = sll(v0, 2);
                s4 = addu(s1, v0);
                lw(v0, s4, 4);
                if (v0 != 0) {
                    // 0x0015c028
                    charge(ctx, 5);
                    a0 = s4;
                    jal(ctx, 0x15C02Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0015c03c
                        charge(ctx, 7);
                        a0 = s4;
                        a1 = addiu(s0, sys::kFiles);
                        a2 = s2;
                        a3 = s3;
                        t0 = addiu(s0, sys::kConfigValues);
                        jal(ctx, 0x15C050u, gen::fn_sub_155830_00155830);
                    }
                }
                // 0x0015c058
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0015c068
            charge(ctx, 193);
            v0 = 0x41A80000;  // 21.0f
            sw(v0, sp, 0xE0);
            v0 = 0x43570000;  // 215.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xE4);
            ld(t0, sp, 0xE0);
            sd(t0, sp, 0xB8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            lw(a0, s0, sys::kPageTweens);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C0C8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x424C0000;  // 51.0f
            sw(v0, sp, 0xE0);
            v0 = 0x43830000;  // 262.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xE4);
            ld(t0, sp, 0xE0);
            sd(t0, sp, 0xC0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 68);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C134u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 136);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C184u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42AE0000;  // 87.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xE4);
            ld(t0, sp, 0xE0);
            sd(t0, sp, 0xC8);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 204);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C1F0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            sw(v0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 272);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C240u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x43C20000;  // 388.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42B80000;  // 92.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xE4);
            ld(t0, sp, 0xE0);
            sd(t0, sp, 0xD0);
            v0 = 0x44160000;  // 600.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 340);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t1, sp, 0xE0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C2ACu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42BE0000;  // 95.0f
            sw(v0, sp, 0xE0);
            v0 = 0x42BA0000;  // 93.0f
            sw(v0, sp, 0xE4);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 408);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C2FCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v1 = 10;
            sw(v1, s0, sys::kState);
            v0 = 0x43C40000;  // 392.0f
            sw(v0, sp, 0xE0);
            v0 = 385;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            swc1(f0, sp, 0xE4);
            sd(zero, sp, 0x0);
            sd(v1, sp, 0x8);
            lw(v1, s0, sys::kPageTweens);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a0 = addiu(v1, 6732);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0xE0);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15C35Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            goto L_0015c430;
        case 0x15C36Cu:  // table[10]: state 10: done (-1)
            // 0x0015c36c
            charge(ctx, 5);
            lw(v0, s0, sys::kFade);
            v0 = addiu(v0, -1);
            sw(v0, s0, sys::kFade);
            if (i64(v0) < 0) {
                // 0x0015c380
                charge(ctx, 1);
                sw(zero, s0, sys::kFade);
            }
            // 0x0015c384
            charge(ctx, 6);
            lw(s5, s0, sys::kConfigCursor);
            lw(s1, s0, sys::kPageTweens);
            s3 = 1;
            s4 = 0;
            for (;;) {
                // 0x0015c410
                charge(ctx, 3);
                v0 = slti(s4, 100);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015c39c
                charge(ctx, 7);
                v0 = sll(s4, 4);
                v0 = addu(v0, s4);
                v0 = sll(v0, 2);
                s2 = addu(s1, v0);
                lw(v0, s2, 4);
                if (v0 != 0) {
                    // 0x0015c3b8
                    charge(ctx, 5);
                    a0 = s2;
                    jal(ctx, 0x15C3BCu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0015c3cc
                        charge(ctx, 7);
                        a0 = s2;
                        a1 = addiu(s0, sys::kFiles);
                        a2 = s4;
                        a3 = s5;
                        t0 = addiu(s0, sys::kConfigValues);
                        jal(ctx, 0x15C3E0u, gen::fn_sub_155830_00155830);
                    }
                    // 0x0015c3e8
                    charge(ctx, 8);
                    v0 = sll(s4, 4);
                    v0 = addu(v0, s4);
                    v0 = sll(v0, 2);
                    v0 = addu(s1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0015c408
                        charge(ctx, 1);
                        s3 = 0;
                    }
                }
                // 0x0015c40c
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
            // 0x0015c41c
            charge(ctx, 2);
            if (s3 == 0) {
                goto L_0015c430;
            }
            // 0x0015c424
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x15C430u:  // table[3, 4, 5]
            goto L_0015c430;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0015c434 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x80);
        lq(s5, sp, 0x70);
        lq(s4, sp, 0x60);
        lq(s3, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        sp = addiu(sp, 0xF0);
        return;
    }
    goto L_0015c430;
}

}  // namespace p3fes::game
