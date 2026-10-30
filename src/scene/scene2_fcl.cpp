// Slice scene2 (game/include/p3fes/game/scene2.h has the records): fclMisc.c's "psStatus" screen (loader, fades,
// layouts), the "psModel_dummy" preview and fclBankManager.c's update.
// p3fes_handgen bodies (register for register, block for block as the recompiled ones) with a role comment per
// function and named offsets / globals (each constant equals the literal it replaces; a script checks the bodies stay
// token-identical to the generator's output).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/scene.h"
#include "p3fes/game/scene2.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);
void fn_fclBank_UpdateTask_003cfe50(p3fes::EEContext&);
void fn_fclMisc_CreatePsModelDummyTask_003cf080(p3fes::EEContext&);
void fn_fclMisc_UpdatePsModelDummyTask_003cda00(p3fes::EEContext&);
void fn_fclMisc_UpdatePsStatusTask_003ca230(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_106730_00106730(p3fes::EEContext&);
void fn_sub_106860_00106860(p3fes::EEContext&);
void fn_sub_106EC0_00106ec0(p3fes::EEContext&);
void fn_sub_106F30_00106f30(p3fes::EEContext&);
void fn_sub_106FF0_00106ff0(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_119A20_00119a20(p3fes::EEContext&);
void fn_sub_119A60_00119a60(p3fes::EEContext&);
void fn_sub_119A80_00119a80(p3fes::EEContext&);
void fn_sub_133180_00133180(p3fes::EEContext&);
void fn_sub_1332F0_001332f0(p3fes::EEContext&);
void fn_sub_133460_00133460(p3fes::EEContext&);
void fn_sub_133A80_00133a80(p3fes::EEContext&);
void fn_sub_133B40_00133b40(p3fes::EEContext&);
void fn_sub_133B70_00133b70(p3fes::EEContext&);
void fn_sub_133B80_00133b80(p3fes::EEContext&);
void fn_sub_16BC80_0016bc80(p3fes::EEContext&);
void fn_sub_16BDB0_0016bdb0(p3fes::EEContext&);
void fn_sub_16BEE0_0016bee0(p3fes::EEContext&);
void fn_sub_16BF80_0016bf80(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DEB0_0016deb0(p3fes::EEContext&);
void fn_sub_17C0E0_0017c0e0(p3fes::EEContext&);
void fn_sub_198540_00198540(p3fes::EEContext&);
void fn_sub_198560_00198560(p3fes::EEContext&);
void fn_sub_198570_00198570(p3fes::EEContext&);
void fn_sub_198580_00198580(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A4580_001a4580(p3fes::EEContext&);
void fn_sub_1A4600_001a4600(p3fes::EEContext&);
void fn_sub_316E00_00316e00(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_317A20_00317a20(p3fes::EEContext&);
void fn_sub_318A70_00318a70(p3fes::EEContext&);
void fn_sub_318A90_00318a90(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_319050_00319050(p3fes::EEContext&);
void fn_sub_319070_00319070(p3fes::EEContext&);
void fn_sub_319230_00319230(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C9FE0_003c9fe0(p3fes::EEContext&);
void fn_sub_3CA6B0_003ca6b0(p3fes::EEContext&);
void fn_sub_3CA780_003ca780(p3fes::EEContext&);
void fn_sub_3CA960_003ca960(p3fes::EEContext&);
void fn_sub_3CACC0_003cacc0(p3fes::EEContext&);
void fn_sub_3CB1F0_003cb1f0(p3fes::EEContext&);
void fn_sub_3CB960_003cb960(p3fes::EEContext&);
void fn_sub_3CBA50_003cba50(p3fes::EEContext&);
void fn_sub_3CCC40_003ccc40(p3fes::EEContext&);
void fn_sub_3CD0B0_003cd0b0(p3fes::EEContext&);
void fn_sub_3CD5A0_003cd5a0(p3fes::EEContext&);
void fn_sub_3CDBA0_003cdba0(p3fes::EEContext&);
void fn_sub_3CE2A0_003ce2a0(p3fes::EEContext&);
void fn_sub_3CEA50_003cea50(p3fes::EEContext&);
void fn_sub_3CF6C0_003cf6c0(p3fes::EEContext&);
void fn_sub_3CFAC0_003cfac0(p3fes::EEContext&);
void fn_sub_3CFB50_003cfb50(p3fes::EEContext&);
void fn_sub_40EC50_0040ec50(p3fes::EEContext&);
void fn_sub_4944B0_004944b0(p3fes::EEContext&);
void fn_sub_49C480_0049c480(p3fes::EEContext&);
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);
void fn_sub_4C9D20_004c9d20(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace scene2;

// 0x003C9FE0 sub_3C9FE0 -- 592 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusLoadSprites] (work) Builds the sprites from the loaded archive (+200): the shared banks 6 / 8 / 10 (members
// 0..2 -> sprCreateHandleFromData -> sub_119A80), the sheet (member 3 -> +208) and the kind's extra bank (member 4 ->
// +216 for kinds 2 / 4, +212 for 0 / 1 / 3); prints its three progress lines (printf + sub_1052B0).
void sub_3C9FE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003c9fe0
    enter(ctx, 85);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, ps::kCdReq);
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 1816;
    jal(ctx, 0x3CA008u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16688);  // "psStatusSpriteInit 0\n"
    jal(ctx, 0x3CA018u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16688);  // "psStatusSpriteInit 0\n"
    jal(ctx, 0x3CA028u, gen::fn_sub_1052B0_001052b0);
    jal(ctx, 0x3CA030u, gen::fn_sub_119A20_00119a20);
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 1818;
    jal(ctx, 0x3CA048u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16720);  // "psStatusSpriteInit 1\n"
    jal(ctx, 0x3CA058u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16720);  // "psStatusSpriteInit 1\n"
    jal(ctx, 0x3CA068u, gen::fn_sub_1052B0_001052b0);
    a0 = s0;
    a1 = 0;
    a2 = addiu(sp, 0x3C);
    jal(ctx, 0x3CA07Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x3CA088u, gen::fn_sprCreateHandleFromData_00112420);
    a0 = 6;
    a1 = v0;
    jal(ctx, 0x3CA098u, gen::fn_sub_119A80_00119a80);
    a0 = s0;
    a1 = 1;
    a2 = addiu(sp, 0x3C);
    jal(ctx, 0x3CA0ACu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x3CA0B8u, gen::fn_sprCreateHandleFromData_00112420);
    a0 = 8;
    a1 = v0;
    jal(ctx, 0x3CA0C8u, gen::fn_sub_119A80_00119a80);
    a0 = s0;
    a1 = 2;
    a2 = addiu(sp, 0x3C);
    jal(ctx, 0x3CA0DCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x3CA0E8u, gen::fn_sprCreateHandleFromData_00112420);
    a0 = 10;
    a1 = v0;
    jal(ctx, 0x3CA0F8u, gen::fn_sub_119A80_00119a80);
    a0 = s0;
    a1 = 3;
    a2 = addiu(sp, 0x3C);
    jal(ctx, 0x3CA10Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x3CA118u, gen::fn_sprCreateHandleFromData_00112420);
    sw(v0, s1, ps::kSprSheet);
    // the kind's extra bank (archive member 4): kinds 2 / 4 -> +216, kinds 0 / 1 / 3 -> +212
    lw(v1, s1, ps::kKind);
    a1 = 4;
    if (v1 != a1) {
        // 0x003ca134
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            goto L_003ca1bc;
        }
        // 0x003ca140
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x003ca194
            charge(ctx, 10);
            a0 = s0;
            a2 = addiu(sp, 0x3C);
            jal(ctx, 0x3CA19Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
            a0 = v0;
            jal(ctx, 0x3CA1A8u, gen::fn_sprCreateHandleFromData_00112420);
            sw(v0, s1, ps::kSprA);
        } else {
            // 0x003ca14c
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
                // 0x003ca158
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003ca168;
                }
                // 0x003ca160
                charge(ctx, 2);
                goto L_003ca1e0;
            }
        L_003ca168:
            charge(ctx, 11);
            a0 = s0;
            a1 = 4;
            a2 = addiu(sp, 0x3C);
            jal(ctx, 0x3CA174u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
            a0 = v0;
            jal(ctx, 0x3CA180u, gen::fn_sprCreateHandleFromData_00112420);
            sw(v0, s1, ps::kSprA);
        }
        goto L_003ca1e0;
    }
L_003ca1bc:
    charge(ctx, 9);
    a0 = s0;
    a1 = 4;
    a2 = addiu(sp, 0x3C);
    jal(ctx, 0x3CA1C8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
    a0 = v0;
    jal(ctx, 0x3CA1D4u, gen::fn_sprCreateHandleFromData_00112420);
    sw(v0, s1, ps::kSprB);
L_003ca1e0:
    charge(ctx, 20);
    a0 = addiu(gp, -22008);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 15896);  // "fclMisc.c"
    a2 = 1840;
    jal(ctx, 0x3CA1F0u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16752);  // "psStatusSpriteInit 2\n"
    jal(ctx, 0x3CA200u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 16752);  // "psStatusSpriteInit 2\n"
    jal(ctx, 0x3CA210u, gen::fn_sub_1052B0_001052b0);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003CA230 fclMisc_UpdatePsStatusTask -- 988 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Update of "psStatus": states 1 (print), 2 (request the file +204, H_Cdvd_Request(name, 1) -> +200), 3 (once loaded:
// the sprites, sub_3C9FE0; state 4, flag 0x20); state 4 runs the fade in (8) / out (0x10) over +12 / +14 frames into the
// alpha +18 (255 t / n), the slide (0x40: +22 up to +20 or down to 0 by the side +232), the layout callback +220 and
// the text group's colour (sub_133B70 / sub_133B80; flag 4 resets it, sub_133B40 sets the alpha while drawn); 0.
void fclMisc_UpdatePsStatusTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ca230
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3CA23Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lw(a0, v0, ps::kState);
    v0 = 4;
    if (a0 == v0) {
        // 0x003ca398
        charge(ctx, 4);
        // state 4 (run): the fade in (8) / out (0x10) of the alpha +18 over +12 / +14 frames
        lw(v1, s0, ps::kFlags);
        v0 = v1 & 0x8;
        if (v0 == 0) {
            // 0x003ca40c
            charge(ctx, 3);
            v0 = v1 & 0x10;
            if (v0 != 0) {
                // 0x003ca418
                charge(ctx, 18);
                lh(v0, s0, ps::kTimer);
                v0 = addiu(v0, 1);
                sh(v0, s0, ps::kTimer);
                v1 = dsll32(v0, 16);
                v1 = dsra32(v1, 16);
                v0 = sll(v1, 8);
                v1 = subu(v0, v1);
                lh(v0, s0, ps::kFadeOut);
                div(v1, v0);
                mflo(v1);
                v0 = 255;
                v0 = subu(v0, v1);
                sh(v0, s0, ps::kAlpha);
                lh(v1, s0, ps::kTimer);
                lh(v0, s0, ps::kFadeOut);
                v0 = slt(v1, v0);
                if (v0 == 0) {
                    // 0x003ca460
                    charge(ctx, 8);
                    sh(zero, s0, ps::kTimer);
                    lw(v1, s0, ps::kFlags);
                    v0 = si(-17);
                    v1 = v1 & v0;
                    sw(v1, s0, ps::kFlags);
                    v0 = si(-2);
                    v0 = v1 & v0;
                    sw(v0, s0, ps::kFlags);
                }
            }
        } else {
            // 0x003ca3a8
            charge(ctx, 18);
            v0 = v1 | 0x1;
            sw(v0, s0, ps::kFlags);
            lh(v0, s0, ps::kTimer);
            v0 = addiu(v0, 1);
            sh(v0, s0, ps::kTimer);
            v1 = dsll32(v0, 16);
            v1 = dsra32(v1, 16);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            lh(v0, s0, ps::kFadeIn);
            div(v1, v0);
            mflo(v0);
            sh(v0, s0, ps::kAlpha);
            lh(v1, s0, ps::kTimer);
            lh(v0, s0, ps::kFadeIn);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                // 0x003ca3f0
                charge(ctx, 7);
                sh(zero, s0, ps::kTimer);
                lw(v1, s0, ps::kFlags);
                v0 = si(-9);
                v0 = v1 & v0;
                sw(v0, s0, ps::kFlags);
            }
        }
        // 0x003ca480
        charge(ctx, 4);
        lw(v0, s0, ps::kFlags);
        v0 = v0 & 0x40;
        if (v0 != 0) {
            // 0x003ca490
            charge(ctx, 3);
            lb(v1, s0, ps::kRow);
            if (v1 != 0) {
                // 0x003ca4d0
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x003ca4dc
                    charge(ctx, 9);
                    lh(v0, s0, ps::kSlideTime);
                    v0 = addiu(v0, 1);
                    sh(v0, s0, ps::kSlideTime);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    lh(v0, s0, ps::kSlideFrames);
                    v0 = slt(v1, v0);
                    if (v0 == 0) {
                        // 0x003ca500
                        charge(ctx, 4);
                        lw(v1, s0, ps::kFlags);
                        v0 = si(-65);
                        v0 = v1 & v0;
                        sw(v0, s0, ps::kFlags);
                    }
                }
            } else {
                // 0x003ca49c
                charge(ctx, 7);
                lh(v0, s0, ps::kSlideTime);
                v0 = addiu(v0, -1);
                sh(v0, s0, ps::kSlideTime);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (i64(v0) <= 0) {
                    // 0x003ca4b8
                    charge(ctx, 6);
                    lw(v1, s0, ps::kFlags);
                    v0 = si(-65);
                    v0 = v1 & v0;
                    sw(v0, s0, ps::kFlags);
                }
            }
        }
        // 0x003ca510
        charge(ctx, 8);
        a0 = s0;
        // the layout callback, then the text group's colour (flag 4 resets it; while drawn the persona row and the alpha)
        lw(v0, s0, ps::kLayout);
        jalr(ctx, 0x3CA518u, v0.u());
        lw(v1, s0, ps::kFlags);
        v0 = v1 & 0x1;
        if (v0 == 0) {
            // 0x003ca5c4
            charge(ctx, 12);
            lw(a0, s0, ps::kText);
            jal(ctx, 0x3CA5C8u, gen::fn_sub_133B70_00133b70);
            a0 = v0 & 0xFF;
            lw(v1, s0, ps::kRgba);
            v0 = si(-256);
            v0 = v1 & v0;
            a2 = v0 | a0;
            lw(a0, s0, ps::kText);
            a1 = 0;
            jal(ctx, 0x3CA5ECu, gen::fn_sub_133B80_00133b80);
        } else {
            // 0x003ca530
            charge(ctx, 3);
            v0 = v1 & 0x4;
            if (v0 != 0) {
                // 0x003ca53c
                charge(ctx, 16);
                lw(a0, s0, ps::kText);
                jal(ctx, 0x3CA540u, gen::fn_sub_133B70_00133b70);
                a0 = v0 & 0xFF;
                lw(v1, s0, ps::kRgba);
                v0 = si(-256);
                v0 = v1 & v0;
                a2 = v0 | a0;
                lw(a0, s0, ps::kText);
                a1 = 0;
                jal(ctx, 0x3CA564u, gen::fn_sub_133B80_00133b80);
                lw(v1, s0, ps::kFlags);
                v0 = si(-5);
                v0 = v1 & v0;
                sw(v0, s0, ps::kFlags);
            }
            // 0x003ca57c
            charge(ctx, 18);
            lw(a0, s0, ps::kText);
            jal(ctx, 0x3CA580u, gen::fn_sub_133B70_00133b70);
            a0 = v0 & 0xFF;
            lw(v1, s0, ps::kRgba);
            v0 = si(-256);
            v0 = v1 & v0;
            a2 = v0 | a0;
            lhu(a1, s0, ps::kPersona);
            lw(a0, s0, ps::kText);
            jal(ctx, 0x3CA5A4u, gen::fn_sub_133B80_00133b80);
            lbu(a1, s0, ps::kAlpha);
            lw(a0, s0, ps::kText);
            jal(ctx, 0x3CA5B4u, gen::fn_sub_133B40_00133b40);
        }
    } else {
        // 0x003ca258
        charge(ctx, 3);
        v0 = 3;
        if (a0 != v0) {
            // 0x003ca264
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x003ca270
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003ca284
                    charge(ctx, 15);
                    sw(v1, s0, ps::kState);
                    a0 = addiu(gp, -22008);  // "[%s:%d]"
                    a1 = 0x6A0000;
                    a1 = addiu(a1, 15896);  // "fclMisc.c"
                    a2 = 1853;
                    // state 1: the start print, then state 2's request
                    jal(ctx, 0x3CA298u, gen::fn_printf_005225a8);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 16784);  // "psStatusCalc START\n"
                    jal(ctx, 0x3CA2A8u, gen::fn_printf_005225a8);
                    a0 = 0x6A0000;
                    a0 = addiu(a0, 16784);  // "psStatusCalc START\n"
                    jal(ctx, 0x3CA2B8u, gen::fn_sub_1052B0_001052b0);
                    goto L_003ca2c0;
                }
                // 0x003ca27c
                charge(ctx, 2);
                // 0x003ca5f4 (the shared epilogue, written out on this path)
                charge(ctx, 6);
                v0 = 0;
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        // state 2: request the file +204 (state 3)
        L_003ca2c0:
            charge(ctx, 25);
            v0 = 3;
            sw(v0, s0, ps::kState);
            lw(a0, s0, ps::kFile);
            a1 = 1;
            jal(ctx, 0x3CA2D0u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, ps::kCdReq);
            a0 = addiu(gp, -22008);  // "[%s:%d]"
            a1 = 0x6A0000;
            a1 = addiu(a1, 15896);  // "fclMisc.c"
            a2 = 1857;
            jal(ctx, 0x3CA2ECu, gen::fn_printf_005225a8);
            a0 = 0x6A0000;
            a0 = addiu(a0, 16816);  // "psStatusCalc LOAD %s %x\n"
            lw(a1, s0, ps::kFile);
            lw(a2, s0, ps::kCdReq);
            jal(ctx, 0x3CA304u, gen::fn_printf_005225a8);
            a0 = 0x6A0000;
            a0 = addiu(a0, 16816);  // "psStatusCalc LOAD %s %x\n"
            lw(a1, s0, ps::kFile);
            lw(a2, s0, ps::kCdReq);
            jal(ctx, 0x3CA31Cu, gen::fn_sub_1052B0_001052b0);
        }
        // 0x003ca324
        charge(ctx, 5);
        lw(a0, s0, ps::kCdReq);
        // state 3: once loaded, the sprites (state 4, flag 0x20)
        jal(ctx, 0x3CA328u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        if (v0 != 0) {
            // 0x003ca338
            charge(ctx, 24);
            a0 = s0;
            jal(ctx, 0x3CA33Cu, gen::fn_sub_3C9FE0_003c9fe0);
            v0 = 4;
            sw(v0, s0, ps::kState);
            lw(v0, s0, ps::kFlags);
            v0 = v0 | 0x20;
            sw(v0, s0, ps::kFlags);
            a0 = addiu(gp, -22008);  // "[%s:%d]"
            a1 = 0x6A0000;
            a1 = addiu(a1, 15896);  // "fclMisc.c"
            a2 = 1863;
            jal(ctx, 0x3CA368u, gen::fn_printf_005225a8);
            a0 = 0x6A0000;
            a0 = addiu(a0, 16848);  // "psStatusCalc LOAD_SYNC\n"
            jal(ctx, 0x3CA378u, gen::fn_printf_005225a8);
            a0 = 0x6A0000;
            a0 = addiu(a0, 16848);  // "psStatusCalc LOAD_SYNC\n"
            jal(ctx, 0x3CA388u, gen::fn_sub_1052B0_001052b0);
        }
    }
    // 0x003ca5f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CA6B0 sub_3CA6B0 -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of "psStatus": frees the sprite banks 6 / 8 / 10 (sub_119A60 -> sub_1124B0), the sheet and the two kind banks,
// the file request (H_Cdvd_Destroy) and the work (RwFree).
void sub_3CA6B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ca6b0
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3CA6BCu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    a0 = 6;
    jal(ctx, 0x3CA6CCu, gen::fn_sub_119A60_00119a60);
    a0 = v0;
    jal(ctx, 0x3CA6D8u, gen::fn_sub_1124B0_001124b0);
    a0 = 8;
    jal(ctx, 0x3CA6E4u, gen::fn_sub_119A60_00119a60);
    a0 = v0;
    jal(ctx, 0x3CA6F0u, gen::fn_sub_1124B0_001124b0);
    a0 = 10;
    jal(ctx, 0x3CA6FCu, gen::fn_sub_119A60_00119a60);
    a0 = v0;
    jal(ctx, 0x3CA708u, gen::fn_sub_1124B0_001124b0);
    lw(a0, s0, ps::kSprSheet);
    jal(ctx, 0x3CA714u, gen::fn_sub_1124B0_001124b0);
    lw(a0, s0, ps::kSprA);
    if (a0 != 0) {
        // 0x003ca728
        charge(ctx, 2);
        jal(ctx, 0x3CA728u, gen::fn_sub_1124B0_001124b0);
    }
    // 0x003ca730
    charge(ctx, 3);
    lw(a0, s0, ps::kSprB);
    if (a0 != 0) {
        // 0x003ca73c
        charge(ctx, 2);
        jal(ctx, 0x3CA73Cu, gen::fn_sub_1124B0_001124b0);
    }
    // 0x003ca744
    charge(ctx, 13);
    lw(a0, s0, ps::kCdReq);
    jal(ctx, 0x3CA748u, gen::fn_H_Cdvd_Destroy_00100ec0);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwFree);  // 0x96017C
    jalr(ctx, 0x3CA75Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CA780 sub_3CA780 -- 468 bytes; frame 0x80: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [psStatusDrawSprite] (x, y, rgba, sprite, w, h, file, $f12 z, $f13, $f14, $f15) One sprite of a sheet: a handle
// (sprCreateHandle(0, file, sprite)) at (x, y, z), alpha 255 - (rgba & 0xFF), r / g / b from rgba's upper bytes, w / h
// (+36 / +38; mostly 0, the bottom bar's end piece -260), $f13 at +32, $f14 / $f15 as the two 4096-fixed values +40 /
// +42 (the layouts pass 0, 0, 1.0, 1.0), drawn and freed; 0. The layouts pass rgba = 0xFFFFFF00 | the work's alpha
// (+18).
void sub_3CA780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x003ca780
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
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
    s5 = a0;
    s4 = a1;
    mov_s(f23, f12);
    s3 = a2;
    s2 = t0;
    s1 = t1;
    mov_s(f22, f13);
    mov_s(f21, f14);
    mov_s(f20, f15);
    a0 = 0;
    a1 = t2;
    a2 = a3;
    jal(ctx, 0x3CA7E0u, gen::fn_sprCreateHandle_001158b0);
    s0 = v0;
    mtc1(s5, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, sprh::kX);
    mtc1(s4, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, sprh::kY);
    swc1(f23, v0, sprh::kZ);
    a0 = 255;
    v1 = s3 & 0xFF;
    v1 = subu(a0, v1);
    sb(v1, v0, sprh::kInvAlpha);
    v1 = srl(s3, 24);
    sb(v1, v0, sprh::kR);
    v1 = srl(s3, 16);
    sb(v1, v0, sprh::kG);
    v1 = srl(s3, 8);
    sb(v1, v0, sprh::kB);
    sh(s2, v0, sprh::kW);
    sh(s1, v0, sprh::kH);
    swc1(f22, v0, sprh::kU);
    v0 = 0x45800000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x003ca884
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFFFF;
    } else {
        // 0x003ca86c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFFFF;
    }
    // 0x003ca89c
    charge(ctx, 11);
    sh(v1, s0, sprh::kFix0);
    v0 = 0x45800000;
    mtc1(v0, f0);
    mul_s(f1, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x003ca8e0
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFFFF;
    } else {
        // 0x003ca8c8
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFFFF;
    }
    // 0x003ca8f8
    charge(ctx, 23);
    sh(v1, s0, sprh::kFix1);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x3CA904u, gen::fn_sub_1127D0_001127d0);
    a0 = s0;
    jal(ctx, 0x3CA910u, gen::fn_sub_115980_00115980);
    v0 = 0;
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
    sp = addiu(sp, 0x80);
}

