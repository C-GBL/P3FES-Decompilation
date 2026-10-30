// Phase 5 slice boot, part 2 (boot_panels.h): the party / area panels, their boot loaders, the tween stepper, the
// fusion-spell and battle member cut-ins, 0x18A3F0-0x18F0E0. Started from p3fes_handgen's bodies (register for register,
// block for block as the recompiled ones; game/include/p3fes/game/hg_cpu.h) and made readable on top: a role comment per
// function, structured control flow (the jump-table state machines' shared "return 0" blocks become host flags),
// block roles. Every path keeps the original's statements, charges and check points in order; tests/game/
// test_boot_panels.cpp pairs them.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/boot_panels.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_CacheAddArchive_00102720(p3fes::EEContext&);
void fn_H_Cdvd_CacheRemove_00102870(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_fptodp_00530da0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprGetSpriteHeight_00112740(p3fes::EEContext&);
void fn_sprGetSpriteWidth_001126b0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_111150_00111150(p3fes::EEContext&);
void fn_sub_111380_00111380(p3fes::EEContext&);
void fn_sub_1114B0_001114b0(p3fes::EEContext&);
void fn_sub_111500_00111500(p3fes::EEContext&);
void fn_sub_111520_00111520(p3fes::EEContext&);
void fn_sub_111530_00111530(p3fes::EEContext&);
void fn_sub_1115B0_001115b0(p3fes::EEContext&);
void fn_sub_1115E0_001115e0(p3fes::EEContext&);
void fn_sub_1120C0_001120c0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_113D80_00113d80(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_114AF0_00114af0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115AD0_00115ad0(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C5F0_0016c5f0(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_18A3F0_0018a3f0(p3fes::EEContext&);
void fn_sub_18A9C0_0018a9c0(p3fes::EEContext&);
void fn_sub_18A9F0_0018a9f0(p3fes::EEContext&);
void fn_sub_18B270_0018b270(p3fes::EEContext&);
void fn_sub_18B360_0018b360(p3fes::EEContext&);
void fn_sub_18B380_0018b380(p3fes::EEContext&);
void fn_sub_18B5F0_0018b5f0(p3fes::EEContext&);
void fn_sub_18B620_0018b620(p3fes::EEContext&);
void fn_sub_18B6D0_0018b6d0(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18B7B0_0018b7b0(p3fes::EEContext&);
void fn_sub_18BA60_0018ba60(p3fes::EEContext&);
void fn_sub_18BB20_0018bb20(p3fes::EEContext&);
void fn_sub_18BB80_0018bb80(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_18BC80_0018bc80(p3fes::EEContext&);
void fn_sub_18BD90_0018bd90(p3fes::EEContext&);
void fn_sub_18BEE0_0018bee0(p3fes::EEContext&);
void fn_sub_18BFA0_0018bfa0(p3fes::EEContext&);
void fn_sub_18BFF0_0018bff0(p3fes::EEContext&);
void fn_sub_18C0A0_0018c0a0(p3fes::EEContext&);
void fn_sub_18C0C0_0018c0c0(p3fes::EEContext&);
void fn_sub_18C150_0018c150(p3fes::EEContext&);
void fn_sub_18C780_0018c780(p3fes::EEContext&);
void fn_sub_18CE50_0018ce50(p3fes::EEContext&);
void fn_sub_18D320_0018d320(p3fes::EEContext&);
void fn_sub_18DB20_0018db20(p3fes::EEContext&);
void fn_sub_18DDE0_0018dde0(p3fes::EEContext&);
void fn_sub_18DE60_0018de60(p3fes::EEContext&);
void fn_sub_18E330_0018e330(p3fes::EEContext&);
void fn_sub_18E390_0018e390(p3fes::EEContext&);
void fn_sub_18E490_0018e490(p3fes::EEContext&);
void fn_sub_18E4A0_0018e4a0(p3fes::EEContext&);
void fn_sub_18E540_0018e540(p3fes::EEContext&);
void fn_sub_18E5C0_0018e5c0(p3fes::EEContext&);
void fn_sub_18E7A0_0018e7a0(p3fes::EEContext&);
void fn_sub_18E820_0018e820(p3fes::EEContext&);
void fn_sub_18E8E0_0018e8e0(p3fes::EEContext&);
void fn_sub_18EB30_0018eb30(p3fes::EEContext&);
void fn_sub_18EB40_0018eb40(p3fes::EEContext&);
void fn_sub_18EF60_0018ef60(p3fes::EEContext&);
void fn_sub_18EFB0_0018efb0(p3fes::EEContext&);
void fn_sub_18F060_0018f060(p3fes::EEContext&);
void fn_sub_18F080_0018f080(p3fes::EEContext&);
void fn_sub_18F0A0_0018f0a0(p3fes::EEContext&);
void fn_sub_18F0B0_0018f0b0(p3fes::EEContext&);
void fn_sub_18F0C0_0018f0c0(p3fes::EEContext&);
void fn_sub_18F0E0_0018f0e0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x0018A3F0 sub_18A3F0 -- 1480 bytes; frame 0x10: ra sp+0x0
// sub_18A3F0(task) [H_MixWord5Draw] ("h_mix_word5_draw", made by sub_18B380): the fifth word of the fusion-spell
// (mix raid) cut-in. Work: +0 phase, +4 phase timer, +8 total timer, +12 the sprite. Both timers advance every frame;
// phase 0 waits 3 frames (then both reset), 1 waits to 17, phases 2..6 end at 20 / 22 / 26 / 28 / 39 and draw the
// sprite full-screen (sub_1140D0, white) scaled ((5 t / 50 + 90) percent, 4.12 fixed point); phase 7 fades it out
// over 11 frames (alpha 255 - 255 (t - 39) / 11) and ends the task (-1) at t = 50. A jump table on the phase.
void sub_18A3F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018a3f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(v1, v0, 4);
    v1 = addiu(v1, 1);
    sw(v1, v0, 4);
    lw(v1, v0, 8);
    v1 = addiu(v1, 1);
    sw(v1, v0, 8);
    lw(v1, v0, 0);
    at = sltiu(v1, 8);
    bool ended = false;  // host-side: the paths that skip the shared "return 0" block (0x0018a9a4)
    if (at != 0) {
        // 0x0018a424
        charge(ctx, 7);
        a0 = 0x7B0000;
        a0 = addiu(a0, 26784);  // &0x7B68A0
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x18A440u:  // table[0]
            // 0x0018a440
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 3;
            if (a0 == v1) {
                // 0x0018a450
                charge(ctx, 6);
                sw(zero, v0, 4);
                sw(zero, v0, 8);
                v1 = 1;
                sw(v1, v0, 0);
            }
            break;
        case 0x18A468u:  // table[1]
            // 0x0018a468
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 17;
            if (a0 == v1) {
                // 0x0018a478
                charge(ctx, 4);
                v1 = 2;
                sw(v1, v0, 0);
            }
            break;
        case 0x18A488u:  // table[2]
            // 0x0018a488
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 20;
            if (a0 == v1) {
                // 0x0018a498
                charge(ctx, 2);
                v1 = 3;
                sw(v1, v0, 0);
            }
            // 0x0018a4a0
            charge(ctx, 35);
            lw(v1, v0, 4);
            a0 = addiu(v1, -18);
            mtc1(zero, f1);
            v1 = 419;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x40000000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f0, f0);
            mul_s(f0, f1, f0);
            div_s(f1, f0, f1);
            v1 = 273;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            a0 = addu(v1, a0);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 6);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a52c
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a534
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A544u, gen::fn_sub_1140D0_001140d0);
            break;
        case 0x18A554u:  // table[3]
            // 0x0018a554
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 22;
            if (a0 == v1) {
                // 0x0018a564
                charge(ctx, 2);
                v1 = 4;
                sw(v1, v0, 0);
            }
            // 0x0018a56c
            charge(ctx, 42);
            lw(v1, v0, 4);
            a0 = addiu(v1, -20);
            v1 = 0x40800000;
            mtc1(v1, f1);
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            mul_s(f0, f1, f3);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f0, f2);
            v1 = 419;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x41100000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 271;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            a0 = addu(v1, a0);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 6);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a614
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a61c
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A62Cu, gen::fn_sub_1140D0_001140d0);
            break;
        case 0x18A63Cu:  // table[4]
            // 0x0018a63c
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 26;
            if (a0 == v1) {
                // 0x0018a64c
                charge(ctx, 2);
                v1 = 5;
                sw(v1, v0, 0);
            }
            // 0x0018a654
            charge(ctx, 35);
            lw(v1, v0, 4);
            v1 = addiu(v1, -22);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40800000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 423;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            mul_s(f0, f2, f3);
            div_s(f1, f0, f2);
            v1 = 0x438C0000;
            mtc1(v1, f0);
            sub_s(f14, f0, f1);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            a0 = addu(v1, a0);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 6);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a6e0
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a6e8
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A6F8u, gen::fn_sub_1140D0_001140d0);
            break;
        case 0x18A708u:  // table[5]
            // 0x0018a708
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 28;
            if (a0 == v1) {
                // 0x0018a718
                charge(ctx, 2);
                v1 = 6;
                sw(v1, v0, 0);
            }
            // 0x0018a720
            charge(ctx, 37);
            lw(v1, v0, 4);
            v1 = addiu(v1, -26);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
            v1 = 0x40000000;
            mtc1(v1, f2);
            div_s(f1, f3, f2);
            v1 = 0x43D60000;
            mtc1(v1, f0);
            add_s(f13, f1, f0);
            v1 = 0x41200000;
            mtc1(v1, f0);
            mul_s(f0, f0, f3);
            div_s(f1, f0, f2);
            v1 = 0x438A0000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            a0 = addu(v1, a0);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 6);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a7b4
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a7bc
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A7CCu, gen::fn_sub_1140D0_001140d0);
            break;
        case 0x18A7DCu:  // table[6]
            // 0x0018a7dc
            charge(ctx, 4);
            lw(a0, v0, 4);
            v1 = 39;
            if (a0 == v1) {
                // 0x0018a7ec
                charge(ctx, 2);
                v1 = 7;
                sw(v1, v0, 0);
            }
            // 0x0018a7f4
            charge(ctx, 38);
            lw(v1, v0, 4);
            a0 = addiu(v1, -28);
            v1 = 0x41B00000;
            mtc1(v1, f3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
            mul_s(f0, f3, f2);
            div_s(f1, f0, f3);
            v1 = 429;
            mtc1(v1, f0);
            cvt_s_w(f0, f0);
            add_s(f13, f1, f0);
            v1 = 0x41900000;
            mtc1(v1, f0);
            mul_s(f0, f0, f2);
            div_s(f1, f0, f3);
            v1 = 0x438F0000;
            mtc1(v1, f0);
            add_s(f14, f1, f0);
            lw(a0, v0, 8);
            v1 = sll(a0, 2);
            a0 = addu(v1, a0);
            v1 = 50;
            div(a0, v1);
            mflo(v1);
            v1 = addiu(v1, 90);
            a0 = sll(v1, 12);
            v1 = 100;
            div(a0, v1);
            mflo(v1);
            v1 = sll(v1, 6);
            a1 = sra(v1, 12);
            if (i64(v1) < 0) {
                // 0x0018a88c
                charge(ctx, 2);
                v1 = addiu(v1, 4095);
                a1 = sra(v1, 12);
            }
            // 0x0018a894
            charge(ctx, 8);
            mtc1(zero, f12);
            a0 = si(-1);
            a2 = a1;
            lw(a3, v0, 12);
            jal(ctx, 0x18A8A4u, gen::fn_sub_1140D0_001140d0);
            break;
        case 0x18A8B4u:  // table[7]
            // 0x0018a8b4
            charge(ctx, 4);
            lw(a2, v0, 4);
            a1 = 50;
            if (a2 != a1) {
                // 0x0018a8d0
                charge(ctx, 44);
                a0 = addiu(a2, -28);
                v1 = 0x41B00000;
                mtc1(v1, f3);
                mtc1(a0, f0);
                cvt_s_w(f2, f0);
                mul_s(f0, f3, f2);
                div_s(f1, f0, f3);
                v1 = 429;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f13, f1, f0);
                v1 = 0x41900000;
                mtc1(v1, f0);
                mul_s(f0, f0, f2);
                div_s(f1, f0, f3);
                v1 = 0x438F0000;
                mtc1(v1, f0);
                add_s(f14, f1, f0);
                a0 = addiu(a2, -39);
                v1 = sll(a0, 8);
                a0 = subu(v1, a0);
                v1 = 11;
                div(a0, v1);
                mflo(a0);
                v1 = 255;
                a2 = subu(v1, a0);
                lw(a0, v0, 8);
                v1 = sll(a0, 2);
                v1 = addu(v1, a0);
                div1(v1, a1);
                mflo1(v1);
                v1 = addiu(v1, 90);
                a0 = sll(v1, 12);
                v1 = 100;
                div(a0, v1);
                mflo(v1);
                v1 = sll(v1, 6);
                a1 = sra(v1, 12);
                if (i64(v1) < 0) {
                    // 0x0018a980
                    charge(ctx, 2);
                    v1 = addiu(v1, 4095);
                    a1 = sra(v1, 12);
                }
                // 0x0018a988
                charge(ctx, 7);
                mtc1(zero, f12);
                v1 = si(-256);
                a0 = a2 | v1;
                a2 = a1;
                lw(a3, v0, 12);
                jal(ctx, 0x18A99Cu, gen::fn_sub_1140D0_001140d0);
                break;
            }
            // 0x0018a8c4
            charge(ctx, 3);
            v0 = si(-1);
            ended = true;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    if (!ended) {
        // 0x0018a9a4: keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0018a9a8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0018A9C0 sub_18A9C0 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_18A9C0(task) [H_MixDestroyWork]: the shared destroy callback of the five h_mix_word draw tasks: RwFree(work).
void sub_18A9C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018a9c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18A9D4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0018A9F0 sub_18A9F0 -- 2172 bytes; frame 0x190: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// sub_18A9F0(task) [H_PerEfcMixraidUpdate] ("H_PerEfcMixraidDraw", h_permixefc.c): the fusion-spell cut-in. Work
// (2,676 bytes): +0 step, +4 the spell id (0x110..0x121), +8 its index 0..17, +20..+28 three animation tasks, +32..+44
// four texture builds, +48..+60 their textures, +64 the archive node, three 868-byte file records from +340, +2672 the
// frame counter.
//   0: index = id - 0x110 (a jump table; other ids keep the index); requests "battle/cutin/per_mix%02d.bin" as an
//      archive; step 1;
//   1: when loaded: files 4..6 of the archive into the three records, each added to the cache under "battle/cutin/";
//      three animation tasks (sub_111380, priority 0x18BF) on the records; step 2;
//   2: when the three are ready (sub_1114B0): four texture builds (sub_10C1A0) of "battle/cutin/mixraid/m_flash.tmx",
//      "m_glow.tmx", "m_word01.tmx", "m_word02.tmx" (h_permixefc.c lines 1062..1065); step 3;
//   3: polls the builds (sub_10C3A0) until all four textures exist; step 4 (sub_18B380 then starts the words, step 5);
//   5: the 80-frame show: the screen flashes (sub_113A30 colour fills, frames 6..8 and 9..64), the animation tasks
//      are drawn while alive (sub_1115B0 / sub_1115E0) and destroyed at frame 70, the glow and flash textures are
//      blended over the screen (sub_114AF0, frames 6..69 and 50..69), a white fade (sub_113D80) in 55..79; at frame 80
//      the task ends (-1).
void sub_18A9F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018a9f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s2 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    at = sltiu(v0, 6);
    bool first_flash = false;  // host-side (step 5): frames 6..8 skip the 9..64 flash test
    bool ended = false;  // host-side: the paths that skip the shared "return 0" block (0x0018b244)
    if (at != 0) {
        // 0x0018aa24
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 26896);  // &0x7B6910
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x18AA40u:  // table[0]
            // 0x0018aa40
            charge(ctx, 5);
            lw(v0, s0, 4);
            v0 = addiu(v0, -272);
            at = sltiu(v0, 18);
            if (at != 0) {
                // 0x0018aa54
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 26816);  // &0x7B68C0
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x18AA70u:  // table[0]
                    // 0x0018aa70
                    charge(ctx, 3);
                    sw(zero, s0, 8);
                    break;
                case 0x18AA7Cu:  // table[1]
                    // 0x0018aa7c
                    charge(ctx, 4);
                    v0 = 1;
                    sw(v0, s0, 8);
                    break;
                case 0x18AA8Cu:  // table[2]
                    // 0x0018aa8c
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, s0, 8);
                    break;
                case 0x18AA9Cu:  // table[3]
                    // 0x0018aa9c
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, 8);
                    break;
                case 0x18AAACu:  // table[4]
                    // 0x0018aaac
                    charge(ctx, 4);
                    v0 = 4;
                    sw(v0, s0, 8);
                    break;
                case 0x18AABCu:  // table[5]
                    // 0x0018aabc
                    charge(ctx, 4);
                    v0 = 5;
                    sw(v0, s0, 8);
                    break;
                case 0x18AACCu:  // table[6]
                    // 0x0018aacc
                    charge(ctx, 4);
                    v0 = 6;
                    sw(v0, s0, 8);
                    break;
                case 0x18AADCu:  // table[7]
                    // 0x0018aadc
                    charge(ctx, 4);
                    v0 = 7;
                    sw(v0, s0, 8);
                    break;
                case 0x18AAECu:  // table[8]
                    // 0x0018aaec
                    charge(ctx, 4);
                    v0 = 8;
                    sw(v0, s0, 8);
                    break;
                case 0x18AAFCu:  // table[9]
                    // 0x0018aafc
                    charge(ctx, 4);
                    v0 = 9;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB0Cu:  // table[10]
                    // 0x0018ab0c
                    charge(ctx, 4);
                    v0 = 10;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB1Cu:  // table[11]
                    // 0x0018ab1c
                    charge(ctx, 4);
                    v0 = 11;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB2Cu:  // table[12]
                    // 0x0018ab2c
                    charge(ctx, 4);
                    v0 = 12;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB3Cu:  // table[13]
                    // 0x0018ab3c
                    charge(ctx, 4);
                    v0 = 13;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB4Cu:  // table[14]
                    // 0x0018ab4c
                    charge(ctx, 4);
                    v0 = 14;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB5Cu:  // table[15]
                    // 0x0018ab5c
                    charge(ctx, 4);
                    v0 = 15;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB6Cu:  // table[16]
                    // 0x0018ab6c
                    charge(ctx, 4);
                    v0 = 16;
                    sw(v0, s0, 8);
                    break;
                case 0x18AB7Cu:  // table[17]
                    // 0x0018ab7c
                    charge(ctx, 2);
                    v0 = 17;
                    sw(v0, s0, 8);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x0018ab84
            charge(ctx, 15);
            a0 = addiu(sp, 0x80);
            a1 = 0x5E0000;
            a1 = addiu(a1, 17344);  // "battle/cutin/per_mix%02d.bin"
            lw(a2, s0, 8);
            jal(ctx, 0x18AB94u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x80);
            a1 = 1;
            jal(ctx, 0x18ABA4u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 64);
            v0 = 1;
            sw(v0, s0, 0);
            break;
        case 0x18ABC0u:  // table[1]
            // 0x0018abc0
            charge(ctx, 5);
            lw(a0, s0, 64);
            jal(ctx, 0x18ABC4u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0018abd4
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x0018ac2c
                    charge(ctx, 3);
                    v0 = slti(s1, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0018abe0
                    charge(ctx, 19);
                    v0 = sll(s1, 5);
                    v1 = subu(v0, s1);
                    v0 = sll(v1, 3);
                    v0 = subu(v0, v1);
                    v0 = sll(v0, 2);
                    v0 = addu(s0, v0);
                    s3 = addiu(v0, 340);
                    a1 = addiu(s1, 4);
                    lw(a0, s0, 64);
                    a2 = addiu(v0, 348);
                    jal(ctx, 0x18AC08u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    sw(v0, s3, 0);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, 17376);  // "battle/cutin/"
                    a1 = v0;
                    jal(ctx, 0x18AC20u, gen::fn_H_Cdvd_CacheAddArchive_00102720);
                    s1 = addiu(s1, 1);
                }
                // 0x0018ac38
                charge(ctx, 8);
                v0 = 41;
                sh(v0, sp, 0x180);
                v0 = 1;
                sh(v0, sp, 0x182);
                lw(v1, s0, 8);
                at = slti(v1, 9);
                if (at == 0) {
                    // 0x0018ac70
                    charge(ctx, 4);
                    v0 = 11;
                    sh(v0, sp, 0x184);
                    v0 = addiu(v1, -9);
                    sh(v0, sp, 0x186);
                } else {
                    // 0x0018ac58
                    charge(ctx, 6);
                    v0 = 10;
                    sh(v0, sp, 0x184);
                    v0 = addiu(v1, 1);
                    sh(v0, sp, 0x186);
                }
                // 0x0018ac80
                charge(ctx, 34);
                a0 = s2;
                a1 = 6335;
                ld(a2, sp, 0x180);
                a3 = addiu(s0, 936);
                jal(ctx, 0x18AC90u, gen::fn_sub_111380_00111380);
                sw(v0, s0, 20);
                v0 = 2;
                sh(v0, sp, 0x182);
                a0 = s2;
                a1 = 6335;
                ld(a2, sp, 0x180);
                a3 = addiu(s0, 1804);
                jal(ctx, 0x18ACB4u, gen::fn_sub_111380_00111380);
                sw(v0, s0, 24);
                v0 = 41;
                sh(v0, sp, 0x180);
                v0 = 1;
                sh(v0, sp, 0x182);
                v0 = 10;
                sh(v0, sp, 0x184);
                sh(zero, sp, 0x186);
                a0 = s2;
                a1 = 6335;
                ld(a2, sp, 0x180);
                a3 = addiu(s0, 68);
                jal(ctx, 0x18ACECu, gen::fn_sub_111380_00111380);
                sw(v0, s0, 28);
                v0 = 2;
                sw(v0, s0, 0);
            }
            break;
        case 0x18AD08u:  // table[2]
            // 0x0018ad08
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x0018ad3c
                charge(ctx, 3);
                v0 = slti(s2, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0018ad18
                charge(ctx, 7);
                v0 = sll(s2, 2);
                v0 = addu(s0, v0);
                lw(a0, v0, 20);
                jal(ctx, 0x18AD24u, gen::fn_sub_1114B0_001114b0);
                if (v0 == 0) {
                    // 0x0018ad34
                    charge(ctx, 1);
                    s1 = 0;
                }
                // 0x0018ad38
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0018ad48
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0018ad50
                charge(ctx, 80);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, 17432);  // "h_permixefc.c"
                sd(v0, sp, 0x10);
                v0 = 1062;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, 17392);  // "battle/cutin/mixraid/m_flash.tmx"
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x18AD90u, gen::fn_sub_10C1A0_0010c1a0);
                sw(v0, s0, 32);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, 17432);  // "h_permixefc.c"
                sd(v0, sp, 0x10);
                v0 = 1063;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, 17456);  // "battle/cutin/mixraid/m_glow.tmx"
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x18ADDCu, gen::fn_sub_10C1A0_0010c1a0);
                sw(v0, s0, 36);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, 17432);  // "h_permixefc.c"
                sd(v0, sp, 0x10);
                v0 = 1064;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, 17488);  // "battle/cutin/mixraid/m_word01.tmx"
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x18AE28u, gen::fn_sub_10C1A0_0010c1a0);
                sw(v0, s0, 40);
                sd(zero, sp, 0x0);
                sd(zero, sp, 0x8);
                v0 = 0x5E0000;
                v0 = addiu(v0, 17432);  // "h_permixefc.c"
                sd(v0, sp, 0x10);
                v0 = 1065;
                sd(v0, sp, 0x18);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, 17536);  // "battle/cutin/mixraid/m_word02.tmx"
                a2 = 0;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x18AE74u, gen::fn_sub_10C1A0_0010c1a0);
                sw(v0, s0, 44);
                v0 = 3;
                sw(v0, s0, 0);
            }
            break;
        case 0x18AE90u:  // table[3]
            // 0x0018ae90
            charge(ctx, 4);
            s1 = 1;
            s2 = 0;
            for (;;) {
                // 0x0018aeec
                charge(ctx, 3);
                v0 = slti(s2, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0018aea0
                charge(ctx, 6);
                v0 = sll(s2, 2);
                s4 = addu(s0, v0);
                s3 = addiu(s4, 32);
                lw(a0, s4, 32);
                if (a0 != 0) {
                    // 0x0018aeb8
                    charge(ctx, 8);
                    a1 = addiu(sp, 0x18C);
                    a2 = 0;
                    jal(ctx, 0x18AEC0u, gen::fn_sub_10C3A0_0010c3a0);
                    sw(v0, s4, 48);
                    lw(v0, sp, 0x18C);
                    if (v0 == 0) {
                        // 0x0018aee4
                        charge(ctx, 1);
                        s1 = 0;
                    } else {
                        // 0x0018aed8
                        charge(ctx, 3);
                        sw(zero, s3, 0);
                    }
                }
                // 0x0018aee8
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0018aef8
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0018af00
                charge(ctx, 4);
                v0 = 4;
                sw(v0, s0, 0);
            }
            break;
        case 0x18AF10u:  // table[5]
            // 0x0018af10
            charge(ctx, 6);
            lw(v0, s0, 2672);
            v1 = addiu(v0, 1);
            sw(v1, s0, 2672);
            v0 = 70;
            if (v1 == v0) {
                // 0x0018af28
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x0018af80
                    charge(ctx, 3);
                    v0 = slti(s1, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0018af34
                    charge(ctx, 6);
                    v0 = sll(s1, 2);
                    v0 = addu(s0, v0);
                    s2 = addiu(v0, 20);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x0018af4c
                        charge(ctx, 5);
                        jal(ctx, 0x18AF4Cu, gen::fn_kwlnTaskGetState_00195290);
                        v1 = 3;
                        if (v0 == v1) {
                            // 0x0018af60
                            charge(ctx, 1);
                            sw(zero, s2, 0);
                        }
                    }
                    // 0x0018af64
                    charge(ctx, 3);
                    lw(a0, s2, 0);
                    if (a0 != 0) {
                        // 0x0018af70
                        charge(ctx, 2);
                        jal(ctx, 0x18AF70u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                    // 0x0018af78
                    charge(ctx, 2);
                    sw(zero, s2, 0);
                    s1 = addiu(s1, 1);
                }
            }
            // 0x0018af8c: the screen flash -- colour 0x0F395603 in frames 6..8, 0x0F3956FF in frames 9..64
            charge(ctx, 4);
            lw(v1, s0, 2672);
            v0 = slti(v1, 6);
            first_flash = false;
            if (v0 == 0) {
                // 0x0018af9c
                charge(ctx, 3);
                at = slti(v1, 9);
                if (at != 0) {
                    // 0x0018afa8
                    charge(ctx, 12);
                    v0 = 0x42C80000;
                    mtc1(v0, f12);
                    mtc1(zero, f13);
                    v0 = 0xF390000;
                    a0 = v0 | 0x5603;
                    mov_s(f14, f13);
                    a1 = 640;
                    a2 = 448;
                    jal(ctx, 0x18AFC8u, gen::fn_sub_113A30_00113a30);
                    first_flash = true;
                }
            }
            if (!first_flash) {
                // 0x0018afd8
                charge(ctx, 3);
                v0 = slti(v1, 9);
                if (v0 == 0) {
                    // 0x0018afe4
                    charge(ctx, 3);
                    at = slti(v1, 65);
                    if (at != 0) {
                        // 0x0018aff0
                        charge(ctx, 10);
                        v0 = 0x42C80000;
                        mtc1(v0, f12);
                        mtc1(zero, f13);
                        v0 = 0xF390000;
                        a0 = v0 | 0x56FF;
                        mov_s(f14, f13);
                        a1 = 640;
                        a2 = 448;
                        jal(ctx, 0x18B010u, gen::fn_sub_113A30_00113a30);
                    }
                }
            }
            // 0x0018b018: the two animation tasks drawn while they run
            charge(ctx, 3);
            s1 = 0;
            for (;;) {
                // 0x0018b084
                charge(ctx, 3);
                v0 = slti(s1, 2);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0018b024
                charge(ctx, 6);
                v0 = sll(s1, 2);
                v0 = addu(s0, v0);
                s2 = addiu(v0, 20);
                lw(a0, v0, 20);
                if (a0 != 0) {
                    // 0x0018b03c
                    charge(ctx, 5);
                    jal(ctx, 0x18B03Cu, gen::fn_kwlnTaskGetState_00195290);
                    v1 = 3;
                    if (v0 == v1) {
                        // 0x0018b050
                        charge(ctx, 1);
                        sw(zero, s2, 0);
                    }
                }
                // 0x0018b054
                charge(ctx, 3);
                lw(a0, s2, 0);
                if (a0 != 0) {
                    // 0x0018b060
                    charge(ctx, 8);
                    v0 = sll(s1, 2);
                    v0 = addu(s0, v0);
                    s2 = addiu(v0, 20);
                    jal(ctx, 0x18B06Cu, gen::fn_sub_1115B0_001115b0);
                    lw(a0, s2, 0);
                    jal(ctx, 0x18B078u, gen::fn_sub_1115E0_001115e0);
                }
                // 0x0018b080
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0018b090
            charge(ctx, 4);
            lw(v1, s0, 2672);
            v0 = slti(v1, 6);
            if (v0 == 0) {
                // 0x0018b0a0
                charge(ctx, 3);
                at = slti(v1, 70);
                if (at != 0) {
                    // 0x0018b0ac
                    charge(ctx, 10);
                    v0 = 0x42C60000;
                    mtc1(v0, f12);
                    mtc1(zero, f13);
                    a0 = si(-1);
                    mov_s(f14, f13);
                    a1 = 640;
                    a2 = 448;
                    lw(a3, s0, 52);
                    jal(ctx, 0x18B0CCu, gen::fn_sub_114AF0_00114af0);
                }
            }
            // 0x0018b0d4
            charge(ctx, 3);
            lw(a0, s0, 28);
            if (a0 != 0) {
                // 0x0018b0e0
                charge(ctx, 5);
                jal(ctx, 0x18B0E0u, gen::fn_kwlnTaskGetState_00195290);
                v1 = 3;
                if (v0 == v1) {
                    // 0x0018b0f4
                    charge(ctx, 1);
                    sw(zero, s0, 28);
                }
            }
            // 0x0018b0f8
            charge(ctx, 3);
            lw(a0, s0, 28);
            if (a0 != 0) {
                // 0x0018b104
                charge(ctx, 5);
                jal(ctx, 0x18B104u, gen::fn_sub_1115B0_001115b0);
                lw(a0, s0, 28);
                jal(ctx, 0x18B110u, gen::fn_sub_1115E0_001115e0);
            }
            // 0x0018b118
            charge(ctx, 4);
            lw(v1, s0, 2672);
            v0 = slti(v1, 50);
            if (v0 == 0) {
                // 0x0018b128
                charge(ctx, 3);
                at = slti(v1, 70);
                if (at != 0) {
                    // 0x0018b134
                    charge(ctx, 18);
                    v1 = addiu(v1, -50);
                    v0 = sll(v1, 8);
                    v1 = subu(v0, v1);
                    v0 = 15;
                    div(v1, v0);
                    mflo(v1);
                    v0 = 0x42C40000;
                    mtc1(v0, f12);
                    v0 = si(-256);
                    a0 = v1 | v0;
                    mtc1(zero, f13);
                    mov_s(f14, f13);
                    a1 = 640;
                    a2 = 448;
                    lw(a3, s0, 48);
                    jal(ctx, 0x18B174u, gen::fn_sub_114AF0_00114af0);
                }
            }
            // 0x0018b17c
            charge(ctx, 4);
            lw(v1, s0, 2672);
            v0 = slti(v1, 55);
            if (v0 == 0) {
                // 0x0018b18c
                charge(ctx, 3);
                at = slti(v1, 80);
                if (at != 0) {
                    // 0x0018b198
                    charge(ctx, 3);
                    at = slti(v1, 65);
                    if (at == 0) {
                        // 0x0018b1c4
                        charge(ctx, 3);
                        at = slti(v1, 70);
                        if (at == 0) {
                            // 0x0018b1dc
                            charge(ctx, 8);
                            v1 = addiu(v1, -70);
                            v0 = sll(v1, 8);
                            v1 = subu(v0, v1);
                            v0 = 10;
                            div(v1, v0);
                            mflo(v1);
                            v0 = 255;
                            v1 = subu(v0, v1);
                        } else {
                            // 0x0018b1d0
                            charge(ctx, 3);
                            v1 = 255;
                        }
                    } else {
                        // 0x0018b1a4
                        charge(ctx, 8);
                        v1 = addiu(v1, -55);
                        v0 = sll(v1, 8);
                        v1 = subu(v0, v1);
                        v0 = 10;
                        div(v1, v0);
                        mflo(v1);
                    }
                    // 0x0018b1fc
                    charge(ctx, 11);
                    v0 = 0x42C20000;
                    mtc1(v0, f12);
                    v0 = si(-256);
                    a0 = v1 | v0;
                    mtc1(zero, f13);
                    mov_s(f14, f13);
                    a1 = 640;
                    a2 = 448;
                    jal(ctx, 0x18B220u, gen::fn_sub_113D80_00113d80);
                }
            }
            // 0x0018b228
            charge(ctx, 4);
            lw(v0, s0, 2672);
            v0 = slti(v0, 80);
            if (v0 != 0) {
                break;
            }
            // 0x0018b238
            charge(ctx, 3);
            v0 = si(-1);
            ended = true;
            break;
        case 0x18B244u:  // table[4]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    if (!ended) {
        // 0x0018b244: keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0018b248 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0x190);
}

// 0x0018B270 sub_18B270 -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18B270(task) [H_PerEfcMixraidDestroy]: destroy callback of "H_PerEfcMixraidDraw": removes the three cached
// archive files (H_Cdvd_CacheRemove on the records' +340 words), destroys the four textures (sub_4D0F00), destroys the
// archive node (+64), RwFree(work).
void sub_18B270(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018b270
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    s1 = 0;
    for (;;) {
        // 0x0018b2cc
        charge(ctx, 3);
        v0 = slti(s1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0018b294
        charge(ctx, 10);
        v0 = sll(s1, 5);
        v1 = subu(v0, s1);
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        s2 = addiu(v0, 340);
        lw(a0, v0, 340);
        if (a0 != 0) {
            // 0x0018b2bc
            charge(ctx, 2);
            jal(ctx, 0x18B2BCu, gen::fn_H_Cdvd_CacheRemove_00102870);
        }
        // 0x0018b2c4
        charge(ctx, 2);
        sw(zero, s2, 0);
        s1 = addiu(s1, 1);
    }
    // 0x0018b2d8
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x0018b30c
        charge(ctx, 3);
        v0 = slti(s2, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0018b2e4
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 48);
        lw(a0, v0, 48);
        if (a0 != 0) {
            // 0x0018b2fc
            charge(ctx, 3);
            jal(ctx, 0x18B2FCu, gen::fn_sub_4D0F00_004d0f00);
            sw(zero, s1, 0);
        }
        // 0x0018b308
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0018b318
    charge(ctx, 3);
    lw(a0, s0, 64);
    if (a0 != 0) {
        // 0x0018b324
        charge(ctx, 3);
        jal(ctx, 0x18B324u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 64);
    }
    // 0x0018b330
    charge(ctx, 12);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18B33Cu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0018B360 sub_18B360 -- 24 bytes; leaf frame (no stack)
// sub_18B360(task) [H_PerEfcMixraidIsReady]: step >= 4 (everything loaded). Caller: sub_2E3DB0 (battle).
void sub_18B360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0018b360
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 0);
    v0 = slti(v0, 4);
    v0 = v0 ^ 0x1;
}

// 0x0018B380 sub_18B380 -- 616 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18B380(task) [H_PerEfcMixraidStartWords]: at step 4 starts the show: the three animation tasks are started
// (sub_111530), the frame counter (+2672) = -2, and five "h_mix_wordN_draw" tasks (priority 0x18C0, 16-byte works,
// sub_188C30 / sub_189230 / sub_189810 / sub_189DF0 / sub_18A3F0, destroy sub_18A9C0) get the word textures (+56 for
// words 1..3, +60 for 4..5) in their work +12; step 5. Caller: sub_2E3E60.
void sub_18B380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018b380
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    lw(a0, s1, 0);
    v1 = 4;
    if (a0 == v1) {
        // 0x0018b3ac
        charge(ctx, 23);
        lw(a0, s1, 20);
        jal(ctx, 0x18B3B0u, gen::fn_sub_111530_00111530);
        lw(a0, s1, 24);
        jal(ctx, 0x18B3BCu, gen::fn_sub_111530_00111530);
        lw(a0, s1, 28);
        jal(ctx, 0x18B3C8u, gen::fn_sub_111530_00111530);
        v0 = si(-2);
        sw(v0, s1, 2672);
        lw(s2, s1, 56);
        s0 = 0x960000;
        s0 = addiu(s0, 388);  // &0x960184
        a0 = 1;
        a1 = 16;
        a2 = 0x40000;
        lw(v0, s0, 0);  // 0x960184
        jalr(ctx, 0x18B3F4u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x0018b408
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, 17184);  // "h_mix_word1_draw"
            a2 = 6336;
            a3 = 0x190000;
            a3 = addiu(a3, -29648);  // &sub_188C30
            t0 = 0x190000;
            t0 = addiu(t0, -22080);  // &sub_18A9C0
            t1 = s3;
            jal(ctx, 0x18B42Cu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x0018b43c
                charge(ctx, 1);
                sw(s2, s3, 12);
            }
        }
        // 0x0018b440
        charge(ctx, 10);
        lw(s2, s1, 56);
        a0 = 1;
        a1 = 16;
        a2 = 0x40000;
        lw(v0, s0, 0);
        jalr(ctx, 0x18B454u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x0018b468
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, 17216);  // "h_mix_word2_draw"
            a2 = 6336;
            a3 = 0x190000;
            a3 = addiu(a3, -28112);  // &sub_189230
            t0 = 0x190000;
            t0 = addiu(t0, -22080);  // &sub_18A9C0
            t1 = s3;
            jal(ctx, 0x18B48Cu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x0018b49c
                charge(ctx, 1);
                sw(s2, s3, 12);
            }
        }
        // 0x0018b4a0
        charge(ctx, 10);
        lw(s2, s1, 56);
        a0 = 1;
        a1 = 16;
        a2 = 0x40000;
        lw(v0, s0, 0);
        jalr(ctx, 0x18B4B4u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x0018b4c8
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, 17248);  // "h_mix_word3_draw"
            a2 = 6336;
            a3 = 0x190000;
            a3 = addiu(a3, -26608);  // &sub_189810
            t0 = 0x190000;
            t0 = addiu(t0, -22080);  // &sub_18A9C0
            t1 = s3;
            jal(ctx, 0x18B4ECu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x0018b4fc
                charge(ctx, 1);
                sw(s2, s3, 12);
            }
        }
        // 0x0018b500
        charge(ctx, 10);
        lw(s2, s1, 60);
        a0 = 1;
        a1 = 16;
        a2 = 0x40000;
        lw(v0, s0, 0);
        jalr(ctx, 0x18B514u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x0018b528
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, 17280);  // "h_mix_word4_draw"
            a2 = 6336;
            a3 = 0x190000;
            a3 = addiu(a3, -25104);  // &sub_189DF0
            t0 = 0x190000;
            t0 = addiu(t0, -22080);  // &sub_18A9C0
            t1 = s3;
            jal(ctx, 0x18B54Cu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x0018b55c
                charge(ctx, 1);
                sw(s2, s3, 12);
            }
        }
        // 0x0018b560
        charge(ctx, 10);
        lw(s2, s1, 60);
        a0 = 1;
        a1 = 16;
        a2 = 0x40000;
        lw(v0, s0, 0);
        jalr(ctx, 0x18B574u, v0.u());
        s0 = v0;
        if (s0 != 0) {
            // 0x0018b588
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, 17312);  // "h_mix_word5_draw"
            a2 = 6336;
            a3 = 0x190000;
            a3 = addiu(a3, -23568);  // &sub_18A3F0
            t0 = 0x190000;
            t0 = addiu(t0, -22080);  // &sub_18A9C0
            t1 = s0;
            jal(ctx, 0x18B5ACu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x0018b5bc
                charge(ctx, 1);
                sw(s2, s0, 12);
            }
        }
        // 0x0018b5c0
        charge(ctx, 2);
        v1 = 5;
        sw(v1, s1, 0);
    }
    // 0x0018b5c8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018B5F0 sub_18B5F0 -- 44 bytes; leaf frame (no stack)
