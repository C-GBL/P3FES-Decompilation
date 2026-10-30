// The camp menu's screens, second pass (slice ui6; game/include/p3fes/game/ui6.h has the records, the role of
// every function and how the screens work): the skill screen (its update, layouts, list and element draws, the skill list builder) and the party-status root
// ("H_CampFrStatusRoot").
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
void fn_datGetSkillName_0030bb40(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_nullsub_3_0011bba0(p3fes::EEContext&);
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
void fn_sub_15C520_0015c520(p3fes::EEContext&);
void fn_sub_15C840_0015c840(p3fes::EEContext&);
void fn_sub_15CE50_0015ce50(p3fes::EEContext&);
void fn_sub_15D8E0_0015d8e0(p3fes::EEContext&);
void fn_sub_15DA70_0015da70(p3fes::EEContext&);
void fn_sub_15E150_0015e150(p3fes::EEContext&);
void fn_sub_15E6E0_0015e6e0(p3fes::EEContext&);
void fn_sub_15EE40_0015ee40(p3fes::EEContext&);
void fn_sub_15F320_0015f320(p3fes::EEContext&);
void fn_sub_15FA90_0015fa90(p3fes::EEContext&);
void fn_sub_160800_00160800(p3fes::EEContext&);
void fn_sub_1618A0_001618a0(p3fes::EEContext&);
void fn_sub_166A50_00166a50(p3fes::EEContext&);
void fn_sub_166C00_00166c00(p3fes::EEContext&);
void fn_sub_166C30_00166c30(p3fes::EEContext&);
void fn_sub_166C50_00166c50(p3fes::EEContext&);
void fn_sub_167EF0_00167ef0(p3fes::EEContext&);
void fn_sub_167F10_00167f10(p3fes::EEContext&);
void fn_sub_167F30_00167f30(p3fes::EEContext&);
void fn_sub_167F40_00167f40(p3fes::EEContext&);
void fn_sub_1685D0_001685d0(p3fes::EEContext&);
void fn_sub_1685E0_001685e0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_173660_00173660(p3fes::EEContext&);
void fn_sub_174960_00174960(p3fes::EEContext&);
void fn_sub_174A90_00174a90(p3fes::EEContext&);
void fn_sub_175200_00175200(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_17B480_0017b480(p3fes::EEContext&);
void fn_sub_17B4E0_0017b4e0(p3fes::EEContext&);
void fn_sub_17B500_0017b500(p3fes::EEContext&);
void fn_sub_17B5B0_0017b5b0(p3fes::EEContext&);
void fn_sub_17B660_0017b660(p3fes::EEContext&);
void fn_sub_17BB40_0017bb40(p3fes::EEContext&);
void fn_sub_17BC20_0017bc20(p3fes::EEContext&);
void fn_sub_17D2E0_0017d2e0(p3fes::EEContext&);
void fn_sub_18B6D0_0018b6d0(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_1C7CE0_001c7ce0(p3fes::EEContext&);
void fn_sub_3B32D0_003b32d0(p3fes::EEContext&);
void fn_sub_3C7E20_003c7e20(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui6;  // the record offsets, $gp words, pad words and sprite tables of ui6.h

// 0x0015C840 sub_15C840 -- 1544 bytes; frame 0x110: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SkillBuildList] (list): builds the skill screen's list: every distinct skill of the used stock slots
// (datPersonaIsSlotUsed / datPersonaGetHeroPersona, eight skills each; datPersonaSelectSlot is called per slot, the
// current slot word_836BA8 read first) as 20-byte rows from +12 -- skill id, persona id, stock slot, HP cost, SP cost
// (sub_17B480 / sub_17B500 / sub_17B5B0) --, a skill two personas share kept with the one of higher Ma
// (datPersonaGetTotalStat(.., 1)); +2012 the count; then sorted: skills 192..255 first, the rest by id.
void sub_15C840(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x0015c840
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
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
    v0 = 0x830000;
    lh(v0, v0, spr::kCurrentPersona);  // 0x836BA8: the current persona slot
    sh(v0, sp, 0xC0);
    s1 = 0;
    for (;;) {
        // 0x0015cb9c
        charge(ctx, 3);
        v0 = slti(s1, 12);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015c88c
        charge(ctx, 6);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x15C894u, gen::fn_sub_174960_00174960);  // [datPersonaIsSlotUsed]
        if (v0 != 0) {
            // 0x0015c8a4
            charge(ctx, 12);
            a0 = dsll32(s1, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x15C8ACu, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
            s0 = v0;
            a0 = dsll32(s1, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x15C8C0u, gen::fn_sub_175200_00175200);  // [datPersonaSelectSlot]
            s4 = 0;
            for (;;) {
                // 0x0015cb8c
                charge(ctx, 3);
                v0 = slti(s4, 8);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015c8d4
                charge(ctx, 6);
                v0 = sll(s4, 1);
                a1 = addu(s0, v0);
                s6 = addiu(a1, 12);
                lhu(v0, a1, 12);
                if (v0 != 0) {
                    // 0x0015c8ec
                    charge(ctx, 4);
                    a2 = 0;
                    s2 = 0;
                    for (;;) {
                        // 0x0015ca7c
                        charge(ctx, 3);
                        v0 = slt(s2, s3);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x0015c8fc
                        charge(ctx, 9);
                        v0 = sll(s2, 2);
                        v0 = addu(v0, s2);
                        v0 = sll(v0, 2);
                        a0 = addu(s5, v0);
                        fp = addiu(a0, 0xC);
                        lw(v1, a0, 12);
                        lhu(v0, a1, 12);
                        if (v1 == v0) {
                            goto L_0015c920_6;
                        }
                        // 0x0015ca78
                        charge(ctx, 1);
                        s2 = addiu(s2, 1);
                    }
                L_0015ca88:
                    charge(ctx, 2);
                    if (a2 == 0) {
                        // 0x0015ca90
                        charge(ctx, 19);
                        v0 = sll(s4, 1);
                        a0 = addu(s0, v0);
                        v0 = sll(s3, 2);
                        v0 = addu(v0, s3);
                        v0 = sll(v0, 2);
                        v1 = addu(s5, v0);
                        lhu(v0, a0, 12);
                        sw(v0, v1, 12);
                        sw(s1, v1, 20);
                        lhu(v0, s0, 2);
                        sw(v0, v1, 16);
                        lhu(a0, a0, 12);
                        jal(ctx, 0x15CAC0u, gen::fn_sub_17B480_0017b480);
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x0015cb6c
                            charge(ctx, 6);
                            v0 = sll(s2, 2);
                            v0 = addu(v0, s2);
                            v0 = sll(v0, 2);
                            v0 = addu(s5, v0);
                            sw(zero, v0, 24);
                            sw(zero, v0, 28);
                        } else {
                            // 0x0015cadc
                            charge(ctx, 8);
                            a0 = 1;
                            lhu(a1, s6, 0);
                            jal(ctx, 0x15CAE4u, gen::fn_sub_17B500_0017b500);
                            v1 = v0 & 0xFFFF;
                            v0 = 2;
                            if (v1 == v0) {
                                // 0x0015cb3c
                                charge(ctx, 12);
                                v0 = sll(s2, 2);
                                v0 = addu(v0, s2);
                                v0 = sll(v0, 2);
                                s2 = addu(s5, v0);
                                a0 = 1;
                                lhu(a1, s6, 0);
                                jal(ctx, 0x15CB54u, gen::fn_sub_17B5B0_0017b5b0);
                                sw(v0, s2, 24);
                                sw(zero, s2, 28);
                            } else {
                                // 0x0015cafc
                                charge(ctx, 3);
                                a0 = 1;
                                if (v1 == a0) {
                                    // 0x0015cb10
                                    charge(ctx, 11);
                                    v0 = sll(s2, 2);
                                    v0 = addu(v0, s2);
                                    v0 = sll(v0, 2);
                                    s2 = addu(s5, v0);
                                    sw(zero, s2, 24);
                                    lhu(a1, s6, 0);
                                    jal(ctx, 0x15CB28u, gen::fn_sub_17B5B0_0017b5b0);
                                    sw(v0, s2, 28);
                                } else {
                                    // 0x0015cb08
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x0015cb84
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                }
                // 0x0015cb88
                charge(ctx, 1);
                s4 = addiu(s4, 1);
            }
        }
        // 0x0015cb98
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0015cba8
    charge(ctx, 7);
    sw(s3, s5, 2012);
    a2 = 0;
    a1 = addiu(sp, 0xD0);
    a0 = 5;
    v1 = addiu(sp, 0xF0);
    for (;;) {
        // 0x0015cdf8
        charge(ctx, 4);
        lw(v0, s5, 2012);
        v0 = slt(a2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015cbc4
        charge(ctx, 7);
        v0 = sll(a2, 2);
        v0 = addu(v0, a2);
        v0 = sll(v0, 2);
        t2 = addu(s5, v0);
        t1 = addiu(t2, 12);
        a3 = a0;
        t0 = a1;
        for (;;) {
            // 0x0015cbe0
            charge(ctx, 7);
            lw(v0, t1, 0);
            t1 = addiu(t1, 4);
            a3 = addiu(a3, -1);
            sw(v0, t0, 0);
            t0 = addiu(t0, 4);
            if (i64(a3) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0015cbfc
        charge(ctx, 4);
        a3 = addiu(a2, 1);
        v0 = addiu(t2, 12);
        for (;;) {
            // 0x0015cde4
            charge(ctx, 4);
            lw(t0, s5, 2012);
            t0 = slt(a3, t0);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0015cc0c
            charge(ctx, 8);
            t0 = sll(a3, 2);
            t0 = addu(t0, a3);
            t0 = sll(t0, 2);
            t0 = addu(s5, t0);
            t0 = addiu(t0, 12);
            t2 = a0;
            t4 = t0;
            t3 = v1;
            for (;;) {
                // 0x0015cc2c
                charge(ctx, 7);
                lw(t1, t4, 0);
                t4 = addiu(t4, 4);
                t2 = addiu(t2, -1);
                sw(t1, t3, 0);
                t3 = addiu(t3, 4);
                if (i64(t2) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0015cc48
            charge(ctx, 4);
            lw(t3, sp, 0xF0);
            t1 = slti(t3, 192);
            if (t1 == 0) {
                // 0x0015cc58
                charge(ctx, 3);
                at = slti(t3, 256);
                if (at == 0) {
                    goto L_0015cd54;
                }
                // 0x0015cc64
                charge(ctx, 4);
                lw(t2, sp, 0xD0);
                t1 = slti(t2, 192);
                if (t1 == 0) {
                    // 0x0015cc74
                    charge(ctx, 3);
                    at = slti(t2, 256);
                    if (at == 0) {
                        goto L_0015ccf0;
                    }
                    // 0x0015cc80
                    charge(ctx, 3);
                    at = slt(t3, t2);
                    if (at != 0) {
                        // 0x0015cc8c
                        charge(ctx, 3);
                        t2 = a0;
                        t4 = v1;
                        t3 = v0;
                        for (;;) {
                            // 0x0015cc98
                            charge(ctx, 7);
                            lw(t1, t4, 0);
                            t4 = addiu(t4, 4);
                            t2 = addiu(t2, -1);
                            sw(t1, t3, 0);
                            t3 = addiu(t3, 4);
                            if (i64(t2) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0015ccb4
                        charge(ctx, 2);
                        t2 = a0;
                        t3 = a1;
                        for (;;) {
                            // 0x0015ccbc
                            charge(ctx, 7);
                            lw(t1, t3, 0);
                            t3 = addiu(t3, 4);
                            t2 = addiu(t2, -1);
                            sw(t1, t0, 0);
                            t0 = addiu(t0, 4);
                            if (i64(t2) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x0015ccd8
                        charge(ctx, 6);
                        lq(t0, sp, 0xF0);
                        lwc1(f0, sp, 0x100);
                        sq(t0, sp, 0xD0);
                        swc1(f0, sp, 0xE0);
                    }
                    goto L_0015cde0;
                }
            L_0015ccf0:
                charge(ctx, 3);
                t2 = a0;
                t4 = v1;
                t3 = v0;
                for (;;) {
                    // 0x0015ccfc
                    charge(ctx, 7);
                    lw(t1, t4, 0);
                    t4 = addiu(t4, 4);
                    t2 = addiu(t2, -1);
                    sw(t1, t3, 0);
                    t3 = addiu(t3, 4);
                    if (i64(t2) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0015cd18
                charge(ctx, 2);
                t2 = a0;
                t3 = a1;
                for (;;) {
                    // 0x0015cd20
                    charge(ctx, 7);
                    lw(t1, t3, 0);
                    t3 = addiu(t3, 4);
                    t2 = addiu(t2, -1);
                    sw(t1, t0, 0);
                    t0 = addiu(t0, 4);
                    if (i64(t2) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0015cd3c
                charge(ctx, 6);
                lq(t0, sp, 0xF0);
                lwc1(f0, sp, 0x100);
                sq(t0, sp, 0xD0);
                swc1(f0, sp, 0xE0);
                goto L_0015cde0;
            }
        L_0015cd54:
            charge(ctx, 4);
            lw(t2, sp, 0xD0);
            t1 = slti(t2, 192);
            if (t1 == 0) {
                // 0x0015cd64
                charge(ctx, 3);
                at = slti(t2, 256);
                if (at == 0) {
                    goto L_0015cd70;
                }
                goto L_0015cde0;
            }
        L_0015cd70:
            charge(ctx, 5);
            lw(t2, sp, 0xD0);
            lw(t1, sp, 0xF0);
            at = slt(t1, t2);
            if (at != 0) {
                // 0x0015cd84
                charge(ctx, 3);
                t2 = a0;
                t4 = v1;
                t3 = v0;
                for (;;) {
                    // 0x0015cd90
                    charge(ctx, 7);
                    lw(t1, t4, 0);
                    t4 = addiu(t4, 4);
                    t2 = addiu(t2, -1);
                    sw(t1, t3, 0);
                    t3 = addiu(t3, 4);
                    if (i64(t2) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0015cdac
                charge(ctx, 2);
                t2 = a0;
                t3 = a1;
                for (;;) {
                    // 0x0015cdb4
                    charge(ctx, 7);
                    lw(t1, t3, 0);
                    t3 = addiu(t3, 4);
                    t2 = addiu(t2, -1);
                    sw(t1, t0, 0);
                    t0 = addiu(t0, 4);
                    if (i64(t2) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0015cdd0
                charge(ctx, 4);
                lq(t0, sp, 0xF0);
                lwc1(f0, sp, 0x100);
                sq(t0, sp, 0xD0);
                swc1(f0, sp, 0xE0);
            }
        L_0015cde0:
            charge(ctx, 1);
            a3 = addiu(a3, 1);
        }
        // 0x0015cdf4
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x0015ce08
    charge(ctx, 16);
    lh(a0, sp, 0xC0);
    jal(ctx, 0x15CE0Cu, gen::fn_sub_175200_00175200);  // [datPersonaSelectSlot]
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
    sp = addiu(sp, 0x110);
    return;
L_0015c920_6:
    charge(ctx, 21);
    v0 = addiu(a0, 20);
    sq(v0, sp, 0xB0);
    lh(a0, a0, 20);
    jal(ctx, 0x15C92Cu, gen::fn_sub_174A90_00174a90);  // [datPersonaGetHeroPersona] (slot)
    s7 = v0;
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x15C940u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    v0 = v0 & 0xFF;
    sq(v0, sp, 0xA0);
    a0 = s7;
    a1 = 1;
    jal(ctx, 0x15C958u, gen::fn_sub_173660_00173660);  // [datPersonaGetTotalStat] (persona, stat)
    v1 = v0 & 0xFF;
    lq(v0, sp, 0xA0);
    at = slt(v1, v0);
    if (at != 0) {
        // 0x0015c974
        charge(ctx, 20);
        v0 = sll(s4, 1);
        a0 = addu(s0, v0);
        v0 = sll(s2, 2);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        v1 = addu(s5, v0);
        lhu(v0, a0, 12);
        sw(v0, fp, 0x0);
        lq(v0, sp, 0xB0);
        sw(s1, v0, 0);
        lhu(v0, s0, 2);
        sw(v0, v1, 16);
        lhu(a0, a0, 12);
        jal(ctx, 0x15C9A8u, gen::fn_sub_17B480_0017b480);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = 2;
        if (v1 == v0) {
            // 0x0015ca54
            charge(ctx, 6);
            v0 = sll(s2, 2);
            v0 = addu(v0, s2);
            v0 = sll(v0, 2);
            v0 = addu(s5, v0);
            sw(zero, v0, 24);
            sw(zero, v0, 28);
        } else {
            // 0x0015c9c4
            charge(ctx, 8);
            a0 = 1;
            lhu(a1, s6, 0);
            jal(ctx, 0x15C9CCu, gen::fn_sub_17B500_0017b500);
            v1 = v0 & 0xFFFF;
            v0 = 2;
            if (v1 == v0) {
                // 0x0015ca24
                charge(ctx, 12);
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                v0 = sll(v0, 2);
                s7 = addu(s5, v0);
                a0 = 1;
                lhu(a1, s6, 0);
                jal(ctx, 0x15CA3Cu, gen::fn_sub_17B5B0_0017b5b0);
                sw(v0, s7, 24);
                sw(zero, s7, 28);
            } else {
                // 0x0015c9e4
                charge(ctx, 3);
                a0 = 1;
                if (v1 == a0) {
                    // 0x0015c9f8
                    charge(ctx, 11);
                    v0 = sll(s2, 2);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    s7 = addu(s5, v0);
                    sw(zero, s7, 24);
                    lhu(a1, s6, 0);
                    jal(ctx, 0x15CA10u, gen::fn_sub_17B5B0_0017b5b0);
                    sw(v0, s7, 28);
                } else {
                    // 0x0015c9f0
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0015ca6c
    charge(ctx, 3);
    a2 = 1;
    goto L_0015ca88;
}

// 0x0015CE50 sub_15CE50 -- 2692 bytes; frame 0x1D0: ra sp+0xB0, s7 sp+0xA0 (sq), s6 sp+0x90 (sq), s5 sp+0x80 (sq), s4 sp+0x70 (sq), s3 sp+0x60 (sq), s2 sp+0x50 (sq), s1 sp+0x40 (sq), s0 sp+0x30 (sq), f31 sp+0x2C, f30 sp+0x28, f29 sp+0x24, f28 sp+0x20, f27 sp+0x1C, f26 sp+0x18, f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [H_Camp_SkillDrawList] (xy, list, alpha): the skill list: the scroll marks (+2012 count), five visible rows from
// +2020 with the element icon (datSkillElementClass), the name (datGetSkillName -> sprintf -> sub_3B32D0) and the cost
// digits (font 1), the cursor row (+2016) highlighted.
void sub_15CE50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25}, f26{ctx, 26}, f27{ctx, 27}, f28{ctx, 28}, f29{ctx, 29}, f30{ctx, 30}, f31{ctx, 31};
    // 0x0015ce50
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1D0);
    sd(ra, sp, 0xB0);
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
    sd(a0, sp, 0xC8);
    mov_s(f31, f12);
    s2 = a1;
    s1 = a2;
    v1 = 255;
    s3 = subu(v1, s1);
    lw(v1, a1, 2012);
    if (v1 != 0) {
        // 0x0015cecc
        charge(ctx, 51);
        lwc1(f1, sp, 0xCC);
        v0 = 0x40C00000;  // 6.0f
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        lw(v1, s2, 2016);
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
        lwc1(f0, sp, 0xC8);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 6;
        mov_s(f14, f31);
        jal(ctx, 0x15CF30u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v1, s2, 2016);
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
        lwc1(f0, sp, 0xC8);
        add_s(f12, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 7;
        mov_s(f14, f31);
        jal(ctx, 0x15CF90u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0015cf98
    charge(ctx, 61);
    s0 = 0;
    lwc1(f20, sp, 0xCC);
    v1 = 0x40000000;  // 2.0f
    mtc1(v1, f0);
    add_s(f30, f0, f20);
    v1 = 0x41700000;  // 15.0f
    mtc1(v1, f0);
    lwc1(f2, sp, 0xC8);
    add_s(f29, f0, f2);
    v1 = si(-256);
    s6 = s3 | v1;
    cvt_w_s(f0, f20);
    cvt_s_w(f1, f0);
    v1 = 0x3F800000;  // 1.0f
    mtc1(v1, f0);
    add_s(f28, f0, f1);
    cvt_w_s(f0, f2);
    cvt_s_w(f1, f0);
    v1 = 0x425C0000;  // 55.0f
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(s7, f0);
    v1 = 0x41980000;  // 19.0f
    mtc1(v1, f0);
    add_s(f27, f0, f20);
    v1 = 0x43790000;  // 249.0f
    mtc1(v1, f0);
    add_s(f26, f0, f2);
    v1 = 0x41800000;  // 16.0f
    mtc1(v1, f0);
    add_s(f25, f0, f20);
    v1 = 0x43700000;  // 240.0f
    mtc1(v1, f0);
    add_s(f24, f0, f2);
    v1 = 0x43800000;  // 256.0f
    mtc1(v1, f0);
    add_s(f23, f0, f2);
    v1 = 0x43880000;  // 272.0f
    mtc1(v1, f0);
    add_s(f0, f0, f2);
    swc1(f0, sp, 0xC4);
    v1 = 0x41880000;  // 17.0f
    mtc1(v1, f0);
    add_s(f22, f0, f20);
    v1 = 0x43900000;  // 288.0f
    mtc1(v1, f0);
    add_s(f21, f0, f2);
    for (;;) {
        // 0x0015d6d8
        charge(ctx, 3);
        v1 = slti(s0, 5);
        if (v1 != 0) {
            backedge(ctx);
            // 0x0015d08c
            charge(ctx, 6);
            lw(v1, s2, 2020);
            v1 = addu(s0, v1);
            lw(a0, s2, 2012);
            at = slt(v1, a0);
            if (at != 0) {
                // 0x0015d0a4
                charge(ctx, 3);
                lw(v0, s2, 2016);
                if (s0 != v0) {
                    // 0x0015d3c0
                    charge(ctx, 72);
                    v0 = 0x830000;
                    lw(s4, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    v0 = sll(s0, 1);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s0);
                    s3 = sll(v0, 1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x15D3F0u, gen::fn_sub_17D2E0_0017d2e0);  // [datSkillElementClass]
                    a2 = addiu(v0, 47);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f30, f0);
                    a3 = s1 & 0xFF;
                    a0 = s5;
                    a1 = s4;
                    mov_s(f12, f29);
                    t0 = 32;
                    t1 = 67;
                    t2 = 120;
                    mov_s(f14, f31);
                    jal(ctx, 0x15D42Cu, gen::fn_sub_115BC0_00115bc0);  // draw sprite $a2 of file $a1 at ($f12, $f13), alpha $a3, tinted ($t0, $t1, $t2)
                    lw(v0, s2, 2020);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x15D450u, gen::fn_datGetSkillName_0030bb40);
                    a0 = addiu(sp, 0xD0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x15D464u, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f28, f0);
                    v0 = 0x41600000;  // 14.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f31);
                    a2 = s6;
                    a3 = 10;
                    t0 = 1;
                    t1 = addiu(sp, 0xD0);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x15D4B4u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s2, 2020);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lw(s4, v0, 24);
                    if (s4 == 0) {
                        // 0x0015d4e0
                        charge(ctx, 1);
                        lw(s4, v0, 28);
                    }
                    // 0x0015d4e4
                    charge(ctx, 2);
                    if (s4 != 0) {
                        // 0x0015d528
                        charge(ctx, 4);
                        v1 = 0;
                        v0 = slti(s4, 100);
                        if (v0 == 0) {
                            // 0x0015d538
                            charge(ctx, 22);
                            a0 = 2;
                            jal(ctx, 0x15D53Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f25, f0);
                            v1 = 100;
                            div(s4, v1);
                            mflo(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f24);
                            mov_s(f14, f31);
                            jal(ctx, 0x15D578u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            v1 = 1;
                            v0 = 100;
                            div(s4, v0);
                            mfhi(s4);
                        }
                        // 0x0015d590
                        charge(ctx, 3);
                        at = slti(s4, 10);
                        if (at != 0) {
                            // 0x0015d59c
                            charge(ctx, 2);
                            if (v1 != 0) {
                                goto L_0015d5a4;
                            }
                            goto L_0015d5f8;
                        }
                    L_0015d5a4:
                        charge(ctx, 21);
                        a0 = 2;
                        jal(ctx, 0x15D5A8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f25, f0);
                        v1 = 10;
                        div(s4, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        a3 = s1 & 0xFF;
                        a0 = s5;
                        a1 = v0;
                        mov_s(f12, f23);
                        mov_s(f14, f31);
                        jal(ctx, 0x15D5E4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = 10;
                        div(s4, v0);
                        mfhi(s4);
                    L_0015d5f8:
                        charge(ctx, 24);
                        a0 = 2;
                        jal(ctx, 0x15D5FCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f25, f0);
                        a2 = addiu(s4, 11);
                        a3 = s1 & 0xFF;
                        a0 = s5;
                        a1 = v0;
                        lwc1(f12, sp, 0xC4);
                        mov_s(f14, f31);
                        jal(ctx, 0x15D62Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lw(v1, s2, 2020);
                        a0 = addu(v1, s0);
                        v1 = sll(a0, 2);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        a0 = addu(s2, v1);
                        lw(v1, a0, 24);
                        if (v1 == 0) {
                            // 0x0015d694
                            charge(ctx, 3);
                            lw(v1, a0, 28);
                            if (v1 != 0) {
                                // 0x0015d6a0
                                charge(ctx, 13);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f22, f0);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 3;
                                mov_s(f12, f21);
                                mov_s(f14, f31);
                                jal(ctx, 0x15D6CCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                        } else {
                            // 0x0015d658
                            charge(ctx, 15);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f22, f0);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 5;
                            mov_s(f12, f21);
                            mov_s(f14, f31);
                            jal(ctx, 0x15D684u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x0015d4ec
                        charge(ctx, 15);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f27, f0);
                        a3 = s1 & 0xFF;
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                        a2 = 16;
                        mov_s(f12, f26);
                        mov_s(f14, f31);
                        jal(ctx, 0x15D518u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                } else {
                    // 0x0015d0b0
                    charge(ctx, 69);
                    v0 = 0x830000;
                    lw(s4, v0, spr::camp(0));  // 0x833B70: camp sprite file 0
                    v0 = sll(s0, 1);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s0);
                    s3 = sll(v0, 1);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x15D0E0u, gen::fn_sub_17D2E0_0017d2e0);  // [datSkillElementClass]
                    a2 = addiu(v0, 32);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f13, f30, f0);
                    a3 = s1 & 0xFF;
                    a0 = s5;
                    a1 = s4;
                    mov_s(f12, f29);
                    mov_s(f14, f31);
                    jal(ctx, 0x15D110u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    lw(v0, s2, 2020);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lhu(a0, v0, 12);
                    jal(ctx, 0x15D134u, gen::fn_datGetSkillName_0030bb40);
                    a0 = addiu(sp, 0xD0);
                    a1 = addiu(gp, -30340);  // "%s"
                    a2 = v0;
                    jal(ctx, 0x15D148u, gen::fn_sprintf_00523ac8);
                    mtc1(s3, f0);
                    cvt_s_w(f0, f0);
                    add_s(f1, f28, f0);
                    v0 = 0x41600000;  // 14.0f
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    cvt_w_s(f0, f0);
                    mfc1(a1, f0);
                    a0 = s7;
                    mov_s(f12, f31);
                    a2 = s6;
                    a3 = 6;
                    t0 = 1;
                    t1 = addiu(sp, 0xD0);
                    t2 = 16;
                    t3 = 120;
                    jal(ctx, 0x15D198u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                    lw(v0, s2, 2020);
                    v1 = addu(v0, s0);
                    v0 = sll(v1, 2);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s2, v0);
                    lw(s4, v0, 24);
                    if (s4 == 0) {
                        // 0x0015d1c4
                        charge(ctx, 1);
                        lw(s4, v0, 28);
                    }
                    // 0x0015d1c8
                    charge(ctx, 2);
                    if (s4 != 0) {
                        // 0x0015d20c
                        charge(ctx, 4);
                        v1 = 0;
                        v0 = slti(s4, 100);
                        if (v0 == 0) {
                            // 0x0015d21c
                            charge(ctx, 22);
                            a0 = 1;
                            jal(ctx, 0x15D220u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f25, f0);
                            v1 = 100;
                            div(s4, v1);
                            mflo(v1);
                            a2 = addiu(v1, 11);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            a1 = v0;
                            mov_s(f12, f24);
                            mov_s(f14, f31);
                            jal(ctx, 0x15D25Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            v1 = 1;
                            v0 = 100;
                            div(s4, v0);
                            mfhi(s4);
                        }
                        // 0x0015d274
                        charge(ctx, 3);
                        at = slti(s4, 10);
                        if (at != 0) {
                            // 0x0015d280
                            charge(ctx, 2);
                            if (v1 != 0) {
                                goto L_0015d288;
                            }
                            goto L_0015d2dc;
                        }
                    L_0015d288:
                        charge(ctx, 21);
                        a0 = 1;
                        jal(ctx, 0x15D28Cu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f25, f0);
                        v1 = 10;
                        div(s4, v1);
                        mflo(v1);
                        a2 = addiu(v1, 11);
                        a3 = s1 & 0xFF;
                        a0 = s5;
                        a1 = v0;
                        mov_s(f12, f23);
                        mov_s(f14, f31);
                        jal(ctx, 0x15D2C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        v0 = 10;
                        div(s4, v0);
                        mfhi(s4);
                    L_0015d2dc:
                        charge(ctx, 24);
                        a0 = 1;
                        jal(ctx, 0x15D2E0u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f25, f0);
                        a2 = addiu(s4, 11);
                        a3 = s1 & 0xFF;
                        a0 = s5;
                        a1 = v0;
                        lwc1(f12, sp, 0xC4);
                        mov_s(f14, f31);
                        jal(ctx, 0x15D310u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        lw(v1, s2, 2020);
                        a0 = addu(v1, s0);
                        v1 = sll(a0, 2);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        a0 = addu(s2, v1);
                        lw(v1, a0, 24);
                        if (v1 == 0) {
                            // 0x0015d378
                            charge(ctx, 3);
                            lw(v1, a0, 28);
                            if (v1 != 0) {
                                // 0x0015d384
                                charge(ctx, 15);
                                mtc1(s3, f0);
                                cvt_s_w(f0, f0);
                                add_s(f13, f22, f0);
                                a3 = s1 & 0xFF;
                                a0 = s5;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                a2 = 2;
                                mov_s(f12, f21);
                                mov_s(f14, f31);
                                jal(ctx, 0x15D3B0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                        } else {
                            // 0x0015d33c
                            charge(ctx, 15);
                            mtc1(s3, f0);
                            cvt_s_w(f0, f0);
                            add_s(f13, f22, f0);
                            a3 = s1 & 0xFF;
                            a0 = s5;
                            v0 = 0x830000;
                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                            a2 = 4;
                            mov_s(f12, f21);
                            mov_s(f14, f31);
                            jal(ctx, 0x15D368u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        }
                    } else {
                        // 0x0015d1d0
                        charge(ctx, 15);
                        mtc1(s3, f0);
                        cvt_s_w(f0, f0);
                        add_s(f13, f27, f0);
                        a3 = s1 & 0xFF;
                        a0 = s5;
                        v0 = 0x830000;
                        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                        a2 = 17;
                        mov_s(f12, f26);
                        mov_s(f14, f31);
                        jal(ctx, 0x15D1FCu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    }
                }
                // 0x0015d6d4
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
        }
        break;
    }
    // 0x0015d6e4
    charge(ctx, 10);
    lw(a0, s2, 2016);
    lw(v1, s2, 2020);
    a0 = addu(v1, a0);
    v1 = sll(a0, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, s2);
    lw(t2, v1, 12);
    if (t2 != 0) {
        // 0x0015d70c
        charge(ctx, 27);
        v0 = 0x42580000;  // 54.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xC8);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v0 = 0x43520000;  // 210.0f
        mtc1(v0, f0);
        add_s(f1, f0, f20);
        v0 = 0x41F00000;  // 30.0f
        mtc1(v0, f0);
        sub_s(f1, f1, f0);
        v0 = 0x41A00000;  // 20.0f
        mtc1(v0, f0);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        mov_s(f12, f31);
        a2 = si(-1);
        a3 = 1;
        t0 = 10;
        t1 = 3;
        jal(ctx, 0x15D770u, gen::fn_sub_3C7E20_003c7e20);  // a message text
    }
    // 0x0015d778
    charge(ctx, 3);
    lw(v1, s2, 2012);
    if (v1 != 0) {
        // 0x0015d784
        charge(ctx, 29);
        v0 = 0x44130000;  // 588.0f
        mtc1(v0, f1);
        lwc1(f0, sp, 0xC8);
        add_s(f1, f1, f0);
        v0 = 0x43770000;  // 247.0f
        mtc1(v0, f0);
        sub_s(f21, f1, f0);
        v0 = 0x41F00000;  // 30.0f
        mtc1(v0, f0);
        add_s(f1, f0, f20);
        v0 = 0x41C00000;  // 24.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 8;
        mov_s(f12, f21);
        mov_s(f14, f31);
        jal(ctx, 0x15D7E0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lw(v0, s2, 2012);
        a0 = addiu(v0, -5);
        if (i64(a0) <= 0) {
            // 0x0015d81c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0015d7f8
            charge(ctx, 9);
            lw(v1, s2, 2020);
            v0 = 89;
            mult(v0, v1, v0);
            div(v0, a0);
            mflo(v0);
        }
        // 0x0015d820
        charge(ctx, 21);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x42080000;  // 34.0f
        mtc1(v0, f0);
        add_s(f0, f0, f20);
        add_s(f1, f0, f1);
        v0 = 0x41C00000;  // 24.0f
        mtc1(v0, f0);
        sub_s(f13, f1, f0);
        a3 = s1 & 0xFF;
        a0 = s5;
        v0 = 0x830000;
        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
        a2 = 13;
        mov_s(f12, f21);
        mov_s(f14, f31);
        jal(ctx, 0x15D86Cu, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    }
    // 0x0015d874 (the shared epilogue, written out on this path)
    charge(ctx, 24);
    ld(ra, sp, 0xB0);
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
    sp = addiu(sp, 0x1D0);
}

// 0x0015DA70 sub_15DA70 -- 1760 bytes; frame 0xC0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_SkillOpenLayout] (skill work): the skill page's slide-in on its 60 tweens (+56): the panels from 50 px right
// over frames 6..13, the target rows (85 px apart).
void sub_15DA70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0015da70
    enter(ctx, 123);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x41E80000;  // 29.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41B00000;  // 22.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0xB8);
    lwc1(f1, sp, 0xB8);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xB8);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, a0, 56);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB8);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15DAF8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    sw(zero, sp, 0xB0);
    sw(zero, sp, 0xB4);
    v0 = 6;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, s2, skl::kTweens);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xB0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15DB40u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, skl::kTweens);
    sw(zero, v0, 140);
    v0 = 447;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB0);
    v0 = 411;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    ld(v0, sp, 0xB0);
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
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15DBD4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0xB0);
    v0 = 0x41C00000;  // 24.0f
    sw(v0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0x70);
    lwc1(f1, sp, 0x70);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x70);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x70);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15DC48u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0015e01c
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015dc5c
        charge(ctx, 4);
        lw(v0, s2, skl::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x0015dfb0
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 752);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 820);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 888);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 956);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1092);
        } else {
            // 0x0015dc6c
            charge(ctx, 209);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42280000;  // 42.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x78);
            lwc1(f1, sp, 0x78);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x78);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 1);
            v0 = sll(v1, 4);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t0, sp, 0x78);
            ld(t1, sp, 0xB0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15DD28u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x80);
            lwc1(f1, sp, 0x80);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x80);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 11);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
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
            jal(ctx, 0x15DDC4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x88);
            lwc1(f1, sp, 0x88);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x88);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 12);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
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
            jal(ctx, 0x15DE54u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xB0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x90);
            lwc1(f1, sp, 0x90);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x90);
            v0 = 6;
            sd(v0, sp, 0x0);
            v0 = 13;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 13);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
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
            jal(ctx, 0x15DEE4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xB0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0xB4);
            ld(v0, sp, 0xB0);
            sd(v0, sp, 0x98);
            lwc1(f1, sp, 0x98);
            v0 = 0x42480000;  // 50.0f
            mtc1(v0, f0);
            sub_s(f0, f1, f0);
            swc1(f0, sp, 0x98);
            v0 = 3;
            sd(v0, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 14);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
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
            jal(ctx, 0x15DF74u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1092);
        }
        // 0x0015e018
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0015e028
    charge(ctx, 74);
    v0 = 0x41880000;  // 17.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    ld(v0, sp, 0xB0);
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
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3400);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E0A0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, skl::kTweens);
    sw(zero, v0, 3472);
    v0 = 0x43F40000;  // 488.0f
    sw(v0, sp, 0xB0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xB4);
    ld(v0, sp, 0xB0);
    sd(v0, sp, 0xA8);
    lwc1(f1, sp, 0xA8);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xA8);
    v0 = 8;
    sd(v0, sp, 0x0);
    v0 = 13;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3536);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA8);
    ld(t1, sp, 0xB0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E128u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xC0);
}

// 0x0015E150 sub_15E150 -- 1424 bytes; frame 0x70: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_SkillCloseLayout] (skill work): the skill page's slide-out.
void sub_15E150(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0015e150
    enter(ctx, 95);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x41E80000;  // 29.0f
    sw(v0, sp, 0x60);
    v0 = 0x41B00000;  // 22.0f
    sw(v0, sp, 0x64);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, a0, 56);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E1B4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    sw(zero, sp, 0x60);
    sw(zero, sp, 0x64);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    lw(a0, s2, skl::kTweens);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E1F8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, skl::kTweens);
    sw(zero, v0, 140);
    v0 = 447;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x60);
    v0 = 411;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x64);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E268u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0x60);
    v0 = 0x41C00000;  // 24.0f
    sw(v0, sp, 0x64);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E2B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0015e5d8
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015e2cc
        charge(ctx, 4);
        lw(v0, s2, skl::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x0015e56c
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 752);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 820);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 888);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 956);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1092);
        } else {
            // 0x0015e2dc
            charge(ctx, 164);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42280000;  // 42.0f
            mtc1(v0, f0);
            add_s(f20, f0, f1);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x60);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x64);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 1);
            v0 = sll(v1, 4);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x60);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15E374u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x60);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x64);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 11);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x60);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15E3ECu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x60);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x64);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 12);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x60);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15E458u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0x60);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x64);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 13);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x60);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15E4C4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0x60);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x64);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 14);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x60);
            t1 = t0;
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15E530u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1092);
        }
        // 0x0015e5d4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0015e5e4
    charge(ctx, 63);
    v0 = 0x41880000;  // 17.0f
    sw(v0, sp, 0x60);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x64);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3400);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x60);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E638u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    lw(v0, s2, skl::kTweens);
    sw(zero, v0, 3472);
    v0 = 0x43F40000;  // 488.0f
    mtc1(v0, f1);
    sw(v0, sp, 0x60);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x64);
    ld(t0, sp, 0x60);
    sd(t0, sp, 0x68);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x60);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3536);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x60);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E6B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0015E6E0 sub_15E6E0 -- 1880 bytes; frame 0xB0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f21 sp+0x14, f20 sp+0x10