// 0x003CACC0 sub_3CACC0 -- 912 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusDrawTabs] (work) The row tabs: for each of +233 rows the tab frames 23 / 24 (the cursor row +232) and the
// labels 25 + 2 i / 26 + 2 i at the per-count positions of the tables 0x6A41E8 / 0x6A41F8, the last row 37 / 38.
void sub_3CACC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cacc0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 16872);  // &0x6A41E8
    a0 = addiu(sp, 0x80);
    v1 = 5;
    for (;;) {
        // 0x003cacf4
        charge(ctx, 7);
        lh(v0, a1, 0);
        a1 = addiu(a1, 2);
        v1 = addiu(v1, -1);
        sh(v0, a0, 0);
        a0 = addiu(a0, 2);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003cad10
    charge(ctx, 4);
    a1 = 0x6A0000;
    a1 = addiu(a1, 16888);  // &0x6A41F8
    a0 = addiu(sp, 0x70);
    v1 = 5;
    for (;;) {
        // 0x003cad20
        charge(ctx, 7);
        lh(v0, a1, 0);
        a1 = addiu(a1, 2);
        v1 = addiu(v1, -1);
        sh(v0, a0, 0);
        a0 = addiu(a0, 2);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003cad3c
    charge(ctx, 9);
    lb(v0, s0, ps::kRows);
    s4 = addiu(v0, -3);
    s5 = 0;
    v0 = sll(s4, 1);
    v0 = addu(v0, sp);
    s2 = addiu(v0, 112);
    s1 = addiu(v0, 128);
    for (;;) {
        // 0x003caeb0
        charge(ctx, 5);
        lb(v0, s0, ps::kRows);
        s3 = addiu(v0, -1);
        v0 = slt(s5, s3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cad60
        charge(ctx, 3);
        lb(v0, s0, ps::kRow);
        if (v0 != s5) {
            // 0x003cae10
            charge(ctx, 39);
            lh(v1, s1, 0);
            lh(v0, s2, 0);
            mult(v0, s5, v0);
            a0 = addu(v1, v0);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a1 = 10;
            a3 = 23;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CAE54u, gen::fn_sub_3CA780_003ca780);
            lh(v1, s1, 0);
            lh(v0, s2, 0);
            mult(v0, s5, v0);
            a0 = addu(v1, v0);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = sll(s5, 1);
            a3 = addiu(v0, 25);
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a1 = 8;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CAEA4u, gen::fn_sub_3CA780_003ca780);
        } else {
            // 0x003cad6c
            charge(ctx, 41);
            lh(v1, s1, 0);
            lh(v0, s2, 0);
            mult(v0, s5, v0);
            a0 = addu(v1, v0);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a1 = 10;
            a3 = 24;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CADB0u, gen::fn_sub_3CA780_003ca780);
            lh(v1, s1, 0);
            lh(v0, s2, 0);
            mult(v0, s5, v0);
            a0 = addu(v1, v0);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = sll(s5, 1);
            a3 = addiu(v0, 26);
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a1 = 8;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CAE00u, gen::fn_sub_3CA780_003ca780);
        }
        // 0x003caeac
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x003caec4
    charge(ctx, 3);
    lb(v0, s0, ps::kRow);
    if (v0 != s3) {
        // 0x003caf80
        charge(ctx, 42);
        v0 = sll(s4, 1);
        v0 = addu(v0, sp);
        s2 = addiu(v0, 112);
        s1 = addiu(v0, 128);
        lh(v1, s1, 0);
        lh(v0, s2, 0);
        mult(v0, s3, v0);
        a0 = addu(v1, v0);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a1 = 10;
        a3 = 23;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CAFD4u, gen::fn_sub_3CA780_003ca780);
        lh(v1, s1, 0);
        lh(v0, s2, 0);
        mult(v0, s3, v0);
        a0 = addu(v1, v0);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a1 = 8;
        a3 = 37;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CB020u, gen::fn_sub_3CA780_003ca780);
    } else {
        // 0x003caed0
        charge(ctx, 44);
        v0 = sll(s4, 1);
        v0 = addu(v0, sp);
        s2 = addiu(v0, 112);
        s1 = addiu(v0, 128);
        lh(v1, s1, 0);
        lh(v0, s2, 0);
        mult(v0, s3, v0);
        a0 = addu(v1, v0);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a1 = 10;
        a3 = 24;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CAF24u, gen::fn_sub_3CA780_003ca780);
        lh(v1, s1, 0);
        lh(v0, s2, 0);
        mult(v0, s3, v0);
        a0 = addu(v1, v0);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a1 = 8;
        a3 = 38;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CAF70u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cb028 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003CB1F0 sub_3CB1F0 -- 1896 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// [psStatusLayoutSheet] (work) Layout callback: the sheet frame (frames 3..6), the text group (sub_133A80 then