// sub_18B5F0(task) [H_PerEfcMixraidGetFrame]: the show's frame counter (+2672) at step 5, else 0. Caller: sub_2E3E60.
void sub_18B5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0018b5f0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    lw(v1, a0, 0);
    v0 = 5;
    if (v1 != v0) {
        // 0x0018b610
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0018b604
        charge(ctx, 3);
        lw(v0, a0, 2672);
    }
    // 0x0018b614 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0018B620 sub_18B620 -- 176 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18B620(parent, spell) [H_PerEfcMixraidCreate]: RwCalloc(1, 2676) and kwlnTaskCreate(parent,
// "H_PerEfcMixraidDraw", 0x18BF, sub_18A9F0, sub_18B270, work); work +4 = spell. Caller: sub_2E3D50.
void sub_18B620(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018b620
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 2676;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x18B650u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0018b670
        charge(ctx, 13);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17584);  // "H_PerEfcMixraidDraw"
        a2 = 6335;
        a3 = 0x190000;
        a3 = addiu(a3, -22032);  // &sub_18A9F0
        t0 = 0x190000;
        t0 = addiu(t0, -19856);  // &sub_18B270
        t1 = s0;
        jal(ctx, 0x18B694u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0018b6b0
            charge(ctx, 1);
            sw(s1, s0, 4);
        } else {
            // 0x0018b6a4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018b664
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0018b6b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0018B7B0 sub_18B7B0 -- 688 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18B7B0(tween, out xy) [H_TweenPosition]: the position at the current frame, t = frame - first of n = last -
// first, between from (+40, +44) and to (+48, +52), by the motion curve +12 (a jump table): 0 -> `to`; 1 linear,
// from + (to - from) t / n; 2 a sine curve (sinf of t scaled by the float 0x7CAF38) that ends at `to`; 3 a cosine
// curve that ends at `from`; at t == n curves 1 / 2 give `to`, curve 3 gives `from`. The R5900 multiply-add forms
// (adda.s / madd.s / msub.s) of the original are kept as they are.
void sub_18B7B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12};
    // 0x0018b7b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(a1, a0, 28);
    lw(v1, a0, 32);
    s1 = subu(v1, a1);
    lw(v1, a0, 24);
    s0 = subu(v1, a1);
    lw(a0, a0, 12);
    v1 = 3;
    if (a0 == v1) {
        // 0x0018b97c
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x0018b9b4
            charge(ctx, 2);
            v0 = 0x42B40000;
            mtc1(v0, f1);
        } else {
            // 0x0018b984
            charge(ctx, 12);
            v0 = sll(s0, 4);
            v1 = subu(v0, s0);
            v0 = sll(v1, 2);
            v0 = subu(v0, v1);
            v0 = sll(v0, 1);
            div(v0, s1);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x0018b9bc
        charge(ctx, 13);
        lwc1(f0, gp, -32184);  // 0x7CAF38
        mul_s(f1, f0, f1);
        v0 = 0x43340000;
        mtc1(v0, f0);
        div_s(f12, f1, f0);
        jal(ctx, 0x18B9E0u, gen::fn_cosf_0052e6d8);
        if (s0 != s1) {
            // 0x0018ba08
            charge(ctx, 14);
            lwc1(f2, s3, 48);
            lwc1(f1, s3, 40);
            sub_s(f1, f1, f2);
            mtc1(zero, f3);
            adda_s(f3, f2);
            msub_s(f1, f0, f1);
            swc1(f1, s2, 0);
            lwc1(f2, s3, 52);
            lwc1(f1, s3, 44);
            sub_s(f1, f1, f2);
            adda_s(f3, f2);
            msub_s(f0, f0, f1);
            swc1(f0, s2, 4);
        } else {
            // 0x0018b9f0
            charge(ctx, 6);
            lwc1(f0, s3, 40);
            swc1(f0, s2, 0);
            lwc1(f0, s3, 44);
            swc1(f0, s2, 4);
        }
    } else {
        // 0x0018b7f4
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x0018b8b0
            charge(ctx, 2);
            if (s1 == 0) {
                // 0x0018b8e8
                charge(ctx, 2);
                v0 = 0x42B40000;
                mtc1(v0, f1);
            } else {
                // 0x0018b8b8
                charge(ctx, 12);
                v0 = sll(s0, 4);
                v1 = subu(v0, s0);
                v0 = sll(v1, 2);
                v0 = subu(v0, v1);
                v0 = sll(v0, 1);
                div(v0, s1);
                mflo(v0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x0018b8f0
            charge(ctx, 13);
            lwc1(f0, gp, -32184);  // 0x7CAF38
            mul_s(f1, f0, f1);
            v0 = 0x43340000;
            mtc1(v0, f0);
            div_s(f12, f1, f0);
            jal(ctx, 0x18B914u, gen::fn_sinf_0052e878);
            if (s0 != s1) {
                // 0x0018b93c
                charge(ctx, 16);
                lwc1(f2, s3, 40);
                lwc1(f1, s3, 48);
                sub_s(f1, f1, f2);
                mtc1(zero, f3);
                adda_s(f3, f2);
                madd_s(f1, f0, f1);
                swc1(f1, s2, 0);
                lwc1(f2, s3, 44);
                lwc1(f1, s3, 52);
                sub_s(f1, f1, f2);
                adda_s(f3, f2);
                madd_s(f0, f0, f1);
                swc1(f0, s2, 4);
            } else {
                // 0x0018b924
                charge(ctx, 6);
                lwc1(f0, s3, 48);
                swc1(f0, s2, 0);
                lwc1(f0, s3, 52);
                swc1(f0, s2, 4);
            }
        } else {
            // 0x0018b800
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x0018b834
                charge(ctx, 2);
                if (s0 != s1) {
                    // 0x0018b854
                    charge(ctx, 23);
                    lwc1(f4, s3, 40);
                    lwc1(f0, s3, 48);
                    sub_s(f1, f0, f4);
                    mtc1(s0, f0);
                    cvt_s_w(f3, f0);
                    mul_s(f1, f1, f3);
                    mtc1(s1, f0);
                    cvt_s_w(f2, f0);
                    div_s(f0, f1, f2);
                    add_s(f0, f4, f0);
                    swc1(f0, s2, 0);
                    lwc1(f1, s3, 44);
                    lwc1(f0, s3, 52);
                    sub_s(f0, f0, f1);
                    mul_s(f0, f0, f3);
                    div_s(f0, f0, f2);
                    add_s(f0, f1, f0);
                    swc1(f0, s2, 4);
                } else {
                    // 0x0018b83c
                    charge(ctx, 6);
                    lwc1(f0, s3, 48);
                    swc1(f0, s2, 0);
                    lwc1(f0, s3, 52);
                    swc1(f0, s2, 4);
                }
            } else {
                // 0x0018b80c
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0018b81c
                    charge(ctx, 6);
                    lwc1(f0, s3, 48);
                    swc1(f0, s2, 0);
                    lwc1(f0, s3, 52);
                    swc1(f0, s2, 4);
                } else {
                    // 0x0018b814
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0018ba40 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018BA60 sub_18BA60 -- 180 bytes; leaf frame (no stack)
// sub_18BA60(tween, u8* out) [H_TweenAlpha]: the alpha at the current frame by the fade curve +16 (a jump table): 0
// -> 0; 1 fade out, 255 - 255 t / n (0 when n == 0); 2 fade in, 255 t / n (255 when n == 0).
void sub_18BA60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0018ba60
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(a2, a0, 28);
    lw(v1, a0, 32);
    a3 = subu(v1, a2);
    lw(v1, a0, 24);
    a2 = subu(v1, a2);
    lw(a0, a0, 16);
    v1 = 2;
    if (a0 == v1) {
        // 0x0018bae4
        charge(ctx, 2);
        if (a3 != 0) {
            // 0x0018baf8
            charge(ctx, 4);
            v1 = sll(a2, 8);
            v1 = subu(v1, a2);
            div(v1, a3);
            mflo(v1);
        } else {
            // 0x0018baec
            charge(ctx, 3);
            v1 = 255;
        }
        // 0x0018bb08
        charge(ctx, 1);
        sb(v1, a1, 0);
    } else {
        // 0x0018ba84
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x0018baac
            charge(ctx, 2);
            if (a3 != 0) {
                // 0x0018bac0
                charge(ctx, 4);
                v1 = sll(a2, 8);
                v1 = subu(v1, a2);
                div(v1, a3);
                mflo(a0);
            } else {
                // 0x0018bab4
                charge(ctx, 3);
                a0 = 255;
            }
            // 0x0018bad0
            charge(ctx, 5);
            v1 = 255;
            v1 = subu(v1, a0);
            sb(v1, a1, 0);
        } else {
            // 0x0018ba90
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x0018baa0
                charge(ctx, 3);
                sb(zero, a1, 0);
            } else {
                // 0x0018ba98
                charge(ctx, 2);
            }
        }
    }
    // 0x0018bb0c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0018BB20 sub_18BB20 -- 96 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_18BB20(tween) [H_TweenUpdatePlain]: position and alpha into the record (+56, +60 = x, y; +64 = alpha);
// returns alpha != 255.
void sub_18BB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0018bb20
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = addiu(sp, 0x20);
    jal(ctx, 0x18BB34u, gen::fn_sub_18B7B0_0018b7b0);
    a0 = s0;
    a1 = addiu(sp, 0x2F);
    jal(ctx, 0x18BB44u, gen::fn_sub_18BA60_0018ba60);
    lwc1(f1, sp, 0x20);
    lwc1(f0, sp, 0x24);
    swc1(f1, s0, 56);
    swc1(f0, s0, 60);
    lbu(v0, sp, 0x2F);
    sw(v0, s0, 64);
    v0 = v0 ^ 0xFF;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0018BB80 sub_18BB80 -- 144 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18BB80(tween) [H_TweenUpdateSprite]: as sub_18BB20, then also draws the record's sprite (+0) with the frame
// +20 at full alpha (sub_115AD0).
void sub_18BB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018bb80
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x18BB98u, gen::fn_sub_18B7B0_0018b7b0);
    a0 = s1;
    a1 = addiu(sp, 0x3F);
    jal(ctx, 0x18BBA8u, gen::fn_sub_18BA60_0018ba60);
    lwc1(f1, sp, 0x30);
    lwc1(f0, sp, 0x34);
    swc1(f1, s1, 56);
    swc1(f0, s1, 60);
    lbu(t0, sp, 0x3F);
    sw(t0, s1, 64);
    a0 = s0;
    lw(a1, s1, 0);
    lw(a2, s1, 20);
    lwc1(f12, sp, 0x30);
    lwc1(f13, sp, 0x34);
    a3 = 255;
    lwc1(f14, s1, 36);
    jal(ctx, 0x18BBE4u, gen::fn_sub_115AD0_00115ad0);
    lw(v0, s1, 64);
    v0 = v0 ^ 0xFF;
    v0 = sltu(0, v0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0018BC80 sub_18BC80 -- 272 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18BC80() [H_PartyPanelLoad]: boot loader of the party panel's sprites (from kwlnInitMain): requests
// "camp/ptypnl.pak" (archive) and reads it synchronously (H_Cdvd_ReadSync), makes a sprite file of each of its 18
// files (H_Cdvd_ArchiveGetFile + sprCreateHandleFromData) into 0x846730[0..17], then pumps the sprite manager
// (sub_1120C0) until all 18 are ready (sprFileIsReady), and destroys the node.
void sub_18BC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018bc80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x5E0000;
    a0 = addiu(a0, 17616);  // "camp/ptypnl.pak"
    a1 = 1;
    jal(ctx, 0x18BCA0u, gen::fn_H_Cdvd_Request_00100d80);
    s2 = v0;
    a0 = s2;
    jal(ctx, 0x18BCB0u, gen::fn_H_Cdvd_ReadSync_001023a0);
    s0 = 0;
    for (;;) {
        // 0x0018bcfc
        charge(ctx, 3);
        v0 = slti(s0, 18);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0018bcc4
        charge(ctx, 14);
        a0 = s2;
        a1 = s0;
        a2 = addiu(sp, 0x4C);
        jal(ctx, 0x18BCD0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
        a0 = v0;
        jal(ctx, 0x18BCDCu, gen::fn_sprCreateHandleFromData_00112420);
        a0 = sll(s0, 2);
        v1 = 0x840000;
        v1 = addiu(v1, 26416);  // &0x846730
        v1 = addu(v1, a0);
        sw(v0, v1, 0);
        s0 = addiu(s0, 1);
    }
    for (;;) {
        // 0x0018bd08
        charge(ctx, 6);
        jal(ctx, 0x18BD08u, gen::fn_sub_1120C0_001120c0);
        s1 = 1;
        s0 = 0;
        for (;;) {
            // 0x0018bd4c
            charge(ctx, 3);
            v0 = slti(s0, 18);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0018bd20
            charge(ctx, 9);
            v1 = sll(s0, 2);
            v0 = 0x840000;
            v0 = addiu(v0, 26416);  // &0x846730
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x18BD34u, gen::fn_sprFileIsReady_00111f30);
            if (v0 == 0) {
                // 0x0018bd44
                charge(ctx, 1);
                s1 = 0;
            }
            // 0x0018bd48
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x0018bd58
        charge(ctx, 4);
        v0 = sltu(0, s1);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0018bd68
    charge(ctx, 10);
    a0 = s2;
    jal(ctx, 0x18BD6Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018BD90 sub_18BD90 -- 328 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18BD90(task) [H_PartyPanelUpdate] ("h_party_panel_draw_proc", made by sub_18BFF0): the field's party panel.
// Work (100 bytes): +0 step, +8 shown flag, +12..+24 the four member panels (sub-tasks), +28..+96 the 18 sprite files.
// Step 0 -> 1; step 1 copies the 18 files of 0x846730, creates the four member panels (sub_18E390 with slots 0..3),
// step 2; every frame each member panel gets the shown flag (sub_18E490). Returns 0.
void sub_18BD90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018bd90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 != v0) {
        // 0x0018bdb8
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x0018bde0
            charge(ctx, 5);
            a2 = 0;
            a0 = 0x840000;
            a0 = addiu(a0, 26416);  // &0x846730
            for (;;) {
                // 0x0018be0c
                charge(ctx, 3);
                v0 = slti(a2, 18);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0018bdf4
                charge(ctx, 6);
                a1 = sll(a2, 2);
                v0 = addu(a0, a1);
                lw(v1, v0, 0);
                v0 = addu(s0, a1);
                sw(v1, v0, 28);
                a2 = addiu(a2, 1);
            }
            // 0x0018be18
            charge(ctx, 26);
            a0 = s1;
            a1 = 0;
            a2 = addiu(s0, 28);
            jal(ctx, 0x18BE24u, gen::fn_sub_18E390_0018e390);
            sw(v0, s0, 12);
            a0 = s1;
            a1 = 1;
            a2 = addiu(s0, 28);
            jal(ctx, 0x18BE3Cu, gen::fn_sub_18E390_0018e390);
            sw(v0, s0, 16);
            a0 = s1;
            a1 = 2;
            a2 = addiu(s0, 28);
            jal(ctx, 0x18BE54u, gen::fn_sub_18E390_0018e390);
            sw(v0, s0, 20);
            a0 = s1;
            a1 = 3;
            a2 = addiu(s0, 28);
            jal(ctx, 0x18BE6Cu, gen::fn_sub_18E390_0018e390);
            sw(v0, s0, 24);
            v0 = 2;
            sw(v0, s0, 0);
        } else {
            // 0x0018bdc4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0018bdd4
                charge(ctx, 3);
                sw(v0, s0, 0);
            } else {
                // 0x0018bdcc
                charge(ctx, 2);
            }
        }
    }
    // 0x0018be80
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x0018beb0
        charge(ctx, 3);
        v0 = slti(s1, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0018be8c
        charge(ctx, 5);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, 12);
        if (a0 != 0) {
            // 0x0018bea0
            charge(ctx, 3);
            lw(a1, s0, 8);
            jal(ctx, 0x18BEA4u, gen::fn_sub_18E490_0018e490);
        }
        // 0x0018beac
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0018bebc
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0018BEE0 sub_18BEE0 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18BEE0(panel task, unit, kind) [H_PartyPanelSetMemberMode]: finds the member panel of `unit` -- unit 1 is the
// hero's (+12), else the party slot whose member (sub_16DD60(slot) for slots 0..2) is the unit (+16 + 4 slot) -- and
// sets its mode through sub_18DDE0. Callers: the field camera's battle encounter tasks, sub_456EA0.
void sub_18BEE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018bee0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;  // the unit
    s1 = a2;  // the kind
    lw(s0, a0, 60);  // the party panel's work
    v1 = 1;
    if (s2 != v1) {
        // 0x0018bf28: find the party slot (0..2) whose member is the unit
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x0018bf74
            charge(ctx, 3);
            v1 = slti(s3, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0018bf34
            charge(ctx, 7);
            a0 = s3;
            jal(ctx, 0x18BF38u, gen::fn_sub_16DD60_0016dd60);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            if (s2 == v1) {
                // 0x0018bf50: the member panel of that party slot
                charge(ctx, 8);
                v0 = sll(s3, 2);
                v0 = addu(v0, s0);
                lw(a0, v0, 16);
                a1 = s1;
                jal(ctx, 0x18BF60u, gen::fn_sub_18DDE0_0018dde0);
                break;
            }
            // 0x0018bf70
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    } else {
        // 0x0018bf10
        charge(ctx, 6);
        lw(a0, s0, 12);
        a1 = s1;
        jal(ctx, 0x18BF18u, gen::fn_sub_18DDE0_0018dde0);
    }
    // 0x0018bf80 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018BFA0 sub_18BFA0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_18BFA0(task) [H_PartyPanelDestroy]: destroy callback of "h_party_panel_draw_proc": destroys the node at work +4
// if one is held, RwFree(work).
void sub_18BFA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018bfa0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 4);
    if (a0 != 0) {
        // 0x0018bfbc
        charge(ctx, 3);
        jal(ctx, 0x18BFBCu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 4);
    }
    // 0x0018bfc8
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18BFD4u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0018BFF0 sub_18BFF0 -- 168 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18BFF0(parent) [H_PartyPanelCreate]: RwCalloc(1, 100), kwlnTaskCreate(parent, "h_party_panel_draw_proc", 0x18B3,
// sub_18BD90, sub_18BFA0, work), work +8 = 1 (shown). Callers: the field root and the field event task.
void sub_18BFF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018bff0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 100;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x18C018u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0018c038
        charge(ctx, 13);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17632);  // "h_party_panel_draw_proc"
        a2 = 6323;
        a3 = 0x190000;
        a3 = addiu(a3, -17008);  // &sub_18BD90
        t0 = 0x190000;
        t0 = addiu(t0, -16480);  // &sub_18BFA0
        t1 = s0;
        jal(ctx, 0x18C05Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0018c078
            charge(ctx, 2);
            v1 = 1;
            sw(v1, s0, 8);
        } else {
            // 0x0018c06c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018c02c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0018c080 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0018C0A0 sub_18C0A0 -- 24 bytes; leaf frame (no stack)
// sub_18C0A0(task) [H_PartyPanelIsReady]: step == 2 (the member panels exist).
void sub_18C0A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0018c0a0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 0);
    v0 = v0 ^ 0x2;
    v0 = sltiu(v0, 1);
}

