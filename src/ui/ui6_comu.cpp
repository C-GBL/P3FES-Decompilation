// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the social-link screen (its update, the link list, the card view, the arcana pages).
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
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_11E380_0011e380(p3fes::EEContext&);
void fn_sub_135120_00135120(p3fes::EEContext&);
void fn_sub_135460_00135460(p3fes::EEContext&);
void fn_sub_1355C0_001355c0(p3fes::EEContext&);
void fn_sub_136820_00136820(p3fes::EEContext&);
void fn_sub_1368A0_001368a0(p3fes::EEContext&);
void fn_sub_136A10_00136a10(p3fes::EEContext&);
void fn_sub_137300_00137300(p3fes::EEContext&);
void fn_sub_137580_00137580(p3fes::EEContext&);
void fn_sub_1380E0_001380e0(p3fes::EEContext&);
void fn_sub_1387B0_001387b0(p3fes::EEContext&);
void fn_sub_138E80_00138e80(p3fes::EEContext&);
void fn_sub_138EE0_00138ee0(p3fes::EEContext&);
void fn_sub_1392D0_001392d0(p3fes::EEContext&);
void fn_sub_139660_00139660(p3fes::EEContext&);
void fn_sub_139DC0_00139dc0(p3fes::EEContext&);
void fn_sub_139FC0_00139fc0(p3fes::EEContext&);
void fn_sub_13AFD0_0013afd0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_1775A0_001775a0(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_3B2F90_003b2f90(p3fes::EEContext&);
void fn_sub_3C7D80_003c7d80(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
void fn_sub_3C7E50_003c7e50(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui6;  // the record offsets, $gp words, pad words and sprite tables of ui6.h

// 0x001355C0 sub_1355C0 -- 4080 bytes; frame 0x180: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_Camp_UpdateComuDrawTask] Update of the social-link screen "H_CampComuDraw" (jump table 0x7B5D00): 0 waits for
// camp/comu/datComuHelp.bmd (+336, message 11) and builds the list of shown arcana pages into 0x833A60 from flags 336..
// / 26 / 343; 2 waits for flash 7, creates the file loader "H_CampComuFileSetup" and lists the active links
// (datComuIsActive) into +32; 3..5 slide in and are the input state (cancel -1, confirm -> 6, H_Camp_MoveListCursor
// over the links); 6 releases the pictures (textureDestroy); 7 / 8 wait for flash 8 and request the arcana and bust-up
// pictures (sub_135460 / sub_135120); 9 / 0xB the card view: the picture builds (sub_10C1A0 / sub_10C3A0 of
// off_5DB998[datComuGetArcana] and camp/commu/tim2_bustup/i_bust%02X_{a,b}.tmx). Draws through sub_136820 / sub_138E80.
void sub_1355C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x001355c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x180);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s2 = a0;
    lw(s1, a0, 60);
    mtc1(zero, f0);
    sw(zero, sp, 0x174);
    sw(zero, sp, 0x170);
    lw(v0, s1, comu::kState);
    at = sltiu(v0, 12);
    if (at != 0) {
        // 0x001355f8
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23808);  // &0x7B5D00
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x135614u:  // table[0]: state 0: datComuHelp.bmd, the arcana pages
            // 0x00135614
            charge(ctx, 5);
            lw(a0, s1, comu::kHelpFile);
            jal(ctx, 0x135618u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00135628
                charge(ctx, 9);
                lw(v0, s1, comu::kHelpFile);
                a0 = 11;
                lw(a1, v0, 272);
                jal(ctx, 0x135634u, gen::fn_sub_3C7D80_003c7d80);
                s0 = 0;
                s2 = 0;
                for (;;) {
                    // 0x001357b8
                    charge(ctx, 3);
                    v0 = slti(s2, 9);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0013564c
                    charge(ctx, 3);
                    v0 = 5;
                    if (s2 != v0) {
                        // 0x00135690
                        charge(ctx, 3);
                        v0 = 7;
                        if (s2 != v0) {
                            // 0x0013569c
                            charge(ctx, 5);
                            a0 = addiu(s2, 336);
                            jal(ctx, 0x1356A0u, gen::fn_datGetFlag_0016f190);
                            if (v0 != 0) {
                                // 0x001356b0
                                charge(ctx, 3);
                                at = sltiu(s2, 9);
                                if (at != 0) {
                                    // 0x001356bc
                                    charge(ctx, 7);
                                    v1 = 0x7B0000;
                                    v1 = addiu(v1, 23760);  // &0x7B5CD0
                                    v0 = sll(s2, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 0);
                                    switch (v0.u()) {
                                    case 0x1356D8u:  // table[0]: page 2
                                        // 0x001356d8
                                        charge(ctx, 8);
                                        a0 = 2;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x1356F8u:  // table[1]: page 3
                                        // 0x001356f8
                                        charge(ctx, 8);
                                        a0 = 3;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x135718u:  // table[2]: page 4
                                        // 0x00135718
                                        charge(ctx, 8);
                                        a0 = 4;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x135738u:  // table[3]
                                        // 0x00135738
                                        charge(ctx, 8);
                                        a0 = 5;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x135758u:  // table[4]
                                        // 0x00135758
                                        charge(ctx, 8);
                                        a0 = 6;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x135778u:  // table[6]
                                        // 0x00135778
                                        charge(ctx, 8);
                                        a0 = 8;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x135798u:  // table[8]
                                        // 0x00135798
                                        charge(ctx, 6);
                                        a0 = 10;
                                        v1 = sll(s0, 1);
                                        v0 = 0x830000;
                                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                                        v0 = addu(v0, v1);
                                        sh(a0, v0, 0);
                                        break;
                                    case 0x1357B0u:  // table[5, 7]
                                        break;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, v0.u());
                                        return;
                                    }
                                }
                                // 0x001357b0
                                charge(ctx, 1);
                                s0 = addiu(s0, 1);
                            }
                        }
                    } else {
                        // 0x00135658
                        charge(ctx, 5);
                        a0 = 26;
                        jal(ctx, 0x13565Cu, gen::fn_datGetFlag_0016f190);
                        if (v0 != 0) {
                            // 0x0013566c
                            charge(ctx, 9);
                            a0 = 7;
                            v1 = sll(s0, 1);
                            v0 = 0x830000;
                            v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                            v0 = addu(v0, v1);
                            sh(a0, v0, 0);
                            s0 = addiu(s0, 1);
                        }
                    }
                    // 0x001357b4
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x001357c4
                charge(ctx, 5);
                a0 = 343;
                jal(ctx, 0x1357C8u, gen::fn_datGetFlag_0016f190);
                if (v0 != 0) {
                    // 0x001357d8
                    charge(ctx, 7);
                    a0 = 9;
                    v1 = sll(s0, 1);
                    v0 = 0x830000;
                    v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                    v0 = addu(v0, v1);
                    sh(a0, v0, 0);
                    s0 = addiu(s0, 1);
                }
                // 0x001357f4
                charge(ctx, 3);
                v0 = 9;
                if (s0 != v0) {
                    // 0x00135800
                    charge(ctx, 5);
                    v1 = sll(s0, 1);
                    v0 = 0x830000;
                    v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                    v0 = addu(v0, v1);
                    sh(zero, v0, 0);
                }
                // 0x00135814
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s1, comu::kState);
            }
        L_00136590:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x135824u:  // table[2]: state 2: flash 7, the file loader, the links
            // 0x00135824
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 7;
            jal(ctx, 0x13582Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00135848
                charge(ctx, 3);
                lw(v0, s1, 372);
                if (v0 == 0) {
                    // 0x00135854
                    charge(ctx, 9);
                    a0 = 1;
                    a1 = 248;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, 388);  // 0x960184
                    jalr(ctx, 0x135868u, v0.u());
                    if (v0 != 0) {
                        // 0x00135884
                        charge(ctx, 13);
                        a0 = s2;
                        a1 = 4207;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, -17696);  // "H_CampComuFileSetup"
                        a3 = 0x130000;
                        a3 = addiu(a3, 18960);  // &sub_134A10
                        t0 = 0x130000;
                        t0 = addiu(t0, 19840);  // &sub_134D80
                        t1 = v0;
                        jal(ctx, 0x1358A8u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
                        if (v0 == 0) {
                            // 0x001358b8
                            charge(ctx, 1);
                            v0 = 0;
                        }
                    } else {
                        // 0x00135878
                        charge(ctx, 3);
                        v0 = 0;
                    }
                    // 0x001358bc
                    charge(ctx, 5);
                    sw(v0, s1, 372);
                    s2 = 0;
                    s0 = 0;
                    for (;;) {
                        // 0x0013590c
                        charge(ctx, 3);
                        v0 = slti(s0, 30);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001358d0
                        charge(ctx, 10);
                        v1 = si(-1);
                        v0 = sll(s0, 2);
                        v0 = addu(s1, v0);
                        sw(v1, v0, 32);
                        a0 = dsll32(s0, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x1358E8u, gen::fn_sub_16E100_0016e100);  // [datComuIsActive]
                        if (v0 != 0) {
                            // 0x001358f8
                            charge(ctx, 4);
                            v0 = sll(s2, 2);
                            v0 = addu(s1, v0);
                            sw(s0, v0, 32);
                            s2 = addiu(s2, 1);
                        }
                        // 0x00135908
                        charge(ctx, 1);
                        s0 = addiu(s0, 1);
                    }
                    // 0x00135918
                    charge(ctx, 6);
                    sw(s2, s1, 16);
                    t1 = 0;
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 12832);  // &0x5E3220
                    for (;;) {
                        // 0x00135994
                        charge(ctx, 4);
                        lw(v0, s1, 16);
                        v0 = slt(t1, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00135930
                        charge(ctx, 5);
                        t2 = addiu(t1, 1);
                        v0 = sll(t1, 2);
                        t0 = addu(s1, v0);
                        for (;;) {
                            // 0x00135980
                            charge(ctx, 4);
                            lw(v0, s1, 16);
                            v0 = slt(t2, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x00135944
                            charge(ctx, 12);
                            v0 = sll(t2, 2);
                            v0 = addu(s1, v0);
                            a3 = addiu(v0, 32);
                            lw(a2, v0, 32);
                            lw(a1, t0, 32);
                            v0 = addu(a0, a1);
                            lb(v1, v0, 0);
                            v0 = addu(a0, a2);
                            lb(v0, v0, 0);
                            at = slt(v0, v1);
                            if (at != 0) {
                                // 0x00135974
                                charge(ctx, 2);
                                sw(a2, t0, 32);
                                sw(a1, a3, 0);
                            }
                            // 0x0013597c
                            charge(ctx, 1);
                            t2 = addiu(t2, 1);
                        }
                        // 0x00135990
                        charge(ctx, 1);
                        t1 = addiu(t1, 1);
                    }
                }
                // 0x001359a4
                charge(ctx, 4);
                v0 = 3;
                sw(v0, s1, comu::kState);
                goto L_00136590;
            }
            // 0x0013583c
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x1359B4u:  // table[3]: state 3: slide in
            // 0x001359b4
            charge(ctx, 5);
            lw(v0, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v0, v0, 60);
            lw(v0, v0, 16);
            if (v0 != 0) {
                // 0x001359c8
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s1, comu::kState);
            }
            goto L_00136590;
        case 0x1359D8u:  // table[4]: state 4: slide in
            // 0x001359d8
            charge(ctx, 6);
            lw(v0, s1, 372);
            lw(v0, v0, 60);
            lw(v0, v0, 0);
            at = slti(v0, 3);
            if (at == 0) {
                // 0x001359fc
                charge(ctx, 8);
                swc1(f0, sp, 0x16C);
                swc1(f0, sp, 0x168);
                lw(v0, s1, 12);
                v0 = addiu(v0, 1);
                sw(v0, s1, 12);
                at = slti(v0, 31);
                if (at == 0) {
                    // 0x00135a1c
                    charge(ctx, 2);
                    v0 = 5;
                    sw(v0, s1, comu::kState);
                }
                // 0x00135a24
                charge(ctx, 14);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                ld(a0, sp, 0x168);
                a1 = addiu(s1, comu::kLinks);
                lw(a2, s1, 16);
                lw(a3, s1, comu::kScroll);
                lw(t0, s1, comu::kCursor);
                t1 = 0;
                lw(t2, s1, 12);
                t3 = 0;
                jal(ctx, 0x135A4Cu, gen::fn_sub_136820_00136820);  // [H_Camp_ComuDrawPanel]
                goto L_00136590;
            }
            // 0x001359f0
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x135A5Cu:  // table[5]: state 5: the list (input)
            // 0x00135a5c
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
            v0 = v0 & 0x20;  // cancel
            if (v0 == 0) {
                // 0x00135a94
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, pad::kRepeat);  // 0x7E0952
                v0 = v0 & 0x40;  // confirm
                if (v0 == 0) {
                    // 0x00135b14
                    charge(ctx, 6);
                    lw(a0, s1, 16);
                    a1 = 5;
                    a2 = addiu(s1, comu::kScroll);
                    a3 = addiu(s1, comu::kCursor);
                    jal(ctx, 0x135B24u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                } else {
                    // 0x00135aa8
                    charge(ctx, 9);
                    lw(v1, s1, comu::kScroll);
                    lw(v0, s1, comu::kCursor);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s1);
                    lw(v1, v0, 32);
                    v0 = si(-1);
                    if (v1 != v0) {
                        // 0x00135acc
                        charge(ctx, 18);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x135ADCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = si(-200);
                        sw(v0, gp, g::kComuCardScroll);  // 0x7CDF6C
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 1;
                        jal(ctx, 0x135AFCu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        v0 = 6;
                        sw(v0, s1, comu::kState);
                    }
                }
                // 0x00135b2c
                charge(ctx, 16);
                sw(zero, sp, 0x164);
                sw(zero, sp, 0x160);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                ld(a0, sp, 0x160);
                a1 = addiu(s1, comu::kLinks);
                lw(a2, s1, 16);
                lw(a3, s1, comu::kScroll);
                lw(t0, s1, comu::kCursor);
                t1 = 1;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x135B5Cu, gen::fn_sub_136820_00136820);  // [H_Camp_ComuDrawPanel]
                goto L_00136590;
            }
            // 0x00135a70
            charge(ctx, 9);
            a0 = 0;
            a1 = 0;
            a2 = 0;
            a3 = 2;
            jal(ctx, 0x135A80u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
            v0 = si(-1);
            break;
        case 0x135B6Cu:  // table[6]: state 6: release the pictures
            // 0x00135b6c
            charge(ctx, 4);
            v0 = 0x830000;
            lw(v0, v0, spr::kComuCards);  // 0x833AD8: a card texture slot
            if (v0 != 0) {
                // 0x00135b7c
                charge(ctx, 3);
                lw(a0, s1, 364);
                if (a0 != 0) {
                    // 0x00135b88
                    charge(ctx, 4);
                    jal(ctx, 0x135B88u, gen::fn_sub_4D0F00_004d0f00);  // [textureDestroy]
                    sw(zero, s1, 364);
                    sw(zero, gp, g::kComuBustBuild);  // 0x7CDF70
                }
                // 0x00135b98
                charge(ctx, 3);
                lw(a0, s1, 368);
                if (a0 != 0) {
                    // 0x00135ba4
                    charge(ctx, 4);
                    jal(ctx, 0x135BA4u, gen::fn_sub_4D0F00_004d0f00);  // [textureDestroy]
                    sw(zero, s1, 368);
                    sw(zero, gp, g::kComuArcanaBuild);  // 0x7CDF74
                }
                // 0x00135bb4
                charge(ctx, 2);
                v0 = 7;
                sw(v0, s1, comu::kState);
            }
            // 0x00135bbc
            charge(ctx, 16);
            sw(zero, sp, 0x174);
            sw(zero, sp, 0x170);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            ld(a0, sp, 0x170);
            a1 = addiu(s1, comu::kLinks);
            lw(a2, s1, 16);
            lw(a3, s1, comu::kScroll);
            lw(t0, s1, comu::kCursor);
            t1 = 2;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x135BECu, gen::fn_sub_136820_00136820);  // [H_Camp_ComuDrawPanel]
            goto L_00136590;
        case 0x135BFCu:  // table[7]: state 7
            // 0x00135bfc
            charge(ctx, 19);
            sw(zero, s1, 20);
            swc1(f0, sp, 0x174);
            swc1(f0, sp, 0x170);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            ld(a0, sp, 0x170);
            a1 = addiu(s1, comu::kLinks);
            lw(a2, s1, 16);
            lw(a3, s1, comu::kScroll);
            lw(t0, s1, comu::kCursor);
            t1 = 2;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x135C30u, gen::fn_sub_136820_00136820);  // [H_Camp_ComuDrawPanel]
            v0 = 8;
            sw(v0, s1, comu::kState);
            goto L_00136590;
        case 0x135C48u:  // table[8]: state 8: flash 8, request the pictures
            // 0x00135c48
            charge(ctx, 20);
            swc1(f0, sp, 0x174);
            swc1(f0, sp, 0x170);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            ld(a0, sp, 0x170);
            a1 = addiu(s1, comu::kLinks);
            lw(a2, s1, 16);
            lw(a3, s1, comu::kScroll);
            lw(t0, s1, comu::kCursor);
            t1 = 2;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x135C78u, gen::fn_sub_136820_00136820);  // [H_Camp_ComuDrawPanel]
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 8;
            jal(ctx, 0x135C88u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00135ca4
                charge(ctx, 11);
                a0 = s2;
                jal(ctx, 0x135CA8u, gen::fn_sub_135460_00135460);
                a0 = s2;
                jal(ctx, 0x135CB4u, gen::fn_sub_135120_00135120);
                sw(zero, s1, 12);
                v0 = 9;
                sw(v0, s1, comu::kState);
                goto L_00136590;
            }
            // 0x00135c98
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x135CD0u:  // table[9]: state 9: the card view
            // 0x00135cd0
            charge(ctx, 6);
            lw(v0, s1, 372);
            lw(v0, v0, 60);
            lw(v0, v0, 0);
            at = slti(v0, 9);
            if (at == 0) {
                // 0x00135cf4
                charge(ctx, 5);
                lw(v0, gp, g::kCampFlashTask);  // 0x7CDF50
                lw(v0, v0, 60);
                lw(v0, v0, 16);
                if (v0 != 0) {
                    // 0x00135d08
                    charge(ctx, 2);
                    v0 = 11;
                    sw(v0, s1, comu::kState);
                }
                // 0x00135d10
                charge(ctx, 14);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                ld(a0, sp, 0x170);
                a1 = addiu(s1, comu::kLinks);
                lw(a2, s1, 16);
                lw(a3, s1, comu::kScroll);
                lw(t0, s1, comu::kCursor);
                t1 = 2;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x135D38u, gen::fn_sub_136820_00136820);  // [H_Camp_ComuDrawPanel]
                goto L_00136590;
            }
            // 0x00135ce8
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x135D48u:  // table[11]: state 11: the picture builds
            // 0x00135d48
            charge(ctx, 4);
            lw(v0, s1, 12);
            at = slti(v0, 20);
            if (at != 0) {
                // 0x00135d58
                charge(ctx, 2);
                v0 = addiu(v0, 1);
                sw(v0, s1, 12);
            }
            // 0x00135d60
            charge(ctx, 3);
            lw(a0, s1, 348);
            if (a0 != 0) {
                // 0x00135d6c
                charge(ctx, 3);
                lw(v0, s1, 360);
                if (v0 != 0) {
                    // 0x00135e10
                    charge(ctx, 9);
                    a0 = v0;
                    a1 = addiu(sp, 0x17C);
                    a2 = 0;
                    jal(ctx, 0x135E1Cu, gen::fn_sub_10C3A0_0010c3a0);  // poll the texture build
                    sw(v0, s1, 368);
                    lw(v0, sp, 0x17C);
                    if (v0 == 0) {
                        // 0x00135e5c
                        charge(ctx, 1);
                        sw(zero, gp, g::kComuArcanaBuild);  // 0x7CDF74
                    } else {
                        // 0x00135e34
                        charge(ctx, 10);
                        sw(zero, s1, 28);
                        sw(zero, s1, 360);
                        lw(v0, s1, 368);
                        sw(v0, gp, g::kComuArcanaBuild);  // 0x7CDF74
                        lw(a0, s1, 348);
                        jal(ctx, 0x135E48u, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s1, 348);
                    }
                } else {
                    // 0x00135d78
                    charge(ctx, 4);
                    jal(ctx, 0x135D78u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        // 0x00135d88
                        charge(ctx, 34);
                        lw(v1, s1, comu::kCursor);
                        lw(v0, s1, comu::kScroll);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s1);
                        lh(a0, v0, 32);
                        jal(ctx, 0x135DA0u, gen::fn_sub_16DF30_0016df30);  // [datComuGetArcana]
                        v1 = dsll32(v0, 24);
                        v1 = dsra32(v1, 24);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5E0000;
                        v0 = addiu(v0, -17864);  // "_h_camp_comu.c"
                        sd(v0, sp, 0x10);
                        v0 = 746;
                        sd(v0, sp, 0x18);
                        v1 = sll(v1, 2);
                        v0 = 0x5E0000;
                        v0 = addiu(v0, -18024);  // &0x5DB998
                        v0 = addu(v0, v1);
                        a0 = 0;
                        lw(a1, v0, 0);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x135DFCu, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                        sw(v0, s1, 360);
                    }
                }
            }
            // 0x00135e60
            charge(ctx, 3);
            lw(a0, s1, 344);
            if (a0 != 0) {
                // 0x00135e6c
                charge(ctx, 3);
                lw(v0, s1, 356);
                if (v0 != 0) {
                    // 0x0013606c
                    charge(ctx, 9);
                    a0 = v0;
                    a1 = addiu(sp, 0x17C);
                    a2 = 0;
                    jal(ctx, 0x136078u, gen::fn_sub_10C3A0_0010c3a0);  // poll the texture build
                    sw(v0, s1, 364);
                    lw(v0, sp, 0x17C);
                    if (v0 == 0) {
                        // 0x001360b8
                        charge(ctx, 1);
                        sw(zero, gp, g::kComuBustBuild);  // 0x7CDF70
                    } else {
                        // 0x00136090
                        charge(ctx, 10);
                        sw(zero, s1, 24);
                        sw(zero, s1, 356);
                        lw(v0, s1, 364);
                        sw(v0, gp, g::kComuBustBuild);  // 0x7CDF70
                        lw(a0, s1, 344);
                        jal(ctx, 0x1360A4u, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s1, 344);
                    }
                } else {
                    // 0x00135e78
                    charge(ctx, 4);
                    jal(ctx, 0x135E78u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        // 0x00135e88
                        charge(ctx, 8);
                        lw(v1, s1, comu::kScroll);
                        lw(v0, s1, comu::kCursor);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s1);
                        lw(s0, v0, 32);
                        if (s0 != 0) {
                            // 0x00135ea8
                            charge(ctx, 3);
                            v0 = 29;
                            if (s0 == v0) {
                                goto L_00135f94;
                            }
                            // 0x00135eb4
                            charge(ctx, 5);
                            a0 = s0;
                            jal(ctx, 0x135EB8u, gen::fn_sub_172160_00172160);  // (link)
                            if (v0 == 0) {
                                // 0x00135ec8
                                charge(ctx, 5);
                                a0 = s0;
                                jal(ctx, 0x135ECCu, gen::fn_sub_1717C0_001717c0);  // (link)
                                if (v0 != 0) {
                                    goto L_00135edc;
                                }
                                // 0x00135f38
                                charge(ctx, 23);
                                lw(v1, s1, comu::kCursor);
                                lw(v0, s1, comu::kScroll);
                                v0 = addu(v1, v0);
                                v0 = sll(v0, 2);
                                v0 = addu(v0, s1);
                                lw(v1, v0, 32);
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                v1 = sll(v0, 1);
                                v0 = 0x5E0000;
                                v0 = addiu(v0, -17664);  // &0x5DBB00
                                v1 = addu(v0, v1);
                                lw(v0, s1, 20);
                                v0 = sll(v0, 1);
                                v0 = addu(v0, v1);
                                lhu(a2, v0, 0);
                                a0 = addiu(sp, 0x60);
                                a1 = 0x5E0000;
                                a1 = addiu(a1, -17424);  // "camp/commu/tim2_bustup/i_bust%02X_a.tmx"
                                jal(ctx, 0x135F84u, gen::fn_sprintf_00523ac8);
                                goto L_0013601c;
                            }
                        L_00135edc:
                            charge(ctx, 23);
                            lw(v1, s1, comu::kCursor);
                            lw(v0, s1, comu::kScroll);
                            v0 = addu(v1, v0);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, s1);
                            lw(v1, v0, 32);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v1 = sll(v0, 1);
                            v0 = 0x5E0000;
                            v0 = addiu(v0, -17664);  // &0x5DBB00
                            v1 = addu(v0, v1);
                            lw(v0, s1, 20);
                            v0 = sll(v0, 1);
                            v0 = addu(v0, v1);
                            lhu(a2, v0, 0);
                            a0 = addiu(sp, 0x60);
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -17472);  // "camp/commu/tim2_bustup/i_bust%02X_b.tmx"
                            jal(ctx, 0x135F28u, gen::fn_sprintf_00523ac8);
                            goto L_0013601c;
                        }
                    L_00135f94:
                        charge(ctx, 5);
                        a0 = s0;
                        jal(ctx, 0x135F98u, gen::fn_sub_172160_00172160);  // (link)
                        if (v0 == 0) {
                            // 0x00135fa8
                            charge(ctx, 5);
                            a0 = s0;
                            jal(ctx, 0x135FACu, gen::fn_sub_1717C0_001717c0);  // (link)
                            if (v0 != 0) {
                                goto L_00135fbc;
                            }
                            // 0x00135ff0
                            charge(ctx, 11);
                            lw(v0, s1, 20);
                            v1 = sll(v0, 1);
                            v0 = 0x830000;
                            v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                            v0 = addu(v0, v1);
                            lh(a2, v0, 0);
                            a0 = addiu(sp, 0x60);
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -17424);  // "camp/commu/tim2_bustup/i_bust%02X_a.tmx"
                            jal(ctx, 0x136014u, gen::fn_sprintf_00523ac8);
                            goto L_0013601c;
                        }
                    L_00135fbc:
                        charge(ctx, 13);
                        lw(v0, s1, 20);
                        v1 = sll(v0, 1);
                        v0 = 0x830000;
                        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
                        v0 = addu(v0, v1);
                        lh(a2, v0, 0);
                        a0 = addiu(sp, 0x60);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -17472);  // "camp/commu/tim2_bustup/i_bust%02X_b.tmx"
                        jal(ctx, 0x135FE0u, gen::fn_sprintf_00523ac8);
                    L_0013601c:
                        charge(ctx, 20);
                        sd(zero, sp, 0x0);
                        sd(zero, sp, 0x8);
                        v0 = 0x5E0000;
                        v0 = addiu(v0, -17864);  // "_h_camp_comu.c"
                        sd(v0, sp, 0x10);
                        v0 = 787;
                        sd(v0, sp, 0x18);
                        a0 = 0;
                        a1 = addiu(sp, 0x60);
                        a2 = 0;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        t2 = 0;
                        t3 = 0;
                        jal(ctx, 0x136058u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                        sw(v0, s1, 356);
                    }
                }
            }
            // 0x001360bc
            charge(ctx, 8);
            lw(v1, s1, comu::kScroll);
            lw(v0, s1, comu::kCursor);
            s0 = addu(v0, v1);
            v1 = sll(s0, 2);
            v1 = addu(v1, s1);
            lw(a1, v1, 32);
            if (a1 != 0) {
                // 0x001360dc
                charge(ctx, 3);
                v1 = 29;
                if (a1 == v1) {
                    goto L_00136140;
                }
                // 0x001360e8
                charge(ctx, 10);
                v1 = 0;
                a2 = 0;
                a0 = sll(a1, 1);
                a0 = addu(a0, a1);
                a1 = sll(a0, 1);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17664);  // &0x5DBB00
                a1 = addu(a0, a1);
                for (;;) {
                    // 0x0013612c
                    charge(ctx, 3);
                    a0 = slti(a2, 3);
                    if (a0 == 0) {
                        goto L_00136138_109;
                    }
                    backedge(ctx);
                    // 0x00136110
                    charge(ctx, 5);
                    a0 = sll(a2, 1);
                    a0 = addu(a0, a1);
                    lhu(a0, a0, 0);
                    if (a0 != 0) {
                        // 0x00136124
                        charge(ctx, 2);
                        v1 = addiu(v1, 1);
                        a2 = addiu(a2, 1);
                        continue;
                    }
                    break;
                }
                goto L_001361cc;
            }
        L_00136140:
            charge(ctx, 3);
            v1 = 0;
            if (a1 != 0) {
                // 0x00136190
                charge(ctx, 5);
                a2 = 0;
                a1 = 0x830000;
                a1 = addiu(a1, spr::kComuPages);  // &0x833A60: the arcana pages shown
                for (;;) {
                    // 0x001361c0
                    charge(ctx, 3);
                    a0 = slti(a2, 8);
                    if (a0 != 0) {
                        backedge(ctx);
                        // 0x001361a4
                        charge(ctx, 5);
                        a0 = sll(a2, 1);
                        a0 = addu(a1, a0);
                        lh(a0, a0, 0);
                        if (a0 != 0) {
                            // 0x001361b8
                            charge(ctx, 2);
                            v1 = addiu(v1, 1);
                            a2 = addiu(a2, 1);
                            continue;
                        }
                    }
                    break;
                }
            } else {
                // 0x0013614c
                charge(ctx, 5);
                a2 = 0;
                a1 = 0x830000;
                a1 = addiu(a1, spr::kComuPages);  // &0x833A60: the arcana pages shown
                for (;;) {
                    // 0x0013617c
                    charge(ctx, 3);
                    a0 = slti(a2, 9);
                    if (a0 == 0) {
                        goto L_00136188_115;
                    }
                    backedge(ctx);
                    // 0x00136160
                    charge(ctx, 5);
                    a0 = sll(a2, 1);
                    a0 = addu(a1, a0);
                    lh(a0, a0, 0);
                    if (a0 != 0) {
                        // 0x00136174
                        charge(ctx, 2);
                        v1 = addiu(v1, 1);
                        a2 = addiu(a2, 1);
                        continue;
                    }
                    break;
                }
            }
        L_001361cc:
            charge(ctx, 5);
            a0 = 0x7E0000;
            lhu(a1, a0, 2386);  // 0x7E0952
            a0 = a1 & 0x4;
            if (a0 == 0) {
                // 0x001362cc
                charge(ctx, 3);
                v0 = a1 & 0x8;
                if (v0 == 0) {
                    // 0x00136410
                    charge(ctx, 4);
                    v0 = a1 & 0x1000;
                    v0 = sltu(0, v0);
                    if (v0 == 0) {
                        // 0x00136420
                        charge(ctx, 4);
                        v0 = 0x7E0000;
                        lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                        v0 = v0 & 0x1000;  // cursor - 1
                        v0 = sltu(0, v0);
                    }
                    // 0x00136430
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x0013647c
                        charge(ctx, 4);
                        v0 = a1 & 0x4000;
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x0013648c
                            charge(ctx, 4);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x4000;  // cursor + 1
                            v0 = sltu(0, v0);
                        }
                        // 0x0013649c
                        charge(ctx, 2);
                        if (v0 == 0) {
                            // 0x001364f0
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                            v0 = v0 & 0x20;  // cancel
                            if (v0 != 0) {
                                // 0x00136504
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 2;
                                jal(ctx, 0x136514u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                v0 = 2;
                                sw(v0, s1, comu::kState);
                            }
                        } else {
                            // 0x001364a4
                            charge(ctx, 5);
                            lw(a0, s1, 20);
                            v0 = addiu(v1, -1);
                            at = slt(a0, v0);
                            if (at != 0) {
                                // 0x001364b8
                                charge(ctx, 14);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x1364C8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(v0, s1, 20);
                                v0 = addiu(v0, 1);
                                sw(v0, s1, 20);
                                a0 = s2;
                                jal(ctx, 0x1364E0u, gen::fn_sub_135120_00135120);
                            }
                        }
                    } else {
                        // 0x00136438
                        charge(ctx, 3);
                        lw(v0, s1, 20);
                        if (v0 != 0) {
                            // 0x00136444
                            charge(ctx, 14);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 0;
                            jal(ctx, 0x136454u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            lw(v0, s1, 20);
                            v0 = addiu(v0, -1);
                            sw(v0, s1, 20);
                            a0 = s2;
                            jal(ctx, 0x13646Cu, gen::fn_sub_135120_00135120);
                        }
                    }
                } else {
                    // 0x001362d8
                    charge(ctx, 4);
                    lw(v0, s1, 16);
                    at = slti(v0, 6);
                    if (at == 0) {
                        // 0x00136338
                        charge(ctx, 10);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x136348u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        lw(a1, s1, comu::kCursor);
                        v0 = 3;
                        if (a1 != v0) {
                            // 0x00136398
                            charge(ctx, 3);
                            v0 = 4;
                            if (a1 != v0) {
                                // 0x001363b4
                                charge(ctx, 2);
                                v0 = addiu(a1, 1);
                                sw(v0, s1, comu::kCursor);
                            } else {
                                // 0x001363a4
                                charge(ctx, 4);
                                sw(zero, s1, comu::kScroll);
                                sw(zero, s1, comu::kCursor);
                            }
                        } else {
                            // 0x00136360
                            charge(ctx, 6);
                            lw(a0, s1, 16);
                            lw(v1, s1, comu::kScroll);
                            v0 = addiu(v1, 5);
                            at = slt(v0, a0);
                            if (at == 0) {
                                // 0x00136388
                                charge(ctx, 4);
                                v0 = addiu(a1, 1);
                                sw(v0, s1, comu::kCursor);
                            } else {
                                // 0x00136378
                                charge(ctx, 4);
                                v0 = addiu(v1, 1);
                                sw(v0, s1, comu::kScroll);
                            }
                        }
                    } else {
                        // 0x001362e8
                        charge(ctx, 6);
                        lw(v0, s1, comu::kCursor);
                        v1 = addiu(v0, 1);
                        sw(v1, s1, comu::kCursor);
                        lw(v0, s1, 16);
                        if (v1 == v0) {
                            // 0x00136300
                            charge(ctx, 6);
                            sw(zero, s1, comu::kScroll);
                            sw(zero, s1, comu::kCursor);
                            lw(v1, s1, 16);
                            v0 = 1;
                            if (v1 != v0) {
                                // 0x00136318
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x136328u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            }
                        }
                    }
                    // 0x001363bc
                    charge(ctx, 5);
                    lw(v1, s1, comu::kCursor);
                    lw(v0, s1, comu::kScroll);
                    v0 = addu(v1, v0);
                    if (s0 != v0) {
                        // 0x001363d0
                        charge(ctx, 16);
                        a0 = 0;
                        a1 = 0;
                        a2 = 0;
                        a3 = 0;
                        jal(ctx, 0x1363E0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        sw(zero, s1, 20);
                        a0 = s2;
                        jal(ctx, 0x1363F0u, gen::fn_sub_135460_00135460);
                        a0 = s2;
                        jal(ctx, 0x1363FCu, gen::fn_sub_135120_00135120);
                        sw(zero, s1, 12);
                    }
                }
            } else {
                // 0x001361e0
                charge(ctx, 4);
                lw(a0, s1, comu::kCursor);
                v1 = 1;
                if (a0 != v1) {
                    // 0x00136224
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00136270
                        charge(ctx, 2);
                        v0 = addiu(a0, -1);
                        sw(v0, s1, comu::kCursor);
                    } else {
                        // 0x0013622c
                        charge(ctx, 4);
                        lw(v0, s1, 16);
                        at = slti(v0, 5);
                        if (at == 0) {
                            // 0x00136254
                            charge(ctx, 7);
                            v0 = 4;
                            sw(v0, s1, comu::kCursor);
                            lw(v0, s1, 16);
                            v0 = addiu(v0, -5);
                            sw(v0, s1, comu::kScroll);
                        } else {
                            // 0x0013623c
                            charge(ctx, 6);
                            sw(zero, s1, comu::kScroll);
                            lw(v0, s1, 16);
                            v0 = addiu(v0, -1);
                            sw(v0, s1, comu::kCursor);
                        }
                    }
                } else {
                    // 0x001361f0
                    charge(ctx, 4);
                    sw(v1, sp, 0x17C);
                    lw(v0, s1, comu::kScroll);
                    if (v0 == 0) {
                        // 0x00136210
                        charge(ctx, 5);
                        lw(v0, s1, comu::kCursor);
                        v0 = addiu(v0, -1);
                        sw(v0, s1, comu::kCursor);
                    } else {
                        // 0x00136200
                        charge(ctx, 4);
                        v0 = addiu(v0, -1);
                        sw(v0, s1, comu::kScroll);
                    }
                }
                // 0x00136278
                charge(ctx, 5);
                lw(v1, s1, comu::kCursor);
                lw(v0, s1, comu::kScroll);
                v0 = addu(v1, v0);
                if (s0 != v0) {
                    // 0x0013628c
                    charge(ctx, 16);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x13629Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    sw(zero, s1, 20);
                    a0 = s2;
                    jal(ctx, 0x1362ACu, gen::fn_sub_135460_00135460);
                    a0 = s2;
                    jal(ctx, 0x1362B8u, gen::fn_sub_135120_00135120);
                    sw(zero, s1, 12);
                }
            }
            // 0x00136524
            charge(ctx, 21);
            sw(zero, sp, 0x174);
            sw(zero, sp, 0x170);
            lw(v0, s1, 24);
            sd(v0, sp, 0x0);
            sd(zero, sp, 0x8);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            ld(a0, sp, 0x170);
            a1 = addiu(s1, comu::kLinks);
            lw(a2, s1, 16);
            lw(a3, s1, comu::kScroll);
            lw(t0, s1, comu::kCursor);
            lw(t1, s1, 20);
            t2 = 0;
            lw(t3, s1, 12);
            jal(ctx, 0x136560u, gen::fn_sub_138E80_00138e80);  // [H_Camp_ComuDrawCard]
            lw(v0, s1, 12);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x00136578
                charge(ctx, 4);
                lw(v0, s1, 24);
                at = slti(v0, 10);
                if (at != 0) {
                    // 0x00136588
                    charge(ctx, 2);
                    v0 = addiu(v0, 1);
                    sw(v0, s1, 24);
                }
            }
            goto L_00136590;
        case 0x136590u:  // table[1, 10]: state 1
            goto L_00136590;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00136594 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x50);
        lq(s2, sp, 0x40);
        lq(s1, sp, 0x30);
        lq(s0, sp, 0x20);
        sp = addiu(sp, 0x180);
        return;
    }
    goto L_00136590;