// sub_1332F0 / sub_133180 by flag 2), and by page +234: 2 the kind's header frames (21 / 22 or 2 / 3), the tabs
// (sub_3CACC0) and, with a persona and a value, the arcana icon (sub_16DEB0 / sub_16DBA0) and two numbers
// (sprintf "%d" -> sub_40EC50 with the colour callback sub_3CB050); 1 the header and frame 20; 0 frame 20 and the numbers.
void sub_3CB1F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cb1f0
    enter(ctx, 76);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s0 = a0;
    mtc1(zero, f12);
    lh(v1, a0, 18);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 37;
    a3 = 5;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CB23Cu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 363;
    a1 = 37;
    a3 = 6;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CB27Cu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 98;
    a3 = 4;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CB2BCu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 3;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CB2FCu, gen::fn_sub_3CA780_003ca780);
    lw(a0, s0, ps::kText);
    jal(ctx, 0x3CB308u, gen::fn_sub_133A80_00133a80);
    v1 = addiu(sp, 0x58);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003cb320
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003cb33c
    charge(ctx, 4);
    lw(v0, s0, ps::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003cb370
        charge(ctx, 7);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x58);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CB384u, gen::fn_sub_133180_00133180);
    } else {
        // 0x003cb34c
        charge(ctx, 9);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x58);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CB360u, gen::fn_sub_1332F0_001332f0);
    }
    // 0x003cb38c
    charge(ctx, 4);
    // by page +234: 2 the header, tabs and numbers; 1 the header and frame 20; 0 frame 20 and the numbers
    lh(v1, s0, ps::kPage);
    a1 = 2;
    if (v1 == a1) {
        // 0x003cb6bc
        charge(ctx, 4);
        lw(v1, s0, ps::kKind);
        v0 = 4;
        if (v1 != v0) {
            // 0x003cb6cc
            charge(ctx, 2);
            if (v1 == a1) {
                goto L_003cb784;
            }
            // 0x003cb6d4
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x003cb6e0
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_003cb6fc;
                }
                // 0x003cb6ec
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003cb6fc;
                }
                // 0x003cb6f4
                charge(ctx, 2);
                goto L_003cb804;
            }
        L_003cb6fc:
            charge(ctx, 34);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 42;
            a1 = 12;
            a3 = 2;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CB734u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 519;
            a1 = 12;
            a3 = 3;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CB774u, gen::fn_sub_3CA780_003ca780);
            goto L_003cb804;
        }
    L_003cb784:
        charge(ctx, 32);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 22;
        a1 = 12;
        a3 = 21;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CB7BCu, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 539;
        a1 = 12;
        a3 = 22;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CB7FCu, gen::fn_sub_3CA780_003ca780);
    L_003cb804:
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x3CB808u, gen::fn_sub_3CACC0_003cacc0);
        lhu(a0, s0, ps::kPersona);
        if (a0 != 0) {
            // 0x003cb81c
            charge(ctx, 3);
            lw(v1, s0, ps::kValue);
            if (v1 != 0) {
                // 0x003cb828
                charge(ctx, 70);
                lw(v1, gp, g::kGpPersonaTable);  // 0x7CE420
                v0 = sll(a0, 3);
                v0 = subu(v0, a0);
                v0 = sll(v0, 1);
                v0 = addu(v0, v1);
                lbu(a0, v0, 2);
                jal(ctx, 0x3CB840u, gen::fn_sub_16DEB0_0016deb0);
                a0 = v0;
                jal(ctx, 0x3CB84Cu, gen::fn_sub_16DBA0_0016dba0);
                s1 = dsll32(v0, 24);
                s1 = dsra32(s1, 24);
                mtc1(zero, f12);
                lh(v1, s0, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 361;
                a1 = 201;
                a3 = 0;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s0, ps::kSprB);
                jal(ctx, 0x3CB894u, gen::fn_sub_3CA780_003ca780);
                a2 = dsll32(s1, 16);
                a2 = dsra32(a2, 16);
                a0 = addiu(sp, 0x48);
                a1 = addiu(gp, -22000);  // "%d"
                jal(ctx, 0x3CB8ACu, gen::fn_sprintf_00523ac8);
                sd(s0, sp, 0x0);
                mtc1(zero, f12);
                lh(v1, s0, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                a0 = 526;
                a1 = 199;
                a3 = 0;
                t0 = addiu(sp, 0x48);
                t1 = 0;
                t2 = 23;
                t3 = 0x3D0000;
                t3 = addiu(t3, -20400);  // &sub_3CB050
                jal(ctx, 0x3CB8E8u, gen::fn_sub_40EC50_0040ec50);
                a0 = addiu(sp, 0x48);
                a1 = addiu(gp, -21996);  // "%6d"
                lw(a2, s0, ps::kValue);
                jal(ctx, 0x3CB8FCu, gen::fn_sprintf_00523ac8);
                sd(s0, sp, 0x0);
                mtc1(zero, f12);
                lh(v1, s0, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                a0 = 612;
                a1 = 252;
                a3 = 1;
                t0 = addiu(sp, 0x48);
                t1 = a3;
                t2 = 27;
                t3 = 0x3D0000;
                t3 = addiu(t3, -20400);  // &sub_3CB050
                jal(ctx, 0x3CB938u, gen::fn_sub_40EC50_0040ec50);
            }
        }
    } else {
        // 0x003cb39c
        charge(ctx, 3);
        a0 = 1;
        if (v1 == a0) {
            // 0x003cb530
            charge(ctx, 4);
            lw(v1, s0, ps::kKind);
            v0 = 4;
            if (v1 != v0) {
                // 0x003cb540
                charge(ctx, 2);
                if (v1 == a1) {
                    goto L_003cb5f4;
                }
                // 0x003cb548
                charge(ctx, 3);
                v0 = 3;
                if (v1 != v0) {
                    // 0x003cb554
                    charge(ctx, 2);
                    if (v1 == a0) {
                        goto L_003cb56c;
                    }
                    // 0x003cb55c
                    charge(ctx, 2);
                    if (v1 == 0) {
                        goto L_003cb56c;
                    }
                    // 0x003cb564
                    charge(ctx, 2);
                    goto L_003cb674;
                }
            L_003cb56c:
                charge(ctx, 34);
                mtc1(zero, f12);
                lh(v1, s0, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 42;
                a1 = 12;
                a3 = 2;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s0, ps::kSprA);
                jal(ctx, 0x3CB5A4u, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s0, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 519;
                a1 = 12;
                a3 = 3;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s0, ps::kSprA);
                jal(ctx, 0x3CB5E4u, gen::fn_sub_3CA780_003ca780);
                goto L_003cb674;
            }
        L_003cb5f4:
            charge(ctx, 32);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 22;
            a1 = 12;
            a3 = 21;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CB62Cu, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 539;
            a1 = 12;
            a3 = 22;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CB66Cu, gen::fn_sub_3CA780_003ca780);
        L_003cb674:
            charge(ctx, 18);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 193;
            a1 = 8;
            a3 = 20;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprSheet);
            jal(ctx, 0x3CB6ACu, gen::fn_sub_3CA780_003ca780);
        } else {
            // 0x003cb3a8
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x003cb3b8
                charge(ctx, 19);
                mtc1(zero, f12);
                lh(v1, s0, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 193;
                a1 = 8;
                a3 = 20;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s0, ps::kSprSheet);
                jal(ctx, 0x3CB3F0u, gen::fn_sub_3CA780_003ca780);
                lhu(a0, s0, ps::kPersona);
                if (a0 != 0) {
                    // 0x003cb404
                    charge(ctx, 3);
                    lw(v1, s0, ps::kValue);
                    if (v1 != 0) {
                        // 0x003cb410
                        charge(ctx, 72);
                        lw(v1, gp, g::kGpPersonaTable);  // 0x7CE420
                        v0 = sll(a0, 3);
                        v0 = subu(v0, a0);
                        v0 = sll(v0, 1);
                        v0 = addu(v0, v1);
                        lbu(a0, v0, 2);
                        jal(ctx, 0x3CB428u, gen::fn_sub_16DEB0_0016deb0);
                        a0 = v0;
                        jal(ctx, 0x3CB434u, gen::fn_sub_16DBA0_0016dba0);
                        s1 = dsll32(v0, 24);
                        s1 = dsra32(s1, 24);
                        mtc1(zero, f12);
                        lh(v1, s0, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = 361;
                        a1 = 201;
                        a3 = 0;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s0, ps::kSprB);
                        jal(ctx, 0x3CB47Cu, gen::fn_sub_3CA780_003ca780);
                        a2 = dsll32(s1, 16);
                        a2 = dsra32(a2, 16);
                        a0 = addiu(sp, 0x50);
                        a1 = addiu(gp, -22000);  // "%d"
                        jal(ctx, 0x3CB494u, gen::fn_sprintf_00523ac8);
                        sd(s0, sp, 0x0);
                        mtc1(zero, f12);
                        lh(v1, s0, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a0 = 526;
                        a1 = 199;
                        a3 = 0;
                        t0 = addiu(sp, 0x50);
                        t1 = 0;
                        t2 = 23;
                        t3 = 0x3D0000;
                        t3 = addiu(t3, -20400);  // &sub_3CB050
                        jal(ctx, 0x3CB4D0u, gen::fn_sub_40EC50_0040ec50);
                        a0 = addiu(sp, 0x50);
                        a1 = addiu(gp, -21996);  // "%6d"
                        lw(a2, s0, ps::kValue);
                        jal(ctx, 0x3CB4E4u, gen::fn_sprintf_00523ac8);
                        sd(s0, sp, 0x0);
                        mtc1(zero, f12);
                        lh(v1, s0, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a0 = 612;
                        a1 = 252;
                        a3 = 1;
                        t0 = addiu(sp, 0x50);
                        t1 = a3;
                        t2 = 27;
                        t3 = 0x3D0000;
                        t3 = addiu(t3, -20400);  // &sub_3CB050
                        jal(ctx, 0x3CB520u, gen::fn_sub_40EC50_0040ec50);
                    }
                }
            } else {
                // 0x003cb3b0
                charge(ctx, 2);
            }
        }
    }
    // 0x003cb940 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x003CB960 sub_3CB960 -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusLayoutBar] (work) Layout callback: the three frames of the bottom bar (2 at the origin, 0 at (-357, 189),