// 0x0018C0C0 sub_18C0C0 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18C0C0(task, shown) [H_PartyPanelSetShown]: work +8 = shown and, once the member panels exist, each of the four
// gets it (sub_18E490).
void sub_18C0C0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018c0c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, 60);
    sw(s1, s0, 8);
    lw(v1, a0, 60);
    lw(a0, v1, 0);
    v1 = 2;
    if (a0 == v1) {
        // 0x0018c0f0
        charge(ctx, 15);
        lw(a0, s0, 12);
        jal(ctx, 0x18C0F4u, gen::fn_sub_18E490_0018e490);
        lw(a0, s0, 16);
        a1 = s1;
        jal(ctx, 0x18C104u, gen::fn_sub_18E490_0018e490);
        lw(a0, s0, 20);
        a1 = s1;
        jal(ctx, 0x18C114u, gen::fn_sub_18E490_0018e490);
        lw(a0, s0, 24);
        a1 = s1;
        jal(ctx, 0x18C124u, gen::fn_sub_18E490_0018e490);
    }
    // 0x0018c12c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0018C150 sub_18C150 -- 1572 bytes; frame 0xA0: ra sp+0x90, s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// sub_18C150(member work) [H_PartyMemberDrawNormal]: member-panel mode 0. The portrait (the unit's sprite file,
