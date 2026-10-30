// The message / menu / font band, fourth UI pass (slice ui4; game/include/p3fes/game/ui4.h has the role of every function and
// the records they work on): the message manager of itfMesManager.c (the COMM handlers next to scrCommand_MSG, the
// text and panel helpers, the "CalcMsgMng" / "DrawMsgMng" tasks, the selection cursor and the window pop-in), the itfPanel.c entry points
// and draw-type dispatch, the BMD text-tag handlers of sFrTagTable 0x6A2370 (frTagTable.c), the frFont.c /
// frFontRaster.c / fmGslCont.c leaves and the font system's start, and the spr* file list (sub_1120C0, sprAddFile,
// sprSpriteDrawAll).
// docs/ANALYSIS/20_menu_ui.md sections 4.3 and 5, 18_script_vm.md section 5.
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest registers,
// the original's frame, spills, $ra links, cycle charges and check points, so every register the original leaves at a
// check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). This readability
// pass names the record offsets and globals (ui4.h: ui4::spr / rw / mes / pnl / lay / fnt -- each constant equals the
// literal it replaces), states each function's role above it, and notes what the callees are; it changes no statement.
// `// 0x00xxxxxx` lines name the original basic block a C++ block comes from.
//
// Kept as the original has them: the K_Assert / K_Abort calls (sub_19D3F0 / sub_19D400, `jr $ra` in retail: a failed check
// continues), the debug printfs, the dead locals (sub_3A8590's corner array, sub_3A8260's row position), the empty hooks
// (nullsub_116..121, sub_3AC590) and the tag handlers that do nothing but return 0.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/ui4.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentWeekDay_0017db00(p3fes::EEContext&);
void fn_datCalcGetSkillElement_003082f0(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_fclMisc_CreateMsgAssistTask_003c88d0(p3fes::EEContext&);
void fn_fmGslAllocEntry_003b4520(p3fes::EEContext&);
void fn_frAddFontStyle_003afad0(p3fes::EEContext&);
void fn_frFontChainCountLines_003b1a90(p3fes::EEContext&);
void fn_frFontChainGetRowPos_003b1bc0(p3fes::EEContext&);
void fn_frFontChainGetRowWidth_003b1b00(p3fes::EEContext&);
void fn_frFontDraw_003b1360(p3fes::EEContext&);
void fn_frFontLayoutNewRow_003b2400(p3fes::EEContext&);
void fn_frFontLineFadeStep_003b0ec0(p3fes::EEContext&);
void fn_frFontLineSetAlpha_003b0bb0(p3fes::EEContext&);
void fn_frFontLineSetColourSet_003b0dd0(p3fes::EEContext&);
void fn_frFontLineSetStyle_003b0ce0(p3fes::EEContext&);
void fn_frFontNodeSetCode_003b0c20(p3fes::EEContext&);
void fn_frFontPrintClutData_003aff50(p3fes::EEContext&);
void fn_frFontRasterAgeSlots_003b3770(p3fes::EEContext&);
void fn_frFontRasterAllocSlot_003b3e60(p3fes::EEContext&);
void fn_frFontRasterFindOrAlloc_003b3d60(p3fes::EEContext&);
void fn_frFontRasterLookup_003b3e00(p3fes::EEContext&);
void fn_frFontRegisterGlyphRaster_003b03a0(p3fes::EEContext&);
void fn_frFontSystemStart_003b4ee0(p3fes::EEContext&);
void fn_frFreeFontStyles_003afe30(p3fes::EEContext&);
void fn_frInitFontTable_003af7a0(p3fes::EEContext&);
void fn_frLoadFontData_Ptr_003af770(p3fes::EEContext&);
void fn_frSetMessageFontStyle_003b19a0(p3fes::EEContext&);
void fn_itfMesManagerDrawMsg_003a7e90(p3fes::EEContext&);
void fn_itfMesManagerDrawSpriteEx_003a8710(p3fes::EEContext&);
void fn_itfMesManagerDrawSprite_003a8170(p3fes::EEContext&);
void fn_itfMesMngChangeWindowType_003a4990(p3fes::EEContext&);
void fn_itfMesMngInitSpeakerRecord_003a6900(p3fes::EEContext&);
void fn_itfMesMngInitTextRecord_003a6930(p3fes::EEContext&);
void fn_itfMesMngPushMessageArgs_003a5fd0(p3fes::EEContext&);
void fn_itfMesMngResetSelectionBySlot_003a3ab0(p3fes::EEContext&);
void fn_itfMesMngSetStateFlags_003a3e10(p3fes::EEContext&);
void fn_itfMesMngTextSetLineAlpha_003a6380(p3fes::EEContext&);
void fn_itfPnlRelease_003a8d60(p3fes::EEContext&);
void fn_itfPnlSetColor_003a8fb0(p3fes::EEContext&);
void fn_itfPnlSetPosition_003a8dc0(p3fes::EEContext&);
void fn_kwlnTaskInitEx_00194e10(p3fes::EEContext&);
void fn_kwlnTaskInit_00194c50(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_msgWinReset_003c7270(p3fes::EEContext&);
void fn_nullsub_116_003b4eb0(p3fes::EEContext&);
void fn_nullsub_117_003b4ec0(p3fes::EEContext&);
void fn_nullsub_118_003b4ed0(p3fes::EEContext&);
void fn_nullsub_119_003b4e90(p3fes::EEContext&);
void fn_nullsub_121_003b4ea0(p3fes::EEContext&);
void fn_nullsub_21_0035ac80(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrGetMessageID_0035f140(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_sprAddFile_00112370(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprFileHandleUpdate_00112110(p3fes::EEContext&);
void fn_sprSpriteDrawAll_001125d0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_10A2E0_0010a2e0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_1120C0_001120c0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_16DD40_0016dd40(p3fes::EEContext&);
void fn_sub_16E190_0016e190(p3fes::EEContext&);
void fn_sub_16E2B0_0016e2b0(p3fes::EEContext&);
void fn_sub_170C00_00170c00(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171C40_00171c40(p3fes::EEContext&);
void fn_sub_172200_00172200(p3fes::EEContext&);
void fn_sub_177670_00177670(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_17C860_0017c860(p3fes::EEContext&);
void fn_sub_191A10_00191a10(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19D400_0019d400(p3fes::EEContext&);
void fn_sub_35AD80_0035ad80(p3fes::EEContext&);
void fn_sub_35AEA0_0035aea0(p3fes::EEContext&);
void fn_sub_3A2660_003a2660(p3fes::EEContext&);
void fn_sub_3A2900_003a2900(p3fes::EEContext&);
void fn_sub_3A2970_003a2970(p3fes::EEContext&);
void fn_sub_3A2A30_003a2a30(p3fes::EEContext&);
void fn_sub_3A2B30_003a2b30(p3fes::EEContext&);
void fn_sub_3A3470_003a3470(p3fes::EEContext&);
void fn_sub_3A37C0_003a37c0(p3fes::EEContext&);
void fn_sub_3A4010_003a4010(p3fes::EEContext&);
void fn_sub_3A4220_003a4220(p3fes::EEContext&);
void fn_sub_3A4CE0_003a4ce0(p3fes::EEContext&);
void fn_sub_3A4DD0_003a4dd0(p3fes::EEContext&);
void fn_sub_3A5210_003a5210(p3fes::EEContext&);
void fn_sub_3A52C0_003a52c0(p3fes::EEContext&);
void fn_sub_3A53B0_003a53b0(p3fes::EEContext&);
void fn_sub_3A5540_003a5540(p3fes::EEContext&);
void fn_sub_3A5CA0_003a5ca0(p3fes::EEContext&);
void fn_sub_3A6060_003a6060(p3fes::EEContext&);
void fn_sub_3A6B00_003a6b00(p3fes::EEContext&);
void fn_sub_3A6B90_003a6b90(p3fes::EEContext&);
void fn_sub_3A6E30_003a6e30(p3fes::EEContext&);
void fn_sub_3A7120_003a7120(p3fes::EEContext&);
void fn_sub_3A7490_003a7490(p3fes::EEContext&);
void fn_sub_3A7940_003a7940(p3fes::EEContext&);
void fn_sub_3A7CB0_003a7cb0(p3fes::EEContext&);
void fn_sub_3A7D60_003a7d60(p3fes::EEContext&);
void fn_sub_3A7DD0_003a7dd0(p3fes::EEContext&);
void fn_sub_3A8080_003a8080(p3fes::EEContext&);
void fn_sub_3A8260_003a8260(p3fes::EEContext&);
void fn_sub_3A8350_003a8350(p3fes::EEContext&);
void fn_sub_3A8440_003a8440(p3fes::EEContext&);
void fn_sub_3A84C0_003a84c0(p3fes::EEContext&);
void fn_sub_3A8530_003a8530(p3fes::EEContext&);
void fn_sub_3A8590_003a8590(p3fes::EEContext&);
void fn_sub_3A8600_003a8600(p3fes::EEContext&);
void fn_sub_3A8650_003a8650(p3fes::EEContext&);
void fn_sub_3A8EA0_003a8ea0(p3fes::EEContext&);
void fn_sub_3A9080_003a9080(p3fes::EEContext&);
void fn_sub_3A90C0_003a90c0(p3fes::EEContext&);
void fn_sub_3A9E20_003a9e20(p3fes::EEContext&);
void fn_sub_3AA280_003aa280(p3fes::EEContext&);
void fn_sub_3AA2D0_003aa2d0(p3fes::EEContext&);
void fn_sub_3AB2A0_003ab2a0(p3fes::EEContext&);
void fn_sub_3AC230_003ac230(p3fes::EEContext&);
void fn_sub_3AC500_003ac500(p3fes::EEContext&);
void fn_sub_3AC590_003ac590(p3fes::EEContext&);
void fn_sub_3AC5A0_003ac5a0(p3fes::EEContext&);
void fn_sub_3AC600_003ac600(p3fes::EEContext&);
void fn_sub_3AC6C0_003ac6c0(p3fes::EEContext&);
void fn_sub_3AC6E0_003ac6e0(p3fes::EEContext&);
void fn_sub_3AC6F0_003ac6f0(p3fes::EEContext&);
void fn_sub_3AC750_003ac750(p3fes::EEContext&);
void fn_sub_3AC7B0_003ac7b0(p3fes::EEContext&);
void fn_sub_3AC7C0_003ac7c0(p3fes::EEContext&);
void fn_sub_3AC820_003ac820(p3fes::EEContext&);
void fn_sub_3AC890_003ac890(p3fes::EEContext&);
void fn_sub_3ACA30_003aca30(p3fes::EEContext&);
void fn_sub_3ACA40_003aca40(p3fes::EEContext&);
void fn_sub_3ACA50_003aca50(p3fes::EEContext&);
void fn_sub_3ACA90_003aca90(p3fes::EEContext&);
void fn_sub_3ACAB0_003acab0(p3fes::EEContext&);
void fn_sub_3ACB10_003acb10(p3fes::EEContext&);
void fn_sub_3ACDA0_003acda0(p3fes::EEContext&);
void fn_sub_3ACF80_003acf80(p3fes::EEContext&);
void fn_sub_3AD030_003ad030(p3fes::EEContext&);
void fn_sub_3AD130_003ad130(p3fes::EEContext&);
void fn_sub_3AD1B0_003ad1b0(p3fes::EEContext&);
void fn_sub_3AD2A0_003ad2a0(p3fes::EEContext&);
void fn_sub_3AD360_003ad360(p3fes::EEContext&);
void fn_sub_3AD380_003ad380(p3fes::EEContext&);
void fn_sub_3AD400_003ad400(p3fes::EEContext&);
void fn_sub_3AD640_003ad640(p3fes::EEContext&);
void fn_sub_3AD860_003ad860(p3fes::EEContext&);
void fn_sub_3AD930_003ad930(p3fes::EEContext&);
void fn_sub_3ADA00_003ada00(p3fes::EEContext&);
void fn_sub_3ADB00_003adb00(p3fes::EEContext&);
void fn_sub_3ADD00_003add00(p3fes::EEContext&);
void fn_sub_3ADD30_003add30(p3fes::EEContext&);
void fn_sub_3ADE60_003ade60(p3fes::EEContext&);
void fn_sub_3ADE70_003ade70(p3fes::EEContext&);
void fn_sub_3ADF40_003adf40(p3fes::EEContext&);
void fn_sub_3ADF50_003adf50(p3fes::EEContext&);
void fn_sub_3ADF60_003adf60(p3fes::EEContext&);
void fn_sub_3ADF70_003adf70(p3fes::EEContext&);
void fn_sub_3AE140_003ae140(p3fes::EEContext&);
void fn_sub_3AE150_003ae150(p3fes::EEContext&);
void fn_sub_3AE160_003ae160(p3fes::EEContext&);
void fn_sub_3AE260_003ae260(p3fes::EEContext&);
void fn_sub_3AE360_003ae360(p3fes::EEContext&);
void fn_sub_3AE560_003ae560(p3fes::EEContext&);
void fn_sub_3AE650_003ae650(p3fes::EEContext&);
void fn_sub_3AE750_003ae750(p3fes::EEContext&);
void fn_sub_3AE820_003ae820(p3fes::EEContext&);
void fn_sub_3AE840_003ae840(p3fes::EEContext&);
void fn_sub_3AE850_003ae850(p3fes::EEContext&);
void fn_sub_3AE860_003ae860(p3fes::EEContext&);
void fn_sub_3AE870_003ae870(p3fes::EEContext&);
void fn_sub_3AE8D0_003ae8d0(p3fes::EEContext&);
void fn_sub_3AE930_003ae930(p3fes::EEContext&);
void fn_sub_3AE970_003ae970(p3fes::EEContext&);
void fn_sub_3AE9B0_003ae9b0(p3fes::EEContext&);
void fn_sub_3AEC20_003aec20(p3fes::EEContext&);
void fn_sub_3AED10_003aed10(p3fes::EEContext&);
void fn_sub_3AEE00_003aee00(p3fes::EEContext&);
void fn_sub_3AF520_003af520(p3fes::EEContext&);
void fn_sub_3AF560_003af560(p3fes::EEContext&);
void fn_sub_3AFA40_003afa40(p3fes::EEContext&);
void fn_sub_3AFC30_003afc30(p3fes::EEContext&);
void fn_sub_3AFFD0_003affd0(p3fes::EEContext&);
void fn_sub_3B0030_003b0030(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_sub_3B1300_003b1300(p3fes::EEContext&);
void fn_sub_3B1330_003b1330(p3fes::EEContext&);
void fn_sub_3B18C0_003b18c0(p3fes::EEContext&);
void fn_sub_3B1D90_003b1d90(p3fes::EEContext&);
void fn_sub_3B2020_003b2020(p3fes::EEContext&);
void fn_sub_3B22A0_003b22a0(p3fes::EEContext&);
void fn_sub_3B2430_003b2430(p3fes::EEContext&);
void fn_sub_3B2900_003b2900(p3fes::EEContext&);
void fn_sub_3B2940_003b2940(p3fes::EEContext&);
void fn_sub_3B2990_003b2990(p3fes::EEContext&);
void fn_sub_3B2C60_003b2c60(p3fes::EEContext&);
void fn_sub_3B3740_003b3740(p3fes::EEContext&);
void fn_sub_3B44A0_003b44a0(p3fes::EEContext&);
void fn_sub_3B45F0_003b45f0(p3fes::EEContext&);
void fn_sub_3B4740_003b4740(p3fes::EEContext&);
void fn_sub_3B4920_003b4920(p3fes::EEContext&);
void fn_sub_3B4A90_003b4a90(p3fes::EEContext&);
void fn_sub_3B4B40_003b4b40(p3fes::EEContext&);
void fn_sub_3B4D10_003b4d10(p3fes::EEContext&);
void fn_sub_3BB060_003bb060(p3fes::EEContext&);
void fn_sub_3C3F80_003c3f80(p3fes::EEContext&);
void fn_sub_3CF120_003cf120(p3fes::EEContext&);
void fn_sub_3CF520_003cf520(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui4;  // the named offsets of ui4.h (spr, rw, mes, pnl, lay, fnt)

// 0x001120C0 sub_1120C0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [sprUpdateFiles] Runs sprFileHandleUpdate on every .SPR file handle of the list (gp-0x4DB0), from the
// head along +0x1B8 (sprFontInit, kwlnRootUpdate2DDrawBeginTask, the PAK screens).
void sub_1120C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001120c0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, gp, spr::kGpFileList);  // 0x7CDF40: first file handle
    for (;;) {
        // 0x001120d0
        charge(ctx, 3);
        if (s0 == 0) {
            break;
        }
        // 0x001120dc
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x1120E0u, gen::fn_sprFileHandleUpdate_00112110);
        lw(s0, s0, spr::kFileNext);
        backedge(ctx);
    }
    // 0x001120f4
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00112370 sprAddFile -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Registers a .SPR file by path: RwCalloc(1, 0x1C0, 0x40000) a file handle, kind 0, the path copied to +2,
// appended at the tail of the file list (the loading itself is sprFileHandleUpdate's, frame by frame).
// Returns the handle.
void sprAddFile(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00112370
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 448;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCalloc);  // 0x960184
    jalr(ctx, 0x112398u, v0.u());
    s0 = v0;
    sh(zero, v0, spr::kFileKind);  // kind 0: a path
    a0 = addiu(s0, 2);
    a1 = s1;
    jal(ctx, 0x1123B0u, gen::fn_strcpy_00524270);
    lw(v1, gp, spr::kGpFileList);  // 0x7CDF40
    if (v1 != 0) {
        for (;;) {
            // 0x001123d0
            charge(ctx, 3);
            lw(v0, v1, spr::kFileNext);
            if (v0 == 0) {
                break;
            }
            // 0x001123ec
            charge(ctx, 3);
            v1 = v0;
            backedge(ctx);
        }
        // 0x001123dc
        charge(ctx, 4);
        sw(s0, v1, spr::kFileNext);  // tail->next = new
        sw(v1, s0, spr::kFilePrev);  // new->prev = tail
    } else {
        // 0x001123c4
        charge(ctx, 3);
        sw(s0, gp, spr::kGpFileList);  // 0x7CDF40: the first handle
    }
    // 0x001123f8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001125D0 sprSpriteDrawAll -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Draws the persistent sprite handles (kwlnRootUpdate2DDrawBeginTask): the Im2D render states (6,1) (7,2) (8,1)
// (9,1) (12,1) (11,6) (10,5) through RwRenderStateSet (0x960090), then sprDrawSprite (sub_1127D0) on every
// handle of the list at gp-0x4DB4.
void sprSpriteDrawAll(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001125d0
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 144);  // &pfn_RwRenderStateSet
    a0 = 6;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x1125F0u, v0.u());
    a0 = 7;
    a1 = 2;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x112604u, v0.u());
    a0 = 8;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x112618u, v0.u());
    a0 = 9;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x11262Cu, v0.u());
    a0 = 12;
    a1 = 1;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x112640u, v0.u());
    a0 = 11;
    a1 = 6;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x112654u, v0.u());
    a0 = 10;
    a1 = 5;
    lw(v0, s0, 0);  // pfn_RwRenderStateSet
    jalr(ctx, 0x112668u, v0.u());
    lw(s0, gp, spr::kGpHandleList);  // 0x7CDF3C: first handle
    for (;;) {
        // 0x00112674
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        // 0x0011267c
        charge(ctx, 7);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x112684u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite(handle, 1)
        lw(s0, s0, spr::kHandleNext);
        backedge(ctx);
    }
    // 0x00112698
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A2660 sub_3A2660 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [scrCommand_MSG_SEL] Script COMM handler of a selection: with no message slot returns 1. Otherwise (K_Assert
// line 937 on a null handle) reads integer parameter 0; while +84 is 0 it (re)issues the selection request
// (sub_3A37C0(slot, p)) and returns 0 (call again); once +84 went negative it clears it, returns the chosen
// option (+86) to the script, resets the selection and returns 1. A positive +84 returns 0.
void sub_3A2660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2660
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3A2670u, gen::fn_scrGetMessageID_0035f140);  // the script's message slot (< 0: none)
    s0 = v0;
    if (i64(s0) >= 0) {
        // 0x003a2690
        charge(ctx, 11);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x960000;
        v0 = addiu(v0, -24852);  // &0x959EEC
        v0 = addu(v0, v1);
        lw(s1, v0, 0);
        if (s1 == 0) {
            // 0x003a26bc
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 6768);  // "itfMesManager.c"
            a1 = 937;
            jal(ctx, 0x3A26C8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
        }
        // 0x003a26d0
        charge(ctx, 7);
        a0 = 0;
        jal(ctx, 0x3A26D4u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        a0 = addiu(s1, 64);
        lh(v1, s1, mes::kSelectWord84);
        if (v1 == 0) {
            // 0x003a26ec
            charge(ctx, 6);
            a0 = s0;
            a1 = v0;
            jal(ctx, 0x3A26F4u, gen::fn_sub_3A37C0_003a37c0);
            goto L_003a2734;
        }
        // 0x003a2704
        charge(ctx, 2);
        if (i64(v1) >= 0) {
        L_003a2734:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003a270c
            charge(ctx, 10);
            sh(zero, a0, 20);
            lh(a0, a0, 22);
            jal(ctx, 0x3A2714u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM's integer result
            a0 = s0;
            jal(ctx, 0x3A2720u, gen::fn_itfMesMngResetSelectionBySlot_003a3ab0);
            v0 = 1;
        }
    } else {
        // 0x003a2684
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003a2738 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A2900 sub_3A2900 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [scrCommand_MSG_WINDOW] COMM handler: switches the script's message window to type 4 (arg 0) and sets state
// bit 0x200000 (open on the next request). Returns 1.
void sub_3A2900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2900
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3A290Cu, gen::fn_scrGetMessageID_0035f140);  // the script's message slot (< 0: none)
    s0 = v0;
    if (i64(s0) >= 0) {
        // 0x003a292c
        charge(ctx, 10);
        a0 = s0;
        a1 = 4;
        a2 = 0;
        jal(ctx, 0x3A2938u, gen::fn_itfMesMngChangeWindowType_003a4990);
        a0 = s0;
        a1 = 0x200000;
        jal(ctx, 0x3A2948u, gen::fn_itfMesMngSetStateFlags_003a3e10);
        v0 = 1;
    } else {
        // 0x003a2920
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003a2954 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A2970 sub_3A2970 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [scrCommand_MSG_CLOSE] COMM handler: with no slot returns 1. Otherwise (K_Assert line 1227) while the window
// phase (state bits 8-9) is 1 or 2 it starts the close (sub_3A2A30); returns 1 once the phase is 0 (closed),
// else 0.
void sub_3A2970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2970
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3A2980u, gen::fn_scrGetMessageID_0035f140);  // the script's message slot (< 0: none)
    s0 = v0;
    if (i64(s0) >= 0) {
        // 0x003a29a0
        charge(ctx, 11);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 2);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x960000;
        v0 = addiu(v0, -24852);  // &0x959EEC
        v0 = addu(v0, v1);
        lw(s1, v0, 0);
        if (s1 == 0) {
            // 0x003a29cc
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 6768);  // "itfMesManager.c"
            a1 = 1227;
            jal(ctx, 0x3A29D8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
        }
        // 0x003a29e0
        charge(ctx, 5);
        lw(v0, s1, mes::kState);
        s1 = v0 & 0x300;
        v0 = 256;
        if (s1 != v0) {
            // 0x003a29f4
            charge(ctx, 3);
            v0 = 512;
            if (s1 == v0) {
                goto L_003a2a00;
            }
            goto L_003a2a0c;
        }
    L_003a2a00:
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x3A2A04u, gen::fn_sub_3A2A30_003a2a30);
    L_003a2a0c:
        charge(ctx, 2);
        v0 = s1;
        v0 = sltiu(v0, 1);
    } else {
        // 0x003a2994
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003a2a14 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A2B30 sub_3A2B30 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [scrCommand_SET_MSG_VAR] COMM handler SET_MSG_VAR(index, value, type): prints the call (debug printf), then
// sub_3A4010(slot, index, value, type), the three parameters read again. Returns 1.
void sub_3A2B30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a2b30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3A2B44u, gen::fn_scrGetMessageID_0035f140);  // the script's message slot (< 0: none)
    s2 = v0;
    if (i64(s2) >= 0) {
        // 0x003a2b64
        charge(ctx, 36);
        a0 = 0;
        jal(ctx, 0x3A2B68u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        s1 = v0;
        a0 = 1;
        jal(ctx, 0x3A2B78u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        s0 = v0;
        a0 = 2;
        jal(ctx, 0x3A2B88u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        a0 = 0x6A0000;
        a0 = addiu(a0, 6784);  // "CALL SET_MSG_VAR(INT,INT,INT) index=%d val=%d type=%d\n"
        a1 = s1;
        a2 = s0;
        a3 = v0;
        jal(ctx, 0x3A2BA4u, gen::fn_printf_005225a8);  // printf (debug text)
        a0 = 0;
        jal(ctx, 0x3A2BB0u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        s1 = v0;
        a0 = 1;
        jal(ctx, 0x3A2BC0u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        s0 = v0;
        a0 = 2;
        jal(ctx, 0x3A2BD0u, gen::fn_scrGetIntPara_0035ed20);  // integer parameter $a0 of the COMM
        a0 = s2;
        a1 = s1;
        a2 = s0;
        a3 = v0;
        jal(ctx, 0x3A2BE8u, gen::fn_sub_3A4010_003a4010);
        v0 = 1;
    } else {
        // 0x003a2b58
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003a2bf4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003A3470 sub_3A3470 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngClearText] Releases the handle's text lines and resets the text sub-record (itfMesMngInitTextRecord,
// keep 0), clears the request state (bits 0-2) and bit 17; with `also_speaker` the speaker name line too
// (itfMesMngInitSpeakerRecord, keep 0).
void sub_3A3470(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a3470
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    s2 = addiu(s1, 36);
    lw(a0, a0, mes::kTextLines);
    if (a0 != 0) {
        // 0x003a349c
        charge(ctx, 3);
        jal(ctx, 0x3A349Cu, gen::fn_sub_3B0170_003b0170);  // release the line chain once faded
        sw(zero, s2, mes::kSubTextLines);
    }
    // 0x003a34a8
    charge(ctx, 14);
    a0 = s2;
    a1 = 0;
    jal(ctx, 0x3A34B0u, gen::fn_itfMesMngInitTextRecord_003a6930);
    lw(a0, s1, mes::kState);
    v1 = si(-8);
    a0 = a0 & v1;
    sw(a0, s1, mes::kState);
    v1 = lui(0xFFFD);
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    sw(v1, s1, mes::kState);
    if (s0 != 0) {
        // 0x003a34e0
        charge(ctx, 4);
        s0 = addiu(s1, 20);
        lw(a0, s1, mes::kSpeakerLine);
        if (a0 != 0) {
            // 0x003a34f0
            charge(ctx, 3);
            jal(ctx, 0x3A34F0u, gen::fn_sub_3B0170_003b0170);  // release the line chain once faded
            sw(zero, s0, mes::kSubLine);
        }
        // 0x003a34fc
        charge(ctx, 4);
        a0 = addiu(s1, 20);
        a1 = 0;
        jal(ctx, 0x3A3504u, gen::fn_itfMesMngInitSpeakerRecord_003a6900);
    }
    // 0x003a350c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003A4220 sub_3A4220 -- 72 bytes; frame 0x10: ra sp+0x0
// [itfMesMngSetMessageArgStringBySlot] sub_3A5CA0(handle of slot, i, text, 0): message argument i of the slot
// becomes a copy of `text` (18 callers: the battle, facility and event texts).
void sub_3A4220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a4220
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -24852);  // &0x959EEC
    v0 = addu(v0, v1);
    lw(a0, v0, 0);  // the slot's handle
    a3 = 0;
    jal(ctx, 0x3A4250u, gen::fn_sub_3A5CA0_003a5ca0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A4CE0 sub_3A4CE0 -- 236 bytes; frame 0x10: ra sp+0x0
// [itfMesMngSystemInit] The message manager's start (frFontSystemStart): counters and flags cleared, the 64-slot
// list built over 0x959EE0 (sub_3B4920, 52-byte slots) with every free slot's handle cleared, the process
// "CalcMsgMng" (dds3InitProcess sub_35AD80: priority 4207, update sub_3A8440, destroy sub_3A8530) and the task
// "DrawMsgMng" (kwlnTaskInit: 7359, sub_3A84C0, sub_3A8530) created, then "[%s] init mes manage" printed.
void sub_3A4CE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a4ce0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    sw(zero, v0, mes::kLoHandleCount);  // 0x959EC0
    v0 = 0x960000;
    sw(zero, v0, mes::kLoDrawFrames);  // 0x959EC8
    v0 = 0x960000;
    sh(zero, v0, mes::kLoFlags);  // 0x959ECC
    a0 = 0x960000;
    a0 = addiu(a0, -24880);  // &0x959ED0
    a1 = 0x960000;
    a1 = addiu(a1, -24864);  // &0x959EE0
    a2 = 64;
    a3 = 52;
    jal(ctx, 0x3A4D18u, gen::fn_sub_3B4920_003b4920);
    v0 = 0x960000;
    lw(v0, v0, mes::kLoSlotFree);  // 0x959ED8
    for (;;) {
        // 0x003a4d38
        charge(ctx, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a4d30
        charge(ctx, 2);
        sw(zero, v0, mes::kSlotHandle);
        lw(v0, v0, mes::kSlotNext);
    }
    // 0x003a4d4c
    charge(ctx, 32);
    a0 = 0x6A0000;
    a0 = addiu(a0, 7000);  // "CalcMsgMng"
    a1 = 4207;
    a2 = 0;
    a3 = 0;
    t0 = 0x3B0000;
    t0 = addiu(t0, -31680);  // &sub_3A8440
    t1 = 0x3B0000;
    t1 = addiu(t1, -31440);  // &sub_3A8530
    t2 = 0;
    jal(ctx, 0x3A4D74u, gen::fn_sub_35AD80_0035ad80);
    a0 = 0x6A0000;
    a0 = addiu(a0, 7016);  // "DrawMsgMng"
    a1 = 7359;
    a2 = 0x3B0000;
    a2 = addiu(a2, -31552);  // &sub_3A84C0
    a3 = 0x3B0000;
    a3 = addiu(a3, -31440);  // &sub_3A8530
    t0 = 0;
    jal(ctx, 0x3A4D9Cu, gen::fn_kwlnTaskInit_00194c50);
    a0 = 0x6A0000;
    a0 = addiu(a0, 7040);  // "[%s] init mes manage\n"
    a1 = 0x6A0000;
    a1 = addiu(a1, 6768);  // "itfMesManager.c"
    jal(ctx, 0x3A4DB4u, gen::fn_printf_005225a8);  // printf (debug text)
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A5210 sub_3A5210 -- 176 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngSetTextStyleBySlot] On the slot's text line chain: alpha, line code, style, colour set
// (frFontLineSetAlpha / frFontNodeSetCode / frFontLineSetStyle / frFontLineSetColourSet).
void sub_3A5210(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a5210
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    s0 = t0;
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -24852);  // &0x959EEC
    v0 = addu(v0, v1);
    lw(v0, v0, 0);  // the slot's handle
    lw(s3, v0, mes::kTextLines);
    a1 = a3 & 0xFF;
    a0 = s3;
    jal(ctx, 0x3A5264u, gen::fn_frFontLineSetAlpha_003b0bb0);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    a0 = s3;
    jal(ctx, 0x3A5278u, gen::fn_frFontNodeSetCode_003b0c20);
    a0 = s3;
    a1 = s2;
    jal(ctx, 0x3A5288u, gen::fn_frFontLineSetStyle_003b0ce0);
    a1 = s1 & 0xFF;
    a0 = s3;
    jal(ctx, 0x3A5298u, gen::fn_frFontLineSetColourSet_003b0dd0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003A52C0 sub_3A52C0 -- 236 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [itfMesMngLayoutLineBySlot] Pushes the message arguments of the slot in $t2 to the font, lays out a dialogue line
// through sub_3A53B0 (its sixth argument 0) and sets the result's style to $a3. Returns the line chain
// (sub_248580, sub_25BE60: battle texts).
void sub_3A52C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003a52c0
    enter(ctx, 59);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s5 = a0;
    s4 = a1;
    mov_s(f20, f12);
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    s6 = t2;
    v0 = sll(s0, 1);
    v0 = addu(v0, s0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -24852);  // &0x959EEC
    v0 = addu(v0, v1);
    lw(v0, v0, 0);  // the slot's handle
    a0 = addiu(v0, 212);
    jal(ctx, 0x3A5330u, gen::fn_itfMesMngPushMessageArgs_003a5fd0);
    a0 = s5;
    a1 = s4;
    mov_s(f12, f20);
    a2 = s3;
    a3 = s2;
    t0 = s1;
    t1 = 0;
    t2 = s0;
    t3 = s6;
    jal(ctx, 0x3A535Cu, gen::fn_sub_3A53B0_003a53b0);
    s0 = v0;
    a0 = s0;
    a1 = s2;
    jal(ctx, 0x3A5370u, gen::fn_frFontLineSetStyle_003b0ce0);
    v0 = s0;
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003A5540 sub_3A5540 -- 48 bytes; frame 0x10: ra sp+0x0
// [itfMesMngLayoutLine] sub_3A53B0 with the arguments from the sixth on moved one register up and 0 as the
// sixth (5 callers in the battle UI).
void sub_3A5540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a5540
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = t1;
    t3 = t2;
    t1 = 0;
    t2 = v0;
    jal(ctx, 0x3A5558u, gen::fn_sub_3A53B0_003a53b0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A6060 sub_3A6060 -- 160 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngSetSpeakerText] Replaces the handle's speaker name line by a layout of `text` at the speaker
// position (style 0, colour set 1, alpha 255) and marks the speaker index 0xFFFF (sub_3A5980). K_Assert line
// 4406 on a null handle.
void sub_3A6060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a6060
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    if (s2 == 0) {
        // 0x003a6084
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 6768);  // "itfMesManager.c"
        a1 = 4406;
        jal(ctx, 0x3A6090u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003a6098
    charge(ctx, 4);
    s0 = addiu(s2, 20);
    lw(a0, s2, mes::kSpeakerLine);
    if (a0 != 0) {
        // 0x003a60a8
        charge(ctx, 2);
        jal(ctx, 0x3A60A8u, gen::fn_sub_3B0170_003b0170);  // release the line chain once faded
    }
    // 0x003a60b0
    charge(ctx, 20);
    lw(a0, s0, mes::kSubX);
    lw(a1, s0, mes::kSubY);
    a2 = 0;
    a3 = 1;
    t0 = 0;
    t1 = 255;
    t2 = s1;
    t3 = 0;
    jal(ctx, 0x3A60D0u, gen::fn_sub_3B2940_003b2940);  // lay out text at (x, y)
    sw(v0, s0, mes::kSubLine);
    v1 = 0xFFFF;
    sh(v1, s0, mes::kSubIndex);  // no speaker
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003A6B00 sub_3A6B00 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngReleasePanels] Releases the three panels of the handle (+168, +172, +176) and clears state bits 8-11.
void sub_3A6B00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a6b00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = addiu(s1, 168);
    lw(a0, a0, mes::kPanel0);
    if (a0 != 0) {
        // 0x003a6b24
        charge(ctx, 3);
        jal(ctx, 0x3A6B24u, gen::fn_itfPnlRelease_003a8d60);
        sw(zero, s0, 0);  // handle +168 = 0
    }
    // 0x003a6b30
    charge(ctx, 3);
    lw(a0, s0, mes::kPnlRecNext);
    if (a0 != 0) {
        // 0x003a6b3c
        charge(ctx, 3);
        jal(ctx, 0x3A6B3Cu, gen::fn_itfPnlRelease_003a8d60);
        sw(zero, s0, mes::kPnlRecNext);
    }
    // 0x003a6b48
    charge(ctx, 3);
    lw(a0, s0, mes::kPnlRecThird);
    if (a0 != 0) {
        // 0x003a6b54
        charge(ctx, 3);
        jal(ctx, 0x3A6B54u, gen::fn_itfPnlRelease_003a8d60);
        sw(zero, s0, mes::kPnlRecThird);
    }
    // 0x003a6b60 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(a0, s1, mes::kState);
    v1 = si(-3841);
    v1 = a0 & v1;
    sw(v1, s1, mes::kState);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A6B90 sub_3A6B90 -- 116 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngFreeArgStrings] For the 32 message-argument words at `table`: a non-zero word has its heap block
// (32 words further) H_Freed and is cleared.
void sub_3A6B90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a6b90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = 0;
    for (;;) {
        // 0x003a6bdc
        charge(ctx, 3);
        v1 = slti(s1, 32);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a6bb4
        charge(ctx, 5);
        v1 = sll(s1, 2);
        s0 = addu(s2, v1);
        lw(v1, s0, 0);  // argument word i
        if (v1 != 0) {
            // 0x003a6bc8
            charge(ctx, 4);
            lw(a0, s0, mes::kArgBlocks);  // its heap block
            jal(ctx, 0x3A6BCCu, gen::fn_sub_191A10_00191a10);  // H_Free
            sw(zero, s0, 0);  // word i = 0
        }
        // 0x003a6bd8
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003a6be8
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003A7940 sub_3A7940 -- 256 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngMoveWindowY] Moves a handle's window down by `dy`: text y and every text line's y, panels 1 and 0
// (sub_3A8EA0, the panel move), and when a speaker name exists the speaker y and its lines.
void sub_3A7940(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a7940
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = addiu(a0, 20);
    s0 = addiu(a0, 168);
    lw(v1, a0, mes::kTextY);
    v1 = addu(v1, s2);
    sw(v1, a0, mes::kTextY);
    lw(a0, a0, mes::kTextLines);
    for (;;) {
        // 0x003a7988
        charge(ctx, 3);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a7978
        charge(ctx, 4);
        lw(v1, a0, mes::kLineY);
        v1 = addu(v1, s2);
        sw(v1, a0, mes::kLineY);
        lw(a0, a0, mes::kLineNext);
    }
    // 0x003a7994
    charge(ctx, 3);
    lw(a0, s0, mes::kPnlRecNext);  // panel 1
    if (a0 != 0) {
        // 0x003a79a0
        charge(ctx, 7);
        a1 = 0;
        a2 = s2;
        a3 = 0;
        t0 = 0;
        t1 = 0;
        jal(ctx, 0x3A79B4u, gen::fn_sub_3A8EA0_003a8ea0);
    }
    // 0x003a79bc
    charge(ctx, 3);
    lw(a0, s0, 0);  // panel 0 (handle +168)
    if (a0 != 0) {
        // 0x003a79c8
        charge(ctx, 7);
        a1 = 0;
        a2 = s2;
        a3 = 0;
        t0 = s2;
        t1 = 0;
        jal(ctx, 0x3A79DCu, gen::fn_sub_3A8EA0_003a8ea0);
    }
    // 0x003a79e4
    charge(ctx, 3);
    lw(v1, s1, mes::kSubLine);  // speaker name line
    if (v1 != 0) {
        // 0x003a79f0
        charge(ctx, 6);
        lw(v1, s1, mes::kSubY);
        v1 = addu(v1, s2);
        sw(v1, s1, mes::kSubY);
        lw(a0, s1, mes::kSubLine);
        for (;;) {
            // 0x003a7a18
            charge(ctx, 3);
            if (a0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a7a08
            charge(ctx, 4);
            lw(v1, a0, mes::kLineY);
            v1 = addu(v1, s2);
            sw(v1, a0, mes::kLineY);
            lw(a0, a0, mes::kLineNext);
        }
    }
    // 0x003a7a24 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003A7CB0 sub_3A7CB0 -- 176 bytes; frame 0x10: ra sp+0x0
// [itfMesMngMoveSelection] Moves the selection cursor of a selection sub-record one option by the sign of $a1
// (wrapping at both ends): the old row back to alpha 0, the new one to 6 (itfMesMngTextSetLineAlpha), +86 and
// +88 = the new row, then the cursor sound (sub_10A4E0(0, 0, 0, 0)).
void sub_3A7CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a7cb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t1 = a0;
    t0 = a1;
    lh(v0, a0, mes::kSelChosen);
    lh(a2, a0, mes::kSelCount);
    lw(a0, a0, mes::kSelLines);
    a1 = v0;
    a3 = 0;
    jal(ctx, 0x3A7CD4u, gen::fn_itfMesMngTextSetLineAlpha_003a6380);
    if (i64(t0) >= 0) {
        // 0x003a7d00
        charge(ctx, 5);
        t0 = addiu(v0, 1);
        lh(v0, t1, mes::kSelCount);
        v0 = slt(t0, v0);
        if (v0 == 0) {
            // 0x003a7d14
            charge(ctx, 1);
            t0 = 0;
        }
    } else {
        // 0x003a7ce4
        charge(ctx, 3);
        t0 = addiu(v0, -1);
        if (i64(t0) < 0) {
            // 0x003a7cf0
            charge(ctx, 4);
            lh(v0, t1, mes::kSelCount);
            t0 = addiu(v0, -1);
        }
    }
    // 0x003a7d18
    charge(ctx, 18);
    lh(a2, t1, mes::kSelCount);
    lw(a0, t1, mes::kSelLines);
    a1 = t0;
    a3 = 6;
    jal(ctx, 0x3A7D28u, gen::fn_itfMesMngTextSetLineAlpha_003a6380);
    sh(t0, t1, mes::kSelChosen);
    sh(t0, t1, mes::kSelCursor2);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3A7D48u, gen::fn_sub_10A4E0_0010a4e0);  // the cursor sound
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A7D60 sub_3A7D60 -- 100 bytes; leaf frame (no stack)
// [itfMesMngKeyToValue] Returns the value of the first {pad bit, value} pair (from +40, count at +38) whose bit
// is held in gPadFlags (0x7E094E); -1 when none.
void sub_3A7D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x003a7d60
    enter(ctx, 7);  // entry check point + this block's cycles
    t0 = 0;
    v0 = 0x7E0000;
    lhu(a3, v0, 2382);  // gPadFlags
    lh(a2, a0, mes::kSelKeyCount);
    v1 = 1;
    for (;;) {
        // 0x003a7dac
        charge(ctx, 3);
        v0 = slt(t0, a2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a7d7c
        charge(ctx, 8);
        v0 = sll(t0, 2);
        v0 = addu(a0, v0);
        a1 = addiu(v0, 40);
        lh(v0, v0, 40);
        v0 = sllv(v1, v0);
        v0 = a3 & v0;
        if (v0 != 0) {
            goto L_003a7d9c_2;
        }
        // 0x003a7da8
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
    // 0x003a7db8
    charge(ctx, 1);
    v0 = si(-1);
    // 0x003a7dbc (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003a7d9c_2:
    charge(ctx, 3);
    lh(v0, a1, 2);
    // 0x003a7dbc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003A7DD0 sub_3A7DD0 -- 180 bytes; frame 0x10
// [itfMesMngWindowPopStep] One frame of the window pop-in: while the window sub-record (+468) is active and in
// phase 0 the frame advances and the y offset takes the curve value {0, -32, -12, 6, -4, 0}[frame] (0x6A1BD0,
// copied to the frame first); at frame 5 the phase becomes 1 (done).
void sub_3A7DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29};
    // 0x003a7dd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = addiu(a0, 468);
    a3 = 0x6A0000;
    a3 = addiu(a3, 7120);  // &0x6A1BD0
    a2 = addiu(sp, 0x0);
    a1 = 3;
    for (;;) {
        // 0x003a7de8
        charge(ctx, 9);
        lh(a0, a3, 0);
        lh(v1, a3, 2);
        a3 = addiu(a3, 4);
        a1 = addiu(a1, -1);
        sh(a0, a2, 0);
        sh(v1, a2, 2);
        a2 = addiu(a2, 4);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003a7e0c
    charge(ctx, 3);
    lbu(v1, t0, mes::kWinActive);
    if (v1 != 0) {
        // 0x003a7e18
        charge(ctx, 4);
        lh(v1, t0, mes::kWinPhase);
        a0 = 1;
        if (v1 != a0) {
            // 0x003a7e28
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x003a7e38
                charge(ctx, 13);
                lh(v1, t0, mes::kWinFrame);
                v1 = addiu(v1, 1);
                sh(v1, t0, mes::kWinFrame);
                v1 = dsll32(v1, 16);
                v1 = dsra32(v1, 16);
                v1 = sll(v1, 1);
                v1 = addu(v1, sp);
                lh(v1, v1, 0);
                sh(v1, t0, mes::kWinYOffset);
                lh(v1, t0, mes::kWinFrame);
                v1 = slti(v1, 5);
                if (v1 == 0) {
                    // 0x003a7e6c
                    charge(ctx, 3);
                    sh(a0, t0, mes::kWinPhase);  // done
                    v1 = 5;
                    sh(v1, t0, mes::kWinFrame);
                }
            } else {
                // 0x003a7e30
                charge(ctx, 2);
            }
        }
    }
    // 0x003a7e78 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sp = addiu(sp, 0x10);
}

// 0x003A8080 sub_3A8080 -- 236 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesManagerDrawPanels] Draws a handle's window panels unless state bit 19 is set: with a window phase >= 1
// panel 1 (not for window type 3) through sub_3A9080, manager flag bit 1 set, and panel 2 when present; then,
// when the record at 0x958BE8 names this handle, the cursor corners of panel 1 (sub_3A8590).
void sub_3A8080(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8080
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 0);
    v1 = 0x80000;
    v1 = a0 & v1;
    if (v1 == 0) {
        // 0x003a80a8
        charge(ctx, 5);
        s0 = addiu(s1, 168);
        v1 = a0 & 0x300;
        v1 = sltiu(v1, 256);
        if (v1 == 0) {
            // 0x003a80bc
            charge(ctx, 4);
            lh(v1, s1, mes::kWindowType);
            at = sltiu(v1, 6);
            if (at != 0) {
                // 0x003a80cc
                charge(ctx, 7);
                a0 = 0x7C0000;
                a0 = addiu(a0, -20032);  // &0x7BB1C0
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x3A80E8u:  // table[0, 1, 2, 4, 5]
                L_003a80e8:
                    charge(ctx, 4);
                    lw(a0, s0, mes::kPnlRecNext);  // panel 1
                    a1 = 0;
                    jal(ctx, 0x3A80F0u, gen::fn_sub_3A9080_003a9080);
                    break;
                case 0x3A80F8u:  // table[3]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
                goto L_003a80f8;
            }
            goto L_003a80e8;
        }
    L_003a8124:
        charge(ctx, 4);
        v1 = 0x960000;
        lw(v1, v1, mes::kLoCursorOwner);  // 0x958BE8
        if (v1 != 0) {
            // 0x003a8134
            charge(ctx, 3);
            lw(v1, v1, mes::kSlotHandle);  // its +12
            if (v1 == s1) {
                // 0x003a8140
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x003a8148
                    charge(ctx, 3);
                    lw(a0, s0, mes::kPnlRecNext);  // panel 1
                    jal(ctx, 0x3A814Cu, gen::fn_sub_3A8590_003a8590);
                }
            }
        }
    }
    // 0x003a8154 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_003a80f8:
    charge(ctx, 8);
    v1 = 0x960000;
    lhu(v1, v1, mes::kLoFlags);  // 0x959ECC
    a0 = v1 | 0x2;
    v1 = 0x960000;
    sh(a0, v1, mes::kLoFlags);  // 0x959ECC
    lw(a0, s0, mes::kPnlRecThird);  // panel 2
    if (a0 != 0) {
        // 0x003a8118
        charge(ctx, 3);
        a1 = 0;
        jal(ctx, 0x3A811Cu, gen::fn_sub_3A9080_003a9080);
    }
    goto L_003a8124;
}

// 0x003A8170 itfMesManagerDrawSprite -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Draws the selection cursor bar of a handle (when a cursor row is set and an option line exists): y =
// 1928 + 200 * row for 4 options, else 1928 + 8 * (int)(75.0 / count) * row + 8 * ((int)(75.0 / count) >> 1);
// then sprites 0x12 at x 225 and 0x13 at x 561 of facility/i_mes_win01.spr at (y >> 3) + 2, alpha 255
// (itfMesManagerDrawSpriteEx). (20_menu_ui.md 4.3 calls these the window frame; the instructions draw them
// at the cursor row.)
void itfMesManagerDrawSprite(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x003a8170
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a2 = addiu(a0, 64);
    lh(a1, a0, mes::kSelectRow);
    v1 = si(-1);
    if (a1 != v1) {
        // 0x003a8190
        charge(ctx, 3);
        lw(v1, a2, mes::kSelLines);  // the option lines
        if (v1 != 0) {
            // 0x003a819c
            charge(ctx, 4);
            lh(v1, a2, mes::kSelCount);
            v0 = 4;
            if (v1 != v0) {
                // 0x003a81cc
                charge(ctx, 15);
                v0 = 0x42960000;
                mtc1(v0, f1);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(a0, f0);
                v0 = sra(a0, 1);
                v0 = sll(v0, 3);
                v1 = addiu(v0, 1928);
                v0 = sll(a0, 3);
                mult(v0, v0, a1);
                v0 = addu(v1, v0);
            } else {
                // 0x003a81ac
                charge(ctx, 8);
                v0 = sll(a1, 2);
                v1 = addu(v0, a1);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v0 = sll(v0, 3);
                v0 = addiu(v0, 1928);
            }
            // 0x003a8208
            charge(ctx, 16);
            v0 = sra(v0, 3);
            s0 = addiu(v0, 2);
            mtc1(zero, f12);
            a0 = 225;
            a1 = s0;
            a2 = 255;
            a3 = 18;
            jal(ctx, 0x3A8224u, gen::fn_itfMesManagerDrawSpriteEx_003a8710);
            mtc1(zero, f12);
            a0 = 561;
            a1 = s0;
            a2 = 255;
            a3 = 19;
            jal(ctx, 0x3A8240u, gen::fn_itfMesManagerDrawSpriteEx_003a8710);
        }
    }
    // 0x003a8248 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A8260 sub_3A8260 -- 228 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngMeasureCursor] Debug "drawCursolVist": for a handle with a cursor row, finds the widest row of the
// option lines (its position into +92, its width into +96) and the cursor row's position (into a dead local).
void sub_3A8260(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8260
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = addiu(a0, 64);
    lh(s1, a0, mes::kSelectRow);
    v1 = si(-1);
    if (s1 != v1) {
        // 0x003a828c
        charge(ctx, 9);
        a0 = 0x6A0000;
        a0 = addiu(a0, 7136);  // "%s drawCursolVist\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, 6768);  // "itfMesManager.c"
        jal(ctx, 0x3A829Cu, gen::fn_printf_005225a8);  // printf (debug text)
        s3 = 0;
        for (;;) {
            // 0x003a82f8
            charge(ctx, 6);
            lw(a0, s0, mes::kSelLines);
            jal(ctx, 0x3A82FCu, gen::fn_frFontChainCountLines_003b1a90);
            v0 = slt(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003a82b0
            charge(ctx, 9);
            a0 = s3;
            lw(a1, s0, mes::kSelLines);
            jal(ctx, 0x3A82B8u, gen::fn_frFontChainGetRowWidth_003b1b00);
            s2 = v0;
            lw(v0, s0, mes::kSelWidest);
            at = slt(v0, s2);
            if (at != 0) {
                // 0x003a82d4
                charge(ctx, 8);
                a0 = addiu(sp, 0x58);
                a1 = s3;
                lw(a2, s0, mes::kSelLines);
                jal(ctx, 0x3A82E0u, gen::fn_frFontChainGetRowPos_003b1bc0);
                lw(v0, sp, 0x58);
                sw(v0, s0, mes::kSelWidestPos);
                sw(s2, s0, mes::kSelWidest);
            }
            // 0x003a82f4
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x003a8310
        charge(ctx, 5);
        a0 = addiu(sp, 0x58);
        a1 = s1;
        lw(a2, s0, mes::kSelLines);
        jal(ctx, 0x3A831Cu, gen::fn_frFontChainGetRowPos_003b1bc0);
    }
    // 0x003a8324 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003A8350 sub_3A8350 -- 236 bytes; frame 0x20: ra sp+0x0
// [itfMesMngDrawPrompt] Draws sprite 0x10 of i_mes_win01.spr at the window position (+480, +482 - 5 + the pop-in
// y offset) with alpha 255 * frame / 5 (the float -> u8 conversion with its >= 2^31 path).
void sub_3A8350(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x003a8350
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    ld(v0, gp, -22584);  // 0x7CD4B8
    sd(v0, sp, 0x18);
    lh(v0, a0, mes::kWindowX);
    mtc1(v0, f0);
    cvt_s_w(f2, f0);
    swc1(f2, sp, 0x18);
    lh(v0, a0, mes::kWindowY);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x1C);
    cvt_w_s(f0, f2);
    mfc1(a3, f0);
    cvt_w_s(f0, f1);
    mfc1(v0, f0);
    v1 = addiu(v0, -5);
    lh(v0, a0, mes::kWindowYOffset);
    a1 = addu(v1, v0);
    lh(v1, a0, mes::kWindowFrame);
    v0 = sll(v1, 8);
    v0 = subu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x40A00000;
    mtc1(v0, f0);
    div_s(f1, f1, f0);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x003a8400
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v0 = lui(0x8000);
        a2 = a2 | v0;
        a2 = a2 & 0xFF;
    } else {
        // 0x003a83e8
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(a2, f0);
        a2 = a2 & 0xFF;
    }
    // 0x003a8418
    charge(ctx, 9);
    mtc1(zero, f12);
    a0 = a3;
    a3 = 16;
    jal(ctx, 0x3A8424u, gen::fn_itfMesManagerDrawSpriteEx_003a8710);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A8440 sub_3A8440 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesManagerCalcProc] The "CalcMsgMng" update: per slot in use, on its current handle sub_3A6E30, sub_3A7120,
// sub_3A7490 and the pop-in step sub_3A7DD0. Returns 0.
void sub_3A8440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8440
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(s1, v0, mes::kLoSlotList);  // 0x959ED0
    for (;;) {
        // 0x003a8498
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a8460
        charge(ctx, 14);
        lw(s0, s1, mes::kSlotHandle);
        a0 = s0;
        jal(ctx, 0x3A8468u, gen::fn_sub_3A6E30_003a6e30);
        a0 = s0;
        jal(ctx, 0x3A8474u, gen::fn_sub_3A7120_003a7120);
        a0 = s0;
        jal(ctx, 0x3A8480u, gen::fn_sub_3A7490_003a7490);
        a0 = s0;
        jal(ctx, 0x3A848Cu, gen::fn_sub_3A7DD0_003a7dd0);
        lw(s1, s1, mes::kSlotNext);
    }
    // 0x003a84a0
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A84C0 sub_3A84C0 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [itfMesManagerUpdateDrawTask] The "DrawMsgMng" update: itfMesManagerDrawMsg on every slot's handle, then the
// frame counter. Returns 0.
void sub_3A84C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a84c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(s0, v0, mes::kLoSlotList);  // 0x959ED0
    for (;;) {
        // 0x003a84ec
        charge(ctx, 4);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a84dc
        charge(ctx, 4);
        lw(a0, s0, mes::kSlotHandle);
        jal(ctx, 0x3A84E0u, gen::fn_itfMesManagerDrawMsg_003a7e90);
        lw(s0, s0, mes::kSlotNext);
    }
    // 0x003a84fc
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v0, v0, mes::kLoDrawFrames);  // 0x959EC8
    v1 = addiu(v0, 1);
    v0 = 0x960000;
    sw(v1, v0, mes::kLoDrawFrames);  // 0x959EC8
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A8530 sub_3A8530 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [itfMesManagerDestroyProc] Destroy callback of both manager tasks: sub_3A4DD0 on every slot id in use (the next
// slot read first), then 0x959EC4 = 0.
void sub_3A8530(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8530
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v1 = 0x960000;
    lw(v1, v1, mes::kLoSlotList);  // 0x959ED0
    for (;;) {
        // 0x003a8560
        charge(ctx, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a854c
        charge(ctx, 5);
        lw(s0, v1, mes::kSlotNext);
        lw(a0, v1, mes::kSlotId);
        jal(ctx, 0x3A8554u, gen::fn_sub_3A4DD0_003a4dd0);  // destroy the slot
        v1 = s0;
    }
    // 0x003a856c
    charge(ctx, 7);
    v1 = 0x960000;
    sw(zero, v1, mes::kLoDestroyed);  // 0x959EC4
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A8590 sub_3A8590 -- 108 bytes; frame 0x20
// [itfPnlCursorCorners] Copies the four corners {x0,y0} {x1,y0} {x1,y1} {x0,y1} of a panel into a 32-byte local
// that nothing reads (the stripped cursor draw); the zeroing loop before it runs only on a non-null frame address.
void sub_3A8590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29};
    // 0x003a8590
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = addiu(sp, 0x0);
    v1 = 32;
    if (a1 != 0) {
        for (;;) {
            // 0x003a85a4
            charge(ctx, 7);
            sb(zero, a1, 0);
            a1 = addiu(a1, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x003a85c0 (the shared epilogue, written out on this path)
    charge(ctx, 15);
    lw(a2, a0, pnl::kX0);
    sw(a2, sp, 0x0);
    lw(a1, a0, pnl::kY0);
    sw(a1, sp, 0x4);
    lw(v1, a0, pnl::kX1);
    sw(v1, sp, 0x8);
    sw(a1, sp, 0xC);
    sw(v1, sp, 0x10);
    lw(v1, a0, pnl::kY1);
    sw(v1, sp, 0x14);
    sw(a2, sp, 0x18);
    sw(v1, sp, 0x1C);
    sp = addiu(sp, 0x20);
}

// 0x003A8600 sub_3A8600 -- 72 bytes; frame 0x10: ra sp+0x0
// [itfMesMngSetPanelValueBySlot] sub_3AB2A0(panel 1 of the slot's handle, value).
void sub_3A8600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8600
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -24852);  // &0x959EEC
    v0 = addu(v0, v1);
    lw(v0, v0, 0);  // the slot's handle
    lw(a0, v0, mes::kPanel1);
    jal(ctx, 0x3A8630u, gen::fn_sub_3AB2A0_003ab2a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003A8650 sub_3A8650 -- 188 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesMngSetPanelRectBySlot] itfPnlSetPosition(panel 1 of the slot's handle, x0, y0, x1, y1, z) from
// (slot, x0, y0, z, x1, y1); K_Assert line 7477 on a null handle.
void sub_3A8650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8650
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s0 = t1;
    v0 = sll(a0, 1);
    v0 = addu(v0, a0);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -24852);  // &0x959EEC
    v0 = addu(v0, v1);
    lw(s5, v0, 0);  // the slot's handle
    if (s5 == 0) {
        // 0x003a86b0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 6768);  // "itfMesManager.c"
        a1 = 7477;
        jal(ctx, 0x3A86BCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003a86c4
    charge(ctx, 18);
    lw(a0, s5, mes::kPanel1);
    a1 = s4;
    a2 = s3;
    a3 = s1;
    t0 = s0;
    t1 = s2;
    jal(ctx, 0x3A86DCu, gen::fn_itfPnlSetPosition_003a8dc0);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003A8710 itfMesManagerDrawSpriteEx -- 188 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Draws sprite `id` of facility/i_mes_win01.spr (gp-0x469C) once at (x, y) with z $f12 and alpha `alpha`
// (inverse alpha 255 - alpha): sprCreateHandle(0, file, id), sprDrawSprite, sprDestroyHandle. Returns 0.
void itfMesManagerDrawSpriteEx(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x003a8710
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    mov_s(f20, f12);
    s1 = a2;
    a0 = 0;
    lw(a1, gp, fnt::kGpMesWinSpr);  // 0x7CE654
    a2 = a3;
    jal(ctx, 0x3A8748u, gen::fn_sprCreateHandle_001158b0);
    s0 = v0;
    mtc1(s3, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, spr::kHandleX);
    mtc1(s2, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, spr::kHandleY);
    swc1(f20, v0, spr::kHandleZ);
    a0 = 255;
    v1 = s1 & 0xFF;
    v1 = subu(a0, v1);
    sb(v1, v0, spr::kHandleInvAlpha);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x3A8790u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite(handle, 1)
    a0 = s0;
    jal(ctx, 0x3A879Cu, gen::fn_sub_115980_00115980);  // sprDestroyHandle
    v0 = 0;
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003A8D60 itfPnlRelease -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Frees a panel (debug print first): the work buffer's heap block when the panel has a work buffer, then the
// panel's own block. A null panel only prints.
void itfPnlRelease(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8d60
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0x6A0000;
    a0 = addiu(a0, 7536);  // "itfPnlRelease()\n"
    jal(ctx, 0x3A8D78u, gen::fn_printf_005225a8);  // printf (debug text)
    if (s0 != 0) {
        // 0x003a8d88
        charge(ctx, 3);
        lw(v0, s0, pnl::kWork);
        if (v0 != 0) {
            // 0x003a8d94
            charge(ctx, 3);
            lw(a0, s0, pnl::kWorkBlock);
            jal(ctx, 0x3A8D98u, gen::fn_sub_191A10_00191a10);  // H_Free
        }
        // 0x003a8da0
        charge(ctx, 3);
        lw(a0, s0, pnl::kBlock);
        jal(ctx, 0x3A8DA4u, gen::fn_sub_191A10_00191a10);  // H_Free
    }
    // 0x003a8dac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A8DC0 itfPnlSetPosition -- 220 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Sets a panel's rectangle and z (K_Assert line 590; debug print) and rebuilds its vertices through the
// per-type table 0x6A1C10 (itfPnlSetVertexType*: work buffer, x0, y0, x1, y1) when the type has one.
void itfPnlSetPosition(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8dc0
    enter(ctx, 16);  // entry check point + this block's cycles
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
    s2 = a2;
    s1 = a3;
    s0 = t0;
    s5 = t1;
    if (s4 == 0) {
        // 0x003a8e00
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 7160);  // "itfPanel.c"
        a1 = 590;
        jal(ctx, 0x3A8E0Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003a8e14
    charge(ctx, 17);
    a0 = 0x6A0000;
    a0 = addiu(a0, 7568);  // "itfPnlSetPosition()\n"
    jal(ctx, 0x3A8E1Cu, gen::fn_printf_005225a8);  // printf (debug text)
    sw(s3, s4, pnl::kX0);
    sw(s2, s4, pnl::kY0);
    sw(s1, s4, pnl::kX1);
    sw(s0, s4, pnl::kY1);
    sw(s5, s4, pnl::kZ);
    lbu(v1, s4, pnl::kType);
    a0 = sll(v1, 2);
    v1 = 0x6A0000;
    v1 = addiu(v1, 7184);  // &tbl_itfPnlSetPositionByType
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    if (v1 != 0) {
        // 0x003a8e58
        charge(ctx, 7);
        lw(a0, s4, pnl::kWork);
        a1 = s3;
        a2 = s2;
        a3 = s1;
        t0 = s0;
        jalr(ctx, 0x3A8E6Cu, v1.u());
    }
    // 0x003a8e74 (the shared epilogue, written out on this path)
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

// 0x003A8FB0 itfPnlSetColor -- 204 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Sets a panel's colour (K_Assert line 660; debug print) and its per-type colours through the table 0x6A1C50
// (itfPnlSetColorType*: work buffer, r, g, b, a) when the type has one.
void itfPnlSetColor(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a8fb0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    if (s4 == 0) {
        // 0x003a8fe8
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 7160);  // "itfPanel.c"
        a1 = 660;
        jal(ctx, 0x3A8FF4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003a8ffc
    charge(ctx, 16);
    a0 = 0x6A0000;
    a0 = addiu(a0, 7632);  // "itfPnlSetColor()\n"
    jal(ctx, 0x3A9004u, gen::fn_printf_005225a8);  // printf (debug text)
    sw(s3, s4, pnl::kR);
    sw(s2, s4, pnl::kG);
    sw(s1, s4, pnl::kB);
    sw(s0, s4, pnl::kA);
    lbu(v1, s4, pnl::kType);
    a0 = sll(v1, 2);
    v1 = 0x6A0000;
    v1 = addiu(v1, 7248);  // &tbl_itfPnlSetColorByType
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    if (v1 != 0) {
        // 0x003a903c
        charge(ctx, 7);
        lw(a0, s4, pnl::kWork);
        a1 = s3;
        a2 = s2;
        a3 = s1;
        t0 = s0;
        jalr(ctx, 0x3A9050u, v1.u());
    }
    // 0x003a9058 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003A9080 sub_3A9080 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [itfPnlDraw] Draws a panel: sub_3AC590 (an empty hook) and sub_3A90C0(panel, 0).
void sub_3A9080(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9080
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 0;
    jal(ctx, 0x3A9094u, gen::fn_sub_3AC590_003ac590);
    a0 = s0;
    a1 = 0;
    jal(ctx, 0x3A90A4u, gen::fn_sub_3A90C0_003a90c0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003A90C0 sub_3A90C0 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfPnlDrawByType] K_Assert line 726 on a null panel, then the panel's draw routine from
// itfMesManagerDrawTypeTbl 0x6A1C90[type] (panel, arg).
void sub_3A90C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a90c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x003a90e0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 7160);  // "itfPanel.c"
        a1 = 726;
        jal(ctx, 0x3A90ECu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003a90f4
    charge(ctx, 16);
    a0 = s1;
    a1 = s0;
    lbu(v0, s1, pnl::kType);
    v1 = sll(v0, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 7312);  // &itfMesManagerDrawTypeTbl
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    jalr(ctx, 0x3A9114u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003A9E20 sub_3A9E20 -- 168 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesManagerDrawType0] Draw type 0: the panel alpha into the work buffer's colour table, then three gouraud
// quads (sub_3B4B40: points, colours, the index lists 0x6A1EE0 + 4i / 0x6A1EF0 + 4i, z, arg).
void sub_3A9E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003a9e20
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    lw(s1, a0, pnl::kWork);
    s0 = addiu(s1, 64);
    lw(v1, a0, pnl::kA);
    sw(v1, s1, pnl::kType0Alpha);
    s2 = 0;
    for (;;) {
        // 0x003a9e98
        charge(ctx, 3);
        v1 = slti(s2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003a9e60
        charge(ctx, 14);
        v1 = sll(s2, 2);
        v0 = 0x6A0000;
        v0 = addiu(v0, 7904);  // &0x6A1EE0
        a2 = addu(v0, v1);
        v0 = 0x6A0000;
        v0 = addiu(v0, 7920);  // &0x6A1EF0
        a3 = addu(v0, v1);
        a0 = s1;
        a1 = s0;
        lw(t0, s4, pnl::kZ);
        t1 = s3;
        jal(ctx, 0x3A9E8Cu, gen::fn_sub_3B4B40_003b4b40);  // a gouraud quad
        s2 = addiu(s2, 1);
    }
    // 0x003a9ea4
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003AA280 sub_3AA280 -- 72 bytes; frame 0x10: ra sp+0x0
// [itfMesManagerDrawType4] Draw type 4: the alpha into the colour table, one gouraud quad (index lists 0x7CD4D0,
// 0x7CE624).
void sub_3AA280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aa280
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t0 = a0;
    t1 = a1;
    lw(v1, a0, pnl::kWork);
    a1 = addiu(v1, 32);
    lw(v0, a0, pnl::kA);
    sw(v0, v1, pnl::kType4Alpha);
    a0 = v1;
    a2 = addiu(gp, -22560);  // &0x7CD4D0
    a3 = addiu(gp, -18124);  // &0x7CE624
    lw(t0, t0, pnl::kZ);
    jal(ctx, 0x3AA2B0u, gen::fn_sub_3B4B40_003b4b40);  // a gouraud quad
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AA2D0 sub_3AA2D0 -- 160 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfMesManagerDrawType5] Draw type 5: the alpha into the colour table; the rest calls the empty hooks
// nullsub_118 / nullsub_116 (a stripped six-point draw over 0x7CD4D8 / 0x7CD4E0).
void sub_3AA2D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aa2d0
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v1, a0, pnl::kWork);
    s2 = addiu(v1, 48);
    lw(v0, a0, pnl::kA);
    sw(v0, v1, pnl::kType5Alpha);
    lw(s3, a0, pnl::kWork);
    a0 = s0;
    a1 = 2;
    a2 = 0;
    jal(ctx, 0x3AA310u, gen::fn_nullsub_118_003b4ed0);
    a0 = s3;
    a1 = s2;
    a2 = addiu(gp, -22552);  // &0x7CD4D8
    a3 = addiu(gp, -22544);  // &0x7CD4E0
    t0 = 6;
    lw(t1, s1, pnl::kZ);
    t2 = s0;
    jal(ctx, 0x3AA334u, gen::fn_nullsub_116_003b4eb0);
    a0 = s0;
    a1 = 0;
    a2 = 0;
    jal(ctx, 0x3AA348u, gen::fn_nullsub_118_003b4ed0);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003AB2A0 sub_3AB2A0 -- 120 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [itfPnlSetType12Value] K_Assert a non-null type-12 panel (lines 2059 / 2060), then work +4 = value.
void sub_3AB2A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ab2a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x003ab2c0
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 7160);  // "itfPanel.c"
        a1 = 2059;
        jal(ctx, 0x3AB2CCu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003ab2d4
    charge(ctx, 4);
    lbu(a0, s1, pnl::kType);
    v1 = 12;
    if (a0 != v1) {
        // 0x003ab2e4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 7160);  // "itfPanel.c"
        a1 = 2060;
        jal(ctx, 0x3AB2F0u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003ab2f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, s1, pnl::kWork);
    sw(s0, v1, pnl::kType12Value);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AC230 sub_3AC230 -- 8 bytes; leaf frame (no stack)
// [itfMesManagerDrawType14] Draw type 14: nothing.
void sub_3AC230(EEContext& ctx) {
    using namespace hg;
    // 0x003ac230
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003AC500 sub_3AC500 -- 132 bytes; frame 0x20: ra sp+0x0
// [itfMesManagerDrawType9] Draw type 9: the colour alpha at 0x6A212C = 103 * panel alpha / 128 (toward zero), the
// rectangle copied to a local, then sub_3B4D10(rect, colour 0x6A2120, z, 576, arg).
void sub_3AC500(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ac500
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a2 = a0;
    t0 = a1;
    lw(v1, a0, pnl::kA);
    v0 = 103;
    mult(v0, v1, v0);
    v1 = sra(v0, 7);
    if (i64(v0) < 0) {
        // 0x003ac528
        charge(ctx, 2);
        v0 = addiu(v0, 127);
        v1 = sra(v0, 7);
    }
    // 0x003ac530
    charge(ctx, 21);
    v0 = 0x6A0000;
    sw(v1, v0, pnl::kType9Alpha);  // 0x6A212C
    lw(v0, a2, pnl::kX0);
    sw(v0, sp, 0x10);
    lw(v0, a2, pnl::kY0);
    sw(v0, sp, 0x14);
    lw(v0, a2, pnl::kX1);
    sw(v0, sp, 0x18);
    lw(v0, a2, pnl::kY1);
    sw(v0, sp, 0x1C);
    a0 = addiu(sp, 0x10);
    a1 = 0x6A0000;
    a1 = addiu(a1, 8480);  // &0x6A2120
    lw(a2, a2, pnl::kZ);
    a3 = 576;
    jal(ctx, 0x3AC56Cu, gen::fn_sub_3B4D10_003b4d10);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003AC590 sub_3AC590 -- 8 bytes; leaf frame (no stack)
// [itfPnlDrawHook] An empty hook (sub_3A9080 calls it before every panel).
void sub_3AC590(EEContext& ctx) {
    using namespace hg;
    // 0x003ac590
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003AC5A0 sub_3AC5A0 -- 92 bytes; leaf frame (no stack)
// tag 0x02 (sFrTagTable 0x6A2370 [0x02]): colour set = b0 - 1. Returns 0.
void sub_3AC5A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003ac5a0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ac5d4
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ac5c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ac5dc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sb(v0, a1, lay::kColourSet);
    v0 = 0;
}

// 0x003AC600 sub_3AC600 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x03 (sFrTagTable 0x6A2370 [0x03]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; when message argument p (kTagSlotTable 0x95AC70) is set, the pending run is
// closed (sub_3B22A0) and argument p & 0xFF laid out (sub_3B1D90). Returns 0.
void sub_3AC600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ac600
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ac648
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ac63c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ac650
    charge(ctx, 12);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    s1 = v0 & 0xFFFF;
    v1 = sll(s1, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -21392);  // &0x95AC70
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x003ac680
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x3AC684u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
        a0 = s1 & 0xFF;
        a1 = s0;
        jal(ctx, 0x3AC694u, gen::fn_sub_3B1D90_003b1d90);  // lay out message argument $a0
    }
    // 0x003ac69c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AC6C0 sub_3AC6C0 -- 24 bytes; leaf frame (no stack)
// tag 0x04 (sFrTagTable 0x6A2370 [0x04]): tag flags |= 1; returns 1 (stops the layout).
void sub_3AC6C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003ac6c0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = v0 | 0x1;
    sw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = 1;
}

// 0x003AC6E0 sub_3AC6E0 -- 12 bytes; leaf frame (no stack)
// tag 0x05 (sFrTagTable 0x6A2370 [0x05]): nothing; returns 0.
void sub_3AC6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ac6e0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AC6F0 sub_3AC6F0 -- 92 bytes; leaf frame (no stack)
// tag 0x06 (sFrTagTable 0x6A2370 [0x06]): font style = b0 - 1. Returns 0.
void sub_3AC6F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003ac6f0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ac724
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ac718
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ac72c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sb(v0, a1, lay::kStyle);
    v0 = 0;
}

// 0x003AC750 sub_3AC750 -- 92 bytes; leaf frame (no stack)
// tag 0x07 (sFrTagTable 0x6A2370 [0x07]): alpha = b0 - 1. Returns 0.
void sub_3AC750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003ac750
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ac784
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ac778
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ac78c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sb(v0, a1, lay::kAlpha);
    v0 = 0;
}

// 0x003AC7B0 sub_3AC7B0 -- 12 bytes; leaf frame (no stack)
// tag 0x08 (sFrTagTable 0x6A2370 [0x08]): nothing; returns 0.
void sub_3AC7B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ac7b0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AC7C0 sub_3AC7C0 -- 92 bytes; leaf frame (no stack)
// tag 0x09 (sFrTagTable 0x6A2370 [0x09]): glyph mode = b0 - 1. Returns 0.
void sub_3AC7C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003ac7c0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ac7f4
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ac7e8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ac7fc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sb(v0, a1, lay::kMode);
    v0 = 0;
}

// 0x003AC820 sub_3AC820 -- 100 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x0A (sFrTagTable 0x6A2370 [0x0A]): lays out sprintf("%s", sub_177670(1)) -- a name string from the buffer at 0x833BB0 (inf: the
// hero's family name). Returns 0.
void sub_3AC820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ac820
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a0 = 1;
    jal(ctx, 0x3AC834u, gen::fn_sub_177670_00177670);
    a0 = addiu(sp, 0x28);
    a1 = addiu(gp, -22480);  // "%s"
    a2 = v0;
    jal(ctx, 0x3AC848u, gen::fn_sprintf_00523ac8);  // sprintf into the frame buffer
    a0 = s0;
    jal(ctx, 0x3AC854u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = addiu(sp, 0x28);
    a1 = s0;
    jal(ctx, 0x3AC864u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AC890 sub_3AC890 -- 100 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x0B (sFrTagTable 0x6A2370 [0x0B]): the same with sub_177790(1) (the buffer at 0x833BD0; inf: the given name). Returns 0.
void sub_3AC890(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ac890
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a0 = 1;
    jal(ctx, 0x3AC8A4u, gen::fn_sub_177790_00177790);
    a0 = addiu(sp, 0x28);
    a1 = addiu(gp, -22480);  // "%s"
    a2 = v0;
    jal(ctx, 0x3AC8B8u, gen::fn_sprintf_00523ac8);  // sprintf into the frame buffer
    a0 = s0;
    jal(ctx, 0x3AC8C4u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = addiu(sp, 0x28);
    a1 = s0;
    jal(ctx, 0x3AC8D4u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003ACA30 sub_3ACA30 -- 12 bytes; leaf frame (no stack)
// tag 0x0D (sFrTagTable 0x6A2370 [0x0D]): nothing; returns 0.
void sub_3ACA30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003aca30
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ACA40 sub_3ACA40 -- 12 bytes; leaf frame (no stack)
// tag 0x0E (sFrTagTable 0x6A2370 [0x0E]): nothing; returns 0.
void sub_3ACA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003aca40
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ACA50 sub_3ACA50 -- 56 bytes; frame 0x10: ra sp+0x0
// tag 0x0F (sFrTagTable 0x6A2370 [0x0F]): a new row (frFontLayoutNewRow) unless default glyph flag 4 is set. Returns 0.
void sub_3ACA50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aca50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(v0, gp, lay::kGpGlyphFlags);  // 0x7CD500
    v0 = v0 & 0x4;
    if (v0 == 0) {
        // 0x003aca68
        charge(ctx, 3);
        a0 = a1;
        jal(ctx, 0x3ACA6Cu, gen::fn_frFontLayoutNewRow_003b2400);
    }
    // 0x003aca74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ACA90 sub_3ACA90 -- 24 bytes; leaf frame (no stack)
// tag 0x10 (sFrTagTable 0x6A2370 [0x10]): tag flags |= 2; returns 0.
void sub_3ACA90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003aca90
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = v0 | 0x2;
    sw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = 0;
}

// 0x003ACAB0 sub_3ACAB0 -- 92 bytes; frame 0x10: ra sp+0x0
// tag 0x11 (sFrTagTable 0x6A2370 [0x11]): with default glyph flag 8: tag flags |= 1 and returns 1 (stop); else a new row when flag 0x20
// is set; returns 0.
void sub_3ACAB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003acab0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lh(v1, gp, lay::kGpGlyphFlags);  // 0x7CD500
    v0 = v1 & 0x8;
    if (v0 == 0) {
        // 0x003acae0
        charge(ctx, 3);
        v0 = v1 & 0x20;
        if (v0 != 0) {
            // 0x003acaec
            charge(ctx, 3);
            a0 = a1;
            jal(ctx, 0x3ACAF0u, gen::fn_frFontLayoutNewRow_003b2400);
        }
        // 0x003acaf8
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003acac8
        charge(ctx, 6);
        lw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
        v0 = v0 | 0x1;
        sw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
        v0 = 1;
    }
    // 0x003acafc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ACB10 sub_3ACB10 -- 172 bytes; leaf frame (no stack)
// tag 0x12 (sFrTagTable 0x6A2370 [0x12]): alpha = b0 - 1, line code = parameter 1 (bytes 2, 3). Returns 0.
void sub_3ACB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003acb10
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003acb44
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003acb38
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003acb4c
    charge(ctx, 15);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sb(v0, a1, lay::kAlpha);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003acb94
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003acb88
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003acb9c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sh(v0, a1, lay::kLineCode);
    v0 = 0;
}

// 0x003ACDA0 sub_3ACDA0 -- 192 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x48 (sFrTagTable 0x6A2370 [0x48]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; with flag 388 set and default glyph flag 0x100 clear, sub_10A2E0(2, 2, p) (a sound
// request; inf: a voice line). Returns 0.
void sub_3ACDA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003acda0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003acde0
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003acdd4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003acde8
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s0 = v1 | v0;
    a0 = 388;
    jal(ctx, 0x3ACDFCu, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x003ace18
        charge(ctx, 4);
        lh(v0, gp, lay::kGpGlyphFlags);  // 0x7CD500
        v0 = v0 & 0x100;
        if (v0 == 0) {
            // 0x003ace34
            charge(ctx, 6);
            a0 = 2;
            a1 = a0;
            a2 = s0;
            jal(ctx, 0x3ACE40u, gen::fn_sub_10A2E0_0010a2e0);  // sound request
            v0 = 0;
        } else {
            // 0x003ace28
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003ace0c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ace4c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003ACF80 sub_3ACF80 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x4A (sFrTagTable 0x6A2370 [0x4A]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; with flag 388 set, sub_10A2E0(2, 2, p). Returns 0.
void sub_3ACF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003acf80
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003acfc0
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003acfb4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003acfc8
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s0 = v1 | v0;
    a0 = 388;
    jal(ctx, 0x3ACFDCu, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x003acff8
        charge(ctx, 6);
        a0 = 2;
        a1 = a0;
        a2 = s0;
        jal(ctx, 0x3AD004u, gen::fn_sub_10A2E0_0010a2e0);  // sound request
        v0 = 0;
    } else {
        // 0x003acfec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad010 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003AD030 sub_3AD030 -- 248 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x4B (sFrTagTable 0x6A2370 [0x4B]): parameters p0, p1; with flag 388 set, sub_10A2E0(p0, 2, p1). Returns 0.
void sub_3AD030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ad030
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad074
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad068
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad07c
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s0 = v1 | v0;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad0c0
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad0b4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad0c8
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s1 = v1 | v0;
    a0 = 388;
    jal(ctx, 0x3AD0DCu, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x003ad0f8
        charge(ctx, 6);
        a0 = s0;
        a1 = 2;
        a2 = s1;
        jal(ctx, 0x3AD104u, gen::fn_sub_10A2E0_0010a2e0);  // sound request
        v0 = 0;
    } else {
        // 0x003ad0ec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad110 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AD130 sub_3AD130 -- 128 bytes; leaf frame (no stack)
// tag 0x14 (sFrTagTable 0x6A2370 [0x14]): a wait on the current line: +0x38 = 1 when a wait is armed (+0x34), +0x30 = the tag code,
// +0x3C = parameter 0 ticks. Returns 0.
void sub_3AD130(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003ad130
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a1, lay::kLine);
    lw(v0, v1, lay::kWaitArmed);
    if (v0 != 0) {
        // 0x003ad140
        charge(ctx, 2);
        v0 = 1;
        sw(v0, v1, lay::kWaitFlag);
    }
    // 0x003ad148
    charge(ctx, 12);
    lw(v0, a1, lay::kLine);
    sw(a0, v0, lay::kWaitCode);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad184
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad178
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad18c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v1 = v1 | v0;
    lw(v0, a1, lay::kLine);
    sw(v1, v0, lay::kWaitTicks);
    v0 = 0;
}

// 0x003AD1B0 sub_3AD1B0 -- 228 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x15 (sFrTagTable 0x6A2370 [0x15]): the same wait, ticks = (s16) parameter 0 with flag 388 set, else 35; clamped at 0.
void sub_3AD1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ad1b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, lay::kLine);
    lw(v0, v1, lay::kWaitArmed);
    if (v0 != 0) {
        // 0x003ad1d0
        charge(ctx, 2);
        v0 = 1;
        sw(v0, v1, lay::kWaitFlag);
    }
    // 0x003ad1d8
    charge(ctx, 7);
    lw(v0, s0, lay::kLine);
    sw(a0, v0, lay::kWaitCode);
    a0 = 388;
    jal(ctx, 0x3AD1E4u, gen::fn_datGetFlag_0016f190);
    if (v0 != 0) {
        // 0x003ad208
        charge(ctx, 10);
        lw(v1, s0, lay::kPos);
        lw(v0, s0, lay::kText);
        v1 = addu(v0, v1);
        lbu(v0, v1, 0);
        v0 = addiu(v0, -1);
        a0 = v0 & 0xFF;
        lbu(v1, v1, 1);
        v0 = 255;
        if (v1 != v0) {
            // 0x003ad23c
            charge(ctx, 2);
            v0 = addiu(v1, -1);
            v0 = v0 & 0xFF;
        } else {
            // 0x003ad230
            charge(ctx, 3);
            v0 = 0;
        }
        // 0x003ad244
        charge(ctx, 8);
        v0 = v0 & 0xFF;
        v1 = sll(v0, 8);
        v0 = a0 & 0xFF;
        v0 = v1 | v0;
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        lw(v0, s0, lay::kLine);
        sw(v1, v0, lay::kWaitTicks);
    } else {
        // 0x003ad1f4
        charge(ctx, 5);
        v1 = 35;
        lw(v0, s0, lay::kLine);
        sw(v1, v0, lay::kWaitTicks);
    }
    // 0x003ad264
    charge(ctx, 5);
    lw(v0, s0, lay::kLine);
    v1 = addiu(v0, 60);
    lw(v0, v0, lay::kWaitTicks);
    if (i64(v0) < 0) {
        // 0x003ad278
        charge(ctx, 1);
        sw(zero, v1, 0);  // negative ticks -> 0
    }
    // 0x003ad27c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003AD2A0 sub_3AD2A0 -- 184 bytes; leaf frame (no stack)
// tag 0x16 (sFrTagTable 0x6A2370 [0x16]): parameters p0 / p1 to 0x7CE628 / 0x7CE62C, tag flags |= 8. Returns 0.
void sub_3AD2A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003ad2a0
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad2d4
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad2c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad2dc
    charge(ctx, 15);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sw(v0, gp, lay::kGpTag16A);  // 0x7CE628
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad324
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad318
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad32c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    sw(v0, gp, lay::kGpTag16B);  // 0x7CE62C
    lw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = v0 | 0x8;
    sw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = 0;
}

// 0x003AD360 sub_3AD360 -- 20 bytes; leaf frame (no stack)
// tag 0x17 (sFrTagTable 0x6A2370 [0x17]): arms a wait on the current line (+0x34 = the tag code). Returns 0.
void sub_3AD360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003ad360
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a1, lay::kLine);
    sw(a0, v0, lay::kWaitArmed);
    v0 = 0;
}

// 0x003AD380 sub_3AD380 -- 116 bytes; leaf frame (no stack)
// tag 0x18 (sFrTagTable 0x6A2370 [0x18]): with parameter 0 equal to 0, 0x7CE634 = 20. Returns 0.
void sub_3AD380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x003ad380
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad3b4
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad3a8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad3bc
    charge(ctx, 6);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    if (v0 == 0) {
        // 0x003ad3e0
        charge(ctx, 3);
        v0 = 20;
        sw(v0, gp, lay::kGpTag18);  // 0x7CE634
        v0 = 0;
    } else {
        // 0x003ad3d4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad3ec (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003AD640 sub_3AD640 -- 256 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x19 (sFrTagTable 0x6A2370 [0x19]): A parameter is the byte pair (b0, b1) -> (b0 - 1) | (b1 == 0xFF ? 0 : b1 - 1) << 8; when message argument p is set: with colour set 3, the glyph 0x83D5 then argument p
// & 0xFF laid out; the colour set restored. Returns 0.
void sub_3AD640(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ad640
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad68c
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad680
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad694
    charge(ctx, 12);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    s0 = v0 & 0xFFFF;
    v1 = sll(s0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -21392);  // &0x95AC70
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x003ad6c4
        charge(ctx, 23);
        lbu(s2, s1, lay::kColourSet);  // saved
        v0 = 3;
        sb(v0, s1, lay::kColourSet);
        v0 = si(-125);
        sb(v0, sp, 0x48);
        v0 = si(-43);
        sb(v0, sp, 0x49);
        sb(zero, sp, 0x4A);
        a0 = s1;
        jal(ctx, 0x3AD6E8u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
        a0 = addiu(sp, 0x48);
        a1 = s1;
        jal(ctx, 0x3AD6F8u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
        a0 = s1;
        jal(ctx, 0x3AD704u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
        a0 = s0 & 0xFF;
        a1 = s1;
        jal(ctx, 0x3AD714u, gen::fn_sub_3B1D90_003b1d90);  // lay out message argument $a0
        sb(s2, s1, lay::kColourSet);  // restored
    }
    // 0x003ad720 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003AD860 sub_3AD860 -- 208 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x1B (sFrTagTable 0x6A2370 [0x1B]): when message argument p is set, argument p & 0xFF laid out with colour set 3. Returns 0.
void sub_3AD860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ad860
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad8ac
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad8a0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad8b4
    charge(ctx, 12);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    s0 = v0 & 0xFFFF;
    v1 = sll(s0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -21392);  // &0x95AC70
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x003ad8e4
        charge(ctx, 11);
        lbu(s2, s1, lay::kColourSet);  // saved
        v0 = 3;
        sb(v0, s1, lay::kColourSet);
        a0 = s1;
        jal(ctx, 0x3AD8F4u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
        a0 = s0 & 0xFF;
        a1 = s1;
        jal(ctx, 0x3AD904u, gen::fn_sub_3B1D90_003b1d90);  // lay out message argument $a0
        sb(s2, s1, lay::kColourSet);  // restored
    }
    // 0x003ad910 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003AD930 sub_3AD930 -- 208 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x1C (sFrTagTable 0x6A2370 [0x1C]): the same as tag 0x1B. Returns 0.
void sub_3AD930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ad930
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ad97c
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ad970
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ad984
    charge(ctx, 12);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    s0 = v0 & 0xFFFF;
    v1 = sll(s0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -21392);  // &0x95AC70
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x003ad9b4
        charge(ctx, 11);
        lbu(s2, s1, lay::kColourSet);  // saved
        v0 = 3;
        sb(v0, s1, lay::kColourSet);
        a0 = s1;
        jal(ctx, 0x3AD9C4u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
        a0 = s0 & 0xFF;
        a1 = s1;
        jal(ctx, 0x3AD9D4u, gen::fn_sub_3B1D90_003b1d90);  // lay out message argument $a0
        sb(s2, s1, lay::kColourSet);  // restored
    }
    // 0x003ad9e0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003ADA00 sub_3ADA00 -- 256 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x1D (sFrTagTable 0x6A2370 [0x1D]): with colour set 3: the glyph 0x83D5, then the name sub_171110((s16) p, 0) returns (a table
// lookup over 0x5DABF0.. of g_data.c); the colour set restored. Returns 0.
void sub_3ADA00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ada00
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    s1 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ada50
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        s2 = v0 & 0xFF;
    } else {
        // 0x003ada44
        charge(ctx, 3);
        s2 = 0;
    }
    // 0x003ada58
    charge(ctx, 42);
    v0 = si(-125);
    sb(v0, sp, 0x58);
    v0 = si(-43);
    sb(v0, sp, 0x59);
    sb(zero, sp, 0x5A);
    lbu(s0, s3, lay::kColourSet);  // saved
    v0 = 3;
    sb(v0, s3, lay::kColourSet);
    a0 = s3;
    jal(ctx, 0x3ADA7Cu, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = addiu(sp, 0x58);
    a1 = s3;
    jal(ctx, 0x3ADA8Cu, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    a0 = s3;
    jal(ctx, 0x3ADA98u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    v0 = s2 & 0xFF;
    v1 = sll(v0, 8);
    v0 = s1 & 0xFF;
    v0 = v1 | v0;
    v0 = v0 & 0xFFFF;
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    jal(ctx, 0x3ADAC0u, gen::fn_sub_171110_00171110);
    a0 = v0;
    a1 = s3;
    jal(ctx, 0x3ADAD0u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    sb(s0, s3, lay::kColourSet);  // restored
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003ADB00 sub_3ADB00 -- 128 bytes; frame 0x10: ra sp+0x0
// tag 0x1E (sFrTagTable 0x6A2370 [0x1E]): sub_3AD400((u16) p, 2, code, layout). Returns 0.
void sub_3ADB00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003adb00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a0;
    a3 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003adb44
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003adb38
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003adb4c
    charge(ctx, 13);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    a0 = v0 & 0xFFFF;
    a1 = 2;
    jal(ctx, 0x3ADB64u, gen::fn_sub_3AD400_003ad400);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ADD00 sub_3ADD00 -- 36 bytes; frame 0x10: ra sp+0x0
// tag 0x20 (sFrTagTable 0x6A2370 [0x20]): sub_3CF520() (a flag-389 / 0x7CE680 check of the facility layer). Returns 0.
void sub_3ADD00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003add00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3ADD08u, gen::fn_sub_3CF520_003cf520);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ADD30 sub_3ADD30 -- 12 bytes; leaf frame (no stack)
// tag 0x21 (sFrTagTable 0x6A2370 [0x21]): nothing; returns 0.
void sub_3ADD30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003add30
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ADE60 sub_3ADE60 -- 12 bytes; leaf frame (no stack)
// tag 0x23 (sFrTagTable 0x6A2370 [0x23]): nothing; returns 0.
void sub_3ADE60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ade60
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ADE70 sub_3ADE70 -- 196 bytes; frame 0x10: ra sp+0x0
// tag 0x24 (sFrTagTable 0x6A2370 [0x24]): sub_3BB060(p0, p1) (the scene layer, mt_sceneFunc.c). Returns 0.
void sub_3ADE70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ade70
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003adeac
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003adea0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003adeb4
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a0 = v1 | v0;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a1 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003adef8
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003adeec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003adf00
    charge(ctx, 13);
    a0 = a0 & 0xFFFF;
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a1 & 0xFF;
    v0 = v1 | v0;
    a1 = v0 & 0xFFFF;
    jal(ctx, 0x3ADF18u, gen::fn_sub_3BB060_003bb060);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003ADF40 sub_3ADF40 -- 12 bytes; leaf frame (no stack)
// tag 0x25 (sFrTagTable 0x6A2370 [0x25]): nothing; returns 0.
void sub_3ADF40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003adf40
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ADF50 sub_3ADF50 -- 12 bytes; leaf frame (no stack)
// tag 0x26 (sFrTagTable 0x6A2370 [0x26]): nothing; returns 0.
void sub_3ADF50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003adf50
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ADF60 sub_3ADF60 -- 12 bytes; leaf frame (no stack)
// tag 0x27 (sFrTagTable 0x6A2370 [0x27]): nothing; returns 0.
void sub_3ADF60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003adf60
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003ADF70 sub_3ADF70 -- 144 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x28 (sFrTagTable 0x6A2370 [0x28]): clndGetCurrentWeekDay() (result unused), then sub_16E2B0(sub_16DD40(), p) (g_data.c). Returns 0.
void sub_3ADF70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003adf70
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003adfb0
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003adfa4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003adfb8
    charge(ctx, 18);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s0 = v1 | v0;
    jal(ctx, 0x3ADFC8u, gen::fn_clndGetCurrentWeekDay_0017db00);
    jal(ctx, 0x3ADFD0u, gen::fn_sub_16DD40_0016dd40);  // the u16 at 0x836274
    a0 = v0;
    a1 = s0;
    jal(ctx, 0x3ADFE0u, gen::fn_sub_16E2B0_0016e2b0);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003AE140 sub_3AE140 -- 12 bytes; leaf frame (no stack)
// tag 0x2A (sFrTagTable 0x6A2370 [0x2A]): nothing; returns 0.
void sub_3AE140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ae140
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AE150 sub_3AE150 -- 12 bytes; leaf frame (no stack)
// tag 0x2B (sFrTagTable 0x6A2370 [0x2B]): nothing; returns 0.
void sub_3AE150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ae150
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AE160 sub_3AE160 -- 252 bytes; frame 0x30: ra sp+0x0
// tag 0x32 (sFrTagTable 0x6A2370 [0x32]): datSetFlag({0, 0x400, 0xC00, 0x1000, 0x1400}[p0] + p1, 1): sets a flag of bank p0 (the table
// 0x6A2680 copied to the frame). Returns 0.
void sub_3AE160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae160
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae19c
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae190
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae1a4
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a3 = v1 | v0;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae1e8
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae1dc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae1f0
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a2 = v1 | v0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 9856);  // &0x6A2680
    a0 = addiu(sp, 0x10);
    v1 = 5;
    for (;;) {
        // 0x003ae210
        charge(ctx, 7);
        lw(v0, a1, 0);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(v0, a0, 0);
        a0 = addiu(a0, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ae22c
    charge(ctx, 12);
    v0 = sll(a3, 2);
    v0 = addu(v0, sp);
    lw(v0, v0, 16);
    a0 = addu(a2, v0);
    a1 = 1;
    jal(ctx, 0x3AE240u, gen::fn_datSetFlag_0016f1f0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE260 sub_3AE260 -- 252 bytes; frame 0x30: ra sp+0x0
// tag 0x33 (sFrTagTable 0x6A2370 [0x33]): the same with datSetFlag(..., 0): clears the flag. Returns 0.
void sub_3AE260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae260
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae29c
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae290
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae2a4
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a3 = v1 | v0;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae2e8
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae2dc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae2f0
    charge(ctx, 8);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a2 = v1 | v0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 9856);  // &0x6A2680
    a0 = addiu(sp, 0x10);
    v1 = 5;
    for (;;) {
        // 0x003ae310
        charge(ctx, 7);
        lw(v0, a1, 0);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(v0, a0, 0);
        a0 = addiu(a0, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ae32c
    charge(ctx, 12);
    v0 = sll(a3, 2);
    v0 = addu(v0, sp);
    lw(v0, v0, 16);
    a0 = addu(a2, v0);
    a1 = 0;
    jal(ctx, 0x3AE340u, gen::fn_datSetFlag_0016f1f0);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE360 sub_3AE360 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x2C (sFrTagTable 0x6A2370 [0x2C]): lays out string sub_17C860(p) of row p of the phrase table 0x6A24D0 (four pointers a row:
// "Sayonara", "Mata na", "Ja ne", "Hasta la vista", ...). Returns 0.
void sub_3AE360(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae360
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae3a8
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae39c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae3b0
    charge(ctx, 27);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    s1 = v1 | v0;
    a0 = s0;
    jal(ctx, 0x3AE3C4u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = s1;
    jal(ctx, 0x3AE3D0u, gen::fn_sub_17C860_0017c860);
    a0 = sll(v0, 2);
    v1 = sll(s1, 4);
    v0 = 0x6A0000;
    v0 = addiu(v0, 9424);  // &0x6A24D0
    v0 = addu(v0, v1);
    v0 = addu(a0, v0);
    lw(a0, v0, 0);
    a1 = s0;
    jal(ctx, 0x3AE3F8u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE560 sub_3AE560 -- 228 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x2E (sFrTagTable 0x6A2370 [0x2E]): lays out club name sub_16E190(p) of the table 0x6A25C0 ("Go-home", "Track Team", ...,
// "Music Club"; K_Assert line 747 when above 6). Returns 0.
void sub_3AE560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae560
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae5a8
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae59c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae5b0
    charge(ctx, 11);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x3AE5C8u, gen::fn_sub_16E190_0016e190);
    s1 = v0;
    if (i64(s1) >= 0) {
        // 0x003ae5dc
        charge(ctx, 3);
        v0 = sltiu(s1, 7);
        if (v0 == 0) {
            goto L_003ae5e8;
        }
        goto L_003ae5fc;
    }
L_003ae5e8:
    charge(ctx, 5);
    a0 = 0x6A0000;
    a0 = addiu(a0, 9880);  // "frTagTable.c"
    a1 = 747;
    jal(ctx, 0x3AE5F4u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
L_003ae5fc:
    charge(ctx, 18);
    a0 = s0;
    jal(ctx, 0x3AE600u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    v1 = sll(s1, 2);
    v0 = 0x6A0000;
    v0 = addiu(v0, 9664);  // &0x6A25C0
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    a1 = s0;
    jal(ctx, 0x3AE620u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE650 sub_3AE650 -- 256 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x2F (sFrTagTable 0x6A2370 [0x2F]): copies the text from the read position up to the next 10 (two-byte glyphs and tag parameters
// skipped whole) into the zeroed buffer 0x95ABF0, NUL-terminated; tag flags |= 0x10; the read position moves past
// it. Returns 0.
void sub_3AE650(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae650
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = 0;
    lw(v1, a1, lay::kPos);
    lw(v0, a1, lay::kText);
    a2 = addu(v0, v1);
    a0 = 240;
    v0 = 10;
    for (;;) {
        // 0x003ae6bc
        charge(ctx, 6);
        v1 = s0;
        s0 = addiu(s0, 1);
        v1 = addu(a2, v1);
        lbu(v1, v1, 0);
        if (v1 == v0) {
            break;
        }
        backedge(ctx);
        // 0x003ae684
        charge(ctx, 3);
        a1 = v1 & 0xF0;
        if (a1 != a0) {
            // 0x003ae6ac
            charge(ctx, 3);
            v1 = sltiu(v1, 128);
            if (v1 == 0) {
                // 0x003ae6b8
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
        } else {
            // 0x003ae690
            charge(ctx, 7);
            v1 = v1 & 0xF;
            v1 = addiu(v1, -1);
            v1 = sll(v1, 1);
            v1 = addiu(v1, 1);
            s0 = addu(s0, v1);
        }
    }
    // 0x003ae6d4
    charge(ctx, 31);
    a0 = 0x960000;
    a0 = addiu(a0, -21520);  // &0x95ABF0
    a1 = 0;
    a2 = 128;
    jal(ctx, 0x3AE6E4u, gen::fn_memset_00521408);
    lw(v1, s1, lay::kText);
    lw(v0, s1, lay::kPos);
    a1 = addu(v1, v0);
    a0 = 0x960000;
    a0 = addiu(a0, -21520);  // &0x95ABF0
    a2 = s0;
    jal(ctx, 0x3AE704u, gen::fn_memcpy_00521250);
    v0 = 0x960000;
    v0 = addiu(v0, -21521);  // &0x95ABEF
    v0 = addu(v0, s0);
    sb(zero, v0, 0);
    lw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = v0 | 0x10;
    sw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    lw(v0, s1, lay::kPos);
    v0 = addu(v0, s0);
    sw(v0, s1, lay::kPos);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE750 sub_3AE750 -- 208 bytes; frame 0x10: ra sp+0x0
// tag 0x30 (sFrTagTable 0x6A2370 [0x30]): sub_170C00(1, p0, p1) (g_data.c). Returns 0.
void sub_3AE750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae750
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae78c
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae780
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae794
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a2 = v1 | v0;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v1, v0);
    lbu(v0, v1, 2);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 3);
    v0 = 255;
    if (v1 != v0) {
        // 0x003ae7d8
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003ae7cc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ae7e0
    charge(ctx, 16);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    a1 = dsll32(a2, 16);
    a1 = dsra32(a1, 16);
    a2 = dsll32(v0, 16);
    a2 = dsra32(a2, 16);
    a0 = 1;
    jal(ctx, 0x3AE804u, gen::fn_sub_170C00_00170c00);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AE820 sub_3AE820 -- 24 bytes; leaf frame (no stack)
// tag 0x31 (sFrTagTable 0x6A2370 [0x31]): tag flags |= 3; returns 1 (stops the layout).
void sub_3AE820(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003ae820
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = v0 | 0x3;
    sw(v0, gp, lay::kGpTagFlags);  // 0x7CD4E8
    v0 = 1;
}

// 0x003AE840 sub_3AE840 -- 12 bytes; leaf frame (no stack)
// tag 0x34 (sFrTagTable 0x6A2370 [0x34]): nothing; returns 0.
void sub_3AE840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ae840
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AE850 sub_3AE850 -- 12 bytes; leaf frame (no stack)
// tag 0x35 (sFrTagTable 0x6A2370 [0x35]): nothing; returns 0.
void sub_3AE850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ae850
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AE860 sub_3AE860 -- 12 bytes; leaf frame (no stack)
// tag 0x36 (sFrTagTable 0x6A2370 [0x36]): nothing; returns 0.
void sub_3AE860(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ae860
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003AE870 sub_3AE870 -- 96 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x37 (sFrTagTable 0x6A2370 [0x37]): lays out the current month, sprintf("%d", clndGetCurrentMonth()). Returns 0.
void sub_3AE870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae870
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3AE880u, gen::fn_clndGetCurrentMonth_0017d920);
    a0 = addiu(sp, 0x28);
    a1 = addiu(gp, -22476);  // "%d"
    a2 = v0;
    jal(ctx, 0x3AE894u, gen::fn_sprintf_00523ac8);  // sprintf into the frame buffer
    a0 = s0;
    jal(ctx, 0x3AE8A0u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = addiu(sp, 0x28);
    a1 = s0;
    jal(ctx, 0x3AE8B0u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE8D0 sub_3AE8D0 -- 96 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x38 (sFrTagTable 0x6A2370 [0x38]): lays out the current day of the month (clndGetCurrentDay). Returns 0.
void sub_3AE8D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae8d0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3AE8E0u, gen::fn_clndGetCurrentDay_0017da40);
    a0 = addiu(sp, 0x28);
    a1 = addiu(gp, -22476);  // "%d"
    a2 = v0;
    jal(ctx, 0x3AE8F4u, gen::fn_sprintf_00523ac8);  // sprintf into the frame buffer
    a0 = s0;
    jal(ctx, 0x3AE900u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = addiu(sp, 0x28);
    a1 = s0;
    jal(ctx, 0x3AE910u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AE930 sub_3AE930 -- 56 bytes; frame 0x10: ra sp+0x0
// tag 0x39 (sFrTagTable 0x6A2370 [0x39]): sub_171C40(sub_16DD40(), 1) (g_data.c). Returns 0.
void sub_3AE930(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae930
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3AE938u, gen::fn_sub_16DD40_0016dd40);  // the u16 at 0x836274
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    a1 = 1;
    jal(ctx, 0x3AE94Cu, gen::fn_sub_171C40_00171c40);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AE970 sub_3AE970 -- 56 bytes; frame 0x10: ra sp+0x0
// tag 0x3A (sFrTagTable 0x6A2370 [0x3A]): sub_171C40(sub_16DD40(), 0). Returns 0.
void sub_3AE970(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae970
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3AE978u, gen::fn_sub_16DD40_0016dd40);  // the u16 at 0x836274
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    jal(ctx, 0x3AE98Cu, gen::fn_sub_171C40_00171c40);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AE9B0 sub_3AE9B0 -- 148 bytes; frame 0x70: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x3B (sFrTagTable 0x6A2370 [0x3B]): lays out the weekday glyph of clndGetCurrentWeekDay() from the 7 x 8-byte table 0x6A26B0
// (copied to the frame). Returns 0.
void sub_3AE9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ae9b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a2 = 0x6A0000;
    a2 = addiu(a2, 9904);  // &0x6A26B0
    a1 = addiu(sp, 0x30);
    a0 = 28;
    for (;;) {
        // 0x003ae9d4
        charge(ctx, 9);
        lb(v1, a2, 0);
        lb(v0, a2, 1);
        a2 = addiu(a2, 2);
        a0 = addiu(a0, -1);
        sb(v1, a1, 0);
        sb(v0, a1, 1);
        a1 = addiu(a1, 2);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ae9f8
    charge(ctx, 19);
    jal(ctx, 0x3AE9F8u, gen::fn_clndGetCurrentWeekDay_0017db00);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x3AEA08u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    v0 = sll(s1, 3);
    v0 = addu(v0, sp);
    a0 = addiu(v0, 48);
    a1 = s0;
    jal(ctx, 0x3AEA20u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003AEC20 sub_3AEC20 -- 240 bytes; frame 0x40: ra sp+0x10, s0 sp+0x0 (sq)
// tag 0x3D (sFrTagTable 0x6A2370 [0x3D]): lays out the element icon of skill p: the glyph 0x8D, table0x6A26F0[datCalcGetSkillElement(0, p)]
// - 90 (the 19-byte table copied to the frame). Returns 0.
void sub_3AEC20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aec20
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003aec64
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003aec58
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003aec6c
    charge(ctx, 14);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    v0 = v1 | v0;
    a1 = v0 & 0xFFFF;
    a0 = 0;
    jal(ctx, 0x3AEC84u, gen::fn_datCalcGetSkillElement_003082f0);
    a2 = dsll32(v0, 16);
    a2 = dsra32(a2, 16);
    a1 = 0x6A0000;
    a1 = addiu(a1, 9968);  // &0x6A26F0
    a0 = addiu(sp, 0x20);
    v1 = 19;
    for (;;) {
        // 0x003aeca4
        charge(ctx, 7);
        lb(v0, a1, 0);
        a1 = addiu(a1, 1);
        v1 = addiu(v1, -1);
        sb(v0, a0, 0);
        a0 = addiu(a0, 1);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003aecc0
    charge(ctx, 20);
    v0 = si(-115);
    sb(v0, sp, 0x3C);
    v0 = addu(a2, sp);
    lb(v0, v0, 32);
    v0 = addiu(v0, -90);
    sb(v0, sp, 0x3D);
    sb(zero, sp, 0x3E);
    a0 = s0;
    jal(ctx, 0x3AECE0u, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = addiu(sp, 0x3C);
    a1 = s0;
    jal(ctx, 0x3AECF0u, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003AED10 sub_3AED10 -- 240 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// tag 0x3E (sFrTagTable 0x6A2370 [0x3E]): lays out sub_3C3F80 [comuGetLinkTitle] of p, or of sub_16DD40() when p is 0 (K_Assert line
// 908 when that is 0 too). Returns 0.
void sub_3AED10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aed10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    lw(v1, a1, lay::kPos);  // read position: the first parameter byte
    lw(v0, a1, lay::kText);  // the text
    v1 = addu(v0, v1);
    lbu(v0, v1, 0);
    v0 = addiu(v0, -1);
    a0 = v0 & 0xFF;
    lbu(v1, v1, 1);
    v0 = 255;
    if (v1 != v0) {
        // 0x003aed58
        charge(ctx, 2);
        v0 = addiu(v1, -1);
        v0 = v0 & 0xFF;
    } else {
        // 0x003aed4c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003aed60
    charge(ctx, 6);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 8);
    v0 = a0 & 0xFF;
    a0 = v1 | v0;
    if (a0 != 0) {
        // 0x003aedbc
        charge(ctx, 3);
        jal(ctx, 0x3AEDBCu, gen::fn_sub_3C3F80_003c3f80);
        s1 = v0;
    } else {
        // 0x003aed78
        charge(ctx, 6);
        jal(ctx, 0x3AED78u, gen::fn_sub_16DD40_0016dd40);  // the u16 at 0x836274
        s1 = dsll32(v0, 16);
        s1 = dsra32(s1, 16);
        if (s1 == 0) {
            // 0x003aed90
            charge(ctx, 5);
            a0 = 0x6A0000;
            a0 = addiu(a0, 9880);  // "frTagTable.c"
            a1 = 908;
            jal(ctx, 0x3AED9Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
        }
        // 0x003aeda4
        charge(ctx, 6);
        a0 = s1;
        jal(ctx, 0x3AEDA8u, gen::fn_sub_3C3F80_003c3f80);
        s1 = v0;
    }
    // 0x003aedc8
    charge(ctx, 14);
    a0 = s0;
    jal(ctx, 0x3AEDCCu, gen::fn_sub_3B22A0_003b22a0);  // close the layout's pending glyph run
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x3AEDDCu, gen::fn_sub_3B2020_003b2020);  // lay out the string in $a0
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003AEE00 sub_3AEE00 -- 28 bytes; leaf frame (no stack)
// tag 0x3F (sFrTagTable 0x6A2370 [0x3F]): alpha = 20, line code = 32. Returns 0.
void sub_3AEE00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5};
    // 0x003aee00
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 20;
    sb(v0, a1, lay::kAlpha);
    v0 = 32;
    sh(v0, a1, lay::kLineCode);
    v0 = 0;
}

// 0x003AF520 sub_3AF520 -- 56 bytes; frame 0x10: ra sp+0x0
// tag 0x44 (sFrTagTable 0x6A2370 [0x44]): sub_172200(sub_16DD40(), 1) (g_data.c). Returns 0.
void sub_3AF520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003af520
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3AF528u, gen::fn_sub_16DD40_0016dd40);  // the u16 at 0x836274
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    a1 = 1;
    jal(ctx, 0x3AF53Cu, gen::fn_sub_172200_00172200);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AF560 sub_3AF560 -- 56 bytes; frame 0x10: ra sp+0x0
// tag 0x45 (sFrTagTable 0x6A2370 [0x45]): sub_172200(sub_16DD40(), 0). Returns 0.
void sub_3AF560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003af560
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3AF568u, gen::fn_sub_16DD40_0016dd40);  // the u16 at 0x836274
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    jal(ctx, 0x3AF57Cu, gen::fn_sub_172200_00172200);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AF770 frLoadFontData_Ptr -- 40 bytes; frame 0x10: ra sp+0x0
// frAddFontStyle(style, 0, fnt): adds a font style from a .FNT already in memory (sub_27ACE0).
void frLoadFontData_Ptr(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003af770
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0;
    jal(ctx, 0x3AF780u, gen::fn_frAddFontStyle_003afad0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AFA40 sub_3AFA40 -- 144 bytes; frame 0x10: ra sp+0x0
// [frFontSystemEnd] Destroy callback of the task "fontMan": frees the font styles, releases both deferred line
// lists, destroys the glyph and line ring buffers (sub_3B4740), the GS list (sub_3B44A0), hands the buffers
// 0x95AE24 / 0x95AE28 to nullsub_21 and frees the raster-slot manager (sub_3B3740).
void sub_3AFA40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003afa40
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3AFA48u, gen::fn_frFreeFontStyles_003afe30);
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoReleaseList0);  // 0x95AE60
    jal(ctx, 0x3AFA58u, gen::fn_sub_3B0030_003b0030);  // nodes back to the ring buffers
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoReleaseList1);  // 0x95AE64
    jal(ctx, 0x3AFA68u, gen::fn_sub_3B0030_003b0030);  // nodes back to the ring buffers
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoGlyphRing);  // 0x95AE1C
    jal(ctx, 0x3AFA78u, gen::fn_sub_3B4740_003b4740);
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoLineRing);  // 0x95AE20
    jal(ctx, 0x3AFA88u, gen::fn_sub_3B4740_003b4740);
    jal(ctx, 0x3AFA90u, gen::fn_sub_3B44A0_003b44a0);
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoBuffer24);  // 0x95AE24
    jal(ctx, 0x3AFAA0u, gen::fn_nullsub_21_0035ac80);
    v0 = 0x960000;
    lw(a0, v0, fnt::kLoBuffer28);  // 0x95AE28
    jal(ctx, 0x3AFAB0u, gen::fn_nullsub_21_0035ac80);
    jal(ctx, 0x3AFAB8u, gen::fn_sub_3B3740_003b3740);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AFC30 sub_3AFC30 -- 64 bytes; frame 0x10: ra sp+0x0
// [frFreeFontStyleBlock] RwFree of the first word of font style `style` (sFrFontStyles 0x95ACF0, 32 bytes a
// style; sub_27AFD0).
void sub_3AFC30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003afc30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a0 & 0xFF;
    v1 = sll(v0, 5);
    v0 = 0x960000;
    v0 = addiu(v0, -21264);  // &sFrFontStyles
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x3AFC58u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003AFF50 frFontPrintClutData -- 124 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Debug: six times an empty 16-step loop and printf("load clut data for font :%s\n", "frFont.c").
void frFontPrintClutData(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003aff50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    for (;;) {
        // 0x003affac
        charge(ctx, 3);
        v1 = slti(s0, 6);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003aff68
        charge(ctx, 3);
        v1 = 0;
        for (;;) {
            // 0x003aff78
            charge(ctx, 6);
            v0 = slti(v1, 16);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003aff74
            charge(ctx, 1);
            v1 = addiu(v1, 1);
        }
        // 0x003aff90
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10000);  // "load clut data for font :%s\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, 10032);  // "frFont.c"
        jal(ctx, 0x3AFFA0u, gen::fn_printf_005225a8);  // printf (debug text)
        s0 = addiu(s0, 1);
    }
    // 0x003affb8
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003AFFD0 sub_3AFFD0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [frFontLineReleaseFaded2] A copy of sub_3B0170 (sub_3A7490 calls this one).
void sub_3AFFD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003affd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x3AFFE0u, gen::fn_frFontLineFadeStep_003b0ec0);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    if (v0 == 0) {
        // 0x003b0000
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x3B0004u, gen::fn_sub_3B0030_003b0030);  // nodes back to the ring buffers
        s0 = v0;
    } else {
        // 0x003afff8
        charge(ctx, 2);
    }
    // 0x003b0010 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B0170 sub_3B0170 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [frFontLineReleaseFaded] Steps a line chain's fade (frFontLineFadeStep); once nothing changed any more the
// chain's nodes go back to the ring buffers (sub_3B0030). Returns the chain or sub_3B0030's result.
void sub_3B0170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b0170
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x3B0180u, gen::fn_frFontLineFadeStep_003b0ec0);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    if (v0 == 0) {
        // 0x003b01a0
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x3B01A4u, gen::fn_sub_3B0030_003b0030);  // nodes back to the ring buffers
        s0 = v0;
    } else {
        // 0x003b0198
        charge(ctx, 2);
    }
    // 0x003b01b0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B03A0 frFontRegisterGlyphRaster -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Takes a GS-list entry (fmGslAllocEntry; K_Abort "FONT SYS : GS buffer over flow." line 1599 when none) and
// its raster slot (+0x14; K_Assert line 1604), marks the slot (+4 = 1) and links it back to the entry (+8).
// Returns the slot.
void frFontRegisterGlyphRaster(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b03a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3B03B0u, gen::fn_fmGslAllocEntry_003b4520);
    s0 = v0;
    if (s0 == 0) {
        // 0x003b03c4
        charge(ctx, 7);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10288);  // "FONT SYS : GS buffer over flow.\n"
        a1 = 0x6A0000;
        a1 = addiu(a1, 10032);  // "frFont.c"
        a2 = 1599;
        jal(ctx, 0x3B03D8u, gen::fn_sub_19D400_0019d400);  // K_Abort: `jr $ra` in retail
    }
    // 0x003b03e0
    charge(ctx, 3);
    lw(s1, s0, fnt::kEntrySlot);
    if (s1 == 0) {
        // 0x003b03ec
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10032);  // "frFont.c"
        a1 = 1604;
        jal(ctx, 0x3B03F8u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003b0400 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = 1;
    sh(v0, s1, fnt::kSlotGlyph);
    sw(s0, s1, fnt::kSlotEntry);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B1300 sub_3B1300 -- 36 bytes; frame 0x10: ra sp+0x0
// [itfMesManagerFontDraw] sub_3B1330(line, 0) (itfMesManagerDrawMsg).
void sub_3B1300(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b1300
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 0;
    jal(ctx, 0x3B130Cu, gen::fn_sub_3B1330_003b1330);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B1330 sub_3B1330 -- 36 bytes; frame 0x10: ra sp+0x0
// [itfMesManagerFontDraw2] frFontDraw(line, skip, the word at 0x7CE630).
void sub_3B1330(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b1330
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, gp, lay::kGpDrawMode);  // 0x7CE630
    jal(ctx, 0x3B133Cu, gen::fn_frFontDraw_003b1360);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B18C0 sub_3B18C0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [frFontManUpdate] The task "fontMan"'s update: releases deferred line list sub_35AEA0() (0x95AE60 + 4i;
// sub_35AEA0 returns 0) through sub_3B0030 and stores the result back, then ages the raster slots
// (frFontRasterAgeSlots). Returns 0.
void sub_3B18C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b18c0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3B18CCu, gen::fn_sub_35AEA0_0035aea0);
    v0 = v0 & 0xFF;
    v1 = sll(v0, 2);
    v0 = 0x960000;
    v0 = addiu(v0, -20896);  // &0x95AE60
    s0 = addu(v0, v1);
    lw(a0, s0, 0);  // the list
    jal(ctx, 0x3B18ECu, gen::fn_sub_3B0030_003b0030);  // nodes back to the ring buffers
    sw(v0, s0, 0);  // what sub_3B0030 left
    jal(ctx, 0x3B18F8u, gen::fn_frFontRasterAgeSlots_003b3770);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B19A0 frSetMessageFontStyle -- 44 bytes; frame 0x10: ra sp+0x0
// frAddFontStyle(8, fnt, 0): binds a message's own font as style 8 (itfMesMngRequestMessage for "MSG1").
void frSetMessageFontStyle(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b19a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = a0;
    a0 = 8;
    a2 = 0;
    jal(ctx, 0x3B19B4u, gen::fn_frAddFontStyle_003afad0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B2900 sub_3B2900 -- 60 bytes; frame 0x20: ra sp+0x10
// [frFontLayoutTextSimple] sub_3B2990(x, y, 0, 0, 0, 0, 255, text, chain): a text layout with style 0, colour
// set 0, mode 0, alpha 255 (sub_3A4B90).
void sub_3B2900(EEContext& ctx) {
    using namespace hg;
    Gpr a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b2900
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    t3 = a2;
    sd(a3, sp, 0x0);
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    t2 = 255;
    jal(ctx, 0x3B2924u, gen::fn_sub_3B2990_003b2990);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x003B2940 sub_3B2940 -- 80 bytes; frame 0x20: ra sp+0x10
// [frFontLayoutTextAt] sub_3B2990(x, y, 0, style, colour set, mode, alpha, text, chain): the layout with colour
// word 0 (the message manager's name and text lines).
void sub_3B2940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b2940
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    t6 = a2;
    t5 = a3;
    t4 = t0;
    v1 = t1;
    v0 = t2;
    sd(t3, sp, 0x0);
    a2 = 0;
    a3 = t6;
    t0 = t5;
    t1 = t4;
    t2 = v1;
    t3 = v0;
    jal(ctx, 0x3B2978u, gen::fn_sub_3B2990_003b2990);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x003B2990 sub_3B2990 -- 104 bytes; frame 0x30: ra sp+0x0
// [frFontLayoutText] Builds the 48-byte FrTextLayout record on its frame -- x, y, 16 * colour, style, colour
// set, mode, alpha, text, chain, position 0, new-line 1, position-pending 1, line code 32 -- and runs the
// layout (sub_3B2430). Returns the line chain.
void sub_3B2990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b2990
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    sw(a0, sp, 0x10);
    sw(a1, sp, 0x14);
    v0 = sll(a2, 4);
    sw(v0, sp, 0x18);
    sb(a3, sp, 0x1C);
    sb(t0, sp, 0x1D);
    sb(t1, sp, 0x1E);
    sb(t2, sp, 0x1F);
    sw(t3, sp, 0x20);
    lw(v0, sp, 0x30);
    sw(v0, sp, 0x24);
    sw(zero, sp, 0x28);
    v0 = 1;
    sb(v0, sp, 0x2C);
    sb(v0, sp, 0x2D);
    v0 = 32;
    sh(v0, sp, 0x2E);
    a0 = addiu(sp, 0x10);
    jal(ctx, 0x3B29E0u, gen::fn_sub_3B2430_003b2430);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B2C60 sub_3B2C60 -- 80 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [frFontLineSetZ] K_Assert(line) ("frFontEx.c" line 19), then the line's z (+0x14) = $f12. 18 callers.
void sub_3B2C60(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x003b2c60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    mov_s(f20, f12);
    if (s0 == 0) {
        // 0x003b2c80
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 10376);  // "frFontEx.c"
        a1 = 19;
        jal(ctx, 0x3B2C8Cu, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): `jr $ra` in retail, the path continues
    }
    // 0x003b2c94 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    swc1(f20, s0, fnt::kLineZ);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003B3740 sub_3B3740 -- 48 bytes; frame 0x10: ra sp+0x0
// [frFontRasterSlotsFree] RwFree of the raster-slot manager (gp-0x46AC), which is then cleared.
void sub_3B3740(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b3740
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, fnt::kGpRasterSlots);  // 0x7CE644
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x3B3754u, v0.u());
    sw(zero, gp, fnt::kGpRasterSlots);  // 0x7CE644
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B3D60 frFontRasterFindOrAlloc -- 112 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// The raster slot of (glyph, colour): frFontRasterLookup, else frFontRasterAllocSlot; 0 when both fail.
void frFontRasterFindOrAlloc(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b3d60
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a1 = s0;
    jal(ctx, 0x3B3D84u, gen::fn_frFontRasterLookup_003b3e00);
    if (v0 == 0) {
        // 0x003b3d94
        charge(ctx, 7);
        a0 = s2;
        a1 = s1;
        a2 = s0;
        jal(ctx, 0x3B3DA0u, gen::fn_frFontRasterAllocSlot_003b3e60);
        if (v0 == 0) {
            // 0x003b3db0
            charge(ctx, 1);
            v0 = 0;
        }
    }
    // 0x003b3db4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003B44A0 sub_3B44A0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fmGslFree] When the GS list exists (0x95AEBC), RwFrees its two blocks (0x95AEA0, 0x95AEA4), clears it and returns
// 1; else 0.
void sub_3B44A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b44a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 0x960000;
    lw(v0, v0, fnt::kLoGslList);  // 0x95AEBC
    if (v0 != 0) {
        // 0x003b44c8
        charge(ctx, 15);
        s0 = 0x960000;
        s0 = addiu(s0, 380);  // &0x96017C
        v0 = 0x960000;
        lw(a0, v0, fnt::kLoGslBlock0);  // 0x95AEA0
        lw(v0, s0, 0);  // 0x96017C
        jalr(ctx, 0x3B44DCu, v0.u());
        v0 = 0x960000;
        lw(a0, v0, fnt::kLoGslBlock1);  // 0x95AEA4
        lw(v0, s0, 0);  // 0x96017C
        jalr(ctx, 0x3B44F0u, v0.u());
        v0 = 0x960000;
        sw(zero, v0, fnt::kLoGslList);  // 0x95AEBC
        v0 = 1;
    } else {
        // 0x003b44bc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003b4504 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003B45F0 sub_3B45F0 -- 184 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [rbInitRingBuf] A ring buffer of `count` records of `size` bytes: RwMalloc((size + 8) * (count + 1) + 4,
// 0x40000), the block's own address in its first word, then count + 1 headers {index, next} chained (each
// record 8 + size bytes), the last {count, first}. Returns the first record (block + 4).
void sub_3B45F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b45f0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    v1 = addiu(s2, 8);
    v0 = addiu(s1, 1);
    mult(v0, v1, v0);
    a0 = addiu(v0, 4);
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kMalloc);  // 0x960178
    jalr(ctx, 0x3B4628u, v0.u());
    sw(v0, sp, 0x4C);
    s0 = v0;
    a0 = s0;
    a1 = addiu(sp, 0x4C);
    a2 = 4;
    jal(ctx, 0x3B4644u, gen::fn_memcpy_00521250);
    a0 = addiu(s0, 4);
    v1 = 0;
    for (;;) {
        // 0x003b4674
        charge(ctx, 3);
        v0 = slt(v1, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003b465c
        charge(ctx, 6);
        sw(v1, a0, 0);
        v0 = addu(a0, s2);
        v0 = addiu(v0, 8);
        sw(v0, a0, 4);
        a0 = v0;
        v1 = addiu(v1, 1);
    }
    // 0x003b4680
    charge(ctx, 10);
    sw(s1, a0, 0);
    v0 = addiu(s0, 4);
    sw(v0, a0, 4);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003B4740 sub_3B4740 -- 48 bytes; frame 0x10: ra sp+0x0
// [rbDestroy] RwFree of the block in front of a ring buffer (its word -4). Returns 1.
void sub_3B4740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b4740
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, -4);
    v0 = 0x960000;
    lw(v0, v0, rw::kFree);  // 0x96017C
    jalr(ctx, 0x3B4754u, v0.u());
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003B4A90 sub_3B4A90 -- 164 bytes; leaf frame (no stack)
// [itfPnlShadeColours] For `n` 16-byte entries of a 16.16 shade table: dst = {min(r * t.r, 0xFF0000) >> 16,
// the same for g (MMI mult1) and b, alpha}; dst advances 16 bytes. itfPnlSetColorType1..3 call it.
void sub_3B4A90(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14};
    // 0x003b4a90
    enter(ctx, 3);  // entry check point + this block's cycles
    t3 = 0xFF0000;
    for (;;) {
        // 0x003b4b24
        charge(ctx, 2);
        if (i64(t2) <= 0) {
            break;
        }
        backedge(ctx);
        // 0x003b4a9c
        charge(ctx, 11);
        lw(v1, t1, pnl::kShadeR);
        mult(t6, a1, v1);
        lw(v1, t1, pnl::kShadeG);
        mult1(t5, a2, v1);
        lw(v1, t1, pnl::kShadeB);
        mult(t4, a3, v1);
        at = 0xFF0000;
        at = at | 0x1;  // &0xFF0001
        at = slt(t6, at);
        if (at == 0) {
            // 0x003b4ac8
            charge(ctx, 1);
            t6 = t3;
        }
        // 0x003b4acc
        charge(ctx, 5);
        at = 0xFF0000;
        at = at | 0x1;  // &0xFF0001
        at = slt(t5, at);
        if (at == 0) {
            // 0x003b4ae0
            charge(ctx, 1);
            t5 = t3;
        }
        // 0x003b4ae4
        charge(ctx, 5);
        at = 0xFF0000;
        at = at | 0x1;  // &0xFF0001
        at = slt(t4, at);
        if (at == 0) {
            // 0x003b4af8
            charge(ctx, 1);
            t4 = t3;
        }
        // 0x003b4afc
        charge(ctx, 10);
        v1 = sra(t6, 16);
        sw(v1, a0, 0);
        v1 = sra(t5, 16);
        sw(v1, a0, 4);
        v1 = sra(t4, 16);
        sw(v1, a0, 8);
        sw(t0, a0, pnl::kOutA);
        t2 = addiu(t2, -1);
        t1 = addiu(t1, 16);
        a0 = addiu(a0, 16);
    }
    // 0x003b4b2c
    charge(ctx, 2);
}

// 0x003B4E90 nullsub_119 -- 8 bytes; leaf frame (no stack)
// An empty hook of the panel draws (sub_3AA370, sub_3AC240, sub_3AC350).
void nullsub_119(EEContext& ctx) {
    using namespace hg;
    // 0x003b4e90
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003B4EA0 nullsub_121 -- 8 bytes; leaf frame (no stack)
// An empty hook (sub_3AC240).
void nullsub_121(EEContext& ctx) {
    using namespace hg;
    // 0x003b4ea0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003B4EB0 nullsub_116 -- 8 bytes; leaf frame (no stack)
// An empty hook: the stripped point draw of draw types 1, 2, 5.
void nullsub_116(EEContext& ctx) {
    using namespace hg;
    // 0x003b4eb0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003B4EC0 nullsub_117 -- 8 bytes; leaf frame (no stack)
// An empty hook (draw types 1, 2, 3).
void nullsub_117(EEContext& ctx) {
    using namespace hg;
    // 0x003b4ec0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003B4ED0 nullsub_118 -- 8 bytes; leaf frame (no stack)
// An empty hook: the stripped render-state set of draw type 5.
void nullsub_118(EEContext& ctx) {
    using namespace hg;
    // 0x003b4ed0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x003B4EE0 frFontSystemStart -- 224 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// The font / message system start (kwlnInitMain): msgWinReset, the task "fclBank" (kwlnTaskInitEx: 6320,
// fclBank_UpdateTask) stored into sub_3CF120's record, frInitFontTable(256, 256), the task "fontMan" (4196,
// update sub_3B18C0, destroy sub_3AFA40), the message manager (sub_3A4CE0), fclMisc_CreateMsgAssistTask, then
// facility/i_mes_win01.spr read synchronously (H_Cdvd_Request + H_Cdvd_ReadSync) and registered with
// sprAddFile into gp-0x469C.
void frFontSystemStart(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003b4ee0
    enter(ctx, 56);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3B4EECu, gen::fn_msgWinReset_003c7270);
    jal(ctx, 0x3B4EF4u, gen::fn_sub_3CF120_003cf120);
    s0 = v0;
    a0 = addiu(gp, -22464);  // "fclBank"
    a1 = 6320;
    a2 = 0;
    a3 = 0;
    t0 = 0x3D0000;
    t0 = addiu(t0, -432);  // &fclBank_UpdateTask
    t1 = 0;
    t2 = 0;
    jal(ctx, 0x3B4F20u, gen::fn_kwlnTaskInitEx_00194e10);
    sw(v0, s0, 0);
    a0 = 256;
    a1 = a0;
    jal(ctx, 0x3B4F34u, gen::fn_frInitFontTable_003af7a0);
    a0 = addiu(gp, -22456);  // "fontMan"
    a1 = 4196;
    a2 = 0;
    a3 = 0;
    t0 = 0x3B0000;
    t0 = addiu(t0, 6336);  // &sub_3B18C0
    t1 = 0x3B0000;
    t1 = addiu(t1, -1472);  // &sub_3AFA40
    t2 = 0;
    jal(ctx, 0x3B4F60u, gen::fn_kwlnTaskInitEx_00194e10);
    jal(ctx, 0x3B4F68u, gen::fn_sub_3A4CE0_003a4ce0);
    jal(ctx, 0x3B4F70u, gen::fn_fclMisc_CreateMsgAssistTask_003c88d0);
    a0 = 0x6A0000;
    a0 = addiu(a0, 10816);  // "facility/i_mes_win01.spr"
    a1 = 0;
    jal(ctx, 0x3B4F84u, gen::fn_H_Cdvd_Request_00100d80);
    a0 = v0;
    jal(ctx, 0x3B4F90u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 0x6A0000;
    a0 = addiu(a0, 10816);  // "facility/i_mes_win01.spr"
    jal(ctx, 0x3B4FA0u, gen::fn_sprAddFile_00112370);
    sw(v0, gp, fnt::kGpMesWinSpr);  // 0x7CE654
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