// 1 at (-97, 189) 260 wide).
void sub_3CB960(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cb960
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    mtc1(zero, f12);
    lh(v1, a0, 18);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 2;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CB9A8u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-357);
    a1 = 189;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CB9ECu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-97);
    a1 = 189;
    a3 = 1;
    t0 = si(-260);
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CBA30u, gen::fn_sub_3CA780_003ca780);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CBA50 sub_3CBA50 -- 4572 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psStatusLayoutPages] (work) Layout callback for the paged screens (page +234 4, 3, 2, ...): the sheet frames, the
// text group, the panel slide (sub_3CA960), the kind's header and, per row, the row frames (69 / 70, 52 / 53, 71 + 2 i
// / 72 + 2 i and the like) at the x positions of the table 0x7CD708.
void sub_3CBA50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cba50
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    // by page +234: the frames of each paged layout
    lh(v1, a0, ps::kPage);
    v0 = 4;
    if (v1 == v0) {
        // 0x003cc2f8
        charge(ctx, 4);
        lb(v1, s1, ps::kRow);
        v0 = 1;
        if (v1 != v0) {
            // 0x003cc768
            charge(ctx, 74);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 0;
            a1 = 37;
            a3 = 5;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC7A0u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 363;
            a1 = 37;
            a3 = 6;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC7E0u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 0;
            a1 = 98;
            a3 = 4;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC820u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 0;
            a1 = 0;
            a3 = 3;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC860u, gen::fn_sub_3CA780_003ca780);
            lw(a0, s1, ps::kText);
            jal(ctx, 0x3CC86Cu, gen::fn_sub_133A80_00133a80);
            a0 = s1;
            jal(ctx, 0x3CC878u, gen::fn_sub_3CA960_003ca960);
            lw(a0, s1, ps::kKind);
            v1 = 4;
            if (a0 != v1) {
                // 0x003cc890
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_003cc94c;
                }
                // 0x003cc89c
                charge(ctx, 3);
                v1 = 3;
                if (a0 != v1) {
                    // 0x003cc8a8
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        goto L_003cc8c4;
                    }
                    // 0x003cc8b4
                    charge(ctx, 2);
                    if (a0 == 0) {
                        goto L_003cc8c4;
                    }
                    // 0x003cc8bc
                    charge(ctx, 2);
                    goto L_003cc9cc;
                }
            L_003cc8c4:
                charge(ctx, 34);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 42;
                a1 = 12;
                a3 = 2;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprA);
                jal(ctx, 0x3CC8FCu, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 519;
                a1 = 12;
                a3 = 3;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprA);
                jal(ctx, 0x3CC93Cu, gen::fn_sub_3CA780_003ca780);
                goto L_003cc9cc;
            }
        L_003cc94c:
            charge(ctx, 32);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 22;
            a1 = 12;
            a3 = 21;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC984u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 539;
            a1 = 12;
            a3 = 22;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC9C4u, gen::fn_sub_3CA780_003ca780);
        L_003cc9cc:
            charge(ctx, 11);
            lh(a2, gp, -21984);  // 0x7CD710
            lh(a1, gp, -21982);  // 0x7CD712
            lh(a0, gp, -21980);  // 0x7CD714
            lh(v1, gp, -21978);  // 0x7CD716
            sh(a2, sp, 0x68);
            sh(a1, sp, 0x6A);
            sh(a0, sp, 0x6C);
            sh(v1, sp, 0x6E);
            s0 = 0;
            for (;;) {
                // 0x003ccbb0
                charge(ctx, 4);
                lb(v1, s1, ps::kRows);
                v1 = slt(s0, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003cc9f8
                charge(ctx, 3);
                lb(v0, s1, ps::kRow);
                if (v0 != s0) {
                    // 0x003ccadc
                    charge(ctx, 52);
                    s3 = sll(s0, 1);
                    v0 = addu(s3, sp);
                    s2 = addiu(v0, 104);
                    lh(s4, s2, 0);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    a3 = 70;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CCB24u, gen::fn_sub_3CA780_003ca780);
                    lh(a0, s2, 4);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a1 = 10;
                    a3 = 53;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CCB64u, gen::fn_sub_3CA780_003ca780);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    a3 = addiu(s3, 72);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CCBA4u, gen::fn_sub_3CA780_003ca780);
                } else {
                    // 0x003cca04
                    charge(ctx, 54);
                    s3 = sll(s0, 1);
                    v0 = addu(s3, sp);
                    s2 = addiu(v0, 104);
                    lh(s4, s2, 0);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    a3 = 69;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CCA4Cu, gen::fn_sub_3CA780_003ca780);
                    lh(a0, s2, 4);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a1 = 10;
                    a3 = 52;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CCA8Cu, gen::fn_sub_3CA780_003ca780);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    a3 = addiu(s3, 71);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CCACCu, gen::fn_sub_3CA780_003ca780);
                }
                // 0x003ccbac
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x003ccbc0
            charge(ctx, 2);
        } else {
            // 0x003cc308
            charge(ctx, 74);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 0;
            a1 = 37;
            a3 = 5;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC340u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 363;
            a1 = 37;
            a3 = 6;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC380u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 0;
            a1 = 98;
            a3 = 4;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC3C0u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 0;
            a1 = 0;
            a3 = 3;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC400u, gen::fn_sub_3CA780_003ca780);
            lw(a0, s1, ps::kText);
            jal(ctx, 0x3CC40Cu, gen::fn_sub_133A80_00133a80);
            a0 = s1;
            jal(ctx, 0x3CC418u, gen::fn_sub_3CA960_003ca960);
            lw(a0, s1, ps::kKind);
            v1 = 4;
            if (a0 != v1) {
                // 0x003cc430
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_003cc4ec;
                }
                // 0x003cc43c
                charge(ctx, 3);
                v1 = 3;
                if (a0 != v1) {
                    // 0x003cc448
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        goto L_003cc464;
                    }
                    // 0x003cc454
                    charge(ctx, 2);
                    if (a0 == 0) {
                        goto L_003cc464;
                    }
                    // 0x003cc45c
                    charge(ctx, 2);
                    goto L_003cc56c;
                }
            L_003cc464:
                charge(ctx, 34);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 42;
                a1 = 12;
                a3 = 2;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprA);
                jal(ctx, 0x3CC49Cu, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 519;
                a1 = 12;
                a3 = 3;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprA);
                jal(ctx, 0x3CC4DCu, gen::fn_sub_3CA780_003ca780);
                goto L_003cc56c;
            }
        L_003cc4ec:
            charge(ctx, 32);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 22;
            a1 = 12;
            a3 = 21;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC524u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 539;
            a1 = 12;
            a3 = 22;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CC564u, gen::fn_sub_3CA780_003ca780);
        L_003cc56c:
            charge(ctx, 11);
            lh(a2, gp, -21984);  // 0x7CD710
            lh(a1, gp, -21982);  // 0x7CD712
            lh(a0, gp, -21980);  // 0x7CD714
            lh(v1, gp, -21978);  // 0x7CD716
            sh(a2, sp, 0x70);
            sh(a1, sp, 0x72);
            sh(a0, sp, 0x74);
            sh(v1, sp, 0x76);
            s0 = 0;
            for (;;) {
                // 0x003cc750
                charge(ctx, 4);
                lb(v1, s1, ps::kRows);
                v1 = slt(s0, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003cc598
                charge(ctx, 3);
                lb(v0, s1, ps::kRow);
                if (v0 != s0) {
                    // 0x003cc67c
                    charge(ctx, 52);
                    s3 = sll(s0, 1);
                    v0 = addu(s3, sp);
                    s2 = addiu(v0, 112);
                    lh(s4, s2, 0);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    a3 = 70;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CC6C4u, gen::fn_sub_3CA780_003ca780);
                    lh(a0, s2, 4);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a1 = 10;
                    a3 = 53;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CC704u, gen::fn_sub_3CA780_003ca780);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    a3 = addiu(s3, 72);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CC744u, gen::fn_sub_3CA780_003ca780);
                } else {
                    // 0x003cc5a4
                    charge(ctx, 54);
                    s3 = sll(s0, 1);
                    v0 = addu(s3, sp);
                    s2 = addiu(v0, 112);
                    lh(s4, s2, 0);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    a3 = 69;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CC5ECu, gen::fn_sub_3CA780_003ca780);
                    lh(a0, s2, 4);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a1 = 10;
                    a3 = 52;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CC62Cu, gen::fn_sub_3CA780_003ca780);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    a3 = addiu(s3, 71);
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = s4;
                    a1 = 10;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprSheet);
                    jal(ctx, 0x3CC66Cu, gen::fn_sub_3CA780_003ca780);
                }
                // 0x003cc74c
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x003cc760
            charge(ctx, 2);
        }
    } else {
        // 0x003cba80
        charge(ctx, 3);
        a3 = 3;
        if (v1 == a3) {
            // 0x003cba94
            charge(ctx, 4);
            lb(v1, s1, ps::kRow);
            v0 = 1;
            if (v1 != v0) {
                // 0x003cbf74
                charge(ctx, 19);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 0;
                a1 = 0;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBFA8u, gen::fn_sub_3CA780_003ca780);
                lw(a0, s1, ps::kKind);
                v1 = 4;
                if (a0 != v1) {
                    // 0x003cbfc0
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        goto L_003cc07c;
                    }
                    // 0x003cbfcc
                    charge(ctx, 3);
                    v1 = 3;
                    if (a0 != v1) {
                        // 0x003cbfd8
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            goto L_003cbff4;
                        }
                        // 0x003cbfe4
                        charge(ctx, 2);
                        if (a0 == 0) {
                            goto L_003cbff4;
                        }
                        // 0x003cbfec
                        charge(ctx, 2);
                        goto L_003cc0fc;
                    }
                L_003cbff4:
                    charge(ctx, 34);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 42;
                    a1 = 12;
                    a3 = 2;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprA);
                    jal(ctx, 0x3CC02Cu, gen::fn_sub_3CA780_003ca780);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 519;
                    a1 = 12;
                    a3 = 3;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprA);
                    jal(ctx, 0x3CC06Cu, gen::fn_sub_3CA780_003ca780);
                    goto L_003cc0fc;
                }
            L_003cc07c:
                charge(ctx, 32);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 22;
                a1 = 12;
                a3 = 21;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CC0B4u, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 539;
                a1 = 12;
                a3 = 22;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CC0F4u, gen::fn_sub_3CA780_003ca780);
            L_003cc0fc:
                charge(ctx, 11);
                lh(a2, gp, -21992);  // 0x7CD708
                lh(a1, gp, -21990);  // 0x7CD70A
                lh(a0, gp, -21988);  // 0x7CD70C
                lh(v1, gp, -21986);  // 0x7CD70E
                sh(a2, sp, 0x78);
                sh(a1, sp, 0x7A);
                sh(a0, sp, 0x7C);
                sh(v1, sp, 0x7E);
                s0 = 0;
                for (;;) {
                    // 0x003cc2e0
                    charge(ctx, 4);
                    lb(v1, s1, ps::kRows);
                    v1 = slt(s0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003cc128
                    charge(ctx, 3);
                    lb(v0, s1, ps::kRow);
                    if (v0 != s0) {
                        // 0x003cc20c
                        charge(ctx, 52);
                        s3 = sll(s0, 1);
                        v0 = addu(s3, sp);
                        s2 = addiu(v0, 120);
                        lh(s4, s2, 0);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        a3 = 50;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CC254u, gen::fn_sub_3CA780_003ca780);
                        lh(a0, s2, 4);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a1 = 10;
                        a3 = 52;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CC294u, gen::fn_sub_3CA780_003ca780);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a3 = addiu(s3, 54);
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CC2D4u, gen::fn_sub_3CA780_003ca780);
                    } else {
                        // 0x003cc134
                        charge(ctx, 54);
                        s3 = sll(s0, 1);
                        v0 = addu(s3, sp);
                        s2 = addiu(v0, 120);
                        lh(s4, s2, 0);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        a3 = 51;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CC17Cu, gen::fn_sub_3CA780_003ca780);
                        lh(a0, s2, 4);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a1 = 10;
                        a3 = 53;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CC1BCu, gen::fn_sub_3CA780_003ca780);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a3 = addiu(s3, 55);
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CC1FCu, gen::fn_sub_3CA780_003ca780);
                    }
                    // 0x003cc2dc
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x003cc2f0
                charge(ctx, 2);
            } else {
                // 0x003cbaa4
                charge(ctx, 71);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 0;
                a1 = 37;
                a3 = 5;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBADCu, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 363;
                a1 = 37;
                a3 = 6;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBB1Cu, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 0;
                a1 = 98;
                a3 = 4;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBB5Cu, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 0;
                a1 = 0;
                a3 = 3;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBB9Cu, gen::fn_sub_3CA780_003ca780);
                lw(a0, s1, ps::kText);
                jal(ctx, 0x3CBBA8u, gen::fn_sub_133A80_00133a80);
                v1 = addiu(sp, 0x88);
                v0 = 8;
                if (v1 != 0) {
                    for (;;) {
                        // 0x003cbbc0
                        charge(ctx, 7);
                        sb(zero, v1, 0);
                        v1 = addiu(v1, 1);
                        v0 = addiu(v0, -1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x003cbbdc
                charge(ctx, 4);
                lw(v0, s1, ps::kFlags);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x003cbc10
                    charge(ctx, 7);
                    mtc1(zero, f12);
                    lh(a3, s1, ps::kAlpha);
                    ld(a0, sp, 0x88);
                    a1 = addiu(s1, 28);
                    a2 = addiu(s1, 32);
                    jal(ctx, 0x3CBC24u, gen::fn_sub_133180_00133180);
                } else {
                    // 0x003cbbec
                    charge(ctx, 9);
                    mtc1(zero, f12);
                    lh(a3, s1, ps::kAlpha);
                    ld(a0, sp, 0x88);
                    a1 = addiu(s1, 28);
                    a2 = addiu(s1, 32);
                    jal(ctx, 0x3CBC00u, gen::fn_sub_1332F0_001332f0);
                }
                // 0x003cbc2c
                charge(ctx, 4);
                lw(a0, s1, ps::kKind);
                v1 = 4;
                if (a0 != v1) {
                    // 0x003cbc3c
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        goto L_003cbcf8;
                    }
                    // 0x003cbc48
                    charge(ctx, 3);
                    v1 = 3;
                    if (a0 != v1) {
                        // 0x003cbc54
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            goto L_003cbc70;
                        }
                        // 0x003cbc60
                        charge(ctx, 2);
                        if (a0 == 0) {
                            goto L_003cbc70;
                        }
                        // 0x003cbc68
                        charge(ctx, 2);
                        goto L_003cbd78;
                    }
                L_003cbc70:
                    charge(ctx, 34);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 42;
                    a1 = 12;
                    a3 = 2;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprA);
                    jal(ctx, 0x3CBCA8u, gen::fn_sub_3CA780_003ca780);
                    mtc1(zero, f12);
                    lh(v1, s1, ps::kAlpha);
                    v0 = si(-256);
                    a2 = v1 | v0;
                    v0 = 0x3F800000;
                    mtc1(v0, f14);
                    a0 = 519;
                    a1 = 12;
                    a3 = 3;
                    t0 = 0;
                    t1 = 0;
                    mov_s(f13, f12);
                    mov_s(f15, f14);
                    lw(t2, s1, ps::kSprA);
                    jal(ctx, 0x3CBCE8u, gen::fn_sub_3CA780_003ca780);
                    goto L_003cbd78;
                }
            L_003cbcf8:
                charge(ctx, 32);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 22;
                a1 = 12;
                a3 = 21;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBD30u, gen::fn_sub_3CA780_003ca780);
                mtc1(zero, f12);
                lh(v1, s1, ps::kAlpha);
                v0 = si(-256);
                a2 = v1 | v0;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = 539;
                a1 = 12;
                a3 = 22;
                t0 = 0;
                t1 = 0;
                mov_s(f13, f12);
                mov_s(f15, f14);
                lw(t2, s1, ps::kSprSheet);
                jal(ctx, 0x3CBD70u, gen::fn_sub_3CA780_003ca780);
            L_003cbd78:
                charge(ctx, 11);
                lh(a2, gp, -21992);  // 0x7CD708
                lh(a1, gp, -21990);  // 0x7CD70A
                lh(a0, gp, -21988);  // 0x7CD70C
                lh(v1, gp, -21986);  // 0x7CD70E
                sh(a2, sp, 0x80);
                sh(a1, sp, 0x82);
                sh(a0, sp, 0x84);
                sh(v1, sp, 0x86);
                s0 = 0;
                for (;;) {
                    // 0x003cbf5c
                    charge(ctx, 4);
                    lb(v1, s1, ps::kRows);
                    v1 = slt(s0, v1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003cbda4
                    charge(ctx, 3);
                    lb(v0, s1, ps::kRow);
                    if (v0 != s0) {
                        // 0x003cbe88
                        charge(ctx, 52);
                        s3 = sll(s0, 1);
                        v0 = addu(s3, sp);
                        s2 = addiu(v0, 128);
                        lh(s4, s2, 0);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        a3 = 50;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CBED0u, gen::fn_sub_3CA780_003ca780);
                        lh(a0, s2, 4);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a1 = 10;
                        a3 = 52;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CBF10u, gen::fn_sub_3CA780_003ca780);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a3 = addiu(s3, 54);
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CBF50u, gen::fn_sub_3CA780_003ca780);
                    } else {
                        // 0x003cbdb0
                        charge(ctx, 54);
                        s3 = sll(s0, 1);
                        v0 = addu(s3, sp);
                        s2 = addiu(v0, 128);
                        lh(s4, s2, 0);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        a3 = 51;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CBDF8u, gen::fn_sub_3CA780_003ca780);
                        lh(a0, s2, 4);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a1 = 10;
                        a3 = 53;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CBE38u, gen::fn_sub_3CA780_003ca780);
                        mtc1(zero, f12);
                        lh(v1, s1, ps::kAlpha);
                        v0 = si(-256);
                        a2 = v1 | v0;
                        a3 = addiu(s3, 55);
                        v0 = 0x3F800000;
                        mtc1(v0, f14);
                        a0 = s4;
                        a1 = 10;
                        t0 = 0;
                        t1 = 0;
                        mov_s(f13, f12);
                        mov_s(f15, f14);
                        lw(t2, s1, ps::kSprSheet);
                        jal(ctx, 0x3CBE78u, gen::fn_sub_3CA780_003ca780);
                    }
                    // 0x003cbf58
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x003cbf6c
                charge(ctx, 2);
            }
        } else {
            // 0x003cba8c
            charge(ctx, 2);
            // 0x003ccbc8
            charge(ctx, 16);
            mtc1(zero, f12);
            lh(v1, s1, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 193;
            a1 = 8;
            a3 = 20;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s1, ps::kSprSheet);
            jal(ctx, 0x3CCC00u, gen::fn_sub_3CA780_003ca780);
        }
    }
    // 0x003ccc08 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003CCC40 sub_3CCC40 -- 1108 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusLayoutSheetBar] (work) Layout callback: the bottom bar and the sheet frames, the text group and its panel