// +60 + 4 unit, where The Answer shows unit 1 and 3 as 11 and unit 9 as 12) frame 1, then frame 2 when the unit has the
// status bit 0x80 (sub_16C970) else 0; the frame (+44) frame 0. With status 0x80: twelve sparks circle the portrait
// (timer +32 mod 100, sprite file +48 frames 1..3, sinf / cosf, fading in and out). Then the HP bar (+44 frame 1)
// clipped to 32 hp / max (sub_16C4F0 / sub_16C5F0; sub_113A30 sets the clip) and the SP bar (frame 2: sub_16C570 /
// sub_16C670). Every draw uses the tween's alpha (+112 tween, +64).
void sub_18C150(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0018c150
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
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
    s2 = a0;
    lw(s4, a0, 112);
    lh(s0, a0, 20);
    s3 = s0;
    jal(ctx, 0x18C190u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0018c1a0
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 == v0) {
            // 0x0018c1b4
            charge(ctx, 1);
            s3 = 11;
        }
        // 0x0018c1b8
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 9;
        if (v1 == v0) {
            // 0x0018c1cc
            charge(ctx, 1);
            s3 = 12;
        }
        // 0x0018c1d0
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 3;
        if (v1 == v0) {
            // 0x0018c1e4
            charge(ctx, 1);
            s3 = 11;
        }
    }
    // 0x0018c1e8
    charge(ctx, 28);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v1 = addu(v0, s2);
    s3 = addiu(v1, 60);
    lwc1(f1, s4, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s4, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s4, 64);
    a0 = s1;
    lw(a1, v1, 60);
    a2 = 1;
    lwc1(f14, s4, 36);
    jal(ctx, 0x18C238u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = s0;
    jal(ctx, 0x18C244u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x0018c2a4
        charge(ctx, 17);
        lwc1(f1, s4, 56);
        v0 = 0x41A00000;
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        lwc1(f1, s4, 60);
        v0 = 0x41900000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lbu(a3, s4, 64);
        a0 = s1;
        lw(a1, s3, 0);
        a2 = 2;
        lwc1(f14, s4, 36);
        jal(ctx, 0x18C2E0u, gen::fn_sprDrawSpriteBasic_001159f0);
    } else {
        // 0x0018c258
        charge(ctx, 19);
        lwc1(f1, s4, 56);
        v0 = 0x41A00000;
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        lwc1(f1, s4, 60);
        v0 = 0x41900000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lbu(a3, s4, 64);
        a0 = s1;
        lw(a1, s3, 0);
        a2 = 0;
        lwc1(f14, s4, 36);
        jal(ctx, 0x18C294u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x0018c2e8
    charge(ctx, 23);
    lwc1(f1, s4, 56);
    v0 = 0x42300000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s4, 60);
    v0 = 0x421C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s4, 64);
    a0 = s1;
    lw(a1, s2, 44);
    a2 = 0;
    lwc1(f14, s4, 36);
    jal(ctx, 0x18C324u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = s0;
    jal(ctx, 0x18C330u, gen::fn_sub_16C970_0016c970);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x0018c344
        charge(ctx, 6);
        lw(v0, s2, 32);
        v0 = addiu(v0, 1);
        sw(v0, s2, 32);
        v0 = slti(v0, 100);
        if (v0 == 0) {
            // 0x0018c35c
            charge(ctx, 1);
            sw(zero, s2, 32);
        }
        // 0x0018c360
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x0018c560
            charge(ctx, 3);
            v0 = slti(s3, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0018c36c
            charge(ctx, 10);
            v0 = sll(s3, 4);
            v1 = subu(v0, s3);
            lw(v0, s2, 32);
            v1 = addu(v0, v1);
            v0 = 100;
            div(v1, v0);
            mfhi(s0);
            at = slti(s0, 51);
            if (at == 0) {
                // 0x0018c394
                charge(ctx, 9);
                v0 = 3;
                div(s3, v0);
                mflo(v1);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 3);
                v0 = sra(v1, 2);
                if (i64(v1) < 0) {
                    // 0x0018c3b8
                    charge(ctx, 2);
                    v0 = addiu(v1, 3);
                    v0 = sra(v0, 2);
                }
                // 0x0018c3c0
                charge(ctx, 43);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                lwc1(f0, gp, -32184);  // 0x7CAF38
                mul_s(f1, f0, f1);
                v0 = 0x43340000;
                mtc1(v0, f0);
                div_s(f21, f1, f0);
                mov_s(f12, f21);
                jal(ctx, 0x18C400u, gen::fn_sinf_0052e878);
                mov_s(f20, f0);
                mov_s(f12, f21);
                jal(ctx, 0x18C410u, gen::fn_cosf_0052e6d8);
                a0 = addiu(s0, -50);
                v0 = sll(a0, 2);
                v1 = addu(v0, a0);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v1 = sll(v0, 1);
                v0 = 50;
                div(v1, v0);
                mflo(v0);
                mtc1(v0, f1);
                cvt_s_w(f1, f1);
                mul_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(s6, f0);
                mul_s(f0, f1, f20);
                cvt_w_s(f0, f0);
                mfc1(s7, f0);
                at = slti(a0, 10);
                if (at == 0) {
                    // 0x0018c490
                    charge(ctx, 3);
                    at = slti(a0, 40);
                    if (at == 0) {
                        // 0x0018c4a8
                        charge(ctx, 6);
                        v1 = addiu(s0, -90);
                        v0 = sll(v1, 8);
                        v1 = subu(v0, v1);
                        v0 = 10;
                        div(v1, v0);
                        mflo(s0);
                    } else {
                        // 0x0018c49c
                        charge(ctx, 3);
                        s0 = 0;
                    }
                } else {
                    // 0x0018c46c
                    charge(ctx, 9);
                    v0 = sll(a0, 8);
                    v1 = subu(v0, a0);
                    v0 = 10;
                    div(v1, v0);
                    mflo(v1);
                    v0 = 255;
                    s0 = subu(v0, v1);
                }
                // 0x0018c4c0
                charge(ctx, 39);
                v0 = 3;
                div(s3, v0);
                mfhi(v0);
                a2 = addiu(v0, 1);
                a0 = 0;
                lw(a1, s2, 48);
                jal(ctx, 0x18C4D8u, gen::fn_sprCreateHandle_001158b0);
                s1 = v0;
                lwc1(f0, s4, 36);
                swc1(f0, v0, 44);
                lwc1(f1, s4, 56);
                v1 = 0x42300000;
                mtc1(v1, f0);
                add_s(f1, f0, f1);
                mtc1(s6, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f1, f0);
                swc1(f0, v0, 16);
                lwc1(f1, s4, 60);
                v1 = 0x42080000;
                mtc1(v1, f0);
                add_s(f1, f0, f1);
                mtc1(s7, f0);
                cvt_s_w(f0, f0);
                sub_s(f0, f1, f0);
                swc1(f0, v0, 20);
                sb(s0, v0, 24);
                a0 = s1;
                a1 = 1;
                jal(ctx, 0x18C548u, gen::fn_sub_1127D0_001127d0);
                a0 = s1;
                jal(ctx, 0x18C554u, gen::fn_sub_115980_00115980);
            }
            // 0x0018c55c
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    }
    // 0x0018c56c
    charge(ctx, 16);
    lw(s0, s2, 112);
    lh(s1, s2, 20);
    a0 = s1;
    jal(ctx, 0x18C578u, gen::fn_sub_16C4F0_0016c4f0);
    v0 = v0 & 0xFFFF;
    s3 = sll(v0, 5);
    a0 = s1;
    jal(ctx, 0x18C58Cu, gen::fn_sub_16C5F0_0016c5f0);
    v0 = v0 & 0xFFFF;
    div(s3, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018c5ac
        charge(ctx, 24);
        lwc1(f1, s0, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s0, 36);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s0, 60);
        v0 = 0x42380000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18C604u, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018c60c
    charge(ctx, 31);
    lwc1(f1, s0, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x42380000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s5;
    lw(a1, s2, 44);
    a2 = 1;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18C648u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = s1;
    jal(ctx, 0x18C654u, gen::fn_sub_16C570_0016c570);
    v0 = v0 & 0xFFFF;
    s3 = sll(v0, 5);
    a0 = s1;
    jal(ctx, 0x18C668u, gen::fn_sub_16C670_0016c670);
    v0 = v0 & 0xFFFF;
    div(s3, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018c688
        charge(ctx, 24);
        lwc1(f1, s0, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s0, 36);
        v0 = 0x40400000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s0, 60);
        v0 = 0x424C0000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18C6E0u, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018c6e8
    charge(ctx, 35);
    lwc1(f1, s0, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x424C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    lwc1(f1, s0, 36);
    v0 = 0x40000000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s5;
    lw(a1, s2, 44);
    a2 = 2;
    jal(ctx, 0x18C734u, gen::fn_sprDrawSpriteBasic_001159f0);
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
    sp = addiu(sp, 0xA0);
}

// 0x0018C780 sub_18C780 -- 1732 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18C780(member work) [H_PartyMemberDrawMarkIn]: member-panel mode 3: the portrait in its alternate frames (8, 7;
// frame sprite 6), the HP / SP bars, and a mark (sprite file +60 frame 1) zooming in over 5 frames (scale (t << 12) / 5)
// and fading in; frames 5..12 a second mark (frame 0) grows and fades out; after 18 frames the mode becomes 4.
void sub_18C780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018c780
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, 112);
    lh(s3, a0, 20);
    jal(ctx, 0x18C7ACu, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0018c7bc
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 == v0) {
            // 0x0018c7d0
            charge(ctx, 1);
            s3 = 11;
        }
        // 0x0018c7d4
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 9;
        if (v1 == v0) {
            // 0x0018c7e8
            charge(ctx, 1);
            s3 = 12;
        }
        // 0x0018c7ec
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 3;
        if (v1 == v0) {
            // 0x0018c800
            charge(ctx, 1);
            s3 = 11;
        }
    }
    // 0x0018c804
    charge(ctx, 72);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v1 = addu(v0, s2);
    s3 = addiu(v1, 60);
    lwc1(f1, s0, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s1;
    lw(a1, v1, 60);
    a2 = 8;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18C854u, gen::fn_sprDrawSpriteBasic_001159f0);
    lwc1(f1, s0, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s1;
    lw(a1, s3, 0);
    a2 = 7;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18C898u, gen::fn_sprDrawSpriteBasic_001159f0);
    lwc1(f1, s0, 56);
    v0 = 0x42300000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x421C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s1;
    lw(a1, s2, 44);
    a2 = 6;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18C8DCu, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(s3, s2, 112);
    lh(s4, s2, 20);
    a0 = s4;
    jal(ctx, 0x18C8F0u, gen::fn_sub_16C4F0_0016c4f0);
    v0 = v0 & 0xFFFF;
    s1 = sll(v0, 5);
    a0 = s4;
    jal(ctx, 0x18C904u, gen::fn_sub_16C5F0_0016c5f0);
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018c924
        charge(ctx, 24);
        lwc1(f1, s3, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s3, 36);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s3, 60);
        v0 = 0x42380000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18C97Cu, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018c984
    charge(ctx, 31);
    lwc1(f1, s3, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x42380000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    a0 = s5;
    lw(a1, s2, 44);
    a2 = 1;
    lwc1(f14, s3, 36);
    jal(ctx, 0x18C9C0u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = s4;
    jal(ctx, 0x18C9CCu, gen::fn_sub_16C570_0016c570);
    v0 = v0 & 0xFFFF;
    s1 = sll(v0, 5);
    a0 = s4;
    jal(ctx, 0x18C9E0u, gen::fn_sub_16C670_0016c670);
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018ca00
        charge(ctx, 24);
        lwc1(f1, s3, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s3, 36);
        v0 = 0x40400000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s3, 60);
        v0 = 0x424C0000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18CA58u, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018ca60
    charge(ctx, 25);
    lwc1(f1, s3, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x424C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    lwc1(f1, s3, 36);
    v0 = 0x40000000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s5;
    lw(a1, s2, 44);
    a2 = 2;
    jal(ctx, 0x18CAACu, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(a0, s2, 24);
    at = slti(a0, 6);
    if (at == 0) {
        // 0x0018cac4
        charge(ctx, 1);
        a0 = 5;
    }
    // 0x0018cac8
    charge(ctx, 105);
    v0 = sll(a0, 12);
    v1 = 5;
    div(v0, v1);
    mflo(s4);
    v0 = sll(a0, 8);
    v0 = subu(v0, a0);
    div1(v0, v1);
    mflo1(v1);
    v0 = 255;
    s3 = subu(v0, v1);
    a0 = 0;
    lw(a1, s2, 60);
    a2 = 1;
    jal(ctx, 0x18CAFCu, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    lwc1(f1, s0, 36);
    v1 = 0x40800000;
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 44);
    v1 = addiu(s4, 1);
    sh(v1, v0, 40);
    sh(v1, v0, 42);
    a0 = s1;
    jal(ctx, 0x18CB30u, gen::fn_sprGetSpriteWidth_001126b0);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sh(v0, s1, 36);
    a0 = s1;
    jal(ctx, 0x18CB5Cu, gen::fn_sprGetSpriteHeight_00112740);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sh(v0, s1, 38);
    v0 = 0x42B40000;
    sw(v0, s1, 32);
    a0 = s1;
    jal(ctx, 0x18CB90u, gen::fn_sprGetSpriteWidth_001126b0);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f2, f0, f1);
    lwc1(f1, s0, 56);
    v0 = 0x40C00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    sub_s(f1, f0, f2);
    v0 = 0x42000000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x41200000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, s1, 16);
    a0 = s1;
    jal(ctx, 0x18CBE8u, gen::fn_sprGetSpriteHeight_00112740);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f2, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41B00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    sub_s(f1, f0, f2);
    v0 = 0x41800000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x40A00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, s1, 20);
    sb(s3, s1, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x18CC48u, gen::fn_sub_1127D0_001127d0);
    a0 = s1;
    jal(ctx, 0x18CC54u, gen::fn_sub_115980_00115980);
    lw(v1, s2, 24);
    v1 = addiu(v1, -5);
    if (i64(v1) >= 0) {
        // 0x0018cc6c
        charge(ctx, 3);
        at = slti(v1, 8);
        if (at != 0) {
            // 0x0018cc78
            charge(ctx, 4);
            v0 = sll(v1, 12);
            s3 = sra(v0, 3);
            if (i64(v0) < 0) {
                // 0x0018cc88
                charge(ctx, 2);
                v0 = addiu(v0, 7);
                s3 = sra(v0, 3);
            }
            // 0x0018cc90
            charge(ctx, 5);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            v1 = sra(v0, 3);
            if (i64(v0) < 0) {
                // 0x0018cca4
                charge(ctx, 2);
                v0 = addiu(v0, 7);
                v1 = sra(v0, 3);
            }
            // 0x0018ccac
            charge(ctx, 83);
            v0 = 255;
            s1 = subu(v0, v1);
            a0 = 0;
            lw(a1, s2, 60);
            a2 = 0;
            jal(ctx, 0x18CCC0u, gen::fn_sprCreateHandle_001158b0);
            s4 = v0;
            lwc1(f1, s0, 36);
            v1 = 0x40800000;
            mtc1(v1, f0);
            sub_s(f0, f1, f0);
            swc1(f0, v0, 44);
            v1 = addiu(s3, 1);
            sh(v1, v0, 40);
            sh(v1, v0, 42);
            a0 = s4;
            jal(ctx, 0x18CCF4u, gen::fn_sprGetSpriteWidth_001126b0);
            v0 = 0x40000000;
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s4, 36);
            a0 = s4;
            jal(ctx, 0x18CD20u, gen::fn_sprGetSpriteHeight_00112740);
            v0 = 0x40000000;
            mtc1(v0, f1);
            div_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s4, 38);
            a0 = s4;
            jal(ctx, 0x18CD4Cu, gen::fn_sprGetSpriteWidth_001126b0);
            v0 = 0x40000000;
            mtc1(v0, f1);
            div_s(f2, f0, f1);
            lwc1(f1, s0, 56);
            v0 = 0x40C00000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            sub_s(f1, f0, f2);
            v0 = 0x422C0000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, s4, 16);
            a0 = s4;
            jal(ctx, 0x18CD94u, gen::fn_sprGetSpriteHeight_00112740);
            v0 = 0x40000000;
            mtc1(v0, f1);
            div_s(f2, f0, f1);
            lwc1(f1, s0, 60);
            v0 = 0x41900000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            sub_s(f1, f0, f2);
            v0 = 0x41C80000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, s4, 20);
            sb(s1, s4, 24);
            a0 = s4;
            a1 = 1;
            jal(ctx, 0x18CDE4u, gen::fn_sub_1127D0_001127d0);
            a0 = s4;
            jal(ctx, 0x18CDF0u, gen::fn_sub_115980_00115980);
        }
    }
    // 0x0018cdf8
    charge(ctx, 6);
    lw(v1, s2, 24);
    v1 = addiu(v1, 1);
    sw(v1, s2, 24);
    v1 = slti(v1, 18);
    if (v1 == 0) {
        // 0x0018ce10
        charge(ctx, 3);
        sw(zero, s2, 24);
        v1 = 4;
        sw(v1, s2, 12);
    }
    // 0x0018ce1c (the shared epilogue, written out on this path)
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