// [H_Camp_SkillTargetOpenLayout] (skill work): the panels for the target choice.
void sub_15E6E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0015e6e0
    enter(ctx, 127);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x41E80000;  // 29.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xA0);
    v0 = 0x41B00000;  // 22.0f
    sw(v0, sp, 0xA4);
    ld(t0, sp, 0xA0);
    sd(t0, sp, 0xA8);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    v0 = 3;
    sd(v0, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, a0, 56);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E768u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x429A0000;  // 77.0f
    sw(v0, sp, 0xA0);
    v0 = 0x41B00000;  // 22.0f
    sw(v0, sp, 0xA4);
    ld(v0, sp, 0xA0);
    sd(v0, sp, 0x68);
    lwc1(f1, sp, 0x68);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    v0 = 3;
    sd(v0, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E7DCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 447;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x68);
    v0 = 411;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x6C);
    v0 = 0x43FC0000;  // 504.0f
    sw(v0, sp, 0xA0);
    v0 = 0x43C90000;  // 402.0f
    sw(v0, sp, 0xA4);
    v0 = 3;
    sd(v0, sp, 0x0);
    v0 = 7;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E858u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43770000;  // 247.0f
    sw(v0, sp, 0x68);
    v0 = 0x41C00000;  // 24.0f
    sw(v0, sp, 0x6C);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0xA0);
    lwc1(f1, sp, 0xA0);
    v0 = 0x42040000;  // 33.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15E8C8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0015ecf4
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015e8dc
        charge(ctx, 4);
        lw(v0, s2, skl::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x0015ec88
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 752);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 820);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 888);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 956);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1092);
        } else {
            // 0x0015e8ec
            charge(ctx, 14);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            a0 = addu(v1, v0);
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42280000;  // 42.0f
            mtc1(v0, f0);
            add_s(f21, f0, f1);
            lw(v1, s2, skl::kTargetCursor);
            if (s1 != v1) {
                // 0x0015e924
                charge(ctx, 3);
                v0 = si(-2);
                if (v1 == v0) {
                    goto L_0015e930;
                }
                // 0x0015e9c8
                charge(ctx, 6);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f20);
                v1 = sll(a0, 3);
                lw(v0, s2, skl::kTweens);
                v0 = addu(v0, v1);
                sw(zero, v0, 1092);
                goto L_0015e9e0;
            }
        L_0015e930:
            charge(ctx, 38);
            v0 = 0x42400000;  // 48.0f
            mtc1(v0, f20);
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xA0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(t0, sp, 0xA0);
            sd(t0, sp, 0x70);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            v0 = sll(v0, 1);
            v1 = addiu(v0, 16);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 1;
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15E9B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        L_0015e9e0:
            charge(ctx, 170);
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xA0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(t0, sp, 0xA0);
            sd(t0, sp, 0x78);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 1);
            v0 = sll(v1, 4);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15EA5Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xA0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(t0, sp, 0xA0);
            sd(t0, sp, 0x80);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xA0);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 11);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15EAE4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xA0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(t0, sp, 0xA0);
            sd(t0, sp, 0x88);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 12);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15EB60u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xA0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(t0, sp, 0xA0);
            sd(t0, sp, 0x90);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 13);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15EBDCu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            mtc1(v0, f1);
            sw(v0, sp, 0xA0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(t0, sp, 0xA0);
            sd(t0, sp, 0x98);
            add_s(f0, f1, f20);
            swc1(f0, sp, 0xA0);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 14);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15EC58u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
        }
        // 0x0015ecf0
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0015ed00
    charge(ctx, 78);
    v0 = 0x41880000;  // 17.0f
    sw(v0, sp, 0xA0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3400);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xA0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15ED54u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41880000;  // 17.0f
    sw(v0, sp, 0xA0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3468);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15EDB0u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F40000;  // 488.0f
    sw(v0, sp, 0xA0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3536);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0xA0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15EE0Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f21, sp, 0x14);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xB0);
}