// draw (sub_1332F0 or sub_133460), then the page's frames.
void sub_3CCC40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003ccc40
    enter(ctx, 125);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    mtc1(zero, f12);
    lh(v1, a0, 18);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 2;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCC88u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-357);
    a1 = 189;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCCCCu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-97);
    a1 = 189;
    a3 = 1;
    t0 = si(-260);
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCD10u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 37;
    a3 = 5;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCD50u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 363;
    a1 = 37;
    a3 = 6;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCD90u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 98;
    a3 = 4;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCDD0u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 3;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CCE10u, gen::fn_sub_3CA780_003ca780);
    lw(a0, s0, ps::kText);
    jal(ctx, 0x3CCE1Cu, gen::fn_sub_133A80_00133a80);
    v1 = addiu(sp, 0x28);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003cce34
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003cce50
    charge(ctx, 4);
    lw(v0, s0, ps::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003cce84
        charge(ctx, 7);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x28);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CCE98u, gen::fn_sub_133460_00133460);
    } else {
        // 0x003cce60
        charge(ctx, 9);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x28);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CCE74u, gen::fn_sub_1332F0_001332f0);
    }
    // 0x003ccea0
    charge(ctx, 3);
    lw(t2, s0, ps::kSprA);
    if (t2 != 0) {
        // 0x003cceac
        charge(ctx, 31);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 170;
        a1 = 8;
        a3 = 0;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x3CCEE0u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 376;
        a1 = 8;
        a3 = 1;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprA);
        jal(ctx, 0x3CCF20u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003ccf28
    charge(ctx, 4);
    // by page +234: the page's frames
    lh(v1, s0, ps::kPage);
    a1 = 1;
    if (v1 == a1) {
        // 0x003ccf38
        charge(ctx, 4);
        lw(a0, s0, ps::kKind);
        v1 = 4;
        if (a0 != v1) {
            // 0x003ccf48
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_003cd000;
            }
            // 0x003ccf54
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x003ccf60
                charge(ctx, 2);
                if (a0 == a1) {
                    goto L_003ccf78;
                }
                // 0x003ccf68
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_003ccf78;
                }
                // 0x003ccf70
                charge(ctx, 2);
                // 0x003cd080 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_003ccf78:
            charge(ctx, 34);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 42;
            a1 = 12;
            a3 = 2;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CCFB0u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 519;
            a1 = 12;
            a3 = 3;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CCFF0u, gen::fn_sub_3CA780_003ca780);
            // 0x003cd080 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_003cd000:
        charge(ctx, 32);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 22;
        a1 = 12;
        a3 = 21;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CD038u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 539;
        a1 = 12;
        a3 = 22;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CD078u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cd080 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CD0B0 sub_3CD0B0 -- 1244 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusLayoutB] (work) Layout callback: as sub_3CCC40 with the other page set (sub_1332F0 / sub_133180).
void sub_3CD0B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cd0b0
    enter(ctx, 125);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    mtc1(zero, f12);
    lh(v1, a0, 18);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 2;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD0F8u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-357);
    a1 = 189;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD13Cu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-97);
    a1 = 189;
    a3 = 1;
    t0 = si(-260);
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD180u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 37;
    a3 = 5;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD1C0u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 363;
    a1 = 37;
    a3 = 6;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD200u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 98;
    a3 = 4;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD240u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 3;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD280u, gen::fn_sub_3CA780_003ca780);
    lw(a0, s0, ps::kText);
    jal(ctx, 0x3CD28Cu, gen::fn_sub_133A80_00133a80);
    v1 = addiu(sp, 0x28);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003cd2a4
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003cd2c0
    charge(ctx, 4);
    lw(v0, s0, ps::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003cd2f4
        charge(ctx, 7);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x28);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CD308u, gen::fn_sub_133180_00133180);
    } else {
        // 0x003cd2d0
        charge(ctx, 9);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x28);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CD2E4u, gen::fn_sub_1332F0_001332f0);
    }
    // 0x003cd310
    charge(ctx, 3);
    lw(t2, s0, ps::kSprA);
    if (t2 != 0) {
        // 0x003cd31c
        charge(ctx, 31);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 170;
        a1 = 8;
        a3 = 0;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x3CD350u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 376;
        a1 = 8;
        a3 = 1;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprA);
        jal(ctx, 0x3CD390u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cd398
    charge(ctx, 4);
    // by page +234: the page's frames
    lh(v1, s0, ps::kPage);
    a1 = 1;
    if (v1 == a1) {
        // 0x003cd3a8
        charge(ctx, 4);
        lw(a0, s0, ps::kKind);
        v1 = 4;
        if (a0 != v1) {
            // 0x003cd3b8
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_003cd470;
            }
            // 0x003cd3c4
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x003cd3d0
                charge(ctx, 2);
                if (a0 == a1) {
                    goto L_003cd3e8;
                }
                // 0x003cd3d8
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_003cd3e8;
                }
                // 0x003cd3e0
                charge(ctx, 2);
                goto L_003cd4f0;
            }
        L_003cd3e8:
            charge(ctx, 34);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 42;
            a1 = 12;
            a3 = 2;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CD420u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 519;
            a1 = 12;
            a3 = 3;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CD460u, gen::fn_sub_3CA780_003ca780);
            goto L_003cd4f0;
        }
    L_003cd470:
        charge(ctx, 32);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 22;
        a1 = 12;
        a3 = 21;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CD4A8u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 539;
        a1 = 12;
        a3 = 22;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CD4E8u, gen::fn_sub_3CA780_003ca780);
    }
L_003cd4f0:
    charge(ctx, 3);
    lw(t2, s0, ps::kSprA);
    if (t2 != 0) {
        // 0x003cd4fc
        charge(ctx, 31);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 468;
        a1 = 417;
        a3 = 13;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x3CD530u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 561;
        a1 = 417;
        a3 = 14;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprA);
        jal(ctx, 0x3CD570u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cd578 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CD5A0 sub_3CD5A0 -- 1108 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [psStatusLayoutC] (work) Layout callback: a third page set of the same frames.
void sub_3CD5A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003cd5a0
    enter(ctx, 125);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    mtc1(zero, f12);
    lh(v1, a0, 18);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 2;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD5E8u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-357);
    a1 = 189;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD62Cu, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = lui(0xC20C);
    mtc1(v0, f13);
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = si(-97);
    a1 = 189;
    a3 = 1;
    t0 = si(-260);
    t1 = 0;
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD670u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 37;
    a3 = 5;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD6B0u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 363;
    a1 = 37;
    a3 = 6;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD6F0u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 98;
    a3 = 4;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD730u, gen::fn_sub_3CA780_003ca780);
    mtc1(zero, f12);
    lh(v1, s0, ps::kAlpha);
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = 0x3F800000;
    mtc1(v0, f14);
    a0 = 0;
    a1 = 0;
    a3 = 3;
    t0 = 0;
    t1 = 0;
    mov_s(f13, f12);
    mov_s(f15, f14);
    lw(t2, s0, ps::kSprSheet);
    jal(ctx, 0x3CD770u, gen::fn_sub_3CA780_003ca780);
    lw(a0, s0, ps::kText);
    jal(ctx, 0x3CD77Cu, gen::fn_sub_133A80_00133a80);
    v1 = addiu(sp, 0x28);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003cd794
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003cd7b0
    charge(ctx, 4);
    lw(v0, s0, ps::kFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003cd7e4
        charge(ctx, 7);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x28);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CD7F8u, gen::fn_sub_133180_00133180);
    } else {
        // 0x003cd7c0
        charge(ctx, 9);
        mtc1(zero, f12);
        lh(a3, s0, ps::kAlpha);
        ld(a0, sp, 0x28);
        a1 = addiu(s0, 28);
        a2 = addiu(s0, 32);
        jal(ctx, 0x3CD7D4u, gen::fn_sub_1332F0_001332f0);
    }
    // 0x003cd800
    charge(ctx, 3);
    lw(t2, s0, ps::kSprA);
    if (t2 != 0) {
        // 0x003cd80c
        charge(ctx, 31);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 170;
        a1 = 8;
        a3 = 0;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x3CD840u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 376;
        a1 = 8;
        a3 = 1;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprA);
        jal(ctx, 0x3CD880u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cd888
    charge(ctx, 4);
    // by page +234: the page's frames
    lh(v1, s0, ps::kPage);
    a1 = 1;
    if (v1 == a1) {
        // 0x003cd898
        charge(ctx, 4);
        lw(a0, s0, ps::kKind);
        v1 = 4;
        if (a0 != v1) {
            // 0x003cd8a8
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_003cd960;
            }
            // 0x003cd8b4
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x003cd8c0
                charge(ctx, 2);
                if (a0 == a1) {
                    goto L_003cd8d8;
                }
                // 0x003cd8c8
                charge(ctx, 2);
                if (a0 == 0) {
                    goto L_003cd8d8;
                }
                // 0x003cd8d0
                charge(ctx, 2);
                // 0x003cd9e0 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_003cd8d8:
            charge(ctx, 34);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 42;
            a1 = 12;
            a3 = 2;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CD910u, gen::fn_sub_3CA780_003ca780);
            mtc1(zero, f12);
            lh(v1, s0, ps::kAlpha);
            v0 = si(-256);
            a2 = v1 | v0;
            v0 = 0x3F800000;
            mtc1(v0, f14);
            a0 = 519;
            a1 = 12;
            a3 = 3;
            t0 = 0;
            t1 = 0;
            mov_s(f13, f12);
            mov_s(f15, f14);
            lw(t2, s0, ps::kSprA);
            jal(ctx, 0x3CD950u, gen::fn_sub_3CA780_003ca780);
            // 0x003cd9e0 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_003cd960:
        charge(ctx, 32);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 22;
        a1 = 12;
        a3 = 21;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CD998u, gen::fn_sub_3CA780_003ca780);
        mtc1(zero, f12);
        lh(v1, s0, ps::kAlpha);
        v0 = si(-256);
        a2 = v1 | v0;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = 539;
        a1 = 12;
        a3 = 22;
        t0 = 0;
        t1 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        lw(t2, s0, ps::kSprSheet);
        jal(ctx, 0x3CD9D8u, gen::fn_sub_3CA780_003ca780);
    }
    // 0x003cd9e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003CDA00 fclMisc_UpdatePsModelDummyTask -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Update of "psModel_dummy": once the model's load finished (sub_316F70) it is released (sub_3174E0): -1; else 0.
void fclMisc_UpdatePsModelDummyTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cda00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3CDA0Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x3CDA1Cu, gen::fn_sub_316F70_00316f70);
    if (v0 == 0) {
        // 0x003cda44
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003cda2c
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x3CDA30u, gen::fn_sub_3174E0_003174e0);
        v0 = si(-1);
    }
    // 0x003cda48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CE2A0 sub_3CE2A0 -- 1956 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [psModelUpdate] (task) The persona-model preview, once a frame: states 1 / 2 release an old model and request the