// 0x0018CE50 sub_18CE50 -- 1228 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18CE50(member work) [H_PartyMemberDrawMark]: member-panel mode 4: as mode 3's steady state -- alternate
// portrait frames, the bars, the mark at full size (4096) with alpha 40.
void sub_18CE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018ce50
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s3, a0, 112);
    lh(s1, a0, 20);
    jal(ctx, 0x18CE7Cu, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0018ce8c
        charge(ctx, 5);
        v1 = dsll32(s1, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 == v0) {
            // 0x0018cea0
            charge(ctx, 1);
            s1 = 11;
        }
        // 0x0018cea4
        charge(ctx, 5);
        v1 = dsll32(s1, 16);
        v1 = dsra32(v1, 16);
        v0 = 9;
        if (v1 == v0) {
            // 0x0018ceb8
            charge(ctx, 1);
            s1 = 12;
        }
        // 0x0018cebc
        charge(ctx, 5);
        v1 = dsll32(s1, 16);
        v1 = dsra32(v1, 16);
        v0 = 3;
        if (v1 == v0) {
            // 0x0018ced0
            charge(ctx, 1);
            s1 = 11;
        }
    }
    // 0x0018ced4
    charge(ctx, 72);
    v0 = dsll32(s1, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v1 = addu(v0, s0);
    s1 = addiu(v1, 60);
    lwc1(f1, s3, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    a0 = s2;
    lw(a1, v1, 60);
    a2 = 8;
    lwc1(f14, s3, 36);
    jal(ctx, 0x18CF24u, gen::fn_sprDrawSpriteBasic_001159f0);
    lwc1(f1, s3, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    a0 = s2;
    lw(a1, s1, 0);
    a2 = 7;
    lwc1(f14, s3, 36);
    jal(ctx, 0x18CF68u, gen::fn_sprDrawSpriteBasic_001159f0);
    lwc1(f1, s3, 56);
    v0 = 0x42300000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x421C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    a0 = s2;
    lw(a1, s0, 44);
    a2 = 6;
    lwc1(f14, s3, 36);
    jal(ctx, 0x18CFACu, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(s2, s0, 112);
    lh(s4, s0, 20);
    a0 = s4;
    jal(ctx, 0x18CFC0u, gen::fn_sub_16C4F0_0016c4f0);
    v0 = v0 & 0xFFFF;
    s1 = sll(v0, 5);
    a0 = s4;
    jal(ctx, 0x18CFD4u, gen::fn_sub_16C5F0_0016c5f0);
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018cff4
        charge(ctx, 24);
        lwc1(f1, s2, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s2, 36);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s2, 60);
        v0 = 0x42380000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18D04Cu, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018d054
    charge(ctx, 31);
    lwc1(f1, s2, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s2, 60);
    v0 = 0x42380000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s2, 64);
    a0 = s5;
    lw(a1, s0, 44);
    a2 = 1;
    lwc1(f14, s2, 36);
    jal(ctx, 0x18D090u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = s4;
    jal(ctx, 0x18D09Cu, gen::fn_sub_16C570_0016c570);
    v0 = v0 & 0xFFFF;
    s1 = sll(v0, 5);
    a0 = s4;
    jal(ctx, 0x18D0B0u, gen::fn_sub_16C670_0016c670);
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018d0d0
        charge(ctx, 24);
        lwc1(f1, s2, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s2, 36);
        v0 = 0x40400000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s2, 60);
        v0 = 0x424C0000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18D128u, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018d130
    charge(ctx, 123);
    lwc1(f1, s2, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s2, 60);
    v0 = 0x424C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s2, 64);
    lwc1(f1, s2, 36);
    v0 = 0x40000000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s5;
    lw(a1, s0, 44);
    a2 = 2;
    jal(ctx, 0x18D17Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = 0;
    lw(a1, s0, 60);
    a2 = 1;
    jal(ctx, 0x18D190u, gen::fn_sprCreateHandle_001158b0);
    s2 = v0;
    lwc1(f1, s3, 36);
    v1 = 0x40800000;
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 44);
    v1 = 4096;
    sh(v1, v0, 40);
    sh(v1, v0, 42);
    a0 = s2;
    jal(ctx, 0x18D1C4u, gen::fn_sprGetSpriteWidth_001126b0);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sh(v0, s2, 36);
    a0 = s2;
    jal(ctx, 0x18D1F0u, gen::fn_sprGetSpriteHeight_00112740);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sh(v0, s2, 38);
    v0 = 0x42B40000;
    sw(v0, s2, 32);
    a0 = s2;
    jal(ctx, 0x18D224u, gen::fn_sprGetSpriteWidth_001126b0);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f2, f0, f1);
    lwc1(f1, s3, 56);
    v0 = 0x40C00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    sub_s(f1, f0, f2);
    v0 = 0x42000000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x41200000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, s2, 16);
    a0 = s2;
    jal(ctx, 0x18D27Cu, gen::fn_sprGetSpriteHeight_00112740);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f2, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x41B00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    sub_s(f1, f0, f2);
    v0 = 0x41800000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x40A00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, s2, 20);
    v0 = 40;
    sb(v0, s2, 24);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x18D2E0u, gen::fn_sub_1127D0_001127d0);
    a0 = s2;
    jal(ctx, 0x18D2ECu, gen::fn_sub_115980_00115980);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0018D320 sub_18D320 -- 2036 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18D320(member work) [H_PartyMemberDrawFlash]: member-panel mode 2 (a temporary effect): portrait frames 6 / 4,