// 0x0015EE40 sub_15EE40 -- 1244 bytes; frame 0xC0: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f22 sp+0x18, f21 sp+0x14, f20 sp+0x10
// [H_Camp_SkillMoveTargetCursor] (skill work, previous): moves the target highlight (rows 85 px apart from y 42) from
// `previous` to the cursor (+24).
void sub_15EE40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0015ee40
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
        // 0x0015f2e0
        charge(ctx, 3);
        v1 = slti(s2, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015ee7c
        charge(ctx, 4);
        lw(v1, s4, skl::kTargetCount);
        at = slt(s2, v1);
        if (at != 0) {
            // 0x0015ee8c
            charge(ctx, 14);
            v1 = sll(s2, 4);
            a0 = addu(v1, s2);
            v1 = sll(a0, 2);
            a1 = addu(a0, v1);
            mtc1(a1, f0);
            cvt_s_w(f1, f0);
            v1 = 0x42280000;  // 42.0f
            mtc1(v1, f0);
            add_s(f22, f0, f1);
            lw(v1, s4, skl::kTargetCursor);
            if (s2 == v1) {
                // 0x0015eec4
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
                v1 = addiu(v0, 16);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v1 = sll(v0, 2);
                lw(v0, s4, skl::kTweens);
                a0 = addu(v0, v1);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 1;
                ld(t0, sp, 0xB8);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x15EF64u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                goto L_0015f01c;
            }
            // 0x0015ef74
            charge(ctx, 2);
            if (s2 == s3) {
                // 0x0015ef7c
                charge(ctx, 40);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f21);
                lw(a0, s4, skl::kTweens);
                v0 = sll(a1, 3);
                v0 = addu(a0, v0);
                lwc1(f1, v0, 1144);
                lwc1(f0, v0, 1148);
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
                v1 = addiu(v0, 16);
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
                jal(ctx, 0x15F014u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            L_0015f01c:
                charge(ctx, 176);
                lw(a0, s4, skl::kTweens);
                v0 = sll(s2, 4);
                v1 = addu(v0, s2);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                s1 = sll(v0, 3);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 736);
                lwc1(f0, v0, 740);
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
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s2, 1);
                v0 = sll(v1, 4);
                v1 = addu(v0, v1);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                a0 = addu(a0, v0);
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0x88);
                ld(t1, sp, 0xB0);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x15F0B8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, skl::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 804);
                lwc1(f0, v0, 808);
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
                v0 = sll(s2, 2);
                v0 = addu(v0, s2);
                s0 = sll(v0, 1);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 11);
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
                jal(ctx, 0x15F14Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, skl::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 872);
                lwc1(f0, v0, 876);
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
                v1 = addiu(s0, 12);
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
                jal(ctx, 0x15F1D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, skl::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 940);
                lwc1(f0, v0, 944);
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
                v1 = addiu(s0, 13);
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
                jal(ctx, 0x15F25Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
                lw(a0, s4, skl::kTweens);
                v0 = addu(a0, s1);
                lwc1(f1, v0, 1008);
                lwc1(f0, v0, 1012);
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
                v1 = addiu(s0, 14);
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
                jal(ctx, 0x15F2D4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            }
        }
        // 0x0015f2dc
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0015f2ec
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