// persona's (sub_316E00(11, id, 0); none for id 0 -> state 4); 3 once loaded: motion 8 (sub_319230), the second id's
// set-up (sub_3CDBA0) or the model's colour flags by the persona's kind (sub_17C0E0: 4 -> sub_319070, 2 -> flag 0x200)
// and the two colour vectors (sub_16BC80 / sub_16BDB0); state 4 (shown, animating) runs the rgba fade and the two vec4
// tweens (the float -> u8 conversions with the 2^31 bias) and draws (sub_3CEA50); 0.
void sub_3CE2A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x003ce2a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3CE2B4u, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    v1 = addiu(sp, 0x38);
    v0 = 8;
    if (v1 != 0) {
        for (;;) {
            // 0x003ce2d0
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003ce2ec
    charge(ctx, 4);
    // by state: 4 runs the fade and the tweens and draws; 1 / 2 request the persona's model; 3 waits for it
    lw(a0, s0, psm::kState);
    v0 = 4;
    if (a0 == v0) {
        // 0x003ce490
        charge(ctx, 4);
        lw(v1, s0, psm::kFlags);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x003ce4a0
            charge(ctx, 4);
            v0 = 0x10000;
            v0 = v1 & v0;
            if (v0 != 0) {
                // 0x003ce4b0
                charge(ctx, 6);
                v0 = addiu(s0, 164);
                lh(a0, s0, psm::kFadeTime);
                lh(v1, s0, psm::kFadeFrames);
                at = slt(a0, v1);
                if (at != 0) {
                    // 0x003ce4c8
                    charge(ctx, 21);
                    v1 = addiu(a0, 1);
                    sh(v1, v0, psfade::kTime);
                    lbu(a1, v0, psfade::kFrom);
                    a0 = dsll32(v1, 16);
                    a0 = dsra32(a0, 16);
                    lbu(v1, v0, psfade::kTo);
                    v1 = subu(v1, a1);
                    mult(v1, a0, v1);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lh(v1, v0, psfade::kFrames);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    if (i64(a1) < 0) {
                        // 0x003ce530
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003ce51c
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003ce54c
                    charge(ctx, 7);
                    add_s(f1, f0, f1);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x003ce580
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                        a0 = a0 & 0xFF;
                    } else {
                        // 0x003ce568
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                        a0 = a0 & 0xFF;
                    }
                    // 0x003ce598
                    charge(ctx, 19);
                    sb(a0, s0, psm::kRgba);
                    lbu(a1, v0, psfade::kFromG);
                    lbu(v1, v0, psfade::kToG);
                    a0 = subu(v1, a1);
                    lh(v1, v0, psfade::kTime);
                    mult(v1, v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lh(v1, v0, psfade::kFrames);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    if (i64(a1) < 0) {
                        // 0x003ce5f8
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003ce5e4
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003ce614
                    charge(ctx, 7);
                    add_s(f1, f0, f1);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x003ce648
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                        a0 = a0 & 0xFF;
                    } else {
                        // 0x003ce630
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                        a0 = a0 & 0xFF;
                    }
                    // 0x003ce660
                    charge(ctx, 19);
                    sb(a0, s0, psm::kRgbaG);
                    lbu(a1, v0, psfade::kFromB);
                    lbu(v1, v0, psfade::kToB);
                    a0 = subu(v1, a1);
                    lh(v1, v0, psfade::kTime);
                    mult(v1, v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lh(v1, v0, psfade::kFrames);
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    if (i64(a1) < 0) {
                        // 0x003ce6c0
                        charge(ctx, 7);
                        a0 = srl(a1, 1);
                        v1 = a1 & 0x1;
                        a0 = a0 | v1;
                        mtc1(a0, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003ce6ac
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003ce6dc
                    charge(ctx, 7);
                    add_s(f1, f0, f1);
                    v1 = 0x4F000000;
                    mtc1(v1, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x003ce710
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(a0, f0);
                        v1 = lui(0x8000);
                        a0 = a0 | v1;
                        a0 = a0 & 0xFF;
                    } else {
                        // 0x003ce6f8
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(a0, f0);
                        a0 = a0 & 0xFF;
                    }
                    // 0x003ce728
                    charge(ctx, 19);
                    sb(a0, s0, psm::kRgbaB);
                    lbu(a1, v0, psfade::kFromA);
                    lbu(v1, v0, psfade::kToA);
                    a0 = subu(v1, a1);
                    lh(v1, v0, psfade::kTime);
                    mult(v1, v1, a0);
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    lh(v0, v0, psfade::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f1, f1, f0);
                    if (i64(a1) < 0) {
                        // 0x003ce788
                        charge(ctx, 7);
                        v1 = srl(a1, 1);
                        v0 = a1 & 0x1;
                        v1 = v1 | v0;
                        mtc1(v1, f0);
                        cvt_s_w(f0, f0);
                        add_s(f0, f0, f0);
                    } else {
                        // 0x003ce774
                        charge(ctx, 5);
                        mtc1(a1, f0);
                        cvt_s_w(f0, f0);
                    }
                    // 0x003ce7a4
                    charge(ctx, 7);
                    add_s(f1, f0, f1);
                    v0 = 0x4F000000;
                    mtc1(v0, f0);
                    c_le_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x003ce7d8
                        charge(ctx, 6);
                        sub_s(f0, f1, f0);
                        cvt_w_s(f0, f0);
                        mfc1(v1, f0);
                        v0 = lui(0x8000);
                        v1 = v1 | v0;
                        v1 = v1 & 0xFF;
                    } else {
                        // 0x003ce7c0
                        charge(ctx, 6);
                        cvt_w_s(f0, f1);
                        mfc1(v1, f0);
                        v1 = v1 & 0xFF;
                    }
                    // 0x003ce7f0
                    charge(ctx, 1);
                    sb(v1, s0, psm::kRgbaA);
                }
                // 0x003ce7f4
                charge(ctx, 6);
                a0 = addiu(s0, 176);
                // the two vec4 tweens (+176.. -> +132, +212.. -> +148): from + (to - from) x time / frames
                lh(v1, s0, psm::kTweenATime);
                lh(v0, s0, psm::kTweenAFrames);
                at = slt(v1, v0);
                if (at != 0) {
                    // 0x003ce80c
                    charge(ctx, 63);
                    v0 = addiu(v1, 1);
                    sh(v0, a0, tween4::kTime);
                    lwc1(f2, a0, tween4::kFrom);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kTo);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColA);
                    lwc1(f2, a0, tween4::kFromY);
                    lh(v0, a0, tween4::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kToY);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColAY);
                    lwc1(f2, a0, tween4::kFromZ);
                    lh(v0, a0, tween4::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kToZ);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColAZ);
                    lwc1(f2, a0, tween4::kFromW);
                    lh(v0, a0, tween4::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kToW);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColAW);
                }
                // 0x003ce908
                charge(ctx, 6);
                a0 = addiu(s0, 212);
                lh(v1, s0, psm::kTweenBTime);
                lh(v0, s0, psm::kTweenBFrames);
                at = slt(v1, v0);
                if (at != 0) {
                    // 0x003ce920
                    charge(ctx, 63);
                    v0 = addiu(v1, 1);
                    sh(v0, a0, tween4::kTime);
                    lwc1(f2, a0, tween4::kFrom);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kTo);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColB);
                    lwc1(f2, a0, tween4::kFromY);
                    lh(v0, a0, tween4::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kToY);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColBY);
                    lwc1(f2, a0, tween4::kFromZ);
                    lh(v0, a0, tween4::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kToZ);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColBZ);
                    lwc1(f2, a0, tween4::kFromW);
                    lh(v0, a0, tween4::kTime);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, a0, tween4::kToW);
                    sub_s(f0, f0, f2);
                    mul_s(f1, f1, f0);
                    lh(v0, a0, tween4::kFrames);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, s0, psm::kColBW);
                }
                // 0x003cea1c
                charge(ctx, 3);
                a0 = s0;
                jal(ctx, 0x3CEA20u, gen::fn_sub_3CEA50_003cea50);
            }
        }
    } else {
        // 0x003ce2fc
        charge(ctx, 3);
        v0 = 3;
        if (a0 != v0) {
            // 0x003ce308
            charge(ctx, 3);
            v1 = 2;
            if (a0 != v1) {
                // 0x003ce314
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003ce328
                    charge(ctx, 1);
                    sw(v1, s0, psm::kState);
                    goto L_003ce32c;
                }
                // 0x003ce320
                charge(ctx, 2);
                // 0x003cea28 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                v0 = 0;
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x40);
                return;
            }
        L_003ce32c:
            charge(ctx, 3);
            lw(a0, s0, psm::kModel);
            if (a0 != 0) {
                // 0x003ce338
                charge(ctx, 2);
                jal(ctx, 0x3CE338u, gen::fn_sub_3174E0_003174e0);
            }
            // 0x003ce340
            charge(ctx, 3);
            lh(v0, s0, psm::kPersona);
            if (v0 != 0) {
                // 0x003ce368
                charge(ctx, 8);
                a1 = v0 & 0xFFFF;
                a0 = 11;
                a2 = 0;
                jal(ctx, 0x3CE374u, gen::fn_sub_316E00_00316e00);
                sw(v0, s0, psm::kModel);
                v0 = 3;
                sw(v0, s0, psm::kState);
                goto L_003ce388;
            }
            // 0x003ce34c
            charge(ctx, 7);
            v0 = 4;
            sw(v0, s0, psm::kState);
            lw(v0, s0, psm::kFlags);
            v0 = v0 | 0x1;
            sw(v0, s0, psm::kFlags);
            // 0x003cea28 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            v0 = 0;
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ce388:
        charge(ctx, 5);
        lw(a0, s0, psm::kModel);
        jal(ctx, 0x3CE38Cu, gen::fn_sub_316F70_00316f70);
        if (v0 != 0) {
            // 0x003ce39c
            charge(ctx, 12);
            lw(a0, s0, psm::kModel);
            a1 = 8;
            jal(ctx, 0x3CE3A4u, gen::fn_sub_319230_00319230);
            v0 = 4;
            sw(v0, s0, psm::kState);
            lw(v0, s0, psm::kFlags);
            v0 = v0 | 0x1;
            sw(v0, s0, psm::kFlags);
            lh(v0, s0, psm::kAltId);
            if (v0 == 0) {
                // 0x003ce3e4
                charge(ctx, 14);
                lw(v1, s0, psm::kModel);
                lhu(v0, v1, mdlx::kFlags);
                v0 = v0 & 0xFEFF;
                sh(v0, v1, mdlx::kFlags);
                lw(a0, s0, psm::kModel);
                jal(ctx, 0x3CE3F8u, gen::fn_sub_319050_00319050);
                lh(a0, s0, psm::kPersona);
                jal(ctx, 0x3CE404u, gen::fn_sub_17C0E0_0017c0e0);
                v1 = v0 & 0xFFFF;
                v0 = 8;
                if (v1 != v0) {
                    // 0x003ce41c
                    charge(ctx, 3);
                    v0 = 4;
                    if (v1 == v0) {
                        // 0x003ce454
                        charge(ctx, 3);
                        lw(a0, s0, psm::kModel);
                        jal(ctx, 0x3CE458u, gen::fn_sub_319070_00319070);
                    } else {
                        // 0x003ce428
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x003ce43c
                            charge(ctx, 6);
                            lw(v1, s0, psm::kModel);
                            lhu(v0, v1, mdlx::kFlags);
                            v0 = v0 | 0x200;
                            sh(v0, v1, mdlx::kFlags);
                        } else {
                            // 0x003ce434
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x003ce460
                charge(ctx, 12);
                lhu(a1, s0, psm::kPersona);
                a0 = 0;
                a2 = addiu(s0, 132);
                jal(ctx, 0x3CE46Cu, gen::fn_sub_16BC80_0016bc80);
                lhu(a1, s0, psm::kPersona);
                a0 = 0;
                a2 = addiu(s0, 148);
                jal(ctx, 0x3CE480u, gen::fn_sub_16BDB0_0016bdb0);
            } else {
                // 0x003ce3cc
                charge(ctx, 6);
                a1 = v0 & 0xFFFF;
                a0 = s1;
                jal(ctx, 0x3CE3D4u, gen::fn_sub_3CDBA0_003cdba0);
            }
        }
    }
    // 0x003cea28 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003CEA50 sub_3CEA50 -- 1572 bytes; frame 0x1B0: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [psModelDraw] (work) Draws the persona model into the main camera: saves the camera's view window / matrix and the
// two light colours, sets the persona's light colours (+132 / +148, sub_4944B0), turns the light frame by the
// persona's quaternion (sub_16BEE0, the matrix built from it, sub_4C2F30), places the model (sub_16BF80's offset +28..,
// scale +36, the matrix +64.., colour +128 with its alpha scaled; sub_318A70 / sub_318A90 / sub_318AD0), sets the
// view window to the persona's size / (640, 448), renders it between RwCameraBeginUpdate / RwCameraEndUpdate with the
// render states 6, 8, 14 and RpSky states 2 / 3 (sub_317A20; asserts fclMisc.c 2861 when the camera will not begin),
// then restores the camera, lights and view window; 0.
void sub_3CEA50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003cea50
    enter(ctx, 45);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3CEA6Cu, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x3CEA78u, gen::fn_sub_1A4600_001a4600);
    mov_s(f20, f0);
    jal(ctx, 0x3CEA84u, gen::fn_sub_198560_00198560);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x150);
    swc1(f2, sp, 0x154);
    swc1(f1, sp, 0x158);
    swc1(f0, sp, 0x15C);
    jal(ctx, 0x3CEAACu, gen::fn_sub_198570_00198570);
    lwc1(f3, v0, 24);
    lwc1(f2, v0, 28);
    lwc1(f1, v0, 32);
    lwc1(f0, v0, 36);
    swc1(f3, sp, 0x140);
    swc1(f2, sp, 0x144);
    swc1(f1, sp, 0x148);
    swc1(f0, sp, 0x14C);
    jal(ctx, 0x3CEAD4u, gen::fn_sub_198590_00198590);
    lwc1(f1, v0, 120);
    lwc1(f0, v0, 124);
    swc1(f1, sp, 0x1A0);
    swc1(f0, sp, 0x1A4);
    jal(ctx, 0x3CEAECu, gen::fn_sub_198570_00198570);
    lw(v0, v0, 4);
    a2 = addiu(v0, 16);
    a1 = addiu(sp, 0x100);
    a0 = 8;
    for (;;) {
        // 0x003ceb04
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ceb28
    charge(ctx, 13);
    v0 = 0x6A0000;
    lq(v0, v0, 16960);  // 0x6A4240
    sq(v0, sp, 0xB0);
    v0 = 0x6A0000;
    ld(v1, v0, 16976);  // 0x6A4250
    v0 = 0x6A0000;
    lwc1(f0, v0, 16984);  // 0x6A4258
    sd(v1, sp, 0x188);
    swc1(f0, sp, 0x190);
    v1 = addiu(sp, 0x178);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x003ceb5c
            charge(ctx, 7);
            sb(zero, v1, 0);
            v1 = addiu(v1, 1);
            v0 = addiu(v0, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003ceb78
    charge(ctx, 180);
    v0 = 0x6A0000;
    ld(v1, v0, 16992);  // 0x6A4260
    v0 = 0x6A0000;
    lwc1(f0, v0, 17000);  // 0x6A4268
    sd(v1, sp, 0x168);
    swc1(f0, sp, 0x170);
    jal(ctx, 0x3CEB90u, gen::fn_sub_198590_00198590);
    lw(v0, v0, 4);
    s0 = addiu(v0, 16);
    jal(ctx, 0x3CEBA0u, gen::fn_sub_198590_00198590);
    v1 = 0x42200000;
    mtc1(v1, f12);
    a0 = v0;
    jal(ctx, 0x3CEBB4u, gen::fn_sub_1A4580_001a4580);
    jal(ctx, 0x3CEBBCu, gen::fn_sub_198560_00198560);
    a0 = v0;
    a1 = addiu(s1, 132);
    jal(ctx, 0x3CEBCCu, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x3CEBD4u, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(s1, 148);
    jal(ctx, 0x3CEBE4u, gen::fn_sub_4944B0_004944b0);
    lhu(a1, s1, psm::kPersona);
    a0 = 0;
    a2 = addiu(sp, 0xB0);
    jal(ctx, 0x3CEBF8u, gen::fn_sub_16BEE0_0016bee0);
    lwc1(f4, sp, 0xB4);
    lwc1(f12, sp, 0xB0);
    lwc1(f11, sp, 0xB8);
    lwc1(f3, sp, 0xBC);
    mula_s(f4, f4);
    madda_s(f12, f12);
    madda_s(f11, f11);
    madd_s(f1, f3, f3);
    v0 = 0x40000000;
    mtc1(v0, f0);
    div_s(f0, f0, f1);
    mul_s(f2, f12, f0);
    mul_s(f1, f4, f0);
    mul_s(f0, f11, f0);
    mul_s(f10, f2, f3);
    mul_s(f9, f1, f3);
    mul_s(f8, f0, f3);
    mul_s(f7, f12, f2);
    mul_s(f6, f4, f1);
    mul_s(f5, f11, f0);
    mul_s(f4, f4, f0);
    mul_s(f3, f11, f2);
    mul_s(f2, f12, f1);
    add_s(f0, f6, f5);
    v0 = 0x3F800000;
    mtc1(v0, f1);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xC0);
    add_s(f0, f2, f8);
    swc1(f0, sp, 0xC4);
    sub_s(f0, f3, f9);
    swc1(f0, sp, 0xC8);
    sub_s(f0, f2, f8);
    swc1(f0, sp, 0xD0);
    add_s(f0, f5, f7);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xD4);
    add_s(f0, f4, f10);
    swc1(f0, sp, 0xD8);
    add_s(f0, f3, f9);
    swc1(f0, sp, 0xE0);
    sub_s(f0, f4, f10);
    swc1(f0, sp, 0xE4);
    add_s(f0, f7, f6);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0xE8);
    sw(zero, sp, 0xF0);
    sw(zero, sp, 0xF4);
    sw(zero, sp, 0xF8);
    v0 = 3;
    sw(v0, sp, 0xCC);
    a0 = addiu(sp, 0xC0);
    a1 = a0;
    a2 = s0;
    jal(ctx, 0x3CECE0u, gen::fn_sub_4C2F30_004c2f30);
    jal(ctx, 0x3CECE8u, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(sp, 0xC0);
    a2 = 0;
    jal(ctx, 0x3CECFCu, gen::fn_sub_4CB7F0_004cb7f0);
    s2 = 3;
    jal(ctx, 0x3CED08u, gen::fn_sub_198570_00198570);
    sb(s2, v0, 2);
    jal(ctx, 0x3CED14u, gen::fn_sub_198570_00198570);
    lw(a0, gp, -19492);  // 0x7CE0CC
    jal(ctx, 0x3CED20u, gen::fn_sub_198540_00198540);
    s2 = v0;
    jal(ctx, 0x3CED2Cu, gen::fn_sub_198580_00198580);
    a0 = s2;
    a1 = v0;
    jal(ctx, 0x3CED3Cu, gen::fn_sub_49C480_0049c480);
    lhu(a1, s1, psm::kPersona);
    lhu(a0, s1, psm::kView);
    a2 = addiu(sp, 0x50);
    jal(ctx, 0x3CED50u, gen::fn_sub_16BF80_0016bf80);
    lh(v0, sp, 0x6C);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x44200000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    swc1(f0, sp, 0x198);
    lh(v0, sp, 0x6E);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x43E00000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    swc1(f0, sp, 0x19C);
    lh(v1, s1, psm::kOffX);
    lh(v0, sp, 0x50);
    v0 = addu(v1, v0);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x178);
    lh(v1, s1, psm::kOffY);
    lh(v0, sp, 0x52);
    v0 = addu(v1, v0);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x17C);
    lh(v1, s1, psm::kOffZ);
    lh(v0, sp, 0x54);
    v0 = addu(v1, v0);
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x180);
    lwc1(f1, s1, psm::kScale);
    lwc1(f0, sp, 0x58);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x170);
    swc1(f0, sp, 0x16C);
    swc1(f0, sp, 0x168);
    a0 = addiu(sp, 0x1AC);
    a1 = addiu(s1, 128);
    a2 = 4;
    jal(ctx, 0x3CEE18u, gen::fn_memcpy_00521250);
    lbu(v1, sp, 0x1AF);
    lh(v0, sp, 0x60);
    mult(v1, v1, v0);
    v0 = 255;
    div(v1, v0);
    mflo(v0);
    sb(v0, sp, 0x1AF);
    a2 = addiu(s1, 64);
    a1 = addiu(sp, 0x70);
    a0 = 8;
    for (;;) {
        // 0x003cee48
        charge(ctx, 9);
        lw(v1, a2, 0);
        lw(v0, a2, 4);
        a2 = addiu(a2, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003cee6c
    charge(ctx, 43);
    a0 = addiu(sp, 0x70);
    a1 = addiu(sp, 0x188);
    lwc1(f12, sp, 0x5C);
    a2 = 1;
    jal(ctx, 0x3CEE7Cu, gen::fn_sub_4C31B0_004c31b0);
    a0 = addiu(sp, 0x70);
    a1 = addiu(sp, 0x178);
    a2 = 2;
    jal(ctx, 0x3CEE90u, gen::fn_sub_4C35D0_004c35d0);
    a0 = addiu(sp, 0x70);
    a1 = a0;
    a2 = s0;
    jal(ctx, 0x3CEEA4u, gen::fn_sub_4C2F30_004c2f30);
    lw(a0, s1, psm::kModel);
    a1 = addiu(sp, 0x70);
    a2 = 0;
    jal(ctx, 0x3CEEB8u, gen::fn_sub_318A70_00318a70);
    lw(a0, s1, psm::kModel);
    a1 = addiu(sp, 0x168);
    a2 = 1;
    jal(ctx, 0x3CEECCu, gen::fn_sub_318A90_00318a90);
    lw(a0, s1, psm::kModel);
    a1 = addiu(sp, 0x1AC);
    jal(ctx, 0x3CEEDCu, gen::fn_sub_318AD0_00318ad0);
    jal(ctx, 0x3CEEE4u, gen::fn_sub_198590_00198590);
    a0 = v0;
    a1 = addiu(sp, 0x198);
    jal(ctx, 0x3CEEF4u, gen::fn_sub_4C9D20_004c9d20);
    jal(ctx, 0x3CEEFCu, gen::fn_sub_198590_00198590);
    a0 = v0;
    // render the model between RwCameraBeginUpdate / RwCameraEndUpdate, then restore the camera, the lights and the view window
    jal(ctx, 0x3CEF08u, gen::fn_RwCameraBeginUpdate_004c9d10);
    if (v0 == 0) {
        // 0x003cefa8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 15896);  // "fclMisc.c"
        a1 = 2861;
        jal(ctx, 0x3CEFB4u, gen::fn_sub_19D3F0_0019d3f0);
    } else {
        // 0x003cef18
        charge(ctx, 36);
        s0 = 0x960000;
        s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
        a0 = 6;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x3CEF2Cu, v0.u());
        a0 = 8;
        a1 = 1;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x3CEF40u, v0.u());
        a0 = 14;
        a1 = 0;
        lw(v0, s0, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x3CEF54u, v0.u());
        a0 = 2;
        a1 = 68;
        jal(ctx, 0x3CEF64u, gen::fn_RpSkyRenderStateSet_004d7f60);
        a0 = 3;
        v0 = 0x70000;
        a1 = v0 | 0x17FB;
        jal(ctx, 0x3CEF78u, gen::fn_RpSkyRenderStateSet_004d7f60);
        lw(a0, s1, psm::kModel);
        jal(ctx, 0x3CEF84u, gen::fn_sub_317A20_00317a20);
        jal(ctx, 0x3CEF8Cu, gen::fn_sub_198590_00198590);
        a0 = v0;
        jal(ctx, 0x3CEF98u, gen::fn_RwCameraEndUpdate_004c9d00);
    }
    // 0x003cefbc
    charge(ctx, 46);
    jal(ctx, 0x3CEFBCu, gen::fn_sub_198590_00198590);
    a0 = v0;
    mov_s(f12, f20);
    jal(ctx, 0x3CEFCCu, gen::fn_sub_1A4580_001a4580);
    jal(ctx, 0x3CEFD4u, gen::fn_sub_198560_00198560);
    a0 = v0;
    a1 = addiu(sp, 0x150);
    jal(ctx, 0x3CEFE4u, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x3CEFECu, gen::fn_sub_198570_00198570);
    a0 = v0;
    a1 = addiu(sp, 0x140);
    jal(ctx, 0x3CEFFCu, gen::fn_sub_4944B0_004944b0);
    jal(ctx, 0x3CF004u, gen::fn_sub_198570_00198570);
    lw(a0, v0, 4);
    a1 = addiu(sp, 0x100);
    a2 = 0;
    jal(ctx, 0x3CF018u, gen::fn_sub_4CB7F0_004cb7f0);
    s0 = 3;
    jal(ctx, 0x3CF024u, gen::fn_sub_198570_00198570);
    sb(s0, v0, 2);
    jal(ctx, 0x3CF030u, gen::fn_sub_198570_00198570);
    jal(ctx, 0x3CF038u, gen::fn_sub_198590_00198590);
    a0 = v0;
    a1 = addiu(sp, 0x1A0);
    jal(ctx, 0x3CF048u, gen::fn_sub_4C9D20_004c9d20);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x1B0);
}