// frame sprite 5, the bars, a sprite (+56 frame 0) zooming in over 5 frames, then its frames 1..5 flickering with
// random alphas (RpRandom % 153, sub_488F30); after 31 frames the mode returns to the saved one (+16).
void sub_18D320(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018d320
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s0, a0, 112);
    lh(s3, a0, 20);
    jal(ctx, 0x18D34Cu, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x0018d35c
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 1;
        if (v1 == v0) {
            // 0x0018d370
            charge(ctx, 1);
            s3 = 11;
        }
        // 0x0018d374
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 9;
        if (v1 == v0) {
            // 0x0018d388
            charge(ctx, 1);
            s3 = 12;
        }
        // 0x0018d38c
        charge(ctx, 5);
        v1 = dsll32(s3, 16);
        v1 = dsra32(v1, 16);
        v0 = 3;
        if (v1 == v0) {
            // 0x0018d3a0
            charge(ctx, 1);
            s3 = 11;
        }
    }
    // 0x0018d3a4
    charge(ctx, 72);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v0 = sll(v0, 2);
    v1 = addu(v0, s2);
    s3 = addiu(v1, 60);
    lwc1(f1, s0, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s1;
    lw(a1, v1, 60);
    a2 = 6;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18D3F4u, gen::fn_sprDrawSpriteBasic_001159f0);
    lwc1(f1, s0, 56);
    v0 = 0x41A00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s1;
    lw(a1, s3, 0);
    a2 = 4;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18D438u, gen::fn_sprDrawSpriteBasic_001159f0);
    lwc1(f1, s0, 56);
    v0 = 0x42300000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x421C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s0, 64);
    a0 = s1;
    lw(a1, s2, 44);
    a2 = 5;
    lwc1(f14, s0, 36);
    jal(ctx, 0x18D47Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(s3, s2, 112);
    lh(s4, s2, 20);
    a0 = s4;
    jal(ctx, 0x18D490u, gen::fn_sub_16C4F0_0016c4f0);
    v0 = v0 & 0xFFFF;
    s1 = sll(v0, 5);
    a0 = s4;
    jal(ctx, 0x18D4A4u, gen::fn_sub_16C5F0_0016c5f0);
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018d4c4
        charge(ctx, 24);
        lwc1(f1, s3, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s3, 36);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s3, 60);
        v0 = 0x42380000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18D51Cu, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018d524
    charge(ctx, 31);
    lwc1(f1, s3, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x42380000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    a0 = s5;
    lw(a1, s2, 44);
    a2 = 1;
    lwc1(f14, s3, 36);
    jal(ctx, 0x18D560u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = s4;
    jal(ctx, 0x18D56Cu, gen::fn_sub_16C570_0016c570);
    v0 = v0 & 0xFFFF;
    s1 = sll(v0, 5);
    a0 = s4;
    jal(ctx, 0x18D580u, gen::fn_sub_16C670_0016c670);
    v0 = v0 & 0xFFFF;
    div(s1, v0);
    mflo(a0);
    v1 = 32;
    if (a0 != v1) {
        // 0x0018d5a0
        charge(ctx, 24);
        lwc1(f1, s3, 56);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f1, f0);
        v0 = 0x42480000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        lwc1(f1, s3, 36);
        v0 = 0x40400000;
        mtc1(v0, f0);
        sub_s(f12, f1, f0);
        lwc1(f1, s3, 60);
        v0 = 0x424C0000;
        mtc1(v0, f0);
        add_s(f14, f0, f1);
        a1 = subu(v1, a0);
        a0 = si(-256);
        a2 = 20;
        jal(ctx, 0x18D5F8u, gen::fn_sub_113A30_00113a30);
    }
    // 0x0018d600
    charge(ctx, 25);
    lwc1(f1, s3, 56);
    v0 = 0x42480000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s3, 60);
    v0 = 0x424C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    lbu(a3, s3, 64);
    lwc1(f1, s3, 36);
    v0 = 0x40000000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s5;
    lw(a1, s2, 44);
    a2 = 2;
    jal(ctx, 0x18D64Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(a0, s2, 24);
    at = slti(a0, 6);
    if (at == 0) {
        // 0x0018d664
        charge(ctx, 1);
        a0 = 5;
    }
    // 0x0018d668
    charge(ctx, 94);
    v0 = sll(a0, 12);
    v1 = 5;
    div(v0, v1);
    mflo(s3);
    v0 = sll(a0, 8);
    v0 = subu(v0, a0);
    div1(v0, v1);
    mflo1(v1);
    v0 = 255;
    s4 = subu(v0, v1);
    a0 = 0;
    lw(a1, s2, 56);
    a2 = 0;
    jal(ctx, 0x18D69Cu, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    lwc1(f1, s0, 36);
    v1 = 0x40800000;
    mtc1(v1, f0);
    sub_s(f0, f1, f0);
    swc1(f0, v0, 44);
    sh(s3, v0, 40);
    sh(s3, v0, 42);
    a0 = s1;
    jal(ctx, 0x18D6CCu, gen::fn_sprGetSpriteWidth_001126b0);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sh(v0, s1, 36);
    a0 = s1;
    jal(ctx, 0x18D6F8u, gen::fn_sprGetSpriteHeight_00112740);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f0, f0, f1);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sh(v0, s1, 38);
    a0 = s1;
    jal(ctx, 0x18D724u, gen::fn_sprGetSpriteWidth_001126b0);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f2, f0, f1);
    lwc1(f1, s0, 56);
    v0 = 0x41B00000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    sub_s(f1, f0, f2);
    v0 = 0x42280000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, s1, 16);
    a0 = s1;
    jal(ctx, 0x18D76Cu, gen::fn_sprGetSpriteHeight_00112740);
    v0 = 0x40000000;
    mtc1(v0, f1);
    div_s(f2, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x42040000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    sub_s(f1, f0, f2);
    v0 = 0x41D80000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, s1, 20);
    sb(s4, s1, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x18D7BCu, gen::fn_sub_1127D0_001127d0);
    a0 = s1;
    jal(ctx, 0x18D7C8u, gen::fn_sub_115980_00115980);
    lw(v0, s2, 24);
    v1 = addiu(v0, -5);
    if (i64(v1) >= 0) {
        // 0x0018d7e0
        charge(ctx, 3);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x0018d800
            charge(ctx, 5);
            jal(ctx, 0x18D800u, gen::fn_sub_488F30_00488f30);
            v1 = 153;
            divu(v0, v1);
            mfhi(s4);
        } else {
            // 0x0018d7ec
            charge(ctx, 5);
            v0 = 5;
            div(v1, v0);
            mflo(s4);
        }
    }
    // 0x0018d814
    charge(ctx, 25);
    lwc1(f1, s0, 56);
    v0 = 0x41E00000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41B00000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    a3 = s4 & 0xFF;
    lwc1(f1, s0, 36);
    v0 = 0x40800000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s1;
    lw(a1, s2, 56);
    a2 = 1;
    jal(ctx, 0x18D860u, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(v0, s2, 24);
    v1 = addiu(v0, -5);
    if (i64(v1) >= 0) {
        // 0x0018d878
        charge(ctx, 3);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x0018d898
            charge(ctx, 5);
            jal(ctx, 0x18D898u, gen::fn_sub_488F30_00488f30);
            v1 = 153;
            divu(v0, v1);
            mfhi(s4);
        } else {
            // 0x0018d884
            charge(ctx, 5);
            v0 = 5;
            div(v1, v0);
            mflo(s4);
        }
    }
    // 0x0018d8ac
    charge(ctx, 25);
    lwc1(f1, s0, 56);
    v0 = 0x426C0000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x41B80000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    a3 = s4 & 0xFF;
    lwc1(f1, s0, 36);
    v0 = 0x40800000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s1;
    lw(a1, s2, 56);
    a2 = 2;
    jal(ctx, 0x18D8F8u, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(v0, s2, 24);
    v1 = addiu(v0, -5);
    if (i64(v1) >= 0) {
        // 0x0018d910
        charge(ctx, 3);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x0018d930
            charge(ctx, 5);
            jal(ctx, 0x18D930u, gen::fn_sub_488F30_00488f30);
            v1 = 153;
            divu(v0, v1);
            mfhi(s4);
        } else {
            // 0x0018d91c
            charge(ctx, 5);
            v0 = 5;
            div(v1, v0);
            mflo(s4);
        }
        // 0x0018d944
        charge(ctx, 21);
        lwc1(f1, s0, 56);
        v0 = 0x41A80000;
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        lwc1(f1, s0, 60);
        v0 = 0x423C0000;
        mtc1(v0, f0);
        add_s(f13, f0, f1);
        a3 = s4 & 0xFF;
        lwc1(f1, s0, 36);
        v0 = 0x40800000;
        mtc1(v0, f0);
        sub_s(f14, f1, f0);
        a0 = s1;
        lw(a1, s2, 56);
        a2 = 3;
        jal(ctx, 0x18D990u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x0018d998
    charge(ctx, 4);
    lw(v0, s2, 24);
    v1 = addiu(v0, -5);
    if (i64(v1) >= 0) {
        // 0x0018d9a8
        charge(ctx, 3);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x0018d9c8
            charge(ctx, 5);
            jal(ctx, 0x18D9C8u, gen::fn_sub_488F30_00488f30);
            v1 = 153;
            divu(v0, v1);
            mfhi(s4);
        } else {
            // 0x0018d9b4
            charge(ctx, 5);
            v0 = 5;
            div(v1, v0);
            mflo(s4);
        }
    }
    // 0x0018d9dc
    charge(ctx, 25);
    lwc1(f1, s0, 56);
    v0 = 0x42440000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x422C0000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    a3 = s4 & 0xFF;
    lwc1(f1, s0, 36);
    v0 = 0x40800000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s1;
    lw(a1, s2, 56);
    a2 = 4;
    jal(ctx, 0x18DA28u, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(v0, s2, 24);
    v1 = addiu(v0, -5);
    if (i64(v1) >= 0) {
        // 0x0018da40
        charge(ctx, 3);
        at = slti(v1, 5);
        if (at == 0) {
            // 0x0018da60
            charge(ctx, 5);
            jal(ctx, 0x18DA60u, gen::fn_sub_488F30_00488f30);
            v1 = 153;
            divu(v0, v1);
            mfhi(s4);
        } else {
            // 0x0018da4c
            charge(ctx, 5);
            v0 = 5;
            div(v1, v0);
            mflo(s4);
        }
    }
    // 0x0018da74
    charge(ctx, 27);
    lwc1(f1, s0, 56);
    v0 = 0x42860000;
    mtc1(v0, f0);
    add_s(f12, f0, f1);
    lwc1(f1, s0, 60);
    v0 = 0x42780000;
    mtc1(v0, f0);
    add_s(f13, f0, f1);
    a3 = s4 & 0xFF;
    lwc1(f1, s0, 36);
    v0 = 0x40800000;
    mtc1(v0, f0);
    sub_s(f14, f1, f0);
    a0 = s1;
    lw(a1, s2, 56);
    a2 = 5;
    jal(ctx, 0x18DAC0u, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(v1, s2, 24);
    v1 = addiu(v1, 1);
    sw(v1, s2, 24);
    at = slti(v1, 31);
    if (at == 0) {
        // 0x0018dae0
        charge(ctx, 3);
        lw(v1, s2, 16);
        sw(v1, s2, 12);
        sw(zero, s2, 24);
    }
    // 0x0018daec (the shared epilogue, written out on this path)
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

// 0x0018DB20 sub_18DB20 -- 696 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18DB20(member work) [H_PartyMemberDraw]: steps the member's tween (+112, sub_18B700) and, when it says draw and
// the panel is shown (+36), draws by the mode +12: 0 sub_18C150, 1 the simple form (portrait frames 3 / 1, frame
// sprites 0 / 3, sprite +52 frame 0), 2 sub_18D320, 3 sub_18C780, 4 sub_18CE50. A jump table on the mode.
void sub_18DB20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018db20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    lw(a0, a0, 112);
    jal(ctx, 0x18DB40u, gen::fn_sub_18B700_0018b700);
    if (v0 != 0) {
        // 0x0018db50
        charge(ctx, 3);
        lw(v1, s3, 36);
        if (v1 != 0) {
            // 0x0018db5c
            charge(ctx, 4);
            lw(a0, s3, 12);
            v1 = 4;
            if (a0 == v1) {
                // 0x0018ddac
                charge(ctx, 3);
                a0 = s3;
                jal(ctx, 0x18DDB0u, gen::fn_sub_18CE50_0018ce50);
            } else {
                // 0x0018db6c
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x0018dd98
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x18DD9Cu, gen::fn_sub_18C780_0018c780);
                } else {
                    // 0x0018db78
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x0018dd84
                        charge(ctx, 5);
                        a0 = s3;
                        jal(ctx, 0x18DD88u, gen::fn_sub_18D320_0018d320);
                    } else {
                        // 0x0018db84
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0018dbb4
                            charge(ctx, 6);
                            lw(s1, s3, 112);
                            lh(s0, s3, 20);
                            jal(ctx, 0x18DBBCu, gen::fn_sub_17D800_0017d800);
                            if (v0 != 0) {
                                // 0x0018dbcc
                                charge(ctx, 5);
                                v1 = dsll32(s0, 16);
                                v1 = dsra32(v1, 16);
                                v0 = 1;
                                if (v1 == v0) {
                                    // 0x0018dbe0
                                    charge(ctx, 1);
                                    s0 = 11;
                                }
                                // 0x0018dbe4
                                charge(ctx, 5);
                                v1 = dsll32(s0, 16);
                                v1 = dsra32(v1, 16);
                                v0 = 9;
                                if (v1 == v0) {
                                    // 0x0018dbf8
                                    charge(ctx, 1);
                                    s0 = 12;
                                }
                                // 0x0018dbfc
                                charge(ctx, 5);
                                v1 = dsll32(s0, 16);
                                v1 = dsra32(v1, 16);
                                v0 = 3;
                                if (v1 == v0) {
                                    // 0x0018dc10
                                    charge(ctx, 1);
                                    s0 = 11;
                                }
                            }
                            // 0x0018dc14
                            charge(ctx, 92);
                            v0 = dsll32(s0, 16);
                            v0 = dsra32(v0, 16);
                            v0 = sll(v0, 2);
                            v1 = addu(v0, s3);
                            s0 = addiu(v1, 60);
                            lwc1(f1, s1, 56);
                            v0 = 0x41A00000;
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, 60);
                            v0 = 0x41900000;
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, 64);
                            a0 = s2;
                            lw(a1, v1, 60);
                            a2 = 3;
                            lwc1(f14, s1, 36);
                            jal(ctx, 0x18DC64u, gen::fn_sprDrawSpriteBasic_001159f0);
                            lwc1(f1, s1, 56);
                            v0 = 0x41A00000;
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, 60);
                            v0 = 0x41900000;
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, 64);
                            a0 = s2;
                            lw(a1, s0, 0);
                            a2 = 1;
                            lwc1(f14, s1, 36);
                            jal(ctx, 0x18DCA8u, gen::fn_sprDrawSpriteBasic_001159f0);
                            lwc1(f1, s1, 56);
                            v0 = 0x42300000;
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, 60);
                            v0 = 0x421C0000;
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, 64);
                            a0 = s2;
                            lw(a1, s3, 44);
                            a2 = 0;
                            lwc1(f14, s1, 36);
                            jal(ctx, 0x18DCECu, gen::fn_sprDrawSpriteBasic_001159f0);
                            lwc1(f1, s1, 56);
                            v0 = 0x42480000;
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, 60);
                            v0 = 0x424C0000;
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, 64);
                            a0 = s2;
                            lw(a1, s3, 44);
                            a2 = 3;
                            lwc1(f14, s1, 36);
                            jal(ctx, 0x18DD30u, gen::fn_sprDrawSpriteBasic_001159f0);
                            lwc1(f1, s1, 56);
                            v0 = 0x41D80000;
                            mtc1(v0, f0);
                            add_s(f12, f0, f1);
                            lwc1(f1, s1, 60);
                            v0 = 0x41B00000;
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s1, 64);
                            a0 = s2;
                            lw(a1, s3, 52);
                            a2 = 0;
                            lwc1(f14, s1, 36);
                            jal(ctx, 0x18DD74u, gen::fn_sprDrawSpriteBasic_001159f0);
                        } else {
                            // 0x0018db90
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x0018dba0
                                charge(ctx, 5);
                                a0 = s3;
                                jal(ctx, 0x18DBA4u, gen::fn_sub_18C150_0018c150);
                            } else {
                                // 0x0018db98
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x0018ddb8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018DDE0 sub_18DDE0 -- 124 bytes; leaf frame (no stack)
// sub_18DDE0(member task, kind) [H_PartyMemberSetMode]: kind 0 -> mode 0, 1 -> mode 3 (the mark comes in), 2 -> mode
// 1, 3 -> mode 2 (the flash; the current mode is saved in +16 to come back to); the mode timer +24 restarts.
void sub_18DDE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0018dde0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a2, a0, 60);  // the member panel work
    a0 = 3;
    if (a1 == a0) {
        // 0x0018de40
        charge(ctx, 4);
        lw(v1, a2, 12);  // kind 3: the flash (mode 2); the current mode kept in +16
        sw(v1, a2, 16);
        v1 = 2;
        sw(v1, a2, 12);
    } else {
        // 0x0018ddf0
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0018de30
            charge(ctx, 4);
            v1 = 1;
            sw(v1, a2, 12);
        } else {
            // 0x0018ddfc
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0018de24
                charge(ctx, 3);
                sw(a0, a2, 12);
            } else {
                // 0x0018de08
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0018de18
                    charge(ctx, 3);
                    sw(zero, a2, 12);
                } else {
                    // 0x0018de10
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0018de50 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sw(zero, a2, 24);  // the mode timer restarts
}