L_00136138_109:
    charge(ctx, 2);
    goto L_001361cc;
L_00136188_115:
    charge(ctx, 2);
    goto L_001361cc;
}

// 0x00136A10 sub_136A10 -- 2288 bytes; frame 0x190: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawLinkRow] (xy, link, selected, alpha): one social-link row: the rank (datComuGetRank; "MAX" sprites at
// 10, else the digit of font 1), the arcana icon (camp comu file 1, 2 * (0x5E3220[link] - 1) + 1), the partner's name
// (off_5D80E4[10 * link + rank] through sprintf + sub_3B2F90), the reversed / broken colouring (sub_172160 /
// sub_1717C0).
void sub_136A10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00136a10
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
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
    sd(a0, sp, 0x88);
    mov_s(f22, f12);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    v0 = 255;
    s0 = subu(v0, s1);
    if (s2 == 0) {
        // 0x00136ce4
        charge(ctx, 9);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x136CECu, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = 10;
        if (v1 == v0) {
            // 0x00136db8
            charge(ctx, 17);
            lwc1(f21, sp, 0x8C);
            v0 = 0x42AE0000;  // 87.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x41E80000;  // 29.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            a2 = 46;
            mov_s(f14, f22);
            jal(ctx, 0x136DF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x00136d08
            charge(ctx, 44);
            lwc1(f21, sp, 0x8C);
            v0 = 0x42A80000;  // 84.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            a2 = 45;
            mov_s(f14, f22);
            jal(ctx, 0x136D44u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a0 = 2;
            jal(ctx, 0x136D50u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            s4 = v0;
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x136D64u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            a2 = addiu(v0, 11);
            v0 = 0x43120000;  // 146.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x420C0000;  // 35.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            a1 = s4;
            mov_s(f14, f22);
            jal(ctx, 0x136DA8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
        // 0x00136dfc
        charge(ctx, 9);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x136E04u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = 10;
        if (v1 == v0) {
            // 0x00136e78
            charge(ctx, 17);
            v0 = 0x423C0000;  // 47.0f
            mtc1(v0, f0);
            add_s(f20, f0, f21);
            v0 = 0x42A60000;  // 83.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            a2 = 47;
            mov_s(f13, f20);
            mov_s(f14, f22);
            jal(ctx, 0x136EB4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x00136e20
            charge(ctx, 22);
            v0 = 0x423C0000;  // 47.0f
            mtc1(v0, f0);
            add_s(f20, f0, f21);
            v0 = 0x42A60000;  // 83.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            a2 = 48;
            mov_s(f13, f20);
            t0 = 79;
            t1 = 164;
            t2 = 255;
            mov_s(f14, f22);
            jal(ctx, 0x136E68u, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
        }
        // 0x00136ebc
        charge(ctx, 9);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x136EC4u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = 10;
        if (v1 == v0) {
            // 0x00136f3c
            charge(ctx, 22);
            v0 = 0x5E0000;
            v0 = addiu(v0, 12832);  // &0x5E3220
            v0 = addu(v0, s3);
            lb(v0, v0, 0);
            v0 = addiu(v0, -1);
            v0 = sll(v0, 1);
            a2 = addiu(v0, 1);
            v0 = 0x42A80000;  // 84.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f13, f20, f0);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            mov_s(f14, f22);
            jal(ctx, 0x136F8Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x00136ee0
            charge(ctx, 23);
            v0 = 0x5E0000;
            v0 = addiu(v0, 12832);  // &0x5E3220
            v0 = addu(v0, s3);
            lb(v0, v0, 0);
            v0 = addiu(v0, -1);
            a2 = sll(v0, 1);
            v0 = 0x42A80000;  // 84.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f13, f20, f0);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            mov_s(f14, f22);
            jal(ctx, 0x136F2Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
        // 0x00136f94
        charge(ctx, 48);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x136F9Cu, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        a0 = sll(v0, 2);
        v0 = sll(s3, 2);
        v0 = addu(v0, s3);
        v1 = sll(v0, 3);
        v0 = 0x5E0000;
        v0 = addiu(v0, -32540);  // &0x5D80E4
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -30340);  // "%s"
        lw(a2, v0, 0);
        jal(ctx, 0x136FD8u, gen::fn_sprintf_00523ac8);
        lwc1(f0, sp, 0x88);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a0 = addiu(v0, 173);
        cvt_w_s(f0, f21);
        mfc1(v0, f0);
        v0 = addiu(v0, 53);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f12);
        v0 = si(-256);
        a2 = s0 | v0;
        a3 = 10;
        t0 = 1;
        t1 = addiu(sp, 0x90);
        t2 = 16;
        t3 = si(-1);
        jal(ctx, 0x13704Cu, gen::fn_sub_3B2F90_003b2f90);  // text at (x, y): colour, size, font, string
    } else {
        // 0x00136a64
        charge(ctx, 9);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x136A6Cu, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v1 = dsll32(v0, 24);
        v1 = dsra32(v1, 24);
        v0 = 10;
        if (v1 == v0) {
            // 0x00136b38
            charge(ctx, 17);
            lwc1(f21, sp, 0x8C);
            v0 = 0x42AE0000;  // 87.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x41E80000;  // 29.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            a2 = 46;
            mov_s(f14, f22);
            jal(ctx, 0x136B74u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x00136a88
            charge(ctx, 44);
            lwc1(f21, sp, 0x8C);
            v0 = 0x42A80000;  // 84.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
            a2 = 44;
            mov_s(f14, f22);
            jal(ctx, 0x136AC4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            a0 = 1;
            jal(ctx, 0x136AD0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
            s4 = v0;
            a0 = dsll32(s3, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x136AE4u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            a2 = addiu(v0, 11);
            v0 = 0x43120000;  // 146.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x420C0000;  // 35.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            a1 = s4;
            mov_s(f14, f22);
            jal(ctx, 0x136B28u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
        // 0x00136b7c
        charge(ctx, 90);
        lwc1(f23, sp, 0x8C);
        v0 = 0x423C0000;  // 47.0f
        mtc1(v0, f0);
        add_s(f20, f0, f23);
        v0 = 0x42A60000;  // 83.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x88);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
        a2 = 47;
        mov_s(f13, f20);
        mov_s(f14, f22);
        jal(ctx, 0x136BBCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x5E0000;
        v0 = addiu(v0, 12832);  // &0x5E3220
        v0 = addu(v0, s3);
        lb(v0, v0, 0);
        v0 = addiu(v0, -1);
        v0 = sll(v0, 1);
        a2 = addiu(v0, 1);
        v0 = 0x42A80000;  // 84.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x88);
        add_s(f12, f1, f0);
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f13, f20, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
        mov_s(f14, f22);
        jal(ctx, 0x136C14u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x136C24u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        a0 = sll(v0, 2);
        v0 = sll(s3, 2);
        v0 = addu(v0, s3);
        v1 = sll(v0, 3);
        v0 = 0x5E0000;
        v0 = addiu(v0, -32540);  // &0x5D80E4
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        a0 = addiu(sp, 0x90);
        a1 = addiu(gp, -30340);  // "%s"
        lw(a2, v0, 0);
        jal(ctx, 0x136C60u, gen::fn_sprintf_00523ac8);
        lwc1(f0, sp, 0x88);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a0 = addiu(v0, 173);
        cvt_w_s(f0, f23);
        mfc1(v0, f0);
        v0 = addiu(v0, 53);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f12);
        v0 = si(-256);
        a2 = s0 | v0;
        a3 = 6;
        t0 = 1;
        t1 = addiu(sp, 0x90);
        t2 = 16;
        t3 = si(-1);
        jal(ctx, 0x136CD4u, gen::fn_sub_3B2F90_003b2f90);  // text at (x, y): colour, size, font, string
    }
    // 0x00137054
    charge(ctx, 5);
    a0 = s3;
    jal(ctx, 0x137058u, gen::fn_sub_172160_00172160);  // (link)
    if (v0 == 0) {
        // 0x00137100
        charge(ctx, 5);
        a0 = s3;
        jal(ctx, 0x137104u, gen::fn_sub_1717C0_001717c0);  // (link)
        if (v0 == 0) {
            // 0x001371ac
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x001371c4
                charge(ctx, 11);
                s0 = 17;
                s2 = 19;
                a0 = dsll32(s3, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1371D4u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v0 = 10;
                if (v1 == v0) {
                    // 0x001371f0
                    charge(ctx, 1);
                    s2 = 20;
                }
            } else {
                // 0x001371b4
                charge(ctx, 4);
                s0 = 18;
                s2 = 20;
            }
            // 0x001371f4
            charge(ctx, 28);
            lwc1(f20, sp, 0x8C);
            v0 = 0x43250000;  // 165.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
            a2 = s0;
            mov_s(f14, f22);
            jal(ctx, 0x137230u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            s0 = 0;
            v0 = 0x42140000;  // 37.0f
            mtc1(v0, f0);
            add_s(f21, f0, f20);
            v0 = 0x432E0000;  // 174.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f20, f1, f0);
            for (;;) {
                // 0x001372a4
                charge(ctx, 9);
                a0 = dsll32(s3, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1372ACu, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
                v1 = dsll32(v0, 24);
                v1 = dsra32(v1, 24);
                v1 = slt(s0, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00137264
                charge(ctx, 16);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f12, f20, f0);
                a3 = s1 & 0xFF;
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                a2 = s2;
                mov_s(f13, f21);
                mov_s(f14, f22);
                jal(ctx, 0x137298u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                s0 = addiu(s0, 1);
            }
        } else {
            // 0x00137114
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x00137164
                charge(ctx, 18);
                v0 = 0x43250000;  // 165.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x88);
                add_s(f12, f1, f0);
                v0 = 0x42080000;  // 34.0f
                mtc1(v0, f0);
                add_s(f13, f0, f21);
                a3 = s1 & 0xFF;
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                a2 = 5;
                mov_s(f14, f22);
                jal(ctx, 0x13719Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0013711c
                charge(ctx, 18);
                v0 = 0x43250000;  // 165.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x88);
                add_s(f12, f1, f0);
                v0 = 0x42080000;  // 34.0f
                mtc1(v0, f0);
                add_s(f13, f0, f21);
                a3 = s1 & 0xFF;
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                a2 = 15;
                mov_s(f14, f22);
                jal(ctx, 0x137154u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
        }
    } else {
        // 0x00137068
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x001370b8
            charge(ctx, 18);
            v0 = 0x43250000;  // 165.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
            a2 = 6;
            mov_s(f14, f22);
            jal(ctx, 0x1370F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x00137070
            charge(ctx, 18);
            v0 = 0x43250000;  // 165.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x42080000;  // 34.0f
            mtc1(v0, f0);
            add_s(f13, f0, f21);
            a3 = s1 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
            a2 = 16;
            mov_s(f14, f22);
            jal(ctx, 0x1370A8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
    }
    // 0x001372c8 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0x190);
}

// 0x00137580 sub_137580 -- 2912 bytes; frame 0x130: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawListIn] (xy, links, cursor, scroll, z, frame): the link list's reveal (from frame 23 the five row
// frames, each row easing in 3 frames after the previous), the ribbon (sub_1368A0), the rows (sub_136A10), the cards
// (sub_137300) and the cursor.
void sub_137580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00137580
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
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
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xE0);
    mov_s(f24, f12);
    fp = a1;
    s1 = a2;
    s6 = a3;
    sw(t0, sp, 0xDC);
    s0 = t1;
    lwc1(f22, sp, 0xE0);
    lwc1(f23, sp, 0xE4);
    sw(zero, sp, 0x12C);
    sw(zero, sp, 0x128);
    ld(v0, sp, 0x128);
    sd(v0, sp, 0x120);
    v0 = 0x425C0000;  // 55.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x120);
    add_s(f12, f1, f0);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x124);
    add_s(f13, f1, f0);
    v0 = 0x830000;
    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
    a2 = 0;
    a3 = 0;
    mov_s(f14, f24);
    jal(ctx, 0x137628u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    at = slti(s0, 23);
    if (at == 0) {
        // 0x00137894
        charge(ctx, 7);
        s2 = 0;
        v0 = 0x42440000;  // 49.0f
        mtc1(v0, f21);
        v0 = 0x42920000;  // 73.0f
        mtc1(v0, f20);
        for (;;) {
            // 0x0013795c
            charge(ctx, 3);
            v0 = slti(s2, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001378b0
            charge(ctx, 43);
            swc1(f22, sp, 0x128);
            v0 = sll(s2, 6);
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f23, f0);
            v0 = 0x42440000;  // 49.0f
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x12C);
            ld(v0, sp, 0x128);
            sd(v0, sp, 0x108);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
            a2 = 13;
            jal(ctx, 0x1378F4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s3 = v0;
            swc1(f24, v0, 44);
            lwc1(f0, sp, 0x108);
            swc1(f0, v0, 16);
            v1 = 0x42920000;  // 73.0f
            mtc1(v1, f1);
            lwc1(f0, sp, 0x10C);
            add_s(f1, f1, f0);
            v1 = 0x42440000;  // 49.0f
            mtc1(v1, f0);
            sub_s(f0, f1, f0);
            swc1(f0, v0, 20);
            v1 = 4096;
            sh(v1, v0, 42);
            sb(zero, v0, 24);
            a0 = s3;
            a1 = 1;
            jal(ctx, 0x137944u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s3;
            jal(ctx, 0x137950u, gen::fn_sub_115980_00115980);  // draw and release the handle
            s2 = addiu(s2, 1);
        }
    } else {
        // 0x0013763c
        charge(ctx, 7);
        s2 = 0;
        v0 = 0x42440000;  // 49.0f
        mtc1(v0, f21);
        v0 = 0x42920000;  // 73.0f
        mtc1(v0, f20);
        for (;;) {
            // 0x00137880
            charge(ctx, 3);
            v0 = slti(s2, 5);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00137658
            charge(ctx, 5);
            v0 = sll(s2, 1);
            v0 = addu(v0, s2);
            a0 = subu(s0, v0);
            if (i64(a0) >= 0) {
                // 0x0013766c
                charge(ctx, 3);
                at = slti(a0, 8);
                if (at == 0) {
                    // 0x001377d4
                    charge(ctx, 42);
                    swc1(f22, sp, 0x128);
                    v0 = sll(s2, 6);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f23, f0);
                    v0 = 0x42440000;  // 49.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x12C);
                    ld(v0, sp, 0x128);
                    sd(v0, sp, 0x110);
                    a0 = 0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                    a2 = 13;
                    jal(ctx, 0x137818u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                    s4 = v0;
                    swc1(f24, v0, 44);
                    lwc1(f0, sp, 0x110);
                    swc1(f0, v0, 16);
                    v1 = 0x42920000;  // 73.0f
                    mtc1(v1, f1);
                    lwc1(f0, sp, 0x114);
                    add_s(f1, f1, f0);
                    v1 = 0x42440000;  // 49.0f
                    mtc1(v1, f0);
                    sub_s(f0, f1, f0);
                    swc1(f0, v0, 20);
                    v1 = 4096;
                    sh(v1, v0, 42);
                    sb(zero, v0, 24);
                    a0 = s4;
                    a1 = 1;
                    jal(ctx, 0x137868u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                    a0 = s4;
                    jal(ctx, 0x137874u, gen::fn_sub_115980_00115980);  // draw and release the handle
                } else {
                    // 0x00137678
                    charge(ctx, 12);
                    sw(zero, sp, 0x128);
                    v0 = 8;
                    v1 = subu(v0, a0);
                    v0 = sll(v1, 2);
                    v1 = addu(v0, v1);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    v1 = sll(v0, 3);
                    v0 = dsll32(v0, 3);
                    v0 = dsra32(v0, 3);
                    if (i64(v1) < 0) {
                        // 0x001376a8
                        charge(ctx, 2);
                        v0 = addiu(v1, 7);
                        v0 = sra(v0, 3);
                    }
                    // 0x001376b0
                    charge(ctx, 18);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = sll(s2, 6);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f23, f0);
                    add_s(f1, f0, f1);
                    v0 = 0x42440000;  // 49.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x12C);
                    v0 = sll(a0, 12);
                    s4 = sra(v0, 3);
                    if (i64(v0) < 0) {
                        // 0x001376f8
                        charge(ctx, 2);
                        v0 = addiu(v0, 7);
                        s4 = sra(v0, 3);
                    }
                    // 0x00137700
                    charge(ctx, 4);
                    ld(v0, sp, 0x128);
                    sd(v0, sp, 0x118);
                    if (s4 == 0) {
                        // 0x00137788
                        charge(ctx, 19);
                        v0 = 0x42920000;  // 73.0f
                        mtc1(v0, f1);
                        lwc1(f0, sp, 0x11C);
                        add_s(f1, f1, f0);
                        v0 = 0x42440000;  // 49.0f
                        mtc1(v0, f0);
                        sub_s(f13, f1, f0);
                        a0 = s3;
                        v0 = 0x830000;
                        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                        a2 = 13;
                        lwc1(f12, sp, 0x118);
                        a3 = 0;
                        mov_s(f14, f24);
                        jal(ctx, 0x1377C4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    } else {
                        // 0x00137710
                        charge(ctx, 30);
                        a0 = 0;
                        v0 = 0x830000;
                        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                        a2 = 13;
                        jal(ctx, 0x137720u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                        s3 = v0;
                        swc1(f24, v0, 44);
                        lwc1(f0, sp, 0x118);
                        swc1(f0, v0, 16);
                        v1 = 0x42920000;  // 73.0f
                        mtc1(v1, f1);
                        lwc1(f0, sp, 0x11C);
                        add_s(f1, f1, f0);
                        v1 = 0x42440000;  // 49.0f
                        mtc1(v1, f0);
                        sub_s(f0, f1, f0);
                        swc1(f0, v0, 20);
                        sh(s4, v0, 42);
                        sb(zero, v0, 24);
                        a0 = s3;
                        a1 = 1;
                        jal(ctx, 0x13776Cu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                        a0 = s3;
                        jal(ctx, 0x137778u, gen::fn_sub_115980_00115980);  // draw and release the handle
                    }
                }
            }
            // 0x0013787c
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x0013788c
        charge(ctx, 2);
    }
    // 0x00137968
    charge(ctx, 3);
    at = slti(s0, 10);
    if (at == 0) {
        // 0x00137a50
        charge(ctx, 7);
        sw(zero, sp, 0x12C);
        sw(zero, sp, 0x128);
        ld(a0, sp, 0x128);
        mov_s(f12, f24);
        a1 = 0;
        jal(ctx, 0x137A64u, gen::fn_sub_1368A0_001368a0);  // the ribbon
    } else {
        // 0x00137974
        charge(ctx, 55);
        a0 = 10;
        v1 = subu(a0, s0);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(s3);
        v0 = subu(0, v1);
        v0 = sll(v0, 2);
        v0 = subu(v0, v1);
        v0 = sll(v0, 7);
        div1(v0, a0);
        mflo1(v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x128);
        sw(zero, sp, 0x12C);
        ld(v0, sp, 0x128);
        sd(v0, sp, 0x100);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(0));  // 0x833B40: social-link sprite file 0
        a2 = 1;
        jal(ctx, 0x1379D0u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
        s2 = v0;
        swc1(f24, v0, 44);
        v1 = 0x439F0000;  // 318.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x100);
        add_s(f1, f1, f0);
        v1 = 0x42C80000;  // 100.0f
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, v0, 16);
        v1 = 0x41A00000;  // 20.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0x104);
        add_s(f0, f1, f0);
        swc1(f0, v0, 20);
        sb(s3, v0, 24);
        v1 = 8000;
        sh(v1, v0, 40);
        sh(v1, v0, 42);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x137A30u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
        a0 = s2;
        jal(ctx, 0x137A3Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
        sw(zero, gp, g::kComuRibbonY);  // 0x7CDF9C
    }
    // 0x00137a6c
    charge(ctx, 3);
    sw(s1, sp, 0xC0);
    if (s1 != 0) {
        // 0x00137a78
        charge(ctx, 3);
        v0 = 4;
        if (s1 == v0) {
            // 0x00137acc
            charge(ctx, 3);
            s5 = 0;
        } else {
            // 0x00137a84
            charge(ctx, 3);
            v0 = 3;
            if (s1 == v0) {
                // 0x00137ac0
                charge(ctx, 3);
                s5 = 1;
            } else {
                // 0x00137a90
                charge(ctx, 3);
                s5 = 2;
                if (s1 == s5) {
                    // 0x00137ab8
                    charge(ctx, 2);
                } else {
                    // 0x00137a9c
                    charge(ctx, 3);
                    v0 = 1;
                    if (s1 == v0) {
                        // 0x00137ab0
                        charge(ctx, 2);
                    } else {
                        // 0x00137aa8
                        charge(ctx, 2);
                        // 0x00137ad8
                        charge(ctx, 3);
                        s5 = 0;
                        v0 = 5;
                        sw(v0, sp, 0xC0);
                    }
                }
            }
        }
        // 0x00137ae4
        charge(ctx, 5);
        s4 = 0;
        v0 = sll(s6, 2);
        s3 = addu(fp, v0);
        for (;;) {
            // 0x00137d44
            charge(ctx, 4);
            lw(v0, sp, 0xC0);
            v0 = slt(s4, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00137af8
            charge(ctx, 7);
            a0 = addu(s4, s5);
            v0 = sll(a0, 1);
            v0 = addu(v0, a0);
            v0 = addiu(v0, 8);
            v1 = subu(s0, v0);
            if (i64(v1) > 0) {
                // 0x00137b14
                charge(ctx, 3);
                at = slti(v1, 8);
                if (at == 0) {
                    goto L_00137c40;
                }
                // 0x00137b20
                charge(ctx, 7);
                v0 = 8;
                v1 = subu(v0, v1);
                v0 = sll(v1, 8);
                v0 = subu(v0, v1);
                s2 = sra(v0, 3);
                if (i64(v0) < 0) {
                    // 0x00137b3c
                    charge(ctx, 2);
                    v0 = addiu(v0, 7);
                    s2 = sra(v0, 3);
                }
                // 0x00137b44
                charge(ctx, 11);
                swc1(f22, sp, 0x128);
                v0 = sll(a0, 6);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f23, f0);
                add_s(f0, f21, f0);
                swc1(f0, sp, 0x12C);
                lw(v0, sp, 0xDC);
                if (v0 != s4) {
                    // 0x00137bf4
                    charge(ctx, 19);
                    v0 = sll(s4, 2);
                    fp = addu(s3, v0);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, fp, 0x0);
                    a2 = 0;
                    a3 = s2;
                    jal(ctx, 0x137C10u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, fp, 0x0);
                    a2 = 0;
                    a3 = 0;
                    t0 = s2;
                    jal(ctx, 0x137C30u, gen::fn_sub_137300_00137300);  // a card
                } else {
                    // 0x00137b70
                    charge(ctx, 33);
                    ld(v0, sp, 0x128);
                    sd(v0, sp, 0xF8);
                    lwc1(f0, sp, 0xFC);
                    add_s(f0, f20, f0);
                    sub_s(f13, f0, f21);
                    a3 = s2 & 0xFF;
                    a0 = s7;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                    a2 = 14;
                    lwc1(f12, sp, 0xF8);
                    mov_s(f14, f24);
                    jal(ctx, 0x137BA0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = sll(s4, 2);
                    fp = addu(s3, v0);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, fp, 0x0);
                    a2 = 1;
                    a3 = s2;
                    jal(ctx, 0x137BC4u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, fp, 0x0);
                    a2 = 1;
                    a3 = 0;
                    t0 = s2;
                    jal(ctx, 0x137BE4u, gen::fn_sub_137300_00137300);  // a card
                }
                goto L_00137d40;
            }
        L_00137c40:
            charge(ctx, 3);
            v0 = slti(v1, 8);
            if (v0 == 0) {
                // 0x00137c4c
                charge(ctx, 11);
                swc1(f22, sp, 0x128);
                v0 = sll(a0, 6);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f23, f0);
                add_s(f0, f21, f0);
                swc1(f0, sp, 0x12C);
                lw(v0, sp, 0xDC);
                if (v0 != s4) {
                    // 0x00137cfc
                    charge(ctx, 17);
                    v0 = sll(s4, 2);
                    s2 = addu(s3, v0);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, s2, 0);
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x137D18u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, s2, 0);
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x137D38u, gen::fn_sub_137300_00137300);  // a card
                } else {
                    // 0x00137c78
                    charge(ctx, 33);
                    ld(v0, sp, 0x128);
                    sd(v0, sp, 0xF0);
                    lwc1(f0, sp, 0xF4);
                    add_s(f0, f20, f0);
                    sub_s(f13, f0, f21);
                    a0 = s7;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                    a2 = 14;
                    lwc1(f12, sp, 0xF0);
                    a3 = 0;
                    mov_s(f14, f24);
                    jal(ctx, 0x137CA8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = sll(s4, 2);
                    s2 = addu(s3, v0);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, s2, 0);
                    a2 = 1;
                    a3 = 0;
                    jal(ctx, 0x137CCCu, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0x128);
                    mov_s(f12, f24);
                    lw(a1, s2, 0);
                    a2 = 1;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x137CECu, gen::fn_sub_137300_00137300);  // a card
                }
            }
        L_00137d40:
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x00137d54
        charge(ctx, 3);
        at = slti(s0, 10);
        if (at == 0) {
            // 0x00137d80
            charge(ctx, 1);
            s2 = 0;
        } else {
            // 0x00137d60
            charge(ctx, 8);
            a0 = 10;
            v1 = subu(a0, s0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(s2);
        }
        // 0x00137d84
        charge(ctx, 39);
        v0 = 0x44160000;  // 600.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xE0);
        add_s(f20, f1, f0);
        v0 = 0x439A0000;  // 308.0f
        mtc1(v0, f0);
        add_s(f13, f0, f23);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 11;
        mov_s(f12, f20);
        jal(ctx, 0x137DCCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43C90000;  // 402.0f
        mtc1(v0, f0);
        add_s(f13, f0, f23);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 12;
        mov_s(f12, f20);
        jal(ctx, 0x137E0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v1 = addiu(s1, -5);
        if (i64(v1) <= 0) {
            // 0x00137e40
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x00137e20
            charge(ctx, 8);
            v0 = sll(s6, 4);
            v0 = subu(v0, s6);
            v0 = sll(v0, 2);
            v0 = subu(v0, s6);
            div(v0, v1);
            mflo(v1);
        }
        // 0x00137e44
        charge(ctx, 89);
        v0 = 311;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f23);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f23, f1, f0);
        v0 = 597;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0xE0);
        add_s(f20, f1, f0);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 10;
        mov_s(f12, f20);
        mov_s(f13, f23);
        jal(ctx, 0x137EACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x40E00000;  // 7.0f
        mtc1(v0, f0);
        add_s(f21, f0, f23);
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        add_s(f22, f0, f20);
        a3 = s2 & 0xFF;
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 8;
        mov_s(f12, f22);
        mov_s(f13, f21);
        jal(ctx, 0x137EF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x41A00000;  // 20.0f
        mtc1(v0, f0);
        add_s(f20, f0, f23);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 9;
        mov_s(f12, f22);
        mov_s(f13, f20);
        jal(ctx, 0x137F38u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 8;
        mov_s(f12, f22);
        mov_s(f13, f21);
        jal(ctx, 0x137F6Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f24, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 9;
        mov_s(f12, f22);
        mov_s(f13, f20);
        jal(ctx, 0x137FA0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00137fa8
    charge(ctx, 3);
    at = slti(s0, 10);
    if (at == 0) {
        // 0x00138000
        charge(ctx, 3);
        s0 = 0;
        sw(zero, sp, 0x12C);
        sw(zero, sp, 0x128);
    } else {
        // 0x00137fb4
        charge(ctx, 19);
        a0 = 10;
        v1 = subu(a0, s0);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(s0);
        v0 = subu(0, v1);
        v0 = sll(v0, 2);
        v0 = subu(v0, v1);
        v0 = sll(v0, 7);
        div1(v0, a0);
        mflo1(v0);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x128);
        sw(zero, sp, 0x12C);
    }
    // 0x0013800c
    charge(ctx, 53);
    ld(v0, sp, 0x128);
    sd(v0, sp, 0xE8);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(0));  // 0x833B40: social-link sprite file 0
    a2 = 0;
    jal(ctx, 0x138024u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
    s1 = v0;
    swc1(f24, v0, 44);
    v1 = 389;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xE8);
    add_s(f1, f1, f0);
    v1 = 0x42C80000;  // 100.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 16);
    lwc1(f1, sp, 0xEC);
    v1 = 0x42040000;  // 33.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 20);
    sb(s0, v0, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x138084u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
    a0 = s1;
    jal(ctx, 0x138090u, gen::fn_sub_115980_00115980);  // draw and release the handle
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
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x001380E0 sub_1380E0 -- 1740 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawList] (xy, links, cursor, scroll, z, alpha): the link list drawn at once: five row frames, the
// ribbon, rows, cards, cursor.
void sub_1380E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001380e0
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
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
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f22, f12);
    s7 = a1;
    s4 = a2;
    s3 = a3;
    sw(t0, sp, 0xB4);
    s2 = t1;
    lwc1(f20, sp, 0xBC);
    lwc1(f21, sp, 0xB8);
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(v0, sp, 0xE8);
    sd(v0, sp, 0xE0);
    v0 = 0x425C0000;  // 55.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xE0);
    add_s(f12, f1, f0);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xE4);
    add_s(f13, f1, f0);
    v0 = 0x830000;
    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
    a2 = 0;
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138180u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s0 = 0;
    for (;;) {
        // 0x00138240
        charge(ctx, 3);
        v0 = slti(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00138194
        charge(ctx, 43);
        swc1(f21, sp, 0xE8);
        v0 = sll(s0, 6);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f20, f0);
        v0 = 0x42440000;  // 49.0f
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0xEC);
        ld(v0, sp, 0xE8);
        sd(v0, sp, 0xD8);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 13;
        jal(ctx, 0x1381D8u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
        s1 = v0;
        swc1(f22, v0, 44);
        lwc1(f0, sp, 0xD8);
        swc1(f0, v0, 16);
        v1 = 0x42920000;  // 73.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0xDC);
        add_s(f1, f1, f0);
        v1 = 0x42440000;  // 49.0f
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, v0, 20);
        v1 = 4096;
        sh(v1, v0, 42);
        sb(s2, v0, 24);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x138228u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
        a0 = s1;
        jal(ctx, 0x138234u, gen::fn_sub_115980_00115980);  // draw and release the handle
        s0 = addiu(s0, 1);
    }
    // 0x0013824c
    charge(ctx, 11);
    s2 = 0;
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(a0, sp, 0xE8);
    mov_s(f12, f22);
    a1 = 0;
    jal(ctx, 0x138264u, gen::fn_sub_1368A0_001368a0);  // the ribbon
    s1 = s4;
    if (s4 != 0) {
        // 0x00138278
        charge(ctx, 3);
        v0 = 4;
        if (s4 == v0) {
            // 0x001382cc
            charge(ctx, 3);
            s0 = 0;
        } else {
            // 0x00138284
            charge(ctx, 3);
            v0 = 3;
            if (s4 == v0) {
                // 0x001382c0
                charge(ctx, 3);
                s0 = 1;
            } else {
                // 0x00138290
                charge(ctx, 3);
                s0 = 2;
                if (s4 == s0) {
                    // 0x001382b8
                    charge(ctx, 2);
                } else {
                    // 0x0013829c
                    charge(ctx, 3);
                    v0 = 1;
                    if (s4 == v0) {
                        // 0x001382b0
                        charge(ctx, 2);
                    } else {
                        // 0x001382a8
                        charge(ctx, 2);
                        // 0x001382d8
                        charge(ctx, 2);
                        s0 = 0;
                        s1 = 5;
                    }
                }
            }
        }
        // 0x001382e0
        charge(ctx, 3);
        s5 = 0;
        if (i64(s1) > 0) {
            // 0x001382ec
            charge(ctx, 5);
            s2 = 0;
            v0 = sll(s3, 2);
            fp = addu(s7, v0);
            for (;;) {
                // 0x00138410
                charge(ctx, 3);
                v0 = slt(s5, s1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00138300
                charge(ctx, 15);
                swc1(f21, sp, 0xE8);
                v0 = addu(s5, s0);
                v0 = sll(v0, 6);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f20, f0);
                v0 = 0x42440000;  // 49.0f
                mtc1(v0, f2);
                add_s(f0, f2, f0);
                swc1(f0, sp, 0xEC);
                lw(v0, sp, 0xB4);
                if (v0 != s5) {
                    // 0x001383c8
                    charge(ctx, 17);
                    v0 = sll(s5, 2);
                    s7 = addu(fp, v0);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x1383E4u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x138404u, gen::fn_sub_137300_00137300);  // a card
                } else {
                    // 0x0013833c
                    charge(ctx, 35);
                    ld(v0, sp, 0xE8);
                    sd(v0, sp, 0xD0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xD4);
                    add_s(f0, f1, f0);
                    sub_s(f13, f0, f2);
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                    a2 = 14;
                    lwc1(f12, sp, 0xD0);
                    a3 = 0;
                    mov_s(f14, f22);
                    jal(ctx, 0x138374u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = sll(s5, 2);
                    s7 = addu(fp, v0);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 1;
                    a3 = 0;
                    jal(ctx, 0x138398u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 1;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x1383B8u, gen::fn_sub_137300_00137300);  // a card
                }
                // 0x0013840c
                charge(ctx, 1);
                s5 = addiu(s5, 1);
            }
        }
        // 0x0013841c
        charge(ctx, 39);
        v0 = 0x44160000;  // 600.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xB8);
        add_s(f21, f1, f0);
        v0 = 0x439A0000;  // 308.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 11;
        mov_s(f12, f21);
        jal(ctx, 0x138464u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43C90000;  // 402.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 12;
        mov_s(f12, f21);
        jal(ctx, 0x1384A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v1 = addiu(s4, -5);
        if (i64(v1) <= 0) {
            // 0x001384d8
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x001384b8
            charge(ctx, 8);
            v0 = sll(s3, 4);
            v0 = subu(v0, s3);
            v0 = sll(v0, 2);
            v0 = subu(v0, s3);
            div(v0, v1);
            mflo(v1);
        }
        // 0x001384dc
        charge(ctx, 61);
        v0 = 311;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f20);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f21, f1, f0);
        v0 = 597;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0xB8);
        add_s(f20, f1, f0);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 10;
        mov_s(f12, f20);
        mov_s(f13, f21);
        jal(ctx, 0x138544u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f1);
        add_s(f20, f1, f20);
        v0 = 0x40E00000;  // 7.0f
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s2 & 0xFF;
        sub_s(f14, f22, f1);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 8;
        mov_s(f12, f20);
        jal(ctx, 0x138588u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x41A00000;  // 20.0f
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 9;
        mov_s(f12, f20);
        jal(ctx, 0x1385C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x001385d0
    charge(ctx, 119);
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(v0, sp, 0xE8);
    sd(v0, sp, 0xC8);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(0));  // 0x833B40: social-link sprite file 0
    a2 = 0;
    jal(ctx, 0x1385F0u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
    s0 = v0;
    swc1(f22, v0, 44);
    v1 = 389;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xC8);
    add_s(f1, f1, f0);
    v1 = 0x42C80000;  // 100.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 16);
    lwc1(f1, sp, 0xCC);
    v1 = 0x42040000;  // 33.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 20);
    sb(zero, v0, 24);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x138650u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
    a0 = s0;
    jal(ctx, 0x13865Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(v0, sp, 0xE8);
    sd(v0, sp, 0xC0);
    lwc1(f1, sp, 0xC4);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f20, f0, f1);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
    a2 = 0;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x1386B8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42500000;  // 52.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
    a2 = 6;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x1386ECu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 465;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
    a2 = 1;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138728u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
    a2 = 3;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138764u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
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
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x001387B0 sub_1387B0 -- 1736 bytes; frame 0xF0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawListOut] (xy, links, cursor, scroll, z, alpha): the same list for the close fade (identical layout to
// sub_1380E0).
void sub_1387B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001387b0
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
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
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f22, f12);
    s7 = a1;
    s4 = a2;
    s3 = a3;
    sw(t0, sp, 0xB4);
    s2 = t1;
    lwc1(f20, sp, 0xBC);
    lwc1(f21, sp, 0xB8);
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(v0, sp, 0xE8);
    sd(v0, sp, 0xE0);
    v0 = 0x425C0000;  // 55.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xE0);
    add_s(f12, f1, f0);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xE4);
    add_s(f13, f1, f0);
    v0 = 0x830000;
    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
    a2 = 0;
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138850u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    s0 = 0;
    for (;;) {
        // 0x00138910
        charge(ctx, 3);
        v0 = slti(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00138864
        charge(ctx, 43);
        swc1(f21, sp, 0xE8);
        v0 = sll(s0, 6);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f20, f0);
        v0 = 0x42440000;  // 49.0f
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        swc1(f0, sp, 0xEC);
        ld(v0, sp, 0xE8);
        sd(v0, sp, 0xD8);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 13;
        jal(ctx, 0x1388A8u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
        s1 = v0;
        swc1(f22, v0, 44);
        lwc1(f0, sp, 0xD8);
        swc1(f0, v0, 16);
        v1 = 0x42920000;  // 73.0f
        mtc1(v1, f1);
        lwc1(f0, sp, 0xDC);
        add_s(f1, f1, f0);
        v1 = 0x42440000;  // 49.0f
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, v0, 20);
        v1 = 4096;
        sh(v1, v0, 42);
        sb(s2, v0, 24);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x1388F8u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
        a0 = s1;
        jal(ctx, 0x138904u, gen::fn_sub_115980_00115980);  // draw and release the handle
        s0 = addiu(s0, 1);
    }
    // 0x0013891c
    charge(ctx, 10);
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(a0, sp, 0xE8);
    mov_s(f12, f22);
    a1 = 0;
    jal(ctx, 0x138930u, gen::fn_sub_1368A0_001368a0);  // the ribbon
    s1 = s4;
    if (s4 != 0) {
        // 0x00138944
        charge(ctx, 3);
        v0 = 4;
        if (s4 == v0) {
            // 0x00138998
            charge(ctx, 3);
            s0 = 0;
        } else {
            // 0x00138950
            charge(ctx, 3);
            v0 = 3;
            if (s4 == v0) {
                // 0x0013898c
                charge(ctx, 3);
                s0 = 1;
            } else {
                // 0x0013895c
                charge(ctx, 3);
                s0 = 2;
                if (s4 == s0) {
                    // 0x00138984
                    charge(ctx, 2);
                } else {
                    // 0x00138968
                    charge(ctx, 3);
                    v0 = 1;
                    if (s4 == v0) {
                        // 0x0013897c
                        charge(ctx, 2);
                    } else {
                        // 0x00138974
                        charge(ctx, 2);
                        // 0x001389a4
                        charge(ctx, 2);
                        s0 = 0;
                        s1 = 5;
                    }
                }
            }
        }
        // 0x001389ac
        charge(ctx, 3);
        s5 = 0;
        if (i64(s1) > 0) {
            // 0x001389b8
            charge(ctx, 5);
            s2 = 0;
            v0 = sll(s3, 2);
            fp = addu(s7, v0);
            for (;;) {
                // 0x00138adc
                charge(ctx, 3);
                v0 = slt(s5, s1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001389cc
                charge(ctx, 15);
                swc1(f21, sp, 0xE8);
                v0 = addu(s5, s0);
                v0 = sll(v0, 6);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f20, f0);
                v0 = 0x42440000;  // 49.0f
                mtc1(v0, f2);
                add_s(f0, f2, f0);
                swc1(f0, sp, 0xEC);
                lw(v0, sp, 0xB4);
                if (v0 != s5) {
                    // 0x00138a94
                    charge(ctx, 17);
                    v0 = sll(s5, 2);
                    s7 = addu(fp, v0);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 0;
                    a3 = 0;
                    jal(ctx, 0x138AB0u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x138AD0u, gen::fn_sub_137300_00137300);  // a card
                } else {
                    // 0x00138a08
                    charge(ctx, 35);
                    ld(v0, sp, 0xE8);
                    sd(v0, sp, 0xD0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0xD4);
                    add_s(f0, f1, f0);
                    sub_s(f13, f0, f2);
                    a0 = s6;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
                    a2 = 14;
                    lwc1(f12, sp, 0xD0);
                    a3 = 0;
                    mov_s(f14, f22);
                    jal(ctx, 0x138A40u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = sll(s5, 2);
                    s7 = addu(fp, v0);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 1;
                    a3 = 0;
                    jal(ctx, 0x138A64u, gen::fn_sub_136A10_00136a10);
                    ld(a0, sp, 0xE8);
                    mov_s(f12, f22);
                    lw(a1, s7, 0);
                    a2 = 1;
                    a3 = 0;
                    t0 = 0;
                    jal(ctx, 0x138A84u, gen::fn_sub_137300_00137300);  // a card
                }
                // 0x00138ad8
                charge(ctx, 1);
                s5 = addiu(s5, 1);
            }
        }
        // 0x00138ae8
        charge(ctx, 39);
        v0 = 0x44160000;  // 600.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xB8);
        add_s(f21, f1, f0);
        v0 = 0x439A0000;  // 308.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 11;
        mov_s(f12, f21);
        jal(ctx, 0x138B30u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43C90000;  // 402.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 12;
        mov_s(f12, f21);
        jal(ctx, 0x138B70u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v1 = addiu(s4, -5);
        if (i64(v1) <= 0) {
            // 0x00138ba4
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x00138b84
            charge(ctx, 8);
            v0 = sll(s3, 4);
            v0 = subu(v0, s3);
            v0 = sll(v0, 2);
            v0 = subu(v0, s3);
            div(v0, v1);
            mflo(v1);
        }
        // 0x00138ba8
        charge(ctx, 61);
        v0 = 311;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f20);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f21, f1, f0);
        v0 = 597;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0xB8);
        add_s(f20, f1, f0);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 10;
        mov_s(f12, f20);
        mov_s(f13, f21);
        jal(ctx, 0x138C10u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f1);
        add_s(f20, f1, f20);
        v0 = 0x40E00000;  // 7.0f
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s2 & 0xFF;
        sub_s(f14, f22, f1);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 8;
        mov_s(f12, f20);
        jal(ctx, 0x138C54u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x41A00000;  // 20.0f
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s2 & 0xFF;
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f14, f22, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(2));  // 0x833B48: social-link sprite file 2
        a2 = 9;
        mov_s(f12, f20);
        jal(ctx, 0x138C94u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x00138c9c
    charge(ctx, 119);
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(v0, sp, 0xE8);
    sd(v0, sp, 0xC8);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(0));  // 0x833B40: social-link sprite file 0
    a2 = 0;
    jal(ctx, 0x138CBCu, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
    s0 = v0;
    swc1(f22, v0, 44);
    v1 = 389;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xC8);
    add_s(f1, f1, f0);
    v1 = 0x42C80000;  // 100.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 16);
    lwc1(f1, sp, 0xCC);
    v1 = 0x42040000;  // 33.0f
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 20);
    sb(zero, v0, 24);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x138D1Cu, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
    a0 = s0;
    jal(ctx, 0x138D28u, gen::fn_sub_115980_00115980);  // draw and release the handle
    sw(zero, sp, 0xEC);
    sw(zero, sp, 0xE8);
    ld(v0, sp, 0xE8);
    sd(v0, sp, 0xC0);
    lwc1(f1, sp, 0xC4);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f20, f0, f1);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
    a2 = 0;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138D84u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42500000;  // 52.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
    a2 = 6;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138DB8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 465;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
    a2 = 1;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138DF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0xC0);
    add_s(f12, f1, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
    a2 = 3;
    mov_s(f13, f20);
    a3 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138E30u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
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
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x00139660 sub_139660 -- 1888 bytes; frame 0x1D0: ra sp+0xB0, fp sp+0xA0 (sq), s7 sp+0x90 (sq), s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawArcanaPage] (xy, page, row, alpha): the arcana page of the card view: page 29 lists the shown arcana
// (0x833A60, names sub_1775A0, the selected row highlighted), other pages the six text lines of 0x5DBB00 for that page.
void sub_139660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00139660
    enter(ctx, 24);  // entry check point + this block's cycles
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
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xC8);
    mov_s(f20, f12);
    s7 = a2;
    s3 = a3;
    v1 = 255;
    v1 = subu(v1, s3);
    if (a1 != 0) {
        // 0x001398f4
        charge(ctx, 3);
        a0 = 29;
        if (a1 != a0) {
            // 0x00139b34
            charge(ctx, 36);
            s0 = 0;
            a0 = sll(a1, 1);
            a0 = addu(a0, a1);
            a1 = sll(a0, 1);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17664);  // &0x5DBB00
            fp = addu(a0, a1);
            lwc1(f2, sp, 0xCC);
            a0 = 0x433D0000;  // 189.0f
            mtc1(a0, f0);
            add_s(f24, f0, f2);
            a0 = 0x43830000;  // 262.0f
            mtc1(a0, f0);
            lwc1(f1, sp, 0xC8);
            add_s(f23, f0, f1);
            a0 = 0x43440000;  // 196.0f
            mtc1(a0, f0);
            add_s(f22, f0, f2);
            a0 = 0x420C0000;  // 35.0f
            mtc1(a0, f0);
            add_s(f21, f0, f1);
            a0 = si(-256);
            s2 = v1 | a0;
            cvt_w_s(f0, f2);
            mfc1(v1, f0);
            s6 = addiu(v1, 194);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            s1 = addiu(v1, 56);
            for (;;) {
                // 0x00139d6c
                charge(ctx, 3);
                v1 = slti(s0, 3);
                if (v1 != 0) {
                    backedge(ctx);
                    // 0x00139bc4
                    charge(ctx, 5);
                    v1 = sll(s0, 1);
                    v1 = addu(fp, v1);
                    lhu(v1, v1, 0);
                    if (v1 != 0) {
                        // 0x00139bd8
                        charge(ctx, 11);
                        a0 = dsll32(v1, 16);
                        a0 = dsra32(a0, 16);
                        jal(ctx, 0x139BE0u, gen::fn_sub_1775A0_001775a0);  // an arcana name
                        a0 = addiu(sp, 0xD0);
                        a1 = addiu(gp, -30340);  // "%s"
                        a2 = v0;
                        jal(ctx, 0x139BF4u, gen::fn_sprintf_00523ac8);
                        if (s7 != s0) {
                            // 0x00139cd4
                            charge(ctx, 37);
                            v0 = sll(s0, 1);
                            v0 = addu(v0, s0);
                            s4 = sll(v0, 3);
                            mtc1(s4, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f22, f0);
                            a3 = s3 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                            a2 = 25;
                            mov_s(f12, f21);
                            mov_s(f14, f20);
                            jal(ctx, 0x139D0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            v0 = addu(s6, s4);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x40000000;  // 2.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = 0x42C80000;  // 100.0f
                            mtc1(v0, f12);
                            a0 = s1;
                            a2 = s2;
                            a3 = 10;
                            t0 = 1;
                            t1 = addiu(sp, 0xD0);
                            t2 = 16;
                            t3 = 0;
                            jal(ctx, 0x139D60u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                        } else {
                            // 0x00139c04
                            charge(ctx, 52);
                            v0 = sll(s0, 1);
                            v0 = addu(v0, s0);
                            s4 = sll(v0, 3);
                            mtc1(s4, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f24, f0);
                            a3 = s3 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                            a2 = 27;
                            mov_s(f12, f23);
                            mov_s(f14, f20);
                            jal(ctx, 0x139C3Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            mtc1(s4, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f22, f0);
                            a3 = s3 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                            a2 = 29;
                            mov_s(f12, f21);
                            mov_s(f14, f20);
                            jal(ctx, 0x139C70u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            v0 = addu(s6, s4);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x40000000;  // 2.0f
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            cvt_w_s(f0, f0);
                            mfc1(a1, f0);
                            v0 = 0x42C80000;  // 100.0f
                            mtc1(v0, f12);
                            a0 = s1;
                            a2 = s2;
                            a3 = 6;
                            t0 = 1;
                            t1 = addiu(sp, 0xD0);
                            t2 = 16;
                            t3 = 0;
                            jal(ctx, 0x139CC4u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                        }
                        // 0x00139d68
                        charge(ctx, 1);
                        s0 = addiu(s0, 1);
                        continue;
                    }
                }
                break;
            }
        } else {
            // 0x00139900
            charge(ctx, 30);
            s0 = 0;
            lwc1(f2, sp, 0xCC);
            a0 = 0x433D0000;  // 189.0f
            mtc1(a0, f0);
            add_s(f24, f0, f2);
            a0 = 0x43830000;  // 262.0f
            mtc1(a0, f0);
            lwc1(f1, sp, 0xC8);
            add_s(f23, f0, f1);
            a0 = 0x43440000;  // 196.0f
            mtc1(a0, f0);
            add_s(f22, f0, f2);
            a0 = 0x420C0000;  // 35.0f
            mtc1(a0, f0);
            add_s(f21, f0, f1);
            a0 = si(-256);
            s1 = v1 | a0;
            cvt_w_s(f0, f2);
            mfc1(v1, f0);
            s6 = addiu(v1, 194);
            cvt_w_s(f0, f1);
            mfc1(v1, f0);
            s4 = addiu(v1, 56);
            for (;;) {
                // 0x00139b20
                charge(ctx, 3);
                v1 = slti(s0, 8);
                if (v1 == 0) {
                    goto L_00139b2c_17;
                }
                backedge(ctx);
                // 0x00139978
                charge(ctx, 7);
                a0 = sll(s0, 1);
                v1 = 0x830000;
                v1 = addiu(v1, spr::kComuPages);  // &0x833A60: the arcana pages shown
                v1 = addu(v1, a0);
                lh(a0, v1, 0);
                if (a0 != 0) {
                    // 0x00139994
                    charge(ctx, 9);
                    jal(ctx, 0x139994u, gen::fn_sub_1775A0_001775a0);  // an arcana name
                    a0 = addiu(sp, 0xD0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x1399A8u, gen::fn_sprintf_00523ac8);
                    if (s7 != s0) {
                        // 0x00139a88
                        charge(ctx, 37);
                        v0 = sll(s0, 1);
                        v0 = addu(v0, s0);
                        s2 = sll(v0, 3);
                        mtc1(s2, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f22, f0);
                        a3 = s3 & 0xFF;
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                        a2 = 25;
                        mov_s(f12, f21);
                        mov_s(f14, f20);
                        jal(ctx, 0x139AC0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = addu(s6, s2);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40000000;  // 2.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = 0x42C80000;  // 100.0f
                        mtc1(v0, f12);
                        a0 = s4;
                        a2 = s1;
                        a3 = 10;
                        t0 = 1;
                        t1 = addiu(sp, 0xD0);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x139B14u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    } else {
                        // 0x001399b8
                        charge(ctx, 52);
                        v0 = sll(s0, 1);
                        v0 = addu(v0, s0);
                        s2 = sll(v0, 3);
                        mtc1(s2, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f24, f0);
                        a3 = s3 & 0xFF;
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                        a2 = 27;
                        mov_s(f12, f23);
                        mov_s(f14, f20);
                        jal(ctx, 0x1399F0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        mtc1(s2, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f22, f0);
                        a3 = s3 & 0xFF;
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                        a2 = 29;
                        mov_s(f12, f21);
                        mov_s(f14, f20);
                        jal(ctx, 0x139A24u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = addu(s6, s2);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x40000000;  // 2.0f
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        cvt_w_s(f0, f0);
                        mfc1(a1, f0);
                        v0 = 0x42C80000;  // 100.0f
                        mtc1(v0, f12);
                        a0 = s4;
                        a2 = s1;
                        a3 = 6;
                        t0 = 1;
                        t1 = addiu(sp, 0xD0);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x139A78u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                    }
                    // 0x00139b1c
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                    continue;
                }
                break;
            }
        }
    } else {
        // 0x001396c0
        charge(ctx, 30);
        s1 = 0;
        lwc1(f2, sp, 0xCC);
        a0 = 0x433D0000;  // 189.0f
        mtc1(a0, f0);
        add_s(f24, f0, f2);
        a0 = 0x43830000;  // 262.0f
        mtc1(a0, f0);
        lwc1(f1, sp, 0xC8);
        add_s(f23, f0, f1);
        a0 = 0x43440000;  // 196.0f
        mtc1(a0, f0);
        add_s(f22, f0, f2);
        a0 = 0x420C0000;  // 35.0f
        mtc1(a0, f0);
        add_s(f21, f0, f1);
        a0 = si(-256);
        s0 = v1 | a0;
        cvt_w_s(f0, f2);
        mfc1(v1, f0);
        s6 = addiu(v1, 194);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        s4 = addiu(v1, 56);
        for (;;) {
            // 0x001398e0
            charge(ctx, 3);
            v1 = slti(s1, 9);
            if (v1 == 0) {
                goto L_001398ec_8;
            }
            backedge(ctx);
            // 0x00139738
            charge(ctx, 7);
            a0 = sll(s1, 1);
            v1 = 0x830000;
            v1 = addiu(v1, spr::kComuPages);  // &0x833A60: the arcana pages shown
            v1 = addu(v1, a0);
            lh(a0, v1, 0);
            if (a0 != 0) {
                // 0x00139754
                charge(ctx, 9);
                jal(ctx, 0x139754u, gen::fn_sub_1775A0_001775a0);  // an arcana name
                a0 = addiu(sp, 0xD0);
                a1 = addiu(gp, -30340);  // "%s"
                a2 = v0;
                jal(ctx, 0x139768u, gen::fn_sprintf_00523ac8);
                if (s7 != s1) {
                    // 0x00139848
                    charge(ctx, 37);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    s2 = sll(v0, 3);
                    mtc1(s2, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f22, f0);
                    a3 = s3 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                    a2 = 25;
                    mov_s(f12, f21);
                    mov_s(f14, f20);
                    jal(ctx, 0x139880u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = addu(s6, s2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = s4;
                    a2 = s0;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0xD0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x1398D4u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                } else {
                    // 0x00139778
                    charge(ctx, 52);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    s2 = sll(v0, 3);
                    mtc1(s2, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f24, f0);
                    a3 = s3 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                    a2 = 27;
                    mov_s(f12, f23);
                    mov_s(f14, f20);
                    jal(ctx, 0x1397B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    mtc1(s2, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f22, f0);
                    a3 = s3 & 0xFF;
                    a0 = s5;
                    v0 = 0x830000;
                    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
                    a2 = 29;
                    mov_s(f12, f21);
                    mov_s(f14, f20);
                    jal(ctx, 0x1397E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    v0 = addu(s6, s2);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = 0x42C80000;  // 100.0f
                    mtc1(v0, f12);
                    a0 = s4;
                    a2 = s0;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0xD0);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x139838u, gen::fn_sub_3B2CB0_003b2cb0);  // text at (x, y): colour, size, font, string
                }
                // 0x001398dc
                charge(ctx, 1);
                s1 = addiu(s1, 1);
                continue;
            }
            break;
        }
    }
    // 0x00139d78 (the shared epilogue, written out on this path)
    charge(ctx, 18);
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
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
    return;
L_001398ec_8:
    charge(ctx, 2);
    // 0x00139d78 (the shared epilogue, written out on this path)
    charge(ctx, 18);
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
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
    return;
L_00139b2c_17:
    charge(ctx, 2);
    // 0x00139d78 (the shared epilogue, written out on this path)
    charge(ctx, 18);
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
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1D0);
}

// 0x00139FC0 sub_139FC0 -- 4108 bytes; frame 0x210: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawCardIn] (xy, links, cursor, scroll, ?, frame): the card view's reveal: the black corner (sub_139DC0),
// the ribbon, the card and its pulse (sub_138EE0 / sub_1392D0) sliding in from frame 8 over 5 frames, the arcana
// picture (gp-19856 + ..., sub_1140D0), the rank block, the partner name and help lines (sub_3C7E20 / sub_3C7E50), the
// arcana page (sub_139660).
void sub_139FC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00139fc0
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
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
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xB8);
    mov_s(f23, f12);
    s4 = a1;
    s3 = a3;
    s2 = t0;
    sw(t1, sp, 0xB4);
    s1 = t2;
    s0 = t3;
    a1 = 0;
    jal(ctx, 0x13A020u, gen::fn_sub_139DC0_00139dc0);  // the black corner
    sw(zero, sp, 0x20C);
    sw(zero, sp, 0x208);
    ld(a0, sp, 0x208);
    mov_s(f12, f23);
    a1 = 0;
    jal(ctx, 0x13A03Cu, gen::fn_sub_1368A0_001368a0);  // the ribbon
    v0 = slti(s1, 8);
    if (v0 == 0) {
        // 0x0013a050
        charge(ctx, 4);
        v1 = addiu(s1, -8);
        v0 = slti(v1, 5);
        if (v0 != 0) {
            // 0x0013a0b4
            charge(ctx, 71);
            v0 = 5;
            a0 = subu(v0, v1);
            v1 = sll(a0, 3);
            v1 = subu(v1, a0);
            v1 = sll(v1, 3);
            v1 = subu(v1, a0);
            v1 = sll(v1, 2);
            div(v1, v0);
            mflo(v1);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x208);
            lwc1(f0, sp, 0xB8);
            sub_s(f2, f0, f1);
            swc1(f2, sp, 0x208);
            v1 = sll(a0, 2);
            a0 = addu(v1, a0);
            v1 = sll(a0, 2);
            v1 = addu(a0, v1);
            v1 = sll(v1, 1);
            div1(v1, v0);
            mflo1(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x20C);
            lwc1(f0, sp, 0xBC);
            add_s(f1, f1, f0);
            swc1(f1, sp, 0x20C);
            v0 = 0x40A00000;  // 5.0f
            mtc1(v0, f0);
            sub_s(f0, f2, f0);
            swc1(f0, sp, 0x208);
            v0 = 0x41200000;  // 10.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x20C);
            v0 = addu(s3, s2);
            v0 = sll(v0, 2);
            s6 = addu(s4, v0);
            ld(a0, sp, 0x208);
            mov_s(f12, f23);
            lw(a1, s6, 0);
            a2 = 0;
            jal(ctx, 0x13A170u, gen::fn_sub_138EE0_00138ee0);  // the rank block
            lwc1(f1, sp, 0x208);
            v0 = 0x40A00000;  // 5.0f
            mtc1(v0, f0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0x208);
            lwc1(f1, sp, 0x20C);
            v0 = 0x41200000;  // 10.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x20C);
            lw(a3, s6, 0);
            v0 = 0x5E0000;
            v0 = addiu(v0, 12832);  // &0x5E3220
            v0 = addu(v0, a3);
            lb(a1, v0, 0);
            ld(a0, sp, 0x208);
            mov_s(f12, f23);
            a2 = 0;
            jal(ctx, 0x13A1C8u, gen::fn_sub_1392D0_001392d0);  // the bust-up picture
        } else {
            // 0x0013a060
            charge(ctx, 21);
            v0 = addu(s3, s2);
            v0 = sll(v0, 2);
            s6 = addu(s4, v0);
            ld(a0, sp, 0xB8);
            mov_s(f12, f23);
            lw(a1, s6, 0);
            a2 = 0;
            jal(ctx, 0x13A07Cu, gen::fn_sub_138EE0_00138ee0);  // the rank block
            lw(a3, s6, 0);
            v0 = 0x5E0000;
            v0 = addiu(v0, 12832);  // &0x5E3220
            v0 = addu(v0, a3);
            lb(a1, v0, 0);
            ld(a0, sp, 0xB8);
            mov_s(f12, f23);
            a2 = 0;
            jal(ctx, 0x13A0A4u, gen::fn_sub_1392D0_001392d0);  // the bust-up picture
        }
    }
    // 0x0013a1d0
    charge(ctx, 3);
    v0 = slti(s1, 5);
    if (v0 == 0) {
        // 0x0013a1dc
        charge(ctx, 7);
        v1 = addiu(s1, -5);
        v0 = addu(s3, s2);
        v0 = sll(v0, 2);
        a1 = addu(s4, v0);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x0013a218
            charge(ctx, 1);
            a3 = 0;
        } else {
            // 0x0013a1f8
            charge(ctx, 8);
            a0 = 5;
            v1 = subu(a0, v1);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(a3);
        }
        // 0x0013a21c
        charge(ctx, 6);
        ld(a0, sp, 0xB8);
        mov_s(f12, f23);
        lw(a1, a1, 0);
        lw(a2, sp, 0xB4);
        jal(ctx, 0x13A22Cu, gen::fn_sub_139660_00139660);
    }
    // 0x0013a234
    charge(ctx, 3);
    at = slti(s0, 2);
    if (at == 0) {
        // 0x0013a24c
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 != 0) {
            // 0x0013a264
            charge(ctx, 7);
            v0 = 7;
            v1 = subu(v0, s0);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 5;
            div(v1, v0);
            mflo(v1);
        } else {
            // 0x0013a258
            charge(ctx, 3);
            v1 = 0;
        }
    } else {
        // 0x0013a240
        charge(ctx, 3);
        v1 = 255;
    }
    // 0x0013a280
    charge(ctx, 5);
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x200);
    lw(a3, gp, g::kComuBustBuild);  // 0x7CDF70
    if (a3 != 0) {
        // 0x0013a294
        charge(ctx, 5);
        v0 = 255;
        a0 = subu(v0, v1);
        at = sltiu(a0, 179);
        if (at == 0) {
            // 0x0013a2a8
            charge(ctx, 1);
            a0 = 178;
        }
        // 0x0013a2ac
        charge(ctx, 13);
        v0 = 0x43BB0000;  // 374.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x200);
        add_s(f13, f1, f0);
        v0 = 0x42DA0000;  // 109.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x204);
        add_s(f14, f1, f0);
        mov_s(f12, f23);
        a1 = 300;
        a2 = a1;
        jal(ctx, 0x13A2D8u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
    }
    // 0x0013a2e0
    charge(ctx, 3);
    v0 = slti(s0, 5);
    if (v0 != 0) {
        // 0x0013a2f8
        charge(ctx, 6);
        a0 = 5;
        v1 = subu(a0, s0);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(s0);
    } else {
        // 0x0013a2ec
        charge(ctx, 3);
        s0 = 0;
    }
    // 0x0013a310
    charge(ctx, 9);
    v0 = addu(s3, s2);
    v0 = sll(v0, 2);
    fp = addu(s4, v0);
    lw(s6, fp, 0x0);
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1F8);
    lw(a3, gp, g::kComuBustBuild);  // 0x7CDF70
    if (a3 != 0) {
        // 0x0013a334
        charge(ctx, 26);
        v0 = 255;
        v1 = subu(v0, s0);
        lwc1(f20, sp, 0x1FC);
        v0 = si(-256);
        a0 = v1 | v0;
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f2);
        v0 = 0x43B10000;  // 354.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1F8);
        add_s(f0, f1, f0);
        add_s(f13, f2, f0);
        v0 = 0x42E40000;  // 114.0f
        mtc1(v0, f0);
        add_s(f14, f0, f20);
        mov_s(f12, f23);
        a1 = 300;
        a2 = a1;
        jal(ctx, 0x13A380u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
        a0 = s6;
        jal(ctx, 0x13A38Cu, gen::fn_sub_172160_00172160);  // (link)
        if (v0 == 0) {
            // 0x0013a3ec
            charge(ctx, 5);
            a0 = s6;
            jal(ctx, 0x13A3F0u, gen::fn_sub_1717C0_001717c0);  // (link)
            if (v0 != 0) {
                // 0x0013a400
                charge(ctx, 18);
                v0 = 519;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0x1F8);
                add_s(f12, f1, f0);
                v0 = 0x43070000;  // 135.0f
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s0 & 0xFF;
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::comu(9));  // 0x833B64: social-link sprite file 9
                a2 = 3;
                mov_s(f14, f23);
                jal(ctx, 0x13A440u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
        } else {
            // 0x0013a39c
            charge(ctx, 20);
            v0 = 519;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x1F8);
            add_s(f12, f1, f0);
            v0 = 0x43070000;  // 135.0f
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s0 & 0xFF;
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(9));  // 0x833B64: social-link sprite file 9
            a2 = 2;
            mov_s(f14, f23);
            jal(ctx, 0x13A3DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
    }
    // 0x0013a448
    charge(ctx, 3);
    v0 = slti(s1, 2);
    if (v0 == 0) {
        // 0x0013a454
        charge(ctx, 4);
        v0 = addiu(s1, -2);
        at = slti(v0, 5);
        if (at == 0) {
            // 0x0013a484
            charge(ctx, 1);
            s0 = 0;
        } else {
            // 0x0013a464
            charge(ctx, 8);
            a0 = 5;
            v1 = subu(a0, v0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(s0);
        }
        // 0x0013a488
        charge(ctx, 90);
        lw(v1, fp, 0x0);
        v0 = 0x5E0000;
        v0 = addiu(v0, 12832);  // &0x5E3220
        v0 = addu(v0, v1);
        lb(s6, v0, 0);
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1F0);
        lwc1(f20, sp, 0x1F4);
        a2 = addiu(s6, -1);
        v0 = 0x430C0000;  // 140.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1F0);
        add_s(f12, f1, f0);
        v0 = 0x41900000;  // 18.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s0 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        mov_s(f14, f23);
        jal(ctx, 0x13A4E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x42200000;  // 40.0f
        mtc1(v0, f0);
        add_s(f21, f0, f20);
        v0 = 0x430E0000;  // 142.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1F0);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 43;
        mov_s(f13, f21);
        mov_s(f14, f23);
        jal(ctx, 0x13A524u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x44090000;  // 548.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1F0);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 44;
        mov_s(f13, f21);
        mov_s(f14, f23);
        jal(ctx, 0x13A558u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        a2 = addiu(s6, 49);
        v0 = 0x43130000;  // 147.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1F0);
        add_s(f12, f1, f0);
        v0 = 0x42240000;  // 41.0f
        mtc1(v0, f0);
        add_s(f1, f0, f20);
        v0 = 0x3F800000;  // 1.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s0 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
        mov_s(f14, f23);
        jal(ctx, 0x13A5A8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x43670000;  // 231.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1F0);
        add_s(f12, f1, f0);
        v0 = 0x42400000;  // 48.0f
        mtc1(v0, f0);
        add_s(f13, f0, f20);
        a3 = s0 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 45;
        mov_s(f14, f23);
        jal(ctx, 0x13A5E8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0013a5f0
    charge(ctx, 3);
    v0 = slti(s1, 3);
    if (v0 == 0) {
        // 0x0013a5fc
        charge(ctx, 4);
        v0 = addiu(s1, -3);
        at = slti(v0, 5);
        if (at == 0) {
            // 0x0013a62c
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x0013a60c
            charge(ctx, 8);
            a0 = 5;
            v1 = subu(a0, v0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(v1);
        }
        // 0x0013a630
        charge(ctx, 58);
        v0 = addu(s3, s2);
        v0 = sll(v0, 2);
        s0 = addu(s4, v0);
        lw(s6, s0, 0);
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1E8);
        v0 = 255;
        s5 = subu(v0, v1);
        a0 = dsll32(s6, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x13A658u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        a0 = sll(v0, 2);
        v0 = sll(s6, 2);
        v0 = addu(v0, s6);
        v1 = sll(v0, 3);
        v0 = 0x5E0000;
        v0 = addiu(v0, -32540);  // &0x5D80E4
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        a0 = addiu(sp, 0xC0);
        a1 = addiu(gp, -30340);  // "%s"
        lw(a2, v0, 0);
        jal(ctx, 0x13A694u, gen::fn_sprintf_00523ac8);
        lwc1(f0, sp, 0x1E8);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a0 = addiu(v0, 253);
        lwc1(f0, sp, 0x1EC);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        a1 = addiu(v0, 48);
        v0 = 0x42C80000;  // 100.0f
        mtc1(v0, f12);
        v0 = si(-256);
        a2 = s5 | v0;
        a3 = 6;
        t0 = 1;
        t1 = addiu(sp, 0xC0);
        t2 = 16;
        t3 = si(-1);
        jal(ctx, 0x13A6E8u, gen::fn_sub_3B2F90_003b2f90);  // text at (x, y): colour, size, font, string
        lh(a0, s0, 0);
        jal(ctx, 0x13A6F4u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        s6 = dsll32(v0, 24);
        s6 = dsra32(s6, 24);
        lw(s0, s0, 0);
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1E0);
        if (s6 != 0) {
            // 0x0013a718
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x13A71Cu, gen::fn_sub_1717C0_001717c0);  // (link)
            if (v0 == 0) {
                // 0x0013a7cc
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x13A7D0u, gen::fn_sub_172160_00172160);  // (link)
                if (v0 == 0) {
                    // 0x0013a880
                    charge(ctx, 40);
                    v0 = 0x430F0000;  // 143.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x1E0);
                    add_s(f1, f1, f0);
                    v0 = 0x41600000;  // 14.0f
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x1E4);
                    add_s(f1, f1, f0);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    sub_s(f12, f23, f0);
                    v0 = si(-256);
                    a2 = s5 | v0;
                    v0 = sll(s0, 1);
                    v0 = addu(v0, s0);
                    v1 = sll(v0, 3);
                    v0 = 0x5D0000;
                    v0 = addiu(v0, 28654);  // &0x5D6FEE
                    v1 = addu(v0, v1);
                    v0 = sll(s6, 1);
                    v0 = addu(v0, v1);
                    lh(t2, v0, 0);
                    a3 = 1;
                    t0 = 10;
                    t1 = 7;
                    jal(ctx, 0x13A918u, gen::fn_sub_3C7E20_003c7e20);  // a message text
                } else {
                    // 0x0013a7e0
                    charge(ctx, 40);
                    v0 = 0x430F0000;  // 143.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x1E0);
                    add_s(f1, f1, f0);
                    v0 = 0x41600000;  // 14.0f
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    v0 = 0x42920000;  // 73.0f
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x1E4);
                    add_s(f1, f1, f0);
                    v0 = 0x41000000;  // 8.0f
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    v0 = 0x40000000;  // 2.0f
                    mtc1(v0, f0);
                    sub_s(f12, f23, f0);
                    v0 = si(-256);
                    a2 = s5 | v0;
                    v0 = sll(s0, 1);
                    v0 = addu(v0, s0);
                    v1 = sll(v0, 3);
                    v0 = 0x5D0000;
                    v0 = addiu(v0, 28678);  // &0x5D7006
                    v0 = addu(v0, v1);
                    lh(t2, v0, 0);
                    a3 = 1;
                    t0 = 10;
                    t1 = 7;
                    jal(ctx, 0x13A870u, gen::fn_sub_3C7E20_003c7e20);  // a message text
                }
            } else {
                // 0x0013a72c
                charge(ctx, 40);
                v0 = 0x430F0000;  // 143.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x1E0);
                add_s(f1, f1, f0);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                v0 = 0x42920000;  // 73.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x1E4);
                add_s(f1, f1, f0);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                sub_s(f12, f23, f0);
                v0 = si(-256);
                a2 = s5 | v0;
                v0 = sll(s0, 1);
                v0 = addu(v0, s0);
                v1 = sll(v0, 3);
                v0 = 0x5D0000;
                v0 = addiu(v0, 28676);  // "\n"
                v0 = addu(v0, v1);
                lh(t2, v0, 0);
                a3 = 1;
                t0 = 10;
                t1 = 7;
                jal(ctx, 0x13A7BCu, gen::fn_sub_3C7E20_003c7e20);  // a message text
            }
        }
    }
    // 0x0013a920
    charge(ctx, 3);
    v0 = slti(s1, 5);
    if (v0 == 0) {
        // 0x0013a92c
        charge(ctx, 4);
        v0 = addiu(s1, -5);
        at = slti(v0, 5);
        if (at == 0) {
            // 0x0013a95c
            charge(ctx, 1);
            s0 = 0;
        } else {
            // 0x0013a93c
            charge(ctx, 8);
            a0 = 5;
            v1 = subu(a0, v0);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            div(v0, a0);
            mflo(s0);
        }
        // 0x0013a960
        charge(ctx, 79);
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1D8);
        lwc1(f1, sp, 0x1DC);
        v0 = 415;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f20, f0, f1);
        v0 = 0x42100000;  // 36.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1D8);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x40800000;  // 4.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
        a2 = 0;
        mov_s(f13, f20);
        jal(ctx, 0x13A9B8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 0x42500000;  // 52.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1D8);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x40800000;  // 4.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
        a2 = 7;
        mov_s(f13, f20);
        jal(ctx, 0x13A9F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 561;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x1D8);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x40800000;  // 4.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 3;
        mov_s(f13, f20);
        jal(ctx, 0x13AA40u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 427;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x1D8);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x40800000;  // 4.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
        a2 = 8;
        mov_s(f13, f20);
        jal(ctx, 0x13AA88u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, fp, 0x0);
        if (v1 != 0) {
            // 0x0013aa9c
            charge(ctx, 3);
            v0 = 29;
            if (v1 == v0) {
                goto L_0013aaa8;
            }
            // 0x0013ac48
            charge(ctx, 65);
            v0 = addu(s3, s2);
            v0 = sll(v0, 2);
            s2 = addu(s4, v0);
            a0 = dsll32(v1, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x13AC5Cu, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
            s3 = dsll32(v0, 24);
            s3 = dsra32(s3, 24);
            lw(v1, s2, 0);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 1);
            v0 = 0x5E0000;
            v0 = addiu(v0, -17664);  // &0x5DBB00
            v1 = addu(v0, v1);
            lw(v0, sp, 0xB4);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            lhu(s2, v0, 0);
            ld(v0, sp, 0xB8);
            sd(v0, sp, 0x1C8);
            v0 = 255;
            s4 = subu(v0, s0);
            lwc1(f20, sp, 0x1CC);
            v0 = 0x43A70000;  // 334.0f
            mtc1(v0, f0);
            add_s(f21, f0, f20);
            v0 = 0x43880000;  // 272.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C8);
            add_s(f12, f1, f0);
            a3 = s0 & 0xFF;
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            sub_s(f14, f23, f0);
            a0 = s7;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
            a2 = 31;
            mov_s(f13, f21);
            jal(ctx, 0x13ACF4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            v0 = 607;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x1C8);
            add_s(f12, f1, f0);
            a3 = s0 & 0xFF;
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            sub_s(f14, f23, f0);
            a0 = s7;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
            a2 = 32;
            mov_s(f13, f21);
            jal(ctx, 0x13AD3Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            if (s3 != 0) {
                // 0x0013ad4c
                charge(ctx, 45);
                v0 = 289;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0x1C8);
                add_s(f1, f1, f0);
                v0 = 0x40800000;  // 4.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                v0 = 341;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                add_s(f1, f0, f20);
                v0 = 0x41200000;  // 10.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f1);
                add_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                sub_s(f12, f23, f1);
                v0 = si(-256);
                a2 = s4 | v0;
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v1 = sll(v0, 2);
                v0 = 0x5D0000;
                v0 = addiu(v0, 29354);  // &0x5D72AA
                v1 = addu(v0, v1);
                v0 = sll(s3, 1);
                v0 = addu(v0, v1);
                lh(t3, v0, 0);
                a3 = 1;
                t0 = 10;
                t1 = 0;
                t2 = 7;
                jal(ctx, 0x13ADF8u, gen::fn_sub_3C7E50_003c7e50);  // a message text
            }
            goto L_0013ae00;
        }
    L_0013aaa8:
        charge(ctx, 57);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x13AAB0u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        s3 = dsll32(v0, 24);
        s3 = dsra32(s3, 24);
        lw(v0, sp, 0xB4);
        v1 = sll(v0, 1);
        v0 = 0x830000;
        v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
        v0 = addu(v0, v1);
        lh(s2, v0, 0);
        ld(v0, sp, 0xB8);
        sd(v0, sp, 0x1D0);
        v0 = 255;
        s4 = subu(v0, s0);
        lwc1(f20, sp, 0x1D4);
        v0 = 0x43A70000;  // 334.0f
        mtc1(v0, f0);
        add_s(f21, f0, f20);
        v0 = 0x43880000;  // 272.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1D0);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 31;
        mov_s(f13, f21);
        jal(ctx, 0x13AB34u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 607;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x1D0);
        add_s(f12, f1, f0);
        a3 = s0 & 0xFF;
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s7;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 32;
        mov_s(f13, f21);
        jal(ctx, 0x13AB7Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        if (s3 != 0) {
            // 0x0013ab8c
            charge(ctx, 47);
            v0 = 289;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x1D0);
            add_s(f1, f1, f0);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            v0 = 341;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f0, f20);
            v0 = 0x41200000;  // 10.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f1);
            add_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            sub_s(f12, f23, f1);
            v0 = si(-256);
            a2 = s4 | v0;
            v0 = sll(s2, 2);
            v0 = addu(v0, s2);
            v1 = sll(v0, 2);
            v0 = 0x5D0000;
            v0 = addiu(v0, 29354);  // &0x5D72AA
            v1 = addu(v0, v1);
            v0 = sll(s3, 1);
            v0 = addu(v0, v1);
            lh(t3, v0, 0);
            a3 = 1;
            t0 = 10;
            t1 = 0;
            t2 = 7;
            jal(ctx, 0x13AC38u, gen::fn_sub_3C7E50_003c7e50);  // a message text
        }
    }
L_0013ae00:
    charge(ctx, 3);
    at = slti(s1, 5);
    if (at == 0) {
        // 0x0013ae2c
        charge(ctx, 1);
        s0 = 0;
    } else {
        // 0x0013ae0c
        charge(ctx, 8);
        a0 = 5;
        v1 = subu(a0, s1);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(s0);
    }
    // 0x0013ae30
    charge(ctx, 8);
    ld(v0, sp, 0xB8);
    sd(v0, sp, 0x1C0);
    lw(v0, gp, g::kComuCardScroll);  // 0x7CDF6C
    v0 = addiu(v0, 1);
    sw(v0, gp, g::kComuCardScroll);  // 0x7CDF6C
    at = slti(v0, 449);
    if (at == 0) {
        // 0x0013ae50
        charge(ctx, 1);
        sw(zero, gp, g::kComuCardScroll);  // 0x7CDF6C
    }
    // 0x0013ae54
    charge(ctx, 94);
    lwc1(f22, sp, 0x1C4);
    v0 = 0x43470000;  // 199.0f
    mtc1(v0, f0);
    add_s(f20, f0, f22);
    v0 = 0x44100000;  // 576.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1C0);
    add_s(f21, f1, f0);
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f13, f20, f0);
    a3 = s0 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s7;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 0;
    mov_s(f12, f21);
    jal(ctx, 0x13AEACu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f13, f22, f0);
    a3 = s0 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s7;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 1;
    mov_s(f12, f21);
    jal(ctx, 0x13AEE8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f1, f20, f0);
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s7;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 0;
    mov_s(f12, f21);
    jal(ctx, 0x13AF34u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f1, f22, f0);
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s7;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 1;
    mov_s(f12, f21);
    jal(ctx, 0x13AF80u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
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
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x210);
}

// 0x0013AFD0 sub_13AFD0 -- 3296 bytes; frame 0x220: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_ComuDrawCard] (xy, links, cursor, scroll, ?, alpha): the card view drawn at once (the same parts as
// sub_139FC0 in place).
void sub_13AFD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0013afd0
    enter(ctx, 72);  // entry check point + this block's cycles
    sp = addiu(sp, -0x220);
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
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0xC8);
    mov_s(f23, f12);
    s4 = a1;
    s3 = a3;
    s7 = t0;
    fp = t1;
    s2 = t2;
    a1 = 0;
    jal(ctx, 0x13B02Cu, gen::fn_sub_139DC0_00139dc0);  // the black corner
    sw(zero, sp, 0x21C);
    sw(zero, sp, 0x218);
    ld(a0, sp, 0x218);
    mov_s(f12, f23);
    a1 = 0;
    jal(ctx, 0x13B048u, gen::fn_sub_1368A0_001368a0);  // the ribbon
    v0 = addu(s3, s7);
    v0 = sll(v0, 2);
    s1 = addu(s4, v0);
    lw(v1, s1, 0);
    v0 = 0x5E0000;
    v0 = addiu(v0, 12832);  // &0x5E3220
    v0 = addu(v0, v1);
    lb(a1, v0, 0);
    ld(a0, sp, 0xC8);
    mov_s(f12, f23);
    a2 = 0;
    jal(ctx, 0x13B07Cu, gen::fn_sub_138EE0_00138ee0);  // the rank block
    lw(a3, s1, 0);
    v0 = 0x5E0000;
    v0 = addiu(v0, 12832);  // &0x5E3220
    v0 = addu(v0, a3);
    lb(a1, v0, 0);
    ld(a0, sp, 0xC8);
    mov_s(f12, f23);
    a2 = 0;
    jal(ctx, 0x13B0A4u, gen::fn_sub_1392D0_001392d0);  // the bust-up picture
    ld(a0, sp, 0xC8);
    mov_s(f12, f23);
    lw(a1, s1, 0);
    a2 = fp;
    a3 = 0;
    jal(ctx, 0x13B0C0u, gen::fn_sub_139660_00139660);
    ld(a0, sp, 0xC8);
    mov_s(f12, f23);
    a1 = 0;
    jal(ctx, 0x13B0D4u, gen::fn_sub_139DC0_00139dc0);  // the black corner
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x210);
    lw(a3, gp, g::kComuBustBuild);  // 0x7CDF70
    if (a3 != 0) {
        // 0x0013b0f0
        charge(ctx, 14);
        v0 = 0x43BB0000;  // 374.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x210);
        add_s(f13, f1, f0);
        v0 = 0x42DA0000;  // 109.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x214);
        add_s(f14, f1, f0);
        mov_s(f12, f23);
        a0 = 178;
        a1 = 300;
        a2 = a1;
        jal(ctx, 0x13B120u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
    }
    // 0x0013b128
    charge(ctx, 6);
    lw(s0, s1, 0);
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x208);
    lw(a3, gp, g::kComuBustBuild);  // 0x7CDF70
    if (a3 != 0) {
        // 0x0013b140
        charge(ctx, 23);
        lwc1(f20, sp, 0x20C);
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f2);
        v0 = 0x43B10000;  // 354.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x208);
        add_s(f0, f1, f0);
        add_s(f13, f2, f0);
        v0 = 0x42E40000;  // 114.0f
        mtc1(v0, f0);
        add_s(f14, f0, f20);
        mov_s(f12, f23);
        a0 = si(-1);
        a1 = 300;
        a2 = a1;
        jal(ctx, 0x13B180u, gen::fn_sub_1140D0_001140d0);  // [textured rectangle]
        a0 = s0;
        jal(ctx, 0x13B18Cu, gen::fn_sub_172160_00172160);  // (link)
        if (v0 == 0) {
            // 0x0013b1ec
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x13B1F0u, gen::fn_sub_1717C0_001717c0);  // (link)
            if (v0 != 0) {
                // 0x0013b200
                charge(ctx, 18);
                v0 = 519;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, sp, 0x208);
                add_s(f12, f1, f0);
                v0 = 0x43070000;  // 135.0f
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::comu(9));  // 0x833B64: social-link sprite file 9
                a2 = 3;
                a3 = 0;
                mov_s(f14, f23);
                jal(ctx, 0x13B240u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
        } else {
            // 0x0013b19c
            charge(ctx, 20);
            v0 = 519;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x208);
            add_s(f12, f1, f0);
            v0 = 0x43070000;  // 135.0f
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::comu(9));  // 0x833B64: social-link sprite file 9
            a2 = 2;
            a3 = 0;
            mov_s(f14, f23);
            jal(ctx, 0x13B1DCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        }
    }
    // 0x0013b248
    charge(ctx, 224);
    v0 = addu(s3, s7);
    v0 = sll(v0, 2);
    s0 = addu(s4, v0);
    lw(v1, s0, 0);
    v0 = 0x5E0000;
    v0 = addiu(v0, 12832);  // &0x5E3220
    v0 = addu(v0, v1);
    lb(v0, v0, 0);
    sq(v0, sp, 0xB0);
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x200);
    lwc1(f20, sp, 0x204);
    lq(v0, sp, 0xB0);
    a2 = addiu(v0, -1);
    v0 = 0x430C0000;  // 140.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x200);
    add_s(f12, f1, f0);
    v0 = 0x41900000;  // 18.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
    a3 = 0;
    mov_s(f14, f23);
    jal(ctx, 0x13B2B4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42200000;  // 40.0f
    mtc1(v0, f0);
    add_s(f21, f0, f20);
    v0 = 0x430E0000;  // 142.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x200);
    add_s(f12, f1, f0);
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
    a2 = 43;
    mov_s(f13, f21);
    a3 = 0;
    mov_s(f14, f23);
    jal(ctx, 0x13B2F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x44090000;  // 548.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x200);
    add_s(f12, f1, f0);
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
    a2 = 44;
    mov_s(f13, f21);
    a3 = 0;
    mov_s(f14, f23);
    jal(ctx, 0x13B32Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lq(v0, sp, 0xB0);
    a2 = addiu(v0, 49);
    v0 = 0x43130000;  // 147.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x200);
    add_s(f12, f1, f0);
    v0 = 0x42240000;  // 41.0f
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    v0 = 0x3F800000;  // 1.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(1));  // 0x833B44: social-link sprite file 1
    a3 = 0;
    mov_s(f14, f23);
    jal(ctx, 0x13B380u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x43670000;  // 231.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x200);
    add_s(f12, f1, f0);
    v0 = 0x42400000;  // 48.0f
    mtc1(v0, f0);
    add_s(f13, f0, f20);
    a0 = s5;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
    a2 = 45;
    a3 = 0;
    mov_s(f14, f23);
    jal(ctx, 0x13B3C0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lw(s5, s0, 0);
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x1F8);
    a0 = dsll32(s5, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x13B3DCu, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    a0 = sll(v0, 2);
    v0 = sll(s5, 2);
    v0 = addu(v0, s5);
    v1 = sll(v0, 3);
    v0 = 0x5E0000;
    v0 = addiu(v0, -32540);  // &0x5D80E4
    v0 = addu(v0, v1);
    v0 = addu(a0, v0);
    a0 = addiu(sp, 0xD0);
    a1 = addiu(gp, -30340);  // "%s"
    lw(a2, v0, 0);
    jal(ctx, 0x13B418u, gen::fn_sprintf_00523ac8);
    lwc1(f0, sp, 0x1F8);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    a0 = addiu(v0, 253);
    lwc1(f0, sp, 0x1FC);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    a1 = addiu(v0, 48);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a2 = si(-1);
    a3 = 6;
    t0 = 1;
    t1 = addiu(sp, 0xD0);
    t2 = 16;
    t3 = a2;
    jal(ctx, 0x13B468u, gen::fn_sub_3B2F90_003b2f90);  // text at (x, y): colour, size, font, string
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x1F0);
    lwc1(f1, sp, 0x1F4);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    add_s(f20, f0, f1);
    v0 = 0x42100000;  // 36.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1F0);
    add_s(f12, f1, f0);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
    a2 = 0;
    mov_s(f13, f20);
    a3 = 0;
    jal(ctx, 0x13B4C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 0x42500000;  // 52.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1F0);
    add_s(f12, f1, f0);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(10));  // 0x833B68: social-link sprite file 10
    a2 = 7;
    mov_s(f13, f20);
    a3 = 0;
    jal(ctx, 0x13B508u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 561;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x1F0);
    add_s(f12, f1, f0);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
    a2 = 3;
    mov_s(f13, f20);
    a3 = 0;
    jal(ctx, 0x13B550u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 427;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x1F0);
    add_s(f12, f1, f0);
    v0 = 0x40800000;  // 4.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::camp(13));  // 0x833BA4: camp sprite file 13
    a2 = 8;
    mov_s(f13, f20);
    a3 = 0;
    jal(ctx, 0x13B598u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lh(a0, s0, 0);
    jal(ctx, 0x13B5A4u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
    s5 = dsll32(v0, 24);
    s5 = dsra32(s5, 24);
    lw(s0, s0, 0);
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x1E8);
    if (s5 != 0) {
        // 0x0013b5c8
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x13B5CCu, gen::fn_sub_1717C0_001717c0);  // (link)
        if (v0 == 0) {
            // 0x0013b678
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x13B67Cu, gen::fn_sub_172160_00172160);  // (link)
            if (v0 == 0) {
                // 0x0013b728
                charge(ctx, 39);
                v0 = 0x430F0000;  // 143.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x1E8);
                add_s(f1, f1, f0);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                v0 = 0x42920000;  // 73.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x1EC);
                add_s(f1, f1, f0);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                sub_s(f12, f23, f0);
                v0 = sll(s0, 1);
                v0 = addu(v0, s0);
                v1 = sll(v0, 3);
                v0 = 0x5D0000;
                v0 = addiu(v0, 28654);  // &0x5D6FEE
                v1 = addu(v0, v1);
                v0 = sll(s5, 1);
                v0 = addu(v0, v1);
                lh(t2, v0, 0);
                a2 = si(-1);
                a3 = 1;
                t0 = 10;
                t1 = 7;
                jal(ctx, 0x13B7BCu, gen::fn_sub_3C7E20_003c7e20);  // a message text
            } else {
                // 0x0013b68c
                charge(ctx, 39);
                v0 = 0x430F0000;  // 143.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x1E8);
                add_s(f1, f1, f0);
                v0 = 0x41600000;  // 14.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                v0 = 0x42920000;  // 73.0f
                mtc1(v0, f1);
                lwc1(f0, sp, 0x1EC);
                add_s(f1, f1, f0);
                v0 = 0x41000000;  // 8.0f
                mtc1(v0, f0);
                sub_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a1, f0);
                v0 = 0x40000000;  // 2.0f
                mtc1(v0, f0);
                sub_s(f12, f23, f0);
                v0 = sll(s0, 1);
                v0 = addu(v0, s0);
                v1 = sll(v0, 3);
                v0 = 0x5D0000;
                v0 = addiu(v0, 28678);  // &0x5D7006
                v0 = addu(v0, v1);
                lh(t2, v0, 0);
                a2 = si(-1);
                a3 = 1;
                t0 = 10;
                t1 = 7;
                jal(ctx, 0x13B718u, gen::fn_sub_3C7E20_003c7e20);  // a message text
            }
        } else {
            // 0x0013b5dc
            charge(ctx, 39);
            v0 = 0x430F0000;  // 143.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1E8);
            add_s(f1, f1, f0);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            v0 = 0x42920000;  // 73.0f
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1EC);
            add_s(f1, f1, f0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            sub_s(f12, f23, f0);
            v0 = sll(s0, 1);
            v0 = addu(v0, s0);
            v1 = sll(v0, 3);
            v0 = 0x5D0000;
            v0 = addiu(v0, 28676);  // "\n"
            v0 = addu(v0, v1);
            lh(t2, v0, 0);
            a2 = si(-1);
            a3 = 1;
            t0 = 10;
            t1 = 7;
            jal(ctx, 0x13B668u, gen::fn_sub_3C7E20_003c7e20);  // a message text
        }
    }
    // 0x0013b7c4
    charge(ctx, 3);
    lw(v1, s1, 0);
    if (v1 != 0) {
        // 0x0013b7d0
        charge(ctx, 3);
        v0 = 29;
        if (v1 == v0) {
            goto L_0013b7dc;
        }
        // 0x0013b96c
        charge(ctx, 62);
        v0 = addu(s3, s7);
        v0 = sll(v0, 2);
        s1 = addu(s4, v0);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x13B980u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
        s0 = dsll32(v0, 24);
        s0 = dsra32(s0, 24);
        lw(v1, s1, 0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 1);
        v0 = 0x5E0000;
        v0 = addiu(v0, -17664);  // &0x5DBB00
        v1 = addu(v0, v1);
        v0 = sll(fp, 1);
        v0 = addu(v0, v1);
        lhu(s1, v0, 0);
        ld(v0, sp, 0xC8);
        sd(v0, sp, 0x1D8);
        lwc1(f20, sp, 0x1DC);
        v0 = 0x43A70000;  // 334.0f
        mtc1(v0, f0);
        add_s(f21, f0, f20);
        v0 = 0x43880000;  // 272.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0x1D8);
        add_s(f12, f1, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 31;
        mov_s(f13, f21);
        a3 = 0;
        jal(ctx, 0x13BA0Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        v0 = 607;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x1D8);
        add_s(f12, f1, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f0);
        sub_s(f14, f23, f0);
        a0 = s6;
        v0 = 0x830000;
        lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
        a2 = 32;
        mov_s(f13, f21);
        a3 = 0;
        jal(ctx, 0x13BA54u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        if (s0 != 0) {
            // 0x0013ba64
            charge(ctx, 44);
            v0 = 289;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x1D8);
            add_s(f1, f1, f0);
            v0 = 0x40800000;  // 4.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            v0 = 341;
            mtc1(v0, f0);
            cvt_s_w(f0, f0);
            add_s(f1, f0, f20);
            v0 = 0x41200000;  // 10.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f1);
            add_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            sub_s(f12, f23, f1);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            v1 = sll(v0, 2);
            v0 = 0x5D0000;
            v0 = addiu(v0, 29354);  // &0x5D72AA
            v1 = addu(v0, v1);
            v0 = sll(s0, 1);
            v0 = addu(v0, v1);
            lh(t3, v0, 0);
            a2 = si(-1);
            a3 = 1;
            t0 = 10;
            t1 = 0;
            t2 = 7;
            jal(ctx, 0x13BB0Cu, gen::fn_sub_3C7E50_003c7e50);  // a message text
        }
        goto L_0013bb14;
    }
L_0013b7dc:
    charge(ctx, 54);
    a0 = dsll32(v1, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x13B7E4u, gen::fn_sub_16DBA0_0016dba0);  // [datComuGetRank]
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    v1 = sll(fp, 1);
    v0 = 0x830000;
    v0 = addiu(v0, spr::kComuPages);  // &0x833A60: the arcana pages shown
    v0 = addu(v0, v1);
    lh(s1, v0, 0);
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x1E0);
    lwc1(f20, sp, 0x1E4);
    v0 = 0x43A70000;  // 334.0f
    mtc1(v0, f0);
    add_s(f21, f0, f20);
    v0 = 0x43880000;  // 272.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1E0);
    add_s(f12, f1, f0);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
    a2 = 31;
    mov_s(f13, f21);
    a3 = 0;
    jal(ctx, 0x13B85Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    v0 = 607;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x1E0);
    add_s(f12, f1, f0);
    v0 = 0x40000000;  // 2.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(6));  // 0x833B58: social-link sprite file 6
    a2 = 32;
    mov_s(f13, f21);
    a3 = 0;
    jal(ctx, 0x13B8A4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    if (s0 != 0) {
        // 0x0013b8b4
        charge(ctx, 46);
        v0 = 289;
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, sp, 0x1E0);
        add_s(f1, f1, f0);
        v0 = 0x40800000;  // 4.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v0 = 341;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f0, f20);
        v0 = 0x41200000;  // 10.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        v0 = 0x40000000;  // 2.0f
        mtc1(v0, f1);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        sub_s(f12, f23, f1);
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        v1 = sll(v0, 2);
        v0 = 0x5D0000;
        v0 = addiu(v0, 29354);  // &0x5D72AA
        v1 = addu(v0, v1);
        v0 = sll(s0, 1);
        v0 = addu(v0, v1);
        lh(t3, v0, 0);
        a2 = si(-1);
        a3 = 1;
        t0 = 10;
        t1 = 0;
        t2 = 7;
        jal(ctx, 0x13B95Cu, gen::fn_sub_3C7E50_003c7e50);  // a message text
    }
L_0013bb14:
    charge(ctx, 8);
    ld(v0, sp, 0xC8);
    sd(v0, sp, 0x1D0);
    lw(v0, gp, g::kComuCardScroll);  // 0x7CDF6C
    v0 = addiu(v0, 1);
    sw(v0, gp, g::kComuCardScroll);  // 0x7CDF6C
    at = slti(v0, 449);
    if (at == 0) {
        // 0x0013bb34
        charge(ctx, 1);
        sw(zero, gp, g::kComuCardScroll);  // 0x7CDF6C
    }
    // 0x0013bb38
    charge(ctx, 94);
    lwc1(f22, sp, 0x1D4);
    v0 = 0x43470000;  // 199.0f
    mtc1(v0, f0);
    add_s(f20, f0, f22);
    v0 = 0x44100000;  // 576.0f
    mtc1(v0, f1);
    lwc1(f0, sp, 0x1D0);
    add_s(f21, f1, f0);
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f13, f20, f0);
    a3 = s2 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 0;
    mov_s(f12, f21);
    jal(ctx, 0x13BB90u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f13, f22, f0);
    a3 = s2 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 1;
    mov_s(f12, f21);
    jal(ctx, 0x13BBCCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f1, f20, f0);
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 0;
    mov_s(f12, f21);
    jal(ctx, 0x13BC18u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    lwc1(f0, gp, g::kComuCardScroll);  // 0x7CDF6C
    cvt_s_w(f0, f0);
    add_s(f1, f22, f0);
    v0 = 0x43E00000;  // 448.0f
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    v0 = 0x40400000;  // 3.0f
    mtc1(v0, f0);
    sub_s(f14, f23, f0);
    a0 = s6;
    v0 = 0x830000;
    lw(a1, v0, spr::comu(8));  // 0x833B60: social-link sprite file 8
    a2 = 1;
    mov_s(f12, f21);
    jal(ctx, 0x13BC64u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
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
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x220);
}

}  // namespace p3fes::game