// 0x003CF080 fclMisc_CreatePsModelDummyTask -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of the psModel work: a loaded model (+24) is released at once (sub_3174E0); one still loading is handed to a
// "psModel_dummy" task (priority 5244, fclMisc_UpdatePsModelDummyTask) that releases it when it arrives; the work is freed (RwFree).
void fclMisc_CreatePsModelDummyTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf080
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3CF08Cu, gen::fn_kwlnTaskGetWorkData_00195540);
    s0 = v0;
    lw(a0, v0, psm::kModel);
    if (a0 != 0) {
        // 0x003cf0a4
        charge(ctx, 4);
        jal(ctx, 0x3CF0A4u, gen::fn_sub_316F70_00316f70);
        if (v0 == 0) {
            // 0x003cf0c8
            charge(ctx, 10);
            a0 = 0;
            a1 = 0x6A0000;
            a1 = addiu(a1, 16904);  // "psModel_dummy"
            a2 = 5244;
            a3 = 0x3D0000;
            a3 = addiu(a3, -9728);  // &fclMisc_UpdatePsModelDummyTask
            t0 = 0;
            lw(t1, s0, psm::kModel);
            jal(ctx, 0x3CF0E8u, gen::fn_kwlnTaskCreate_00194b20);
        } else {
            // 0x003cf0b4
            charge(ctx, 5);
            lw(a0, s0, psm::kModel);
            jal(ctx, 0x3CF0B8u, gen::fn_sub_3174E0_003174e0);
        }
    }
    // 0x003cf0f0
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, g::kLoRwFree);  // 0x96017C
    jalr(ctx, 0x3CF0FCu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003CF6C0 sub_3CF6C0 -- 552 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBankTakePanel] (request) Takes a bust-up panel for a request node (+20 -> {u16 flags, .., u32 bust-up}): the first
// free panel, else the first used one neither loading nor shown; prints "BankNo:%d"; none -> -1. The panel gets the
// bust-up, the flags and its record number; the bust-up is requested (H_ChrDsp_Request sub_106860(slot, character,
// pose, expression)), its fade set (sub_106EC0(slot, 1)) and flip cleared (sub_106F30(slot, 0)), the panel marked used +
// loading and the request unlinked (sub_3C49E0); returns the panel.
void sub_3CF6C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cf6c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, gp, g::kGpBankTask);  // 0x7CE680
    lw(v1, v0, bank::kWork);
    a0 = addiu(v1, 4);
    a1 = 0;
    for (;;) {
        // 0x003cf718
        charge(ctx, 3);
        v0 = slti(a1, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cf6f0
        charge(ctx, 4);
        lh(v0, a0, bank::kPFlags);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            goto L_003cf700_2;
        }
        // 0x003cf710
        charge(ctx, 2);
        a0 = addiu(a0, 20);
        a1 = addiu(a1, 1);
    }
    // 0x003cf724
    charge(ctx, 1);
    v0 = si(-1);
L_003cf728:
    charge(ctx, 5);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    v0 = si(-1);
    if (s1 == v0) {
        // 0x003cf73c
        charge(ctx, 4);
        a0 = addiu(v1, 4);
        a1 = 0;
        for (;;) {
            // 0x003cf78c
            charge(ctx, 3);
            v0 = slti(a1, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003cf74c
            charge(ctx, 4);
            lh(v1, a0, bank::kPFlags);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x003cf75c
                charge(ctx, 3);
                v0 = v1 & 0x2;
                if (v0 != 0) {
                    goto L_003cf784;
                }
                // 0x003cf768
                charge(ctx, 3);
                v0 = v1 & 0x8;
                if (v0 != 0) {
                    goto L_003cf784;
                }
                goto L_003cf774_11;
            }
        L_003cf784:
            charge(ctx, 2);
            a0 = addiu(a0, 20);
            a1 = addiu(a1, 1);
        }
        // 0x003cf798
        charge(ctx, 1);
        v0 = si(-1);
    L_003cf79c:
        charge(ctx, 2);
        s1 = dsll32(v0, 16);
        s1 = dsra32(s1, 16);
    }
    // 0x003cf7a4
    charge(ctx, 21);
    a0 = addiu(gp, -21960);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 17008);  // "fclBankManager.c"
    a2 = 359;
    jal(ctx, 0x3CF7B4u, gen::fn_printf_005225a8);
    s0 = dsll32(s1, 16);
    s0 = dsra32(s0, 16);
    a0 = 0x6A0000;
    a0 = addiu(a0, 17112);  // "BankNo:%d\n"
    a1 = s0;
    jal(ctx, 0x3CF7D0u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 17112);  // "BankNo:%d\n"
    a1 = s0;
    jal(ctx, 0x3CF7E4u, gen::fn_sub_1052B0_001052b0);
    v0 = si(-1);
    if (s0 != v0) {
        // 0x003cf800
        charge(ctx, 51);
        lw(v0, gp, g::kGpBankTask);  // 0x7CE680
        // take the panel: the bank, the request's flags, the slot; load the bank and mark the panel used + opening
        lw(v1, v0, bank::kWork);
        lw(a0, s2, nmnode::kPayload);
        v0 = sll(s0, 2);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v1 = addu(v1, v0);
        s0 = addiu(v1, 4);
        lw(v0, a0, bank::kPanels);
        sw(v0, v1, bankw::kBank);
        lh(v0, a0, bank::kPFlags);
        sh(v0, v1, bankw::kFlags);
        sh(s1, v1, bankw::kSlot);
        lw(v1, v1, bankw::kBank);
        v0 = lui(0xFFFF);
        v0 = v1 & v0;
        v0 = srl(v0, 16);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        v0 = v1 & 0xFF00;
        v0 = srl(v0, 8);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        v0 = v1 & 0xFF;
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3CF870u, gen::fn_sub_106860_00106860);
        lh(a0, s0, bank::kPSlot);
        a1 = 1;
        jal(ctx, 0x3CF880u, gen::fn_sub_106EC0_00106ec0);
        lh(a0, s0, bank::kPSlot);
        a1 = 0;
        jal(ctx, 0x3CF890u, gen::fn_sub_106F30_00106f30);
        lh(v0, s0, bank::kPFlags);
        v0 = v0 | 0x1;
        sh(v0, s0, bank::kPFlags);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        v0 = v0 | 0x2;
        sh(v0, s0, bank::kPFlags);
        lw(a0, gp, g::kGpBankTask);  // 0x7CE680
        a1 = addiu(a0, 4);
        a2 = s2;
        jal(ctx, 0x3CF8C0u, gen::fn_sub_3C49E0_003c49e0);
        v0 = s1;
    } else {
        // 0x003cf7f8
        charge(ctx, 2);
    }
    // 0x003cf8cc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003cf700_2:
    charge(ctx, 4);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    goto L_003cf728;