// 0x0018DE60 sub_18DE60 -- 1224 bytes; frame 0x70: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// sub_18DE60(task) [H_PartyMemberUpdate] ("h_party_pnl_sub_draw", one per slot). Work (116 bytes): +0 step, +4 the
// slide state, +8 the slot (0 = the hero, 1..3 party slots), +20 the unit shown, +28 the party size the layout was
// made for, +112 its tween record.
//   step 0: a tween record (sub_18B6D0(1)), slide state 0, mode 0, step 1;
//   step 1: party size = 1 + the members present (sub_16DD60(0..2)); a slot whose member left hides (slide 0, the
//           tween stops); a changed member restarts the slide; slide 0: the panel slides in from x 834 to 534 (the
//           y from the party size: 4 -> 53 slot + 195, 3 -> 60 slot + 234, 2 -> 60 slot + 294, 1 -> 0x43A20000 =
//           324.0), printing " ## %02d : YPOS = %f ##" (a debug print left in retail), slide 1; slide 1 waits for the
//           tween's end (frame == last), slide 3; slide 3 re-lays out when the party size changes (a 10-frame move);
//           slide 2 -> 0. In slides 1 and 3 the member is drawn (sub_18DB20).
void sub_18DE60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0018de60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    lw(s2, a0, 60);
    lw(v0, s2, 0);
    a0 = 1;
    if (v0 == a0) {
        // 0x0018debc
        charge(ctx, 4);
        s1 = a0;
        s0 = 0;
        for (;;) {
            // 0x0018def0
            charge(ctx, 3);
            v0 = slti(s0, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0018decc
            charge(ctx, 7);
            a0 = s0;
            jal(ctx, 0x18DED0u, gen::fn_sub_16DD60_0016dd60);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (v0 != 0) {
                // 0x0018dee8
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
            // 0x0018deec
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x0018defc
        charge(ctx, 3);
        lw(v0, s2, 8);
        if (v0 != 0) {
            // 0x0018df08
            charge(ctx, 7);
            a0 = addiu(v0, -1);
            jal(ctx, 0x18DF0Cu, gen::fn_sub_16DD60_0016dd60);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (v0 == 0) {
                // 0x0018df24
                charge(ctx, 3);
                sw(zero, s2, 4);
                lw(v0, s2, 112);
                sw(zero, v0, 4);
            }
        }
        // 0x0018df30
        charge(ctx, 3);
        lw(v0, s2, 8);
        if (v0 != 0) {
            // 0x0018df4c
            charge(ctx, 8);
            lw(s0, s2, 20);
            a0 = addiu(v0, -1);
            jal(ctx, 0x18DF54u, gen::fn_sub_16DD60_0016dd60);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (s0 != v0) {
                // 0x0018df6c
                charge(ctx, 8);
                sw(zero, s2, 4);
                lw(v0, s2, 8);
                a0 = addiu(v0, -1);
                jal(ctx, 0x18DF78u, gen::fn_sub_16DD60_0016dd60);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                sw(v0, s2, 20);
            }
        } else {
            // 0x0018df3c
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s2, 20);
        }
        // 0x0018df8c
        charge(ctx, 4);
        lw(v0, s2, 4);
        a1 = 3;
        if (v0 == a1) {
            // 0x0018e170
            charge(ctx, 3);
            lw(v0, s2, 28);
            if (s1 != v0) {
                // 0x0018e17c
                charge(ctx, 15);
                sw(s1, s2, 28);
                lw(v0, s2, 112);
                lwc1(f1, v0, 56);
                lwc1(f0, v0, 60);
                swc1(f1, sp, 0x58);
                swc1(f0, sp, 0x5C);
                lw(s0, s2, 8);
                v0 = 534;
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                swc1(f0, sp, 0x60);
                v0 = 4;
                if (s1 == v0) {
                    // 0x0018e258
                    charge(ctx, 10);
                    v0 = 53;
                    mult(v0, s0, v0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x43430000;
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x64);
                } else {
                    // 0x0018e1b8
                    charge(ctx, 2);
                    if (s1 == a1) {
                        // 0x0018e224
                        charge(ctx, 13);
                        v0 = sll(s0, 4);
                        v0 = subu(v0, s0);
                        v0 = sll(v0, 2);
                        mtc1(v0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x436A0000;
                        mtc1(v0, f0);
                        add_s(f0, f0, f1);
                        swc1(f0, sp, 0x64);
                    } else {
                        // 0x0018e1c0
                        charge(ctx, 3);
                        v0 = 2;
                        if (s1 == v0) {
                            // 0x0018e1f0
                            charge(ctx, 13);
                            v0 = sll(s0, 4);
                            v0 = subu(v0, s0);
                            v0 = sll(v0, 2);
                            mtc1(v0, f0);
                            cvt_s_w(f1, f0);
                            v0 = 0x43930000;
                            mtc1(v0, f0);
                            add_s(f0, f0, f1);
                            swc1(f0, sp, 0x64);
                        } else {
                            // 0x0018e1cc
                            charge(ctx, 3);
                            v0 = 1;
                            if (s1 == v0) {
                                // 0x0018e1e0
                                charge(ctx, 4);
                                v0 = 0x43A20000;
                                sw(v0, sp, 0x64);
                            } else {
                                // 0x0018e1d8
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x0018e280
                charge(ctx, 24);
                lwc1(f12, sp, 0x64);
                jal(ctx, 0x18E284u, gen::fn_fptodp_00530da0);
                a0 = 0x5E0000;
                a0 = addiu(a0, 17664);  // " ## %02d : YPOS = %f ##\n"
                a1 = s0;
                a2 = v0;
                jal(ctx, 0x18E29Cu, gen::fn_printf_005225a8);
                sd(zero, sp, 0x0);
                v0 = 10;
                sd(v0, sp, 0x8);
                v0 = 0x42DC0000;
                mtc1(v0, f12);
                lw(a0, s2, 112);
                a1 = 0;
                a2 = 2;
                a3 = 0;
                ld(t0, sp, 0x58);
                ld(t1, sp, 0x60);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x18E2D8u, gen::fn_sub_18BC10_0018bc10);
            }
        } else {
            // 0x0018df9c
            charge(ctx, 3);
            a0 = 2;
            if (v0 == a0) {
                // 0x0018e164
                charge(ctx, 3);
                sw(zero, s2, 4);
            } else {
                // 0x0018dfa8
                charge(ctx, 3);
                v1 = 1;
                if (v0 == v1) {
                    // 0x0018e144
                    charge(ctx, 5);
                    lw(v0, s2, 112);
                    lw(v1, v0, 24);
                    lw(v0, v0, 32);
                    if (v1 == v0) {
                        // 0x0018e158
                        charge(ctx, 3);
                        sw(a1, s2, 4);
                    }
                } else {
                    // 0x0018dfb4
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x0018dfc4
                        charge(ctx, 4);
                        sw(s1, s2, 28);
                        lw(v0, s2, 20);
                        if (v0 != 0) {
                            // 0x0018dfd4
                            charge(ctx, 9);
                            lw(s0, s2, 8);
                            v0 = 534;
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            swc1(f0, sp, 0x60);
                            v0 = 4;
                            if (s1 == v0) {
                                // 0x0018e090
                                charge(ctx, 10);
                                v0 = 53;
                                mult(v0, s0, v0);
                                mtc1(v0, f0);
                                cvt_s_w(f1, f0);
                                v0 = 0x43430000;
                                mtc1(v0, f0);
                                add_s(f0, f0, f1);
                                swc1(f0, sp, 0x64);
                            } else {
                                // 0x0018dff8
                                charge(ctx, 2);
                                if (s1 == a1) {
                                    // 0x0018e05c
                                    charge(ctx, 13);
                                    v0 = sll(s0, 4);
                                    v0 = subu(v0, s0);
                                    v0 = sll(v0, 2);
                                    mtc1(v0, f0);
                                    cvt_s_w(f1, f0);
                                    v0 = 0x436A0000;
                                    mtc1(v0, f0);
                                    add_s(f0, f0, f1);
                                    swc1(f0, sp, 0x64);
                                } else {
                                    // 0x0018e000
                                    charge(ctx, 2);
                                    if (s1 == a0) {
                                        // 0x0018e028
                                        charge(ctx, 13);
                                        v0 = sll(s0, 4);
                                        v0 = subu(v0, s0);
                                        v0 = sll(v0, 2);
                                        mtc1(v0, f0);
                                        cvt_s_w(f1, f0);
                                        v0 = 0x43930000;
                                        mtc1(v0, f0);
                                        add_s(f0, f0, f1);
                                        swc1(f0, sp, 0x64);
                                    } else {
                                        // 0x0018e008
                                        charge(ctx, 2);
                                        if (s1 == v1) {
                                            // 0x0018e018
                                            charge(ctx, 4);
                                            v0 = 0x43A20000;
                                            sw(v0, sp, 0x64);
                                        } else {
                                            // 0x0018e010
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                            // 0x0018e0b8
                            charge(ctx, 35);
                            lwc1(f12, sp, 0x64);
                            jal(ctx, 0x18E0BCu, gen::fn_fptodp_00530da0);
                            a0 = 0x5E0000;
                            a0 = addiu(a0, 17664);  // " ## %02d : YPOS = %f ##\n"
                            a1 = s0;
                            a2 = v0;
                            jal(ctx, 0x18E0D4u, gen::fn_printf_005225a8);
                            a3 = 1;
                            sw(a3, s2, 4);
                            ld(v0, sp, 0x60);
                            sd(v0, sp, 0x68);
                            lwc1(f1, sp, 0x68);
                            v0 = 0x43960000;
                            mtc1(v0, f0);
                            add_s(f0, f1, f0);
                            swc1(f0, sp, 0x68);
                            sd(zero, sp, 0x0);
                            v0 = 10;
                            sd(v0, sp, 0x8);
                            v0 = 0x42DC0000;
                            mtc1(v0, f12);
                            lw(a0, s2, 112);
                            a1 = 0;
                            a2 = 2;
                            ld(t0, sp, 0x68);
                            ld(t1, sp, 0x60);
                            t2 = 0;
                            t3 = 0;
                            jal(ctx, 0x18E134u, gen::fn_sub_18BC10_0018bc10);
                        }
                    } else {
                        // 0x0018dfbc
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x0018e2e0: draw the member while it slides in (1) or stands (3)
        charge(ctx, 4);
        lw(v1, s2, 4);
        v0 = 1;
        bool draw = true;  // host-side: slide state 1 or 3
        if (v1 != v0) {
            // 0x0018e2f0
            charge(ctx, 3);
            v0 = 3;
            draw = v1 == v0;
        }
        if (draw) {
            // 0x0018e2fc
            charge(ctx, 3);
            a0 = s2;
            jal(ctx, 0x18E300u, gen::fn_sub_18DB20_0018db20);
        }
    } else {
        // 0x0018de88
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x0018de98
            charge(ctx, 9);
            jal(ctx, 0x18DE98u, gen::fn_sub_18B6D0_0018b6d0);
            sw(v0, s2, 112);
            sw(zero, s2, 4);
            sw(zero, s2, 12);
            v0 = 1;
            sw(v0, s2, 0);
        } else {
            // 0x0018de90
            charge(ctx, 2);
        }
    }
    // 0x0018e308 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0018E330 sub_18E330 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_18E330(task) [H_PartyMemberDestroy]: destroy callback of "h_party_pnl_sub_draw": RwFree(tween +112), clears it,
// RwFree(work).
void sub_18E330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018e330
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 112);
    if (a0 != 0) {
        // 0x0018e34c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x18E354u, v0.u());
    }
    // 0x0018e35c
    charge(ctx, 11);
    sw(zero, s0, 112);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18E36Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0018E390 sub_18E390 -- 244 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18E390(parent, slot, files[18]) [H_PartyMemberCreate]: RwCalloc(1, 116), kwlnTaskCreate(parent,
// "h_party_pnl_sub_draw", 0x18B4, sub_18DE60, sub_18E330, work); copies the 18 sprite files to work +40, shown (+36) =
// 1, slot (+8) = slot.
void sub_18E390(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018e390
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = 1;
    a1 = 116;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x18E3C8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0018e3e8
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17696);  // "h_party_pnl_sub_draw"
        a2 = 6324;
        a3 = 0x190000;
        a3 = addiu(a3, -8608);  // &sub_18DE60
        t0 = 0x190000;
        t0 = addiu(t0, -7376);  // &sub_18E330
        t1 = s0;
        jal(ctx, 0x18E40Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0018e428
            charge(ctx, 3);
            a2 = 0;
            for (;;) {
                // 0x0018e44c
                charge(ctx, 3);
                v1 = slti(a2, 18);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0018e434
                charge(ctx, 6);
                a1 = sll(a2, 2);
                v1 = addu(s1, a1);
                lw(a0, v1, 0);
                v1 = addu(s0, a1);
                sw(a0, v1, 40);
                a2 = addiu(a2, 1);
            }
            // 0x0018e458
            charge(ctx, 3);
            v1 = 1;
            sw(v1, s0, 36);
            sw(s2, s0, 8);
        } else {
            // 0x0018e41c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018e3dc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0018e464 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018E490 sub_18E490 -- 16 bytes; leaf frame (no stack)
// sub_18E490(member task, shown): work +36 = shown.
void sub_18E490(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0018e490
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 36);
}

// 0x0018E4A0 sub_18E4A0 -- 152 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_18E4A0() [H_AreaPanelLoad]: boot loader of the area panel's sprite (from kwlnInitMain): "camp/areapnl.pak"
// read synchronously, its file 0 made a sprite file into 0x7CE008, the sprite manager pumped until it is ready, the
// node destroyed.
void sub_18E4A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018e4a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x5E0000;
    a0 = addiu(a0, 17728);  // "camp/areapnl.pak"
    a1 = 1;
    jal(ctx, 0x18E4B8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x18E4C8u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = s0;
    a1 = 0;
    a2 = addiu(sp, 0x2C);
    jal(ctx, 0x18E4DCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x18E4E8u, gen::fn_sprCreateHandleFromData_00112420);
    sw(v0, gp, -19688);  // 0x7CE008
    for (;;) {
        // 0x0018e4f4
        charge(ctx, 9);
        jal(ctx, 0x18E4F4u, gen::fn_sub_1120C0_001120c0);
        lw(a0, gp, -19688);  // 0x7CE008
        jal(ctx, 0x18E500u, gen::fn_sprFileIsReady_00111f30);
        v0 = sltu(0, v0);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0018e518
    charge(ctx, 8);
    a0 = s0;
    jal(ctx, 0x18E51Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0018E540 sub_18E540 -- 116 bytes; frame 0x10: ra sp+0x0
// sub_18E540(task) [H_AreaPanelUpdate] ("h_area_panel_draw_proc"): step 0 -> 1; step 1 takes the area sprite file
// (0x7CE008) into work +532, step 2; step 2 draws (sub_18E8E0). Returns 0.
void sub_18E540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018e540
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 60);
    lw(a1, a0, 0);
    v1 = 2;
    if (a1 == v1) {
        // 0x0018e598
        charge(ctx, 2);
        jal(ctx, 0x18E598u, gen::fn_sub_18E8E0_0018e8e0);
    } else {
        // 0x0018e55c
        charge(ctx, 3);
        v0 = 1;
        if (a1 == v0) {
            // 0x0018e584
            charge(ctx, 5);
            lw(v0, gp, -19688);  // 0x7CE008
            sw(v0, a0, 532);
            sw(v1, a0, 0);
        } else {
            // 0x0018e568
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x0018e578
                charge(ctx, 3);
                sw(v0, a0, 0);
            } else {
                // 0x0018e570
                charge(ctx, 2);
            }
        }
    }
    // 0x0018e5a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0018E5C0 sub_18E5C0 -- 476 bytes; frame 0x70: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f21 sp+0x14, f20 sp+0x10
// sub_18E5C0(task, name) [H_AreaPanelSetName]: shows a new area name on the area panel (work: +8 the current name, 256
// bytes; +264 the previous one; +520 shown flag; +528 the three tweens): the first time the panel slides in (tween 0
// from x -6 to 194, y 399); later the old name moves to +264 and slides out (tween 2, 40 -> 240, y 407); the new
// name is copied (strcpy) and slides in (tween 1 from 40 - $f21 to 40, y 407). Every motion lasts 10 frames
// (sub_18BC10). Caller: sub_1DDCA0.
void sub_18E5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0018e5c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f21, sp, 0x14);
    swc1(f20, sp, 0x10);
    s1 = a1;
    lw(s0, a0, 60);
    lw(v0, s0, 520);
    if (v0 == 0) {
        // 0x0018e680
        charge(ctx, 32);
        v0 = 0x43420000;
        sw(v0, sp, 0x60);
        v0 = 399;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x64);
        ld(v0, sp, 0x60);
        sd(v0, sp, 0x50);
        v0 = 0x43480000;
        mtc1(v0, f21);
        lwc1(f0, sp, 0x50);
        sub_s(f0, f0, f21);
        swc1(f0, sp, 0x50);
        v0 = 0x42C80000;
        mtc1(v0, f20);
        sd(zero, sp, 0x0);
        v0 = 10;
        sd(v0, sp, 0x8);
        lw(a0, s0, 528);
        a1 = 0;
        a2 = 2;
        a3 = 1;
        ld(t0, sp, 0x50);
        ld(t1, sp, 0x60);
        t2 = 0;
        t3 = 0;
        mov_s(f12, f20);
        jal(ctx, 0x18E6F0u, gen::fn_sub_18BC10_0018bc10);
        v0 = 1;
        sw(v0, s0, 520);
    } else {
        // 0x0018e5ec
        charge(ctx, 37);
        a0 = addiu(s0, 264);
        a1 = addiu(s0, 8);
        jal(ctx, 0x18E5F4u, gen::fn_strcpy_00524270);
        v0 = 0x42200000;
        mtc1(v0, f1);
        sw(v0, sp, 0x60);
        v0 = 407;
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        swc1(f0, sp, 0x64);
        ld(t0, sp, 0x60);
        sd(t0, sp, 0x68);
        v0 = 0x43480000;
        mtc1(v0, f21);
        add_s(f0, f1, f21);
        swc1(f0, sp, 0x60);
        v0 = 0x42C80000;
        mtc1(v0, f20);
        sd(zero, sp, 0x0);
        v0 = 10;
        sd(v0, sp, 0x8);
        lw(v0, s0, 528);
        a0 = addiu(v0, 136);
        a1 = 0;
        a2 = 2;
        a3 = a2;
        ld(t1, sp, 0x60);
        t2 = 0;
        t3 = 0;
        mov_s(f12, f20);
        jal(ctx, 0x18E670u, gen::fn_sub_18BC10_0018bc10);
    }
    // 0x0018e700
    charge(ctx, 39);
    a0 = addiu(s0, 8);
    a1 = s1;
    jal(ctx, 0x18E708u, gen::fn_strcpy_00524270);
    v0 = 0x42200000;
    sw(v0, sp, 0x60);
    v0 = 407;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x64);
    ld(v0, sp, 0x60);
    sd(v0, sp, 0x58);
    lwc1(f0, sp, 0x58);
    sub_s(f0, f0, f21);
    swc1(f0, sp, 0x58);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, s0, 528);
    a0 = addiu(v0, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x60);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x18E774u, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f21, sp, 0x14);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0018E7A0 sub_18E7A0 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_18E7A0(task) [H_AreaPanelDestroy]: destroy callback of "h_area_panel_draw_proc": when a node is held at +4 the
// word is cleared and H_Cdvd_Destroy is called with 0 (a retail slip: $a0 is set to 0, not to the node, so the node
// is never released; kept as it is), then RwFree(tweens +528) when set, RwFree(work).
void sub_18E7A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018e7a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, 4);
    if (v0 != 0) {
        // 0x0018e7bc
        charge(ctx, 4);
        sw(zero, s0, 4);
        a0 = 0;
        jal(ctx, 0x18E7C4u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x0018e7cc
    charge(ctx, 3);
    lw(a0, s0, 528);
    if (a0 != 0) {
        // 0x0018e7d8
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x18E7E0u, v0.u());
    }
    // 0x0018e7e8
    charge(ctx, 11);
    sw(zero, s0, 528);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18E7F8u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0018E820 sub_18E820 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18E820(parent) [H_AreaPanelCreate]: RwCalloc(1, 536), kwlnTaskCreate(parent, "h_area_panel_draw_proc", 0x18B4,
// sub_18E540, sub_18E7A0, work); three tween records (sub_18B6D0(10): +528), shown (+524) = 1. Caller: the field root.
void sub_18E820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018e820
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 536;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x18E848u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0018e868
        charge(ctx, 14);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, 17760);  // "h_area_panel_draw_proc"
        a2 = 6324;
        a3 = 0x190000;
        a3 = addiu(a3, -6848);  // &sub_18E540
        t0 = 0x190000;
        t0 = addiu(t0, -6240);  // &sub_18E7A0
        t1 = s0;
        jal(ctx, 0x18E88Cu, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x0018e8ac
            charge(ctx, 7);
            a0 = 10;
            jal(ctx, 0x18E8B0u, gen::fn_sub_18B6D0_0018b6d0);
            sw(v0, s0, 528);
            v0 = 1;
            sw(v0, s0, 524);
            v0 = s1;
        } else {
            // 0x0018e8a0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018e85c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0018e8c8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0018E8E0 sub_18E8E0 -- 584 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18E8E0(work) [H_AreaPanelDraw]: for each of the three tweens (+528 + 68 i) that says draw (sub_18B700), when the
// panel is shown (+524): tween 0 draws the panel sprite (+532 frames 0 and 2), tweens 1 / 2 draw the current / the
// previous name (+8 / +264) with sub_3B2CB0 at the tween's position (x - 10, y + 5), alpha 255 - tween alpha.
void sub_18E8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x0018e8e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = 0;
    for (;;) {
        // 0x0018eafc
        charge(ctx, 3);
        v1 = slti(s2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0018e908
        charge(ctx, 9);
        v0 = sll(s2, 4);
        v0 = addu(v0, s2);
        s0 = sll(v0, 2);
        lw(v0, s3, 528);
        a0 = addu(v0, s0);
        jal(ctx, 0x18E91Cu, gen::fn_sub_18B700_0018b700);
        if (v0 != 0) {
            // 0x0018e92c
            charge(ctx, 5);
            lw(v1, s3, 528);
            s0 = addu(v1, s0);
            lw(v1, s3, 524);
            if (v1 != 0) {
                // 0x0018e940
                charge(ctx, 3);
                v1 = 2;
                if (s2 == v1) {
                    // 0x0018ea8c
                    charge(ctx, 27);
                    lw(v1, s0, 64);
                    v0 = 255;
                    v1 = subu(v0, v1);
                    lwc1(f0, s0, 56);
                    cvt_w_s(f0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    lwc1(f0, s0, 60);
                    cvt_w_s(f0, f0);
                    mfc1(v0, f0);
                    a1 = addiu(v0, 5);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    lwc1(f12, s0, 36);
                    a3 = 5;
                    t0 = 1;
                    t1 = addiu(s3, 264);
                    t2 = 16;
                    t3 = 0;
                    jal(ctx, 0x18EAF0u, gen::fn_sub_3B2CB0_003b2cb0);
                } else {
                    // 0x0018e94c
                    charge(ctx, 3);
                    t0 = 1;
                    if (s2 == t0) {
                        // 0x0018ea1c
                        charge(ctx, 28);
                        lw(v1, s0, 64);
                        v0 = 255;
                        v1 = subu(v0, v1);
                        lwc1(f0, s0, 56);
                        cvt_w_s(f0, f0);
                        cvt_s_w(f1, f0);
                        v0 = 0x41200000;
                        mtc1(v0, f0);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        lwc1(f0, s0, 60);
                        cvt_w_s(f0, f0);
                        mfc1(v0, f0);
                        a1 = addiu(v0, 5);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        lwc1(f12, s0, 36);
                        a3 = 5;
                        t1 = addiu(s3, 8);
                        t2 = 16;
                        t3 = 0;
                        jal(ctx, 0x18EA7Cu, gen::fn_sub_3B2CB0_003b2cb0);
                    } else {
                        // 0x0018e958
                        charge(ctx, 2);
                        if (s2 == 0) {
                            // 0x0018e968
                            charge(ctx, 45);
                            lbu(a3, s0, 64);
                            a0 = s1;
                            lw(a1, s3, 532);
                            a2 = 0;
                            lwc1(f12, s0, 56);
                            lwc1(f13, s0, 60);
                            lwc1(f14, s0, 36);
                            jal(ctx, 0x18E984u, gen::fn_sprDrawSpriteBasic_001159f0);
                            lwc1(f1, s0, 56);
                            v0 = 0x41A80000;
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 0x432E0000;
                            mtc1(v0, f0);
                            sub_s(f1, f1, f0);
                            v0 = 0x41D80000;
                            mtc1(v0, f0);
                            sub_s(f12, f1, f0);
                            lwc1(f1, s0, 60);
                            v0 = 0x43CE0000;
                            mtc1(v0, f0);
                            add_s(f1, f0, f1);
                            v0 = 399;
                            mtc1(v0, f0);
                            cvt_s_w(f0, f0);
                            sub_s(f1, f1, f0);
                            v0 = 0x40400000;
                            mtc1(v0, f0);
                            add_s(f13, f0, f1);
                            lbu(a3, s0, 64);
                            a0 = s1;
                            lw(a1, s3, 532);
                            a2 = 2;
                            lwc1(f14, s0, 36);
                            jal(ctx, 0x18EA0Cu, gen::fn_sprDrawSpriteBasic_001159f0);
                        } else {
                            // 0x0018e960
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
        // 0x0018eaf8
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0018eb08
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0018EB30 sub_18EB30 -- 16 bytes; leaf frame (no stack)
// sub_18EB30(task, shown): work +524 = shown.
void sub_18EB30(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0018eb30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 524);
}

// 0x0018EB40 sub_18EB40 -- 1048 bytes; frame 0x150: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18EB40(task) [H_BtlEscEffectUpdate] ("H_BtlEscEfectDraw"): the battle cut-in of one party member. Work (976
// bytes): +0 step, +4 the unit, +8 the animation task, +96 frame, +104 released. Every frame first sets the RW render
// states 6..12 (the RwRenderStateSet slot 0x960090) for 2-D drawing. Jump tables on the step and the unit:
//   0: the movie name by unit into the frame: "battle/cutin/c41_4b0N.cpk" with N = the unit's index below (3 -> 4b01,
//      4 -> 4b02, 5 -> 4b03, 7 -> 4b04, 8 -> 4b05, 9 -> 4b08 in The Answer else 4b06, 10 -> 4b07, the others 4b00;
//      the name is not used further: test_boot_panels checks it); step 1;
//   1: the animation task sub_111150(task, {0x40029, kind 11, index}) with that index (3 -> 1, 4 -> 2, 5 -> 3,
//      7 -> 4, 8 -> 5, 9 -> 8 in The Answer else 6, 10 -> 7, the others 0); step 2;
//   2: when it is ready (sub_1114B0): sub_111520(anim, 50); step 3 (the battle polls sub_18F060 and calls
//      sub_18F080);
//   4: sub_111530(anim) starts it; step 5;
//   5: the frame counts up to 50, beyond only once released (sub_18F0E0), then sub_111500(anim) every frame; the task
//      ends (-1) when the animation task is ending (state 3).
void sub_18EB40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018eb40
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, 60);
    jal(ctx, 0x18EB5Cu, gen::fn_sub_198590_00198590);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EB78u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EB8Cu, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EBA0u, v0.u());
    a0 = 9;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EBB4u, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EBC8u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EBDCu, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x18EBF0u, v0.u());
    lw(v0, s1, 0);
    at = sltiu(v0, 6);
    bool ended = false;  // host-side: the paths that skip the shared "return 0" block (0x0018ef38)
    if (at != 0) {
        // 0x0018ec08
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 27024);  // &0x7B6990
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x18EC24u:  // table[0]
            // 0x0018ec24
            charge(ctx, 4);
            lw(v0, s1, 4);
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x0018ec34
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 26976);  // &0x7B6960
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x18EC50u:  // table[2]
                    // 0x0018ec50
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17792);  // "battle/cutin/c41_4b00.cpk"
                    jal(ctx, 0x18EC5Cu, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18EC6Cu:  // table[3]
                    // 0x0018ec6c
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17824);  // "battle/cutin/c41_4b01.cpk"
                    jal(ctx, 0x18EC78u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18EC88u:  // table[4]
                    // 0x0018ec88
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17856);  // "battle/cutin/c41_4b02.cpk"
                    jal(ctx, 0x18EC94u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18ECA4u:  // table[5]
                    // 0x0018eca4
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17888);  // "battle/cutin/c41_4b03.cpk"
                    jal(ctx, 0x18ECB0u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18ECC0u:  // table[7]
                    // 0x0018ecc0
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17920);  // "battle/cutin/c41_4b04.cpk"
                    jal(ctx, 0x18ECCCu, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18ECDCu:  // table[8]
                    // 0x0018ecdc
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17952);  // "battle/cutin/c41_4b05.cpk"
                    jal(ctx, 0x18ECE8u, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18ECF8u:  // table[9]
                    // 0x0018ecf8
                    charge(ctx, 4);
                    jal(ctx, 0x18ECF8u, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x0018ed24
                        charge(ctx, 7);
                        a0 = addiu(sp, 0x40);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, 18016);  // "battle/cutin/c41_4b06.cpk"
                        jal(ctx, 0x18ED30u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x0018ed08
                        charge(ctx, 7);
                        a0 = addiu(sp, 0x40);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, 17984);  // "battle/cutin/c41_4b08.cpk"
                        jal(ctx, 0x18ED14u, gen::fn_sprintf_00523ac8);
                    }
                    break;
                case 0x18ED40u:  // table[10]
                    // 0x0018ed40
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 18048);  // "battle/cutin/c41_4b07.cpk"
                    jal(ctx, 0x18ED4Cu, gen::fn_sprintf_00523ac8);
                    break;
                case 0x18ED5Cu:  // table[0, 1, 6]
                    // 0x0018ed5c: the other units
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x40);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, 17792);  // "battle/cutin/c41_4b00.cpk"
                    jal(ctx, 0x18ED68u, gen::fn_sprintf_00523ac8);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            } else {
                // 0x0018ed5c (the same block: units 11 and up)
                charge(ctx, 5);
                a0 = addiu(sp, 0x40);
                a1 = 0x5E0000;
                a1 = addiu(a1, 17792);  // "battle/cutin/c41_4b00.cpk"
                jal(ctx, 0x18ED68u, gen::fn_sprintf_00523ac8);
            }
            // 0x0018ed70: step 1
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s1, 0);
            break;
        case 0x18ED80u:  // table[1]
            // 0x0018ed80
            charge(ctx, 10);
            v0 = 41;
            sh(v0, sp, 0x148);
            a0 = 4;
            sh(a0, sp, 0x14A);
            v0 = 11;
            sh(v0, sp, 0x14C);
            lw(v0, s1, 4);
            at = sltiu(v0, 11);
            if (at != 0) {
                // 0x0018eda8
                charge(ctx, 7);
                v1 = 0x7B0000;
                v1 = addiu(v1, 26928);  // &0x7B6930
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x18EDC4u:  // table[2]
                    // 0x0018edc4
                    charge(ctx, 3);
                    sh(zero, sp, 0x14E);
                    break;
                case 0x18EDD0u:  // table[3]
                    // 0x0018edd0
                    charge(ctx, 4);
                    v0 = 1;
                    sh(v0, sp, 0x14E);
                    break;
                case 0x18EDE0u:  // table[4]
                    // 0x0018ede0
                    charge(ctx, 4);
                    v0 = 2;
                    sh(v0, sp, 0x14E);
                    break;
                case 0x18EDF0u:  // table[5]
                    // 0x0018edf0
                    charge(ctx, 4);
                    v0 = 3;
                    sh(v0, sp, 0x14E);
                    break;
                case 0x18EE00u:  // table[7]
                    // 0x0018ee00
                    charge(ctx, 3);
                    sh(a0, sp, 0x14E);
                    break;
                case 0x18EE0Cu:  // table[8]
                    // 0x0018ee0c
                    charge(ctx, 4);
                    v0 = 5;
                    sh(v0, sp, 0x14E);
                    break;
                case 0x18EE1Cu:  // table[9]
                    // 0x0018ee1c
                    charge(ctx, 4);
                    jal(ctx, 0x18EE1Cu, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x0018ee3c
                        charge(ctx, 4);
                        v0 = 6;
                        sh(v0, sp, 0x14E);
                    } else {
                        // 0x0018ee2c
                        charge(ctx, 4);
                        v0 = 8;
                        sh(v0, sp, 0x14E);
                    }
                    break;
                case 0x18EE4Cu:  // table[10]
                    // 0x0018ee4c
                    charge(ctx, 4);
                    v0 = 7;
                    sh(v0, sp, 0x14E);
                    break;
                case 0x18EE5Cu:  // table[0, 1, 6]
                    // 0x0018ee5c: the other units -- index 0
                    charge(ctx, 1);
                    sh(zero, sp, 0x14E);
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            } else {
                // 0x0018ee5c (the same block: units 11 and up)
                charge(ctx, 1);
                sh(zero, sp, 0x14E);
            }
            // 0x0018ee60: the animation task on the descriptor {0x40029 (41, 4), kind 11, index}; step 2
            charge(ctx, 9);
            a0 = s2;
            ld(a1, sp, 0x148);
            jal(ctx, 0x18EE68u, gen::fn_sub_111150_00111150);
            sw(v0, s1, 8);
            v0 = 2;
            sw(v0, s1, 0);
            break;
        case 0x18EE84u:  // table[2]
            // 0x0018ee84
            charge(ctx, 5);
            lw(a0, s1, 8);
            jal(ctx, 0x18EE88u, gen::fn_sub_1114B0_001114b0);
            if (v0 != 0) {
                // 0x0018ee98
                charge(ctx, 8);
                lw(a0, s1, 8);
                a1 = 50;
                jal(ctx, 0x18EEA0u, gen::fn_sub_111520_00111520);
                v0 = 3;
                sw(v0, s1, 0);
            }
            break;
        case 0x18EEB8u:  // table[4]
            // 0x0018eeb8
            charge(ctx, 7);
            lw(a0, s1, 8);
            jal(ctx, 0x18EEBCu, gen::fn_sub_111530_00111530);
            v0 = 5;
            sw(v0, s1, 0);
            break;
        case 0x18EED4u:  // table[5]
            // 0x0018eed4
            charge(ctx, 4);
            lw(v1, s1, 96);
            v0 = slti(v1, 50);
            if (v0 != 0) {
                // 0x0018ef0c
                charge(ctx, 2);
                v0 = addiu(v1, 1);
                sw(v0, s1, 96);
            } else {
                // 0x0018eee4
                charge(ctx, 3);
                lw(v0, s1, 104);
                if (v0 != 0) {
                    // 0x0018eef0
                    charge(ctx, 7);
                    v0 = addiu(v1, 1);
                    sw(v0, s1, 96);
                    lw(a0, s1, 8);
                    jal(ctx, 0x18EEFCu, gen::fn_sub_111500_00111500);
                }
            }
            // 0x0018ef14
            charge(ctx, 6);
            lw(a0, s1, 8);
            jal(ctx, 0x18EF18u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 != v1) {
                break;
            }
            // 0x0018ef2c
            charge(ctx, 3);
            v0 = si(-1);
            ended = true;
            break;
        case 0x18EF38u:  // table[3]: step 3 waits for the battle (sub_18F080)
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    if (!ended) {
        // 0x0018ef38: keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0018ef3c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x0018EF60 sub_18EF60 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_18EF60(task) [H_BtlEscEffectDestroy]: destroy callback of "H_BtlEscEfectDraw": destroys the node at work +32 if
// held, RwFree(work).
void sub_18EF60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018ef60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 32);
    if (a0 != 0) {
        // 0x0018ef7c
        charge(ctx, 3);
        jal(ctx, 0x18EF7Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 32);
    }
    // 0x0018ef88
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x18EF94u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0018EFB0 sub_18EFB0 -- 176 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_18EFB0(parent, unit) [H_BtlEscEffectCreate]: RwCalloc(1, 976), kwlnTaskCreateWithAutoPriority(parent, 0x106F,
// "H_BtlEscEfectDraw", sub_18EB40, sub_18EF60, work); work +4 = unit. Caller: sub_2E3F70 (battle).
void sub_18EFB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018efb0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 976;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x18EFE0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0018f000
        charge(ctx, 13);
        a0 = s2;
        a1 = 4207;
        a2 = 0x5E0000;
        a2 = addiu(a2, 18080);  // "H_BtlEscEfectDraw"
        a3 = 0x190000;
        a3 = addiu(a3, -5312);  // &sub_18EB40
        t0 = 0x190000;
        t0 = addiu(t0, -4256);  // &sub_18EF60
        t1 = s0;
        jal(ctx, 0x18F024u, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        if (v0 != 0) {
            // 0x0018f040
            charge(ctx, 1);
            sw(s1, s0, 4);
        } else {
            // 0x0018f034
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0018eff4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0018f044 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0018F060 sub_18F060 -- 24 bytes; leaf frame (no stack)
// sub_18F060(task): step == 3. Caller: sub_2E3FB0.
void sub_18F060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0018f060
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 0);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
}

// 0x0018F080 sub_18F080 -- 20 bytes; leaf frame (no stack)
// sub_18F080(task): step = 4. Caller: sub_2E4040.
void sub_18F080(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0018f080
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 4;
    lw(v1, a0, 60);
    sw(a1, v1, 0);
}

// 0x0018F0A0 sub_18F0A0 -- 12 bytes; leaf frame (no stack)
// sub_18F0A0(): returns 63. Caller: sub_2E4120.
void sub_18F0A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0018f0a0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 63;
}

// 0x0018F0B0 sub_18F0B0 -- 16 bytes; leaf frame (no stack)
// sub_18F0B0(task): work +96 (the effect's frame). Caller: sub_2E4120.
void sub_18F0B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0018f0b0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 96);
}

// 0x0018F0C0 sub_18F0C0 -- 24 bytes; leaf frame (no stack)
// sub_18F0C0(task): work +96 >= 50. Caller: sub_2E4040.
void sub_18F0C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0018f0c0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lw(v0, v0, 96);
    v0 = slti(v0, 50);
    v0 = v0 ^ 0x1;
}

// 0x0018F0E0 sub_18F0E0 -- 20 bytes; leaf frame (no stack)
// sub_18F0E0(task): work +104 = 1. Caller: sub_2E4120.
void sub_18F0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0018f0e0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 1;
    lw(v1, a0, 60);
    sw(a1, v1, 104);
}

}  // namespace p3fes::game