// 0x0015F320 sub_15F320 -- 1896 bytes; frame 0xB0: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f21 sp+0x14, f20 sp+0x10
// [H_Camp_SkillTargetCloseLayout] (skill work): back from the target choice.
void sub_15F320(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0015f320
    enter(ctx, 125);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    s2 = a0;
    v0 = 0x41E80000;  // 29.0f
    sw(v0, sp, 0xA0);
    v0 = 0x41B00000;  // 22.0f
    sw(v0, sp, 0xA4);
    ld(v0, sp, 0xA0);
    sd(v0, sp, 0xA8);
    lwc1(f1, sp, 0xA8);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0xA8);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, a0, 56);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA8);
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15F3A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x429A0000;  // 77.0f
    mtc1(v0, f1);
    sw(v0, sp, 0xA0);
    v0 = 0x41B00000;  // 22.0f
    sw(v0, sp, 0xA4);
    ld(t0, sp, 0xA0);
    sd(t0, sp, 0x68);
    v0 = 0x42480000;  // 50.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15F414u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 447;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA0);
    v0 = 411;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    v0 = 0x43FC0000;  // 504.0f
    sw(v0, sp, 0x68);
    v0 = 0x43C90000;  // 402.0f
    sw(v0, sp, 0x6C);
    v0 = 3;
    sd(v0, sp, 0x0);
    v0 = 7;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15F490u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x438C0000;  // 280.0f
    sw(v0, sp, 0x68);
    v0 = 0x41C00000;  // 24.0f
    sw(v0, sp, 0x6C);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0xA0);
    lwc1(f1, sp, 0xA0);
    v0 = 0x42040000;  // 33.0f
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xA0);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x68);
    ld(t1, sp, 0xA0);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15F500u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    s1 = 0;
    for (;;) {
        // 0x0015f944
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0015f514
        charge(ctx, 4);
        lw(v0, s2, skl::kTargetCount);
        at = slt(s1, v0);
        if (at == 0) {
            // 0x0015f8d8
            charge(ctx, 26);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 684);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 752);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 820);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 888);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 956);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1092);
        } else {
            // 0x0015f524
            charge(ctx, 14);
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            a0 = addu(v1, v0);
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x42280000;  // 42.0f
            mtc1(v0, f0);
            add_s(f21, f0, f1);
            lw(v1, s2, skl::kTargetCursor);
            if (s1 != v1) {
                // 0x0015f55c
                charge(ctx, 3);
                v0 = si(-2);
                if (v1 == v0) {
                    goto L_0015f568;
                }
                // 0x0015f604
                charge(ctx, 6);
                v0 = 0x41D80000;  // 27.0f
                mtc1(v0, f20);
                v1 = sll(a0, 3);
                lw(v0, s2, skl::kTweens);
                v0 = addu(v0, v1);
                sw(zero, v0, 1092);
                goto L_0015f61c;
            }
        L_0015f568:
            charge(ctx, 39);
            v0 = 0x42400000;  // 48.0f
            mtc1(v0, f20);
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xA0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(v0, sp, 0xA0);
            sd(v0, sp, 0x70);
            lwc1(f0, sp, 0x70);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x70);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            v0 = sll(v0, 1);
            v1 = addiu(v0, 16);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = a2;
            ld(t0, sp, 0x70);
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15F5F4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
        L_0015f61c:
            charge(ctx, 175);
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xA0);
            v0 = 0x41000000;  // 8.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(v0, sp, 0xA0);
            sd(v0, sp, 0x78);
            lwc1(f0, sp, 0x78);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x78);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s1, 1);
            v0 = sll(v1, 4);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x78);
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15F69Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xA0);
            v0 = 0x41F80000;  // 31.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(v0, sp, 0xA0);
            sd(v0, sp, 0x80);
            lwc1(f0, sp, 0x80);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x80);
            v0 = sll(s1, 2);
            v0 = addu(v0, s1);
            s0 = sll(v0, 1);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 11);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x80);
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15F728u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xA0);
            v0 = 0x42340000;  // 45.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(v0, sp, 0xA0);
            sd(v0, sp, 0x88);
            lwc1(f0, sp, 0x88);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x88);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 12);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x88);
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15F7A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x42820000;  // 65.0f
            sw(v0, sp, 0xA0);
            v0 = 0x42800000;  // 64.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(v0, sp, 0xA0);
            sd(v0, sp, 0x90);
            lwc1(f0, sp, 0x90);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x90);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 13);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x90);
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15F828u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = 0x41600000;  // 14.0f
            sw(v0, sp, 0xA0);
            v0 = 0x40000000;  // 2.0f
            mtc1(v0, f0);
            add_s(f0, f0, f21);
            swc1(f0, sp, 0xA4);
            ld(v0, sp, 0xA0);
            sd(v0, sp, 0x98);
            lwc1(f0, sp, 0x98);
            add_s(f0, f0, f20);
            swc1(f0, sp, 0x98);
            sd(zero, sp, 0x0);
            v0 = 10;
            sd(v0, sp, 0x8);
            v1 = addiu(s0, 14);
            v0 = sll(v1, 4);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            lw(v0, s2, skl::kTweens);
            a0 = addu(v0, v1);
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f12);
            a1 = 0;
            a2 = 2;
            a3 = 0;
            ld(t0, sp, 0x98);
            ld(t1, sp, 0xA0);
            t2 = 0;
            t3 = 0;
            jal(ctx, 0x15F8A8u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
            v0 = sll(s1, 4);
            v1 = addu(v0, s1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 3);
            lw(v0, s2, skl::kTweens);
            v0 = addu(v0, v1);
            sw(zero, v0, 1024);
        }
        // 0x0015f940
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0015f950
    charge(ctx, 78);
    v0 = 0x41880000;  // 17.0f
    sw(v0, sp, 0xA0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3400);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0xA0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15F9A4u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x41880000;  // 17.0f
    sw(v0, sp, 0xA0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3468);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0xA0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15FA00u, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    v0 = 0x43F40000;  // 488.0f
    sw(v0, sp, 0xA0);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0xA4);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s2, skl::kTweens);
    v0 = 0x42C80000;  // 100.0f
    mtc1(v0, f12);
    a0 = addiu(v1, 3536);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0xA0);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x15FA5Cu, gen::fn_sub_18BC10_0018bc10);  // [H_Camp_TweenStart] (record, kind, mode, curve, from, to, a, b, z, first, last)
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f21, sp, 0x14);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0xB0);
}