L_003cf774_11:
    charge(ctx, 4);
    v0 = dsll32(a1, 16);
    v0 = dsra32(v0, 16);
    goto L_003cf79c;
}

// 0x003CFE50 fclBank_UpdateTask -- 1164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Update of the "fclBank" task, the facility bust-ups (asserts fclBankManager.c 624 without one): serves the request
// list (sub_3CF6C0; "No Bank!!!" when no panel is free), then per used panel: loading -> open once the bust-up is in
// (H_ChrDsp_IsReady sub_106FF0); open with a request: 0x200 "OPEN" (sub_3CFAC0; the same character on another shown
// panel of the same side -> 0x20), 0x400 "CLOSE" (shown: slide state 4), 0x800 "END" (shown: becomes a close; else
// H_ChrDsp_Release sub_106730), 0x1000 "KILL" (H_ChrDsp_Release); then the panel slides (sub_3CFB50); 0.
void fclBank_UpdateTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003cfe50
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, g::kGpBankTask);  // 0x7CE680
    if (v0 == 0) {
        // 0x003cfe6c
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 17008);  // "fclBankManager.c"
        a1 = 624;
        jal(ctx, 0x3CFE78u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003cfe80
    charge(ctx, 5);
    lw(v0, gp, g::kGpBankTask);  // 0x7CE680
    // serve the request list (sub_3CF6C0) until no panel is free
    lw(s0, v0, bank::kWork);
    lw(a0, v0, nml::kFirst);
    for (;;) {
        // 0x003cfef8
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cfe94
        charge(ctx, 8);
        lw(s1, a0, nmnode::kNext);
        jal(ctx, 0x3CFE98u, gen::fn_sub_3CF6C0_003cf6c0);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = si(-1);
        if (v1 == v0) {
            goto L_003cfeb4_4;
        }
        // 0x003cfef4
        charge(ctx, 1);
        a0 = s1;
    }
L_003cff00:
    charge(ctx, 4);
    s1 = addiu(s0, 4);
    s0 = 0;
    for (;;) {
        // 0x003d02ac
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003cff10
        charge(ctx, 4);
        // per used panel: opening -> open once loaded; then the OPEN / CLOSE / END / KILL requests
        lh(v1, s1, bank::kPFlags);
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x003cff20
            charge(ctx, 3);
            v0 = v1 & 0x2;
            if (v0 != 0) {
                // 0x003cff2c
                charge(ctx, 6);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3CFF34u, gen::fn_sub_106FF0_00106ff0);
                if (v0 != 0) {
                    // 0x003cff44
                    charge(ctx, 13);
                    lh(v1, s1, bank::kPFlags);
                    v0 = si(-3);
                    v0 = v1 & v0;
                    sh(v0, s1, bank::kPFlags);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    v0 = v0 | 0x4;
                    sh(v0, s1, bank::kPFlags);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = v1 & 0x400;
                    if (v0 != 0) {
                        // 0x003cff78
                        charge(ctx, 8);
                        v0 = si(-513);
                        v0 = v1 & v0;
                        sh(v0, s1, bank::kPFlags);
                        v1 = dsll32(v0, 16);
                        v1 = dsra32(v1, 16);
                        v0 = si(-1025);
                        v0 = v1 & v0;
                        sh(v0, s1, bank::kPFlags);
                    }
                }
            }
            // 0x003cff98
            charge(ctx, 4);
            lh(v1, s1, bank::kPFlags);
            v0 = v1 & 0x2;
            if (v0 == 0) {
                // 0x003cffa8
                charge(ctx, 3);
                v0 = v1 & 0x4;
                if (v0 != 0) {
                    // 0x003cffb4
                    charge(ctx, 3);
                    v0 = v1 & 0x200;
                    if (v0 == 0) {
                        // 0x003d0104
                        charge(ctx, 3);
                        v0 = v1 & 0x400;
                        if (v0 == 0) {
                            // 0x003d0180
                            charge(ctx, 3);
                            v0 = v1 & 0x800;
                            if (v0 == 0) {
                                // 0x003d0224
                                charge(ctx, 3);
                                v0 = v1 & 0x1000;
                                if (v0 != 0) {
                                    // 0x003d0230
                                    charge(ctx, 29);
                                    a0 = addiu(gp, -21960);  // "[%s:%d]"
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, 17008);  // "fclBankManager.c"
                                    a2 = 699;
                                    jal(ctx, 0x3D0240u, gen::fn_printf_005225a8);
                                    a0 = addiu(gp, -21928);  // "KILL\n"
                                    jal(ctx, 0x3D024Cu, gen::fn_printf_005225a8);
                                    a0 = addiu(gp, -21928);  // "KILL\n"
                                    jal(ctx, 0x3D0258u, gen::fn_sub_1052B0_001052b0);
                                    lh(v1, s1, bank::kPFlags);
                                    v0 = si(-4097);
                                    v0 = v1 & v0;
                                    sh(v0, s1, bank::kPFlags);
                                    v1 = dsll32(v0, 16);
                                    v1 = dsra32(v1, 16);
                                    v0 = si(-5);
                                    v0 = v1 & v0;
                                    sh(v0, s1, bank::kPFlags);
                                    v1 = dsll32(v0, 16);
                                    v1 = dsra32(v1, 16);
                                    v0 = si(-2);
                                    v0 = v1 & v0;
                                    sh(v0, s1, bank::kPFlags);
                                    lh(a0, s1, bank::kPSlot);
                                    jal(ctx, 0x3D029Cu, gen::fn_sub_106730_00106730);
                                }
                            } else {
                                // 0x003d018c
                                charge(ctx, 3);
                                v0 = v1 & 0x8;
                                if (v0 == 0) {
                                    // 0x003d01a8
                                    charge(ctx, 31);
                                    a0 = addiu(gp, -21960);  // "[%s:%d]"
                                    a1 = 0x6A0000;
                                    a1 = addiu(a1, 17008);  // "fclBankManager.c"
                                    a2 = 690;
                                    jal(ctx, 0x3D01B8u, gen::fn_printf_005225a8);
                                    a0 = addiu(gp, -21936);  // "END\n"
                                    jal(ctx, 0x3D01C4u, gen::fn_printf_005225a8);
                                    a0 = addiu(gp, -21936);  // "END\n"
                                    jal(ctx, 0x3D01D0u, gen::fn_sub_1052B0_001052b0);
                                    lh(v1, s1, bank::kPFlags);
                                    v0 = si(-2049);
                                    v0 = v1 & v0;
                                    sh(v0, s1, bank::kPFlags);
                                    v1 = dsll32(v0, 16);
                                    v1 = dsra32(v1, 16);
                                    v0 = si(-5);
                                    v0 = v1 & v0;
                                    sh(v0, s1, bank::kPFlags);
                                    v1 = dsll32(v0, 16);
                                    v1 = dsra32(v1, 16);
                                    v0 = si(-2);
                                    v0 = v1 & v0;
                                    sh(v0, s1, bank::kPFlags);
                                    lh(a0, s1, bank::kPSlot);
                                    jal(ctx, 0x3D0214u, gen::fn_sub_106730_00106730);
                                } else {
                                    // 0x003d0198
                                    charge(ctx, 4);
                                    v0 = v1 | 0x400;
                                    sh(v0, s1, bank::kPFlags);
                                }
                            }
                        } else {
                            // 0x003d0110
                            charge(ctx, 21);
                            a0 = addiu(gp, -21960);  // "[%s:%d]"
                            a1 = 0x6A0000;
                            a1 = addiu(a1, 17008);  // "fclBankManager.c"
                            a2 = 675;
                            jal(ctx, 0x3D0120u, gen::fn_printf_005225a8);
                            a0 = addiu(gp, -21944);  // "CLOSE\n"
                            jal(ctx, 0x3D012Cu, gen::fn_printf_005225a8);
                            a0 = addiu(gp, -21944);  // "CLOSE\n"
                            jal(ctx, 0x3D0138u, gen::fn_sub_1052B0_001052b0);
                            lh(v1, s1, bank::kPFlags);
                            v0 = si(-1025);
                            v0 = v1 & v0;
                            sh(v0, s1, bank::kPFlags);
                            v1 = dsll32(v0, 16);
                            v1 = dsra32(v1, 16);
                            v0 = v1 & 0x8;
                            if (v0 != 0) {
                                // 0x003d0164
                                charge(ctx, 7);
                                v0 = si(-5);
                                v0 = v1 & v0;
                                sh(v0, s1, bank::kPFlags);
                                v0 = 4;
                                sh(v0, s1, bank::kPState);
                            }
                        }
                    } else {
                        // 0x003cffc0
                        charge(ctx, 3);
                        v0 = v1 & 0x8;
                        if (v0 == 0) {
                            // 0x003cffe0
                            charge(ctx, 5);
                            a0 = s1;
                            jal(ctx, 0x3CFFE4u, gen::fn_sub_3CFAC0_003cfac0);
                            if (v0 != 0) {
                                // 0x003cfff4
                                charge(ctx, 30);
                                a0 = addiu(gp, -21960);  // "[%s:%d]"
                                a1 = 0x6A0000;
                                a1 = addiu(a1, 17008);  // "fclBankManager.c"
                                a2 = 664;
                                jal(ctx, 0x3D0004u, gen::fn_printf_005225a8);
                                a0 = addiu(gp, -21952);  // "OPEN\n"
                                jal(ctx, 0x3D0010u, gen::fn_printf_005225a8);
                                a0 = addiu(gp, -21952);  // "OPEN\n"
                                jal(ctx, 0x3D001Cu, gen::fn_sub_1052B0_001052b0);
                                lh(v1, s1, bank::kPFlags);
                                v0 = si(-513);
                                v0 = v1 & v0;
                                sh(v0, s1, bank::kPFlags);
                                v1 = dsll32(v0, 16);
                                v1 = dsra32(v1, 16);
                                v0 = si(-5);
                                v0 = v1 & v0;
                                sh(v0, s1, bank::kPFlags);
                                v0 = 1;
                                sh(v0, s1, bank::kPState);
                                lw(v0, gp, g::kGpBankTask);  // 0x7CE680
                                lw(v0, v0, bank::kWork);
                                a2 = addiu(v0, 4);
                                a1 = 0;
                                a0 = lui(0xFFFF);
                                for (;;) {
                                    // 0x003d00d8
                                    charge(ctx, 3);
                                    v0 = slti(a1, 3);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x003d006c
                                    charge(ctx, 2);
                                    if (a2 != s1) {
                                        // 0x003d0074
                                        charge(ctx, 4);
                                        lh(v1, a2, bank::kPFlags);
                                        v0 = v1 & 0x1;
                                        if (v0 == 0) {
                                            goto L_003d00d0;
                                        }
                                        // 0x003d0084
                                        charge(ctx, 3);
                                        v0 = v1 & 0x8;
                                        if (v0 == 0) {
                                            goto L_003d00d0;
                                        }
                                        // 0x003d0090
                                        charge(ctx, 5);
                                        v1 = v1 & 0x100;
                                        lh(v0, s1, bank::kPFlags);
                                        v0 = v0 & 0x100;
                                        if (v1 != v0) {
                                            goto L_003d00d0;
                                        }
                                        // 0x003d00a4
                                        charge(ctx, 8);
                                        lw(v0, a2, bank::kPanels);
                                        v0 = v0 & a0;
                                        v1 = srl(v0, 16);
                                        lw(v0, s1, bank::kPanels);
                                        v0 = v0 & a0;
                                        v0 = srl(v0, 16);
                                        if (v1 != v0) {
                                            goto L_003d00d0;
                                        }
                                        goto L_003d00c4_25;
                                    }
                                L_003d00d0:
                                    charge(ctx, 2);
                                    a2 = addiu(a2, 20);
                                    a1 = addiu(a1, 1);
                                }
                                // 0x003d00e4
                                charge(ctx, 1);
                                v0 = 0;
                            L_003d00e8:
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x003d00f0
                                    charge(ctx, 5);
                                    lh(v0, s1, bank::kPFlags);
                                    v0 = v0 | 0x20;
                                    sh(v0, s1, bank::kPFlags);
                                }
                            }
                        } else {
                            // 0x003cffcc
                            charge(ctx, 5);
                            v0 = si(-513);
                            v0 = v1 & v0;
                            sh(v0, s1, bank::kPFlags);
                        }
                    }
                }
            }
        }
        // 0x003d02a4
        charge(ctx, 2);
        s1 = addiu(s1, 20);
        s0 = addiu(s0, 1);
    }
    // 0x003d02b8
    charge(ctx, 9);
    jal(ctx, 0x3D02B8u, gen::fn_sub_3CFB50_003cfb50);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003cfeb4_4:
    charge(ctx, 16);
    a0 = addiu(gp, -21960);  // "[%s:%d]"
    a1 = 0x6A0000;
    a1 = addiu(a1, 17008);  // "fclBankManager.c"
    a2 = 633;
    jal(ctx, 0x3CFEC4u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 17176);  // "No Bank!!!\n"
    jal(ctx, 0x3CFED4u, gen::fn_printf_005225a8);
    a0 = 0x6A0000;
    a0 = addiu(a0, 17176);  // "No Bank!!!\n"
    jal(ctx, 0x3CFEE4u, gen::fn_sub_1052B0_001052b0);
    goto L_003cff00;
L_003d00c4_25:
    charge(ctx, 3);
    v0 = 1;
    goto L_003d00e8;
}

}  // namespace p3fes::game