// 0x0015FA90 sub_15FA90 -- 3428 bytes; frame 0x160: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SkillDrawElement] (tween, element, skill work): one tween element of the skill page: 52 / 51 / 50 frames, the
// list (sub_15CE50), the ribbon (sub_15D8E0), the caster's and the targets' panels (name, HP / SP digits and gauges,
// condition).
void sub_15FA90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0015fa90
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    v1 = 52;
    if (a1 == v1) {
        // 0x00160770
        charge(ctx, 24);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 3;
        lwc1(f12, s1, tw::kX);
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x160790u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        lwc1(f1, s1, tw::kX);
        v0 = 0x42920000;  // 73.0f
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        lbu(a3, s1, tw::kAlpha);
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, spr::camp(12));  // 0x833BA0: camp sprite file 12
        a2 = 1;
        lwc1(f13, s1, tw::kY);
        lwc1(f14, s1, tw::kZ);
        jal(ctx, 0x1607C8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
    } else {
        // 0x0015fabc
        charge(ctx, 3);
        v1 = 51;
        if (a1 == v1) {
            // 0x00160708
            charge(ctx, 26);
            lbu(a3, s1, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 0;
            lwc1(f12, s1, tw::kX);
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x160728u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s1, tw::kX);
            v0 = 0x41800000;  // 16.0f
            mtc1(v0, f0);
            add_s(f12, f0, f1);
            lbu(a3, s1, tw::kAlpha);
            a0 = s0;
            v0 = 0x830000;
            lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
            a2 = 2;
            lwc1(f13, s1, tw::kY);
            lwc1(f14, s1, tw::kZ);
            jal(ctx, 0x160760u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
        } else {
            // 0x0015fac8
            charge(ctx, 3);
            v1 = 50;
            if (a1 == v1) {
                // 0x001606a0
                charge(ctx, 26);
                lbu(a3, s1, tw::kAlpha);
                a0 = s0;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
                a2 = 0;
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1606C0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                lwc1(f1, s1, tw::kX);
                v0 = 0x41800000;  // 16.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                lbu(a3, s1, tw::kAlpha);
                a0 = s0;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
                a2 = 1;
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x1606F8u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            } else {
                // 0x0015fad4
                charge(ctx, 3);
                v1 = 46;
                if (a1 != v1) {
                    // 0x0015fae0
                    charge(ctx, 3);
                    v1 = 36;
                    if (a1 == v1) {
                        goto L_00160670;
                    }
                    // 0x0015faec
                    charge(ctx, 3);
                    v1 = 26;
                    if (a1 == v1) {
                        goto L_00160670;
                    }
                    // 0x0015faf8
                    charge(ctx, 3);
                    v1 = 16;
                    if (a1 == v1) {
                        goto L_00160670;
                    }
                    // 0x0015fb04
                    charge(ctx, 3);
                    v1 = 45;
                    if (a1 != v1) {
                        // 0x0015fb10
                        charge(ctx, 3);
                        v1 = 35;
                        if (a1 == v1) {
                            goto L_00160640;
                        }
                        // 0x0015fb1c
                        charge(ctx, 3);
                        v1 = 25;
                        if (a1 == v1) {
                            goto L_00160640;
                        }
                        // 0x0015fb28
                        charge(ctx, 3);
                        v1 = 15;
                        if (a1 == v1) {
                            goto L_00160640;
                        }
                        // 0x0015fb34
                        charge(ctx, 3);
                        v1 = 44;
                        if (a1 != v1) {
                            // 0x0015fb40
                            charge(ctx, 3);
                            v1 = 34;
                            if (a1 == v1) {
                                goto L_00160610;
                            }
                            // 0x0015fb4c
                            charge(ctx, 3);
                            v1 = 24;
                            if (a1 == v1) {
                                goto L_00160610;
                            }
                            // 0x0015fb58
                            charge(ctx, 3);
                            v1 = 14;
                            if (a1 == v1) {
                                goto L_00160610;
                            }
                            // 0x0015fb64
                            charge(ctx, 3);
                            a0 = 43;
                            if (a1 != a0) {
                                // 0x0015fb70
                                charge(ctx, 3);
                                a0 = 33;
                                if (a1 == a0) {
                                    goto L_00160434;
                                }
                                // 0x0015fb7c
                                charge(ctx, 3);
                                a0 = 23;
                                if (a1 == a0) {
                                    goto L_00160434;
                                }
                                // 0x0015fb88
                                charge(ctx, 3);
                                a0 = 13;
                                if (a1 == a0) {
                                    goto L_00160434;
                                }
                                // 0x0015fb94
                                charge(ctx, 3);
                                a0 = 42;
                                if (a1 != a0) {
                                    // 0x0015fba0
                                    charge(ctx, 3);
                                    a0 = 32;
                                    if (a1 == a0) {
                                        goto L_00160124;
                                    }
                                    // 0x0015fbac
                                    charge(ctx, 3);
                                    a0 = 22;
                                    if (a1 == a0) {
                                        goto L_00160124;
                                    }
                                    // 0x0015fbb8
                                    charge(ctx, 3);
                                    a0 = 12;
                                    if (a1 == a0) {
                                        goto L_00160124;
                                    }
                                    // 0x0015fbc4
                                    charge(ctx, 3);
                                    a0 = 41;
                                    if (a1 != a0) {
                                        // 0x0015fbd0
                                        charge(ctx, 3);
                                        a0 = 31;
                                        if (a1 == a0) {
                                            goto L_0015fe14;
                                        }
                                        // 0x0015fbdc
                                        charge(ctx, 3);
                                        a0 = 21;
                                        if (a1 == a0) {
                                            goto L_0015fe14;
                                        }
                                        // 0x0015fbe8
                                        charge(ctx, 3);
                                        a0 = 11;
                                        if (a1 == a0) {
                                            goto L_0015fe14;
                                        }
                                        // 0x0015fbf4
                                        charge(ctx, 3);
                                        a0 = 40;
                                        if (a1 != a0) {
                                            // 0x0015fc00
                                            charge(ctx, 3);
                                            a0 = 30;
                                            if (a1 == a0) {
                                                goto L_0015fd70;
                                            }
                                            // 0x0015fc0c
                                            charge(ctx, 3);
                                            a0 = 20;
                                            if (a1 == a0) {
                                                goto L_0015fd70;
                                            }
                                            // 0x0015fc18
                                            charge(ctx, 3);
                                            a0 = 10;
                                            if (a1 == a0) {
                                                goto L_0015fd70;
                                            }
                                            // 0x0015fc24
                                            charge(ctx, 2);
                                            if (a1 == 0) {
                                                // 0x0015fd50
                                                charge(ctx, 8);
                                                ldr(a0, s1, 56);
                                                ldl(a0, s1, 63);
                                                lwc1(f12, s1, tw::kZ);
                                                lw(a1, s1, tw::kAlpha);
                                                jal(ctx, 0x15FD60u, gen::fn_sub_15D8E0_0015d8e0);  // the skill ribbon
                                            } else {
                                                // 0x0015fc2c
                                                charge(ctx, 3);
                                                a0 = 4;
                                                if (a1 == a0) {
                                                    // 0x0015fd2c
                                                    charge(ctx, 9);
                                                    ldr(a0, s1, 56);
                                                    ldl(a0, s1, 63);
                                                    lwc1(f12, s1, tw::kZ);
                                                    lw(a1, a2, 40);
                                                    lw(a2, s1, tw::kAlpha);
                                                    jal(ctx, 0x15FD40u, gen::fn_sub_15CE50_0015ce50);
                                                } else {
                                                    // 0x0015fc38
                                                    charge(ctx, 3);
                                                    a0 = 3;
                                                    if (a1 == a0) {
                                                        // 0x0015fcc4
                                                        charge(ctx, 26);
                                                        a0 = 0;
                                                        v0 = 0x830000;
                                                        lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                                        a2 = v1;
                                                        jal(ctx, 0x15FCD4u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                                                        s0 = v0;
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
                                                        a0 = s0;
                                                        a1 = 1;
                                                        jal(ctx, 0x15FD10u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                                                        a0 = s0;
                                                        jal(ctx, 0x15FD1Cu, gen::fn_sub_115980_00115980);  // draw and release the handle
                                                    } else {
                                                        // 0x0015fc44
                                                        charge(ctx, 3);
                                                        v1 = 2;
                                                        if (a1 == v1) {
                                                            // 0x0015fc94
                                                            charge(ctx, 12);
                                                            lbu(a3, s1, tw::kAlpha);
                                                            a0 = s0;
                                                            v0 = 0x830000;
                                                            lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                                            a2 = 1;
                                                            lwc1(f12, s1, tw::kX);
                                                            lwc1(f13, s1, tw::kY);
                                                            lwc1(f14, s1, tw::kZ);
                                                            jal(ctx, 0x15FCB4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                        } else {
                                                            // 0x0015fc50
                                                            charge(ctx, 3);
                                                            v1 = 1;
                                                            if (a1 == v1) {
                                                                // 0x0015fc64
                                                                charge(ctx, 12);
                                                                lbu(a3, s1, tw::kAlpha);
                                                                a0 = s0;
                                                                v0 = 0x830000;
                                                                lw(a1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                                                                a2 = 0;
                                                                lwc1(f12, s1, tw::kX);
                                                                lwc1(f13, s1, tw::kY);
                                                                lwc1(f14, s1, tw::kZ);
                                                                jal(ctx, 0x15FC84u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                                            } else {
                                                                // 0x0015fc5c
                                                                charge(ctx, 2);
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            // 0x001607d0 (the shared epilogue, written out on this path)
                                            charge(ctx, 9);
                                            ld(ra, sp, 0x50);
                                            lq(s4, sp, 0x40);
                                            lq(s3, sp, 0x30);
                                            lq(s2, sp, 0x20);
                                            lq(s1, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0x160);
                                            return;
                                        }
                                    L_0015fd70:
                                        charge(ctx, 41);
                                        lw(v1, s1, tw::kAlpha);
                                        v0 = 255;
                                        s0 = subu(v0, v1);
                                        v1 = addiu(a1, -10);
                                        v0 = 10;
                                        div(v1, v0);
                                        mflo(v0);
                                        v0 = sll(v0, 2);
                                        v0 = addu(v0, a2);
                                        lh(a0, v0, 60);
                                        jal(ctx, 0x15FD98u, gen::fn_sub_177790_00177790);  // a member's name
                                        a0 = addiu(sp, 0x60);
                                        a1 = addiu(gp, -30340);  // "%s"
                                        a2 = v0;
                                        jal(ctx, 0x15FDACu, gen::fn_sprintf_00523ac8);
                                        lwc1(f0, s1, tw::kX);
                                        cvt_w_s(f0, f0);
                                        mfc1(a0, f0);
                                        lwc1(f0, s1, tw::kY);
                                        cvt_w_s(f0, f0);
                                        cvt_s_w(f1, f0);
                                        v0 = 0x40400000;  // 3.0f
                                        mtc1(v0, f0);
                                        add_s(f0, f0, f1);
                                        cvt_w_s(f0, f0);
                                        mfc1(a1, f0);
                                        v0 = si(-256);
                                        a2 = s0 | v0;
                                        lwc1(f12, s1, tw::kZ);
                                        a3 = 10;
                                        t0 = 1;
                                        t1 = addiu(sp, 0x60);
                                        t2 = 16;
                                        t3 = 120;
                                        jal(ctx, 0x15FE04u, gen::fn_sub_3B32D0_003b32d0);  // text at (x, y): colour, size, font, string
                                        // 0x001607d0 (the shared epilogue, written out on this path)
                                        charge(ctx, 9);
                                        ld(ra, sp, 0x50);
                                        lq(s4, sp, 0x40);
                                        lq(s3, sp, 0x30);
                                        lq(s2, sp, 0x20);
                                        lq(s1, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0x160);
                                        return;
                                    }
                                L_0015fe14:
                                    charge(ctx, 15);
                                    v1 = addiu(a1, -11);
                                    v0 = 10;
                                    div(v1, v0);
                                    mflo(v0);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v0, a2);
                                    s2 = addiu(v0, 60);
                                    lh(a0, v0, 60);
                                    jal(ctx, 0x15FE34u, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
                                    s4 = v0 & 0xFFFF;
                                    s3 = 0;
                                    v0 = slti(s4, 100);
                                    if (v0 == 0) {
                                        // 0x0015fe50
                                        charge(ctx, 20);
                                        s3 = 1;
                                        a0 = 2;
                                        jal(ctx, 0x15FE58u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                        v1 = 100;
                                        div(s4, v1);
                                        mflo(v1);
                                        a2 = addiu(v1, 11);
                                        lbu(t0, s1, tw::kAlpha);
                                        a0 = s0;
                                        a1 = v0;
                                        lwc1(f12, s1, tw::kX);
                                        lwc1(f13, s1, tw::kY);
                                        a3 = 39;
                                        lwc1(f14, s1, tw::kZ);
                                        jal(ctx, 0x15FE8Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                        v0 = 100;
                                        div(s4, v0);
                                        mfhi(s4);
                                    }
                                    // 0x0015fea0
                                    charge(ctx, 3);
                                    at = slti(s4, 10);
                                    if (at != 0) {
                                        // 0x0015feac
                                        charge(ctx, 2);
                                        if (s3 != 0) {
                                            goto L_0015feb4;
                                        }
                                        goto L_0015ff10;
                                    }
                                L_0015feb4:
                                    charge(ctx, 23);
                                    a0 = 2;
                                    jal(ctx, 0x15FEB8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s4, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    lwc1(f1, s1, tw::kX);
                                    v1 = 0x41800000;  // 16.0f
                                    mtc1(v1, f0);
                                    add_s(f12, f0, f1);
                                    lbu(t0, s1, tw::kAlpha);
                                    a0 = s0;
                                    a1 = v0;
                                    lwc1(f13, s1, tw::kY);
                                    a3 = 39;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x15FEFCu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                    v0 = 10;
                                    div(s4, v0);
                                    mfhi(s4);
                                L_0015ff10:
                                    charge(ctx, 82);
                                    a0 = 2;
                                    jal(ctx, 0x15FF14u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 10;
                                    div(s4, v1);
                                    mfhi(v1);
                                    a2 = addiu(v1, 11);
                                    lwc1(f1, s1, tw::kX);
                                    v1 = 0x42000000;  // 32.0f
                                    mtc1(v1, f0);
                                    add_s(f12, f0, f1);
                                    lbu(t0, s1, tw::kAlpha);
                                    a0 = s0;
                                    a1 = v0;
                                    lwc1(f13, s1, tw::kY);
                                    a3 = 39;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x15FF58u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                    lw(s2, s2, 0);
                                    a0 = dsll32(s2, 16);
                                    a0 = dsra32(a0, 16);
                                    jal(ctx, 0x15FF6Cu, gen::fn_sub_16C4F0_0016c4f0);  // [datGetPcHp]
                                    v1 = v0 & 0xFFFF;
                                    v0 = sll(v1, 3);
                                    v0 = addu(v0, v1);
                                    v0 = sll(v0, 1);
                                    v0 = addu(v0, v1);
                                    s3 = sll(v0, 2);
                                    a0 = dsll32(s2, 16);
                                    a0 = dsra32(a0, 16);
                                    jal(ctx, 0x15FF94u, gen::fn_sub_16C5F0_0016c5f0);  // [datGetPcMaxHp]
                                    v0 = v0 & 0xFFFF;
                                    div(s3, v0);
                                    mflo(v1);
                                    v0 = 76;
                                    s2 = subu(v0, v1);
                                    lwc1(f1, s1, tw::kX);
                                    v0 = 0x42480000;  // 50.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f1);
                                    lwc1(f1, s1, tw::kY);
                                    v0 = 0x40000000;  // 2.0f
                                    mtc1(v0, f0);
                                    add_s(f13, f0, f1);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s0;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                    a2 = 13;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x15FFF0u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    lwc1(f1, s1, tw::kX);
                                    v0 = 0x425C0000;  // 55.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f1);
                                    lwc1(f1, s1, tw::kY);
                                    v0 = 0x40000000;  // 2.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x3F800000;  // 1.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s0;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                    a2 = 11;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x160048u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    if (s2 != 0) {
                                        // 0x00160058
                                        charge(ctx, 27);
                                        lwc1(f1, s1, tw::kX);
                                        v0 = 0x42600000;  // 56.0f
                                        mtc1(v0, f0);
                                        add_s(f1, f0, f1);
                                        v0 = 76;
                                        v0 = subu(v0, s2);
                                        mtc1(v0, f0);
                                        cvt_s_w(f0, f0);
                                        add_s(f13, f1, f0);
                                        lwc1(f0, s1, tw::kZ);
                                        v0 = 0x3F800000;  // 1.0f
                                        mtc1(v0, f2);
                                        sub_s(f12, f0, f2);
                                        lwc1(f1, s1, tw::kY);
                                        v0 = 0x40000000;  // 2.0f
                                        mtc1(v0, f0);
                                        add_s(f0, f0, f1);
                                        sub_s(f14, f0, f2);
                                        a0 = si(-256);
                                        a1 = s2;
                                        a2 = 10;
                                        jal(ctx, 0x1600BCu, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
                                    }
                                    // 0x001600c4
                                    charge(ctx, 24);
                                    lwc1(f1, s1, tw::kX);
                                    v0 = 0x425C0000;  // 55.0f
                                    mtc1(v0, f0);
                                    add_s(f12, f0, f1);
                                    lwc1(f1, s1, tw::kY);
                                    v0 = 0x40000000;  // 2.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 0x3F800000;  // 1.0f
                                    mtc1(v0, f0);
                                    sub_s(f13, f1, f0);
                                    lbu(a3, s1, tw::kAlpha);
                                    a0 = s0;
                                    v0 = 0x830000;
                                    lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                    a2 = 9;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x160114u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                    // 0x001607d0 (the shared epilogue, written out on this path)
                                    charge(ctx, 9);
                                    ld(ra, sp, 0x50);
                                    lq(s4, sp, 0x40);
                                    lq(s3, sp, 0x30);
                                    lq(s2, sp, 0x20);
                                    lq(s1, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x160);
                                    return;
                                }
                            L_00160124:
                                charge(ctx, 15);
                                v1 = addiu(a1, -12);
                                v0 = 10;
                                div(v1, v0);
                                mflo(v0);
                                v0 = sll(v0, 2);
                                v0 = addu(v0, a2);
                                s2 = addiu(v0, 60);
                                lh(a0, v0, 60);
                                jal(ctx, 0x160144u, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
                                s3 = v0 & 0xFFFF;
                                s4 = 0;
                                v0 = slti(s3, 100);
                                if (v0 == 0) {
                                    // 0x00160160
                                    charge(ctx, 20);
                                    s4 = 1;
                                    a0 = 2;
                                    jal(ctx, 0x160168u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                    v1 = 100;
                                    div(s3, v1);
                                    mflo(v1);
                                    a2 = addiu(v1, 11);
                                    lbu(t0, s1, tw::kAlpha);
                                    a0 = s0;
                                    a1 = v0;
                                    lwc1(f12, s1, tw::kX);
                                    lwc1(f13, s1, tw::kY);
                                    a3 = 39;
                                    lwc1(f14, s1, tw::kZ);
                                    jal(ctx, 0x16019Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                    v0 = 100;
                                    div(s3, v0);
                                    mfhi(s3);
                                }
                                // 0x001601b0
                                charge(ctx, 3);
                                at = slti(s3, 10);
                                if (at != 0) {
                                    // 0x001601bc
                                    charge(ctx, 2);
                                    if (s4 != 0) {
                                        goto L_001601c4;
                                    }
                                    goto L_00160220;
                                }
                            L_001601c4:
                                charge(ctx, 23);
                                a0 = 2;
                                jal(ctx, 0x1601C8u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                v1 = 10;
                                div(s3, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x41800000;  // 16.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                lbu(t0, s1, tw::kAlpha);
                                a0 = s0;
                                a1 = v0;
                                lwc1(f13, s1, tw::kY);
                                a3 = 39;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x16020Cu, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                v0 = 10;
                                div(s3, v0);
                                mfhi(s3);
                            L_00160220:
                                charge(ctx, 82);
                                a0 = 2;
                                jal(ctx, 0x160224u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                v1 = 10;
                                div(s3, v1);
                                mfhi(v1);
                                a2 = addiu(v1, 11);
                                lwc1(f1, s1, tw::kX);
                                v1 = 0x42000000;  // 32.0f
                                mtc1(v1, f0);
                                add_s(f12, f0, f1);
                                lbu(t0, s1, tw::kAlpha);
                                a0 = s0;
                                a1 = v0;
                                lwc1(f13, s1, tw::kY);
                                a3 = 39;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x160268u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                lw(s2, s2, 0);
                                a0 = dsll32(s2, 16);
                                a0 = dsra32(a0, 16);
                                jal(ctx, 0x16027Cu, gen::fn_sub_16C570_0016c570);  // [datGetPcSp]
                                v1 = v0 & 0xFFFF;
                                v0 = sll(v1, 3);
                                v0 = addu(v0, v1);
                                v0 = sll(v0, 1);
                                v0 = addu(v0, v1);
                                s3 = sll(v0, 2);
                                a0 = dsll32(s2, 16);
                                a0 = dsra32(a0, 16);
                                jal(ctx, 0x1602A4u, gen::fn_sub_16C670_0016c670);  // [datGetPcMaxSp]
                                v0 = v0 & 0xFFFF;
                                div(s3, v0);
                                mflo(v1);
                                v0 = 76;
                                s2 = subu(v0, v1);
                                lwc1(f1, s1, tw::kX);
                                v0 = 0x42480000;  // 50.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s1, tw::kY);
                                v0 = 0x40000000;  // 2.0f
                                mtc1(v0, f0);
                                add_s(f13, f0, f1);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s0;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                a2 = 13;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x160300u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                lwc1(f1, s1, tw::kX);
                                v0 = 0x425C0000;  // 55.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s1, tw::kY);
                                v0 = 0x40000000;  // 2.0f
                                mtc1(v0, f0);
                                add_s(f1, f0, f1);
                                v0 = 0x3F800000;  // 1.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s0;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                a2 = 12;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x160358u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                if (s2 != 0) {
                                    // 0x00160368
                                    charge(ctx, 27);
                                    lwc1(f1, s1, tw::kX);
                                    v0 = 0x42600000;  // 56.0f
                                    mtc1(v0, f0);
                                    add_s(f1, f0, f1);
                                    v0 = 76;
                                    v0 = subu(v0, s2);
                                    mtc1(v0, f0);
                                    cvt_s_w(f0, f0);
                                    add_s(f13, f1, f0);
                                    lwc1(f0, s1, tw::kZ);
                                    v0 = 0x3F800000;  // 1.0f
                                    mtc1(v0, f2);
                                    sub_s(f12, f0, f2);
                                    lwc1(f1, s1, tw::kY);
                                    v0 = 0x40000000;  // 2.0f
                                    mtc1(v0, f0);
                                    add_s(f0, f0, f1);
                                    sub_s(f14, f0, f2);
                                    a0 = si(-256);
                                    a1 = s2;
                                    a2 = 10;
                                    jal(ctx, 0x1603CCu, gen::fn_sub_113A30_00113a30);  // [plain rectangle] (rgba, w, h)
                                }
                                // 0x001603d4
                                charge(ctx, 24);
                                lwc1(f1, s1, tw::kX);
                                v0 = 0x425C0000;  // 55.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s1, tw::kY);
                                v0 = 0x40000000;  // 2.0f
                                mtc1(v0, f0);
                                add_s(f1, f0, f1);
                                v0 = 0x3F800000;  // 1.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s0;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                a2 = 10;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x160424u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                                // 0x001607d0 (the shared epilogue, written out on this path)
                                charge(ctx, 9);
                                ld(ra, sp, 0x50);
                                lq(s4, sp, 0x40);
                                lq(s3, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0x160);
                                return;
                            }
                        L_00160434:
                            charge(ctx, 14);
                            v1 = addiu(a1, -12);
                            v0 = 10;
                            div(v1, v0);
                            mflo(v0);
                            v0 = sll(v0, 2);
                            v0 = addu(v0, a2);
                            s2 = addiu(v0, 60);
                            lh(a0, v0, 60);
                            jal(ctx, 0x160454u, gen::fn_sub_16C470_0016c470);  // [datGetPcLevel]
                            s3 = v0 & 0xFF;
                            v0 = slti(s3, 10);
                            if (v0 == 0) {
                                // 0x0016046c
                                charge(ctx, 19);
                                a0 = 2;
                                jal(ctx, 0x160470u, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                                v1 = 10;
                                div(s3, v1);
                                mflo(v1);
                                a2 = addiu(v1, 11);
                                lbu(t0, s1, tw::kAlpha);
                                a0 = s0;
                                a1 = v0;
                                lwc1(f12, s1, tw::kX);
                                lwc1(f13, s1, tw::kY);
                                a3 = 39;
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x1604A4u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                                v0 = 10;
                                div(s3, v0);
                                mfhi(s3);
                            }
                            // 0x001604b8
                            charge(ctx, 27);
                            a0 = 2;
                            jal(ctx, 0x1604BCu, gen::fn_sprFontGetFile_001120a0);  // sprite font file $a0 (digits = sprite 11 + d)
                            v1 = 10;
                            div(s3, v1);
                            mfhi(v1);
                            a2 = addiu(v1, 11);
                            lwc1(f1, s1, tw::kX);
                            v1 = 0x41800000;  // 16.0f
                            mtc1(v1, f0);
                            add_s(f12, f0, f1);
                            lbu(t0, s1, tw::kAlpha);
                            a0 = s0;
                            a1 = v0;
                            lwc1(f13, s1, tw::kY);
                            a3 = 39;
                            lwc1(f14, s1, tw::kZ);
                            jal(ctx, 0x160500u, gen::fn_sub_115AD0_00115ad0);  // draw sprite $a2 of file $a1 at ($f12, $f13) with two colour bytes $a3 / $t0
                            lh(a0, s2, 0);
                            jal(ctx, 0x16050Cu, gen::fn_sub_16C970_0016c970);  // [datGetPcBadStatus]
                            v1 = 0x80000;
                            v1 = v0 & v1;
                            if (v1 == 0) {
                                // 0x00160530
                                charge(ctx, 6);
                                lh(a0, s2, 0);
                                jal(ctx, 0x160534u, gen::fn_sub_16C970_0016c970);  // [datGetPcBadStatus]
                                v1 = v0 & 0x80;
                                if (v1 == 0) {
                                    // 0x00160554
                                    charge(ctx, 7);
                                    lh(a0, s2, 0);
                                    jal(ctx, 0x160558u, gen::fn_sub_16C920_0016c920);  // [datGetPcCondition]
                                    a0 = v0 & 0xFFFF;
                                    v1 = 5;
                                    if (a0 == v1) {
                                        // 0x001605a8
                                        charge(ctx, 3);
                                        a2 = 1;
                                    } else {
                                        // 0x00160570
                                        charge(ctx, 3);
                                        v1 = 4;
                                        if (a0 == v1) {
                                            // 0x0016059c
                                            charge(ctx, 3);
                                            a2 = 0;
                                        } else {
                                            // 0x0016057c
                                            charge(ctx, 3);
                                            v1 = 3;
                                            if (a0 == v1) {
                                                // 0x00160590
                                                charge(ctx, 3);
                                                a2 = 2;
                                            } else {
                                                // 0x00160588
                                                charge(ctx, 2);
                                                // 0x001605b4
                                                charge(ctx, 1);
                                                a2 = si(-1);
                                            }
                                        }
                                    }
                                } else {
                                    // 0x00160548
                                    charge(ctx, 3);
                                    a2 = 15;
                                }
                            } else {
                                // 0x00160524
                                charge(ctx, 3);
                                a2 = 14;
                            }
                            // 0x001605b8
                            charge(ctx, 3);
                            v1 = si(-1);
                            if (a2 != v1) {
                                // 0x001605c4
                                charge(ctx, 19);
                                lwc1(f1, s1, tw::kX);
                                v0 = 0x42300000;  // 44.0f
                                mtc1(v0, f0);
                                add_s(f12, f0, f1);
                                lwc1(f1, s1, tw::kY);
                                v0 = 0x40C00000;  // 6.0f
                                mtc1(v0, f0);
                                sub_s(f13, f1, f0);
                                lbu(a3, s1, tw::kAlpha);
                                a0 = s0;
                                v0 = 0x830000;
                                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                                lwc1(f14, s1, tw::kZ);
                                jal(ctx, 0x160600u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                            }
                            // 0x001607d0 (the shared epilogue, written out on this path)
                            charge(ctx, 9);
                            ld(ra, sp, 0x50);
                            lq(s4, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0x160);
                            return;
                        }
                    L_00160610:
                        charge(ctx, 12);
                        lbu(a3, s1, tw::kAlpha);
                        a0 = s0;
                        v0 = 0x830000;
                        lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                        a2 = 3;
                        lwc1(f12, s1, tw::kX);
                        lwc1(f13, s1, tw::kY);
                        lwc1(f14, s1, tw::kZ);
                        jal(ctx, 0x160630u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                        // 0x001607d0 (the shared epilogue, written out on this path)
                        charge(ctx, 9);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0x160);
                        return;
                    }
                L_00160640:
                    charge(ctx, 12);
                    lbu(a3, s1, tw::kAlpha);
                    a0 = s0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                    a2 = 3;
                    lwc1(f12, s1, tw::kX);
                    lwc1(f13, s1, tw::kY);
                    lwc1(f14, s1, tw::kZ);
                    jal(ctx, 0x160660u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
                    // 0x001607d0 (the shared epilogue, written out on this path)
                    charge(ctx, 9);
                    ld(ra, sp, 0x50);
                    lq(s4, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x160);
                    return;
                }
            L_00160670:
                charge(ctx, 12);
                lbu(a3, s1, tw::kAlpha);
                a0 = s0;
                v0 = 0x830000;
                lw(a1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                a2 = 4;
                lwc1(f12, s1, tw::kX);
                lwc1(f13, s1, tw::kY);
                lwc1(f14, s1, tw::kZ);
                jal(ctx, 0x160690u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
        }
    }
    // 0x001607d0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x00160800 sub_160800 -- 3780 bytes; frame 0x90: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [H_Camp_UpdateNewCampSkillDrawTask] Update of the skill screen "H_NewCampSkillDraw" (jump table 0x7B61E0): 0 / 1 fade
// the background in (8 frames) and close the main list (sub_11DA80); 2 takes camp_skil.pak's three sprite files
// (+28..); 3 waits for them, builds the skill list (+40, sub_15C840); 4 waits for flash 13 and slides in; 5 / 6 the
// list (confirm on a usable skill -> 8 target choice, cancel -> 7 close, -1); 8 / 9 the target choice: confirm casts
// (sub_15C520 when the target is near the hero (K_FldUnit_IsPcNearHero) and accepts the skill, sound 1) or refuses; 0xA
// back to the list. Steps and draws its tweens (sub_15FA90) every frame.
void sub_160800(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00160800
    enter(ctx, 15);  // entry check point + this block's cycles
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
    lw(s0, a0, 60);
    lw(v0, s0, skl::kState);
    at = sltiu(v0, 11);
    if (at != 0) {
        // 0x0016083c
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25056);  // &0x7B61E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x160858u:  // table[0]: state 0: background fade in
            // 0x00160858
            charge(ctx, 4);
            sw(zero, gp, g::kSkillRibbonX);  // 0x7CDF8C
            lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
            if (v0 != 0) {
                // 0x00160874
                charge(ctx, 5);
                lw(a0, v0, 60);
                lw(v1, a0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x00160894
                    charge(ctx, 1);
                    t0 = 0;
                } else {
                    // 0x00160888
                    charge(ctx, 3);
                    lw(t0, a0, 12);
                }
            } else {
                // 0x00160868
                charge(ctx, 3);
                t0 = 0;
            }
            // 0x00160898
            charge(ctx, 2);
            if (t0 != 0) {
                // 0x001608a0
                charge(ctx, 12);
                v0 = 0x42CC0000;  // 102.0f
                mtc1(v0, f12);
                mtc1(zero, f13);
                v0 = lui(0xC2AE);
                mtc1(v0, f14);
                a0 = si(-1);
                v0 = 0x4FA40000;
                a1 = v0 | 0xFF19;
                a2 = 640;
                a3 = a2;
                jal(ctx, 0x1608C8u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
            }
            // 0x001608d0
            charge(ctx, 42);
            mtc1(zero, f12);
            v0 = 0x42CC0000;  // 102.0f
            mtc1(v0, f14);
            mov_s(f13, f12);
            a0 = 0;
            a1 = 0;
            jal(ctx, 0x1608E8u, gen::fn_nullsub_3_0011bba0);
            a0 = 0;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
            a2 = 0;
            jal(ctx, 0x160900u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
            s1 = v0;
            v1 = 0x42CA0000;  // 101.0f
            sw(v1, v0, 44);
            v1 = 0x43D60000;  // 428.0f
            sw(v1, v0, 16);
            v1 = 0x41D80000;  // 27.0f
            sw(v1, v0, 20);
            sb(zero, v0, 24);
            sh(zero, v0, 40);
            sh(zero, v0, 42);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x160938u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
            a0 = s1;
            jal(ctx, 0x160944u, gen::fn_sub_115980_00115980);  // draw and release the handle
            a0 = 60;
            jal(ctx, 0x160950u, gen::fn_sub_18B6D0_0018b6d0);  // [H_Camp_AllocTweens] RwCalloc(n, 68)
            sw(v0, s0, skl::kTweens);
            v0 = 1;
            sw(v0, s0, skl::kState);
            sw(v0, s0, 60);
            sw(v0, s0, skl::kTargetCount);
            s1 = 0;
            for (;;) {
                // 0x001609c8
                charge(ctx, 3);
                v0 = slti(s1, 3);
                if (v0 != 0) {
                    backedge(ctx);
                    // 0x00160978
                    charge(ctx, 7);
                    a0 = s1;
                    jal(ctx, 0x16097Cu, gen::fn_sub_16DD60_0016dd60);  // [datGetPartyMember]
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (v0 != 0) {
                        // 0x00160994
                        charge(ctx, 13);
                        a0 = s1;
                        jal(ctx, 0x160998u, gen::fn_sub_16DD60_0016dd60);  // [datGetPartyMember]
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        lw(v0, s0, skl::kTargetCount);
                        v0 = sll(v0, 2);
                        v0 = addu(s0, v0);
                        sw(v1, v0, 60);
                        lw(v0, s0, skl::kTargetCount);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, skl::kTargetCount);
                        s1 = addiu(s1, 1);
                        continue;
                    }
                }
                break;
            }
            // 0x001609d4
            charge(ctx, 3);
            sw(zero, s0, 12);
        L_00161690:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1609E0u:  // table[1]: state 1: fade (8 frames), close the main list
            // 0x001609e0
            charge(ctx, 4);
            lw(v1, s0, 12);
            v0 = 10;
            if (v1 != v0) {
                // 0x00160a00
                charge(ctx, 3);
                at = slti(v1, 9);
                if (at != 0) {
                    // 0x00160a0c
                    charge(ctx, 3);
                    at = slti(v1, 3);
                    if (at == 0) {
                        // 0x00160a30
                        charge(ctx, 17);
                        a0 = addiu(v1, -3);
                        v0 = sll(a0, 2);
                        v1 = addu(v0, a0);
                        v0 = sll(v1, 2);
                        v0 = addu(v1, v0);
                        v0 = sll(v0, 4);
                        v1 = 5;
                        div(v0, v1);
                        mflo(v0);
                        mtc1(v0, f0);
                        cvt_s_w(f21, f0);
                        mtc1(zero, f20);
                        v0 = sll(a0, 8);
                        v0 = subu(v0, a0);
                        div1(v0, v1);
                        mflo1(s2);
                    } else {
                        // 0x00160a18
                        charge(ctx, 6);
                        mtc1(zero, f21);
                        mov_s(f20, f21);
                        s2 = 0;
                    }
                    // 0x00160a74
                    charge(ctx, 3);
                    lw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
                    if (v0 != 0) {
                        // 0x00160a8c
                        charge(ctx, 5);
                        lw(a0, v0, 60);
                        lw(v1, a0, 0);
                        v0 = 3;
                        if (v1 != v0) {
                            // 0x00160aac
                            charge(ctx, 1);
                            t0 = 0;
                        } else {
                            // 0x00160aa0
                            charge(ctx, 3);
                            lw(t0, a0, 12);
                        }
                    } else {
                        // 0x00160a80
                        charge(ctx, 3);
                        t0 = 0;
                    }
                    // 0x00160ab0
                    charge(ctx, 2);
                    if (t0 != 0) {
                        // 0x00160ab8
                        charge(ctx, 8);
                        v1 = dsll32(s2, 16);
                        v1 = dsra32(v1, 16);
                        v0 = 255;
                        v1 = subu(v0, v1);
                        a1 = v1;
                        v0 = sltiu(v1, 25);
                        if (v0 == 0) {
                            // 0x00160ad8
                            charge(ctx, 1);
                            a1 = 25;
                        }
                        // 0x00160adc
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
                        jal(ctx, 0x160B14u, gen::fn_sub_114450_00114450);  // [nine-slice window] / the persona picture
                    }
                    // 0x00160b1c
                    charge(ctx, 43);
                    mtc1(zero, f12);
                    v0 = 0x42CC0000;  // 102.0f
                    mtc1(v0, f14);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    mov_s(f13, f12);
                    a1 = 0;
                    jal(ctx, 0x160B38u, gen::fn_nullsub_3_0011bba0);
                    a0 = 0;
                    v0 = 0x830000;
                    lw(a1, v0, spr::camp(2));  // 0x833B78: camp sprite file 2
                    a2 = 0;
                    jal(ctx, 0x160B50u, gen::fn_sprCreateHandle_001158b0);  // a sprite handle (file $a1, sprite $a2)
                    s1 = v0;
                    v1 = 0x42CA0000;  // 101.0f
                    sw(v1, v0, 44);
                    v1 = 0x43D60000;  // 428.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f21);
                    swc1(f0, v0, 16);
                    v1 = 0x41D80000;  // 27.0f
                    mtc1(v1, f0);
                    add_s(f0, f0, f20);
                    swc1(f0, v0, 20);
                    v1 = dsll32(s2, 16);
                    v1 = dsra32(v1, 16);
                    sb(v1, v0, 24);
                    sh(zero, v0, 40);
                    sh(zero, v0, 42);
                    a0 = s1;
                    a1 = 1;
                    jal(ctx, 0x160BA8u, gen::fn_sub_1127D0_001127d0);  // [sprite quad] build the handle's vertices
                    a0 = s1;
                    jal(ctx, 0x160BB4u, gen::fn_sub_115980_00115980);  // draw and release the handle
                    lw(v0, s0, 12);
                    if (v0 == 0) {
                        // 0x00160bc8
                        charge(ctx, 10);
                        lw(v0, gp, g::kCampRootTask);  // 0x7CDF5C
                        lw(s1, v0, 60);
                        v0 = 0x42C80000;  // 100.0f
                        mtc1(v0, f12);
                        a0 = s1;
                        jal(ctx, 0x160BDCu, gen::fn_sub_11DA80_0011da80);  // [H_Camp_RootFadeOut2]
                        v0 = 9;
                        sw(v0, s1, 0);
                        sw(zero, s1, 4);
                    }
                    // 0x00160bf0
                    charge(ctx, 4);
                    lw(v1, s0, 12);
                    v0 = 4;
                    if (v1 == v0) {
                        // 0x00160c00
                        charge(ctx, 8);
                        lw(a0, gp, g::kCampPcKani);  // 0x7CDF54
                        a1 = 13;
                        jal(ctx, 0x160C08u, gen::fn_sub_121DE0_00121de0);  // [H_Camp_PcKaniSetScreen]
                        lw(a0, gp, g::kCampPersonaKani);  // 0x7CDF58
                        a1 = 13;
                        jal(ctx, 0x160C18u, gen::fn_sub_122710_00122710);  // [H_Camp_PersonaKaniSetScreen]
                    }
                }
                // 0x00160c20
                charge(ctx, 5);
                lw(v0, s0, 12);
                v0 = addiu(v0, 1);
                sw(v0, s0, 12);
            } else {
                // 0x001609f0
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, skl::kState);
            }
            goto L_00161690;
        case 0x160C34u:  // table[2]: state 2: camp_skil.pak -> sprite files
            // 0x00160c34
            charge(ctx, 5);
            lw(a0, s0, skl::kPak);
            jal(ctx, 0x160C38u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00160c48
                charge(ctx, 37);
                lw(a0, s0, skl::kPak);
                a1 = 0;
                a2 = addiu(sp, 0x8C);
                jal(ctx, 0x160C54u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x160C60u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, skl::kFiles);
                lw(a0, s0, skl::kPak);
                a1 = 1;
                a2 = addiu(sp, 0x8C);
                jal(ctx, 0x160C78u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x160C84u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, skl::kFile1);
                lw(a0, s0, skl::kPak);
                a1 = 2;
                a2 = addiu(sp, 0x8C);
                jal(ctx, 0x160C9Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);  // entry $a1 of the pak
                a0 = v0;
                jal(ctx, 0x160CA8u, gen::fn_sprCreateHandleFromData_00112420);  // a sprite file from the entry
                sw(v0, s0, skl::kFile2);
                a0 = 1;
                a1 = 2032;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x160CC8u, v0.u());
                a0 = 0;
                for (;;) {
                    // 0x00160cf8
                    charge(ctx, 3);
                    v1 = slti(a0, 100);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00160cdc
                    charge(ctx, 7);
                    v1 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(v0, v1);
                    sw(zero, v1, 12);
                    sw(zero, v1, 16);
                    a0 = addiu(a0, 1);
                }
                // 0x00160d04
                charge(ctx, 17);
                sw(v0, s0, skl::kList);
                a0 = v0;
                jal(ctx, 0x160D0Cu, gen::fn_sub_15C840_0015c840);
                lw(v1, s0, skl::kFiles);
                v0 = 0x830000;
                sw(v1, v0, spr::screen(0));  // 0x833A50: the screen's sprite file 0
                lw(v1, s0, skl::kFile1);
                v0 = 0x830000;
                sw(v1, v0, spr::screen(1));  // 0x833A54: the screen's sprite file 1
                lw(v1, s0, skl::kFile2);
                v0 = 0x830000;
                sw(v1, v0, spr::screen(2));  // 0x833A58: the screen's sprite file 2
                v0 = 3;
                sw(v0, s0, skl::kState);
            }
            goto L_00161690;
        case 0x160D48u:  // table[3]: state 3: wait for the files, build the skill list
            // 0x00160d48
            charge(ctx, 5);
            lw(a0, s0, skl::kFiles);
            jal(ctx, 0x160D4Cu, gen::fn_sprFileIsReady_00111f30);
            if (v0 != 0) {
                // 0x00160d5c
                charge(ctx, 5);
                lw(a0, s0, skl::kFile1);
                jal(ctx, 0x160D60u, gen::fn_sprFileIsReady_00111f30);
                if (v0 != 0) {
                    // 0x00160d70
                    charge(ctx, 5);
                    lw(a0, s0, skl::kFile2);
                    jal(ctx, 0x160D74u, gen::fn_sprFileIsReady_00111f30);
                    if (v0 != 0) {
                        // 0x00160d84
                        charge(ctx, 4);
                        v0 = 4;
                        sw(v0, s0, skl::kState);
                    }
                }
            }
            goto L_00161690;
        case 0x160D94u:  // table[4]: state 4: wait for flash 13, slide in
            // 0x00160d94
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 13;
            jal(ctx, 0x160D9Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x00160dac
                charge(ctx, 7);
                a0 = s0;
                jal(ctx, 0x160DB0u, gen::fn_sub_15DA70_0015da70);
                v0 = 5;
                sw(v0, s0, skl::kState);
            }
            goto L_00161690;
        case 0x160DC8u:  // table[5]: state 5: arrived
            // 0x00160dc8
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00160e4c
                charge(ctx, 3);
                v0 = slti(s2, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00160dd8
                charge(ctx, 8);
                lw(v1, s0, skl::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00160df8
                    charge(ctx, 4);
                    jal(ctx, 0x160DF8u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00160e08
                        charge(ctx, 6);
                        lw(v0, s0, skl::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x160E18u, gen::fn_sub_15FA90_0015fa90);
                    }
                    // 0x00160e20
                    charge(ctx, 9);
                    lw(v1, s0, skl::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x00160e44
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00160e48
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00160e58
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00160e60
                charge(ctx, 4);
                v0 = 6;
                sw(v0, s0, skl::kState);
            }
            goto L_00161690;
        case 0x160E70u:  // table[6]: state 6: the skill list (input)
            // 0x00160e70
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00160ef4
                charge(ctx, 3);
                v0 = slti(s2, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00160e80
                charge(ctx, 8);
                lw(v1, s0, skl::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00160ea0
                    charge(ctx, 4);
                    jal(ctx, 0x160EA0u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00160eb0
                        charge(ctx, 6);
                        lw(v0, s0, skl::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x160EC0u, gen::fn_sub_15FA90_0015fa90);
                    }
                    // 0x00160ec8
                    charge(ctx, 9);
                    lw(v1, s0, skl::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x00160eec
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00160ef0
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00160f00
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00160f08
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v1, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = v1 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x00160f50
                    charge(ctx, 3);
                    v0 = v1 & 0x40;
                    if (v0 == 0) {
                        // 0x00161080
                        charge(ctx, 9);
                        lw(v0, s0, skl::kList);
                        lw(a0, v0, 2012);
                        a1 = 5;
                        a2 = addiu(v0, 2020);
                        a3 = addiu(v0, 2016);
                        jal(ctx, 0x161094u, gen::fn_H_Camp_MoveListCursor_0011abd0);  // (count, page, &scroll, &cursor)
                    } else {
                        // 0x00160f5c
                        charge(ctx, 6);
                        lw(a0, s0, skl::kList);
                        lw(v1, a0, 2016);
                        lw(v0, a0, 2012);
                        at = slt(v1, v0);
                        if (at != 0) {
                            // 0x00160f74
                            charge(ctx, 20);
                            lw(v0, a0, 2020);
                            v1 = addu(v1, v0);
                            v0 = sll(v1, 2);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v1 = addu(v0, a0);
                            lw(s2, v1, 12);
                            v0 = 0x830000;
                            lh(s1, v0, spr::kCurrentPersona);  // 0x836BA8: the current persona slot
                            lh(a0, v1, 20);
                            jal(ctx, 0x160F9Cu, gen::fn_sub_175200_00175200);  // [datPersonaSelectSlot]
                            a0 = s2 & 0xFFFF;
                            jal(ctx, 0x160FA8u, gen::fn_sub_17B480_0017b480);
                            v1 = dsll32(v0, 16);
                            v1 = dsra32(v1, 16);
                            v0 = 2;
                            if (v1 != v0) {
                                // 0x00160fc4
                                charge(ctx, 6);
                                a1 = s2 & 0xFFFF;
                                a0 = 1;
                                jal(ctx, 0x160FCCu, gen::fn_sub_17B660_0017b660);
                                if (v0 != 0) {
                                    goto L_00161054;
                                }
                                // 0x00160fdc
                                charge(ctx, 6);
                                a0 = s2 & 0xFFFF;
                                jal(ctx, 0x160FE0u, gen::fn_sub_17B4E0_0017b4e0);
                                a3 = 1;
                                if (v0 != a3) {
                                    goto L_00161054;
                                }
                                // 0x00160ff4
                                charge(ctx, 13);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                jal(ctx, 0x161000u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                a0 = s2 & 0xFFFF;
                                jal(ctx, 0x16100Cu, gen::fn_sub_17BB40_0017bb40);
                                sh(v0, s0, skl::kTargetKind);
                                lhu(v1, s0, skl::kTargetKind);
                                v0 = 3;
                                if (v1 != v0) {
                                    // 0x00161028
                                    charge(ctx, 2);
                                    if (v1 != 0) {
                                        // 0x0016103c
                                        charge(ctx, 2);
                                        v0 = si(-2);
                                        sw(v0, s0, skl::kTargetCursor);
                                    } else {
                                        // 0x00161030
                                        charge(ctx, 3);
                                        sw(zero, s0, skl::kTargetCursor);
                                    }
                                    // 0x00161044
                                    charge(ctx, 4);
                                    v0 = 8;
                                    sw(v0, s0, skl::kState);
                                }
                                goto L_0016106c;
                            }
                        L_00161054:
                            charge(ctx, 6);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 8;
                            jal(ctx, 0x161064u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        L_0016106c:
                            charge(ctx, 5);
                            a0 = s1;
                            jal(ctx, 0x161070u, gen::fn_sub_175200_00175200);  // [datPersonaSelectSlot]
                        }
                    }
                } else {
                    // 0x00160f1c
                    charge(ctx, 13);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x160F2Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    a0 = s0;
                    jal(ctx, 0x160F38u, gen::fn_sub_15E150_0015e150);
                    v0 = 7;
                    sw(v0, s0, skl::kState);
                }
            }
            goto L_00161690;
        case 0x1610A4u:  // table[7]: state 7: slide out, done (-1)
            // 0x001610a4
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00161128
                charge(ctx, 3);
                v0 = slti(s2, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001610b4
                charge(ctx, 8);
                lw(v1, s0, skl::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x001610d4
                    charge(ctx, 4);
                    jal(ctx, 0x1610D4u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x001610e4
                        charge(ctx, 6);
                        lw(v0, s0, skl::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x1610F4u, gen::fn_sub_15FA90_0015fa90);
                    }
                    // 0x001610fc
                    charge(ctx, 9);
                    lw(v1, s0, skl::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x00161120
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00161124
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00161134
            charge(ctx, 2);
            if (s1 == 0) {
                goto L_00161690;
            }
            // 0x0016113c
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x161148u:  // table[8]: state 8: wait for flash 14, open the target choice
            // 0x00161148
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x001611a0
                charge(ctx, 3);
                v0 = slti(s1, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00161154
                charge(ctx, 8);
                lw(v1, s0, skl::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00161174
                    charge(ctx, 4);
                    jal(ctx, 0x161174u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00161184
                        charge(ctx, 6);
                        lw(v0, s0, skl::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x161194u, gen::fn_sub_15FA90_0015fa90);
                    }
                }
                // 0x0016119c
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x001611ac
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 14;
            jal(ctx, 0x1611B4u, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x001611c4
                charge(ctx, 7);
                a0 = s0;
                jal(ctx, 0x1611C8u, gen::fn_sub_15E6E0_0015e6e0);
                v0 = 9;
                sw(v0, s0, skl::kState);
            }
            goto L_00161690;
        case 0x1611E0u:  // table[9]: state 9: the target choice (input; cast)
            // 0x001611e0
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x00161264
                charge(ctx, 3);
                v0 = slti(s2, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001611f0
                charge(ctx, 8);
                lw(v1, s0, skl::kTweens);
                v0 = sll(s2, 4);
                v0 = addu(v0, s2);
                s3 = sll(v0, 2);
                a0 = addu(v1, s3);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x00161210
                    charge(ctx, 4);
                    jal(ctx, 0x161210u, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x00161220
                        charge(ctx, 6);
                        lw(v0, s0, skl::kTweens);
                        a0 = addu(v0, s3);
                        a1 = s2;
                        a2 = s0;
                        jal(ctx, 0x161230u, gen::fn_sub_15FA90_0015fa90);
                    }
                    // 0x00161238
                    charge(ctx, 9);
                    lw(v1, s0, skl::kTweens);
                    v0 = sll(s2, 4);
                    v0 = addu(v0, s2);
                    v0 = sll(v0, 2);
                    v0 = addu(v1, v0);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 != v0) {
                        // 0x0016125c
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x00161260
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x00161270
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00161278
                charge(ctx, 6);
                lw(s3, s0, skl::kTargetCursor);
                v0 = 0x7E0000;
                lhu(a0, v0, pad::kTrig);  // gPadFlags (0x7E094E)
                v0 = a0 & 0x20;  // cancel
                if (v0 == 0) {
                    // 0x001612b8
                    charge(ctx, 3);
                    v0 = a0 & 0x40;
                    if (v0 == 0) {
                        // 0x0016145c
                        charge(ctx, 6);
                        a1 = 1;
                        v0 = 0x7E0000;
                        lhu(v1, v0, pad::kRepeat);  // 0x7E0952
                        v0 = v1 & 0x1000;  // cursor - 1
                        if (v0 == 0) {
                            // 0x00161474
                            charge(ctx, 5);
                            v0 = 0x7E0000;
                            lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                            v0 = v0 & 0x1000;  // cursor - 1
                            if (v0 == 0) {
                                // 0x00161488
                                charge(ctx, 1);
                                a1 = 0;
                            }
                        }
                        // 0x0016148c
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x00161528
                            charge(ctx, 4);
                            v0 = v1 & 0x4000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x00161538
                                charge(ctx, 4);
                                v0 = 0x7E0000;
                                lhu(v0, v0, pad::kRepeat2);  // 0x7E095A
                                v0 = v0 & 0x4000;  // cursor + 1
                                v0 = sltu(0, v0);
                            }
                            // 0x00161548
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x00161550
                                charge(ctx, 3);
                                v0 = si(-2);
                                if (s3 != v0) {
                                    // 0x0016155c
                                    charge(ctx, 4);
                                    lw(v0, s0, skl::kTargetCount);
                                    v0 = addiu(v0, -1);
                                    if (s3 == v0) {
                                        // 0x00161598
                                        charge(ctx, 4);
                                        v0 = a0 & 0x4000;
                                        v0 = sltu(0, v0);
                                        if (v0 == 0) {
                                            // 0x001615a8
                                            charge(ctx, 4);
                                            v0 = 0x7E0000;
                                            lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                            v0 = v0 & 0x4000;  // cursor + 1
                                            v0 = sltu(0, v0);
                                        }
                                        // 0x001615b8
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x001615c0
                                            charge(ctx, 7);
                                            a0 = 0;
                                            a1 = 0;
                                            a2 = 0;
                                            a3 = 0;
                                            jal(ctx, 0x1615D0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                            sw(zero, s0, skl::kTargetCursor);
                                        }
                                    } else {
                                        // 0x0016156c
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x16157Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, skl::kTargetCursor);
                                        v0 = addiu(v0, 1);
                                        sw(v0, s0, skl::kTargetCursor);
                                    }
                                }
                            }
                        } else {
                            // 0x00161494
                            charge(ctx, 3);
                            v0 = si(-2);
                            if (s3 != v0) {
                                // 0x001614a0
                                charge(ctx, 2);
                                if (s3 == 0) {
                                    // 0x001614d4
                                    charge(ctx, 4);
                                    v0 = a0 & 0x1000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x001614e4
                                        charge(ctx, 4);
                                        v0 = 0x7E0000;
                                        lhu(v0, v0, pad::kTrig2);  // 0x7E0958
                                        v0 = v0 & 0x1000;  // cursor - 1
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x001614f4
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x001614fc
                                        charge(ctx, 11);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x16150Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                        lw(v0, s0, skl::kTargetCount);
                                        v0 = addiu(v0, -1);
                                        sw(v0, s0, skl::kTargetCursor);
                                    }
                                } else {
                                    // 0x001614a8
                                    charge(ctx, 11);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x1614B8u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                    lw(v0, s0, skl::kTargetCursor);
                                    v0 = addiu(v0, -1);
                                    sw(v0, s0, skl::kTargetCursor);
                                }
                            }
                        }
                    } else {
                        // 0x001612c4
                        charge(ctx, 12);
                        lw(a0, s0, skl::kList);
                        lw(v1, a0, 2016);
                        lw(v0, a0, 2020);
                        v1 = addu(v1, v0);
                        v0 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, a0);
                        lw(s1, v0, 12);
                        lhu(v0, s0, skl::kTargetKind);
                        if (v0 != 0) {
                            // 0x00161390
                            charge(ctx, 4);
                            s4 = 0;
                            s2 = 0;
                            for (;;) {
                                // 0x001613ec
                                charge(ctx, 4);
                                lw(v0, s0, skl::kTargetCount);
                                v0 = slt(s2, v0);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001613a0
                                charge(ctx, 8);
                                v0 = sll(s2, 2);
                                v0 = addu(s0, v0);
                                lw(s5, v0, 60);
                                a0 = s5;
                                jal(ctx, 0x1613B0u, gen::fn_sub_1C7CE0_001c7ce0);  // [K_FldUnit_IsPcNearHero]
                                if (v0 != 0) {
                                    // 0x001613c0
                                    charge(ctx, 9);
                                    a1 = dsll32(s5, 16);
                                    a1 = dsra32(a1, 16);
                                    a2 = s1 & 0xFFFF;
                                    a0 = 1;
                                    a3 = 0;
                                    jal(ctx, 0x1613D4u, gen::fn_sub_17BC20_0017bc20);
                                    if (v0 == 0) {
                                        // 0x001613e4
                                        charge(ctx, 1);
                                        s4 = 1;
                                    }
                                }
                                // 0x001613e8
                                charge(ctx, 1);
                                s2 = addiu(s2, 1);
                            }
                            // 0x001613fc
                            charge(ctx, 2);
                            if (s4 == 0) {
                                // 0x0016143c
                                charge(ctx, 8);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 8;
                                jal(ctx, 0x16144Cu, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                            } else {
                                // 0x00161404
                                charge(ctx, 14);
                                a0 = 1;
                                a1 = 0;
                                a2 = 3;
                                a3 = a0;
                                jal(ctx, 0x161414u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(a0, s0, skl::kList);
                                a1 = si(-2);
                                jal(ctx, 0x161424u, gen::fn_sub_15C520_0015c520);  // [H_Camp_SkillUseOnTarget]
                                v0 = 10;
                                sw(v0, s0, skl::kState);
                            }
                        } else {
                            // 0x001612f4
                            charge(ctx, 8);
                            v0 = sll(s3, 2);
                            v0 = addu(v0, s0);
                            lw(s2, v0, 60);
                            a0 = s2;
                            jal(ctx, 0x161304u, gen::fn_sub_1C7CE0_001c7ce0);  // [K_FldUnit_IsPcNearHero]
                            if (v0 != 0) {
                                // 0x00161314
                                charge(ctx, 9);
                                a1 = dsll32(s2, 16);
                                a1 = dsra32(a1, 16);
                                a2 = s1 & 0xFFFF;
                                a0 = 1;
                                a3 = 0;
                                jal(ctx, 0x161328u, gen::fn_sub_17BC20_0017bc20);
                                if (v0 != 0) {
                                    goto L_00161370;
                                }
                                // 0x00161338
                                charge(ctx, 14);
                                a0 = 1;
                                a1 = 0;
                                a2 = 3;
                                a3 = a0;
                                jal(ctx, 0x161348u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                                lw(a0, s0, skl::kList);
                                lw(a1, s0, skl::kTargetCursor);
                                jal(ctx, 0x161358u, gen::fn_sub_15C520_0015c520);  // [H_Camp_SkillUseOnTarget]
                                v0 = 10;
                                sw(v0, s0, skl::kState);
                                goto L_001615dc;
                            }
                        L_00161370:
                            charge(ctx, 8);
                            a0 = 0;
                            a1 = 0;
                            a2 = 0;
                            a3 = 8;
                            jal(ctx, 0x161380u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                        }
                    }
                } else {
                    // 0x00161290
                    charge(ctx, 10);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 2;
                    jal(ctx, 0x1612A0u, gen::fn_sub_10A4E0_0010a4e0);  // sound request (sound $a3)
                    v0 = 10;
                    sw(v0, s0, skl::kState);
                }
            L_001615dc:
                charge(ctx, 3);
                lw(v0, s0, skl::kTargetCursor);
                if (s3 != v0) {
                    // 0x001615e8
                    charge(ctx, 6);
                    a0 = s0;
                    a1 = s3;
                    jal(ctx, 0x1615F0u, gen::fn_sub_15EE40_0015ee40);
                }
            }
            goto L_00161690;
        case 0x161600u:  // table[10]: state 10: wait for flash 13, back to the list
            // 0x00161600
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x00161658
                charge(ctx, 3);
                v0 = slti(s1, 60);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0016160c
                charge(ctx, 8);
                lw(v1, s0, skl::kTweens);
                v0 = sll(s1, 4);
                v0 = addu(v0, s1);
                s2 = sll(v0, 2);
                a0 = addu(v1, s2);
                lw(v0, a0, 4);
                if (v0 != 0) {
                    // 0x0016162c
                    charge(ctx, 4);
                    jal(ctx, 0x16162Cu, gen::fn_sub_18B700_0018b700);  // [H_Camp_TweenStep] advance the tween; 1 while active
                    if (v0 != 0) {
                        // 0x0016163c
                        charge(ctx, 6);
                        lw(v0, s0, skl::kTweens);
                        a0 = addu(v0, s2);
                        a1 = s1;
                        a2 = s0;
                        jal(ctx, 0x16164Cu, gen::fn_sub_15FA90_0015fa90);
                    }
                }
                // 0x00161654
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00161664
            charge(ctx, 6);
            lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
            a1 = 13;
            jal(ctx, 0x16166Cu, gen::fn_sub_11E380_0011e380);  // [H_CampFlash_Request] (flash, n): 1 once transition n arrived
            if (v0 != 0) {
                // 0x0016167c
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x161680u, gen::fn_sub_15F320_0015f320);
                v0 = 6;
                sw(v0, s0, skl::kState);
            }
            goto L_00161690;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x00161694 (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        return;
    }
    goto L_00161690;
}

// 0x001618A0 sub_1618A0 -- 1212 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateFrStatusRootTask] Update of "H_CampFrStatusRoot" (the party-status root a script opens for one member;
// jump table): creates the two side-portrait tasks ("h_camp_pc_kani_control" / "h_camp_persona_kani_control") and the
// status page (sub_166A50); state 1 waits for the flash (sub_1685D0), 2 swaps the status page and the persona page
// (sub_167F40) on the page answer, 3 recreates them, 5 waits for the page task's end (-1). Draws the frame sprite of
// camp file 11.
void sub_1618A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x001618a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s3, a0, 60);
    lw(v1, s3, 0);
    v0 = 5;
    if (v1 != v0) {
        // 0x001618d8
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x00161b54
            charge(ctx, 4);
            lw(v1, s3, 4);
            v0 = 1;
            if (v1 == v0) {
                // 0x00161bc0
                charge(ctx, 12);
                lw(a0, s3, 20);
                jal(ctx, 0x161BC4u, gen::fn_sub_167F10_00167f10);
                sw(zero, s3, 4);
                lh(a2, s3, 12);
                a0 = s0;
                a1 = 6334;
                a3 = 0;
                t0 = 1;
                jal(ctx, 0x161BE4u, gen::fn_sub_166A50_00166a50);  // [H_Camp_CreatePartyStatusDrawTask]
                sw(v0, s3, 20);
            } else {
                // 0x00161b64
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00161b74
                    charge(ctx, 19);
                    lw(a0, s3, 20);
                    jal(ctx, 0x161B78u, gen::fn_sub_166C50_00166c50);
                    mtc1(zero, f12);
                    sw(zero, sp, 0x78);
                    sw(zero, sp, 0x7C);
                    v0 = 1;
                    sw(v0, s3, 4);
                    lh(a3, s3, 12);
                    a0 = s0;
                    a1 = 6334;
                    ld(a2, sp, 0x78);
                    t0 = 0;
                    t1 = 0;
                    jal(ctx, 0x161BACu, gen::fn_sub_167F40_00167f40);  // [H_Camp_CreateFrStatusPersonaDrawTask]
                    sw(v0, s3, 20);
                } else {
                    // 0x00161b6c
                    charge(ctx, 2);
                }
            }
            // 0x00161bf0
            charge(ctx, 4);
            v0 = 2;
            sw(v0, s3, 0);
        } else {
            // 0x001618e4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x00161a9c
                charge(ctx, 3);
                lw(v0, s3, 4);
                if (v0 != 0) {
                    // 0x00161abc
                    charge(ctx, 3);
                    lw(a0, s3, 20);
                    jal(ctx, 0x161AC0u, gen::fn_sub_167F30_00167f30);
                } else {
                    // 0x00161aa8
                    charge(ctx, 5);
                    lw(a0, s3, 20);
                    jal(ctx, 0x161AACu, gen::fn_sub_166C00_00166c00);
                }
                // 0x00161ac8
                charge(ctx, 3);
                v1 = si(-1);
                if (v0 != v1) {
                    // 0x00161b38
                    charge(ctx, 3);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00161b44
                        charge(ctx, 4);
                        v0 = 3;
                        sw(v0, s3, 0);
                    }
                } else {
                    // 0x00161ad4
                    charge(ctx, 4);
                    lw(v1, s3, 4);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00161b08
                        charge(ctx, 3);
                        lw(a0, s3, 20);
                        jal(ctx, 0x161B0Cu, gen::fn_sub_167EF0_00167ef0);
                    } else {
                        // 0x00161ae4
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x00161af4
                            charge(ctx, 5);
                            lw(a0, s3, 20);
                            jal(ctx, 0x161AF8u, gen::fn_sub_166C30_00166c30);
                        } else {
                            // 0x00161aec
                            charge(ctx, 2);
                        }
                    }
                    // 0x00161b14
                    charge(ctx, 9);
                    lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
                    a1 = 3;
                    jal(ctx, 0x161B1Cu, gen::fn_sub_1685E0_001685e0);  // [H_Camp_FrStatusFlashRequest]
                    sw(zero, s3, 44);
                    v0 = 5;
                    sw(v0, s3, 0);
                }
            } else {
                // 0x001618f0
                charge(ctx, 3);
                a0 = 1;
                if (v1 == a0) {
                    // 0x00161a6c
                    charge(ctx, 5);
                    lw(a0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
                    jal(ctx, 0x161A70u, gen::fn_sub_1685D0_001685d0);
                    if (v0 != 0) {
                        // 0x00161a80
                        charge(ctx, 7);
                        sw(zero, s3, 16);
                        v0 = 1;
                        sw(v0, s3, 44);
                        v0 = 2;
                        sw(v0, s3, 0);
                    }
                } else {
                    // 0x001618fc
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0016190c
                        charge(ctx, 11);
                        lh(s1, s3, 12);
                        s2 = 0x960000;
                        s2 = addiu(s2, rw::kCallocSlot);  // &0x960184: RwCalloc
                        a1 = 24;
                        a2 = 0x40000;
                        lw(v0, s2, 0);  // 0x960184
                        jalr(ctx, 0x161924u, v0.u());
                        s4 = v0;
                        if (s4 != 0) {
                            // 0x00161944
                            charge(ctx, 13);
                            a0 = s0;
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -20528);  // "h_camp_pc_kani_control"
                            a2 = 6337;
                            a3 = 0x120000;
                            a3 = addiu(a3, 8176);  // &sub_121FF0
                            t0 = 0x120000;
                            t0 = addiu(t0, 9776);  // &sub_122630
                            t1 = s4;
                            jal(ctx, 0x161968u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                            if (v0 != 0) {
                                // 0x00161984
                                charge(ctx, 2);
                                sw(zero, s4, 12);
                                sh(s1, s4, 20);
                            } else {
                                // 0x00161978
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x00161938
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x0016198c
                        charge(ctx, 17);
                        sw(v0, gp, g::kCampPcKani);  // 0x7CDF54
                        lw(v0, s3, 12);
                        s1 = dsll32(v0, 16);
                        s1 = dsra32(s1, 16);
                        a0 = v0 & 0xFFFF;
                        jal(ctx, 0x1619A0u, gen::fn_datPersonaGetByPcId_00174800);
                        s4 = v0;
                        a0 = 1;
                        a1 = 28;
                        a2 = 0x40000;
                        lw(v0, s2, 0);
                        jalr(ctx, 0x1619BCu, v0.u());
                        s2 = v0;
                        if (s2 != 0) {
                            // 0x001619dc
                            charge(ctx, 13);
                            a0 = s0;
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -20496);  // "h_camp_persona_kani_control"
                            a2 = 6337;
                            a3 = 0x120000;
                            a3 = addiu(a3, 10560);  // &sub_122940
                            t0 = 0x120000;
                            t0 = addiu(t0, 12240);  // &sub_122FD0
                            t1 = s2;
                            jal(ctx, 0x161A00u, gen::fn_kwlnTaskCreate_00194b20);  // (parent, name, priority, update, destroy, work)
                            if (v0 != 0) {
                                // 0x00161a1c
                                charge(ctx, 3);
                                sw(zero, s2, 12);
                                sw(s4, s2, 16);
                                sh(s1, s2, 24);
                            } else {
                                // 0x00161a10
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x001619d0
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00161a28
                        charge(ctx, 17);
                        sw(v0, gp, g::kCampPersonaKani);  // 0x7CDF58
                        sw(zero, s3, 4);
                        lh(a2, s3, 12);
                        a0 = s0;
                        a1 = 6334;
                        a3 = 0;
                        t0 = 0;
                        jal(ctx, 0x161A44u, gen::fn_sub_166A50_00166a50);  // [H_Camp_CreatePartyStatusDrawTask]
                        sw(v0, s3, 20);
                        v0 = 0x43A00000;  // 320.0f
                        sw(v0, s3, 36);
                        sw(zero, s3, 40);
                        v0 = 1;
                        sw(v0, s3, 0);
                    } else {
                        // 0x00161904
                        charge(ctx, 2);
                    }
                }
            }
        }
        goto L_00161c24;
    }
    // 0x00161c00
    charge(ctx, 6);
    lw(a0, s3, 20);
    jal(ctx, 0x161C04u, gen::fn_kwlnTaskGetState_00195290);
    v1 = 3;
    if (v0 != v1) {
    L_00161c24:
        charge(ctx, 3);
        lw(v0, s3, 44);
        if (v0 != 0) {
            // 0x00161c30
            charge(ctx, 6);
            lw(v0, s3, 16);
            v0 = addiu(v0, 1);
            sw(v0, s3, 16);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x00161c48
                charge(ctx, 2);
                v0 = 10;
                sw(v0, s3, 16);
            }
            // 0x00161c50
            charge(ctx, 25);
            lw(v1, s3, 16);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            s0 = subu(v0, v1);
            a3 = s0 & 0xFF;
            v0 = 0x42C80000;  // 100.0f
            mtc1(v0, f14);
            a0 = s5;
            v0 = 0x830000;
            lw(a1, v0, spr::camp(11));  // 0x833B9C: camp sprite file 11
            a2 = 0;
            lwc1(f12, s3, 36);
            lwc1(f13, s3, 40);
            jal(ctx, 0x161C94u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            lwc1(f1, s3, 36);
            mtc1(zero, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x00161cb4
                charge(ctx, 14);
                v0 = 0x44200000;  // 640.0f
                mtc1(v0, f0);
                add_s(f12, f0, f1);
                a3 = s0 & 0xFF;
                v0 = 0x42C80000;  // 100.0f
                mtc1(v0, f14);
                a0 = s5;
                v0 = 0x830000;
                lw(a1, v0, spr::camp(11));  // 0x833B9C: camp sprite file 11
                a2 = 0;
                lwc1(f13, s3, 40);
                jal(ctx, 0x161CE4u, gen::fn_sprDrawSpriteBasic_001159f0);  // draw sprite $a2 of file $a1 at ($f12, $f13), z $f14, alpha $a3
            }
            // 0x00161cec
            charge(ctx, 12);
            lwc1(f1, s3, 36);
            v0 = 0x3F800000;  // 1.0f
            mtc1(v0, f0);
            sub_s(f1, f1, f0);
            swc1(f1, s3, 36);
            v0 = lui(0xC420);
            mtc1(v0, f0);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x00161d1c
                charge(ctx, 5);
                v0 = 0x44200000;  // 640.0f
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, s3, 36);
            }
        }
        // 0x00161d30
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00161c18
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x00161d34 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

}  // namespace p3fes::game
